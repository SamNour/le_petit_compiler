#include "lexcer.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

std::string tokens_to_x86_asm(std::vector<Token>& tokens){
    std::string res;
    for (int i = 0; i < tokens.size(); i++){
        if (tokens[i].type == TokenType::_return){
            std::cout << "Correct\n";
        }
    }
    return NULL;
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
  return EXIT_SUCCESS;
}