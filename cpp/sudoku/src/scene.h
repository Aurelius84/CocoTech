#pragma once

#include <iostream>
#include <vector>

#include "block.h"
#include "command.h"
#include "common.h"

// 数独场景类
class CScene {
 public:
  CScene(int index = 3);
  virtual ~CScene();

  void generate();

  void show() const;

  bool setCurValue(const int nCurValue, int& nLastValue);

  bool setPointValue(const point_t&, const int);

  point_t getCurPoint();

  void eraseRandomGrids(const int count);

  bool isComplete();

  void play();

 private:
  void init();  // 将每个格子的指针放到block里
  void printUnderline(int line_no=-1) const;
  void setValue(const int);
  void setValue(const point_t &, const int);


 private:
  int _index;
  int _max_column;
  point_t _cur_point;
  CBlock _column_block[9];
  CBlock _row_block[9];
  CBlock _xy_block[3][3];
  point_value_t _map[81];

  std::vector<CCommand> _vCommand;
};