#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "include/State.h"
#include "include/Value.h"
#include "include/HillClimb.h"
#include <vector>
#include <cassert>

class QueenValue: public Value
{
  public:
    enum {
      INFINITY = -1
    };
    QueenValue(); 
    QueenValue(int value);
    ~QueenValue();
  
    QueenValue* clone();
    QueenValue& operator=(const QueenValue& other);
    void        updateValue(int changeBy);
    void        setValue(const Value* val);
    int         compare(const Value* other) const;
    void        show() const;
  
  private:
    void        setValue(const int &value) { _value = value; }
    int         getValInt() const;
  
  private:
    int         _value;
};

class QueenState: public State
{
  public:
    QueenState(unsigned n);
    QueenState(const QueenState& other);
    ~QueenState();
  
    int         compare(const QueenState& other) const; 
    bool        setQueenPos(unsigned qNum, unsigned newPos);
    
    State*      getNextNeighbor();
    void        copyState(const State* other);
    void        show(const std::string& msg = "") const;
    
  private:
    void        evaluateValue();
    void        initState();
    void        updateValue(unsigned queenNum, unsigned oldPos, unsigned newPos);
  
  private:
    std::vector<unsigned>       _queenArr;
    unsigned                    _qnum;
    unsigned                    _qpos;
};

class Queen
{
  public:
    Queen(unsigned numQueens = 4);
    ~Queen();
  
    bool        solve(int iterations = -1);
    void        dumpState() const;
  
  private:
    void        init(unsigned numQueens);
  
  private:
    unsigned    _numQueens;
    QueenState* _qstate;
    QueenValue* _qgoal;
    HillClimb*  _hc;
};

#endif
