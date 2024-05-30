#ifndef PARSE_H
#define PARSE_H

#include "lexcer.h"
#include <iostream>
#include <vector>
struct NodeExpr {
  Token int_lit;
};

struct NodeExit {
  NodeExpr expr;
};

class Parser {
private:
  const std::vector<Token> m_tokens;
  size_t m_curr{};

  std::optional<Token> peek(int ahead = 0) const {
    if (m_curr + ahead >= m_tokens.size())
      return {};
    else
      return m_tokens[m_curr + ahead];
  };

  Token consume() {
    Token token = m_tokens[m_curr];
    m_curr += 1;
    return token;
  }

public:
  explicit Parser(std::vector<Token> &tokens) : m_tokens(tokens) {}

  std::optional<NodeExpr> parse_expr() {
    std::optional<NodeExpr> expr_node;
    if (peek().has_value() && peek().value().type == TokenType::_int) {
      return NodeExpr{.int_lit = consume()};
    } else
      return {};
  }

  std::optional<NodeExit> parse() {
    std::optional<NodeExit> exit_node;
    while (peek().has_value()) {
      if (peek().value().type == TokenType::_exit) {
        consume();
        if (auto node_expr = parse_expr()) {
          exit_node = NodeExit{.expr = node_expr.value()};
        } else {
          throw "Error: Expected an integer literal after exit keyword";
        }
        if (peek().has_value()) {
          if (peek().value().type == TokenType::_semicolon) {
            consume();
          }
        } else {
          std::cerr << "Error: Expected a semicolon after exit statement\n";
          exit(EXIT_FAILURE);
        }
      }
    }
    m_curr = 0;
    return exit_node;
  }
};

#endif