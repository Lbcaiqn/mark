# 一、基本

域名：

* 127\.0\.0\.1 为本机，域名为 localhost

* 从右往左解析，不区分大小写

* 构成：
  
  * 次级域名\.顶级域名，如 www.example.com ，分别是三级、二级、顶级域名
  
  * 次级域名\.公共后缀，如 www.example.github.io ，分别是四级 \~ 顶级域名，其中 github\.op 是公共后缀：
    
    * 公共后缀是一个标准，如 \.com ，.github\.io ，具体可查阅 https://publicsuffix.org/list/
    
    * 顶级域名一定是公共后缀，反之则不然

* 站点域：次级域名\.公共后缀，可以不断划分子域，如 sub\.example\.com 是 example\.com 的子域

（2）域名映射

有时在开发环境需要把 localhost 映射为其他域名，这里使用 whistle \+ Prosy Switch Omega 。

```
npm install -g whistle
w2 start
```

管理员权限修改 hosts 文件：

```
# windows 在 C:\Windows\System32\drivers\etc\hosts
# Linux 、mac 在 /etc/hosts

127.0.0.1 a.test
127.0.0.1 b.test
```

终端 ping 测试是否配置成功：

```
ping a.test
ping b.test
```

浏览器输入 localhost\:8899 进入 whistle 配置页面，在 Rules 中配置：

```
a.test 127.0.0.1
b.test 127.0.0.1
```

chrome 安装插件 Proxy Switch Omega \-\> 点击插件 \-\> 选项 \-\> 进入配置页面 \-\> 左侧栏的添加情景模式 \-> 输入代理名并配置为 http\://127.0.0.1\:8899 \-\> 左侧栏的应用选项。

当需要进入 a\.test 和 b\.test 时，把 Switch Omega 的代理设置为刚才配置的代理即可，访问 localhost 依然有效，也不用代理。

这样，localhost ，a\.test ，b\.test 就是三个不同的站点域。 

# 一、ajax

狭义的ajax就是指ajax这个技术。

广义的ajax泛指通过ajax实现的网络请求技术的统称，如fetch，axios等。

## 1 基本

ajax：异步的js和xml
可以在不刷新页面的情况下，向服务器发送http请求，和接收服务器的http相应。
XML：可扩展标记语言，由标签组成，与HTML的区别：

* XML用来传输和存储数据，HTML用来呈现数据

* XML没有预定义的标签，标签都是自定义的

ajax特点：
优点：

- 可以在不刷新页面情况下发送网络请求

- 允许用户的事件更新页面的内容，即可以在事件函数中发送网络请求

缺点：

- 没有浏览历史，不能回退

- 不能跨域（跨域：一个域名向另一个域名发送请求，JSONP可解决）

- SEO(搜索引擎优化)不友好，因为页面展示的的数据，大部分是网络请求过来的数据保存在变量中的，这样爬虫就无法通过源代码获得数据

## 2 JSON

早期的ajax使用的是xml格式，服务器返回的也是xml格式的字符串，不过现在的ajax使用的都是json格式，json格式更简洁，且json有自带的数据转换api，数据转换更方便。数据格式基本与js数据类型一样，JSON.xxx()可以将js的数据类型转换成JSON格式，如JSON.stringify()可以将js数据转换成JSON字符串

### 2.1 JSON的格式

JSON的表现形式有JSON文件和JSON字符串。

xxx.json文件内容为JSON对象，通常作为配置文件使用，注意无法写注释

JSON字符串常用于数据传输，内容可以不仅仅是对象，还可以是数组，基本数据类型。但函数不行。

JSON格式是JavaScript对象的表示形式，但是在格式上严格一些

- value为字符串时，用双引号就包裹

- key要用双引号包裹

- 最后一个属性结束不能加逗号

由于JSON字符串里面内容还可以是数组/基本数据类型，所以也有严格的规定：

* 数组最后一个元素后不能有逗号

* 数组的字符串元素，基本数据类型的字符串必须是双引号

### 2.2 JSON的api

js自带，用于将对象序列化为字符串，和字符串恢复为对象。JSON的api需要的对象不一定是JSON对象，普通js对象也可以。此外。

