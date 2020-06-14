## 習題解題方式

1. 先寫一個power的函數並儲存成.c檔

2. 將此power函數執行編譯不連結產生.o檔 => `gcc -c power.c`

3. 對產生出的power.o檔進行反組譯得到16進位的機器碼 => `objdump -d power.o`

4. 將此結果傾印成power.dump檔案並進行處理

```
nan@20190116-01 MINGW64 ~/Desktop/sp108b/sp108b/week9/c (master)
$ gcc -c power.c

nan@20190116-01 MINGW64 ~/Desktop/sp108b/sp108b/week9/c (master)
$ objdump -d power.o

power.o:     file format pe-i386


Disassembly of section .text:   

00000000 <_power>:
   0:   55                      push   %ebp
   1:   89 e5                   mov    %esp,%ebp
   3:   83 ec 10                sub    $0x10,%esp
   6:   c7 45 fc 01 00 00 00    movl   $0x1,-0x4(%ebp)
   d:   eb 0e                   jmp    1d <_power+0x1d>
   f:   8b 45 08                mov    0x8(%ebp),%eax
  12:   0f af 45 08             imul   0x8(%ebp),%eax
  16:   89 45 08                mov    %eax,0x8(%ebp)
  19:   83 45 fc 01             addl   $0x1,-0x4(%ebp)
  1d:   8b 45 fc                mov    -0x4(%ebp),%eax
  20:   3b 45 0c                cmp    0xc(%ebp),%eax
  23:   7c ea                   jl     f <_power+0xf>
  25:   8b 45 08                mov    0x8(%ebp),%eax
  28:   c9                      leave
  29:   c3                      ret
  2a:   90                      nop
  2b:   90                      nop

nan@20190116-01 MINGW64 ~/Desktop/sp108b/sp108b/week9/c (master)
$ objdump -d power.o > power.dump
```

5. 「一些處理」將前方的編號刪除、將後方的組合語言註解掉、在每個機器碼後方加上逗號、在每個機器碼前方加上0x代表16進位

6. 回到jitCall.c檔進行處理

    1. 在main()前定義函數原型<br>
    ```
    int (*power)(int a, int b);
    ```
    2. 在main前宣告unsigned char類型的powerCode陣列中加入「一些處理」後的機器碼<br>
    ```
    unsigned char powerCode[] = {
    0x55,                   				         //push   %ebp
    0x89, 0xe5,                			         //mov    %esp,%ebp
    0x83, 0xec, 0x10,             			      //sub    $0x10,%esp
    0xc7, 0x45, 0xfc, 0x01, 0x00, 0x00, 0x00, 	//movl   $0x1,-0x4(%ebp)
    0xeb, 0x0e,                			         //jmp    1d <_power+0x1d>
    0x8b, 0x45, 0x08,             			      //mov    0x8(%ebp),%eax
    0x0f, 0xaf, 0x45, 0x08,          		      //imul   0x8(%ebp),%eax
    0x89, 0x45, 0x08,             			      //mov    %eax,0x8(%ebp)
    0x83, 0x45, 0xfc, 0x01,          		      //addl   $0x1,-0x4(%ebp)
    0x8b, 0x45, 0xfc,             			      //mov    -0x4(%ebp),%eax
    0x3b, 0x45, 0x0c,             			      //cmp    0xc(%ebp),%eax
    0x7c, 0xea,                			         //jl     f <_power+0xf>
    0x8b, 0x45, 0x08,             			      //mov    0x8(%ebp),%eax
    0xc9,                   				         //leave  
    0xc3,                   				         //ret    
    0x90,                   				         //nop
    0x90,                   				         //nop
    };
    ```
    3. 在main()中加上以下程式段，完成! 
    ```
    power = (int (*)(int, int)) powerCode;
    printf("power(5,2)=%d\n", power(5, 2));
    ```

### 習題執行結果

```
nan@20190116-01 MINGW64 ~/Desktop/sp108b/sp108b/week9/習題 (master)
$ gcc jitCall.c -o jitCall

nan@20190116-01 MINGW64 ~/Desktop/sp108b/sp108b/week9/習題 (master)
$ ./jitCall
add(5, 8)=13
sum(10)=55   
fib(10)=89   
power(5,2)=25
```
