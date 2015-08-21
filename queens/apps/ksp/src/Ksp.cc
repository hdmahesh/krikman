#include "Ksp.h"
#include "include/util.h"
#include "include/HillClimbBasic.h"
#include <cassert>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>


// ----------------------------------------------
// Implementation of Player Class
// ----------------------------------------------

//  Player::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Player::Player(unsigned playerId)
  :_id(playerId)
{
}

//  Player::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Player::~Player()
{
}

//  Player::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
unsigned
Player::getId() const
{
  return _id;
}

//  Player::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
unsigned
Player::getGroupId(unsigned wId) const
{
  assert(_w2g.count(wId));
  return _w2g.find(wId)->second;
}

//  Player::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
Player::setGroupId(unsigned wId, unsigned gId)
{
  _w2g[wId] = gId;
}

//  Player::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
Player::show() const
{
  using namespace std;
  cout << "P = {" << setw(2) << _id << ": [";
  for (WeekToGroupMap_t::const_iterator it = _w2g.begin(); it !=
      _w2g.end(); ++it) {
    cout << setw(2) << "(" << it->first << " " << it->second << ") "; 
  }
  cout << "]}" << endl;
}


// ----------------------------------------------
// Implementation of Group Class
// ----------------------------------------------

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Group::PlayerArrayCIterator
Group::getPlayerArrCBegin() const
{
  return _pArr.cbegin();
}

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Group::PlayerArrayCIterator
Group::getPlayerArrCEnd() const
{
  return _pArr.cend();
}

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Group::PlayerArrayIterator
Group::getPlayerArrBegin()
{
  return _pArr.begin();
}

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Group::PlayerArrayIterator
Group::getPlayerArrEnd()
{
  return _pArr.end();
}

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Group::Group(unsigned groupId, unsigned wId)
  :_id(groupId), _wId(wId)
{
}

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Group::~Group()
{
}

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
unsigned
Group::getId() const
{
  return _id;
}

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
unsigned
Group::getWeekId() const
{
  return _wId;
}

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
Group::addPlayer(unsigned pId)
{
  if (!hasPlayer(pId)) {
    _pArr.push_back(pId);
  }
  assert(_pArr.size() < 4);
}

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
bool
Group::removePlayer(unsigned pId)
{
  PlayerArrayIterator toDelete = std::find(_pArr.begin(), _pArr.end(), pId);
  if (toDelete != _pArr.end()) {
    _pArr.erase(toDelete);
    return true;
  }
  return false;
  return std::remove(_pArr.begin(), _pArr.end(), pId) != _pArr.end();
}

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
bool
Group::hasPlayer(unsigned pId) const
{
  return std::find(_pArr.begin(), _pArr.end(), pId) != _pArr.end();
}

//  Group::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
Group::show() const
{
  struct gShow {
    void operator() (const unsigned &val) {
      std::cout << std::setw(2) << val << " ";
    };
  };
  std::cout << "G = {" << std::setw(2) << _id << ": [" << _wId << ": (";
  std::for_each(_pArr.begin(), _pArr.end(), gShow());
  std::cout << ")]}" << std::endl;
}


// ----------------------------------------------
// Implementation of Week Class
// ----------------------------------------------

//  Week::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Week::Week(unsigned weekId)
  :_id(weekId)
{
}

//  Week::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Week::~Week()
{
}

//  Week::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
unsigned
Week::getId() const
{
  return _id;
}

//  Week::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
Week::addGroup(unsigned gId)
{
  if (!hasGroup(gId)) {
    _gArr.push_back(gId);
  }
}

//  Week::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
bool
Week::hasGroup(unsigned gId) const
{
  return std::find(_gArr.begin(), _gArr.end(), gId) != _gArr.end();
}

//  Week::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Week::GroupArrayCIterator
Week::getGroupArrCBegin() const
{
  return _gArr.cbegin();
}

//  Week::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Week::GroupArrayCIterator
Week::getGroupArrCEnd() const
{
  return _gArr.cend();
}

//  Week::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Week::GroupArrayIterator
Week::getGroupArrBegin()
{
  return _gArr.begin();
}

//  Week::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Week::GroupArrayIterator
Week::getGroupArrEnd()
{
  return _gArr.end();
}

