#include "csapp.h"
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

#define MAXARGS 128
#define MAXJOBS 32

typedef struct {
    pid_t pid;
    int jid;
    int state;
    char cmdline[MAXLINE];
} job_t;

enum job_state { UNDEF, FG, BG, ST };

job_t job_list[MAXJOBS];

int nextjid = 1;

void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void sigchld_handler(int sig);
void list_jobs();
int add_job(pid_t pid, int state, char *cmdline);
int delete_job(pid_t pid);
int fgpid();
void do_bgfg(char **argv);
void waitfg(pid_t pid);
int pid2jid(pid_t pid);
pid_t jid2pid(int jid);

int main() {
    char cmdline[MAXLINE];

    Signal(SIGCHLD, sigchld_handler);

    while (1) {
        printf("> ");
        Fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin))
            exit(0);

        eval(cmdline);
    }
}

void eval(char *cmdline) {
    char *argv[MAXARGS];
    char buf[MAXLINE];
    int bg;
    pid_t pid;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);

    if (argv[0] == NULL)
        return;

    if (!builtin_command(argv)) {
        if ((pid = Fork()) == 0) {   // Child runs user job
            if (execvp(argv[0], argv) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }
        
        int state = bg ? BG : FG;
        add_job(pid, state, cmdline);

        if (!bg)
            waitfg(pid);
        else
            printf("[%d] (%d) %s", nextjid, pid, cmdline);
    }
}

int builtin_command(char **argv) {
    if (!strcmp(argv[0], "quit"))
        exit(0);
    if (!strcmp(argv[0], "jobs")) {
        list_jobs();
        return 1;
    }
    if (!strcmp(argv[0], "bg") || !strcmp(argv[0], "fg")) {
        do_bgfg(argv);
        return 1;
    }
    return 0;
}

/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv) 
{
    char *delim;         /* Points to first space delimiter */
    int argc;            /* Number of args */
    int bg;              /* Background job? */

    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* Ignore blank line */
	return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
	argv[--argc] = NULL;

    return bg;
}

void sigchld_handler(int sig) {
    int olderrno = errno;
    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
        if (WIFSTOPPED(status))
            printf("Job [%d] (%d) stopped by signal %d\n", pid2jid(pid), pid, WSTOPSIG(status));
        else if (WIFSIGNALED(status))
            printf("Job [%d] (%d) terminated by signal %d\n", pid2jid(pid), pid, WTERMSIG(status));
        else if (WIFEXITED(status))
            printf("Job [%d] (%d) exited with status %d\n", pid2jid(pid), pid, WEXITSTATUS(status));
        delete_job(pid);
    }

    errno = olderrno;
}

void list_jobs() {
    for (int i = 0; i < MAXJOBS; i++) {
        if (job_list[i].pid != 0) {
            printf("[%d] (%d) %s", job_list[i].jid, job_list[i].pid, job_list[i].cmdline);
        }
    }
}

int add_job(pid_t pid, int state, char *cmdline) {
    for (int i = 0; i < MAXJOBS; i++) {
        if (job_list[i].pid == 0) {
            job_list[i].pid = pid;
            job_list[i].state = state;
            job_list[i].jid = nextjid++;
            if (nextjid > MAXJOBS)
                nextjid = 1;
            strcpy(job_list[i].cmdline, cmdline);
            return 1;
        }
    }
    printf("Tried to create too many jobs\n");
    return 0;
}

int delete_job(pid_t pid) {
    for (int i = 0; i < MAXJOBS; i++) {
        if (job_list[i].pid == pid) {
            job_list[i].pid = 0;
            job_list[i].cmdline[0] = '\0';
            return 1;
        }
    }
    return 0;
}

int fgpid() {
    for (int i = 0; i < MAXJOBS; i++) {
        if (job_list[i].state == FG)
            return job_list[i].pid;
    }
    return 0;
}

void do_bgfg(char **argv) {
    int jid;
    pid_t pid;
    char *id = argv[1];

    if (id == NULL) {
        printf("%s command requires PID or %%jobid argument\n", argv[0]);
        return;
    }

    if (id[0] == '%') { // JID
        jid = atoi(&id[1]);
        if (!(pid = jid2pid(jid))) {
            printf("%s: No such job\n", id);
            return;
        }
    } else if (isdigit(id[0])) { // PID
        pid = atoi(id);
        if (!(jid = pid2jid(pid))) {
            printf("(%d): No such process\n", pid);
            return;
        }
    } else {
        printf("%s: argument must be a PID or %%jobid\n", argv[0]);
        return;
    }

    job_t *job = &job_list[jid - 1];
    if (!strcmp(argv[0], "bg")) {
        job->state = BG;
        printf("[%d] (%d) %s", jid, pid, job->cmdline);
        Kill(-pid, SIGCONT);
    } else if (!strcmp(argv[0], "fg")) {
        job->state = FG;
        Kill(-pid, SIGCONT);
        waitfg(pid);
    }
}

void waitfg(pid_t pid) {
    while (pid == fgpid())
        sleep(1);
}

int pid2jid(pid_t pid) {
    for (int i = 0; i < MAXJOBS; i++) {
        if (job_list[i].pid == pid) {
            return job_list[i].jid;
        }
    }
    return 0;
}

pid_t jid2pid(int jid) {
    for (int i = 0; i < MAXJOBS; i++) {
        if (job_list[i].jid == jid) {
            return job_list[i].pid;
        }
    }
    return 0;
}
