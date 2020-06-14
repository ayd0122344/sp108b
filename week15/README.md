# week15筆記

## Linux組合語言

### hello.s理解

* 使用BIOS系統呼叫，並參閱系統呼叫中斷表來寫組合語言
```
        .global _start

        .text
_start:
        # write(1, message, 13)
        mov     $1, %rax                # 1就是標準輸出，表中為sys_write
        mov     $1, %rdi                # file handle 1 is stdout
        mov     $message, %rsi          # address of string to output
        mov     $13, %rdx               # number of bytes
        syscall                         # invoke operating system to do the write

        # exit(0)
        mov     $60, %rax               # 60在表中為sys_exit，也就是離開
        xor     %rdi, %rdi              # we want return code 0
        syscall                         # invoke operating system to exit
message:
        .ascii  "Hello, world\n"
```

### helloMacro.s理解

* 使用巨集(在組合語言中類似函數的功能)來簡短程式，如果寫相同功能的程式段可以使用巨集，達到不用一直翻表的目的

```
        .include "../myMacro.s" //把外部的巨集檔案連結進來
        .global _start

        .text
_start:
        WRITES $1, $message, $13 //WRITES是寫在myMacro的一個巨集，分別傳入三個參數讓巨集做展開處理，1代表stdout, 13代表字串長度
        EXIT //EXIT也是引用巨集來處理
message:
        .ascii  "Hello, world\n"
```
* myMacro.s程式碼筆記
```
# write(1, message, 13)
.macro WRITES fd, msg, len
  mov     $1, %rax            
  mov     \fd, %rdi           #參數就要在前面加上斜線(/)
  mov     \msg, %rsi          
  mov     \len, %rdx          
  syscall
.endm

.macro EXIT
  mov 	$60, %rax  //60 => sys_exit
  xor	%rdi, %rdi //把rdi設成0
  syscall
.endm

.macro PUTS msg
  mov   \msg, %rdi
  call  puts
.endm


.macro PRINTF fmt, p1
  # We need to call printf, but we are using eax, ebx, and ecx.  printf
  # may destroy eax and ecx so we will save these before the call and
  # restore them afterwards.

  push    %rax                    # caller-save register
  push    %rcx                    # caller-save register

  mov     \fmt, %rdi              # set 1st parameter (format)
  mov     \p1, %rsi               # set 2nd parameter (current_number)
  xor     %rax, %rax              # because printf is varargs

  # Stack is already aligned because we pushed three 8 byte registers
  call    printf                  # printf(format, current_number)

  pop     %rcx                    # restore caller-save register
  pop     %rax                    # restore caller-save register
.endm
 
```

## hola.s

* 展示組合語言如何連結C語言的函式庫，puts()

* 注意編譯的時候要加上"-no-pie" : gcc -no-pie hola.s -o hola<br>
    * 告訴gcc不要編成和未指無關的組合語言(p:position, i:independent, e:executable)，也就是編成和位置有關的組合語言

## C語言和組合語言連結: callmaxofthree.c 和 maxofthree.s

* 透過在C語言程式中(此為callmaxofthree.c)定義函數原型 `int64_t maxofthree(int 64_t, int64_t, int64_t);`後, 便可以呼叫組合語言。但maxofthree實際定義在maxofthree.s檔中，在組合語言中最後用ret返回到C語言程式的呼叫點。

## 存取命令列參數: echo.s

* 使用迴圈`jnz main`來不斷地取命令列參數，最後呼叫puts()來印出

## 浮點數的處理: sum.s

* 現在x86中使用xmm的暫存器處理

* 在sum.s中寫一個計算總和的組合語言，最後在callsum.c中呼叫來處理浮點數計算

## 資料段處理: average.s - 取平均值

## 遞迴運算: callfactorial.s - 呼叫本身

* 組合語言中寫遞迴可以直接使用push、pop來做，但不一定要做框架暫存器(C語言才需要)。

## sp2/net/01-timeTcp1/server.c

## 程式碼理解
```
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <time.h>
#include <assert.h>
#include <sys/wait.h>

#define PORT 8080 // 沒有設定port的狀態下，預設port為8080

int main(int argc, char *argv[]) {
  int listenfd = socket(AF_INET, SOCK_STREAM, 0); // 在server端創建socket
  assert(listenfd >= 0);
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));

  //設定socket基本屬性
  serv_addr.sin_family = AF_INET; //設定網路類型
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //設定傾聽網址
  serv_addr.sin_port = htons(PORT); //設定傾聽port

  assert(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) >= 0); //bind的作用為佔下port(在此為8080)並開始傾聽
  assert(listen(listenfd, 10) >= 0); // 規定傾聽的時候最多十個同時連線

  //設定緩衝區
  char sendBuff[1025];
  memset(sendBuff, 0, sizeof(sendBuff));

  while(1) {
    int connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); //server接受客戶端連線
    assert(connfd >= 0);
    time_t ticks = time(NULL); //呼叫time()來取得目前時間
    snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks)); //使用ctime()將ticks轉成字串並放入sendBuff中
    assert(write(connfd, sendBuff, strlen(sendBuff)) >=0); //將sendBuff的內容傳給客戶端
    close(connfd);//關閉和客戶端之連線
    sleep(1); //休息一秒鐘後繼續，此server一秒最多就處理1個連線
  }
}
```
## sp2/net/01-timeTcp1/client.c

