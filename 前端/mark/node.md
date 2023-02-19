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
npm init
npm install express --save
启动服务器：
node xxx.js
自动重启服务器：
调试：
127.0.0.1:8000/url  可以调试

通过nodemon启动服务器，当代码修改时会自动重启（但有时不会，就需要自己重启）

npm install --save nodemon

npx nodemon xxx.js  

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

restfulAPI：

后端接口的设计规范，增删改查的请求分别是post，delete，put，get

# 三、注册/登录/鉴权/权限管理

需要的第三方库

```
const bcryptjs = require('bcryptjs')
const jsonwebtoken = require('jsonwebtoken')
```

## 1 注册

后端需要定义用户的表，账号限制唯一u，密码需要bcrypt加密

```//
//用户表定义
const bcryptjs = require('bcryptjs')
const mongoose = require('mongoose')
mongoose.connect('mongodb://localhost:27017/vnpDB',{
  useNewUrlParser: true
})

const Users = mongoose.model('users',new mongoose.Schema({
  username: {
    type: String,
    unique: true  //限制账号唯一，若重复会报错
  },
  password: {
    type: String,
    set(val){
      return bcryptjs.hashSync(val,10)  //加密
    }
  }
}))

module.exports = {
  Users
}
```

注册的接口，当账号已存在时需捕获异常

```
const {Users} = require('./db/Users.js')
app.post('/logup',async (request,response,next) => {
  try {
    await Users.create({
      username: request.body.username,
      password: request.body.password
    })
    response.send('注册成功')
  }
  catch(err) {
    response.send('注册失败')
  }
})
```

前端代码略，就是一些表单的验证和发送请求而已

## 2 登录

有账号密码登录、手机验证码登录、微信登录等。

状态保持：用某种方法保持登录状态，不需要重复登录。目前有cookie，session，jsonwebtoken三种，jsonwebtoken最常用。

后端：

（1）账号密码登录

先判断账号是否存在，再匹配密码，匹配成功返回jwt（jsonwebtoken），用于鉴权

```
//私钥为了安全一般是不可见的，保存在本地文件中，不存放于git，这里为了方便就直接定义为了变量
const SECRCT = 'asf34g35s1g56erssa'

app.post('/login',async (request,response) => {
  let user = await Users.findOne({
    "username": request.body.username
  })
  if(!user) return response.send('用户名不存在')
  let passwordValid = bcryptjs.compareSync(request.body.password,user.password)
  if(!passwordValid)  return response.send('密码错误')
  //jwt用users表的id和私钥签名
  let token = jsonwebtoken.sign({
    id: String(user._id)
  },SECRCT)
  response.send({
    user,
    token
  })
})
```

（2）手机验证码登录

（3）微信登录

前端：

```
//账号密码登录
请求.then(res => {
  console.log(res.data.token);
})
//微信登录
wx.login();
```

拿到token后，将token存放到storage和vuex中。

token作为登录凭证来保持持久登录，无需账号密码。

那既然都存到storage了，为什么还要存到vuex中？

* 相对来说vuex的存取比storage方便一些，且配合vuex的持久化存储插件可以更加方便

* vuex的数据是响应式的，而storage不是响应式，有时候可能会考虑这一点

* vuex存在内存中，而storage存在本地磁盘中，在内存中存取数据会快一点

跳转页面，可以全局前置守卫判断是否需要登录和是否已登录：

```
// /router/index.js
router.beforeEach((to,from,next) => {
  if(!to.meta.token)  next();
  else {
    if(localStorage.getItem('token'))  next();
    else next('/Login');  
  }    
})
```

后端的接口总体分为需要token鉴权和不需要token鉴权两种。一般后端需要token鉴权的接口会统一命名，如果是统一命名就适用下面的方法，如果不是就另找方法。

