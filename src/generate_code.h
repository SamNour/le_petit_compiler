#ifndef GENERATE_CODE_H
#define GENERATE_CODE_H

#include "parser.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
class Generator {
private:
  struct Var {
    size_t stack_loc;
  };
  NodeProgram m_prog;
  std::stringstream m_out;
  size_t m_stack_index{};
  std::unordered_map<std::string, Var> hm_vars{};

  void push(const std::string &reg) {
    m_out << "    push " << reg << "\n";
    m_stack_index++;
  }

  void pop(const std::string &reg) {
    m_out << "    pop " << reg << "\n";
    m_stack_index--;
  }

public:
  Generator(NodeProgram &prog) : m_prog(prog){};

  void gen_expr(const NodeExpr &expr) {

    if (std::holds_alternative<NodeExprIntLit>(expr.var)) {
      const NodeExprIntLit &int_lit_node = std::get<NodeExprIntLit>(expr.var);
      Token int_lit = int_lit_node.int_lit;
      m_out << "    mov rax, " << int_lit.value << "\n";
      push("rax");
    } else if (std::holds_alternative<NodeExprIdent>(expr.var)) {
      auto &ident = std::get<NodeExprIdent>(expr.var).ident.value;
      if (!hm_vars.contains(ident)) {
        std::cerr << "Use of Undeclared identifier: " << ident << "\n";
        exit(EXIT_FAILURE);
      }
      const auto &hm_value = hm_vars.at(ident);
      std::stringstream offset;
      offset << "QWORD [rsp + " << (m_stack_index - hm_value.stack_loc - 1) * 8
             << "]\n";
      push(offset.str());
    }
  }

  void gen_stmt(const NodeStmt &stmt) {
    if (std::holds_alternative<NodeStmtExit>(stmt.var)) {
      const NodeStmtExit &stmt_exit = std::get<NodeStmtExit>(stmt.var);
      gen_expr(stmt_exit.expr);

      m_out << "    mov rax, 60\n"; // exit code
      pop("rdi");
      m_out << "    syscall\n";
    } else if (std::holds_alternative<NodeStmtLet>(stmt.var)) {
      // case 1: Identifier is already in use!
      if (hm_vars.contains(std::get<NodeStmtLet>(stmt.var).ident.value)) {
        std::cerr << "Identifier :"
                  << std::get<NodeStmtLet>(stmt.var).ident.value
                  << " is already used!\n";
        exit(EXIT_FAILURE);
      } else { // identifier was not used before!

        hm_vars.insert({std::get<NodeStmtLet>(stmt.var).ident.value,
                        Var{.stack_loc = m_stack_index}});

        gen_expr(std::get<NodeStmtLet>(stmt.var).expr);
      }
    } else {
      // Handle other types
    }
  }

  std::string generate_prog() {
    m_out << "global _start\n_start:\n";
    for (const NodeStmt &stmt : m_prog.stmts) {
      gen_stmt(stmt);
      std::cout << m_out.str() << "\n";
    }
    m_out << "    mov rax, 60\n"; // exit code
    m_out << "    mov rdi, 0\n";
    m_out << "    syscall\n";

    return m_out.str();
  }
};
#endif