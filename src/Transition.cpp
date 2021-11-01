#include "../include/Transition.hpp"

#include <iostream>
Transition::Transition(size_t id, std::string initialState, std::string resultingState,
std::string readSymbol, std::string writeSymbol, movements_ movement) :
initialState_(std::move(initialState)), resultingState_(std::move(resultingState)),
readSymbol_(std::move(readSymbol)), writeSymbol_(std::move(writeSymbol)) {
  id_ = id;
  movement_ = movement;
}

Transition::Transition(const Transition& other) {
  *this = other;
}

std::string Transition::getOldState() const {
  return initialState_;
}

std::string Transition::getNewState() const { // TODO change name
  return resultingState_;
}

std::string Transition::getWriteSymbol() const { // TODO change name
  return writeSymbol_;
}

std::string Transition::getReadSymbol() const {
  return readSymbol_;
}

movements_ Transition::getMovement() const {
  return movement_;
}

std::ostream& Transition::show(std::ostream& os) const {
  os << '\t' << id_ << ". { " << initialState_ << ", " << readSymbol_ << ", " << resultingState_ << ", " << writeSymbol_ << ", ";
  if (movement_ == movements_::R) {
    os << "R";
  } else {
    os << "L";
  }
  os << " }\n";
  return os;
}

////////////////////////////////////////////////////////////////////////////

void TransitionMap::insert(const Transition& transition) {
  transitionMap_.emplace(std::make_pair(transition.getOldState(),
  transition.getReadSymbol()), transition);
}

// You should free Transition* if is not null
Transition* TransitionMap::find(const std::string& state,
const std::string& readSymbol) const {
  auto transitionIt = transitionMap_.find(std::make_pair(state, readSymbol));
  if (transitionIt != transitionMap_.end()) {
      return new Transition(transitionIt->second);
  }
  return nullptr;
}

std::ostream& TransitionMap::show(std::ostream& os) const {
  for (const auto& it : transitionMap_) {
    it.second.show(os);
  }
  return os;
}