```
//可以在请求拦截器上根据url判断是否需要token，给请求头加上token
//比如需要token的接口的url都包含一个'/v2/''
请求拦截器(config => {
  if(/\/v2\//.test(config.url)){
    let token: string = JSON.parse(localStorage.getItem('mainStore') as string) ? JSON.parse(localStorage.getItem('mainStore') as string)?.token : '';
    config.headers!.Authorization = token;

    //如果是ts，headers可能为空而报错，需要非空断言
    //config.headers!.Authorization = token;
  }
  return config;
})
```

退出登录时，需要清空storage和vuex的token

## 3 鉴权

在进行数据的增删改查的时候，需要鉴权，将token发送给后端，鉴权成功才能进行增删改查，以查询数据为例：

前端代码：

```
//拿数据
axios({
  url: '/getProfile',
  method: 'get',
  headers: {
    Authorization: sessionStorage.getItem('token'),
  }
}).then(res => {
  console.log(res.data)  
})
```

后端代码：

响应头需要加上Authorization

为了简化代码，将鉴权逻辑定义为express中间件，每个需要鉴权的url调用这个中间件即可。

```
async function auth(req,res,next){
  let token = req.headers.authorization
  //解析jwt中的user的id
  let {id} = jsonwebtoken.verify(token,SECRCT)
  let user = await Users.findById(id)
  res.user = user
  next()
}

//在执行回调之前，会先执行auth中间件
app.get('/getProfile',auth,(req,res) => {
  res.send(res.user)
})
```

## 4 权限管理

权限管理分为前端权限管理和后端权限管理，前后端未分离的时代权限都是由后端管理的，但是在前后端分离的时代，前端也需要权限管理。

权限的本质就是对数据库中的数据的增删改查

后台管理系统一般admin需要有对用户、角色、权限、菜单的增删改查

### 4.1 后端权限管理

后端权限通过token来鉴权增删改查的操作，是权限管理的最后一道关口

## 4.2 前端权限管理

前端权限管理仅仅是针对于视图层展示和请求的发送，并不能管理数据库的增删改查。

RBAC（基于角色的权限控制）：权限并不是针对于某个用户，而是针对于某类角色，一个用户可能有多个角色，在数据库设计上可以设计成用户表、角色表、权限表。

前端登录成功时，会同时发送该用户具备的权限。

但是前端的权限管理也是非常有必要的，主要有以下几点：

* 减少用户非法操作的可能性，如隐藏需要权限的按钮。

* 尽可能排除非必要和不具备权限的请求，减少服务器压力，尽管这些请求也一定不会成功

* 提高用户使用体验，如用户在浏览器输入url，若此url需要登录就跳转登录页，若此url需要权限且用户不具备权限则跳转404页面等

前端权限管理分为四个方面：

* 菜单权限：主要指后台管理系统的侧边菜单栏，登录后根据后端返回的菜单权限，只展示该用户具备权限的菜单。菜单权限控制一般都要配合页面的权限控制。

* 页面/路由权限：用户只能访问自己具备权限的页面，若用户通过非法操作（如输入不具备权限的url，或控制台进行路由跳转），应当强制跳转到登录页或404页。

* 按钮/超链接权限：一些页面可能几类角色都有权限进入（或非法进入），而该页面的按钮则具备权限，如普通角色只有查看权，而管理员有编辑、删除等按钮，那么这些按钮就应该根据权限来显示隐藏/启用禁用。

* 请求权限：若通过以上操作还不能规避用户非法操作，如用户非法进入页面，通过控制台修改按钮为显示/启用，那么在发送请求时，应当根据权限在前端层面请求发起时就拒绝发送请求。

可以看出这四个方面是循序渐进的。由前端进行的一系列权限控制之后若用户还是能够非法的操作对数据进行增删改查，后端通过token鉴权也能规避。

### 4.3 前端权限管理代码实现

#### 4.3.1 场景模拟

某系统具备七个页面，分别是登录页，404页、个人主页，订单信息页和管理页（用户管理、商品给管理），具有两种角色，分别是普通用户和管理员。

登录页和404页在未登录时就能访问，

个人主页需要登录但是所有角色都可访问。

订单信息页和管理页需要登录且只有管理员具备权限访问。其中用户管理页和商品管理页是管理页的嵌套路由

