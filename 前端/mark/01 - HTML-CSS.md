# 一、HTML

HTML 标签无法识别大写，遇到大写会转化成 \-小写 ，如 \<xxx-yyy\> ，不过打包工具可以解决。

（1）基本

```
<!DOCTYPE html>
<!-- 使用 HTML5,必须在最顶部 -->

<!-- 根元素 -->
<html lang="en">
  <!-- head 中用来设置页面、引入资源等 -->
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>标题</title>
  </head>

  <!-- 页面主体 -->
  <body>
    <!-- 注释 -->

    <!-- 特殊字符，分别是空格，小于号、大于号 -->
      < >

    <!-- 换行 -->
    <br />

    <!-- 行内元素，一行多个 -->
    <span>文本</span>
    <strong>加粗</strong>
    <b>加粗</b>
    <em>倾斜</em>
    <i>倾斜</i>
    <ins>下划线</ins>
    <u>下划线</u>
    <del>删除线</del>
    <s>删除线</s>

    <!-- 块级元素，独占一行 -->
    <div>独占一行</div>
    <p>p 比 div 在多了上下 margin</p>

    <!-- 行内快元素，一行多个 -->
    <a href="">link</a>
    <img src="" alt="" />
    <input type="text" />

    <!-- 属性没有顺序之分，多个属性用空格隔开 -->
    <div id="app" class="box"></div>

    <!-- 布尔属性，value 只有有或没有两种情况，可以简写 -->
    <button disabled="disabled"></button>
    <button disabled></button>

    <!-- 双标签 -->
    <div></div>
    <!-- 单标签，/ 不加，但最好加上 -->
    <input />
  </body>
</html>
```

html 内容默认不换行。多个空格默认只显示一个。

书写在不同行的标签会多出一个空格，在同一行在不书写空格前提下，不会有空格。

（2）图片、超链接

都是行内快元素：

```
<img src="" alt="" /> 单标签，不换行
```

| 属性           | 描述                                           |
| ------------ | -------------------------------------------- |
| src          | 图像路径，必选属性                                    |
| alt          | 替换文本，图片不能正常显示时，显示的文本                         |
| title        | 显示文本，鼠标移动到图片时显示的文本                           |
| border       | 设置边框                                         |
| width、height | width和height只修改一个时另一个等比缩放，两个都改可能会扭曲图片，一般只改一个 |

超链接：

分为：外部链接，内部链接，空链接，下载链接，锚点链接五种和一种元素链接
被a标签包含的标签（如img标签）整个元素成为超链接，称为元素链接

```
<a href="#">超链接</a>  不换行
```

| 属性     | 描述                                                                                       |
| ------ | ---------------------------------------------------------------------------------------- |
| href   | 必选属性，跳转网址(外部链接)或自己html路径(内部链接)，#表示不跳转(空链接),文件或者压缩包(下载链接)。#id(锚点链接，需要在待跳转的标签中添加 id=”id名”) |
| target | 跳转方式，默认为_self当前页面打开，_blank为新窗口打开                                                         |

（3）表格

* 块级元素：table、tr、thead、tbody

* 行内快元素：th、td

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <table>
      <!-- thead、tbody 不是必须得 -->
      <thead>
        <th>表头</th>
        <th>表头</th>
      </thead>
      <tbody>
        <tr>
          <td>1</td>
          <td>2</td>
        </tr>
        <tr>
          <td>3</td>
          <td>4</td>
        </tr>
      </tbody>
    </table>

    <!-- 合并单元格 -->
    <table border="1">
      <tr>
        <td colspan="2">1</td>
        <td rowspan="2">2</td>
      </tr>
      <tr>
        <td>3</td>
        <td>4</td>
      </tr>
    </table>
    <!-- 合并前 -->
    <!-- <table>
      <tr>
        <td>1</td>
        <td></td>
        <td>2</td>
      </tr>
      <tr>
        <td>3</td>
        <td>4</td>
        <td></td>
      </tr>
    </table> -->
  </body>
</html>
```

| table 属性     | 描述                           |
| ------------ | ---------------------------- |
| align        | 整个表格页面对齐位置，left，center，right |
| cellpadding  | 单元格和其内容的距离                   |
| border       | 边框宽度                         |
| cellspacing  | 每个单元格之间的距离                   |
| width、height | 宽、高                          |

（4）列表

都是块级元素：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <!-- 无序列表 -->
    <ul>
      <li>1</li>
      <li>2</li>
    </ul>

    <!-- 有序列表 -->
    <ol>
      <li>1</li>
      <li>2</li>
    </ol>

    <!-- 自定义列表 -->
    <dl>
      <dt>title</dt>
      <dd>1</dd>
      <dd>2</dd>
    </dl>
  </body>
</html>
```

（5）表单

一个表单由表单域、表单控件、提示信息组成。表单域是包含所有表单控件和提示信息的区域。

* 块级元素：form、select、option

* 行内快元素：input、button、textarea

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <form action="">
      <div>
        <input type="text" />
        <button disabled>button</button>
      </div>

      <div>
        <textarea rols="50" cols="50"></textarea>
      </div>

      <div>
        <!-- label 效果是只要点击了 label 的内容就能选中 radip 、checkbox -->

        <label for="radio-id-1">
          <input type="radio" id="radio-id-1" name="radios" />
          <span>radio 1</span>
        </label>

        <label for="radio-id-2">
          <input type="radio" id="radio-id-2" name="radios" />
          <span>radio 1</span>
        </label>
      </div>

      <div>
        <label for="checkbox-id-1">
          <input type="checkbox" id="checkbox-id-1" />
          <span>agree</span>
        </label>
      </div>

      <select>
        <option value="1">options 1</option>
        <option value="2" selected>options 2</option>
      </select>
    </form>
  </body>
</html>
```

| form 属性 | 描述         |
| ------- | ---------- |
| action  | 提交的后端 url  |
| method  | 提交的 method |
| name    | form name  |

| input type | 描述                        |
| ---------- | ------------------------- |
| text       | 文本框                       |
| password   | 密码框                       |
| hidden     | 隐藏的文本框                    |
| radio      | 单选框                       |
| checkbox   | 复选框                       |
| button     | 普通按钮、按钮也有单独的标签 \<button\> |
| submit     | 提交按钮                      |
| reset      | 重置按钮，重置所有表单值              |
| image      | 图片形式的按钮                   |
| file       | 文件上传按钮                    |

| input 属性         | 描述                              |
| ---------------- | ------------------------------- |
| value            | 表单值                             |
| name             | 只有相同 name 的 radio 才能实现单选        |
| id               | 唯一 id ，通常配合 \<label\>           |
| checked、selected | radio、checkbox 是否选中、option 是否选中 |
| disabled         | 是否禁用、\<button\> 也有该属性           |

表单应该都放在 form 中，可以避免很多问题，如搜索功能：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <!-- 错误做法，监听 button 的 click 事件，需要处理很多问题，如 enter 也要触发、中文输入 enter 问题等等 -->
    <div>
      <input type="text" />
      <button>搜索</button>
    </div>

    <!-- 正确做法，只要监听 form 的 submit 事件就能解决上述问题 -->
    <form action="">
      <input type="text" />
      <input type="submit" value="搜索" />
    </form>
  </body>
</html>
```

