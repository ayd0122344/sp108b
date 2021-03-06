> 本篇作為一個大綱整理，其餘詳情編寫在程式碼旁邊以便參照

註解入口:
1. https://github.com/ayd0122344/sp108b/blob/master/note/week2/exp0.c

2. https://github.com/ayd0122344/sp108b/blob/master/note/week2/exp0hack.c

3. https://github.com/ayd0122344/sp108b/blob/master/note/week2/exp0var.c

# exp0.c

## 理解3+5的過程

1. 設輸入為'`3+5`'：

   * 輸出結果為:
   
      * t0=3
      * t1=5
      * t2=t0+t1

2. 首先進入  parse(argv[1]);

    * argv[0]是"./exp0"，為了取得運算式`3+5`，要取argv[1]。

3. parse中，`3+5`被設為tokens，並呼叫E()。

4. E() 中，i1呼叫F()。

5. F() 中：

    1. c呼叫了 ch() 來取得目前字元，並判斷是否為數字 -- 是的話 nextTemp()產生新變數作為位址(如`3+5`取得3，nextTemp()則產生0，`t0`的0)。
  
    2. 印出 t0=3。
  
    3. 回到 E()。
  
6. isNext("+-")判斷運算式的下一個字元是否為 + 或 - (一樣由 ch()去取得)。

    * 如3+5，op 設為在此則被設為`+`。
  
7. i2再次呼叫 F()，同第5點所述，最後印出t1=5。

8. 最後由`printf("t%d=t%d%ct%d\n", i, i1, op, i2);`印出。

## 筆記

* 如果處理的是有括號的情況，像是 exp0 '3+(5-2)'，遇到"("後會進入處理(5-2)的程序,所以必須呼叫E()來處理括號內的運算式。

* `assert()` 可以做為一個debug的小技巧讓程式停掉離開。

* `char *set` C語言中沒有字串型態，但字元指標有做為字串的功能!

***

# exp0hack.c

* 大致與exp0相同，但exp0是輸出中間碼，exp0hack是將中間碼再編譯成hackCPU所使用的組合語言。

* exp0hack多了 genOp1 和 genOp2來做組合語言的輸出。

***

# exp0var.c

* 大致與exp0hack相同，但genOp1多了一個`isdigit()`來檢查是變數或是常數--變數的話是 D=M ，常數的話是 D=A。

