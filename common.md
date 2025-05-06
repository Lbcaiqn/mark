# 一、正则表达式

abc    匹配abc

若要匹配的字符是正则表达式内置的，则需要\转义，如 \+

1. 限定符
   
   | a?  | a出现0次或1次 |
   | --- | -------- |
   | a*  | a出现0次或多次 |
   | a+  | a出现1次或多次 |
   
   a{}，花括号的内容左闭右闭，可以是0，第一个参数不能省略
   
   | a{6}   | a出现6次    |
   | ------ | -------- |
   | a{2,6} | a出现2次到6次 |
   | a{3,}  | a出现3次及以上 |
   
   (ab)限定符    限定ab出现的次数
   
   贪婪匹配：正则表达式会默认尽可能多的字符
   
   懒惰匹配：限定正则表达式在能匹配成功时就结束匹配
   
   如匹配所有标签，结果如下：

| <.+>  | 贪婪匹配，从<html>一直匹配到</html>，即一直匹配到最后一个> |
| ----- | ------------------------------------ |
| <.+?> | 懒惰匹配，只匹配<标签>，即<到第一个>就结束匹配            |

   全部限定符的懒惰匹配：

| ??     | 若0个能复合结果就0个        |
| ------ | ------------------ |
| +?     | 若n个复合结果就n个         |
| *?     | 若n个复合结果就n个，比如1个就1个 |
| {2,6}? | 就可能向少的匹配，比如3个就3个   |

2. 或运算符
   
   | a\|b           | a或b         |
   |:-------------- | ----------- |
   | (ab)\|(cd)     | ab或cd       |
   | a (cat)\|(dog) | a cat或a dog |

3. 字符类（也叫原子表），中括号包裹
   
   原子表中   ()  .  +  就是普通的字符   ^是取反
   
   | [abc]       | a或b或c         |
   | ----------- | ------------- |
   | [a-c]       | 同上            |
   | [a-zA-Z0-9] | 大写或小写或数字      |
   | [^0-9]      | 除了数字之外（包括换行符） |

4. 元字符
   
   | \d            | 数字                |
   | ------------- | ----------------- |
   | \w            | 单词字符（字母，数字，下划线）   |
   | \s            | 空白（空格、TAB、换行符）    |
   | \D \W \S \s\S | 除了数字/单词/空白之外/所有字符 |
   | .             | 任意字符（不包括换行符）      |
   | \b            | 限制边界，防止过多匹配       |
   | ^a            | 行收的a              |
   | a$            | 行尾的a              |

5. 字符属性
   
   不同类型的字符有不同的属性，若要根据字符类型不同来匹配，则需要修饰符u和字符类\p，例子如下，其他查阅文档
   
   | /宽字符/u        | 匹配宽字符，如数学公式 |
   | ------------- | ----------- |
   | /\p{P}/       | 匹配标点符号      |
   | /\p{sc=Han}/u | 匹配中文        |

6. 分组
   
   用小括号包裹部分表达式使其变成子表达式（也叫院子组），最基本的使用时与四则运算一样改变正则运算顺序，和分割|的内容。
   
   捕获：院子组的内容会被缓存到内存中，这种行为叫做捕获
   
   反向引用：通过反向引用可以使用被捕获的院子组的内容，相当于别名
   
   1. 原正则表达式内使用： \1 \2 \3  依次类推表示第几个院子组
   
   2. str.replace(reg,'$2')    str.replace(reg,(reg,p1,p2) => {})  同上
   
   3. 嵌套院子组的情况就从左括号开始数，来判断第几个
   
   4. js的match和exec会返回每个原子组的匹配结果（提取）
   
   5. 左括号之后加上?:表示该院子组不记录，不能再使用上述情况，但括号之外的?:就是普通字符

