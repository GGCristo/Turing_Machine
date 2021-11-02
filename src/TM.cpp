#include "../include/TM.hpp"
#include <string>

TM::TM(const sepTuplet& tuple) : 
states_(tuple.states_), 
initialAlphabet_(tuple.initialAlphabet_),
initialState_(tuple.initialState_), 
finalStates_(tuple.finalStates_), 
transitions_(tuple.transitions_),
tape_(tuple.tapeAlphabet_, tuple.blankSymbol_) {
  // Checks tape alphabet
  for (const std::string& symbol : initialAlphabet_) {
    if (!tape_.getAlphabet_().contains(symbol)) {
      throw std::string(symbol + " doesn't belong to this automaton.\n");
    }
  }
  // Checks initial state
  if (!states_.contains(initialState_)) {
    throw std::string(initialState_ + " don't belong to the states set");
  }
  // Checks blank symbol
  if (!tape_.getAlphabet_().contains(tape_.getBlankSymbol()) ||
    initialAlphabet_.contains(tape_.getBlankSymbol())) {
    throw std::string("Blank symbol is not in the correct set");
  }
  // Check final states
  for (const auto& finalState : finalStates_) {
    if (!finalStates_.contains(finalState)) {
      throw std::string(finalState + " is not a final State");
    }
  }
  // Check Transitions
  for (const auto& transition : transitions_.getTransitions()) {
    if (!states_.contains(transition.second.getOldState())) {
        throw std::string("Old state: " + transition.second.getOldState() + 
        " from transition number " + std::to_string(transition.second.getID()) + 
        " is not a valid state");
    }
    if (!states_.contains(transition.second.getNewState())) {
        throw std::string("New state: " + transition.second.getNewState() + 
        " from transition number " + std::to_string(transition.second.getID()) + 
        " is not a valid state");
    }
    if (!tape_.getAlphabet_().contains(transition.second.getReadSymbol())) {
        throw std::string("Read symbol" + transition.second.getReadSymbol() + 
        " from transition number " + std::to_string(transition.second.getID()) + 
        " is not a valid symbol");
    }
    if (!tape_.getAlphabet_().contains(transition.second.getWriteSymbol())) {
        throw std::string("Write symbol" + transition.second.getWriteSymbol() + 
        " from transition number " + std::to_string(transition.second.getID()) + 
        " is not a valid symbol");
    }
  }
  state_ = initialState_;
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
