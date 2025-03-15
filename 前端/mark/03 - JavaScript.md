# 一、ES5

JS 是面向对象的脚本语言，组成：

* ECMAScript（ES，JS的语法）

* DOM（页面文档对象模型，对标签进行操作实现动态效果）。

* BOM（浏览器对象模型，操作浏览器窗口）

JS 书写位置：

* 行内式，标签内书写 事件=””

* 内嵌式，<script>JS代码</script>

* 外部式，<script src=”xxx.js”>此处不能写代码</script>，

（1）注释、输入输出

```
// 单行注释
/* 多行注释 */
/**
 * 文档注释
 */

// 单引号、双引号都可以，分号加不加都可以
var str = "asdf";

// 输入
// var a = prompt("请输入");

// 输出，浏览器有时候输出时机不一定对，需要注意
var aaa = [{ a: 123 }];
// 可能有时候会输出修改后的 456
console.log(aaa);
aaa[0].value = 456;
```

（2） 变量，数据类型，类型转换，运算符

变量、数据类型：

```
// 变量
var a = 1;
// 等价于 window.b = 2;
b = 2;
// undefined
var c;
// 命名
var $a_1;

/**数据类型
 * 基本数据类型：Number String Boolean null undefined （ES6 以上还有 Symbol BigInt）
 * 引用数据类型：Object（Array、Function 等都是 Object）
 * 字面量：如 {a: 1}
 * undefined 和 null 的区别：
   * undefined 不是关键字，而 null 是
   * undefined 表示无值，null 表示空引用
   * 转为 number ，undefined 是 NaN ，null 是 0
   * typeof ，undefined 时 undefined ，null 是 Objct
 */
var t1 = 123;
var t2 = "asdf";
var t3 = true;
var t4 = null;
var t5 = undefined;
var t6_obj = { a: 1 };
var t6_arr = [123, "asdf", true];

// JS 是弱类型语言，赋值可以使其他数据类型
t1 = true;

// Number 可以是整数、小数等
var n = 3.1415926;
// NaN 表示非数字
var nan = NaN;
// 保留 2 位小数
console.log(n.toFixed(2));
// 最大值、最小值
console.log(Number.MAX_VALUE, Number.MIN_VALUE);

// 4 123
console.log("asdf".length, 123 + "");
// 访问 String
var str = "asdf";
console.log(str.charAt(0), str.charCodeAt(0), str[0]);
```

循环引用，自己引用了自己：

```
var obj1 = { a: 1 };
var obj2 = { a: 2, myself: obj1 };
```

判断数据类型：

```
// "number" ，缺点是 null，Symbol 和引用类型都判断为 object ，而函数又单独判断为 function
console.log(typeof 123);

// true 判断是否在原型链上可以找到
console.log({ a: 1 } instanceof Object);

// true ，判断是否是数组
console.log(Array.isArray([]));

// "[object Null]" ，最实用，可以判断所有数据类型
console.log(Object.prototype.toString.call(null));
```

类型转换：

```
// 隐式类型转换
console.log("asdf" + NaN);
console.log("3.14" - 2, "6" / 3);

// 强制类型转换
var n = 1;
var str = "3.14";
console.log(n.toString(), String(n));
console.log(Number.parseInt(str), Number.parseFloat(str), Number(str));

// 都是 false
console.log(Boolean(null), Boolean(undefined), Boolean(NaN), Boolean(""));

// [] 隐式是 false ，[] {} 隐式、强制都是 true
console.log(Boolean([]), Boolean({}));
console.log(false == [], false == {});
```

运算符：

中断运算的运算结果是中断你的结果，而不是 Boolean ：

```
// 123 456
console.log(true && 123);
console.log(false || 456);
```

== 只比较 value ，而 === 还比较数据类型：

```
// true false
console.log("123" == 123, "123" === 123);
// false true
console.log("123" != 123, "123" !== 123);
```

（4）in运算符

判断 key 是否存在于 Object 中，会涉及判断到原型上：

```
var arr = [5, undefined, 7];
var obj = { a: 1 };
Object.prototype.c = 123;

// true ，key 即 index ， 0 1 2 都是 true ，3 就是 false 了
console.log(0 in arr);

// true true
console.log("a" in obj, "c" in obj);
```

其他和 C 一样。

## 3 流程控制

使用循环时，需要注意var会被提升成全局变量（闭包或let解决）

此外，js有特有的循环forEach，只能用来遍历数组、Set、Map，无法用来遍历对象。

```
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
3 forEach的返回值为undefined
4 对每个item的操作会修改原数组
*/
```

for...in...循环

需要特别注意，无论遍历的是数组，对象还是属性的键类型不为string的对象，i的类型都是string

可以遍历出原型上的自定义属性/方法。

无法遍历Set，Map。

```
for(var k in xxx){
  console.log('key',k);         
  console.log('value',xxx[k]);    
}
```

其他与C语言一样

## 4 函数

若形参为基本类型，则传递值，若形参为引用类型，则传递引用（地址）

JS没有类型检测机制，如形参为字符串，实参为数值，却不会报错（缺陷）

形参不加var，不指定数据类型：

调用时可以传递任意类型的实参，基本/引用/函数等，实参是函数时，是将形参，函数体传进来

```
/声明
//具名函数
function fun1(){}

//匿名函数，没有函数名,fun2只是保存这个函数的地址，这样定义匿名函数可以通过变量名调用
//其他匿名函数有立即执行函数、回调函数等
var fun2  = function(){}


//调用：
fun1()
fun2()
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

（5）形参默认值：
可以给形参设置默认值，函数体中
var a = 形参 || 默认值

（6）立即执行函数：

```
(function(形参){})(实参)
(function(形参){}(实参))
不用调用，这样写会立即执行
同时，函数内部的var会变成局部变量，只在该函数中有效，这就是闭包，解决了var的作用域问题。
当整个js文件都在立即执行函数中时，引入多个js文件就不会产生变量名冲突的问题。
```

## 5 对象

### 5.1 创建对象：

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

### 5.2 调用对象，添加属性方法

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

### 5.3 Object

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

// 这种定义叫做属性描述符
Object.defineProperty(objname,'key'或变量,{
 set(value){//一旦修改值，就回调这个函数，value拿到了修改的值，一般通过value赋值给要修改的属性}
 get(){//一旦访问值，就回调这个函数，一般要return访问结果}
})
```

Object，Array等原型上的方法都是基于自己的，如果要给其他的对象/数组等用需要call改变this，如：

```
let arr = [1,2];
console.log(Object.prototype.toString())         //'[object Object]，判断了Object原型的类型'
console.log(Object.prototype.toString.call(arr)) //'【object Array】'
```

### 5.5 常用内置对象

查阅文档：https://developer.mozilla.org/zh-CN/
非构造函数直接可以使用，而构造函数需要var objname=new 对象名();

#### 5.5.1 Math

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

#### 5.5.2 Date()

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

#### 5.5.3 Array()

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

//若数组为多维数组，则转化后得到的字符串是一维数组的形式
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

#### 5.5.4 String

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

## 6 js使用正则表达式

正则表达式的内容详见相关笔记。

创建：

```
//字面量创建（编译时就创建）
var reg = /正则/;
//构造函数创建（运行时才创建）
var reg = new RegExp(‘正则’);
```

匹配模式（也叫修饰符，在正则规则之外的附加规则）：

```
//不加修饰符默认情况区分大小写，只匹配第一个结果
var a = /aaa/;

//g：找到所有结果 i：不区分大小写 m：每行分别匹配
var b = /正则/i;
var c = new RegExp(‘正则’,i);

//可以同时使用多个模式：
var d = /正则/gmi;
```

使用正则进行字符串匹配：

```
var str = 'aaa';
var reg = /a/;

//test，看是否有匹配结果，返回布尔值
console.log(/aaa/.test(str));
console.log(a.test(str));

/*exec
找不到返回null，找到则回结果和结果的第一个字符在原字符
串的下标，注意只能找到第一个匹配的结果(g也不行)，匹配结果是一个元素的数组
*/
console.log(/aaa/.exec(str));

/*search
找不到返回-1，找到返回结果的第一个字符在原字符串的下标，
不返回结果且只匹配第一个找到的。功能与indexOf()相同，
只是indexOf参数为字符串.
*/
console.log(str.search(reg));

/*match
普通模式与exec一样，g会匹配所有结果但不再返回下标.
*/
console.log(str.match(reg));

//Js的正则有lastIndex属性，保留上一次调用exec的结果，所以可以：
//lastIndex属性只有在g模式才有效，
//若想返回所有结果且保留下标信息，可以：
var res;
while((res = //g.exec(str))) 
  console.log(res);
```

配合正则进行字符串替换：

```
onsole.log('aba'.replace(/b/,'a'));  //'aaa' 
```

配合正则进行字符串转数组：

```
console.log('aba'.split(/b/));  //['a','a']
```

有些需求需要多个正则配合，将多个正则放到数组中，可以配合ES6的every()，如：
密码由数字和字母组成，限制6到10位，且必须包含大写字母和数字

```
var reg = [
 /[a-zA-Z0-9]{6,10}/,
 /[A-Z]/,
 /[0-9]/
]
console.log(reg.every( r => r.test(123456)))
```

js内置对象RegExp

RegExp会保存上一次使用正则的分组的匹配结果，如：

```
var reg1 = /xxx/, reg2 = /yyy/
console.log(/(x+)/.test('xxx5x')
console.log(RegExp.$1)  //结果字符串xxx
console.log(/(y+)/.test('xyyxxxx')
console.log(RegExp.$1)  //结果为字符串yy
```

# 二、Web API

## 1 DOM

DOM，文档对象模型，使 JS 可以操作 HTML。

DOM树：整个html页面是一个 DOM 树，根元素是 \<html\>，叫文档 document ，每一个html 标签，叫元素 element ，所有页面内容，包括每个标签/属性/文本/注释等，叫节点 node 。

### 1.1 基本操作

（1）获取元素

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <div id="app"></div>
    <div class="box"></div>
  </body>
  <script>
    // id 只返回一个，tag、class 返回 HTMLCollection
    var app = document.getElementById("app");
    var div = document.getElementsByTagName("div");
    var box1 = document.getElementsByClassName("box");

    // <html> <body>
    var html = document.documentElement;
    var body = document.body;

    /**html5 新特性，必须加上 # .
     * querySelector() 只返回找到的第一个
     * querySelectorAll() 返回伪数组
     */
    var box2 = document.querySelector(".box");
    var boxArr = document.querySelectorAll(".box");

    console.log(app);
    console.log(div);
    console.log(box1);
    console.log(html);
    console.log(body);
    console.log(box2);
    console.log(boxArr);
  </script>
</html>
```

（2）读写文本，属性、样式

文本、原生属性：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <div class="box1"></div>
    <div class="box2"></div>
    <input class="inp" type="text" value="asdf" />
  </body>
  <script>
    var box1 = document.querySelector(".box1");
    var box2 = document.querySelector(".box2");
    var inp = document.querySelector(".inp");

    // 读写文本、html
    box1.innerText = "123";
    box2.innerHTML = "<p>456</p>";
    console.log(box1.innerText, box2.innerHTML);

    // 读写原生属性
    inp.disabled = true;
    inp.value = 123;
  </script>
</html>
```

自定义属性：

为了和原生属性区分，建议加上 data\- ：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <div class="box" data-box-id="1" data-box-type="box"></div>
  </body>
  <script>
    var box = document.querySelector(".box");

    // 读写自定义属性，原生属性
    console.log(box.getAttribute("data-box-id"));
    box.setAttribute("data-box-id", "2");
    console.log(box.getAttribute("data-box-id"));

    // 删除自定义属性
    box.removeAttribute("data-box-id");
    console.log(box.getAttribute("data-box-id"));

    /**html5 新增
     * 自动加上 data-
     * data-xxx-yyy 得到 xxxYyy
     */
    console.log(box.dataset["boxType"]);
    console.log(box.dataset.boxType);
  </script>
</html>
```

样式、类名：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .box {
        font-size: 20px;
      }
    </style>
  </head>
  <body>
    <div class="box">123</div>
  </body>
  <script>
    var box = document.querySelector(".box");

    // 读取任意属性
    console.log(getComputedStyle(box).fontSize);

    // 读写行内样式
    console.log(box.style.fontWeight);
    box.style.backgroundColor = "red";

    // 修改 class
    box.className = "cls1 cls2 cls3";
    console.log(box.className);

    // html5 新增，单独操作 class
    box.classList.add("cls4");
    box.classList.remove("cls4");
    // 切换，即存在就删除，不存在就添加
    box.classList.toggle("cls5");
    console.log(box.classList);
  </script>
</html>
```

（3）节点操作

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <div class="box">
      <div class="item"></div>
      <div class="item"></div>
      <div class="item"></div>
    </div>
  </body>
  <script>
    var box = document.querySelector(".box");
    console.log(box.nodeType);

    // 获取子 node 数组，node 包括元素、属性、文本等
    var itemsNode = box.childNodes;
    var firstNode = box.firstChild;
    var lastNode = box.lastChild;
    console.log(itemsNode[0].nodeType, firstNode.nodeType);

    // 获取子 element
    var items = box.children;
    var first = box.firstElementChild;
    var last = box.lastElementChild;
    console.log(items[0].nodeType, first.nodeType, items.length);

    // 父 node
    console.log(first.parentElement, first.parentNode);

    // 获取兄弟
    var nestNode = items[0].nextSibling;
    var nestElement = items[0].nextElementSibling;
    var preNode = items[1].previousSibling;
    var preElement = items[1].previousElementSibling;

    // 创建、添加 element
    var p1 = document.createElement("p");
    var p2 = document.createElement("p");
    p1.innerText = 123;
    p2.innerText = 456;
    box.appendChild(p2);
    box.insertBefore(p1, items[1]);

    // 删除
    box.removeChild(items[items.length - 1]);

    // clone，无参只拷贝元素，不拷贝文本等信息；true 拷贝全部
    var newBox = box.cloneNode(true);
  </script>
</html>
```

### 1.2 事件

事件三要素：事件源、事件类型、事件函数。事件函数的 this 指向事件源。

（1）绑定

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <div class="box1">123</div>
    <div class="box2">456</div>
  </body>
  <script>
    var box1 = document.querySelector(".box1");
    var box2 = document.querySelector(".box2");
    var box3 = document.querySelector(".box3");

    function myEvent(e) {
      console.log(this, e);
    }

    // 绑定
    box1.onclick = myEvent;
    box2.addEventListener("click", myEvent);

    // 可以在 JS 中手动触发事件
    box1.click();
    box2.click();

    // 删除
    // box1.onclick = null;
    // box2.removeEventListener("click", myEvent);
  </script>
</html>
```

（2）常见的事件类型

鼠标事件

| click       | 单击             |
| ----------- | -------------- |
| dblclick    | 双击             |
| mousedown   | 鼠标按下           |
| mouseup     | 鼠标弹起           |
| mounseenter | 鼠标经过，经过子盒子时不触发 |
| mouseleave  | 鼠标离开，离开子盒子不触发  |
| mouseover   | 鼠标经过，经过子盒子时也触发 |
| mouseout    | 鼠标离开，离开子盒子也触发  |
| mousemove   | 鼠标移动           |

键盘事件

| keydown  | 按键按下，按键按着不放就一直触发，可识别所有键  |
| -------- | ------------------------ |
| keypress | 按键按下，按键按着不放就一直触发，不能识别功能键 |
| keyup    | 按键弹起                     |

注意事项：

* event.keyCode 可获得按键码，up，down 不区分大小写，press 区分。通过event.keyCode 可实现对特定键的监听

input 事件

| focus | 获得焦点 |
| ----- | ---- |
| blur  | 失去焦点 |

form事件：

| submit | 提交  |
| ------ | --- |
| reset  | 重置  |

表单通用事件（部分表单不能用）：

| input   | 值变化时触发，在修改完并失去焦点后才触发 |
| ------- | -------------------- |
| change  | 值变化时触发，修改的时候实时触发     |
| invalid | 非法输入时触发，可自定义非法输出信息   |

其他事件

textmemu，鼠标右键菜单事件，常应用与阻止右键弹出菜单：

```
document.addEventListener("contextmenu", function (e) {
  e.preventDefault();
});
```

selectstart，选中文本时触发，常应用于阻止选中文本：

```
document.addEventListener("selectstart", function (e) {
  e.preventDefault();
});
```

触屏事件

移动端手指触屏触发

| 事件          | 说明         |
| ----------- | ---------- |
| touchstart  | 手指触屏       |
| touchmove   | 手指移动       |
| touchend    | 手指弹起       |
| touchcancel | 触屏事件被取消时触发 |

（3）事件对象

通用：

