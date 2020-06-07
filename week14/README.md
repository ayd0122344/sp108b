# week14筆記

## sp2/os/02-fork/01-hello/fork1.c

### 程式碼
```
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>

int main() { 
    fork(); // 一個行程分叉成父子兩個行程
    fork(); // 剛剛分叉出的兩個行程又分別分叉出一父一子，所以結果是四個行程。
    printf("%-5d : Hello world!\n", getpid());// getpid()用於取進程碼，也就是以下的310、308..
}
```
### 執行結果
```
310     : Hello world!
308     : Hello world!
309     : Hello world!
311     : Hello world!
```

## sp2/os/02-fork/01-hello/fork2.c

### 程式碼
```
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>

int main() { 
    printf("%-5d : enter\n", getpid());
    fork(); // 一個行程分叉成父子兩個行程
    printf("%-5d : after 1st fork\n", getpid());
    fork(); // 兩個行程又分別分叉出兩對父子，所以變成四個行程。
    printf("%-5d : Hello world!\n", getpid());
}
```
### 執行結果
```
317 : enter //原進程碼為317
317 : after 1st fork
318 : after 1st fork // 原本的317分叉出318
318 : Hello world! //317、318又分別分叉一次: 317分叉出319，318分叉出320
319 : Hello world!
317 : Hello world!
320 : Hello world!
```

## sp2/os/fork/02-child/fork2.c

### 程式碼
```
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>

int main() { 
    fork();  // 一個行程分叉成父子兩個行程
    if (fork()==0) { // 在此行的fork()還會讓剛剛分叉出的兩個行程再分叉一次，所以最後會有4個行程! // 如果分叉的結果是0就是子行程，是1就是父行程
      printf("%-5d: I am child!\n", getpid());
    } else {  
      printf("%-5d: I am parent!\n", getpid());
    }
}
```
### 執行結果
```
1871 : I am parent! //1871為祖父輩
1873 : I am child!  //1873為兒子輩(由1871的第二次分叉分叉出)
1872 : I am parent! //1872為兒子輩(由1871的第一次分叉出)
1874 : I am child!  //1874為孫子輩(由1872分叉出)
```

## sp2/os/02-fork/03-exec/execvp1.c

* execvp用於把目前行程代換成另一行程

* `ls -l`指令用於把目前資料夾的內容詳細列出

### 程式碼
```
#include <stdio.h>
#include <unistd.h>

int main() {
  char *arg[] = {"ls", "-l", NULL };
  printf("execvp():before\n");
  execvp(arg[0], arg); //arg[0]為arg的第一個參數，arg為存放"ls -l的陣列"
  printf("execvp():after\n"); // 此行不執行，因為行程被代換為ls -l
}
```
### 執行結果
```
execvp():before
總用量 153
drwxr-xr-x 1 nan None      0 六月    3 14:03 backup
-rw-r--r-- 1 nan None    185 六月    3 14:03 execvp1.c
-rwxr-xr-x 1 nan None 151556 六月    6 11:36 execvp1.exe
```

## sp2/os/02-fork/04-system/system1

### 程式碼
```
#include <stdio.h>
#include <stdlib.h>

int main() {
  system("ls -l"); //直接執行ls -l指令，執行完後也會回到原本程式
  printf("main end!\n"); // 所以這一行還是會執行
}
```
### 執行結果
```
總用量 298
-rw-r--r-- 1 Tim None 333 六月 3 14:20 mysystem1.c
-rwxr-xr-x 1 Tim None 151444 六月 3 14:20 mysystem1.exe
-rw-r--r-- 1 Tim None 106 六月 3 14:19 system1.c
-rwxr-xr-x 1 Tim None 151044 六月 3 14:20 system1.exe
main end!
```
## sp2/os/02-fork/04-system/mysystem1

### 程式碼
```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

int mysystem(char *arg[]) {
  if (fork()==0) {  
    execvp(arg[0], arg); // child : exec("ls -l")
  } // 讓兒子去做指令，在此傳入參數為ls -l
  int status;
  wait(&status);
}

int main() {
  char *arg[] = {"ls", "-l", NULL };
  mysystem(arg);
}

```
### 執行結果
```
總用量 298
-rw-r--r-- 1 Tim None 333 六月 3 14:20 mysystem1.c
-rwxr-xr-x 1 Tim None 151444 六月 3 14:20 mysystem1.exe
-rw-r--r-- 1 Tim None 106 六月 3 14:19 system1.c
-rwxr-xr-x 1 Tim None 151044 六月 3 14:20 system1.exe
main end!
```
## sp2/os/03-fs/01-echo/echo1.c

