#ifndef COMPILER_PRINCIPLE_PROJECT__LEXICAL_ANALYZER_H
#define COMPILER_PRINCIPLE_PROJECT__LEXICAL_ANALYZER_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <unordered_map>
#include "Token.h"
#include "SymbolType.h"

namespace MyCompiler
{
    Token nextToken(std::istream &stream)
    {
        typedef SymbolType ST;
        enum class State
        {
            START, WORD, NUM, LT, GT, COLON
        };
        static const std::unordered_map<std::string, SymbolType> keywordsMap = {
                {"begin",     ST::BEGIN},
                {"end",       ST::END},
                {"if",        ST::IF},
                {"then",      ST::THEN},
                {"while",     ST::WHILE},
                {"write",     ST::WRITE},
                {"read",      ST::READ},
                {"do",        ST::DO},
                {"call",      ST::CALL},
                {"const",     ST::CONST},
                {"var",       ST::VAR},
                {"procedure", ST::PROC},
                {"odd",       ST::ODD}
        };

        std::string buffer;
        State state = State::START;
        while (stream.good())
        {
            if (state == State::START)
            {
                std::ws(stream);
                char c = stream.peek();
                if (std::isalpha(c))
                {
                    buffer.push_back(stream.get());
                    state = State::WORD;
                }
                else if (std::isdigit(c))
                {
                    buffer.push_back(stream.get());
                    state = State::NUM;
                }
                else
                {
                    switch (c)
                    {
                        case '+':
                            stream.get();
                            return Token(ST::PLUS, "+");
                        case '-':
                            stream.get();
                            return Token(ST::MINUS, "-");
                        case '*':
                            stream.get();
                            return Token(ST::TIMES, "*");
                        case '/':
                            stream.get();
                            return Token(ST::SLASH, "/");
                        case '=':
                            stream.get();
                            return Token(ST::EQL, "=");
                        case '#':
                            stream.get();
                            return Token(ST::NEQ, "#");
                        case '(':
                            stream.get();
                            return Token(ST::LPAREN, "(");
                        case ')':
                            stream.get();
                            return Token(ST::RPAREN, ")");
                        case ',':
                            stream.get();
                            return Token(ST::COMMA, ",");
                        case ';':
                            stream.get();
                            return Token(ST::SEMICOLON, ";");
                        case '.':
                            stream.get();
                            return Token(ST::PERIOD, ".");
                        case ':':
                            stream.get();
                            state = State::COLON;
                            break;
                        case '<':
                            stream.get();
                            state = State::LT;
                            break;
                        case '>':
                            stream.get();
                            state = State::GT;
                            break;
                        default:
                            return Token(ST::NUL);
                    }
                }
            }
            else if (state == State::WORD)
            {
                char c = stream.peek();
                if (std::isalnum(c))
                    buffer.push_back(stream.get());
                else
                    break;
            }
            else if (state == State::NUM)
            {
                char c = stream.peek();
                if (std::isdigit(c))
                    buffer.push_back(stream.get());
                else
                    break;
            }
            else if (state == State::LT)
            {
                char c = stream.peek();
                if (c == '=')
                {
                    stream.get();
                    return Token(ST::LEQ, "<=");
                }
                else
                    break;
            }
            else if (state == State::GT)
            {
                char c = stream.peek();
                if (c == '=')
                {
                    stream.get();
                    return Token(ST::GEQ, ">=");
                }
                else
                    break;
            }
            else // if (state == COLON)
            {
                char c = stream.peek();
                if (c == '=')
                {
                    stream.get();
                    return Token(ST::BECOMES, ":=");
                }
                else
                    break;
            }
        }
        if (state == State::WORD)
        {
            std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
            auto search = keywordsMap.find(buffer);
            if (search != keywordsMap.end())
                return Token(search->second, buffer);
            else
                return Token(ST::IDENT, buffer);
        }
        else if (state == State::NUM)
            return Token(ST::NUMBER, buffer);
        else if (state == State::LT)
            return Token(ST::LSS, "<");
        else if (state == State::GT)
            return Token(ST::GTR, ">");
        else
            return Token(ST::NUL);
    }
}

#endif // COMPILER_PRINCIPLE_PROJECT__LEXICAL_ANALYZER_H