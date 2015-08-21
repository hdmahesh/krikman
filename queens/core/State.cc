#include "State.h"
#include "Value.h"
#include "util.h"
#include <iostream>
#include <cassert>

//  State::State(Value*)
//! @author Sajjan and Mahesh
//! @date   01 Jan, 2015
//! @brief  Non-default Constructor
State::State(Value *val)
  :_value(val)
{
}

//  State::State(const State&)
//! @author Sajjan and Mahesh
//! @date   01 Jan, 2015
//! @brief  Copy Constructor, for deep copy
State::State(const State& other)
{
  FFL;
  _value = NULL;
  if (other._value) {
    _value = other._value->clone();
  }
}

//  State::~State()
//! @author Sajjan and Mahesh
//! @date   01 Jan, 2015
//! @brief  Destructor, responsible for cleaning up its Value
State::~State()
{
  FFL;
  if (_value) delete _value;
  _value = NULL;
}

//  State::copyState(const State*)
//! @author Sajjan and Mahesh
//! @date   01 Jan, 2015
//! @brief  API to copy contents of one State to another
void
State::copyState(const State* other)
{
  setValue(other->getValue());
}

//  State::getValue()
//! @author Sajjan and Mahesh
//! @date   01 Jan, 2015
//! @brief  Get the value of the State
const Value*
State::getValue() const
{
  return _value;
}

//  State::setValue(const Value*)
//! @author Sajjan and Mahesh
//! @date   01 Jan, 2015
//! @brief  Copy the State value from the given value, therefore both must exist
void
State::setValue(const Value *v) {
  assert(v);
  assert(_value);
  if (_value != NULL) {
    _value->setValue(v);
  }
}
