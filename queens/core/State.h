#ifndef _STATE_H_
#define _STATE_H_

#include <iostream>

// forward declaration
class Value;

class State
{
public:
  // non-default constructor
  State(Value* val);

  // copy constructor
  State(const State& other);

  // destructor
  virtual ~State() = 0;

  // copy the one state to another
  virtual void copyState(const State* other);

  // get the value of the state
  const Value* getValue() const;


  // evaluate the value of the state
  virtual void evaluateValue() = 0;

  // to display value of the state
  virtual void show(const std::string& msg = "") const = 0;
  
  // gets the neighbors of the current state one-by-one upon successive calls
  virtual State* getNextNeighbor() = 0;

protected:
  // set the value of the state
  void setValue(const Value* v);

  // Used to updated the value
  // TODO: Find a better way
  Value* accessValue() {return _value;}

private:
  // every state has a value associated with it
  Value *_value;
};

#endif