| 属性/方法                   | 说明                                                                                    |
| ----------------------- | ------------------------------------------------------------------------------------- |
| event.type              | 事件类型                                                                                  |
| .event.preventDefault() | addEventListener中阻止默认行为，如a的跳转，button的提交。如果是on...中，则改成event.returnValue 或 return false |
| event.stopPropagation() | 阻止事件冒泡                                                                                |

鼠标事件对象：

鼠标坐标是右边下边为正。

| 属性                            | 说明                      |
| ----------------------------- | ----------------------- |
| event.offsetX 和 event.offsetY | 当前鼠标距离触发事件的元素边缘的距离      |
| event.clientX 和 event.clientY | 当前鼠标距浏览器视口边缘的距离         |
| event.pageX 和 event.pageY     | 当前鼠标距页面边缘的距离，即包括滚动卷去的距离 |
| event.screenX 和 event.screenY | 当前鼠标距电脑屏幕边缘的距离          |

### 1.3 offset，client，scroll

（1）offset

只读属性，获取结果是 number ，宽高是 border + padding + content ，偏移是 border 外部距最近非 static 定位的块盒祖先的 content 边缘：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      * {
        margin: 0;
        padding: 0;
      }

      .container {
        position: relative;
        margin: 100px;
        border: 1px solid #000;
        padding: 10px;
        width: 300px;
        height: 300px;
      }

      .box {
        margin: 50px;
        border: 1px solid #000f;
        padding: 10px;
        width: 100px;
        height: 100px;
      }
    </style>
  </head>
  <body>
    <div class="container">
      <div class="box"></div>
    </div>
  </body>
  <script>
    var box = document.querySelector(".box");

    // 50 50
    console.log(box.offsetLeft, box.offsetTop);
    // 122 122
    console.log(box.offsetWidth, box.offsetHeight);
    // 最近的非 static 定位祖先，container
    console.log(box.offsetParent);
  </script>
</html>
```

（2）client

只读属性，获取结果是 number ，宽高是 padding + content ，偏移是 border 的大小：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      * {
        margin: 0;
        padding: 0;
      }

      .container {
        position: relative;
        margin: 100px;
        border: 1px solid #000;
        padding: 10px;
        width: 300px;
        height: 300px;
      }

      .box {
        margin: 50px;
        border: 1px solid #000f;
        padding: 10px;
        width: 100px;
        height: 100px;
      }
    </style>
  </head>
  <body>
    <div class="container">
      <div class="box"></div>
    </div>
  </body>
  <script>
    var box = document.querySelector(".box");

    // 1 1
    console.log(box.clientLeft, box.clientTop);
    // 120 120
    console.log(box.clientWidth, box.clientHeight);
  </script>
</html>
```

（3）scroll

只读属性，获取结果是 number ，宽高是 padding + content 加上 content 超出部分的大小，偏移是滚动卷去的距离：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      * {
        margin: 0;
        padding: 0;
      }

      .container {
        position: relative;
        margin: 100px;
        border: 1px solid #000;
        padding: 10px;
        width: 300px;
        height: 3000px;
      }

      .box {
        margin: 50px;
        border: 1px solid #000f;
        padding: 10px;
        width: 100px;
        height: 100px;
      }
    </style>
  </head>
  <body>
    <div class="container">
      <div class="box"></div>
    </div>
  </body>
  <script>
    var box = document.querySelector(".box");

    // 0 0
    console.log(box.scrollLeft, box.scrollTop);
    // 120 120
    console.log(box.scrollWidth, box.scrollHeight);

    // 浏览器水平、垂直滚动的距离
    console.log(window.scrollX, window.scrollY);
  </script>
</html>
```

（4）获取元素到视口边缘的偏移

```
console.log(e.getBoundingClientRect());
/*top，left，bottom，right*/
```

（5）获取元素到整个页面边缘的偏移

如果父元素是body或者祖先都没有设置定位，那使用offsetLeft，offsetTop就可以了，但是其他情况就需要下面的方法：

元素到body的距离 = 元素到视口的距离 + 浏览器滚动的距离

```
function offsetPage(el) {
  const rect = el.getBoundingClientRect();
  const scrollLeft = window.scrollX || document.documentElement.scrollLeft;
  const scrollTop = window.scrollY || document.documentElement.scrollTop;
  return {
    left: rect.left + scrollLeft,
    top: rect.top + scrollTop,
  };
}
```

（6）获取鼠标指针在元素内的相对位置

```
const box = document.querySelector(".box");

 small.addEventListener("mousemove", function (e) {
    //方法一，不推荐，只有在祖先元素都没有设置定位时才可用
    let innerX1 = e.pageX - small.offsetLeft;
    let innerY2 = e.pageY - small.offsetTop;

    //方法二，缺点是部分低版本浏览器不支持
    let innerX2 = e.offsetX;
    let innerY2 = e.offsetY;

    //方法三
    let innerX3 = e.clientX - box.getBoundingClientRect().left;
    let innerY3 = e.clientY - box.getBoundingClientRect().top;

    //方法四，offsetPage()是自定义的函数，见上面笔记
    let innerX4 = e.pageX - offsetPage(box).left;
    let innerY4 = e.pageY - offsetPage(box).top;
});
```

## 2 BOM

BOM，浏览器对象模型。

（1）BOM 事件

页面事件

| onload             | 页面所有内容，包括标签文本图片样式都加载完才触发                                       |
| ------------------ | -------------------------------------------------------------- |
| onDOMContentLoaded | 当DOM加载完（即所有标签），就触发                                             |
| pageshow           | 与onload基本一样，但是在火狐浏览器中，前进页面后，之前的页面会缓存，再后退不会触发onload，而pageshow可以 |

onload应用：

页面加载完后触发，若引入js在html页面之前（页面未加载，js就无效了），需要将所有代码放在时间函数里面。

多个onload事件，只执行最后一个。

```
//也可写成 window.addEventListener(‘load’,function(){})
window.onload() = () => {
  //里面的代码在html页面完全加载完，才执行
}
```

窗口事件

| onscroll | 滚动             |
| -------- | -------------- |
| onresize | 浏览器窗口大小发生变化时触发 |

（2）定时器

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
    /**定时器
     *  返回 id ，类型 number
     * claer 可以清除定时器，定时器结束也会自动清除
     */

    // 执行一次
    var timerId = setTimeout(() => {
      console.log(123);
    }, 1000);

    // 重复执行
    var intervalId = setInterval(() => {
      console.log(456);
    }, 2000);

    clearTimeout(timerId);
    clearInterval(intervalId);
  </script>
</html>
```

（3）location

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

（4）navigation

```
存放浏览器的信息，可以知道是PC端的浏览器还是移动端的浏览器，由此可以知道显示PC端还是移动端页面
Navigator.userAgent.match()
但是代码比较复杂
```

（5）history

```
跟浏览器的历史记录进行交互，保存了用户浏览过的地址
history.forward() 前进
history.back()  后退
history.go(x)  正数前进x步  负数后退x步
```

# 三、ES6

ES6↑ 兼容性问题：babel 可以把ES6↑转化成ES5，解决兼容性问题。

这里说的 ES6 语法，包含 ES6 之后各个新版本的特性（ES6 \- ES13）。

需要考虑浏览器的兼容性，若 node 不支持，就升级更高版本的 node 。

babel ：奖惩 ES6 以上语法和 TypeScript 转化为 ES5 代码的工具。

关于新特性：

自从 TC39 进程指定以来，新特性提案阶段就比 ECMA 版本更为重要，因为某个 ECMA 版本发布的新特性不一定全部能用，未正式发布的新特性也可能可以使用，能不能用得看这个新特性是否处于第4个提案阶段。

ECMA 新特性的指定分为 4 个阶段，当处于第 4 阶段的新特性才能正式使用。如果想看这些正式可用的新特性有哪些，可访问：

```
https://github.com/tc39/proposals/blob/main/finished-proposals.md
```

如果想看正在开发测试中的新特性，可以访问：

```
https://github.com/tc39/ecma262/blob/main/README.md
```

## 1 let，const 和运算符

### 1.1 let，const

声明的变量具有块级作用域：

* let 声明变量

* const 声明常量，必须初始化且初始化后就无法修改
  
  * cosnt 声明的数组、对象，本身地址无法修改即无法重新赋值成新的数组、对象、但内部的元素、属性是在堆内存中，可以修改
  
  * 在确定不会修改变量时，推荐使用 const ，提升性能，如数组、对象、导入等

var 其实是JS设计上的缺陷，var 没有块级作用域，会带来非常多的问题且解决很麻烦，因此 ES6 就出现了有块级作用域的 let 和 const 。

块级作用域：for，if 等除了函数内的大括号里（函数中是局部左同宇）：

```
var i = 0;
for (var i = 0; i < 10; i++) {}
// 10
console.log(i);

var j = 0;
for (let j = 0; i < 10; j++) {}
// 0
console.log(j);
```

### 1.2 运算符

ES7 新特性，幂运算：

```
// 8
console.log(2 ** 3);
```

ES11 新特性，可选链操作符 ?\.

用于对象、数组、函数调用，只有它们存在时才会调用，有效防止 undefined 调用的错误：

PS：最外层的对象、数组、函数需要已定义，如形参。

```
const obj = {
  a: 1,
  o1: {
    b: 2,
  },
};

const arr1 = [1, 2];
const arr2 = undefined;

const func1 = () => {
  console.log("func1");
};
const func2 = undefined;

// 2 undefined ，因为 o2 不存在
console.log(obj?.o1?.b, obj?.o2?.a, "\n");

// 1 undefined
console.log(arr1[0], arr2?.[0]);

// func1 undefined
console.log(func1(), func2?.());
```

```
// ES5 处理这种问题只能用 && 或 ?: 或 if ，非常麻烦

const obj = {
  a: 1,
  o1: {
    b: 2,
  },
};

// undefined undefined
console.log(obj.o2 && obj.o2.b);
console.log(obj.o2 ? obj.o2.b : undefined);
```

ES11 新特性，空值合并操作符 ??

类似 \|\| 。但比 \|\| 限制更大，\|\| 会把 0 ，"" 等都会执行右边，而 ?? 只有 null 和 undefined 才会执行右边，false 都不行：

```
// 都是执行左边
console.log(false ?? "is left");
console.log(0 ?? "is left");
console.log("" ?? "is left");
console.log([] ?? "is left");
console.log({} ?? "is left", "\n");

// 执行右边
console.log(undefined ?? "is right");
console.log(null ?? "is right");
```

ES12 新特性，逻辑赋值操作符，??= &&= \|\|=

```
let a = true, b = false, c = null;

a &&= 1;
b ||= 2;
c ??= 3;

// 1 2 3
console.log(a, b, c);
```

ES12 新特性，数字的下划线分隔符 \_

解决长数字可读性差的问题：

```
const a = 100000000;
const b = 1_0000_0000;
const c = 100_000_000;

// true true true
console.log(a === b);
console.log(a === c);
console.log(b === c);
```

## 2 字符串、正则

### 2.1 模板字符串

更强大的字符串，用反引号。

可以把字符串中的换行保存下来：

```
let str = `
  第一行
  第二行
`;

console.log(str);
```

可以嵌入表达式：

```
function func() {
  return 123;
}

const num = 456;

const str = `${func()} 和 ${num}`;

// 123 和 456
console.log(str);
```

### 2.2 字符串 api

ES8 新特性，padStart\(\) 和 padEnd\(\) ，填充字符串，都不改变原字符串。

padStart()和padEnd()，在字符串首尾进行填充。

```
// str.padStart(num, string) 在 str 前面填充 string ，直到 size 为 num 为止
// 第二个参数默认为 " "

const str = "b";

// "aab"
console.log(str.padStart(3, "a"));

// " b"
console.log(str.padStart(2));

// "qwb"
console.log(str.padStart(3, "qwertyu"));
```

ES10 新特性，trimStart\(\) ，trimEnd\(\) ，去掉首尾空格，不改变原数组：

```
const str = "  abc  ";

// ES5，首尾空格都去掉
console.log(str.trim());

// 只去掉首尾一边的空格
console.log(str.trimStart());
console.log(str.trimEnd());
```

ES12 新特性，replaceAll\(\)

以前的 replace 只能替换匹配到的第一个，除非使用正则的 g 模式来全部替换。

而现在 replaceAll 可以替换全部匹配结果。

模式的所有匹配都会被替代项替换。模式可以是字符串或正则表达式，而替换项可以是字符串或针对每次匹配执行的函数。不改变原字符串：

```
const str = '2022-10-06';
const newStr = str.replace(/-/g,'/');   //'2022/10/05'
const newStr = str.replaceAll('-','/'); //'2022/10/05'
```

### 2.3 正则

ES9 新特性：

```
// 分组可以命名 左括号后加 ?<name>
const a = /\w+(?<num>\d+)/;

// 为每个字符分配了多个转义属性，比如判断是否存在希腊语字符，可以匹配 Script_Extensions 属性为 Greek 的字符
console.log(/\p{Script_Extensions=Greek}/.test("π"));

// 增加了负向后行断言，正向后行断言

// 新增匹配模式：dotAll 模式，修饰符 s ，使得可以匹配换行符
```

ES11 新特性，matchAll\(\)

```
// ES5 正则中，若想获得所有匹配结果并同时得到下标，只能使用循环
const regExp = /yyds(\d+)/g;
const text = "yyds1 is a very good yyds2";
let matches;
while ((matches = regExp.exec(text)) !== null) {
  console.log(matches);
}

// matchAll
const reg = /yyds(\d+)/g;
const t = "yyds1 is a very good yyds2";
let m = [...t.matchAll(reg)];
for (const match of m) {
  console.log(match);
}
```

ES13 新特性，正则表达式匹配索引

新的修饰符 d，表示想要匹配字符串的开始和结束索引。  
以前，只能在字符串匹配操作期间获得一个包含提取的字符串和索引信息的数组。在某些情况下，这是不够的。因此，在这个规范中，如果设置标志 /d，将额外获得一个带有开始和结束索引的数组。

```
const matchObj = /(a+)(b+)/d.exec("aaaabb");

// 'aaaa'
console.log(matchObj[1]);

// 'bb'
console.log(matchObj[2]);

// 由于 /d 标识的存在，matchObj 有一个属性 .indices，它用来记录捕获的每个编号组
console.log(matchObj.indices[1]); // [0, 4]
console.log(matchObj.indices[2]); // [4, 6]
```

## 3 新的数据类型

### 3.1 Symbol

（1）基本使用

特性：

- 值唯一，且不可见，可用来解决命名冲突问题

- 无法运算与比较大小，只能用 == \!= === \!== 比较

- Symobole 可以转为字符串，可转为布尔值且值为 true

```
// 值唯一，且不可以见
const s1 = Symbol();
const s2 = Symbol();
// Symbol()
console.log(s1);
// false
console.log(s1 === s2, "\n");

// 这个字符串并不是值，只是一个说明，用于注释，字符串相同的 Symbol 也是不同的
const s3 = Symbol("asdf");
const s4 = Symbol("asdf");
// Symbol("asdf")
console.log(s3);
// false
console.log(s3 === s4, "\n");

// 用函数对象创建，当传入的字符串相相同时，两个 Symbol 就相同
const s5 = Symbol.for();
const s6 = Symbol.for("123");
const s7 = Symbol.for("123");
// false false true
console.log(s5 === s6, s5 === s7, s6 === s7, "\n");
```

应用：作为对象中属性、方法第一无二的 key ：

- 可以作为对象的 key （对象、Map 的 key 只能是 string 和 Symbol）
  
  ```
  const obj = {
    [Symbol()]: 123,
  };
  
  console.log(obj);
  ```

- 对象中用 Symbol 定义的属性不能遍历出来（Map 可以），但可用 Reflect.ownKeys 遍历出来
  
  ```
  const obj = {
    [Symbol("123")]: "123",
    a: "a",
  };
  
  // 都无法看到 Symbol 为 key 的属性
  for (let i in obj) console.log(i);
  console.log(Object.keys(obj));
  console.log(Object.getOwnPropertyNames(obj));
  console.log(JSON.stringify(obj), "\n");
  
  // 只能看到 Symbol 为 key 的属性
  console.log(Object.getOwnPropertySymbols(obj), "\n");
  
  // 全部属性都能看到
  console.log(obj);
  console.log(Reflect.ownKeys(obj));
  ```

- Symbol 的内置属性：通常用来作为对象的属性，在其他特性中用作各种用途：
  
  ```
  const obj = {
    [Symbol.hasInstance]: 123,
  };
  ```

ES10 新特性，新增 description ，用来查看 Symbol 变量的描述字符串：

```
const s = Symbol("123");
// 123
console.log(s.description);
```

### 3.2 BigInt

ES11 新特性，用于存放更大的数字，不过只能是整数：

```
const a = 123n;
```

将 Number 和 String 转为 BigInt ，只能装整数，小数不行：

```
let b = BigInt(123);
let c = BigInt("456");

// 123n 456n
console.log(b, c);
```

