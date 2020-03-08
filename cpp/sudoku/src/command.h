#pragma once

#include <memory>
#include "common.h"

class CScene;
class CCommand {
 public:
  CCommand(CScene *pOwner);
  CCommand(const CCommand &);
  ~CCommand();

  bool execute(int nInputValue);
  void undo();

 private:
  CScene *_pOwner;
  point_t _stPoint;
  int _nPreValue;
  int _nCurValue;
};