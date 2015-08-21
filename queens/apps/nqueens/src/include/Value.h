#ifndef _VALUE_H_
#define _VALUE_H_

class Value
{
public:
  // destructor
  virtual ~Value();

  // set the Value from the given Value
  virtual void setValue(const Value* v);

  // overload =
  virtual Value& operator=(const Value& other);

  // clone itself
  virtual Value* clone() = 0;

  // we should be able to compare two values
  virtual int compare(const Value* other) const = 0;

  // to show the contents of Value
  virtual void show() const = 0;
};

#endif
