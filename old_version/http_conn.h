#ifndef HTTP_CONN_H  // 任务类
#define HTTP_CONN_H

#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "lock.h"

class http_conn {
public:
    static int m_epollfd;                       // all socket上事件都被注册到同一个epoll对象上，故需要静态
    static int m_user_count;                    // 统计用户数量
    static const int READ_BUFFER_SIZE = 2048;   // read buffer大小
    static const int WRITE_BUFFER_SIZE = 2048;  // write buffer大小
    static const int FILENAME_LEN = 200;        // 文件名最大长度
    // HTTP请求方法，这里只支持GET
    enum METHOD { GET = 0,
                  POST,
                  HEAD,
                  PUT,
                  DELETE,
                  TRACE,
                  OPTIONS,
                  CONNECT };

    /*
        解析客户端请求时，主状态机的状态
        CHECK_STATE_REQUESTLINE:当前正在分析请求行
        CHECK_STATE_HEADER:当前正在分析头部字段
        CHECK_STATE_CONTENT:当前正在解析请求体
    */
    enum CHECK_STATE { CHECK_STATE_REQUESTLINE = 0,
                       CHECK_STATE_HEADER,
                       CHECK_STATE_CONTENT };

    /*
        服务器处理HTTP请求的可能结果，报文解析的结果
        NO_REQUEST          :   请求不完整，需要继续读取客户数据
        GET_REQUEST         :   表示获得了一个完成的客户请求
        BAD_REQUEST         :   表示客户请求语法错误
        NO_RESOURCE         :   表示服务器没有资源
        FORBIDDEN_REQUEST   :   表示客户对资源没有足够的访问权限
        FILE_REQUEST        :   文件请求,获取文件成功
        INTERNAL_ERROR      :   表示服务器内部错误
        CLOSED_CONNECTION   :   表示客户端已经关闭连接了
    */
    enum HTTP_CODE { NO_REQUEST,
                     GET_REQUEST,
                     BAD_REQUEST,
                     NO_RESOURCE,
                     FORBIDDEN_REQUEST,
                     FILE_REQUEST,
                     INTERNAL_ERROR,
                     CLOSED_CONNECTION };

    // 从状态机的三种可能状态，即行的读取状态，分别表示
    // 1.读取到一个完整的行 2.行出错 3.行数据尚且不完整
    enum LINE_STATUS { LINE_OK = 0,
                       LINE_BAD,
                       LINE_OPEN };

    http_conn();
    ~http_conn();
    void process();                                  // 处理客户端的请求（解析请求报文，并处理）
    void init(int sockfd, const sockaddr_in& addr);  // init new accept conn
    void close_conn();                               // 关闭连接
    bool read();                                     // nio read
    bool write();                                    // nio write
    void unmap();                                    // 释放内存映射区的资源

private:
    int m_sockfd;                         // 该HTTP连接的socket
    sockaddr_in m_address;                // 通信的socket地址
    char m_read_buf[READ_BUFFER_SIZE];    // 读缓冲区
    char m_write_buf[WRITE_BUFFER_SIZE];  // 写缓冲区
    int m_read_idx;                       // 表示读缓冲区中已经读入的客户端数据的最后一个字节的位置
    int m_write_idx;                      // 表示缓冲区中已经写入的数据的最后一个位置

    int m_checked_index;  // 分析当前分析字符在读缓冲区的位置
    int m_start_line;     // 当前正在解析的行的起始位置
    char* m_url;          // 请求目标文件的文件名
    char* m_version;      // 协议版本，只支持HTTP1.1
    METHOD m_method;      // 请求方法
    char* m_host;         // 主机名
    bool m_linger;        // 判断HTTP请求是否要保持连接

    int m_content_length;     // 内容长度
    char m_real_file[200];    // 访问的文件名
    struct stat m_file_stat;  // 目标文件的状态。通过它可以判断文件是否存在
    char* m_file_address;     // 客户请求的目标文件被mmap映射到内存中的起始位置
    struct iovec m_iv[2];     // 用writev来写入多个缓冲区内容（m_file_address和写缓冲区）
    int m_iv_count;           // 表示被写内存块的数量

    CHECK_STATE m_check_state;  // 主状态机当前所在的状态

    void init();                               // 初始化连接其余的信息
    HTTP_CODE process_read();                  // 解析HTTP请求
    bool process_write(HTTP_CODE ret);         // 生成响应
    HTTP_CODE parse_request_line(char* text);  // 解析请求首行
    HTTP_CODE parse_headers(char* text);       // 解析请求头
    HTTP_CODE parse_content(char* text);       // 解析请求内容

    LINE_STATUS parse_line();  // 解析一行
    char* get_line() { return m_read_buf + m_start_line; }
    HTTP_CODE do_request();

    bool add_response(const char* format, ...);
    bool add_status_line(int status, const char* title);
    bool add_headers(int content_len);
    bool add_content_length(int content_len);
    bool add_content(const char* content);

    bool add_content_type();
    bool add_linger();
    bool add_blank_line();
};

#endif  // HTTP_CONN_H