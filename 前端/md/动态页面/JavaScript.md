# 一、基本介绍

HTML，CSS首选双引号，JS代码首选单引号。外双内单，外单内双
JavaScript是一种面向对象的脚本语言（解释语言是用解释器解释一行执行一行，编译语言是编译器全部代码编译完后再执行）
浏览器的渲染引擎用来解析html和css，也叫内核；js引擎用来解析js
JS的组成：

1. ECMAScript（ES，JS的语法）

2. DOM（页面文档对象模型，对标签进行操作实现动态效果）。

3. BOM（浏览器对象模型，操作浏览器窗口）

JS书写位置：

1. 行内式，标签内书写 事件=””

2. 内嵌式，<script>JS代码</script>

3. 外部式，<script src=”xxx.js”>此处不能写代码</script>，

内嵌式和外部式需要注意，由于html代码是由上至下解析，所以script标签一定要在全部网页标签代码后面，否则大部分js会无效。也可以在将script代码放在window.onload(){}中，使得页面加载完再加载JS。

# 二、ES5

注释方法与c一样，每个语句也是以分号结尾(但是不加分号也不会报错)

## 1 输入输出

```
var a = prompt('提示文本'); 页面出现带有提示文本的输入框
alert('输出文本'); 页面出现警示框
consolo.log('输出文本'); 控制台输出
```

## 2 变量，数据类型，类型转换，运算符

### 2.1 变量

1. 变量声明用var，不加var会变成全局变量（但此时必须赋值）

2. 使用未赋值的变量结果为undefind，直接使用未声且明未赋值变量会报错

3. var a=1,b=2,c=3;相当于用var声明了三个var变量，但是，var a=b=c=4; 相当于var声明a是局部变量，而b，c没有用var声明，变成全局变量

4. 命名：还可以用$命名，变量属性，函数方法小驼峰，对象，构造函数大驼峰，其他与c一样

### 2.2 数据类型

JS属于弱类型语言，未赋值的变量数据类型不确定，赋值后才自动确定。JS属于动态语言，变量重新赋值时可以赋值另外的数据类型，JS分为简单数据类型，复杂数据类型

```
Number,Boolean,Stirng
undefined,null
Object
Symbol(ES6)
BigInt(ES11)

typeof 变量 检测变量的数据类型（注意prompt和任何表单获取的值都是字符串）
2)、各数据类型在控制台的颜色：
数字（蓝），字符串（黑），布尔（深蓝），undefind和null（灰）
字面量：一眼就看出是什么类型的东西，如18 ‘aaa’都是字面量
```

需要注意的点：

简单数据类型（值类型/基本类型）：

1. Number：
   
   包括整型，浮点型，0八进制，0x十六进制，
   
   Number.MAX_VALUE最大值，Number.MIN_VALUE最小值，最大值*2 无穷大infinity，-最大值*2 无小-infinity，NaN非数字 isNaN(变量或值) true为非数字。
   数值字面量/数值变量.toFixed(n) 保留n位小数

2. String
   
   str.length返回长度（不包括\0）
   
   加法表达式一旦有字符串结果都是字符串拼接（包括’’）
   
   转义符与c一样，

3. Boolean
   
   可参与加法，分别代表1和0，字符串相加当成’true’ ’false’

4. undefined
   
   与数字计算结果为NaN，与字符串相加，当成’undefind’

5. null
   
   可参与运算，当成0，字符串相加当成’null’（被null赋值的变量返回是object，可作为空对象，是历史遗留问题）

复杂数据类型（引用类型）：数组，对象

1. 数组可以存放不同的数据类型
   
   ```
   var arr = []; 或 var arr = new Array();
   arr.length 返回数组元素个数 arrname.length = n 数组大小改为n，常用扩容
   直接给数组名赋值会丢失整个数组的数据。
   所有语言都是一样，即使只有值传递，数组作为形参也能修改数组本身
   其他与c一样。
   ```

2. 对象
   
   ```
   var obj = {
   
   }
   ar obj = new Object()
   ```

### 2.3 类型转换

1. 转成String
   
   xxx + ’’（隐式转换） xxx.toString()  String(xxx)（两个强制转换）

2. 转成Number
   
   parseInt(str)  parseFloat(str)
   Number(str)（string转数值，强制转换） 
   
   str - 0 str * 1 str / 1（隐式转换）

3. 转成Boolean
   
   Boolean(xxx) 空的否定的值如0 ‘’ NaN null undefind转换成false，其余true

### 2.4 运算符：

（1）浮点数由于有精度，所以比较浮点数时需要处理
（2）短路运算（逻辑中断）：当逻辑运算符两边其中一个不是布尔而是算数表达式或值时的情况，根据左的真假返回相应的值（若左非布尔，则会隐转成布尔）

1. 逻辑与短路运算：左真用右，左假用左（中断右）

2. 逻辑或短路运算：左真用左（中断右），左假用右

（3）== 和 ===

1. == != 先转换成相同类型再比较

2. !== 先判断类型是否一致，不一致直接true，再比较

（4）检测数据类型

1. typeof 变量        检测变量的数据类型

2. instanceof xxx  判断是否为数组，对象，是返回true，否则false
   obj instanceof Object        arr instanceof Array

3. Array.isArray(arr)    比instanceof优先级高，H5新增

其他运算符与C一样

## 3 流程控制

使用循环时，需要注意var会被提升成全局变量（闭包或let解决）

此外，js有特有的循环forEach

```
//只能用于遍历数组
var arr = [123,456,789]
arr.forEach(function(item,index,arr){
  console.log('值为',item)
  console.log('下标为',index)
  console.log('遍历的原数组为',arr)
},this)
/*参数
1 function(){}  若arr为空则不会回调
  1.1 item  必传
  1.2 index 可选
  1.3 arr   可选
2 this 若不传，undefined或空则默认为this
*/
```

其他与C语言一样

## 4 函数

JS只有值传递没有引用传递。

```
//声明
function fun1(){}（命名函数）
var fun1  = function(){}（匿名函数，没有函数名）
JS没有类型检测机制，如形参为字符串，实参为数值，却不会报错（缺陷）
形参不加var，不指定数据类型：

//调用：
fun()
fun2()

调用时可以传递任意类型的实参，基本/引用/函数等
形参是函数时，是将形参，函数体传进来
```

（1）JS函数的实参个数可以和形参不一样：

1. 实参比形参多：多出的实参忽略

2. 实参比形参少或没有实参：缺失的实参看作undefind

（2）返回值：

1. 有多个返回值时只返回最后一个（如ruturn n1,n2;返回n2，想返回多个用数组 [] ）

2. 变量接收没有return的函数，得到undefind

函数不一定要声明在执行前，即使函数内嵌函数也是。（会被提升）

（3）arguments：

所有函数都有的内置对象，存储所有实参，是一个伪数组，在函数内直接当做名字为arguments的数组使用即可。
arguments作用：在不知道要设置多少形参时使用，不管多少实参都行。

（4）伪数组：

具有length属性，也按索引方式存储元素，但没有真正数组的内置的Array方法。

（5）作用域：
var没有块级作用域（if，for等{}包含的区域），所以局部作用域只在函数内部和形参。
在函数内部（不是形参）不加var声明但赋值的变量是全局变量。
作用域链：

函数内嵌函数，内部函数可调用外部函数变量，反之不可，调用时找最近一级有该变量的外部函数（链式查找）。全局变量是最远的一级。
其他与c一样

（6）形参默认值：
可以给形参设置默认值，函数体中
var a = 形参 || 默认值

（7）立即执行函数：