管理员能在用户管理页设置各个用户的各项权限

如管理员的菜单如下：

个人信息

订单信息

管理

---用户管理
---商品管理

### 4.3.2 菜单权限控制

默认路由为f个人主页，未登录时跳转到登录页，登录同时后端会返回权限列表，普通用户的菜单只有个人主页，管理员的菜单有个人主页、订单信息和管理（用户管理、商品管理）。

路由配置共有一条默认路由，一条NotFound路由和六条页面路由。其中管理页路由又有两个嵌套路由

但是由于菜单控制一般都要配合页面控制，所以路由配置不能写死，初始只配置不需要权限的路由，需要权限的路由根据权限列表由动态路由addRoute()动态添加

后端返回的菜单权限有可能是只有需要权限的菜单（如管理），也有可能是连个人主页也返回，这里就以只返回需要权限的菜单。

路由配置：

```
const route = [
  {
     // 默认路由
     path: '/',
     redirect: '/profile'
  },
  {
     //NotFound路由
     path: '/:catchAll(.*)',
     component: () => import(...)  
  },
  {
     path: '/login',
     component: () => import(...)  
  },
  {
     path: '/profile',
     component: () => import(...)  
  }
]
```

登录拿到权限列表后，就可以实现菜单/路由权限，分两种：

（1）后端实现

后端把权限信息、菜单信息和路由信息都返回了，前端必须要有一个菜单/路由管理的页面。

适合体量大，菜单变动多的项目。

缺陷：前后端开发人员需要高度配合。此外，后端返回的路由信息不一定是规范的，需要前端自行转换。

```
/*
管理员登录，后端返回的数据模拟：
token: '...',
rights:[
  {
    ...
  },
  {
    name: 'manage',
    title: '管理',
    icon: 'xxx',
    path: '/manage',
    url: '/Manage/Manage.vue',
    children: [
      ...
    ]
  }
]
普通用户登录rights则是空数组
*/

axios({
  //登录
}).then(res => {
  /* 拿到token并保存到storage和vuex的操作... */
  //拿到菜单权限，并保存到本地和vuex
  for(let i of res.data.rights){
    //若有多级菜单，就多套一层循环，视情况是配置普通路由还是嵌套路由
    this.$router.addRoute({
      path: i.path,
      name: i.name,
      component: () => import('...' + i.componentURL)
    ))
  }
  localStorage.set('rights',res.data.rights)
  this.$store.commit('setRights',res.data.rights)
})
```

（1）前端实现

后端不返回路由信息或菜单信息，这两个信息存储在前端，拿到权限信息后，在丛中筛选出对应的路由、菜单。

适合体量小，菜单变动少的项目，实现起来比较简单。

缺陷：路由信息、菜单信息存储在前端，一旦要修改这些信息就要重新打包前端。

① 前端实现方案1，后台只返回了菜单信息和权限信息，没有路由信息

需要前端先定义全部路由的数组，根据后台返回的权限来筛选出相应的路由并动态添加到路由配置

返回的权限信息可能是标识字符串，也可能是是角色信息，若是角色信息，则meta的内容就是角色，根据角色筛选权限，若是标识，就是下面的代码

```
/*
管理员登录，后端返回的数据模拟：
token: '...',
rights:[
  {
    ...
  },
  {
    name: 'manage',
    title: '管理',
    icon: 'xxx',
    children: [
      ...
    ]
  }
]
普通用户登录rights则是空数组
*/
//先定义好全部路由,若后台返回的name能和路由的name对应，也可以不要meta
const allRoutes = [
  {
    ...
  },
  {
    path: '/manage',
    url: '/Manage/Manage.vue',
    meta: {
      name: 'manage'
    },
    children: [
      ...
    ]
  }
]
//筛选路由的方法
function filteRoutes(userRoutes, allRoutes){
    let routes = [], allRoutesCopy = 深拷贝(allRoutes)
    for(let userR of userRoutes){
        for(let allR of allRoutesCopy){
            if(userR.name == allR.meta.name){
                if(userR?.children?.length > 0){
                  allR.children = filteRoutes(userR.children,allR.children)
                }
                else delete allR.children
                routes.push(allR)
            }
        }
    }
    return routes
}

//登录拿到权限列表的代码略
```

