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

## git reflog
重返未来某个版本，需要记住commit号  

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


## HEAD
HEAD代表当前版本  

##  git reset --hard commitID
回退到某个版本，甚至可以未来版本  

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

## 合并本地分支
git merge

## git patch
使用git diff打补丁

git diff > patch //patch的命名是随意的，不加其他参数时作用是当我们希望将我们本仓库工作区的修改拷贝一份到其他机器上使用，但是修改的文件比较多，拷贝量比较大，此时我们可以将修改的代码做成补丁，之后在其他机器上对应目录下使用 git apply patch 将补丁打上即可 . 

git diff --cached > patch //是将我们暂存区与版本库的差异做成补丁 . 

git diff --HEAD > patch //是将工作区与版本库的差异做成补丁 . 

git diff Testfile > patch//将单个文件做成一个单独的补丁


## git cherry-pick

挑拣提交，它会获取某个分支的单笔提交，并作为一个新的提交引入到你当前分支上。当我们需要在本地何如其他分支的提交时，如果不想对整个分支进行合并，而是志向将某一次提交合入到当前分支上，那么就要使用git cherry-pick

```C++
git cherry-pick

--quit 退出当前cherry-pick序列
--continue 继续当前的cherry-pick序列
--abort 取消当前cherry-pick序列，恢复当前分支
-n 不自动提交
-e 编辑提交信息
```

## git tag

常用于版本发布

```C++
git tag #在控制台打印当前仓库所有标签
```

git标签分为两种类型：轻量标签和附注标签。轻量标签是指向对象的引用，附注标签则是仓库中的一个独立对象。建议使用附注标签



```C++
git tag v0.1.2-light #创建轻量标签
git tage -a v0.1.2 -m '0.1.2版本'  #创建附注标签
git tag -a v0.0.1 9fbc3d0  #补打标签
git checkout v.1.2 #切换到标签
git tag -d v0.1.2 #删除标签
git push origin v0.1.2	 #将标签提交到git 服务器
```



## git origin

origin指向远端代码仓库

如果远程仓库是dev，那么git push origin dev可以将本地仓库的修改push到远程服务器



## git merge diff
git merge --no-ff，这样无论如何都会产生一个新的 merge commit。然后你 git show <merge-commit-sha1> 就可以看到这次 merge 的所有改动。  