```
(function(形参){})(实参)
(function(形参){}(实参))
不用调用，这样写会立即执行
同时，函数内部的var会变成局部变量，只在该函数中有效，这就是闭包，解决了var的作用域问题。
当整个js文件都在立即执行函数中时，引入多个js文件就不会产生变量名冲突的问题。
```

## 5 预解析（预编译）

JS引擎运行JS代码分预解析和执行两步：
预解析，将各作用域var和function声明提升到当前作用域最前。
执行：由上至下一行行解释运行。

### 5.1 var的预解析：

将var 的声明提升，赋值不提升（注意是要有var声明的）
因为匿名函数是var声明，所以与var一样。

```
//提升前：
console.log(n)
var n = 10
//提升后：
var n
console.log(n)
n = 10
```

### 5.2 具名函数预解析：

提升function声明，不提升调用。即命名函数调用可以在声明前。（匿名函数不行）

## 6 对象

### 6.1 创建对象：

属性，方法都是逗号隔开的键值对，方法都是匿名函数

（1）字面量创建对象：

```
var obj = {
 属性1 : 值,
 …,
 属性n : 值,
 方法1 : function(){},
 …,
 方法n : function(){}
} 
/*
属性名和方法名本来是要加单引号的，但是可简写为不加，但是当名字为表达式时必须加单引号
*/
```

（2）new创建对象：

```
var obj = new Object(); 创建空对象
```

（3）构造函数创建对象

前面两种方式一次只能创建一个对象，当需要创建多个对象，且属性方法很多相同时，代码会冗余。此时就需要构造函数。
构造函数里放各个对象公共的属性和方法，各个对象根据需要另行追加属性方法。
构造函数名首字母大写，没有return

```
//属性
function xxx(形参){
 this.属性 = 初始化值; //属性可以自己初始化，也可接收形参  
 this.属性 = 形参; //this与形参同名不会冲突
 this.方法 = function(){}
}
//添加非静态属性/方法 （实例化对象可调用）
xxx.prototype.属性名 = 值
xxx.prototype.方法名 = function(){}
//添加静态属性和静态方法（静态的职能构造函数调用，实例化的对象无法调用）
xxx.属性 = 值
xxx.方法 = function(){}
```

```
//使用时；
var obj = new xxx(实参); //构造函数不需要return就能返回一个对象
```

new创建对象过程：内存创建空对象，this指向该空对象，执行构造函数里面代码追加属性方法，最后返回这个对象。

### 6.2 调用对象，添加属性方法

```
obj,key
obj[‘key’]         //此处的'key'也可以是字符串变量
obj[‘key’] = value //改变属性值，若没有key，则是添加属性
obj.fun()
obj['fun']()
obj.fun = function(){} //追加方法

若调用没有的属性/方法噶，值为undefined
undefined.undefined会报错

if(obj['key'])  //可判断key是否存在
```

### 6.3 ES5对象继承

分为原型继承，组合继承，构造函数继承

```
//构造函数继承：
//父构造函数
function fa(a){
 this.a=a
}
//子构造函数继承父
function ch(a,b,c){
 fa.call(this,b,c) //改变父的this指向ch
 this.b=b
 this.c=c
}
//要实现继承，还需设置子构造函数的原型
ch.prototype=new fa
//定义子构造函数的方法
ch.prototype.func=function(){}
//实例化
let chi=new ch(1,2,3)
```

### 6.4 Object与原型：

（1）Object：

Object是所有对象的原型，具有内置的属性和方法，此外，Array，String，Number，Boolean都是继承于Object，都可以使用Object的属性方法

```
//遍历对象的所有属性
Object.keys(objname) 数组形式返回对象中得到key
//给对象增加爱属性
Object.defineProperty(objname,'key'或变量,{
 value:xxx //这样给对象添加属性和值，默认无法枚举（即遍历），无法修改，无法删除
 enumerable:true //可遍历
 writable:true //可修改
 configurable:ture //可删除  
})

Object.defineProperty(objname,'key'或变量,{
 set(value){//一旦修改值，就回调这个函数，value拿到了修改的值，一般通过value赋值给要修改的属性}
 get(){//一旦访问值，就回调这个函数，一般要return访问结果}
})
```

（2）原型

### 6.5 常用内置对象

查阅文档：https://developer.mozilla.org/zh-CN/
非构造函数直接可以使用，而构造函数需要var objname=new 对象名();

#### 6.5.1 Math

非构造函数，不用new        使用 Math.方法()

```
Math.PI 圆周率
若传入参数为全数字的字符串，会隐转，但若非数字的字符串则返回NaN
Math.max() 最大值，补给实参返回负无穷
Math.min() 最小值，补给实参返回正无穷
Math.abs() 绝对值
Math.floor() 向下取整
Math.cell() 向上取整
Math.round() 四舍五入（特殊：负数.5往大的取）
Math.random() 无参数，返回0-1（左闭右开）的小数
function r(min,max) // min-max(左闭右闭)的整数
{
return Math.floor(Math.random()*(max-min+1))+min;
}
```

#### 6.5.2 Date()

构造函数，需要new     使用 对象名.方法()

```
var date=new Date()
console.log(date) //不带参数返回系统时间
参数格式：
数字型 年,月,日 月份输出比参数大1
字符串 ‘年-月-日 时:分:秒’ 月份正常
date.getFullYear() 返回当前年
date.getMonth()+1 返回当前月（Date对象的月是0-11，所以要+1）
date.getDate() 返回当前日
date.getDay() 返回当前星期几（周日返回0）
date.getHours() 返回当前小时
date.getMinutes() 返回当前分
date.getSeconds() 返回当前秒
1970-1-1 0:0:0到现在的总毫秒数（时间戳）：
date.valueOf(); date.getTime(); +new Date() Date.now()（H5新增）
```

#### 6.5.3 Array()

构造函数需要new        使用 对象名.方法()
只有一个参数为长度，>=2个参数为初始化数组元素

```
IndexOf(元素值) 返回从前往后，第一个符合的元素下标，找不到返回-1
lastIndexOf(元素值) 返回从后往前，第一个符合的元素下标，找不到返回-1
这两个方法也可以用来判断数组是否存在该元素，不存在则-1，去重也可利用

push() 数组后面添加元素，参数可多个，返回数组变化后的长度
unshift() 数组前面添加元素，参数可多个，返回数组变化后的长度
pop() 删除最后一个元素，不带参，返回删除的元素值。
shift() 删除第一个元素，不带参，返回删除的元素值。
toString() 数组转字符串，逗号分隔，不改变原数组
join(‘str’) 以str作为分隔符将数组转字符串，不带参为逗号，不改变原数组
（一般提交到后台的数据以’&’分隔）
concat() 在数组后面连接多个数组，不改变原数组
slice(a,b) 取出下标a-b(左闭右开)的元素，不改变原数组
splice(a,n) 删除下标a-a+n（左闭右开）），改变原数组，返回删除的元素
（splice还有插入/删除/替换功能）
reverse() 翻转数组,不带参
sort() 不带参时，按个位值大小升序排序
与C++类似，sort()的参数为比较函数，常用两个按照字面量大小排序的比较函数
sort( function(a,b) { return a-b; } ) //升序
sort( function(a,b) { return b-a; } ) //降序
```

#### 6.5.4 String

基本包装类型，不用new，直接     字符串变量.方法()使用
普通字符串本身是简单数据类型却具有length属性，是因为它是基本包装类型（简单数据类型包装成复杂数据类型，可给属性和方法，就是Java的包装类，JS有Number，String，Bool三种）

