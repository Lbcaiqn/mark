编写规范：一行一属性，小写，注意空格。

```
选择器 {
  属性: 值;
}
```

css分为：
行内样式表：直接在标签中添加属性style=”属性: 值; 属性: 值;……….”
内部样式表：一般在head标签中书写<style></style>
外部样式表：单独一个.css文件，在head标签中使用：<link rel="stylesheet" href="路径">

# 一、 属性

## 1 编写顺序规范：

display

定位

浮动

盒子（宽高-外内边距-边框）

背景复合写法-字体复合写法

文本

CSS3

## 2 字体类：

| font-style  | 倾斜，如italic，normal       |
| ----------- | ----------------------- |
| font-weight | 粗细，如bold或700 normal或400 |
| font-size   | 字体大小                    |
| line-height | 行高，行高=盒子高可实现文本垂直居中      |
| font-family | 字体集，如“Microsoft Yahei”  |

复合写法：

font: font-style font-weight font-size/line-height font-family;
注意加上line-height时/是要写的
书写复合属性时。必须按照顺序，且font-size和font-family必须有

示例：font: normal normal 15px/20px “Microsoft Yahei”;

## 3 文本类：

| color           | 字体颜色     | 颜色英文，#16，rgb(x,y,z)                                        |
| --------------- | -------- | ---------------------------------------------------------- |
| text-indent     | 首行缩进     | 2em                                                        |
| text-align      | 文本水平对齐方式 | left，center，right                                          |
| line-height     | 行高       | 行高 = 字体大小+上间距+下间距，由此可以设置行间距。（行高=盒子高度达到垂直居中。没有px时表示字体大小的倍数） |
| text-decoration | 文本装饰     | none，underline，orderline，line-through（a标签一般设置为none）        |
| list-style      | 列表默认s样式  | none（去除列表默认样式）                                             |

直接给父元素设置文字，文本属性，利用继承性方便给包含的子元素设置效果，但是注意text-align只影响包含的行内元素和行内块元素。

## 4 背景

| background-color      | 背景颜色 | 颜色英文  #16  rgb()                                                                                                                                        |
|:--------------------- | ---- | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| background-image      | 背景图片 | url(路径)   注意没有引号。默认图片重复平铺，背景图片比img标签方便控制位置,小图片放需要的盒子，大图片（如网站背景）设置body的css。                                                                              |
| background-repeat     | 平铺   | repeat \| no-repeat \| repeat-x \| repeat-y<br/>分别是全平铺，不平铺，x轴平铺，y轴平铺                                                                                    |
| background-position   | 位置   | x y;   值可以是百分制或者px的数值，也可以是范围名词<方位名词：top,botton,center,left,right,center<br/>都是方位名词则顺序随意；若只写一个另一个默认为center<br/>都是数值时或方位数值混合时，xy为距离左上的距离/方位，只写一个另一个默认垂直居中 |
| background-attachment | 滚动固定 | scroll \| fixed 分别是滚动和固定                                                                                                                                |

复合写法：

background: color url() no-repeat fixed x y; 没有顺序之分

# 二、 选择器

## 1 基础选择器

| 标签选择器  | tagname {}                                                        |
| ------ | ----------------------------------------------------------------- |
| 类选择器   | .classname {}  标签需要class属性，多类名：一个标签可以有多个类名，用空格隔开  class=”类名a 类名b” |
| id选择器  | #id {}   需要标签具有id属性  id唯一（有多个相同id的标签则最前的使用），class不唯一。             |
| 通配符选择器 | 选择所有标签，通常用来出书画                                                    |

## 2 复合选择到期

复合选择器，基础选择器的复合
（1）后代选择器：父 子 …  {}
（2）子选择器： 父>子 {}        只选择最近一级的子
（3）并集选择器：a,b {}        同时选择
（4）伪类选择器：
①、链接伪类选择器：a标签有默认样式，要修改a就要单独选择出a
a:link {}   a:visiter {}    a:hover {}    a:active {}
分别是未访问，已访问，鼠标经过，活动（如点击）
书写顺序：a的样式，lvha
②、:focus伪类选择器：input:focus {}   选出光标当前点击的表单
③、基础选择器:hover 设置鼠标经过时的样式

# 三、元素显示模式

## 1 分类：

### 1.1 块元素

div ，h1…h6，p，ol，ul，li

独占一行，可以设置宽高（宽度默认与父相同），内外边距

里面可以放块元素和行内元素（但文字类块元素不能再放块元素）

### 1.2 行内元素

span，a，格式化标签

一行多个，无法设置宽高（默认宽度为内容宽度）

里面只能有文本或行内元素。

PS：a里不能放a，a能放块元素。（a通常转换为块元素）

### 1.3 行内块元素

img，input，td

一行多个（空格隔开），可以设置宽高（宽度默认为内容宽度），内外边距，

## 2 转换：

display: blpck;  display: inline;   display: inline-blpck;  分别转换成块，行内，行内块。

## 3 元素显示与隐藏：

display: block; 显示元素。

隐藏分为三种：

* 不删除且保留位置的隐藏

* 不删除且不保留位置的隐藏 ，display: none;

* 直接删除的隐藏（原位置自然就空出了）

