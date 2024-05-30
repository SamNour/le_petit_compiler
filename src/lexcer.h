#ifndef LEXCER_H
#define LEXCER_H

#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>

enum class TokenType {
  _exit,
  _int,
  _semicolon,
};

const std::map<TokenType, std::string> TokenTypeMap = {
    {TokenType::_exit, "exit"},
    {TokenType::_int, "exit"},
    {TokenType::_semicolon, "semicolon"},
};

struct Token {
  TokenType type;
  std::string value;

  std::tuple<std::string, std::string> getToken() {
    return std::make_tuple(TokenTypeMap.at(type), value);
  }
};
class Lexer {
private:
  const std::string m_src{};
  size_t m_curr{};

  std::optional<char> peek(int ahead = 0) const {
    if (m_curr + ahead >= m_src.size()) {
      return {};
    } else {
      return m_src.at(m_curr + ahead);
    }
  };

  char consume() {
    char curr_char = m_src.at(m_curr);
    m_curr += 1;
    return curr_char;
  }
  void restart_to_start_of_file() { m_curr = 0; }

public:
  explicit Lexer(std::string &src) : m_src(src) {}

  std::vector<Token> lexical_analysis() {
    std::vector<Token> tokens;
    std::string buff;
    while (peek().has_value()) {
      if (std::isalpha(peek().value())) {
        buff.push_back(consume());
        while (peek().has_value() && std::isalnum(peek().value())) {
          buff.push_back(consume());
        }
        if (buff == "exit")
          tokens.push_back(Token{TokenType::_exit, buff});
        else
          throw std::runtime_error("Error: Token not found!");

        buff.clear();
      } else if (isspace(peek().value())) {
        consume();
        buff.clear();
      } else if (isdigit(peek().value())) {
        buff.push_back(consume());
        while (peek().has_value() && isdigit(peek().value())) {
          buff.push_back(consume());
        }
        tokens.push_back(Token{TokenType::_int, buff});
        buff.clear();
      } else if (peek().value() == ';') {
        consume();
        tokens.push_back(Token{TokenType::_semicolon});
      } else
        throw std::runtime_error("Error: Token not found!");
    }
    restart_to_start_of_file();
    return tokens;
  }
};

#endif
