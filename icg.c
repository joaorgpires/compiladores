#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abssyn.h"
#include "icg.h"

FILE * fout;

int nTacs = 0;
int nVars = 0;
int nAddr = 0;
int nLab = 0;
int fl = 0;
char Vars[10000][100];
Tac Tacs[10000];

int exists(char var[]) {
  int i;
  for(i = 0; i < nVars; i++) {
    if(!strcmp(Vars[i], var))
      return i;
  }
  
  if(i == nVars)
    return -1;
}

void genAddr4Exp(char name[], Exp e) {
  Tacs[nTacs] = malloc(sizeof(*Tacs[nTacs]));
  strcpy(Tacs[nTacs]->name, name);
  
  if(e->kind != opExp) {
    switch(e->kind) {
    case numExp:
      Tacs[nTacs]->ID = TCInt;
      Tacs[nTacs]->tactype.l = e->exptype.num;
      nTacs++;
      break;
    case varExp:
      Tacs[nTacs]->ID = TCVar;
      if(exists(e->exptype.var) == -1) {
	fl = 1;
	printf("%s was not declared!\n", e->exptype.var);
      }
      strcpy(Tacs[nTacs]->tactype.r, e->exptype.var);
      nTacs++;
      break;
    case boolExp:
      Tacs[nTacs]->ID = TCBool;
      Tacs[nTacs]->tactype.b = e->exptype.b;
      nTacs++;
      break;
    }
    
    return;
  }
  
  switch (e->exptype.oper.op) {
    
  case Plus:
    Tacs[nTacs]->op = TCPlus;
    break;
    
  case Minus:
    Tacs[nTacs]->op = TCMinus;
    break;
    
  case Times:
    Tacs[nTacs]->op = TCTimes;
    break;
    
  case Div:
    Tacs[nTacs]->op = TCDiv;
    break;
    
  case Mod:
    Tacs[nTacs]->op = TCMod;
    break;
    
  case Or:
    Tacs[nTacs]->op = TCOr;
    break;
  
  case And:
    Tacs[nTacs]->op = TCAnd;
    break;

  case Eq:
    Tacs[nTacs]->op = TCEq;
    break;
    
  case Neq:
    Tacs[nTacs]->op = TCNeq;
    break;

  case Lt:
    Tacs[nTacs]->op = TCLt;
    break;

  case Le:
    Tacs[nTacs]->op = TCLe;
    break;

  case Gt:
    Tacs[nTacs]->op = TCGt;
    break;

  case Ge:
    Tacs[nTacs]->op = TCGe;
    break;
    
  }
  
  Exp l = e->exptype.oper.left;
  Exp r = e->exptype.oper.right;
  if(l->kind == numExp && r->kind == numExp) {
    Tacs[nTacs]->ID = TCIntInt;
    Tacs[nTacs]->tactype.TCINTINT.l = l->exptype.num;
    Tacs[nTacs]->tactype.TCINTINT.r = r->exptype.num;
    nTacs++;
  }
  else if(l->kind == numExp && r->kind == varExp) {
    Tacs[nTacs]->ID = TCIntVar;
    Tacs[nTacs]->tactype.TCINTVAR.l = l->exptype.num;
    if(exists(r->exptype.var) == -1) {
      fl = 1;
      printf("%s was not declared!\n", r->exptype.var);
    }
    strcpy(Tacs[nTacs]->tactype.TCINTVAR.r, r->exptype.var);
    nTacs++;
  }
  else if(l->kind == varExp && r->kind == varExp) {
    Tacs[nTacs]->ID = TCVarVar;
    if(exists(l->exptype.var) == -1) {
      fl = 1;
      printf("%s was not declared!\n", l->exptype.var);
    }
    if(exists(r->exptype.var) == -1) {
      fl = 1;
      printf("%s was not declared!\n", r->exptype.var);
    }
    strcpy(Tacs[nTacs]->tactype.TCVARVAR.l, l->exptype.var);
    strcpy(Tacs[nTacs]->tactype.TCVARVAR.r, r->exptype.var);
    nTacs++;
  }
  else if(l->kind == varExp && r->kind == numExp) {
    Tacs[nTacs]->ID = TCVarInt;
    if(exists(l->exptype.var) == -1) {
      fl = 1;
      printf("%s was not declared!\n", l->exptype.var);
    }
    strcpy(Tacs[nTacs]->tactype.TCVARINT.l, l->exptype.var);
    Tacs[nTacs]->tactype.TCVARINT.r = r->exptype.num;
    nTacs++;
  }
  else if(l->kind == numExp && r->kind == opExp) {
    Tacs[nTacs]->ID = TCIntExp;
    Tacs[nTacs]->tactype.TCINTEXP.l = l->exptype.num;
    char c[20];
    sprintf(c, "t%d", nAddr++);
    strcpy(Tacs[nTacs]->tactype.TCINTEXP.r, c);
    nTacs++;
    Exp expl = r->exptype.oper.left;
    Exp expr = r->exptype.oper.right;
    BinOp o = r->exptype.oper.op;
    Exp e = malloc(sizeof(*e));
    e->kind = opExp;
    e->exptype.oper.left = expl;
    e->exptype.oper.right = expr;
    e->exptype.oper.op = o;
    genAddr4Exp(c, e);
  }
  else if(r->kind == numExp && l->kind == opExp) {
    Tacs[nTacs]->ID = TCIntExp;
    Tacs[nTacs]->tactype.TCINTEXP.l = r->exptype.num;
    char c[20];
    sprintf(c, "t%d", nAddr++);
    strcpy(Tacs[nTacs]->tactype.TCINTEXP.r, c);
    nTacs++;
    Exp expl = l->exptype.oper.left;
    Exp expr = l->exptype.oper.right;
    BinOp o = l->exptype.oper.op;
    Exp e = malloc(sizeof(*e));
    e->kind = opExp;
    e->exptype.oper.left = expl;
    e->exptype.oper.right = expr;
    e->exptype.oper.op = o;
    genAddr4Exp(c, e);
  }
  else if(l->kind == opExp && r->kind == opExp) {
    Tacs[nTacs]->ID = TCExpExp;
    int tmp = nTacs;
    nTacs++;
    char c[20];
    sprintf(c, "t%d", nAddr++);
    strcpy(Tacs[tmp]->tactype.TCEXPEXP.l, c);
    Exp expl = l->exptype.oper.left;
    Exp expr = l->exptype.oper.right;
    BinOp o = l->exptype.oper.op;
    Exp e = malloc(sizeof(*e));
    e->kind = opExp;
    e->exptype.oper.left = expl;
    e->exptype.oper.right = expr;
    e->exptype.oper.op = o;
    genAddr4Exp(c, e);
    sprintf(c, "t%d", nAddr++);
    strcpy(Tacs[tmp]->tactype.TCEXPEXP.l, c);
    expl = r->exptype.oper.left;
    expr = r->exptype.oper.right;
    o = r->exptype.oper.op;
    e = malloc(sizeof(*e));
    e->kind = opExp;
    e->exptype.oper.left = expl;
    e->exptype.oper.right = expr;
    e->exptype.oper.op = o;
    genAddr4Exp(c, e);
  }
  else if(l->kind == numExp && r->kind == boolExp) {
    Tacs[nTacs]->ID = TCIntBool;
    Tacs[nTacs]->tactype.TCINTBOOL.l = l->exptype.num;
    Tacs[nTacs]->tactype.TCINTBOOL.r = r->exptype.b;
    nTacs++;
  }
  else if(r->kind == numExp && l->kind == boolExp) {
    Tacs[nTacs]->ID = TCIntBool;
    Tacs[nTacs]->tactype.TCINTBOOL.l = r->exptype.num;
    Tacs[nTacs]->tactype.TCINTBOOL.r = l->exptype.b;
    nTacs++;
  }
  else if(l->kind == boolExp && r->kind == boolExp) {
    Tacs[nTacs]->ID = TCBoolBool;
    Tacs[nTacs]->tactype.TCBOOLBOOL.l = l->exptype.b;
    Tacs[nTacs]->tactype.TCBOOLBOOL.r = r->exptype.b;
    nTacs++;
  }
  else if(l->kind == boolExp && r->kind == varExp) {
    Tacs[nTacs]->ID = TCBoolVar;
    Tacs[nTacs]->tactype.TCBOOLVAR.l = l->exptype.b;
    if(exists(r->exptype.var) == -1) {
      fl = 1;
      printf("%s was not declared!\n", r->exptype.var);
    }
    strcpy(Tacs[nTacs]->tactype.TCBOOLVAR.r, r->exptype.var);
    nTacs++;
  }
  else if(r->kind == boolExp && l->kind == varExp) {
    Tacs[nTacs]->ID = TCBoolVar;
    Tacs[nTacs]->tactype.TCBOOLVAR.l = r->exptype.b;
    if(exists(l->exptype.var) == -1) {
      fl = 1;
      printf("%s was not declared!\n", l->exptype.var);
    }
    strcpy(Tacs[nTacs]->tactype.TCBOOLVAR.r, l->exptype.var);
    nTacs++;
  }
  else if(l->kind == boolExp && r->kind == opExp) {
    Tacs[nTacs]->ID = TCBoolExp;
    Tacs[nTacs]->tactype.TCBOOLEXP.l = l->exptype.b;
    char c[20];
    sprintf(c, "t%d", nAddr++);
    strcpy(Tacs[nTacs]->tactype.TCBOOLEXP.r, c);
    nTacs++;
    Exp expl = r->exptype.oper.left;
    Exp expr = r->exptype.oper.right;
    BinOp o = r->exptype.oper.op;
    Exp e = malloc(sizeof(*e));
    e->kind = opExp;
    e->exptype.oper.left = expl;
    e->exptype.oper.right = expr;
    e->exptype.oper.op = o;
    genAddr4Exp(c, e);
  }
  else if(r->kind == boolExp && l->kind == opExp) {
    Tacs[nTacs]->ID = TCBoolExp;
    Tacs[nTacs]->tactype.TCBOOLEXP.l = r->exptype.b;
    char c[20];
    sprintf(c, "t%d", nAddr++);
    strcpy(Tacs[nTacs]->tactype.TCBOOLEXP.r, c);
    nTacs++;
    Exp expl = l->exptype.oper.left;
    Exp expr = l->exptype.oper.right;
    BinOp o = l->exptype.oper.op;
    Exp e = malloc(sizeof(*e));
    e->kind = opExp;
    e->exptype.oper.left = expl;
    e->exptype.oper.right = expr;
    e->exptype.oper.op = o;
    genAddr4Exp(c, e);
  }
  else if(l->kind == varExp && r->kind == opExp) {
    Tacs[nTacs]->ID = TCVarExp;
    if(exists(l->exptype.var) == -1) {
      fl = 1;
      printf("%s was not declared!\n", l->exptype.var);
    }
    strcpy(Tacs[nTacs]->tactype.TCVAREXP.l, l->exptype.var);
    char c[20];
    sprintf(c, "t%d", nAddr++);
    strcpy(Tacs[nTacs]->tactype.TCVAREXP.r, c);
    nTacs++;
    Exp expl = r->exptype.oper.left;
    Exp expr = r->exptype.oper.right;
    BinOp o = r->exptype.oper.op;
    Exp e = malloc(sizeof(*e));
    e->kind = opExp;
    e->exptype.oper.left = expl;
    e->exptype.oper.right = expr;
    e->exptype.oper.op = o;
    genAddr4Exp(c, e);
  }
  else if(r->kind == varExp && l->kind == opExp) {
    Tacs[nTacs]->ID = TCVarExp;
    if(exists(r->exptype.var) == -1) {
      fl = 1;
      printf("%s was not declared!\n", r->exptype.var);
    }
    strcpy(Tacs[nTacs]->tactype.TCVAREXP.l, r->exptype.var);
    char c[20];
    sprintf(c, "t%d", nAddr++);
    strcpy(Tacs[nTacs]->tactype.TCVAREXP.r, c);
    nTacs++;
    Exp expl = r->exptype.oper.left;
    Exp expr = r->exptype.oper.right;
    BinOp o = r->exptype.oper.op;
    Exp e = malloc(sizeof(*e));
    e->kind = opExp;
    e->exptype.oper.left = expl;
    e->exptype.oper.right = expr;
    e->exptype.oper.op = o;
    genAddr4Exp(c, e);
  }
}

