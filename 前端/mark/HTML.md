驼峰标识问题：

HTML5一直都没有驼峰标识，不能识别大写，需要用到大写时，需要变为 -小写，如：

userName  变为 user-name

因此，css的选择器等也不能用驼峰命名

路径：

绝对路径：从根目录开始，下一级用/，也可以使用网络图片，使用网址访问
相对路径：同一个目录中，可以直接访问，下一级用/,上一级用../

# 一、基本结构

```
<!DOCTYPE html> //使用HTML5,必须在最顶部
<html lang=”zh-CN”> //表示中文网站
<head>
  <meta charset="UTF-8">
</head>
<body>
</body>
</html>
```

html的内容默认不换行。多个空格默认只显示一个
书写在不同行的标签会多出一个空格，在同一行在不书写空格前提下，不会有空格

# 二、标签与属性

标签的各个属性用空格隔开，但不分顺序，数值型属性单位为像素或百分比
属性格式：key=”value”

标签格式：

双标签：<xxx></xxx>

单标签：<xxx />  或  <xxx>  推荐第一种

## 1 文本类

```
<title>网站标题</title>
<h1>一级标题</h1>….. <h6>六级标题</h6>  独占一行，字体从大到小
<p>段落标签</p>
<br>和<br />       单标签，换行
<!—注释-->
文本格式化标签
加粗：<strong></strong> 或者 <b></b>
倾斜：<em></em>          或者 <i></i>
下划线：<ins></ins>      或者 <u></u>
删除线：<del></del>      或者 <s></s>
```

## 2 盒子标签

div和span，没有语义

div与p的区别：

p有自带的margin-top和margin-bottom，div没有

```
<div></div> 独占一行
<span></span> 不换行
```

## 3 图片标签

```
<img src="" alt="" /> 单标签，不换行
```

| src    | 图像路径，必选属性                                    |
| ------ | -------------------------------------------- |
| alt    | 替换文本，图片不能正常显示时，显示的文本                         |
| title  | 显示文本，鼠标移动到图片时显示的文本                           |
| border | 设置边框                                         |
| width  | width和height只修改一个时另一个等比缩放，两个都改可能会扭曲图片，一般只改一个 |
| height | 同上                                           |

## 4 超链接

分为：外部链接，内部链接，空链接，下载链接，锚点链接五种和一种元素链接
被a标签包含的标签（如img标签）整个元素成为超链接，称为元素链接

```
<a href="#">超链接</a>  不换行
```

属性：

| href   | 必选属性，跳转网址(外部链接)或自己html路径(内部链接)，#表示不跳转(空链接),文件或者压缩包(下载链接)。#id(锚点链接，需要在待跳转的标签中添加 id=”id名”) |
| ------ | ---------------------------------------------------------------------------------------- |
| target | 跳转方式，默认为_self当前页面打开，_blank为新窗口打开                                                         |

## 5 特殊字符

| $space; | 空格  |
| ------- | --- |
| $lt;    | 小于号 |
| $gt;    | 大于号 |

# 三、高级标签

## 1 表格

thead,tbody无功能，只是增加可读性，非必要
tr为行，td为普通单元格，th为表头单元格（加粗居中，非必要）

```
<table>
<thead>
    <th></th>
    ...
    <th></th>
</thead>
<tbody>
   <tr><td></td>...<td></td></tr>
   ...
   <tr></tr>
</tbody>
</table>
```

table属性：

| align        | 整个表格页面对齐位置，left，center，right |
| ------------ | ---------------------------- |
| cellpadding  | 单元格和其内容的距离                   |
| border       | 边框宽度                         |
| cellspacing  | 每个单元格之间的距离                   |
| width和height | 宽和高                          |

合并单元格（在写入文本之前）：

1. 确定跨行合并（合成一列）还是跨列合并（合成一行）

2. 找到目标td，添加属性rowspan=”value”（跨行）或者colspan=”value”（跨列），value的值为合并的单元格数量

3. 删除合并后多余的td

## 2 列表

```
无序列表：
<ul>
<li></li>
</ul>
li之间没有顺序级别之分，是并列的，每个li前有圆点；按照规范，ul下一级只能有li，li的下一级可以放除了li之外的所有标签。

有序列表
<ol>
<li></li>
</ol>
li之间有顺序但是还是并列的，li前有数字序号；按照规范，ol下一级只能有li，li的下一级可以放除了li之外的所有标签。

自定义列表
<dl>
<dt></dt>
<dd></dd>
</dl>
dt可以有多个，但一般都是一个dt和多个dd为组合，可以有多组
dd之前有缩进，dt没有，dd，dt并列；按照规范，dl下一级只能dd，dt，dd，dt下一级可以翻除了dd，dt之外标签。
```

## 3 表单

一个表单由表单域，表单控件，提示信息组成
表单域是包含所有表单控件和提示信息的区域
表单控件是表单中的每个方框
提示信息是每个方框的提示说明

