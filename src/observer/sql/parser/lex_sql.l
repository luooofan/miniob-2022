%{
#include<string.h>
#include<stdio.h>

struct ParserContext;

#include "yacc_sql.tab.h"
extern int atoi();
extern double atof();

#if YYDEBUG > 0
#define debug_printf  printf
#else
#define debug_printf(...)
#endif // YYDEBUG

#define RETURN_TOKEN(token) debug_printf("%s\n",#token);return token
%}

/* Prevent the need for linking with -lfl */
%option noyywrap
%option bison-bridge
%option reentrant

WHITE_SAPCE      [\ \t\b\f]
DIGIT            [0-9]+

ID               [A-Za-z_]+[A-Za-z0-9_]*
DOT              \.
QUOTE            \'
DOUBLE_QUOTE     \"
%x STR

%%

{WHITE_SAPCE}                                        // ignore whitespace
\n                                                   ;
"-"                                                  RETURN_TOKEN(SUB);
{DIGIT}+                                        yylval->number=atoi(yytext); RETURN_TOKEN(NUMBER);
{DIGIT}+{DOT}{DIGIT}+                           yylval->floats=(float)(atof(yytext)); RETURN_TOKEN(FLOAT);

";"                                                  RETURN_TOKEN(SEMICOLON);
{DOT}                                                RETURN_TOKEN(DOT);
"*"                                                  RETURN_TOKEN(STAR);
[Ee][Xx][Ii][Tt]                                     RETURN_TOKEN(EXIT);
[Hh][Ee][Ll][Pp]                                     RETURN_TOKEN(HELP);
[Dd][Ee][Ss][Cc]                                     RETURN_TOKEN(DESC);
[Aa][Ss]                                             RETURN_TOKEN(AS);
[Aa][Ss][Cc]                                         RETURN_TOKEN(ASC);
[Cc][Rr][Ee][Aa][Tt][Ee]                             RETURN_TOKEN(CREATE);
[Dd][Rr][Oo][Pp]                                     RETURN_TOKEN(DROP);
[Tt][Aa][Bb][Ll][Ee]                                 RETURN_TOKEN(TABLE);
[Tt][Aa][Bb][Ll][Ee][Ss]                             RETURN_TOKEN(TABLES);
[Ii][Nn][Dd][Ee][Xx]                                 RETURN_TOKEN(INDEX);
[Ii][Nn][Nn][Ee][Rr]                                 RETURN_TOKEN(INNER);
[Jj][Oo][Ii][Nn]                                     RETURN_TOKEN(JOIN);
[Oo][Nn]                                             RETURN_TOKEN(ON);
[Ss][Hh][Oo][Ww]                                     RETURN_TOKEN(SHOW);
[Ss][Yy][Nn][Cc]                                     RETURN_TOKEN(SYNC);
[Ss][Ee][Ll][Ee][Cc][Tt]                             RETURN_TOKEN(SELECT);
[Ff][Rr][Oo][Mm]                                     RETURN_TOKEN(FROM);
[Ww][Hh][Ee][Rr][Ee]                                 RETURN_TOKEN(WHERE);
[Aa][Nn][Dd]                                         RETURN_TOKEN(AND);
[Oo][Rr]                                             RETURN_TOKEN(OR);
[Ii][Nn][Ss][Ee][rR][tT]                             RETURN_TOKEN(INSERT);
[Ii][Nn][Tt][Oo]                                     RETURN_TOKEN(INTO);
[Vv][Aa][Ll][Uu][Ee][Ss]                             RETURN_TOKEN(VALUES);
[Dd][Ee][Ll][Ee][Tt][Ee]                             RETURN_TOKEN(DELETE);
[Uu][Pp][Dd][Aa][Tt][Ee]                             RETURN_TOKEN(UPDATE);
[Ss][Ee][Tt]                                         RETURN_TOKEN(SET);
[Bb][Ee][Gg][Ii][Nn]                                 RETURN_TOKEN(TRX_BEGIN);
[Cc][Oo][Mm][Mm][Ii][Tt]                             RETURN_TOKEN(TRX_COMMIT);
[Rr][Oo][Ll][Ll][Bb][Aa][Cc][Kk]                     RETURN_TOKEN(TRX_ROLLBACK);
[Ii][Nn][Tt]                                         RETURN_TOKEN(INT_T);
[Cc][Hh][Aa][Rr]                                     RETURN_TOKEN(STRING_T);
[Dd][Aa][Tt][Ee]                                     RETURN_TOKEN(DATE_T);
[Ff][Ll][Oo][Aa][Tt]                                 RETURN_TOKEN(FLOAT_T);
[Ll][Oo][Aa][Dd]                                     RETURN_TOKEN(LOAD);
[Dd][Aa][Tt][Aa]                                     RETURN_TOKEN(DATA);
[Ii][Nn][Ff][Ii][Ll][Ee]                             RETURN_TOKEN(INFILE);
[Nn][Oo][Tt]                                         RETURN_TOKEN(NOT);
[Ll][Ii][Kk][Ee]                                     RETURN_TOKEN(LIKE); 
[Uu][Nn][Ii][Qq][Uu][Ee]                             RETURN_TOKEN(UNIQUE);
[Oo][Rr][Dd][Ee][Rr]                                 RETURN_TOKEN(ORDER);
[Gg][Rr][Oo][Uu][Pp]                                 RETURN_TOKEN(GROUP);
[Bb][Yy]                                             RETURN_TOKEN(BY);
[Ii][Nn]                                             RETURN_TOKEN(IN);
[Ee][Xx][Ii][Ss][Tt][Ss]                             RETURN_TOKEN(EXISTS);
[Hh][Aa][Vv][Ii][Nn][Gg]                             RETURN_TOKEN(HAVING);
[Mm][Aa][Xx]                                         RETURN_TOKEN(AGGR_MAX);
[Mm][Ii][Nn]                                         RETURN_TOKEN(AGGR_MIN);
[Ss][Uu][Mm]                                         RETURN_TOKEN(AGGR_SUM);
[Aa][Vv][Gg]                                         RETURN_TOKEN(AGGR_AVG);
[Cc][Oo][Uu][Nn][Tt]                                 RETURN_TOKEN(AGGR_COUNT);
[Ll][Ee][Nn][Gg][Tt][Hh]                             RETURN_TOKEN(LENGTH);
[Rr][Oo][Uu][Nn][Dd]                                 RETURN_TOKEN(ROUND);
[Dd][Aa][Tt][Ee][_][Ff][Oo][Rr][Mm][Aa][Tt]          RETURN_TOKEN(DATE_FORMAT);
[Ii][Ss]                                             RETURN_TOKEN(IS);
[Nn][Uu][Ll][Ll]                                     RETURN_TOKEN(NULL_VALUE);
[Nn][Uu][Ll][Ll][Aa][Bb][Ll][Ee]                     RETURN_TOKEN(NULLABLE);
[Tt][Ee][Xx][Tt]                                     RETURN_TOKEN(TEXT);
{ID}                                                 yylval->string=strdup(yytext); RETURN_TOKEN(ID);
"("                                                  RETURN_TOKEN(LBRACE);
")"                                                  RETURN_TOKEN(RBRACE);