visibility: value; inherit | visible | hidden | collapse   分别是；
继承（默认，继承上一个父亲的可见性），显示，隐藏（保留原位置），隐藏表格行或列。
设置盒子装不下的溢出内容的可见性。

overflow: visible | hidden | auto,scroll;

分别是显示（默认）,隐藏，需要时自动增加滚动条，强制增加滚动条。

overflow: hidden; 还可以清除浮动和解决包含关系盒子的垂直margin的塌陷。

# 四、CSS三大特性

## 1 层叠性

SS属性冲突时，最后面的生效。

## 2 继承性

字标签会继承父标签的CSS

特殊情况：

* 行高的继承，行高为倍数时，看最近的父的字体大小（包括自己）。

* a标签有自带样式，权重比继承的样式高，所以相当于不能继承。

## 3 优先级

与层叠性一样，优先级只影响冲突的属性。

行内样式表>内部样式表>外部样式表

若选择器相同，则按照层叠性；

若不同，根据选择器的权重。

各选择器权重：

权重的大小从左到右对比

| 继承和*       | 0000        |
| ---------- | ----------- |
| 标签/伪元素     | 0001        |
| 类/:伪类/[]属性 | 0010        |
| id         | 0100        |
| 行内样式       | 1000        |
| !important | 10000或者说无穷大 |

!important修改权重：

用于修改某选择器某属性的权重，CSS的属性之后分号之前加上!important

```
.box {
  color: red !important;
}
```

!important的几个注意点：

* 应当尽量避免使用它，特别是自定义的css插件，要用也尽量用在全局样式

* 若有有多个地方同个样式使用了它，则权重大的生效

* 子元素不受影响

复合选择器的权重叠加计算：

1. 复合的各个选择器按照十进制求和；

2. 没有进位，如10个标签选择器相加得到00010；

3. 从左至右对比大小；

4. XX伪类选择器=标签+:伪类；

# 五、页面布局

传统PC端网页布局的三种方式：普通流(也叫标准流/文档流)，浮动，定位。

## 1 盒子模型：

盒子属性：

margin  padding  width  height  border

盒子大小 = width/height+2*padding+2*border

### 1.1 margin padding

margin，padding，border都有top，bottom，left，right属性，如margin-top

也可以合成一个属性写，如margin: 10px 10px 10px 10px;

合成写法的值数量不同的效果：

| margin: 10px;                | 全部      |
| ---------------------------- | ------- |
| margin: 10px 10px;           | 上下-左右   |
| margin: 10px 10px 10px;      | 上-左右-下  |
| margin: 10px 10px 10px 10px; | 上-右-下-左 |

特殊用法：

1. margin: 0 auto;
   块元素设置了width的前提下，左右外边距设置为auto可以实现水平居中（行内元素和行内块元素通过text-align: center;实现）

2. margin: 负数px;
   margin负值的应用：当紧挨着的盒子设置边框时，若想合并边框，可以给margin-方位设置为边框大小的负值。但是当设置时hover显示边框时，由于合并边框原理是压住另一个盒子，此时边框就会显示不全。解决：全部盒子设置相对定位，而hover中设置z-index

3. 未指定width时，设置padding不会加大盒子宽度。

### 1.2 border属性的值

行内元素最多只设置左右外边距

border: border-width | border-style | border-color  没有顺序之分

示例；border: 1px solid #000;
最常用的样式：实线solid，虚线dathed，点线dotted
border-collapse: collapse; 用来合并单元格之间的多余的边框。

## 2 浮动布局：

标准流的所有标签按照默认位置排列，而设置浮动后，将能根据需求排列（如一行放多个元素）。 

（1）浮动特性：

* *元素浮动后脱离标准流（脱标，元素浮起来了），不再保留原来位置。

* 设置浮动的元素，按左或按右在一行无缝隙排列，顶部对着最近的上一个标准流盒子所在行的底部（重点，简单理解为浮动失去原位置只影响下面），若没有则顶部对齐父元素顶部，若一行放不下则另起一行。

* 浮动元素具有行内块元素特点，可以设置宽高，未设置宽度的默认宽度为文本大小。

* 设置浮动会脱标，但是不会压住移动上来的文字和图片，可以利用其制作文字环绕图片。

* 若父元素的一个子元素设置了浮动，则其他子元素也应全部设置为浮动。

（2）设置浮动：

子元素：

float: value; left | right;

（3）清除浮动：

清除浮动元素造成的影响，如为了通用性，标准流父元素不设置height，但由于子元素全浮动，height就会为0，影响后面的标准流元素，此时就需要清除浮动。

清除浮动都是在写父元素的样式：

1. clear: value;  left | right | both，分别为清除左浮，右浮，左右的影响。采用闭合浮动。

2. 额外标签法(隔墙法)：html中最后一个子元素的后面添加一个空的块元素（如div，br等），此空盒子样式设置为 clear: both;后，父height不会为0，也不会影响后面。

3. 给父元素添加overflow: hidden | auto,scroll,缺点是无法显示溢出部分。

4. :after伪元素法（额外标签法的升级）：在父元素后面添加伪元素，一般给父元素一个类名clearfix。
   
   ```
   父元素:after {
    content: “”;
    display: block;
    height: 0;
    clear: both;
    visibility: hidden;
   }
   父元素 {
    *zoom: 1; /*兼容IE6,7*/
   }
   ```

