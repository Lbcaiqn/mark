# 一、基本

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

注释方法与c一样，每个语句也是以分号结尾，虽然不加分号也不会报错，但是最好加上。

谷歌浏览器控制台输出bug；
输出较为复杂的数据时，会先展示 [...]  当点击后才会显示完整数据，这时候就会有个bug：

```
ler aaa = [{
  value: 123
]]
console.log(aaa)
aaa[0].value = 456
```

正常来说，输出在修改之前，应该输出123，可是却输出456
这是因为浏览器的bug，若点开三角的时候数据已经改了，name浏览器会展示最新的数据

以下例子就能证明，若在3秒内点开三角，就展示123，若3秒后数据修改了再点开三角，就展示456

```
ler aaa = [{
  value: 123
]]
console.log(aaa)
setTimeout(() => aaa[0].value = 456, 3000)
```

这只是展示的bug，并不是代码逻辑的bug，代码里该输出什么还是输出什么，只是在调试代码的时候要特别注意。

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

4. var重复声明不会报错，重复声明的变量采用最后声明的那个
   
   ```
   var a = 5;
   var a = 555;
   console.log(a); //555
   ```

5. 命名：还可以用$命名，变量属性，函数方法小驼峰，对象，构造函数大驼峰，其他与c一样

### 2.2 数据类型

7种基本数据类型：Number，Stirng，Boolean，null，undefined，Symbole（ES6），BIGInt（ES11）

1种引用数据类型：Object（数组、函数、Set、Date等都是Object）

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

### 2.2.1 简单数据类型（值类型/基本类型）：

（1）Number：

包括整型，浮点型，0八进制，0x十六进制，

Number.MAX_VALUE最大值，Number.MIN_VALUE最小值，最大值*2 无穷大infinity，-最大值*2 无小-infinity，NaN非数字 isNaN(变量或值) true为非数字。
数值字面量/数值变量.toFixed(n) 保留n位小数

0.1+0.2为什么不等于0.3

原因：

js的浮点数有精度，0.1和0.2在内存中存的并不是0.1和0.2，可能是0.10000001 0.2000001所以相加就不等于0.3

如何判断相等：
0.1+0.2和0.3相减，得到的结果的绝对值若小于一个很小的树，那就相等。

```
var res = Math.abs((0.1 + 0.2 - 0.3) > 0.00000000000000000001) ? true : false;
console.log(res);  //true
```

（2）String

str.length返回长度（不包括\0）

加法表达式一旦有字符串结果都是字符串拼接（包括’’）

访问某个字符：

```
var str = 'abc';
console.log(str.charAt(0));    //a
console.log(str,charCodeAt(0)) //97，返回下标0字符的ASCI码
onsole.log(str[0));  //a

//chatAt()和下标访问效果一样，只是charAt是更早的特性，兼容性好一些
```

转义符与c一样，

（3）Boolean

可参与加法，分别代表1和0，字符串相加当成’true’ ’false’

（4）undefined

与数字计算结果为NaN，与字符串相加，当成’undefind’

当变量未赋值，形参未给实参，调用对象不存在的属性，函数没有返回值都是undefined

（5）null

可参与运算，当成0，字符串相加当成’null’（被null赋值的变量返回是object，可作为空对象，是历史遗留问题）

原型的终点，不存在的DOM都是null

undefined与null区别：

* undefined不是关键字，null是关键字

* urndefined代表未定义，没有赋值，连null都没有；而null代表空值或空引用

* null转为number是0；undefined转为number是NaN

* typoof判断null是Object，undefined是undefined

### 2.2.2 复杂数据类型（引用类型）

（1）数组

```
var arr1 = [];
var arr2 = new Array();
arr.length  //返回数组元素个数 arrname.length = n 数组大小改为n，常用扩容
```

注意点：

* 数组可以存放不同的数据类型

* 数组没有限制长度，且js的数组可以给超出长度的位置赋值，数组会自动扩容，中间的元素为undfined
  
  ```
  var arr = [1]
  arr[3] = 3
  // [1,undefined,3]
  ```

* 数组变量存放在占内存中，本身存储的是整个数组在堆内存中的地址，所以哦直接给数组名赋值会丢失整个数组的数据，数组作为形参也能修改数组本身。

（2）对象

键的引号可以省略，但是若键比较复杂时就不能生路（如'a.b' ）

```
var obj = {
  'name': 'lgx',
  sex: 'man',
}
var obj = new Object()
```

（3）其他引用类型

函数也是引用类型。

此外，Date，Set等等new出来的是一个对象，也是引用类型。

（4）循环引用

引用类型的某个成员是自己，或某个成员的成员里面是自己，就会形成循环引用，以对象为例：

```
//情况一，obj1->obj1......
let obj1 = {a: 1};
obj1.myself = obj1;

//情况二，obj2->obj3->obj2......
let obj2 = {a: 1};
let obj3 = {yourself: obj2};
obj2.obj3 = obj3;
xun
```

目前数组/对象等得到循环引用没有发现有什么用，在深拷贝和HSON序列化还会带来问题。

而函数的循环引用的应用就是递归。

### 2.3 类型转换

1. 转成String
   
   xxx + ’’（隐式转换） xxx.toString()  String(xxx)（两个强制转换）

2. 转成Number
   
   parseInt(str)  parseFloat(str)
   Number(str)（string转数值，强制转换） 
   
   str - 0 str * 1 str / 1（隐式转换）

3. 转成Boolean
   
   Boolean(xxx) 空的否定的值如0 ‘’ NaN null undefind转换成false，其余true

### 2.4 运算符

（1）浮点数由于有精度，所以比较浮点数时需要处理
（2）短路运算（逻辑中断）：当逻辑运算符两边其中一个不是布尔而是算数表达式或值时的情况，根据左的真假返回相应的值（若左非布尔，则会隐转成布尔）

1. 逻辑与短路运算：左真用右，左假用左（中断右）

2. 逻辑或短路运算：左真用左（中断右），左假用右

（3）== 和 ===

1. == != 先转换成相同类型再比较

2. !== 先判断类型是否一致，不一致直接true，再比较

（4）in运算符

判断数组/对象是否存在某个key

```
let arr = [5,undefined,7];
let obj = {a: 1};

console.log(0 in arr); //true
console.log(1 in arr); //true
console.log(2 in arr); //true
console.log(3 in arr); //false

console.log('a' in obj); //true
console.log('b' in obj); //false
```

（5）其他

判断数据类型的运算符在下面介绍。

其他的就和c一样了。

### 2.5 检测数据类型

共有四种方法：

（1）typeof运算符

```
console.log(typeof 123);  //'number'
```

typeof的结果为一个字符串，它只能判断出number，string，boolean，undefined，object，function。其他的如Array，null，symbol，Set，Map等一律判断为object。NaN判断为number。

（2）instanceof运算符

```
console.log({a: 123} instanceof Object); //true
```

instanceof的结果为一个布尔值，判断是基于xxx是否为yyy的实例，如Array，Function，Symbol，Set，Map等都是Object的实例，所以返回true，以此类推。

（3）Object.prototype.toString()

```
console.log(Object.prototype.toString.call(123)); //'[object Number]'
```

最实用，可以判断出所有数据类型，返回一个字符串，形式为'[object xxx]'。

使用时需要注意，由于它是Object原型上的方法，this默认为Object，所以需要call修改this为对应的变量。

虽然它是Object原型的方法，而数组等有这个方法，但是数组等会重写这个方法使得不是检测类型的功能了，所以只能Object调用。

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

### 5.3 ES5对象继承

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

### 5.4 Object

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

文本：

```
e.innerText  //写：覆盖所有文本      读：去除所有空格和换行，读取文本
e.innerHTML  //写：覆盖所有文本和标签 读：保留空格和换行，读取文本和标签
```

原生属性：

只能读写原生属性

```
//普通属性
e.属性

//表单属性
e.value   //表单内容
e.disable //true为不能输入/选中
e.type    //表单类型
```

自定义属性：

直接在标签中写属性，就是自定义属性，H5的自定义属性命名规范；data-xxx data-xxx-xxx，如：

```
<div data-xxx="123"></div>
```

```
e.getAttribute(‘属性’ )      //可获得内置/自定义属性的值
e.setAttribute(‘属性’,’值’ ) //可修改内置/自定义属性的值
e.removeAttribute(‘属性’ )  //删除自定义属性

//H5新增获得自定义属性得到api：(省略data-，xxx-xxx变成xxxXxx)
e.dataset.xxx 
e.data.xxxXxx
e.dataset[‘xxx’] 
e.dataset[‘xxxXxx’]
```

样式：

```
e.style.样式属性  //（小驼峰） 行内样式
e.className     //修改类名，会覆盖原有，多个类名空格隔开
```

## 3 节点操作

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

可以通过元素对象直接在代码触发事件：

```
var box = document.querySelector('#box');
box.onclick = function(){
  console.log(123);
};
box.click();
```

### 4.3 事件类型：

只列举常见的事件。

（1）鼠标事件

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

（2）键盘事件

| keydown  | 按键按下，按键按着不放就一直触发，可识别所有键  |
| -------- | ------------------------ |
| keypress | 按键按下，按键按着不放就一直触发，不能识别功能键 |
| keyup    | 按键弹起                     |

注意事项：

* 三个键盘事件不管代码顺序，执行顺序都是down-press-up

* event.keyCode 可获得按键码，up，down不区分大小写，press区分。通过event.keyCode 可实现对特定键的监听

（3）表单事件

input事件：

| focus | 获得焦点 |
| ----- | ---- |
| blur  | 失去焦点 |

form事件：

| submit | 提交  |
| ------ | --- |
| reset  | 重置  |

通用（部分表单不能用）：

| input   | 值变化时触发，在修改完并失去焦点后才触发 |
| ------- | -------------------- |
| change  | 值变化时触发，修改的时候实时触发     |
| invalid | 非法输入时触发，可自定义非法输出信息   |

（4）其他事件

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

（4）触屏事件

移动端手指触屏触发

| 事件          | 说明         |
| ----------- | ---------- |
| touchstart  | 手指触屏       |
| touchmove   | 手指移动       |
| touchend    | 手指弹起       |
| touchcancel | 触屏事件被取消时触发 |

### 4.4 事件对象

事件函数给个形参event，事件函数内 console.log(event) 可以看到，事件对象保存了事件类型，事件源等信息，如event.type 是事件类型。只有事件触发事件时，事件对象才会创建。

是件函数里面的this指向真正触发该事件的元素，未使用时事件委派时this就是绑定事件的那个元素，event是它的事件对象。若使用了事件委派（ul里有若干li，给ul注册事件，li触发了事件），则this是实际触发事件的那个li，event.target是哪个li，event是ul。

事件对象包含的常用属性方法：

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

### 4.5 事件流

即事件的传播过程：

* 捕获阶段：触发事件后，从document-html-body-…，一旦有有定义该事件的事件函数就会执行。

* 冒泡阶段：从…-body-html-document传播，一旦有定义该事件的时间函数就会执行
  Js只能选择捕获/冒泡其中一个观察效果。

指定捕获还是冒泡：

* onclick,attachEvent只能观察冒泡

* addEventListener(‘click’,function(){},true) 第三个参数为true/false，为捕获/冒泡，参数补给则默认false。一般都使用冒泡。

事件冒泡：

* 当子触发事件后，它的祖先只要有该事件类型的事件函数，都会执行。

* 阻止冒泡：子到祖先的所有该事件事件函数中，event.stopPropagation()  有兼容性问题
  无兼容性问题：event.cancelBubble 

事件委托（事件代理/事件委派）：

* 事件冒泡的应用，原理是只给父元素注册事件，子元素都不注册，当子元素触发事件后，通过事件冒泡执行父元素的事件函数，这样就能将n个事件监听变为一个事件监听，提升性能

