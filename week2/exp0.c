#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

int tokenIdx = 0;//紀錄看到第幾個字
char *tokens;

int E();
int F();

//有任何錯誤時,印出錯誤訊息
void error(char *msg) {
  printf("%s", msg);
  assert(0);//讓程式停掉離開
}

//取得目前字元
char ch() {
  char c = tokens[tokenIdx];//tokens為運算字串, tokenIdx紀錄現在到哪個字
  return c;
}


char next() {
  char c = ch();//取得目前tokens的索引值下的字元,
  tokenIdx++;//把索引值+1以便下次進入next()時,呼叫ch()的結果為下一個字元
  return c;
}

//判斷下一個字元是否為+或-,是的話回傳true(1),否的話回傳false(0)
//由於C語言沒有字串型別,又字元指標可用來作為字串型別,故此處使用char *set來儲存"+-"
int isNext(char *set) {
  char c = ch();
  return (c!='\0' && strchr(set, c)!=NULL);
}

//產生下一個臨時變數(也就是組合語言中的位址編號)的代號EX: 0代表t0, 3代表 t3
int nextTemp() {
  static int tempIdx = 0;//static只會讓這行執行一次
  return tempIdx++;
}

// F =  Number | '(' E ')'
int F() {
  int f;
  char c = ch();
  if (isdigit(c)) {
    next(); // skip c
    f = nextTemp();//如果是數字則產生新的變數。E.g.3+5結果中的t0,t1
    printf("t%d=%c\n", f, c);//E.g.3+5結果中印出t0=3(f=0,c=3), t1=5(f=1,c=5)
  } else if (c=='(') { // '(' E ')',處理有括號的情況，像是 exp0 '3+(5-2)'，遇到"("後會進入處理(5-2)的程序,所以必須呼叫E()來處理括號內的運算式
    next();
    f = E();
    assert(ch()==')');//以assert確認後面是否還有一個")",否的話則終止程式並離開
    next();
  } else {
    error("F = (E) | Number fail!");
  }
  return f; 
}

// E = F ([+-] F)*,E.g.3+5 =>E在此為3+5,"="之後第一個"F"比對到"3","+"比對到"+"",第二個F比對到5
int E() {
  int i1 = F();//i1為一個數字。E.g.3+5的結果中t0的"0"。(3+5的過程中,遇到3時傳入F()後驗證他是數字,進入第一個if印出t0=3,並回傳F()中的f,也就是位址t0的"0"到此)
  while (isNext("+-")) {
    char op=next();//op是"+","-"
    int i2 = F();//i1為一個數字。E.g.3+5的結果中t1的"1"。
    int i = nextTemp();//產生下一個臨時變數,也就是組合語言中的下一個記憶體位址。E.g.3+5的結果中t2的"2"。
    printf("t%d=t%d%ct%d\n", i, i1, op, i2);
    i1 = i;//把最後的位址變成第一個位址繼續做運算。E.g.3+5的結果中t2的"2"存成i1繼續做下一個運算,也就是下一個被使用的位址應是t3。
  }
  return i1;
}

void parse(char *str) {
  tokens = str;//str為運算式(E.g."3+5"),將3+5設為tokens
  E();//呼叫E(),expression
}
//argc:參數的個數argument counter;argv:參數的陣列argument variable
int main(int argc, char * argv[]) {
  printf("argv[0]=%s argv[1]=%s\n", argv[0], argv[1]);
  printf("=== EBNF Grammar =====\n");
  printf("E=F ([+-] F)*\n");
  printf("F=Number | '(' E ')'\n");
  printf("==== parse:%s ========\n", argv[1]);
  parse(argv[1]);//argv[0]是"./exp0",為了取得運算式(E.g."3+5"),要取argv[1]
}