② 前端实现方案2，后端只返回权限信息，菜单信息和路由信息都不返回

需要在①的基础上在meta加入菜单信息即可

③ 前端实现方案3，不太推荐，后端只返回权限信息和路由信息，不返回菜单

把①的先定义全部路由改为先定义全部菜单，筛选路由改为筛选菜单即可

其他：

权限菜单路由信息和token一样需要持久化存储。

动态路由保持持久化，在App.vue的create()中，若有token，则根据storage的rights来重新addRoute()

退出登录时，需要清除storage和vuex的token和权限信息，removeRoute()对应路由或代码刷新页面

缺陷就是用户可以通过控制台自己addRoute()再push()达到非法进入页面的目的

若有动态默认路由的需求，可使用addRouter添加默认路由，修改默认路由通过router.getRoutes()[0].redirect == '/xxx'

#### 4.3.3 页面/路由权限控制

上面的NotFound路由和动态路由其实已经涉及了大部分页面/路由控制，就差一个登录状态的判断了

组件内守卫或独享守卫配置，缺陷就是每一个需要登录的页面都要配置；

```
//以组件内守卫为例
beforeRouteEnter(to,from,next){
  if(sessionStorage.getItem('token') != null) next()
  else  next({path: '/login'})
}

/*
路由守卫中，next({path: '/login'})跳转到登录页时，可以正常跳转，但是报错 ...via a navigation...
解决：
路由文件中：
const originalPush = VueRouter.prototype.push
VueRouter.prototype.push = function push(location, onResolve, onReject){
  if (onResolve || onReject) return originalPush.call(this, location, onResolve, onReject)
  return originalPush.call(this, location).catch(err => err)
}
其本质是跳转报错时，catch捕获异常，所以还是没有解决根本的问题，只是没有报错了
*/
```

也可以全局前置守卫中配置，更方便：

```
//路由的js文件中
...
router.beforeEach((from,to,next) => {

  if(sessionStorage.getItem('token') != null) next()
  else  next({path: '/login'})
})
```

#### 4.3.4 按钮/超链接权限控制

后端返回的权限列表里，可能也会有按钮的权限，一种是返回增删改查的权限，按钮根据增删改考察的类型来设置权限，一种是返回特定按钮的布尔值。在筛选路由的同时可以把按钮权限存到对应路由配置的meta中。

根据权限信息来v-if，v-show来隐藏，但是比较麻烦。最方便的实现就是全局自定义指令，需要权限的按钮绑定自定义指令，自定义指令内部根据当前路由的meta取得权限信息，来隐藏/禁用/删除按钮。

【警告】在某些情况下，使用自定义指令v-permission将无效。例如：元素UI的选项卡组件或el表格列以及其他动态渲染dom的场景。您只能使用v-if来执行此操作

#### 4.3.5 请求权限控制

分为token鉴权和截断无权限请求

token鉴权不再赘述

截断无权限请求：在发送请求前，先根据当前路由的meta的权限信息判断是否有权发送。在筛选路由的同时可以把请求权限存到对应路由配置的meta中。

后端接口如果设计比较规范的，如restfulAPI，可能会返回增删改查的权限，前端根据请求类型的设置权限

# 四、文件上传

## 1 前端读取文件

在文件上传时，有可能会在前端读取文件，但不是必须的

file表单读取文件

```
//选择是获取文本内容，注意先清空自己变量的数据
 if(event.target.files.length != 0){
 let file = event.target.files[0]
 const fileReader=new FileReader()
 fileReader.readAsText(file,'utf8') //编码要与csv文件的编码一致，否则中文乱码
 fileReader.onload=()=>{ //读取完成时回调
 let res = fileReader.result,str='' //读取结果保存在result
 //已经得到文本内容res，接下来取出首行并转成数组，赋值给变量展示select
 }
 }
```