* Linux中，一切皆檔案，所以鍵盤、螢幕也可以當作檔案，使用read()來讀取

### 程式碼
```
#include <stdio.h>
#include <unistd.h>
#define SMAX 128

int main() {
  char line[SMAX];
  int n = read(0, line, SMAX); // 從 0 (標準輸入,stdin)，意即鍵盤, 讀入一行字 (line)
  line[n] = '\0';              // 設定字串結尾
  write(1, line, n);           // 將 line 輸出到 1 (標準輸出 stdout),意即螢幕
  write(2, line, n);           // 將 line 輸出到 2 (標準錯誤 stderr)
}
```
### 執行結果
```
hello // 這一行式鍵盤輸入的
hello //標準輸出印出這一行hello
hello //由於預設的標準錯誤輸出平台是終端機，所以此行也會印出hello
```
## sp2/os/03-fs/02-fecho/fecho1.c

* open()尋找沒被使用的最小檔案代號

### 程式碼
```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define SMAX 128

int main() {
  close(0);                      // 關閉標準輸入 stdin，不能從鍵盤輸入
  close(1);                      // 關閉標準輸出 stdout，不能印東西到螢幕
  open("a.txt", O_RDWR);         // 因為0被關掉了，所以目前open()找到的最小檔案代號就是0，a.txt變成標準輸入
  //O_RDWR表示此檔案可讀可寫(RD:read,WR:write)
  open("b.txt", O_CREAT|O_RDWR); // 0被上一行使用了，1還再關閉狀態，所以open()找到的最小檔案代號就是1，b.txt變成標準輸出
  //O_CREAT表示此檔案不存在則創建，b.txt在此處擁有:不存在則創建 或 可讀可寫的屬性
  char line[SMAX];
  gets(line);                    // gets()會從標準輸入(0, 目前是a.txt) 讀入一行字 line
  puts(line);                    // puts()會輸出 line 到標準輸出(1, 目前為b.txt)
}
// 所以這個程式做的就是將a.txt的內容輸出到b.txt中，若b.txt不存在則創建
```
### 執行結果
```
nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ cat a.txt
Hello, File descriptor !---------印出a.txt內容

nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ gcc fecho1.c -o fecho1

nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ ls
a.txt  fecho1.c  fecho1.exe  fecho2.c  README.md---------b.txt不存在

nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ ./fecho1

nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ ls
a.txt  b.txt  fecho1.c  fecho1.exe  fecho2.c  README.md---------編譯之後，發現b.txt不存在，於是創建

nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ cat b.txt
Hello, File descriptor !---------b.txt的內容和a.txt內容相同!
```
## sp2/os/03-fs/02-fecho/fecho2.c

### 程式碼
```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define SMAX 128

int main() {
  int fda = open("a.txt", O_RDWR);          // 打開檔案 a.txt 並取得檔案代號放入fda
  int fdb = open("b.txt", O_CREAT|O_RDWR);  // 打開檔案 b.txt 並取得檔案代號放入fdb
  dup2(fda, 0);                             // 複製 fda (並非複製代號，而是檔案描述器的內容) 到 0 (stdin)，如果0原本是開啟狀態則會先關閉再複製過去
  dup2(fdb, 1);                             // 複製 fdb 到 1 (stdout)，如果1原本是開啟狀態則會自動關閉
  char line[SMAX];
  gets(line);                               // 從 0 (a.txt) 讀入一行字 line
  puts(line);                               // 輸出 line 到 1 (b.txt)
}
```
### 執行結果
```
nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ ls
a.txt  fecho1.c  fecho1.exe  fecho2.c  README.md

nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ gcc fecho2.c -o fecho2

nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ ./fecho2

nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ ls
a.txt  b.txt  fecho1.c  fecho1.exe  fecho2.c  fecho2.exe  README.md

nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ cat b.txt
Hello, File descriptor !

nan@20190116-01 MSYS /sp/sp2/os/03-fs/02-fecho
$ cat a.txt
Hello, File descriptor !

```
## sp2/os/04-myshell/v1/myshell.c

* 此程式無法使用cd來切換路徑

