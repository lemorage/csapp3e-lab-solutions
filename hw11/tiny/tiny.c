/* $begin tinymain */
/*
 * tiny.c - A simple, iterative HTTP/1.0 Web server that uses the 
 *     GET method to serve static and dynamic content.
 *
 * Updated 11/2019 droh 
 *   - Fixed sprintf() aliasing issue in serve_static(), and clienterror().
 */
#include "csapp.h"

void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg);
char* get_header_value(rio_t *rp, char *header_name);
void send_static_headers(int fd, char *filename, int filesize);

void sigchld_handler(int sig) {
    while (waitpid(-1, 0, WNOHANG) > 0);
    return;
}

void sigpipe_handler(int sig) {
    printf("Received SIGPIPE signal. Handling it gracefully.\n");
    return;
}

int main(int argc, char **argv) 
{
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    /* Check command line args */
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(1);
    }

    listenfd = Open_listenfd(argv[1]);
    Signal(SIGCHLD, sigchld_handler);
    Signal(SIGPIPE, sigpipe_handler);
    while (1) {
	clientlen = sizeof(clientaddr);
	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); //line:netp:tiny:accept
        Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, 
                    port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
	doit(connfd);                                             //line:netp:tiny:doit
	Close(connfd);                                            //line:netp:tiny:close
    }
}
/* $end tinymain */

/*
 * doit - handle one HTTP request/response transaction
 */
/* $begin doit */
void doit(int fd) 
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;
    int content_length = 0;
    char *post_data = NULL;  // Declare post_data

    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    if (!Rio_readlineb(&rio, buf, MAXLINE))  //line:netp:doit:readrequest
        return;
    printf("\033[1mRequest lines:\n\033[0m");
    printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);       //line:netp:doit:parserequest
    if (strcasecmp(method, "GET") && strcasecmp(method, "HEAD")) {                     //line:netp:doit:beginrequesterr
        clienterror(fd, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return;
    }                                                    //line:netp:doit:endrequesterr
    read_requesthdrs(&rio);                              //line:netp:doit:readrequesthdrs

    if (strcasecmp(method, "POST") == 0) {
        // Extract content length from headers
        content_length = atoi(get_header_value(&rio, "Content-Length"));
        Rio_readnb(&rio, post_data, content_length);
        strcpy(cgiargs, post_data); // Use post_data as CGI arguments
        is_static = 0;
    } else {
        // Parse URI from GET request
        is_static = parse_uri(uri, filename, cgiargs);
    }

    if (stat(filename, &sbuf) < 0) {                     //line:netp:doit:beginnotfound
	clienterror(fd, filename, "404", "Not found",
		    "Tiny couldn't find this file");
	return;
    }                                                    //line:netp:doit:endnotfound

    if (is_static) { /* Serve static content */
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
            clienterror(fd, filename, "403", "Forbidden",
                        "Tiny couldn't read the file");
            return;
        }

        // If the method is HEAD, only send headers
        if (strcasecmp(method, "HEAD") == 0) {
            send_static_headers(fd, filename, sbuf.st_size);
        } else {
            serve_static(fd, filename, sbuf.st_size);
        }
    } else { /* Serve dynamic content */
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
            clienterror(fd, filename, "403", "Forbidden",
                        "Tiny couldn't run the CGI program");
            return;
        }
        serve_dynamic(fd, filename, cgiargs);
    }
}
/* $end doit */

void send_static_headers(int fd, char *filename, int filesize) {
    char filetype[MAXLINE], headers[MAXBUF];

    get_filetype(filename, filetype);
    strcpy(headers, "HTTP/1.0 200 OK\r\n");  // Initialize headers with the first string
    strcat(headers, "Server: Tiny Web Server\r\n");
    char content_length[MAXLINE];
    sprintf(content_length, "Content-length: %d\r\n", filesize);
    strcat(headers, content_length);
    char content_type[MAXLINE];
    sprintf(content_type, "Content-type: %s\r\n\r\n", filetype);
    strcat(headers, content_type);
    Rio_writen(fd, headers, strlen(headers));
}

char* get_header_value(rio_t *rp, char *header_name) {
    // Function to extract a specific header value from the request headers
    static char buf[MAXLINE], header_val[MAXLINE];
    Rio_readlineb(rp, buf, MAXLINE);
    while (strcmp(buf, "\r\n")) {
        if (strstr(buf, header_name)) {
            sscanf(buf, "%*s %s", header_val);
            return header_val;
        }
        Rio_readlineb(rp, buf, MAXLINE);
    }
    return NULL;
}

/*
 * read_requesthdrs - read HTTP request headers
 */
/* $begin read_requesthdrs */
void read_requesthdrs(rio_t *rp) 
{
    char buf[MAXLINE];

    Rio_readlineb(rp, buf, MAXLINE);
    printf("\033[1mRequest headers:\n\033[0m");
    printf("%s", buf);
    while(strcmp(buf, "\r\n")) {          //line:netp:readhdrs:checkterm
	Rio_readlineb(rp, buf, MAXLINE);
	printf("%s", buf);
    }
    return;
}
/* $end read_requesthdrs */

/*
 * parse_uri - parse URI into filename and CGI args
 *             return 0 if dynamic content, 1 if static
 */
