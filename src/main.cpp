#include "generate_code.h"
#include "lexcer.h"
#include "parser.h"
#include <algorithm>
#include <fstream>
#include <iostream>

#include <string>
#include <string_view>
#include <vector>

int main(int argc, char **argv) {
  // if (argc < 2) {
  //   std::cerr << "Usage: " << argv[0] << " <file.69>"
  //             << "\n";
  //   return EXIT_FAILURE;
  // }

  std::string str;
  { // reading the file
    std::stringstream contents;
    // std::ifstream file(argv[1]);
    std::ifstream file("txt.69");
    contents << file.rdbuf();
    str = contents.str();
  }

  Lexer lex(str);

  std::vector<Token> tokens = lex.lexical_analysis();

  Parser parser(tokens);
  std::optional<NodeExit> tree = (parser.parse());
  if (!tree.has_value()) {
    std::cerr << "Tree does not exist! Are you in debug-mode?\n";
  } else {
    NodeExit exit_node = tree.value();
    Generator gen(exit_node);

    std::string assembly = gen.generate();

    /*
      Debugging
    */
    std::cout << assembly;

    std::ofstream file("output.asm");
    file << assembly;
    file.close();

    system("nasm -f elf64 output.asm -o output.o && ld output.o -o "
           "output");

    // for (auto token : tokens) {
    //   std::cout << "Tokens:\n";
    //   std::cout << std::get<0>(token.getToken()) << " : "
    //             << std::get<1>(token.getToken()) << std::endl;
    // }
    // std::cout << "-----------------\n\n";
  }

  return EXIT_SUCCESS;
}