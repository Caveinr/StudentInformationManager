# StudentInformationManager
学生信息管理器 (取这个名字是当初以为还要做寝室信息以外的东西.

成果就是这个大型　"hello world"　程序.

使用前请在程序所在位置创建一个si.txt(如果没有的话

__实现了:__

增添,修改删除,根据学生号/名字/寝室楼+门牌号查询室友.(以及文件读写

__打算做:__

已完成//垃圾代码优化(比如把modify()和add合在一起

交互人性化(比如每次要求输入的时候, 都可以直接反悔, 不作出修改

已完成//把stdio.h依赖去掉(项目最开始是用C写的, 后来重构了几次, 但有些用起来实在顺手而且细枝末节的东西就懒得改了

以XML文件读写

数据持久化

实现快速排列(Quicksort)

排列数据为B+树,以方便查询

以及其他饼

(在做了在做了我羽中哥哥什么时候骗过你.jpg

 __不打算做:__
 
 根据规定顺序确定当天执勤人员:  能做, 要加东西, 虽说不多但再用C++写的话我要疯了

___一些碎碎念：___

__结构体 *Stu:__

包含id号(int类型), 名字(char[16]), 性别(char), 寝室楼(int), 门牌号(int), 下一个*Stu的地址(ptr)

通过指向下一个Stu的指针实现了单向链表

__打印室友:__

通过所给的寝室成员打印他的室友

在main()里实现的比较别扭

面试官:那么是怎么找他的室友的?

我:那简单, 当然是双循环啦!

面试官:下一个面试者请进.

不过以后实现了排列后就能不用双循环了(画饼中

__用户交互:__

到目前为止,用户都不能在输入信息的时候放弃输入,返回上级

已实现//以后可以把void modify(...)成int modify(Stu *p,int attribute)来决定到底改那一项属性

大概已实现//这样就可以在修改之前问一下用户需不需要返回上级

基本上每次要求用户输入都做了合法性检查

__代码质量:__

由于是第一次这么折腾链表, 尽量保证现在程序里无内存泄漏的情况

不知道如何对这堆*做评价, 但还是保证遵循了代码书写规范,尽量满足了风格一致( 后来换到vs2017,它的自动缩进和我的习惯不大一样

__代码可移植性:__
没有实现全平台可编译( 不知道怎么在不同linux发行版里引用io.h

(看着python哭了为啥我当初想不通要用C++开坑

# 其它:

待增添...

对一个问题的歧义回答埋了一个彩蛋
