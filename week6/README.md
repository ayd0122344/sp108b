# week6筆記

## 虛擬機:vm.c之筆記

### vm.c程式碼理解順序

1. 指令記憶體、資料記憶體大小

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/vmM.png)

2. main()

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/vmMain.png)

3.Run()

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/vmRun1.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/vmRun2.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/vmRun3.png)

### 補充圖片

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/syntax.jpg)

### 執行方式

```
    mingw32-make => 

    1) ./asm ../test/Add => ./vm ../test/add.bin

    2) ./asm ../test/sum => ./vm ../test/sum.bin
```

### 執行結果探討

1. add.bin

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/addResult.png)

2. sum.bin

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/sumResult.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/sumResult2.png)

## 03-asmVm/01-add之筆記

* add.s & main.s產生方式

```

PS D:\ccc\sp\code\c\03-asmVm\gcc\01-add> gcc main.c add.c -o add
PS D:\ccc\sp\code\c\03-asmVm\gcc\01-add> ./add
add(5, 8)=13
PS D:\ccc\sp\code\c\03-asmVm\gcc\01-add> gcc -S add.c -o add.s

(有註解版本)
PS D:\ccc\sp\code\c\03-asmVm\gcc\01-add> gcc -fverbose-asm -S add.c -o add.s
PS D:\ccc\sp\code\c\03-asmVm\gcc\01-add> gcc -fverbose-asm -S main.c -o main.s

```

### 理解過程

 - add.s檔案觀察結果

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/addx86.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/addx86-2.png)

### x86之堆疊- foorbar.c 執行與理解

* 產生方式

```

連結網址: https://eli.thegreenplace.net/.../where-the-top-of-the...

PS D:\ccc\sp\code\c\03-asmVm\gcc\00-foobar> gcc -fverbose-asm -S foobar.c -o foobar.s

```
![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/x86stack.png)

> 00-foobar、02-sum的組合語言與大部分同add.s的寫法，在此不再贅述。

[可參考陳鍾成老師對foobar.c的組合語言註解](https://github.com/ccccourse/sp/tree/master/code/c/03-asmVm/asm/00-foobar)

[可參考陳鍾成老師對sum.c的組合語言註解](https://github.com/ccccourse/sp/tree/master/code/c/03-asmVm/asm/02-sum)
