#pragma once

#include <ostream>
#include <string>
#include <unordered_set>

#include "../include/Transition.hpp"
#include "../include/Tape.hpp"

struct sepTuplet {
  std::unordered_set<std::string> states_;
  std::unordered_set<std::string> initialAlphabet_;
  std::string initialState_;
  std::unordered_set<std::string> finalStates_;
  TransitionMap transitions_;
  std::unordered_set<std::string> tapeAlphabet_;
  std::string blankSymbol_;
};

class TM {
  private:
  std::unordered_set<std::string> states_;
  std::unordered_set<std::string> initialAlphabet_;
  std::string initialState_;
  std::unordered_set<std::string> finalStates_;
  TransitionMap transitions_;

  Tape tape_;
  std::string state_;
  std::string getSymbol(const std::string& tape) const;

  public:
  explicit TM(const sepTuplet& seventhTuple);
  bool run(const std::string& tape);
  std::ostream& show(std::ostream& os);
};
