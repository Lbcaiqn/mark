```
书写规范：一行一属性，小写，注意空格。
CSS分为：
行内样式表：直接在标签中添加属性style=”属性: 值; 属性: 值;……….”
内部样式表：一般在head标签中书写<style></style>
外部样式表：单独一个.css文件，在head标签中使用：<link rel="stylesheet" href="路径">
选择器 {
  属性: 值;
}
```

# 一、 属性

1 书写顺序：

display-定位-浮动-盒子（宽高-外内边距-边框）-背景复合写法-字体复合写法-文本-CSS3
2 字体类：
font: font-style font-weight font-size/line-height font-family;
分别是倾斜(值为italic  normal)，粗细(值为bold或700   normal或400)，大小（单位px），
行高，字体集(“Microsoft Yahei”)，注意加上line-height时/是要写的
书写复合属性时。必须按照顺序，且font-size和font-family必须有
3 文本类：

| color           | 字体颜色     | 颜色英文，#16，rgb(x,y,z)                                        |
| --------------- | -------- | ---------------------------------------------------------- |
| text-indent     | 首行缩进     | 2em                                                        |
| text-align      | 文本水平对齐方式 | left，center，right                                          |
| line-height     | 行高       | 行高 = 字体大小+上间距+下间距，由此可以设置行间距。（行高=盒子高度达到垂直居中。没有px时表示字体大小的倍数） |
| text-decoration | 文本装饰     | none，underline，orderline，line-through（a标签一般设置为none）        |
| list-style      | 列表默认s样式  | none（去除列表默认样式）                                             |

直接给父元素设置文字，文本属性，利用继承性方便给包含的子元素设置效果，但是注意text-align只影响包含的行内元素和行内块元素。

4 背景
复合写法：background: color url() no-repeat fixed x y;   没有顺序之分

| background-color      | 背景颜色 | 颜色英文  #16  rgb()                                                                                                                                        |
|:--------------------- | ---- | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| background-image      | 背景图片 | url(路径)   注意没有引号。默认图片重复平铺，背景图片比img标签方便控制位置,小图片放需要的盒子，大图片（如网站背景）设置body的css。                                                                              |
| background-repeat     | 平铺   | repeat \| no-repeat \| repeat-x \| repeat-y<br/>分别是全平铺，不平铺，x轴平铺，y轴平铺                                                                                    |
| background-position   | 位置   | x y;   值可以是百分制或者px的数值，也可以是范围名词<方位名词：top,botton,center,left,right,center<br/>都是方位名词则顺序随意；若只写一个另一个默认为center<br/>都是数值时或方位数值混合时，xy为距离左上的距离/方位，只写一个另一个默认垂直居中 |
| background-attachment | 滚动固定 | scroll \| fixed 分别是滚动和固定                                                                                                                                |

# 二、 选择器

1 基础选择器

| 标签选择器  | tagname {}                                                        |
| ------ | ----------------------------------------------------------------- |
| 类选择器   | .classname {}  标签需要class属性，多类名：一个标签可以有多个类名，用空格隔开  class=”类名a 类名b” |
| id选择器  | #id {}   需要标签具有id属性  id唯一（有多个相同id的标签则最前的使用），class不唯一。             |
| 通配符选择器 | 选择所有标签，通常用来出书画                                                    |

2 复合选择到期

复合选择器，基础选择器的复合
（1）后代选择器：父 子 …  {}
（2）子选择器： 父>子 {}        只选择最近一级的子
（3）并集选择器：a,b {}        同时选择
（4）伪类选择器：
1)、链接伪类选择器：a标签有默认样式，要修改a就要单独选择出a
a:link {}   a:visiter {}    a:hover {}    a:active {}
分别是未访问，已访问，鼠标经过，活动（如点击）
书写顺序：a的样式，lvha
2)、:focus伪类选择器：input:focus {}   选出光标当前点击的表单
3)、基础选择器:hover 设置鼠标经过时的样式

# 三、元素显示模式