* 通过e.target获取触发事件的子元素

* 事件委派中，可以给子元素增加自定义属性，通过自定义属性区分每个子元素

## 5 offset，client，scroll

首先需要了解几个概念：

* 内容宽度：width

* 可是区域宽度：width+padding*2

* 盒子宽度：width+padding*2+border*2

（1）offset

获取元素距父元素的偏移和该元素盒子宽高（不带单位的number）

要求：父元素必须有定位（没有定位则以body为父），若没有父元素，则父是body（不用定位）

| API            | 说明                                                         |
| -------------- | ---------------------------------------------------------- |
| e.offsetTop    | 元素e的左边缘距带定位的父元素顶部的偏移，包含外边距，注意没有offsetBottom                |
| e.offsetLeft   | 元素e的上边缘距带定位的父元素左边的偏移，包含外边距，注意没有offsetRight                 |
| e.offsetWidth  | 获取元素e的宽（包含widtj，内边距和边框，不包含外边距），与处于什么盒子模型无关                 |
| e.offsetHeight | 获取元素e的高（包含height，内边距和边框，不包含外边距），与处于什么盒子模型无关                |
| e.offsetParent | 获取父元素，若父元素没有定位或没有父元素，返回body；与e.parentNode区别是parentNode不用定位 |

offsetTop，ioffsetLeft中的带定位的父元素解释：

* 若父元素没有设置任何定位，而是默认的话，则继续往祖先找，直到找到有定位的父元素或window为止。

e.offset与e.style.xxx的区别：

* e.style.xxx只能获取行内样式，e.offset可获取任意的样式

* e.style.xxx读写有单位的字符串，e.offest返回不带单位的数值

* e.style的宽高只有width/height，不包含内外边距和边框

* e.style.xxx可读写，但是e.style.top/width等是只写，读的话是空；e.offset是只读

（2）client

获取元素的边框和可视区域宽高（不带单位的number）

| API          | 说明                                    |
| ------------ | ------------------------------------- |
| clientTop    | 上边框大小，注意没有clientBottom                |
| clientLeft   | 左边框大小，注意没有clientRight                 |
| clientWith   | 宽度，包含width和内边距，不包含边框和外边距，与处于什么盒子模型无关  |
| clientHeight | 高度，包含height和内边距，不包含边框和外边距，与处于什么盒子模型无关 |

（3）scroll

获取滚动后被卷去的那部分大小，获取把滚动超出部分宽高计算在内client宽高，都是不带单位得到number

| API            | 说明                               |
| -------------- | -------------------------------- |
| e.scrollTop    | 返回滚动后被卷去的那部分top，即滚动距离            |
| e.scrollLeft   | 返回滚动后被卷去的那部分left，即滚动距离           |
| e.scrollWidth  | clientWidth的基础上，加上盒子内的内容超出部分的大小  |
| e.scrollHeight | clientHeight的基础上，加上盒子内的内容超出部分的大小 |

| API             | 说明          |
| --------------- | ----------- |
| window.scroillX | 浏览器水平滚动过的距离 |
| window.scrollY  | 浏览器垂直滚动过的距离 |

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

# 四、BOM

BOM：浏览器对象模型
Window是浏览器的根对象，包括：document，navigator，location，history，screen，所以BOM包含DOM，window.document…的window.可省略
window是全局对象，多以全局变量和 全局函数都会鞭策window的属性/方法
同样，调用全局变量/全局函数，window.可省略
alert()也是window的方法

## 1 BOM事件：

（1）页面事件：

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

窗口事件：

| onscroll | 滚动             |
| -------- | -------------- |
| onresize | 浏览器窗口大小发生变化时触发 |

```

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

# 五、ES6-ES13

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

### 1.5 Symbol

ES6新的基本数据类型，具有以下特性：

* 值唯一，可用来解决命名冲突问题

* 无法运算与比较大小，只能用== != === !==比较

* Symobole可以转为字符串，可转为布尔值且值为true

* 对象中用Symbol定义的属性不能遍历出来，但可用Reflect.ownKeys遍历出来

```
//声明，注意symbol的值是不可见的
let s0=Symbol()
//里面的字符串并不是值，只是做一个说明，相当于注释，字符层相同的symbpl值也是不一样的
let s1=Symbol('abc')
//函数对象创建
let s2=Symbol.for() //这样创建的两个symbol值一样，但与空字符串''创建的值不一样'
let s3=Symbol.for('123') //这样创建，字符串相同，值就相同

//应用：给对象添加独一无二的属性和方法
let obj={
  run:Symbol(),     //第一种
  [Symbol('sleep')]:function(){}  //第二种
}
obj.run=function(){}   s//与对象内的run是不同的
```

Symbol有内置属性，作用是作为对象的属性，如Symbol.hasInstance，作为对象的属性 [Symbol.hasInstance] : …

Symbol作为Map的键时可以直接遍历出来。

Symbol作为对象属性的键时，需要特定的方式才能看到这个属性

```
let obj = {
  [Symbol('123')]: '123',
  a: 'a'
}

//以下四种方式都无法看到Symbol定义的属性
for (let i in obj) console.log(i)
console.log(Object.keys(obj))
console.log(Object.getOwnPropertyNames(obj))
console.log(JSON.stringify(obj))

//以下一种方式只能看到Symbol定义的属性
console.log(Object.getOwnPropertySymbols(obj))

//以下两种方式可以看到所有属性
console.log(obj)
console.log(Reflect.ownKeys(obj))
```

### 1.7 新运算符

扩展运算符...

将数组转化成逗号分隔的列表
具备iterator接口的数据类型才可使用

```
const arr=[‘a’,’b’,’c’]

//传入了’a’,’b’,’c’三个字符串作为实参
fun(...arr)

//arr_arr为[‘a’,’b’,’c’,‘a’,’b’,’c’]
let arr_arr=[...arr, ...arr]

//数组深拷贝
let arr_copy=[...arr]

//将伪数组（如querySelectAll得到的）转化为真正的数组
let arr_new = [...伪数组]

//使用第三方库的函数时，若不知道里面的回调函数有几个形参，可以这样查看有什么参数
xxx((...aaa) => {
  console.log(aaa)
})
```

### 1.8 迭代器和for of

for...of..

for of与for in的区别就在于for of的i。遍历出来的是value

对象不能用for of

```
for(let i of xxx){
  console.log('value',i)
}
```

迭代器：
ES6提供了iterator接口，为不同的数据结构提供统一的访问机制。一种数据结构只要部署了interator接口，就能通过 for of 遍历
一般iterator接口是各数据结构的原型对象中的一个方法：

```
[Symbo.iterator] : function(){}
```

自带iterator接口的数据结构：
Array，String，Arguments，Set，Map，NodeList，typedArray（没有Object），其中Set，Map无法用for in循环，对象无法用for of循环

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
let arr = [1,2]
let arrite = arr[Symbol.iterator]()
console.log(arrite.next()) //第一个成员
console.log(arrite.next()) //第二个成员
...
```

自定义遍历数据：
需求：有一个对象o，需求是使用for of遍历o里面的arr的每一个值
虽然可以直接 for( I of o.arr ) 或其它方法进行遍历，但不符合面向对象的思想，此时要给o部署iterator接口

此外，也可以根据其他的需求来进行自定义

```
const o = {
  name:'lgx',
  arr:[1,2,3],
  [Symbol.iterator](){
    let i=0 //索引
    let _this=this //_this指向o
    return {
      //return这个对象的里面的this指向return的这个对象，所以才需要_this，或用箭头函数
      next(){
        if(i < _this.arr.length)  return {value:_this.arr[i++],done:false}
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
  
  注意：
  
  以下是错的，本意是想要return一个对象且省略函数体，但是由于包裹对象的也是大括号
  
  ```
  let func = () => {a:1, b:2}
  ```
  
  所以实际上解析成下面这样，就语法错误了
  
  ```
  let func = () => {
    a:1, b:2
  }
  ```

* 箭头函数没有arguments，可以用...args代替

* 没有原型

* 只能定义匿名函数，不能定义具名函数

* 不能作为构造函数不能new，因为箭头函数本身没有this

* 箭头函数的this由上下文决定，一旦确定就无法改变
  
  * 箭头函数的this是静态的，指向声明此箭头函数的那个对象的作用域，如对象o中声明了一个箭头函数f，则f的this指向o的作用域window
    
    * this指向无法修改
    
    * 一般代码中的this是指向window的
      但是箭头函数中的this指向最近的上一级，若在类obj中的箭头函数中，指向obj，若在普通函数中的箭头函数中，指向window
      但是若this在箭头函数中的普通函数中，指向window

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

#### 1.9.3 标签模板

函数调用结合模板字符串的一种新的函数调用方式。标签指的就是函数，在函数调用后面的模板字符串会按照规则作为函数的实参。

```
function aaa(str){
  console.log(str);
}
aaa`111`;  //相当于aaa([`111`]);
alert`aaa` //相当于alert([`aaa`]);
```

其他情况

```
function aaa(str,a,b){
  console.log(str,a,b);
}
let a = 'aaa', b = 25; 
aaa`q${a}w${b}e`  //相当于 aaa(['q','w','e'],a,b);
aaa`q${a}w${b}`  //相当于 aaa(['q','w',''],a,b);
aaa`${a}w${b}`  //相当于 aaa(['','w',''],a,b);
aaa`q${a}${b}`  //相当于 aaa(['q','',''],a,b);
aaa`${a}${b}`  //相当于 aaa(['','',''],a,b);
aaa`q${b}w${b}e${b}r`  //相当于 aaa(['q','w','e','r'],b,b,b);
```

### 1.10 生成器

本质是一个函数，但是语法与传统函数完全不同，是es6提供的一个异步解决方案，进行异步编程。解决了回调地狱。
以前的异步解决方案是单纯使用回调函数。

```
//定义：三种都一样
function * xxx(){} 
function* xxx(){} 
function *xxx(){}

//调用：生成器定义后是一个迭代器对象，所以
xxx().next() 
//或：
let x = xxx()
x.next()
```

yield语句 

在生成器函数体中定义，将代码区域上下分割，n条yield语句将代码分割成n+1个代码块，每次调用next()都只执行当前代码块，然后将指针指向下一个代码块。

```
function * xxx(){
  console.log(111)
  yield '分割线1'
  console.log(222)
  yield '分割线21'
  console.log(333)
}

/*注意，这样调用必须将生成器赋值给一个变量，这样x.next()才是在同一个生成器内，而xxx().next()调用的话都是临时变量，都是在不同的生成器中，所以一般生成器最好赋值给一个变量*/
let x = xxx()
console.log(x.next())
console.log(x.next())
console.log(x.next())

//也可使用for of，这样调可不用将生成器赋值给变量
for(i of xxx()) console.log(i)
```

生成器函数参数：

* 生成器可以定义形参

* next()可传实参，生成器用 let x=yield 123 接收，x的值就是实参的值

* 第n次调用的next，则第n-1个yield接收

应用：

回调地狱的代码：

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
```

同样的逻辑用生成器实现，简化代码：

```
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
具有iterator接口，可使用for of（遍历出每个元素） 和扩展运算符

```
//声明
let s0 = new Set();
let s1 = new Set([1,2,3]);

//无法通过索引访问
/*
Set本质是对象，具有属性和方法
s1.size 元素个数
s1.add(元素) 增
s1.delete(元素) 删
s1.has(元素) 查 存在返回true
s1.clear() 清空
*/
```

遍历：

```
let s = new Set([1,2,3,4])

//常规的Object，Reflect的遍历方法都无法遍历，如Object.keys(),Reflect.ownKey()
//for...in...无法遍历
for(let i in s)  console.log(i);

//forEach和for...of...可以正常遍历
s.forEach(i => {
  console.log(i);
})
for(let i of s)  console.log(i);
```

实际应用：

```
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

