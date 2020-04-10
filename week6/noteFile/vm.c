#include <stdio.h>
#include <assert.h>
#include <stdint.h>

int imTop = 0;
int16_t im[32768], m[65536];
//im為指令記憶體,m為資料記憶體(原32768(32K)就夠了，但為了後面擴充容易起見，放大至65536(64K))

#define BIT0 0x0001
#define BIT1 0x0002
#define BIT2 0x0004

int run(uint16_t *im, int16_t *m) {
  int16_t D = 0, A = 0, PC = 0;//PC=program counter，A=A register(save address)，D=D register
  uint16_t I = 0;
  uint16_t a, c, d, j;
  while (1) {
    //無窮迴圈，指令超出程式大小會跳出。
    //在虛擬機可以這樣寫，但真實機很難知道你的程式大小，因為整個記憶體都可以使用
    int16_t aluOut = 0, AM = 0;
    if (PC >= imTop) { //imTop為指令記憶體讀入的程式大小(在main()讀入的)
      printf("exit program !\n");
      break;
    }
    I = im[PC];//取出im[PC](指令記憶體中目前的指令)放到I
    printf("PC=%04X I=%04X", PC, I);//印出PC跟I的值
    PC ++;//取完後PC+1

    //A指令第一碼為0，C指令前三碼為1
    if ((I & 0x8000) == 0) { //檢查是否為 A 指令，0x代表16進位，8000=1000 0000 0000 0000
      A = I;//如果是A指令就直接印出來
    } 
    
    else { // 檢查是否為 C 指令
      a = (I & 0x1000) >> 12;//1000: 0001 0000 0000 0000
      c = (I & 0x0FC0) >>  6;//0FC0: 0000 1111 1100 0000
      d = (I & 0x0038) >>  3;//0038: 0000 0000 0011 1000
      j = (I & 0x0007) >>  0;//0007: 0000 0000 0000 0111
      // 右移為變相地分別取出a、c、d、j區塊真正的值，以便下面依照syntax來encode
      if (a == 0) AM = A; else AM = m[A];//AM的意思是AorM的意思，AM=A是指在這裡為A register，AM = m[A]是指在這裡為記憶體
      switch (c) { // 處理 c1..6, 計算 aluOut
        case 0x2A: aluOut = 0;  break; // "0",   "101010"
        case 0x3F: aluOut = 1;  break; // "1",   "111111"
        case 0x3A: aluOut = -1; break; // "-1",  "111010"
        case 0x0C: aluOut = D;  break; // "D",   "001100"
        case 0x30: aluOut = AM; break; // "AM",  "110000"
        case 0x0D: aluOut = D^0xFFFF; break; // "!D",  "001101"
        case 0x31: aluOut = AM^0xFFFF; break; // "!AM", "110001"
        case 0x0F: aluOut = -D; break; // "-D",  "001111"
        case 0x33: aluOut = -AM; break; // "-AM", "110011"
        case 0x1F: aluOut = D+1; break; // "D+1", "011111"
        case 0x37: aluOut = AM+1; break; // "AM+1","110111"
        case 0x0E: aluOut = D-1; break; // "D-1", "001110"
        case 0x32: aluOut = AM-1; break; // "AM-1","110010"
        case 0x02: aluOut = D+AM; break; // "D+AM","000010"
        case 0x13: aluOut = D-AM; break; // "D-AM","010011"
        case 0x07: aluOut = AM-D; break; // "AM-D","000111"
        case 0x00: aluOut = D&AM; break; // "D&AM","000000"
        case 0x15: aluOut = D|AM; break; // "D|AM","010101"
        default: assert(0);
      }
      if (d&BIT2) A = aluOut;
      if (d&BIT1) D = aluOut;
      if (d&BIT0) m[A] = aluOut;
      switch (j) {
        case 0x0: break;                          // 
        case 0x1: if (aluOut >  0) PC = A; break; // JGT
        case 0x2: if (aluOut == 0) PC = A; break; // JEQ
        case 0x3: if (aluOut >= 0) PC = A; break; // JGE
        case 0x4: if (aluOut <  0) PC = A; break; // JLT
        case 0x5: if (aluOut != 0) PC = A; break; // JNE
        case 0x6: if (aluOut <= 0) PC = A; break; // JLE
        case 0x7: PC = A; break;                  // JMP
      }
    }
    printf(" A=%04X D=%04X m[A]=%04X", A, D, m[A]);
    if ((I & 0x8000) != 0) printf(" a=%X c=%02X d=%X j=%X", a, c, d, j);
    printf("\n");
  }
}

// run: ./vm <file.bin>
int main(int argc, char *argv[]) {
  char *binFileName = argv[1];
  //1. 取得第一個參數。如:"./vm ../test/sum.bin"中的"../test/sum.bin"， ./vm為argv[0]
  FILE *binFile = fopen(binFileName, "rb");//2. 用fopen開啟bin檔(由組譯器將asm檔轉換而成)
  imTop = fread(im, sizeof(uint16_t), 32768, binFile);//3. 把bin檔整個讀到im(instruction memory指令記憶體)中
  fclose(binFile);//4.讀完後關閉
  run(im, m);//5.把剛剛讀進指令記憶體的程式拿來跑
}
