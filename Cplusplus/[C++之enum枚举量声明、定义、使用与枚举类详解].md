#  [C++之enum枚举量声明、定义、使用与枚举类详解]

#### (https://blog.csdn.net/Bruce_0712/article/details/54984371)

 众所周知，C/C++语言可以使用#define和const创建符号常量，而使用enum工具不仅能够创建符号常量，还能定义新的数据类型，但是必须按照一定的规则进行，下面我们一起看下enum的使用方法。

步骤(一)——枚举量的声明和定义

(1)首先，请看下面的语句：

*enum enumType {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};*

这句话有两个作用：

第一：声明enumType为新的数据类型，称为**枚举**(enumeration);

第二：声明Monday、Tuesday等为符号常量，通常称之为**枚举量**，其值默认分别为0-6。（后面会介绍怎样显式的初始化**枚举量**的值）

(2)接着利用新的枚举类型enumType声明这种类型的变量：*enumType Weekday'*就像使用基本变量类型int声明变量一样，如 *int a;*也可以在定义枚举类型时定义枚举变量*enum enumType {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday}Weekday;*

然而与基本变量类型不同的地方是，**在不进行强制转换的前提下**，只能将定义的**枚举量**赋值给该种枚举的变量，如：*Weekday = Monday;*或者Weekday = Sunday;不能将其他值赋给**枚举变量**，如：Weekday = 10;这是不允许的，因为10不是**枚举量**。也就是说Weekday只能是定义的Monday-Sunday这些定义过的**枚举量**。然而这不是绝对的，第六条会讲到利用强制类型转换将其他类型值赋给**枚举变量**。

(3)上面讲不能将**非枚举量**赋给**枚举变量**，那么能不能将**枚举量**赋给**非枚举变量**呢？如：int a=Monday;这是允许的，因为**枚举量**是符号常量，这里的赋值编译器会自动把**枚举量**转换为int类型。

(4)前面讲可以对枚举进行赋值运算，那**枚举变量**能不能进行算术运算呢？

*Weekday++;*Weekday = Monday + Tuesday;这是非法的，因为这些操作可能导致违反类型限制，比如：Weekday = Sunday;

*Weekday++;*Weekday首先被赋予**枚举量**中的最后一个值Sunday(值为6)，再进行递增的话，Weekday增加到7，而对于enumType类型来说，7是无效的。

**总结：对于枚举，只定义了赋值运算符，没有为枚举定义算术运算。**

(5)不能对枚举量进行算术运算，那么枚举量能不能参与其他类型变量的运算呢？int a;a = 1 + Monday;这是允许的，因为编译器会自动把枚举量转换为int类型。

(6)第二条讲：在不进行强制转换的前提下，只能将定义的枚举量赋值给该种枚举的变量，言下之意就是可以通过强制转换将其他类型值赋给枚举变量：

*Weekday = enumType(2);*等同于：Weekday = Wednesday;但是，如果试图将一个超出枚举取值范围的值通过强制转换赋给枚举变量，会出现什么结果？

*Weekday = enumType(20);*结果将是不确定的，这么做不会出错，但得不到想要的结果。

## 步骤(二)——自定义枚举量的值