## 2 文件上传前需要知道的内容

（1）后端文件存储形式

* 将整个文件以二进制形式存入数据库（不推荐）

* 存在后端服务器某个目录，数据库存放文件的路径

* 存放到另一个服务器（文件服务器）或第三方服务器，数据库存放网络url

（2）文件上传模块样式方面的设计：

* file表单隐藏，通过自定义按钮来触发file表单的点击

* 文件选择和文件上传可以分开，也可以合并

* 选择文件的方式也可以是拖拽，事件dragenter,dragleave,dragover,drop分别是拖拽移入，拖拽移开，拖拽在框里移动，拖拽放入触发，拖拽放入时，浏览器会触发默认行为（打开新页面并显示文件内容），自己需要关闭默认行为。drapenter，drapleave可以用来设置样式，drapover和drop需要e.preventDefault()关闭默认行为（根据需要也可以关闭整个浏览器的这个行为），drop里面用e.dataTransfer.files获得文件对象。

* 上传时，通过css修改样式，js修改按钮描述内容和禁用按钮

（3）文件上传需要实现一些限制条件

* 文件类型限制：
  
  ```
  //两种方法任选一个
          //这样限制，文件选择框变成只有这些格式的文件
          <input type="file" accept=".jpg,.png">
          //这样限制，文件选择框还有其他类型文件
          if(!/(jpg|png)/i.test(file.type)){
            console.log('不支持的格式')
            return
          }
  ```

* 文件大小限制：
  
  ```
  if(file.size > 2*1024*1024){
            console.log('文件超过2M，无法上传')
            return
          }
  ```

（4）上传成功后，显示已选文件列表：

* 单文件直接显示就行

* 多文件可以实现删除功能，利用li事件委托到ul实现

（5）已选文件预览/缩略图：

* 图片，先将图片转化为base64码，再将base64码赋值给img的src即能实现缩略图
  
  ```
  function fileToBase64(file){
   return new Promise((resolve,reject) => {
   let fileReader = new FileReader()
   fileReader.readAsDataURL(file) //这是异步的，需要下面事件监听处理完成
   fileReader.onload = e => {
   resolve(e.target.result)
   }
   })
   }
  ```

* 文本，可以用FileReader实现预览

* 其他类型的文件，为了美观可以用图标表示缩略图

（6）上传进度：

axios的配置项onUploadProgress可以实时监听，至于上传速度可以用已上传大小和已花费时间计算，剩余时间可以用上传速度和剩余大小计算

```
onUploadProgress: progress => {
 console.log('当前已上传:',progress.loaded,'字节')
 console.log('文件总大小:',progress.total,'字节')
 console.log('当前百分比:',Math.round((progress.loaded*100)/progress.total) + '%')
}
```

（7）HASH命名文件：

后端为了避免上传的文件与服务器中原有文件重名，会根据上传的文件弄出一个HASH值来对文件命名（如multer中间件），但有的后端不处理，则需要前端自己处理。使用SparkMD5，根据buffer格式的文件生成HASH值

```
import SparkMD5 from 'spark-md5'

//先将文件对象转为buffer
 function fileToBuffer(file){
 return new Promise((resolve,reject) => {
 let fileReader = new FileReader()
 fileReader.readAsArrayBuffer(file)
 fileReader.onload = e => {
 resolve(e.target.result)
 }
 })
 }
 //生成HASHa
 asnyc function(file){
 let buffer = await fileToBuffer(file)
 let sparkmd5 = new SparkMD5.ArrayBuffer()
 sparkmd5.append(buffer)
 let HASH = sparkmd5.end()
 //HASH的值只跟文件内容有关(与文件名无关)，文件内容完全一样HASH就一样
 //下面根据需要可以将文件命名为 HASH.后缀名，有时也直接命名为HASH
 }
```

## 3 文件上传的不同实现

### 3.1 单文件上传（FormData）

post请求，请求体放FormData，设置请求头

