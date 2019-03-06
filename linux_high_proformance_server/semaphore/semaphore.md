#### 信号
信号是由用户、系统内核或者进程发送给目标进程的信息，已通知目标进程某个状态的改变或者系统的异常。Linux信号可以由如下条件产生：
	1. 前台进程，用户可以通过输入特殊的终端字符来给它发送信号，比如输入ctrl+C 通常会给进程发送一个中断信号。
	2. 系统异常。比如浮点异常和非法内存段访问。
	3. 系统状态变化。比如alarm定时器到期会引起SIGALRM信号。
	4. 运行Kill命令或者调用kill函数。

### 信号处理方式
目标进程在收到信号时，需要定义一个接收函数来处理之，信号处理函数的原型如下：
```
#include<signal.h>
typedef void(*_sighandler_t)(int);
```
信号处理函数中应该是可重入的，所以在信号处理函数中严禁调用一些不安全的函数。
除了用户自定义的信号处理函数之外，bits/signum.h头文件中还定义了信号的2种其他处理方式——SIG_IGN 和SIG_DEL;
```
#include<bits/signum.h>
#define SIG_DEL ((_sighandler_t)0)
#define SIG_IGN  ((_sighandler_t)1)

```
SIG_IGN表示忽略目标信号，SIG_DFL表示使用信号的默认处理方式。信号的默认处理方式有如下几种：结束进程(Term)、忽略信号(Ign)、结束进程并产生核心转储文件(Core)、暂停进程(Stop)、以及继续进程(Cont)。

### 中断系统调用
如果程序在执行阻塞系统调用时接收到信号，并且我们为该信号设置了信号处理函数，则默认情况系统调用将被中断，并且errno设置为EINTR，我们可以使用sigaction函数为信号设置为SA_RESTART标志以自动重启被该信号中断的系统调用。


### 信号函数
#### 要为一个信号设置处理函数，可以使用下面的signal系统调用：

```
#include<signal.h>
_sighandler_t signal(int sig,_sighandler_t handler);

```

#### sigaction系统调用
设置信号处理函数更为健壮的接口是如下的系统调用：
```
#include<signal.h>
int sigaction(int sig,const struct sigaction* act,struct sigaction* oact);

```

下面为sigaction的源代码：

```

struct sigaction{
	#ifdef _USE_POSIX199309
	union{
		_sighandler_t sa_handler;
		void (*sa_sigaction)(int ,siginfo_t * ,void *);
	}_sigaction_handler;
	
	#define sa_handler _sigaction_handler.sa_handler
	#define sa_siaction _sigaction_handler.sa_sigaction;
	
	#else
		_sighandler_t handler;
	#endif 
		_sigset_t sa_mask;
		int sa_flags;
		void (*sa_restorer)(void);

};
```
该结构体中的sa_hander成员指定信号处理函数，sa_mask成员设置进程的信号掩码(准确的说在进程原有信号掩码的基础上增加信号掩码)，以指定哪些信号不能发送给本进程。

#### 信号集

Linux使用数据结构sigset_t来表示一组信号，其定义如下：
```
#include<bits/sigset.h>
#define _SIGSET_NWORDS (1024/(8*sizeof(unsigned long int)))

typedef struct {
	unsigned long int _val[_SIGSET_NWORDS];
}_sigset_t;
```
由该定义可见，sigset_t实际上是一个长整形数组，数组的每个元素的每个byte表示一个信号，这种定义的方式和fd_set类似，linux提供了一组函数来设置、修改、删除、查询信号集：
```
#include<signal.h>
int sigemptyset(sigset_t *_set);  //清空信号集
int sigfillset(sigset_t *_set);   //在信号集中设置所有信号
int sigaddset(sigset_t *_set,int _signo);       //将信号_signo添加至信号集中
int sigdelset(sigset_t *_set,int _signo);	//将信号_signo从信号集中删除
int sigismemeber(_const sigset_t* _set,int _signo);	//测试_signo是否在信号集合中

```

#### 进程信号掩码
我们可以利用sigcation结构体的sa_mask成员来设置进程的信号掩码，下列函数也可以用于设置和查看进程的的信号掩码：
```
#include<signal.h>
int sigprocmask(int _how,_const sigset_t *_set,sigset_t* _oset);

```
#### 被挂起的信号
设置进程信号掩码后，被屏蔽的信号不能将进程接受，如果给进程发送一个被屏蔽的信号，则操作系统将该信号设置为该进程的一个被挂起的信号。如果我们取消对被挂起信号的屏蔽，则它能立即被进程接收到。如下函数可以获得进程当前被挂起的信号集：
```
#include<signal.h>
int sigpending(sigset_t *set);

```
set参数用来保存被挂起的信号集，显然，进程即使多次接收到同一个被挂起的信号，sigpending函数也只能被反应一次，并且，当我们再次使用sigprocmask使能够该挂起的信号时，该信号的处理函数也只能被触发一次。
在fork原语中，parent和child进程中，child进程将继承父进程的信号掩码，但是具有一个空的挂起的信号集合。


### 统一事件源
信号是一种异步事件，信号处理函数和程序的主循环是2条不同的执行路线。很显然，信号处理函数应该需要尽可能快的执行完毕，以确保信号不被屏蔽，一种典型的方案是：把信号的主要处理逻辑放到程序的主循环中，当信号处理函数被触发的时候，它只是见到那的通知主循环程序接收到信号，并把信号值传入主循环，主循环在根据信号值执行目标信号对应的逻辑代码。信号处理函数通常使用管道来将信号传递给主循环；信号处理函数往管道的写端写入信号值，主循环则从管道的读端读出该信号的值，那么主循环是如何知道管道上何时有数据可以可以读呢？这很简单，我们需要使用使用io复用函数用来监听管道的读端文件描述符上的可读事件，如此一来，信号事件就能和其他io事件一样被处理，即统一事件源。
很多优秀的io框架库和后台服务器程序都统一处理信号和io事件，比如libevent io框架库和xinetd超级服务。

### 网络编程相关信号
#### SIGPIPE
默认情况下，往一个读端关闭的管道或者socket连接套接字中写入数据将引发SIGPIPE信号，我们需要在代码中捕获并处理该信号，或者至少忽略它，因为程序接收到SIGPIPE信号的默认行为是结束进程，而我们绝对不希望因为错误的写操作而导致程序退出。引起SIGPIPE信号的写操作将设置为errno为EPIPE。
我们可以使用send函数中MSG_NOSIGNAL标志来禁止写操作触发SIGPIPE信号，这种情况下，我们能应该使用send函数反馈的errno值来判断或者socket连接的读端是否已经关闭。
此外，我们可以使用io复用系统调用检测管道和socket连接的读端是否已经关闭，以poll为例，当管道的读端关闭时，写端文件描述符上的POLLHUP事件将被触发；当socket连接被对方关闭时，socket上的POLLRDHUP事件将被触发。

#### SGIURG
在Linux环境下，内核通知应用程序带外数据主要有2种方法：一种是介绍的io复用技术，select等系统调用在接收到带外数据时将返回，并向应用程序报告socket的异常事件；另外一种就是使用SIGURG信号。
