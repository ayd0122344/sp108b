# 系統程式期中報告-組合語言研究(RISC-V, ARM, x86, CPU0)

## 前言-組合語言(Assembly language)

* 是任何一種用於電腦、微處理器、微控制器，或其他可程式化器件的低階語言。在不同的裝置中，組合語言對應著不同的機器語言指令集。

* `組譯過程`：使用組合語言編寫的原始碼，然後通過相應的組譯程式將它們轉換成可執行的機器碼。

* `使用輔助記憶碼（Mnemonics）`：用以代替和表示特定低階機器語言的操作。特定的組譯目標指令集可能會包括特定的運算元。許多組譯程式可以辨識代表位址和常數的標籤（Label）和符號（Symbols），這樣就可以用字元來代表運算元而無需採取寫死的方式。普遍地說，每一種特定的組合語言和其特定的機器語言指令集是一對一的。

* 組合語言在系統中角色如下圖所示：

![](https://github.com/ayd0122344/sp108b/blob/master/min-term/image/character.jpg)

## RISC-V

* 是一個基於精簡指令集（RISC）原則的開源指令集架構（ISA）。

* `和多數指令集之差異`：可以自由地用於任何目的，允許任何人設計、製造和銷售RISC-V晶片和軟體而不必支付給任何公司專利費。

* `不是第一個開源指令集，卻具有重要意義`：其設計使其適用於現代計算裝置（如倉庫規模雲端運算機、高階行動電話和微小嵌入式系統）。設計者考慮到了這些用途中的效能與功率效率。該指令集還具有眾多支援的軟體，這解決了新指令集通常的弱點。

## ARM

* 

## x86 

### 

### 上課教材之03-asmVm/01-add之筆記

* add.s檔案理解結果

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/addx86.png)

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/addx86-2.png)

* x86之堆疊- foorbar.c 理解結果

![](https://github.com/ayd0122344/sp108b/blob/master/week6/Image/x86stack.png)

> 00-foobar、02-sum的組合語言與大部分同add.s的寫法，在此不再贅述。

## hackCPU

### 以本學期組譯器: asm.c 之成果來解說

![](https://github.com/ayd0122344/sp108b/blob/master/week4/Image/PASS2.png)

## CPU0