## 2 HTML5

（1）语义化标签

和 div 一模一样，只是语义化不同，利于 SEO ：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <header>header</header>
    <main>main</main>
    <footer>footer</footer>

    <nav>导航栏</nav>
    <aside>侧边栏</aside>

    <article>文章</article>
    <section>某段内容</section>
  </body>
</html>
```

（2）多媒体标签

```
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
      <!-- 视频，只支持 MP4，WebM，Ogg 三种格式，各浏览器支持不同，但几乎都支持 MP4 -->
      <video src=""></video>

      <!-- 由于各个浏览器支持的格式不同，可以这样处理 -->
       <video>
        <source src="xx.mp4" type=”video/mp4”></source>
          <source src="xx.ogg" type=”video/ogg”></source>
          <h3>浏览器不支持该格式</h3>
       </video>

       <!-- 音频，只支持 MP3、Wav、Ogg 三种格式，各浏览器支持的也不同，但几乎都支持 MP3 -->
       <audio src="">
       </audio>

       由于各个浏览器支持的格式不同，可以这样处理：
       <audio>
         <source src="xx.mp3" type=”audio/mpeg”>
         <source src="xx.ogg" type=”audio/ogg”>
         <h3>浏览器不支持该格式</h3>
       </audio>
</body>
</html>
```

| video 属性      | 描述                                                                         |
| ------------- | -------------------------------------------------------------------------- |
| src           | 资源路径                                                                       |
| width、height  | 宽、高，单位 px 或 %                                                              |
| autoplay      | 是否自动播放（默认不）                                                                |
| muted         | 是否静音播放（默认不静音），可以解决谷歌浏览器强制不能自动播放的问题                                         |
| controls      | 是否显示播放控件，即播放，音量，全屏等按钮                                                      |
| loop          | 是否循环播放（默认只播放一次的                                                            |
| preload       | 是否预先加载视频，设置了autoplay则忽略该属性（auto：预加载，none：不预加载，metadata：只预加载元数据如大小、时间、第一帧等） |
| poster=“图片路径” | 视频等待加载时的封面                                                                 |

audio 属性：没有 width、height。autoplay 谷歌浏览器无效，需要 JS 解决，其他属性与视频一样。

JS 操作，视频、音频一样：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <video class=".mp4" src=""></video>
  </body>
  <script>
    var mp4 = document.querySelector(".mp4");

    // 播放
    mp4.play();
    // 暂停
    mp4.pause();
    // 重新加载
    mp4.load();

    // 是否已暂停
    console.log(mp4.paused);
    // src
    console.log(mp4.currentSrc);

    // 设置 src
    mp4.src = "";

    /**网络状态
     * 0 初始
     * 1 空闲 （此时还未建立网络连接）
     * 2 正在加载
     * 3 没找到或不支持
     */
    console.log(mp4.networkState);

    /**当前就绪状态
     * 0 还未获取任何数据
     * 1 已获得元数据，但未获得媒体数据，无法播放
     * 2 已获得当前位置媒体数据，但未获得下一位置媒体数据，或当前位置是最后
     * 3 当前/下一位置美体数据都获得
     * 4 获得
     */
    console.log(mp4.readyState);
  </script>
</html>
```

（3）input 新特性

type 新类型，若输入的格式不一致，会自动报错：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <form action="">
      <input type="email" />
      <input type="url" />
      <input type="tel" />
      <input type="email" />
      <input type="number" />

      <input type="date" />
      <input type="time" />
      <input type="month" />
      <input type="week" />

      <input type="search" />
      <input type="color" />
    </form>
  </body>
</html>
```

新属性：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <form action="">
      <!-- 必填，在 submit 时验证 -->
      <input required />

      <!-- 自动聚焦 -->
      <input autofocus />

      <!-- input::placeholder 可修改样式 -->
      <input placeholder="请输入..." />

      <!-- submit 时是否记录历史，默认 on，必须有 name 属性才有效 -->
      <input autocomplete="off" />

      <!-- 多选，一般用于 file -->
      <input type="file" multiple />
    </form>
  </body>
</html>
```

（4）绘图

canvas，用 JS 绘制 2D 图，依赖分辨率，可保存为 jpg、png，适合做游戏：

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

vg，用 xml 描述 2D 图，不依赖分辨率（即缩放不失真），可使用事件监听，适合做高清地图：

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

（5）Web Storage

本地存储，多页面可共享数据，在调试工具的 application 可以看到 loaclstorage 和 cookie。

和 cookie 一样是键值对，key、value 都是 string，区别是：

* 网络请求时，请求头会携带 cookie，有安全隐患；大小 4KB 

* Web Storage：不会被网络请求携带，更安全；大小 4M\-5M（根据浏览器）

两种 stroge 的区别：

* local storage：永久存储，只有清除缓存、或主动调用 clear\(\) 清除才会被清除

* session storage：会话存储，关闭会话（即浏览器）就清除

使用：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body></body>
  <script>
    var obj = { a: 1 };

    // set get
    sessionStorage.setItem("key", JSON.stringify(obj));
    console.log(JSON.parse(sessionStorage.getItem("key")));

    // 删除
    sessionStorage.removeItem("key");

    // 清除全部
    sessionStorage.clear();
  </script>
</html>
```

（6）其他

拖拽 API ，地理定位 Geolocation，Web Worker ，WebSocket

# 二、CSS 基础

html 标签只是一个语义化的功能，而盒子类型、样式都是由浏览器默认样式决定的，如 div ，p 就是因为默认样式是 display: block; 才会是块盒，p 默认样式由上下的 margin

CSS，层叠样式表，分为：

- 行内样式表：也叫内联样式表，在 html 元素中用 style 属性编写

- 内部样式表；在 <style> 中编写

- 外部样式表：<link> 导入的外部 .css 文件

- 浏览器默认样式表：各个浏览器的默认样式

优先级：默认 > 外部 > 内部 > 行内 。

CSS 只有多行注释：

```
/* 多行注释 */
```

.css 文件导入另一个 .css 文件：

```
@import "./1.css";
```

## 1 盒子模型

（1）盒子模型

盒子由 margin 、border 、padding 、content 构成，分类：

* W3C 标准盒子模型：所有 html 元素都是盒子，浏览器默认样式就是这种模型：
  
  ```
  .box {
    /* 默认值，不需要特意编写 */
    /* box-sizing: content-box; */
  
    /* 特点：width 、height 设置的是 content 的宽高度 */
    /* 总宽高: 142px ，content 宽高: 100px */
    margin: 10px;
    border: 1px solid #000f;
    padding: 10px;
    width: 100px;
    height: 100px;
  }
  ```

* CSS3 盒子模型：CSS3 提出，也叫 IE 怪异盒子模型：
  
  ```
  .box {
    box-sizing: border-box;
  
    /* 特点：width 、height 设置的是 border、padding、content 的宽高度 */
    /* 总宽高: 142px ，content 高度: 78px */
    margin: 10px;
    border: 1px solid #000f;
    padding: 10px;
    width: 100px;
    height: 100px;
  }
  ```

可以继承父盒子的盒子模型：

```
.box {
  box-sizing: inherit;
}
```

JS ：

```
console.log(box.offsetWidth, "content + 2 * padding + 2 * border");
console.log(box.clientWidth, "content + 2 * padding");
```

（2）盒子类型

行内元素、块级元素的说法是老标准，准确的说法是行盒、块盒

主要有行盒、块盒、行内块盒，由 display 指定：

```
div {
  display: block;
}

