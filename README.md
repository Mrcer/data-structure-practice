# 数据结构实践

用于学习数据结构和积累大型项目开发经验的个人项目。
github:[https://github.com/Mrcer/data-structure-practice](https://github.com/Mrcer/data-structure-practice)
gitee:[https://gitee.com/mrcer/data-struct-practice](https://gitee.com/mrcer/data-struct-practice)
## 使用方式

该项目目前使用纯C++在VSCode开发，请预先安装好C++运行环境和VSCode，详细配置过程参见GZTime博客（工作目录环境已配置，如有需要请自行更改编译器路径）：  
[https://blog.gztime.cc/posts/2020/6b9b4626/](https://blog.gztime.cc/posts/2020/6b9b4626/)

所有cpp文件均应放在Source根目录下；所有数据结构和算法均应以`.hpp`形式保存在Include相应位置，且应把接口文件通过`include.h`暴露。

## 关于项目的使用

由于是个人学习项目，会发生频繁的项目重构。请不要pr，想基于代码开发或改进的fork就行了。有项目开发经验的大佬如果对项目有改进建议，欢迎issue，我会抽空学习。如果发现bug也可以提issue，我会抽空修。

## 已实现的数据结构或算法

1. `LinkedList`：链表实现的线性表
2. `Tree<T>`：基于`std::vector`实现的一般的树
3. `LinkedBinaryTree<T>`：链表实现的二叉树
4. `ArrayBinaryTree<T>`：基于`std::vector`实现的二叉树

## 待办事项

### 已知Bug
1. 目前无法多次引用`include.h`，因为有非模板实现`LinkedList`，这会在下次项目重构中修复

### 待实现功能
1. 哈夫曼树
2. ArrayList
3. 树的序列化和反序列化

### 项目相关
1. 使用cmake构建项目
2. 增加VS开发支持
3. 规范化注释
4. 系统测试模块
