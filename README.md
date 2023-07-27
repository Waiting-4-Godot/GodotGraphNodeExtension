# GraphExtension

对GraphEdit和GraphNode这两个节点的拓展

看完 GraphEdit 和 GraphNode 这两个节点的文档发现虽然每一个端口都有类型但是却并没有设置值的功能
在连接端口时仅仅只是将其连接起来，由于端口中没有值所以就更不谈将输出端口的值传给与其
连接的输入端口。

所以目前想要实现传值的话要自己对这两个节点进行拓展。

不过官方打算在之后的版本中对GraphEdit和GraphNode进行重构, 不知道会变成什么样。

使用指南：
1. 下载 godot-cpp 4.1 的分支，并使用 MSVC 编译成静态库
2. 修改 CMakeLists.txt 中的相关配置，将库路径换成自己的
3. 编译
4. 使用 Godot 4.1 打开 project.godot
