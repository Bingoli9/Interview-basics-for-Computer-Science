### Queue适配器

queue使用list或deque容器实现，默认情况下使用dequeue实现。

### Priority_queue适配器

使用STL序列容器vector和dequeue实现，默认是vector作为底层容器。

使用堆排序实现优先队列。

priority_queue的通常操作包括在priority_queue的适当位置插入元素的push（实现是调用底层容器的push_back函数，然后使用heapsort算法重新排序)， 从priority_queue中删除最高优先级元素的pop，获得顶端元素引用的top。

使用：

```
std::priority_queue<T> pq;
std::priority_queue<T, std::vector<T>, cmp> pq;
```

优先级定义：

priority_queue<vector<int>, less<int> > pq1; 　　　 // 使用递增less<int>函数对象排序
priority_queue<deque<int>, greater<int> > pq2; 　　// 使用递减greater<int>函数对象排序

```
priority_queue<int> q;   　　　　　　　　　　　　  //通过操作，按照元素从大到小的顺序出队
priority_queue<int,vector<int>, greater<int> > q;  　　//通过操作，按照元素从小到大的顺序出队
```

```c++
struct cmp {     
　　operator bool ()(int x, int y)     
　　{        
　　　　 return　x > y;　　 // x小的优先级高       
       //也可以写成其他方式，如： return p[x] > p[y];表示p[i]小的优先级高
　　}
};
```

```c++
/*优先队列的基本使用    2017/8/1    xzxl*/ 
#include<stdio.h> 
#include<functional> 
#include<queue> 
#include<vector> 
using namespace std; 
//定义结构，使用运算符重载,自定义优先级1 
struct cmp1{ 
    bool operator ()(int &a,int &b){ 
        return a>b;//最小值优先 
    } 
}; 
struct cmp2{ 
    bool operator ()(int &a,int &b){ 
        return a<b;//最大值优先 
    } 
}; 
//定义结构，使用运算符重载,自定义优先级2 
struct number1{ 
    int x; 
    bool operator < (const number1 &a) const { 
        return x>a.x;//最小值优先 
    } 
}; 
struct number2{ 
    int x; 
    bool operator < (const number2 &a) const { 
        return x<a.x;//最大值优先 
    } 
}; 
int a[]={14,10,56,7,83,22,36,91,3,47,72,0}; 
number1 num1[]={14,10,56,7,83,22,36,91,3,47,72,0}; 
number2 num2[]={14,10,56,7,83,22,36,91,3,47,72,0}; 
   
int main() 
{   priority_queue<int>que;//采用默认优先级构造队列 
   
    priority_queue<int,vector<int>,cmp1>que1;//最小值优先 
    priority_queue<int,vector<int>,cmp2>que2;//最大值优先 
   
    priority_queue<int,vector<int>,greater<int> >que3;//注意“>>”会被认为错误， 
                                                      //这是右移运算符，所以这里用空格号隔开 
    priority_queue<int,vector<int>,less<int> >que4;////最大值优先 
   
    priority_queue<number1>que5; 
    priority_queue<number2>que6; 
   
    int i; 
    for(i=0;a[i];i++){ 
        que.push(a[i]); 
        que1.push(a[i]); 
        que2.push(a[i]); 
        que3.push(a[i]); 
        que4.push(a[i]); 
    } 
    for(i=0;num1[i].x;i++) 
        que5.push(num1[i]); 
    for(i=0;num2[i].x;i++) 
        que6.push(num2[i]); 
   
   
    printf("采用默认优先关系:\n(priority_queue<int>que;)\n"); 
    printf("Queue 0:\n"); 
    while(!que.empty()){ 
        printf("%3d",que.top()); 
        que.pop(); 
    } 
    puts(""); 
    puts(""); 
   
    printf("采用结构体自定义优先级方式一:\n(priority_queue<int,vector<int>,cmp>que;)\n"); 
    printf("Queue 1:\n"); 
    while(!que1.empty()){ 
        printf("%3d",que1.top()); 
        que1.pop(); 
    } 
    puts(""); 
    printf("Queue 2:\n"); 
    while(!que2.empty()){ 
        printf("%3d",que2.top()); 
        que2.pop(); 
    } 
    puts(""); 
    puts(""); 
    printf("采用头文件\"functional\"内定义优先级:\n(priority_queue<int,vector<int>,greater<int>/less<int> >que;)\n"); 
    printf("Queue 3:\n"); 
    while(!que3.empty()){ 
        printf("%3d",que3.top()); 
        que3.pop(); 
    } 
    puts(""); 
    printf("Queue 4:\n"); 
    while(!que4.empty()){ 
        printf("%3d",que4.top()); 
        que4.pop(); 
    } 
    puts(""); 
    puts(""); 
    printf("采用结构体自定义优先级方式二:\n(priority_queue<number>que)\n"); 
    printf("Queue 5:\n"); 
    while(!que5.empty()){ 
        printf("%3d",que5.top()); 
        que5.pop(); 
    } 
    puts(""); 
    printf("Queue 6:\n"); 
    while(!que6.empty()){ 
        printf("%3d",que6.top()); 
        que6.pop(); 
    } 
    puts(""); 
    return 0; 
} 
/*
运行结果 ：
采用默认优先关系:
(priority_queue<int>que;)
Queue 0:
83 72 56 47 36 22 14 10  7  3
  
采用结构体自定义优先级方式一:
(priority_queue<int,vector<int>,cmp>que;)
Queue 1:
 7 10 14 22 36 47 56 72 83 91
Queue 2:
83 72 56 47 36 22 14 10  7  3
  
采用头文件"functional"内定义优先级:
(priority_queue<int,vector<int>,greater<int>/less<int> >que;)
Queue 3:
 7 10 14 22 36 47 56 72 83 91
Queue 4:
83 72 56 47 36 22 14 10  7  3
  
采用结构体自定义优先级方式二:
(priority_queue<number>que)
Queue 5:
 7 10 14 22 36 47 56 72 83 91
Queue 6:
83 72 56 47 36 22 14 10  7  3
*/ 
```

