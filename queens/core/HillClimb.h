
#ifndef _HILL_CLIMB_H_
#define _HILL_CLIMB_H_

#define ENV_HC_DEBUG_LEVEL "HC_DEBUG_LEVEL"

class State;
class Value;

class HillClimb
{
public:
  HillClimb(State *init_state, Value *goal, int debug_level = 0);
  virtual ~HillClimb();
  bool startClimb();
  int getDebugLevel();

private:
  virtual bool isGoalReached() const;
  virtual State* getNextBestState();

protected:
  State *_current_state;
  Value *_goal_value;

private:
  int _debug_level;
};

#endif
