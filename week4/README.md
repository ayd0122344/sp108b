# week4筆記

## 3/25作業入口

* [點我進入](https://github.com/ayd0122344/sp108b/tree/master/week4/HW-05-compiler-run)

## 05-compiler資料夾內檔案關係圖

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/compilerChart.jpg)

這麼多檔案的關係是因為模組化，程式執行的時候會一直呼叫檔案，方便之後要做管理——

可能之後要修正某個功能的時候不會找很久，或是減少只有這裡改了而另一個檔案沒改就出現錯誤回報的風險。

但相對的閱讀起來就很吃力，大概類似看一個故事直接從結局開始看，根本不知道主角的前因後果，還要一直往前翻那樣XDDD

## 編譯器:05-compiler-run之筆記

> 執行方式: mingw32-make => ./compiler test/sum.c -ir 或 ./compiler test/sum.c -run

1. 觀察compiler.c檔 : 發現主要的函式(STMT、WHILE、ASSIGN、E()、F()...)跟上周的03-compiler比起來多了呼叫ir的模組來emit程式碼。

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/compiler.png)

2. 觀察ir.h檔: 裡面定義了一個名為"IR"的陣列結構，其中包含了目標參數、臨時參數、標記以及運算子。並在下方使用此結構宣告了一個陣列ir[]。

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/ir.png)

3. 觀察定義emit功能ir.c檔 : 

    * 因為有了上述的IR結構，所以每次emit都會創建一個IR結構。

    * 其中有許多irEmit的相關格式化模組，最後用irPrint()執行並傳回irDump()來將這些中間碼印出。此處舉irEmitAssignTs為例: 

        * irEmitAssignTs程式碼: 
        ```
        void irEmitAssignSt(char *s, int t) {
        irNew((IR) {.type=IrAssignSt, .op="s=t", .t=t, .s=s});
        }
        ```

        `.type=IrAssignSt`輸出t5=s之類的東西、`.op="s=t"`輸出s=t、`t`取得代號、`s`取得名字。

4. 觀察irvm.c檔(執行中間碼的程式): 

    * 自我不足點補充 —— 箭頭運算子"->"使用時機:
        
        * 與點運算子( . )相似，兩者都是二元操作符，而且右邊的運算元都是結構體中成員的名稱。

        * 與點運算子( . )不同的地方在於: "."左邊運算元是一個結果為結構的表示式，而"->"的左邊的運算元是一個指向結構體的" 指  標 "。

        * E.g. (參考網站: https://www.itread01.com/content/1544015299.html)

        ```
        typedef struct          // 定義一個結構體型別：DATA
        {
            char key[10];       // 結構體成員：key
            char name[20];      // 結構體成員：name
            int age;            // 結構體成員：age
        }DATA;
            
        DATA data;              // 宣告一個結構體變數
        DATA *pdata;            // 宣告一個指向結構體的指標
            
        // 訪問資料操作如下：
        data.age = 24;          // 結構體變數通過點運算子( . )訪問
        pdata->age = 24;        // 指向結構體的指標通過箭頭運算子( -> )訪問

        ```

        * 結論: 使用->時，左邊必須為欲訪問之結構體指標
        
![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/irvm1.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/irvm2.png)

### 成果理解

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/irDump%E7%90%86%E8%A7%A3.png)
![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/irRun%E7%90%86%E8%A7%A3.png)

## 組譯器: asm.c 之筆記

> 執行方式: mingw32-make => ./asm ../test/Add

### 成果理解

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/PASS2.png)

>> 執行方式: mingw32-make => ./asm ../test/sum

### 成果理解

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/asmPass1.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/asmPass2.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/asmParse.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/asmCode2Bin.png)

## 其他相關筆記入口

* compiler.h

https://github.com/ayd0122344/sp108b/blob/master/week4/noteFile/compiler.h



