#### 11.6
A.\
See the changes in `doit` and `read_requesthdrs` functions before every `printf("%s", buf);`.

B. 
```cmd
$ cd hw11/tiny && make tiny
$ stdbuf -o0 ./tiny 8080 > output.txt
```

C.\
HTTP/1.1

D.
1. **GET / HTTP/1.1**: This is the request line. It indicates that the client wants to retrieve the root resource using the HTTP/1.1 protocol.

2. **Accept**: Specifies the types of media that the client can process. The client prefers `text/html`, `application/xhtml+xml`, and `application/xml`.

3. **Host**: The domain name of the server and the TCP port number on which the server is listening.

4. **User-Agent**: Provides information about the browser making the request. In this case, it's Chrome version 118 on macOS 10.15.7.

5. **Accept-Encoding**: Indicates what content encodings the client understands. The client can handle `gzip`, `deflate`, and `br` (Brotli) compressed content.

6. **Accept-Language**: Describes the languages the client prefers. The client prefers British English, then American English, and then any other form of English.

7. **Referer**: The address of the previous web page from which a link to the currently requested page was followed.

8. **traceparent**: Part of the W3C Trace Context standard, used for distributed tracing.

9. **Proxy-Connection**: Indicates the desired control options for the current connection.

The RFC 2616 standard provides detailed explanations of many of these headers, but some, like the `sec-*` and `X-*` headers, are extensions or part of newer standards.

#### 11.7
Update the `get_filetype` function, add a condition to check for `.mpg` files and set the MIME type to `video/mpeg`.
```c
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
    else if (strstr(filename, ".mpg"))  // Add this condition for MPG files
        strcpy(filetype, "video/mpeg");
    else
        strcpy(filetype, "text/plain");
}
```

#### 11.8
1. **Define a SIGCHLD handler**:
This handler will reap the zombie processes.

```c
void sigchld_handler(int sig) {
    while (waitpid(-1, 0, WNOHANG) > 0);
    return;
}
```

2. **Install the SIGCHLD handler**:
In the `main()` function, before entering the main server loop, install the `SIGCHLD` handler using `Signal()`.

```c
Signal(SIGCHLD, sigchld_handler);
```

3. **Remove the explicit `Wait()` call**:
In the `serve_dynamic()` function, we can remove the `Wait(NULL);` line since the `SIGCHLD` handler will now take care of reaping the child processes.

```c
// ... other includes ...
#include "csapp.h"

void sigchld_handler(int sig) {
    while (waitpid(-1, 0, WNOHANG) > 0);
    return;
}

int main(int argc, char **argv) {
    // ... other code ...

    Signal(SIGCHLD, sigchld_handler);  // Install the SIGCHLD handler

    while (1) {
        // ... main server loop ...
    }
}

// ... other functions ...

void serve_dynamic(int fd, char *filename, char *cgiargs) {
    char buf[MAXLINE], *emptylist[] = { NULL };

    // ... other code ...

    if (Fork() == 0) { /* Child */
        // ... child code ...
    }
    // No need to explicitly wait for the child here
}
```

#### 11.9
See the changes about the `serve_static` function in `tiny.c`.

#### 11.10
See `adder-form.html` for more details.

#### 11.11
1. **Modify the `doit` Function**:
   Update the `doit` function in `tiny.c` to handle the `HEAD` method. This involves checking the method and then deciding whether to send only the headers or both headers and content.

```c
void doit(int fd) 
{
    ...
    sscanf(buf, "%s %s %s", method, uri, version);
    if (strcasecmp(method, "GET") && strcasecmp(method, "HEAD")) {
        clienterror(fd, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return;
    }
    ...
    if (is_static) {
        if (strcasecmp(method, "HEAD") == 0) {
            // Only send headers for HEAD request
            send_static_headers(fd, filename, sbuf.st_size);
        } else {
            serve_static(fd, filename, sbuf.st_size);
        }
    } else {
        serve_dynamic(fd, filename, cgiargs);
    }
}
```

2. **Add a Function to Send Only Headers**:
   Create a new function `send_static_headers` that sends only the headers for static content:

```c
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
```

#### 11.12
1. **Update the `doit` Function**:
   - Add support for the `POST` method by checking the method type.
   - For `POST` requests, read the request body to get the data sent by the client.

2. **Handle POST Data**:
   - Extract the content length from the headers to know how much data to read from the request body.
   - Read the data and pass it to the CGI program as input.

```c
void doit(int fd) 
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE], post_data[MAXLINE];
    rio_t rio;
    int content_length = 0;

    // ... other code ...

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

    // ... (rest of the function remains mostly unchanged)

    serve_dynamic(fd, filename, cgiargs);
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
```

#### 11.13
1. **Signal Handler for SIGPIPE**:

```c
void sigpipe_handler(int sig) {
    printf("Received SIGPIPE signal. Handling it gracefully.\n");
    return;
}
```

2. **Install the Signal Handler in the `main` Function**:

```c
int main(int argc, char **argv) 
{
    // ... (rest of the code)

    Signal(SIGPIPE, sigpipe_handler); // Install the SIGPIPE handler

    // ... (rest of the code)
}
```

3. **Handle EPIPE Errors**:

Whenever we use the `Rio_writen` function or any other writing function, we should check for errors. If an `EPIPE` error is detected, we can handle it gracefully:

```c
ssize_t n;
if ((n = Rio_writen(fd, buf, count)) < 0) {
    if (errno == EPIPE) {
        printf("EPIPE error detected. Client closed the connection prematurely.\n");
    } else {
        // Handle other errors if necessary
    }
}
```
