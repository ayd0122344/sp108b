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
  char c = tokens[tokenIdx];
  return c;
}

//取得目前字元,同時進入下一格
char next() {
  char c = ch();
  tokenIdx++;
  return c;
}

//讓程式初始化
int isNext(char *set) {
  char c = ch();
  return (c!='\0' && strchr(set, c)!=NULL);
}

//產生下一個臨時變數的代號EX: 0 代表 t0,3 代表 t3
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
    f = nextTemp();
    printf("t%d=%c\n", f, c);
  } else if (c=='(') { // '(' E ')'
    next();
    f = E();
    assert(ch()==')');//確認還要一個"("
    next();
  } else {
    error("F = (E) | Number fail!");
  }
  return f; 
}

// E = F ([+-] F)*
int E() {
  int i1 = F();
  while (isNext("+-")) {
    char op=next();
    int i2 = F();
    int i = nextTemp();
    printf("t%d=t%d%ct%d\n", i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

void parse(char *str) {
  tokens = str;
  E();
}
//argc:參數的個數argument counter;argv:參數的陣列argument variable
int main(int argc, char * argv[]) {
  printf("argv[0]=%s argv[1]=%s\n", argv[0], argv[1]);
  printf("=== EBNF Grammar =====\n");
  printf("E=F ([+-] F)*\n");
  printf("F=Number | '(' E ')'\n");
  printf("==== parse:%s ========\n", argv[1]);
  parse(argv[1]);
}