BigInt 只能和 BigInt 或 String 运算，不能和 Number 运算：

```
const d = 123n + 456n;
const e = 123 + "456n";

// 579n "123456"
console.log(d, e);
```

BigInt 也能转为 Number ，但会涉及到边界问题：

```
const f = Number(123456n);
```

转为 Boolean ：

```
// false true
console.log(!!0n);
console.log(!!10086n);
```

也提供了对应 BigInt 的数组构造函数：

```
const arr1 = new BigInt64Array(2);
```

Number 和 BigInt 比较大小：

```
// true false true false
console.log(2n == 2);
console.log(2n === 2);
console.log(2n > 1);
console.log(2n > 2);
```

### 3.3 Number 新 api

Number ：

```
// Number.EPSILON ，用于浮点数运算
console.log(Number.EPSILON);
if (Math.abs(0.3 - (0.1 + 0.2)) < Number.EPSILON) console.log("相等");

// 进制
const a = 0b1010,
  b = 0o777,
  c = 0xff;

// 判断是否是整数
console.log(Number.isInteger(123));

// 判断是否是有理数
console.log(Number.isFinite(123));

// 转化成整数、浮点数
console.log(Number.parseInt(3.14), Number.parseFloat("3"));

// 判断是否是 NaN ，只有 NaN 才返回 true
console.log(Number.isNaN(NaN));
// 而 window.isNaN 会把 undefined ，String 、Object 都返回 true ，因为会进行类型转换
// console.log(window.isNaN(undefined));
```

Math ：

```
// 去掉小数部分
console.log(Math.trunc(3.14));

// 正数/负数/0返回 1/-1/0
console.log(Math.sign(123));
```

## 4 解构赋值、扩展运算符、for\.\.\.of、迭代器

### 4.1 解构赋值

将数组、对象中的元素/属性一次赋值给多个变量。

若变量多余数组元素、或变量是对象中不存在的属性，则值为 undefined 。

```
// 数组解构赋值，可以设置默认值，可以连续结构
const arr = [1, 3, 5, [7, 9]];

// 1 3 5 7 9 undefined 10
const [a, b, c, [d, e], f, g = 10] = arr;
console.log(a, b, c, d, e, f, g);
// ---------------------------------------------------

// 对象解构赋值，可以设置默认值，可以起别名，可以连续结构
const obj = {
  name: "asdf",
  age: 18,
  other: {
    o1: 123,
  },
};

// 18 asdf 123 undefined false
const {
  age: myAge,
  name,
  other: { o1 },
  sex,
  isDelete = false,
} = obj;
console.log(myAge, name, o1, sex, isDelete);
```

可以灵活使用，如数组里的对象、对象里的数组，对象连续结构并起别名，函数参数和返回值解构。

### 4.2 扩展运算符

扩展运算符...

将数组转化成逗号分隔的列表，具备 iterator 接口的数据类型才可使用。

```
const arr1 = ["12", "34", "56"];

// 简化传参
function func1(a, b, c) {
  console.log("func1", a, b, c, "\n");

  // 伪数组也行，如 querySelectAll，argument
  const arr22 = [...arguments];
  console.log(arr22, "\n");
}
func1(...arr1);

// 构建新的数组
const arr2 = [123, ...arr1, ...arr1];
console.log(arr2, "\n");

// 只有一层的深拷贝，嵌套的就不行了
let arr3 = [...arr1];
console.log(arr3, "\n");

/* 使用第三方库的函数时，若不知道里面的回调函数有几个形参，可以这样查看有什么参数
xxx((...aaa) => {
  console.log(aaa);
});
*/
```

### 4.3 for\.\.\.of

具备 iterator 接口的数据类型才可使用。

与 for\.\.\. in 区别就在于 for\.\.\.of 遍历出来的是 value 而不是 key 。

```
const arr = [1, 3, 5];

// 1 3 5
for (let i of arr) {
  console.log(i);
}
```

### 4.4 迭代器

（1）基本概念

ES6 提供了 iterator 接口，为不同的数据结构提供统一的访问机制。

数组解构赋值是按顺序结构出来的，因为底层实现使用的迭代器，扩展运算符和 for\.\.\.of 也只有具备 iterator 接口的数据解构才能使用。

* 只有 Object 没有 iterator 接口，其他都有，如 Array，String，Arguments，Set，Map，NodeList，typedArray）

* 其中 Set，Map 比较特殊，无法使用 for in ，只能用 for of

一般 iterator 接口是各数据结构的原型对象中的一个方法：

```
[Symbo.iterator] : function(){}
```

（2）原理与使用

迭代器中有一个 next\(\) 方法，作用是返回当一个对象，对象的内容为当前 value 和是否结束，得到这个信息后，移动到下一个元素：

```
const arr = [1, 2, 3];
const arrIterator = arr[Symbol.iterator]();

/* {value: 1, done: false}
 * value：当前元素
 * done：是否到达 end
 */
console.log(arrIterator.next());

// {value: 2, done: false}
console.log(arrIterator.next());
// {value: 3, done: false}
console.log(arrIterator.next());

// {value: undefined, done: truye}  结束
console.log(arrIterator.next());
```

当 done 为 true 时，迭代结束。总体上指针在 begin 到 end 是一个左闭右开的区间。

（3）自定义遍历数据

例如给某个对象单独部署 iterator 接口，使其可以使用 for\.\.\.of ，且 for\.\.\.of 的遍历规则是自定义的：

```
const o = {
  name: "asdf",
  arr: [1, 2, 3],
  [Symbol.iterator]() {
    let index = 0;
    const _this = this;

    return {
      next() {
        // 这里 this指向 o
        if (index < _this.arr.length)
          return { value: _this.arr[index++], done: false };
        else return { value: undefined, done: true };
      },
    };
  },
};

// 1 2 3
for (i of o) console.log(i);
```

直接给 Object 部署 iterator 接口也可以，例如用数组解构赋值的语法按顺序结构对象：

```
Object.prototype[Symbol.iterator] = function () {
  // 直接借助 Array 的 iterator 也可以，自己写也可以
  return Object.keys(this)[Symbol.iterator]();
};

const [n1, n2] = { a: 1, b: 2 };
console.log(n1, n2);

for (const i of { a: 1, b: 2 }) console.log(i);
```

## 5 函数新特性

### 5.1 新语法

rest 参数

用于接收不定数量的参数，必须放在最后面，接收后是一个数组，可以替代 arguments ：

```
function func(a, b, ...args) {
  console.log(a, b, args);
}

// 1 2 [3, 4, 5]
func(1, 2, 3, 4, 5);
```

此外，数组的解构赋值也能使用 rest 参数，不过也必须放在最后面：

```
const arr = [1, 2, 3];

const [a, ...b] = arr;
// 2 3
console.log(b);
```

形参默认值

```
// ES5
function func1(a) {
  a = a || 5;
  console.log(a);
}

// ES6
function func2(a = 5) {
  console.log(a);
}

// 5 5
func1();
func2();
```

ES8 新特性，函数可以喝数组、对象一样，最后面加一个逗号而不报错了：

```
function func(a, b, ) {}
func(1, 2, );
```

ES10 新特性，优化了 Function\.prototype\.toString\(\) ，返回结果可以保留空格和换行符：

```
function func(a) {
  console.log(a);
}

console.log(func.toString());
```

### 5.2 箭头函数

在 ES6 之前，function 既可以作为普通函数封装代码，又可以作为构造函数来实例化对象，这实际上是 JS 设计上的缺陷，作为面向对象的语言，应该把这两个功能在语法上区分开来，消除函数的二义性。

箭头函数就是解决方案之一（另一个是 class ）：

```
// 普通函数
// 具名
function func1(a, b) {}
// 匿名
const func2 = function (a, b) {};

// 箭头函数
const func3 = (a, b) => {};
```

与普通函数的区别：

* 只能定义匿名函数

* 由于设计初衷是为了消除二义性，所以箭头函数不能作为构造函数，不能 new、没有原型，没有 arguments、没有自己的 this

若箭头函数内部使用了 this 就需要看执行上下文，可以简单理解为自身没有 this 变量，this 是从作用域链上找到的：

```
function func() {
  const that = this;

  const f = () => {
    // true
    console.log(this === that);
  };

  f();
}

func();

const obj = {
  func1: () => {
    // window
    console.log(this);
  },

  func2: function () {
    const that = this;

    const o = {
      f: () => {
        // true
        console.log(this === that);
      },
    };

    o.f();
  },

  func3: () => {
    const o = {
      f: () => {
        // window
        console.log(this);
      },
    };

    o.f();
  },

  func4: function () {
    const that = this;
    // true
    return () => console.log(that === this);
  },

  func5: function (fn) {
    fn();
  },
};

obj.func1();
obj.func2();
obj.func3();
obj.func4()();

// window
obj.func5(() => console.log(this));

function f() {
  const that = this;
  // that
  obj.func5(() => console.log(this));
}
f();
```

特殊情况下，可以简化：

当形参只有一个时，小括号可以省略；当函数体只有一行时，大括号可以省略，注意省略后，会隐含 return ：

```
const func1 = (a) => a * 5;

// 等价于
const func2 = (a) => {
  return a * 5;
};
```

注意：

以下是错的，本意是想要 return 一个对象且省略函数体

```
const func = () => { a: 1, b: 2 };
```

但是由于包裹对象的也是大括号，所以会解析成这样，就语法错误了：

```
const func = () => {
  return a: 1, b: 2;
}
```

解决方法是用 \(\) ：

```
const func = () => ({ a: 1, b: 2 });
```

### 5.3 标签模板

函数调用结合模板字符串的一种新的函数调用方式。标签指的就是函数，在函数调用后面的模板字符串会按照规则作为函数的实参：

```
const func = (a) => {
  console.log(a);
};

// 相当于 func([`111`]);
func`111`;
```

其他情况：

```
const func = (str, a, b) => {
  console.log(str, a, b, "\n");
};

const a = "aaa",
  b = 25;

// func(["q", "w", "e"], a, b);
func`q${a}w${b}e`;

// func(["q", "w", ""], a, b);
func`q${a}w${b}`;

// func(["", "w", ""], a, b);
func`${a}w${b}`;

// func(["q", "", ""], a, b);
func`q${a}${b}`;

// func(["", "", ""], a, b);
func`${a}${b}`;

// func(["q", "w", "e", "r"], b, b, b);
func`q${b}w${b}e${b}r`;
```

ES9 新特性，若模板字符串中有错误的转义字符，不再报错，而是把这个转义字符变成 undefined ，且可以从 raw 看到原始字符串：

```
function tag(strs) {
  // undefined
  console.log(strs[0]);

  // "\\unicode and \\u{55}";
  console.log(strs.raw[0]);
}

tag`\unicode and \u{55}`;
```

## 6 对象、数组

### 6.1 对象

（1）新语法

对象中，属性名、方法名可以是表达式/函数，用 [] ：

```
const obj = {
  [1 + 2 + 3]: 789,
};

// {"6": 789}
console.log(obj);

// 但若不是字符串，只能用 [] 调用，不能用 obj.6 调用
console.log(obj[6]);
```

若属性、方法已声明，在对象中就可以简化：

```
const num = 123;
function func() {}

const obj = {
  num,
  func,
};
```

对象中的方法新的写法：

```
const obj = {
  // 老写法
  func1: function () {},
  // 新写法
  func2() {},
};
```

ES9 新特性，对象也可以使用扩展运算符了：

```
const obj1 = {
  a: 1,
  b: 2,
};

const obj2 = {
  ...obj1,
  c: 3,
};

console.log(obj2);

// 数组可以扩展对象，但对象不可以扩展数组
const testObj = { a: 1 };
const testArr = [2];
const o = { ...testArr };
// { "0": 1 }
console.log(o);
// error
// const a = [...testObj];
```

ES9 新特性，对象也可以使用 rest 参数了：

```
const func = ({ a, b, ...c }) => {
  // 1 2 { c: 3, d: 4 }
  console.log(a, b, c);
};

func({
  a: 1,
  b: 2,
  c: 3,
  d: 4,
});

// 也可以配合对象的解构赋值，实现属性过滤
const obj = {
  a: 1,
  b: 2,
  c: 3,
  d: 4,
};

const { a, d, ...o } = obj;
// { b: 2, c: 3 }
console.log(o);
```

ES11 新特性，globalThis

始终指向全局环境（浏览器是 window，node 是 global）：

```
console.log(globalThis);
```

（3）Object 新的 api

Js的数组，字符层，Set，Map 本质都是对象，所以这些方法都可以调用

- 数组，字符层可以正常调用

- Set，Map可以调，但结果为空

api ：

```
const obj = {
  a: 1,
  b: 2,
};

// 返回 key 或 value 的数组
console.log(Object.keys(obj));
console.log(Object.values(obj), "\n");

// 返回 [key, value] 构成的二维数组
console.log(Object.entries(obj), "\n");

// 判断两个对象是否完全相等，与 === 不同的是两个 NaN 比较为 true
console.log(Object.is(obj, obj), "\n");

// 把多个对象合并到 obj ，机会改变 obj 又能返回，若有相同 key ，则后面会覆盖前面的
const newObj = Object.assign(obj, { a: 11 }, { c: 3 });
console.log(newObj, obj, "\n");

// 返回 obj 的原型
console.log(Object.getPrototypeOf(obj), "\n");

// 给 obj 设置新的原型
Object.setPrototypeOf(obj, { a: 1 });
console.log(obj.__proto__), "\n";
```

ES8 新特性，Object\.getOwnPropertyDescriptors\(\) ：

```
const obj = { a: 1, b: 2 };

/* 返回 obj 的属性的描述对象
 * 描述对象：用 Object.create() 创建的对象的类似格式，有是否可枚举、是否可删除等信息
 * 主要作用是实现更深层次的对象拷贝，把是否可枚举/可删除等都拷贝了
 */
console.log(Object.getOwnPropertyDescriptors(obj));
```

ES10 新特性，Object.fromEntries\(\) ，用二维数组创建一个对象：

```
const obj = Object.fromEntries([
  ["a", 1],
  ["b", 2],
]);

console.log(obj);
```

ES13 新特性，Object\.hasOwn\(\)

检查 value 是否属于 obk ，比 ES5 的 Object\.prototype\.hasOwnProperty 更简洁可靠：

```
const example = {
  name: "asdf",
};

console.log(Object.prototype.hasOwnProperty.call(example, "name"));

console.log(Object.hasOwn(example, "name"));
```

### 6.2 数组

（1）map、filter、reduce

新增数组的高阶函数 map() 、filter() 、reduce() 。

高阶函数是函数式编程的一个概念，指的是接收函数参数，或者返回值是函数的函数，接收的这个函数参数会作为回调函数在合适的时候调用。

```
const func1 = (fn) => {
  fn();
  console.log("高阶函数");
};

const func2 = () => {
  return () => {
    console.log("高阶函数");
  };
};
```

若返回函数的函数中，内部函数的行为是由外部函数的参数决定的，就叫所函数科里化：

```
const func = (a) => {
  return () => {
    console.log("函数科里化");

    if (a) return 123;
    else return 456;
  };
};
```

map()

遍历数组，并按照自定义的规则构造新数组：

```
const arr = [1, 2, 3];

const newArr = arr.map((item, index, source) => {
  // value, key 和原始数组
  console.log(item, index, source);

  // 新数组中每一个新元素
  return item * 10;
});

// 10 20 30
console.log(newArr);
```

filter()

遍历数组，按照自定义的规则筛选元素，构建新数组：

```
const arr = [1, 2, 3];

const newArr = arr.filter((item, index, source) => {
  // value, key 和原始数组
  console.log(item, index, source);

  // 新数组中每一个新元素
  return item >= 2;
});

// 2 3
console.log(newArr);
```

reduce()

遍历数组，并汇总数据：

```
const arr = [1, 2, 3];

// 第二个参数 0 是初始值，会成为第一轮的 pre
const sum = arr.reduce((pre, item, index, source) => {
  // 上一轮 return 的值，value，key 和原始数组
  console.log(pre, item, index, source);

  return pre + item;
}, 0);

// 6
console.log(sum);
```

map() 和 filter() 都返回数组，所以互相之间可以链式调用。

（2）其他数组 api

使用这些数组 api 的注意点：

- 是遍历整个数组还是有结果就中断遍历并返回结果

- 数据有修改的是否改变原数组

- 参数有范围的是左闭右开区间还是左闭右闭区间

- 浅拷贝还是深拷贝

Array\.isArray\(\) ，判断是否为数组，结果为一个 Boolean，优先级高于 instanceof ：

```
const arr = [1, 2];
const obj = {};

// true false
console.log(Array.isArray(arr), Array.isArray(obj));
```

判断数组的元素是否符合某个条件：

都不改变原数组

