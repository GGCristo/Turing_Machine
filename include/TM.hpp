#pragma once

#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_set>

#include "../include/Transition.hpp"
#include "../include/Tape.hpp"

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
  explicit TM(std::ifstream& inputF);
  bool run(const std::string& tape);
  std::ostream& show(std::ostream& os);
};

std::string readLine(std::ifstream& inputF, const std::string& whatToExpect);
