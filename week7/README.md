# week7筆記

## 03-fib 之筆記 - Fibonacci

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

## 04-inline 之筆記 - 內嵌組合語言寫法

* 執行方式

```

PS D:\ccc\sp\code\c\03-asmVm\gcc\04-inline> gcc inline.c -o inline
PS D:\ccc\sp\code\c\03-asmVm\gcc\04-inline> ./inline
sum = 30

```
* 對inline.c之理解

![](https://github.com/ayd0122344/sp108b/blob/master/week7/Image/inline.png)

## 05-globalCall 之筆記 -使用全域變數時，變數可直接存取，不需要透過框架暫存器

* 執行方式

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