5. 双伪元素法：3)的升级，父元素前后都添加伪元素
   
   ```
   父元素:before,
   基础选择器父元素:after {
    content: “”;
    display: table;
   }
   父元素:after {
    clear: both;
   }
   父元素 {
    *zoom: 1; /*兼容IE6,7*/
   }
   ```

## 3 定位：

将盒子定到某一位置不动，由定位模式和边偏移两部分组成。

### 3.1 定位模式

position: static | relative | absolute | fixed | sticky;

分别为静态定位，相对定位，绝对定位，固定定位。黏性定位

（1）静态定位：即无定位；为标准流。

（2）相对定位：边偏移根据它的原本位置，会浮起来但是会保留原位置（即没有脱标）

（3）绝对定位：边偏移根据它的最近的有绝对/相对/固定定位的祖先元素位置，直到以浏览器为父元素（若没有任何祖先，则直接以浏览器边缘为准），绝对定位后浮起来不再占有原位置（脱标）。
子绝父相：若子元素为绝对定位，则父元素最好要相对定位（为了保留原位置），典型应用如轮播图将若干图片绝对定位到同一位置。

（4）固定定位：以浏览器可视窗口为父的绝对定位，浏览器动我不动，边偏移以浏览器边缘为准，会脱标，固定定位到版心右边方法（left: 50%; margin-left: 版心宽度一半）

（5）黏性定位：相当于相对定位和固定定位的混合，保留原位置（不脱标），边偏移是浏览器下滑一定程度后的边缘，当浏览器下滑到与边偏移一致时，固定不动 （之前会动）

### 3.2 定位特性：

1. 定位的叠放次序：z-index: value; 值为不带单位的正负整数或0，越大盒子越上面。若不设置则为auto，后来居上。

2. 设置定位后，不能再用margrin设置水平居中，可以采用：
   水平居中：left: 50%;   margin-left: -盒子宽;
   垂直居中：top:50%;     margin-top:-盒子高;

3. 与浮动一样，设置定位后具有行内块元素特点，可以设置宽高，未设置宽度的默认宽度为文本大小。

4. 与浮动不同，绝对/固定定位脱标后会完全压住文字和图片。

5. 脱标的定位后，width不再自动100%，需要自行设置宽高。

### 3.3 边偏移：

有四个属性：

top  bottom  left  right，分别是距离上下左右边的距离

# 六、BFC

形成独立的渲染区域，形成一个隔离的独立的容器，使得容器内每个子元素的布局都不会影响外界的布局（也不会影响父元素本身）。

形成BFC的条件（符合任一条件就形成BFC）：

1. 根元素以及

2. float值不为默认的none

3. position值不为relative

4. display值不为block 如：flex，inline-flex，inline-block，grid，inline-grid，table-xxx等等

5. overflow值不为默认的visible的块级元素

6. contain值为如下：layout，content，paint

7. 多列元素，即column-count或column-width值不为默认的auto碎

常见用法：

1. 清除浮动：子元素设置了浮动，父元素没有设置高度，此时父元素的高度就会塌陷。此时给父元素overflow: hidden; 使得整个父元素变成BFC元素，使得它的子元素浮动后不会影响到外界，高度不变，达到清除浮动的效果。

2. 浮动元素会覆盖未浮动元素：只需要将被覆盖的元素设置为BFC，如overflow:hidden，就不会覆盖了。

3. 解决外边距合并问题：若两个上下/左右排列的div分别设置了margin-top，margin-bottom，则他们之间的间距会变成top，bottom t中值较大的那一个。解决：将两个div分别放入两个BFC父元素中（注意左右排列的margin-left和margin-right不胡已出现这种情况）

4. margin塌陷问题：子元素设置margin-top后，子元素不生效，反而是父元素生效了，此时父元素的margin-top=父+子。解决：给父元素设置BFC就能解决。此外，给父元素一个参照，给父元素设置上边框或上内边距也能解决。

# 七、CSS其他使用

## 1 精灵图：

将大量小图片合到一张大图片，一次请求就能获取大量图片，能减少对服务器的请求，减少服务器压力。
精灵图中小图片的使用：

```
选择器 {
 width:目标图片宽;
 heighr:目标图片高;
 background: url(精灵图路径) no-repeat –xpx –ypx; //x y为目标图片坐标
}
```

## 2 字体图标

看似是图标，实际是文字，可以设置字体文本类样式

图标库：https://icomoon.io/            https://www.iconfont.cn/

引入...

## 3 CSS三角，梯形，圆形

```
选择器 {
  width: 0;
  height: 0;
  border-top: 100px solid red;
  border-bottom: 100px solid blue;
  border-left: 100px solid gray;
  border-right: 100px solid black;
}
```

通过将其中一个如bottom的px设置为0，再设置其他方位的px，就可以获得任意大小的直角三角形。与矩形结合能得到梯形。

通过以下代码可以获得等腰三角形

```
选择器 {
width: 0;
height: 0; //宽高必须为0
 border: 50px solid transparent; /*四条边框先设置全透明，px控制大小*/
 border-left-color: black;       /*选择一个三角*/
}
```

