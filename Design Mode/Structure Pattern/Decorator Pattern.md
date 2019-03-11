## Decorator Pattern

There are two ways to add behavior to a class or object:

Inheritance mechanism. Using inheritance mechanism is an effective way to add functions to existing classes. By inheriting an existing class, subclasses can have both their own methods and the methods of the parent class.But this approach is static, and the user has no control over how and when to add behavior.

Decorators are decorators in which an object of a class is embedded in another object, and the other object decides whether to call the behavior of the embedded object in order to extend its behavior.

The decorator pattern dynamically attaches more responsibility to an object in a way that is transparent to the client; in other words, the client does not perceive the object to be different before and after the decoration.The decorator pattern extends the functionality of an object without creating more subclasses.This is the pattern motivation of the decorative pattern.

Decorator Pattern: dynamically add some additional Responsibility to an object. Decorator Pattern is more flexible than subclassing an implementation in terms of adding object functionality.The aliases, which can also be called wrappers, are the same as the aliases for the adapter pattern, but they are suitable for different situations.Depending on the translation, the decoration pattern is also known as the "painter pattern," which is an object structure pattern.

![Decorator](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/Decorator.jpg?raw=true)

![seq_Decorator](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/seq_Decorator.jpg?raw=true)

```C++

#include <iostream>
#include <string>
using namespace std;
//定义各商品的价格
const int ESPRESSO_PRICE = 25;
const int DRAKROAST_PRICE = 20;
const int MOCHA_PRICE = 10;
const int WHIP_PRICE = 8;
 
class Beverage{//饮料
protected:
	string description;
public:
	virtual string getDescription(){//这里virtual不能省，不然找不到上一级的Beverage的了
		return description;
	}
	virtual int cost()=0;
};
 
class CondimentDecorator : public Beverage{//配料
protected:
	Beverage *beverage;//这个指针，用于回溯之前已经存在的内容
};
 
//两种咖啡，其构造函数皆没有Beverage *beverage;也就是说，这两个类只能作为基础，不能作为叠加上去的配件。
class Espresso : public Beverage{//蒸馏咖啡
public:
	Espresso(){
		description="Espresso"; 
	}
	int cost(){
		return ESPRESSO_PRICE;
	}
};
class DarkRoast : public Beverage {//深度烘焙咖啡
public:
	DarkRoast(){ 
		description = "DardRoast"; 
	}
	int cost(){ 
		return DRAKROAST_PRICE; 
	}
};
 
//对比起上述两种“基类”，这两种东西构造函数皆存在Beverage *beverage;（Beverage *beverage;的声明源于对CondimentDecorator这个类的继承），其可以叠加
class Mocha : public CondimentDecorator {//摩卡
public:
	Mocha(Beverage* beverage){ 
		this->beverage=beverage; 
	}
	string getDescription(){ 
		return beverage->getDescription()+",Mocha"; 
	}
	int cost(){ 
		return MOCHA_PRICE+beverage->cost(); 
	}
};
 
 
class Whip :public CondimentDecorator {//奶泡
public:
	Whip(Beverage* beverage){
		this->beverage=beverage; 
	}
	string getDescription() {
		return beverage->getDescription()+",Whip"; 
	}
	int cost() { 
		return WHIP_PRICE+beverage->cost(); 
	}
};
 
//主函数
int main() {
	Beverage* beverage = new DarkRoast();
	beverage=new Mocha(beverage);
	beverage=new Whip(beverage);
	cout<<beverage->getDescription()<<"￥"<<beverage->cost()<<endl;
	return 0;
}
```