```
var str=’abc’;
相当于
var temp=new String(‘abc’);
var str=temp;
temp=null;

注意，JS的字符串是不可变的：重新赋值的字符串会新开辟一个内存空间，原空间不清理且值保留，所以尽量不要对字符串大量的重新赋值，拼接等操作。

常用方法：
由于字符串不可变，字符串所有方法都不会修改自身，都需要变量接收

[index] 下标访问，H5新增所以有兼容性问题
charAt(index) 下标访问，无兼容性问题
charCodeAt(index) 下标访问，不过得到的是ASCI码

IndexOf(‘字符’) 返回从前往后，第一个符合的下标，找不到返回-1
lastIndexOf(‘字符’) 返回从后往前，第一个符合的下标，找不到返回-1
IndexOf(‘字符’,n) 返回下标n始，从前往后，第一个符合的下标，找不到-1
lastIndexOf(‘字符’,n) 返回下标n始，从后往前，第一个符合的下标，找不到-1
利用字符出现的位置代入n+1，遍历，就能找出某个字符出现的所有位置和次数。

concat() slice()与Array的一样 substring()与slice()一样但不能传入负值
substr()与Array的splice()一样，但不改变自身。
toUpperCase() 全部字符转换大写
toLowerCase() 全部字符转换小写

replace(‘str1’,’str2’) 用str2替换从前往后第一个str1
while(indexOf(x)!=-1) replace(‘x’,’str2’); 实现str2替换所有x字符，但是x只能是一个字符。

split(‘str’) 忽略字符串中的str，并以此分隔，转成数组。
```

# 三、DOM

DOM：文档对象模型，用来操作html制作响应式动态页面
DOM树：
整个html页面是一个DOM树，整个页面就是根元素，叫文档（document），每一个html标签，叫元素（element），所有页面内容，包括每个标签/属性/文本/注释等，叫节点（node）
DOM把以上都看成对象，有自己的属性和方法
注意点：若b.js依赖于a.js 则a必须在b之前引入

## 1 获取元素

```
//Id，querySelector，返回element对象，找不到返回none
/*TagName，ClassName，querySelectorAll返回element对象组成的伪数组，只有一个也是伪数组，找不到返回空的伪数组*/
var a=document.getElementById('id') //找id
var b=document.getElementsByTagName('tagname') //找标签
var c=document.getElementsByClassName('classname') //找类名，h5新增

//#xxx id名  .xxx 类名  xxx 标签名，H5新增
var d=document.querySelector('#xxx') //只返回第一个
var e=document.querySelectorAll('.xxx') //返回所有

//获取body，html标签
var f=document.body //body
var g=document.documentElement //html
```

## 2 读写文本，属性，样式

以下e代表element元素对象

```
//文本：
e.innerText  写：覆盖所有文本       读：去除所有空格和换行，读取文本
e.innerHTML 写：覆盖所有文本和标签 读：保留空格和换行，读取文本和标签

//普通标签的属性：
e.属性
*表单属性：
e.value   表单内容
e.disable  true为不能输入/选中
e.type    表单类型

//样式
e.style.样式属性（小驼峰） 行内样式
e.className  修改类名，会覆盖原有，多个类名空格隔开

//自定义属性：
直接在标签中写属性，就是自定义属性
e.属性 只能读写内置属性
e.getAttribute(‘属性’ ) //可获得内置/自定义属性的值
e.setAttribute(‘属性’,’值’ ) //可修改内置/自定义属性的值
e.removeAttribute(‘属性’ ) //删除自定义属性
H5的自定义属性命名规范；data-xxx data-xxx-xxx
新增获得自定义属性得到api：(省略data-，xxx-xxx变成xxxXxx)
e.dataset.xxx    e.data.xxxXxx
e.dataset[‘xxx’]  e.dataset[‘xxxXxx’]
```

## 3 节点操作：

页面的所有内容都是节点，节点操作是对元素的父子兄的操作
如获得e的子元素对象，需要：
获取element对象e后，通过e.getElement... e.query…获取它的子元素对象
节点操作则更方便。

```
//父节点：
e.parentNode //最近一级的父元素对象

//子节点：
e.childNodes //所有子节点，包括元素，文本，注释等
.nodeType  节点类型
.length     节点个数
e.firstChild  e.lastChild  //第一个/最后一个子节点，节点可以是元素，文本等
e.children //获得所有子元素节点
e.firstElementChild  e.lastElementChild //第一个/最后一个字元素节点

//兄弟节点：
e.nextSibling  e.previousSibling  //下/上一个兄弟节点，包括元素，文本等
e.nextElementSibling e.previousElementSibling //下/上一个兄弟元素节点

//创建/添加节点：
let n=document.createElement(‘标签’) //创建一个元素节点，但还未放入页面
e.appendChild(n)  //将n放入e的子最后
e.insertBefore(n,e.children[x]) //将n放入e的x索引的子之前
当页面加载完后执行（如点击事件，window.onload），会清空所以的页面内容重绘，且只重绘document.write的内容
document.write(‘HTML内容’) 
innerHTML在不进行字符层拼接，而使用数组的方式添加节点，效率比createElement高

//删除节点：
e.removeChild(e.children[x]) //删除e的x索引的子元素节点

//复制节点：
let n=e.children[0].cloneNode() //复制e的第一个元素节点，但还未放入页面

//appendChild等操作
若cloneNode() 参数为空，则是浅拷贝，只拷贝元素，元素里的文本等不拷贝
cloneNode(true) 深拷贝，拷贝包括元素，文本等所有节点
```

## 4 事件

### 4.1 事件三要素：

* 事件源：触发该事件的元素对象

* 事件类型：给元素对象注册某事件类型的事件

* 事件函数：触发事件后的操作，事件函数里的this指向事件源

### 4.2 注册事件（绑定事件）：

```
//html标签也可以绑定事件，如<button onclick="fun()"></button>

e.onclick=function(){} //若以此方式注册多个相同事件，后面会覆盖前面的

e.addEventListener(‘click’,function(){}) //事件类型不加on，多个相同事件不会覆盖

e.attachEvent(‘onclick’,function(){}) //IE9以下才支持，最好别用

//删除事件（解绑事件，一一对应三种注册事件方式）：
e.onclick=none
e.removeEventListener(‘click’,func) //注册事件时，事件函数不能是匿名函数
e.detachEvent(‘onclick’,func) //注册事件时，事件函数不能是匿名函数
```

### 4.3 事件类型：

onclick  点击
onfocus 获得焦点
onblur  失去焦点
onmousemove 鼠标移动
onmouseover  鼠标经过  经过子盒子时也触发
onmouseenter  与mouseover区别，经过子盒子不触发
onmouseout   鼠标离开，离开子盒子也触发
onmouseleaves 离开子盒子不触发
onmouseup    鼠标弹起
onmousedown  鼠标按下
contextmemu 鼠标右键菜单，事件函数中event.preventDefault()可阻止菜单打开
selectstart 鼠标选中触发，事件函数中event.preventDefault()可阻止选中
鼠标事件对象常用的是坐标 event.pageX  event.pageY
onkeydown 按键弹起
onkeypress 按键按着不放就一直触发，不能识别功能键
onkeyup   按键按着不放就一直触发，可识别所有键
三个键盘事件不管代码顺序，执行顺序都是down-press-up
event.keyCode 可获得按键码，up，down不区分大小写，press区分
通过event.keyCode 可实现对特定键的监听

onscroll  滚动事件

## 4.4 事件对象：

事件函数给个形参event，事件函数内 console.log(event) 可以看到
事件对象保存了事件类型，事件源等信息，如event.type 事件类型
只有事件触发事件时，事件对象才会创建。
Ul里有若干li，给ul注册事件，li触发了事件：
event.target //返回触发事件的元素对象，li
this  //注册事件的元素对象，ul
阻止默认行为，如a的跳转，button的提交
addEventListener点击事件内：
event.preventDefault()
onclick事件函数内：
event.returnValue   或  return false