```
const a = [1, 2, 3, 4];

// 遍历整个数组，当所有值都符合条件时，才返回true v值，i索引，arr原数组
const boolean1 = a.every((v, i, arr) => v >= 2);

// 遍历整个数组或一部分，当有一个值符合条件时，就中断并返回true v值，i索引，arr原数组
const boolean2 = a.some((v, i, arr) => v >= 2);
```

数据查询：

都不改变原数组

```
const a = [1, 2, 3, 4];

/* 遍历数组一部分，返回符合条件的值
   一旦找到就结束遍历并返回该元素，找不到返回undefine
  若结果为基本数据类型，就返回值。
  若结果为引用数据类型，就返回地址，也就是浅拷贝
  形参v值，i索引，arr原数组
 */
const res1 = a.find((v, i, arr) => v >= 2);
//与find区别在于它返回索引值，找不到返回-1
const index1 = a.findIndex((v, i, arr) => v >= 2);
```

数组元素替换，数组深拷贝：

替换会改变原数组

```
const a = [1, 2, 3, 4];

/* 替换数组里的元素，会改变原数组
 * 形参：值，开始索引，结束索引。
 * 用值替换掉开始到结束索引(左//闭右开)的值
 */
a.fill(5, 0, 3);
console.log(a);

// 深拷贝数组
const aCopy = Array.from(a);
```

ES7 新特性，includes\(\) ，判断数组中是否有某个元素，一旦找到就结束遍历，返回 Booleran：

```
const arr = ["a", "b"];

// true
console.log(arr.includes("a"));
```

ES10 新特性，flat() 和 flatMap() ，用于数组降维，返回降维后的数组，都不会改变原数组：

```
const arr2 = [1, 2, [3, 4]];
const arr3 = [1, 2, [3, 4, [5, 6]]];

// flat
// [1,2,3,4] 二维转化一维
console.log(arr2.flat());
// [1,2,3,4,[5,6]] 三维转二维
console.log(arr3.flat());
// [1,2,3,4,5,6] 三维转一维，2 表示深度 2, 3 - 1 = 2，空参则默认为 1
console.log(arr3.flat(2));

// flatMap,相当于 map() 之后使用 flat()
const arr = [1, 2, 3];
// 先 map 后 flat
const arrMap = arr.map((item) => [item * 10, item * 20]);
console.log(arrMap.flat());
// flatMap
console.log(arr.flatMap((item) => [item * 10, item * 20]));
```

```
// ES5 数组降维

const arr = [1, [2, 3, [4, 5, 6]]];

/* 方法一：自定义递归函数
 * 优点是不用对结果进行数据类型转换
 * 缺点是写法复杂
 */
function myFlat(arr, deep) {
  deep = deep || 1;

  if (deep < 1) return [...arr];

  let res = [];
  for (const i of arr) {
    if (Array.isArray(i)) res = [...res, ...myFlat(i, deep - 1)];
    else res.push(i);
  }

  return res;
}

console.log(myFlat(arr, 2));

/* 方法二：先转为字符串，再转为数组
 * 优点是写法简单
 * 缺点是结果需要数据类型转换，这里就不处理了
 */
function func(arr) {
  // toString ，join 都可以
  const str1 = arr.toString();
  // const str2 = arr.join();

  return str1.split(",");
}

console.log(func(arr));
```

ES13 新特性，at\(\)

访问数组、字符串中的元素，整数是正向索引，负数是反向索引：

```
const arr = [1, 2, 3];
const str = "abcd";

// 1 3
console.log(arr.at(0), arr.at(-1));

// a d
console.log(str.at(0), str.at(-1));
```

## 7 异步编程

都是用于封装异步代码，使得异步代码结构更加清晰，解决回调地狱的问题。

对调地狱：传统方案单纯使用回电函数进行异步编程，当嵌套太深时，可读性很差，不好维护。

### 7.1 生成器

本质是一个函数，但是语法与传统函数完全不同,进行异步编程。

```
// 定义：三种都一样
function* xxx() {}
function * xxx() {}
function *xxx() {}

/// 调用：生成器定义后是一个迭代器对象，所以：
xxx().next();
// 或：
const x = xxx();
x.next();
```

yield 语句：

在生成器函数体中定义，将代码区域上下分割，n 条 yield 语句将代码分割成 n + 1 个代码块，每次调用 next() 都只执行当前代码块，然后将指针指向下一个代码块。

```
function* xxx() {
  console.log(1);
  yield "分割线 1";
  console.log(2);
  yield "分割线 2";
  console.log(3);
}

// 不能是 xxx().next() 因为这样是不同的迭代器对象
const x = xxx();

/* res
  1
 {}value: "分割线 1", done: false}
  2
 {}value: "分割线 2", done: false}
  3
 {}value: undefined, done: true}
 */
console.log(x.next());
console.log(x.next());
console.log(x.next());

// for...of
/* res
  1
  分割线 1
  2
  分割线 2
  3
  */
console.log("\n\n\n");
for (i of xxx()) console.log(i);
```

生成器函数参数：

- 生成器可以定义形参

- next() 可传实参，生成器用 let x = yield 123 接收，x的值就是实参的值

- 第 n 次调用的 next，则第 n - 1 个yield 接收

```
function* func(a) {
  console.log(a);

  const b = yield "接收参数 b";
  console.log(b);

  const c = yield "接收参数 c";
  console.log(c);
}

const f = func(1);
console.log(f.next());
console.log(f.next(2));
console.log(f.next(3));
```

应用：

回调地狱的代码：

```
setTimeout(() => {
  console.log(111);

  setTimeout(() => {
    console.log(222);

    setTimeout(() => {
      console.log(333);
    }, 3000);
  }, 2000);
}, 1000);
```

同样的逻辑用生成器实现，简化代码：

```
function* xxx(a) {
  yield setTimeout(() => {
    console.log(111);
    x.next();
  }, 1000);

  yield setTimeout(() => {
    console.log(222);
    x.next();
  }, 2000);

  yield setTimeout(() => {
    console.log(333);
    x.next();
  }, 3000);
}

const x = xxx();
x.next();
```

### 7.2 Promise

（1）基本使用

Promise 有 3 种状态：

- Pending：待定，初始状态，未完成也未拒绝，then、catch 都不会执行

- Fullfilled：已完成，resolve() 实现，后可以执行 then

- Rejected：已拒绝，reject() 实现，后可以执行 catch

状态只能从 Pending 改变到 Fillfilled 或 Rejected ，且只能改变一次。

```
const flag = true;

/* 格式：
 * new Promise((resolve, reject) => {}).then(res => {}).catch(err => {})
 * new Promise((resolve, reject) => {}).then(res => {}, err => {})
 */
new Promise((resolve, reject) => {
  setTimeout(() => {
    /* resolve, reject
     * resolve: 表示成功，执行后进入 then 的回调
     * reject： 表示失败，执行后进入 catch 的回调
     * 若 resolve、reject 都没有，则状态为 Pending， thern、catch 都不执行
     */
    if (flag) resolve("this is res");
    else reject("err");
  }, 1000);
})
  .then((res) => {
    console.log(111, res);
  })
  .catch((str) => {
    console.log(str);
  });
```

resolve ，reject 后面的代码也会执行，也是同步任务：

```
// 输出结果：1 2 3 4

new Promise((resolve, reject) => {
  console.log(1);
  resolve();
  console.log(2);
}).then(() => {
  console.log(4);
});

console.log(3);
```

then，catch 都可以链式调用，具体则根据内部是 return 还是 throw ：

```
// 1 3 2 4

new Promise((resolve, reject) => {
  resolve();
})
  .then(() => {
    console.log(1);
  })
  .then(() => {
    console.log(2);
  });

new Promise((resolve, reject) => {
  reject();
})
  .catch(() => {
    console.log(3);
  })
  .then(() => {
    console.log(4);
  });
```

但如果没有 resolve 也没有 reject ，Promise 就是 Pending 状态，then，catch 都不执行：

```
// 无结果

const p = new Promise((resolve, reject) => {
  // resolve();
})
  .then(() => {
    console.log(1);
  })
  .then(() => {
    console.log(2);
  });
console.log(p);
```

（2）then ，catch

then、catch 返回的也是 Promise ：

* 若内部正常 return （默认 return undefined），则返回的 Promise 状态为 Fullfilled ，return 的值会成为下一个链式调用的 then 的参数
  
  ```
  new Promise((resolve) => {
    resolve();
  })
    .then(() => {
      console.log(0);
  
      return 123;
    })
    .then((res) => {
      // 123
      console.log(res);
    });
  ```

* 若内部 throw 了，则返回的 Promise 状态为 Rejected ，throw 的值的值会成为下一个链式调用的 catch 的参数
  
  ```
  new Promise((resolve) => {
    resolve();
  })
    .then(() => {
      console.log(0);
  
      throw 123;
    })
    .catch((res) => {
      // 123
      console.log(res);
    });
  ```

* 特殊情况，若 return 的是一个 Promise （这里记为 p1），则状态和 p1 的状态一样，且p1.then\(\) 整个表达式入队为队列，而不是常规的 then 中的回调函数入队：
  
  ```
  new Promise((resolve) => {
    resolve();
  })
    .then(() => {
      console.log(0);
  
      // .then 或 .catch(finallyFn) 的状态和 p1 一样
  
      // Fullfilled，执行 then
      const p1 = Promise.resolve(123);
      // const p1 = new Promise((resolve) => resolve(123));
      // const p1 = new Promise((resolve) => resolve(123)).then(() => 123);
  
      // Rejected，执行 catch
      // const p1 = Promise.reject(123);
      // const p1 = new Promise((resolve, reject) => reject(123));
      // const p1 = new Promise((resolve, reject) => reject(123)).catch(() => {
      //   throw 123;
      // });
  
      // Pending，then ，catch 都不入队，也就不执行
      // const p1 = new Promise((resolve) => resolve());
  
      // return 一个 Promise，会变成把 p1.then(fn) 入队微任务
      return p1;
    })
    // 这里的 then，catch 的回调函数记为 finallyFn
    .then((res) => console.log(res))
    .catch((res) => console.log(res));
  
  /* p1.then(fn) , p1.catch() 会整体入队微任务
   * 1. 微任务中，执行 p1.then(fn) ，结果是把 fn 入队
   * 2. 微任务中，执行 fn 《结果是 p1 完成，将最终的 finallyFn 入队
   * 执行 finallyFn
   */
  ```

Promise 的 then 和 catch 的回调函数是微任务，如果要把某些任务直接放入微任务人咧时，也可以：

```
Promise.resolve().then(() => {});
Promise.reject().catch(() => {});
```

ES9 新特性：\.finally\(\) ，无论时 Fullfilled 还是 Rejected 都会回调，但是 Pending 依然不会回调：

```
new Promise((resolve, reject) => {
  resolve();
  // reject();
}).finally(() => {
  console.log(123);
});
```

（3）处理多个 Promise

当一个请求需要多个子请求的结果时，是不好判断子请求的完成顺序的，代码写起来就复杂。使用 Promise.all\(\) 会方便很多。

Promise\.all\(\) ：
传入一个 Promise 数组，数组中所有的 Promise 状态都是 Fullfilled 时，外部 Promise  才是 Fullfilled 。

由于封装的都是异步，所以all执行总时间就是执行最慢的那一个异步操作的时间。

```
const p1 = new Promise((resolve, reject) => {
  resolve(1);
});

const p2 = new Promise((resolve, reject) => {
  resolve(2);
});

const p3 = new Promise((resolve, reject) => reject("err"));

Promise.all([p1, p2]).then((resArr) => {
  // resArr 时一个数组，元素分别是各个 Promise 中 resolve 传入的参数
  console.log("FullFilled", resArr);
});

Promise.all([p1, p3]).catch((err) => {
  console.log(err);
});
```

ES12 新特性：Promise\.any\(\) ，也是传入 Promise 的数组，不同的是，只要其中一个成功就成功，且 then 只能处理成功 Promise 的信息，有点像多个 Promise 竞速。

所有 Promise 失败才会失败。

```
const p1 = new Promise((resolve) => {
  setTimeout(() => resolve("p1"), 1000);
});

const p2 = new Promise((resolve) => {
  setTimeout(() => resolve("p2"), 2000);
});

const p3 = new Promise((resolve, reject) => {
  reject();
});

const p4 = new Promise((resolve, reject) => {
  reject();
});

// ------------------------------------------------------------------
Promise.any([p1, p2]).then((res) => {
  //'p1'，1秒后输出
  console.log(res);
});

Promise.any([p2, p3]).then((res) => {
  //‘p2’，2秒后输出
  console.log(res);
});

Promise.any([p3, p4]).catch((err) => {
  // err 信息
  console.log(err);
});
```

ES11 新特性，Promise.allSettle\(\) ，传入 Promise 数组，数组中的 Promise 无论成功失败，外部 Promise 都是 Fullfilled ，成功的值为对象数组，保存每个 Promise 的状态和值：

```
const p1 = new Promise((resolve) => {
  resolve(1);
});

const p2 = new Promise((resolve) => {
  resolve(2);
});

const p3 = new Promise((resolve, reject) => {
  reject(3);
});

/*输出
 [
   { status: 'fulfilled', value: 1 },
   { status: 'fulfilled', value: 2 },
   { status: 'rejected', reason: 3 }
 ]
 */
const res = Promise.allSettled([p1, p2, p3]);
res.then((res) => {
  console.log(res);
});
```

（4）顶层 await

ES13 新特性，允许在全局作用域使用 await 。在之前，如果 import 的资源是异步加载的，需要这么做：

```
// 1.js
export let data;

export default new Promise((resolve) => {
  setTimeout(() => {
    data = 123;
    resolve();
  }, 1000);
});
```

```
// 2.js
import p, { data } from "./1.js";

p.then(() => {
  console.log(data);
});
```

比较繁琐，而用顶层 await 会方便很多：

```
// 1.js
export let data = await 异步;
```

```
// 2.js
import { data } from "./1.js";
console.log(data);
```

其他用途：

- 动态加载模块
  
  ```
  const str = await import(`/i18n/${navigator.language}`);
  ```

- 资源初始化
  
  ```
  const con = await dbConnector();
  ```

- 依赖回退
  
  ```
  let translations;
  try {
    translations = await import('https://app.fr.json');
  } catch {
    translations = await import('https://fallback.en.json');
  }
  ```

### 7.3 async、await

ES8 新特性，以类似同步的方式使用异步。

（1）async

用来声明 async 函数，该函数一定会返回一个 Promise ，return 的值是 reslove 传入的参数，根据 async函数 返回的 Promise 的成状态，可以使用 then 、catch：

```
async function func1() {
  return 123;
}

func1().then((val) => {
  console.log(val); //输出123
});

//上面代码相当于
new Promise((resolve) => {
  resolve(123);
}).then((val) => {
  console.log(val);
});
```

若 async 函数的返回值为：

- *没有 return 或只有 return ，rereturn undefined，返回的 Promise 状态为 Fullfilled ，then 参数值为 undefined

- return xxx ，返回的 Promise 状态为 Fuillfilled ，then 的参数值为 xxx

- return Promise  ，记为 p，返回的 Promise 状态即 p 的状态，then 、catch 的参数值为 p 内 resolve ，reject 的值

- 该函数内跑出异常，返回的 Promise 状态为 Rejected

（2）await

后面可以放一个表达式，称为await 表达式（一般为Promise对象）。

* *await 必须放在 async 函数中，不过 async 函数中不一定要有 await 。

* await 下面的代码若 await 成功 ，则相当于 then ，若有多个 await ，则相当于嵌套的 then

* await 之前的代码就相当于 Promise 的 \(resolve, reject\) =\> \{\}

await 后面的表达式，若为：

* Promise，若该 Promise 状态为 Fullfilled ，则 await 表达式结果为 resolve 传入的值；若状态为 Rejected ，则需要 try\.\.\.catch 捕获异常，catch 获得的值即 reject 传入的值：
  
  ```
  /* 输出结果
   * resolve：1 2 end
   * reject：1 err 3 end
   */
  
  const p = new Promise((resolve, reject) => {
    resolve();
    // reject();
  });
  
  async function func() {
    try {
      const res = await p;
      console.log(2);
    } catch (err) {
      console.log("err");
      console.log(3);
    }
  
    // 若 resolve ，则这里相当于把下面的代码放入 then 中的后面
    // 若 reject ， 则这里相当于把下面的代码放入 catch 中的后面
    console.log("end");
  }
  
  func();
  console.log(1);
  ```
  
  await 失败的另一种写法，虽然比 try\.\.\.catch 简洁，但是只能获取 Promise 自己的成功失败，获取不到 Promise 内部代码的错误：
  
  ```
  const p = new Promise((resolve, reject) => {
    resolve(1);
    // reject(2);
  });
  
  async function func() {
    const [res, err] = await p
      .then((res) => [res, null])
      .catch((err) => [null, err]);
  
    console.log(res, err);
  }
  
  func();
  ```

