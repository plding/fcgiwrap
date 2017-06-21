/*
 * Copyright (c) 2017-2017 Dingpeilong
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <netinet/in.h>

#include <fcgi_stdio.h>

/* glibc doesn't seem to export it */
#ifndef UNIX_PATH_MAX
#define UNIX_PATH_MAX 108
#endif

int
main(int argc, char **argv)
{
    int nchildren = 1;
    int c;

    while ((c = getopt(argc, argv, "c:hfs:p:")) != -1) {
        switch (c) {

        case 'h':
            printf("Usage: %s [OPTION]\nInvokes CGI scripts as FCGI.\n\n"
                PACKAGE_NAME" version "PACKAGE_VERSION"\n\n"
                "Options are:\n"
                "  -f                   Send CGI's stderr over FastCGI\n"
                "  -c <number>          Number of processes to prefork\n"
                "  -s <socket_url>      Socket to bind to (say -s help for help)\n"
                "  -h                   Show this help message and exit\n"
                "  -p <path>            Restrict execution to this script. (repeated options will be merged)\n",
                argv[0]
            );
            return 0;
        case 'c':
            nchildren = atoi(optarg);
            break;
        default:
            abort();
        }
    }

    return 0;
}