//  Week::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
Week::show() const
{
  struct wShow {
    void operator() (const unsigned &groupId) {
      std::cout << std::setw(2) << groupId << " ";
    };
  };
  std::cout << "W = {" << std::setw(2) << _id << "[(";
  std::for_each(_gArr.begin(), _gArr.end(), wShow());
  std::cout << ")]}" << std::endl;
}


// ----------------------------------------------
// Implementation of KspValue Class
// ----------------------------------------------

//  KspValue::KspValue()
//! @author    Mahesh H D & P. Sajjan
//! @date      06 Jan, 2015
//! @brief     Default constructor
//!
KspValue::KspValue()
  : _value(-1)
{
  FFL;
}

//  KspValue::KspValue()
//! @author    Mahesh H D & P. Sajjan
//! @date      06 Jan, 2015
//! @brief     Constructor
//! 
KspValue::KspValue(int initVal)
  : _value(initVal)
{
  FFL;
}

//  KspValue::~KspValue()
//! @author    Mahesh H D & P. Sajjan
//! @date      06 Jan, 2015
//! @brief     Destructor
//! 
KspValue::~KspValue()
{
  FFL;
}

//  KspValue::compare()
//! @author    Mahesh H D & P. Sajjan
//! @date      06 Jan, 2015
//! @brief     Compare two values. Can be used as a predicate function
//!            in many places (STL algos etc).
//! 
int
KspValue::compare(const Value* other) const
{
  FFL;
  const KspValue *otherVal = dynamic_cast<const KspValue*>(other);
  assert(otherVal);
  return (_value - otherVal->_value);
}

//  KspValue::show()
//! @author    Mahesh H D & P. Sajjan
//! @date      06 Jan, 2015
//! @brief     Useful in debugging.
//!
void
KspValue::show() const
{
  std::cout << _value ;
}

//  KspValue::clone()
//! @author    Mahesh H D & P. Sajjan
//! @date      06 Jan, 2015
//! @brief     Clone self. Useful in implementing a prototype pattern.
//!            TODO: Check if this can be a const API
KspValue*
KspValue::clone()
{
  return new KspValue(_value);
}

//  KspValue::setValue()
//! @author    Mahesh H D & P. Sajjan
//! @date      06 Jan, 2015
//! @brief     Pick value from another homogenous object.
//!
void
KspValue::setValue(const Value* val)
{
  const KspValue* toSetFrom = dynamic_cast<const KspValue*>(val);
  assert(toSetFrom);
  setValue(toSetFrom->getValInt());
}

//  KspValue::updateValue()
//! @author    Mahesh H D & P. Sajjan
//! @date      06 Jan, 2015
//! @brief     Update the value. Useful in avoiding a complete
//!            recomputation.
//!
void
KspValue::updateValue(int changeBy)
{
  _value += changeBy;
}

//  KspValue::getValInt()
//! @author    Mahesh H D & P. Sajjan
//! @date      06 Jan, 2015
//! @brief     Update the value. Useful in avoiding a complete
//!            recomputation.
//!
int
KspValue::getValInt() const
{
  return _value;
}

//  KspValue::setValue()
//! @author    Mahesh H D & P. Sajjan
//! @date      06 Jan, 2015
//! @brief     Set the value
//!
void
KspValue::setValue(const int &value)
{
  _value = value;
}


