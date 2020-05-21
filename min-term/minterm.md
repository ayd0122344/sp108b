### 系統程式期中報告-組合語言研究(RISC-V, ARM, x86, CPU0)

## 前言-組合語言(Assembly language)

* 是任何一種用於電腦、微處理器、微控制器，或其他可程式化器件的低階語言。在不同的裝置中，組合語言對應著不同的機器語言指令集。

* 組譯過程：使用組合語言編寫的原始碼，然後通過相應的組譯程式將它們轉換成可執行的機器碼。

* 使用輔助記憶碼（Mnemonics）來代替和表示特定低階機器語言的操作。特定的組譯目標指令集可能會包括特定的運算元。許多組譯程式可以辨識代表位址和常數的標籤（Label）和符號（Symbols），這樣就可以用字元來代表運算元而無需採取寫死的方式。普遍地說，每一種特定的組合語言和其特定的機器語言指令集是一對一的。

* 組合語言在系統中角色如下圖所示：


## RISC-V

* 

## x86 

* ### 03-asmVm/01-add之筆記

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

* 理解過程

 - add.s檔案觀察結果

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/addx86.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/addx86-2.png)

* x86之堆疊- foorbar.c 執行與理解

 - 產生方式

```

連結網址: https://eli.thegreenplace.net/.../where-the-top-of-the...

PS D:\ccc\sp\code\c\03-asmVm\gcc\00-foobar> gcc -fverbose-asm -S foobar.c -o foobar.s

```
![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/x86stack.png)

> 00-foobar、02-sum的組合語言與大部分同add.s的寫法，在此不再贅述。