void genAddr(Cmd c) {
  switch(c->kind) {
    
  case whileExp:
    
    break;

  case ifExp:

    break;
    
  case ifElseExp:

    break;
    
  case attr:
    if(exists(c->cmdtype.ATTR.var) == -1) {
      printf("%s was not declared!\n", c->cmdtype.ATTR.var);
      fl = 1;
    }
    else {
      Tacs[nTacs] = malloc(sizeof(*Tacs[nTacs]));
      Tacs[nTacs]->ID = TCcmd;
      Tacs[nTacs]->op = TCattr;
      char ch[20];
      sprintf(ch, "t%d", nAddr++);
      strcpy(Tacs[nTacs]->name, ch);
      strcpy(Tacs[nTacs]->tactype.TCATTR.name, c->cmdtype.ATTR.var);
      sprintf(ch, "t%d", nAddr++);
      strcpy(Tacs[nTacs]->tactype.TCATTR.e, ch);
      nTacs++;
      genAddr4Exp(ch, c->cmdtype.ATTR.ex);
    }
    break;
    
  case dec:
    if(exists(c->cmdtype.DEC.var) == -1) {
      strcpy(Vars[nVars], c->cmdtype.DEC.var);
      nVars++;
    }
    else {
      printf("%s declared more than once.\n", c->cmdtype.DEC.var);
      fl = 1;
    }
    
    break;

  case decAt:
    if(exists(c->cmdtype.DECAT.var) == -1) {
      strcpy(Vars[nVars], c->cmdtype.DECAT.var);
      nVars++;
      Tacs[nTacs] = malloc(sizeof(*Tacs[nTacs]));
      Tacs[nTacs]->ID = TCcmd;
      Tacs[nTacs]->op = TCattr;
      char ch[20];
      sprintf(ch, "t%d", nAddr++);
      strcpy(Tacs[nTacs]->name, ch);
      strcpy(Tacs[nTacs]->tactype.TCATTR.name, c->cmdtype.DECAT.var);
      sprintf(ch, "t%d", nAddr++);
      strcpy(Tacs[nTacs]->tactype.TCATTR.e, ch);
      nTacs++;
      genAddr4Exp(ch, c->cmdtype.DECAT.ex);
    }
    else {
      printf("%s declared more than once.\n", c->cmdtype.DEC.var);
      fl = 1;
    }
    
    break;
    
  case cmdSeq:
    genAddr(c->cmdtype.CMDSEQ.cmd1);
    genAddr(c->cmdtype.CMDSEQ.cmd2);

    break;

  case boolTest:
    
    break;
    
  case sCmd:
    genAddr(c->cmdtype.cm);
    break;
    
  }
}

