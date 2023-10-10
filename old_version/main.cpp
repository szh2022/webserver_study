#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "http_conn.h"
#include "lock.h"
#include "threadpool.h"
const int MAX_FD = 65535;            // max fd num
const int LISTENQ = 5;               // max listen
const int MAX_EVENT_NUMBER = 10000;  // 一次可以监听的最大事件数量

void addsig(int sig, void(handler)(int)) {
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = handler;
    sigfillset(&sa.sa_mask);
    sigaction(sig, &sa, NULL);
}

// add fd to epoll
extern void addfd(int epollfd, int fd, bool one_shot);
// del fd from epoll
extern void removefd(int epollfd, int fd);
// modify fd
extern void modfd(int epollfd, int fd, int ev);

// main thread
int main(int argc, char* argv[]) {
    if (argc <= 1)
        error(1, 0, "usage: <port>");
    // get port
    int port = atoi(argv[1]);

    // handle SIGPIPE
    addsig(SIGPIPE, SIG_IGN);

    // init threadpool
    threadpool<http_conn>* pool = NULL;
    try {
        pool = new threadpool<http_conn>;
    } catch (...) {
        exit(-1);
    }

    // create a array to save all client information
    http_conn* users = new http_conn[MAX_FD];

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
        error(1, errno, "create socket failed");

    // set port reuse
    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    // bind
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    int rt1 = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (rt1 < 0)
        error(1, errno, "bind failed");
    int rt2 = listen(listenfd, LISTENQ);
    if (rt2 < 0)
        error(1, errno, "listen failed");

    // create epoll object —— event array
    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);  // must greate than 0

    // add fd to epoll object
    addfd(epollfd, listenfd, false);
    http_conn::m_epollfd = epollfd;

    while (true) {
        int num = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (num < 0 && (errno != EINTR)) {
            printf("epoll failed");
            break;
        }
        // 循环遍历event array
        for (int i = 0; i < num; i++) {
            int sockfd = events[i].data.fd;
            if (sockfd == listenfd) {
                // client connect
                struct sockaddr_in cli_addr;
                socklen_t cli_len = sizeof(cli_addr);
                int connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &cli_len);
                if (connfd < 0)
                    error(1, errno, "connect failed");
                if (http_conn::m_user_count >= MAX_FD) {
                    // 当前连接数满了
                    // send to client: server is busying
                    close(connfd);
                    continue;
                }
                // init client infor and add to http_conn array
                // 之后新的连接就进入数组中了
                users[connfd].init(connfd, cli_addr);
            } else if (events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                // 对方异常断开或错误
                users[sockfd].close_conn();
            } else if (events[i].events & EPOLLIN) {
                if (users[sockfd].read()) {
                    // read all data in once
                    pool->append(users + sockfd);

                } else {
                    users[sockfd].close_conn();
                }
            } else if (events[i].events & EPOLLOUT) {
                if (!users[sockfd].write()) {  // write all data in once
                    users[sockfd].close_conn();
                }
            }
        }
    }

    close(epollfd);
    close(listenfd);
    delete[] users;
    delete pool;
    return 0;
}