1 分类：
（1）块元素：div ，h1…h6，p，ol，ul，li，独占一行，可以设置宽高（宽度默认与父相同），内外边距，里面可以放块元素和行内元素（但文字类块元素不能再放块元素）
（2）行内元素：span，a，格式化标签，一行多个，无法设置宽高（默认宽度为内容宽度），里面只能有文本或行内元素。
PS：a里不能放a，a能放块元素。（a通常转换为块元素）
（3）行内块元素：img，input，td，一行多个（空格隔开），可以设置宽高（宽度默认为内容宽度），内外边距，

2 转换：
display: blpck;  display: inline;   display: inline-blpck;  分别转换成块，行内，行内块。

3 元素显示与隐藏：
隐藏分为三种：不删除且保留位置的隐藏，不删除且不保留位置的隐藏，直接删除的隐藏（原位置自然就空出了）。
display: block; 显示元素。
display: none; 隐藏元素（不是删除），并不再占有原位置。
visibility: value; value值为inherit,visible,hidden,collapse，分别是：
继承（默认，继承上一个父亲的可见性），显示，隐藏（保留原位置），隐藏表格行或列。
overflow: value; value为visible,hidden,auto,scroll 设置盒子装不下的溢出内容的可见性。
分别是显示（默认）,隐藏，需要时自动增加滚动条，强制增加滚动条。
overflow: hidden; 还可以清除浮动和解决包含关系盒子的垂直margin的塌陷。

# 四、CSS三大特性

1 层叠性

SS属性冲突时，最后面的生效。
2 继承性

字标签会继承父标签的CSS
特殊1：行高的继承，行高为倍数时，看最近的父的字体大小（包括自己）。
特殊2：a标签有自带样式，权重比继承的样式高，所以相当于不能继承。
3 优先级

与层叠性一样，优先级只影响冲突的属性。
行内样式表>内部样式表>外部样式表
若选择器相同，则按照层叠性；
若不同，根据选择器的权重。
权重：从左到右对比。 
继承或者*              0000
标签/伪元素              0001
类/:伪类/[]属性         0010
ID选择器              0100
行内样式              1000
!important              无穷大（在CSS的属性之后分号之前加上!important）
复合选择器的权重叠加计算：
复合的各个选择器按照十进制求和；
没有进位，如10个标签选择器相加得到00010；
从左至右对比大小；
XX伪类选择器=标签+:伪类；

# 五、页面布局

传统PC端网页布局的三种方式：普通流(也叫标准流/文档流)，浮动，定位。
1 盒子模型：
盒子属性：margin,padding,width,height,border
盒子大小 = width/height+padding+border

1.1 margin padding
margin，padding，border都有top，bottom，left，right
margin，padding的值为1,2,3,4个时分别代表：全部，上下-左右，上-左右-下，上-右-下-左。行内元素最多只设置左右外边距。

1.1.1 margin: 0 auto;
块元素设置了width的前提下，左右外边距设置为auto可以实现水平居中（行内元素和行内块元素通过text-align: center;实现）

1.1.2 margin: 负数px;
margin负值的应用：当紧挨着的盒子设置边框时，若想合并边框，可以给margin-方位设置为边框大小的负值。但是当设置时hover显示边框时，由于合并边框原理是压住另一个盒子，此时边框就会显示不全。解决：全部盒子设置相对定位，而hover中设置z-index

margin，padding的特殊点：
1.1.3 未指定width时，设置padding不会加大盒子宽度。
1.2 border属性的值

border: border-width | border-style | border-color  没有顺序之分
最常用的样式：实线solid，虚线dathed，点线dotted
border-collapse: collapse; 用来合并单元格之间的多余的边框。

