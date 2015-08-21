
#include "HillClimbBasic.h"
#include "State.h"
#include "Value.h"
#include "util.h"

HillClimbBasic::HillClimbBasic(
    State *init_state, Value *goal, int debug_level):
  HillClimb(init_state, goal, debug_level)
{
  FFL;
}

HillClimbBasic::~HillClimbBasic()
{
  FFL;
}

bool
HillClimbBasic::isGoalReached() const
{
  FFL;
  const Value *state_value = _current_state->getValue();
  return !(state_value->compare(_goal_value));
}

State*
HillClimbBasic::getNextBestState()
{
  FFL;
  State *best = NULL;
  State *curr = NULL;
  
  while ((curr = _current_state->getNextNeighbor()) != NULL) {
    if (!best) {
      best = curr;
      if (getDebugLevel() >= 2) {
        best->show("FIRST BEST NEIGHBOR");
      }
    } else if (curr->getValue()->compare(best->getValue()) < 0) {
      delete best;
      best = curr;
      if (getDebugLevel() >= 2) {
        best->show("NEXT BEST NEIGHBOR");
      }
    } else {
      delete curr;
    }
  }

  // caller is responsible to delete *best
  return best;
}
