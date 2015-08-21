
#ifndef KIRKMAN_H
#define KIRKMAN_H

#include <vector>

class nodeInfo {
    struct combination;

  public:
    typedef std::vector<int>   NeighborList;
    enum State {
      UNDEFINED = -1,
      UNPROCESSED,
      SELECT,
      REJECT,
      SKIP
    };

    nodeInfo();
    nodeInfo(int id, unsigned int x, unsigned int y, unsigned int z);
    ~nodeInfo();

    int    getObjId() const {return _objId;}
    const NeighborList & getNeighbors() const;

    const combination& getCombination() const {return _comb;}

    bool            isSkip() const {return _status == SKIP;}
    bool            isUndefined() const {return _status == UNDEFINED;}
    bool            isUnprocessed() const {return _status == UNPROCESSED;}
    bool            isSelect() const {return _status == SELECT;}
    bool            isReject() const {return _status == REJECT;}
    void            show(int verboseLevel = 0) const;

    State           getState() const {return _status;}
    void            setState(State sInfo) {_status = sInfo;}

    bool            addNeighbor(const nodeInfo& nn, bool force = false);

  private:

    bool            isNeighbor(const nodeInfo& nn) const;

    struct combination {
      unsigned int x;
      unsigned int y;
      unsigned int z;
      combination() {
	x = y = z = 0;
      }
      combination(unsigned int ix, unsigned int iy, unsigned iz) {
	x = ix; y = iy; z = iz;
      }

      bool    sharesMember(const combination &other) const;
    };

    int            _objId;
    combination    _comb;
    NeighborList   _neighbors;
    State          _status;
};

#endif