2 浮动：
标准流的所有标签按照默认位置排列，而设置浮动后，将能根据需求排列(如一行放多个块元素)。 
浮动特性：
1)、元素浮动后脱离标准流（脱标，元素浮起来了），不再保留原来位置。
2)、设置浮动的元素，按左或按右在一行无缝隙排列，顶部对着最近的上一个标准流盒子所在行的底部（重点，简单理解为浮动失去原位置只影响下面），若没有则顶部对齐父元素顶部，若一行放不下则另起一行。
3)、浮动元素具有行内块元素特点，可以设置宽高，未设置宽度的默认宽度为文本大小。
4)、设置浮动会脱标，但是不会压住移动上来的文字和图片，可以利用其制作文字环绕图片。
注意，若父元素的一个子元素设置了浮动，则其他子元素也应全部设置为浮动。

设置浮动：
float: value; value为left或right，元素获得浮动。
清除浮动：清除浮动元素造成的影响，如为了通用性，标准流父元素不设置height，但由于子元素全浮动，height就会为0，影响后面的标准流元素，此时就需要清除浮动。
clear: value;  值为left,right,both，分别为清除左浮，右浮，左右的影响。采用闭合浮动。
1)额外标签法(隔墙法)：最后一个子元素的后面添加一个空的块元素（如div，br等），此空盒子样式设置为 clear: both;后，父height不会为0，也不会影响后面。
2)给父元素添加overflow: value; value为hidden,auto,scroll,缺点是无法显示溢出部分。
3):after伪元素法（额外标签法的升级）：在父元素后面添加伪元素，一般给父元素一个类名clearfix。
基础选择器父元素:after {
    content: “”;
    display: block;
    height: 0;
    clear: both;
    visibility: hidden;
}
基础选择器父元素 {
    *zoom: 1;     //兼容IE6,7
}
4)、双伪元素法：3)的升级，父元素前后都添加伪元素
基础选择器父元素:before,
基础选择器父元素:after {
    content: “”;
    display: table;
}
基础选择器父元素:after {
    clear: both;
}
基础选择器父元素 {
    *zoom: 1;     //兼容IE6,7
}

3 定位：
脱标的定位后，width不再自动100%

将盒子定到某一位置不动，由定位模式和边偏移两部分组成。
1)、定位模式：
position: value;  value值为static,relative,absolute,fixed,sticky
分别为静态定位，相对定位，绝对定位，固定定位。黏性定位
静态定位：即无定位；为标准流。
相对定位：边偏移根据它的原本位置，会浮起来但是会保留原位置（即没有脱标）。
绝对定位：边偏移根据它的最近的有绝对/相对/固定定位的祖先元素位置，直到以浏览器为父元素（若没有任何祖先，则直接以浏览器边缘为准），绝对定位后浮起来不再占有原位置（脱标）。
子绝父相：若子元素为绝对定位，则父元素最好要相对定位（为了保留原位置），典型应用如轮播图将若干图片绝对定位到同一位置。
固定定位：以浏览器可视窗口为父的绝对定位，浏览器动我不动，边偏移以浏览器边缘为准，会脱标，固定定位到版心右边方法（left: 50%; margin-left: 版心宽度一半）
黏性定位：相当于相对定位和固定定位的混合，保留原位置（不脱标），边偏移是浏览器下滑一定程度后的边缘，当浏览器下滑到与边偏移一致时，固定不动 （之前会动）
特性：
1)、定位的叠放次序：z-index: value; 值为不带单位的正负整数或0，越大盒子越上面。若不设置则为auto，后来居上。
2)、设置定位后，不能再用margrin设置水平居中，可以采用：
水平居中：left: 50%;   margin-left: -盒子宽;
垂直居中：top:50%;     margin-top:-盒子高;
3)、与浮动一样，设置定位后具有行内块元素特点，可以设置宽高，未设置宽度的默认宽度为文本大小。
4)、与浮动不同，绝对/固定定位脱标后会完全压住文字和图片。

2)、边偏移：
有四个属性top,bottom,left,right，分别是距离上下左右边的距离。单位为px。

# 六、CSS其他使用

1 精灵图：
将大量小图片合到一张大图片，一次请求就能获取大量图片，能减少对服务器的请求，减少服务器压力。
精灵图中小图片的使用：
选择器 {
    width:目标图片宽;
    heighr:目标图片高;
    background: url(精灵图路径) no-repeat –xpx –ypx;    //x y为目标图片坐标
}