","                                                  RETURN_TOKEN(COMMA);
"="                                                  RETURN_TOKEN(EQ);
"<="                                                 RETURN_TOKEN(LE);
"<>"                                                 RETURN_TOKEN(NE);
"!="                                                 RETURN_TOKEN(NE);
"<"                                                  RETURN_TOKEN(LT);
">="                                                 RETURN_TOKEN(GE);
">"                                                  RETURN_TOKEN(GT);
"+"                                                  RETURN_TOKEN(ADD);

"/"                                                  RETURN_TOKEN(DIV);

{QUOTE}([0-9]{4})\-([0-9]|[0-9]{2})\-([0-9]|[0-9]{2}){QUOTE}     yylval->string=strdup(yytext); RETURN_TOKEN(DATE_STR);
{QUOTE}(\\\47|[\40\42A-Za-z0-9_/\.\-\%\,])*{QUOTE}            yylval->string=strdup(yytext); RETURN_TOKEN(SSS);
{DOUBLE_QUOTE}(\\\42|[\40\47A-Za-z0-9_/\.\-\%\,])*{DOUBLE_QUOTE}            yylval->string=strdup(yytext); RETURN_TOKEN(SSS);

.                                                    printf("Unknown character [%c]\n",yytext[0]); return yytext[0];
%%

void scan_string(const char *str, yyscan_t scanner) {
  yy_switch_to_buffer(yy_scan_string(str, scanner), scanner);
}