7. 断言（环视）
   
   给某部分正则表达式前后增加附加条件，匹配的结果不包含断言
   
   下表的中括号应是英文，以  'workingandsingsing' 为例，[a-zA-Z]img  匹配出working和singsing
   
   | 正向先行断言【a-zA-Z】+(?=ing)      | 匹配出work和sing                        |
   | --------------------------- | ----------------------------------- |
   | 负向先行断言【a-zA-Z】+(?!ing)\w{3} | 这里的\w{3}也可以换成$  匹配出and              |
   | 正向后行断言 (?>=wo)【a-zA-Z】+     | 匹配出rking                            |
   | 负向后行断言 \w{2}(?!wo)【a-zA-Z】+ | 这里的\w{2}也可以换成^  匹配出rkingandsingsing |
   
   几个注意点：
   
   1. 断言虽然被小括号包括，但断言不是分组；如果断言内有小括号，则小括号是分组，但断言依旧不是分组
   
   2. 断言只是条件，不会作为匹配结果；如working  /w+ing和/w+(?=ing)的匹配结果分别为working和work
   
   3. 使用负向先行/后行断言时，由于条件不作为匹配结果，所以需要在前/后加上相应的东西；如匹配结尾补不为ng的单词，字符串为working sing的匹配
      
      | /w+(?!ing)      | working和sing |
      | --------------- | ------------ |
      | /w+(?!ing)\w{3} | sing         |
      | /w+(?!ing)$     | sing         |

# 二、Linux命令

# 三、git

git是一个版本控制工具。

基本原理：经过一轮开发或修改代码后，进行一次提交，每次提交生成一个新的版本，但是并不是完全拷贝原来的版本，而是只保存此次新增或修改的内容，通过指针指向上一个版本，就可以联结上一个版本的内容。

假设目前有一个版本C0，有一个123.txt文件；新增了一个456.txt文件后提交一次生成版本C1，在C1版本中就有123.txt和456.txt两个文件，但是C1实际上只存储456.txt，而123.txt是通过指针找到C0版本拿到的。

## 1 基本

（1）git结构

* 工作区：写代码的地方

* 暂存区：暂存代码，准备提交

* 本地库：保存提交的代码

* 远程库：github，gitee等托管代码网站

（2）使用

在需要git管理的目录中，右键菜单中点击 Git Bash Here 打开git命令行，里面的命令都是Linux命令。

若没有本地库，则需要初始化git本地库：

```
# 初始化本地库，生成.git文件夹（隐藏）
git init

#查看隐藏文件
ls -a    
```

操作git本地库时，若该电脑没有设置签名，必须要先要设置签名，签名只是作为说明信息，没有其他功能，有了签名才能提交等操作：

```
# 项目级别签名，只在这个项目使用
git config user.name ...
git config user.email ...

# 查看项目签名
cat .git/config

#系统用户级别签名，改系统的所有git仓库都会使用
git config --global user.name ...
git config --global user.eamil ...

# 在家目录中找.git文件中的config
cd ~  
```

做完以上操作后，就可以用git管理项目了。

查看各种文件状态；

```
# 查看工作区i，暂存区状态
git status
```

项目提交操作：

```
# 查看工作区，暂存区状态,红字表示工作区有文件可提交到暂存区，绿字表示暂存区有文件可提交到本地库
git status

# 提交到暂存区，...为文件名，若为. 则是全部文件
git add ...

#若...没有指明，则是commit所有暂存区的文件
# 提交到本地库（会进入vim输入说明信息）
git commit ... 
#直接写说明信息提交（不进入vim
git commit -m "..." ... 
```

注意事项：

* 空的文件夹不会被提交到本地库，若想保存该空文件夹，可以在里面放一个隐藏文件占位，命名一般为 .gitkeep

* 若有不需要保存到本地库的文件，可以新建.gitignore文件，在里面中声明，如想忽略node_modules文件夹：
  
  ```
  /node_modules
  ```

## 2 版本控制

提交后，可以查看文件提交历史记录，前进到新版本，后退到老版本，因此文件一旦提交到本地库后，即使删除的文件可找回。

（1）查看版本信息

git log 只能看到当前和更早版本的信息，无法看到新版本的信息

```
# 查看历史记录
git log

# 以下命令月下面显示结越更简洁
git log --pretty=oneline
git log --oneline
```

最常用的是git reflog，可以看到所有版本的信息

```
git reflog
```

HEAD是指向当前版本的指针，{n}表示从当前版本到此版本的移动步数，16进制数据是跳转版本的索引。

（2）版本的前进和后退

前进/后退版本，都是用git reset，操作后，文件夹内的内容会变为前进/后退后的样子：

第一种，使用hash值，直接到指定版本，可以是前进/后退

```
# --hard 一定不要漏了
git reset --hard 16进制索引
```

第二种，只能后退版本：

