#ifndef GENERATE_CODE_H
#define GENERATE_CODE_H

#include "parser.h"
#include <iostream>
#include <sstream>

class Generator {
private:
  NodeProgram m_prog;

public:
  Generator(NodeProgram &exit) : m_prog(exit){};

  std::string generate_prog() {
    std::stringstream out;
    out << "global _start\n_start:\n";
    for (const NodeStmt &stmt : m_prog.stmts) {
      out << gen_stmt(stmt);
    }
    out << "    mov rax, 60\n"; // exit code
    out << "    mov rdi, 0";
    out << "    syscall\n";

    return out.str();
  }
};
#endif