// ----------------------------------------------
// Implementation of KspState Class
// ----------------------------------------------

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
KspState::KspState(unsigned numPlayers)
  :State(new KspValue), _numStudents(numPlayers)
{
  assert((_numStudents%GROUP_SIZE) == 0);
  _numGroups = _numStudents/GROUP_SIZE;
  _numWeeks  = (_numStudents - 1) / (GROUP_SIZE - 1);
  initState();
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
KspState::KspState(const KspState& other)
  : State(other)
{
  static unsigned INVALID = -1;
  _weekIndex = INVALID;
  _pArrIndex1 = INVALID;
  _pArrIndex2 = INVALID;

  _wArr = other._wArr;
  _gArr = other._gArr;
  _pArr = other._pArr;

  _numStudents = other._numStudents;
  _numGroups = other._numGroups;
  _numWeeks = other._numWeeks;
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
KspState::~KspState()
{
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
unsigned
KspState::getPlayerGroupId(
    unsigned pId,
    unsigned weekId)
{
  Week& wObj = getWeekObject(weekId);
  Week::GroupArrayCIterator gBegin = wObj.getGroupArrCBegin();
  Week::GroupArrayCIterator gEnd   = wObj.getGroupArrCEnd();
  Week::GroupArrayCIterator result;
  //!
  //! Note: The below use of stl-algorithms won't provide any
  //! more meaning or performance improvements.
  //! It is used here, just to get a clear understanding of its usage.
  //!
  //! Define a predicate for use in std::find_if. The predicate can be
  //! a function object as well. For now, lets keep it simple :-)
  //!
  bool useMethod1 = false;
  if (useMethod1) {
    /* method 1 : with binders, a little old-style now! */
    struct pred {
      pred(KspState *sObj, unsigned pId) :
        stateObj(sObj), playerId(pId) {};
      bool operator() (const unsigned &groupId) {
        return stateObj->getGroupObject(groupId).hasPlayer(playerId);
      };
      KspState   *stateObj;
      unsigned    playerId;
    };
    result = std::find_if(gBegin, gEnd, pred(this, pId));
  } else {
    /* method 2 : with lambdas, extremely useful, concise and elegant */
    result = std::find_if(gBegin, gEnd,
                          [&](const unsigned &groupId) -> bool {
                             return getGroupObject(groupId).hasPlayer(pId);
                           });
  }
  if (result == gEnd) {
    assert(false);
    return -1;
  }
  return *result;
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Week&
KspState::getWeekObject(unsigned weekId)
{
  assert(weekId < _wArr.size());
  return _wArr[weekId];
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Group&
KspState::getGroupObject(unsigned groupId)
{
  assert(groupId < _gArr.size());
  return _gArr[groupId];
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Player&
KspState::getPlayerObject(unsigned playerId)
{
  assert(playerId < _pArr.size());
  return _pArr[playerId];
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
unsigned
KspState::createWeek()
{
  unsigned wId = _wArr.size();
  Week wObj(wId);
  _wArr.push_back(wObj);

  for (unsigned gNo = 0; gNo < _numGroups; ++gNo) {
    _wArr.back().addGroup(createGroup(wId));
  }
  return wId;
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
unsigned
KspState::createGroup(unsigned weekId)
{
  unsigned gId = _gArr.size();
  _gArr.push_back(Group(gId, weekId));
  return gId;
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
unsigned
KspState::createPlayer()
{
  unsigned pId = _pArr.size();
  _pArr.push_back(Player(pId));
  return pId;
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
KspState::initState()
{

  // Create _numWeeks of Week objects;
  // and _numGroups of Group objects in each Week object
  for (unsigned wNo = 0; wNo < _numWeeks; ++wNo) {
    (void)createWeek();
  }

  // Create _numStudents of Player objects
  for (unsigned pNo = 0; pNo < _numStudents; ++pNo) {
    (void)createPlayer();
  }

  // Associate Players with Groups
  for (WeeksArray_t::iterator wIt = _wArr.begin(); wIt != _wArr.end(); ++wIt) {
    Week &wObj = *wIt;
    PlayersArray_t::iterator pIt = _pArr.begin();

    for (Week::GroupArrayIterator gIt = wObj.getGroupArrBegin(); gIt != wObj.getGroupArrEnd(); ++gIt) {
      Group &gObj = getGroupObject(*gIt);
      for (unsigned gs = 0; gs < GROUP_SIZE; ++gs) {
        Player &pObj = *pIt++;
        gObj.addPlayer(pObj.getId());
        pObj.setGroupId(wObj.getId(), *gIt);
      }
    }
    assert(pIt == _pArr.end());
  }

  // TODO: Need to duplicate in copy object
  static unsigned INVALID = -1;
  _weekIndex = INVALID;
  _pArrIndex1 = INVALID;
  _pArrIndex2 = INVALID;
  
  evaluateValue();
  // std::cout << "INIT : ";
  // show();
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
KspState::updateValue(unsigned p1Id, unsigned p2Id, unsigned weekId)
{
  Player &p1Obj = getPlayerObject(p1Id);
  Player &p2Obj = getPlayerObject(p2Id);
  Group &g1Obj =
    getGroupObject(getPlayerObject(p1Id).getGroupId(weekId));
  Group &g2Obj =
    getGroupObject(getPlayerObject(p2Id).getGroupId(weekId));
  
  Group::PlayerArrayCIterator pIter1 = g1Obj.getPlayerArrCBegin();
  Group::PlayerArrayCIterator pIter2 = g2Obj.getPlayerArrCBegin();

  int decreaseBy = 0;
  int increaseBy = 0;

  for (; pIter1 != g1Obj.getPlayerArrCEnd(); ++pIter1) {
    if (*pIter1 != p1Id && *pIter1 != p2Id) {
      int p2SameGroupCount = getSameGroupCount(p2Obj, getPlayerObject(*pIter1));
      int p1SameGroupCount = getSameGroupCount(p1Obj, getPlayerObject(*pIter1));

      if (p2SameGroupCount != 0) {
        ++decreaseBy;
      }
      if (p1SameGroupCount != 1) {
        ++increaseBy;
      }
    }
  }
  for (; pIter2 != g2Obj.getPlayerArrCEnd(); ++pIter2) {
    if (*pIter2 != p1Id && *pIter2 != p2Id) {
      int p1SameGroupCount = getSameGroupCount(p1Obj, getPlayerObject(*pIter2));
      int p2SameGroupCount = getSameGroupCount(p2Obj, getPlayerObject(*pIter2));

      if (p1SameGroupCount != 0) {
        ++decreaseBy;
      }
      if (p2SameGroupCount != 1) {
        ++increaseBy;
      }
    }
  }
  // getValue()->show();
  // std::cout << " D[-" << decreaseBy << "] I[+" << increaseBy << "] ";
  static_cast<KspValue*>(accessValue())->updateValue(-decreaseBy);
  static_cast<KspValue*>(accessValue())->updateValue(increaseBy);
  // getValue()->show();
  // std::cout << std::endl;
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
KspState::evaluateValue()
{
  unsigned totalCost = 0;
  PlayersArray_t::const_iterator pItOuter = _pArr.begin();
  for(; pItOuter != _pArr.end(); ++pItOuter) {
    PlayersArray_t::const_iterator pItInner = pItOuter + 1;
    for (; pItInner != _pArr.end(); ++pItInner) {
      unsigned localCost = getSameGroupCount(*pItOuter, *pItInner);
      if (localCost) --localCost;
      totalCost += localCost;
    }
  }
  KspValue val(totalCost);
#ifdef __DEBUG__
  std::cout << "        In evaluateValue()" << std::endl;
  val.show();
#endif
  setValue(&val);
#ifdef __DEBUG__
  std::cout << "        After set" << std::endl;
  static_cast<const KspValue*>(getValue())->show();
#endif
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
unsigned
KspState::getSameGroupCount(const Player &p1Obj, const Player &p2Obj)
  const
{
  unsigned localCost = 0;
  WeeksArray_t::const_iterator wIt = _wArr.begin();
  for (; wIt != _wArr.end(); ++wIt) {
    unsigned weekId = (*wIt).getId();
    if (p1Obj.getGroupId(weekId) ==
        p2Obj.getGroupId(weekId)) {
      ++localCost;
    }
  }
  return localCost;
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
State*
KspState::getNextNeighbor()
{
  static unsigned INVALID = -1;
  unsigned weekId = INVALID;
  unsigned p1Id = INVALID;
  unsigned p2Id = INVALID;
  unsigned g1Id = INVALID;
  unsigned g2Id = INVALID;
  do {
    if (_weekIndex == INVALID ||
        _pArrIndex1 == INVALID ||
        _pArrIndex2 == INVALID) {
      _weekIndex = 0;
      _pArrIndex1 = 0;
      _pArrIndex2 = _pArrIndex1 + 1;
    } else {
      ++_weekIndex;
      if (_weekIndex == _wArr.size()) {
        _weekIndex = 0;
        _pArrIndex2++;
      }
      if (_pArrIndex2 == _pArr.size()) {
        _pArrIndex1++;
        if (_pArrIndex1 == (_pArr.size() - 1)) {
          return NULL; // No more neighbors
        }
        _pArrIndex2 = _pArrIndex1 + 1;
      }
    }
    // Here, we can assume we have proper values for week index and
    // player index
    // Now, check if swapping is possible
    weekId = _weekIndex;
    p1Id   = _pArrIndex1;
    p2Id   = _pArrIndex2; 
    //std::cout << "NextNeighbor: p1 = " << p1Id << " p2 = " << p2Id << std::endl;
    g1Id   = getPlayerObject(p1Id).getGroupId(weekId);
    g2Id   = getPlayerObject(p2Id).getGroupId(weekId);
  } while (g1Id == g2Id);
  assert(weekId != INVALID);
  assert((g1Id != INVALID) && (g2Id != INVALID));
  assert((p1Id != INVALID) && (p2Id != INVALID));

  // Responsibility of the caller to release this memory
  KspState *np = new KspState(*this);
  np->swapPlayerGroups(p1Id, p2Id, weekId);
  return np;
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
bool
KspState::swapPlayerGroups(unsigned p1Id, unsigned p2Id, unsigned
    weekId)
{
  //std::cout << "Swap : p1 = " << p1Id << " p2 = " << p2Id << std::endl;
  unsigned g1Id = getPlayerObject(p1Id).getGroupId(weekId);
  unsigned g2Id = getPlayerObject(p2Id).getGroupId(weekId);
  assert(g1Id != g2Id);
  if (g1Id == g2Id) {
    return false;
  }
  getPlayerObject(p1Id).setGroupId(weekId, g2Id);
  getPlayerObject(p2Id).setGroupId(weekId, g1Id);
  assert(getGroupObject(g1Id).removePlayer(p1Id));
  getGroupObject(g1Id).addPlayer(p2Id);
  assert(getGroupObject(g2Id).removePlayer(p2Id));
  getGroupObject(g2Id).addPlayer(p1Id);
  // After swap p2Id is new player1 and p1Id is new player2
  updateValue(p2Id, p1Id, weekId);
  return true;
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
KspState::copyState(const State* other)
{
  const KspState *ns = dynamic_cast<const KspState*>(other);
  _numStudents = ns->_numStudents;
  _numGroups = ns->_numGroups;
  _numWeeks = ns->_numWeeks;

  _pArr = ns->_pArr;
  _gArr = ns->_gArr;
  _wArr = ns->_wArr;
  
  static unsigned INVALID = -1;
  _weekIndex = INVALID;
  _pArrIndex1 = INVALID;
  _pArrIndex2 = INVALID;

  State::copyState(other);
}

//  KspState::
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
KspState::show(const std::string& msg) const
{
  std::cout << std::endl << "***** STATE: " << msg << " *****" << std::endl;
  
  // Show value
  std::cout << "----> VALUE: "; 
  getValue()->show(); 
  std::cout << std::endl;

  // Show state
  std::for_each(_wArr.begin(), _wArr.end(), [](const Week& wObj) {wObj.show();});
  std::for_each(_gArr.begin(), _gArr.end(), [](const Group& gObj) {gObj.show();});
}


// ----------------------------------------------
// Implementation of Ksp Class
// ----------------------------------------------

//  Ksp::Ksp()
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Ksp::Ksp(unsigned numPlayers)
  : _kState(NULL), _kGoal(NULL), _hc(NULL), _numPlayers(numPlayers), _debug_level(0)
{
  init();
}

//  Ksp::~Ksp()
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
Ksp::~Ksp()
{
  if (!_hc) delete _hc;
  if (!_kState) delete _kState;
  if (!_kGoal) delete _kGoal;
}

//  Ksp::init()
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
Ksp::init()
{
  _debug_level = utility::envGetIntegerVar(ENV_KSP_DEBUG_LEVEL, _debug_level);
  _kState = new KspState(_numPlayers);
  _kGoal = new KspValue(0);
  _hc = new HillClimbBasic(_kState, _kGoal, _debug_level);
}

//  Ksp::solve()
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
bool
Ksp::solve(int iterations)
{
  return _hc->startClimb();
}

//  Ksp::dumpState()
//! @author Sajjan and Mahesh H D
//! @date   05 Jan, 2015
//! @brief  
void
Ksp::dumpState() const
{
  std::cout << "***** Ksp[ " << _numPlayers << " ] *****" << std::endl; 
  _kState->show();
}
