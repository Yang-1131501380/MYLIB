初始化

git init

添加

git add .

提交

git commit -m "first commit"

输入地址

git remote add origin 粘贴地址（最好使用SSH地址）

推送

git push -u origin master



问题点：

1.nothing to commit, working tree clean工作库很干净

解决：将文件夹里要上传的文件剪切到别的地方，然后再添加进去。或者直接修改当前文件。

2.fatal: remote origin already exists已存在远程源

删除远程已存在的来源

查看远程源

git remote -v

删除它，比如查看后的远程源名字叫做origin，则

git remote remove origin
