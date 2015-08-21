#include "Queen.h"
#include "include/util.h"
#include "include/HillClimbBasic.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <set>


// ----------------------------------------------
// Implementation of QueenValue Class
// ----------------------------------------------

//  QueenValue::QueenValue()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
QueenValue::QueenValue()
  : _value((int)INFINITY)
{
  FFL;
}

//  QueenValue::QueenValue()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
QueenValue::QueenValue(int value)
  :_value(value)
{
  FFL;
}

//  QueenValue::~QueenValue()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
QueenValue::~QueenValue()
{
  FFL;
}

//  QueenValue::compare()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
int
QueenValue::compare(const Value* other) const
{
  FFL;
  const QueenValue *temp = dynamic_cast<const QueenValue*>(other);
  assert(temp);
#ifdef __DEBUG__
  std::cout << "Value.show(): " << std::endl;
  show();
  std::cout << "Other.show(): " << std::endl;
  temp->show();
#endif
  return (_value - temp->_value);
}

//  QueenValue::operator=()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
QueenValue&
QueenValue::operator=(const QueenValue& other)
{
  assert(0);
  FFL;
  _value = other._value;
  return *this;
}

//  QueenValue::clone()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
QueenValue*
QueenValue::clone()
{
  return new QueenValue(_value);
}

//  QueenValue::show()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
void
QueenValue::show() const
{
            
  std::cout << _value ;
}

//  QueenValue::getValInt()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
int
QueenValue::getValInt() const
{
  FFL;
  return _value;
}

//  QueenValue::setValue()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
void
QueenValue::setValue(const Value* val)
{
  FFL;
  return setValue(static_cast<const QueenValue*>(val)->getValInt());
}

//  QueenValue::updateValue()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
void
QueenValue::updateValue(int changeBy)
{
  FFL;
  _value += changeBy;
}


// ----------------------------------------------
// Implementation of QueenState Class
// ----------------------------------------------

//  QueenState::QueenState()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
QueenState::QueenState(unsigned n)
  :State(new QueenValue), _queenArr(n)
{
  FFL;
  initState();
}

//  QueenState::QueenState()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
QueenState::QueenState(const QueenState& other)
  : State(other)
{
  FFL;
  _queenArr = other._queenArr;
  _qnum = 0;
  _qpos = _queenArr[_qnum];
}

//  QueenState::~QueenState()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
QueenState::~QueenState()
{
  FFL;
}

//  QueenState::initState()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
void
QueenState::initState() {
  FFL;
  // all queens are placed on zeroth row
  // std::fill(_queenArr.begin(), _queenArr.end(), 0);
  std::set<int> alreadySet;
  std::random_device generator;
  std::uniform_int_distribution<int> distribution(0, _queenArr.size() - 1);
  do {
    int queenNum = distribution(generator);
    int position = distribution(generator);
    if (!alreadySet.count(queenNum)) {
      _queenArr[queenNum] = position;
      alreadySet.insert(queenNum);
    }
  } while (alreadySet.size() < _queenArr.size());
  _qnum = 0;
  _qpos = _queenArr[_qnum];
  evaluateValue();
  // std::cout << "INIT : ";
  // show();
}

//  QueenState::compare()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
int
QueenState::compare(const QueenState& other) const
{ 
  FFL;
  return (getValue()->compare(other.getValue()));
}

//  QueenState::getNextNeighbor()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
State*
QueenState::getNextNeighbor()
{
  // New position of queen with number _qnum
  // (just move the queen to next row)
  ++_qpos;
  _qpos = _qpos % _queenArr.size();

  while (_qpos == _queenArr[_qnum]) {
    ++_qnum;
    if (_qnum == _queenArr.size()) {
      return NULL;
    }
    _qpos = _queenArr[_qnum] + 1;
    _qpos = _qpos % _queenArr.size();
  }

  // Caller is responsible to free *nb
  QueenState *nb = new QueenState(*this);
  nb->setQueenPos(_qnum, _qpos);
  return nb;
}

//  QueenState::copyState()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
void
QueenState::copyState(const State* other)
{
  const QueenState *qs = dynamic_cast<const QueenState*>(other);
  _queenArr = qs->_queenArr;
  _qnum = 0;
  _qpos = _queenArr[_qnum];
  State::copyState(other);
}

