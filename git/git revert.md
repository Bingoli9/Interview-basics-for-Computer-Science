## git revert

git revert撤销某次操作，此次操作之前和之后的commit都会被保留，并且会把这次撤销作为一次最新的提交：

```C++
git revert HEAD    #撤销前一次commit
git revert HEAD^   #撤销前前一次commit
```

git revert提交新版本，将需要revert的版本在反向修改回去；版本会递增，不影响之前的提交内容

git reset还原到指定版本上，这将扔掉指定版本之后的版本