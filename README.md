# StudentInformationManager
学生信息管理器 (取这个名字是当初以为还要做寝室信息以外的东西.
A large "hellow world" application, which gulp a bunch of memery of 7 Poke*on first generation(128k).
成果就是这个大型　"hellow world"　程序，一打开就直接吃掉７个宝＊梦无印(128k).(以msvc编译,打开后911k)
使用前请在程序所在位置创建一个si.txt(如果没有的话

实现了:
增添,修改删除,根据学生号/名字/寝室楼+门牌号查询室友.(以及文件读写

CAP实现了A(reads and writes always succeed)
ACID实现了ACD
(我才没有在对一个本地数据库在套分布式数据库的特点

打算做:
垃圾代码优化(比如把modify()和add合在一起
交互人性化(比如每次要求输入的时候, 都可以直接反悔, 不作出修改
把stdio.h依赖去掉
以XML文件读写
数据持久化
实现快速排列(Quicksort)
排列数据为B+树,以方便查询
以及其他饼
(在做了在做了我羽中哥哥什么时候骗过你.jpg

一些解释：

结构体 *Stu:
包含id号(int类型), 名字(char[16]), 性别(char), 寝室楼(int), 门牌号(int), 下一个*Stu的地址(ptr)
通过指向下一个Stu的指针实现了单向列表,实现的非常C(而不是C++

打印室友:
通过所给的寝室成员打印他的室友
在main()里实现的比较别扭:
面试官:那么是怎么找他的室友的?
我:当然是双循环啦!
面试官:下一个面试者请进.
不过以后实现了排列后就能不用双循环了(画饼中

用户交互:
到目前为止,用户都不能在输入信息的时候放弃输入,返回上级
以后可以把void modify(...)成int modify(Stu *p,int attribute)来决定到底改那一项属性
这样就可以在修改之前问一下用户需不需要返回上级

待增添...

其它:
对一个问题的歧义埋了一个彩蛋
