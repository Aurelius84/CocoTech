### 项目结构：
```bash
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