## 程式碼理解
```
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <time.h>
#include <assert.h>
#include <sys/wait.h>

#define PORT 8080

int main(int argc, char *argv[]) {
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  assert(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) > 0);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0); //創建完socket後會給你一個socketfd(file descriptor檔案描述器)，由於在Linux中把所有東西都當作檔案，在此也把網路當檔案讀
  assert(sockfd >=0);

  //server要做listen、bind、accept，client只要做connect。
  //客戶端connect完就連上server，連上就可以讀寫
  assert(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) >= 0);
  char recvBuff[1024];
  int n;
  while ((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0) { //讀取「網路」這個檔案 => read(sockfd..
    recvBuff[n] = 0;
    fputs(recvBuff, stdout);//將讀取到的東西印出
  }
  return 0;
}
```

## sp2/net/net.c

* sp2/net/02-timeTcp2為01-timeTcp1使用net.c

## 程式碼理解
```
#include "net.h"

char ip[SMAX];

//把 misavo.com 這樣的 hostname 轉成ip => 172.104.100.202
char *host_to_ip(char *hostname, char *ip) { // 查出 host 對應的 ip
	struct hostent *host = gethostbyname(hostname);
	/*
	char **pp;
	printf("hostname=%s\n", host->h_name);
	for (pp=host->h_aliases; *pp != NULL; pp++)
		printf("  alias:%s\n", *pp);
	for (pp=host->h_addr_list; *pp != NULL; pp++)
		printf("  address:%s\n", inet_ntop(host->h_addrtype, *pp, ip, SMAX));
	printf("  ip=%s\n", ip);
	*/
	inet_ntop(host->h_addrtype, host->h_addr_list[0], ip, SMAX); // 取第一個 IP
	return ip;
}

//初始化網路 socket
int net_init(net_t *net, int protocol, int side, int port, char *host) {
	memset(net, 0, sizeof(net_t));
	net->protocol = protocol; // 設定協定:TCP 或 UDP
	net->side = side; //client 端或server端
	net->port = port;// 埠號
	net->serv_ip = (side==CLIENT) ? host_to_ip(host, ip) : "127.0.0.1";
	int socketType = (protocol == TCP) ? SOCK_STREAM : SOCK_DGRAM;// 若protocol == TCP設定socket型態為串流，若為UDP則設為datagram
	net->sock_fd = socket(AF_INET, socketType, 0);//創建socket
  assert(net->sock_fd >= 0);
	net->serv_addr.sin_family = AF_INET; //檢查是否連接成功
	net->serv_addr.sin_addr.s_addr = (side == SERVER) ? htonl(INADDR_ANY) : inet_addr(net->serv_ip); //設定伺服機的基本位址資訊
	net->serv_addr.sin_port = htons(net->port);//設定port
  return 0;
}

// client 端做的-connect
int net_connect(net_t *net) {
	int r = connect(net->sock_fd, (struct sockaddr *)&net->serv_addr, sizeof(net->serv_addr));
	// assert(r>=0);
	return r;
}

// server 端做的-bind
int net_bind(net_t *net) {
	int r = bind(net->sock_fd, (struct sockaddr*)&net->serv_addr, sizeof(net->serv_addr));
	assert(r>=0);
	return r;
}

// server 端做的-listen
int net_listen(net_t *net) {
	int r = listen(net->sock_fd, 10); // 最多十個同時連線
	assert(r>=0);
	return r;
}

//server 端做的 accept
int net_accept(net_t *net) {
	int r = accept(net->sock_fd, (struct sockaddr*)NULL, NULL);
	assert(r>=0);
	return r;
}

// client、server端都會做的關閉連線
int net_close(net_t *net) {
	shutdown(net->sock_fd, SHUT_WR);
	close(net->sock_fd);
	return 0;
}
```

## sp2/net/03-telnet1/server.c

### 程式碼理解
```
#include "../net.h"

int serv(int connfd) {
  close(STDOUT_FILENO);                    // 關閉 stdout
  dup2(connfd, STDOUT_FILENO);             // 用 connfd 取代 stdout
  dup2(connfd, STDERR_FILENO);             // 用 connfd 取代 stderr =>不管是stdout還是stdert都要導回到client端
  while (1) {
    char cmd[SMAX];
    int len = read(connfd, cmd, SMAX);     // 讀入 client 傳來的命令
    if (len <= 0) break;                   // 若沒讀到就結束了！
    strtok(cmd, "\n");                     // 把 \n 去除
    fprintf(stderr, "cmd=%s\n", cmd);      // 印出命令方便觀察
    if (strncmp(cmd, "exit", 4)==0) break; // 若是 exit 則離開！
    system(cmd);                           // 執行該命令 (由於 connfd 取代了 stdout，所以命令的輸出會直接傳回給 client)
    write(connfd, "\n", 1); // 至少要回應 1byte ，否則 client 會讀不到而導致當掉
  }
  close(connfd);            // 關閉連線
  exit(0);                  // 結束此子行程
}

int main(int argc, char *argv[]) {
  int port = (argc >= 2) ? atoi(argv[1]) : PORT;
  net_t net;
  net_init(&net, TCP, SERVER, port, NULL);
  net_bind(&net);
  net_listen(&net);
  while(1) { // 主迴圈：等待 client 連進來，然後啟動 serv 為其服務
    int connfd = net_accept(&net); // 等待連線進來
    assert(connfd >= 0);
    if (fork() <= 0) { // 創建新的行程去服務該連線。
      serv(connfd);    // 子行程開始執行 serv()
    }
  }
}
```