* 不是 Promise ，则 await jscode 会转化成 await Promise\.resolve(jscode) ：
  
  ```
  // 输出结果：1 2 3 undefined
  
  async function func() {
    // 转化成 await Promise.resolve(123)
    const res1 = await 2;
    console.log(res1);
  
    // 转换成 await Promise.resolve((() => console.log(3))())
    const res2 = await (() => console.log(3))();
    console.log(res2);
  }
  
  func();
  console.log(1);
  ```

await 的优先级低于 \] 和 \. ：

```
const p1 = new Promise((resolve) => {
  resolve({ a: 123 });
});

const p2 = new Promise((resolve) => {
  resolve([5, 7]);
});

async function func() {
  const res1 = (await p1).a;
  const res2 = (await p2)[0];
  console.log(res1, res2);

  // 也可以直接解构赋值
  const { a } = await p1;
  const [res3] = await p2;
  console.log(a, res3);
}

func();
```

### 7.4 异步迭代器

ES9 新特性，即异步循环 for\.\.\.await\.\.\.of 。

普通的在 for 中若有异步操作，其实就是把循环体按顺序执行 n 次，先执行同步任务再执行异步任务，本质上还是正常的 JS 执行机制：

```
function func(i) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(i);
    }, 1000);
  });
}

console.log("start");

for (let i = 0; i < 3; i++) {
  console.log(`同步${i}`);
  func(i).then((res) => {
    console.log(`异步${res}`);
  });
}
console.log("end");

/* 整个 for 循环其实就是 3 次 console...Promise
start
同步0
同步1
同步2
end
异步0
异步1
异步2
*/
```

async ，await 也一样：

```
function func(i) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(i);
    }, 1000);
  });
}

async function run1() {
  console.log("start");

  for (let i = 0; i < 3; i++) {
    console.log(`${i}`);
    const res = await func(i);
    console.log(`异步${res}`);
  }

  console.log("for执行完我才执行"); //这是最后一次await后的then
}

run1();
console.log("end");

/*
start
0
end
异步0
1
异步1
2
异步2
for执行完我才执行
*/
```

而异步迭代器 for\.\.\.await\.\.\.of ，在上面代码的基础上，把整个 for 的循环体放入一个 Promise 的 then 中：

```
function func(i) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(i);
    }, 1000);
  });
}

async function run2() {
  console.log("start");

  for await (let i of [0, 1, 2]) {
    console.log(i);
    const res = await func(i);
    console.log(`异步${res}`);
  }

  console.log("for执行完我才执行"); //这是最后一次await后的then
}
run2();
console.log("end");

/*
start
end
0
异步0
1
异步1
2
异步2
for执行完我才执行
*/
```

### 7.5 并发 Promise

当需要处理多个 Promise 可以用 Promise\.allSettle\(\) 并行处理，或 for await 穿行处理。但如果想要并行处理，且需要控制同一时间的并发量，就需要手写了，如大文件上传。

此外，若 reject 了，也可以按需求看是否需要重新执行，如请求重传。

```
/**可控制并发量的 Promise
 * taskList: 任务数组，每个元素是返回 Promise 的 function
 * maxMaxConcurrent: 最大并发量
 * needRestart: reject 时需要重新运行的次数
 */
function myAllSettle(taskList, maxConcurrent = 1, needRestart = 0) {
  return new Promise((resolve) => {
    if (!Array.isArray(taskList) || taskList.length === 0) return resolve([]);

    maxCpncurrent = Number.parseInt(maxConcurrent);
    needRestart = Number.parseInt(needRestart);
    if (maxConcurrent <= 0 || Number.isNaN(maxConcurrent)) maxConcurrent = 1;
    if (needRestart < 0 || Number.isNaN(needRestart)) needRestart = 0;

    const result = [];
    let index = 0, isFinally = 0;

    const run = async (
      nowindex,
      isRestart = false,
      remainRestart = needRestart
    ) => {
      try {
        const nowindexRes = {
          status: "fullfilled",
          value: await taskList[nowindex](),
        };

        if (isRestart) result[nowindex].push(nowindexRes);
        else result[nowindex] = nowindexRes;
      } catch (err) {
        const nowindexErr = {
          status: "rejected",
          reson: err,
        };

        if (isRestart) result[nowindex].push(nowindexErr);
        else result[nowindex] = [nowindexErr];
      } finally {
        if (
          remainRestart > 0 &&
          result[nowindex]?.at?.(-1)?.status === "rejected"
        ) {
          run(nowindex, true, remainRestart - 1);
        } else {
          ++isFinally;

          if (isFinally >= taskList.length) resolve(result);
          else if (index < taskList.length) run(index++);
        }
      }
    };

    for (let i = 0; i < Math.min(maxConcurrent, taskList.length); i++)
      run(index++);
  });
}

// 测试 ——------------------------------------------------------------------------------
function delayTask(fn, ms) {
  return new Promise((resolve, reject) => {
    setTimeout(() => fn(resolve, reject), ms);
  });
}

const taskList = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9].map((item) => {
  return () => {
    return delayTask((resolve, reject) => {
      if (item % 3 === 0) reject(`err ${item}`);
      else resolve(item);
    }, Number.parseInt(Math.random() * 1000));
  };
});

myAllSettle(taskList, 3, 2).then((res) => {
  console.log(res);
});
```

# 8 新数据结构

Set 、Map 底层是用红黑树实现的。

### 8.1 Set

集合，成员的值是惟一的，有相同的会去重，具有iterator接口

```
const s0 = new Set();
const s1 = new Set([1, 2, 3]);

s0.add(1);
s0.delete(1);
console.log(s0, s0.size);

// true
console.log(s1.has(3));

s1.clear();
console.log(s1);
```

遍历，无法使用 for\.\.\.in ：

```
const s = new Set([1, 2, 3, 4]);

s.forEach((i) => {
  console.log(i);
});

for (const i of s) console.log(i);
```

实际应用：

```
// 数组去重
const arr = [1, 1, 2, 2, 3];
const arr0 = [...new Set([...arr])];

// 交集
const arr1 = [1, 1, 2, 2, 3];
const arr2 = [3, 4, 4, 5, 5];
const arr3 = [...new Set([...arr1])].filter((i) => new Set([...arr2]).has(i));

// 并集
let arr4 = [...new Set([...arr1, ...arr2])];

// 差集 (a-b a 有但 b没有)
const arr5 = [...new Set([...arr1])].filter((i) => !new Set([...arr2]).has(i));
```

WeakSet ：

与 Set 的区别就两个：

* 每个成员只能是引用类型：
  
  ```
  const ws = new WeakSet([[1, 2], { a: 123 }, new Date(), new Set()]);
  ```

* 每个成员都是弱引用：
  
  ```
  const s = new Set();
  const ws = new WeakSet();
  
  function test() {
    const o1 = { a: 123 };
    const o2 = { a: 456 };
  
    s.add(o1);
    ws.add(o2);
  }
  
  test();
  
  // Set 的成员是强引用，函数调用完成员还保持着对 {a:123} 的引用
  console.log(s);
  
  // WeakSet 是弱引用，函数调用完成员是否还保持着对 {a:456} 的引用得看垃圾回收有没有回收到这里
  console.log(ws);
  ```
  
  由于弱引用的不确定性，因此 WeakSet 的成员是否存在是不确定的，所以没有 size 和 clear\(\)，无法遍历。

### 8.2 Map

字典，键值对的集合，key 是唯一的，相同的 key 会覆盖前面的 key ，有 iterator 接口。

key 可以是任何数据类型，Symbol 类型的 key 也可以遍历出来。

```
const m1 = new Map();
const m2 = new Map([
  ["name", "asdf"],
  ["age", 23],
]);
const m3 = new Map(Object.entries({ a: 1, b: 2 }));

const obj = Object.fromEntries(m3);

m1.set("name", "qwer");
console.log(m1.get("name"), m1.has("name"), m1.size);

m1.delete("name");
m2.clear();
```

遍历，可以遍历出来 Symbol key ，无法使用 for\.\.\.in

```
const m = new Map([
  ["name", "asdf"],
  ["age", 23],
]);

m.forEach((i, k) => {
  console.log(i, k);
});

// [key, value]
for (const i of m) console.log(i);
```

实际应用：

```
// 统计出现个数

const arr = ["apple", "apple", "banana"];
const m = new Map();

for (const i of arr) {
  if (m.has(i)) m.set(i, m.get(i) + 1);
  else m.set(i, 1);
}

console.log(m);
```

WeakMap ：

与 Map 区别就两个：

* key 只能是引用类型，但 value 可以是任何数据类型

* key 时弱引用，没有 size 和 clear\(\) ，无法遍历

Vue3 的响应式系统的源码，采用了 WeakMap，是为了使不再使用的资源释放掉，来优化性能。

## 9 Class

解决 JS 函数二义性的另一个方案，实例对象专门由 class 的 constructor 构造。

class 里的 this 永远不会指向 window ，硬要指向 window 也会指向 undefined 。

ES6 的 class 功能比较简陋，ES13 才比较完善。

（1）ES6 class

基本使用：

```
// 声明，class 不会被提升
class A {
  // 构造函数
  constructor(a) {
    this.a = a;
    this.b = 2;
  }

  // 定义方法，方法内的 this 为实例对象
  func1() {
    console.log(this);
  }

  // 箭头函数，属于 func2 ，func2 所在的作用域时 class 内，所以 this 指向实例对象
  func2 = () => {
    console.log(this);
  };
}

const obj = new A(1);

// 1 2
console.log(obj.a, obj.b);

obj.func1();
obj.func2();
```

类的继承：

```
// 父类
class A {
  constructor(a) {
    this.a = a;
  }

  fatherFunc() {
    console.log("fatherFunc");
  }
}

//子类继承父类
class B extends A {
  constructor(a, b, c) {
    // 子类中必须有 super() 调用父类的 constructor ，才能使用 this
    super(a);

    this.b = b;
    this.c = c;
  }

  sonFunc() {
    // 调用父类的方法
    super.fatherFunc();
    console.log("sonFunc", "\n");
  }

  /* 重写父类方法
   * 内部无法使用 super() 调用父类同名方法
   */
  fatherFunc() {
    console.log("rewrite fatherFunc");
  }
}

const son = new B(1, 2, 3);

// 1 2 3
console.log(son.a, son.b, son.c);

son.sonFunc();
son.fatherFunc();
```

存取器：

子类会继承父类的存取器：

```
class A {
  // 定义 a 的存取器，就有了 _a 属性

  set a(newVal) {
    this._a = newVal;
  }

  get a() {
    return this._a;
  }
}

class B extends A {
  constructor(val) {
    super()._a = val;
  }
}

const obj = new A();
console.log(obj.a);

obj.a = 456;
console.log(obj.a);

const son = new B(789);
console.log(obj._a, son._a);
```

（2）ES13

可以在 constructor 外定义属性，也可以用公共实例字段定义属性：

```
let test = "Name";

class A {
  a = 123;
  b;

  // 公共实例字段定义属性
  [`user${test}`] = "ASDF";
}

const obj = new A();

console.log(obj.a, obj.b);

console.log(obj.userName);
```

私有属性、私有方法，用 \# 定义：

```
class A {
  // public
  name;

  // private
  #age;
  #run() {}

  constructor(name, age) {
    this.name = name;
    this.#age = age;
  }

  getAge() {
    return this.#age;
  }

  setAge(newAge) {
    this.#age = newAge;
  }
}

const obj = new A("asdf", 18);
console.log(obj.getAge());

obj.setAge(28);
console.log(obj.getAge());
```

静态属性、静态方法：

```
class A {
  static name = "class A";

  static func() {
    // this 还想类本身
    console.log(A.name);
    console.log(this.name);
  }
}

console.log(A.name);
A.func();
```

静态初始化代码块，可以有多个，在编译阶段就执行，由于是 static 的，所以只能调用 static 的属性和方法，在代码块你诶不定义的是局部变量和局部方法：

```
class Person {
  static a = "static";

  static {
    // this 指向类本身
    console.log(this.a);

    // 局部变量
    const b = 123;
  }
}

// undefined
console.log(Person.b);
```

in ，判断类中是否有某个属性和方法：

```
class A {
  a;
  func() {}

  #b;

  static c;
  static #d;

  hasB(obj) {
    console.log(#b in obj);
  }

  static hasD() {
    console.log(#d in A);
  }
}

const obj = new A();

// public 属性和方法需要加 ""
console.log("a" in obj, "func" in obj);
console.log("c" in A);

// private
obj.hasB(obj);
A.hasD();
```

（3）ES5 继承

```
function Person(name) {
  this.name = name || "person";
  this.run = function () {
    console.log("run");
  };
}
Person.prototype.msg = "msg";

/**原型链继承
 * 优点：可继承父类原型
 * 缺点：无法多继承；无法继承方法；无法给父构造函数传参
 */
function SonA(age) {
  this.age = age || 18;
}
SonA.prototype = new Person("a");

const a = new SonA(18);
// { age } name msg
console.log(a, a.name, a.msg, "\n");

/**构造函数继承
 * 优点：可以给父构造函数传参；可用搓个 call 实现多继承
 * 无法继承父类原型
 */
function SonB(name, age) {
  Person.call(this, name);
  this.age = age || 18;
}

// { name, age, run() } undefined
const b = new SonB("b", 18);
console.log(b, b.msg, "\n");

/**组合继承
 * 原型链继承 + 构造函数继承
 * 结合优点，去掉缺点
 */
function SonC(name, age) {
  Person.call(this, name);
  this.age = age || 18;
}
SonC.prototype = new Person();

const c = new SonC('c"', 18);
// { name, age, run() } msg
console.log(c, c.msg);
```

（4）实现私有属性

ES6 的存取器使用 \_name 在命名上区分私有属性，但约束力不强；用 Symbol key 实现私有属性和也有办法访问。 

ES13 有 \# 可以实现，且是运行时，不过由于是新特性，可能有兼容性问题。

TypeScript 中的 private 只是编译时，编译后的 JS 也没有使用 \# ，且就算再 ts 中，也有办法可以使用动态属性绕过检查：

```
class A {
  private a = 5;
}

const obj = new A();
console.log(obj["a"]);
```

自己实现可以使用立即执行函：

```
class A {
  // 立即执行函数，防止外部访问私有属性
  privateFields = (function () {
    const fields = {
      a: 1,
    };

    // 闭包，防止 fields 被垃圾回收
    return {
      get: (key) => {
        // 防止从原型上访问，只有 key 时 privateFields 有的属性时，才允许访问
        if (fields.hasOwnProperty(key)) return fields[key];
      },
      set: (key, newValue) => {
        if (fields.hasOwnProperty(key)) fields[key] = newValue;
      },
    };
  })();
}

const obj = new A();

// 1
console.log(obj.privateFields.get("a"));

// 2
obj.privateFields.set("a", 2);
console.log(obj.privateFields.get("a"));

// 测试从原型上访问
Object.defineProperty(Object.prototype, "abc", {
  get() {
    return this;
  },
});
obj.privateFields.set("a", 3);
console.log(obj.privateFields.get("abc")?.a);
```

或者使用模块化，把私有属性存放在 WeakMap ：

```
// 用 WeakMap 而不是 Map、Object ，是为了垃圾回收对象时，同时也会受 WeakMap 的元素
const privateFields = new WeakMap();

export default class {
  constructor() {
    privateFields.set(this, { a: 1 });
  }

  getPrivateFields = () => privateFields.get(this);
}
```

## 10 模块化、其他

### 10.1 模块化

解决导入多个 JS 文件后冲突的问题。模块化的核心是导入、导出。

ES5 模块化：

```
<script type="module" src="..."></script>
<script type="module">
  import ... from '...'
</script>
```

模块化规范：ES6 ，CommonJS ，AMD ，CMD 。其中 AMD 用在 requireJS ，CMD 用在 sealS ，不太常用。

绝对路径：完整的路径

相对路径：\./ 当前目录 ，\.\./ 上一级目录 ，\.\./\.\./ 上两级目录。

（1）ES6 模块化

方式一：

```
// 1.js
const a = 1, b = 2;
export { a, b };
```

```
// 2.js
export const c = 3;
```

```
// 3.js
const { a, b } from "./1.js";
```

```
// 4.js
export * from "./1.js";
```

```
import { a, b } from "./1.js";
import { c } from "./2.js";

console.log(a, c);
```

```
import * as js1 from "./1.js";
import * as js2 from "./2.js";

console.log(js1.a, js2.c);
```

方式二：

default 一个文件只能有一个：

```
// 1.js
export default a = 1;
```

```
import js1 from "./1.js";
// 1
console.log(js1);
```

（2）CommonJS 模块化

nodejs ，Browserify 使用。

```
// 1.js
const a = 1, b = 2;
module.exports = {
  a, b
}
```

```
const { a, b } = require("./1.js");
```

（3）新特性