还可以&gt和&lt

圆形先准备正方形盒子，然后border-radius: 高一半;非正方形也会变成左右边圆弧。

## 4 用户界面样式（鼠标指针等）：

即用户操作的样式（如光标的形状变化）

（1）鼠标样式：

cursor: value; value为default,pointer,move,text,not-allowed
分别是小白光标(默认)，小手，移动(十字架)，文本(竖线)，禁止

（2）取消表单默认蓝色轮廓线：outline: none或0;

（3）防止文本域textarea被拉大：resize: none;

## 5 vertical-align

vertical-align: baseline | top | middle | bottom;
分别是基线，顶部，中线，底部对齐

用来设置图片，文字，表单的垂直对齐方式（只适用于行内元素，行内块元素）

行内块元素img默认基线对齐，下面会有空隙：

可以设置vertical-align的顶中底，也可以转换成块元素display: block; 解决

## 6 溢出文字省略号表示：

单行文本：

```
选择器 {
  white-space: nowrap;      /*强制转为一行*/
  overflow: hidden;         /*隐藏溢出文字*/
  text-overflow: ellipsis; /*显示省略号*/
}
```

多汗文本（有较大的兼容性问题）：

```
overflow: hidden;  
text-overflow: ellipsis;
display: -webkit-box;         /*弹性伸缩盒子*/
-webkit-line-clamp: 2;        /*第几行省略号*/
-webkit-box-orient: vertical; /*垂直居中*/
```

## 7 图片放置方案

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

## 8 居中总结

### 8.1 文本居中

text-align: center; 文本水平居中

line-height: 盒子高度; 文本垂直居中

### 8.2 盒子居中

（1）margin实现水平居中

margin: 0 auto;

（2）

margin配置定位或translate实现

```
/*父盒子*/
.father {
  position: relative;
  width: 200px;
  height: 200px;
  border: 1px solid #000;
}
/*子盒子*/
.son {
  position: absolute;
  top: 50%;
  left: 50%;
  width: 100px;
  height: 100px;
  border: 1px solid #000;

  /*方式一，写死
  margin-top: -50px;
  margin-left: -50px;
  */
  /*方式二，translate自动计算
  transform: translate(-50%,-50%);
  */
  /*方式绝对定位偏移都为0，margin自动就能水平垂直居中
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  margin: auto;
  */
}
```

（3）flex实现

```
/*单行*/
父元素 {
  display:
  flex; justify-content: center;
  align-items: center;
}

/*多汗*/
父元素 {
  display:
  flex-wrap: wrap;
  flex; justify-content: center;
  align-contgent: center;
}
```

# 八、CSS3新特性

这些新特性都有兼容性问题。移动端兼容性问题比较少。

## 1 新属性

### 1.1 半透明效果：

```
background: rgba(r,g,b,a)，a为透明度（0-1），0全透明，1不透明
```

### 1.2 圆角边框：

```
border-radius: 
值为像素或百分比（width的%）的半径，可以跟1-4个值:
2个时为对角
4个时分别为左上顺时针到左下
也可以如border-top-left-radius设置单独圆角。
```

### 1.3 盒子阴影：

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

### 1.4 文本阴影

```
text-shadow: h-shadow(必写) v-shadow(必写) | blur | color; 使用与盒子阴影一样。
```

### 1.5 滤镜

```
filter: 函数();
最常用的模糊处理：blur( xpx )，x越大越模糊，0为不模糊。
```

### 1.6 宽度自动计算

如：width: calc(100%-80px); 可以永远比父少80px，+-*/均可

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

### 1.8 transiform平面转换

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

### 1.9 渐变背景色

```
background-image: linear-gradient(to right,red,rgba(0,255,0,0.8),blue)
第一个参数可以省略，默认为 to bottom
颜色参数可以有任意个，可以使用rgba()和transparent
```

## 2 新选择器

以下示例的E表示选择器

### 2.1 属性选择器：

```
E[属性] {} 选出写有该属性的标签。
E[属性=”value”] {} 选出写有该属性,且值为value的标签。

^*$
E[属性^=”value”] {} 选出写有该属性,且值开头为value的标签。
E[属性*=”value”] {} 选出写有该属性,且值含有value的标签。
E[属性$=”value”] {} 选出写有该属性,且值结尾value的标签。

权重：[]=0010, =0010+E权重
```

### 2.2 结构伪类选择器：

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

### 2.3 伪元素选择器：

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

## 3 新盒子模型

```
//默认的盒子大小计算方式，加不加都一样，padding，border会撑大盒子，大小=w/h+padding+border
box-sizing: content-box;
//CSS3的盒子模型，盒子大小始终是width，padding，border不会撑大盒子，大小=width，但是注意当padding+border > w/h，就会撑大盒子。
box-sizing: border-box;  
```

盒子宽度总结（高度以此类推）：

宽度都不计算margin

offsetWidth为整个盒子宽度，clientWidth为可视内容宽度，scrollWidth为实际内容宽度

|             | content-box              | border-box               |
| ----------- | ------------------------ | ------------------------ |
| offsetWidth | width+2倍padding+2倍border | width                    |
| clientWidth | width+2倍padding          | width-2倍border           |
| scrollWidth | width                    | width-2倍border-2倍padding |

