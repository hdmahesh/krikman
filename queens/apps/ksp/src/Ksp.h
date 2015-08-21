#ifndef _KSP_H_
#define _KSP_H_

#include "include/Value.h"
#include "include/State.h"
#include <map>
#include <vector>

#define ENV_KSP_DEBUG_LEVEL "KSP_DEBUG_LEVEL"

/* Forward declarations */
class HillClimb;

class Player
{
  public:
    Player(unsigned playerId);
    ~Player();

    unsigned    getId() const;
    unsigned    getGroupId(unsigned wId) const;
    void        setGroupId(unsigned wId, unsigned gId);
    void        show() const;

  private:
    typedef std::map<unsigned,unsigned> WeekToGroupMap_t;
    unsigned             _id;
    WeekToGroupMap_t     _w2g;
};

class Group
{
  public:
    typedef std::vector<unsigned>                   PlayerArray_t;
    typedef std::vector<unsigned>::iterator         PlayerArrayIterator; 
    typedef std::vector<unsigned>::const_iterator   PlayerArrayCIterator; 

    Group(unsigned groupId, unsigned wId);
    ~Group();

    unsigned                    getId() const;
    unsigned                    getWeekId() const;
    void                        addPlayer(unsigned pId);
    bool                        removePlayer(unsigned pId);
    bool                        hasPlayer(unsigned pId) const;
    void                        show() const;
    PlayerArrayCIterator        getPlayerArrCBegin() const;
    PlayerArrayCIterator        getPlayerArrCEnd() const;
    PlayerArrayIterator         getPlayerArrBegin();
    PlayerArrayIterator         getPlayerArrEnd();

  private:
    unsigned                    _id;
    unsigned                    _wId;
    PlayerArray_t               _pArr;
};

class Week
{
  public:
    typedef std::vector<unsigned>                   GroupArray_t;
    typedef std::vector<unsigned>::iterator         GroupArrayIterator;
    typedef std::vector<unsigned>::const_iterator   GroupArrayCIterator;

    Week(unsigned weekId);
    ~Week();

    unsigned            getId() const;
    void                addGroup(unsigned gId);
    bool                hasGroup(unsigned gId) const;
    GroupArrayCIterator getGroupArrCBegin() const;
    GroupArrayCIterator getGroupArrCEnd() const;
    GroupArrayIterator  getGroupArrBegin();
    GroupArrayIterator  getGroupArrEnd();
    void                show() const;

  private:
    unsigned            _id;
    GroupArray_t        _gArr;
};

class KspValue : public Value
{
  public:
    KspValue();
    KspValue(int initVal);
    ~KspValue();

    int         compare(const Value* other) const;
    void        show() const;

    // Needed to get a prototype of this!
    KspValue*   clone();
    void        setValue(const Value* val);

    // Needed to quickly update the fitness value without actually
    // having to trigger a recomputation.
    // TODO: find if there is a more elegant way!
    void        updateValue(int changeBy);

  private:
    void        setValue(const int &value);
    int         getValInt() const;

  private:
    // Represents the total violations of
    // the third constraint, i.e. the total
    // number of excess appearance of two (any two)
    // players in the same group:
    // Ref : <Provide a link to our site where this info is aggregated>
    int         _value;
};

class KspState : public State
{
  public:
    KspState(unsigned numPlayers = 15);
    KspState(const KspState& other);
    ~KspState();

    unsigned    getPlayerGroupId(unsigned pId, unsigned weekId);
    State*      getNextNeighbor();
    void        copyState(const State* other);
    void        show(const std::string& msg = "") const;

  private:
    bool        swapPlayerGroups(unsigned p1Id, unsigned p2Id, unsigned weekId);
    void        evaluateValue();
    void        updateValue(unsigned p1Id, unsigned p2Id, unsigned weekId);
    unsigned    getSameGroupCount(const Player &p1Obj, const Player &p2Obj) const;
    void        initState();
    Week&       getWeekObject(unsigned weekId);
    Group&      getGroupObject(unsigned groupId);
    Player&     getPlayerObject(unsigned playerId);

    unsigned    createWeek();
    unsigned    createGroup(unsigned weekId);
    unsigned    createPlayer();

  private:
    static const unsigned       GROUP_SIZE = 3; // Standard

    unsigned    _numStudents; // Input from user
    unsigned    _numGroups;    
    unsigned    _numWeeks;

    typedef std::vector<Player> PlayersArray_t;
    typedef std::vector<Group>  GroupsArray_t;
    typedef std::vector<Week>   WeeksArray_t;

    PlayersArray_t      _pArr;
    GroupsArray_t       _gArr;
    WeeksArray_t        _wArr;

    // Needed to remember previous participants in neighbor
    // generation.
    unsigned    _pArrIndex1;
    unsigned    _pArrIndex2;
    unsigned    _weekIndex;
};

class Ksp
{
  public:
    Ksp(unsigned numPlayers = 9);
    ~Ksp();

    bool        solve(int iterations = -1);
    void        dumpState() const;

  private:
    void        init();

  private:
    KspState*   _kState;
    KspValue*   _kGoal;
    HillClimb*  _hc;
    unsigned    _numPlayers;
    int         _debug_level;
};

#endif