## 4.5 事件流：

即事件的传播过程
捕获阶段：触发事件后，从document-html-body-…，一旦有有定义该事件的事件函数就会执行
冒泡阶段：从…-body-html-document传播，一旦有定义该事件的时间函数就会执行
Js只能选择捕获/冒泡其中一个观察效果
onclick,attachEvent只能观察冒泡
addEventListener(‘click’,function(){},true) 第三个参数为true/false，为捕获/冒泡，参数补给则默认false
一般都是冒泡
事件冒泡：当子触发事件后，它的祖先只要有该事件类型的事件函数，都会执行。
阻止冒泡：
子到祖先的所有该事件事件函数中：
event.stopPropagation()  有兼容性问题
无兼容性问题：event.cancelBubble 
事件冒泡的应用：事件委托（事件代理/事件委派）
只给父元素注册事件，子都不注册，当子触发事件后，通过事件冒泡执行父的事件函数，里面用event.target处理子。这样就只操作了一次DOM。

## 4.6 其他

```
//offset：动态获取元素距父元素的偏移（不带单位的数值）

//获取偏移
要求：父元素必须有定位（没有定位则以body为父），若没有父元素，则父是body（不用定位）
e.offsetTop  元素中心点距顶部
e.offsetLeft  元素中心点距左边,没有right和bottom

//获取元素宽高（包含widtj/height，内边距和边框，不包含外边距）
e.offsetWidh   e.offsetHeight

//获取父元素，若父元素没有定位或没有父元素，返回body
e.offsetParent 与e.parentNode区别实：parentNode不用定位

//e.offset与e.style区别
e.style只能获取行内样式，e.offset可获取任意的样式
e.style返回有单位的字符串，e.offest返回不带单位的数值
e.style的宽高只有width/height，不包含内外边距和边框
e.style可读写  e.offset是只读

//应用：模态框（可拖拽移动的盒子）
盒子鼠标按下事件，计算鼠标在盒子内坐标=鼠标坐标-(offset编译-offset宽高/2)
内嵌鼠标移动事件，行内样式left/top=鼠标坐标-鼠标盒子内坐标
全局document事件，鼠标弹起取消鼠标移动事件
```

```
//client：返回的都不带单位
e.clientWidth e.clientHeight  包含内边距，不包含边框和外边距
e.clientTop  e.clientLeft  上/左边框的大小
```

```
//scroll
e.scrollWidth e.scrollHeight 包括内边距不包括边框和外边距，而且，如果盒子内的内容超出了盒子的大小，会把超出的计算在内s
e.scrollTop e.scrollLeft  返回滚动后被卷去的那部分大小
```

# 四、BOM

BOM：浏览器对象模型
Window是浏览器的根对象，包括：document，navigator，location，history，screen，所以BOM包含DOM，window.document…的window.可省略
window是全局对象，多以全局变量和 全局函数都会鞭策window的属性/方法
同样，调用全局变量/全局函数，window.可省略
alert()也是window的方法

## 1 事件：

```
//面加载事件：
若引入js在html页面之前（页面未加载，js就无效了），需要将所有代码放在：
window.onload() = () => {//里面的代码在html页面完全加载完，才执行}
也可写成 window.addEventListener(‘load’,function(){})
多个onload事件，只执行最后一个

onload 页面所有内容，包括标签文本图片样式都加载完才触发
onDOMContentLoaded 当DOM加载完（即所有标签），就触发
pageshow 与onload基本一样，但是在火狐浏览器中，前进页面后，之前的页面会缓存，再后退不会触发onload，而pageshow可以

//窗口大小事件：
Onresize 浏览器窗口大小发生变化时触发
```

## 2 异步和定时器：

*异步：
JS是单线程的，是为了防止DOM冲突，默认是同步
同步：代码按顺序执行，只有执行完一行才会执行下一行
异步：当代码执行到异步代码时，会独立执行，不影响后面代码
异步是非常重要的，以此才能实现如时间，轮播图等
异步有定时器,事件,网络请求
虽然解决了同步问题，但是又带来了回调地狱
当异步中多重嵌套异步时，代码可读性差，又难以维护，可以通过ES6的Promise类解决。
回调函数：当达到异步任务的时机，就会回去调用的函数。

Js执行机制：
分为同步任务和异步任务
将同步任务（包括定时器函数本身）放入执行栈，将回调函数（事件回调/定时器回调/网络请求回调等）作为异步任务放入任务队列（又叫消息队列）。先执行同步任务，遇到了异步任务就把异步任务放入任务队列中且不执行，当所有同步任务都完成后，进入事件轮循：
到任务队列中，看是否有复合条件的异步任务，条件复合就把异步任务放到执行栈中执行。这个过程会一直重复，这就叫事件轮循。

*定时器：
window.定时器 window.可省略
setTimeout(function(){},xms)  延迟xms后执行，只执行一次
setInterval(function(){},xms) 每xms执行一次，重复执行
清除定时器：定义定时器时需要赋值给变量，才能清除
setInterval第一次执行会延迟xms，所以想要一开始就执行，可以在定时器外单独的同步执行一次里面的函数
clearTimeout(xxx)
clearInterval(xxx)

## 3 location对象

```
用来获取/设置/解析窗体的url
url：统一资源定位符
url格式：
protocol://host[:port]/path/[?query]#fragment
protocol：通信协议，如http
host：主机/域名，如www.baidu.com
port：端口号，http的默认端口是80
path：路径，/隔开，文件目录
query：参数，键值对，如 ?a=1&b=2
fragment：片段，常见于锚点链接

读写url： window.location  window.可省略
location.href 整个url 
location.host
location.port
location.pathname
location.search  query参数
location.hash 片段，即#后面的

location方法：
location.assign(‘url’)  跳转页面（也叫重定向），跳转后可返回原页面
location.replace(‘url’) 跳转，但无法返回
location.reload()  参数为空或false重新刷新页面，true为强制刷新
非强制刷新会缓存一些页面内容，速度快一点，强制刷新则全部重新加载，速度慢一点
```

## 4 navigation对象

```
存放浏览器的信息，可以知道是PC端的浏览器还是移动端的浏览器，由此可以知道显示PC端还是移动端页面
Navigator.userAgent.match()
但是代码比较复杂
```

## 5 history对象

```
跟浏览器的历史记录进行交互，保存了用户浏览过的地址
history.forward() 前进
history.back()  后退
history.go(x)  正数前进x步  负数后退x步
```

# 五、ES6-ES11

ES6↑兼容性问题：babel可以把ES6↑转化成ES5，解决兼容性问题。

## 1 ES6

### 1.1 let，const

let 变量     const 常量
var其实是JS设计上的缺陷，var没有块级作用域，会带来非常多的问题且解决很麻烦，而let有，以后尽量都用let。
块级作用域：for，if，函数等大括号里

```
let:
1、声明：let a  let a,b  let a=100  let a=12,b=[5,6],c={}
2、具有块级作用域
const：
1、const常量必须初始化，值初始化后不能修改
2、对于const修饰的对象/数组，对象/数组本身不能修改，但是对象的成员/数组元素可以增删改。
3、确定值不会变时，优先使用const（规范），常量名一把大写
4、具有块级作用域
```

### 1.2 模板字符串

