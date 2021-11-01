#pragma once
#include <cwchar>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <ostream>

enum class movements_{L, R};

//{oldstate, currentSymbol};
typedef std::pair<std::string, std::string> transitInput;

// {newState, symbolToConsume, movement}
/* typedef std::tuple<std::string, std::string, movements_::{L, R}> transitOutput; */

class Transition {
  private:
  size_t id_;
  movements_ movement_;
  std::string initialState_;
  std::string readSymbol_;
  std::string resultingState_;
  std::string writeSymbol_;
  public:
  Transition(size_t ID, std::string initialState, std::string resultingState,
  std::string readSymbol, std::string writeSymbol, movements_ movement);
  Transition(const Transition& other);
  std::string getOldState() const;
  std::string getNewState() const;
  std::string getReadSymbol() const;
  std::string getWriteSymbol() const;
  movements_ getMovement() const;
  std::ostream& show(std::ostream& os) const;
};

class TransitionMap {
  private:
  std::map<transitInput, Transition> transitionMap_;
  public:
  void insert(const Transition& Transition);
  Transition* find(const std::string& state, const std::string& readSymbol) const;
  std::ostream& show(std::ostream& os) const;
};
