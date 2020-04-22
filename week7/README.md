# week7筆記

## 03-asmVm\gcc\03-fib 之筆記 - Fibonacci

### 執行方式

* 對main.c跟fib.c進行編譯並連結: 

```
PS D:\ccc\sp\code\c\03-asmVm\gcc\03-fib> gcc main.c fib.c -o
fib
PS D:\ccc\sp\code\c\03-asmVm\gcc\03-fib> ./fib
fib(10)=89

```

* 將fib.c編譯出組合語言之方式

```
gcc -fverbose-asm -S fib.c -o fib.s

```
* 陳鍾誠老師對於fib.s之註解: 

https://github.com/ccccourse/sp/tree/master/code/c/03-asmVm/gcc/03-fib?fbclid=IwAR26Kv7JxpbxlXJF9OvVvsyiXTDvEhmo6UTmimETKkLqDvEDe41k98sMWBo

* 對fib.s之理解

![](https://github.com/ayd0122344/sp108b/blob/master/week7/Image/fib.png)

## 03-asmVm\gcc\04-inline 之筆記 - 內嵌組合語言寫法

### 執行方式

```

PS D:\ccc\sp\code\c\03-asmVm\gcc\04-inline> gcc inline.c -o inline
PS D:\ccc\sp\code\c\03-asmVm\gcc\04-inline> ./inline
sum = 30

```
* 對inline.c之理解

![](https://github.com/ayd0122344/sp108b/blob/master/week7/Image/inline.png)

## 03-asmVm\gcc\05-globalCall 之筆記 -使用全域變數時，變數可直接存取，不需要透過框架暫存器

### 執行方式

```
PS D:\ccc\sp\code\c\03-asmVm\gcc\05-globalcall> gcc -S globalCall.c -o globalCall.s
PS D:\ccc\sp\code\c\03-asmVm\gcc\05-globalcall> gcc globalCall.c -o globalCall
PS D:\ccc\sp\code\c\03-asmVm\gcc\05-globalcall> ./globalCall
add(5, 8)=13
```

* 重點部分節錄

```
_a:
	.long	5                   # 宣告a為長整數5
	.globl	_b
	.align 4                    # 32位元4個byte
_b:
	.long	8
	.comm	_c, 4, 2            # c沒有被定義，所以放在comm中
	.text
	.globl	_add
	.def	_add;	.scl	2;	.type	32;	.endef
_add:
	pushl	%ebp
	movl	%esp, %ebp          # 使用全域變數時，變數可直接存取，不需要透過框架暫存器
	movl	_a, %edx
	movl	_b, %eax
	addl	%edx, %eax
	movl	%eax, _c
	nop
	popl	%ebp
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
```

## 04-toolchain/gcc/01-toolchain - gcc的工具鏈

### 執行方式

1. 產生組合語言

`$ gcc -S sum.c -o sum.s`

2. 將組合語言轉換為目的碼 (Object Code)-把gcc當成組譯器使用

`$ gcc -c sum.s -o sum.o`

3. 將目的碼與函式庫連結後產生執行檔

```
$ gcc sum.o -o sum
$ ./sum
sum(10)=55
```

4. 反組譯目的碼-將二進位碼轉成組合語言，但會和原本的組合語言有點出入，比如有些符號會消失。

```
PS D:\ccc\book\sp\code\c\01-gcc\01-toolchain> objdump -d sum.o
```
* 當指令集中的指令長度不固定，我們稱之為"變長指令集"。

* 長度不固定的指令架構稱為"複雜指令集"（Complex Instruction Set Computing，CISC）。

* 長度固定的指令架構稱為"精簡指令集"（Reduced Instruction Set Computing，RISC）。

## 04-toolchain/gcc/02-link

> 02-link主要探討gcc的各種用法 

### 執行方式


1. 直接編譯連結

```
$ gcc main.c sum.c -o run
$ ./run
```

2. 產生組合語言

* -S代表產生組合語言但不連結

```
$ gcc -S main.c -o main.s
$ gcc -S sum.c -o sum.s
```

或者:

* 組譯後連結 - 編譯組譯一次做完

```
$ gcc main.c sum.s -o run
$ ./run
sum(10)=55
```

或者:

1. 直接產生目的檔 

* -c代表編譯成目的檔但不連結。(如果程式不完整，連結的話會失敗)

```
$ gcc -c sum.c -o sum.o
$ gcc -c main.c -o main.o
```

2. 連結目的檔來產生執行檔

* 把兩個目的檔(main.o, sum.o)連結起來變成run.exe
```
$ gcc main.o sum.o -o run
$ ./run
```

## 04-toolchain/gcc/03-macroExpand - max.c為一個有巨集的c語言程式

### 執行方式

```
PS D:\ccc\sp\code\c\04-toolchain\gcc\03-macroExpand> gcc -E max.c -o max.i
PS D:\ccc\sp\code\c\04-toolchain\gcc\03-macroExpand> gcc max.c -o max
PS D:\ccc\sp\code\c\04-toolchain\gcc\03-macroExpand> ./max
c=5
```

`gcc -E max.c -o max.i`

```
-E 代表展開巨集然後輸出到max.i(通常巨集展開後的檔案附檔名為".i")
```

## 04-toolchain/gcc/04-make

### 執行方式

```
PS D:\ccc\sp\code\c\04-toolchain\gcc\04-make> mingw32-make
gcc -std=c99 -O0 sum.c main.c -o run
PS D:\ccc\sp\code\c\04-toolchain\gcc\04-make> ./run
sum(10)=55
```

### 04-make\Makefile之理解

* Tips: 

	* `$@`：目前的目標項目名稱。

	* `$<`：代表目前的相依性項目。

	* `$*`：代表目前的相依性項目，但不含副檔名。

	* `$?`：代表需要重建（被修改）的相依性項目。

```
CC := gcc							# 前3行做定義變數的動作
CFLAGS = -std=c99 -O0						# "O0"代表不做最佳化
TARGET = run

all: $(TARGET)							# 1.先執行all，遇到$(TARGET)去找對應值(run)

$(TARGET): sum.c main.c						# 2.執行此行並觸發下一行的$(CC) $(CFLAGS) $^ -o $@動作
	$(CC) $(CFLAGS) $^ -o $@				# $(CC)代表gcc, $(CFLAGS)代表-std=c99 -O0, $^此處代表sum.c main.c, $@此處代表$(TARGET)也就是run

clean:
	rm -f *.o
```

## 04-toolchain/gcc/05-makeLib

### 執行方式

```
PS D:\ccc\sp\code\c\04-toolchain\gcc\05-makeLib> mingw32-make
ar -r libstat.a sum.o						# 先做ar把sum.o壓縮
ar: creating libstat.a						# 創建libstat.a檔案
gcc -std=c99 -O0 -c main.c -o main.o				# 用main.c產生main.o
gcc -std=c99 -O0 libstat.a main.o -L ./ -lstat -o run		# 將libstat.a和main.o連結並輸出run
```

### 05-makeLib\Makefile之執行結果與探討

* 程式碼:

```
CC := gcc
AR := ar
CFLAGS = -std=c99 -O0
TARGET = run
LIB = libstat.a

all: $(TARGET)

$(TARGET): $(LIB) main.o
	$(CC) $(CFLAGS) $^ -L ./ -lstat -o $@

$(LIB): sum.o
	$(AR) -r $@ $^						# AR是把檔案壓縮起來變成函式庫的方式

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.a
```

* 執行結果:

```
ar -r libstat.a sum.o						# 先做ar把sum.o壓縮
ar: creating libstat.a						# 創建libstat.a檔案
gcc -std=c99 -O0 -c main.c -o main.o				# 用main.c產生main.o
gcc -std=c99 -O0 libstat.a main.o -L ./ -lstat -o run		# 將libstat.a和main.o連結並輸出run
```
* 執行順序:

1. 做$(TARGET)觸發$(TARGET): $(LIB) main.o

2. 做$(LIB)觸發$(AR) -r $@ $^所以執行`ar -r libstat.a sum.o`

3. 做完AR也就是做完$(LIB)之後，回到$(TARGET): $(LIB) main.o來做main.o

4. main.o觸發%.o: %.c做	$(CC) $(CFLAGS) -c $< -o $@ 動作 => `gcc -std=c99 -O0 -c main.c -o main.o`

5. 然後回到$(TARGET): $(LIB) main.o做$(CC) $(CFLAGS) $^ -L ./ -lstat -o $@動作 => `gcc -std=c99 -O0 libstat.a main.o -L ./ -lstat -o run`