```
1.声明：let str=`…`
`str`        `在tab键上方，字符串新写法，可以解析出换行，如：
`str1
str2`    等价于’str1\n’+’str2’
2、字符串拼接：
let str1=`hello`;
let str2=`${str1}world`
输出helloworld
3、模板字符串中，${xxx}，xxx可以是表达式，变量，函数，对象等
```

### 1.3 解构赋值

将数组/对象中的元素/属性一次赋值给多个变量，若x变量多于数组元素/变量名在对象中没有对应的属性，则x变量为undefine

```
数组解构：
var let const定义变量都行
const [.. .. .. ..]=数组名
与顺序有关，按顺序将数组的元素赋值给..变量
..变量可以设置默认值：..=..  当值为undefine时使用默认值
函数解构：实参 解构 形参 
对象解构：
const {属性名1，属性名2…} = 对象名
与顺序和取出数量无关，会根据属性名/方法名取出对象中的属性值/方法
取出后属性名/方法名作为const常量名
解构的变量可以设置别名：{变量:别名}，只有对象解构才能起别名
对象连续解构；
const {xxx: {aaa}或[aaa] }=obj 从obj解构出xxx对象或数组，再解构xxx中的aaa
```

### 1.4 对象属性方法的新写法

```
1)、es6对象中，属性名和方法名可以是表达式/函数，用[]包裹
2)、对象字面量的增强写法：
*属性：
const name=’lgx’;
const person={
name,      //等同于 name:name
}
*方法（vue中的方法，计算属性，过滤器也行）：
fun(){}  //等同于 fun:function(){}
```

### 1.5 新数据类型Symbol

```
七个基本数据类型：
ussonnb  undefine string symbol object null number boolean
①Symbol数据类型
  /*ES6新的基本数据类型，类似于字符层
  *值唯一，可用来解决命名冲突问题
  *无法运算与比较，只能用== != === !==比较
  *Symobole可以转为字符串，可转为布尔值且值为true
  *对象中用Symbol定义的属性不能遍历出来，但可用Reflect.ownKeys遍历出所有键名遍历出来*/
  //声明，注意symbol的值是不可见的
  let s0=Symbol()
  //里面的字符层并不是值，只是做一个说明，相当于注释，字符层相同的symbpl值也是不一样的
  let s1=Symbol('abc')
  //函数对象创建
  let s2=Symbol.for() //这样创建的两个symbol值一样，但与空字符串''创建的值不一样'
  let s3=Symbol.for('123') //这样创建，字符串相同，值就相同

  //应用：给对象添加独一无二的属性和方法
let obj={
  run:Symbol(),              //第一种
  [Symbol('sleep')]:function(){}  //第二种
}
obj.run=function(){}   s//与对象内的run是不同的

//Symbol内置属性，作用是作为对象的属性
如Symbol.hasInstance
作为对象的属性 [Symbol.hasInstance] : …
```

### 1.7 新运算符

```
扩展运算符 … 将数组转化成逗号分隔的列表
具备iterator接口的数据类型才可使用
const arr=[‘a’,’b’,’c’]
1、fun(…arr)        //传入了’a’,’b’,’c’三个字符串作为实参
2、let arr_arr=[…arr,…arr]      arr_arr为[‘a’,’b’,’c’,‘a’,’b’,’c’]
3、let arr_copy=[…arr]        拷贝
4、将伪数组（如querySelectAll得到的）转化为真正的数组
5. 使用第三方库的函数时，若不知道里面的回调函数有几个形参，可以这样查看有什么参数
xxx((...aaa) => {
  console.log(aaa)
})
```

### 1.8 新for循环和迭代器

```
for in 和 for of
for in    只能用来遍历数组，字符串，对象
for(var k in 数组名/字符串名/对象名)        //通常用k或key
{
console.log(k);         //k为每个数组或字符串的下标或对象属性名和方法名
console.log(数组串对象[k]);    //遍历每个数组/字符串元素或对象属性的值，不执行方法
}
遍历对象数组时，第一行获得下标，第二行获得各个对象。

for of与for in的区别就在于for of的i是数组/字符串元素的值,对象数组的对象实体。注意对象不能用for of
```

迭代器：
ES6提供了iterator接口，为不同的数据结构提供统一的访问机制。一种数据结构只要部署了interator接口，就能通过 for of 遍历
一般iterator接口是各数据结构的原型对象中的一个方法：
[Symbo.iterator] : function(){}

自带iterator接口的数据结构：
Array，String，Arguments，Set，Map，NodeList，typedArray（没有Object）

迭代器原理：
next()返回一个对象，value属性为当前成员的值，done属性为是否遍历完（true为遍历完），随后指向下一个成员
注意最后一个成员的done为false，继续指向下一个成员done才为true，value为undefine，表明遍历完成。
也就是，一个数据结构包括：起始位置-各成员-结束位置
过程：

* 创建一个指针对象指向该数据结构的起始位置

* 调用指interator接口的next()，使指针指向第一个成员

* 继续调用next()，遍历每一个成员，直到最后一个成员

* 此时指针指向最后一个成员，再调一次next()后，done为true，结束
  

```
let arr=[1,2]
let arrite=arr[Symbol.iterator]()
console.log(arrite.next()) //第一个成员
console.log(arrite.next()) //第二个成员
……
```



自定义遍历数据：
有一个对象o，需求是使用for of遍历o里面的arr的每一个值
虽然可以直接 for( I of o.arr ) 或其它方法进行遍历，但不符合面向对象的思想，此时是给o部署iterator接口

```
const o={
  name:'lgx',
  arr:[1,2,3],
  [Symbol.iterator](){
   let i=0 //索引
   let _this=this //_this指向o
   return { //return这个对象的里面的this指向return的这个对象，所以才需要_this，或用箭头函数
 next(){
   if(i < _this.arr.length)
   return {value:_this.arr[i++],done:false}
   else return {value:undefine,done:true}
 }
 }
 }
 }
for(i of o) console.log(i)
```

## 1.9 函数相关

#### 1.9.1函数形参

（1）rest参数
再形参列表的最后放一个（一定在最后） …args 作为数组接收实参
函数内args是数组名使用

（2）形参默认值
形参=值，当没有给该形参传入实参时，使用默认值
与对象解构配合使用时：
形参obj ---- 形参{.. .. .. ..}，..也可以设置默认值

#### 1.9.2 箭头函数

常用于作为形参
具名：const/let name=(形参列表)=>{函数体}
匿名：(形参列表)=>{函数体}

* 当形参只有一个时，小括号可以省略

* 当函数体只有一行时，大括号可以省略，注意省略后，会隐含return

* 箭头函数没有arguments

* 对象的构造函数声明写法，不能用箭头函数

* 箭头函数的this
  
  * 箭头函数的this是静态的，指向声明此箭头函数的那个对象的作用域，如对象o中声明了一个箭头函数f，则f的this指向o的作用域window
    
    * this指向无法修改
    
    * 一般代码中的this是指向window的
      但是箭头函数中的this指向最近的上一级，若在类obj中的箭头函数中，指向obj，若在普通函数中的箭头函数中，指向window
      但是若this在箭头函数中的普通函数中，指向window

#### 1.9.3 高阶函数

高阶函数指的是可以以用函数作为形参的函数。体现了函数式编程思想。
回调函数：自动遍历数组，以数组的每个值作为形参执行的函数。

JS三种常用的高阶函数：分别用来筛选，操作，汇总。
（1）filter()

```
let 型数组=原数组.filter( function(n){
  return 布尔值（变量/表达式）;
});
```



参数为回调函数，作用是：true时，将元素n加入新数组（用数组接收）

（2）map()

```
let 型数组=原数组.map( function(n){
  return 对n的操作（如n*2）;
});
```



参数为回调函数，作用是：对每个n执行操作，并返回给新数组（用数组接收） 

（3）reduce()

```
let 变量=原数组.reduce( function(pre,n){
  return 汇总（如pre+n 是计算数组元素值的和）;
},0);
```



第一个参数为回调函数，第二个参数为pre的初始化值，一般为0.
作用：pre保存上一次return的值，n为此次遍历的值，每次执行完汇总，将值返回给pre。（最终用一个变量接收）

（4）高阶函数有链式写法：

```
let 变量=原数组.filter( n => … ).map( n => … ).reduce( ( pre , n ) => … , 0 );
```

### 1.10 生成器

本质是一个函数,但是语法与传统函数完全不同，是es6提供的一个异步解决方案，进行异步编程。解决了回调地狱。
以前的异步解决方案是单纯使用回调函数。

定义：三种都一样

```
function * xxx(){} 
function* xxx(){} 
function *xxx(){}

