#include <iostream>
#include <string>
#include "common.h"
#include "utility.inl"

// 设置难度
int inputDifficulty() {
  cls();
  std::string cmd;
  while (1) {
    std::cout << "设置难度: 1.简单 2.普通 3.困难" << std::endl;

    std::cin >> cmd;

    int difficulty = atoi(cmd.c_str());

    switch (difficulty) {
      case EASY:
        return 20;
      case NORMAL:
        return 35;
      case HARD:
        return 50;
      default:
        std::cout << "输入错误" << std::endl;
        continue;
    }
  }
  return 0;
}