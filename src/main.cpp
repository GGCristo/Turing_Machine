#include <exception>
#include <iostream>
#include <fstream>

#include "../include/TM.hpp"

void realMain(int argc, char **argv);

int main(int argc, char **argv) {
  try {
    realMain(argc, argv);
  } catch (const std::string& ex){
    std::cerr << ex << '\n';
    return -1;
  } catch(const std::exception &e) {
    std::cerr << e.what() << '\n';
    return -1;
  } catch(...) {
    std::cerr << "An unkown error ocurred\n";
    return -1;
  }
}

void realMain(int argc, char **argv) {
  if (argc < 2 || argc > 3) {
    throw "Incorrect number of flags\n";
  }
  if (argc == 3) {
    if (std::string("--trace") == argv[2]) {
      /* trace = true; */
    } else {
      throw "Incorrect argument: " + std::string(argv[2]) + '\n';
    }
  }
  std::ifstream inputF(argv[1], std::ifstream::in);
  if (inputF.fail()) {
    throw "The file could not be opened: " + std::string(argv[1]) + '\n';
  }
  TM TM_(inputF);
  inputF.close();
  TM_.show(std::cout);
  std::cout << "How many strings are you going to check?\n";
  int numberOfStrings;
  std::string string;
  std::cin >> numberOfStrings;
  for (int i = 0; i < numberOfStrings; i++) {
    std::cout << "Introduce a string: ";
    std::cin >> string;
    if (TM_.run(string)) {
      std::cout << "It belongs to the language\n";
    } else {
      std::cout << "Does not belongs to the language\n";
    }
  }
}