//调用：生成器定义后是一个迭代器对象，所以
xxx().next() 
//或：
let x=xxx()
x.next()
```

yield语句 在生成器函数体中定义，将代码区域上下分割，n条yield语句将代码分割成n+1个代码块，每次调用next()都只执行当前代码块，然后将指针指向下一个代码块。

```
function * xxx(){
  console.log(111)
  yield '分割线1'
  console.log(222)
  yield '分割线21'
  console.log(333)
}
/*注意，这样调用必须将生成器赋值给一个变量，这样x.next()才是在同一个生成器内，而xxx().next()调用的话都是临时变量，都是在不同的生成器中，所以一般生成器最好赋值给一个变量*/
let x=xxx()
console.log(x.next())
console.log(x.next())
console.log(x.next())
//也可使用for of，这样调可不用将生成器赋值给变量
for(i of xxx()) console.log(i)
```



生成器函数参数：

* 生成器可以定义形参

* next()可传实参，生成器用 let x=yield 123 接收，x的值就是实参的值
   第n次调用的next，则第n-1个yield接收

应用：

```
//回调地狱，代码杂乱
//1s后输出111，再2s后输出222，再3s后输出333，共6s
setTimeout(()=>{
 console.log(111)
 setTimeout(()=>{
 console.log(222)
 setTimeout(()=>{
 console.log(333)
 },3000)
 },2000)
},1000)

//用生成器实现同样的功能
function * xxx(a){
 yield setTimeout(()=>{ //改成let xxx=yield ... 就能接收第二个next参数
 console.log(111)
 x.next() //若此时想传递参数，x.next(数据)，此时第二次调next，所以被第一个yield接收
 },1000)
 yield setTimeout(()=>{
 console.log(222)
 x.next()
 },2000)
 yield setTimeout(()=>{
 console.log(333)
 x.next()
 },3000)

}
let x=xxx()
x.next()
```

### 1.11 Promise

一种异步解决方案
用于封装异步代码，使得异步代码结构更加清晰

```
//举例，这里的异步使用setTimeout()举例
//格式 new Promise().then().catch()
//reject可以不传
new Promise((resolve,reject) => {
 setTimeout(()=>{
 //这里用来进行判断请求是否成功，成功则执行then，失败执行catch
 //都可以传递参数,对应的then，catch可以接收此参数
 if(…..) resolve()
 else reject('err')
 },1000)
}).then(() => {
 console.log(111)
 //嵌套下一层请求
 return new Promise((resolve,reject) => {
 setTimeout(() => {
 resolve()
 },1000)
 }).then(() => {
 console.log(222)
 })
}).catch((str) => {
 console.log(str)
})
//catch()可以不写，在then()中传入第二个回调函数即可代替catch()

/*
then()返回的也是Promise，所以可以then().then()这样链式调用
Promise的三种状态：等待（执行中），成功（执行resolve触发，后执行then），失败（执行reject后触发，后执行catch）
*/
```



简写：

* return new Promise()里面只有一个reslove或一个reject时，可以简写为：
  return Promise.reslove()  return Promise.reject()

* 仅reslove使用：当满足1时，且有参数，简写为：return 参数

* 仅reject适用：1可再简写为：throw 字符串  该字符串会作为参数传入catch
  PS：这里不管是return还是reslove，reject，当return/传入 变量+字符串后，下面then，catch使用该变量时，值就是 变量+字符层

Promise处理多个异步操作：
当一个请求需要多个子请求的结果时，是不好判断子请求的完成顺序的，代码写起来就复杂。但是promise方便很多。
all() 传入一个数组，当成功完成封装的所有请求时，再执行all().then()

```
Promise.all([
 new Promise(),
 new Promise(),
 ….
]).then( )
```



then里面的箭头函数的参数是一个数组（自己命名），该数组按顺序保存all封装的所有reslove的参数
由于封装的都是异步，所以all执行总时间就是执行最慢的那一个异步操作的时间。

## 1.12 新数据结构

#### 1.12.1 Set

Set 集合

成员的值是惟一的，有相同的会去重
具有iterator接口，可使用for of（遍历出每个元素） 和 ..

```
//声明
let set0=new Set()
let set1=new Set([1,2,3])

/*
Set本质是对象，具有属性和方法
size 元素个数
add(元素) 增
delete(元素) 删
has(元素) 查 存在返回true
clear() 清空
*/

//应用
//数组去重 (求交集/并集/差集时，为了效率一般先对数组去重)
let arr=[1,1,2,2,3]
let arr0=[...new Set([...arr])]

//求交集
let arr1=[1,1,2,2,3]
let arr2=[3,4,4,5,5]
let arr3=[...new Set([...arr1])].filter( i => new Set([...arr2]).has(i))

//求并集
let arr4=[...new Set([...arr1,...arr2])]

//求差集 (a-b a有但b没有)
let arr5=[...new Set([...arr1])].filter( i => !new Set([...arr2]).has(i))
```

#### 1.12.2 Map

键值对的集合，键是唯一的，若增加了相同的键，会覆盖原有

键和值都可以是任何数据类型，也可以函数

有iterator接口，可使用for of（遍历出每个键值对） 和 ...

```
//声明
let m=new Map()

/*Map本质是对象，具有属性和方法
size 键值对个数
set(key,value) 增，不像c++中set相同的键会自动+1，可能有其他map方法
get(key) 返回对应的key
delete(key) 删
clear() 清空
*/
```

#### 1.12.3 Class

class里的this永远不会指向window，硬要指向window也会指向undefine

```
//声明，class不会被提升
class c {
 //构造函数定义属性，它在new时调用
 constructor(a){
 this.a=a
 this.b=2
 }
 a = 10 //定义属性
 //定义方法，必须是这种简写的写法，非静态/静态this为实例对象/类本身
 func(){}
 //静态属性/方法，实例化对象无法调用，只能类本身调用
 //未被static修饰的职能new后调用
 static c=5
 static cc(){}
}
//实例化类
let a=new c(123)

//类继承：
//父类
class fa {
 constructor(a){
 this.a=a
 }
 xxxfa(){}
}
//子类继承父类
class ch extends fa {
 constructor(a,b,c){
 //子类中必须有super()，才能使用this
 super(a) //调用父类的constructor函数
 this.b=b
 this.c=c
 }
 xxxch(){
 //子类的新方法中，用 super.xxxfa() 可以调用父类的方法
}
 //重写，重写后子类以后调用的就是重写的方法
 //重写的方法内是无法用super()调用父类的同名方法的
//若未重写，子类对象调用父类方法实际是自动 super.xxxfa()
 xxxfa(){
 //super.xxxfa()  
 //重写的带am
}
}
//实例化子类,可调用子类和父类中的属性和方法
let chi=new ch(1,2,3)