可以将对象和非对象直接序列化为字符串，但也只有对象和数组序列化常用些。

序列化对象时，会变成严格的JSON格式

序列化数组时，字符串元素单引号变双引号，数组最后一个元素后的逗号去掉。

序列化基本数据类型的字符串，单引号变双引号

```
JSON.stringify(obj)  //将对象序列化为字符串
JSON.parse(string)   //将字符串还原为对象
```

在使用JSON.stringify进行深拷贝或者ajax传输数据时，需要考虑它的限制性：

（1）JSON.stringify()序列化对象的限制：

- 值为undefined，值为函数，Symbole键的属性，Symbole值的属性都会被忽略

- 值为NaN变为null，值为Date变为字符串

- 值为RegExp/Set/WeakSet/Map/WeakMap类型，变成空对象，可以使用一些方法来解决，如使用Arra.from()将Map转化为二维数组，二维数组再转为Map

- 若源对象给原型上绑定了自定义的属性和方法，也无法拷贝过来

- 处理循环引用和BigInt直接报错

（2）JSON.stringify()序列化数组的限制：

和序列化对象差不多，区别在于，undefined，Symbol和函数变为null，其他一样。

（3）JSON.stringify()序列化其他类型的限制：

- 直接序列化Number，String，Boolean，null正常，NaN变null，undefined/Symbole/函数不处理直接忽略。BigInt报错

- Date变字符串，RegExp/Set/WeakSet/Map/WeakMap变空对象

- Vue3的ref，reactive变为普通对象

（4）JSON.parse()的要求：

* 无法处理 ''  'undefined'  'NaN'

* 字符串还原对象时，必须是严格的JSON格式，如JSON.parse('{"a":123}')

* 字符串还原数组时，字符串元素必须是双引号，最后一个元素后不能有逗号，如JSON.parse('[123,"abc"]')

* 字符串还原成字符串时，必须是双引号，如JSON.parse('"str"')

### 2.3 JSON的前后端传输

后端：
若响应体只是字符串，直接传就可以
若想返回给客服端对象等数据类型，则需要将其转成JSON字符串：
JSON.stringify()

若使用express，则不需要手动转化，它自己会转化

```
res.send({a: 1})
```

前端：
若服务端返回的只是字符串，直接用就可以
若服务器返回的是转换后的JSON字符串，则组要转化，有两种方式：

* 主动转换：JSON.parse()

* 自动转换：onreadysttatechange事件函数外：xhr.responseType=’jspn’，数据就可以直接用了。

* axios默认是自动转换

## 3 原生ajax

```
//如在事件函数中：
//1.创建对象
let xhr=new XMLHttpRequest()

//2.初始化，设置请求类型和url，GET请求可以加上query参数  ?k=v&&k=v 
xhr.open('GET','http://127.0.0.1:8000/aaa?a=100&&b=200')
//设置请求头，可不写，参数为请求体信息和send()的参数查询字符串的类型
//通常用来做身份校验信息；也可以自定义信息，但是需要服务端特殊处理才能设置
xhr.setRequestHeader('Content-Type','application/x-www-form-urlencoded')

//3.GET请求参数为空，POST请求需要传入参数，参数格式需要服务端能够处理解析的格式
//一般有两种格式  k=v&&k=v  或  k:v&&k:v
xhr.send()

//4.事件绑定，处理服务端返回的结果
/* xhr.readystate的值 0:未初始化 1:open()调用完毕 2:send() 调用完毕 3:服务端返回了部分结果 4:服务端返回了全部结果
该事件是每当xhr.readystate发生改变就触发，共触发4次 0变1变2变3变4 */
xhr.onreadystatechange=function(){
//当服务端返回了全部结果时，才处理
if(xhr.readyState==4){
//当状态码为成功时，才处理
    if(xhr.status>=200 && xhr.status<=300){
      //处理响应结果
      console.log(xhr.status) //状态码
      console.log(xhr.statusText) //状态字符串
      console.log(xhr.getAllResponseHeaders) //相应头
      console.log(xhr.response) //响应体
    }
  }
}
```

