#include "scene.h"
#include <math.h>
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "utility.inl"

CScene::CScene(int index)
    : _index(index), _max_column(pow(index, 2)), _cur_point({0, 0}) {
  init();
}

CScene::~CScene() {}

void CScene::show() const {
  cls();
  printUnderline();
  for (int row = 0; row < _max_column; ++row) {
    auto block = _row_block[row];
    block.print();
    printUnderline(row);
  }
}

void CScene::printUnderline(int line_no) const {
  std::string underline;
  for (int column = 0; column < _max_column; ++column) {
    if (_cur_point.y == line_no && _cur_point.x == column)
      underline += "--^--";
    else
      underline += "----";
  }
  underline += "-";
  std::cout << underline << std::endl;
}

void CScene::init() {
  memset(_map, UNSELECTED, sizeof(_map));
  // column_block 所有列
  for (int column = 0; column < _max_column; column++) {
    CBlock column_block;
    for (int row = 0; row < _max_column; row++) {
      column_block.push_back(_map + row * 9 + column);
    }
    _column_block[column] = column_block;
  }

  // row_block所有行
  for (int row = 0; row < _max_column; row++) {
    CBlock row_block;
    for (int column = 0; column < _max_column; column++) {
      row_block.push_back(_map + column * 9 + row);
    }
    _row_block[row] = row_block;
  }

  // xy所有九宫格 [行][列]
  for (int block_index = 0; block_index < _max_column; block_index++) {
    CBlock xy_block;
    int xy_begin = block_index / 3 * 27 + block_index % 3 * 3;
    xy_block.push_back(_map + xy_begin);
    xy_block.push_back(_map + xy_begin + 1);
    xy_block.push_back(_map + xy_begin + 2);
    xy_block.push_back(_map + xy_begin + 9);
    xy_block.push_back(_map + xy_begin + 10);
    xy_block.push_back(_map + xy_begin + 11);
    xy_block.push_back(_map + xy_begin + 18);
    xy_block.push_back(_map + xy_begin + 19);
    xy_block.push_back(_map + xy_begin + 20);

    _xy_block[block_index / 3][block_index % 3] = xy_block;
  }
  return;
}

void CScene::play() {
  show();
  char key = '\0';
  while (1) {
    key = getch();
    if ('0' < key && key < '9') {
      CCommand oCommand(this);
      if (oCommand.execute(key - '0')) {
        std::cout << "this number can't be modified." << std::endl;
      } else {
        _vCommand.push_back(std::move(oCommand));
        show();
        continue;
      }
    }

    switch (key) {
      case 0x1B: {  // ESC
        std::cout << "quit game? [Y/N]" << std::endl;
        std::string strInput;
        std::cin >> strInput;
        if (strInput[0] == 'y' || strInput[0] == 'Y') {
          exit(0);
        } else {
          std::cout << "continue" << std::endl;
          break;
        }
      }
      case 0x75: {  // u
        if (_vCommand.empty()) {
          std::cout << "no more action to undo." << std::endl;
        } else {
          CCommand &oCommand = _vCommand.back();
          oCommand.undo();
          _vCommand.pop_back();
          show();
        }
        break;
      }
      case 0x61: {  // a
        _cur_point.x = (_cur_point.x - 1) < 0 ? 0 : _cur_point.x - 1;
        show();
        break;
      }
      case 0x64: {  // d
        _cur_point.x = (_cur_point.x + 1) > 8 ? 8 : _cur_point.x + 1;
        show();
        break;
      }
      case 0x73: {  // s
        _cur_point.y = (_cur_point.y + 1) > 8 ? 8 : _cur_point.y + 1;
        show();
        break;
      }
      case 0x77: {  // w
        _cur_point.y = (_cur_point.y - 1) < 0 ? 0 : _cur_point.y - 1;
        show();
        break;
      }
      case 0x0D: {  // enter
        if (isComplete()) {
          std::cout << "congratulation! you win!" << std::endl;
          getchar();
          exit(0);
        } else {
          std::cout << "sorry, not completed." << std::endl;
        }
        break;
      }
      default:
        break;
    }
  }
}

bool CScene::isComplete() {
  for (size_t i = 0; i < 81; ++i) {
    if (UNSELECTED == _map[i].value) {
      return false;
    }
    for (int row = 0; row < _max_column; row++) {
      for (int column = 0; column < _max_column; ++column) {
        if (!_row_block[row].isValid() || !_column_block[column].isValid() ||
            !_xy_block[row / 3][column / 3].isValid()) {
          std::cout << row << " " << column << std::endl;
          return false;
        }
      }
    }
    return true;
  }
}

void CScene::setValue(const point_t &p, const int value) {
  _map[p.x + p.y * 9].value = value;
}

void CScene::setValue(const int value) {
  auto p = _cur_point;
  this->setValue(_cur_point, value);
}

void CScene::eraseRandomGrids(const int count) {
  point_value_t p = {UNSELECTED, ERASED};
  std::vector<int> v;
  for (int i = 0; i < 81; ++i) {
    v.push_back(i);
  }
  for (int i = 0; i < count; ++i) {
    int r = random(0, v.size() - 1);
    _map[v[r]] = p;
    v.erase(v.begin() + r);
  }
}

bool CScene::setCurValue(const int nCurValue, int &nLastValue) {
  auto point = _map[_cur_point.x + _cur_point.y * 9];
  if (ERASED == point.state) {
    nLastValue = point.value;
    setValue(nCurValue);
    return true;
  } else {
    return false;
  }
}

//一个场景可以多次被初始化
void CScene::generate() {
  static char map_pattern[10][10] = {"ighcabfde", "cabfdeigh", "fdeighcab",
                                     "ghiabcdef", "abcdefghi", "defghiabc",
                                     "higbcaefd", "bcaefdhig", "efdhigbca"};
  std::vector<char> v;
  for (int i = 0; i < 9; ++i) {
    v.push_back('a' + i);
  }
  //产生字母到数字的随机映射
  std::map<char, int> hash_map;
  for (int i = 1; i <= 9; ++i) {
    int r = random(0, v.size() - 1);
    char k = v[r];
    v.erase(v.begin() + r);
    hash_map[k] = i;
  }

  for (int row = 0; row < _max_column; ++row) {
    for (int column = 0; column < _max_column; ++column) {
      point_t point = {row, column};
      char key = map_pattern[row][column];
      setValue(point, hash_map[key]);
    }
  }
  assert(isComplete());
  return;
}

bool CScene::setPointValue(const point_t &stPoint, const int nValue) {
  auto point = _map[stPoint.x + stPoint.y * 9];
  if (EACCES == point.state) {
    _cur_point = stPoint;
    setValue(nValue);
    return true;
  } else {
    return false;
  }
}

point_t CScene::getCurPoint() { return _cur_point; }