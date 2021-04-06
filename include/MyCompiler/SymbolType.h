#ifndef COMPILER_PRINCIPLE_PROJECT__SYMBOL_TYPE_H
#define COMPILER_PRINCIPLE_PROJECT__SYMBOL_TYPE_H

namespace MyCompiler
{
    enum class SymbolType
    {
        NUL, IDENT, NUMBER,                                // (null), <id>, <number>,
        PLUS, MINUS, TIMES, SLASH,                         // "+", "-", "*", "/",
        EQL, NEQ, LSS, LEQ, GTR, GEQ,                      // "=", "#", "<", "<=", ">", ">=",
        LPAREN, RPAREN, COMMA, SEMICOLON, PERIOD, BECOMES, // "(", ")", ",", ";", ".", ":=",
        BEGIN, END, IF, THEN, WHILE, WRITE, READ, DO,      // (keywords)
        CALL, CONST, VAR, PROC, ODD
    };
}

#endif // COMPILER_PRINCIPLE_PROJECT__SYMBOL_TYPE_H