IE浏览器ajax缓存问题：
ajax发送请求得到相应结果后，IE浏览器会缓存相应结果，ajax再次发送请求时，只会得到缓存的相应结果，得不到新的相应结果：
解决：通过给url增加时间戳的query参数，使得每次的请求的url都不同，就不会使用缓存的相应结果。
open() 的url形参：
原：’…./xxx’  解决：’…./xxx?t=’+Data.now()

请求超时处理：
onreadystatechange事件函数外：
xhr.timeout=数值毫秒   //超时后自动取消请求
xhr.ontimeout=function(){}  //超时后回调

网络异常处理：
onreadystatechange事件函数外：
xhr.onerror=function(){}  //网络异常时回调

主动取消请求：
在需要的地方，如点击事件内：xhr.abort()
但是发送请求和取消请求在不同的函数作用域，所以xhr要定义在全局：
let xhr=null  //必须是let，因为xhr涉及改变
请求时再 xhr=new XMLHttpRequest()
取消请求时 xhr.abort()

解决重复发送相同请求：
当重复发送相同请求时，是没有必要的，服务器也会增大压力。相同的请求发一次就够了

* 全局定义一个布尔变量let flag=false标识是否发送了请求

* 当flag为true时，取消请求

* 发送请求后，设为true

* onreadystatechange事件函数内，当readystate==4时就设为false，不需要进入判断状态码。

时间戳格式化：

后端接口返回的时间数据一般都是时间戳，这是为了能够多样化的显示时间，所以前端需要将时间戳格式化为自定义的时间格式才能展示

```
export function formatDate(datetime: Date | string | number, fmt: string): string {
  /*使用说明
  参数： datetime(数值或字符串类型，时间戳)，fmt(字符串类型，正则)
  示例：
  yyyy-MM-dd               2022-8-10
  dd/MM yyyy               10/8 2022
  yyyy年0M月0d日 0h:0m:0s  2022年08月01日 15:25:49

  */
  /*
  时间戳有三种：
  第一种：精确到毫秒，共13位
  第二种：精确到秒，共13位（最后三位为0）
  第三种：精确到秒，共10位
  所以传入的时间戳若是10位，需要*1000才能获得正确的时间
  该函数若传入精确到毫秒的时间戳也能正常使用，只是没有写获取毫秒数的代码
  */

  let date = new Date(String(datetime).length == 10 ? Number(datetime) * 1000 : Number(datetime));

  const o: any = {
    'M+': date.getMonth() + 1,
    'd+': date.getDate(),
    'h+': date.getHours(),
    'm+': date.getMinutes(),
    's+': date.getSeconds(),
  };

  if (/(y+)/.test(fmt)) fmt = fmt.replace(RegExp.$1, date.getFullYear() + '');

  for (const i in o) {
    let str = o[i] + '';
    if (new RegExp(`(0${i})`).test(fmt) && str.length >= 2) fmt = fmt.replace(RegExp.$1, str);
    else if (new RegExp(`(${i})`).test(fmt)) fmt = fmt.replace(RegExp.$1, str);
  }

  return fmt;
}
```

## 4 fetch

浏览器提供的原生api，返回Promise

```
// window.fetch(url,options)
fetch('...',{
  method: 'get'
}).then(res => {

}).catch(err => {})
```

## 5 jQuery的ajax

```
//引入
<script 
crossorigin="anonymous" src=https://cdn.bootcdn.net/ajax/libs/jquery/3.5.1/jquery.min.js
></script>
//使用
$.get(‘url’,{k=v,k=v},function(responseBody){},’json’)  $.post()参数一样
$.ajax({
  url:’...’,
  data:{k=v,k=v},
  dataType:’json’,
  type:’GET’,
  success:function(responseBody){},
  error:function(){},
  timeout: 2000,
  header:{}
})
```

## 6 axios

原生ajax配置和使用麻烦，而jqeury-ajax有需要导入jquery，都不适合，而vue有专门的axios
npm install axios --save    npm install axios –g
测试网站：
httpbin.org
http://123.207.32.32:8000/home/multidata

基本使用：

