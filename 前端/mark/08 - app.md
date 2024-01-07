# 一、原生微信小程序

## 1 基本

微信小程序由于是运行在微信中而不是浏览器，所以无法使用DOM和BOM，但是可以调用微信环境的api（扫码，支付，定位等），也可以使用js的api

页面布局使用wxml，wxss，javascript

（1）开发环境

申请小程序开发账号   https://mp.weixin.qq.com/    注册小程序

（个人开发者只能注册个人主体，功能受限，微信认证，支付以及高级接口都无法使用）

开发管理-开发设置 可以看到APPID，开发时会用到

安装微信开发者工具  https://developers.weixin.qq.com/miniprogram/dev/devtools/stable.html)

黑色   设置-外观

代理  设置-代理-不适用代理    防止vpn冲突

## 2 配置文件

小程序整体由顶部导航条，背景区和tabBar组成（注意背景是页面底下的，不是页面本身）

### 2.1 app.json

全局配置文件

（1）page配置项放要展示的页面，第一个为首页

（2）window配置项用来配置窗口的样式（顶部导航条，背景区）

| navigationBarTitleText                       | string      |
| -------------------------------------------- | ----------- |
| navigationBarTextStyle                       | light,dark  |
| navigationBarBackgroundColor                 | #16         |
| backgroundColor                              | #16         |
| backgroundTextStyle                          | white,black |
| enablePullDownRefresh (是否开启下拉刷新，默认关)         | boolean     |
| onReachBottomDistance (上拉距底部多少距离触发对应事件，单位px) | number      |

"navigationStyle":"custom"  隐层导航栏

（3）tabBar配置项配置tabbar的样式：

可以放顶部和底部，2<=item数<=5，顶部只显示文本，底部显示icon和text

tabBar配置项属性（只有list数组的text和pagePath是必填项）：

pagePath必须是pages目录

*tabbar*页面会有类似keep-alive的效果，缓存状态；而非tabbar页面则没有。

```
"tabBar":{
  "list": [
    {
      "text":"首页",
      "pagePath":"pages/index/index",
      "iconPath":"static/...",
      "selectedIconPath":"..."
    },
    {"text":"分类","pagePath":"..."}
  ],
  "position":"bottom",
  "backgroundColor": "#000000",
  "borderStyle": "white",
  "color":"#000",
  "selectedColor":"#f00"
}
```

```
//自定义tabBar
1. app.json 的 tabBar配置项中，增加 "custom": true,这样就会使用自定义tabBar
注意，虽然默认的tabBar会失效，list的内容依然要写，一是为了区分tabBar页面和非tarbBar
A面，二是为了兼容低版本的客户端，在不能使用自定义的情况下能使用默认。
2.miniprogram文件夹下建立 custom-tab-bar 文件夹，存放tabBar组件，内容包括，wxml，
xss，js，json
3.wxml，wxss布局，js通过与 wx.switchTab()跳转tabBar
```

（4）style配置项配置样式版本，目前最新版本v2

（5）跟随微信设置的暗色模式

页面的暗色模式、在全局设置样式

```
page {
  background: #fff;
  color: #000;
}
/* 若微信设置为暗黑模式，应用的样式 */
@media (prefers-color-scheme: dark) {
  page{
    background: #000;
    color: #fff;
  }
}
```

导航栏和tabbar的暗色模式

```
//根目录下新建 theme.json，light和dark都要写，里面的属性名字自定义(但light和dark的属性名要保持一致)
{
  "light": {
    "navBgc": "#ffffff",
    "navC": "black"
  },
  "dark": {
    "navBgc": "#000000",
    "navC": "white"
  }
}

//app.json中，用@使用theme.json的变量
{
  ...
  "window": {
    "navigationBarTitleText": "123",
    "navigationBarBackgroundColor": "@navBgc",
    "navigationBarTextStyle": "@navC"
  },
  "tabBar": {...},
  "darkmode": true,
  "themeLocation": "theme.json"
}
```

### 2.2 页面各自的json配置文件

用于配置各页面特有的窗口样式，会覆盖全局的窗口配置，配置项与app.json不太一样，如：

```
{
  "navigationBarTitleText": "",
  "enablePullDownRefresh": false,
  "usingComponents": {}
}
```

## 3 wxml的标签（组件）

有自己的标签和属性，属性若为布尔值，true时可以省略值

app.json中的pages编写路径就会这届在page下生成页面文件

### 3.1 视图容器

（1）<view>和<block>
<view>类似于<div>

<block>相当于vue的<template>，只作包裹代码作用，不渲染不占内存，适合于if控制多个组件显示时使用

（2）<scroll-view>

实现滚动，属性scroll-y或scroll-x控制垂直/水平滚动，对应的必须设置高度/宽度

有时可能要重置滚动到顶部，实现：

```
...
<view @click="activeChange"></view>
...
<scroll-vie scroll-y :scroll-top="scrollTop"><scroll-view>
...
data: {
  return {
    scrollTop: 0
  }
},
methods: {
  activeChange(){
    //scroll-top无法重复赋值，所以需要0.01和0来回赋值
    this.scrollTop = this.scrollTop == 0 ? 0.01 : 0  
  }
}
```

如分类页面的左右两边都有滚动

```
<view class="ScrollArea" style="display: flex;">
  <scroll-view class="ScrollLeft" scroll-y style="height: 100vh; width: 25%;">
    <view v-for="i in 100">{{i}}</view>
  </scroll-view>
  <scroll-view class="ScrollRight" scroll-y style="height: 100vh; width: 75%;">
    <view v-for="i in 100">1000000</view>
  </scroll-view>
</view>
```

（3）<swiper>和<swiper-items>

轮播图

swiper属性

| 功能     | 属性                     | 类型      | 默认值            |
| ------ | ---------------------- | ------- | -------------- |
| 点是否显示  | indicator-dots         | boolean | flase          |
| 未激活点色  | indicator-color        | color   | rgba(0,0,0,.3) |
| 激活的点色  | indicator-active-color | color   | #000           |
| 是否切换   | autoplay               | boolean | false          |
| 切换间隔   | interval               | ms      | 5000           |
| 是否衔接滚动 | circular               | boolean | false          |

### 3.2 基础内容

（1） <text>

类似于<span>，属性selectable实现长按复制（注意模拟器无效，真机才有效爱哦）

（2）<rich-text>

通过nodes属性将html的标签渲染为wxml结构

```
<rich-text nodes="<h1 style='color:red'>123</h1>"></rich-text>
```

（3） <button>

```
<!-- 基本使用，其他属性和值详见文档 -->
<!-- 独占一行 -->
<button>普通按钮</button>
<button type="primary">主色调按钮</button>
<button type="warn">警告按钮</button>
<!-- 共享一行 -->
<button size="mini" type="primary">小按钮</button>
<button size="mini" type="primary">小按钮</button>
<button size="mini" type="primary">小按钮</button>
<button size="mini" type="primary">小按钮</button>
<!-- 带边框 -->
<button size="mini" plain>123</button>
```

（4） <image>

与img的区别：

* img，若设置width为100%，高度是会自适应的