WeakSet：

与Set的区别就两个：

* 每个成员只能是引用类型
  
  ```
  let ws = new WeakSet([
    [1,2],
    {a: 123},
    new Date(),
    new Set()
  ]);
  
  /*
  ws.add(value)
  ws.delete(value)
  ws.has(value)
  */
  ```

* 每个成员都是弱引用（弱引用的概念见六1.3垃圾回收机制）
  
  ```
  let s = new Set();
  let ws = new WeakSet();
  function test(){
    let o1 = {a: 123};
    let o2 = {a: 456};
    s.add(o1);
    ws.add(o2);
  }
  test();
  
  //Set的成员是强引用，函数调用完成员还保持着对{a:123}的引用
  console.log(s);
  //WeakSet是弱引用，函数调用完成员是否还保持着对{a:456}的引用得看垃圾回收有没有回收到这里
  console.log(ws);
  ```
  
  由于弱引用的不确定性，因此WeakSet的成员是否存在是不确定的，所以没有size属性和clear()，没有size也就无法进行任何形式的迭代遍历。

#### 1.12.2 Map

Map字典，键值对的集合，键是唯一的，若增加了相同的键，会覆盖原有

不像对象的键只能是string，number和Symbol，Map的键和值都可以是任何数据类型，也可以函数，键是Symbol也可以直接遍历出来

有iterator接口，可使用for of（遍历出每个键值对） 和扩展运算符

```
//声明
let m1 = new Map();
let m2 = new Map([['name','lgx'],['age',23]]);

/*Map本质是对象，具有属性和方法
m1.size 键值对个数
m1.set(key,value) 增，不像c++中set相同的键会自动+1，可能有其他map方法
m1.get(key) 返回对应的key
m1.has(key) 是否存在key，返回布尔值
m1.delete(key) 删
m1.clear() 清空
*/
```

遍历：

Map可以直接遍历出键位Symbol的成员

```
let m = new Map([['name','lgx'],['age',23]]);

//常规的Object，Reflect的遍历方法都无法遍历，如Object.keys(),Reflect.ownKey()
//for...in...无法遍历
for(let i in m)  console.log(i);

//forEach可以正常必遍历
m.forEach(i => {
  console.log(i);
})

//for...of...可以正常遍历
//但是得到的i比较特殊，是一个两个元素的数组 [key,value]
for(let i of m)  console.log(i);
//因此可以配合数组的结构赋值，取出key和value
for(let i of m)  console.log(i);
```

实际应用：

```
//统计出现个数
let arr = ['apple','apple','banana'];
let m = new Map();
for(let i of arr){
  if(m.has(i))  m.set(i,m.get(i) + 1);
  else m.set(i,1);
}
console.log(m);
```

WeakMap：

与Map区别就两个：

* 键只能是引用类型，但是值的类型依然可以是全部

* 键是弱引用，参考WeakSet的弱引用，因此也没有size等，也不能遍历。

Vue3的响应式系统部分的源码，采用了WeakMap，是为了使不再使用的资源释放掉，来优化性能。

#### 1.12.3 Class

class里的this永远不会指向window，硬要指向window也会指向undefine

ES6的class功能比较简陋，ES13才比较完善，但大部分浏览器和node也在ES13之前就实现了ES13 class的功能。

下面只展示ES6 class的特性。

类的定义与实例化：

```
//声明，class不会被提升
class c {
  //构造函数定义属性，它在new时调用
  constructor(a){
    this.a=a
    this.b=2
  }
  //定义方法，必须是这种写法，方法内this为实例对象
  func(){};
}
//实例化类
let a=new c(123)
```

类的继承：

```
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
  /*重写
  重写后子类以后调用的就是重写的方法
  重写的方法内是无法用super()调用父类的同名方法的
  若未重写，子类对象调用父类方法实际是自动 super.xxxfa()
  */
  xxxfa(){
    //不重写就自动调用super.xxxfa()  
   //重写的代码
  }
}
//实例化子类,可调用子类和父类中的属性和方法
let chi=new ch(1,2,3)
```

类的存取器：

存取器可以看作是用函数的形式来定义一个存取功能更强的属性。

y偶遇是属性，也会继承给子类。

```
class c {
  //定义了a的存取器，就有了a这个属性，不能另外定义
  get a(){
    return 123 //类实例对象可以直接 obj.a 来调用这个get,获得属性a的值
  }
  set a(newVal){
    //操作 //也是直接 obj.a = 5 会调用set，来修改值
  }
}
let obj = new c();
console.log(obj.a);
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
Object.assign(a,b,......) 合并a，b,....若干个对象/类到a，有重复的key则b的value覆盖a的value，这个函数也会返回结果，常用于配置的合并
Object.setPrototypeOf(a,b)  将b设置为a的原型对象
Object.getPrototypeOf(a)    返回a的原型对象

#### 1.13.3 数组方法的扩展

Array.isArray()

H5新增，专门用于判断是否为数组，结果为一个布尔值，优先级高于instanceof

```
var a = 123;
var arr = [1,2];
console.log(Array.isArray(a));   //false
console.log(Array.isArray(arr)); //true
```

新增数组的高阶函数：

新增了一些处理数组高阶函数，高阶函数指的是可以以用函数作为形参的函数。体现了函数式编程思想。

高阶函数中作为形参的函数都是回调函数，回调函数指的是在函数体内部某个时机会调用传进来的函数。

使用这些函数时要注意：

* 是遍历整个数组还是有结果就中断遍历并返回结果

* 数据有修改的是否改变原数组

* 参数有范围的是左闭右开区间还是左闭右闭区间

* 浅拷贝还是深拷贝

判断数组的元素是否符合某个条件：

都不改变原数组

```
let a = [1,2,3,4];

//遍历整个数组，当所有值都符合条件时，才返回true v值，i索引，arr原数组
let boolean1 = a.every((v,i,arr) => v >= 2);

//遍历整个数组或一部分，当有一个值符合条件时，就中断并返回true v值，i索引，arr原数组
let boolean2 = a.some((v,i,arr) => v >= 2);
```

数据查询：

都不改变原数组

```
let a = [1,2,3,4];

//查找数组中是否存在该值，存在就中断遍历返回true
//查找整个数组
let boolean1 = a.includes(4);
//从索引2开始
let boolean1 = a.includes(4);

/*遍历数组一部分，返回符合条件的值
一旦找到就结束遍历并返回该元素，找不到返回undefine
若结果为基本数据类型，就返回值。
若结果为引用数据类型，就返回地址，也就是浅拷贝
形参v值，i索引，arr原数组
*/
let res1  =a.find((v,i,arr) => v >= 2);
//与find区别在于它返回索引值，找不到返回-1
let index1 = a.findIndex((v,i,arr) => v >= 2);
```

数据过滤、操作、汇总：

都不改变原数组

```
let a = [1,2,3,4];

//遍历整个数组，返回过滤出的符合条件的值组成的数组，不改变原数组
//若没有任何item复合条件，返回[]
let arr1 = a.filter(i => i >= 2);

//遍历整个数组，对每个元素进行某种操作后返回给新数组（不修改原数组）
/*和forEach有点像，它们的区别实；
map返回处理完的新数组，可链式调用；forEach返回undefined
map对item的操作不改变原数组；而forEach会
*/
let arr2  =a.map(i => i + 10086);

/*遍历整个数组，汇总数据
0为pre的初始值，pre为上一次return的值，v为值，
i为索引，arr原数组
*/
//左边开始
let res1 = a.reduce((pre,v,i,arr) => pre + v ,0);
//右边开始
let res2=a.reduceRight((pre,v,i,arr) => pre + v ,0);
```

 数组元素替换，数组深拷贝：

替换会改变原数组

```
let a = [1,2,3,4];

/*替换数组里的元素，会改变原数组
形参：值，开始索引，结束索引。
用值替换掉开始到结束索引(左//闭右开)的值
*/
a.fill(5,0,3);

//深拷贝数组
let aCopy = Array.from(a);
```

链式调用：

```
let res  = arr.filter( n => ... ).map( n => ... ).reduce( ( pre , n ) => ... , 0 );
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
//方式一
export {
 ...
}
//方式二，定义变量/函数/类的最前面加export
export let a = 123;
//方式三，default 只能有一个
export default let b = 456;

//方式四，也可以导出其他模块文件的东西
//导出某文件部分内容
export {xxx} from "...";
//导出某文件全部内容
export * from "...";
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

（1）数组扩展includes()

查找某数组中是否含有某元素，返回布尔值。

以前的indexOf有则返回下标，否则返回-1

```
let arr = ['apple'];
console.log(arr.includes('apple'));  //true
console.log(arr.includes('banana'));  //false
```

（2）新运算符 ，幂运算

```
let a = 2**3;  //8
 a **= 2;      //64
```

## 3 ES8

（1）async和await

新的异步解决方案，以类似同步的方式使用异步
① async

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

② await

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

await失败的另一种写法，虽然比try...catch简洁，但是只能获取Promise的成功失败，获取不到Promise内部代码的错误：

```
const [res, err] = await p(value).then(res => [res, null]).catch(err => [null, err]);
```

try...catch...捕获await失败时，按道理await下面的代码应该是try没问题才执行，但是实际上不是这样的，具体原因不明：

```
async function aaa(a) {
  let p = new Promise((resolve, reject) => {
    if (a) resolve("ok");
    else reject("err");
  });

  let res;
  try {
    res = await p;
  } catch (err) {
    console.log(err);
  }
  console.log("你看catch了还会不会执行");
}

aaa(0);
```

解决方法是把await下面的代码放到try里，但这样就不够直观了。也可以用await获取失败的第二种方法：

```
//方法一
async function aaa(a) {
  let p = new Promise((resolve, reject) => {
    if (a) resolve("ok");
    else reject("err");
  });

  let res;
  try {
    res = await p;
    console.log("你看catch了还会不会执行");
  } catch (err) {
    console.log(err);
  }
}
aaa(0);

//方法二
async function aaa(a) {
  let p = new Promise((resolve, reject) => {
    if (a) resolve("ok");
    else reject("err");
  });

  let [res, err] = await p.then((res) => [res, null]).catch((err) => [null, err]);
  if (res) console.log("ok");
  else console.log("err");
}
aaa(0);

//方法三，也可以在方法一判断res，但是这样还不如方法二呢
```



如果await得到的数据有子项，需要注意：

```
//方式一，可以但不优雅
let xxx = await p
let res = xxx.data

//错误写法
//let xxx = await p.data

//方式二
let data = (await p).data

//方式三
let {data} = await p
```

（2）字符串方法的扩展

padStart()和padEnd()，在字符串首尾进行填充。

都不改变原字符串。

第一个参数为最终字符串的长度

第二个参数为填充字符串，若循环填充直到充满第一个参数指定的长度，若为空，则天空空格，

```
let str = 'b';
let s1 = str.padStart(2,'a'); //'ab'
let s2 = str.padEnd(3,'c');   //'bcc'

'es8'.padStart(2);          // 'es8'
'es8'.padStart(5);          // '  es8'
'es8'.padStart(6, 'woof');  // 'wooes8'
'es8'.padStart(14, 'wow');  // 'wowwowwowwoes8'
'es8'.padStart(7, '0');     // '0000es8'
'es8'.padEnd(2);          // 'es8'
'es8'.padEnd(5);          // 'es8  '
'es8'.padEnd(6, 'woof');  // 'es8woo'
'es8'.padEnd(14, 'wow');  // 'es8wowwowwowwo'
'es8'.padEnd(7, '6');     // 'es86666'
```

（3）函数形参、实参结尾逗号将不会报错

ES5及之前，数组和对象的结尾就可以加逗号不报错了，ES8函数也增加了这个特性。

```
function aaa(a,){}
aaa(123,);
```

（4）对象方法的扩展

