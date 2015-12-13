#include <stdlib.h>
#include <string.h>
#include "abssyn.h"
//#include <stdio.h>

Exp NumExp(int n) {
  Exp p = malloc(sizeof(*p));
  p->kind = numExp;
  p->exptype.num = n;
  return p;
}

Exp VarExp(char n[100]) {
  Exp p = malloc(sizeof(*p));
  p->kind = varExp;
  strcpy(p->exptype.var, n);
  return p;
}

Exp OpExp(Exp l, BinOp o, Exp r) {
  Exp p = malloc(sizeof(*p));
  p->kind = opExp;
  p->exptype.oper.left = l;
  p->exptype.oper.op = o;
  p->exptype.oper.right = r;
  //printf("ok\n");
  return p;
}

Exp BoolExp(bool bl) {
  Exp p = malloc(sizeof(*p));
  p->kind = boolExp;
  p->exptype.b = bl;
  return p;
}

Cmd WhileExp(Exp tst, Cmd d) {
  Cmd p = malloc(sizeof(*p));
  p->kind = whileExp;
  p->cmdtype.WH.test = tst;
  p->cmdtype.WH.doo = d;
  return p;
}

Cmd IfExp(Exp tst, Cmd d) {
  Cmd p = malloc(sizeof(*p));
  p->kind = ifExp;
  p->cmdtype.IF.test = tst;
  p->cmdtype.IF.cm = d;
  return p;
}

Cmd IfElseExp(Exp tst, Cmd i, Cmd el) {
  Cmd p = malloc(sizeof(*p));
  p->kind = ifElseExp;
  p->cmdtype.IFELSE.test = tst;
  p->cmdtype.IFELSE.iff = i;
  p->cmdtype.IFELSE.els = el;
  return p;
}

Cmd Attr(char n[100], Exp res) {
  Cmd p = malloc(sizeof(*p));
  p->kind = attr;
  strcpy(p->cmdtype.ATTR.var, n);
  p->cmdtype.ATTR.ex = res;
  return p;
}

Cmd Dec(Type t, char n[100]) {
  Cmd p = malloc(sizeof(*p));
  p->kind = dec;
  p->cmdtype.DEC.ty = t;
  strcpy(p->cmdtype.DEC.var, n);
  return p;
}

Cmd DecAt(Type t, char n[100], Exp res) {
  Cmd p = malloc(sizeof(*p));
  p->kind = decAt;
  p->cmdtype.DECAT.ty = t;
  strcpy(p->cmdtype.DECAT.var, n);
  p->cmdtype.DECAT.ex = res;
  return p;
}

Cmd CmdSeq(Cmd c1, Cmd c2) {
  Cmd p = malloc(sizeof(*p));
  p->kind = cmdSeq;
  p->cmdtype.CMDSEQ.cmd1 = c1;
  p->cmdtype.CMDSEQ.cmd2 = c2;
  return p;
}

Cmd BoolTest(Exp tst, Cmd ttst, Cmd ftst) {
  Cmd p = malloc(sizeof(*p));
  p->kind = boolTest;
  p->cmdtype.BOOLTEST.expTest = tst;
  p->cmdtype.BOOLTEST.tTest = ttst;
  p->cmdtype.BOOLTEST.fTest = ftst;
  return p;
}

Cmd SCmd(Cmd c) {
  Cmd p = malloc(sizeof(*p));
  p->kind = sCmd;
  p->cmdtype.cm = c;
  return p;
}

Prg PrgEps() {
  Prg p = malloc(sizeof(*p));
  p->kind = eps;
  p->cm = NULL;
  //printf("Test ok.\n");
  return p;
}

Prg PrgNotEps(Cmd c) {
  Prg p = malloc(sizeof(*p));
  p->kind = notEps;
  p->cm = c;
  //printf("Test also ok.\n");
  return p;
}

void printTree(Prg p) {
  
}
