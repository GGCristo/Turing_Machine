#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>

#include "../include/TM.hpp"

void realMain(int argc, char **argv);
TM loadConfig(std::ifstream& inputF);
std::string readLine(std::ifstream& inputF, const std::string& whatToExpect);

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
  if (argc < 2 || argc > 2) {
    throw std::string("Incorrect number of flags\n");
  }
  std::ifstream inputF(argv[1], std::ifstream::in);
  if (inputF.fail()) {
    throw std::string("The file could not be opened: " + std::string(argv[1]) + '\n');
  }
  TM TM_ = loadConfig(inputF);
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
      std::cout << "Accepted\n";
    } else {
      std::cout << "Rejected\n";
    }
  }
}

TM loadConfig(std::ifstream& inputF) {
  std::unordered_set<std::string> states;
  std::unordered_set<std::string> initialAlphabet;
  std::string initialState;
  std::unordered_set<std::string> finalStates;
  std::unordered_set<std::string> tapeAlphabet;
  std::string blankSymbol;
  TransitionMap transitions;

  std::stringstream statesS(readLine(inputF, "States"));
  std::string word;
  while (statesS >> word) {
    states.emplace(word);
  }
  std::stringstream initialAlphabetS(readLine(inputF, "Initial alphabet"));
  while (initialAlphabetS >> word) {
    initialAlphabet.emplace(word);
  }
  std::stringstream tapeAlphabetS(readLine(inputF, "Initial alphabet"));
  while (tapeAlphabetS >> word) {
    tapeAlphabet.emplace(word);
  }
  initialState = readLine(inputF, "Initial state");
  blankSymbol = readLine(inputF, "Blank symbol");
  std::stringstream finalStatesS(readLine(inputF, "States"));
  while (finalStatesS >> word) {
    finalStates.emplace(word);
  }
  // Transitions
  std::string transitionLineS;
  int transitionID = 1;
  while (std::getline(inputF, transitionLineS)) {
    if (transitionLineS.empty() || transitionLineS[0] == '#') {
      continue;
    }
    std::stringstream transitionLineSS(transitionLineS);
    std::string currentState;
    transitionLineSS >> currentState;
    std::string readSymbol;
    transitionLineSS >> readSymbol;
    std::string newState;
    transitionLineSS >> newState;
    std::string writeSymbol;
    transitionLineSS >> writeSymbol;
    std::string movementS;
    transitionLineSS >> movementS;
    movements_ movement;
    if (movementS == "R") {
      movement = movements_::R;
    } else if (movementS == "L") {
      movement = movements_::L;
    } else {
      throw std::string(movementS + " is not a valid movement\n");
    }
    transitions.insert(Transition(transitionID++, currentState, newState, 
    readSymbol, writeSymbol, movement));
  }
  return TM(sepTuplet{states, initialAlphabet, initialState, finalStates, transitions, tapeAlphabet, blankSymbol});
}

std::string readLine(std::ifstream& inputF, const std::string& whatToExpect) {
  std::string line;
  bool error;
  do {
    line.clear();
    error = !std::getline(inputF, line);
  } while (line[0] == '#' && !error); // If line is a comment read next
  if (error) {
    throw std::string(whatToExpect + " line is missing or is in a incorrect position in the input file.\n");
  }
  return line;
}
