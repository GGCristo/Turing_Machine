#include "../include/TM.hpp"

#include <iostream>
std::string readLine(std::ifstream& inputF, const std::string& whatToExpect) {
  std::string line;
  bool error;
  do { // TODO explore error
    line.clear();
    error = !std::getline(inputF, line);
  } while (line[0] == '#' && !error); // If line is a comment read next
  if (error) {
    throw whatToExpect + " line is missing or is in a incorrect position in the input file.\n";
  }
  return line;
}

TM::TM(std::ifstream& inputF) {
  std::stringstream statesS(readLine(inputF, "States"));
  std::string word;
  while (statesS >> word) {
    states_.emplace(word);
  }
  std::stringstream initialAlphabetS(readLine(inputF, "Initial alphabet"));
  while (initialAlphabetS >> word) {
    initialAlphabet_.emplace(word);
  }
  std::stringstream tapeAlphabetS(readLine(inputF, "Initial alphabet"));
  std::unordered_set<std::string> tapeAlphabet;
  while (tapeAlphabetS >> word) {
    tapeAlphabet.emplace(word);
  }
  initialState_ = readLine(inputF, "Initial state");
  tape_ = Tape(tapeAlphabet, readLine(inputF, "Blank symbol"));
  std::stringstream finalStatesS(readLine(inputF, "States"));
  while (finalStatesS >> word) {
    finalStates_.emplace(word);
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
      throw movementS + " is not a valid movement\n";
    }
    transitions_.insert(Transition(transitionID++, currentState, newState, 
    readSymbol, writeSymbol, movement));
  }
  state_ = initialState_;
}

bool TM::run(const std::string& tape) {
  tape_.setString(tape);
  Transition* transition = transitions_.find(state_, tape_.getHeadValue());
  while(transition) {
    state_ = transition->getNewState();
    tape_.transit(transition->getWriteSymbol(), transition->getMovement());
    delete transition;
    transition = transitions_.find(state_, tape_.getHeadValue());
  }
  tape_.showTape(std::cout);
  return isInFinalState();
}

bool TM::isInFinalState() const {
  if (finalStates_.find(state_) != finalStates_.end()) {
    return true;
  }
  return false;
}

std::ostream& TM::show(std::ostream& os) {
  os << "Turing Machine (7-tuple)\n";
  const char *padding = "";
  os << "1. States\n\t";
  for (const auto& state : states_) {
    os << padding << state;
    padding = ", ";
  }
  padding = "";
  os << "\n2. Initial tape alphabet\n\t";
  for (const auto& character : initialAlphabet_) {
    os << padding << character;
    padding = ", ";
  }
  tape_.showTapeAlphabet(os);
  os << "\n4. InitialState: " << initialState_;
  os << "\n5. Blank symbole: " << tape_.getBlankSymbol();
  os << "\n6. Transitions\n";
  transitions_.show(os);
  padding = "";
  os << "\n7. Final States\n\t";
  for (const auto& finalState : finalStates_) {
    os << padding << finalState; 
    padding = ", ";
  }
  os << '\n';
  return os;
}