```
Import axios from ‘axios’
//方式一
axios({                
//配置选项除了url都可以省略
  baseURL:’’,   //最终url=baseURL+url，默认为空
  url:’...’ ,   // 可传params参数如：?key=’val’&key=’val’…
  method: ‘…’ , //省略后默认为get请求
  params: {…},    //get专用，可以将url的?后面的参数写在里面，简化url
  data:{},        //poet专用，请求体    
  …..
}).then( res => {…})        //axios会return一个promise对象，then，catch在axios()后面

//方式二
axios.请求类型(‘url’,{config})
fetch(‘url’,{config})

/*
方式三，并发请求：
一个请求需要多个子请求都完成后再开始
除了Promise.all(),还有更简便的方法
*/
axios.all([        //传入数组
  axios(),
  axios()
]).then(res=>{})    //所有子请求的结果都在res数组里
/*
若不想通过下标访问res数组，可以
then( axios.spread( (.. .. ..) => {} ) ) 就可以直接用小括号里的…变量直接访问
*/
```

封装使用：

可以给配置选项设置默认值，删除重复代码，如
axios.default.baseURL=”…”  //设置公共的url部分，简化url
然而，在真实项目中通常会有多个服务器，ip地址都不同，此时全局配置就不太合适了。
解决方法：
创建axios实例：
const instance1=axios.create(baseConfig)    //创建axios实例并配置默认值
instance1(config)    //使用与axios()一样
这样就可以创建多个实例来适配多个服务器

一般会做两侧封装：

```
//1.  /src/network/index.js  第一层封装
import axios from 'axios'
export function request1(config){
  //对该实例进行全局配置
  const instance1=axios.create({
    baseURL:'http://123.207.32.32:8000'
  })
  /*拦截器：
  分为请求拦截（拦截配置信息）和相应拦截（拦截请求结果），拦截成功后注意需要返回config和res，主要作用是对配置信息和请求结果进行一些处理，或其它特殊用途。
  */
  //拦截请求的配置信息
  instance1.interceptors.request.use(config => {
    //用处1 增删改查配置信息
    //用处2 请求状态时，给页面增加爱一些动画效果
    //用处3 请求需要token时(如登录)，提交登录信息
    return config
  },err => { console.log(err) })
  //拦截请求结果
  instance1.interceptors.response.use(res => {
    //用途1，根据状态码进行操作
    console.log(res.status)
    //用途2，对请求结果进行过滤，去掉浏览器给的无用信息
    return res.data
  },err => { console.log(err) })

  //instance是axios，会返回一个promise，通过return再将此promise返回到外部
  return instance1(config)
}

//2. /network/home.js  第二层封装
import instance from './index'

export function HomeRequestMultidata(){
  return instance({
    url: '/Home/multidata'
  })
}

export function HomeRequestGoods(type, page){
  return instance({
    url: '/Home/data',
    params: {
      type,
      page
    }
  })
}

//3. 用到的组件中
Import {HomeRequestMultidata} from '...'
HomeRequestMultidata().then().catch()
```

ts：

```
//1. /src/network/request.ts  第一层封装
import axios,{AxiosInstance,InternalAxiosRequestConfig,AxiosResponse} from 'axios'

let instance: AxiosInstance = axios.create({
  baseURL: 'http://152.136.185.210:7878/api/hy66',
  timeout: 1000 * 60
})
instance.interceptors.request.use((config: InternalAxiosRequestConfig) => {
  return config
})
instance.interceptors.response.use((res: AxiosResponse) => {
  return res
})
export default instance

//2. /src/network/index.ts  第二层封装
import {InternalAxiosRequestConfig,AxiosResponse} from 'axios'
import instance from './request'

export function HomeRequestMultidata(): Promise<AxiosResponse>{
  return instance({
    url: '/Home/multidata'
  })
}

export function HomeRequestGoods(type: string, page: number){
  return instance({
    url: '/Home/data',
    params: {
      type,
      page
    }
  })
}

//3. 用到的组件中
Import {HomeRequestMultidata} from '...'
HomeRequestMultidata().then().catch()
```

ts，请求拦截器中添加请求头需要注意：

可能会报错说headers可能为undefined，解决方法：

