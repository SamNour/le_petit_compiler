#ifndef LEXCER_H
#define LEXCER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

enum class TokenType {
  _return,
  EOF_,
  _if,
  _else,
  _while,
  _for,
  _break,
  _continue,
  _int,
  _float,
  _char,
  _string,
  _bool,
  _void,
  _true,
  _false,
  _null,
  _new,
  _delete,
  _this,
  _super,
  _class,
  _interface,
  _extends,
  _implements,
  _public,
  _protected,
  _private,
  _static,
  _final,
  _abstract,
  _native,
  _synchronized,
  _semicolon,
  _comma,
  _dot,
};

const std::map<TokenType, std::string> TokenTypeString = {
    {TokenType::_return, "return"},
    {TokenType::EOF_, "EOF_"},
    {TokenType::_if, "if"},
    {TokenType::_else, "else"},
    {TokenType::_while, "while"},
    {TokenType::_for, "for"},
    {TokenType::_break, "break"},
    {TokenType::_continue, "continue"},
    {TokenType::_int, "int"},
    {TokenType::_float, "float"},
    {TokenType::_char, "char"},
    {TokenType::_string, "string"},
    {TokenType::_bool, "bool"},
    {TokenType::_void, "void"},
    {TokenType::_true, "true"},
    {TokenType::_false, "false"},
    {TokenType::_null, "null"},
    {TokenType::_new, "new"},
    {TokenType::_delete, "delete"},
    {TokenType::_this, "this"},
    {TokenType::_super, "super"},
    {TokenType::_class, "class"},
    {TokenType::_interface, "interface"},
    {TokenType::_extends, "extends"},
    {TokenType::_implements, "implements"},
    {TokenType::_public, "public"},
    {TokenType::_protected, "protected"},
    {TokenType::_private, "private"},
    {TokenType::_static, "static"},
    {TokenType::_final, "final"},
    {TokenType::_abstract, "abstract"},
    {TokenType::_native, "native"},
    {TokenType::_synchronized, "synchronized"},
    {TokenType::_semicolon, "semicolon"},
    {TokenType::_comma, "comma"},
    {TokenType::_dot, "dot"},
};

struct Token {
  TokenType type;
  std::string value;

  std::tuple<std::string, std::string> getToken() {
    return std::make_tuple(TokenTypeString.at(type), value);
  }
};

std::vector<Token> lexical_analysis(std::string &str) {
  std::vector<Token> tokens;
  std::string buff;
  for (int i = 0; i < str.size(); i++) {


    while (isalpha(str[i])) {
      buff.push_back(str[i]);
      i++;
    }
    if (buff == "return") {
      tokens.push_back(Token{TokenType::_return, buff});
      buff.clear();
    } else if (buff == "EOF") {
      tokens.push_back(Token{TokenType::EOF_, buff});
      buff.clear();
    } else if (buff == "if") {
      tokens.push_back(Token{TokenType::_if, buff});
      buff.clear();
    } else if (buff == "else") {
      tokens.push_back(Token{TokenType::_else, buff});
      buff.clear();
    } else if (buff == "while") {
      tokens.push_back(Token{TokenType::_while, buff});
      buff.clear();
    } else if (buff == "for") {
      tokens.push_back(Token{TokenType::_for, buff});
      buff.clear();
    } else if (buff == "break") {
      tokens.push_back(Token{TokenType::_break, buff});
      buff.clear();
    } else if (buff == "continue") {
      tokens.push_back(Token{TokenType::_continue});
      buff.clear();
    } else if (buff == "int") {
      tokens.push_back(Token{TokenType::_int, buff});
      buff.clear();
    } else if (buff == "float") {
      tokens.push_back(Token{TokenType::_float, buff});
      buff.clear();
    } else if (buff == "char") {
      tokens.push_back(Token{TokenType::_char, buff});
      buff.clear();
    } else if (buff == "string") {
      tokens.push_back(Token{TokenType::_string, buff});
      buff.clear();
    } else if (buff == "bool") {
      tokens.push_back(Token{TokenType::_bool, buff});
      buff.clear();
    } else if (buff == "void") {
      tokens.push_back(Token{TokenType::_void, buff});
      buff.clear();
    } else if (buff == "true") {
      tokens.push_back(Token{TokenType::_true, buff});
      buff.clear();
    } else if (buff == "false") {
      tokens.push_back(Token{TokenType::_false, buff});
      buff.clear();
    } else if (buff == "null") {
      tokens.push_back(Token{TokenType::_null, buff});
      buff.clear();
    } else if (buff == "new") {
      tokens.push_back(Token{TokenType::_new, buff});
      buff.clear();
    } else if (buff == "delete") {
      tokens.push_back(Token{TokenType::_delete, buff});
      buff.clear();
    } else if (buff == "this") {
      tokens.push_back(Token{TokenType::_this, buff});
      buff.clear();
    } else if (buff == "super") {
      tokens.push_back(Token{TokenType::_super});
      buff.clear();
    } else if (buff == "class") {
      tokens.push_back(Token{TokenType::_class, buff});
      buff.clear();
    } else if (buff == "extends") {
      tokens.push_back(Token{TokenType::_extends, buff});
      buff.clear();
    } else if (buff == "implements") {
      tokens.push_back(Token{TokenType::_implements, buff});
      buff.clear();
    } else if (buff == "public") {
      tokens.push_back(Token{TokenType::_public, buff});
      buff.clear();
    } else if (buff == "protected") {
      tokens.push_back(Token{TokenType::_protected, buff});
      buff.clear();
    } else if (buff == "private") {
      tokens.push_back(Token{TokenType::_private, buff});
      buff.clear();
    } else if (buff == "static") {
      tokens.push_back(Token{TokenType::_static, buff});
      buff.clear();
    } else if (buff == "final") {
      tokens.push_back(Token{TokenType::_final, buff});
      buff.clear();
    } else if (buff == "abstract") {
      tokens.push_back(Token{TokenType::_abstract, buff});
      buff.clear();
    } else if (buff == "native") {
      tokens.push_back(Token{TokenType::_native, buff});
      buff.clear();
    } else if (buff == "synchronized") {
      tokens.push_back(Token{TokenType::_synchronized, buff});
      buff.clear();
    }

    if (isspace(str[i])) {
      continue;
    }

    while (isdigit(str[i])) {
      buff.push_back(str[i]);
      i++;
    }

    if (buff.size() > 0 && std::all_of(buff.begin(), buff.end(), ::isdigit)) {
      tokens.push_back(Token{TokenType::_int, buff});
      buff.clear();
    }

    if (str[i] == ';') {
      tokens.push_back(Token{TokenType::_semicolon});
      buff.clear();
      i++;
    }
  }
  return tokens;
}
#endif
