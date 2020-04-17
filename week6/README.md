# week6筆記

## 虛擬機:vm.c之筆記

* vm.c程式碼理解順序

1. 指令記憶體、資料記憶體大小

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/vmM.png)

2. main()

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/vmMain.png)

3.Run()

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/vmRun1.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/vmRun2.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/vmRun3.png)

* 補充圖片

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/syntax.jpg)

* 執行方式

```
    mingw32-make => 

    1) ./asm ../test/Add => ./vm ../test/add.bin

    2) ./asm ../test/sum => ./vm ../test/sum.bin
```

* 執行結果探討

1. add.bin

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/addResult.png)

2. sum.bin

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/sumResult.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/sumResult2.png)

## 工具鏈 : gcc 在x86上的組合語言之筆記

* 執行方式

```

PS D:\ccc\sp\code\c\03-asmVm\gcc\01-add> gcc main.c add.c -o add
PS D:\ccc\sp\code\c\03-asmVm\gcc\01-add> ./add
add(5, 8)=13
PS D:\ccc\sp\code\c\03-asmVm\gcc\01-add> gcc -S add.c -o add.s

(有註解版本)
PS D:\ccc\sp\code\c\03-asmVm\gcc\01-add> gcc -fverbose-asm -S add.c -o add.s
PS D:\ccc\sp\code\c\03-asmVm\gcc\01-add> gcc -fverbose-asm -S main.c -o main.s

```

* 理解過程

觀察add.s檔案

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/addx86.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/addx86-2.png)
