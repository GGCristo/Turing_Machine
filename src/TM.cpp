#include "../include/TM.hpp"

TM::TM(const sepTuplet& tuple) : 
states_(tuple.states_), 
initialAlphabet_(tuple.initialAlphabet_),
initialState_(tuple.initialState_), 
finalStates_(tuple.finalStates_), 
transitions_(tuple.transitions_),
tape_(tuple.tapeAlphabet_, tuple.blankSymbol_) {
  state_ = initialState_;
  // TODO checks
}

bool TM::run(const std::string& tape) {
  tape_.set(tape);
  Transition* transition = transitions_.find(state_, tape_.getHeadValue());
  while(transition) {
    state_ = transition->getNewState();
    tape_.transit(transition->getWriteSymbol(), transition->getMovement());
    delete transition;
    transition = transitions_.find(state_, tape_.getHeadValue());
  }
  tape_.showTape(std::cout);
  return finalStates_.contains(state_);
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
  os << "\n3. Tape alphabet\n\t";
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