keys，values和entries，keys是ES5及之前就有了，这里放出来只是为了整齐。

若遍历数组、字符串，则是对应的下标和值。

```
let obj = {a:1,b:2};

console.log(Object.keys(obj)); //返回一个数组，值为对象中所有的键
console.log(Object.values(obj)) //返回一个数组，

/*
返回一个数组，每个元素的值为对象中所有的键和值组成的数
组，第一个值为键，第二个值为值*/值为对象中所有的值
*/
console.log(Object.entries(obj));
```

其中entries可以很方便的用对象生成一个Map

```
let m = new Map(Object.entries(obj));
```

Object.getOwnPropertyDescriptors()

```
let obj = {a:1,b:2};

/*
返回obj的属性的描述对象（描述对象就是用Object.create()创建
出来的对象的那种格式，内容有是否可枚举/可删除等）
主要作用是实现更深层次的对象拷贝，把是否可枚举/可删除等都拷贝了
*/
console.log(Object.getOwnPropertyDescriptors(obj));
```

（5）共享内存

## 4 ES9

（1）对象rest参数和扩展运算符

① 对象rest参数

为对象提供了像ES6数组一样的rest参数

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

可以做对象属性得到过滤：

```
const obj = {a: 1, b: 2};
const {b, ...xxx} = obj;
console.log(b);    // 2
console.log(xxx);  // {a: 1}
```

② 对象的扩展运算符：

对象也可以使用扩展运算符了。

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

注意，数组和对象之间不能互相用扩展运算符，如：

```
let obj = {a: 1}
let arr = [1]
//let newObj = {...arr} //报错
//let newArr = [...obj] //报错
```

数组/对象的扩展运算符可以实现单层的深拷贝。

（2）模板字符串增强

ES2018 放松了对标签模板里面的字符串转义的限制。如果遇到不合法的字符串转义，就返回`undefined`，而不是报错，并且从`raw`属性上面可以得到原始字符串。

```
function tag(strs) {
  console.log(strs[0]); //undefined
  console.log(strs.raw[0]); //"\\unicode and \\u{55}";
}
tag`\unicode and \u{55}`;
```

上面代码中，模板字符串原本是应该报错的，但是由于放松了对字符串转义的限制，所以不报错了，JavaScript 引擎将第一个字符设置为`undefined`，但是`raw`属性依然可以得到原始字符串，因此`tag`函数还是可以对原字符串进行处理。

（3）Promise.finally()

在.then()和.catch之后，新增了.finally()，不管Promise成功还是失败都会回调

```
new Promise().finally();
```

（4）正则扩展

① 对分组可进行命名

左括号后加?<别名>  如：

```
let a = /\w+(?<num>\d+)/
```

exec和match，matchAll获得的匹配结果可用匹配结果.groups.num 获得该分组。

② ES9增加了ES5不支持的负向后行断言，正向后行断言
③ 新的匹配模式：dotAll模式（修饰符为s），使得.能够匹配换行符

④为每个字符分配了多个转义属性，如相匹配看看字符串是否存在希腊语字符，可以匹配Script_Extensions属性为Greek的字符。

```
console.log(/\p{Script_Extensions=Greek}/.test('π'));
```

（5）异步迭代器（异步循环，for...await...of）

要理解异步循环，先要理解包含异步操作的正常for循环是如何执行的：

下一段代码符合js执行机制，先执行完全部的同步操作，再执行异步操作

```
function func(i) {
  return new Promise((resolve) => {
    // 传入的i值分别为0,1,2，延迟分别为3000,2000,1000
    setTimeout(() => {
      resolve(i);
    }, (3 - i) * 1000);
  });
}

console.log('start');
for (let i = 0; i < 3; i++) {
  console.log(`同步${i}`);
  func(i).then((res) => {
    console.log(`异步${res}`);
  });
}
console.log("end");
/*
start
同步0
同步1
同步2
end
异步2
异步1
异步0
*/
```

如何此时结合了async/await，会使得前一部分是同步for循环，后一部分是异步for循环，原因是await后面的代码相当于.then里面的代码造成的，await后面的await相当于嵌套.then。

结合这些特性，就非常适合用于发送一系列请求且一个请求的发送需要上一个请求的结果的场景。

注意：async函数里面的代码本质是async函数返回的那个Promise内的代码，参考async笔记和js执行机制笔记。

