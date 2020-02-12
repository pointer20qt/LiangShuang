# signSystem签到系统



# GIT操作

## 在邮件中确认邀请

老师创建小组后，在注册GitHub的邮箱中会收到这样一封邮件，Join即可


## 在所在工程中添加自己的仓库

点击 new 创建属于自己的仓库 
创建完成后要使用连接


## 本地操作

在你要使用Git上传到Github的目录下右键，选择Git GUI Here



```nginx
git config --global user.name"你的用户名"
git config --global user.email"你注册的邮箱"
git config --list  #查看信息
```



``` nginx
echo "# signSystem" >> README.md
git init    #初始化本地版本库

add README.md #创建说明文档    
git add . #添加所有改动过的文件，在本次操作中相当于添加该目录下所有文件

git commit -m "commit message"  #提交所有更新过的文件

git remote add origin https://github.com/pointer20qt/......
#连接远程仓库

git push -u origin master
#运行 git push origin master 来推送本地更改到在线仓库
```

