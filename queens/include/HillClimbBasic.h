#ifndef _HCBASIC_H_
#define _HCBASIC_H_
#include "HillClimb.h"

class HillClimbBasic: public HillClimb
{
public:
  HillClimbBasic(State *init_state, Value *goal, int debug_level = 0);
  virtual ~HillClimbBasic();

private:
  virtual bool isGoalReached() const;
  virtual State* getNextBestState();
};

#endif