span {
  display: inline;
}

a {
  display: inline-block;
}
```

特点：

- 只有块盒，行内快盒才可以设置 width ，height ；行盒不能设置 width、height，但可以设置 margin、border、padding，但是需要注意：
  
  * 行盒的 margin 只有左右有效
  
  * 行盒的 padding ，水平垂直都会撑开行盒自己，也会撑开父盒的宽度，但父盒的高度不会撑开

- 行盒、行内块多个占一行、块盒独占一行；行盒、行内快盒内不能放快盒

- 行盒内只能是行盒、行内块盒、内容；行盒和块盒不能在同一界，如果出现了这些情况，浏览器会使用匿名行盒、匿名块盒，匿名盒子不会被渲染出来；最好按规范来，避免不必要的麻烦

常见标签：

* 行盒：a span

* 行内快盒：a image input

* 块盒：div p ul li ol dl table

## 2 属性

属性顺序规范：布局、盒子、背景、文本、字体 。

（1）字体

```
.box {
  /* 默认 normal ，文本的特性，如倾斜 italic */
  font-size: italic;

  /* 文本粗细，string ，number 都行，默认 400 或 normal ，常用的是 700 或 bold  */
  font-weight: bold;

  /* 字体大小 */
  font-size: 20px;

  /* 行高 px、无单位、% 都行，无单位时字体大小的倍数，% 时字体大小百分比 */
  line-height: 20px;

  /* 字体 */
  font-family: "Microsort Yahei";

  /**符合写法
   * 需要按顺序，且 font-size ，font-family 不能省略
   * line-height 前需要加 /
   */
   /* font: italic bold 20px/20px "Microsort Yahei"; */
}
```

（2）文本

```
.box {
  /**字体颜色
   * 只要是颜色属性，就有 4 种形式：rgb(n, n, n) ，"color" ，"#ffffff" ，"#fff"
   * color: transparent; 全透明
   * CSS3 新增 rgba(n, n, n, opecity) 透明度颜色
   */
  color: red;

  /* 首行缩进 */
  text-indent: 2em;

  /* 水平对齐方式 */
  text-align: left;

  /**行盒垂直对齐的基准线，类似英文单词的 4 条线
   * top
   * middle
   * baseline 基线，默认值
   * bottom   可以让垂直排列的 img 没有空隙
   */
  vertical-align: baseline;

  /* 一般默认 none ，不过 <a> 不是，一般也是用来去除 a 的样式 */
  text-decoration-color: none;

  /* 一般默认 none ，不过 li 不是，一般也用来去除 li 的样式 */
  list-style: none;

  /**文本引用，CSS3 新属性
   * 分别是水平偏移，垂直偏移，半径，颜色，前两个必须有
   */
  text-shadow: 2px 2px 5px #000;
}
```

（3）背景

```
.box1 {
  /* 背景颜色 */
  background-color: #000;

  /* 背景图 */
  background-image: url(./1.jpg);

  /* 背景图是否需要平铺，默认会 */
  background-repeat: no-repeat;

    /* 背景图滚动还是固定，scroll | fixed ，默认 scroll */
    background-attachment: fixed;

  /* 距离左上角的 px ，或方位名词（如 center），若只写一个，另一个默认是 center */
  background-position: center center;

  /* 符合写法，顺序随意 */
  /* background: #000 url(./1.jpg) no-repeat fixed center center; */
}

.box2 {
  width: 200px;
  height: 200px;

  /**渐变背景，CSS3 新特性
   * 百分比可以不写
   */
  background-image: linear-gradient(
    to right,
    red 0%,
    blue 50%,
    #000 100%
  );
}
```

（4）盒子属性

```
.box {
  display: block;
  box-sizing: border-box;

  /**margin、padding 4 种写法
   * margin: 10px;                 全部
   * margin: 10px 10px;            上下 左右
   * margin: 10px 10px 10px;       上 左右 下
   * margin: 10px 10px 10px 10px;  上 右 下 左
   */
  /* margin、border、padding 都可以单独设置一个方向，如 margin-left */

  /**
   * 设置了左右 margin，且 auto 的 width，会压缩 content
   * margin: 0 auto; 水平居中
   */
  margin: 10px 20px 10px;

  /**
   * 顺序随意，也可以拆开写 
   * auto 的 width 的 content 会被压缩 
   * auto 的 height，块盒的高度会撑开
   */
  border: 1px solid #000;
  /* 合并多余的单元格 */
  /* border-collapse: collapse; */

  /**CSS3 新属性，圆角边框
   * value 为圆角半径
   * 和 margin、padding 一样的 4 种写法，从左上角开始
   * 也可以拆开写，如 border-top-left-radius
   */
  border-radius: 10px;

  /**
   * auto 的 width 的 content 会被压缩 
   * auto 的 height，块盒的高度会撑开
   */
  padding: 10px 20px;

  /**width ，height 默认是 auto
   * width: auto;  块盒撑满包含块（行盒，行内块盒是内容宽度）
   * height: auto; height 即最高的子元素的 height
   */
  width: 100px;
  height: 100px;

  /**盒子引用，CSS3 新属性
   * 分别是水平偏移，垂直偏移，半径，颜色，内部，前两个必须有，默然阴影在外部，内部可设 inset
   */
   box-shadow: 2px 2px 5px #000 inset;
}

/* margin 为负数时，时向反方向移动 */
.box {
  margin-left: -50px;
}
```

5）CSS API

如 rgb\(\) ，CSS3 也新增了 API：

```
.box {
  /* 计算 */
  width: calc(100% - 80px);
}
```

## 3 选择器

（1）基础选择器

```
/* 通配符选择器，选择全部 html 元素 */
* {}

/* 元素选择器，也叫标签选择器，选择所有此类标签元素 */
div {}

/* id 选择器，选择 html 标签对饮 id 的元素 */
#app {}

/* 类选择器，选择 html 元素对饮 class 的元素 */
.box {}
```

（2）符合选择器

基础选择器互相组合：

```
/* 后代选择器，选择 a 所有后代层级的 b ， */
.box .text {}

/* 子选择器，只选择 a 下一级中的 b */
.list > .item {}

/* 并集选择器，只要其中一个符合，就选中 */
.big, .small {}

/* 一般兄弟选择器，选择 a 之后的所有兄弟 b */
div ~ p {}

/* 相邻兄弟选择器，只选中 a 的下一个兄弟 b */
span + img {}

/**属性选择器
 * 可单独使用，也可以结合其他选择器
 * ^*& 分贝是模糊匹配开头、中间、结尾
 */
[href] {}
.btn[disable] {}
.box[data-id = "1"] {}
.img[src &= ".jpg"] {}
```

（3）伪元素、伪类

伪元素选择器，在 html 中在的选中元素里，生成一个子元素，放在最前面或最后面，但伪元素不会出现在 html 中：

```
/**
 * 默认是行盒
 * content 必须指定，"" 也可以
 * CSS3 之后也可以使用 :
 */
