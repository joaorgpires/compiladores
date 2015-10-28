/* parser to be done here */

%{

%}

  /* Something missing */

%token TokenInt

%%
exp :    TokenInt             { $$ = $1;       }
      |  exp '+' exp          {                }
      |  exp '-' exp          {                }
      |  exp '*' exp          {                }
      |  exp '/' exp          {                }