```
headers: {"Content-Type": "multipart/form-data"}
```

但是这样设置有时候会报错，说找不到边界，可以换成：headers: false

前端代码：

```
<template>
      <div id="upload">
        <input ref="inp" type="file" style="display: none;" @change="upload">
        <button @click="clickUpload">点击上传</button>
      </div>
    </template>

    <script>
    import {request} from '../network/index.js'

    export default {
      methods: {
        clickUpload(){
          this.$refs.inp.click()
        },
        upload(e){
          const file = e.target.files[0]
          const formData = new FormData()
          //append的第一/二个参数分别是键和值，键可以根据需要自定义名，方便后端处理
          //如append('fileName',file.name) append('HASH',hash值)
          formData.append('file',file)
          request({
            url: '/upload',
            method: "post",
            data: formData,
            headers: false,
          }).then(res => {
            console.log(res.data)
          })
        }
      }
    }
    </script>
```

后端代码：

```
const express = require('express')
      const fs = require('fs')
      const multer = require('multer')
      const app = express()

      //解析FormData并放到对应目录的中间件
      const UploadMiddle = multer({

        dest: './upload/'

      })

      //multer为了防止重名覆盖原有文件，会将文件名命名为随机序列并且没有后缀名，需要自己重新命名
      app.post('/upload',UploadMiddle.any(),(req,res) => {

        const newName = './upload/' + req.files[0].originalname
        fs.rename(req.files[0].path, newName, (err) => {
          if(err) res.send("上传失败")
          else    res.send('上传成功')
        })

      })
```

### 3.2 单文件上传（base64）

适合图片，音频，视频，图片居多

post请求，请求体base64

请求头

```
headers:{'Content-Type':'application/x-www-dorm-urlencoded'}
```

## 3.3 多文件上传

选择文件，一是file表单增加属性multiple，一次选多个，在change事件中将files数组的元素全append到FormData，二是不加multiple，一次选一个，每次change将files[0]的文件append到已声明的FormData，最终都是得到含有多个file对象的FormData

上传文件也有两种方式，一是一次性上传全部file（但无法获得进度），后端通过req.files得到各个file信息并改名。二是每个file单独上传（能获得每个file的进度），都断与单文件上传一样。

## 3.4 大文件上传（切片与断点续传）

前端代码：

```
async function upload(e){
 const file = e.target.files[0]
 //1.为了标识切片，需要给每个切片命名为 HASH_数字.后缀
 //1.1 后缀名
 let fileName = file.name.split('.')
 let suffix = fileName[fileName.length-1]
 //1.2 HASH
 let buffer = await this.fileToBuffer(file)
 let sparkmd5 = new SparkMD5.ArrayBuffer()
 sparkmd5.append(buffer)
 let HASH = sparkmd5.end()

//2.切片可以固定数量或固定大小，但切片不要太多建议设置最大切片数量，推荐先固定大小，看有多少切片，若切片数量多于最大数量，则就切最大数量的切片
 //2.1 确定切片数
 let chunkSize = 1024 * 100, maxSum = 100
 let chunkSum = Math.ceil(file.size / chunkSize)
 if(chunkSum > maxSum){
 chunkSum = maxSum
 chunkSize = 
}

let chunks = []
 //2.2 先看后端是否有已上传的切片
 let alreadyList = await request({
 url: '/already',
 method: 'get',
 params: {
 HASH
 }
 })
 alreadyList = alreadyList.data.map(i => parseInt(i))
 //2.3 确定未上传的切片index
 let chunkIndex = []
 for(let i=0;i<chunkSum;i++) chunkIndex.push(i)
 chunkIndex = [...new Set([...chunkIndex])].filter( i => !new Set([...alreadyList]).has(i))

//3 开始切片，file.slice(a,b)切片，左闭右开,chunks存放每个切片的名字和值
 //3.1 若此时切片都已上传，但未合并
 if(chunkSum == alreadyList.length){
 request({
 url: '/merge',
 method: 'post',
 data: {
 HASH: HASH,
 fileName: file.name,
 chunkSum
 }
 }).then(r => {
 console.log(r.data)
 })
 }
 //3.2 切片从未上传过，或上传了部分切片
 else {
 for(let i of chunkIndex){
 let chunk = null
 if(i == chunkSum - 1) chunk = file.slice(i * chunkSize,file.size)
 else chunk = file.slice(i * chunkSize,i * chunkSize + chunkSize)
 chunks.push({
 name: `${HASH}_${i}.${suffix}`,
 chunk
 }) 
}
 //4.发送请求，进度可以用已上传的切片数来确定
 //4.1 上传切片
 let res = await Promise.all(chunks.map(c => {
 let formData = new FormData()
 formData.append('chunk',c.chunk)
 formData.append('name',c.name)
 return request({
 url: '/upload',
 method: 'post',
 data: formData,
 headers: false
 })
 }))
 console.log(res)
 res = await request({
 url: '/merge',
 method: 'post',
 data: {
 HASH: HASH,
 fileName: file.name,
 chunkSum,
 }
 })
 console.log(res)
 }
}
```

