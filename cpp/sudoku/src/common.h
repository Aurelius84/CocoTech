// #ifndef _SUDOKU_COMMON_H_
// #define _SUDOKU_COMMON_H_
#pragma once

static const unsigned int UNSELECTED = 0;

enum difficulty_e { EASY = 1, NORMAL, HARD };

enum state_e { INITED = 0, ERASED };

typedef struct stPoint
{
  int x;
  int y;
} point_t;

typedef struct stPointValue
{
  int value;
  int state;
} point_value_t;

// #endif
