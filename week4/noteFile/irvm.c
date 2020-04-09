#include "ir.h"

Pair varList[VAR_MAX];
Map varMap;
int L[VAR_MAX];
int v[VAR_MAX];
int t[VAR_MAX] = { 0 };//負責存臨時變數

int *varLookup(char *name) {//查表函式，以便查出變數
  int h = mapFindIdx(&varMap, name);
  return &v[h];
}

int *varAdd(char *name) {//如果查表程式未查到變數將新增變數！
  return mapAdd(&varMap, name, &t[0])->value;
}

int irOp2(int a, char *op, int b) {
  if (eq(op, "+")) return a + b;
  if (eq(op, "-")) return a - b;
  if (eq(op, "*")) return a * b;
  if (eq(op, "/")) return a / b;
  if (eq(op, "%%")) return a % b;
  if (eq(op, "<")) return a < b;
  if (eq(op, ">")) return a > b;
  if (eq(op, "==")) return a == b;
  if (eq(op, "!=")) return a != b;
  if (eq(op, "<=")) return a <= b;
  if (eq(op, ">=")) return a >= b;
  error("irOp2: op=%s not found!", op);
}

int irExec(int i) {
  IR *p = &ir[i];//p為一IR結構體指標，指向方才於ir.h宣告的ir陣列。
  char *op = p->op;//將ir陣列中的op以指標的方式訪問並存為字串。
  int pc = i + 1;//程式計數器+1。
  trace("%02d: ", i);//補充:類似C的printf，但trace只有才除錯狀態下才會有輸出，而printf在任何狀態都有輸出。
  if (eq(op, "s=t")) {
    int *vp = varLookup(p->s);
    *vp = t[p->t];
    trace("%s = t%d (%d)\n", p->s, p->t, *vp);
  } else if (eq(op, "t=s")) {
    int v = (isdigit(*p->s)) ? atoi(p->s) : *varLookup(p->s);
    t[p->t] = v;
    trace("t%d = %s (%d)\n", p->t, p->s, v);
  } else if (eq(op, "label")) {
    trace("(L%d) (%d)\n", p->label, L[p->label]);
  } else if (eq(op, "goto")) {
    pc = L[p->label];
    trace("goto L%d (%d)\n", p->label, pc);
  } else if (eq(op, "if-goto")) {
    int cond = t[p->t];
    trace("if t%d (%d) ", p->t, cond);
    if (cond) {
      pc = L[p->label];
      trace("goto L%d (%d)\n", p->label, pc);
    } else trace(" -- fail\n");
  } else if (eq(op, "ifnot-goto")) {
    int cond = t[p->t];
    trace("ifnot t%d (%d) ", p->t, cond);
    if (!cond) {
      pc = L[p->label];
      trace("goto L%d (%d)\n", p->label, L[p->label]);
    } else trace(" -- fail\n");
  } else {
    t[p->t] = irOp2(t[p->t1], op, t[p->t2]);
    trace("t%d = t%d %s t%d (%d)\n", p->t, p->t1, op, p->t2, t[p->t]);
  }
  return pc;
}

void irRun() {
  printf("===================irRun()=======================\n");
  mapNew(&varMap, VAR_MAX);
  for (int pc = 0; pc < irTop;) {
    pc = irExec(pc);
  }
}