```
# --hard 一定不要漏了

# 后瑞n个^步数的版本
git reset --hard HEAD^^

# 后退n个版本
git reset --hard HEAD~n
```

参数：

* --hard 移动本地库HEAD，并将暂存区，工作区替换为相应版本

* *--mixed 移动本地库HEAD，并将暂存区替换版本，工作区不变

* --soft 移动本地库HEAD，暂存区，工作区不变

sort,mixed后git status的显示：

* *soft本地库移动了，暂存区不变，但是暂存区相对于本地库是移动了的，所以会显示绿字

* mixed是工作区相对移动了，所以显示红字

（3）注意事项

版本回退后，不建议修改并提交，如：

加深现在有三个版本

* c1：1.txt  内容111

* c2：2.txt 内容222，还有1.txt

* c3：3.txt 内容333，还有1.txt，2.txt

从c3回退到c2，修改内容变为222666，commit后得到c4，那么c4的内容就会有更新后的2.txt和1.txt，而不会有3.txt

如果真的需要回退修改commit，那么只能合并版本，到c4版本，执行以下命令：

```
git cherry-pick c3的hash
```

（4）文件删除后，可找回：

提交到本地库后，工作区删除的文件可找回

如果删除文件后，再提交到暂存区-本地库（只暂不本地也行），然后需要找回的话，就回退到上一个版本就可以恢复。

（5）有时候修改了工作区，想和原先进行比较：

```
# 不带文件名是将工作区所有文件都比较
# 本地库比较可以指定版本 如HEAD^

git diff ... 或 git diff 与暂存区比较
git diff HEAD ... 或 git diff HEAD 与本地库比较
```

## 3 分支

（1）介绍

在一个项目里，不同的程序员在不同的分支中开发，互不影响，各分支开发完后与主干合并。若有bug则新建一个hot_fix临时分支测试。

一般master作为主干，作为正式发布的线上版本，另外有一个dev分支作为开发版本，再从dev分支中划分出各个功能开发的分支。根据公司需要，master可能还会分出测试分支，review分支等。

另外一种场景是，当线上版本出bug需要修复时，可以从master分出debug分支，dedbug结束后再合并到master，就不会影响其他正在开发的功能。

（2）分支的原理

当master分出一个分支时，并不是拷贝所有代码，而是和版本控制一样，仅仅是将新分支的指针指向master，该新分支只存储新增或修改的内容。

B分支到合并A分支，其实只是把A分支的指针指向B分支。B分支合并完后可以删除（未合并的分支无法删除），删除也只是去掉指针。

（3）使用

查看、创建、切换分支：

```
# 查看所有分支和当前所在分支
git branch -v

# 创建一个新分支，指针指向当前分支
git branch name

#  直接创建并切换到xxx分支，是git branch和git checkout的结合
git checkout -b xxx

# 切换分支
git checkout name

# 修改分支名
git branch –m xxx

#删除分支
git branch -d xxx
```

（4）合并分支

各分支开发到一定阶段后，需要合并到父分支或主干中，注意合并的是该分支的本地库，所以main合并分支后不需要add和commit就能直接push。且main指向合并后最新的版本。

若push时远程库没有该分支，则远程库会自动创建该分支

开发完成该分支后，应该push该分支，而后合并到主干，再push主干

```
# 将name分支和主干合并（必须在master分支下操作），将分支修改的内容更新到主干
git merge name
```

（4）冲突：

当合并的两个分支，都对同一个文件的同一个位置进行了修改，此时git就不知道如何合并，发生冲突。
解决：编辑文件，修改到没有冲突的程度

## 4 远程库

### 4.1 push到远程库的基本流程

常见的远程库有github，gitee

提交到远程库的一般操作：