/* $begin parse_uri */
int parse_uri(char *uri, char *filename, char *cgiargs) 
{
    char *ptr;

    if (!strstr(uri, "cgi-bin")) {  /* Static content */ //line:netp:parseuri:isstatic
	strcpy(cgiargs, "");                             //line:netp:parseuri:clearcgi
	strcpy(filename, ".");                           //line:netp:parseuri:beginconvert1
	strcat(filename, uri);                           //line:netp:parseuri:endconvert1
	if (uri[strlen(uri)-1] == '/')                   //line:netp:parseuri:slashcheck
	    strcat(filename, "home.html");               //line:netp:parseuri:appenddefault
	return 1;
    }
    else {  /* Dynamic content */                        //line:netp:parseuri:isdynamic
	ptr = index(uri, '?');                           //line:netp:parseuri:beginextract
	if (ptr) {
	    strcpy(cgiargs, ptr+1);
	    *ptr = '\0';
	}
	else 
	    strcpy(cgiargs, "");                         //line:netp:parseuri:endextract
	strcpy(filename, ".");                           //line:netp:parseuri:beginconvert2
	strcat(filename, uri);                           //line:netp:parseuri:endconvert2
	return 0;
    }
}
/* $end parse_uri */

/*
 * serve_static - copy a file back to the client 
 */
/* $begin serve_static */
// void serve_static(int fd, char *filename, int filesize)
// {
//     int srcfd;
//     char *srcp, filetype[MAXLINE], buf[MAXBUF];

//     /* Send response headers to client */
//     get_filetype(filename, filetype);    //line:netp:servestatic:getfiletype
//     sprintf(buf, "HTTP/1.0 200 OK\r\n"); //line:netp:servestatic:beginserve
//     Rio_writen(fd, buf, strlen(buf));
//     sprintf(buf, "Server: Tiny Web Server\r\n");
//     Rio_writen(fd, buf, strlen(buf));
//     sprintf(buf, "Content-length: %d\r\n", filesize);
//     Rio_writen(fd, buf, strlen(buf));
//     sprintf(buf, "Content-type: %s\r\n\r\n", filetype);
//     Rio_writen(fd, buf, strlen(buf));    //line:netp:servestatic:endserve

//     /* Send response body to client */
//     srcfd = Open(filename, O_RDONLY, 0); //line:netp:servestatic:open
//     srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0); //line:netp:servestatic:mmap
//     Close(srcfd);                       //line:netp:servestatic:close
//     Rio_writen(fd, srcp, filesize);     //line:netp:servestatic:write
//     Munmap(srcp, filesize);             //line:netp:servestatic:munmap
// }

// copy the requested file to the connected descriptor using malloc, rio_readn, and rio_writen
void serve_static(int fd, char *filename, int filesize) {
    int srcfd;
    char *buf, filetype[MAXLINE], headers[MAXBUF];

    /* Send response headers to client */
    get_filetype(filename, filetype);
    strcpy(headers, "HTTP/1.0 200 OK\r\n");  // Initialize headers with the first string
    strcat(headers, "Server: Tiny Web Server\r\n");
    char content_length[MAXLINE];
    sprintf(content_length, "Content-length: %d\r\n", filesize);
    strcat(headers, content_length);
    char content_type[MAXLINE];
    sprintf(content_type, "Content-type: %s\r\n\r\n", filetype);
    strcat(headers, content_type);
    Rio_writen(fd, headers, strlen(headers));

    /* Allocate memory for the file and read it into the buffer */
    buf = (char *)Malloc(filesize);
    srcfd = Open(filename, O_RDONLY, 0);
    Rio_readn(srcfd, buf, filesize);
    Close(srcfd);

    /* Send the file's content to the client */
    Rio_writen(fd, buf, filesize);

    /* Free the allocated memory */
    Free(buf);
}

/*
 * get_filetype - derive file type from file name
 */
void get_filetype(char *filename, char *filetype) 
{
    if (strstr(filename, ".html"))
	strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
	strcpy(filetype, "image/gif");
    else if (strstr(filename, ".png"))
	strcpy(filetype, "image/png");
    else if (strstr(filename, ".jpg"))
	strcpy(filetype, "image/jpeg");
    else if (strstr(filename, ".mpg"))  // for MPG files
    strcpy(filetype, "video/mpeg");
    else
	strcpy(filetype, "text/plain");
}  
/* $end serve_static */

/*
 * serve_dynamic - run a CGI program on behalf of the client
 */
/* $begin serve_dynamic */
void serve_dynamic(int fd, char *filename, char *cgiargs) 
{
    char buf[MAXLINE], *emptylist[] = { NULL };

    /* Return first part of HTTP response */
    sprintf(buf, "HTTP/1.0 200 OK\r\n"); 
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));
  
    if (Fork() == 0) { /* Child */ //line:netp:servedynamic:fork
	/* Real server would set all CGI vars here */
	setenv("QUERY_STRING", cgiargs, 1); //line:netp:servedynamic:setenv
	Dup2(fd, STDOUT_FILENO);         /* Redirect stdout to client */ //line:netp:servedynamic:dup2
	Execve(filename, emptylist, environ); /* Run CGI program */ //line:netp:servedynamic:execve
    }
    /* No need -> parent waits for and reaps child */ //line:netp:servedynamic:wait
}
/* $end serve_dynamic */

/*
 * clienterror - returns an error message to the client
 */
/* $begin clienterror */
void clienterror(int fd, char *cause, char *errnum, 
		 char *shortmsg, char *longmsg) 
{
    char buf[MAXLINE];

    /* Print the HTTP response headers */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n\r\n");
    Rio_writen(fd, buf, strlen(buf));

    /* Print the HTTP response body */
    sprintf(buf, "<html><title>Tiny Error</title>");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<body bgcolor=""ffffff"">\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "%s: %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<p>%s: %s\r\n", longmsg, cause);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<hr><em>The Tiny Web server</em>\r\n");
    Rio_writen(fd, buf, strlen(buf));
}
/* $end clienterror */