### 程式碼
```
  
#include "../myshell.h"

int main(int argc, char *argv[]) {
  char path[SMAX], cmd[SMAX];
  getcwd(path, SMAX-1); // 取得初始路徑放到path陣列中
  while (1) { // 使用無窮迴圈不斷等待使用者輸入命令並執行之
    printf("myshell:%s $ ", path); // 印出myshell:路徑+錢字號($)
    // fgets(cmd,SMAX,stdin); // 使用fgets()從標準輸入讀取指令
    //也可使用gets()得到相同結果，gets()不需要指定大小也不需要指定從哪個檔案描述器去讀取
    gets(cmd);                     // 等待使用者輸入命令
    system(cmd);                   // 執行命令
    //使用cd 無法切換路徑是因為此處使用system。system是一個透過fork產生出的子行程，並且使用execvp去執行某個指令。然而子行程跟父行程間並不會共用任何變數!所以父行程的cmd(指令)跟path(路徑)跟子行程的cmd和path不會有關聯!
  }
}
```
### 執行結果
```
nan@20190116-01 MSYS /sp/sp2/os/04-myshell/v1
$ ./myshell
myshell:/sp/sp2/os/04-myshell/v1 $ ls------輸入ls會印出目前資料夾下的檔案
myshell.c  myshell.exe  README.md
myshell:/sp/sp2/os/04-myshell/v1 $ ls -l------輸入ls -l會印出目前資料夾下的檔案的詳細資訊
總用量 157
-rw-r--r-- 1 nan None    389 六月    3 14:03 myshell.c
-rwxr-xr-x 1 nan None 151639 六月    7 09:15 myshell.exe
-rw-r--r-- 1 nan None   1082 六月    3 14:03 README.md
myshell:/sp/sp2/os/04-myshell/v1 $ cat myshell.c------使用cat指令來印出myshell.c檔的內容
#include "../myshell.h"

int main(int argc, char *argv[]) {
  char path[SMAX], cmd[SMAX];
  getcwd(path, SMAX-1); // 取得初始路徑
        while (1) { // 不斷等待使用者輸入命令並執行之
    printf("myshell:%s $ ", path); // 顯示提示訊息
    fgets(cmd, SMAX, stdin);       // 等待使用者輸入命令
    system(cmd);                   // 執行命令
  }
}
myshell:/sp/sp2/os/04-myshell/v1 $ echo hello how are you------使用echo指令印出後面的字
hello how are you
myshell:/sp/sp2/os/04-myshell/v1 $ exit------使用exit離開，但v1此功能未建置完成所以沒有反應，所以使用ctrl+V離開程式
```
## sp2/os/04-myshell/v2/myshell.c

### 程式碼
```
#include "../myshell.h"

// 將檔案讀入成為字串
int readText(char *file, char *text, int size) {
  FILE *f = fopen(file, "r");
  int n = fread(text, 1, size, f);
  fclose(f);
  return n;
}

int main(int argc, char *argv[]) {
  char ipath[SMAX], path[SMAX], cmd[SMAX], fullcmd[SMAX], pathFile[SMAX];
  getcwd(ipath, SMAX-1); // 取得初始路徑放到ipath,SMAX為ipath的空間大小
  strcpy(path, ipath);   // 將ipath的內容複製到path => path = ipath
  sprintf(pathFile, "%s/path.txt", ipath); // 將第三個參數(ipath)的內容放入第二個參數("%s/path.txt"的%s位置)，最後存在第一個參數的字串中 => pathFile=<ipath>/path.txt
  while (1) { // 不斷等待使用者輸入命令並執行之
    printf("myshell:%s $ ", path); // 顯示提示訊息
    gets(cmd);                     // 等待使用者輸入命令
    strtok(cmd, "\n");             // 切掉 \n (strtok第一個參數放字串，第二個參數放要消除的東西)
    if (strcmp(cmd, "exit")==0) break; // 設定如果指令為"exit"則離開迴圈結束程式
    sprintf(fullcmd, "cd %s;%s;pwd>%s", path, cmd, pathFile); // fullcmd = 切到 path; 使用者輸入的命令; 將路徑存入 pathFile 中。
    system(fullcmd);               // 執行 fullcmd 
    readText(pathFile, path, SMAX);// 讀 pathFile 檔取得路徑
    strtok(path, "\n");            // 切掉 \n
  }
}
```
### 執行結果
```

```