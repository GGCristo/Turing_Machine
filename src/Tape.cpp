#include "../include/Tape.hpp"

Tape::Tape(std::unordered_set<std::string> tapeAlphabet, std::string blankSymbol) :
  tapeAlphabet_(std::move(tapeAlphabet)), blankSymbol_(std::move(blankSymbol)) {
  head_ = 0;
}

void Tape::set(std::string content) {
  tape_.clear();
  head_ = 0;
  while (!content.empty()) {
    std::string symbol = getSymbol(content);
    tape_.push_back(symbol);
    content.erase(content.begin(), content.begin() + int(symbol.size()));
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
  }
}

/**
 * @brief reformat() reformat the tape to has the following form: 
 * <blankSymbol>[Tape]<blankSymbol> being [Tape] the tape with no blank symbols 
 * at the ends
 */
void Tape::reformat() {
  std::size_t nearestBlankSymbolPos = 0;
  while (tape_[nearestBlankSymbolPos] == blankSymbol_) {
    nearestBlankSymbolPos++;
  }
  nearestBlankSymbolPos--;
  int pop = 0;
  for (; pop < nearestBlankSymbolPos && pop < head_ - 1; pop++) {
    tape_.pop_front();
  }
  head_ -= pop;
  // TODO right side
}

std::string Tape::getSymbol(const std::string& tape) const {
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
  const char *padding = "";
  for (const auto& character : tapeAlphabet_) {
    os << padding << character;
    padding = ", ";
  }
  return os;
}

std::ostream& Tape::showTape(std::ostream& os) {
  reformat();
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
  os << "Head: " << head_ + 1 << " element; Head value: " << tape_[head_] << '\n';
  return os;
}