.box::before,
.box::after {
  display: block;
  border: 1px solid #000;
  width: 10px;
  height: 10px;
  background-color: #000;;
  content: "";
}
```

伪类选择器，用于在特定的状态下展示特定的样式：

```
/* 鼠标经过时的样式 */
.box:hover {}

/* input 聚焦的样式 */
input:focus {}

/**链接伪类
 * link    未访问
 * visiter 已访问
 * active  点击
 */
a:link {}
a:visiter {}
a:active {}
```

伪元素使用伪类：

```
.box:hover::before {}
```

（4）CSS3 新选择器

```
/* 多类选择器，选中同时具备这些 class 的元素，只限于 class */
.box.big {}

/**结构伪类选择器
 * E:nth-child() 找到 E 的父元素，并按规则找 E 最近一级子元素
 * n 从 0 开始，但是没有第 0 个元素
 * -child 和 E 无关，-of-type 和 E 有关
 */
.item:first-child {}
.item:first-of-type {}
.item:last-child {}
.item:last-of-type {}
.item:nth-child(1) {}
.item:nth-of-type(1) {}
.item:nth-child(n) {}
.item:nth-of-type(n) {}
/* 奇数 */
.item:nth-child(odd) {}
.item:nth-child(2n + 1) {}
/* 偶数 */
.item:nth-child(even) {}
.item:nth-child(2n) {}

/* 否定伪类选择器，选择不符合条件的元素 */
/* 选中 .item 且不是 .title 的元素 */
.item:not(.title)
```

## 4 显示模式

（1）显示、隐藏

隐藏时不删除元素，保留位置，只会引起 repaint ：

```
.box {
  /* 默认值，继承父盒子的 visibility */
  visibility: inherit;

  /* 隐藏、显示 */
  /* visibility: hidden; */
  /* visibility: visible; */

  /* 隐藏表格行或列 */
  /* visibility: collapse; */
}

/* 设置透明度实现，0 完全隐藏 ，1 完全显示 */
.box {
  opacity: 0;
  /* opacity: 1; */
}

/* 也可以用绝对定位，放在最下面 */
```

不删除元素，不保留位置，会引起 reflow ：

```
.box {
  display: block;
  /* display: none; */
}
```

删除元素，用 JS 实现，不保留位置，引起 reflow 。

（2）溢出

盒子溢出：

```
.box {
  /* 默认值 */
  overflow: visible;

  /* 引出的隐藏 */
  /* overflow: hidden; */

  /* 引出的用滚动实现，auto 会在适合时添加滚动条，scroll 强制添加滚动条 */
  /* overflow: auto; */
  /* overflow: scroll; */
}
```

文本溢出：

```
/* 单行 */
.box {
  /* 溢出文本不换行，并隐层 */
  white-space: nowrap;      
  overflow: hidden;       

  /* 省略号 */  
  text-overflow: ellipsis;
}

.box2 {
  display: -webkit-box;
  -webkit-box-orient: vertical;

  /* 多少行后开始隐藏 */
  overflow: hidden;
  -webkit-line-clamp: 3;

  /* 省略号 */
  text-overflow: ellipsis;
}
```

图片溢出：

```
/* box 宽高不固定 */
.box > img {
  width: 100%;
  height: 100%;
}

/* box 宽高其中一个固定，若 box width 固定则 img width 100% ，反之 height 100% */
.box > img {
  width: 100%;
}

/* box 宽高固定，裁剪 img 的宽或高 */
.box {
  overflow: hidden;
}

,box > img {
  width: 100%;
}

/* box 宽高不固定，不裁剪 img ，则 img 的 width ，height 更大的设置为 100% */
.box > img {
  width: 100%;
}
```

## 5 变黄、过渡、动画

CSS3 新特性。

（1）变换

transform 不会 reflow 和 repaint ，运行在合成线程，所以性能很高，不会阻塞 JS 。

不会影响其他盒子的布局，因为会脱离标准流，但 transform 元素的所有后代元素都会一起变换。

2D：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .box {
        border: 1px solid #000;
        width: 100px;
        height: 100px;
        background-color: #000;
        color: #fff;
        line-height: 100px;
        text-align: center;
        font-size: 30px;
      }

      /* 2D */
      .box1 {
        /* 默认值 */
        transform: none;

        /**移动
         * 参数为 x，y，可以是 number ，负数，也可以是 %
         * 可以只写 x ，y 默认为 0
         * 也可以用 translateX() translateY()
         */
        /* transform: translate(200px, 200px); */

        /**缩放
         * 大于 1 时放大，小于 1 是缩小
         * 只有一个值时作用于 x，y，两个值时分别设置 x，y 的缩放
         * 也可以用 scaleX() scaleY()
         * 浏览器字体大小有最小限制，可以用 scale 解决
         */
        /* transform: scale(2); */

        /**旋转
         * 只能传一个参数，按 Z 周顺时针旋转
         * 2d 只能 Z 轴旋转，rotateX() 这些是 3d 用的
         */
        /* transform: rotate(45deg); */
        /* transform-origin: left bottom; */

        /**倾斜
         * 也可以用 skewX() skewY()
         */
        /* transform: skew(45deg); */
        /* transform: skew(0, 45deg); */

        /* 多重变换时，需要写成如下形式，否则后面的 transform 会覆盖前面的 */
        transform: translate(0200px, 200px) scale(2) rotate(45deg)
          skew(0, 45deg);
      }
    </style>
  </head>
  <body>
    <div class="box box1">2D</div>
  </body>
</html>
```

3D：

Z 轴在屏幕内部：

```
Y
|
|
|------>X
```

（2）过渡

transition 实现：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .box {
        border: 1px solid #000;
        width: 100px;
        height: 100px;
        background-color: #000;

        /* 1s 后，用 ease 方式过渡 2s width */
        /* transition: width 2s ease 1s; */

        /* 只有过渡时间是必须写的，也可以用 ms */
        /* transition: 2s; */

        /* 多个属性的过渡，不写默认就是 all */
        /* transition: all 2s; */
        transition: width 2s, height 10s, background-color 1s;
      }

      .box:hover {
        width: 200px;
        height: 200px;
        background-color: red;
      }
    </style>
  </head>
  <body>
    <div class="box"></div>
  </body>
