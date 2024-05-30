#ifndef GENERATE_CODE_H
#define GENERATE_CODE_H

#include "parser.h"
#include <iostream>
#include <sstream>

class Generator {
private:
  NodeExit m_root;

public:
  Generator(NodeExit &exit)
      : m_root(exit){

        };

  std::string generate() {
    std::stringstream out;
    out << "global _start\n_start:\n";
    out << "    mov rax, 60\n"; // exit code
    out << "    mov rdi, " << m_root.expr.int_lit.value << "\n";
    out << "    syscall\n";

    return out.str();
  }
};
#endif