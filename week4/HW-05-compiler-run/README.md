# 3/25作業 -為 05-compiler-run 加上 IF 的語法，並測試看看執行是否正確！

## 解題思維

同https://github.com/ayd0122344/sp108b/tree/master/week3/HW-03-compiler

## 注意重點

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/Hw0.png)

## 執行方式

* 使用mingw32-make編譯多個C語言檔案:

   * PS C:\Users\nan\Desktop\系統程式\sp108b\note\week3\03-compiler> `mingw32-make`
gcc -std=c99 -O0 lexer.c compiler.c main.c -o compiler

* 執行測試資料夾中的if.c: 

  * PS C:\Users\nan\Desktop\系統程式\sp108b\note\week3\03-compiler> `./compiler test/if.c`

## 執行結果-if

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/Hw1.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/Hw2.png)