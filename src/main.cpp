#include "lexcer.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

std::string tokens_to_x86_asm(std::vector<Token> &tokens) {
  std::stringstream out;
  out << "global _start\n_start:\n";
  for (int i = 0; i < tokens.size(); i++) { // return <int>;
    if (tokens.at(i).type == TokenType::_return) {
      if (i + 1 < tokens.size() && tokens.at(i + 1).type == TokenType::_int) {
        if (i + 2 < tokens.size() &&
            tokens.at(i + 2).type == TokenType::_semicolon) {
          // https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
          out << "    mov rax, 60\n"; // exit code
          out << "    mov rdi, " << tokens.at(i + 1).value
          << "\n";
          out << "    syscall\n";
        }
      }
    }
  }
  return out.str();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <file.69>"
              << "\n";
    return EXIT_FAILURE;
  }

  std::string str;
  { // reading the file
    std::stringstream contents;
    std::ifstream file(argv[1]);
    // std::ifstream file("txt.69");
    contents << file.rdbuf();
    str = contents.str();
  }
  std::vector<Token> tokens{};
  tokens = lexical_analysis(str);
  for (auto token : tokens) {
    std::cout << std::get<0>(token.getToken()) << " : "
              << std::get<1>(token.getToken()) << std::endl;
    // token.toPrint();
  }
  std::string assembly = tokens_to_x86_asm(tokens);
  std::cout << assembly;
  std::ofstream file("output.asm");
  file << assembly;
  file.close();
  return EXIT_SUCCESS;
}