```
async function run1() {
  console.log('start');
  for (let i = 0; i < 3; i++) {
    console.log(`${i}`);
    let res = await func(i);
    console.log(`异步${res}`);
  }
  console.log('for执行完我才执行');  //这是最后一次await后的then
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

而此次新增的异步迭代器则是让整个for循环都变成异步，相当于上一段代码展示的for循环里面只有异步代码没有同步代码的情况。

注意：async函数里面的代码本质是async函数返回的那个Promise内的代码，参考async笔记和js执行机制笔记。

```
//for...await...of必须连用，且必须在async函数内
async function run2() {
  console.log('start');
  for await (let i of [0, 1, 2]) {
    console.log(i);
    let res = await func(i);
    console.log(`异步${res}`);
  }
  console.log('for执行完我才执行');  //这是最后一次await后的then
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

flat() flatMap() ,用于数组降维，返回结果为降维后的数组。

都不改变原数组

```
let arr2 = [1,2,[3,4]];
let arr3 = [1,2,[3,4,[5,6]]];

//flat
console.log(arr2.flat());  // [1,2,3,4] 二维转化一维
console.log(arr3.flat());  // [1,2,3,4,[5,6]] 三维转二维
console.log(arr3.flat(2)); // [1,2,3,4,5,6] 三维转一维，2表示深度2,3-1=2，空参则默认为1

//flatMap,相当于map之后使用flat()
let arr = [1,2,3];
//先map后flat
let arrMap = arr.map(item=>[item*10,item*20]); //[[10,20,30],[20,40,60]]
console.log(arrMap.flat());  //[10,20,30,20,40,60]
//flatMap
console.log(arr.flatMap(item => [item * 10,item * 20]));  //[10,20,30,20,40,60]
```

以前的降维方式：

```
let arr = [1,[2,3,[4,5,6]]];

//方法一，自定义递归函数
/*
优点是不用对结果进行数据类型转换
缺点是写法复杂
*/
function myFlat(arr,deep = 1){
  if(deep < 1)  return [...arr];
  let res = [];
  for(let i of arr){
    if(Array.isArray(i))  res = [...res, ...myFlat(i,deep - 1)];
    else  res.push(i);
  }
  return res;
}
console.log(myFlat(arr,2));


//先转为字符串，再转为数组
/*
优点是写法简单
缺点是结果需要数据类型转换，这里就不处理了
*/
function func(arr){
  let str1 = arr.toString();
  //let str2 = arr.join();  //也可以用join
  return str1.split(',');
}
console.log(func(arr));
```

（4）Sysbol新增description

获取Sysbol的描述字符串

```
let a = Symbol('123456')
console.log(a.description) //输出123456
```

（5）JSON的改变

① JSON superset

什么是 JSON 超集？，简而言之就是让 ECMAScript 兼容所有JSON支持的文本。 ECMAScript 曾在标准 JSON.parse 部分阐明 JSON 确为其一个子集，但由于 JSON 内容可以正常包含 U+2028行分隔符 与 U+2029段分隔符，而ECMAScript 却不行。

② JSON.stringify() 增强能力

JSON.stringify在 ES10 修复了对于一些超出范围的 Unicode展示错误的问题。因为 JSON 都是被编码成 UTF-8，所以遇到 0xD800–0xDFFF 之内的字符会因为无法编码成 UTF-8 进而导致显示错误。在 ES10 它会用转义字符的方式来处理这部分字符而非编码的方式，这样就会正常显示了。

```
// \uD83D\uDE0E emoji 多字节的一个字符
console.log(JSON.stringify('\uD83D\uDE0E')) // "😎"

// 如果我们只去其中的一部分 \uD83D 这其实是个无效的字符串
// 之前的版本 ，这些字符将替换为特殊字符，而现在将未配对的代理代码点表示为JSON转义序列
console.log(JSON.stringify('\uD83D')) // "\ud83d"
```

（6）catch的err可选

try...catch... 不再必须需要err

```
//之前
try {

}catch(err){}
//现在
try {

}catch{}
```

（7）Function.prototype.toString() 的修改

之前将函数转为字符串会把空格和换行符去掉，ES10之后不会。

## 6 ES11

（1）Promise.allSettle(xxx)

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

（2）可选链操作符 ?.

语法 obj?.属性 当obj存在时，才会调用属性，防止出现 undefined.属性 的情况

调用对象、数组、函数时均可使用

```
let obj1 = {a: 1}, obj2 = null;
let arr1 = [1], arr2 = null;
let func1 = () => {}, func2 = null

//?.的作用就是，若?.左边不对，就返回undefined
console.log(obj1.a, obj2?.a);  //1,undefined
console.log(arr1[1], arr2?.[1]);  
console.log(func1(), func2?.());  

//应用，可以看到res3,res2,res1作用相同，res3节省了很多代码
let obj = {a:1};
let res1 = obj.b && obj.b.bb;
let res2 = obj.b ? (obj.b.bb ? obj.b.bb : undefined) : undefined;
let res3 = obj?.b?.bb;
```

若node环境中报错，则需要node升级更高版本，或者安装依赖

```
npm install @babel/plugin-proposal-optional-chaining --save-dev
```

（3）空值合并操作符 ??

??操作符是一个判断是否为空然后赋值的操作，如果没有这个操作符，类似于短路运算符 ||，左边为null或undeiined时就使用右边的值。

区别在于，||的依据是判断左边是否为布尔值，所以0，''等都会隐式类型转换为false，而??的依据是判断左边是否为null或undefined。

```
let a = 0 || 12;  //12
let b = 0 ?? 12;  //0
```

（4）动态import

ES6的是静态import，这里的动态import实现按需加载（懒加载）

```
import(‘…’).then(r=>{
 //r为导出的东西
})
const a = import(‘xxx’) //路由懒加载
```

（5）import.meta

`import.meta`是一个给 JavaScript 模块暴露特定上下文的元数据属性的对象。它包含了这个模块的信息，比如说这个模块的 URL。

```
console.log(import.meta);
```

（6） 新基本数据类型，大整型：BigInt

```
//声明
let a = 123n;

//将Number和String转为BigInt，只能装整数，小数不行
let b = BigInt(567);
let c = BigInt('12');

//运算,BigInt只能和BigInt或String运算
let d = 123n + 456n;  //579n;
let e = 123 + '456n'; //'123456'

//BigInt也能转为Number，但会涉及到边界问题
let f = Number(123456n);

//也提供了对应BigInt的数组构造函数
let arr1 = new BigInt64Array(2); //length=2
let arr2 = new BigInt64Array(3). //length=3
//由于每个数组元素限制最大64位，所以即使是无符号类型最多也只有64位
arr1[0] = 2n ** 64 //0n，超出限制的值转为0n
arr2[1] = 2n **64 - 1n ;  //可存储的最大值

//Number和BigInt值相等时，不严格相等；可以比较大小
console.log(2n == 2);  //true
console.log(2n === 2); //false
console.log(2n > 1);   //true
console.log(2n > 2);   //false

//BigInt转为Boolean和Number一样
console.log(!!0n);     //false
console.log(!!10086n); //true

//Number能表示的最大整数
let max = Number.MAX_SAFE_INTEGER + 1;
//再大就要转为BigInt
console.log(BigInt(a+10));
console.log(typeof max); //BigInt
```

* 可以和字符串一起运算，字符串'2n'或转为'2'

* BitInt一定是正数，所以除法的结果会去掉小数

* 部分内置库如Math无法使用BigInt

（7）新关键字：globalThis

始终指向全局环境（浏览器是window，node是global）

字符串使用正则的新方法：
str.matchAll(reg) 解决了match在全局模式下不显示全部信息的情况

（8）正则匹配 String.prototype.matchAll()

ES5正则中，若想获得所有匹配结果并同时得到下标，只能使用循环：

```
const regExp = /yyds(\d+)/g;
const text = 'yyds1 is a very good yyds2';
let matches;
while ((matches = regExp.exec(text)) !== null) {
  console.log(matches);
}
/*结果
["yyds1","1"]
["yyds2","2"]
*/
```

使用起来有诸多的不便，为了简单起见，ES11引入了matchAll()方法。这个方法可以简单的返回一个遍历器，通过遍历这个遍历器，就可以得到所有的匹配的值，如下所示：

```
const regExp = /yyds(\d+)/g;
const text = 'yyds1 is a very good yyds2';
let matches = [...text.matchAll(regExp)];

for (const match of matches) {
  console.log(match);
}
```

（9）for in 规范了遍历顺序

在之前的 ES 规范中几乎没有指定 for-in 语句在遍历时的顺序，但各 ES 引擎的实现在大多数情况下都是趋于一致的，只有在一些边界情况时才会有所差别。我们很难能够要求各引擎做到完全一致，主要原因在于 for-in 是 ES 中所有遍历 API 中最复杂的一个，再加上规范的疏漏，导致各大浏览器在实现该 API 时都有很多自己特有的实现逻辑，各引擎的维护人员很难有意愿去重新审查这部分的代码。

因此规范的作者作了大量的工作，去测试了很多现有的 ES 引擎中 for-in 的遍历逻辑。并梳理出了它们之间一致的部分，然后将这部分补充到了 ES 规范 当中。

## 7 ES12

（1）String.prototype.replaceAll()

以前的replace只能替换匹配到第一个，除非使用正则的g模式来全部替换。

而现在replaceAll可以替换全部匹配结果。

模式的所有匹配都会被替代项替换。模式可以是字符串或正则表达式，而替换项可以是字符串或针对每次匹配执行的函数。不改变原字符串。

```
const str = '2022-10-06';
const newStr = str.replace(/-/g,'/');   //'2022/10/05'
const newStr = str.replaceAll('-','/'); //'2022/10/05'
```

（2）Promise.any()

接收一个多个Promise的数组，一旦其中一个Promise最快成功那Promise.any()就成功，全部失败那Promise.any()就失败。

有点像多个Promise在竞速。

```
let p1 = new Promise((resolve) => {
  setTimeout(() => resolve('p1'),1000);
});
let p2 = new Promise((resolve) => {
  setTimeout(() => resolve('p2'),2000);
});
let p3 = new Promise((resolve,reject) => {
  reject();
});
let p4 = new Promise((resolve,reject) => {
  reject();
});

Promise.any([p1,p2]).then(res => {
  console.log(res);  //'p1'，1秒后输出
});
Promise.any([p2,p3]).then(res => {
  console.log(res); //‘p2’，2秒后输出
});
Promise.any([p3,p4]).catch(err => {
  console.log(err); 
});
```

（3）逻辑赋值操作符

??=  &&= ||=

x ??= y，逻辑空赋值运算符，仅在x为null或undefined时给x赋y值

```
let a, b = 123;
a ??= 456; //456
b ??= 456; //123
```

&&=，逻辑与赋值运算符，左truee/false，赋值/不赋值

||=，逻辑或赋值运算符，左true/false，不赋值/赋值

```
let a = true, b = false;
a &&= 123; 
b ||= 123; 
console.log(a,b);  //123 123
a = true;
b = false;
a ||= 456; 
b &&= 456; 
console.log(a,b);  //true,false
```

??=和&&=、||=的区别，与??和||的区别一样：

```
let a = 0;
a ??= 123;
console.log(a);  //0，a不为null/undefined，不赋值
a ||= 123;
console.log(a);  //123，a为0转为false，执行赋值

let b = '';
b ??= 123;
console.log(b);  //''，b不为null/undefined，不赋值
b &&= 123;
console.log(b);  //''，b为''转为false，不赋值
```

（4）WeakRef

WeakRef 是一个 Class，一个 WeakRef 对象可以让你拿到一个对象的弱引用。这样，就可以不用阻止垃圾回收这个对象了。  
可以使用其构造函数来创建一个 WeakRef 对象。

```
let obj = {a:1};
//弱引用，不会因为wr引用了obj，而不回收{a:1}
let wr = new WeakRef(obj);
```

我们可以用 WeakRef.prototype.deref() 来取到 anObject 的值。但是，在被引用对象被垃圾回收之后，这个函数就会返回undefined。

```
console.log(wr.deref());
```

（5）数字的下划线分隔符

当你要写一个很长的数字的时候，数字太长会导致可读性很差。  
使用了数字分隔符 _ （下划线），就可以让数字读的更清晰：

```
let a = 100000000;
let b = 1_0000_0000;
let c = 100_000_000;
console.log(a === b);  //true
console.log(a === c);  //true
console.log(b === c);  //true
```

## 8 ES13

（1）class新特性

① 公共实例字段

可以直接在类里声明变量，而不一定要在构造函数里面（之前好像是必须要在构造函数里面声明变量）

```
//之前
class A {
  constructor(){
    this.a = 123;   
  }
}

//现在
let test = 'Name'
class B {
  a = 123;
  b;  //未赋值默认为undefined
  //字段名也可以是表达式计算出来，但是要用[]包裹
  [`user${test}`] = 'lgx'  
}
let b = new B();
console.log(b.userName);
```

② 私有属性，私有方法

默认情况下，类内的属性/方法噶都是public的，现在可以通过#来声明private的属性/方法。

私有属性/方法在类外不可调用，类内可以调用，用#声明，类内调用时，不能少了#

```
class a {
  name;
  #age;
  #run(){};
  constructor(name,age){
    this.name = name
    this.#age = age
  }
  //可以给私有属性对应的get，set方法
  //也可以使用ES6的数据访问器 set xxx(){}  get xxx(){}
  getAge(){
    console.log(this.#age)
  }
  //ES6存取器也是属性，也可以设置为私有
  get #xxx(){}
}

let aaa = new a('lgx',20)
console.log(aaa) //看不到age
console.log(aaa.name,aaa.age) //无法调用私有属性，结果为undefine
aaa.getAge() //通过类内的方法噶来则可以调用
```

③ 静态属性/方法 static

用static修饰属性和方法。被static修饰的属性/方法是静态的，静态属性/方法挂载在类本身上面；而未被static修饰的属性/方法是非静态的，只有在实例化对象时才挂载在对象上。

所以具备以下特点：

* 静态属性/法法，实例化对象调用是undefined，只能类本身调用；而非静态属性/方法，，只能实例对象调用，类本身调用为undefined。

* 静态属性只能被静态方法调用。且静态方法也只能调用静态属性/方法，调用非静态属性为undefined。而非静态方法调用静态属性是undefined。

* 如果想用非静态方法调用静态属性/方法，可以：
  
  ```
  class A {
    static a = 123;
    func(){
      console.log(A.a);  
    }
  }
  ```

* 静态属性/方法也会被继承

代码测试：

```go
class A {
  a = 123;
  static b = 456;
  static func1(){
    console.log(this.a);
    console.log(this.b);
    console.log(A.b);
  }
  func2(){
    console.log(this.a);
    console.log(this.b);
    //非静态方法可通过类名调用静态属性/方法
    console.log(A.b);
  }
}

//类本身只能调用静态属性/方法
console.log(A.b); //456
A.func1();  //undefined 456 456
console.log('a' in A); //false
console.log('b' in A); //true
//类本身无法调用非静态属性/方法
console.log(A.a); //undefined
// A.func2(); //报错，没有undefined()这个方法

//实例对象只能调用非静态属性/方法
let a = new A();
console.log(a.a); //123
a.func2();  //123 undefined 456
//实例对象无法调用静态属性/方法
console.log(a.b);  //undefined
//a.func1(); //报错
```

也可以定义静态的私有字段和方法：

```go
class A {
  static #a = 123;
}
```

同时具有私有和静态的限制，把私有和静态特点结合起来就行，只是这里的私有不仅仅针对实例对象，还会影响类本身：

```
class A {
  static #pri = 'private';
  static getPriA(){
    return A.#pri;
  }
}
console.log(A.pri);  //undefined，因为a是私有的
console.log(A.getPriA())  //'private'
```

此外，在继承的子类中，也无法通过父类名来调用父类的私有静态属性/方法。

④ 类的静态初始化代码块

在类内，只能写构造函数，声明属性/方法这些，而不能写其他的代码，这时候就可以使用代码块。

特点：

* 代码块可以有多个

* 代码块会在代码编译时就执行

* 代码块是静态的，只能调用静态属性/方法

* 代码块内部定义的都属局部变量/方法

```go
class Person {
  static sta = 'static';
  stnoSta = 'no static';
  static {
    console.log(this.sta);   //'static'
    console.log(this.noSta); //undefined
    let a = 123;
  }
}

//运行后就会直接执行代码块
console.log(Person.a)  //undefined，因为a是代码块内的局部变量
```

特别的是，代码块内可以调用非静态的私有属性/方法。但是不能直接调用，因为代码块执行时对象为实例化，也就调用不了。它真正的作用是提供给类外部调用类内私有属性/方法的途径。

可以在代码块内这么做：

```go
let getPri;
class A {
  #noSta = 'no static';
  static #sta = 'static';
  static {
    console.log(this.#sta); //'static'
    // console.log(this.#noSta); //报错，不能从为实例化对象中调用私有属性
    getPri = (obj) => obj.#noSta ;
  }
}
let obj = new A();
//console.log(obj.#noSta); //报错，不能在类外调用私有束胸
console.log(getPri(obj));  //no static
```

⑤ 配合in运算符

由于尝试访问对象上不存在的私有属性/方法，会发生异常，因此需要能够检查对象是否具有给定的私有属性/方法噶。

可以使用 `in` 运算符，in 来检查类/对象是否含有对应的属性/方法，返回一个布尔值。

```
'pub' in xxx  //公共属性/方法需要加引号
#pri in xxx   //私有属性/方法不需要加引号
```

若想检查公共属性/方法噶，在类内外都可以检查。

若想检查私有的属性/方法，只能在类内通过方法来检查。

in 也可以检查类本身是否含有静态属性/方法。

```
class A {
  pub = 1;
  #pri = 2;
  static staPub = 3;
  aaa(){}
  static #staPri = 4;
  func1(obj){
    return #pri in obj;
  }
  //为了方便调用，func2也可以写成静态方法
  func2(){
    return #staPri in A;
  }
}

console.log('pub' in A);    //false
console.log('staPub' in A); //true
// console.log(#pri in A); //true
// console.log(#staPri in A); //报错
// console.log()

let a = new A();
console.log('pub' in a);    //true
console.log('staPub' in a); //false
console.log('aaa' in a);    //true
// console.log(#pri in A); //true
// console.log(#staPri in A); //报错
console.log(a.func1(a));  //true
console.log(a.func2());  //true
```

（2）at()

at() 是一个数组/字符串方法，用于通过给定索引来获取数组元素/字符串元素。

当给定索引为正数时，这种新方法与使用中括号表示法访问具有相同的行为；  

当给出负整数索引时，就会从数组的最后一项开始检索；

```
let arr = [1,2,3];
console.log(arr.at(0));  //1
console.log(arr.at(-1)); /

let str = 'abcd';
console.log(str.at(0));  //a
console.log(str.at(-1)); //d
```

（3）正则表达式匹配索引

新的修饰符d，表示想要匹配字符串的开始和结束索引。  
以前，只能在字符串匹配操作期间获得一个包含提取的字符串和索引信息的数组。在某些情况下，这是不够的。因此，在这个规范中，如果设置标志 /d，将额外获得一个带有开始和结束索引的数组。

```javascript
const matchObj = /(a+)(b+)/d.exec('aaaabb');

console.log(matchObj[1]);   // 'aaaa'
console.log(matchObj[2]);   // 'bb'
```

由于 /d 标识的存在，matchObj 还有一个属性 .indices，它用来记录捕获的每个编号组：

```javascript
console.log(matchObj.indices[1]);   // [0, 4]
console.log(matchObj.indices[2]);   // [4, 6]
```

（4）Object.hasOwn()

在此之前，我们可以使用 Object.prototype.hasOwnProperty() 来检查一个属性是否属于该对象。  
Object.hasOwn() 特性是一种更简洁、更可靠的检查属性是否直接设置在该对象上的方法：

```javascript
const example = {
  name: 'leo'
};

console.log(Object.prototype.hasOwnProperty.call(example, 'name')); // true
// 更简洁的方式
console.log(Object.hasOwn(example, 'name')); // true
```

（5）Error Cause

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

（6）顶层await

在 ES2017 中，引入了 async await，以简化 Promise 的使用，但是 await 关键字只能在 async 函数内使用。如果在异步函数之外使用 await 就会报错。  
顶层 await 允许我们在 async 函数外使用 await 关键字。它允许模块充当大型异步函数，通过顶层 await，这些模块可以等待资源加载，这样其他导入这些模块的模块在执行代码之前要等待资源加载完才会去执行。  
之前由于 await 仅在 async 函数中使用，因此模块需通过将代码包装在 async 函数来在代码中包含await：

```javascript
// test.js
let users;

export const fetchUsers = async () => {
  const res = await fetch('https://www.leoTest.com/users');
  users = res.json();
}
fetchUsers();

export { users };


// usingAwait.js
import { users } from './test.js';
console.log('users: ', users);
console.log('usingAwait module');
```

这样会有一个缺点，直接导入的 users 会是 undefined。如果我们需要访问得到它，需要在异步执行完成之后：

```javascript
// usingAwait.js
import { users } from './test.js';

console.log('users:', users);   // 直接访问，undefined

setTimeout(() => {
  console.log('users:', users);   // 等待异步执行完成，再进行访问
}, 100);

console.log('usingAwait module');
```

当然，这种方法并不完全实现，因为如果异步函数执行花费的时间超过100毫秒，它就不会起作用了，users 仍然是 undefined。  
还有另一个方法是导出一个 Promise，让导入模块知道数据已经准备好了：

```javascript
// test.js
export default (async () => {                   // 导出一个 Promise
  const res = await fetch('https://www.leoTest.com/users');
  users = res.json();
})();
export { users };


// usingAwait.js
import Promise, { users } from './test.js';
Promise.then(() => { 
  console.log('usingAwait module');
  setTimeout(() => console.log('users:', users), 100); 
});
```

虽然这种方法似乎是会得出预期的结果，但也有一定的局限性：导入模块必须了解这种模式才能正确使用它。  
而 top-level await（顶层 await）可以解决这些问题：

```javascript
// test.js
const res = await fetch('https://www.leoTest.com/users');   // 使用顶层 await
const users = res.json();
export { users };


// usingAwait.js
import { users } from './test.js';

console.log(users);
console.log('usingAwait module');
```

此时的 users 必须等到异步执行完毕才会访问。

顶层 await 在以下几种场景中将非常有用：

- 动态加载模块

```javascript
const str = await import(`/i18n/${navigator.language}`);
```

- 资源初始化

```javascript
const con = await dbConnector();
```

- 依赖回退

```javascript
let translations;
try {
  translations = await import('https://app.fr.json');
} catch {
  translations = await import('https://fallback.en.json');
}
```

## 9 ES14

2023年正式发布。目前部分新特性已到第4阶段。

（1）数组的findeLast()

find()的逆向版。

## 10 关于ECMA新特性的使用、

注意，自从TC39进程指定以来，新特性提案阶段就比ecma版本更为重要，因为某个ecma版本发布的新特性不一定全部能用，未正式发布的新特性也可能可以使用。

能不能用得看这个新特性是否处于第4个提案阶段。

ECMA新特性的指定分为4个阶段，当处于第4阶段的新特性才能正式使用。如果想看这些正式可用的新特性有哪些，可访问：https://github.com/tc39/proposals/blob/main/finished-proposals.md

如果想看正在开发测试中的新特性，可以访问：

https://github.com/tc39/ecma262/blob/main/README.md

此外，对于特别新的特性，需要检查浏览器版本和node版本是否支持。

# 六、JS高级内容

以下都是JS的高级用法，且面试也经常问。

## 1 JS执行机制

执行上下文：就是C语言的执行栈。代码开始执行，全局环境入栈，函数执行则函数入栈，函数执行完函数出栈。

### 1.1 同步，异步：

- JS是单线程的，分为同步任务和异步任务，同步任务即一行行执行，异步任务则是在适当的时机执行（异步任务包括定时器，事件，网络请求，回调函数等）

- 执行过程：
  
  将同步任务放入执行栈，将作为异步任务放入任务队列（又叫消息队列）。先执行同步任务，遇到了异步任务就把异步任务放入任务队列中且不执行，当所有同步任务都完成后，进入事件轮循。
  
  注意定时器的规则有点不同
  
  - 是所有同步任务执行完再执行异步任务，setTimeout即使设置延时为0，也要在所有同步任务执行完后，才开始计时。
  
  - 即便同步任务全部完成，定时器也要在在延时到达后，才会进入任务队列，相同时间则按代码顺序来，每一批进入队列都是不同的事件
  
  - 循环

- 事件轮循
  
  在任务队列中，循环查看是否有符合条件的异步任务，条件符合就把异步任务放到执行栈中执行。这个过程会一直重复，这就叫事件轮循
  
  异步任务又可以分为微任务(Promise的then)和宏任务(定时器，ajax，读取文件)

- 整体执行顺序
  
  在node中，有process.nextTick(() => {})和setImmediate(() => {})两个api，这里为了简便，纪委a和b，它们的执行顺序是：
  
  同步任务-a-事件轮循第一次循环后-b-继续事件轮循 详细规则如下：
  
  1. 第一轮事件循环结束的标志是第一个或第一批相同延时定时器执行结束
  
  2. 第一轮事件轮循中异步任务的执行顺序：微任务-宏任务，其中微任务会全部执行完，后面的每一轮只有宏任务
  
  3. 若Promise有嵌套，则先执行完所有Promise的第一层，以此类推
  
  4. awit后面的代码块执行顺序相当于then，await下面还有await，相当于嵌套Promise
  
  5. 执行顺序相同的，按代码先后顺序执行

- js执行顺序的例子：
  
  ```
  async function fun2(){
    console.log('d');
  }
  async function fun1(){
    console.log('c');
    await fun2();
    console.log('e');
    await fun2();
    console.log('f');
  }
  
  setTimeout(() => console.log(1)); //不给时间，默认0
  console.log(2);
  setTimeout(() => console.log(3),0);
  setTimeout(() => console.log(4),100);
  console.log(5);
  new Promise(resolve => {
    resolve();
  }).then(() => {
    console.log('a');
    new Promise(resolve => {
      resolve();
  }).then(() => {
      console.log('b');
    })
  })
  new Promise(resolve => {
    console.log(6);
    resolve();
  }).then(() => {
    console.log(7);
  })
  process.nextTick(() => {
    console.log(8);
  })
  setImmediate(() => {
    console.log(9);
  })
  fun1()
  
  //执行顺序：256cd8a7e1394
  /**�򵥽���
  2 5 6 c d  同步任务
  8          process.nextTick()
  a 7 e d    第一重事件循环的第一层微任务
  b f        第一重事件循环的第二层微任务    
  1 3        第一重事件循环的宏任务
  9          ΪsetImmediate()
  4          第二重事件循环的宏任务
  **/
  ```

### 1.2 预编译

也叫预解析

JS引擎运行JS代码分为预编译和编译运行两部分：

预编译，将各作用域var和function声明提升到当前作用域最前。

编译运行：由上至下一行行解释运行。

（1）var的预编译：

只有var存在变量提升，let和const没有。

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

（2）具名函数预编译：

提升function声明，不提升调用。即命名函数调用可以在声明前。（匿名函数不行）

### 1.3 垃圾回收机制

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

## 2 作用域

（1）作用域

作用域分类：

* 全局作用域

* 局部作用域：函数体，形参

* 块级作用域：if，slse，switch，for

var没有块级作用域，所以在if，for等里面的var是全局变量，而let和const有了块级作用域。

在函数体内，不加var声明但赋值的变量也是全局变量。

形参本身就不用加var，一定是局部变量

（2）作用域链

作用域链：全局->局部/块级->局部/块级->......

调用变量的规则：

* 内部可调用外部的变量，反之不行。

* 调用时找最近一级有该变量的外层作用域，找不到就继续网上找（链式查找）。全局变量是最远的一级。

## 3 闭包

（1）闭包是什么

内部函数可访问外部函数的资源，则该内部函数就是闭包，被访问的资源不会被回收，最常见的是函数内return子函数，该子函数就是一个闭包，子函数内引用父函数的资源不会被回收，但是没引用的会回收

（2）闭包的实现

例1：

```
function func1(){
  let a = 0,b = 0;
  return function(){
    console.log(++a);
  }
}
let f = func1();
f(); //输出1
f(); //输出2
/*
闭包现象在哪：在fun函数外，可以访问到fun函数里面的变量a，
哪个是闭包：return出的函数为闭包
垃圾回收：a因为被用了，不会被回收，b没有用，被回收
*/

//闭包的错误使用例子
function func2(){
  let a = 0,b = 0;
  return function(){
    console.log(++a);
  }()
}
func2();    //1
func2();    //1
func1()();  //1
func1()();  //1
/*
之所以没有达到预期的效果，是因为return出去的是函数且直接调用了，使得每次调用fun()，都是
新的独立的闭包，a自然就不是同一个了。
这种错误使用不仅仅没有达到闭包的效果，也使得闭包的变量没有销毁；且由于每次调用都是新的一
个闭包，调用n次就有n个闭包变量，完全没有意义且占用内存；所以需要特别注意
*/
```

例2，参数为函数fn时且想在闭包内调研，fn的形参如何定义：

```
//普通参数
function func1(fn){
  return function(a){
    fn(a)
  }
}

let f1 = func1((a) => {
  console.log(a)
})
f1(123)

//rest参数
function func2(fn){
  return function(...rest){
    fn(...rest)
  }
}

let f2 = func1((a, b, c) => {
  console.log(a, b, c)
})
f2(123, 456)
```

例3：

```
for(var I=0;i<=3;i++){
 异步代码
}
/*
由于js的执行机制，先执行完同步再进入事件循环执行异步，所以i一直是3，一种解决方法是使用let使得其有块级作用域，使得每一次i都驻留在内存中。
另一种方法是使用闭包：
*/
for(var I=0;i<=3;i++){
  (function(){
    //异步代码
  })(i)
}
//使用立即执行函数将异步代码的函数包裹，使得异步代码的函数成为闭包，闭包使用i使得i驻留在内存中。
```

例4：

```
//筛选出数组中[a,b]的元素
function fun(a,b){
  return function(item){
    return item >= a && item <= b
  }
  arr.fiter(fun(a,b))
}
```

（3）闭包优缺点

闭包好处：*可在函数外访问函数内的资源 *可防止函数内的资源被回收
闭包坏处：函数内的资源不被回收，用不好会导致内存损耗（低版本IE更会导致内存泄漏）。解决方法是将不需要使用的闭包设置为null

（4）也可以用其他方式实现闭包相同的效果

- 定义成全局变量，但是肯定会产生变量冲突问题

- 定义一个class，存放闭包使用的变量和原来闭包的函数

## 4 this指向全总结

### 4.1 基本

- 只有在调用函数时，this才有意义，不调用时没有意义，每个函数调用时都会产生独立的this。

- 函数外的this指向window，函数内看规则，函数内使用严格模式（加上一行代码 ’use strict’ ），可以使得指向window变成undefined

### 4.2 普通函数内this四种绑定规则

优先级：new>显示>隐式>默认

（1）默认绑定规则

- 全局环境下，指向window

- 函数独立调用（即不通过 对象. 来调用），指向window，如立即执行函数，内嵌函数，对象的方法的内嵌函数，return的闭包，形参子函数且在父函数内被调用都是独立调用函数

（2）隐式绑定规则：

- 谁调用就指向谁 a.fun() 指向a，a.b.fun() 指向b。

- 对象方法赋值给全局变量，变量()执行，指向window，本质是函数独立调用，因为赋值时并没有调用，是在变量()指向时才调用，所以指向window，这样叫做隐式丢失。

- 对象方法作为形参，且在父函数内被调用，本质函数独立调用，指向window

（3）显示绑定规则：
js函数本身是一个对象，有一个调用的方法噶call()，所以函数调用 funm(形参….) 是 * * fun.call(this指向,形参….)的语法糖。
fun.call(this指向,形参….)
fun.apply(this指向,形参数组)
let f=fun.bind(this指向,形参….); f();
三种效果一样。

（4）new绑定：
构造函数指向new出来的对象。若构造函数内有return且不是return this 就会该边this指向为return的东西（但一般不会这么做）

### 4.3 箭头函数内的this

由于内嵌函数的this指向window，若想this指向父函数，可以在父函数内用 let That=this，子函数内使用That实现，或者使用显示规则改变this指向，这是在没有箭头函数之前的做法。

- 箭头函数本身没有this，它的this实际上是父级作用域的this四种规则（也可以说是定义该箭头函数的执行上下文所在的对象）（一定要注意父级作用域是哪个）
  
  ```
  let obj = {
      fun: () => {}
  }
  obj.fun()
  /*
  指向window，定义该箭头函数的是obj对象，obj所在的作用域是全局window
  */
  ```

- 默认/隐式/显示规则对箭头函数都无效，箭头函数不能作为构造函数自然也没有new规则。

### 4.4 api的回调函数

- api的回调函数this指向由api作者决定

- 不管api内部如何实现，只要回调函数为箭头函数，就要用箭头函数this规则

- Vue的api的回调函数的this指向Vue实例。

5 实例

```
let name='window'
 let obj1={
 name:'1',
 fn1(){
 console.log(this.name)
 },
 fn2:()=>console.log(this.name),
 fn3(){
 return function(){
 console.log(this.name)
 }
 },
 fn4(){
 return ()=>console.log(this.name)
 }
 }
 let obj2={
 name:'2'
 }
 obj1.fn1() //1，普通函数的隐式规则
 obj1.fn1.call(obj2) //2，普通函数的显示规则
 obj1.fn2() //window，箭头函数的父作用域是全局的默认规则，this执行window
 obj1.fn2.call(obj2) /* window，箭头函数没有显示规则，且父作用域是全局的默认规则，                                            this执行window*/
 obj1.fn3()() //window，普通函数的默认规则
 obj1.fn3().call(obj2) //2，普通函数的显示规则
 obj1.fn3.call(obj2)() //window，普通函数显示后再默认
 obj1.fn4()() //1，箭头函数的父作用域为obj1的隐式规则，name为1
 obj1.fn4().call(obj2) /* 1，箭头函数没有显示规则，且父作用域为obj1的隐式规则，name                                         为1 */
 obj1.fn4.call(obj2)() //2，普通函数显示后，箭头函数的父级作用域的隐式
```

## 5 防抖与节流

有对应的库：

```
npm install --save lodash
```

也可以手写。

### 5.1 基本

防抖与节流的作用都是为了减少函数不必要的执行，限制执行次数，比如在网络请求中如果有大量不必要的请求时非常损耗性能的。又比如滚动事件的调用是非常频繁的，而实际并不需要这阿么多次的调用。

防抖和节流的共同点：

- 都是为了减少不必要的执行次数，优化性能

- 都是在一开始等待delay后才会开始执行第一次

区别是：

- 防抖是在delay计时完后，才允许执行一次，且如果在delay内操作了两次及以上，则会重置定时器，重新计时delay

- 节流是在限定的时间内，限制执行n次，一秒执行 1000/delay 次

几个使用上的注意点：

- 为了防止多个功能调用防抖/节流函数时产生变量冲突，防抖/节流用到的变量要使用闭包，不要定义为全局变量（解决了不同文件调用防抖/节流函数时的变量冲突问题）

- 只要用了闭包，那么在不同的文件中引入使用防抖/节流函数就不会有变量冲突；但是如果在同一个文件中有不止一个功能需要用到防抖/节流时，就不要使用引入的同一个防抖/节流函数，否则会有冲突，解决方式是将引入的防抖/节流函数分别保存给不同的变量，一个功能使用一个变量保存的防抖/节流函数

- 不管是防抖还是节流的实现都是基于定时器，也就是一上来是需要等待一段时间才会执行。所以在含有网络请求的业务中，为了用户体验，应当在第一次的时候立即执行

- 上拉加载不应该使用防抖/节流，使用防抖如果在delay内一直上拉，则永远不会加载；使用节流也只是限制了请求的次数而已；而上拉加载最好是在加载时不再另外加载，可以使用布尔值来控制

- 有些看似可以使用防抖/节流的需求，实际上是不能用的，需谨慎使用，比如上拉加载不需要防抖/节流，只需要if判断是否在加载中，节流还是会加载多次，防抖反而会影响用户体验；有时监听滚动也不一定要节流，如需要实时监听滚动的需求。

### 5.2 防抖

场景：

一个表单的功能是当输入完成后，显示内容，若不是要防抖，则每输入一个字符都会显示内容，而实际上只需要在输入完成后再显示就能达到需求，中间有大量的无意义的函数执行。

是要防抖，每次输入时给一个延时s，若：

- 未超过s，则清空s重新计时，且不显示内容，说明还未输入完成

- 超过s，则输出内容，说明输入完成

代码：

```
<body>
    <input type="text" >
  </body>
  <script>
    let inp = document.querySelector('input')
    inp.oninput = debunce(function(){
      console.log(this.value)
    },1000)

    /*错误写法
    inp.oninput = function(){
      debunce(function(){
        console.log(this.value)
      },1000)()
    }
    */

    function debunce(fn,delay=1000){
      //这里使用了闭包，使得t不会被销毁
      let t = null
      return function(){
        if(t != null)  clearTimeout(t)
        t = setTimeout(() => {
          //此处为内嵌函数的独立调用，this指向window，需要call()改变指向
          let That = this
          fn.call(That) 
        },delay)
      }
    }
  </script>
```

### 5.3 节流

场景：

滚动事件的触发非常频繁，实际上不需要这么多，现在要求减少它的触发次数

代码：

```
window.onscroll = throttle(function(){
  console.log('123')
},1000)
function throttle(fn,delay=1000){
  let flag = true
  return function(){
    if(flag){
      setTimeout(() => {
        let That = this
        fn.call(That)
        flag = true
      },delay)
      flag = false
    }
  }
}
```

### 5.4 Vue中使用

Vue使用会有一个非常容易出错的点：

Vue2：

```
method: {
  //func1，func2是事件监听函数
  //这样试错的，因为这样根本就不是同一个闭包，参考闭包笔记
  func1: function(){
    debunce(() => {
      console.log(123)
    },1000)()
  },
  //这样才是对的
  func2: debunce(() => {
      console.log(123)
    },1000)  
}
```

Vue3：

Vue3的this指向undefined，所以防抖节流函数中的 let that = this 可以删去，fn.call(that) 改为 fn()

```
setup(){
  //func1，func2，func3是事件监听函数
  //错误写法
  function func1(){
    debunce(() => {
      console.log(123)
    },1000)()
  }

  //正确写法
  let func2 = debunce(() => {
    console.log(123)
  },1000)

  //也可以这么写，不过就不太优雅了
  let f = debunce(() => {
      console.log(123)
   },1000)
  function func3(){
    f()
  }
}
```

总之，就是要保证事件监听函数使用的是同一个闭包函数。

### 5.5 ts中的防抖和节流

ts中也可以使用闭包实现，注意形参和定时器的类型。

需要先安装 @types/node 获取定时器的类型：

```
npm install --save @types/node
```

闭包版：

```
export function debunce(fn: Function, delay: number = 1000) {
  let t: NodeJS.Timeout | null = null;
  return function () {
    if (t != null) clearTimeout(t)
    t = setTimeout(() => {
      fn();
    }, delay)
  }
}

export function throttle(fn: Function,delay: number = 1000){
  let flag: boolean = true;
  return function(){
    if(flag){
      setTimeout(() => {
        fn();
        flag = true;
      },delay);
      flag = false;
    }
  }
}
```

class版：

不过ts的class也挺好用（虽然js也可以用class，不过个人不太喜欢js的class语法），所以也可以用class来保存原来js闭包的数据，以下是ts的防抖/节流的封装（这里加了个功能，可通过immediate来控制是否一开始就立即执行一次）.

```
export class Debunce {
  private timer: NodeJS.Timeout | null = null
  private immediate: boolean = false
  public debunce(func: Function,delay: number, immediate: boolean = false){
    let that = this
    return function(){
      if(!that.immediate && immediate){
        that.immediate = true
        func()
      }
      else {
        if(that.timer != null) clearTimeout(Number(that.timer))
        that.timer = setTimeout(() => {
          that.immediate = false
          func()
        },delay)
      }
    }
  }
}

export class Throttle {
  private flag: boolean = true
  private immediate: boolean = false
  public throttle(func: Function, delay: number, immediate: boolean = false){
    let that = this
    return function(){
      if(!that.immediate && immediate){
        func()
        that.immediate = true
      }
      else if(that.flag){
        setTimeout(() => {
          func()
          that.flag = true
          that.immediate = true
        },delay)
        that.flag = false
      }
    }
  }
}
```

使用：

```
import {Debunce} from '...'
...
//每个功能都要new一个，防止冲突
let func1 = new Debunce().debunce(() => {
  console.log(123) 
}, 1000)
...
```

## 6 传值传址，深浅拷贝

堆和栈：

内存分两大块，一个是栈（也叫堆栈），一个是堆

栈内存存放基本数据类型的值和引用数据类型的指针（地址），堆内存存放引用数据类型的值。

```
//变量a，b变量都存放到栈内存中的不同空间，a空间存5，b空间存a的值，就是5
let a = 5
let b = a

//obj1,obj2变量都存放在栈内存中的不同空间，值都是指向同一个堆内存的指针地址，堆内存只有一块，值为{a:1}
let obj1 = {a: 1}, arr1 = [1]
let obj2 = o1, arr2 = arr1
```

浅拷贝出现在引用数据类型，即数组，对象

浅拷贝与深拷贝的区别-

基本数据类型类型直接赋值拷贝酒香，而引用数据类型(对象)则要考虑浅拷贝与深拷贝

浅拷贝是拷贝地址，拷贝出的新对象和被拷贝的对象指向堆内存的同一个地址，这样修改一个对象，另一个对象也同时修改，因为它们实际都是一个对象。像对象直接赋值给新对象，就是浅拷贝

```
/*此时的内存
栈内存：栈指针地址s1-obj=对指针地址值a1  栈指针地址s2-newObj=堆指针地址值a1
堆内崔：堆指针地址a1-值={name: 'lgx'}
*/
let obj = {name: 'lgx'}
let arr = [1,2]
let newObj = obj  //浅拷贝
let newArr = arr  //浅拷贝
//若浅拷贝的变量对立面的数据进行修改，由于与源数组/源对象指向同一地址，源会同样修改
let newArr[0] = 5
console.log(arr[0])

//若将浅拷贝的变量再赋值新值，则newObj和obj指向的不再是同一个地址，互不影响
/*此时的内存
栈内存：栈指针地址s1-obj=对指针地址值a1  栈指针地址s2-newObj=123
堆内崔：堆指针地址a1-值={name: 'lgx'}
*/
let obj = {name: 'lgx'}
let newObj = obj
newObj = 123

/*此时的内存
栈内存：栈指针地址s1-obj=对指针地址值a1  栈指针地址s2-newObj=堆指针地址值a2
堆内崔：堆指针地址a1-值={name: 'lgx'}   堆指针地址a2-值={}
*/
newobj = {}

//同理，obj赋新的值也一样指向不同的内存地址
/*此时的内存
栈内存：栈指针地址s1-obj=对指针地址值a2  栈指针地址s2-newObj=堆指针地址值a1
堆内崔：堆指针地址a1-值={name: 'lgx'}  堆指针地址2-值={xxx: 123}
*/
let obj = {name: 'lgx'}
let newObj = obj
obj = {xxx: 123}

/*浅拷贝情况
只要是赋值，且不做任何处理的情况都是浅拷贝，如函数形参，数组push对象或数组，for...of
和forEach遍历出来得到数组/对象
*/
```

深拷贝则是新申请一个内存地址，再拷贝，这样两个对象的修改就互不影响，完全就是两个不同的对象，有两种方法实现深拷贝

方法一

利用JSON的api，将对象转为字符串再转为对象

```
function deepCopy(obj){
  let newObj = JSON.stringify(obj)
  return JSON.parse(newObj)
}
```

使用时会有JSON的api的限制，详见ajax笔记。

方法二：

扩展运算符实现

```
let obj = [
  a; 1
}
let arr = [1,2]

let newObj = {...obj}
let newArr = [...arr]
```

除了无法拷贝原型上的自定义属性和方法，其他JSON的api的缺陷全部解决，但是扩展运算符只能处理一层的深拷贝，无法处理嵌套的

方法三：

递归实现

遍历旧对象的的属性，给新对象添加对应的属性，若该属性又是一个对象，则要使用递归。

需要实现的功能：

* NaN，函数，基本数据类型不需要深拷贝，直接诶返回

* 支持循环引用的深拷贝

* 支持Symbol，Date，RegExp的深拷贝

* 支持对象、数组、Set、WeakSet、Map、WeakMap的深拷贝

* Symbol可以作为对象和Map的键，由于Symbol键在对象中无法正常遍历出来（Map可以），需要解决。

Symbol比较特殊，虽然是基本类型，但是也涉及深拷贝的问题

函数没要深拷贝。

如果需要同时深拷贝原型上的自定义属性和方法，则参考原型笔记中的7.3，遍历出所有键，再补充这里的代码，由于比较少用这里就不实现了。

```
function deepCopy(source, hash = new WeakMap()) {
  //不需要递归深拷贝的类型
  const nonRecursionTypes = ['[object Symbol]', '[object Date]', '[object RegExp]'];
  //需要递归深拷贝的类型
  const recursionTypes = [
    '[object Object]', 
    '[object Array]',
    '[object Set]',
    '[object Map]',
    '[object WeakSet]',
    '[object WeakMap]'
  ];
  const type = Object.prototype.toString.call(source);

  //1.如果是NaN，函数或基本数据类型（Number,String,Boolean,null,undefined,BigInt），直接返回
  if (!recursionTypes.includes(type) && !nonRecursionTypes.includes(type)) return source;

  //2.如果是Symbol，Date或RegExp，简单深拷贝后返回
  if(nonRecursionTypes.includes(type))  return  type === '[object Symbol]' ? Symbol(source.description) : (type === '[object Date]' ? new Date(source) : new RegExp(source));  
  //3.如果是循环引用，直接return
  if (hash.has(source)) return hash.get(source);
  hash.set(source, source);

  //4.若果是需要递归深拷贝的类型
  let res = null;
  switch (type) {
    case '[object Array]':
    case '[object Object]':
      res = Array.isArray(source) ? [] : {};
      //之所以不直接用for遍历source是因为这样遍历不出键位Symbol的属性，ownKeys才行
      Reflect.ownKeys(source).forEach(i => {
        if(i !== 'length' || type === '[object Object]'){
          res[i] = deepCopy(source[i], hash);
        }
      })
      break;
    case '[object Set]':
    case '[object WeakSet]':
      res = new Set();
      for (let i of source) res.add(deepCopy(i, hash));
      break;
    case '[object Map]':
    case '[object WeakMap]':
      res = new Map();
      for (let [k, v] of source) res.set(k, deepCopy(v, hash));
      break;
    default: break;
  }
  return res;
};


//测试代码
/*
let m = new Map();
m.set('mmm', 'mmm');
let obj = {
  num: 123,
  bigint: 123456789123456789n,
  nan: NaN,
  und: undefined,
  arr: [1, 2],
  obj: {a: 1, b: 2},
  func: () => 123,
  null: null,
  [Symbol('111')]: 111,
  set: new Set([5, 6]),
  map: m,
  sym: Symbol('sym'),
  date: new Date(),
  reg: new RegExp()
};
//测试循环引用
let objTest = {
  obj
};
obj.myself = obj;
obj.objTest = objTest;
obj.arr.push(obj.arr);
obj.set.add(obj.set);
obj.map.set('m', obj.map);
//输出
console.log(obj)
console.log(deepCopy(obj));
*/
```

## 7 原型

JS中每个对象和函数都有自己的原型对象，可以调用，添加原型对象的属性和方法。

### 7.1 原型是什么

原型是一个对象，所以也叫原型对象。

只要是构造函数，都有显示原型属性指向它的原型，由于js中普通函数都是构造函数，所以普通函数也有原型，而箭头函数本身不能作为构造函数，所以箭头函数不睡构造函数也就没有原型。

```
let ObjFunc = function(){
  this.a = 123;
};
function func0(){};
let func1 = function(){};
let func2 = () => 123;

console.log(ObjFunc.prototype);  //有原型
console.log(func0.prototype);    //有原型
console.log(func1.prototype);    //有原型
console.log(func2.prototype);    //undefined
```

只要是对象，包括字面量对象和构造函数new出的一个实例对象d，都有一个隐式原型属性指向它的原型。

```
let ObjFunc = function(){
  this.a = 123;
};
let obj1 = new ObjFunc();
let obj2 = {b: 456};

//注意左右两边都是双下划线
console.log(obj1.__proto__);
console.log(obj2.__proto__);
```

构造函数的原型和new出的对象的原型是同一个原型对象。

```
console.log(ObjFunc.prototype === obj1.__proto__);  //true
```

由于原型对象也是对象，所以也有隐式原型属性，且原型对象的构造者是顶级构造函数Object，所以原型对象的原型就是Object的原型

```
console.log(ObjFunc.prototype.__proto__ === Object.prototype);  //true
```

Object没有构造者，所以Object的原型对象的原型为null

```
console.log(Object.prototype.__proto__);  //null
```

原型链：从上面就可以看出，从一个对象/构造函数-原型-...-Object-Object原型，形成了一条原型链。

### 7.2 原型上的属性和方法

（1）给原型添加属性和方法

```
ObjFunc.prototype.aaa = 123;
ObjFunc.prototype.bbb = function(){};
obj.__proto__.ccc = 456;
obj.__proto__.ddd = function(){};
```

（2）调用原型的属性和方法

```
console.log(ObjFunc.prototype.xxx);
console.log(obj.__proto__.xxx);
```

obj访问原型的属性方法可以简写：

```
console.log(obj.xxx);
```

简写的原理是，先在对象自己内部找xxx，找不到就去原型对象找，再找不到继续往上，最终到Object。

（3）遍历出包括原型上的自定义属性方法在内的对象中所有属性方法

只有for...in...可以遍历出原型上的自定义属性和方法。

```
let o = {a: 123, [Symbol('b')]: 456};
o.__proto__.c = 789;
o.__proto__[Symbol('d')] = 000;

//以下都遍历不出原型上的自定义属性和方法
console.log(o);
console.log(Object.keys(o));
console.log(Object.getOwnPropertyNames(o));
console.log(Reflect.ownKeys(o));

//只有fon...in...可以，但是无法遍历出原型上的Symbol键
for(let i in o) console.log(i)

//如果要把对象的Symbol键和原型上的Symbol键，就：
let keys = [];
for(let i in o)  keys.push(i);
keys = [
  ...new Set([
  ...keys, ...Object.getOwnPropertySymbols(o), 
  ...Object.getOwnPropertySymbols(o.__proto__)])
];
keys.forEach(i => {
  console.log(obj[i]);
));
```

### 7.3 构造函数的原型继承

对象可以调原型的属性方法很像继承，在ES6中有class及继承，但是ES5只有构造函数，想要实现构造函数继承需要借助原型

```
function User(username,password){
  this.username = username
  this.password = password
  this.login = function(){
    console.log('登陆了')
  }
}
function Admin(){
  this.deleteUser = function(){
    console.log('删除用户')
  }
}
Admin.prototype = new User('管理员',123456) //继承就这一行代码
let admin = new Admin()
console.log(admin.username) //省略了__proto__
//  admin.login()admin--.__proto__-->原型:new User()--.__proto__-->原型:User().prototype--__.proto__-->Object
```

## 8 事件流

HTML是一个树结构，html标签是根结点，事件处理包括事件捕获和事件冒泡两个阶段。默认情况下，事件在冒泡阶段触发。

- 事件捕获：从根结点出发到叶子结点捕获事件

- 事件冒泡：从粗发事件的对象出发到根结点，若该事件对象的祖先有定义相同事件，则也会触发。

- 冒泡情况，输出small，mid，big
  
  ```
  <body>
    <div class="big">
      <div class="mid">
        <div class="small"></div>
      </div>
    </div>
  </body>
  <script>
  let small = document.getElementsByClassName('small')
  let mid = document.getElementsByClassName('mid')
  let big = document.getElementsByClassName('big')
  small[0].onclick = function(){
    console.log('small')
  }
  mid[0].onclick = function(){
    console.log('mid')
  }
  big[0].onclick = function(){
    console.log('big')
  }
  ```

事件冒泡有好有坏，一般需要关闭冒泡，但有时也可以利用冒泡实现事件委托

- 事件委托：将子元素的时间委托到父元素

- 实例
  
  给ul的每个li绑定点击事件，点击console.log()
  
  如果给每个li都绑定事件，则不利于后期维护，代码也复杂。
  
  只给ul绑定点击事件，当点击li时，通过冒泡触发ul的点击事件，事件对象为该li
  
  ```
  <body>
    <ul>
      <li>1</li>
      <li>2</li>
      <li>3</li>
    </ul>
  </body>
  <script>
  let ul = document.querySelector('ul')
  ul.onclick = function(e){
    console.log(this)    //因为一直都是ul的事件，所有this指向ul
    console.log(e.target.innerText) //当前事件对象为被点击的li
  }
  </script>
  ```

## 9 异常处理

当代码出错时，会报错并终止运行，可以使用异常处理使报错后不终止运行。

```
try {
  console.log(a)   //a未定义，使用异常处理后，不报错，将报错信息在catch处理，可以理解为报错变为了程序运行的一部分
}
catch(err) {
  console.log(err)
}
```

throw抛出异常，在一些业务中，可能需要手动抛出异常，在处理具有大量代码的项目bug时，是很难根据报错来找到bug的，可以利用抛出异常来方便检查是哪里出了问题

throw一般与try，catch配合使用。

```
let inp = document.getElementById('inp')
let btn = document.getElementById('btn')

btn.onclick = function(){
  try {
    if(inp.value == '') throw '输入框1不能为空'
  }
  catch(err) {
    alert(err)
  }
}
```

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
