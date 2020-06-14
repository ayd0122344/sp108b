## week9筆記

### 05-obj/01-objdump
```
PS D:\ccc\sp\code\c\05-obj\01-objdump> gcc main.c add.c -o add  ------> 編譯並連結，產生add.exe
PS D:\ccc\sp\code\c\05-obj\01-objdump> ./add ------> 執行add.exe
add(5, 8)=13
PS D:\ccc\sp\code\c\05-obj\01-objdump> gcc -c add.c ------> 只編譯不連結，產生add.o目的檔
PS D:\ccc\sp\code\c\05-obj\01-objdump> gcc -c main.c ------> 只編譯不連結，產生main.o目的檔
```
* 使用objdump+s參數來觀察目的檔，以16進位的方式印出相關的段落

執行結果
```
add.o:     file format pe-i386

Contents of section .text:
 0000 5589e583 ec108b45 088945fc 8b450c89  U......E..E..E..
 0010 45f88b55 088b450c 01d0c9c3           E..U..E.....    
Contents of section .rdata$zzz:
 0000 4743433a 20284d69 6e47572e 6f726720  GCC: (MinGW.org 
 0010 4743432d 362e332e 302d3129 20362e33  GCC-6.3.0-1) 6.3
 0020 2e300000                             .0..
Contents of section .eh_frame:
 0000 14000000 00000000 017a5200 017c0801  .........zR..|..
 0000 14000000 00000000 017a5200 017c0801  .........zR..|..
 0010 1b0c0404 88010000 1c000000 1c000000  ................
 0020 04000000 1c000000 00410e08 8502420d  .........A....B.
 0030 0558c50c 04040000                    .X......
```

* 使用objdump+d參數來進行反組譯的動作

執行結果
```
add.o:     file format pe-i386


Disassembly of section .text:

00000000 <_add>:
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   83 ec 10                sub    $0x10,%esp
   6:   8b 45 08                mov    0x8(%ebp),%eax
   9:   89 45 fc                mov    %eax,-0x4(%ebp)
   c:   8b 45 0c                mov    0xc(%ebp),%eax
   f:   89 45 f8                mov    %eax,-0x8(%ebp)
  12:   8b 55 08                mov    0x8(%ebp),%edx
  15:   8b 45 0c                mov    0xc(%ebp),%eax
  18:   01 d0                   add    %edx,%eax
  1a:   c9                      leave
  1b:   c3                      ret
```

* 使用objdump+h參數來印表頭的部分

執行結果
```
add.o:     file format pe-i386

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         0000001c  00000000  00000000  000000dc  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000000  00000000  00000000  00000000  2**2
                  ALLOC, LOAD, DATA
  2 .bss          00000000  00000000  00000000  00000000  2**2
                  ALLOC
  3 .rdata$zzz    00000024  00000000  00000000  000000f8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .eh_frame     00000038  00000000  00000000  0000011c  2**2
                  CONTENTS, ALLOC, LOAD, RELOC, READONLY, DATA
```
<table border="1">
<tr>
    <td>Idx</td>
    <td>Name</td>
    <td>Size</td>
    <td>VMA</td>
    <td>LMA</td>
    <td>File off</td>
    <td>Algn</td>
</tr>
<tr>
    <td>段的代號</td>
    <td>段的名稱</td>
    <td>段的大小</td>
    <td>虛擬記憶體位址</td>
    <td>邏輯記憶體位址</td>
    <td>檔案內的位移</td>
    <td>對齊方式</td>
</tr>
</table>

### 05-obj\03-jitCall\win32\jitCall.c

* 程式中直接定義三個函數原型(add,sum,fib)，透過objdump做反組譯所得到的機器碼經過「一些處理」後放到jitCall.c檔中即可執行!

* 註明: 「一些處理」會在習題的README.md中詳述~<br>
[- 習題入口 -](https://github.com/ayd0122344/sp108b/tree/master/week9/%E7%BF%92%E9%A1%8C)
