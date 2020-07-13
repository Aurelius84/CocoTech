/*
* 描述：以O(n)的时间复杂度shuffle一个list
*/
#include <iostream>
#include <stdlib.h>
#include <time.h>

template <typename T>
static void shuffle(T* arr, int length) {
  srand(time(NULL));
  int i = length, j;
  T temp;
  if (i == 0) return;

  while (--i) { // i--也可以
    // 每次从[0, i]区间随机一个数
    j = rand() % (i + 1);
    // 将其和arr[i]交换
    if (i == j) continue;
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

int main()
{
  int arr[] = {1, 2, 3, 4, 5};
  shuffle(arr, 5);
  for (int i = 0; i < 5; i++){
    std::cout << arr[i] << " ";
  }
  return 0;
}