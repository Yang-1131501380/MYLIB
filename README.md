# Git 使用笔记  

初始化一个新的 Git 仓库：  
`git init`  

将文件添加到暂存区：  
`git add .`  

提交暂存区的更改：  
`git commit -m "first commit"`  

添加远程仓库地址（最好使用 SSH 地址）：  
`git remote add origin <粘贴地址>`  

将本地提交推送到远程仓库：  
`git push -u origin master`  

## 常见问题及解决方案  

1. **nothing to commit, working tree clean** - 工作区很干净，没有提交的更改。  
   **解决**: 将文件夹里要上传的文件剪切到别的地方，然后再添加进去，或者直接修改当前文件。  

2. **fatal: remote origin already exists** - 已存在远程源。  
   **解决**: 查看远程源：  
   `git remote -v`  
   删除它，比如查看后的远程源名字叫做 origin，则：  
   `git remote remove origin`  
## 第二次上传
确保你已经用 `git add` 命令将更改添加到暂存区，然后使用 `git commit` 提交这些更改：  
`git add <changed_files>`  
`git commit -m "Your commit message"`  

然后使用 `git push` 命令将你的提交推送到远程仓库。如果你是第一次推送到远程仓库的当前分支，或者你设置了上游分支，通常只需要：  
`git push`  
如果你需要指定远程仓库和分支，可以使用：  
`git push origin <branch-name>`  

如果在合并过程中出现冲突，你需要手动解决这些冲突，然后再次提交更改：  
`git commit -m "Resolve merge conflicts"`  
解决完任何合并冲突后，你可以安全地再次推送你的更改：  
`git push`  

推送完成后，检查 GitHub 上的仓库以确认你的更改已经更新。每次推送之前都应该确保你的本地更改已经提交，并且已经推送到了正确的分支。如果你不确定当前的状态，可以使用：  
`git status` 查看当前仓库的状态。