后端代码：

```
const express = require('express')
const fs = require('fs')
const bodyParser = require('body-parser')
const multiparty = require('multiparty')

const app = express()
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: false }))

app.all("*", (request, response, next) => {
 response.header("Access-Control-Allow-Origin", "*");
 response.setHeader("Access-Control-Allow-Headers","content-type,Authorization")
 if (request.method == 'OPTIONS') response.send(200);  
 else next();
})

//获取已上传的切片
app.get('/already',(req,res) => {
 const {HASH} = req.query
 let nameList = []
 if(fs.existsSync( './upload/'+HASH))
 nameList = fs.readdirSync('./upload/'+HASH).sort((a,b) => a-b)
 res.send(nameList)
})

//上传切片
app.post('/upload',async (req,res) => {
 let form = new multiparty.Form({uploadDir: './upload'})
 //form.parse()会将文件保存到设置的路径
 form.parse(req,async (err,fields,files) => {
 //fields是前端formData.append()的非FormData类型数据
 //files是文件的路径等信息,
 const index = fields.name[0].match(/(?<=_)\d+(?=.)/)['0']
 const dir = fields.name[0].match(/.+(?=_\d+)/)['0']
 //创建存放切片的目录
 if(!fs.existsSync( './upload/'+dir)) fs.mkdirSync('./upload/'+dir,err => {})
 //将切片移动到创建的目录
 //用常规的移动文件也可以，但有大小限制，推荐用流写入
 const buffer = fs.readFileSync(files.chunk[0].path)
 let ws = fs.createWriteStream(`./upload/${dir}/${index}`)
 ws.write(buffer)
 ws.close()
 //删除留在外面的切片文件
 fs.unlinkSync(files.chunk[0].path,err => {})
 res.send(index)
 })
})

//合并切片
const Buffer = require('buffer').Buffer
app.post('/merge',(req,res) => {
 const {HASH,fileName,chunkSum} = req.body
 //得到所有切片的名字
 const nameList = fs.readdirSync('./upload/'+HASH)
 if(nameList.length < chunkSum){
 res.send('上传失败')
 return
 }
 //排序切片名
 nameList.sort((a,b) => a-b)
 //合并切片需要buffer格式的切片的数组，和所有切片的总字节
 let Byte = 0, bufferList = []
 for(let name of nameList){
 let buffer = fs.readFileSync(`./upload/${HASH}/${name}`)
 bufferList.push(buffer)
 Byte += buffer.length
 }
 let mergeBuffer = Buffer.concat(bufferList,Byte)
 //以流的形式写入文件，没有大小限制
 let ws = fs.createWriteStream('./upload/'+fileName)
 ws.write(mergeBuffer)
 ws.close()
 //合并完成，删除存放切片的临时文件夹
 fs.readdirSync(`./upload/${HASH}`).forEach(name => {
 fs.unlinkSync(`./upload/${HASH}/${name}`)
 })
 fs.rmdirSync(`./upload/${HASH}`)
 res.send('上传成功')
})

app.listen(8000,()=>[
 console.log('服务已启动') 
])
```

