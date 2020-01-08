#### std::unique_ptr

定义在头文件`<memory>`

```cpp
template<class T, class Deleter = std::default_delete<T>>
class unique_ptr;

template<class T, class Deleter>
class unique_ptr<T[], Deleter>;
```

`std::unique_ptr`是一个智能指针，其通过指针来持有和管理任意对象（object）。当其离开作用域（scope）时，`unique_ptr`会自动析构掉持有的对象。



在如下情况下，对象会被关联的`deleter`释放掉：

+ `unique_ptr`自身被销毁

+ `unique_ptr`自身通过`operator()`被赋值给其他指针，或调用了`reset()`函数。



持有的对象是通过调用`get_deleter()(ptr)`被释放，`get_deleter()`会得到用户指定的`deleter`或者默认的`deleter`。



`unique_ptr`可以持有空对象。目前有两个版本的`std::unique_ptr`:

+ 管理单一对象（如通过`new`关键词创建）

+ 管理一个动态申请的`array`数组（如通过`new[]`创建）



> 注：`Deleter`必须是函数对象（FunctionObject），或函数对象的左值引用，或函数（Function）的左值引用，并通过`unique_ptr<T, Deleter>::pointer`调用。



只有非常量的`unique_ptr`可以转移对象的管理权到另一个`unique_ptr`。如果一个对象被一个`const std::unique_ptr`来管理，则其被限制在创建`unique_ptr`时的`scope`内。



`std::unique_ptr`通常用来管理对象的生命周期，包括：

+ 为类和函数在处理动态生命周期的对象是，提供异常安全。通过在正常退出或者异常退出时释放对象。

+ 向函数中传递动态声明周期唯一对象的持有权

+ 从函数中获取动态声明周期唯一对象的持有权
