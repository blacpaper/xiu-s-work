# 1. Git

​	笔记转录于B站up：<u>**GeekHour**</u> ，发表的《一小时Git教程》。笔记中若有讲解不清楚的地方，可访问原视频观看学习。URL：https://www.bilibili.com/video/BV1HM411377j?p=1&vd_source=c69af8172c01f57ba6034bbf27b53d5f。

## 1.1 版本控制系统

​	版本控制系统，顾名思义，是一个文件的版本的控制软件。

​	文件的版本会随着程序的更新、修改等不断的迭代。好比在游戏每隔一段时间就会更新一个新版本；服饰隔半年或一年就会出一个同代的新款。

​	但是随着其存在时间的长久，版本多了就不便于管理。设计时，乙方往往要给甲方多套方案，而甲方总喜欢在一句句“不行”之后加上一句“还是用最开始的吧...”这时候版本控制就发挥了作用，设计时可以直接找到最开始的版本并将其发给甲方。

​	版本控制系统就像一个大的仓库，里面存放着一款款产品（可以是文本，程序代码等）的迭代版本。用户可以在里面下载指定版本的产品或上传修改后产品。

​	这里有利于团队的集体开发。

## 1.2 版本控制系统的分类

1. 集中式

   ​	集中式为所有电脑共用一个中央 Server，每台电脑可以在这个Server里下载或上传产品新的版本。

   ​	但他有个明显的问题，Server一旦出现问题，整个工作部门的工作进程就会受到影响。

   ![集中式版本控制系统](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/集中式版本管理.png)

2. 分布式

   ​	分布式版本控制系统，每个电脑都有一个完整的版本库Server，文件可以同步到不同的电脑Server上，来实现协同的版本控制效果。这样也不用考虑中央Server暴毙的影响。

   ​	Git 就是一种分布式版本控制系统，因为其开源、速度快、支持离线管理等特性，可以说已经成为目前最流行的版本控制系统了。像是GitHub、GitLab、Vue的等网站上的托管开源项目都是 Git 来管理的。

   ![分布式版本管理系统](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/分布式版本管理.png)

## 1.3 Git 的安装

​	找到 git 的官网，下载对应操作系统的git。这里下载的都是<u>命令行版本</u>的，要是用不习惯也可以下载<u>图形操作界面版本</u>的 git 或着<u>插件版本</u>。

​	本人电脑Mac mini，MacOS，M2芯片，命令行版本

官网url: https://git-scm.com。官网还有详细的操作指南，本文档只做快速了解。

macOS

```shell
brew install git
```

Linux

```shell
# ubuntu/debian
apt-get install git

# fedora
yum install git (up to fedora21)
dnf install git (fedora22 and later)
```

​	检查是否安装完成

```shell
git -v # 查看git版本
> git version 2.39.3 (Apple Git-146) # 安装成功
```

![git安装成功](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/安装成功.png)

## 1.4 Git的配置

​	安装成功后需要配置一下 Git ，这样才能识别出来是谁提交了内容。类似于配置用户信息。

```shell
# 配置用户名
git config --global user.name "your_name"

# Local(省略)：本地配置，只对本地仓库有效
# --global：全局配置，所有仓库有效
# --system：系统配置，对所有用户生效

# 用户邮箱
git config --global user.email "your_email_path"

# 保存用户名个密码
git config --global credential.helper store

# 查看git的配置信息，按q退出
git config --global --list
```

# 2. Git 仓库

​	仓库，repository，简称 Repo。用来存放文件，在仓库里的文件会被 git 管理起来，用户对文件的操作会被记录追踪，以便用户可以查询或还原到某一历史版本。

## 2.1 创建仓库

1. **git init**

   ​	本地创建仓库，把本地某一文件变为仓库这个角色

   ```shell
   # 创建一个目录
   mkdir "your_dir_name"
   cd "your_dir_name"
   git init
   
   # 创建成功后会出现一个（main）的指示
   # 该目录成为仓库后会自动创建一个 .git 文件，这个文件比较重要，所以会隐藏起来
   # 查看 .git 文件
   ls -a
   > . .. .git
   
   # 若想指定一个文件作为仓库，可在后面加上仓库名称，会在当前位置创建一个新的目录
   git init "repo_name"
   cd "repo_name"
   ls -a
   > . .. .git
   ```

   ![Init查看隐藏文件](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/查看隐藏文件.png)