# 五、文件下载

正常情况下，部署到静态文件夹的文件，浏览器输入或a标签的href是这个文件的url，若文件是浏览器无法解析的，如exe，csv等，则会进行下载；若是浏览器可以解析的，如html，图片等，则不进行下载，而是预览。

H5的a标签增加了新属性download，加上之后，html、图片等等也会进行下载，但是只在同源下有效（即使前端、后端设置了允许跨域也不行），跨域需要另外的解决方案。

前端发送下载请求，后端一般会返回url或文件流。

## 1 返回下载url

几种解决方案；

* 直接把url放a标签里，a标签默认且只能get请求，所以url有长度限制，且download是H5特性IE有兼容问题。

* form表单下载，最传统无兼容性问题，form可以get或post请求，但无法下载浏览器可解析的文件，如html，图片等等。

* window.open() 或 location.href = url， 简单一行代码，缺点是url长度限制和编码限制，无法下载html，图片等。

* iframe，优缺点基本与直接用a标签一样，但兼容性和性能差。

* ajax请求获取下载url，再生成a标签下载。

除了ajax的方案都有无法监听返回是否成功和进度，无法携带token的问题。

以下是ajax请求uri生成a标签的方案：

前端代码：

```
axios({
 url: 'localhost:8000/download',
 method: 'get',
 params: {
 ...  
 },
 }).then(res => {
 let url = res.data.url, fileName = res.data.fileNmae  
 let ele = document.createElement("a")  
 ele.style.display = 'none'  
 ele.href = url  
 ele.download = fileName  
 document.querySelectorAll("body")[0].appendChild(ele)  
 ele.click()  
 ele.remove()
 })
```

后端代码：

```
app.post('/download',(req,res) => {
 //根据req的参数得到要下载的文件url
 res.send(...) 
}）
```

## 2 返回文件流

url下载最大的问题就是跨域情况下无法下载浏览器可预览的html，图片等文件，文件流式一种解决方案，一般返回blob或base64。

流程是ajax获得文件流后，转化成本地url再用a标签进行下载，可以看出，虽然解决了跨域问题，但是它相当于先下载完成后再出现文件保存框，用户体验性不好，若果文件太大，等待时间更久。

以下是文件流为blob的代码：

前端代码：

```
axios({
 url: 'localhost:8000/download',
 method: 'get',
 responseType: 'blob',
 params: {
 ...
 }
 }).then(res => {
 if(!res) {
 console.log('下载失败')
 return
 }
 let blob = new Blob([res.data],{
 type: 'image/png' //可以查阅blob.type
 })
 let url = window.URL.createObjectURL(blob)  
 let ele = document.createElement("a")  
 ele.style.display = 'none'  
 ele.href = url  
 ele.download = '123' //有了blob的type后缀会自己加上  
 document.querySelectorAll("body")[0].appendChild(ele)  
 ele.click()  
 ele.remove()
 })
```

后端代码：

```
app.get('/download',(req,res) => {
 res.download('./public/a.png')
 })
```

## 3 大文件下载

# 六、资源访问

## 1 数据

直接以JSON格式返回数据库的数据

## 2 图片

图片保存在静态资源文件夹，返回网络URL，若多次请求传的数据不同，且后端由这些数据产生的图片命名相同覆盖，则浏览器会缓存第一次返回的托片而无法获得新图片，解决：返回图片url时， 给url加上时间戳或随机数，使得每次返回的url都不同，就不会缓存了。

# 七、Web Socket

HTML5的新特性，之所以不记在HTML笔记或ajax笔记里，是因为它需要结合后端。

WebSocket是一种网络通信协议，可以实现全双工通信，常用于实现聊天室等。

http是单向的，通过客户端发请求，服务端响应回去；而WebSocket可以服务端主动推送给客户端。

前端：

这是原生js的写法，

后端：
