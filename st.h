//Types: int, bool

typedef struct Exp_ *Exp;
typedef enum {Plus, Minus, Times, Div} Binop;

struct Exp_ {
  enum {NumExp, OpExp} kind;
  
  union {
    int num;
    struct {Exp left; Binop op; Exp right;} op;
  } u;
};
