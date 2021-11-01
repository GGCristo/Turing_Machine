#include "../include/Tape.hpp"
#include <iostream>

Tape::Tape() {
// Invalid
}

Tape::Tape(const std::unordered_set<std::string>& tapeAlphabet, const std::string& blankSymbol) {
  tapeAlphabet_ = tapeAlphabet;
  blankSymbol_ = blankSymbol;
}

void Tape::setString(std::string content) {
  tape_.clear();
  head_ = 0;
  while (!content.empty()) {
    std::string symbol = getSymbol(content);
    tape_.push_back(symbol);
    content.erase(content.begin(), content.begin() + symbol.size());
  }
}

std::string Tape::getHeadValue() const {
  return tape_[head_];
}

void Tape::transit(const std::string& writeSymbol, movements_ movement) {
  tape_[head_] = writeSymbol;
  if (movement == movements_::R) {
    if (head_ == tape_.size() - 1) {
      tape_.push_back(blankSymbol_);
    }
    head_++;
  } else if (movement == movements_::L) {
    if (head_ == 0) {
      tape_.push_front(blankSymbol_);
    } else {
      head_--;
    }
  } else {
    std::cout << "Error\n"; // TODO Improve this
  }
}

std::string Tape::getSymbol(std::string& tape) const {
  std::string symbol;
  for (char c : tape) {
    symbol += c;
    if (tapeAlphabet_.find(symbol) == tapeAlphabet_.end()) {
      symbol.pop_back();
      return symbol;
    }
  }
  return symbol;
}

std::string Tape::getBlankSymbol() const {
  return blankSymbol_;
}

std::ostream& Tape::showTapeAlphabet(std::ostream& os) const {
  os << "\n3. Tape alphabet\n\t";
  const char *padding = "";
  for (const auto& character : tapeAlphabet_) {
    os << padding << character;
    padding = ", ";
  }
  return os;
}

std::ostream& Tape::showTape(std::ostream& os) const {
  const char *padding = "";
  for (const auto& symbol : tape_) {
    os << padding << symbol;
    padding = ", ";
  }
  os << '\n';
  for (int i = 0; i < head_; i++) {
    os << "   ";
  }
  os << "^\n";
  for (int i = 0; i < head_; i++) {
    os << "   ";
  }
  os << "|\n";
  return os;
}