ES11 新特性，动态 import

ES6的是静态 import，这里的动态 import 实现按需加载（懒加载）：

```
import(‘./1.js’).then(res => {
  console.log(res);
})

// 路由懒加载
const a = import(‘xxx’);
```

ES11 新特性，import.meta

是一个 JS 模块暴漏的特定上下文的元数据的对象，包含了这个模块的信息，如模块的 url ：

```
console.log(import.meta);
```

### 10.2 其他

ES10 新特性，catch 不再必须传入形参：

```
try {
} catch () {}
```

ES12 新特性，WeakRef ，得到一个对象的弱引用：

```
const obj = { a: 1 };
const wr = new WeakRef(obj);

// { a: 1 } ，若 obj 被垃圾回收了，则是 undefined
console.log(wr.deref());
```

ES13 新特性，Error Cause

proposal-error-cause 这一提案，目的主要是为了便捷的传递导致错误的原因，如果不使用这个模块，想要清晰的跨越多个调用栈传递错误上下文信息，通常要这么做：

```javascript
async function doJob() {
  const rawResource = await fetch('//domain/resource-a')
    .catch(err => {
      // How to wrap the error properly?
      // 1. throw new Error('Download raw resource failed: ' + err.message);
      // 2. const wrapErr = new Error('Download raw resource failed');
      //    wrapErr.cause = err;
      //    throw wrapErr;
      // 3. class CustomError extends Error {
      //      constructor(msg, cause) {
      //        super(msg);
      //        this.cause = cause;
      //      }
      //    }
      //    throw new CustomError('Download raw resource failed', err);
    })
  const jobResult = doComputationalHeavyJob(rawResource);
  await fetch('//domain/upload', { method: 'POST', body: jobResult });
}

await doJob(); // => TypeError: Failed to fetch
```

而按照这一提案的语法：

```javascript
sync function doJob() {
  const rawResource = await fetch('//domain/resource-a')
    .catch(err => {
      throw new Error('Download raw resource failed', { cause: err });
    });
  const jobResult = doComputationalHeavyJob(rawResource);
  await fetch('//domain/upload', { method: 'POST', body: jobResult })
    .catch(err => {
      throw new Error('Upload job result failed', { cause: err });
    });
}

try {
  await doJob();
} catch (e) {
  console.log(e);
  console.log('Caused by', e.cause);
}
// Error: Upload job result failed
// Caused by TypeError: Failed to fetch
```

# 四、JS 高级

## 1 JS 执行机制

执行上下文：就是执行栈。

### 1.1 事件循环

事件循环（event loop），也叫消息循环（message loop）。

（1）浏览器进程模型

最重要的 3 个进程：

* 浏览器进程：处理浏览器自身

* 网络进程：处理网络传输

* 渲染进程：处理 HTML 、CSS 的渲染，JS 的执行等。一个页面会开启一个渲染进程，渲染进程中只有一个渲染主线程

由于每个页面都会开启一个渲染进程，会消耗很多内存，所以在未来，浏览器会做改进，让一个站点共用同一个渲染进程。

（2）单线程与同步、异步

JS 是单线程的，这是因为 JS 运行在浏览器的渲染主线程中，而渲染主线程只有一个，渲染主线程又承担很多工作，如渲染页面，执行 JS 等。如果只使用同步方式，JS 就有可能阻塞其他的工作。

JS 阻塞渲染的例子：

```
<!DOCTYPE html>
<html lang="en">
  <body>
    <div><button id="btn">变大</button></div>
    <p id="box" style="font-size: 20px">asdf</p>
  </body>

  <script>
    function delay(ms) {
      var start = Date.now();
      while (Date.now() - start < ms) {}
    }

    var box = document.querySelector("#box");
    var btn = document.querySelector("#btn");

    btn.addEventListener("click", function () {
      // 3s 后才会改变字体大小，因为被 JS 阻塞了
      box.style.fontSize = "50px";
      delay(3000);
    });
  </script>
</html>
```

因此就需要异步，当 JS 执行时，若遇到异步任务，就会把异步的回调函数包装成任务（浏览器源码中任务是一个结构体），入队到消息队列中等同步任务执行完再执行，实现永不阻塞。

遇到定时器会交给计时线程进行计时，遇到事件会交给交互线程进行监听。

JS 异步任务分类：

* 微任务：对应微队列，处理 Promise 的回调函数，优先级最该，甚至比页面渲染还高

* 宏任务：对应红队列，处理定时器、事件、ajax、文件 IO 等

由于现在的项目越来越复杂，宏队列已经不够用了，因此在 W3C 最新标准中，去掉了宏任务的概念，新增了延时队列、交互队列、网络队列等：

* 不同任务类型的任务允许放到一个队列中；但所有同一个类型的任务只能存在于一个队列中

* 标准中没有规定队列的优先级，具体如何执行由浏览器决定，不过一般会认为：交互队列 \> 延时队列 \> 网络队列

但微队列不变，优先级最高。

（3）任务执行顺序

自上而下执行，遇到异步任务就入队到对应的消息队列，当执行完所有同步任务后，开始事件循环，事件循环在源码中就是一个死循环，不断查看是否有异步任务需要执行。

多个队列都有任务时，按照消息队列的优先级执行，只要优先级高的队列还有任务，就先执行它。

node 环境中海油 2 个 api ，在特定的节点执行，只执行一次：

```
// 所有同步任务完成后，微任务之前执行
process.nextTick(() => {
  console.log(1);
});

Promise.resolve().then(() => {
  console.log(2);
});

// 第一次事件循环结束后执行
setImmediate(() => {
  console.log(5);
});

// 由于计算机的性能不同，执行完所有同步任务的时间也不同，3 4 在浸入事件循环时已经瑞对，而 6 还未入队
setTimeout(() => console.log(3), 0);
setTimeout(() => console.log(4), 0);
setTimeout(() => console.log(6), 10);

// res：1 2 3 4 5 6
```

顺序：

* 执行完所有同步任务

* process\.nextTick\(\) 的回调

* 开始事件循环，每次循环执行一个任务
  
  * 执行完所有微任务
  
  * 执行宏任务，此后的首次循环结束执行 setImmediate() 的回调 ，这个回调只执行一次。执行宏任务过程中，若入队了新的微任务，则下一个循环就开始执行微任务
  
  * 若不适用宏任务的概念，则若入队了优先级更高的队列，下一次循环就执行这个队列的任务

定时器：

* 定时器在遇到时就开始计时，计时完毕就把回调函数入队
  
  ```
  const delay = (ms) => {
    const start = Date.now();
    while (Date.now() - start < ms) {}
  };
  
  setTimeout(() => {
    console.log(1);
  }, 0);
  
  // 0s 把回调函数包装成任务入队延时队列 3s 后输出 2 1
  delay(3000);
  console.log(2);
  ```

* 定时器设置为 0ms 也是一步任务，延时参数默认值是 0ms 

* 相同延时的定时器，按照代码先后顺序入队

* 定时器无法做到精确计时，因为：
  
  * 计算机硬件本身就有微小偏差
  
  * 定时器函数调用的操作系统的函数，本身也有微小偏差
  
  * W3C 标准中规定，若嵌套超过 5 层，从第 6 层开始，若 \< 4ms ，则会自动变成 4ms ：
    
    ```
    setTimeout(() => {
      console.log(1);
    
      setTimeout(() => {
        console.log(2);
    
        setTimeout(() => {
          console.log(3);
    
          setTimeout(() => {
            console.log(4);
    
            setTimeout(() => {
              console.log(5);
    
              setTimeout(() => {
                console.log("4ms");
              }, 0);
            }, 0);
          }, 0);
        }, 0);
      }, 0);
    }, 0);
    ```

* JS 执行同步任务也需要时间，计时完成可能同步任务还没有完成

大致模拟事件循环的过程：

```
const sync = () => {
  console.log("同步任务");
};

// 微队列
const microQueue = [
  () => {
    console.log("Promise 1");
  },
  () => {
    console.log("Promise 2");
  },
];

// 宏队列
const macroQueue = [
  () => {
    console.log("timeout 1");

    microQueue.push(() => {
      console.log("Promise 3");
    });

    macroQueue.push(() => {
      console.log("timeout 3");
    });
  },
  () => {
    console.log("timeout 2");
  },
];

// 执行顺序 ---------------------------------------------------------------
let isFirst = true;

sync();

console.log("process.nextTick");

// 事件循环
for (;;) {
  while (microQueue.length > 0) {
    microQueue[0]();
    microQueue.shift();
  }

  while (macroQueue.length > 0 && microQueue.length === 0) {
    macroQueue[0]();
    macroQueue.shift();
  }

  if (isFirst) {
    console.log("setImmediate", "\n");
    isFirst = false;
  }
```

（4）JS 执行顺序的案例

```
async function fun2() {
  console.log("d");
}

async function fun1() {
  console.log("c");
  await fun2();
  console.log("e");
  await fun2();
  console.log("f");
}

setTimeout(() => console.log(1)); //不给时间，默认0

console.log(2);

setTimeout(() => console.log(3), 0);

setTimeout(() => console.log(4), 100);

console.log(5);

new Promise((resolve) => {
  resolve();
}).then(() => {
  console.log("a");
  new Promise((resolve) => {
    resolve();
  }).then(() => {
    console.log("b");
  });
});

new Promise((resolve) => {
  console.log(6);
  resolve();
}).then(() => {
  console.log(7);
});

process.nextTick(() => {
  console.log(8);
});

setImmediate(() => {
  console.log(9);
});

fun1();

//执行顺序：256cd8a7e1394
/**�򵥽���
2 5 6 c d   同步任务
8           process.nextTick()
a 7 e d b f 微任务
1 3         事件轮循第一次循环，0ms 的定时器一定在第一次循环中执行
9           setImmediate()
4           第二重事件循环的宏任务
**/
```

```
async function f2() {
  setTimeout(() => {
    Promise.resolve().then(() => {
      console.log(22);
    });
    console.log(2);
  }, 100);
}

async function f1() {
  console.log(1);
  await f2();
  console.log(11);
}

async function f0() {
  Promise.resolve().then(() => {
    console.log(0);
  });
}

f1();
f0();

/* res
 * 1      同步
 * 11 0   微任务
 * 2      宏任务
 * 22     宏任务中遇到的新的微任务
 */
```

```
async function f2() {
  await setTimeout(() => {
    Promise.resolve().then(() => {
      console.log(22);
    });
    console.log(2);
  }, 100);
}

async function f1() {
  console.log(1);
  await f2();
  console.log(11);
}

async function f0() {
  Promise.resolve().then(() => {
    console.log(0);
  });
}

f1();
f0();

/* res，与上一个案例唯一区别就是 await 定时器，定时器返回 timeid ，自动转换成 awai Promise.resolve(timeid)
 * 1      同步
 * 0 11   微任务
 * 2      宏任务
 * 22     宏任务中遇到的新的微任务
 */
```

```
async function f2() {
  await setTimeout(async () => {
    await (async () => {
      await 1;
      console.log(22);
    })();
    console.log(2);
  }, 100);
}

async function f1() {
  console.log(1);
  await f2();
  console.log(11);
}

async function f0() {
  Promise.resolve().then(() => {
    console.log(0);
  });
}

f1();
f0();

/* res，与上一个案例唯雷瑟，await xxx ，当 xx 不是 Promise 时，自动转为 await Promise.resolve(xxx)
 * 1      同步
 * 0 11   微任务
 * 22 2     宏任务
 * 2        宏任务中遇到的新的微任务
 */
```

```
Promise.resolve()
  .then(() => {
    console.log(1);
    return Promise.resolve(5);
  })
  .then((res) => {
    console.log(res);
  });

Promise.resolve()
  .then(() => {
    console.log(2);
  })
  .then(() => {
    console.log(3);
  })
  .then(() => {
    console.log(4);
  })
  .then(() => {
    console.log(6);
  });

/* res：1 2 3 4 5 6
 * 关键在于，then 中手动 return 了一个 Promise，微任务入队顺序如下：
 * 队; 1 2 , print:
 * 队; 2 Promise.resolve().then(() => ...) ,   print: 1
 * 队; Promise.resolve().then(() => ...) 3  , print: 1 2
 * 队: 3 ()=>... print: 1 2
 * 队: () => ... 4 print: 1 2 3
 * 队: 4 () => console.log(5) print: 1 2 3
 * ...
 *
 *
 */
```

（5）事件流

事件处理包括事件捕获、事件冒泡两个阶段。默认情况下，事件在冒泡阶段触发。

- 事件捕获：从 DOM 树根结点出发到叶子结点捕获事件

- 事件冒泡：从触发事件的对象出发，到根结点，若该事件对象的祖先有定义相同事件，则也会触发：
  
  ```
  <!DOCTYPE html>
  <html lang="en">
    <head>
      <style>
        .box {
          border: 1px solid #000;
        }
  
        .big {
          width: 200px;
          height: 200px;
          background-color: #000;
        }
  
        .mid {
          width: 100px;
          height: 100px;
          background-color: #00f;
        }
  
        .small {
          width: 50px;
          height: 50px;
          background-color: #f00;
        }
      </style>
    </head>
    <body>
      <div class="big box">
        <div class="mid box">
          <div class="small box"></div>
        </div>
      </div>
    </body>
    <script>
      /**
       * 当 click small 时，3 个事件都会触发
       * 可以用 e.stopPropagation() 关闭事件冒泡
       */
  
      var big = document.querySelector(".big");
      var mid = document.querySelector(".mid");
      var small = document.querySelector(".small");
  
      big.addEventListener("click", function () {
        console.log("big");
      });
  
      mid.addEventListener("click", function () {
        console.log("mid");
      });
  
      small.addEventListener("click", function (e) {
        // e.stopPropagation();
        console.log("small");
      });
    </script>
  </html>
  ```

利用事件冒泡，当有很多子元素需要绑定相同事件，可以只把这个事件绑定到父元素，让父元素做事件委托，减少事件绑定数，提高性能：

```
<!DOCTYPE html>
<html lang="en">
  <head> </head>
  <body>
    <ul class="list">
      <li data-id="1">1</li>
      <li data-id="2">2</li>
      <li data-id="3">3</li>
    </ul>
  </body>
  <script>
    var list = document.querySelector(".list");
    var items = document.querySelector(".item");

    list.addEventListener("click", function (e) {
      // 只有 click li 时，才处理
      if (!e.target.getAttribute("data-id")) return;

      console.log(e.target.innerText);
    });
  </script>
</html>
```

### 1.2 浏览器渲染原理

渲染，将一个 HTML 字符串（HTML 文档）转变成页面像素信息的过程。

（1）渲染过程

浏览器的网络进程拿到 HTML 文档后，产生一个渲染任务，交给渲染主线程的消息队列，在事件循环机制的作用下，渲染主线程取出渲染任务并处理：

```
const html = "<div>...</div>";
```