* config.headers = {...config.headers,xxx:'xxx'}

* config.headers!.xxx = 'xxx'

## 7 mock

在前段开发的时候，有时候可能后端接口还在开发中，这时候就可以用mock模拟后端接口，mock可以自定义数据或随机生成数据，可以拦截网络请求并返回模拟数据。

```
npm install --savce mockjs

#ts还需要安装types
npm install --save @types/mockjs
```

基本使用：

```
// /src/mock/xxx.json
...

// /src/mock/mockServer.js
import Mock from 'mockjs'
import xxx from './xxx.json'
Mock.mock("/abc", { code: 200, data: xxx })

// /src/main.js
import "@/mock/mockServer"

//使用
axios('/abc').then(res => {
  console.log(res.data)
})
```

# 二、http协议与网络调试

有关http协议的内容、get/post请求的区别、状态码等内容详见计算机网络笔记。 

网络调试：

F12—network—All--Name中是项目的所有html/js等，点开能看到请求/响应报文
其中，QueryString 能看到GET请求的query参数和POST请求的参数

# 三、跨域

（1）cookie

http 是无状态的协议，也就意味着后端服务器无法判断请求是由谁发起的，于是早期的 Web 应用就使用浏览器的 cookie 来保存登录状态。

可以在浏览器调试工具 \- application 中查看 cookie 。

cookie 的缺陷：

* 隐私泄露：对于用户来说，cookie 是非常容易泄露个人隐私的，因为 cookie 可以在不登录的情况下就能被请求携带。

* 较不安全：cookie 可以被跨站的请求携带，所以需要设置 samesite

cookie 的好处：

* 后台具有强控制性，可以随时把 cookie 设置为过期，而 jwt 不行

cookie 特性：

* 每条 cookie 的存储空间为 4KB ：
  
  * 本地打开 html 文件无法读写 cookie ，只有通过网络 url 访问的 html 才行
  
  * 前端可以 document\.cookie 读写 cookie ；后端可以在响应头中设置 cookie ，浏览器收到响应且允许后就会设置 cookie
  
  * 同一个浏览器中，cookie 在同提个站点域共享，不在一个站点域就是跨站，跨站没有跨域严格

* cookie 会再请求中携带：
  
  * 若是同一个站点域且不跨域的页面，发起的 ajax ，会自动携带
  
  * 若是跨域的页面，ajax 需要添加 credential 选项才会携带，同时后端在跨域的情况下还需要再设置允许 cookie 跨域；若是跨站的 ajax ，还需要把 samesite 设为 "none"
  
  * 具有请求属性的标签，如 img 、a 、iframe 、form 等，无论是否跨站，在早期的 Web 都会自动携带 cookie ，包括浏览器中其他站点域的 cookie ；但在 cookie 增加了 samesite 属性后，就由 samesite 决定，samesite 只能后端设置：
    
    * sameSite: "lax" ，默认值，跨站时，只允许 \<a\> 和 get 的 \<form\> 自动携带 cookie
    
    * sameSite\: "none" ，只有在 srcure\: true 才有效，否则视为 "lax"，无论是否跨站这些标签都会自动携带 cookie
    
    * sameSite: "strict" ，只有处于同一个站点域的页面，这些标签才会携带 cookie ，防止 CSRF 攻击
  
  * 除了 samesite 外，还有 2 个只有后端才能设置的 coolkie 属性，默认值为 false ：
    
    * HttpOnly ：不允许前端 JS 读写 cookie ，只允许在请求中携带，防止 XSS 攻击，不过调试工具 aplication 还能看到
    
    * srcure ：只允许在 https 协议中传输 cookie
- 前后端都能设置的 cookie 属性：
  
  * 作用域：
    
    * path ：默认值为根路径 "/" ，path 表示 cookie 在静态文件夹中的哪些路径可以使用
    
    * domain ：默认值（前端：当前域名；后端：请求来源的域名），表示 cookie 能在哪个站点域以及它的子域使用，若设置为其他站点域，cookie 就无法使用了，若设置为子域，则父域无法使用
  
  * 过期时间：
    
    * expires ：绝对过期时间，格式必须是 GMT 时间
    
    * max-age ：相对过期时间，优先级高于 expires ，以秒为单位
    
    * 若没有设置 expirs 和 max-age ，则 expires 默认值为 session，表示为一个会画 cookie ，关闭浏览器后清除（刷新、要转、关闭页面都不会清除）

