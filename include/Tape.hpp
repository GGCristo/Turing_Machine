#pragma once

#include <deque>
#include <string>
#include <unordered_set>
#include <ostream>
#include <sstream>

#include "Transition.hpp"

class Tape {
  private:
  std::unordered_set<std::string> tapeAlphabet_;
  std::deque<std::string> tape_;
  int head_;
  std::string blankSymbol_;

  std::string getSymbol(std::string& tape) const;
  public:
  Tape();
  Tape(const std::unordered_set<std::string>& tapeAlphabetS, const std::string& blankSymbol);
  void setString(std::string content);
  void transit(const std::string& writeSymbol, movements_ movement);
  std::string getHeadValue() const;
  std::string getBlankSymbol() const;
  std::ostream& showTapeAlphabet(std::ostream& os) const;
  std::ostream& showTape(std::ostream& os) const;
};