最开始，先初始化本地库，并设置邮箱和用户名(随便设，只作为标识，若不设，则无法提交：

```
git init 
git config –global user.email “...”
git config –global user.name “...”
```

若使用了代理，git 的端口号要和代理的一致：

查看代理端口号：控制面板 \- 网络和 internet \- internet 选项 \- 连接 \- 局域网设置 。

```
# 查看 git 是否配置了代理
git config --global --get http.proxy
git config --global --get https.proxy

# 若存在，且端口号和代理不一样，就删除
git config --global --unset http.proxy
git config --global --unset https.proxy

# 配置 git 代理
git config --global http.proxy 127.0.0.1:7890
git config --global https.proxy 127.0.0.1:7890
```



提交到远程库之前，必须先要配置远程库链接：

```
# xxx 是名字一般是 origin，...是远程库链接
git remote add xxx ...
```

查看、删除远程库链接：

```
#查看所有链接
git remote -v

#删除链接
git remote rm xxx
```

提交到远程库：

```
# 提交
git push xxx 分支名
```

注意事项：

* git add的警告warning: LF will be replaced by CRLF：
  
  原因：Linux用LF代表换行和回车，而windows的LF是换行，CRLF是回车，若不处理将会将LF转为CRLF，跨平台时就会出错，解决方法：
  
  ```
  git config --global core.autocrlf false
  ```

* github将master改为了main，所以本地库也改成main，否则无法提交：
  
  ```
  git branch –m main
  ```
  
  其他的远程库就还是master

### 4.2 配置免密登录

每次push都要输入账号密码比较麻烦，可以配置ssh，直接push

1. 先在自己电脑上查看或创建ssh公钥
   
   查看ssh公钥，在命令行中输入命令，输入完后一直按下回车：
   
   ```
   # windows
   type %userprofile%\.ssh\id_rsa.pub
   
   # linux
   cat ~/.ssh/id_rsa.pub
   ```
   
   若没有，则创建公钥，不同操作系统的命令都是一样的，创建完成后再查看公钥：
   
   ```
   ssh-keygen -t rsa
   ```

2. 将自己电脑的ssh公钥复制到github的设置中
   
   gifhub-个人头像-setting-SSH and GPG keys-Create ssh key-输入描述褐ssh公钥

3. git remote add origin [git@github.com](mailto:git@github.com):ligengxin549/仓库名.git
   
   * 本地库提交到github：
   
   ```
   # #添加该目录所有文件到暂存区
   git add .
   
   # #添加到本地库
   git commiy –m “描述”
   
   # #建议在push之前先pull下来，得到别人的最新修改
   git pull origin main
   
   # 提交到远程库
   git push origin main
   ```

### 4.3 拉取远程库的项目

可以通过pull或clone拉取远程库的项目，地址在远程库某个项目里找到https地址或ssh地址：

```
git pull xxx
git clone xxx 
```

一般来说，开发者为了减小体积，提交到远程库会通过.ignore文件将项目中的依赖/第三方库忽略掉，所以我们拉取下来时需要自己安装依赖，如vue项目：

```
npm install
```

pull与clone区别：

* clone是没有本地库的情况下，完全克隆远程库的内容

* oull是在有本地库的情况下，pull下来保存到本地库，但不覆盖本来内容。

git pull 其实是git fetch和git merge的结合，所以如果有可能会出现冲突的情况。

## 5 git钩子

Git钩子（Git hooks）是一种机制，可以在Git操作期间触发自定义脚本。这些脚本可以用于实现自动化流程、规范化代码提交等目的。

Git钩子分为两类：

* 客户端钩子：在Git客户端上运行，例如在commit、push等操作之前进行代码检查、格式化等操作。常见的客户端钩子包括：
  
  - pre-commit：在执行commit命令之前运行，用于检查代码规范、格式等问题。
  - prepare-commit-msg：在创建提交信息（commit message）之前运行，用于自动生成部分提交信息，例如添加分支名、任务编号等。
  - post-commit：在执行commit命令之后运行，用于发送通知、更新版本号等操作。

* 服务器端钩子：在Git服务器上运行，例如在push到远程仓库时进行权限验证、自动化测试等操作。常见的服务器端钩子包括：
  
  - pre-receive：在接收到push操作之前运行，用于验证推送的代码是否符合规范、是否有权限等问题。
  - post-receive：在接收到push操作之后运行，用于触发自动化流程、通知相关人员等操作。

使用Git钩子可以帮助团队实现自动化流程、规范化代码提交等目的。

使用方法，以实现commit之前进行eslint代码检查为例：

1. 在本地Git仓库的根目录下，进入.git/hooks目录

2. 查看是否存在pre-commit.sample文件，如果存在，将其重命名为pre-commit（如果不存在则可以直接创建pre-commit文件）。打开后编写shell脚本：
   
   ```
   #!/bin/sh
   
   # Run ESLint
   ./node_modules/.bin/eslint .
   
   # If ESLint exited with an error, abort the commit
   if [ $? -ne 0 ]; then
     echo "ESLint found errors. Aborting commit."
     exit 1
   fi
   ```
   
   上述脚本会在代码commit之前运行，使用ESLint对代码进行规范检查，如果检查出现问题，则终止提交操作。

3. 保存pre-commit文件，并添加执行权限：
   
   ```
   chmod +x pre-commit
   ```

4. commit代码时，pre-commit钩子会自动运行，检查代码规范，如果检查失败则会提示并终止提交操作。

## 6 多人写作

邀请成员：

* 在 仓库-settings 中邀请，常见于个人开发者寻找合作者

* 创建一个组织 右上角+-new oganization，常见于公司，在此组织中创建项目，邀请成员，设置权限，组织内的成员就能协作组织中的项目

协作流程示例：

master作为线上版本，dev作为开发版本，从dev分出每个人的分支，假设现在master上线上正在运行的版本是v1：

* 每个人开发完后，经过上级review检查代码后，合并到dev，测试人员进行测试。

* 所有功能开发完合并到dev并测试后，合并到master作为线上版本

* 线上版本出bug就单独创建一个debug分支解决

```
   |----->debug
   |       |
   |      review
   |       |
master(v1)<--------------------------------------------|
   |                                     |             |
   |                                    review        review
   |                         release测试  |  |-release  |
   |                           |      |  |  |     |     |
  dev--------------------------v2-----v3---v4----v5------
   |                           |          |
   |                          review     review
   |----->功能A----commit...----|          |
   |                                      |
   |----->功能B----commit...---------------|
```

master分支中，为了直观的表示版本，需要打上版本号：

```
# master
git tag -a v1.2.3 -m "v1.2.3版本"
```

review过程：

* 每次合并分支前，需要leader检查代码，需要在远程库配置review

* 开发人员开发完分支后，在远程库提交pull request，申请合并

* leader收到申请，可以在网站上merge pull request或在本地上根据提示的命令合并

release过程：

* dev分出release分支，测试功能，测试一般不会修改代码，最多做一些小的debug

* 测试完后，合并到dev分支

* dev合并到merge，合并前需要review

### 7 其他

（1）多个仓库共用模块

若多个仓库会共用同一个模块，可以封装成一个npm包，pip包等，也可以用gitmodules

.gitmodules ：

1. 将共用的模块单独创建一个仓库

2. 在需要用到的仓库的项目根目录下，创建 .gitmodules ：
   
   ```
   [submodule "src/xxx"]
       path = src/xxx
       url = https://github.com/ligengxin549/xxx.git
   ```
   
   上面代码的意思是将这个xxx.git仓库的内容放到挡墙项目的src下的xxx

（2）git rebase

简化提交记录，注意：最好只合并没有存到远程库的记录，否则很麻烦

通常有3个应用场景：

* 整合多条提交记录：
  
  ```
  # 整合包括当前版本到包括hash版本之间的记录
  git rebase -i hash
  
  # # 整合包括当前版本到前面2个版本共3个版本的记录
  git rebase -i HEAD~3
  ```
  
  执行命令后进入vim，修改pick为s，只保留一个pick，锁条s合并到pick，:wq保存；
  
  然后输入整合后的·提交描述，:wq保存；

* git merge合并后，提交记录会出现分叉以记录分支的提交记录，可以用git rebase将分支的提交记录合并为一个：
  
  ```
  # 现在要把dev分支合并到master
  
  # dev分支中
  git rebase master
  #master分支中
  git merge dev
  ```

* git pull由于半只是git fetch和git merge和结合，所以也会产生分叉，可以合并为一个：
  
  ```
  # git pull 替换为
  git fetch
  git rebase
  ```

若git rebase出现了冲突，rebase暂停，那解决完冲突后，需要继续：

```
git add 解决完冲突的文件
git rebase --continue
```

（3）快速解决冲突

使用软件 beyond compare

（4）github上开源项目贡献

# 四、markdown

（1）标题

#加空格，共6级，每级多一个#

（2）分割线

三个*

---

（3）缩进

大于号

> 一个大于号一级，可以有多级

（4）无序列表

-或*加空格

- 123

（4）有序列表

数字.空格

1. 123

`