```
<form>表单域</form>
属性：
action：提交的后台地址
method：提交方式
name：表单域的名字

输入表单元素
<input type="">  单标签，不换行，type必须有
属性：
type的值：
text:文本框，password:*密码，
radio:单选框，checkbox:复选框
button:普通按钮，submit:提交按钮，提交后台，reset:重置按钮，所有表单恢复默认值
image:图像形式的提交按钮
file:上传文件，hidden:隐藏的表单
其中button也有单独的标签，常用属性disabled=”disabled”  无法点击按钮

name：相同name的radio才能生效爱哦单选，同一组选择框应当都是相同的name
id：id是唯一的，通常与label标签搭配使用
value：表单的默认显示文本
checked=”checked”：选择框默认被选上
maxlength：值为正整数，表单文本的最大长度

<label for=”绑定的表单id”>文本</label>
效果：点击label包含的文本，绑定的表单会生效。

下拉表单元素
<select>
<option></option>
       ...
      <option></option>
</select>
option的属性，selected=”selected”则默认被选上。

文本域元素
<textarea>默认显示文本</textarea> 属性cols，rows设置宽高
```

# 四、 HTML5新特性

狭义的H5只是指本身的标签等，广义的H5则是指H5,C3,JS的集合。
这些新特性都有兼容性问题。移动端则没有兼容性问题。

## 1 新标签

为了方便搜索引擎，新增了名字不同的新盒子标签，功能与div一样，只是名字不同

注意，IE9这些标签不是块元素，所以使用时最好display: block;

| 标签      | 说明   |
| ------- | ---- |
| header  | 头部   |
| main    | 主体部分 |
| footer  | 底部   |
| nav     | 导航栏  |
| aside   | 侧边栏  |
| article | 文章   |
| section | 某段内容 |



## 2 多媒体标签

### 2.1 视频

只支持MP4,WebM，Ogg三种格式，且各个浏览器支持的各不相同，不过几乎所有浏览器都支持MP4

```
<video src="路径"></video>

由于各个浏览器支持的格式不同，可以这样处理：
<video>
  <source src="xx.mp4" type=”video/mp4”>
  <source src="xx.ogg" type=”video/ogg”>
  <h3>浏览器不支持该格式</h3>
</video>
```

| src           | 路径                                                                         |
| ------------- | -------------------------------------------------------------------------- |
| width和height  | 宽高，单位px或%                                                                  |
| autoplay      | 是否自动播放（默认不）                                                                |
| muted         | 是否静音播放（默认不静音），可以解决谷歌浏览器强制不能自动播放的问题                                         |
| controls      | 是否显示播放控件，即播放，音量，全屏等按钮                                                      |
| loop          | 循环播放（默认只播放一次的                                                              |
| preload       | 是否预先加载视频，设置了autoplay则忽略该属性（auto：预加载，none：不预加载，metadata：只预加载元数据如大小、时间、第一帧等） |
| poster=“图片路径” | 视频等待加载时的封面                                                                 |

### 2.2 音频

只支持MP3，Wav，Ogg三种格式，各浏览器支持的也不同，但几乎都支持MP3。

```
<audio src=""></audio>

由于各个浏览器支持的格式不同，可以这样处理：
<audio>
  <source src="xx.mp3" type=”audio/mpeg”>
  <source src="xx.ogg" type=”audio/ogg”>
  <h3>浏览器不支持该格式</h3>
</audio>
```

属性没有width和height

autoplay谷歌浏览器无效，需要js解决

其他属性与视频一样

### 2.3 音频/视频DOM操作：

play() 播放
paused 是否已暂停 true已暂停
pause() 暂停
load() 重新加载
currentSrc 返回url
src 返回或设置url
preload 设置或返回音频的preload属性
currentTime 返回当前播放的时间点，单位秒
startTime 当前时间，一般0
duration 时间长度 单位秒

networkState 返回网络状态

* 0 初始

* 1 空闲 （此时还未建立网络连接）

* 2 正在加载

* 3 没找到或不支持

readyState 返回当前就绪状态

* *0 还未获取任何数据

* 1 已获得元数据，但未获得媒体数据，无法播放

* 2已获得当前位置媒体数据，但未获得下一位置媒体数据，或当前位置是最后

* 3当前/下一位置美体数据都获得

* 4获得

## 3 input增强

### 3.1 新增的type

若输入的格式不一致，会自动报错。

email 邮箱   url 网址  tel 手机  number
date       time  month  week 
search   color

### 3.2 新增的属性：

required=”required”：内容不能为空，否则点击submit的表单会报错
placeholder=”文本”:有输入时清空，无输入时恢复。Input::placeholder {}可以修改样式
autofocus=”autofocus”：自动获得焦点
autocomplete: on | off ：默认是打开的，点击submit后记录历史，必须有name属性才生效。
multiple=”multiple”：多选文件提交，用于默认只能选一个文件提交的file表单。

## 4 绘图