前端读写 cookie ：

```
// 静态资源服务器，3000 、4000 都弄提个，用于测试

const express = require("express");
const path = require("path");

const app = express();
const PORT = 3000;

app.use(express.static(path.join(__dirname, "public")));

app.listen(PORT, () => {
  console.log(`Server is running at http://localhost:${PORT}`);
});
```

```
<!DOCTYPE html>
<html lang="en">
  <body>
    localhost:3000
  </body>

  <script>
    /**设置 cookie ---------------------------------------------------------------------
     * 不是普通的字符串赋值，浏览器内部会拦截处理
     * 一次只能设置一个 cookie
     * 由于 cookie 会在每个请求中携带，所以 cookie 最好只用于存储登录态，不存储大量数据，以免影响请求的速度
     */
    console.log("过期测试", document.cookie);

    document.cookie = "a=0;";
    document.cookie = "a=1;";
    document.cookie = `b=${encodeURIComponent(JSON.stringify({ b: 2 }))};`;

    // // 5s 后过期
    document.cookie = `c=3; expires=${new Date(
      Date.now() + 5000
    ).toUTCString()}`;

    // // 5s 后过期 ，优先级高于 expires ，若同时设置只有 max-age 有效
    document.cookie = "d=4; max-age=5;";

    console.log("seted", document.cookie, document.cookie.split(";"));

    /**删除 ---------------------------------------------------------------------------
     * 需要把过期时间修改为已经过去的时间
     * document.cookie = "" 是无效的
     */
    // Thu, 01 Jan 1970 00:00:00 GMT
    const expiredTime = new Date(0).toUTCString();

    document.cookie = `a=; expires=${expiredTime}`;
    document.cookie = "b=; max-age=-1;";

    console.log("deleted", document.cookie);

    // expires 、path 、domain 这里的默认值
    document.cookie = "e=5; expiress=session; path=/; domain=localhost";
  </script>

  <script src="https://cdn.jsdelivr.net/npm/js-cookie@3.0.5/dist/js.cookie.min.js"></script>
  <script>
    // 第三方库更方便读写 cookie ，有浏览器端的 js-cookie 和 node 的 cookie ，以 js-cookie 为例

    // 1 天后过期
    Cookies.set("name", "value", { expires: 1 });
    console.log(Cookies.get("name"));
    Cookies.remove("name");
  </script>
</html>
```

```
<!DOCTYPE html>
<html lang="en">
  <body>
    localhost:4000
  </body>

  <script>
    // 同提个站点域共享 cookie
    console.log(document.cookie);
  </script>
</html>
```

请求携带 cookie 以及 cookie 跨域：

```
// 后端， localhost:3333

const express = require("express");
const cors = require("cors");
const cookieParser = require("cookie-parser");

const app = express();
app.use(cookieParser());

// 跨域
app.use(
  cors({
    // cookie 跨域的 origin 不能设置为 "*"
    origin: "http://localhost:3000",
    credentials: true,
  })
);

app.get("/login", (req, res) => {
  // 响应头中设置 cookie
  res.cookie("token", "abc123", {
    // 只有后端才能设置 samesite 、HttpOnly 、srcure

    // 默认值都是 false
    httpOnly: false,
    secure: false,

    // 默认值 "lax" ，若 srcure 为 false 则 sameSite 设为 "none" 无效，视为 "lax"
    sameSite: "lax",
  });

  res.send("Cookie 已设置");
});

app.get("/data", (req, res) => {
  console.log(req.cookies);
  res.send("123");
});