2 字体图标（看似是图标，实际是文字，可以设置字体文本类样式）：
图标库：https://icomoon.io/            https://www.iconfont.cn/
引入：

3 CSS三角，梯形，圆形
width: 0;
height: 0;
border-top: 100px solid red;
border-bottom: 100px solid blue;
border-left: 100px solid gray;
border-right: 100px solid black;
通过将其中一个如bottom的px设置为0，再设置其他方位的px，就可以获得任意大小的直角三角形。与矩形结合能得到梯形。
通过以下代码可以获得等腰三角形
选择器 {
width: 0;
height: 0;                                //宽高必须为0
       border: 50px solid transparent;        //四条边框先设置全透明，px控制大小
       border-left-color: black;                //选择一个三角
}
还可以&gt和&lt
圆形先准备正方形盒子，然后border-radius: 高一半;非正方形也会变成左右边圆弧。

4 用户界面样式：
即用户操作的样式（如光标的形状变化）
1)、鼠标样式：
cursor: value; value为default,pointer,move,text,not-allowed
分别是小白光标(默认)，小手，移动(十字架)，文本(竖线)，禁止
2)、取消表单默认蓝色轮廓线：outline: none或0;
3)、防止文本域textarea被拉大：resize: none;

5 vertical-align: value; value为baseline,top,middle,bottom
分别是基线，顶部，中线，底部对齐
用来设置图片，文字，表单的垂直对齐方式（只适用于行内元素，行内块元素）
行内块元素img默认基线对齐，下面会有空隙，可以设置vertical-align的顶中底，也可以转换成块元素解决.

6 溢出文字省略号表示：
单行文本：先white-space: nowrao; 强制转为一行显示，overflow: hidden; 隐层溢出，最后text-overflow: ellipsis;显示省略号。
多汗文本（有较大的兼容性问题）：

```
overflow: hidden;  
text-overflow: ellipsis;
display: -webkit-box; //弹性伸缩盒子
-webkit-line-clamp: 2; //第几行省略号
-webkit-box-orient: vertical; //垂直居中
```

7 图片放置方案

两个img上下之间有空隙，display;block; 解决

```
<div class="img-box"><img /></div>

//1.盒子宽高都不固定，或宽高其中一个固定，一个不固定（若固定宽，img的width:100%，若固定高，img的height:100%），不固定的被图片撑开
//2.盒子宽高都固定，图片多出的裁剪
.img-box {
  display: flex;
  justify-cntent: center;
  align-items: center;
  overflow: hidden;
}
.img-box img {
  width: 100%;  /*或者height: 100%;*/
}
//3.盒子宽高都固定，图片多出的尽量不裁剪
.img-box {
  display: flex;
  justify-cntent: center;
  align-items: center;
  overflow: hidden;
}
/*若 宽>高 */
.img-box img {
  width: 100%;
}
/*若 高>宽 */
.img-box img {
  height: 100%;
}
```



# 七、CSS3新特性

这些新特性都有兼容性问题。移动端兼容性问题比较少。

1 新属性

1.1 半透明效果：

```
background: rgba(r,g,b,a)，a为透明度（0-1），0全透明，1不透明
```

1.2 圆角边框：

```
border-radius: 
值为像素或百分比（width的%）的半径，可以跟1-4个值:
2个时为对角
4个时分别为左上顺时针到左下
也可以如border-top-left-radius设置单独圆角。
```

1.3 盒子阴影：

```
box-shadow: h-shadow(必写) v-shadow(必写) | blur | spread | color | inset;
分别是
水平位置(px)
垂直位置(px)
模糊距离(px,0(实)-1(虚))
尺寸(px)
颜色(一般用rgba设置半透明)
内或外阴影(默认外，可设inset内)
```

1.4 文本阴影

```
text-shadow: h-shadow(必写) v-shadow(必写) | blur | color; 使用与盒子阴影一样。
```

1.5 滤镜

```
filter: 函数();
最常用的模糊处理：blur( xpx )，x越大越模糊，0为不模糊。
```

