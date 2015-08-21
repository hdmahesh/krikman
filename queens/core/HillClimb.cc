#include "HillClimb.h"
#include "State.h"
#include "Value.h"
#include "util.h"
#include <cassert>
#include <iostream>

HillClimb::HillClimb(State *init_state, Value *goal, int debug_level)
  :_current_state(init_state), _goal_value(goal), _debug_level(debug_level)
{
  FFL;
  _debug_level = utility::envGetIntegerVar(ENV_HC_DEBUG_LEVEL, _debug_level);
}

HillClimb::~HillClimb()
{
  FFL;
}

int
HillClimb::getDebugLevel()
{
  return _debug_level;
}

bool
HillClimb::startClimb() {
  FFL;
  assert(_current_state != NULL);

  if (getDebugLevel() >= 1) {
    _current_state->show("INITIAL");
  }

  unsigned steps = 0;
  while (!isGoalReached()) {
    State *neighbor = getNextBestState();
    if (!neighbor) {
      return false;
    }
    // Now check if the best neighbor is better than
    // the current. If yes, then reset the current_state
    // to the new best.
    int compareRes = neighbor->getValue()->compare(_current_state->getValue());
    if (compareRes < 0) {
      ++steps;
      _current_state->copyState(neighbor);
      if (getDebugLevel() >= 1) {
        _current_state->show("NEXT CURRENT STATE");
      }
    }
    delete neighbor;
    if (compareRes >= 0) {
      // The next best is same as current-state.
      // No point in continuing
      break;
    }
  }

  if (getDebugLevel() >= 1) {
    std::cout << std::endl << "***** STEPS: " << steps << " *****" << std::endl;
  }
  return isGoalReached();
}

bool
HillClimb::isGoalReached() const
{
  FFL;
  return true;
}

State*
HillClimb::getNextBestState()
{
  FFL;
  return NULL;
}