</html>
```

只有从数值到数值的变化，transition 才有效，如 display 从 none 到 block ，height 从 0 到 auto 的 transition 都是无效的，可以用其他办法解决。

如一个下拉框，可以通过 jS 获取 auto 后的 height 数值，再修改成 0 再修改成 height ，虽然能实现效果，但是会有多次 reflow 。

另一种方法是过渡 transform 的 scale ，实现简单，性能也高，但效果有一些差异：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .dropdown {
        --selector-padding: 10px;
        --selector-height: 30px;
        --option-item-height: 25px;

        position: relative;
        width: 200px;
      }

      .dropdown > .selector {
        padding: 0 var(--selector-padding);
        border: 1px solid #000;
        height: var(--selector-height);
        line-height: var(--selector-height);
        user-select: none;
      }

      .dropdown > .option {
        position: absolute;
        top: calc(var(--selector-height) + 5px);
        left: 0;
        border: 1px solid #000;
        padding: var(--selector-padding) 0;
        width: 100%;
        transform: scale(0);
        transform-origin: top;
        transition: all 0.3s;
      }

      .dropdown > .option > .option-item {
        padding: 0 var(--selector-padding);
        height: var(--option-item-height);
        line-height: var(--option-item-height);
        cursor: pointer;
        transition: all 0.3s;
      }

      .dropdown > .option > .option-item:hover {
        background-color: orange;
      }
    </style>
  </head>
  <body>
    <div class="dropdown">
      <div class="selector">dropdown</div>
      <div class="option">
        <div class="option-item">item 1</div>
        <div class="option-item">item 2</div>
        <div class="option-item">item 3</div>
        <div class="option-item">item 4</div>
        <div class="option-item">item 5</div>
      </div>
    </div>
  </body>
  <script>
    const selector = document.querySelector(".selector");
    const option = document.querySelector(".option");

    function hiddenOption() {
      option.style.transform = "scale(0)";
      window.removeEventListener("click", hiddenOption);
    }

    function selectorClick(event) {
      event.stopPropagation();

      if (option.style.transform === "scale(1)") {
        option.style.transform = "scale(0)";
        return;
      }

      option.style.transform = "scale(1)";

      window.addEventListener("click", hiddenOption);
    }

    selector.addEventListener("click", selectorClick);
  </script>
</html>
```

（3）动画

分为触发型、自动型：

* transition 只能制作触发型的动画，且只能规定 2 个状态的变化

* animation 触发型、自动型都可以，且可以规定多个状态的变化

animation 通过 keyframs（关键帧）设置的状态进行动画，如下是一个自动型的动画：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .box {
        border: 1px solid red;
        width: 100px;
        height: 100px;
        border-right-color: red;
        animation: box-move 3s alternate infinite;
      }

      @keyframes box-move {
        /* from 可以省略 */
        /* 可以用 n% 替代 from，to 来设置多个状态 */

        from {
          transform: translate(0);
        }

        to {
          transform: translate(200px);
        }
      }
    </style>
  </head>
  <body>
    <div class="box"></div>
  </body>
</html>
```

## 6 其他

（1）用户界面样式

```
.box {
  /* 光标样式 */
  cursor: pointer;
}
```

（2）CSS 三角

```
.item1 {
  border: 50px solid transparent;
  border-left-color: black;
  width: 0;
  height: 0;
}
```

（3）精灵图：

将大量小图片合到一张大图片，一次请求就能获取大量图片，能减少对服务器的请求，减少服务器压力。

盒子的宽高，背景图为精灵图，再通过设置背景图的偏移达到裁剪精灵图的目的。

```
<style>
  .sprite {
    background: url("../1.png") no-repeat;
    display: inline-block;
  }
</style>

<body>
  <div class="sprite" style="background-position: 0 0; width: 100px; height: 100px"></div>
  <div class="sprite" style="background-position: -50 -50; width: 100px; height: 100px"></div>
</body>
```

（4）字体图标

看似是图标，实际是文字，可以设置字体文本类样式。

图标库：[https://icomoon.io/](https://icomoon.io/) [https://www.iconfont.cn/](https://www.iconfont.cn/)

引入使用示例：

```
<style>
@font-face {
    font-family: 'FontAwesome';
    src: url('/fonts/fontawesome-webfont.eot');
    src: url('/fonts/fontawesome-webfont.eot?#iefix') format('embedded-opentype'),
         url('/fonts/fontawesome-webfont.woff2') format('woff2'),
         url('/fonts/fontawesome-webfont.woff') format('woff'),
         url('/fonts/fontawesome-webfont.ttf') format('truetype'),
         url('/fonts/fontawesome-webfont.svg#fontawesomeregular') format('svg');
    font-weight: normal;
    font-style: normal;
}
</style>

<body>
    <i class="fa fa-star"></i>
</body>
```

# 三、属性计算

计算后，每个元素所有的 CSS 属性都会有 value ，且 value 都是绝对单位，如 em 变 px ，颜色都变成 rgb\(\) 。

根据默认样式表、作者样式表计算，过程：

* 确定声明值：没有冲突的属性直接是结果

* 层叠冲突：
  
  * 比较虫咬行：行内样式表 \> 内部样式表 \> 外部样式表 \> 默认样式表，此外一些属性重要性也有区别，如使用 flex: 1; 后 width 失效
  
  * 比较优先级：根据权重比较选择器的优先级
  
  * 比较源次序：若还是有冲突，则后面的属性、选择器覆盖前面的

* 继承：若还有无 value 的属性，就继承，一般文字、文本属性可以继承
  
  * line\-height 继承：px 和比例直接继承，百分比会在父元素计算成 px 后再继承

* 使用默认值：若还有无 value 的属性，就使用默认值
  
  * 符合属性会覆盖前面的属性，如：
    
    ```
    .box {
      font-weight: 700;
    
      /* 符合属性没有写 font-weight ，所以使用默认值 400 覆盖前面的 700 */
      font: 50px "Microsort Yahei";
    }
    ```

（1）选择器的权重

Specificity，也叫特殊性、特定性，权重从高位开始比较，如 0100 大于 0010 。

符合选择器的权重计算：各个位分开计算，十进制求和，且无进位。

```
/* 0 0 0 0 ，* > + ~ */
* {}

/* 0 0 0 1 ，标签，伪元素 */
#app {}

/* 0 0 1 0 ，类、伪类、属性 */
.box {}
:hover {}
[href] {}

/* 0 1 0 0 ，id */
div {}

/* 1 0 0 0 ，行内样式 */

/**1 0 0 0 0 或无穷大
 * 应当尽量避免使用、不好维护
 * important 互相冲突了，就比较权重，用权重大的 important
 * 子元素继承时，只会继承 value ，不继承 important 
 */
.box {
  color: red !important;
}
```

```
/* 0 0 2 0 */
.box:hover {}
.box > .item {}
.box[href] {}

/* 0 1 1 0 */
#app > .box {}

/* 0 0 12 0 */
.a .b .c .d .e .f .g .h .i .j .k .l .m {}
```

# 四、视觉格式化模型

根据各个盒子的几何信息（大小、位置）进行布局。

## 1 包含块

包含块（container block），设置百分比的 margin、border、padding、width 时，是基于包含块的宽度，百分比 height 基于包含块的高度；浮动、绝对定位也是基于包含块的。

分为两类：

* 初始包含块：inital container block ，即根元素 \<html\> 所在的包含块，即视口 viewport，左上角是浮动、定位的参照物

* 非根元素包含块，有以下几种情况：
  
  * 标准流、浮动、定位（static、relative、sticky）的包含块是最近的祖先块盒的 content
  
  * 定位 fixed 的包含块是 viewport
  
  * 定位 absolute 的包含块是最近的非 static 祖先块盒的 padding 区（根元素 \<html\> 默认定位 relative）

absoulte 、fixed 在找到包含块之前，遇到了以下情况的盒子，则这个盒子的 padding 就成为包含块：

* transform 或 perspective 不为 none

* will\-change 为 transform 或 perspective

* contain: paint;

* filter 不为 none，或 will\-change 为 filter （只在 firefox 有效）

## 2 布局

（1）常规流

也叫标准流、普通流、流式布局、百分比布局，即快盒独占一行，行盒、行内快盒一行多个：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .box {
        border: 1px solid #000;
        width: 300px;
        height: 100px;
        background-color: #000;
      }

      .item {
        border: 1px solid red;
        width: 30%;
        height: 30%;
        background-color: red;
      }
    </style>
  </head>
  <body>
    <div class="box">
      <div class="item"></div>
      <div class="item"></div>
    </div>
  </body>
</html>
```

