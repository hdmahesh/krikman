#include "Value.h"
#include "util.h"
#include <cassert>

//  Value::~Value()
//! @author Sajjan and Mahesh
//! @date   01 Jan, 2015
//! @brief  Destructor
Value::~Value()
{
  FFL;
}

//  Value::setValue(const Value*)
//! @author Sajjan and Mahesh
//! @date   01 Jan, 2015
//! @brief  Set the value from another value
void
Value::setValue(const Value* v)
{
  FFL;
}

//  Value::operator=(const Value&)
//! @author Sajjan and Mahesh
//! @date   01 Jan, 2015
//! @brief  Overload the assignment operator
Value&
Value::operator=(const Value& other)
{
  assert(0);
  FFL;
  return *this;
}