1.6 宽度自动计算，如：width: calc(100%-80px); 可以永远比父少80px，+-*/均可

1.7 过渡：

```
transition: cssname time line delay
分别是过渡的属性名，花费时间(单位s必须写) 运动曲线(默认ease，可省) 延时(默认0s，可省)
如transition: height 2s ease 1s; 1s后开始，在2s内完成height属性以ease曲线的过渡。

多条属性必须这样写：
transition: height 2s ease 1s,width 2s ease 1s; ease和延时可省。

若全部属性都需要，则可以：
transition: all 2s ease 1s;
```

1.8 transiform平面转换

```
transform: none; 没有任何转换效果
(1) translate
transform: translate(x,y); 移动盒子，可以只写一个x，xy值可以是数值，px，百分比(百分之宽高)，正/负往右下/左上
transform: translate(x,y) 2d
transform: translate3d(x,y,z) 3d
transform: translateX(x) 
transform: translateY(y) 
transform: translateZ(z) 3d
定位左上都50%后，transform: translate(-50%,-50%); 即可水平垂直居中。
与margin区别：margin会影响其它盒子，而transilate不会

(2) scale
transform: scale(a); 缩放，a值>1/<1，放大/缩小，负数当成整数
transform: scale(a); 2d，xy同时缩放a倍
transform: scale(x,y); 2d，x，y各自缩放x倍，y倍
transform: scale3d(x,y,z); 3d,xyz各自缩放
transform: scaleX(x) transform: scaleY(y) transform: scaleZ(z) 3D，单独缩放xyz

(3) rotate
transform: rotate(adeg) 顺时针旋转a度
transform: rotate(adeg) 2d
transform: rotate3d(x,y,z,deg) 3d
transform: rotateX(adeg) transform: rotateX(adeg) transform: rotateX(adeg) 3d
transform-orgin: left bottom: 设置需旋转点，默认center

(4) skew
transform: skew(xdeg,ydeg); 2d，倾斜
transform: skewX(xdeg) transform: skewY(ydeg) 2d  

(5) 多重转换
transform: translate() rotate()
旋转会改变移动的x轴方向，所以一般移动在旋转之前才能水平移动
```

1.9 渐变背景色

```
background-image: linear-gradient(to right,red,rgba(0,255,0,0.8),blue)
第一个参数可以省略，默认为 to bottom
颜色参数可以有任意个，可以使用rgba()和transparent
```

2 新选择器

以下示例的E表示选择器

2.1 属性选择器：

```
E[属性] {} 选出写有该属性的标签。
E[属性=”value”] {} 选出写有该属性,且值为value的标签。

^*$
E[属性^=”value”] {} 选出写有该属性,且值开头为value的标签。
E[属性*=”value”] {} 选出写有该属性,且值含有value的标签。
E[属性$=”value”] {} 选出写有该属性,且值结尾value的标签。

权重：[]=0010, =0010+E权重
```

2 结构伪类选择器：
根据文档结构选择，常用于选择父元素下的子元素，

注意：

1. 没有第0个孩子，孩子从第一个开始。

2. E最后跟父或子都可以，但最好是跟子元素。

```
（1）先给所有孩子标好序，再找第几个，再看与:前面是否匹配  
E:first-child {} 选择父的第一个孩子
E:last-child {} 选择父的最后一个孩子
E:nth-child(n) {} 选择父的第n个孩子

（2）只在:前面指定的元素中标好序，再找第几个。
E:first-of-type {} 选择父的第一个孩子
E:last-of-type {} 选择父的最后一个孩子
E:nth-of-type(n) {} 选择父的第n个孩子,n从1开始

（3）n可以是数字，关键字，公式
数字：整数
关键字：even odd，选出所有偶数或奇数
公式：如n，2n，3n+2，n从0开始计算。
2n偶数，2n+1奇数，n+5第五个开始，-n+5前五个

（4）权重：伪类0010+E权重
```

3 伪元素选择器：
3.1 生成伪元素