（2）浮动

浮动元素会脱离标准流，浮动起来，不保留原位置，浮动元素按顺序排列在包含块中，若包含块宽度不够放，则浮动元素会排列至下一行。

虽然会脱标，但不会压住一上来的文本和图片。

浮动元素会自动转为 inline-block ：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .box {
        border: 1px solid #000;
        width: 300px;
        height: 100px;
        background-color: #000;
      }

      .item {
        float: left;
        border: 1px solid red;
        width: 30px;
        height: 30px;
        background-color: red;
      }
    </style>
  </head>
  <body>
    <div class="box">
      <div class="item">123</div>
      <div class="item">123</div>
    </div>
  </body>
</html>
```

通常都是希望父元素不设置 height ，而由子元素决定父元素的 height ，但设置浮动后，父元素的 height 会变为 0 ，所以这时候就需要清除浮动（清除浮动元素造成的影响）：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .box {
        /* 兼容低版本 IE */
        *zoom: 1;

        border: 1px solid #000;
        width: 300px;
        background-color: #000;
      }

      /**
       * 也可以只用一个伪元素，用两个更严谨
       * 也可以直接在 html 写一个标签并设置 clear ，但不推荐
       */
      .box::before,
      .box::after {
        display: block;
        /* 清除左右浮动，也可以只清除仪表，如 clear: left; */
        clear: left;
        visibility: hidden;
        content: "";
      }

      .item {
        float: left;
        border: 1px solid red;
        width: 30px;
        height: 30px;
        background-color: red;
      }
    </style>
  </head>
  <body>
    <div class="box">
      <div class="item">123</div>
      <div class="item">123</div>
    </div>
  </body>
</html>
```

也可以直接把父元素变成 BFC ，就能清除浮动。

（3）定位

将盒子定到某一位置不动，由定位模式和边偏移两部分组成：

* 定位通过 position 指定，默认为 static ，即静态定位

* 边偏移通过 top、right、bottom、left 指定，表示距包含块的距离

代码：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <style>
    .box {
      position: relative;
      border: 1px SOLID #000;
      width: 500px;
      height: 3000px;
      background-color: #000;
    }

    .item {
      border: 1px SOLID RED;
      width: 100px;
      height: 50px;
      line-height: 50px;
      text-align: center;
      font-size: 20px;
      background-color: RED;
    }

    /* 相对定位，保留位置，不脱标 */
    .item1 {
      position: relative;
      top: 50px;
      left: 50px;
    }

    /**绝对定位
     * 不保留位置，脱标，会转为 block 盒
     * auto 的 width 为内容宽度
     * 包含块为最近的非 static 盒子，所以一般父元素会设置 relative ，即子绝父相
     */
    .item2 {
      position: absolute;
      top: 50px;
      right: 50px;
    }

    /**固定定位
     * 不保留位置，脱标，会转为 block 盒
     * auto 的 width 为内容宽度
     * 包含块为浏览器 viewport
     */
    .item3 {
      position: fixed;
      top: 0;
      right: 0;
    }

    /**粘性定位
     * relative 基础上，在父元素内 fixed
     * 必须设置 top 才有效
     */
    .item4 {
      position: sticky;
      top: 0;
      left: 15%;
    }
  </style>
  <body>
    <div class="box">
      <div class="item item1">relative</div>
      <div class="item item2">absolute</div>
      <div class="item item3">fixed</div>
      <div class="item item4">sticky</div>
    </div>
  </body>
</html>
```

z-index ：

当定位元素层叠到一起时，可以用 z-index 设置层叠的优先级：

```
/**
 * 只有设置了非 static 的 position ，z-index 才有效
 * 若设置了浮动，需要清除浮动 z-index 才有效
 * 若父元素 position 为 relative ，则子元素 z-index 失效
 */
.item {
  position: absolute;
  z-index: 999;
}
```

层得上下文：

z-index 时基于包含块的，若包含块的祖先元素也设置了 z-index ，可以看成两个 z-index 相加。

（4）flex 布局

又叫弹性布局，伸缩布局等。父元素是弹性容器，子元素是弹性盒子。

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .box {
        margin: 50px 0;
        border: 1px solid #000;
        padding: 10px;
      }

      .item {
        border: 1px solid #000;
        width: 60px;
        height: 30px;
        line-height: 30px;
        text-align: center;
      }

      .box1 {
        /**
         * 子元素会转换成 block 盒，水平显示，但 width，height 会默认设置为内容宽高
         * 设置 display: flex; 后，float、clear、vertical-align 失效
         * 若没有设置 align-items ，且子元素也没有设置 height ，则子元素 height 会撑满父元素
         * 上述情况若父元素也没有设置 height ，则父元素 height 时子元素内容高度
         */
        display: flex;

        /**主轴排列方式
         * flex-start     左排列，默认值
         * flex-end       右编列
         * center         居中
         * space-around   均分
         * space-evenly   均分，且空隙一样大
         * space-between  两边到边缘，中间均分
         */
        justify-content: center;

        /**侧轴排列方式
         * stretch  默认值，撑满父元素
         * flex-start ，flex-end，center
         * 子元素中可用 align-self 单独设置
         */
        align-items: center;

        /**轴向
         * 默 x 为主轴，y 周为侧轴
         * 设置主轴，默然为 row
         */
        /* flex-direction: column; */
      }

      .box2 {
        display: flex;
      }

      .box2 > .item-flex {
        /**
         * 只要设置了 flex ，width，flex-wrap 就无效
         * 设置 flex 的盒子，均分剩余的 content width ，value 为占用的份数
         * flex: none; 去掉 flex
         */
        flex: 1;
      }

      .box2 > .item-fixed {
        /* 设置排列优先级，默认 0 ，大的会排列在小的后面 */
        order: 1;
      }

      .box3 {
        display: flex;
        height: 100px;

        /**换行
         * flex 布局默认不换行，空间不够会压缩子元素的 width
         * 若不换行，又不想压缩 width ，可以在子元素设置 flex-shrink: 0;
         */
        flex-wrap: wrap;

        /* direction，wrap 符合写法 */
        /* flex-flow: column wrap; */

        /**多行的侧轴排列方式
         * stretch  默认值
         * 其他和 justify-content 一样
         */
        align-content: space-around;
      }

      .box3 > .item-big {
        width: 40%;
      }
    </style>
  </head>
  <body>
    <div class="box box1">
      <div class="item">1</div>
      <div class="item">2</div>
      <div class="item">3</div>
    </div>

    <div class="box box2">
      <div class="item item-fixed">1</div>
      <div class="item item-flex">2</div>
      <div class="item item-flex">3</div>
    </div>

    <div class="box box3">
      <div class="item item-big">1</div>
      <div class="item item-big">2</div>
      <div class="item item-big">3</div>
      <div class="item item-big">4</div>
    </div>
  </body>
</html>
```

（5）grid 布局

