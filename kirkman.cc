
#include <iostream>
#include "kirkman.h"

nodeInfo::nodeInfo()
{
  _objId = -1;
  _status = nodeInfo::UNDEFINED;
}

nodeInfo::nodeInfo(int id, unsigned int x,
    unsigned int y, unsigned int z) :
  _objId(id), _comb(x, y, z)
{
  _status = nodeInfo::UNDEFINED;
}

nodeInfo::~nodeInfo()
{
  _objId = -1;
}

const
nodeInfo::NeighborList&
nodeInfo::getNeighbors() const
{
  return _neighbors;
}

void
nodeInfo::show(int verboseLevel) const
{
  std::cout << "Object Id : " << _objId << std::endl;
  std::cout << "{" << _comb.x << "," << _comb.y << "," << _comb.z << "}" << std::endl;
  if (verboseLevel) {
    std::cout << "Neighbors : " << _neighbors.size() << std::endl;
    std::cout << "{";
    NeighborList::const_iterator it = _neighbors.begin();
    while (it!=_neighbors.end()) {
      std::cout << *it++ << ",";
    }
    std::cout << "}" << std::endl;
  }
}

bool
nodeInfo::combination::sharesMember(
    const nodeInfo::combination &other) const
{
  if (x == other.x || x == other.y || x == other.z) return true;
  if (y == other.x || y == other.y || y == other.z) return true;
  if (z == other.x || z == other.y || z == other.z) return true;
  return false;
}

bool
nodeInfo::isNeighbor(const nodeInfo &nn) const
{
  return _comb.sharesMember(nn.getCombination());
}

bool
nodeInfo::addNeighbor(const nodeInfo&  nn, bool force)
{
  if (force || isNeighbor(nn)) {
    _neighbors.push_back(nn.getObjId());
    return true;
  }
  return false;
}
