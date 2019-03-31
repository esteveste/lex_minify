%option stack

%{
#include "main.c"

char* FILE_TYPE ="dart";
%}

%x M_COM
%%
<M_COM>"/*"     yy_push_state(M_COM);
<M_COM>"*/"     yy_pop_state();
<M_COM>.        ;
<M_COM>\n       ;


@.*         ;
"/*"        yy_push_state(M_COM);
"//".*      ;
^[" "\t]*   ;
", "        yytext[1]=0;ECHO;
\n          ;

.           ECHO;
%%