## 4 动画

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

# 九、移动端布局

## 1 基本

### 1.1 与PC端的不同：

- 不用设置版心，px与物理像素一一样。

- 移动端浏览器基本没有兼容性问题，可以放心使用H5C3新特性。

- 一些标签在移动端各浏览器都有各自样式，为了统一各浏览器的标签样式，通常使用github上的normalize.css进行初始化。

- 为了防止用户过渡缩放，移动端页面要设置最小/最大宽度，一般最小宽度为320px，最大宽度看需求
  
  ```
  body {
    min-width: 320px;
    max-width: 640px;
  }
  ```

### 1.2 分辨率：

屏幕真实的分辨率是物理分辨率，px是逻辑分辨率，PC端是1:1的，而移动端中，物理:px都是n:1，这叫物理像素比，
window.devicePixelRatio 获取当前的物理像素比

因此，图片放到移动端中，会放大n倍而模糊，所以在开发中，拿到图片先要将它缩小n倍再放到页面中，它会自动方放大n倍，就能不营销图片清晰度。因此，准备图片应当按照物理像素比来，叫n倍图。

缩小图片是用软件工具缩小，而不是写代码

### 1.3 移动端单位

除了pc端的px和 %，移动端还有em，rem，vh，vw单位
x em 数值是最近且有该属性的祖元素字体大小的x倍
x rem 数值是html标签的对应样式属性的x倍，若html标签未指定样式，则是浏览器样式的x倍
vw/vh，可视窗口的宽/高分成100份，1个vw/vh占一份，如100vw就是与可视窗口一样宽，50vw就是一半宽（可视窗口就是整个手机屏幕）

### 1.4 视口

视口是浏览器显示页面的屏幕区域。手机默认都有一个布局视口，是尽量显示整个PC端页面，手指缩放的形式，很不方便，后来就有了视觉视口，显示部分PC端页面，手指左右滑动的形式。

现在使用的是理想视口，页面宽度即视口宽度，通过视口标签指定：

```
<meta name="viewport" content="width=device-width, initial-scale=1.0">
```

指定视口宽度为设备宽度，其他属性可以设置缩放比例以及是否可缩放

### 1.5 移动端开发方案

  独立页面：流式布局，flex布局，rem布局
同个页面：响应式布局

流式布局（百分比布局）：

现在很少用了。
将宽度都设置为百分比，这样宽度就会随屏幕大小而变化。
一般要设置最小宽度（320px）和最大宽度
一般将body宽度设置为100%，最小320px，最大根据需要，为了方便在PC端查看还要设置水平居中。

## 2 flex布局

又叫弹性布局，伸缩布局等

### 2.1 基本使用

```
ul {
  display: flex;
}
/*flex: 1; 是非必要的*/
li {
  flex: 1;
}
```

- 子元素不管是行内元素还是块级元素，都能设置宽度。

- 效果是水平展示，flex:1;是均分视口宽度（各占一份的意思，可不写）。

- 不脱标。

- flex布局是在剩余空间中，给子项分配空间，减去margin，边框和有宽度的盒子就是剩余空间

- display:felx;使得float,clear,vertical-align属性失效，flex:1;使得width，flex-wrap失效

- flex布局缺点：一般高度定死，字体大小无法岁屏幕缩放，而这些可以通过适配方案解决。

- 由于设置了flex: 1; 后width失效，所以在需要flex:1;同时需要设置下划线长度或背景色宽度等需求时，可以在里面再放一个div，来设置div的width

### 2.2 属性

flex父元素叫弹性容器，子元素叫弹性盒子

主轴和侧轴，默认x轴为主轴，y轴为侧轴，若设置y为主轴，则x为侧轴

flex默认不换行，若超过长度会改变子项大小强行塞入一行

（1）父元素属性

1. display: flex; 所有子元素在主轴上排列显示且不换行

