#### 1. 线程与数据竞争
*****

首先，我们先了解一下**线程与数据竞争**的概念：

程序中的控制流是执行线程，开始于`std::thread::thread`或`std::async`或者顶层函数调用。

任何线程具有访问程序中对象的潜在权限。拥有自动或者线程存储期的对象，仍然可能被另一程序通过指针或引用进行访问。

当某个表达式的求值写入到某个内存位置，而另一个表达式读或者写同一位置的值时，则称**表达式冲突**。拥有两个求值冲突的表达式就产生了数据竞争，除非：

+ 两个求值都在同一个线程上，或在同一个信号处理函数中执行
+ 两个冲突的求值都是原子操作(见 `std::atomic`)
+ 一个冲突的求值(happens-before)另一个(见`std::memory_order`)

若出现数据竞争，则程序行为未定义。(可以借助`std::mutex`的释放同步，其发生早于另一线程对同一mutex的获取，可以用互斥锁来防止数据竞争。)

```cpp
int cnt = 0;
auto f = [&]{cnt++}
std::thread t1{f}, t2{f}, t3{f}; // 未定义行为
```

```cpp
std::atomic<int> cnt{0};
auto f = [&]{cnt++};
std::thread t1{f}, t2{f}, t3{f}; // OK
```

#### 2.std::atomic
****

如上述代码样例，每个`std::atomic`的模板实例化和全特化定义一个原子类型。若一个线程写入对象，同时另一个线程从它读取，则行为良好定义。

另外，对原子对象的访问，可以建立线程间同步，并按照`std::memory_order`对非原子内存访问定序。

**`std::atomic`既不可复制，也不可移动。**

#### 3. 特化
对整数类型的特化，对下列整数类型之一进行实例化时，`std::atomic`提供适合于整数类型的额外操作，如`fetch_add`、`fetch_sub`、`fetch_and`、`fetch_or`、`fetch_xor`。

- 字符型`char`，`char8_t`，`char16_t`，`char32_t`和`wchar_t`
- 标准有符号整型`signed char`，`short，int`，`long`，和`long long`
- 标准无符号整型`unsigned char`，`unsigned short`，`unsigned int`，`unsigned long`，和`unsigned long long`
- 任何\<cstdint\>中`typedef`所需的额外整型

#### 4. 成员函数
****
`is_lock_free`: 检查原子对象是否免锁

`store`: 原子地以非原子对象替换原子对象

`load`: 原子地获取对象

`exchange`:原子地替换原子对象的值，并返回之前的值



#### 5.参考
+ https://zh.cppreference.com/w/cpp/atomic/atomic