#include<stdio.h>
#include<time.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 64
class util_timer;  // 前向声明

struct client_data{
    sockaddr_in address;  // 客户端socket地址
    int sockfd;   // socket文件描述符
    char buf[BUFFER_SIZE];  //读缓存
    util_timer* timer; //定时器
};


class util_timer{
public: 
    util_timer():  prev(NULL),next(NULL){}
public:
    time_t expire;  // 任务超时时间，这里使用绝对时间
    void (*cb_func)(client_data*);  //回调函数
    client_data* user_data;  
    util_timer* prev;  //前一个定时器
    util_timer* next; // 后一个定时器
};

// 定时器链表：一个升序、双向链表，且带有头节点和尾节点
class sort_timer_lst{

private:
    // 一个重载的辅助函数，会被公有的add_timer函数和adjust_timer函数调用
    // 该函数将目标定时器timer 添加到节点lst_head之后的部分链表中
    void add_timer(util_timer* timer,util_timer* lst_head){

    }
private:
    util_timer* head;
    util_timer* tail;
};