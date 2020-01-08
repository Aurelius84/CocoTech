#### std::deque

`deque`（双端队列）是一种支持索引的序列容器，允许在两端高效的插入和删除。插入或删除元素时，不会影响其他元素的指针和元素的使用。

相对于`std::vector`而言，`deque`中的元素并非连续存储，而是使用了一个固定大小`Array`的序列（sequence）来保存元素数据——这意味着利用下标索引队列中元素时，需要两次解引用操作，而`std::vector`中只需要一次。

`deque`也支持自动扩容，其扩容的代价要小于`std::vector`。因为`deque`扩容时没有元素重新拷贝到新地址的代价。

需要注意，`deque`具有较大的最小内存消耗。对于只包含一个元素的`deque`也必须申请内部全部`Array`内存（如在64位libstdc++中是8乘以object size；在64位libc++中更大，为18乘以object size8或4096 ）

`deque`的复杂度如下：

+ 随机访问：`O(1)`

+ 两端的插入或删除：`O(1)`

+ 中间的插入或删除：`O(n)`

**Example:**

```cpp
#include <iostream>
#include <deque>

int main()
{
    // Create a deque containing integers
    std::deque<int> d = {7, 5, 16, 8};

    // Add an integer to the beginning and end of the deque
    d.push_front(13);
    d.push_back(25);

    // Iterate and print values of deque
    for(int n : d) {
        std::cout << n << '\n';
    }
}
```

**Output:**

```cpp
13
7
5
16
8
25
```

翻译自：[https://devdocs.io/cpp/container/deque](https://devdocs.io/cpp/container/deque)
