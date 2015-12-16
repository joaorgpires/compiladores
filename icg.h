#ifndef ICG_H
#define ICG_H

typedef struct Tc *Tac;
typedef struct Address *Addr;

typedef enum {TCPlus, TCMinus, TCTimes, TCDiv, TCMod, TCOr, TCAnd, TCEq, TCNeq, TCLt, TCLe, TCGt, TCGe, TCwhileExp, TCifExp, TCifElseExp, TCattr, TCdec, TCcmdSeq, TCboolTest, TCsCmd} tacOp;
typedef enum {TCInt, TCVar, TCBool, TCIntInt, TCIntVar, TCVarVar, TCVarInt, TCIntExp, TCExpExp, TCIntBool, TCBoolBool, TCBoolVar, TCBoolExp, TCVarExp, TCcmd} id;

/*struct Label {
  int cnt;
  char l[20];
  };*/

struct Tc {
  tacOp op;
  id ID;
  char name[20];
  union {
    int l;
    char r[100];
    bool b;
    struct {char name[100]; char e[20];} TCATTR;
    struct {int l; int r;} TCINTINT;
    struct {char l[100]; char r[100];} TCVARVAR;
    struct {char l[100]; int r;} TCVARINT;
    struct {int l; char r[100];} TCINTVAR;
    struct {int l; char r[20];} TCINTEXP;
    struct {char l[20]; char r[20];} TCEXPEXP;
    struct {int l; bool r;} TCINTBOOL;
    struct {bool l; bool r;} TCBOOLBOOL;
    struct {bool l; char r[100];} TCBOOLVAR;
    struct {bool l; char r[20];} TCBOOLEXP;
    struct {char l[100]; char r[20];} TCVAREXP;
  } tactype;
};

#endif
