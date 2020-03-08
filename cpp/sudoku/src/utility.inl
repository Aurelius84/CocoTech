#include <cstdlib>
#include <assert.h>
#include <time.h>

#include <iostream>

inline unsigned int random(int begin, int end){
  assert(end >= begin && begin >= 0);
  srand(time(NULL));
  return static_cast<unsigned int>(rand() % (end - begin + 1) + begin);
}

inline void cls(void) {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

#ifdef _WIN32
#include <conio.h>
#elif __APPLE__
#include <termios.h>
#include <cstdio>
inline char getch() {
  struct termios tmtemp, tm;
  char c;
  int fd = 0;
  if (tcgetattr(fd, &tm) != 0) {
    // 获取当前的终端属性设置，并保存到tm结构体中
    return -1;
  }

  tmtemp = tm;
  // 将tetemp初始化为终端原始模式的属性设置
  cfmakeraw(&tmtemp);
  if (tcsetattr(fd, TCSANOW, &tmtemp) != 0) {
    //将终端设置为原始模式的设置
    return -1;
  }

  c = getchar();
  if (tcsetattr(fd, TCSANOW, &tm) != 0) {
    //接收字符完毕后将终端设置回原来的属性
    return 0;
  }
  return c;
}
#endif