渲染主线程解析 HTML 字符串，当解析到 \<style\> 和 \{link\> 的 CSS 时，会交给渲染进程中的与解析现成异步解析 CSS ，所以 CSS 不会阻塞 HTML 的解析；而解析到 \<script\> 时，渲染主线程会去下载或执行 JS，之所以解析 JS 不是异步的，是因为 JS 可能修改 HTML ，因此 JS 才会造成解析 HTML 的阻塞：

```
const html = `
<!DOCTYPE html>
<html lang="en">
  <head>
    预解析现成异步解析 CSS
    <style></style>
    <link />

    渲染主线程同步下载或执行 JS
    <script></script>
  </head>
  <body></body>
</html>
`;
```

生成 DOM 顺（DOM Object Model）和 SOM 树（CSS Object Model），都是对象，方便后续处理，同时让 JS 有操作 HTML 、CSS 的能力：

```
// dom 树的根结点
console.log(document);

// SOM 树，是一个森林，根结点时各个样式表（内部、外部、行内、浏览器默认样式表）
console.log(document.styleSheets);
```

样式计算：遍历 DOM 树，每个结点进行样式计算，得到每个节点计算后的最终的样式 computed style（所有 CSS 属性都要有 value ，且都是绝对单位，如 em 变 px ，string 的 color 变 rgb\(\)），最后得到有样式的 DOM 树：

```
// 得到计算后的最终样式
getComputedStyle();
```

布局：遍历 DOM 树，根据样式计算出几何信息（尺寸、相对于包含块的位置），得到布局树（Layout Tree），大部分时候 DOM 树和布局树会不同，因为：

* 隐藏的节点没有集合信息，不会出现在布局树中

* 伪元素是 CSS 产生的，不会出现在 DOM 树中，但会出现在布局树中

* 内容只能在行盒中，行盒、块盒不能在同一级，若出现了这些情况，布局树中会用匿名行盒、匿名快盒填充，这些匿名盒子是不会渲染的

```
// 可以获取部分布局树的信息
console.log(body.clientWidth);
```

分层：渲染主线层使用一条复杂的规则进行分层，好处是在将来某一层改变时仅会处理该层，提升性能，但分层不会太多，因为会加大内存消耗，具体分几层由浏览器决定：

```
.box {
  /* 堆叠上下文的属性可能会影响分层，如以下属性 */
  opacity: 1;
  z-index: 9;
  transform: translate(-50%, -50%);

  /* 这个属性告诉浏览器可能会经常变动，需要单独分一层，但具体分不分，由浏览器决定 */
  will-change: transform;
}
```

生成绘制指令：每一层单独生成绘制指令集（类似 \<canvas\>），用来描述这一层如何绘制。

至此，渲染主线程工作结束，将每层的绘制指令交给渲染进程的合成线程：

* 分块：合成线程从线程池中启动多个线程，共同将每一层分成一个个小块，并把每一个小块交给 GPU 进程进行光栅化

* 光栅化：生成包含像素信息的位图（优先光栅化视口附近的分块），交换给合成线程，合成线程生成指引信息（指引把位图花在屏幕的位置），交给硬件

（2）添加 DOM

```
<!DOCTYPE html>
<html lang="en">
  <body></body>
  <script>
    // 方式一，性能最低，因为要从解析字符串开始
    var div1 = "<div>1</div>";
    document.body.innerHTML = div1;

    // 方式二，性能一般
    var div2 = document.createElement("div");
    div2.textContent = "2";
    document.body.appendChild(div2);

    // 方式三，性能最高，先存储在文档片段中，再一次性 appendChild
    // 文档片段自身不会被渲染
    var frag = document.createDocumentFragment();
    var div3 = document.createElement("div");
    div3.textContent = "3";
    frag.appendChild(div3);
    document.body.appendChild(frag);
  </script>
</html>
```

（3）回流、重绘

区别：

* reflow，也叫重排，本质是当修改了影响几何信息的属性（windth、font-size、display、margin 等等），就会重新计算 Layout Tree ，性能下降：

* repaint，本质是修改了不影响几何信息的属性（如 color），就会在分层阶段开始计算绘制指令，由于在布局之后，所以 reflow 必然 repaint ，反之则不会：

reflow 、repaint 都会产生一个异步的 redner 任务入队到消息队列，优先级：微任务 \< render \< 宏任务 ：

```
<!DOCTYPE html>
<html lang="en">
  <body>
    <div>
      <button id="btn1">btn 1</button>
      <button id="btn2">btn 2</button>
    </div>
    <p id="box" style="font-size: 20px">asdf</p>
  </body>

  <script>
    function delay(ms) {
      var start = Date.now();
      console.log("delay...");
      while (Date.now() - start < ms) {}
      console.log("delay end");
    }

    var box = document.querySelector("#box");
    var btn1 = document.querySelector("#btn1");
    var btn2 = document.querySelector("#btn2");

    // 浏览器为了提高性能，会把相邻的样式修改作为同一个渲染任务，防止多次不必要的 reflow 、repaint
    btn1.addEventListener("click", function () {
      // reflow
      box.style.fontSize = "30px";
      box.style.fontSize = "40px";
      box.style.fontSize = "50px";

      // repaint
      // box.style.backgroundColor = "#f00";
      // box.style.backgroundColor = "#0f0";
      // box.style.backgroundColor = "#000";

      Promise.resolve().then(() => {
        console.log("微任务");
        delay(3000);

        Promise.resolve().then(() => {
          console.log("微任务");
          delay(3000);
          console.log("render");
        });
      });

      setTimeout(() => {
        console.log("宏任务");
        delay(3000);
      }, 0);

      delay(3000);
    });

    /**强制 revlow 、repaint
     * 只要访问呢了几何信息，就会强制 reflow ，同步得到修改后的样式，，但渲染还是要等异步
     * 只要访问了非几何信息的样式，就会强制 repaint，同步得到新的样式，但渲染还是要等异步
     */
    btn2.addEventListener("click", function () {
      box.style.fontSize = "30px";
      box.clientWidth;
      delay(3000);
      box.style.fontSize = "40px";
      delay(3000);

      // box.style.backgroundColor = "#f00";
      // getComputedStyle(box).backgroundColor;
      // delay(3000);
      // box.style.backgroundColor = "#000";
      // delay(3000);
    });
  </script>
</html>
```

（4）transform

transform 是在合成现成中起作用的，已经是渲染的后期了，又不会 reflow 、repaint，又不在渲染主线程，所以性能非常高：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      .container {
        position: relative;
        width: 1000px;
        height: 500px;
        border: 1px solid #000;
      }

      .box {
        position: relative;
        margin-top: 100px;
        width: 100px;
        height: 100px;
        border: 1px solid #000;
        border-radius: 50px;
        background-color: red;
      }

      @keyframes move1 {
        to {
          transform: translate(200px);
        }
      }

      @keyframes move2 {
        from {
          left: 0;
        }
        to {
          left: 200px;
        }
      }

      /* 不会卡死，不 reflow 、repaint ，又不在渲染主线程 */
      .box1 {
        animation: move1 1s alternate infinite ease-in-out;
      }

      /* 卡死，引发了 reflow ，又在渲染主线程 */
      .box2 {
        animation: move2 1s alternate infinite ease-in-out;
      }
    </style>
  </head>
  <body>
    <div class="container">
      <div><button id="btn">卡死 3s</button></div>
      <div class="box box1"></div>
      <div class="box box2"></div>
    </div>
  </body>
  <script>
    function delay(ms) {
      var start = Date.now();
      while (Date.now() - start < ms) {}
    }

    var btn = document.querySelector("#btn");

    btn.addEventListener("click", function () {
      delay(3000);
    });
  </script>
</html>
```

浏览器滚动也不会 reflow、repaint ，所以不会被 JS 阻塞。

### 1.3 作用域

（1）作用域、预编译

三种作用域：

* 全局作用域

* 局部作用域，即函数内部

* 块级作用域，if 、for 等内部，let 、const 具有块级作用域，而 var 没有。

预编译，也叫与解析，JS 运行分为预编译和编译运行两部分。在预编译阶段，会有变量提升，作用是提升具名函数的声明定义，和没有块级作用域的 var 生命到代码最上方：

```
// undefined 10 ，var 只提升声明，不提升赋，且只能；let 、const 不提升
console.log(a);
var a = 10;
console.log(a);

// 1 ，提升了声明和定义，但只能提升具名函数
func();
function func() {
  console.log(1);
}

// 10 ，被提升了
var i = 0;
for (var i = 0; i < 10; i++) {}
console.log(i);
```

没有用 var、let、const 声明的情况：

```
/**
 * 若 var、let、const 都未使用，则必须赋值，否则报错；
 * 若上述情况已赋值，则等价于 window.xxx (浏览器)，globalThis.xxx (node，且未再次用 var 定义)
 * 浏览器中全局变量 var 和具名 func 会加入 window ；node 则不会
 * 全局中使用资源默认省略 window (浏览器)，globalThis (node)
 */

a = 10;

function func1() {
  b = 20;
}
func1();

// 浏览器 10 20
// console.log(window.a, window.b);
// node 10 20
// console.log(globalThis.a, globalThis.b);

var c = 30;
var d = 40;
c = 50;

function func2() {
  d = 60;
}
func2();

// 浏览器 50 60
// console.log(window.c, window.d);
// node undefined undefined
// console.log(globalThis.c, globalThis.d);

function func1() {
  e = 70;

  function func2() {
    console.log(this.e);
  }
  func2();
}

// 70 func2 独立调用 this 为 window （node 为 globalThis），而 e 没有用 var ，挂在了 window (node 是 globalThis)
func1();

// 省略了 window (node 是 globalThis)
console.log(e);
```

在 ES5 只有 var ，又有变量提升，就会有很多问题，如重复定义不报错、先使用后定义不报错等，又比如 for 中的 var 被提升了等问题，在以前是用立即执行函数形成局部作用域解决的：

```
var i = 0;

(function () {
  for (var i = 0; i < 10; i++) {}
})();

// 0
console.log(i);
```

现在直接用 let 、const 即可。

若想防止全局污染（全局暴漏），也可以使用立即执行函数形成局部作用域：

```
(function () {
  var a = 10;
})();
```

作用域链：

类似原型链，用于查找变量，先从自己作用域开始，直到全局，找不到就是 undefined 。规则：

- 内部可以访问外部变量，反之不行；访问的是最近一级作用域的变量

- 只与定义函数时油管，与调用无关
  
  ```
  function func1() {
    var a = 1;
  
    return function () {
      console.log(a);
    };
  }
  
  function func2() {
    var a = 2;
    func1()();
  }
  
  // 1
  func2();
  ```

（2）闭包

闭包是编译原理中的概念，只要 Function 内部中 return 的内容有 Function，且内部 Function 使用了外部 Function 的资源，内部 Function 就变成了闭包，使用的外部 Function 的资源就不会被垃圾回收，只回收内部 Function 未使用的资源：

```
const func1 = (...args) => {
  let num = 0;
  return () => console.log(args[0]++, num++);
};

const func2 = (...args) => {
  let num = 0;
  return {
    getNum: () => console.log(args[0]++, num++),
  };
};

let f1 = func1(0), f2 = func2(0);

// 0 0 0 0
f1();
f2.getNum();

// 1 1 1 1 ，局部变量和形参都没有被回收
f1();
f2.getNum();

// 删除闭包，手动回收资源
f1 = null;
f2.getNum = null;
```

闭包优缺点：

* 优点：可以在外面按照自己的规则访问函数的资源，且闭包不会被垃圾回收，防止生成闭包后，函数内的资源回收而访问不到

* 缺点：不会被垃圾回收，就会加大内存消耗，低版本 IE 则会内存泄漏，解决方法是把不适用的闭包设为 null

（3）防抖、节流

有对应的库：

```
npm install --save lodash
```

防抖、节流的作用都是为了限制执行次数，减少函数不必要的执行，优化性能，区别是：

- 防抖：只允许在一段时间内执行一次

- 节流：在一段时间内只允许最多执行 n 次

防抖案例，输入框 input 只需要最终的 string 就行，不需要每次输入都调用一次函数：

```
<body>
  <input type="text" />
</body>

<script>
  const debunce = (fn, delay = 1000) => {
    let t = null;

    return function (...args) {
      clearTimeout(t);
      t = setTimeout(() => fn.call(this, ...args), delay);
    };
  };

  const inp = document.querySelector("input");

  inp.addEventListener(
    "input",
    debunce(function () {
      console.log(this.value);
    })
  );
</script>
```

节流案例，减少浏览器滚动事件的频率：

```
<body>
  <div style="height: 5000px"></div>
</body>

<script>
  const throttle = (fn, delay = 1000) => {
    let timer = null;

    return function (...args) {
      if (!timer) {
        fn.call(this, ...args);
        timer = setTimeout(() => (timer = null), delay);
      }
    };
  };

  window.addEventListener(
    "scroll",
    throttle(function () {
      console.log(123);
    }, 1000)
  );
</script>
```

有些场景防抖、节流都不合适，如上拉加载更多，这时候就用一个 flag 判断是否执行即可。

封装防抖、节流：

```
npm install --save @types/node
```

```
export default class Debunce {
  public static debunce = <T extends any[]>(
    func: (...args: T) => any,
    delay: number = 1000,
    immediate: boolean = false
  ) => {
    let timer: number | null = null;
    let isFirst = true;

    return function (...args: T): void {
      // 是否需要一开始就执行一次
      if (isFirst && immediate) {
        isFirst = false;
        func.call(this, ...args);
      } else {
        clearTimeout(Number(timer));
        timer = setTimeout(() => func.call(this, ...args), delay);
      }
    };
  };

  public static throttle = <T extends any[]>(
    func: (...args: T) => any,
    delay: number,
    immediate: boolean = false
  ) => {
    let timer: number | null = null;
    let isFirst = true;

    return function (...args: T): void {
      if (isFirst && immediate) {
        isFirst = false;
        func.call(this, ...args);
      } else if (timer) {
        func.call(this, ...args);
        timer = setTimeout(() => (timer = null), delay);
      }
    };
  };
}
```

### 1.4 垃圾回收机制

为了防止内存泄漏，js会对没有使用或不再使用的资源自动地进行回收来释放内存，遵循以下基本规则

- 全局的资源不会回收，除非手动释放或关闭网页。手动释放如下：
  
  ```
  /*此时
  栈内存划分一块内存给obj，存储堆内存中{a:1}的地址（引用）
  堆内存划分一块内存给{a:1}，存放{a:1}
  */
  let obj = {a: 1};
  
  /*
  手动释放，obj赋成别的值，一般是null
  原理就是使得{a:1}不再被使用，其他地方也没有引用{a:1}，就回收了
  */
  et obj = null;
  ```

- 函数执行完则函数内的资源会被回收。

- 闭包使用的资源不会被回收。

如果是引用类型，还需要考虑强引用和弱引用：

强引用：

大部分情况都是强引用，如：

```
//obj强引用了{a:1}
let obj = {a:1};
```

强引用的情况下，若垃圾回收了其中一个引用（如函数调用完），或丢失了引用（如赋值为null），则：

* 若{a:1}不再被任何东西引用，将会被回收

* 反之只要有任何东西还在引用它，就不回收

```
//下面由于没有任何东西再引用{a:1}，就会回收并释放内存
//obj丢失了对{a:1}的引用且没有东西再引用{a:1}了，就户籍手{a:1}
let obj = {a:1}
obj = null
//函数调用完，回收ooo，{a:2}也因为没有东西再引用它，就回收
function test1(){
  let ooo = {a:2};
}
test1();


//下面由于还有东西在引用，就不回收
//o1赋值为null求实了对{a:1}的引用，但是{a:1}已经被o2引用了，所以不回收{a:1}
let o1 = {a:1};
let o2 = o1;
o1 = null;
//函数调用完回收了ooo，但是{a:2}已经被o引用了，所以不回收{a:2}
let o = null
function test2(){
  let ooo = {a:2};
  o = ooo;
}
test2();
```

弱引用：

目前js的弱引用只出现在WeakSet和WeakMap，详见对应的笔记。

简单的说，若垃圾回收了其中一个引用（如函数调用完），或丢失了引用（如赋值为null），则，那么不管其引用的东西是否还再被其他东西引用，都会回收。

需要注意的是，垃圾回收是优先级很低的线程，所以弱引用引用的东西在看的时候可能还未被回收，还在回收的路上，但是最终都会回收。

可以看出，强引用由于可能会有不被垃圾回收的情况，所以可能会出现内存泄漏；而弱引用则没有内存泄漏的问题。

## 2 面向对象

### 2.1 原型

（1）原型、原型链

原型是一个对象，所以也叫原型对象。任何一个实例对象通过隐式原型属性 \_\_proto\_\_ ，任何一个构造函数通过显示原型属性 prototype ，就能访问到原型，实例对象和它的构造函数指向的是同一个原型对象：

```
function Person(name, age) {
  this.name = name;
  this.age = age;
}

const p = new Person("asdf", 18);

// true ，实例对象 p 的隐式原型属性和它的构造函数 Person 的显示原型属性指向的同一个对象，就是原型
console.log(p.__proto__ === Person.prototype);

const obj = { a: 1 };

// true ，字面量对象本事是 new Object()
console.log(obj.__proto__ === Object.prototype);

// 原型对象也是对象，也有原型，而这个原型对象是 Object 构造的
// true
console.log(Person.prototype.__proto__ === Object.prototype);

// Object 的原型不再有原型，指向 null
// null
console.log(Object.prototype.__proto__);
```

数组、函数等都是对象：

```
const arr = [];
const func = () => {};

// true true
console.log(arr.__proto__ === Array.prototype);
console.log(func.__proto__ === Function.prototype, "\n");

// true true ture ，它们的原型对象的原型，即 Object 的原型
console.log(Array.prototype.__proto__ === Object.prototype);
console.log(Function.prototype.__proto__ === Object.prototype);
console.log(Number.prototype.__proto__ === Object.prototype);
```

原型链，从一个实例对象，到原型，再到 Object 的原型，最后到 null ，形成的链条就是原型链：

```
obj -----> constructor func -- prototype --> 原型 ----> Object -- prototype --> Object 的原型 -----> null
 |                                            |           |                          |
 |--------------- __proto__ ----------------->|           |----------- _proto_ ----->|-
```

原型链的作用是查找属性和方法，当对象自身不存在该属性，会去原型上找，直到 Object 的原型中都没有时，返回 undefined ，这个过程是自动的，不需要手动调用原型，简化了语法：

```
const obj = { a: 1 };

// 可以在原型上添加自定义的属性、方法
obj.__proto__.b = 2;

// 1 2 2 ，不用手动找原型，JS 自己就会在原型链上找
console.log(obj.a, obj.b, obj.__proto__.b);

// undefined ，因为 Object.prototype 中都没有属性 c
console.log(obj.c);
```

如果不适用 \_\_proto\_\_ 和 prototype ，那么只能用特殊方法才能获取原型上的属性和方法：

```
const obj = { a: 1, [Symbol("b")]: 2 };

obj.__proto__.c = 3;
obj.__proto__[Symbol("d")] = 4;

// 无法看到 c ，d ，有些也看不到 Symbol
console.log(obj);
console.log(Object.keys(obj));
console.log(Object.getOwnPropertyNames(obj));
console.log(Reflect.ownKeys(obj), "\n");

// ["a", "c"] ，for...in 可以获取 c ，d ，但 Symbol 不行
let keys = [];
for (const key in obj) keys.push(key);
console.log(keys, "\n");

// 可以用 Object.getOwnPropertySymbols 获取 Symbol
keys = [
  ...new Set([
    ...keys,
    ...Object.getOwnPropertySymbols(obj),
    ...Object.getOwnPropertySymbols(obj.__proto__),
  ]),
];
console.log(keys);
```

### 2.2 this

函数中的 this 只有在调用时，才确定 this 的指向。

（1） this 的 4 种绑定规则

优先级：new \> 显示 \> 隐式 \> 默认 。

默认绑定规则：

- 全局作用域中，浏览器 this 指向 window ，node 的 this 指向 \{\}
  
  ```
  // 浏览器中 window window
  // node 中 {} 全局对象
  console.log(this, globalThis);
  ```

- 函数不通过对象直接调用，而是哦独立调用，浏览器中只想 window ，node 中只想 node 全局对象，这个 node 全局对象可以用 globalThis 获取：
  
  ```
  function func1() {
    console.log(this);
  }
  func1();
  
  (function func2() {
    console.log(this);
  })();
  
  function func3() {
    return function () {
      console.log(this);
    };
  }
  func3()();
  
  function func4(fn) {
    fn();
  }
  func4(function () {
    console.log(this);
  });
  
  const obj = {
    func5() {
      return function () {
        console.log(this);
      };
    },
  };
  obj.func5()();
  ```
  
  在严格模式下，这种情况会指向 undefined ，但是不影响全局作用域的 this 和 globalThis ，webpack 、vite 默认都是严格模式：
  
  ```
  "use strict";
  
  console.log(this);
  console.log(globalThis);
  
  function func() {
    console.log(this);
  }
  func();
  ```

隐式绑定规则：

- 对象调用，就指向这个对象：
  
  ```
  const obj = {
    a: 1,
    func() {
      console.log(this);
    },
  };
  
  // obj
  obj.func();
  ```

- 隐式丢失，结果和函数独立调用一样；
  
  ```
  const obj = {
    a: 1,
    func() {
      console.log(this);
    },
  };
  
  // window 或 node 全局对象，严格模式下是 undefined
  const fn = obj.func;
  fn();
  ```

显示绑定规则：

* 函数调用本质上是调用了函数的 call ：
  
  ```
  function func(a, b) {
    console.log(this);
  }
  
  // 等价
  func(1, 2);
  func.call(globalThis, 1, 2);
  ```

* call ，apply ，bind 显示修改 this ，三者等价；
  
  ```
  function func(a, b) {
    console.log(this);
  }
  
  const obj = { a: 1 };
  
  func.call(obj, 1, 2);
  func.apply(obj, [1, 2]);
  func.bind(obj, 1, 2)();
  ```

new 绑定：

* this 指向实例对象：
  
  ```
  function Person() {
    console.log(this);
  
    this.a = 1;
    this.getThis = function () {
      console.log(this);
    };
  }
  
  const obj1 = new Person();
  obj1.getThis();
  ```

* 构造函数默认 return this ，使得接收的变量获得实例对象，若修改了 return ，则会得到 retuirn 的对象，不推荐这么做：
  
  ```
  function Person() {
    console.log(this);
  
    this.a = 1;
    this.getThis = function () {
      console.log(this);
    };
  
    return { b: 2 };
  }
  
  const obj1 = new Person();
  
  // { b: 2 }
  console.log(obj1);
  ```

特殊情况：

* 箭头函数没有这 4 种规则，用自己的规则就行，由于 window 在 node 中有 \{\} 和 node 全局对象两种情况，所以需要看箭头函数最近的作用域是否是全局作用域：
  
  ```
  const obj1 = {
    func1: () => {
      console.log(this);
    },
  
    func2: function () {
      return () => console.log(this);
    },
  
    func3: () => {
      return () => console.log(this);
    },
  };
  
  const obj2 = { b: 2 };
  
  // 指向 window 或 {} ，隐式、显示、默认规则都无效，且这些箭头函数都属于 obj1 ，而 obj1 在全局作用域
  obj1.func1();
  obj1.func1.call(obj2);
  obj1.func3()();
  console.log("\n");
  
  // window 或全局对象
  obj1.func2()();
  obj1.func2().call(obj2);
  console.log("\n");
  
  // obj2 ，因为箭头函数最近的作用域已经变成了 obj2
  obj1.func2.call(obj2)();
  ```

* API 的回调函数的 this 由内部实现决定，如 Vue 的一般都指向 Vue 实例。但如果回调函数是箭头函数，则不管内部如何实现，this 都只看调用 API 的作用域：
  
  ```
  function api(fn) {
    const obj = { a: 1 };
    fn.call(obj);
  }
  
  // obj
  api(function () {
    console.log(this);
  });
  
  // window 或 {} ，因为 api 在全局作用域调用
  api(() => {
    console.log(this);
  });
  ```

（2）实例

```
// node 环境
this.name = 3;
globalThis.name = 3;

// 浏览器环境
// const name = 3;

const obj1 = {
  name: "1",

  fn1() {
    console.log(this?.name);
  },

  fn2: () => console.log(this?.name),

  fn3() {
    return function () {
      console.log(this?.name);
    };
  },

  fn4() {
    return () => console.log(this?.name);
  },
};

const obj2 = {
  name: "2",
};

// 1 2 3 3
obj1.fn1();
obj1.fn1.call(obj2);
obj1.fn2();
obj1.fn2.call(obj2);
console.log("\n");

// 3 2 3
obj1.fn3()();
obj1.fn3().call(obj2);
obj1.fn3.call(obj2)();
console.log("\n");

// 1 1 2
obj1.fn4()();
obj1.fn4().call(obj2);
obj1.fn4.call(obj2)();
```

### 2.3 深拷贝

引用数据类型，引用（地址）存储在栈内存，用变量接收；属性等存储在堆内存。

浅拷贝只拷贝地址，修改拷贝对象的属性，原始对象也会修改，因为是同一个堆内存空间；而深拷贝则是拷贝全部元素，存放在新开票的堆内存中。

```
const obj1 = { a: 1 };

// 浅拷贝
const obj2 = obj1;

obj2.a = 2;

// 2 2
console.log(obj1.a, obj2.a);
```

深拷贝：

```
// 缺点是 JSON API 自己的限制，优先数据类型无法拷贝
const func1 = (obj) => JSON.parse(JSON.stringify(obj));

// 缺点是只能深拷贝一层
const func2 = (obj) => ({ ...obj });

/**自己实现
 * NaN，Function，基本数据类型不需要深拷贝，直接返回，Symbol 除外
 * 支持循环引用的深拷贝
 * 支持 Symbol ，Date ，RegExp 的深拷贝
 * 支持对象、数组、Set、WeakSet、Map、WeakMap 的深拷贝
 * 原型上的自定义属性，需要 for in 遍历、方法，比较少用，这里就不实现拷贝了
 */
function deepCopy(source, hash = new WeakMap()) {
  // 不需要递归深拷贝的类型
  const nonRecursionTypes = [
    "[object Symbol]",
    "[object Date]",
    "[object RegExp]",
  ];

  // 需要递归深拷贝的类型
  const recursionTypes = [
    "[object Object]",
    "[object Array]",
    "[object Set]",
    "[object Map]",
    "[object WeakSet]",
    "[object WeakMap]",
  ];

  const type = Object.prototype.toString.call(source);

  // 1.如果是NaN，函数或基本数据类型（Number,String,Boolean,null,undefined,BigInt），直接返回
  if (!recursionTypes.includes(type) && !nonRecursionTypes.includes(type))
    return source;

  // 2.如果是Symbol，Date或RegExp，简单深拷贝后返回
  if (nonRecursionTypes.includes(type))
    return type === "[object Symbol]"
      ? Symbol(source.description)
      : type === "[object Date]"
      ? new Date(source)
      : new RegExp(source);

  // 3.如果是循环引用，直接return
  if (hash.has(source)) return hash.get(source);
  hash.set(source, source);

  // 4.若果是需要递归深拷贝的类型
  let res = null;
  switch (type) {
    case "[object Array]":
    case "[object Object]":
      res = Array.isArray(source) ? [] : {};
      //之所以不直接用for遍历source是因为这样遍历不出键位Symbol的属性，ownKeys才行
      Reflect.ownKeys(source).forEach((i) => {
        if (i !== "length" || type === "[object Object]") {
          res[i] = deepCopy(source[i], hash);
        }
      });
      break;
    case "[object Set]":
    case "[object WeakSet]":
      res = new Set();
      for (let i of source) res.add(deepCopy(i, hash));
      break;
    case "[object Map]":
    case "[object WeakMap]":
      res = new Map();
      for (let [k, v] of source) res.set(k, deepCopy(v, hash));
      break;
    default:
      break;
  }

  return res;
}

// 测试代码
const obj = {
  num: 123,
  bigint: 123456789123456789n,
  nan: NaN,
  und: undefined,
  arr: [1, 2],
  obj: { a: 1, b: 2 },
  func: () => 123,
  null: null,
  [Symbol("111")]: 111,
  set: new Set([5, 6]),
  map: new Map([["key", "value"]]),
  sym: Symbol("sym"),
  date: new Date(),
  reg: new RegExp(),
};

// 测试循环引用
const objTest = {
  obj,
};

obj.myself = obj;
obj.objTest = objTest;
obj.arr.push(obj.arr);
obj.set.add(obj.set);
obj.map.set("m", obj.map);

// 输出
console.log(obj);
console.log(deepCopy(obj));
```

深拷贝也有第三方 API 可以直接使用。

### 2.4 异常处理

当代码出错时，会报错并终止运行，可以使用异常处理使报错后不终止运行：

```
try {
  console.log(a);
} catch (err) {
  console.log("a is not define");
}
```

throw 抛出异常，在一些业务中，可能需要手动抛出异常，在处理具有大量代码的项目bug 时，是很难根据报错来找到 bug 的，可以利用抛出异常来方便检查是哪里出了问题 

throw 一般与 try，catch 配合使用：

```
const a = 10;

try {
  if (a <= 10) throw new Error("a 必须 > 10");
} catch (err) {
  console.log(err);
}
```

### 2.5 数据响应式

当修改数据时，需要同时修改 DOM ，才能数据同步。

但是当数据太多时，每次修改都要重新操作一下 DOM ，十分麻烦，且如果这个数据用在页面的很多处，就很容易出错。

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style></style>
  </head>
  <body>
    <div id="#app">
      <div>
        <span id="num1"></span>
        <button id="btn1">+</button>
      </div>

      <div>
        <span id="num2"></span>
        <button id="btn2">+</button>
      </div>
    </div>
  </body>
  <script>
    const data = {
      num1: 10,
      num2: 20,
    };

    const num1 = document.querySelector("#num1");
    const num2 = document.querySelector("#num2");
    const btn1 = document.querySelector("#btn1");
    const btn2 = document.querySelector("#btn2");

    const rendNum1 = () => (num1.innerText = data.num1);
    const rendNum2 = () => (num2.innerText = data.num2);

    btn1.addEventListener("click", () => {
      ++data.num1;
      rendNum1();
    });

    btn2.addEventListener("click", () => {
      ++data.num2;
      rendNum2();
    });

    const init = () => {
      rendNum1();
      rendNum2();
    };
    init();
  </script>
</html>
```

啊而数据响应式可以简化代码，也不容易出错，可以使用 Object\.defineProperty 实现：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style></style>
  </head>
  <body>
    <div id="#app">
      <div>
        <span id="num1"></span>
        <button id="btn1">+</button>
      </div>

      <div>
        <span id="num2"></span>
        <button id="btn2">+</button>
      </div>
    </div>
  </body>
  <script>
    class Euv {
      data = null;
      __func = null;
      funcs = {};

      constructor(config) {
        if (!config?.data) return this;
        this.data = config.data;

        const keys = Object.keys(this.data);

        for (const key of keys) {
          let value = this.data[key];
          this.funcs[key] = new Set();

          Object.defineProperty(this.data, key, {
            get: () => {
              // 依赖收集，收集用到该数据的函数
              if (this.__func) this.funcs[key].add(this.__func);
              return value;
            },
            set: (newValue) => {
              value = newValue;
              // 派发更新，通知所有用到该数据的函数，更新页面
              for (const fn of this.funcs[key]) fn();
            },
          });
        }
      }
    }

    const euv = new Euv({
      data: {
        num1: 10,
        num2: 20,
      },
    });

    const num1 = document.querySelector("#num1");
    const num2 = document.querySelector("#num2");
    const btn1 = document.querySelector("#btn1");
    const btn2 = document.querySelector("#btn2");

    const rendNum1 = () => (num1.innerText = euv.data.num1);
    const rendNum2 = () => (num2.innerText = euv.data.num2);
    const autoRun = (fn) => {
      // 让依赖收集知道是哪个函数在使用数据
      euv.__func = fn;
      fn();
      euv.__func = null;
    };

    btn1.addEventListener("click", () => ++euv.data.num1);
    btn2.addEventListener("click", () => ++euv.data.num2);

    const init = () => {
      autoRun(rendNum1);
      autoRun(rendNum2);
    };
    init();
  </script>
</html>
```

这只是简单实现，Vue、React 实现更复杂，有了数据响应式，就可以只关注数据，用数据驱动视图，这也是前端框架的思想。

# 七、JS编码技巧

（1）数组、对象判空

不能用arr == [] 和 obj == {} 判断，因为这是比较两个数组/对象的地址。

```
//数组判空
arr.length == 0
JSON.stringify(arr) == '[]'

//对象判空
Object.keys(obj).length == 0
Object.getOwnPropertyName(obj).length == 0
JSON.stringify(obj) == '{}' 
```

JSON.stringify()要慎用，它有自身的限制，如undefiend和函数会被忽略，详见ajax笔记

也可以自定义一个判空函数：

```
//可判断数组、对象是否非空
function isEmpty(data){
  let isEmpty = true;
  // 没有/有进入循环，说明空/非空
  for(let i in data){
    isEmpty = false;
    break;  
  }
  return isEmpty
}
```

（2）判断对象中是否有某属性

```
let obj = {
  a: undefined
};
obj.__proto__.aaa = 123;

//方法一，直接调用看是否是undefined，缺点是无法判断值本身就是undefined的属性
//undefined，但不是a不存在，而是a的值本身就是undefined
console.log(obj['a'],obj.a);
//undefined，b不存在
console.log(obj['b'],obj.b);
//可以检查原型上的属性
console.log(obj.aaa);

//方式二,即可以判断原型上的属性，也可以判断undefined的属性
console.log('a' in obj);   //true
console.log('b' in obj);   //false
console.log('aaa' in obj); //true

//方式三，可以判断undefined的属性，但是无法检查原型上的属性
console.log(obj.hasOwnProperty('a'));   //true
console.log(obj.hasOwnProperty('b'));   //false
console.log(obj.hasOwnProperty('aaa')); //false

//ES13新增Object.hasOwn()，简化了hasOwnProperty
```

（3）条件分支优化

多个 || 条件，可以简化为：

```
if(a == 'asdf' || a == 'qwer' || a == 'zxcv'){}
//简化
if(['asdf','qwer','zxcv'].includes(a)){}
```

简单的if...else...可简化为三元运算符：

```
let res = '';
if(a > 100){
  res = '>100'
}
else {
  res = '<100'
}
//简化
res = a > 100 ? '>100' : '<100';
```

空值/布尔值检查优化

```
let res = '';
if(!a){
  res = a;
}
//简化，类似的运算符还有 || && ?. ??= &&= ||=
res = a ?? '';
```

（4）变量相关

声明简化

```
let a;
let b;
//简化
let a, b;
```

赋值简化

```
let a,b,c;
a = 1;
b = 2;
c = 3;
//简化
let [a,b,c] = [1,2,3];
```

运算赋值简化：

```
let a = 1;
a = a + 1;
//简化，类似的还有++ -- -= *= /= %= ^=
a += 1;
```

（4）函数

在函数内有多层条件嵌套时，可以简化，增加可读性：

```
//简化前
function func(a, b){
  if(a < 0){
    if(b < 0)[
      return true;
    ]  
  }
}

//简化后
function func(){
  if(a < 0)  return;
  if(b < 0)  return;
  return true;
}
```