void printCmd(Tac t) {
  switch (t->op) {
  case TCattr:
    printf("%s := %s\n%s := %s\n", t->name, t->tactype.TCATTR.name, t->name, t->tactype.TCATTR.e);
  }
}

void printOper(Tac t) {
  switch (t->op) {
  case TCPlus:
    printf("+");
    break;
  case TCMinus:
    printf("-");
    break;
  case TCTimes:
    printf("*");
    break;
  case TCDiv:
    printf("/");
    break;
  case TCMod:
    printf("%%");
    break;
  case TCOr:
    printf("||");
    break;
  case TCAnd:
    printf("&&");
    break;
  case TCEq:
    printf("==");
    break;
  case TCNeq:
    printf("!=");
    break;
  case TCLt:
    printf("<");
    break;
  case TCLe:
    printf("<=");
    break;
  case TCGt:
    printf(">");
    break;
  case TCGe:
    printf(">=");
    break;
  }
}

void printTAC() {
  int i;
  for(i = 0; i < nTacs; i++) {
    Tac t = Tacs[i];
    switch (t->ID) {
      
    case TCInt:
      printf("%s := %d\n", t->name, t->tactype.l);
      break;
      
    case TCVar:
      printf("%s := %s\n", t->name, t->tactype.r);
      break;
      
    case TCBool:
      printf("%s := %d\n", t->name, t->tactype.b);
      break;
      
    case TCIntInt:
      printf("%s := %d ", t->name, t->tactype.TCINTINT.l);
      printOper(t);
      printf(" %d\n", t->tactype.TCINTINT.r);
      break;
      
    case TCIntVar:
      printf("%s := %d ", t->name, t->tactype.TCINTVAR.l);
      printOper(t);
      printf(" %s\n", t->tactype.TCINTVAR.r);
      break;
      
    case TCVarVar:
      printf("%s := %s ", t->name, t->tactype.TCVARVAR.l);
      printOper(t);
      printf(" %s\n", t->tactype.TCVARVAR.r);
      break;
      
    case TCVarInt:
      printf("%s := %s ", t->name, t->tactype.TCVARINT.l);
      printOper(t);
      printf(" %d\n", t->tactype.TCVARINT.r);
      break;
      
    case TCIntExp:
      printf("%s := %d ", t->name, t->tactype.TCINTEXP.l);
      printOper(t);
      printf(" %s\n", t->tactype.TCINTEXP.r);
      break;
      
    case TCExpExp:
      printf("%s := %s ", t->name, t->tactype.TCEXPEXP.l);
      printOper(t);
      printf(" %s\n", t->tactype.TCEXPEXP.r);
      break;
      
    case TCIntBool:
      printf("%s := %d ", t->name, t->tactype.TCINTBOOL.l);
      printOper(t);
      printf(" %d\n", t->tactype.TCINTBOOL.r);
      break;
      
    case TCBoolBool:
      printf("%s := %d ", t->name, t->tactype.TCBOOLBOOL.l);
      printOper(t);
      printf(" %d\n", t->tactype.TCBOOLBOOL.r);
      break;

    case TCBoolVar:
      printf("%s := %d ", t->name, t->tactype.TCBOOLVAR.l);
      printOper(t);
      printf(" %s\n", t->tactype.TCBOOLVAR.r);
      break;

    case TCBoolExp:
      printf("%s := %d ", t->name, t->tactype.TCBOOLEXP.l);
      printOper(t);
      printf(" %s\n", t->tactype.TCBOOLEXP.r);
      break;
      
    case TCVarExp:
      printf("%s := %s ", t->name, t->tactype.TCVAREXP.l);
      printOper(t);
      printf(" %s\n", t->tactype.TCVAREXP.r);
      break;
      
    case TCcmd:
      printCmd(t);
      break;

    }
  }
}

void tac2mips() {
  fprintf(fout, ".data\n");
  int i;
  for(i = 0; i < nVars; i++)
    fprintf(fout, "%s:\t.space 4\n", Vars[i]);
  fprintf(fout, ".text\n");
  fprintf(fout, "main:\n");
  for(i = 0; i < nTacs; i++) {
    //missing code tac2mips
  }
  fprintf(fout, "\tli\t$v0, 10\n");
  fprintf(fout, "\tsyscall\n");
}

void compile(Prg p, char fname[200]) {
  genAddr(p->cm);
  //printf("%d %d\n", nTacs, nVars);
  if(!fl) {
    printTAC();
    fout = fopen(fname, "w");
    tac2mips();
    fclose(fout);
  }
}
