该笔记主要是node后端，以及常用的前后端交互功能实现（如登录，websocket）

# 一、node

NodeJS是运行在服务端的JavaScript的开发平台，实质是对chrome V8引擎的封装。
使用事件驱动和非阻塞I/O模型，使得其轻量，高效，非常适合在分布式设备上进行数据密集型的时时应用。具有以下特点：

* RESTful API

* 单线程：不需要额外的线程，依然可以对任务进行并发处理，原理是通过事件循环实现并发操作，因此应利用这一点，尽可能减少阻塞操作，多使用非阻塞操作

* 非阻塞I/O

* V8虚拟机

* 事件驱动：用module模块划分不同的功能，简化开发，每个类库都有丰富的api，常见的模块有http，require，fs

vscode在当前目录打开命令行： 查看-Teminal  或  ctrl+反引号
vscode的插件node-snippets，输入node可根据提示自动创建代码结构

## 1 npm

npm是nodejs的包管理工具：
（1）初始化package.json：npm init   
会生成package.json，内包含所需依赖的包  
①npm install 会根据其内容安装依赖，别人只需这个文件就能自动装包，不需要发给其modules，所以git只发这个文件就行
npm init –y  全部选项直接yes
②npm update  更新包版本
③npm install --production  npm install --dev  只安装生产环境/开发环境的包

（2）安装/卸载/包，清除缓存：
install可简写为 I   
npm install moduleName -g或—save --dev可选
-g或--global 全局安装 
--save或-S 局部安装，生产环境，在开发/运行时都使用
--save --dev或-D 后只在开发时使用，运行时不适用

npm uninstall xxx –g/--save  卸载

清理npm缓存： npm cache clean –force  可解决包安装出现的一些问题

（3）查看已安装包：
npm list 或 npm list --ave  查看该项目的包和依赖关系
npm list | grep xxx  只显示xxx包的依赖关系
package-lock.jspn会显示已安装的包和依赖关系
npm list –g  查看全局包和依赖关系
npm outdated  查看已过期包

（4）node包的版本号：
①安装指定版本的包
npm install xxx@版本  指定版本   
xxx@1  安装1.x的最高版本 
@latest 最新版
npm view xxx versions  查看xxx的所有版本

②版本号：
主版本号.次版本号.补丁号
朱版本为大版本，一般有大更新
次版本号为小更新
补丁号偶数为稳定版本，奇数为不稳定版本
package.json的版本符号：a.b.c为例
^a.b.c  锁定a的版本，bc最新版本
~a.b.c  锁定ab的版本，c最新版本  （^的bc和~的c不要超过存在的版本，否则npm update报错）
a.b.c  锁定abc就是这个版本

*那abc都是最新版本

（5）导入包和运行js
引入模块：let xxxx=require(‘modulelName’)
注意：若引入内置/第三方包，不加./  若引入自己目录下的包，必须./  因为不加./会从module下找，加了./才会从自己目录找
运行js：cmd在js我那件的目录下，node xxx.js

（6）npm脚本：
package.json中

```
“script”:{
 “xxx”:”ccc”,
}
```

给命令设置别名，执行npm run xxx 相当于 执行ccc
也可以自定义js文件 npm run xxx => node xxx.js

## 2 node内置模块，第三方模块，自定义模块

### 2.1 内置模块

里面的回调函数的参数一般err在前，if(err)。。elsex 的形式，通常用来处理异常
（1）http

```
var http = require('http');
http.createServer(function (request, response) {
 response.writeHead(200, {'Content-Type': 'text/plain'});
 response.end('Hello World'); //必须有end才会结束响应
}).listen(8081);

request的api
url 请求的url

response的api
write(‘html结构’)
```

（2）url
url.parse(‘网址’) 解析网址的端口，域名，query等，传入第二个参数true能将query转对象

（3）path

（4）fs

文件操作