* image[若设置width为100%，高度是不会自适应的，当可以通过mode属性设置

与Vue的img区别：

* 本地图片必须放在项目的miniprogram文件夹下的images文件夹，也就不存在Vue中普通情况下无法动态绑定src的情况：
  
  ```
  <image src="/images/..." />
  <image src="/static/..." />
  ```

* 同样只能使用相对路径和webpack配置的路径，无法使用绝对路径

通过mode属性决定图片的裁剪和缩放模式，值：

| scaleToFile(默认) | 不保持比例，直接将宽高拉伸到与image一样的宽高           |
| --------------- | ----------------------------------- |
| aspectFit       | 保持比例，缩放直到宽高长的那个与image宽高一致，所以可能会造成留白 |
| aspectFile      | 保持比例，缩放直到填充满image，所以可能会裁剪图片         |
| widthFix        | 宽度不变，高度自保持比例适应                      |
| heightFix       | 高度不变，宽度保持比例自适应                      |

通过lazy-load属性设为true可以实现图片懒加载，但有平台限制，详情见文档。

### 3.3 表单组件

<input />，与H5差不多，新增了一些东西

事件confirm用于监听回车按下

<radio checked="true" color="red">  选中√，颜色为红色的radio

### 3.4 导航组件

分为声明式导航和编程式导航：

```
<!-- 声明式导航，注意url最前面加/ -->

<!-- 跳转到tabBar页面 -->
<navigator url="/pages/index/index" open-type="switchTab">跳转到tabBar页面</navigator
>
<!-- 跳转到非tabBar页面，导航条会有返回键后退一级，此时open-type="navigate"可以省略 -->
<navigator url="/pages/logs/logs" open-type="navigate">跳转到非tabBar页面</navigat
or>
<!-- 后退导航，点击后退，deita定义后退层级 -->
<navigator url="/pages/logs/logs" open-type="navigateBack" deita="1">返回</navigator>
```

```
//编程式导航
//tabBar跳转
wx.switchTab({
  url: '/pages/index/index',  //只有url是必填项
  success: () => {//成功回调},
  fail: () => {//失败回调},
  complete: () => {//结束时回调，成功失败都会回调}
})

//非tabBar跳转
wx.navigateTo({
  url: '/pages/logs/logs',  //只有url是必填项
  success: () => {//成功回调},
  fail: () => {//失败回调},
  complete: () => {//结束时回调，成功失败都会回调}
})

//后退
wx.navigateBack({
  deita: 1,  //若补给，默认1
  success: () => {//成功回调},
  fail: () => {//失败回调},
  complete: () => {//结束时回调，成功失败都会回调}
})
```

传参一般都是非tabBar才需要，通过在url后面拼接 ?aaa=1&bbb=2 传参

```
//在生命周期钩子onLoad的参数options可以获取传递的参数
onLoad(options){
  console.log(options)
}
```

若传参时参数太多使得url超过长度限制，或参数有特殊字符，此时就会报错，需要通过encodeURLComponent()编码才行：

```
//跳转前编码以下url
let paramse = {a: 1,b: 2};
let encode = encodeURLComponent(JSON.stringify(parmas));
let url = '...?item=${encode}';
uni.navigateTo({url});

//跳转后解码拿到参数
onLoad(options){
  let params = JSON.parse(decodeURLComponent(options.
}
```

### 3.5 其他

map地图组件，canvas画布组件，开放能力，无障碍访问

## 4 wxss

（1）基本区别

大部分的css的功能都能使用，只有小部分不能用，如id选择器，通配符选择器无法使用，可以用 page {}  代替 * {}

此外，wxss还有自己的适配单位rpx：

rpx将宽度分为750rpx，会根据不同屏幕来自动转化px

1 rpx = 7.5 px

假设设计稿宽度为total，每处px的标注为n，则：

```
rpx = 750 * (n / total)
```

不过，rpx默认最大支持的宽度是960px，超过了就失效了，如果想要适配更大的快递，可以在 pages.json 中配置：

```
"globalStyle": {
    "rpxCalcMaxDeviceWidth": 10240
}
```

也可以使用vw，但是vw在一些小尺寸（如1px）不够精确，此时就使用rpx。

使用vh时需要注意，微信小程序的视口大小是会随着navbar和tabbar的显示隐藏变化的，因此vh也会变化。

（2）全局样式与局部样式

全局样式在app.wxss中定义，使得所有页面都有效果

局部样式在各自页面的wxss文件，若局部样式权重大会覆盖全局样式

## 5 模板语法

在相应的js或ts文件中定义数据，wxml就可以使用了，可用与vue一样的mustache语法

```
// pages/aaa/aaa.ts
Page({
  //页面的初始数据 
  data: {},
  //与data同级可以写函数和声明周期钩子
})
```

若data中定义了数据 a:0 则sxml中通过{{a}}获取，在js中通过this.data.a获取

通过this.xxx()  调用方法（但是wxml无法调用，需要wxs）

数据直接修改不是响应式的，需要this.setData修改才是响应式：

```
this.setData({
  a:this.data.a+1
})
```

### 5.1 数据绑定

与vue不同

```
//css写.big的样式
//js
data:{
  className: 'big'
}
<!--wxml-->
<button class="{{className}}"></button>
```

### 5.2 事件绑定

```
<!--另一种形式是 bind:tap="..." ..>
<text bindtap="fun">123</text>

<!--常用事件
tap   相当于click
input  表单输入
change  任何状态的改变
-->
```

```
//事件函数写在js中的与data同级的区域
btnTapFun(e){
  //e是事件对象
}
```

传参与vue很大不同

```
<button bind:tap="btnTapFun" data-xxx="{{2}}" data-yyy="{{3}}">001</button>
```

```
btnTapFun(e){
  console.log(e.target.dataset.xxx)
  console.log(e.target.dataset.yyy)  
}
```

双向绑定

```
<input type="text" value="{{a}}" bindinput="inp" />
<text>{{a}}</text>
```

```
inp(e){
  this.setData({
    a: e.detail.value
  })
}
```

下拉刷新

```
//下拉刷新可在app.json全局配置或各自页面的json文件配置，
"enablePullDownRefresh":true 
//此自定义下拉行为，在data同级编写，可以做一些数据重置的操作
onPullDownRefresh(){
  //自定义行为，默认是不重新渲染页面的，下拉也不会自动弹回，所以必须要：
  wx.stopPullDownRefresh()  //弹回
}
```

上拉到底部的处理

通常是上拉加载更多，请求下一页的数据

```
//data同级
onReachBottom(){
  //这里可以网络请求更多数据，并且应作防抖处理
}
//可在配置文件配置上拉处理的距离，但是一般默认的50px就行了
```

点击右上角分享

```
onShareAppMessage() {}
```

### 5.3 条件渲染

wx:if和hidden的区别与vue的v-if和v-show一样，唯一的区别就是v-show是“显示”，hidden是“隐藏”

```
<text wx:if="{{a == 0}}">0</text>
<text wx:elif="{{a == 1}}">1</text>
<text wx:else>2</text>
```

```
<text hidden="{{false}}">123</text>
```

### 5.4 列表渲染

```
<view wx:for="{{arr}}">索引是{{index}}，值是{{item}}</view>
<view wx:for="{{obj}}">key是{{index}}，value是{{item}}</view>
<view wx:for="123456">我是第{{index+1}}个数字{{item}}</view>
```

```
<!--可以修改index和item的变量名-->
<view wx:for="{{arr}}" wx:for-index="ind" wx:for-item="i">
  {{ind}},{{i}}
</view>
```

### 5.5 生命周期钩子

分为应用生命周期和页面生命周期，应用包含页面

应用生命周期函数，在app.js中声明，与globalData同级

| onLaunch | 小程序初始化完成时回调，只触发一次 |
| -------- | ----------------- |
| onShow   | 小程序启动，或从后台进入前台触发  |
| onHide   | 小程序从前台到后台时触发      |

页面声明周期函数，在各自页面的js文件中声明，与data同级

| onLoad   | 页面加载完成，只触发一次，相当于vue的created                   |
| -------- | --------------------------------------------- |
| onReady  | 页面渲染完成，只触发一次，相当于vue的mounted                   |
| onShow   | 页面显示时触发                                       |
| onHide   | 页面隐藏时触发                                       |
| onUnload | 页面卸载时触发，只触发一次，相当于vue2的destroyed，vue3的unloaded |

## 6 wxs

weixin script，类似于js，区别：

1. 不支持es6及更高级的语法

2. 模块使用CommonJS规范

3. ios端性能比js块2-20倍，安卓则差不多

4. wxs的函数不能作为事件函数，只能使用{{}}调用wxs的变量、函数

5. wxs不能调wx和js，js不能调wxs，js的数据可通过{{}}传给wxs

页面的js文件的data数据可以在wxml中使用，但是函数却不行，而wxs定义的函数则可以在wxml中使用，一般wxs里面都是定义过滤器

```
<!-- 内嵌exs，卸载wxml中 -->


{{m1.fun('123')}}

<wxs module="m1">
  var fun = function(str){
    return str + '456'
  }
  module.exports = {
    fun:fun
  }
</wxs>
```

```
//外联wxs，如写在utils目录下的filters.wxs
var fun = function(str){
  return str + '456'
}
module.exports = {
  fun:fun
}

----------------------------------------------------

<!-- wxml中引入，src必须是相对路径 -->
{{m1.fun('123')}}

<wxs module="m1" src="..//../utils/filters.wxs"></wxs>
```

## 7 组件

### 7.1 自定义组件

创建、引入与使用

在根目录中建立components文件夹存放组件，里面新建a文件夹再右键新建component就能自动生成json，wxml，wxss，js

局部引入在各页面的json写，只能在该页面使用；全局引入在app.json写，全部页面都能用

```
"usingComponents": {
  "cpn":"/components/cpn/cpn"
}
```

使用：wxml中   <cpn></cpn>

区别：

1. 组件的json中要  "component": true

2. 页面的js使用Page(config)，组件的js使用Component(config)

3. 页面的事件函数与data同级，组件的事件函数写在与data同级的methods中

### 7.2 组件样式

组件与页面的样式是互相隔离的（包括全局样式），但是仅限于类选择器

若想自定义是否隔离，可以：

```
//方式一、组件js文件中
Component({
  options:{
    styleIsolation: 'isolated'  
  }
})
//方式二、组件的json文件中
{
  "styleIsolation": "isolated"
}

/*
isolated     默认
apply-shared 页面样式能影响组件，反之不行
shared       页面，组件样式能互相影响，该组件也能影响其它apply-shared或shared的组件
*/
```

### 7.3 父子组件通信

（1）父传子

```
//组件js中
Component({
  propteries:{
    xxx: Number  //简写
    bbb: {       //可指定默认值
      type: Number,
      value: 10
    }  
  }
})
//js中通过this.propertise.xxx调用

<!-- wxml -->

<cpn xxx="100" bbb="50"></cpn>
```

与vue一样能在{{}}中使用，与vue区别：

1. vue的data和props是不同对象，data可读可写，props只读

2. 小程序的data和properties是一个对象，都是可读可写

（2）子传父

```
//子的事件函数中
this.trigerEvent('xxx',{aaa:...})
//父的wxml中
<cpn bind:xxx="faXxx"></cpn>   bind:xxx可以写成bindxxx
//父的faXxx函数中
e.detail.aaa 获取参数
```

（3）获取组件实例

et cpn = this.selectComponent('类/id选择器')

相当于vue的refs，得到的cpn是子组件实例对象，cpn.方法  cpn.data.属性  cpn.setData()

3.4 

### 7.4 数据监听器

```
Component({
  //可监听单个、多个属性的变化
  observer: {
    'aaa'(newVal){},
    'bbb,cccc'(bbbNewVal,cccNewVal){}  
  }
})
```

### 7.5 纯数据字段

指的是只在js内部使用，不需要到wxml渲染的数据

小程序的数据默认是非响应式的，需要setData修改才能响应式，这样是为了提高性能。我们可以更进一步，将不需要渲染的数据定义为纯数据字段，再提高性能

```
Component({
  options: {
    pureDataPattern: /正则/   //复合正则的属性名将变成纯数据字段  
  }
})
```

由此，官方推荐在组件js内部使用的属性、方法的名字以_开头

### 7.6 组件生命周期

分为组件生命周期和组件所在页面的生命周期

（1）组件生命周期

与data同级

| created  | 组件创建完成，此时无法使用this.setData() |
| -------- | --------------------------- |
| attached | 组件放入页面结点树中，此时可以网络请求数据       |
| reqdy    | 组件渲染完成                      |
| moved    | 组件在节点树中移动                   |
| detached | 组件销毁                        |
| error    | 组件内的函数异常时回调                 |

（2）组件所在页面的生命周期

写在与data同级的pageLifetime中

| show         | 页面显示    |
| ------------ | ------- |
| hide         | 页面隐藏    |
| resize(size) | 页面大小有变化 |

### 7.7 插槽

有默认插槽和具名插槽，使用多个<slot>时如具名插槽，需要在组件的options中添加：

multipleSlot: true

### 7.8 behaviors

相当于vue的混入

```
//定义一个js文件
module.exports = Behaviors({  
  //属性方法生命周期
})
//用到的组件中
const xxx = require('...')
Component({
  behaviors: [xxx]
})
```

## 8 分包

### 8.1 介绍

未分包时，所有的页面和资源在打开小程序时会同时加载，速度会很慢。

分包后，就会俺需加载。

分包：分为一个主包和多个分包，主包包含tabBar页面和公共资源，分包则包含非tabBar页面和私有资源。在首次打开小程序时，只会加载主包的内容，只有在需要分包的页面和资源时，才会加载分包。

主包不能访问跟分包的私有资源，分包可以访问主包的公共资源，分包之间不能相互引用私有资源。

分包限制：主包和分包总大小不大于16M，主包和分包单个大小不超过2M

### 8.2 使用

目录结构：pages文件夹放主包的页面，在pages的同级建立xxx分包文件夹作为一个分包，xxx下建立pages文件夹放页面，分包不能嵌套分包

/pages/主包页面

/xxx1/pages/分包1页面

/xxx2/pages/分包2页面

在app.json中作如下配置，其中name是分包别名，可不写

```
{
  "pages":["pages/...","..."]  //主包页面
  "subpackages": [
    {"root":"xxx1","name":"p1", pages:["pages/...","..."]},
    {"root":"xxx2","name":"p2", pages:["pages/...","..."]}
  ]
}
```

此外，若没有自己新建目录结构，配置文件编译后也会自动生成

查看主包分包大小：详情-基本信息-本地代码

### 8.3 独立分包

独立分包是分包的一种，可以有多个

一般情况下，打开小程序先下载主包，才能下载对应的分包。但是独立分包不一样，打开小程序时不下载主包而是直接下载独立分包并展示。即独立分包不依赖于主包。

注意，独立分包不能引用主包的公共资源。

只需要在app.json的分包配置项中添加 "independent": true 即是独立分包。碎

### 8.4 分包预下载

在进入某个页面时，可能会有需求提前预下载需要的分包，使得节省访问该分包时的下载事件，甚至不用再下载。

app.json中

```
{
  "preloadRule": {
    “pages/...”:{
      "network": "all"   //所有网络都可预下载；另一个值是“wifi”，只有在wifi下才预下载
      "paakages": [“..."]  //需要预下载的分包数组，值为分包的root或name
    }
  }
}
```

注意，同一个分包中，分包大小+预下载大小不能超过2M

## 9 网络请求

官方为了安全，对网络请求做了限制：

1. 只能请求https协议的接口

2. 必须将接口的域名添加到信任列表（查：工具右上角-详情-项目配置-request合法域名）

（1）添加域名到信任列表

登录微信小程序管理后台-开发-开发管理-开发设置-服务器域名，注意无法添加ip地址和localhost，且该域名需要后端做icp备案，且修改域名一个月做多修改5次

（2）发送请求

```
wx.request({
  url:'...',
  method:'...',
  data:{},  //get,post都是data
  succes:res => {
    console.log(res.datas)    
  }
})
```

（3）关闭域名验证

在开发时，为了方便可以关闭域名验证，此时就不需要https协议和添加信任列表

详情-本地设置-不检验合法域名......

但是项目上线时就一定要开启域名验证

（4）跨域和ajax

只有浏览器环境才存在跨域问题，小程序没有跨域问题

ajax是基于浏览器的xhr对象，小程序是没有的，所以小程序不能使用ajax，小程序用的是自己封装的网络数据请求

## 10 API

### 10.1 官方API

分为事件监听API，同步API，异步API

H5的DOM、BOM的api无法使用，localStorage无法使用

保留了定时器

常用api，具体详见官方文档

```
//展示、关闭loading
wx.showLoading({title:'正在加载...'})
wx.hideLoading()
//显示弹窗
wx.showToast({
  title: '连接失败',
  duration: 2000,  //弹窗持续时间
  icon: 'none',    //使用的icon，none为不使用，默认为√,
  mask: true       //防止点击事件穿透
})

//给tabbar设置小标
wx.setTabBarBadge({
  index: 2, //要显示小标tabbar的索引
  text: ''  //必须是字符串，''为不显示任何内容
})
//图片放大预览
wx.previewImage({
  current: 0,    //预览图片的索引
  urls: [...]    //图片们的url地址
})

//选择收获地址，若本地没有收获地址，则会进入填写页面（新版不再需要授权）
wx.chooseAddress().then(res => {
  console.log(res)
))
/*一调用就会进入选择地址页面
res是一个对象，数据有：
{
  userName,     //姓名
  telNumber,    //电话
  provinceName, //省
  cityName,     //市
  countyName,   //区，县
  detailInfo,   //详细地址
  errMeg,       //锁雾信息，若没有错，则值为"chooseAddress:ok"
  postalCode,
  nationalCode
}
*/
//获取用户信息（头像/昵称等）
uni.getUserInfo().then(res => {}) //必须配合 <button open-type="getUserInfo" bindgetuserinfo="xxx"></button> （已失效）
uni.getUserProfile({desc: '随便但必传'}).then(res => {})  //获取的结果一样，比起上面区别在于不用buuton、open-type和
/*
getuserinfo事件，每次获取用户信息都会弹出授权窗口（取消了以后也会弹出）  (2022/10 失效)
2022/10 以后以上两个都失效，但是还可使用，获取的均是 用户名为 '微信用户' , 头像为默认头像，若需要获取用户信息，需要提供用户自
己填写上传的模块 （详见文档-api-开放接口）
*/

//登录：
uni.login().then(res => console.log(res.code))  //将这个code发给自己的后端，后端返回token即可

//微信支付
wx.requestPayment({参数})

//本地存储
wx.setStorageSync('xxx',a)  //a必须是字符串，若不是，需要JSON.stringify()
wx.setStorageSync('xxx','') //清空
wx.getStorageSync('xxx')    //若不存在，返回空字符串，若存在，返回JSON字符串，需要JSON.parse
```

有些api需要授权，有些点击取消后还能再次授权，有些则不会，需要解决。

异步api的使用方式分两种：

```
//1.callback  
wx.xxx({
  ...
  sucess(){},
  fail(){},
  complete(){}
})
//2.promise ,需要api支持promise风格
//若参数不包含sucess/fail/complete，则返回一个promise，否则不返回promise
```

### 10.2 npm安装第三方包

（1）限制：

1. 不支持依赖于nodeJS模块（如fs，path）的包

2. 不支持依赖于浏览器的DOM,BOM的包，如jQuery

3. 不支持依赖C++的包（如一些加密的包）

（2）npm使用：

在项目的miniprogram目录下安装npm包，先npm init再装包

装包成功后，在开发者工具-工具-构建npm，构建成功后会多出miniprogram_npm文件夹

若构建npm时，若miniprogram_npm文件夹已存在，建议先删除再构建，防止不必要的错误。

（3）常用npm包

组件库vant

为了防止样式冲突，建议将 app.json 的 "style":"v2" 删除

使用vant的组件时，需要在json的usingComponents引入

小程序异步API转Promise

```
import {promisifyAll} from 'miniprogram-api-promise'

const wxp = wx.p = {}
promisifyAll(wx,wxp)  //wxp得到了转化为promise的wx异步api，通过wxp.xxx()调用
//如 await resData = wxp.request(...)
```

状态管理工具

相当于vuex，需要安装mobx-miniprogram和mobx-miniprogram-bindings，作用分别是创建store和在各页面中绑定store

注意：页面js和组件js的绑定store语法是不一样的

miniprogram下新建store文件夹存放store.js

```
import {observable,action} from 'mobx-miniprogram'
const store = observable({
  //属性
  data1:123,
  data2:456,
  //计算属性
  get data3(){
    return this.data1 + this.data2
  },
  //修改属性值
  updateData1: action(function(newVal){
    this.data1 = newVal
  }),
})
export default store
```

在需要使用的页面中的js中

```
import {createStoreBindings} from 'mobx-miniprogram-bindings'
import store from '../../store/store'
Page({
  onLoad() {
    this.storeBindings = createStoreBindings(this,{
      store,
      fields: ['data1','data2','data3'], //导入属性和计算属性
      actions:['updateData1']  //导入修改store数据的方法
    })
    //在需要修改store数据的时候，this.updateData1(678910)
  },
  //离开页面时，解除该页面对store的绑定
  onUnload() {
    this.storeBindings.destroyStoreBindings()
  }
})
```

或在需要的组件的js中

```
import {storeBindingsBehavior} from 'mobx-miniprogram-bindings'
import store from '../../store/store'
Component({
  behaviors:[storeBindingsBehavior],
  storeBindings:{
    store,
    //导入属性和计算属性有三种方式
    fields:{
      data1: () => store.data1,      //方式1
      data2: (store) => store.data2, //方式2
      data3: 'data3'                 //方式3
    },
    //导入修改数据的方法只有一种方式
    actions:{
      updateData1: 'updateData1'
      //需要修改store数据时，this.updateData1(123456)
    }
  }
})
```

最后在相应的wxml中

```
<!-- 直接用{{}}使用store的属性和计算属性 -->

<view>{{data1}}</view>
<view>{{data2}}</view>
<view>{{data3}}</view>
```

## 11 协同工作与发布

## 12 公众号

需要另外注册一个公众号的账号，公众号分为订阅号和服务号，服务号需要企业才能申请，功能比订阅号多一些，个人只能申请订阅号。

# 二、uniapp

uniapp用vue的语法结合小程序的语法开发各种小程序、安卓、ios等。

appid，除了各个小程序的appid外，uniapp自己本身也有一个appid。

## 1 在HBuilderX开发

（1）编辑器设置

* 切换快捷键方案：工具-预设快捷键方案切换-VS Code

* 主题切换：工具-主题

* 字体等设置：工具-设置-就能打开settings.json

（2）项目创建和运行

创建项目：

* HBuilder中新建项目，而不是webpack或vite创建。

* 新建项目，选择模板，其中 uni-ui模板 就会自带 uni-ui。

编译运行：

* HBuilderX保存后微信开发者工具会热更新（json不会），所以最好编译一下

* 修改代码时，模拟器会相应变化，但有时不会且数据有时也需要重置，此时就可以进行编译。模拟器有些效果出不来，预览可以在手机上看效果，但前提是得编译通过。

* 有些效果只有在预览才能看见，预览必须配置appid才能用，每次重新修改都要重新编译并重新点击预览生成新的二维码。手机扫码后，右上角三点的设置里开启开发调试模式，否则网络请求失效。

配置文件：

* HBuilder的json文件一些会变成图形界面（manifast.json settings.json，点开后可在左侧栏最下面点击源码视图），一些不会

（2）第三方库安装；

部分npm安装

部分在uniapp插件市场安装（如less，sass），若使用时未安装也会自动安装

HBuilder的项目运行到微信开发者工具查看效果：

1. HBuilder-manifaset.json-微信小程序配置-appid

2. HBuilder-工具-设置-运行配置-小程序运行配置-微信开发者工具路径

3. 微信开发者工具-设置-安全-服务端口

4. HBuilder-运行-运行到小程序模拟器-微信开发者工具 就会编译成微信小程序的代码并打开微信开发者工具，HBuilder修改代码保存后微信开发者工具会热更新

### 1.2 在vscode开发

HBuilderX好像没有 vite 和 ts 的模板，可以选择在 vscode 中开发。

先确保有 vue/cli，如果没有就安装：

```
vue -V
pnpm install -g @vue/cli
```

创建 vite 和 ts 的 uniapp 项目：

```
npx degit dcloudio/uni-preset-vue#vite-ts project-name
cd project-name
pnpm install
```

ts 支持：

官方的 types": ["@dcloudio/types 不太完善，需要再使用社区提供的 @uni-helper/uni-app-types

```
pnpm install -D @uni-helper/uni-app-types
```

```
// tsconfig.json
{
  "compilerOptions": {
    "types": ["@dcloudio/types", "@uni-helper/uni-app-types"]
  }
}
```

运行：

根据 package.json 来运行，h5 就直接可以浏览器访问，app 和小程序就 pnpm run dev:xxx 后根据提示来。

检查 ts：

```
pnpm run type-check
```

vscode 插件支持：

vscode 开发 uniapp 除了需要 volar，eslint，prettier 这些vscode插件外，还需要安装 uniapp-snippet ，uni-app-schemas ，uni-create-view 。

如果要在 HBuilderX 运行 vite 项目：

需要设置 HBuilderX 运行 node 路径改为自己本地的node目录：

HBuilderX->工具->设置->运行配置->node

### 1.3 目录结构

可以像温馨小程序一样，新建页面、新建组件等快速创建文件

不同方式创建的项目，目录结构不同：

- HBuilderX创建的项目的目录是全部文件在根目录。

- 而vscode创建的项目，核心的源码都放在 src 下。

目录结构：

- pages：存放tabbar页面

- components：存放自定义组件，放在这里的自定义组件不需要引入注册就可以在任何页面上使用；其他文件夹下的组件要使用就需要引入注册

- static：存放静态资源文件（图片等），注意static里面的文件不会被webpack编译，需要webpack编译的文件（如es6，ts，less等）不能放在里面

- uni_modules：存放dcloud插件市场下载的第三方库（如uni-ui）

- App.vue：编写应用声明周期，全局样式，不需要写template

- uni.scss：系统会自动引入，配置全局样式（需要自行npm安scss）

- manifast.json：H5，小程序，安卓，ios的配置文件

- pages.json：相当于微信小程序的app.json

- vue.config.json：webpack配置文件（需要自己创建）

### 1.4 全家桶支持

（1）ui库

在HBuilderX开发的话，有了uni-ui就可以直接使用，不需要注册导入。components 下的组件不需要导入也是能直接使用。

但是vscode中就不同了，没有自带 uni-ui ，需要自行安装，且需要导入，就连 components 下的组件都需要导入才能使用：

```
pnpm install --save @dcloudio/uni-ui
```

然后在 pages.json 配置自动注册和引入 uni-ui 和 自定义组件，就可以不用导入直接使用了：

```
{
    "easycom": {
        "autoscan": true,
        "custom": {
            "^uni-(.*)": "@dcloudio/uni-ui/lib/uni-$1/uni-$1.vue",
            "MySearcher":"@/components/common/MySearcher.vue",
            "PullUpLoading":"@/components/common/PullUpLoading.vue",
            "GoodsCard":"@/components/content/GoodsCard.vue",
            "GoodsList":"@/components/content/GoodsList.vue"
        }
    },
}
```

（2）状态管理工具

可以使用 pinia ，不过持久化的插件需要使用支持 uniapp 的，毕竟每个平台的本地存储都不一样：

```
pnpm install --save pinia pinia-plugin-unistorag
```

```
import { createPinia, defineStore } from "pinia";
import { createUnistorage } from "pinia-plugin-unistorage";
import { reactive, toRefs } from "vue";
import type { UserStoreStateInterface } from "@/types/types/store";

const pinia = createPinia();
pinia.use(createUnistorage());

export const UserStore = defineStore(
  "User",
  () => {
    const state = reactive<UserStoreStateInterface>({
      gxbuy_uniapp_jwt: "",
      userInfo: {}
    });

    return {
      ...toRefs(state)
    };

  },
  {
    unistorage: true
  }
);

export default pinia;
```

需要注意的是，修改了pinia的数据后，如果用 uni.getStorageSync() 获取数据获取不到，需要手动刷新页面才行，可能是 bug ，因为调试工具中已经更新数据了，PC端用 localstorage.getItem() 也能正常获取，所以 uniapp 这个不知道是什么原因，那就尽量直接用 pinia 获取数据。 

uni.setStorageSync() 也是一样。

用 uniapp 强制刷新 api 也不行，必须手动刷新。

（3）请求

可以使用 uni.request ，但是比较简陋：

```
// 二次封装示例
const baseURL =
  (import.meta.env.MODE === "development" ? import.meta.env.VITE_DEV_BASEURL : import.meta.env.VITE_PROD_BASEURL) +
  "/v1";
const timeout = 1000 * 10;

// uniapp 有 uni.addInterceptor 可以配置拦截器，但是没有必要，下面已经实现了拦截器功能
const instance = function (options: any): Promise<any> {
  // 这里可以写请求拦截器的功能
  options.url = baseURL + options.url;
  options.timeout = timeout;

  return new Promise((resolve, reject) => {
    uni.request({
      ...options,
      // success 和 fail 可以写响应拦截器的功能
      success(res: any) {
        resolve(res.data);
      },
      faill(err: any) {
        reject(err);
      }
    });
  });
};

export default instance;
```

小程序中，默认无法使用 axios ，需要自己做适配：

原理：uni.request() 可以兼容各个平台，但是没有拦截器，且使用上也不习惯。axios 中提供了适配器，可以修改底层的请求逻辑，我们将底层的请求换成 uni.request ，这样就能用 axios 了。

既然底层是用的 uni.request() ，那么 uni.request() 的问题依然会存在：

* axios get请求参数是放到 params 的，其他类型请求放到 data 中，而 uni.request 不管什么请求类型都放到 data 中，使用上不习惯

* 原生的 axios 若请求结果状态码不为 2xx 时会走 promise 的 catch，而 uni.request 不为 2xx 也会进入 then 回调，这样在使用上就不太方便 try...catch... 了，所以要在 succs
  
  中判断是否要 reject：

* get 请求会把参数放到 url 上，但是 uni.request() 处理的不好，比如传数组会有问题：
  
  ```
  const query = {
    arr1: [100],
    arr2: [123, 456],
    obj: {a: 789}
  }
  
  /* uni.request
   * 后端接收的结果：{ arr1: '100', arr2: '123,456', obj: '{"a":789}' }
   */
  uni.request({
    url: 'xxx',
    data: query
  })
  
  /* axios
   * 后端接收的结果：{ arr1: [ '100' ], arr2: [ '123', '456' ], obj: { a: '789' } }
   */
  axios({
    url: 'xxx',
    params: query
  })
  ```

这些问题可以看代码中的注释：

注意：qs 目前有兼容问题，如果 h5 正常运行但是小程序白屏，那么就是 qs 版本太高了，需要降级到 5.2.1 版本。

```
pnpm install --save qs@5.2.1
pnpm install -D @types/qs
```

```
import axios from "axios";
import type {
  AxiosInstance,
  InternalAxiosRequestConfig,
  AxiosResponse,
  AxiosError,
  AxiosPromise,
  AxiosRequestConfig
} from "axios";
import qs from "qs";
import { UserStore } from "@/store";

// 适配器 ------------------------------------------------------------------------
const getResponse = (res: any, config: any) => {
  const { statusCode, errMsg } = res;

  return {
    ...res,
    status: statusCode,
    statusText: errMsg,
    config,
    request: null
  };
};

function uniAdapter(config: AxiosRequestConfig | any): AxiosPromise {
  if (!uni) throw new Error("please use this in uni-app project!");

  return new Promise((resolve, reject) => {
    const { baseURL, url, headers, method, data, params } = config;
    const uniConfig = {
      ...config,
      url: baseURL + url,
      header: headers
    };

    if (data || params) {
      try {
        uniConfig.data = JSON.parse(data || params);
      } catch (e) {
        uniConfig.data = data || params;
      }
    }

    // 通过 qs.stringify 序列化解决 uni.request 参数问题
    if (method === "get") {
      uniConfig.url = `${uniConfig.url}?${qs.stringify(uniConfig.data)}`;
      delete uniConfig.data;
    }

    uniConfig.header = { ...uniConfig.header };

    uni.request({
      ...uniConfig,
      success(res: any) {
        const response = getResponse(res, config);
        if (response.status < 200 || response.status >= 300) {
          reject(response);
        } else resolve(response);
      },
      fail(res: any) {
        const response = getResponse(res, config);
        reject(response);
      }
    });
  });
}

// 二次封装 axios -------------------------------------------------------------------------
const baseURL =
  (import.meta.env.MODE === "development" ? import.meta.env.VITE_DEV_BASEURL : import.meta.env.VITE_PROD_BASEURL) +
  "/v1";

const cancelTokenSource = axios.CancelToken.source();

const instance: AxiosInstance = axios.create({
  // 使用适配器，以适配小程序
  adapter: uniAdapter,
  // 注意，使用了适配器后，一定要配置 baseURL 和 timeout，否则无法使用
  baseURL,
  timeout: 1000 * 10
});

// 请求拦截器
instance.interceptors.request.use(async (config: InternalAxiosRequestConfig) => {
  uni.showLoading({
    title: "加载中..."
  });

  const routes = getCurrentPages();
  const route = routes[routes.length - 1] as any;

  const userStore = UserStore();
  const jwt = userStore.gxbuy_uniapp_jwt;

  // 后端需要jwt鉴权的接口，url都会有'/jwt/'，所以遇到有 '/jwt/' 的借口就加上请求头
  if (/\/jwt\//.test(config.url as string)) {
    // 如果未登录，就取消此次请求，并跳转登录页
    if (!jwt) {
      uni.hideLoading();
      cancelTokenSource.cancel();
      userStore.toPath = route.$page.fullPath;

      uni.navigateTo({ url: "/sub-pages-user/Login/Login" });

      // 拦截器必须returen，所以这里return一个异常，请求时catch就好
      return Promise.reject(new Error("未登录"));
    } else {
      config.headers!.authorization = jwt;
    }
  } else if (
    jwt &&
    (/\/goods\/search/.test(config.url as string) ||
      /\/goods\/detail/.test(config.url as string) ||
      /\/shop\/getShopInfo/.test(config.url as string))
  ) {
    config.headers!.authorization = jwt;
  }

  return config;
});

// 响应拦截器
instance.interceptors.response.use(
  (res: AxiosResponse | any) => {
    uni.hideLoading();
    return res.data;
  },
  (err: AxiosError) => {
    uni.hideLoading();

    // 如果jwt验证失败或者jwt过期，后端一般是返回403
    if (err.status === 403) {
      const routes = getCurrentPages();
      const route = routes[routes.length - 1] as any;
      const userStore = UserStore();

      cancelTokenSource.cancel();

      userStore.gxbuy_uniapp_jwt = "";
      userStore.userInfo = {};
      userStore.toPath = route.$page.fullPath;

      uni.navigateTo({ url: "/sub-pages-user/Login/Login" });
      return Promise.reject(new Error("请重新登录"));
    }

    return Promise.reject(err);
  }
);

export const staticBaseURL =
  import.meta.env.MODE === "development" ? import.meta.env.VITE_DEV_BASEURL : import.meta.env.VITE_PROD_BASEURL;

export default instance;
```

也可以用第三方的适配器，不过有一些小问题，不过它的问题就是在状态码不为 2xx 时不会抛出异常，get 请求传不了数组参数问题也没解决，所以我才在它的代码基础上进行修改。

```
pnpm install --save axios uniapp-axios-adapter
```

（4）路由

路由是不需要 vue-router 的，路由的功能在 pages.json 配置。但是没有导航守卫，路由元信息，动态路由等等这些功能，路由传参也有限制。

目前的第三方库有 uni-simple-router ，基本和 vue-router 差不多，不过 v3 版本是收费的，v3 开发板可能不稳定，免费v2 版本有不维护了。

如果只是需要守卫功能，可以自己用 uni.addInterceptor() 实现粗糙的导航守卫：

```
// /src/router/index.ts
import { UserStore } from "@/store";

export default function () {
  // 点击 tabbar 底层也是触发 switchTab
  const routeMethod = ["navigateTo", "navigateBack", "redirectTo", "switchTab"];

  // 需要登录才能进入的页面
  const needJwt = ["/pages/Profile/Profile"];

  for (const rm of routeMethod) {
    uni.addInterceptor(rm, {
      // uni api 调用前触发，可以做全局前置守卫
      invoke(args: any) {
        const userStore = UserStore();
        const jwt = userStore.gxbuy_uniapp_jwt;

        // 如果没有jwt且需要jwt
        if (!jwt && needJwt.find((url: string) => new RegExp(url).test(args.url))) {
          // 保存此次跳转的路由，以在登录后跳转回来，不过uni自带的跳转只能把参数连接到url里，且url长度又有限制，只能存到本地存储了
          userStore.toPath = args.url;

          // 跳转登录页
          uni.navigateTo({ url: "/sub-pages-user/Login/Login" });
          return false;
        }
      },
      // uni api 调用成功后触发，可以做全局后置守卫
      success(args: any) {}
    });
  }
}
```

```
// main.ts
import router from '@/router';
router();
```

```
// 登录
function login() {
  // ...
  if (userStore.toPath) {
    if (new RegExp("^\/pages\/").test(userStore.toPath)) uni.switchTab({ url: userStore.toPath });
    else uni.navigateTo({ url: userStore.toPath });
  } else {
    uni.switchTab({ url: "/pages/Home/Home" });
  }
}
```

此外，路由传参也有问题，如果路由传参传的是复杂数据类型，则必须JSON序列化，否则无法正常获取，如：

```
// 路由跳转
const arr = [1, 2, 3];
uni,navigateTo({
  url: `/xxx?arr=${JSON.stringify(arr)}`
))

// 接收参数
onLoad((query: any) => {
  console.log(JSON.parse(query.arr));
})
```

另一种获取参数的方式，也不是很方便：

```
const routes = getCurrentPages();
const route = routes[routes.length - 1] as any;
console.log(route.$page.fullPath);

// #ifdef H5
console.log(123, route.$page.options);
// #endif

// #ifdef MP
console.log(456, route.options);
// #endif
```

至于其他功能，看以后有没有其他库或者 uni-simple-router 会不会开源了。

### 1.5 多段适配

（1）vue 和 nvue

nvue 的 css 限制很多，不过在部分场景下会用到，具体见文档，以下的多段是配方案都是基于 vue 的，nvue可能部分无效。

一般情况下用vue就可以了。如果是 app 且有部分场景 vue 页面的性能不满足需求时，这个页面可以改用 nvue 页面。

（2）尺寸，选择器，全局样式/局部样式

尺寸：

* 用微信小程序的 rpx 就可以了，100 rpx = 750 px。

选择器只支持部分基础的，注意事项如下：

* 全平台不支持 * 选择器，body 选择到期变成 page

* vue 文件结构建议，先需要知道几点：
  
  * 小程序不支持 id 选择器，标签选择器，属性选择器，为了多段兼容就不要用了，都用 class 选择器
  
  * style 的 scoped 在小程序中有效，h5 中无效，这个需要特别注意样式冲突
  
  * 肃然 vue3 的模板已经可以不用根标签了，但是 uniapp 不知道为什么会有警告，所以还是带上吧
  
  为了解决以上问题，结构建议如下：
  
  ```
  <template>
    <view class="xxx">
      带一个跟标签
  </view>
  </template>
  
  <style scoped lang="scss">
  .xxx {
    /* 基础选择器只是用 class，再配合后代，子，伪类这些选择器
     * 样式都写在里面，避免冲突 
     */
  }
  </style>
  ```

布局：

* 尽量使用 flex 布局，兼容多端

* h5 可以哦直接给组件标签修改边距宽度这些样式，但是小程序不知道为什么不行，要修改边距宽度这些还得在外面包一个 <view> ，再修改这个 <view> 的边距宽度

全局样式/j局部样式：

* 全局样式写在 App.vue 或者在 App.vue 引入，局部样式则在各个组件中自行定义

* uni.scss 文件中定义了全局 css 变量，无需导入就可以直接使用

* 别忘了小程序 app.json 的 style 节点，uniapp 在 pages.json 中配置
  
  ```
  {
    "style": "v2"
  }
  ```

（3）导航栏，状态栏和 tabbar 适配

在 app 和 小程序中，这些都是原生控件，是不占用视口的，100vh是不包括这三个的。

而 h5 中，这三个都是用 div 渲染的，100vh包括了导航栏，状态栏和 tabbar。

因此，就需要做适配，否则就会出现 vh 不一样，底部定位被 tabbar 遮挡等等问题。

uniapp 提供了三哥哥 css 变量，--window-top，--status-bar-height 和 --window-top，分别是动态获取当前端的导航栏，状态栏，tabbar占用视口的高度。只有在 h5 中它们的值才不为0，在 app 和小程序中均为0。

例1：将一个盒子定位到页面底部，tabbar上方

```
.box {
  position: fixed;
  bottom: var(--window-bottom);
  left: 0;
  right: 0;
  width: 100%;
  height: 80rpx;
}
```

例2：100vh 的盒子

```
.box {
  height: calc(100vh - var(--window-bottom));
}
```

在每个属性中都这样使用其实很麻烦，但是目前没有找到可以全局配置的方法。

此外，h5 中由于导航栏，状态栏，tabbar 是 div 渲染的，所以定位时有可能会覆盖掉他们，比如tabbaer的z-index是999， >= 999 的盒子会挡住tabbar。

（4）其他

* css 使用背景图片注意，微信小程序不支持相对路径（真机不支持，开发工具支持），所以统一用绝对路径

* ios 对.webp格式的图片支持都不太好；ios 的地图覆盖物，使用高清图时，文件名要以@2或@3结尾，如 [xxx@2.png](mailto:xxx@2.png)

* 支付宝小程序不允许出现以@等特殊符号命名的文件

## 2 使用

### 2.1 基本语法

采用Vue语法+微信小程序语法/配置文件的开发模式，规范如下：

（1）顶级对象uni

uniapp的顶级对象是uni，有各个端的api，微信小程序的全部api都可以通过uni调用，可以通过 uni.xxx = yyy 来挂载到uni，保留了H5的定时器。

（2）Vue语法

每个页面对应一个.vue文件，可以使用所有的Vue语法，此外还可以使用微信小程序的组件、生命周期（应用生命周期都写在app.vue）

（3）事件总线

uniapp事件总线：

```
uni.$emit()  uni.$on()  uni.$off()
```

（4）HTML

若使用了div，span，img，input，button，编译成微信小程序会变成view，text，image，input，button，为了兼容多端推荐使用微信小程序的标签

（5）CSS

css为了兼容多端，推荐使用flex布局。

uniapp也有自己的适配单位upx，起初是为了兼容多个平台而设计的；但随着rpx的兼容性不断增强，再加上upx的精确性不如rpx，使得现在推荐使用rpx。

如何设置全局样式：

```
//app.vue

<style>
page {

}
</style>
```

（6）资源引入

引入资源时，不推荐使用相对路径，推荐使用绝对路径， ‘@/xxx.png’ 是根目录下的xxx.png（但如果是路径保存为js的变量，就不能加@）；非引入资源时（如路由跳转），就根据各自的语法规范。

（7）开发/生产环境

生产环境判断：

```
if(process.env.NODE_ENV == 'development')
  console.log('开发环境')
else console.log('生产环境')
```

### 2.2 Vue如何使用

一般情况下Vue语法直接使用就行，但是Vue版本需要配置，Vue3.2的script 色图片语法糖对于原有的微信小程序语法也有变化。

需要在manifast.json中配置：

```
...
"vueVersion": "3",
...
```

Vue3.2的使用：

```
//微信小程序的生命周期和上拉加载等等在Vue2 Vue3.0都可以写在配置项中，而Vue3.2的script setup用法如下：

<script setup>
import {onLoad} from '@dcloudio/uni-app'
onLoad((options) => {
    console.log(options)
})
</script>
```

### 2.3 配置文件

（1）manifast.json

manifast.json是整个项目的配置文件，可配置项目名，Vue版本，小程序的appid，logo等，里的mp-weixin配置项就是微信小程序project.config.json的相关配置。

（2）pages.json

pages.json和微信小程序的app.json用法一样，可配置页面，导航栏，tabBar等，

不同点：

* window配置项变成了globalStyle

* pages配置项不是数组，而是对象，每个对象可以放path，style，style里面就是微信小程序各个页面的json文件中的样式属性，会覆盖全局配置的样式

### 2.4 分包

分包的使用与微信小程序相同，但是pages配置项和主包一样可以设置style

如在根目录下创建packageA文件夹作为分包，里面创建 GoodsDetail/GoodsDetail.vue

```
"subpackages": [
  {
    "root":"packageA",
    "pages":[{
      "path": "GoodsDetail/GoodsDetail",
      "style": {}
    }]
  }
],
```

### 2.5 自定义组件

自定义组件都放在 /components 目录下，可通过右键新建组件快速创建

自定义组件不用像vue需要引入注册，也不需要像微信小程序需要配置json，而是直接使用

### 2.6 uni-ui

uni-app内置的组件库

旧版本会自动放在components中，新版本需要自己新建一个uni_modules文件夹，栽倒dcloud官网下载uni-ui

uni-ui的组件都不需要引入就可以直接使用

uni-ui可以直接修改源代码
uni-ui直接给class无法修改样式
uni-ui常用：

## 3 网络请求

微信小程序无法使用axios，原生小程序的网络请求API功能也不够用（如没有拦截器）

```
npm install --save @escook/request-miniprogram

//main.js
//挂载到uni，可以使用拦截器，里面调用微信小程序的api
import {$http} from '@escook/request-miniprogram'
$http.baseUrl = '...'
//请求拦截器
$http.beforeRequest = (opt) => {
  uni.showLoading({
    title: '加载中...'
  })
}
//响应拦截器
$http.afterRequest = (res) => {
  uni.hideLoading()
}
uni.$http = $http

//用到的地方中
uni.$http.get('/api/public/v1/home/swiperdata').then(res => {
    console.log(res.data)
})
```

注意，由于项目最终运行到微信小程序端，所以网络请求的要求也和微信小程序一样，需要配置合法域名，或勾选不检验合法域名

## 4 多端适配

### 4.1 平台判断

大部分组件和API，uniapp已经做了跨平台的封装，可以直接使用；但是部分的组件和API由于平台特性而无法跨平台（组件和API在哪个平台可使用详见文档）

在需要自己做跨平台，或不同平台需要不同的个性化，就需要自己进行平台判断。

运行时判断：

```
switch(uni.getSystemInfoSync().platform){
  case 'android':
    console.log('安卓')
    breeak
  ...
}
```

编译时判断：

使用注释条件编译

```
<template>
  <!-- #ifdef h5 -->
  <text>h5</text>
  <!-- #endif -->
  <!-- #ifdef MP-WEIXIN -->
  <text>weixin</text>
  <!-- #endif -->
</template>

<script>
export default {
  onLoad(){
    // #ifdef h5
    console.log('h5')
    // #endif
    // #ifdef MP-WEIXIN
    console.log('weixin')
    // #endif
  }  
}
</script>

/* #ifdef h5 */
...
/* #endif */
/* #ifdef MP-WEIXIN */
...
/* #endif */

<style>

</style>
```

| #ifdef  | 仅在当前平台 |
| ------- | ------ |
| #ifndef | 除了该平台  |

具体的平台类型详见文档，此外还可以判断是在Vue2还是Vue3

```
// #ifdef VUE3
...
// #endif
```

还可以在pages.json中使用（只有pages.json这个json文件可以用）：

由于JSON的严格性，最后一个属性不能加逗号，而条件编译若不成立则整个代码块都不变异，所以需要特别注意逗号。

```
{
  ...
  "xxx":{...}
  // #ifdef h5
  ,"yyy":{},
  // #endif
  ...
}
```

若是globalStyle想实现跨平台，不推荐使用条件编译，推荐使用平台节点：

节点里面的配置，建议参考各平台的说明，直接使用各平台的特有属性

```
{
  "globalStyle":{
    ...
    "mp-weixin":{...}
  }
}
```

此外，static目录也可使用条件编译，在对应平台打包对应的文件夹爱，以此减少打包体积，具体详见文档。

运行时判断和编译时判断的区别：

- 编译时判断，若不符合条件直接不编译，而运行时编译则会全部编译，且运行时多了个判断平台的操作，所以性能上编译时判断占优

- 编译时判断可以在模板、js、css、pages.json中使用，运行时判断只能在js，模板（v-if，v-show）使用，使用上编译时判断也占优

- 编译时判断无法判断安卓，ios，此时只能用运行时编译

### 4.2 各平台注意事项

123

### 4.3 打包发布

uniapp发布微信小程序：
1.微信后台-开发-开发管理-开发设置-服务器域名-来设置合法域名
2.dcloud开发者中心-创建项目-复制项目的appid到manifast.json中
3.复制小程序appid到manifast.json】
4。HBuilder-发行-小程序微信-输入小程序名和小程序appid点击发行
5.弹出的微信开发者工具-上传-输入版本号上传
6.微信后台-管理-版本管理-提交审核

end

```

```

```

```