//  QueenState::evaluateValue()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
void
QueenState::evaluateValue() {
  FFL;
  int num_of_attacks = 0;
  for (size_t qn = 0; qn < _queenArr.size(); ++qn) {
    unsigned pos = _queenArr[qn];
    for (size_t oqn = qn+1; oqn < _queenArr.size(); ++oqn) {
      if (pos == _queenArr[oqn]) {
        ++num_of_attacks;
      } else {
        int col_diff = qn - oqn;
        col_diff = (col_diff < 0) ? (col_diff * -1) : col_diff;
        int row_diff = pos - _queenArr[oqn];
        row_diff = (row_diff < 0) ? (row_diff * -1) : row_diff;
        if (col_diff == row_diff) {
          ++num_of_attacks;
        }
      }
    }
  }
  QueenValue val(num_of_attacks);
#ifdef __DEBUG__
  std::cout << "        In evaluateValue()" << std::endl;
  val.show();
#endif
  setValue(&val);
#ifdef __DEBUG__
  std::cout << "        After set" << std::endl;
  static_cast<const QueenValue*>(getValue())->show();
#endif
}

//  QueenState::updateValue()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
void
QueenState::updateValue(
    unsigned queenNum,
    unsigned oldPos,
    unsigned newPos)
{
  int toDeduct = 0;
  int toAdd = 0;
  for (size_t index = 0; index < _queenArr.size(); ++index) {
    if (index == queenNum) continue;
    if (_queenArr[index] == oldPos) {
      ++toDeduct;
    } else {
      int col_diff = queenNum - index;
      col_diff = (col_diff < 0) ? (col_diff * -1) : col_diff;
      int row_diff = oldPos - _queenArr[index];
      row_diff = (row_diff < 0) ? (row_diff * -1) : row_diff;
      if (col_diff == row_diff) {
        ++toDeduct;
      }
    }
    if (_queenArr[index] == newPos) {
      ++toAdd;
    } else {
      int col_diff = queenNum - index;
      col_diff = (col_diff < 0) ? (col_diff * -1) : col_diff;
      int row_diff = newPos - _queenArr[index];
      row_diff = (row_diff < 0) ? (row_diff * -1) : row_diff;
      if (col_diff == row_diff) {
        ++toAdd;
      }
    }
  }
  static_cast<QueenValue*>(accessValue())->updateValue(-toDeduct);
  static_cast<QueenValue*>(accessValue())->updateValue(toAdd);
}

//  QueenState::setQueenPos()
//! @author Mahesh H D
//! @date   01 Jan, 2015
//! @brief  Set a new position for a given queen
bool
QueenState::setQueenPos(
    unsigned queenNum,
    unsigned newPos)
{
  if (queenNum >= _queenArr.size() ||
      newPos >= _queenArr.size()) {
    return false;
  }
  unsigned oldPos = _queenArr[queenNum];
  _queenArr[queenNum] = newPos;
  _qnum = 0;
  _qpos = _queenArr[_qnum];
  // evaluateValue();
  updateValue(queenNum, oldPos, newPos);
  return true;
}

//  QueenState::show()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
void
QueenState::show(const std::string& msg) const
{
  using namespace std;
  cout << "(" << _qnum << "," << _qpos << ") - "
       << "[ ";
  for (size_t index = 0; index < _queenArr.size(); ++index) {
    cout << _queenArr[index] << " ";
  }
  cout << "]" ;
  cout << " - ";
  getValue()->show();
  cout << endl;
  return;
  cout << "======================" << endl;
  cout << "Queen array : " << endl;
  cout << "----------------------" << endl;
  for (size_t index = 0; index < _queenArr.size(); ++index) {
    cout << "Queen[" << index << "] : " << _queenArr[index] << endl;
  }
  cout << "----------------------" << endl;
  cout << "Value : " << endl;
  getValue()->show();
  cout << "----------------------" << endl;
  cout << "Queen num : " << _qnum << endl;
  cout << "Queen pos : " << _qpos << endl;
  cout << "======================" << endl;
}


// ----------------------------------------------
// Implementation of Queen Class
// ----------------------------------------------

//  Queen::Queen()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
Queen::Queen(unsigned numQueens)
  :_numQueens(numQueens), _qstate(NULL),
  _qgoal(NULL), _hc(NULL)
{
  init(numQueens);
}

//  Queen::~Queen()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
Queen::~Queen()
{
  if (_hc) delete _hc;
  if (_qgoal) delete _qgoal;
  if (_qstate) delete _qstate;
  _hc = NULL;
  _qgoal = NULL;
  _qstate = NULL;
}

//  Queen::init()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
void
Queen::init(unsigned numQueens)
{
  _qstate = new QueenState(numQueens);
  _qgoal = new QueenValue(0);
  _hc = new HillClimbBasic(_qstate, _qgoal);
}

//  Queen::solve()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
bool
Queen::solve(int iterations)
{
  return _hc->startClimb();
}

//  Queen::dumpState()
//! @author Mahesh H D and Sajjan
//! @date   01 Jan, 2015
//! @brief  
void
Queen::dumpState() const
{
  // std::cout << "**** Queen[" << _numQueens << "] ****" << std::endl;
  std::cout << "RESULT : ";
  _qstate->show();
}