2. **git clone**

   ​	克隆仓库，从远程服务器上克隆一个仓库到本地。这应该是用的比较多的，克隆github上的项目经藏会用到git

   ```shell
   # 从GitHub上拉取视频作者的项目
   git clone https://github.com/geekhall-laoyang/remote-repo.git
   ```

   

# 3. 工作区域和文件状态

## 3.1 工作空间

​	git的工作区分为三个内容：工作区、暂存区、本地仓库。

- 工作区

  .git 所在的目录，是我们实际操作的地方

- 暂存区

  .git/index，临时存放数据的地方

- 本地仓库

  .git/objects，是 git 存储代码和版本信息的主要位置

三者关系：现在 “工作区” 完成任务，提交至 “暂存区”，再上传到 “本地仓库”。

![工作空间](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/工作空间.png)

## 3.2 文件状态

- 未跟踪 Untrack

  新创建，但还未被 git 管理起来的文件

- 未修改 Unmodified

  已经被 git 管理起来的文件，但是文件的内容只有被修改

- 已修改 Modified

  文件内容已经被修改，还未添加到暂存区的文件

- 已暂存 Staged

  已添加到暂存区的文件

​	这里放一张视频截图表示四者关系

![文件状态](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/文件状态.png)

# 4. Git 指令操作

## 4.1 git init 创建仓库

## 4.2 git status 查看仓库状态

 	可以查看当前仓库的状态，如处于那个分枝，文件提交状态等。

```shell
git status
> On branch main # 当前处在main分支
>
> No commits yet
>
> nothing to commit (create/copy files and use "git add" to track)
```

​	当我们创建文件之后，就会有变化了。可以看到和最开始的 status 不一样，这次多了一个返回，提示有一个未跟踪的文件，还提示我们使用 `git add <file>...`指令将文件添加到<u>暂存区</u>

```shell
touch first.text	# 创建一个空白的.txt文件

ls								# 查看当前目录下的文件
> first.txt

cat first.txt			# 查看文件内容
> hello git%  		# 我是已经对文本编辑过了，所以才会有内容

git status				# 查看仓库状态
> On branch main
>
> No commits yet
>
> Untracked files:
>   (use "git add <file>..." to include in what will be committed)
> 				first.txt
> 
> nothing added to commit but untracked files present (use "git add" to track)
```

![git_status](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/4.2 git status.png)

## 4.3 git add 添加到暂存区	

​	添加文件到暂存区。文件变成了绿色，表示已经添加到暂存区，等待上传到<u>本地仓库</u>。提示中有个指令`git rm --cached <file>...`表示将文件移除<u>暂存区</u>，放回<u>工作区</u>。

```shell
git add first.txt
```

![git add](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/4.3 git add.png)

## 4.4 git commit 提交

​	文件添加到<u>暂存区</u>后下一步需要上传到<u>本地仓库</u>，使用命令`git commit -m <file_message>...`。只有上传到<u>本地仓库</u>，文件才会被 git 控制起来。`git commit -m <file_message>...`。**只能将<u>暂存区</u>的文件上传**，工作区的文件不受影响。

```shell
# 创建第二个.txt文件，内容为“hi git”
echo "hi git" > second.txt

# 查看仓库状态
git status

# first.txt提交到本地仓库。-m不加的话会出现一个交互界面，下面展示
git commit -m "This is the first file"
```

![git commit](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/4.4 git commit.png)

第二个文件上传，上传时不添加 `-m`，会出现一个交互式窗口。和上面其实是一样的，也要添加上传信息。

```shell
git add second.txt
git status
git commit
```

![git commit -m1](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/4.4-m git commit1.png)

![git commit-m2](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/4.4-m git commit2.png)

## 4.5 git log 日志	

​	还可以使用 `git log`命令来查看日志。log 会展示每次提交产生的id，提交人员，提交时间等信息。

```shell
git log

git log --oneline # 简单版日志
```

![git log1](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/4.5 git log1.png)

