# Compiler.c - 3/18作業

## 解題思維

1. 寫下期望的中間碼成果
  
2. 思考Label個數
    
  `goto elseBegin`: 判斷式之後需加上此label。
    
       * 不符合判斷式則goto elseBegin
      
       * 符合則繼續執行下一行程式碼
      
  `End`: else下方需加上此label。
    
       * 如果進入if之後的判斷式成立，則執行完判斷式之後的Block應跳過else結束，不可進入else
    
3. 其餘跟while概念相同
  
## 執行方式

* 使用mingw32-make編譯多個C語言檔案:

   * PS C:\Users\nan\Desktop\系統程式\sp108b\note\week3\03-compiler> `mingw32-make`
gcc -std=c99 -O0 lexer.c compiler.c main.c -o compiler

* 執行測試資料夾中的if.c: 

  * PS C:\Users\nan\Desktop\系統程式\sp108b\note\week3\03-compiler> `./compiler test/if.c`

## 執行結果-if

```
a = 3;
b = 5;
c = 0;

if( a > b)
    c = a;
else
    c = b;
========== lex ==============
token=a
token==
token=3
token=;
token=b
token==
token=5
token=;
token=c
token==
token=0
token=;
token=if
token=(
token=a
token=>
token=b
token=)
token=c
token==
token=a
token=;
token=else
token=c
token==
token=b
token=;
========== dump ==============
0:a
1:=
2:3
3:;
4:b
5:=
6:5
7:;
8:c
9:=
10:0
11:;
12:if
13:(
14:a
15:>
16:b
17:)
18:c
19:=
20:a
21:;
22:else
23:c
24:=
25:b
26:;
============ parse =============
t0 = 3
a = t0
t1 = 5
b = t1
t2 = 0
c = t2
t3 = a
t4 = b
t5 = t3 > t4
if not t5 goto L0
t6 = a
c = t6
goto L1
(L0)
t7 = b
c = t7
(L1)

```