```
//判断是目录还是文件
const fs = require('fs')
fs.stat('./123.txt',(err,data)=>{
 if(err){
 console.log('err')
 return
 }
 else {
 console.log(`文件？${data.isFile()}`)
 console.log(`目录？${data.isDirectory()}`)
 }
})
//创建文件
fs.mkdir('./666.css',(err)=>{})
//创建文件并写入内容，若文件已存在，则覆盖内容
fs.writeFile('./2.txt','123456789',(err)=>{})
//创建并写入内容，若文件已存在，则追加内容
fs.appendFile('...','...',(err)=>{})
//读取文件/目录内容，data为内容
fs.readFile('...',(err,data)=>{})
fs.readdir('...',(err,data)=>{})
//重命名，若路径不同，则是移动文件
fs.rename('...','...',(err)=>{})
//删除文件
fs.unlink('...',(err)=>{})
//删除目录，目录没有文件时才能删除目录
fs.rmdir('...',(err)=>{})
```

### 2.2 常用第三方包

lodash  字符层，数组，数学，集合，日期等api
debounce  防抖

### 2.3 自定义模块：CommonJS模块化规范

自定义abc.js
module.exports = xxx

package.json中
“main”:”abc.js”  指定入口

# 二、express

## 1 基本

基于nodeJS的简单灵活的web服务端框架，可以对数据库进行操作。

特性：

* 可以设置中间件来响应http请求

* 定义了路由表用于执行不同的http动作

* 可以向模板传递参数来动态渲染html

## 2 使用

先建立一个存放服务器的文件夹，在该目录下：

```
npm init
npm install express --save
```

启动服务器：

```
node xxx.js
```

自动重启服务器：

通过nodemon启动服务器，当代码修改时会自动重启（但有时不会，就需要自己重启）

```
npm install --save nodemon
```

启动：

```
npx nodemon xxx.js
```

调试：

127.0.0.1:8000/url 可以调试

express使用：

```
const express=require('express')
const bodyParser = require('body-parser')

const app = express()
//将public作为静态文件夹，通过 域名:端口/文件名.后缀 就可以访问，注意路径没有public
//若有多级文件夹，就 域名:端口/文件夹/文件名.后缀
app.use(express.static('./public')) 

//请求体解析的中间件
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: false }))

//所有请求类型，所有url都设置可跨域
//注意，node的路由是从上至下看是否有要执行的路由，所以跨域的路由代码要放到最前面
app.all("*", (req, res, next) => {
  //解决跨域
  //允许跨域的ip
  res.header("Access-Control-Allow-Origin", "*");
  //允许跨域的请求类型，get，post，options不用设置也允许
  res.header("Access-Control-Allow-Methods", "*");
  //允许token请求头的跨域
  res.setHeader("Access-Control-Allow-Headers","content-type,Authorization")


  //解决axios的post请求会先发送options请求的问题（post请求但不传数据或formdata则不会有这种问题）
  if (req.method == 'OPTIONS')  res.send(200);  
  else  next();
})

//中间件------------------------
//自定义中间件用函数来定义，在路由中可以使用中间件，中间件代码执行完后才执行路由的代码
function myMid(){
  console.log('我是一个中间件')
}
//-----------------------------

//路由--------------------------
/*获取参数
get等通过params传参的请求：req.query.xxx
post等通过data传参的请求：req.body.xxx
此外，也可以配置动态路由 '/xxx:id'，通过req.params.id获取参数
*/
app.post('/url',myMid,(req,res) => {
  //req.query和req.body分别是get和post请求的参数
  res.send('请求结束')
})
//------------------------------
app.listen('8000',() => {
  console.log('服务器已启动')
})
```

跨域除了手动设置外，还可以直接使用第三方库：

```
const express = require('express');
const cors = require('cors');
const app = express();
app.use(cors());
```

cors()也可以传递参数，比如cors这个库默认是不支持cookie跨域的，此时就需要在参数中允许cookie跨域：

```
app.use(cors({
  origin: true,
  credentials: true,
}));
```

# 