const port = 3333;
app.listen(port, () => {
  console.log(`localhost:${port}`);
});
```

```
<!DOCTYPE html>
<html lang="en">
  <body>
    localhost:3000

    <!-- 处于同一个站点域，自动携带 cookie -->
    <img src="http://localhost:3333/data" />
  </body>

  <script>
    console.log(document.cookie);

    // // 请求后端设置一个 cookie
    fetch("http://localhost:3333/login", {
      method: "GET",

      // 跨域时若没有设置 credential ，即使后端响应头携带了 cookie ，前端也不会设置这个 cookie ；同源则不用
      credentials: "include",
    })
      .then((res) => res.text())
      .then((data) => {
        console.log(data, document.cookie);

        // 请求数据接口，携带 cookie 到后端
        fetch("http://localhost:3333/data", {
          method: "GET",

          // 跨域必须设置 credential ，才会携带 cookie ；同源则会自动携带
          credentials: "include",
        })
          .then((res) => res.text())
          .then((data) => console.log(data, document.cookie));
      });
  </script>
</html>
```

（2）网络安全

XSS 攻击（跨站脚本攻击）：

* 模拟：

* 解决方法：
  
  * 前端避免使用 innerHTML 等注入 html ；后端防止 SQL 注入
  
  * 前端使用 postMessage 时做好防范处理
  
  * 若是 cookie 则 HttpOnly 设为 true

CSRF 攻击（跨站请求伪造），针对 session \+ cookie 的登录模式，原理是利用跨站的 img 、a 等元素请求也能携带 cookie 的特性

* 模拟：
  
  ```
  // 后端， localhost:3333
  
  const express = require("express");
  const cors = require("cors");
  const cookieParser = require("cookie-parser");
  
  const app = express();
  app.use(cookieParser());
  
  app.use(
    cors({
      origin: "http://localhost:3000",
      credentials: true,
    })
  );
  
  app.get("/login", (req, res) => {
    res.cookie("token", "abc123");
    res.send("Cookie 已设置");
  });
  
  app.get("/data", (req, res) => {
    console.log(req.cookies);
    res.send("123");
  });
  
  const port = 3333;
  app.listen(port, () => {
    console.log(`localhost:${port}`);
  });
  ```
  
  ```
  <!DOCTYPE html>
  <html lang="en">
    <body>
      localhost:3000
    </body>
  
    <script>
      // 登录
      fetch("http://localhost:3333/login", {
        method: "GET",
        credentials: "include",
      })
        .then((res) => res.text())
        .then((data) => console.log("登录成功"));
    </script>
  </html>
  ```
  
  ```
  /**模拟 CSRF
   * 访问 http://example.com ，调试工具中运行下面的 JS ，点击生成的 <a>（<form> 会自动 submit），就攻击成功了，已经拿到跨站的 cookie 并伪造了一个有权限的请求
   * 由于后端是 http 协议，所以只能在 http 的页面中攻击
   * http 协议，secure 为 false ，samesite 为 "lax" ，所以只能用 <a> 和 get 的 <form> 模拟
   */
  
  // a 标签
  (function () {
    const a = document.createElement("a");
    a.href = "http://localhost:3333/data";
    a.textContent = "CSRF";
    a.style.fontSize = "100px";
    document.body.appendChild(a);
  })();
  
  // 设置 get 请求的 form
  (function () {
    const form = document.createElement("form");
    form.method = "get";
    form.action = "http://localhost:3333/data";
    document.body.appendChild(form);
    form.submit();
  })();
  ```

* 解决方法：
  
  * 后端接口遵循 Restful 规范，需要增删改的接口使用 POST 、PUT 、DELETE 请求，把参数放到请求体；但防不了 form 的 POST 请求
  
  * cookie 的 samesite 设为 '"strict' 

（2）同源策略与跨域

跨域问题只会出现PC端、移动端的浏览器，小程序/app则没有跨域问题，服务器与服务器之间也没有跨域问题。

浏览器虽然有跨域问题，但是不会限制script标签，link标签，iframe标签，img标签的跨域，a标签部分情况会限制跨域。

发送post，put，delete请求时若出现跨域问题，浏览器会自己先发送一个options请求进行预检查，以判断后端支不支持这类请求，后端需要对options请求做处理（详见nest笔记），前端就不用管了。

## 1 同源策略

浏览器的一种安全策略，当前网页的url和ajax请求目标资源的url两者之间必须协议，域名，端口保持一致。满足同源策略时，发送请求的url可以省略协议/域名/端口
ajax默认遵循同源策略，无法跨域。

跨域就是违背同源策略，即协议，域名，端口任意一个不同就是跨域。（http和https是不同的协议）

## 2 跨域的解决方案

分为前端解决和后端解决

### 2.1 前端解决

（1）JSONP
非官方的跨域解决方案，前端解决，只支持GET请求，实现原理是借助script标签实现跨域（img，a，link，script标签本身就具备跨域特性）

原生js实现：

```
func(data){//处理}
需要发送请求的内部，如点击事件；
let s=document.createElement(‘script’)
s.src=’url’
document.body.append(s)
通过script标签发送请求，服务端返回一个函数的调用，从而执行func() 
```

jquery实现：

```
$.getJSON(‘url?callback=?’,function(data){})
callback的值?其实是该回调函数，服务端获取该参数后，将其作为函数调用返回，然后在这个回调函数中对数据进行处理。
```

（2）proxy正向代理

跨域问题只存在于浏览器，服务器与服务器之间不存在跨域问题，难么如果将浏览器请求转发到本地同源的代理服务器中，再让这个代理服务器请求后端就能解决跨域问题。

如何使用：

比如请求一个后端接口 https://1.2.3.4:5000/login

```
//没有解决跨域时，这样一定会报错
axios.get('https://1.2.3.4:5000/login').then(res => {));
```

需要在vue.config.js或vite.config.js中配置：

```
//vue.config.js
module.exports = {
  devServer: {
    proxy: {
      '/xxx': {
        terget: 'https://1.2.3.4:5000',
        changeOrigin: true,  //允许跨域
        pathRewrite: {
          '^/xxx': ''
        }
      }
    }  
  }
}
```

如果用的是vite，则在vite.config.js中配置（vue 和 react 都一样）：

```
//vite.config.js
module.exports = {
  // ...
  server: {
    proxy: {
      '/api': {
        target: 'https://1.2.3.4:5000',
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/api/, '')
      }
    }
  }
}
```

react 中 craco.config.ts 配置不知道为什么无效，所以在 /src/setupProxy.ts 配置：

```
// /src/setupProxy.ts

