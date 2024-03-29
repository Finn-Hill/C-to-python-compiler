%{
    #include <string>
    #include <iostream>
    #include <fstream>
    #include "FALexer.hh"

    #undef YY_DECL
    #define YY_DECL int FALexer::yylex(void)

    #define YY_USER_ACTION process(yytext);

    #define yyterminate() return 0
    #define YY_NO_UNISTD_H

    std::string remove_EOLNs(std::string txt) {
        int ending = txt.length();
        while (txt[ending-1] == '\r' || txt[ending-1] == '\n') {
            ending--;
        }
        return txt.substr(0,ending);
    }

    void FALexer::process(std::string txt) {
        current = current + txt;
    }

    void FALexer::report(bool accepted) {
        std::cout << remove_EOLNs(current) << " ";
        if (accepted) {
            std::cout << " YES";
        } else {
            std::cout << " NO";
        }
        std::cout << std::endl;
        current = "";
        BEGIN(0);
    }

%}

%option debug
%option nodefault
%option noyywrap
%option yyclass="Lexer"
%option c++

%s SAWA SAWABODD SAWAODD 

EOLN    \r\n|\n\r|\n|\r

%%

%{

%}

<INITIAL>[bc]     { BEGIN(INITIAL); }
<INITIAL>a     { BEGIN(SAWA); }
<SAWA>b        { BEGIN(SAWABODD); }
<SAWA>c        { BEGIN(INITIAL); }
<SAWA>a        { BEGIN(SAWA); }
<SAWABODD>b        { BEGIN(SAWABODD); }
<SAWABODD>c        { BEGIN(SAWABODD); }
<SAWABODD>a        { BEGIN(SAWAODD); }
<SAWAODD>a         { BEGIN(SAWAODD); }
<SAWAODD>c         { BEGIN(SAWABODD); }
<SAWAODD>b         { BEGIN(INITIAL); }
<SAWAODD>{EOLN} { report(false); }
<SAWABODD>{EOLN}    { report(false); }
<*>{EOLN}      { report(true); }

<<EOF>> {
    return 0;
}

. {
    std::string txt { yytext };
    std::cerr << "Unexpected \"" << txt << "\" in input." << std::endl;
    return -1;
}

%%

int main(int argc, char** argv) {
    std::string src_name { argv[1] };
    std::ifstream ins { src_name };
    FALexer lexer { &ins };
    return lexer.yylex();
}
