# CocoTech

## 1. 设计模式学习

### 1.1 创建模式

提供实例化的方法，为适合的情况提供相应的创建方法。

- Factory Method (工厂方法)
- Abstract Factory (抽象工厂)
- Builder (建造者)
- Prototype (原型)
- Singleton (单例)

### 1.2 结构化模式

用于处理实体之间的关系，使得这些实体可以更好的协同工作。

- Adapter Class/Object (适配器)
- Bridge（桥接）
- Composite（组合）
- Decorator（装饰）
- Facade（外观）
- Flyweight（享元）
- Proxy（代理）　

### 1.3 行为模式

用于不同的实体进行通信，为实体之间的通信提供更容易、更灵活的通信方法。

- Interpreter（解释器）
- Template Method（模板方法）
- Chain of Responsibility（责任链）
- Command（命令）
- Iterator（迭代器）
- Mediator（中介者）
- Memento（备忘录
- Observer（观察者
- State（状态）
- Strategy（策略）
- Visitor（访问者）

## 2. C++项目

### 2.1 数独游戏

一款简单的终端数独游戏，可以帮助快速入门C++，fork的其他开源的实现，以供学习（侵删）。

**项目目录：**

    ```
    │  .gitignore
    │  build.bat        // Windows 一键编译脚本
    │  build.sh         // Linux 一键编译脚本
    │  CMakeLists.txt   // CMake 项目文件
    │  README.md
    │
    └─src               //源代码目录
                    block.cpp   //数独格子组合类，可代表行、列、九宫格
                    block.h
                    color.h     //颜色类
                    command.cpp //命令类，实现了撤销功能
                    command.h
                    common.h    //公共头文件
                    input.cpp   //输入类
                    input.h
                    main.cpp    //入口文件
                    scene.cpp   //游戏场景类
                    scene.h
                    test.cpp    //测试文件
                    test.h
                    utility.inl //一些实用的全局函数
    ```
    
## 3. Linux系统学习


## 4. 算法进阶学习