2. 设置子元素在主轴上的排列方式
   
   justify-content: xxx;
   
   | flex-start    | 默认，左边开始                  |
   | ------------- | ------------------------ |
   | flex-end      | 右边开始                     |
   | center        | 实现水平居中                   |
   | space-around( | 均分主轴，缝隙各自用所以中间缝隙是两侧缝隙两倍大 |
   | space-between | 两个子项到边缘，两侧无缝隙，剩余子项平分剩余空间 |
   | space-evenly  | 均分主轴，共用缝隙一样大             |

3. 设置侧轴上子项的位置（限单行）
   
   align-items: xxx;
   
   | strech     | 默认，若没有设置子元素高度，子元素会拉伸父元素一样高 |
   | ---------- | -------------------------- |
   | flex-start | 上边开始                       |
   | flex-end   | 下边开始                       |
   | center     | 垂直居中                       |

4. 设置侧轴上子项的位置（限多行）
   
   align-content: xxx;
   
   属性与justify-content一样，多了个strech(默认)与align-items的一样

5. 设置主轴方向
   
   flex-direction: row(默认) | column | row-reverse | column-reverse

6. 设置换行
   
   flex-wrap: nowrap(默认) | wrap
   
   flex默认不换行，子项太多会压缩宽度以保证在一行显示。且每行的所有元素高度相同

7. 主轴方向，换行复合写法
   
   flex-flow: column wrap

（2）子元素属性

1. flex: 1; 伸缩比属性，让子元素占一份
   
   如有三个孩子a，b，c，flex分别设置为1,2,1，就共4份，a c各占一份，b占2份
   
   注意：flex优先级比width高，会使width失效
   
   利用flex是分配剩余空间的特性，实现圣杯布局（两侧固定px，中间自适应）：
   
   两侧给固定宽度px，只给中间设置flex:1; 剩余空间分成1份而中间独占这一份，同时为了避免过多的缩小，可以给父元素设置min-width，max-width

2. align-self: xxx; xxx与父元素的align-items一样，单独设置子项的侧轴排列方式

3. order: 正负整数(默认0); 设置该子项的排列顺序，数值越大越靠前，相同数值哦按原本顺序

### 2.3 flex布局常用实例

```
/*圣杯布局，左右固定宽度，中间flex:1自动适配*/
.left, .right {
  width: 100px;
}
.middle {
  flex: 1;
}

/*分栏布局，一行x个元素，width: (100/x)% */
.father {
  display: flex;
  justify-content: center;
  flex-wrap: wrap;
}
.son {
  width: 50%;
}
/*分栏布局，每个item有图片+文字(如商品列表)，若图片大小不同，可以使用下面的方案*/
.box {
  display: flex;
  justify-content: space-around;
  flex-wrap: wrap;
}
.item {
  display: flex;
  align-items: center;
  position: relative;
  width: 45%;
  .img {
    width: 100%;
    padding-bottom: 30vw;
  }
  .info {
    position; absolute;
    bottom: 0;
  }
}
```

## 3 多媒体查询

要实现不同屏幕大小来修改html标签的字体大小，需要使用多媒体查询（CSS3）

```
html {
  font-size: 15px;
}
选择器 {
  xxx: 2rem;
}
```

当设备符合条件时就适用里面的css代码

媒体类型有：all（全部），screen（屏幕），print（打印机）

媒体特性即条件，screen媒体特性有：width，min-width（相当于>=），max-width（相当于<=）

注意根据css的层叠性来决定多媒体查询的顺序

如：当宽度小于320px时

```
media screen and (max-width:320px){
  选择器 {
    //css
  }
}
```

screen可省略，简写如下：

```
@media (...){
 //css
}
```

多个条件可用and链接

```
@media (...) and (...){}
```

引入资源：

rem和多媒体查询可以实现字体，高度等的适配，也可以实现不同屏幕适用不同的布局，如果适配的样式太多，可以将不同屏幕给不同的css文件，再引入资源：

link标签里面的属性： mediatype="media screen and (min-width:320px)" 复合条件就使用对应的css文件。

## 4 移动端适配

### 4.1 rem

rem是单位，x rem 数值是html标签的字体大小的x倍，若html标签未指定样式，则是浏览器样式的x倍。

rem适配就是通过只给html标签的字体大小设置px，给其他元素样式设置rem，当屏幕大小变化时只需要修改html标签的px，rem就能根据html标签的样式自动适配。

注意，不管是em还是rem，html都只设置font-size，其他css属性都是根据这个适配，如width，height

```
html {
    font-size: 15px;
  }
  选择器 {
    xxx: 2rem;
  }
```

rem适配方案

- 方案一：rem+多媒体查询+less，例：
  
  设计稿宽750px，需求分15份，最小屏幕320px
  
  1.less文件a，编写多媒体查询，分为x个屏幕区间，字体大小为 屏幕宽px / 15
  
  2.less文件b，引入a，按照屏幕750px进行开发，如设计稿图片宽100px，则将 其宽度（100/(750/15)=2），设置为 width: 2rem;
  
  3.这样，各个屏幕就能根据2rem进行适配

- 方案二：rem+flexible.js+vscode插件cssrem/less
  
  不用再写多媒体查询，flexible.js已经给各种大小的屏幕的html字体大小设置为：屏幕宽px / 10
  
  按750px设计稿设置100px宽的图片时，100/(750/10)=1.33 width: 1.33rem
  
  如果不适用less，可以用cssrem，在写代码的px时就可以代码提示成对应的rem，但是注意，remcss默认是html的font-size是16，需要在首选项中设置为（750/10）=75

### 4.2 vw和vh

vw会适配，但是vh不会（慎用）

它们是相对于视口的单位（宽，高），将视口划分成100粉，如5vw即5%的视口宽度

与流式布局的百分比区别：流式布局的百分比是相对于父元素，而vw，vh是相对于当前视口。

由于是根据视口给的宽高，这样不管屏幕怎样变化都会自动适配，比rem方便太多了。

- 只适用于移动端，PC端完全不兼容

- 由于缩放一般都是缩放宽度而不缩放高度，所以vh很少用，一般不管width还是height，都是用vw。

- 设计稿转化成vw，vh
  
  设计稿一般给750px，它是二倍图，需要缩小原来的1/2，缩小后，如图中的一个盒子宽度为37.5px，则 37.5/375*100=10，所以 width: 10vw; 也可以借助一些工具直接量出来，由于有大量除法也可以用less计算或vscode插件px2vw

## 5 响应式布局

使一套页面根据不同终端屏幕大小（PC,pad,phone）响应式的改变布局。不需要另外开发移动端页面。但是这种布局方式很少用了，但需要了解。

- 原理
  
  通过多媒体查询实现，根据屏幕大小划分为四个档位，<768px(超小屏幕，如手机)，>=768px && <992px(小型屏幕，如pad)，>=992px && <1200px(中等屏幕，如PC显示器)，>=1200px(宽屏，如宽屏显示器)

- 响应式布局容器
  
  为了简便，用一个父元素包裹需要响应式的子元素，用多媒体查询来改变该容器的宽度（四个档位宽度分别改为 100%，750px，970px，1170px），子元素也可以响应式的修改。

- 移动端框架——bootstrap
  
  常用于开发响应式页面，也能做移动端页面
  
  bootstrap有响应式容器，通过栅格系统实现响应式，不需要多媒体查询来修改容器宽度
  
  基本使用：
  
  bootstrap的每行共分为12列
  
  ```
  <!-- 分别在宽屏，中屏，小屏，超小屏中，每个元素占3，4,6,12份，使得一行显示4,3,2,1个元素 -->
    <div class="container">
      <div class="row">
        <div class="col-lg-3 col-md-4 col-sm-6 col-xs-12">1</div>
        <div class="col-lg-3 col-md-4 col-sm-6 col-xs-12">2</div>
        <div class="col-lg-3 col-md-4 col-sm-6 col-xs-12">3</div>
        <div class="col-lg-3 col-md-4 col-sm-6 col-xs-12">4</div>
      </div>
    </div>
    <!-- 列可以嵌套列，被嵌套的列又分为12份 -->
    <div class="container">
      <div class="row">
        <div class="col-md-6">
          <div class="col-md-4">1</div>
          <div class="col-md-4">2</div>
          <div class="col-md-4">3</div>
        </div>
      </div>
    </div>
    <!-- 设置列偏移（左偏），偏移会占用份数，如下是实现各占3份的两个元素贴向两侧 -->
    <div class="container">
      <div class="row">
        <div class="col-md-3">1</div>
        <div class="col-md-3 col-md-offset-6">2</div>
      </div>
    </div>
    <!-- 列排序，改变排列顺序 -->
    <div class="container">
      <div class="row">
        <div class="col-md-4 col-md-push-8">本来是左，后面会推到右</div>
        <div class="col-md-8 col-md-pull-4">本来是右，后面会拉到左</div>
      </div>
    </div>
    <!-- 响应式工具，实现显示隐藏，若隐藏了，则不再占用份数 -->
    <div class="container">
      <div class="row">
        <div class="col-md-4 hidden-md">我只在中屏时隐藏</div>
        <div class="col-lg-6 visible-lg">我只在宽屏时显示</div>
      </div>
    </div>
  ```
  
  其他详见文档

## 6 移动端的历史遗留问题

### 6.1 移动端点击事件300ms延迟：

原因：移动端浏览器一般都有双击缩放或双击xxx，为了监听出双击，在点击第一次后，若300ms内再次点击，就是双击。
但是大部分情况下，300ms都是很难被用户接受的

解决：有很多方法，其中一种：

```
npm install fastclick --save
//main.js
import FastClick from 'fastclick'
FastClick.attack(document.body)
```

### 6.2 移动端滚动问题

移动端浏览器滚动会有一些问题，所以滚动会使用第三方库，如better-scroll

npm install better-scroll --save //若是引用的better-scroll.js文件，是new bscroll()

基本使用

```
/*
使用规则：
1.大盒子里放有且只能一个小盒子，在小盒子里放滚动的元素
2.大盒子设置高度以此限定滚动区域，并设置over-flow:hidden;隐藏超出
3.import bscroll from 'better-scroll'
4.vue中因为以下代码需要在有模板才生效，所以需要写在创建模板结束的生命周期函数mounted()内
5.这里使用ref而不推荐dcument.querySelector('.类名')，因为有多个scroll时会冲突
*/

const scroll = new bscroll(this.$refs.refname,{    //大盒子需要属性 ref="refname"
  //可选属性
  //参数1，默认为0， 0/1不监听位置，2监听，但脱手惯性时不监听，3惯性时也监听
  probeType: 0 | 1 | 2 | 3,    
  //参数2，默认false一些点击事件会失效，所以最好true
  click: false | true,        
  //参数3，上拉，默认false
pullUpLoad: false | true    
})
//监听坐标，需要probeType:2 | 3  position为位置信息
scroll.on('scroll',position => {})     
//监听上拉到底部，需要pullUpLoad:true  拉到最底部时的事件，默认执行一次，与scroll.finishPullUp()配合可以多次
scroll.on('pullingUp',() => {
  scroll.finishPullUp()
})        
//ms可不传默认0，在ms内到x，y位置，0,0为顶部    
scroll.scrollTo(x,y,ms)    
```

封装成vue组件：

```
/*
1.与axios一样依赖性很强，为了方便以后管理维护代码，将以上代码封装成.vue文件，使用时注册该组件使用
2.probeType和pullUpLoad需要传入
3.外部调用scroll对象时最好先判断scroll对象是否为空
*/
<template>
  <div class="wrapper" ref="wrapper">
    <div class="content">
      <slot></slot>
    </div>
  </div>
</template>

<script>
  import bscroll from 'better-scroll'

  export default {
    data(){
      return {
        scroll: null
      }
    },
    props: {
      probeType:Number,
      pullUpLoad:Boolean
    },
    mounted(){
      this.scroll = new bscroll(this.$refs.wrapper,{
        probeType: this.probeType,
        click: true,
        pullUpLoad: this.pullUpLoad
      }),
      this.scroll.on('scroll',position => {
        this.$emit('showBackTop',position)
      }),
      this.scroll.on('pullingUp',() => {
        this.$emit('pullUpLoad')

      })
    }
  }
</script>

<style scoped>
  .wrapper {
    position: absolute;
    top: navbar高度
    bottom: tabbar高度;

    left: 0;
    right: 0;
    overflow:hidden;
  }
</style>
//父组件中获取滚动组件实例对象，来调用scrollTo，refresh
```

注意事项：

注意事项

1. 无法滚动bug
   由于scroll对象创建后会根据网页内容有一个初始高度，而发生网络请求后显示请求的图片，高度变高，但scroll高度不会刷新，就会无法滚动。
   
   解决方法：一旦加载一张图片，就使用scroll.refresh()刷新高度
   在显示图片的组件里，img标签绑定事件 @load="" 并定义自定义事件，home组件刷新高度 ，但是此时home组件和该组件会涉及到非父子组件之间的通信，可以用vuex或事件总线解决。
   优化：防抖动，不用每次加载完图片都调用refresh()

2. 跳转bug，与1同理，都是图片未加载完，高度需要refresh，跳转的位置才会正确

3. better-scroll的滚动是基于自身的可滚动区域，scroll.on('scroll',e=>{})坐标e随自己的可滚动区域而不是window

4. betterscroll的高度是整个可滚动区域的高度而不是当前展示的滚动区域高度，设置top、bottom时需注意

5. better-scroll组件内的子组件的绝对定位、固定定位和黏性定位会有bug（相对定位正常）
   
   - 绝对定位，就算scroll组件没有相对定位，绝对定位也是以scroll组件为父元素，而更下一级以后的组件则正常，但都以scroll组件为根
   
   - 固定定位完全失效，不再以浏览器视口为父，而是以scrill组件为父，所以会随着滚动而滚动
   
   - 黏性定位完全失效，解决方法：多弄一个该子组件在scroll组件外，绝对定位到顶部，需要时再显示

6. offsetTop不准问题（不是betterscroll带来的问题，本身就有），原因是上面有图片未加载完，需要@load监听才能获得最终的offsetTop

7. betterscroll结核的bug，数据确实保存了，但是滚动位置与原来不同：
   
   首先要知道betterscroll的两个特点，一是脱手会惯性滚动，二是滚到顶部或底部会有弹簧效果的滚动
   
   使用了且监听scroll事件，出现的问题：
   
   ①、当手指滑动/惯性滚动/弹簧滚动的同时切换路由时，scroll事件会一直调用且Y坐标为0（activated()和beforeRouteLeave()获取到的也是0），所以路由再切换回来时，就会自己滚到顶部。
   
   ②、当上拉加载更多的同时切换路由，若还在加载中，则scroll会一直调用直到加载完成，与情况1不同的是Y是正确的当前位置，但是路由切换回来时还是会回到顶部
   
   解决思路：
   
   * 用变量a保存Y值，scroll事件函数获取Y值时，如果得到了0，就不赋值给a，否则就把Y值赋值给a
   
   * deactivated()中，scrollTo(0,a)，使滚动停止；但是处于弹簧效果时没用，因为此时a的值还是在弹簧效果内，所以scrollTo(0,0)，以确保Y不处于弹簧效果
   
   * activated()中，scrollTo(0,a)，但是必须在前面refresh一下，否则还是会缓慢滚动顶部
     
     ```
     ...
     deactivatedY: 0
     ...
     onMounted(){
       let scroll = new bscroll({
         probeType: 3,
         click: true,
         pullUpLoad: true  
       })
       scroll.on('scroll',e => {
         this.deactivatedY = e.y == 0 ? this.deactivated : e.y  
       })
       ...
     }
     activated(){
       scroll.refresh()
       scroll.scrollTo(0,deactivatedY)
     }
     deactivated(){
       scrollTo(0,0)
     }
     ```

8. 若betterscroll内的组件有切换展示数据的功能，每类数据有多有少，展示出来的高度就不同且滚动过的距离也不同，为了用户体验，应当监听scroll事件，给每类数据都保存一个Y值，切换数据的同时scrollTo()，典型应用如多种类型的商品列表
   
   或者另一种更好的方案，每次切换都滚动到数据最开始展示的地方，实现比较简单

9. 回滚bug，当在图片未加载完成前滚动或scrollTo到该图片后面，则当图片加载完后，此时滚动区域refresh后被撑高，就会回滚一段距离，距离就是图片的高度，目前无法解决。

10. 不要重复new bscroll，除非是需要使用多个betterscroll

# 十、CSS预处理语言

## 1 less

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

## 2 sass

与less语法基本相同，但是变量用$定义
less基于JavaScript，在客户端处理
sass基于Ruby，在服务端处理

end   