用CSS创建一个模拟的新标签，就叫伪元素，在文档中找不到，就可以不用新增HTML标签，简化HTML。应用如侧边栏三角，遮层。清除浮动，配合字体图标。

```
E::before {} 在E里面的最前面(有文字也跳过文字)生成，作为第一个孩子
E::after {} 在E里面的最后面(有文字也跳过文字)生成，作为最后一个孩子
before,after都是作为E的孩子，它们必须要有content属性，值可以为空。
伪元素默认是行内元素。
```

伪元素一般配合绝对定位

3.2 制作遮层鼠标经过时 E:hover::after
3.3 清除浮动原理：在父盒子最后面生成一个伪元素卡住，若再加上before更严谨的闭合浮动。

3 新盒子模型

```
//默认的盒子大小计算方式，加不加都一样，padding，border会撑大盒子，大小=w/h+padding+border
box-sizing: content-box;
//CSS3的盒子模型，盒子大小始终是width，padding，border不会撑大盒子，大小=width，但是注意当padding+border>w/h，就会撑大盒子。
box-sizing: border-box;  
```

4 动画

```
//显示时从左往右显示，消失时从右往左消失的动画
//类名任取,有该类名得到动画效果
.come {
  animation: hhh 1s;
}
.go {
  //reverse翻转，所以只定义来就可以定义走
  animation: hhh 1s reverse;
}
//配置动画，也在style里
@keyframes hhh{
  //起点与终点
  from{
    //宽度变为0
    transform: translateX(-100%)
  },
  to{
    //宽度不变
    transform: translateX(0px)
  }
}
```

# 八、less

1 less

less（动态样式语言），一种CSS预处理语言。
使用类似css的语法，为css提供了动态语言的特性，如变量，函数，运算，继承等，方便css的管理与维护
引入，三种方法：

```
(1) CDN
<link rel="stylesheet/less" href="css/1.less">
<script src="//cdnjs.cloudflare.com/ajax/libs/less.js/3.10.0-beta/less.min.js"></script>
（2）下载安装koala编译器，编译less成css，再引入css
（3）node
npm install –g less@latest  全局安装最新版本
```

lessc 查看电脑是否有less
lessc xxx.less xxx.css 在xxx.less文件目录下执行，将less编译成css

基本语法：

```
//导入其他less文件
@import “xxx.less”  //后缀名可以省略
//注释，用//注释编译后不保留，/**/编译后保留
//000
/*123*/

//变量定义与使用
@hhh:200px;
.hhh {
  font-size: @hhh;
}
//混合
.minin {
  .hhh();
}
//函数
.xxx {}  等价于  .xxx(){}  都用.xxx()调用
可以带默认参数 .xxx(@aaa:…) {}  没有实参时使用默认值
@arguments 与 js的arguments类似
//嵌套
 //1 相当于后代选择器
.father {
  color: red;
  .child {
    font-size: 500px;
  }
}
 //2
.box1 { //.box:hover
  &:hover {
    background-color: red;
  }
} 
.ul li { //ul li.box
  &.box2 {
    color: red;
  }
}

//规则嵌套，编译后冒泡
.box {
  @media (...){样式} 编译 @media (...){.box {样式}}）
  @media (...){      编译 @media (...) and (...) {.box {}}
    @media (...) {}
  }
}

//运算，运算结果的单位是表达式中，最早出现的单位
@cm: 1+5cm+10mm;   //=7cm 单位类型相同
@pp: 1+3px-2cm;    //2px  单位类型不同，忽略后面的cm
@pr1: 5%;
@pr2: @pr1*2;       //=10% 表达式可以使用变量

//函数,less内置了很多函数，实参可传入变量
.box {
  width: percentage(0.5);
} 
//其他函数 
//saturate(颜色,百分比) 加深或淡化颜色
//lighten(颜色，百分比) 颜色亮度
//spin(颜色,百分比)     颜色旋转角度
```

2 sass

与less语法基本相同，但是变量用$定义
less基于JavaScript，在客户端处理
sass基于Ruby，在服务端处理

# 
