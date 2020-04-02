# CocoTech

## 1. [设计模式学习](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#1%E5%B8%B8%E8%A7%81%E7%9A%84%E4%B8%89%E7%A7%8D%E6%9C%80%E5%9F%BA%E6%9C%AC%E7%9A%84%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F)

### 1.1 [创建模式](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#2%E8%AF%A6%E7%BB%86%E7%9A%84%E6%A8%A1%E5%BC%8F%E4%BB%8B%E7%BB%8D)

提供实例化的方法，为适合的情况提供相应的创建方法。

- [Factory Method (工厂方法)](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#1-factory-method-%E5%B7%A5%E5%8E%82%E6%96%B9%E6%B3%95)
- [Abstract Factory (抽象工厂)](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#2-abstract-factory-%E6%8A%BD%E8%B1%A1%E5%B7%A5%E5%8E%82)
- [Builder (建造者)](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#3-builder-%E5%BB%BA%E9%80%A0%E8%80%85)
- [Prototype (原型)](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#4-prototype-%E5%8E%9F%E5%9E%8B)
- [Singleton (单例)](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#5-singleton-%E5%8D%95%E4%BE%8B)

### 1.2 [结构化模式](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#22-%E7%BB%93%E6%9E%84%E5%9E%8B)

用于处理实体之间的关系，使得这些实体可以更好的协同工作。

- [Adapter Class/Object (适配器)](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#6-adapter-classobject-%E9%80%82%E9%85%8D%E5%99%A8)
- [Bridge（桥接）](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#7-bridge-%E6%A1%A5%E6%8E%A5)
- [Composite（组合）](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#8-composite%E7%BB%84%E5%90%88)
- [Decorator（装饰）](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#9-decorator%E8%A3%85%E9%A5%B0%E5%99%A8)
- [Facade（外观）](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#10-facade-%E5%A4%96%E8%A7%82)
- [Flyweight（享元）](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#11-flyweight-%E4%BA%AB%E5%85%83)
- [Proxy（代理）](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#12-proxy-%E4%BB%A3%E7%90%86)　

### 1.3 行为模式

用于不同的实体进行通信，为实体之间的通信提供更容易、更灵活的通信方法。

- [Interpreter（解释器）](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#13-interpreter-%E8%A7%A3%E6%9E%90%E5%99%A8)
- [Template Method（模板方法）](https://github.com/Aurelius84/CocoTech/tree/master/design_patterns#14-template-method-%E6%A8%A1%E6%9D%BF%E6%96%B9%E6%B3%95)
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

### 2.1 [数独游戏](https://github.com/Aurelius84/CocoTech/tree/master/cpp/sudoku#%E9%A1%B9%E7%9B%AE%E7%BB%93%E6%9E%84)

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