(1)前面讲通过定义enum enumType {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

**枚举量**Monday、Tuesday等的值默认分别为0-6，我们可以显式的设置**枚举量**的值：

*enum enumType {Monday=1, Tuesday=2, Wednesday=3, Thursday=4, Friday=5, Saturday=6, Sunday=7};*

指定的值必须是**整数**！

(2)也可以只显式的定义一部分**枚举量**的值：

*enum enumType {Monday=1, Tuesday, Wednesday=1, Thursday, Friday, Saturday, Sunday};*这样Monday、Wednesday均被定义为1，则Tuesday=2，Thursday、Friday、Saturday、Sunday的值默认分别为2、3、4、5.总结：未被初始化的枚举值的值默认将比其前面的枚举值大1。

(3)第二条还说明另外一个现象，就是

枚举量的值可以相同。

## 步骤(三)——枚举的取值范围

前面讲到可以通过强制转换将其他类型值赋给**枚举变量：**Weekday = enumType(2);这是合法的；但是Weekday = enumType(20);是非法的。这里涉及**枚举取值范围**的概念：枚举的上限是 大于最大**枚举量**的 最小的2的幂，减去1；

枚举的下限有两种情况：一、**枚举量**的最小值不小于0，则枚举下限取0；二、**枚举量**的最小值小于0，则枚举下限是 小于最小**枚举量**的 最大的2的幂，加上1。

举例来讲：

假如定义 *enum enumType1 { First=-5，Second=14，Third=10 };*则枚举的上限是16-1=15（16大于最大**枚举量**14，且为2的幂）；  枚举的下限是-8+1=-7（-8小于最小**枚举量**-5，且为2的幂）；

## 步骤(四)——枚举应用

个人觉得**枚举**和**switch**是最好的搭档：*enum enumType{Step0, Step1, Step2}Step=Step0;*//注意这里在声明枚举的时候直接定义了枚举变量Step,并初始化为Step0

*switch (Step)*

*{*

*  case Step0:{...;break;}*


*  case Step1:{...;break;}*


*  case Step2:{...;break;}*


*  default:break;*

*}*

另外枚举还有一种少见的用法是 enum { one ,two ,three};  就是不指定一个名字,这样我们自然也没法去定义一些枚举类型了。此时就相当于static const int one = 0;这样定义三个常量一样。然后用的话就是int no = one。

————————————————————————————————————————————————————————

## 一、简述

  强类型枚举（Strongly-typed enums），号称枚举类型，是C++11中的新语法，用以解决传统C++枚举类型存在的缺陷。传统C++中枚举常量被暴漏在外层作用域中，这样若是同一作用域下有两个不同的枚举类型，但含有相同的枚举常量也是不可的，比如：

```
enum Side{Right,Left};
enum Thing{Wrong,Right};
```

这是不能一起用的。 
  另外一个缺陷是传统枚举值总是被隐式转换为整形，用户无法自定义类型。C++11中的强类型枚举解决了这些问题。

————————————————————————— 

## 二、强类型枚举

  强类型枚举使用enum class语法来声明，如下：

```
enum class Enumeration{
 VAL1,
 VAL2,
 VAL3=100,
 VAL4
};
```

这样，枚举类型时安全的，枚举值也不会被隐式转换为整数，无法和整数数值比较，比如（Enumeration：：VAL4==10会触发编译错误）。

 另外枚举类型所使用的类型默认为int类型，也可指定其他类型，比如：

```
enum calss Enum:unsigned int{VAL1,VAL2};
```

正如前面所说，强类型枚举能解决传统枚举不同枚举类下同枚举值名的问题，使用枚举类型的枚举名时，必须指明所属范围，比如：Enum::VAL1，而单独的VAL1则不再具有意义。

还有一点值得说明的是C++11中枚举类型的前置声明也是可行的，比如：

```
enum calss Enum;
enum class Enum1:unsigned int;
```

—————————————————————————

 

## 三、项目中的强类型枚举代码片段

## 1、图像处理

```
enum class Color{RED,BLUE,YELLOR,BLACK,WHITE};
```

## 2.交通灯

```
enum class TrafficLight{RED,YELLOR,GREEN};
```

强类型枚举值具有传统枚举的功能——命名枚举值，同时又具有类的特点——具有类域的成员和无法进行默认的类型转换。所以也称之为枚举类——enmu class

枚举类的底层数据必须是有符号或无符号整型，比如char unsigned int unsigned long，默认为int。

## 3.前置声明应用

```
enmu class Clolor:char;  //前置声明枚举类
void Foo(Color*p);        //前置声明的使用
//....................
enum class Color:char{RED,GREEN,BLACK,WHITE};                       //前置声明的定义
```
