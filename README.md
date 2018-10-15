-个人总结和搜集的计算机专业知识

## git 

在仓库上创建分支之后，  
git clone $(仓库地址)  
或者 git pull  

git branch -va 查看所有分支  
git checkout -b $(分支名) 切换分支  
git add.   
git commit -m 'm'  
git push  
上述操作可以更新分支上的代码：  


拉取远程master分支代码到本地并merge  
git pull origin master


## git: please tell me who you are
1.git init
2.git config user.name "someone"
3.git config user.email "someone@someplace.com"

## git其他有用指令
git status //查看当前代码状态，改动，所在分支，当前状态有没有代码冲突等
git branch -a //查看当前主干下有哪些分支
git checkout //切换分支
git pull origin //更新当前指向的分支，当前分支与远程分支已经存在追踪关系
git diff //查看分支代码改动
git merge dev1  //合并最新分支到本地分支
git branch -D dev1 //删除本地分支dev1


进度表

10-15 ~ 10-21 阅读相关文献：a.软件工程方法论-基础篇a b.软件工程方法论-分析篇a c.软件工程方法论-设计篇a  
10-22 ~ 10-28 上周任务总结，基于此进行需求分析，分配工作，建立需求模型  
10-29 ~ 11-4 建立基本模型  
11-5 ~ 11-11 建立辅助模型，整合OOA过程  
11-12 ~ 11-18 开始OOD过程分析，问题域部分设计  
11-19 ~ 11-23 人机交互部分设计 控制驱动部分设计 数据接口部分设计  
11-23 ~       确定开发内容，分配工作，原型开发   
