#pragma once

#include <deque>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_set>

#include "../include/Transition.hpp"

class TM {
  private:
  std::unordered_set<std::string> states_;
  std::unordered_set<std::string> initialAlphabet_;
  std::unordered_set<std::string> tapeAlphabet_;
  std::string initialState_;
  std::string blankSymbol_;
  std::unordered_set<std::string> finalStates_;
  TransitionMap transitions_;

  std::deque<std::string> tape_;
  public:
  explicit TM(std::ifstream& inputF);
  std::ostream& show(std::ostream& os);
};

std::string readLine(std::ifstream& inputF, const std::string& whatToExpect);