### 4.1 canvas

用JavaScript绘2d图，特点：依赖分辨率，可保存成png或jpg，适合做游

```
html中：
<canvas id=”can” width=”500px” height=”500px”></canvas>     //给id，设置画板宽高
Js中：
let c=document.getElementById('can')
    //初始化
    let ctx = c.getContext('2d')
    //1.填充
    ctx.fillStyle="red" //填充色
    //画填充矩形
    ctx.fillRect(0,0,100,100) //起始x，y和终点x，y
    //填充文字
    ctx.font="50px 微软雅黑"  //字体
    ctx.fillText("abcd",0,400)

    //2、画直线，圆形，空心文字
    //设置画笔
    ctx.lineWidth="2"     //画笔粗细
    ctx.strokeStyle="blue"  //画笔颜色
    ctx.lineCap="round"  //原有的基础上在两端加上圆角
    //直线
    ctx.moveTo(150,150)   //起始xy
    ctx.lineTo(200,200)   //重点xy
    ctx.stroke()          //画线
    //圆形
    ctx.beginPath() 
    ctx.arc(300,300,25,5,2*Math.PI,false) //圆心xy，半径，距起点长度，画多长，顺时针false（起点在3点钟方向）
    ctx.stroke()
    ctx.closePath()
    //空心文字,可设置字体，若画笔过粗会变成实心
ctx.strokeText('123',400,400)
//3、裁剪图片
    let pic=document.getElementById('pic')  //获取img标签
    //图片加载完后再裁剪
    pic.onload=function(){
      //待裁剪图，裁剪起始xy宽高，裁剪后放的xy宽高（这个宽高设置不好会缩放图片）
      ctx.drawImage(pic,0,0,260,500,100,100,200,500)
    }


fill() 填充颜色
当绘的2d图发生变化时，需要清空整个画板，再重画
ctx.clearRect(x1,y1,w,h) 画板起始xy，画板宽高
当画时钟，转盘这种大圆形时,为了方便：
ctx.transition(x,y) 将起始点从左上角，移动到xy，xy一般是圆心
c.width  c.height 获得画板宽高，以计算半径
整个画板可用圆角边框设置为圆形，设置背景色
典型案例：数字时钟
注意点：
*圆形边缘坐标 x=r*cos角度 y=r*sin角度
*Math.cos(弧度)  弧度=(角度/180)*PI
*电脑xy是左下正，数学xy是左上正
*0度是三点钟方向，0点是12点钟方向，需要加减法，取余转化
```

### 3.2 svg

用xml描述2d
特点：不依赖分辨率（即缩放不失真），可使用事件监听，适合渲染大型2d图形（如地图），不适合做游

```
可以引入svg文件，也可以<img src=”xxx.svg”>
也可以：
<svg>
    <!-- 圆形，圆心xy，半径，画笔颜色，画笔粗细，填充色 -->
    <circle cx="50" cy="50" r="20" stroke="red" stroke-width="10" fill="blue"></circle>
    <!-- 椭圆，圆心xy，xy半径，画笔颜色，画笔粗细，填充色 -->
    <ellipse cx="200" cy="50" rx="20" ry="20" stroke="red" stroke-width="10" fill="blue"></ellipse>
    <!-- 矩形，起始xy，宽高,圆角边框半径，画笔颜色，画笔粗细，填充色 -->
    <rect x="50" y="100" width="20" height="20" rx="5" ry="5" stroke="red" stroke-width="10" fill="blue"></rect>
    <!-- 直线 起始xy，终点xy -->
    <line x1="100" y1="200" x2="200" y2="500" stroke="red" stroke-width="10"></line>
    <!-- 由各点连成的折线 各个点的xy -->
    <polyline points="10 10 20 20 30 30" stroke="red" stroke-width="5"></polyline>


  </svg>
```

## 4 拖放API

## 5 地理定位

Geolocation

## 6 Web Storage

本地存储，多页面可共享数据，在F12的application可以看到loaclstorage和cookie
与h5之前的cookie相比：
cookie：
带请求头，有安全隐患，大小4KB，键值对以字符层形式存储，低版本IE不支持
Web storage：大小4M-5M（根据浏览器）
local storage：
永久存储，只有清除缓存或主动调用clear()清除才会被清除
session storage：
回话存储，关闭会话（即浏览器）就清除数据
使用时，先用 if(window.localStorage) if(window.sessionStorage)看浏览器是否支持，为了方便调用api，一般也用变量存储window.localStorage  window.sessionStorage
api：
window.sessionStorage   window.localStorage  调用api，window.可以省略，两者的api相同
setItem('key','value') 增，value为字符层，数字自动会转，其他需要自己主动转
.key=value
[‘key’]=value
getItem('key')         查
.key
[‘key’]
removeItem('key')      删
clear()                清空所有
JSON有转换类型的api，如JSON.stringify(obj)将对象转字符层

## 7 Web Worker

## 8 Web Socket
