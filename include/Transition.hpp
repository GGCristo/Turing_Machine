#pragma once
#include <cwchar>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <ostream>
#include <queue>

enum class movements_{L, R};
//{oldstate, currentSymbol};
typedef std::tuple<std::string, std::string> transitInput;

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
  std::string getOldState() const;
  std::string getReadSymbol() const;
  std::ostream& show(std::ostream& os) const;
};

class TransitionMap {
  private:
  std::map<transitInput, Transition> transitionMap_;
  public:
  void insert(const Transition& Transition);
  std::queue<Transition> find(const std::string& state, const std::string& readSymbol) const;
  std::ostream& show(std::ostream& os) const;
};