也叫网格布局、栅格布局。

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .box {
        margin: 50px 0;
        border: 1px solid #000;
        height: 300px;
      }

      .item {
        border: 1px solid #000;
        line-height: 50px;
        text-align: center;
        font-size: 30px;
      }

      .box1 {
        /* 子元素转为 block 盒子 */
        display: grid;

        /**列栅格
         * 1 个 value ，排列 1 个
         * 可以使用 repeat(3, 1fr)
         * 子元素可以不用设置 width ，会自动沾满整个栅格，而栅格的高是内容高度
         * 可以设置 px ，其他的 fr 均分，fr 的 value 是占用的份数
         */
        /* grid-template-columns: 1fr 1fr 1fr; */
        /* grid-template-columns: 1fr 200px 1fr; */
        grid-template-columns: repeat(3, 1fr);

        /**行栅各
         * 格rid-template-rows 优先级高，剩余未指定的 grid-auto-rows 才生效 
         * 子元素可以不用设置 height ，会自动沾满整个栅格，而栅格的宽是内容宽度
         */
        /* grid-template-rows: repeat(3, 1fr); */
        /* grid-auto-rows: 10px 10px 10px; */

        /* 栅格水平、水质排列方式，没有设置 grid-template-columns、grid-template-rows 才需要考虑 */
        /* justify-content: center; */
        /* align-content: center; */

        /**
         * 除了四个边缘外，栅格之间的间距
         * gap 是简写
         * gap: row col;
         * gap: row-and-col;
         */
        gap: 10px;
        /* grid-row-gap: 10px; */
        /* grid-column-gap: 10px; */
        /* grid-gap: 10px; */
      }

      .box2 {
        display: grid;
        grid-template-columns: repeat(3, 1fr);
        gap: 10px;

        /* grid-template-areas:
          "areaname areaname"
          "areaname areaname"; */
      }

      .box2 > .item:first-child {
        /**合并栅格
         * 左闭右开，只差 1 可以只写简写成 grid-column; 2;
         * grid-column 是 grid-column-start 、grid-column-end 的简写
         */
        /* 布局到第 2 列并不合并，布局到第 1 行并合并一个栅格 */
        grid-column: 2 / 3;
        grid-row: 1 / 3;

        /* 也可以命名，在父元素中布局合并栅格 */
        /* grid-area: areaname; */
      }

      .box3 {
        /* 响应式布局，minmax() 为栅格的最小、最大宽度 */
        display: grid;
        grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));
        gap: 10px;
      }
    </style>
  </head>
  <body>
    <div class="box box1">
      <div class="item">1</div>
      <div class="item">2</div>
      <div class="item">3</div>
      <div class="item">4</div>
      <div class="item">5</div>
    </div>

    <div class="box box2">
      <div class="item">1</div>
      <div class="item">2</div>
      <div class="item">3</div>
      <div class="item">4</div>
      <div class="item">5</div>
    </div>

    <div class="box box3">
      <div class="item">1</div>
      <div class="item">2</div>
      <div class="item">3</div>
      <div class="item">4</div>
      <div class="item">5</div>
    </div>
  </body>
</html>
```

## 3 BFC

块级格式化上下文（block formating context），让标准流的块盒形成独立的渲染区域，

\<html\> 默认是 BFC 。

同一个 BFC 中的垂直排列块盒，上下 margin 会合并：

* 若两个盒子的最近一个祖先 BFC 元素是同一个，就属于同一个 BFC 中

* 若某个 BFC 脱离了标准流，那这个 BFC 就从最近一个祖先 BFC 中脱离出来了 

设置 BFC ：

```
/**
 * 只要有其中一个，就能形成 BFC
 * 还有喝多属性可以设置，不过这些最常用
 */
 .box {
  /* 不为 none、block */
  /* display: inline-block; */

  /* 绝对定位 */
  /* overflow: hidden; */

  /* 不为 static、relative */
  /* position: absolute; */
}
```

（1）非父子块盒上下 margin 合并

两个垂直相邻的块盒，上面的 margin-bottom 会和下面的 margin-top 合并，原因是两个块盒都处于 \<html\> 的 BFC 中；

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .box {
        border: 1px solid #000;
        width: 50px;
        height: 50px;
        background-color: #000;
      }

      /**margin 合并规则
      * 两个正数：Math.max(a, b)
      * 两个负数：Math.min(a, b)
      * 一正一负：a + b
      */
      .box1 {
        margin-bottom: 50px;
        /* margin-bottom: -40px; */
        /* margin-bottom: 30px; */
      }

      .box2 {
        margin-top: 50px;
        /* margin-top: -40px; */
        /* margin-top: -20px; */
      }
    </style>
  </head>
  <body>
    <div class="box box1"></div>
    <div class="box box2"></div>
  </body>
</html>
```

解决方法是，可以把其中一个块盒用 BFC 容器包裹，这样一个在 \<html\> 的 BFC 中，另一个在新的 BFC 中，就不会合并 margin 了：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .container {
        overflow: hidden;
        background-color: #000;
      }

      .box {
        width: 50px;
        height: 50px;
        background-color: red;
      }

      .box1 {
        margin-bottom: 50px;
      }

      .box2 {
        margin-top: 50px;
      }
    </style>
  </head>
  <body>
    <div class="container">
      <div class="box box1"></div>
    </div>
    <div class="box box2"></div>
  </body>
</html>
```

（2）父子块盒的上下 margin 塌陷问题

若父元素 border，padding 都没有设置，会造成父子盒子同事设置 margin-top 时，父元素的 margin-top 塌陷的情况，margin\-bottom 同理：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      /**margin 塌陷
       * 子元素 margin-top 无效
       * 父元素的 margin-top 和 子元素的 margin-top 合并，规则和上下块盒 margin 合并一样
       * 即使父元素没有设置 margin-top ，只要子元素设置了，就会塌陷
       **/
      .box {
        margin-top: 50px;
        width: 100px;
        height: 100px;
        background-color: #000;
      }

      .item {
        margin-top: 20px;
        width: 50px;
        height: 50px;
        background-color: red;
      }
    </style>
  </head>
  <body>
    <div class="box">
      <div class="item"></div>
    </div>
  </body>
</html>
```

两种解决方法：

* 父元素设置 BFC ，这样子元素和父元素所处的 \<html\> 的 BFC 就不是同一个了

* 子元素设置浮动或绝对定位实现 BFC ，脱离标准流，和父元素 BFC 就不是同一个了

（3）浮动和 BFC

标准流中，父元素 auto 的 height 不会计算浮动元素的 height ，而 BFC 会，所以 BFC 可以清除浮动。

BFC 也不会覆盖浮动元素压住：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .box {
        overflow: hidden;
        background-color: #000;
        color: #fff;
      }

      .nav {
        float: left;
        width: 50px;
        height: 50px;
        background-color: red;
      }

      /**content 设置 BFC 后
       * content 就不会被浮动的 nav 压住
       * 此时 content 会自带 margin-left ，即 content 到父元素左边缘的距离
       * 若自己设置的 margin-left 小于到父元素左边缘的距离，是无效的，如果像控制 margin ，可以设置浮动元素的 margin-right ，更方便
       */
      .content {
        overflow: hidden;
        height: 100px;
        background-color: blue;
      }
    </style>
  </head>
  <body>
    <div class="box">
      <div class="nav"></div>
      <div class="content"></div>
    </div>
  </body>
