## alias

```C++
alias格式:alias name text
在text中要得到用户传递的参数可以使用以下方式
/!:1    表示第1个参数
/!:2*  表示第2个及余下的所有参数
/!*      表示所有参数
如:alias test_val '@ z = (/!*) ;echo $z'
test_var  1 + 1
得到2

下面的alias将实现"查出用户名为xddai的名为用户传递参数的所有进程号,并传递给kill,将其kill掉"
alias mykill    'ps -u xddai | grep /!:1 | awk' "'"'{print $1}'"'|xargs kill"
如使用mykill java可以kill掉用户名为xddai的所有java进程
注意:单引号'内的字符串不会为shell解释掉,也就是说$1不会变成空,这样实实际的命令变成
ps -u xddai | grep !:1 | awk '{print $1}'|xargs kill
```