const { createProxyMiddleware } = require("http-proxy-middleware");

module.exports = function (app) {
  app.use(
    createProxyMiddleware("/api", {
      target: "http://localhost:5555",
      changeOrigin: true,
      pathRewrite: {
        "^/api": "",
      },
    })
  );
};
```

配置完成后，发送请求，实际url会变为 https://1.2.3.4:5000/login

```
axios.get('/xxx/login').then(res => {})
```

原理解释：

当发送请求时，若遇到开头为xxx的url，请求就会转发到本地代理服务器，在url前面拼接target变成 'https;//1.2.3.4:5000/xxx/login'，在通过pathRewrite的配置将'/xxx'替换成''，最终本地代理服务器向后端请求的url变成了 'https://1.2.3.4:5000/login'

需要注意的是，target最后面的'/'和pathRewrite的''：

* target醉眠有'/'，pathRewrite替换为''，就是上面的情况，最终的url为'https://1.2.3.4:5000/login'

* target醉眠有'/'，pathRewrite替换为'/'，最终的url为'https://1.2.3.4:5000//login'，这样也没错，vue后自动将'//'换成'/'

* target醉眠有''，pathRewrite替换为''，最终的url为'https://1.2.3.4:5000login'，这样就不行了，因为处理后变成了错误的url

* target醉眠有''，pathRewrite替换为'/'，最终的url为'https://1.2.3.4:5000/login'，这样也可以得到正确的url

（3）nginx方向代理

原理和peoxy代理类似

vue

### 2.2 后端解决

CORS：
中文为跨域资源共享，后端解决，官方的跨域解决方案，客户端不需要额外的操作，只需要在服务端处理就能完成跨域。支持GET，POST等请求。
服务端只需设置相应头：
response.setHeader('Access-Control-Allow-Origin','*')
第一个参数是固定写法，第二个参数是允许发送请求的url，*表示所有url都允许

具体详见nest笔记

# 
