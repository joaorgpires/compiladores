#ifndef ABSSYN_H
#define ABSSYN_H

typedef struct BinExp *Exp;
typedef struct Com *Cmd;
typedef struct Prgm *Prg;
typedef struct ST *SymTab;
typedef enum {Plus, Minus, Times, Div, Mod, Or, And, Eq, Neq, Lt, Le, Gt, Ge} BinOp;
typedef enum {Int, Bool} Type;
typedef enum {false, true} bool;

struct Prgm {
  enum {eps, notEps} kind;
  Cmd cm;
};

struct BinExp {
  enum {numExp, varExp, opExp, boolExp} kind;
  union {
    int num;
    char var[100];
    bool b;
    struct {Exp left; BinOp op; Exp right;} oper;
  } exptype;
};

struct Com {
  enum {whileExp, ifExp, ifElseExp, attr, dec, decAt, cmdSeq, boolTest, sCmd} kind;
  union {
    struct {Exp test; Cmd doo;} WH;
    struct {Exp test; Cmd cm;} IF;
    struct {Exp test; Cmd iff; Cmd els;} IFELSE;
    struct {char var[100]; Exp ex;} ATTR;
    struct {Type ty; char var[100];} DEC;
    struct {Type ty; char var[100]; Exp ex;} DECAT;
    struct {Cmd cmd1; Cmd cmd2;} CMDSEQ;
    struct {Exp expTest; Cmd tTest; Cmd fTest;} BOOLTEST;
    Cmd cm;
  } cmdtype;
};

Exp NumExp(int n);
Exp VarExp(char n[100]);
Exp OpExp(Exp l, BinOp o, Exp r); 
Exp BoolExp(bool bl);
Cmd WhileExp(Exp tst, Cmd d);
Cmd IfExp(Exp tst, Cmd d);
Cmd IfElseExp(Exp tst, Cmd i, Cmd el);
Cmd Attr(char n[100], Exp res);
Cmd Dec(Type t, char n[100]);
Cmd DecAt(Type t, char n[100], Exp res);
Cmd CmdSeq(Cmd c1, Cmd c2);
Cmd BoolTest(Exp tst, Cmd ttst, Cmd ftst);
Cmd SCmd(Cmd c);
Prg PrgEps();
Prg PrgNotEps(Cmd c);
void printTree(Prg p);
void genAddr(Cmd c);

#endif
