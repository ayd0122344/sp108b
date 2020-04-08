# week4筆記

> noteFile資料夾下的檔案為部分抓取以便老師閱讀註解部分，並非全部檔案故不可執行！

### 05-compiler資料夾內檔案關係圖

![](https://github.com/ayd0122344/sp108b/blob/master/note/week4/compilerChart.jpg)

這麼多檔案的關係是因為模組化，程式執行的時候會一直呼叫檔案，方便之後要做管理——

可能之後要修正某個功能的時候不會找很久，或是減少只有這裡改了而另一個檔案沒改就出現錯誤回報的風險。

但相對的閱讀起來就很吃力，大概類似看一個故事直接從結局開始看，根本不知道主角的前因後果，還要一直往前翻那樣XDDD

### 閱讀05-compiler-run之心得

1. 觀察compiler.c檔 : 發現主要的函式(STMT、WHILE、ASSIGN、E()、F()...)跟上周的03-compiler比起來多了呼叫ir的模組來emit程式碼。

2. 觀察ir.h檔: 裡面定義了一個名為"IR"的陣列結構，其中包含了目標參數、臨時參數、標記以及運算子。並在下方使用此結構宣告了一個陣列ir[]。

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

