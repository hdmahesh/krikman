//!
//! @author  Mahesh H D
//! @date    2015

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include "kirkman.h"

typedef std::vector<nodeInfo*> NodeArray;

unsigned
getNumCombinations(const int &n, const int &r)
{
  double result = 1.0;
  int index = r-1;
  for (; index >= 0; --index) {
    result *= ((n-index) / (r-index));
  }
  return (unsigned)result;
}

void
printRequestedState(const NodeArray &arr,
    nodeInfo::State state, int verboseLevel = 0)
{
  std::cout << "** State : " << state << " *** " << std::endl;
  for (size_t index = 0; index < arr.size(); ++index) {
    const nodeInfo *obj = arr[index];
    if (obj->getState() == state)
      obj->show(verboseLevel);
  }
}

void
updateState(NodeArray &arr)
{
  for (size_t index = 0; index < arr.size(); ++index) {
    nodeInfo *obj = arr[index];
    nodeInfo::State s = obj->getState();
    if (s == nodeInfo::SKIP) continue;

    if (s == nodeInfo::SELECT) {
      obj->setState(nodeInfo::SKIP);
    } else if (s == nodeInfo::REJECT) {
      obj->setState(nodeInfo::UNDEFINED);
    } else {
      std::cout << "State : " << s << std::endl;
      assert(0);
    }
  }
}

void
traverseBFS(NodeArray &arr)
{
  // BFS
  std::queue<nodeInfo*>  q;
  q.push(arr[0]);
  while (!q.empty()) {
    nodeInfo *obj = q.front();
    q.pop();
    if (obj->isSkip() ||
	(!obj->isUndefined() && !obj->isUnprocessed())) {
      continue;
    }

    bool markChild = false;
    if (obj->isUndefined()) {
      obj->setState(nodeInfo::SELECT);
      markChild = true;
    }
    if (obj->isUnprocessed()) {
      obj->setState(nodeInfo::REJECT);
    }
    const nodeInfo::NeighborList &neighbors = obj->getNeighbors();
    for (size_t index = 0; index < neighbors.size(); ++index) {
      nodeInfo *& child = arr[neighbors[index]];
      if (child->isSkip() || !child->isUndefined()) {
	continue;
      }
      if (markChild) child->setState(nodeInfo::UNPROCESSED);
      q.push(child);
    }
  }
}

int
main ()
{
  const int numElements = 9;
  const int groupSize = 3;
  const int numDays   = (numElements - 1) / 2;

  NodeArray arr(getNumCombinations(numElements, groupSize));
  int id = 0;
  for (size_t index1 = 1; index1 <= numElements; ++index1) {
    for (size_t index2 = index1 + 1; index2 <= numElements; ++index2) {
      for (size_t index3 = index2 + 1; index3 <= numElements; ++index3) {
	arr[id] = new nodeInfo(id, index1, index2, index3);
	// arr[id]->show();
	// Add neighbor information
	for (size_t index = 0; index < id; ++index) {
	  if (arr[id]->addNeighbor(*arr[index])) {
	    (void)arr[index]->addNeighbor(*arr[id], true);
	  }
	}
	++id;
      }
    }
  }

  for (size_t index = 1; index <= 2; ++index) {
    std::cout << "******** DAY " << index << " *******" << std::endl;
    traverseBFS(arr);
    printRequestedState(arr, nodeInfo::SELECT);
    printRequestedState(arr, nodeInfo::UNDEFINED);
    updateState(arr);
  }

  for (size_t index = 0; index < arr.size(); ++index) {
    delete arr[index];
    arr[index] = NULL;
  }
  return 0;
}
