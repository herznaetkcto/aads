#include <iostream>
#include <functional>
#include "BinarySearchTree.hpp"
#include "CommandProcessor.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Wrong input\n";
    return 1;
  }

  bsTree< std::string, bsTree< long long, std::string > > dictionaries;
  bsTree< std::string, std::function< void(bsTree< std::string, bsTree< long long, std::string> > &) > > cmds;

  cmds.insert(std::make_pair("print", handlePrint));
  cmds.insert(std::make_pair("complement", handleComplement));
  cmds.insert(std::make_pair("intersect", handleIntersect));
  cmds.insert(std::make_pair("union", handleUnion));

  auto invalidCommandWarning = std::bind(displayWarning, std::ref(std::cerr), "<INVALID COMMAND>\n");

  try {
    loadTreeFromFile(argv[1], dictionaries);
  } catch (const std::exception &e) {
    std::cerr << "Error loading file: " << e.what() << "\n";
    return 1;
  }

  while (!std::cin.eof()) {
    std::string command;
    std::cin >> command;

    auto commandIter = commands.find(command);
    if (commandIter != cmds.end() && !command.empty()) {
      commandIter->second(dictionaries);
    }
    else if (!command.empty()) {
      invalidCommandWarning();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
