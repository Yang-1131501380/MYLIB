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
首先，确保你已经用 `git add` 命令将更改添加到暂存区，然后使用 `git commit` 提交这些更改。’git add <changed_files> git commit -m "Your commit message" ‘ 然后 使用 `git push` 命令将你的提交推送到远程仓库。如果你是第一次推送到远程仓库的当前分支，或者你设置了上游分支，通常只需要’git push‘，如果你需要指定远程仓库和分支，可以使用’git push origin <branch-name>‘，如果在合并过程中出现冲突，你需要手动解决这些冲突，然后再次提交更改’git commit -m "Resolve merge conflicts" ‘， 解决完任何合并冲突后，你可以安全地再次推送你的更改’git push‘，推送完成后，检查 GitHub 上的仓库以确认你的更改已经更新。每次推送之前都应该确保你的本地更改已经提交，并且已经推送到了正确的分支。如果你不确定当前的状态，可以使用 `git status` 查看当前仓库的状态
