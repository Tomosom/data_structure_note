question:
为什么c++中已经有了string类了，QT中还要实现QString类，MFC中还要实现CString类？QT和mfc中为何不直接使用string类？

answer by tzl:
C++自带一个标准库 STL  已经实现了string 处于std名称空间
但是历史上的STL只有标准  没有标准实现   对于代码移植性一直有影响
所以 各大厂商推出了自己库  微软有 MFC  开源有Qt   Borland有VCL  这些库都有自己的字符串类  没有为什么   都想自己的库尽善近全


实现自己的字符串类时的注意事项：
1.无缝实现String对象与char*字符串的互操作
2.操作符重载函数需要考虑是否支持const版本
3.用过C语言中的字符串函数实现String的成员函数