</html>
```

## 4 居中

（1）行盒、行内快盒

```
.box {
  width: 100px;
  height: 50px;
  line-height: 50px;
  text-align: center;
}

/* border-box ，line-height 需要减去 border、 padding */
.box {
  box-sizing: border-box;
  border: 1px solid #000;
  padding: 10px 0;
  width: 100px;
  height: 50px;
  line-height: 28px;
  text-align: center;
}

/* border-box 计算 line-height 比较麻烦，也可以直接用 flex */
.box {
  box-sizing: border-box;
  border: 1px solid #000;
  padding: 10px 0;
  width: 100px;
  height: 50px;
  display: flex;
  justify-content: center;
}
```

（2）块盒

```
/* flex 单行水平垂直居中 */
.box1 {
  display: flex;
  justify-content: center;
  align-items: center;
}

/* flex 多行水平垂直居中 */
.box2 {
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  align-content: center;
}

/* 相对于父元素，只有水平居中，适合 PC 端版心居中 */
.box3 {
  margin: 0 auto;
}

/* 绝对定位 */
.box4 {
  position: relative;
  border: 1px solid #000;
  width: 200px;
  height: 100px;
}

.box > .item {
  position: absolute;
  top: 50%;
  left: 50%;
  border: 1px solid #000;
  width: 50px;
  height: 50px;

  /* 方式一，推荐 */
  transform: translate((-50%, -50%));

  /* 方式二，写死，不推荐 */
  /* margin-top: -25px; */
  /* margin-left: -25px; */

  /* 方式三，不推荐 */
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  margin: auto;
}
```

## 5 响应式布局

## 1 适配

（1）视口

视口（viewport），浏览器显示页面的屏幕区域。手机默认都有一个布局视口，是尽量显示整个PC端页面，手指缩放的形式，很不方便，后来就有了视觉视口，显示部分 PC 端页面，手指左右滑动的形式。

现在使用的是理想视口，页面宽度即视口宽度，通过视口标签指定：

```
<meta name="viewport" content="width=device-width, initial-scale=1.0">
```

指定视口宽度为设备宽度，其他属性可以设置缩放比例以及是否可缩放。

（2）分辨率

屏幕真实的分辨率是物理分辨率，px 是逻辑分辨率，PC端是 1 \: 1 的，而移动端中，物理 \: px = n \: 1，这叫物理像素比：

```
// 获取当前的物理像素比
console.log(window.devicePixelRatio);
```

因此，图片放到移动端中，会放大 n 倍而模糊，所以在开发中，拿到图片先要将它缩小 n 倍再放到页面中，它会自动方放大 n 倍，就能不营销图片清晰度。因此，准备图片应当按照物理像素比来，叫n倍图。

缩小图片是用软件工具缩小，而不是写代码。

（2）单位

em：

当前元素 font\-size 的倍数：

```
.box {
  /* 2em === 40px */
  width: 2em;
  font-size: 20px;
}
```

rem：

root em，CSS3 新增，与 em 不同的是只基于 \<html\> 的 font\-size ，可配合多媒体查询实现进一步适配。

```
html {
  /* 浏览器默认一般是 16px */
  font-size: 16px;;
}

.box {
  /* 32px */
  width: 2rem;
}
```

vw，vh：

viewport 宽度为 100vw ，vh同理，会随着 viewport 的变化自动适配，通常 vw 用的比较多。

```
.box {
  width: 50vw;
  height: 50vw;
}
```

## 2 布局

一般用流式布局、flex 布局。

为了避免过多的缩放，可以限制最大最小的 width ：

```
body {
  max-width: 1920px;
  min-width: 360px;
}

.box {
  max-width: 100px;
  min-width: 50px;
}
```

多媒体查询，可以根据不同视口宽度，设置不同的样式：

```
/* 视口宽度在 350px 到 750px 之间时，以下样式适用 */
@media screen and (min-width: 375px) and (max-width: 750px) {
  body {
      background-color: red;
  }
}
```

## 3 移动端的历史遗留问题

（1）移动端click事件300ms延迟

原因：移动端浏览器一般都有双击缩放或双击xxx的场景，为了监听出双击，在点击第一次后，若300ms内再次点击，就是双击。
但是大部分情况下，300ms都是很难被用户接受的

解决：有很多方法，其中一种：

```
npm install fastclick --save
// main.js
import FastClick from 'fastclick'
FastClick.attack(document.body)
```

# 五、CSS 预处理器

有 less 和 sass：

* 区别是定义变量，less 用 @ ，sass 用 \$

* scss 时 sass 的高版本

以下就以 less 为例：

```
npm install -g less
```

解析成 \.css ：

```
lessc ./1.less ./1.css
```

less 中导入其他 less 和 css ：

```
@import "./1.less";
```

注释：

```
// 单行注释不会出现在生成的 css 中
/* 多行注释会保留 */
```

变量：

```
// less
@my-color: #000;
@pre: .box;

.box {
  color: @my-color;
}

@{pre}-title {
  color: @my-color;
}
```

```
/* css */
.box {
  color: #000;
}
.box-title {
  color: #000;
}
```

变量运算，最终单位是最早出现的单位：

```
// less
@my-width: 10 + 20px;
@my-height: 20em + 20 + 40px;

.box {
  width: @my-width;
  height: @my-height;
}
```

```
/* css */
.box {
  width: 30px;
  height: 80em;
}
```

选择器嵌套：

```
// less
// & 时上一级选择器，选择器中 & 只能出现一次
.box {
  font-size: 20px;

  .item {
    color: #000f
  }

  &:hover {
    color: #000f
  }

  &.big {
    color: #000f
  }
}
```

```
/* css */
.box {
  font-size: 20px;
}
.box .item {
  color: #000f;
}
.box:hover {
  color: #000f;
}
.box.big {
  color: #000f;
}
```

函数：

```
// less
// 没有参数时，括号可以省略
.my-flex(@width) {
  display: flex;
  justify-content: center;
  align-items: center;
  width: @width;
}

.my-border(@a, @b, @c) {
  border: @arguments;
}

.my-height(@type) when(@type = big) {
  height: 100px;
}

.my-height(@type) when(@type = small) {
  height: 50px;
}

.box {
  // 调用时必须加上括号
  .my-flex(200px);
  .my-border(1px, solid, #000);
  .my-height(big);
}
```

```
/* css */
.box {
  display: flex;
  justify-content: center;
  align-items: center;
  width: 200px;
  border: 1px solid #000;
  height: 100px;
}
```

循环：

```
// less
.my-for(@i) when (@i > 0) {
  .my-padding-@{i} {
    padding: @i * 10px;
  }
  .my-for(@i - 1);
}

.my-for(3);
```

```
/* css */
.my-padding-3 {
  padding: 30px;
}
.my-padding-2 {
  padding: 20px;
}
.my-padding-1 {
  padding: 10px;
}
```

多媒体查询：

```
// less
.box {
  @media screen and (max-width: 750px) {
    .nav {
      display: none;
    }
  }
}
```

```
/* css */
@media screen and (max-width: 750px) {
  .box .nav {
    display: none;
  }
}
```
