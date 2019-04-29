-个人总结和搜集的计算机专业知识

## git 

在仓库上创建分支之后，  
git clone $(仓库地址)   
或者 git pull  

git branch -va 查看所有分支  
git checkout -b $(分支名) 切换分支  
git checkout $(分支名) 切换分支
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

## 版本冲突
冲突保留本地
1.git stash  
2.git pull  
3.git stash pop  
## git其他有用指令
git status //查看当前代码状态，改动，所在分支，当前状态有没有代码冲突等  
git branch -a //查看当前主干下有哪些分支  
git checkout //切换分支  
git pull origin //更新当前指向的分支，当前分支与远程分支已经存在追踪关系  
git diff //查看分支代码改动  
git merge dev1  //合并最新分支到本地分支  
git branch -D dev1 //删除本地分支dev1  

## git merge
git merge [branch1][branch2]  
git merge [branch] 将branch合并到当前分支  

## git pull
git pull  = git fetch + git merge

## git branch
git branch [branch_name] 创建本地分支
git push origin [branch_name] 创建远程分支
git push origin :[branch_name] 删除远程分支
git branch -d [branch_name] 删除本地分支

## git回滚
撤掉add git reset HEAD  
撤掉commit git reset HEAD^  

git fetch -all
git reset --hard
git rm -rf --cache $(文件名)

<center>
    <img src="https://img-blog.csdn.net/20171209154436088?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZ2FpYmlhbjA4MjM=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast"/>
</center>


<center>
    <img src="https://img-blog.csdn.net/20171209154531188?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZ2FpYmlhbjA4MjM=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast"/>
</center>


## 将本地branch分支追踪远程分支
git branch --set-upstream branch-name origin/branch-name
## 将当前分支追踪到远程分支
git branch -u origin/serverfix
## 查看本地分支和远程分支关系
git branch -vv