![git log2](/Users/xiu/Desktop/git-repo/xiu'work/linux/tool/git/img/4.5git log2.png)

## 4.6 git reset 回溯

​	在开发的时候，我们有时候需要回退到某一版本，这时候就可以使用`git reset`这个命令。有三个方法：

- `git reset --soft`

  表示回退到某一版本，并保留<u>工作区</u>和<u>暂存区</u>的所有修改内容

- `git reset --hard`

  回退到某一版本，并且丢弃工作区和暂存区的所有修改内容

- `git reset --mixed`

  回退到某一个版本，只保留工作区的修改内容，丢弃暂存区的修改内容。这也是`git reset`的默认方式。

|  方式   | 工作区 | 暂存区 |
| :-----: | :----: | :----: |
| --soft  |   ✅    |   ✅    |
| --hard  |   ❌    |   ❌    |
| --mixed |   ✅    |   ❌    |

​	他这里的保留于丢弃用法理解如下。

```shell
# 创建三个新的文件
echo "one" > one.txt
echo "two" > two.txt
echo "three" > three.txt

# 上传到暂存区
# 这里分别提交以代替不同版本
git add one.txt
git commit -m "one"

git add two.txt
git commit -m "two"

git add three.txt
git commit -m "three"

# 查看log	可以看到之前的两个上传和这三次的上传，一这三次的上传为例，one two three
git log --oneline
> fad47e0 (HEAD -> main) three
> d9937fa two
> ebbe386 one
> 7f6b693 This is the second file
> 119308b This is the first file
> (END)

# 分别复制了三个文件以展示效果

######################################
# --soft
git reset --soft d9937fa	#回退到two
git log --oneline
> d9937fa (HEAD -> main) two
> ebbe386 one
> 7f6b693 This is the second file
> 119308b This is the first file
> (END)
# 可以看到 回退到two版本了，three已经不在仓库里了

# 查看工作区和暂存区
# 在工作区 three.txt还在，且内容没被修改
ls
> first.txt  second.txt two.txt
one.txt    three.txt
cat three.txt
> three

# 暂存区 three.txt也是还在的
git ls-files
> 
> first.txt
> one.txt
> second.txt
> three.txt
> two.txt

# 查看仓库状态 three是新文件。因为返回到two版本时three还没上传，当时的three就是新文件。所以回退的时候就保留了原样。
git status
> new file:   three.txt


#################################
#  --hard  d9937fa也可以换成HEAD^,表示上一代
git reset --hard d9937fa

# 工作区，three.txt已经不见了
ls
> first.txt  second.txt
one.txt    two.txt

# 暂存区也是一样
git ls-files
> first.txt
> one.txt
> second.txt
> two.txt

# 仓库状态, 没有显示有新文件
git status


####################################
#		--mixed
git reset --mixed d9937fa

# 工作区
ls
> first.txt  second.txt two.txt
one.txt    three.txt

# 暂存区
git ls-files
> first.txt
> one.txt
> second.txt
> two.txt

# 仓库状态 three是未修改文件，需要加到暂存区
git status
> Untracked files:
>   (use "git add <file>..." to include in what will be committed)
> 				three.txt
```

​	这三种用法都是对两个版本间进行操作，所及谨慎使用 `--hard`  他会直接删除两版本间的所有文件。如果误操作了也可以使用回溯来挽救。

```shell
# 找到误操作的ID
git reflog

# 回溯
git reset --hard <'误操作ID'>
```

## 4.7 git diff 差异

​	用于找到存在的差异，可以是各个区间的差异，也可以是两个不同版本之间的差异，甚至是可两个分支间的差异。默认是比较<u>工作区</u>和<u>暂存区</u>之间的差异。

```shell
cat three.txt
> three

vim three.txt # 改成了333

cat three.txt
> 333

git diff
> diff --git a/three.txt b/three.txt
> index 2bdf67a..55bd0ac 100644
> --- a/three.txt
> +++ b/three.txt
> @@ -1 +1 @@
> -three  # 删除的内容
> +333		# 新增内容
> (END)

# 新内容添加到暂存区，再次diff就没有差异了
git add three.txt
```

​	还可以比较<u>工作区</u>和<u>仓库</u>之间的差异。继续使用上面的文件，three还没有上传到仓库

```shell
git diff HEAD
> index 2bdf67a..55bd0ac 100644
> --- a/three.txt
> +++ b/three.txt
> @@ -1 +1 @@
> -three  # 删除的内容
> +333		# 新增内容
> (END)
```

​	<u>暂存区</u>与<u>仓库</u>

```shell
git diff --cached
> index 2bdf67a..55bd0ac 100644
> --- a/three.txt
> +++ b/three.txt
> @@ -1 +1 @@
> -three  # 删除的内容
> +333		# 新增内容
> (END)
```

​	不同版本之间

```shell
git diff <id1> <id2>
```

​	与上一个版本比较

```shell
git diff HEAD~ HEAD
# HEAD^也是一样的
# HEAD～n 表示上n个版本
```

## 4.8 git rm 删除

```shell
#	删除工作区文件 Linux方法
rm <file_name>
git add .	# 更新暂存区

# git方法
git rm <file_name>
```

