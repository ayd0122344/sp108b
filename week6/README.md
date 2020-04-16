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

補充圖片

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/syntax.jpg)

* 執行方式

```
    mingw32-make => 

    1) ./asm ../test/Add => ./vm ../test/add.bin

    2) ./asm ../test/sum => ./vm ../test/sum.bin
```

* 執行結果探討

