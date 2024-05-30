#ifndef PARSE_H
#define PARSE_H

#include "lexcer.h"
#include <iostream>
#include <variant>
#include <vector>

struct NodeExprIntLit {
  Token int_lit;
};

struct NodeExprIdent {
  Token ident;
};

struct NodeStmtExit {
  NodeExpr expr;
};

struct NodeStmtLet {
  Token ident;
  NodeExpr expr;
};

struct NodeStmt {
  std::variant<NodeStmtExit, NodeStmtLet> var;
};

struct NodeExpr {
  std::variant<NodeExprIntLit, NodeExprIdent> var;
};

struct NodeProgram {
  std::vector<NodeStmt> stmts{};
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

  std::optional<NodeProgram> parse_prog() {
    NodeProgram prog;
    while (peek().has_value()) {
      if (const auto &stmt = parse_stmt()) {
        prog.stmts.push_back(stmt.value());
      } else {
        std::cerr << "Invalid Statement\n";
        exit(EXIT_FAILURE);
      }
    }
  }

  std::optional<NodeExpr> parse_expr() {
    if (peek().has_value()) {
      if (peek().value().type == TokenType::_int)
        return NodeExpr{
            .var = NodeExprIntLit{.int_lit = consume()}}; // consume int
    } else if (peek().value().type == TokenType::_identifier) {
      return NodeExpr{.var = NodeExprIdent{.ident = consume()}};
    }
    return {};
  }

  std::optional<NodeStmt> parse_stmt() {
    NodeStmtExit node_exit;
    while (peek().has_value()) {
      // case 1: exit statement
      if (peek().value().type == TokenType::_exit) {
        consume(); // consume exit
        if (peek().has_value() &&
            peek().value().type == TokenType::_open_paranthesis) {
          consume(); // consume (
        } else {
          std::cerr << "Error: Expected an opening paranthesis after exit\n";
          exit(EXIT_FAILURE);
        }

        if (auto node_expr = parse_expr()) {
          NodeStmtExit node_exit = NodeStmtExit{.expr = node_expr.value()};
        } else {
          std::cerr << "Error: Invalid expression in exit statement\n";
          exit(EXIT_FAILURE);
        }
        if (peek().has_value() &&
            peek().value().type == TokenType::_closed_paranthesis) {
          consume();
        } else {
          std::cerr << "Error: Expected a closing paranthesis\n";
          exit(EXIT_FAILURE);
        }
        if (peek().has_value()) {
          if (peek().value().type == TokenType::_semicolon) {
            consume();
          }
        } else {
          std::cerr << "Error: Expected a semicolon after exit statement\n";
          exit(EXIT_FAILURE);
        } // case 2: Identifier statement
        return NodeStmt{.var = node_exit};
      } else if (peek().value().type == TokenType::_let &&
                 peek(1).value().type == TokenType::_identifier &&
                 peek(2).value().type == TokenType::_ass) {
        consume(); // let

        auto stmt_let = NodeStmtLet{.ident = consume()};
        consume(); // =
        if (auto node_expr = parse_expr()) {
          stmt_let.expr = node_expr.value();
        } else {
          std::cerr << "Error: Invalid expression for let statement\n";
          exit(EXIT_FAILURE);
        }
        if (peek().has_value() &&
            peek().value().type == TokenType::_semicolon) {
          consume();
        } else {
          std::cerr << "Error: Expected a semicolon after exit statement\n";
          exit(EXIT_FAILURE);
        }
      }
      return NodeStmt{.var = node_exit};
    }
    return {};
  }
};

#endif