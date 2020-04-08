#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TMAX 10000000
#define SMAX 100000

enum { Id, Int, Keyword, Literal, Char };

char *typeName[5] = {"Id", "Int", "Keyword", "Literal", "Char"};

char code[TMAX];
char strTable[TMAX], *strTableEnd=strTable;
char *tokens[TMAX];
int tokenTop=0;
int types[TMAX];

#define isDigit(ch) ((ch) >= '0' && (ch) <='9')

#define isAlpha(ch) (((ch) >= 'a' && (ch) <='z') || ((ch) >= 'A' && (ch) <= 'Z'))

int readText(char *fileName, char *text, int size) {
  FILE *file = fopen(fileName, "r");
  int len = fread(text, 1, size, file);
  text[len] = '\0';
  fclose(file);
  return len;
}

/* strTable =
#\0include\0"sum.h"\0int\0main\0.....
*/
char *next(char *p) {
  while (isspace(*p)) p++;//遇到空白就跳過，直接進入下一字元

  char *start = p; //         include "sum.h"
                   //         ^      ^
                   //  start= p      p
  int type;
  if (*p == '\0') return NULL;
  if (*p == '"') {//遇到引號的就直接一直印到下一個引號出現
    p++;
    while (*p != '"') p++;
    p++;
    type = Literal;
  } else if (*p >='0' && *p <='9') { // 數字
    while (*p >='0' && *p <='9') p++;
    type = Int;
  } else if (isAlpha(*p) || *p == '_') { // 變數名稱或關鍵字
    while (isAlpha(*p) || isDigit(*p) || *p == '_') p++;
    type = Id;
  } else { // 其餘都是單一字元
    p++;
    type = Char;
  }
  int len = p-start;//掃到的字串長度
  char *token = strTableEnd;
  strncpy(strTableEnd, start, len);//strTableEnd永遠指向strTable的結尾
  //從起始字串開始複製一個len長度的字串到strTableEnd
  strTableEnd[len] = '\0';//把最後的字元設成'\0'
  strTableEnd += (len+1);//把str指標往後移到剛剛的'\0'後面
  types[tokenTop] = type;//設定好此字串之型態
  tokens[tokenTop++] = token;
  printf("token=%s\n", token);//印出詞彙
  return p;
}

//打印一次程式
void lex(char *fileName) {
  char *p = code;
  while (1) {
    p = next(p);
    if (p == NULL) break;
  }
}

//以數字序號的方式印出所有token
void dump(char *strTable[], int top) {
  for (int i=0; i<top; i++) {
    printf("%d:%s\n", i, strTable[i]);
  }
}

int main(int argc, char * argv[]) {
  readText(argv[1], code, sizeof(code));
  puts(code);//印出code
  lex(code);//丟到lex掃描讀到的檔案
  dump(tokens, tokenTop);
}