类属性的存取器：
class c {
 //定义了a的存取器，就有了a这个属性，不用另外定义
 get a(){
 return 123 //类实例对象可以直接 obj.a 来调用这个get,获得属性a的值
 }
 set a(newVal){
 //操作 //也是直接 obj.a = 5 会调用set，来修改值
 }
}
```

### 1.13 其他

#### 1.13.1 数值相关

Number.EPSILON   js表示的最小精度
作用：浮点数运算
浮点数运算是有误差的，0.1+0.2 != 0.3
if(Math.abs(a-b)<Number.EPSILON) 若两个浮点数a-b的值小于最小精度，就可以认为他们相等

进制：
0b1010 二进制
0o777  八进制
123  十进制
0x666 十六进制

Number.isFinite(x)  x为有限数/无限数返回ture/false
Number.isInteger(x)   x为整数返回true
Number.parseInt()  Number.parseFloat()
Number.isNaN(x)   x是/不是NaN返回true/false，注意只有NaN才是true
与window.isNaN()区别：
window.isNaN(x) x是undefine，String，Object，NaN都返回true，因为他会自动对数据进行转换
Number.isNaN(x) x只有NaN才返回true，因为它不对数据进行转换。

Math.trunc(x)  将x的小鼠部分抹掉
Math.sign(x)   x为正数/负数/0返回1/-1/0

#### 1.13.2 对象方法的扩展

Js的数组，字符层，Set，Map本质都是对象，所以这些方法都可以调用

* 数组，字符层可以正常调用

* Set，Map可以调，但结果为空


Object.keys(x)  将x对象的所有key以数组形式返回
Object.values() 将x的所有value以数组的形式返回
Object.entries(x) 返回一个对象数组，每个对象里是一对 key和value的数组
Object.is(a,b) 判断a，b是否完全相等，与===不同的是两个NaN比较为true
Object.assign(a,b) 合并a，b两个类，有重复的key则b的value覆盖a的value，常用于配置的合并
Object.setPrototypeOf(a,b)  将b设置为a的原型对象
Object.getPrototypeOf(a)    返回a的原型对象

#### 1.13.3 数组方法的扩展

```
let a=[1,2,3,4]

//遍历数组，当所有值都符合条件时，才返回true v值，i索引，arr原数组
let res0=a.every((v,i,arr) => v>=2)

//遍历数组，当有一个值符合条件时，就返回true v值，i索引，arr原数组
let res1=a.some((v,i,arr) => v>=2)

//遍历数组，返回由符合条件的值组成的数组，不改变原数组
let arr0=a.filter(i => i>=2)

//遍历数组，0为pre的初始值，pre为上一次return的值，v为值，，i为索引，、、
//arr原数组，常用来汇总
let res2=a.reduce((pre,v,i,arr) => pre+v ,0)
let res3=a.reduceRight((pre,v,i,arr) => pre+v ,0) //从右边开始遍历

//遍历数组，查找数组中是否存在该值，存在返回true，形参：查找的值，开始//索引，结束索引
let res4=a.includes(4,0,3)

//遍历数组，返回符合条件的值，一旦找到就结束遍历并返回值，找不到返回//undefine，形参v值，i索引，arr原数组
let res5=a.find((v,i,arr) => v>=2)
let res6=a.find((v,i,arr) => v>=2) //返回的是索引值

//改变原数组，形参：值，开始索引，结束索引，用值替换掉开始到结束索引(左//闭右开)的值
a.fill(5,0,3)

//复制数组
let aCopy=Array.from(a)
```

#### 1.13.4 模块化

没有模块化时，引入多个js文件会有全局变量的冲突，可以用闭包，但是闭包后必须导出，否则无法复用。
模块化的核心：导出，导入
常见模块化规范：ES6，AMD，CMD，CommonJS
各种产品使用的模块化规范：
AMD：requireJS使用
CMD：seaJS
CommonJS：nodejs，Browserify使用

引入：



```
<script type="module" src="..."></script>
或
<script type="module">
  import ... from '...'
</script>
```

但是这样会有报错，而在实际开发项目中也不会使用这种方式，项目中会将模块化代码用babel转成ES5代码整合成main.js文件，html只引入这个js文件。

```
<script src="main.js"></script>
```



导出语法：

```
export {
 …
}
//或,定义变量/函数/类的最前面加export
//或
export default 定义好的变量等  //default 只能有一个
```



导入语法：
导入的路径规则;
*在当前文件夹或在当前文件夹的一个文件夹内 最前面 ./ 下一级用 /
*在上一级文件夹 最前面 ../ 多级就用多个 ../
*导入包，直接写包名

123

```
Import {…} from ‘路径’

//或
Import * as 别名 from ‘路径’  //别名.调用

