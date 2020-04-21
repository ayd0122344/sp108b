# week7筆記

## 03-fib筆記

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

## 04-inline筆記