//或
Import 别名 from ‘路径’ //与default配合
```



使用CommomJS的NodeJS模块化语法：
导出语法：

```
module.exports={
 变量名或函数名
}
```



导入语法：

```
//路径规则与ES6一样
const {变量名或函数名} = require(‘路径’)
```

#### 1.13.5 babel：

js编译器，将ES6以上代码，typescript代码转化成ES5代码。

## 2 ES7

arr.includes(参数)  若数组中有该参数，返回true，否则false（以前的indexOf有则返回下标，否则返回-1）
新运算符  **  幂运算  2**5  2的5次方

## 3 ES8

### 3.1 async和await

新的异步解决方案，以类似同步的方式使用异步
（1）async

用来声明async函数，该函数一定会返回一个Promise对象，return的值是reslove()的参数，根据async函数返回的Promise的成功或失败状态，可以使用.then()和.catch()

```
async function a(){
 return 123
}
a().then(val => {
 console.log(val) //输出123
})
//上述代码相当于
new Promise((resolve,reject) => {
 resolve(123)
}).then(val => {
 console.log(val) //输出123
})
```



若async函数的返回值为：

* *该函数没有return 或只有return，Promise的值为undefine  状态为成功

* 该函数return xxx  Promise内容为xxx 状态为成功 （xxx为非Promise对象）

* 该函数return Promise对象 a，a成功/失败则返回的成功/失败、值为成功/失败的值

* 该函数内跑出异常，返回的Promise状态为失败



（2）await

后面可以放一个表达式称为await表达式（一般为Promise对象）
await必须放在async函数里面，但async函数里不一定要有await
await语句的返回结果：若后面Promise成功/失败，返回成功的值/跑出异常（可通过捕获异常得到失败的值）

```
const p = new Promise((resolve,reject) => {
 resolve(321)
 //reject(456)
})
async function a(){
 try{
 let val = await p //val值为321
 console.log(val)
 }
 catch(e){
 console.log(e) //e的值为456
}
}
a()
```



awsait失败的另一种写法，返回数组

```
const [err,res] = await xxx.catch(err => err)
```

### 3.2 对象方法的扩展

Object.keys(obj)  //返回一个数组，值为对象中所有的键
Object.values(obj)  //返回一个数组，值为对象中所有的值
Object.entries(obj)  /*返回一个数组，每个元素的值为对象中所有的键和值组成的数组，第一个值为键，第二个值为值*/
entries可以很方便的用对象生成一个Map
let m = new Map(Object.entries(obj))

Object.getOwnPropertyDescriptors(obj) /*返回obj的属性的描述对象（描述对象就是用Object.create()创建出来的对象的那种格式，内容有是否可枚举/可删除等），*/
Object.getOwnPropertyDescriptors()  的主要作用是实现更深层次的对象拷贝，把是否可枚举/可删除等都拷贝了。

## 4 ES9

### 4.1 对象rest参数和扩展运算符

为对象提供了像ES6数组一样的rest参数和扩展运算符

（1）对象的rest：

```
//…hobbit 会保存除了name，age之后的所有参数，保存为一个对象
function a({name,age,...hobbit}){
 console.log(name)
 console.log(age)
 console.log(hobbit)
}
a({
 name: 'asd',
 age: 20,
 hobbit1: 'sleep',
 hobbit2: 'run',
 hobbit3: 'eat'
})
```

（2）对象的扩展运算符：

```
let a = {
 name: 'asd',
 age: 20
}
let b = {
 ...a,
 sex: '男'
}
console.log(b)
```

### 4.2 正则扩展

在ES5中就可以使用正则表达式了



创建：
字面量创建（编译时就创建）；let reg = /正则/
构造函数创建（运行时才创建）：let reg = new RegExp(‘正则’)
匹配模式（也叫修饰符，在正则规则之外的附加规则）：
不加修饰符默认情况区分大小写，只匹配第一个结果
g：找到所有结果   i：不区分大小写      m：每行分别匹配  
/正则/I    new RegExp(‘正则’,i)
可以同时使用多个模式：
/正则/gmi
使用正则：
正则表达式.test(字符串)    //看是否有匹配结果，返回布尔值，
正则表达式.exec(字符串)   //找不到返回null，找到则回结果和结果的第一个字符在原字符串的下标，注意只能找到第一个匹配的结果(g也不行)但是是数组
字符串.search(正则)  //找不到返回-1，找到返回结果的第一个字符在原字符串的下标，不返回结果且只匹配第一个找到的。功能与indexOf()相同，只是indexOf参数为字符串，search()参数为正则
字符串.match(正则)   //普通模式与exec一样，g下会匹配所有结果但不再返回下标，若想返回所有结果且保留下标信息，可以：
Js的正则有lastIndex属性，保留上一次调用exec的结果，所以可以：
while((res = reg.exec(‘…’)))  console.log(res)  //lastIndex属性只有在g模式才有效， 
字符串.replace()   字符串.split()  的参数也可以是正则
有些需求需要多个正则配合，将多个正则放到数组中，用every()，全真才真，如：
密码由数字和字母组成，限制6到10位，且必须包含大写字母的数字

```
let reg = [
 /[a-zA-Z0-9]{6,10}/,
 /[A-Z]/,
 /[0-9]/
]
console.log(reg.every( r => r.test(密码)))
```



js内置对象RegExp

RegExp会保存上一次使用正则的分组的匹配结果，如：

```
let reg1 = /xxx/, reg2 = /yyy/
console.log(/(x+)/.test('xxx5x')
console.log(RegExp.$1)  //结果字符串xxx
console.log(/(y+)/.test('xyyxxxx')
console.log(RegExp.$1)  //结果为字符串yy
```

ES9正则

1.对分组可进行命名：左括号后加?<别名>  如 \w+(?<num>\d+)
exec和match，matchAll获得的匹配结果可用  匹配结果.groups.num 获得该分组
2.ES9增加了ES5不支持的负向后行断言，正向后行断言
3.新的匹配模式：dotAll模式（使用s），使得.包括换行符



## 5 ES10

（1）Object.fromEntries(xxx) 

用二维数组创建一个对象
xxx如 [[k1,v1],[k2,v2]]
Object.entries()返回的和Map就是这种形式，既可以将Map转为对象

（2）字符串方法噶新增

trimStart，trimEnd

```
let str=’ 123 ’
console.log(str.trim()) //ES5的方法，清空两侧空格
console.log(str.trimStart()) //清空左侧空格
console.log(str.trimEnd()) //清空右侧空格
```

（3）数组方法新增 

flat() flatMap() ,用于数组降维

```
let arr2 = [1,2,[3,4]]
let arr3 = [1,2,[3,4,[5,6]]]
console.log(arr2.flat()) // [1,2,3,4] 二维转化一维
console.log(arr3.flat()) // [1,2,3,4,[5,6]] 三维转二维
console.log(arr3.flat(2)) // [1,2,3,4,5,6] 三维转一维，2表示深度2,3-1=2，空参则默认为1

let arr = [1,2,3]
console.log(arr.map(item => item * 10))
console.log(arr.map(item=>[item*10,item*20]))  
console.log(arr.flatMap(item => [item * 10,item * 20])) //相当于map之后使用flat()
```

（4）Sysbol新增description

获取Sysbol的描述字符串

```
let a = Symbol('123456')
console.log(a.description) //输出123456
```

## 6 ES11

（1）class增加私有属性

类外不可调用，类内可以调用，用#声明，类内调用时，不能少了#

```
class a {
 name;
 #age;
 constructor(name,age){
 this.name = name
 this.#age = age
 }
 getAge(){
 console.log(this.#age)
 }
}
let aaa = new a('lgx',20)
console.log(aaa) //看不到age
console.log(aaa.name,aaa.age) //无法调用私有属性，结果为undefine
aaa.getAge() //通过类内的方法噶来则可以调用
```

（2）6.2 Promise.allSettle(xxx)

xxx为由Promise对象组成的数组
它会返回一个成功的Promise对象，成功的值为一个对象数组，对象数组中的每一个对象保存了xxx各个Promise的状态和对应的值

```
let p1 = new Promise((resolve,reject)=>{
 resolve(1)
})
let p2 = new Promise((resolve,reject)=>{
 resolve(2)
})
let p3 = new Promise((resolve,reject)=>{
 reject(3)
})
let res = Promise.allSettled([p1,p2,p3])
res.then( r => {
 console.log(r)
})

/*输出
[
 { status: 'fulfilled', value: 1 },
 { status: 'fulfilled', value: 2 },
 { status: 'rejected', reason: 3 }
]
*/
```



与all()的区别：all(xxx)中，
若xxx数组中的Promise有一个失败，那all()返回的Promise就失败，失败的值为出错的那个Promise的值，

```
Promise.all([p1,p2,p3]).catch( r => {
 console.log(r)
}) 
//输出 3
```



只有全部成功时，all()才成功，成功的值为各个Promise成功的值的数组

```
Promise.all([p1,p2]).then( r => {
 console.log(r)
}) 
//输出 [1,2]
```

（3）可选链操作符 ?.

语法 obj?.属性 当obj存在时，才会调用属性，防止出现 undefined.属性 的情况

```
/*
若node环境中报错，则需要安装依赖
npm install @babel/plugin-proposal-optional-chaining --save-dev
*/

function a(config){
 //原本必须这样做，通过短路运算判断是否传入了这个对象或属性
 let userName = config && config.db && config.db.userName
 console.log(userName)
 /* console.log(config.db.passWord) 报错，没有传入passWord，
 也没有用短路运算判断，不能有 undefine.属性 这种错做*/
 console.log(config?.db?.passWord) //没有传入passWord输出undefine，但是不报错，也不用短路运算
}
a({
 db:{
 userName: 'lgx'
 }
})
```

（4）动态import

ES6的是静态import，这里的动态import实现按需加载（懒加载）

```
import(‘…’).then(r=>{
 //r为导出的东西
})
const a = import(‘xxx’) //路由懒加载
```

（5）6.5 新数据类型，大整型：BigInt

```
let a = 123n //声明
let b = BigInt(567) //将Number的整数转为BigInt，浮点数不能转
let c = 123n + 456n //BigInt只能与BigInt运算
let a=Number.MAX_SAFE_INTEGER + 1 //Number能表示的最大整数
console.log(BigInt(a+10)) //再大就要转为BigInt
```

（6）新关键字：globalThis

始终指向全局环境（浏览器是window，node是global）

字符串使用正则的新方法：
str.matchAll(reg) 解决了match在全局模式下不显示全部信息的情况



end
