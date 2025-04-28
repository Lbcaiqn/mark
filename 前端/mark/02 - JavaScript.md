# 一、ES5

JS 是面向对象的脚本语言，组成：

* ECMAScript（ES，JS的语法）

* DOM（页面文档对象模型，对标签进行操作实现动态效果）。

* BOM（浏览器对象模型，操作浏览器窗口）

JS 书写位置：

* 行内式，标签内书写 事件=””

* 内嵌式，<script>JS代码</script>

* 外部式，<script src=”xxx.js”>此处不能写代码</script>，

## 1 变量、数据类型、运算符

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

（2） 变量，数据类型，运算符

变量、数据类型，数据类型只有 8 种，7 个基本类型 \+ 1 个引用类型；

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

运算符：

中断运算的运算结果是中断的结果，而不像 C 语言中是 Boolean ：

```
// 123 456
console.log(true && 123);
console.log(false || 456);
```

== 会进行隐式类型转换再比较 value ，而 === 会先比较数据类型：

```
// true false
console.log("123" == 123, "123" === 123);

// false true
console.log("123" != 123, "123" !== 123);
```

n 运算符，判断 key 是否存在于 Object 中，会涉及判断到原型上：

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

（3）流程控制

使用循环时，需要注意var会被提升成全局变量（闭包或 let 、const 解决）。

```
var arr = [1, 2, 3];

for (var key in arr) console.log(key);

// this 可不传，默认为 arr
arr.forEach(function (value, key, arr) {
  console.log(arr, key, value);
}, this);
```

其他与C语言一样。

## 2 对象

（1）基本使用

```
// 创建 -------------------------------------------------------------------------------
// 构造函数创建，过程：bnew Object() -> 修改 this -> 执行构造函数 -> return this
function Obj(n) {
  this.a = n;

  // 默认返回值
  // return this;
}
var obj1 = new Obj(123);

// 字面量创建，底层会调用 new Object()
var obj2 = {
  a: 1,

  // key 的引号可以省略，如果是复杂的 key 则必须加引号
  "b.b.b": 2,

  // 都是匿名函数
  func: function () {
    console.log("func");
  },
};

// 调用、添加、删除属性 ----------------------------------------------------------------
// 调用
console.log(obj1.a, obj1["a"]);
// undefined ， 调用没有的属性得到 undefined
console.log(obj1.aaa);
// err ，无法从 undefined 中调用任何属性
// console.log(o.a);

// 删除
delete obj1.a;

// 添加到对象自身
obj1.b = 3;
obj1["c"] = 3;

// 添加到圆形
obj1.__proto__.d = 4;
Obj.prototype.e = 5;

// 添加 static 属性
Obj.f = 6;

// true
console.log(obj1.__proto__ == Obj.prototype);
```

对象的 key 只能是 string 或 Symbol ，如果是其他类型则会转为 string ：

```
var obj = {};
var arr = [];

// 等价于 obj["[object Object]"] = "obj"
obj[{ a: 1 }] = "obj";
// "obj"
console.log(obj["[object Object]"]);

// 等价于 arr["0"] = 123
arr[0] = 123;
// 123
console.log(arr[0]);
```

（2）Reflect 反射

ES6 新特性，对象的任何操作，都会转化成浏览器的内部方法，数组、函数等也是对象，对其的操作也会转化成内部方法。这些方法开发者无法使用，ES5 无法使用这些方法的。

```
const obj = {};

// 等价于 set(obj, "a") ，此时 key 一定是 string
obj.a = 1;

// 等价于 set(obj, "b") ，不同的是如果 key 可能不是 string ，就会强制类型转换成 string
obj["b"] = 2;

// 调用内部方法 defineProperty
Object.defineProperty(obj, "c", { value: 3 });

// 等价于 get(obj, key)
console.log(obj.a, obj["b"], obj.c, "\n");
```



而 Reflect 就有这些内部方法：

```
const obj = {};

// Reflect 使用这些内部方法时，会 try...catch 处理是否处理成功，返回布尔值
// 第三个参数为 this 指向
Reflect.set(obj, "a", obj);

// undefined ，没有圆形
console.log(Reflect.prototype);

// 但是具备 OBJECT 的 static 方法
// Object 圆形上的方法渐渐地也部署成 static 方法了，因此 Reflect 也有
console.log(Reflect.hasOwnProperty, "\n");
```

Reflect 应用场景：

```
// 简化内部操作 -----------------------------------------------------------------------
const obj = { a: 1 };

Object.defineProperty(obj, "b", {
  value: 2,
  enumerable: false,
});

// ["a"] ，keys 方法内部会判断并过滤掉非枚举 key ，再调用 ownKeys
console.log(Object.keys(obj));
// ["a", "b"] ，如果不想要 keys 的操作，就可以直接使用 ownKeys
console.log(Reflect.ownKeys(obj), "\n");

// 修改 this ------------------------------------------------------------------------
const o = {
  a: 1,
  get b() {
    return this.a;
  },
};

const p = new Proxy(o, {
  get(t, k, r) {
    console.log(k);

    // return t[k];
    return Reflect.get(t, k, r);
  },
});

// "b" ，没有 a 是因为 this 只想的是 o ，而不是 p
// "b" "a" ，使用 Reflect 修改 this 为 p 后就可以了
p.b;
```



（2）函数

函数也是对象，调用函数本质就是执行了这个函数对象的 call 方法，因此由 call 方法的对象就是一个函数。

基本使用：

```
// 具名函数
function func1() {
  // 可以在 function 内部定义 function ，内部函数只能在外部函数内使用
  // 不要在 if 等块级作用域声明函数，ECMA 并没有这个标准，不同浏览器的运行逻辑不同
  function func11() {
    P;
  }
}

// 匿名函数
var func2 = function () {};

// JS 没有类型检测，所以不知道传入的参数是什么类型
function func(a, b) {
  // 设置默认值
  b = b || 2;

  console.log(a, b);

  // arguments 保存了传入的所有实参，包括多传的参数
  console.log(arguments);

  // true ，argument 是一个伪数组，具有 length 也可以下标访问，但没有 Array 的方法，因为伪数组是 Object 构造的
  // JS 获取的 DOM 也是伪数组
  console.log(arguments.__proto__ === Object.prototype);

  // ES6 新特性，可以将伪数组转为 Array ，不会改变原伪数组
  var args = Array.from(arguments);
  // true
  console.log(args.__proto__ === Array.prototype, "\n");

  // 默认 return
  // return undefined;

  // 2，错误写法，只能 return 一个值，return 多个则最后一个生效
  // return 1, 2;
}

var func3 = func2;

// func1 func2 func2 ，name 保存了函数名，匿名函数则是保存了最初引用该函数的变量名
console.log(func1.name, func2.name, func3.name);

// 2 ，获取形参个数，注意是形参不是实参
console.log(func.length);

// 1 2 [1, 2, 3] ，多传的参数也放入 argument
func(1, 2, 3);

// undefined 2 [] ，参数没传且没默认值则 undefined
func();

// 1 2 [1, 2] ，函数调用本质是调用了 call 方法
// 等价于 func(1, 2)
func.call(this, 1, 2);
```

函数签名：

由函数名、形参列表、返回值组成，配合文档注释可以说明函数如何使用：

```
/**
 * 求和
 * param {Number, Number} 两个数值
 * return {Number} 求和结果
 */
function sum(a, b) {}
```

立即执行函数：

是匿名函数，不用调用，会立即执行，只执行一次，内部会形成独立的作用域，var 就不会和外部冲突了：

```
(function () {
  console.log("方式一");
})();

(function () {
  console.log("方式二");
})();
```

（3）数组

Array ，构造函数 ，即 Array 也是对象：

```
var arr = [1, 2];
var arr1 = new Array(2);
var arr2 = new Array(2, 123);

// [undefined, undefined] ，[123, 123]
console.log(arr1, arr2);

// 2
console.log([1, 2].length);

// Array 转 String ，不改变原数组
// "1,2" "1,2,3"
console.log([1, 2].toString(), [[1, 2], [30]].toString());
// "1&2"
console.log([1, 2].join("&"));

// 头尾增加、删除，会改变原数组
console.log(arr);
var b = arr.pop();
var a = arr.shift();
arr.push(22);
arr.unshift(11);
// [11, 22] 1 2
console.log(arr, a, b);

// [22] ，删除左闭右开的元素，会改变原数组
arr.splice(0, 1);
console.log(arr);
// [2] ，替换
arr.splice(0, 1, 2);
console.log(arr);
// [1, 2, 3] ，插入
arr.splice(0, 0, 1);
arr.splice(2, 0, 3);
console.log(arr);

// 翻转、排序，会改变原数组
// [3, 2, 1]
arr.reverse();
console.log(arr);
// [1, 2, 3]
arr.sort();
console.log(arr);
// [3, 2, 1]
arr.sort(function (a, b) {
  return b - a;
});
console.log(arr);

console.log("----------------------------------------");

// 以下方法都不改变原数组 ---------------------------------------------------------
// [1, 2, 3, 4] ，拼接
console.log([1, 2].concat([3, 4]));

// [1, 2] ，取出左闭右开的元素
console.log([1, 2, 3].splice(0, 2));

// 查找 ，返回下标，找不到返回 -1 ，第二个参数是开始下标
// 0 2 -1 -1
console.log(
  [1, 2, 3].indexOf(1),
  [1, 2, 3].lastIndexOf(3),
  [1, 2, 3].indexOf(1, 1),
  [1, 2, 3].lastIndexOf(3, 1)
);
```

（4）包装类

除了 null 、undefined 的其他 5 哥基本数据类型，都有包装类，内置了一些属性和方法。

```
var n = 123;
var s = "asdf";
var b = true;

var num = new Number(123);
var str = new String("asdf");
var bool = new Boolean(true);

// 123 "asdf" true
console.log(n, s, b);

// 都是对象
console.log(num, str, bool);
```

其中 String 即使不是 new 出来的，也可以直接使用包装类的 API ，但由于 String 是基本类型，每次调用 API 都会生成一个临时的包装类 String 对象：

```
// "a" 4
console.log("asdf"[0], "asdf".length);

var str = "asdf";

// node 会报错，不允许这么做，浏览器就可以
str[0] = "q";
str.a = "1";

// "asdf" undefined ，因为修改的是临时对象
console.log(str, str.a);
```

String 中的 API ：

```
var sxtr1 = "";
var str2 = new String("asdf");

// 4 "asdf"
console.log("asdf".length, "as" + "df");

// 大小写转换
console.log("asdf".toUpperCase(), "ASDF".toLowerCase());

// ["as", "df"] ，string 转 Array ，不改变原字符串
console.log("as df".split(" "));

// 访问
// "a" 97
console.log("asdf".charAt(0), "asdf".charCodeAt(0));
// "a" ，HTML5 新增
console.log("asdf"[0]);

// "as" ，用法和 slice 一样
console.log("asdf".substring(0, 2));

// 替换第一个遇到的子串，不改变原字符串
// "dfdf"
console.log("asdf".replace("as", "df"));

console.log("----------------------------------------------");

// 以下方法用法都和 Array 一样，不改变原字符串 ----------------------------------------
// "asdf"
console.log("as".concat("df"));

// "asd"
console.log("asdf".slice(0, 3));

// 查找 ，返回下标，找不到返回 -1 ，第二个参数是开始下标
// 0 3 -1 -1
console.log(
  "asdf".indexOf("a"),
  "asdf".lastIndexOf("f"),
  "asdf".indexOf("a", 1),
  "asdf".lastIndexOf("f", 2)
);
```

（5）正则

```
// 创建正则 ----------------------------------------------------------------------------
// 字面量，只能是 /reg/
var reg1 = /a/;

// 构造函数创建，strinmg 和 /reg/ 都可以
var reg2 = new RegExp(/a/);
var reg3 = new RegExp("a");

// 修饰符，用于修改匹配模式 ---------------------------------------------------------
// 默认情况区分大小写，只匹配第一个结果
var r1 = /a/;

// g：找到所有结果  ， i：不区分大小写  ， m：每行分别匹配
var r2 = /a/g;
var r3 = new RegExp("a", "i");
var r3 = /a/gim;

// 匹配 ------------------------------------------------------------------------------
// 找到第一个匹配结果（g 无效），结果为 Array ，信息包含匹配结果、首字符下标等；找不到为 null
// [ 'as', index: 0, input: 'asdf', groups: undefined ]
console.log(/as/.exec("asas")), reg1;

// 默认模式和 exec 一样，g 模式则返回所有匹配结果
// [ 'as', index: 0, input: 'asdf', groups: undefined ]
console.log("asas".match(/as/));
// ["as", "as"]
console.log("asas".match(/as/g), "\n");

// 配合 string 内置方法 -------------------------------------------------------------
// "dfas" ，正则替换，不改变原 string
console.log("asas".replace(/as/, "df"));

// ["as", "as"] ，正则将 string 转 Array ，不改变原 string
console.log("as-as".split(/-/), "\n");

// 配合 ES6 的 every 实现多正则匹配，如密码检测 ------------------------------------
var reg = [/[a-zA-Z0-9]{6,10}/, /[A-Z]/, /[0-9]/];
console.log(reg.every((r) => r.test("123456")));
```

（6）其他内置对象

Math ，只是对象，不是构造函数：

```
// 圆周率 正无穷 负无穷
console.log(Math.PI, Math.max(), Math.min());

// 参数会隐式转为 number ----------------------------------------------------------
// 2 1
console.log(Math.max(1, 2), Math.min(1, 2));

// 绝对值 下取整 上取整 四舍五入
console.log(Math.abs(-3), Math.floor(3.1), Math.ceil(3.9), Math.round(3.5));

// 0 ~ 1 的随机数
console.log(Math.random());

// min ~ max 的随机整数
function myRandom(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}
console.log(myRandom(10, 50));
```

Date ，构造函数：

```
var date = new Date();

// 年 月 日 星期 时 分 秒
console.log(
  date.getFullYear(),
  date.getMonth() + 1,
  date.getDate(),
  date.getDay() || 7,
  date.getHours(),
  date.getMinutes(),
  date.getSeconds()
);

// 获取时间戳（1970.1.1 到现在的 ms）
console.log(date.getTime(), date.valueOf());

// HTML5 新增获取时间戳的方式
console.log(Date.now());
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

| 鼠标事件        | 描述             |
| ----------- | -------------- |
| click       | 单机             |
| dblclick    | 双击             |
| mousedown   | 按下             |
| mouseup     | 谈起             |
| mounseenter | 鼠标经过，经过子盒子时不触发 |
| mouseleave  | 鼠标离开，离开子盒子不触发  |
| mouseover   | 鼠标经过，经过子盒子时也触发 |
| mouseout    | 鼠标离开，离开子盒子也触发  |
| mousemove   | 鼠标移动           |

| 键盘事件     | 描述                       |
| -------- | ------------------------ |
| keydown  | 按键按下，按键按着不放就一直触发，可识别所有键  |
| keypress | 按键按下，按键按着不放就一直触发，不能识别功能键 |
| keyup    | 按键弹起                     |

注意事项：

* event.keyCode 可获得按键码，up，down 不区分大小写，press 区分。通过event.keyCode 可实现对特定键的监听

| form 事件 | 描述  |
| ------- | --- |
| submit  | 提交  |
| reset   | 重置  |

| input 事件 | 描述                 |
| -------- | ------------------ |
| focus    | 聚焦                 |
| blur     | 失焦                 |
| input    | 每次输入、退格都触发         |
| change   | enter 和失焦触发        |
| invalid  | 非法输入时触发，可自定义非法输出信息 |

注意事项：

* 表单应当都放在 form 中，提交时监听 submit 事件，可以避免很多问题

* 部分类型 input 无法用某些 input 事件

| 移动端触屏事件     | 描述         |
| ----------- | ---------- |
| touchstart  | 手指触屏       |
| touchmove   | 手指移动       |
| touchend    | 手指弹起       |
| touchcancel | 触屏事件被取消时触发 |

其他事件：

```
// 鼠标右键菜单事件，常应用与阻止右键弹出菜单
document.addEventListener("contextmenu", function (e) {
  e.preventDefault();
});

// 选中文本时触发，常应用于阻止选中文本
document.addEventListener("selectstart", function (e) {
  e.preventDefault();
});
```

（3）事件对象

通用：

| 属性/方法                   | 描述                                                                                    |
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

### 1.3 获取几何信息

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

如果父元素是body或者祖先都没有设置定位，那使用offsetLeft，offsetTop就可以了，但是其他情况就需要 rect 。

offset 、client 、scroll 无法计算 transform 的偏移，而 rect 可以。

```
console.log(e.getBoundingClientRect());
/*top，left，bottom，right*/
```

（5）获取元素到整个页面边缘的偏移

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

BOM，浏览器对象模型，API 都放在 window ，使用时可以省略 window 。

（1）BOM 事件

| 页面事件             | 描述                                                             |
| ---------------- | -------------------------------------------------------------- |
| load             | 页面所有内容，包括标签文本图片样式都加载完才触发                                       |
| DOMContentLoaded | 当DOM加载完（即所有标签），就触发                                             |
| pageshow         | 与onload基本一样，但是在火狐浏览器中，前进页面后，之前的页面会缓存，再后退不会触发onload，而pageshow可以 |

注意事项：

* 若引入 JS 在 html 页面之前 ，JS 就拿不到页面元素，此时就要 load ：
  
  ```
  // 多个 onload 事件只执行最后一个
  window.onload = function () {
    // 此时 JS 就能拿到页面元素了
  };
  ```

| 窗口事件   | 描述             |
| ------ | -------------- |
| scroll | 滚动             |
| resize | 浏览器窗口大小发生变化时触发 |

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

处理 url ，和页面跳转、刷新：

```
// 获取 url'信息
console.log(
  location.href,
  location.host,
  location.pathname,
  location.search,
  location.hasg
);

// 跳转页面（也叫重定向），跳转后可返回原页面
location.assign("url");

// 跳转，但无法返回
location.replace("url");

/**刷新页面
 * true ：强制刷新页面，数据全部清空
 * false 或无参数：非强制刷新，会缓存一些数据，刷新会快一些
 */
location.reload();
```

（4）navigation

可以得到浏览器的信息，如当前的设备是 PC 还是移动端：

```
console.log(Navigator.userAgent.match());
```

（5）history

与浏览器的历史记录进行交互，保存了用户浏览过的地址：

```
// 前进
history.forward();

// 后退
history.back();

// 正数前进、附属后退
history.go(1);
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

let 、const 也会变量提升，但在声明之前是暂时性死区（TDZ），不允许使用：

```
// err ，暂时性死区
try {
  console.log(a, b);
} catch {
  console.log("err");
}

let a = 1;
const b = 2;
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

## 3 新数据类型

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

## 4 迭代器

### 4.1扩展运算符、 解构赋值

（1）扩展运算符

转化成逗号分隔的列表，具备 iterator 接口的数据类型才可使用：

```
const arr1 = [1, 2, 3];

// 用于函数 ---------------------------------------------------------------------
// 简化传参
function func1(a, b, c) {
  console.log(a, b, c, "\n");
}

// 1 2 3
func1(...arr1);

// 用于数组等有 iterator 接口的数据结构 --------------------------------------------
// 构建新的数组，也能实现浅层深拷贝
const arr2 = [...arr1, 4, ...arr1];

// 数组去重
const arr3 = [...new Set([...arr2])];

// [1, 2, 3, 4, 1, 2, 3]
console.log(arr2);

// [1, 2, 3, 4]
console.log(arr3, "\n");

// ES9 新特性，对象字面量也可以使用，但不是基于迭代器 ---------------------------------------
const obj = { a: 1, b: 2, c: 2 };

// 扩展 key: value ，相同的 key ，后面会覆盖前面的
const o = {
  ...obj,
  c: 33,
  ...arr1,
};

// err ，扩展对象得到的是 key: value ，不能给数组使用
try {
  const a = [...o];
} catch {
  console.log("err");
}

// 1 2 33 1 2 3
console.log(o.a, o.b, o.c, o["0"], o["1"], o["2"]);
```

（2）解构赋值

将数组、对象中的元素/属性一次赋值给多个变量，若变量多余数组元素、或变量是对象中不存在的属性，则值为 undefined 。

数组解构实现基于迭代器，而对象解构不是。

可以使用 rest 参数，但只能放在最后面且只能有一个，其中对象在 ES9 后才允许使用 rest 参数：

```
// 数组解构赋值，和顺序有关，可以设置默认值，可以连续解构 ------------------------------------
const arr = [1, 3, 5, [7, 9]];

// 1 3 5 7 9 undefined 10
const [a, b, c, [d, e], f, g = 10] = arr;
console.log(a, b, c, d, e, f, g);

// 1 3 [5, [7, 9]]
const [a1, b1, ...c1] = arr;
console.log(a1, b1, c1, "\n");

// 对象解构赋值，和顺序无关，可以设置默认值，可以起别名，可以连续解构 ---------------------
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

// 18 {age: 18, other: { o1: 123 }} ，可以实现属性过滤
const { name: myName, ...keys } = obj;
console.log(myName, keys, "\n");

// 函数参数、返回值解构 --------------------------------------------------------------
function func1(options) {
  const { type } = options;
  console.log(type);

  return [0, 1];
}

function func2({ a, ...keys }) {
  console.log(a, keys, "\n");
}

// "asdf" 1 2
const [r1, r2] = func1({ type: "asdf" });
console.log(r1, r2);

// 123 {type: "asdf"}
func2({
  a: 123,
  type: "asdf",
});

// 复杂数据的解构 -----------------------------------------------------------------
const data1 = [{ a: 1, b: 2 }];
const data2 = { list: [3, 4] };

const [{ a: dataA, b: dataB }] = data1;
const {
  list: [dataC, dataD],
} = data2;

// 1 2 3 4
console.log(dataA, dataB, dataC, dataD);
```

### 4.2 for\.\.\.of

具备 iterator 接口的数据类型才可使用 。除了 Object 外都有。

for\.\.\.of 、forEach 、for\.\.\.in 异同：

* 都可以遍历出 value 本身就是 undefined 的属性、遍历出的 key 都是 string 

* 除了 Map 用 for\.\.\.of 、forEach 外，其他情况都无法遍历出 Symbol key

* for\.\.\.in 遍历出 key ，for\.\.\.of 和 forEach 遍历出 value
  
  * forEach 还可以传入第二、三个参数，得到 key 和原始引用
  
  * 对于 Map ，for\.\.\. 遍历 Map 得到 key ，for\...of 得到 \[key, value\] 。forEach 则得到 value

* for\.\.\.in 可以遍历出原型链上的自定义属性；for\.\.\.of 、forEach 不可以

* 使用场景：
  
  * Array 、Object 、Set 、Map 均可以用 for...in ；遍历 Set 、Map 只能遍历出原型链上的自定义属性，无法遍历自身的属性
  
  * for...of 、forEach 无法便利 Object ；Array 、Set 、Map 则可以
  
  * WeakSet 、WeakMap 由于是弱引用所以无法以任何形式遍历
  
  * map\(\) 等方法只有 Array 可以用，效果和 for\.\.\.of 一样

示例：

```
const arr = [1, undefined, 3];
arr[Symbol("arr_sym")] = "arr_sym";
arr.__proto__.arrKey = 4;
arr.__proto__[Symbol("arr_proto_sym")] = "arr_proto_sym";

const obj = { a: 1, b: undefined, c: 3, [Symbol("obj_sym")]: "obj_sym" };
obj.__proto__.objKey = 4;
obj.__proto__[Symbol("obj_proto_sym")] = "obj_proto_sym";

const set = new Set([1, undefined, 3]);
set[Symbol("set_sym")] = "set_sym";
set.__proto__.setKey = 4;
set.__proto__[Symbol("set_proto_sym")] = "set_proto_sym";

const map = new Map([
  ["a", 1],
  ["c", 3],
  [Symbol("map_sym"), "map_sym"],
]);
map.__proto__.mapKey = 4;
map.__proto__[Symbol("map_proto_sym")] = "map_proto_sym";

/**for...in ，便利 key ---------------------------------------------------------------
 * 无法便利出 Symbol key
 * 会遍历出圆形链上的自定义属性
 * Set 、Map 只能便利出原型链上的自定义属性，自己身上的无法遍历
 */
// "0" "1" "2" "arrKey" "objKey"
for (const i in arr) console.log("for...in arr", i);
console.log("\n");

// "a" "b" "c" "objKey"
for (const i in obj) console.log("for...in obj", i);
console.log("\n");

// "setKey" "objKey"
for (const i in set) console.log("for...in set", i);
console.log("\n");

// "mapKey" "objKey"
for (const i in map) console.log("for...in map", i);
console.log("\n");

/**for...of ，便利出 value --------------------------------------------------------------
 * 除了 Map 外都无法遍历出 Symbol key ，Map 遍历出 [key, value]
 * 只能遍历有 iterator 接口的数据结构，Object 无法使用
 * 无法遍历原型链上的属性
 */
// 1 undefined 3
for (const i of arr) console.log("for...of arr", i);
console.log("\n");

// err
try {
  for (const i of obj) console.log("for...of obj", i);
} catch {
  console.log("err");
}
console.log("\n");

// 1 undefined 3
for (const i of set) console.log("for...of set", i);
console.log("\n");

// "mapKey" "objKey"
for (const i of map) console.log("for...of map", i);
console.log("\n");

/**froEach ，便利出 value ---------------------------------------------------
 * Map 遍历出 key
 * 其他和 for...of 都一样
 *
 */
// 1 2  "map_sym"
map.forEach((i) => console.log("forEach map", i));
console.log("\n");

// 数组特有遍历方法
arr.map((i) => console.log("arr.map", i));
```

### 4.3 迭代器

（1）基本概念

ES6 提供了 iterator 接口，为不同的数据结构提供统一的访问机制，只有 Object 没有 iterator 接口，其他都有，如 Array、伪数组、String、Set、Map 等

数组解构赋值是按顺序解构出来的，因为底层实现使用的迭代器，扩展运算符和 for\.\.\.of 也只有具备 iterator 接口的数据解构才能使用。

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

（1）形参

rest 参数，也叫剩余参数：

用于接收不定数量的参数，必须放在最后面且只能有一个，接收后是一个数组，可以替代 arguments ：

```
function func(a, b, ...args) {
  console.log(a, b, args);

  // true
  console.log(args.__proto__ === Array.prototype);
}

// 1 2 [3, 4, 5]
func(1, 2, 3, 4, 5);
```

```
// 可以利用 rest 参数获取回调函数需要几个参数
function func(fn) {
  fn(1, 2);
}

// 2
func((...args) => console.log(args.length));
```

形参默认值：

当未传入参数，或者传入 undefined 时，就使用默认值：

```
function func1(a = 5) {
  console.log(a);
}

// 5
func1();

// 默认参数可以放在除了 rest 的任何位置，但最好往后靠，才比较明确 -----------------------------
function func2(a, b, c = 3) {
  console.log(a, b, c);
}

function func3(a, b = 2, c) {
  console.log(a, b, c);
}

// 1 2 3
func2(1, 2);

// 1 2 undefined
func3(1, 2);

// 默认值也可以是一个表达式 ------------------------------------------------------------
function double(n) {
  return n * 2;
}

// 正常使用，只有在未传入参数或传入 undefined 时，表达式才会执行
function func4(a, b = double(a)) {
  console.log(a, b);
}

/*形成了暂时性死区，就类似于下面代码，无法再 b 声明前使用 b 
 * let a = double(b);
   let b;
 */
function func5(a = double(b), b) {
  console.log(a, b);
}

// 1 2
func4(1);

// 1 undefined ，传入了非 undefined 参数，double(b) 未执行
func5(1);

// err
try {
  func5();
} catch {
  console.log("err");
}
```

```
// 引用类型作为默认值
function func(str, options = {}) {
  const defaultOptions = {};
  options = { ...defaultOptions, ...options };
}
```

函数的 length 的设计是为了获取函数至少需要的参数数量，所以会忽略 rest 参数和默认值参数，只获取第一个默认值参数前面的参数数量：

```
function func(a, b = 1, ...args) {}

// 1
console.log(func.length);
```

ES5 的 arguments 使用很不方便，尽量用 rest 参数替代：

- 外部不知道 argument 需要使用剩余参数

- argument 保存了所有参数，需要分割；arguments 是伪数组

另外 arguments 也有设计上的问题，在修改刑参时会同步修改 arguments ，之所以没有修复这个 bug ，是因为考虑到老项目的兼容问题，所以退出了严格模式，有了 ES6 新语法后，使用这些函数新语法就说明是新项目了，就不用使用严格模式：

```
// 非严格模式下，修改形参会同步影响到 arguments ，这是非常不合理的
function func1(a) {
  // "use strict";

  a = 5;

  // 5
  console.log(arguments[0]);
}

// 但只要用了默认值或 rest 参数。在非严格模式下也会恢复正常
function func2(a, b = 5) {
  a = 5;

  // 1
  console.log(arguments[0]);
}

func1(1);
func2(1);
```

ES8 新特性，函数可以喝数组、对象一样，最后面加一个逗号而不报错了：

```
function func(a, b, ) {}
func(1, 2, );
```

（2）箭头函数

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

* 没有 arguments，因为 rest 参数是更好的替代

* 由于设计初衷是为了消除二义性，所以箭头函数不能作为构造函数，不能 new、没有原型、没有自己的 this ，使用 this 其实就是在作用域链中找到的

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

（3）标签模板

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

ES11 新特性，globalThis

始终指向全局环境（浏览器是 window，node 是 global）：

```
console.log(globalThis);
```

（3）Object 新的 api

string、Array 可以正常使用；Set，Map 可以使用，但结果为空：

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
```

ES10 新特性，Object.fromEntries\(\) ，用二维数组创建一个对象：

```
const obj = Object.fromEntries([
  ["a", 1],
  ["b", 2],
]);

console.log(obj);
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

（4）实现私有属性

ES6 的访问器使用 \_name 在命名上区分私有属性，但约束力不强；用 Symbol key 实现私有属性和也有办法访问。 

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

## 1 JS 执行机制、浏览器渲染

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

因此就需要异步，当 JS 执行时，若遇到异步任务，就会把异步的回调函数包装成任务（浏览器源码中任务是一个结构体），入队到消息队列中等同步任务执行完再执行，实现永不阻塞。

遇到定时器会交给计时线程进行计时，遇到事件会交给交互线程进行监听。

JS 阻塞渲染的例子：

渲染任务是异步的，由于 JS 在同步阶段执行太久，因此阻塞了异步的渲染任务：

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

JS 异步任务分类：

* 微任务：对应微队列，处理 Promise 的回调函数，优先级最高，甚至比页面渲染还高

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

### 1.2 渲染帧

渲染任务的优先级比微任务低，但和宏任务的优先级不好比较，不同浏览器的处理不同，有的比宏任务高，有的在宏任务中间适合的时间段渲染，因此执行顺序不好判断。

浏览器帧数为 60 帧，及约 16.67 ms 为 1 帧，

（1）API

虽然 CSS 动画已经很强大，但一些情况下还是需要 JS 做动画，此时不能使用定时器 setInterval 定时 16.67 ms 。因为浏览器会受到机器配置、卡顿等各种原因导致浏览器分配的渲染帧并不平均，就会导致空帧（小于 16.67 ms ，多个渲染帧没有做任何动画）和跳帧（大于 16.67 ms ，一个渲染帧做了多次动画，只保留了最后一个动画），

HTML5 新特性提供了两个渲染帧相关的 API 。注意只有渲染任务开始了，才会有渲染帧，及也是异步的，顺序在微任务后面：

* requestAnimationFrame ：简称 raf，每次渲染帧开始之前毁掉

* requestIdleCallback ：渲染帧结束后回调，兼容性比 raf 差一点

```
<!DOCTYPE html>
<html lang="en">
  <body>
    <div>123</div>
  </body>

  <script>
    function delay(ms) {
      const now = new Date().getTime();
      while (new Date().getTime() - now < ms) {}
    }

    // 输出 0 1 2 3 4 5
    console.log(0);

    requestIdleCallback((idle) => {
      console.log(4);
    });

    requestIdleCallback((idle) => {
      console.log(5);
    });

    requestAnimationFrame(() => {
      console.log(2);
    });

    requestAnimationFrame(() => {
      console.log(3);
    });

    Promise.resolve().then(() => {
      delay(3000);
      console.log(1);
    });

    //

    // 递归实现类似 setInterval 的效果，时间间隔不一定是 16.67 ms
    // let frameCnt = 0;
    // function run(maxCnt) {
    //   if (frameCnt > maxCnt) return;
    //   requestAnimationFrame(() => {
    //     console.log(`即将开始第 ${frameCnt++} 帧`);
    //     run(maxCnt);
    //   });
    // }
    // run(60);

    // 取消 raf
    // cancelAnimationFrame(raf);
  </script>
</html>
```

（2）封装动画函数

有些动画是必须使用 JS 的，如修改元素的内容。

动画的本质就是数值的变化，因此无论是 JS 还是 CSS 动画，都只能以数值变化作为动画的基础。

下面虽然使用了 raf 和 transform ，但是 JS 修改了样式，就会修改 DOM 树、且 raf 终究是工作在渲染主线程中，还是会有阻塞渲染的风险：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      .container {
        width: 500px;
        height: 200px;
        border: 1px solid #000;
      }
      .box {
        top: -1000px;
        width: 20px;
        height: 20px;
        border: 1px solid #000;
        border-radius: 10px;
        background-color: #000;
        line-height: 20px;
        text-align: center;
        font-size: 10px;
      }
    </style>
  </head>

  <body>
    <div>
      <button class="btn1">start</button>
      <span class="price">9999</span>
    </div>

    <div>
      <button class="btn2">start</button>
      <div class="container">
        <div class="box"></div>
      </div>
    </div>
  </body>

  <script>
    // 柯里化
    function currv(fn, ...preArgs) {
      return (...args) => {
        const totalArgs = [...preArgs, ...args];

        // 如果参数足够 fn 使用，就调用 fn
        if (totalArgs.length >= fn.length) return fn.apply(this, totalArgs);
        // 否则继续 currv
        else return currv.call(this, fn, ...totalArgs);
      };
    }

    // 内置的变化曲线
    const defaultTimeMethods = {
      // 匀速运动
      default(duration, from, to) {
        const speed = (to - from) / duration;

        return currv(function (speed, time) {
          return speed * time;
        }, speed);
      },
    };

    // 动画 ----------------------------------------------------------------------------
    function animation(duration, from, to, onProerese, timeMethods) {
      if (!Array.isArray(from)) from = [from];
      if (!Array.isArray(to)) to = [to];
      if (!Array.isArray(timeMethods)) timeMethods = [timeMethods];

      const startTime = Date.now();
      const that = this;

      // 变化曲线
      const methods = from.map((f, i) => {
        if (typeof timeMethods[i] === "function") return timeMethods[i];
        else {
          return (
            defaultTimeMethods[timeMethods[i]]?.(duration, f, to[i]) ||
            defaultTimeMethods["default"](duration, f, to[i])
          );
        }
      });

      // 开始动画
      function _run() {
        requestAnimationFrame(function () {
          const now = Date.now();
          if (now - startTime >= duration) {
            onProerese && onProerese.call(that, ...to);
            return;
          }

          onProerese &&
            onProerese.call(
              that,
              ...methods.map((getValue, index) => {
                return from[index] + getValue.call(that, now - startTime);
              })
            );

          _run();
        });
      }

      _run();
    }
    // -------------------------------------------------------------------------------

    const btn1 = document.querySelector(".btn1");
    const price = document.querySelector(".price");

    btn1.addEventListener("click", function () {
      const from = Number(price.textContent);

      animation(3000, from, 99, function (to) {
        price.textContent = Math.round(to);
      });
    });

    const btn2 = document.querySelector(".btn2");
    const container = document.querySelector(".container");
    const box = document.querySelector(".box");

    const duration = 10000;
    box.textContent = Number.parseInt(duration / 1000);

    btn2.addEventListener("click", function () {
      const boxRect = box.getBoundingClientRect();
      const containerRect = container.getBoundingClientRect();

      const toX = containerRect.width - boxRect.width;
      const toY = containerRect.height - boxRect.height;

      const seconds = duration / 1000;
      const acc = (2 * toY) / (seconds * seconds);

      // 水平匀速运动，垂直加速运动
      animation(
        duration,
        [0, 0, duration],
        [toX, toY, 0],

        function (x, y, remainTime) {
          x = Number.parseInt(x);
          y = Number.parseInt(y);

          remainTime = (remainTime / 1000).toFixed(1);
          box.textContent = remainTime;

          box.style.transform = `translate(${x}px, ${y}px)`;
        },

        [
          "default",
          function (time) {
            const seconds = time / 1000;
            return (acc * seconds * seconds) / 2;
          },
          "default",
        ]
      );
    });
  </script>
</html>
```

（3）分片任务、分时函数

渲染任务可能有时候在 16.67 ms 内就完成了，剩余的时间可以利用起来，只要这一次渲染帧渲染时间 \+ 剩余时间不超过 16.67 ms 就不影响流畅度。

封装一个分时函数，如一个耗时很长的任务，可以分片，在剩余时间内执行这些分片：

```
<!DOCTYPE html>
<html lang="en">
  <style>
    #box {
      position: relative;
      margin-top: 100px;
      width: 100px;
      height: 100px;
      border: 1px solid #000;
      border-radius: 50px;
      background-color: red;
    }

    @keyframes move_rule {
      from {
        left: 0;
      }
      to {
        left: 200px;
      }
    }
    #box {
      animation: move_rule 1s alternate infinite ease-in-out;
    }
  </style>
  <body>
    <button id="btn1">执行长任务 (requestIdleCallback)</button>
    <button id="btn2">执行长任务 (requestAnimationFrame)</button>
    <div id="box"></div>
  </body>
  <script>
    const datas = new Array(1000000);
    // const datas = 1000000;

    function performChunk(datas, consumer, chunkSplitor, hasTime) {
      if (typeof datas === "number" && !Number.isNaN(datas)) {
        datas = new Array(datas);
      } else if (!Array.isArray(datas) || !datas.length) datas = [];

      if (typeof consumer !== "function" || !consumer) {
        consumer = () => {};
      }

      if (typeof hasTime !== "function" || !hasTime) {
        // 这里的剩余时间设置 > 0ms ，实际情况需要根据任务的执行情况适当增大剩余时间
        hasTime = (remain) => remain > 0;
      }

      if (typeof chunkSplitor !== "function" || !chunkSplitor) {
        /**
         * 如果在一个渲染帧中，渲染任务在 16.67 ms 内完成了，就没必要马上到下一个渲染帧，
           可以利用剩余空闲时间执行分片任务
         * 之所以用 while 是因为想在下一次渲染帧前，尽量利用空闲时间执执行分片任务，当然
           也可以用 if ，只不过用 if 只能在这段时间内执行一个分片了
         * 如果分片的任务执行超过了空闲时间，那还是会有卡顿的，不过这是分片没分好的问题了
         */
        chunkSplitor = (datas, startIndex) => {
          let nowIndex = startIndex;

          requestIdleCallback((idle) => {
            while (hasTime(idle.timeRemaining())) {
              if (nowIndex >= datas.length) return;
              consumer(datas[nowIndex++]);
            }

            // console.log("下一个渲染帧");
            chunkSplitor(datas, nowIndex);
          });
        };
      }

      chunkSplitor(datas, 0);
    }

    const btn1 = document.querySelector("#btn1");
    btn1.addEventListener("click", function () {
      performChunk(datas, (nowData) => {
        console.log(nowData);
      });
    });

    // 也可以用 raf 实现，兼容性好 一点 -----------------------------------------------
    const btn2 = document.querySelector("#btn2");

    const consumer = (nowData) => {
      console.log(nowData);
    };

    const hasTime = (remain) => remain < 16.6;

    const chunkSplitor = (
      datas,
      startIndex,
      startTime = new Date().getTime()
    ) => {
      let nowIndex = startIndex;

      requestAnimationFrame(() => {
        while (hasTime(new Date().getTime() - startTime)) {
          if (nowIndex >= datas.length) return;
          consumer(datas[nowIndex++]);
        }

        // console.log("下一个渲染帧");
        chunkSplitor(datas, nowIndex, new Date().getTime());
      });
    };

    btn2.addEventListener("click", function () {
      performChunk(datas, consumer, chunkSplitor, hasTime);
    });
  </script>
</html>
```

分片任务如果环境不支持这两个 API ，就使用 web worker，再不支持只能用定时器了，但是定时器无法准确在两个渲染帧之间执行任务，就会由卡顿，但至少比直接同步执行好。

### 1.3 Web Worker

HTML5 新特性，开启一个新县城

### 1.4 浏览器渲染原理

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

生成 DOM 树（DOM Object Model）和 SOM 树（CSS Object Model），都是对象，方便后续处理，同时让 JS 有操作 HTML 、CSS 的能力。

当 JS 修改 DOM\.style 事，就会修改 DOM 树，即便是 JS 修改 transform 。

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

* 隐藏的节点没有几何信息，不会出现在布局树中

* 伪元素是 CSS 产生的，不会出现在 DOM 树中，但会出现在布局树中

* 内容只能在行盒中，行盒、块盒不能在同一级，若出现了这些情况，布局树中会用匿名行盒、匿名快盒填充，这些匿名盒子是不会渲染的

当 css 修改几何信息时，引起 reflow ，重新布局 。

```
// 可以获取部分布局树的信息
console.log(body.clientWidth);
```

分层：渲染主线程使用一条复杂的规则进行分层，好处是在将来某一层改变时仅会处理该层，提升性能，但分层不会太多，因为会加大内存消耗，具体分几层由浏览器决定：

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

当 css 修改非几何信息时，引起 repaint ，重新生成绘制指令。

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

reflow 、repaint 都会产生一个异步的渲染任务入队到消息队列，执行这个异步任务才会真正修改样式，修改完后进行重新渲染，进入 raf ：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      .box {
        font-size: 10px;
        transition: all 3s;
      }
    </style>
  </head>

  <body>
    <div>
      <button id="btn1">回流、重绘 1</button>
      <button id="btn2">强制回流、重绘 2</button>
    </div>
  </body>

  <script>
    var btn1 = document.querySelector("#btn1");
    var btn2 = document.querySelector("#btn2");

    function addBox() {
      const box = document.createElement("p");
      box.textContent = "123";
      box.className = "box";

      // 新增了元素，该元素有文字撑开大小，开始 reflow
      document.body.appendChild(box);

      return box;
    }

    // 浏览器为了提高性能，会把相邻的样式修改作为同一个渲染任务，防止多次不必要的 reflow 、repaint
    btn1.addEventListener("click", function () {
      // 效果：transition 无效，原因是 addBox 和修改字体大小都异步 reflow ，只保留了最后一次字体大小修改，因此等价于创建 box 时  font-size 就是 50px
      const box = addBox();

      // reflow
      box.style.fontSize = "30px";
      box.style.fontSize = "40px";
      box.style.fontSize = "50px";

      // repaint ，同理
      // box.style.backgroundColor = "#f00";
      // box.style.backgroundColor = "#0f0";
      // box.style.backgroundColor = "#000";
    });

    /**强制 revlow 、repaint
     * 只要访问呢了几何信息，就会强制 reflow ，同步得到修改后的样式，，但渲染还是要等异步
     * 只要访问了非几何信息的样式，就会强制 repaint，同步得到新的样式，但渲染还是要等异步
     */
    btn2.addEventListener("click", function () {
      /** 效果：transition 生效
       * addBox 后，读取了几何信息。强制同步 reflow ，，得到了 font-size 为 10px
       * 后续的三次字体大小修改中间没有强制 reflow ，只保留了 font-size 为 50px 的修改，有了 10px 到 50px 的变化，因此 transition 生效了
       */
      const box = addBox();

      // 强制 reflow
      box.offsetWidth;

      // reflow
      box.style.fontSize = "30px";
      box.style.fontSize = "40px";
      box.style.fontSize = "50px";

      // 强制 repaint ，同理
      // getComputedStyle(box).backgroundClip;
      // box.style.backgroundColor = "#f00";
      // box.style.backgroundColor = "#0f0";
      // box.style.backgroundColor = "#000";

      // 更好的方式是使用 raf ，效率高
      // requestAnimationFrame(() => {
      // box.style.fontSize = "50px";
      // box.style.backgroundColor = "#000";
      // });
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

### 1.5 作用域

（1）作用域、预编译

三种作用域：

* 全局作用域

* 局部作用域，即函数内部

* 块级作用域，if 、for 等内部，let 、const 具有块级作用域，而 var 没有。

预编译，也叫与解析，JS 运行分为预编译和编译运行两部分。在预编译阶段，会有变量提升和函数提升，作用是吧 var 声明和函数声明的代码放到当前作用域的最前面：

* var 只提升声明，不提升赋值；let、const 也会提升，只不过在声明之前是暂时性死区：
  
  ```
  // undefined 10
  console.log(a);
  var a = 10;
  console.log(a);
  
  // err
  try {
    console.log(b);
  } catch {
    console.log("err\n");
  }
  let b = 10;
  
  // 10 ，由于 var 没有块级作用域，所以 var 当前处于全局作用域
  for (var i = 0; i < 10; i++) {}
  console.log(i);
  
  // 0
  let j = 0;
  for (let j = 0; j < 10; j++) {}
  console.log(j, "\n");
  
  // err ，因为 funcVar 提升的位置是它的当前作用域，也就是局部作用域
  try {
    console.log(funcVar);
  } catch {
    console.log("err");
  }
  
  // undefined 10
  function func() {
    console.log(funcVar);
    var funcVar = 10;
    console.log(funcVar);
  }
  func();
  ```

* 函数也只提升声明，只有具名函数会提升，连 var 定义的匿名函数都不会提升：
  
  ```
  // 1
  func();
  function func() {
    console.log(1);
  }
  
  // err
  try {
    notNameFunc();
  } catch {
    console.log("err\n");
  }
  var notNameFunc = function () {};
  
  //  2，内部函数也会提升到当前作用域最前面
  function f() {
    func();
    function func() {
      console.log(2);
    }
  }
  f();
  ```

注意事项：

* 浏览器全局 this 为 window ，node 全局 this 为 \{\} ；浏览器 globalThis 为 window ，node 中 globalThis 为 node 全局对象：
  
  ```
  console.log(this, globalThis);
  ```

* 全局作用域中，具名函数和 var 声明的变量、var 声明的匿名函数，在浏览器中会加到 window 中（let、const 不会），node 则不会加到 \{\} 和 node 全局对象中：
  
  ```
  var a = 1;
  let b = 2;
  const c = 3;
  
  function func1() {}
  var func2 = function () {};
  let func3 = function () {};
  const func4 = function () {};
  
  // 1 undefined unfined func1 func2 undefined unfined
  try {
    // 浏览器环境
    console.log(
      window.a,
      window.b,
      window.c,
      window.func1,
      window.func2,
      window.func3,
      window.func4
    );
  } catch {
    // {}、undefined ，node 环境
    console.log(
      this,
      globalThis.a,
      globalThis.b,
      globalThis.c,
      globalThis.func1,
      globalThis.func2,
      globalThis.func3,
      globalThis.func4
    );
  }
  ```

* 若声明变量时没有使用 var 、let 、const ，此时必须赋值，否则报错；浏览器会吧变量放到 window 中，node 会放到 globalThis 中。
  
  严格模式下，这种情况浏览器和 node 都会直接报错：
  
  ```
  // 下面的情况等价于 window.xxx = value 或 globalThis.xxx = value
  
  // err ，必须赋值
  try {
    a;
  } catch {
    console.log("err");
  }
  
  a = 1;
  func = function () {};
  
  function func1() {
    b = 2;
  }
  func1();
  
  // func1 必须运行，b 才会加到 window、globalThis 中
  // 1 2 func ，当然调用时 window、globalThis 可以省略
  try {
    console.log(window.a, window.b, window.func);
  } catch {
    console.log(globalThis.a, globalThis.b, globalThis.func);
  }
  ```

* ES6 有了 let、const 后，就不要在使用 var ，var 有很多缺陷：
  
  ```
  // 重复用 var 声明不报错
  var a = 1;
  var a = 2;
  // 2
  console.log(a);
  
  // 用立即执行函数生成局部作用域，解决 var 没有块级作用域问题
  var i = 0;
  (function () {
    for (var i = 0; i < 10; i++) {}
  })();
  // 0
  console.log(i);
  ```

（2）作用域链

类似原型链，用于查找变量，先从自己作用域开始，直到全局，找不到就是 undefined 。规则：

- 内部可以访问外部变量，反之不行；访问的是最近一级作用域的变量

- 只与定义函数时有关，与调用无关：
  
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
* 由于 JS 是解释型语言，所以下面代码不会报错：
  
  ```
  function func() {
    console.log(a);
  }
  
  const a = 1;
  
  // 1
  func();
  ```

### 1.6 垃圾回收机制

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

（1）原型

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

// true ，字面量对象本是 new Object()
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

ES6 新增的有关圆形的 API：

```
// 创建 obj ，并指定原型，属性描述符默认都为 false （new Object() 默认为 true）
function Person() {
  this.a = 1;
}

const obj = Object.create(new Person(), {
  b: {
    value: 2,
  },
});

// 1 2
console.log(obj.__proto__.a, obj.b, "\n");

// { a: 1 } ，返回 obj 的原型 ----------------------------------------------------------
console.log(Object.getPrototypeOf(obj), "\n");

// 给 obj 设置新的原型 -----------------------------------------------------------------
Object.setPrototypeOf(obj, { c: 3 });

// { c: 3 }
console.log(obj.__proto__), "\n";
```

（2）原型链

原形对象和函数都是对象，也有圆形，就形成了原型链，Object new 出原型对象，Function new 出函数：

* Object\.prototype 是最终的原型，没有构造者，网上就是 null

* Function 的 \_\_proto\_\_ 和 prototype 是同一个原型对象

```
// Array 、Set 等也是一样的
function Person() {}
const obj = new Person();

const A = obj.__proto__;
const B = A.__proto__;
const C = Person.__proto__;

// 都是 true
console.log(
  A === Person.prototype,
  B === Object.prototype,
  C === Object.__proto__ && C === Function.prototype,

  // 特殊情况
  B.__proto__ === null,
  Function.__proto__ === Function.prototype
);
```

```
obj ---> __proto__ ---> A ---> __proto__ ---> B ---> null
 |\                    /|\                   /| 
   \                  /   \                 / |
    \                /     \               /  |
     \              /       \             /   |
     new        prototype   new     rototype  |
      \           /          \          /     |
       \         /            \        /      |
        \       /              \      /       |
        \      /                \    /        |
         Person <---- new ----> Object        |
             \         |          /  |        |
              \     Function     /   |        |
               \       |        /    |        |
               \       |       /     |        |
                \  prototype  /      |        |
                 \\    |     /       |        |
                  \    &    /        |        |
                   \   |   /         |        |
                   __proto__         |        |
                     \ | /           |        |
                      \|/            |        |
                       C <--- new ---|        |
                       |                      |
                       |----- __proto__ ------|
```

obj instanceof Func ，判断 obj 的原型链上是否能找到 Func\.prototype ：

```
// true true
console.log({} instanceof Object, [] instanceof Array);

// true ture
console.log(Number instanceof Object, Function instanceof Object);

// 都是 false ，无法判断基本数据类型
console.log(
  123 instanceof Number,
  "" instanceof String,
  undefined instanceof Number,
  null instanceof Number
);
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

（3）ES5 继承

```
/**为了保证原型链的完整性
 * ，实例对象的 __proto__ 和类的 prototype 要保证是一个对象
 * 子类、父类的 prototype 不能是同一个对象
 */

function Person(name) {
  this.name = name || "person";
  this.arr = [1];
  this.run = () => {};
}
Person.prototype.msg = "person_prototype_msg";

/**原型链继承 -------------------------------------------------------------------------
 * 优点：可继承父类原型
 * 缺点：无法多继承；new 时无法给父构造函数传参
        一些操作如数组 push 会先 get ，自身没有就会到原型上再 set ，所有实例对象也会修改
 */
function SonA(age) {
  this.age = age || 18;
}
SonA.prototype = new Person();

const a1 = new SonA(18);
const a2 = new SonA(18);

// { age: 18 } person person_prototype_msg
console.log(a1, a1.name, a1.msg);

a1.name = "xxx";
// xxx person ，由于自己身上没有 name 就直接 set ，而不会去 __proto__
console.log(a1.name, a2.name);

a1.arr.push(2);
// [1, 2] [1, 2] ，先 get arr ，所以会去到 __proto__ 再 set ，所有实例对象就都修改了
console.log(a1.arr, a2.arr, "\n");

/**构造函数继承 --------------------------------------------------------------------
 * 优点：new 时可以给父构造函数传参；可用搓个 call 实现多继承
 * 无法继承父类原型
 */
function SonB(name, age) {
  Person.call(this, name);
  this.age = age || 18;
}

const b = new SonB("myName", 18);

// { name: "myName", age: 18, arr: [1], run } undefined
console.log(b, b.msg, "\n");

/**组合继承 --------------------------------------------------------------------
 * 原型链继承 + 构造函数继承
 * 优点：可多继承，可以给父构造函数传参、可继承圆形，由于实例对象已经有父类的属性方法，所以使用这些属性方法不会去原型找，继承的原型就不会被共享
 * 缺点：需要执行两次父构造函数，Child.prototype 的属性方法实际上是不需要的
 */
function SonC(name, age) {
  Person.call(this, name);
  this.age = age || 18;
}
SonC.prototype = new Person();

const c = new SonC('myName"', 18);

// { name: "myName", age: 18, arr: [1], run } person_prototype_msg
console.log(c, c.msg);

/**寄生组合继承 --------------------------------------------------------------------
 * 组合继承的基础上，吧 Child.prototype 变成空对象
 */
SonC.prototype = Object.create(Person.prototype);

// create 的简化实现
function func(prototype) {
  function F() {}
  F.prototype = prototype;
  return new F();
}

// SonC.prototype = func(Person.prototype);
```

### 2.2 this

函数中的 this 只有在调用时，才确定 this 的指向。

（1） this 的 4 种绑定规则

优先级：new \> 显示 \> 隐式 \> 默认 。

默认绑定规则：

- 全局作用域中，浏览器 this 指向 window ，node 的 this 指向 \{\} ：
  
  ```
  // 浏览器中 window window
  // node 中 {} 和 node 全局对象
  console.log(this, globalThis);
  ```

- 函数不通过对象直接调用，而是独立调用，浏览器中指向 window ，node 中指向 node 全局对象，这个 node 全局对象可以用 globalThis 获取。
  
  本质就是独立调用的函数是 window.func\(\) 或 globalThis.func\(\) 调用的，所以才指向它们：
  
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
  
  在严格模式下，这种情况会指向 undefined ，但是不影响全局作用域的 this 和任何作用域的 globalThis ，webpack 、vite 默认都是严格模式。
  
  原因是严格模式下，认为独立调用时就是一个普通函数，自然没有 this ：
  
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
* 圆形链上的函数，若 obj 是通过隐式的使用隐式圆形属性调用的，指向 obj ；若是主动加上 \_\_proto\_\_ 调用的，指向圆形对象：
  
  ```
  const obj = {};
  const op = obj.__proto__;
  
  obj.__proto__.func = function () {
    console.log(this === obj, this === obj.__proto__);
  };
  
  // true false
  obj.func();
  
  // false true
  obj.__proto__.func();
  
  // false true
  op.func();
  ```

显示绑定规则：

* call ，apply ，bind 显示修改 this ：
  
  ```
  
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

* 箭头函数没有 this ，也不适用 this 的四种绑定规则，使用 this 其实就是在作用域链中找：
  
  ```
  const obj = {
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
  
  // 浏览器：window ，node：{} ，在作用域链中找到 this 在全局作用域
  obj.func1();
  // 浏览器：window ，node：{} ，箭头函数使用 this 规则无效
  obj.func1.call(obj);
  
  // 浏览器和 node 都是 obj，在作用域链中找到 this 在 func2 局部作用域中，而 func2 是 obj 调用的
  obj.func2()();
  
  // 浏览器：window ，node：node 全局对象，在作用域链中找到 this 在 func2 局部作用域中，而 func2 隐式丢失，相当于独立调用
  const f = obj.func2;
  f()();
  
  // 浏览器：window ，node：{} ，在作用域链中找到 this 在全局作用域
  obj.func3()();
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
  
  // 浏览器：window ，node：{} ，在作用域链中找到 this 在全局作用域
  api(() => {
    console.log(this);
  });
  ```

（2）实例

注意，浏览器 window 和 node 全局对象有一些内置属性；

```
// ""
console.log(window.name);
```

```
// 浏览器：window.name = 3 ，node：{}.name = 3 ，node 全局对象.name = 4
// 非严格模式
globalThis.name = 4;
this.name = 3;

const obj1 = {
  name: "1",

  fn1() {
    console.log(this.name);
  },

  fn2: () => console.log(this.name),

  fn3() {
    return function () {
      console.log(this.name);
    };
  },

  fn4() {
    return () => console.log(this.name);
  },
};

const obj2 = {
  name: "2",
};

// 浏览器：1 2 3 3 ，node：1 2 3 3
obj1.fn1();
obj1.fn1.call(obj2);
obj1.fn2();
obj1.fn2.call(obj2);
console.log("\n");

// 浏览器： 3 2 3 ，node：4 2 4
obj1.fn3()();
obj1.fn3().call(obj2);
obj1.fn3.call(obj2)();
console.log("\n");

// 浏览器：1 1 2 ，node：1 1 2
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
  出错了;
  console.log("出现异常后，try 中后续代码不会执行，直接进入 catch");

  // 也可以手动抛出异常
  // throw "myErr";
} catch (err) {
  console.log("err\n");
}

// ES9 新特性，catch 可以不 用传入参数
try {
} catch {}

// ES9 新特性，新增 finally ，无论是否异常都会执行，且就算 return 、breaqk 、continue 后也会执行
function test(value) {
  try {
    if (value) throw "err";
    console.log("ok");
    return "res";
  } catch {
    console.log("err");
  } finally {
    console.log("finally");
  }
}

// ok finally res
console.log(test(false), "\n");
// err finally undefined
console.log(test(true), "\n");

// finally
for (let i = 0; i < 10; i++) {
  try {
    break;
    // continue;
  } finally {
    console.log("finally");
  }
}
```

### 2.5 数据代理、劫持

（1）ES5 的 Object\.defineProperty

给属性设置访问器、属性描述符：

```
const obj = {};
let data = 0;

Object.defineProperty(obj, "a", {
  // 访问器 ---------------------------------------------------------
  get() {
    // 设置 getter 后，obj.a 类似于 get(obj, "a")
    return data;
  },

  set(newValue) {
    // 设置 setter 后，obj.a = newValue 类似于 set(obj, "a", newValue)
    // 不可以 obj.a = newValue ，因为会无线递归 setter
    data = newValue;
  },

  // 设置属性的 value
  // 有了 getter 就不能这样设置 value
  // value: 123,

  // 三个属性描述符 ----------------------------------------------------
  // 构造函数、字面量(即 new Object())、class 创建的对象，这三个属性描述符默认都是 true ，而 defineProperty 默认为 false

  // 默认 false ，是否可修改，包括上面是否能以 value 形式修改
  // 设置了 setter 后，就不能吧 writable: 设为 true ，因为修改已经交给 setter 处理了
  // writable: true,

  // 默认 false ，是否可枚举，如 for...in ，Object.keys() 等是否能获得这个属性
  enumerable: true,

  /**默认 false ，false 后：
   * 属性不可删除
   * 无访问器时无法添加访问器，若已有访问器也无法去掉
   * 三个属性描述符不能再修改
   */
  configurable: true,
});

obj.a = 123;
// 123
console.log(obj.a);

// ES8 新特性，获取属性描述符信息 -----------------------------------------------------
console.log(Object.getOwnPropertyDescriptor(obj, "a"));

// 实现数据代理 -----------------------------------------------------------------
function defineReactive(target, key) {
  if (!(target instanceof Object)) return;

  // 闭包数据
  let value = target[key];

  Object.defineProperty(target, key, {
    get: () => value,
    set: (newValue) => (value = newValue),
  });
}

const o = { a: 1 };
defineReactive(o, "a");
o.a = 123;
// 123
console.log(o.a);
```

ES6 新特性，访问器语法糖，可以在对象、构造函数、class 中直接设置访问器：

```
const obj = {
  a: 1,

  get b() {
    return this._b;
  },

  set b(newValue) {
    this._b = newValue;
  },

  // 可以设置多个访问器
  // get c() {},
  // set c(newValue) {},
};

obj.b = 2;

// 2
console.log(obj.b);
// { a: 1m b: [Getter/Setter], _b: 2}
console.log(obj);

// "a" "b" "_b"
console.log(Object.keys(obj), "\n");

// 实现数据代理 -----------------------------------------------------------------------
function ref(value) {
  // value 是闭包数据

  return {
    get value() {
      return value;
    },

    set value(newValue) {
      value = newValue;
    },
  };
}

const a = ref(123);

a.value = 456;
console.log(a.value);
```

（2）Proxy

ES6 新特性，Proxy 可以实现代理一个对象。

Proxy 可以拦截所有对象的基本操作，如对象属性的读取、修改、添加、删除，判断属性是否存在；数组由于也是对象，所以数组元素的操作也可以拦截。

原理是对象的操作最终都会执行浏览器的内部方法，如 .get() 、.set() 等。

```
const obj = { a: 1 };
// const obj = [1, 2];

const p = new Proxy(obj, {
  // 拦截基本操作 get()
  get(target, key, receiver) {
    // return target[key];
    return Reflect.get(target, key, receiver);
  },

  // 拦截基本操作 .hasProperty ，如使用 in
  has(target, key) {
    // return key in target;
    return Reflect.has(target, key);
  },

  // 拦截基本操作 .ownKeys，如使用 for...in
  ownKeys(target) {
    return Reflect.ownKeys(target);
  },

  // 拦截基本操作 .set ，如修改、添加
  set(target, key, newValue, receiver) {
    // try {
    //   target[key] = newValue;
    //   return true;
    // } catch {
    //   return false;
    // }

    return Reflect.set(target, key, newValue, receiver);
  },

  deleteProperty(target, key) {
    // try {
    //   delete target[key];
    //   return true;
    // } catch {
    //   return false;
    // }

    return Reflect.deleteProperty(target, key);
  },
});
```

Proxy 中的拦截器建议使用 Reflect ：

- Proxy 的 set 、deleteProperty 这些拦截修改、删除操作的拦截器，需要 return 布尔值表示是否操作成功，通常需要 try\.\.\.catch ，而 Reflect 内部就有 try\.\.\.catch ，也 return 布尔值，使用起来更简洁

- Object 的内部方法是 private 的，开发者无法使用：
  
  ```
  // undefined
  console.log(Object.get);
  ```
  
  而 Reflect 就有这些方法，在一些特殊情况下必须使用这些基本方法才能实现功能，如 .get() 可以修改 this 指向：

```
const obj = {
  a: 1,
  b: 2,
  get c() {
    return this.a + this.b;
  },
};

const proxy1 = new Proxy(obj, {
  get(target, key, _) {
    console.log("get");
    return target[key];
  },
});

// 只输出一个 get ，正常应该输出三个，因为 c 用到了 a 和 b
console.log(proxy1.c, "\n");

const proxy2 = new Proxy(obj, {
  // receiver 即 proxy2 本身
  get(target, key, receiver) {
    console.log("get");

    // 最后一个参数修改 this 为 proxy2
    return Reflect.get(target, key, receiver);
  },
});

// 三个 get，原因是 proxy1 在 get c 事 this 指向原始对象，而 proxy2 吧 this 指向 receiver ，也就是 proxy2
console.log(proxy2.c);
```

（3）冻结

Object\.freeze 冻结一个对象、冻结后无法修改、增加、删除属性、无法设置属性描述符、无法更换圆形、但是冻结对象自身可以赋值成另一个引用：

```
// 修改被冻结的对象的属性大多数情况下都会 thrrow error --------------------------------
let obj = { a: 1 };
const sameObj = Object.freeze(obj);

// true
console.log(obj === sameObj);

// err
try {
  obj.a = 2;
} catch {
  console.log("err");
}

// err
try {
  Object.defineProperty(obj, "a", { value: 3 });
} catch {
  console.log("err");
}

// 1 true
console.log(obj.a, Object.isFrozen(obj));

// 冻结对象自身可以重新赋值成另一个引用
obj = { a: 1 };
obj.a = 11;
// 11 false
console.log(obj.a, Object.isFrozen(obj), "\n");

// 浅冻结 --------------------------------------------------------------------------
// freeze 只能冻结自己，如果冻结对象的属性是一个引用类型，是不会深度冻结的
const obj1 = { a: 1, deepObj: { b: 2 } };
Object.freeze(obj1);
obj1.deepObj.b = 3;

// 3 false
console.log(obj1.deepObj.b, Object.isFrozen(obj1.deepObj), "\n");

// freeze 前设置了 setter ------------------------------------------------------
//  只要 set 的目标不是冻结对象的属性，就可以正常 set
let b = 2;
const obj2 = {
  a: 1,
  get b() {
    return b;
  },
  set b(newValue) {
    b = newValue;
  },
};

function defineReactive(o, k) {
  let value = o[k];

  Object.defineProperty(o, k, {
    get() {
      return value;
    },

    set(newValue) {
      value = newValue;
    },
  });
}

defineReactive(obj2, "a");
Object.freeze(obj2);

obj2.a = 11;
obj2.b = 22;

// 11 true
console.log(obj2.a, Object.isFrozen(obj2));

// 22 true
console.log(obj2.b, Object.isFrozen(obj2));

// Proxy 则不行，因为 set 的毁掉已经到了调用 set() 的阶段了
const obj3 = { c: 3 };
const p = new Proxy(obj3, {
  get: (t, k) => t[k],
  set(t, k, v) {
    t[k] = v;
    return true;
  },
});
Object.freeze(p);

// err
try {
  p.c = 33;
} catch {
  console.log("err");
}
```

简单实现 freeze ：

```
function myFreeze(obj) {
  if (!(obj instanceof Object)) return obj;

  // 只处理自己的属性，不涉及到圆形
  const keys = [
    ...Object.getOwnPropertyNames(obj),
    ...Object.getOwnPropertySymbols(obj),
  ];

  for (const key of keys) {
    Object.defineProperty(obj, key, {
      // 设置不能修改 value
      writable: false,

      // 设置不能删除属性、不能设置属性描述符
      configurable: false,
    });
  }

  // 设置不能新增属性、不能更换圆形
  Object.preventExtensions(obj);

  // 用 Object.defineProperty 给所有属性设置 configureble 为 false ，并调用 Object.preventExtensions()
  // Object.seal(obj);

  return obj;
}
```

## 3 函数式编程

（1）纯函数

相同的输入都能得到同样的结果，且无副作用的函数就是纯函数：

* 如 Array 的 push 会修改原数组，那么每次得到的输出就不一样，就不是纯函数

* 无副作用，即不会修改外部作用域的变量，没有定时器、修改 DOM 等异步操作

```
// 纯函数
function func1(a, b) {
  return a + b;
}

// 非纯函数
let a = 0;
function func2() {
  // 返回值依赖外部变量，而外部变量是不确定的，可能会被修改
  return a + 1;
}
function func3(arr) {
  // 修改了外部作用域的 arr ，产生了副作用
  arr[0] = 1;
}

function func3() {
  // 副作用
  setTimeout(() => {});
}（2）高阶函数
```

形参或返回值是 function 的函数，就是高阶函数，其中作为形参的函数称为回调函数

```
function func1(fn) {
  fn();
}

function func2() {
  return function () {};
}

function func3(fn) {
  fn();
  return function () {};
}

// 纯粹的函数式编程中没有对象，但 JS 混合了多种编程思想，所以 JS 中这样也算高阶函数
function func4(options) {
  options.fn();
}
```

（3）惰性函数

当函数中某些逻辑只需要执行一次时，就可以写成惰性函数，提高性能：

```
function nextTick(callback) {
  if (Promise) {
    nextTick = function (callback) {
      Promise.resolve().then(callback);
    };
  } else {
    nextTick = function (callback) {
      setTimeout(() => callback);
    };
  }

  // 执行修改后的函数
  nextTick(callback);
}
```

```
// 另一种方式，在项目最开始就判断，缺点是会增加初始化时间
const nextTick = ((callback) => {
  if (Promise) return (callback) => Promise.resolve().then(callback);
  else return (callback) => setTimeout(() => callback);
})();
```

（4）闭包

编译原理的概念，只要函数形成了嵌套，且内部函数使用了外部函数的资源，那么内部函数就变成了闭包，即使外部函数被垃圾回收了，闭包使用的资源依然存在，这是非常合理的，因为内部函数还在使用就不应该被垃圾回收。

直到闭包函数也被垃圾回收了，闭包的资源才会被垃圾回收：

- 优点：缓存资源；也可以在外面按照自己的规则访问函数的私有资源

- 缺点：不会被垃圾回收，使用不慎就会加大内存消耗，低版本 IE 则会内存泄漏，解决方法是把不适用的闭包设为 null

```
const func1 = (...args) => {
  let num = 0;

  // 内部函数使用了形参和 num ，这两个变量都不会被垃圾回收
  return () => console.log(args[0]++, num++);
};

const func2 = (...args) => {
  let num = 0;

  // z这样也是函数嵌套，这种方式通常用来实现私有资源，只给外部提供 get 方法访问资源
  return {
    getNum: () => console.log(args[0]++, num++),
  };
};

const func3 = () => {
  const a = 1;

  // 这也是函数嵌套，也形成了闭包，只不过内部函数没有被外部使用，已经被垃圾回收了
  const func = () => a;
};

let f1 = func1(0),
  f2 = func2(0);

// 0 0 0 0
f1();
f2.getNum();

// 1 1 1 1 ，
f1();
f2.getNum();

// 手动回收闭包
f1 = null;
f2.getNum = null;
```

（5）面向切面编程

将函数的核心功能和非核心功能分开，在适当的时候可以给有核心功能的函数添加一些非核心功能；

实现方式一：

```
function AOP(fn, before, after) {
  return function (...args) {
    before?.call(this, ...args);
    fn?.call(this, ...args);
    after?.call(this, ...args);
    ``;
  };
}

// -----------------------------------------------------------------------------
const obj = {
  func1() {
    console.log("func1");
  },

  func2(a, b) {
    console.log("func2", a, b);
  },
};

const func1 = AOP(
  obj.func1,
  function (...args) {
    console.log("func1 before", this === obj, ...args);
  },
  function (...args) {
    console.log("func1 after", this === obj, ...args);
  }
);

// func1 before true
// func1
// func1 after true
func1.call(obj, "\n");

const func2 = AOP(
  obj.func2,
  function (...args) {
    console.log("func2 before", this === obj, ...args);
  },
  function (...args) {
    console.log("func2 after", this === obj, ...args);
  }
);

// func2 before true 1 2
// func2 1 2
// func2 after true 1 2
func2.call(obj, 1, 2);
```

实现方式二：

```
Function.prototype.before = function (beforeFn) {
  const fn = this;

  return function (...args) {
    beforeFn.call(this, ...args);
    fn.call(this, ...args);
  };
};

Function.prototype.after = function (afterFn) {
  const fn = this;

  return function (...args) {
    fn.call(this, ...args);
    afterFn.call(this, ...args);
  };
};

// -------------------------------------------------------------------------------
const obj = {
  test(...args) {
    console.log("test", this === obj, ...args);
  },
};

const fullTest = obj.test
  .before(function (...args) {
    console.log("before", this === obj, ...args);
  })
  .after(function (...args) {
    console.log("after", this === obj, ...args);
  });

// before true 1 2
// test true 1 2
// after true 1 2
fullTest.call(obj, 1, 2);
```

（6）柯里化

处理一个原函数，固化其某些参数（即闭包这些参数），并生成一个新函数，新函数只需要传入剩下的参数即可。柯里化通尝将多参函数转化为参数更少的函数或单参函数。

如果一个函数需要被使用多次，且其中某些参数是不变的，就可以使用柯里化，后续只需要使用新生成的函数，传入剩下的参数即可：

```
function currv(fn, ...preArgs) {
  return (...args) => {
    const totalArgs = [...preArgs, ...args];

    // 如果参数足够 fn 使用，就调用 fn
    if (totalArgs.length >= fn.length) return fn.apply(this, totalArgs);
    // 否则继续 currv
    else return currv.call(this, fn, ...totalArgs);
  };
}

const sum1 = currv(function (a, b) {
  return a + b;
}, 10);

// 30
console.log(sum1(20));
// 40
console.log(sum1(30), "\n");

const sum2 = currv(function (a, b, c) {
  return a + b + c;
}, 10);

// 50
console.log(sum2(20, 20));
// 80
console.log(sum2(30, 40), "\n");

const sum3 = sum2(20);
// 70 ，10+20+40
console.log(sum3(40));
```

（7）函数管道

将多个单参函数组合成一个新的单参函数，上一个单参函数的输出会作为下一个单参函数的输入。若传入的不是单参函数，则需要 currv ：

```
function pipe(...fns) {
  return (value) => fns.reduce((pre, fn) => fn.call(this, pre), value);
}

const obj = {
  num1: 2,
  num2: 1,

  double(n) {
    return n * this.num1;
  },

  add(n) {
    return n + this.num2;
  },
};

const func = pipe.call(obj, obj.double, obj.add);

// 5 ，2*2+1
console.log(func(2));
```

（8）防抖、节流

有对应的库：

```
npm install --save lodash
```

防抖、节流的作用都是为了限制执行次数，减少函数不必要的执行，优化性能，区别是：

- 防抖：在一段时间内只允许执行一次，若在此时间段内再次触发，则重新计时

- 节流：在一段时间内只允许执行一次，可以在开头或结尾执行
* 有些场景防抖、节流都不合适，如上拉加载更多，这时候就用一个 flag 判断是否执行即可。

```
npm install --save @types/node
```

```
function debunce<T extends any[]>(
  func: (...args: T) => any,
  delay: number = 1000
) {
  let timer: number | null = null;

  return function (...args: T): void {
    clearTimeout(Number(timer));
    timer = setTimeout(() => func.call(this, ...args), delay);
  };
}

function throttle<T extends any[]>(
  func: (...args: T) => any,
  delay: number = 1000,
  immediate: boolean = true
) {
  let timer: number | null = null;

  return function (...args: T): void {
    if (!timer) {
      immediate && func.call(this, ...args);

      timer = setTimeout(() => {
        timer = nul;
        immediate || func.call(this, ...args);
      }, delay);
    }
  };
}
```

## 4 常用 JS 操作

（1）判断数据类型

```
// typeof ，有设计缺陷，null 、Array 、Set 、Map 、WeakSet、WeakMap 都直接判断成 "object" ，而 function 则判断为 "function"

// "number" "string" "boolean" "undefined" "symbol" "bigint"
console.log(
  typeof 1,
  typeof "'",
  typeof true,
  typeof undefined,
  typeof Symbol(),
  typeof 1n
);

// 都是 "object"
console.log(
  typeof null,
  typeof [],
  typeof new Set(),
  typeof new Map(),
  typeof new WeakSet(),
  typeof new WeakMap()
);

class Person {}
// 都是 "function"
console.log(typeof (() => {}), typeof Person);
```

```
// true
console.log(Array.isArray([]));
```

```
// toString ，所有类型都能正常判断

// "[object Undefined]" , 都是这种格式
console.log(Object.prototype.toString.call(undefined));

// 自定义输出结果
const obj = { a: 1 };
obj[Symbol.toStringTag] = "MyType";
// "[object MyType]"
console.log(Object.prototype.toString.call(obj));

// 默认情况下 Symbol.toStringTag 是 undefined ，但 async 函数就有设置
// AsyncFunction
console.log(async function () {}[Symbol.toStringTag]);
```

```
// 判断是否是 Proxy

// 方法一，拦截 new ，可以做复杂的逻辑，如判断是第几层 Proxy --------------------------------------
Proxy = new Proxy(Proxy, {
  construct(target, argsList) {
    const result = new target(...argsList);

    const originType = Object.prototype.toString
      .call(result)
      .slice(1, -1)
      .split(" ")[1];

    result[Symbol.toStringTag] = `Proxy.${originType}`;

    return result;
  },
});

const p = new Proxy([1, 2, 3], {});
const pp = new Proxy(p, {});

// [object Proxy.Proxy.Array] 表示代理两次的 Array
console.log(Object.prototype.toString.call(p));

// 方法二 ---------------------------------------------------------------------------------
// const p = new Proxy(
//   { a: 1 },
//   {
//     get(target, key) {
//       if (key === Symbol.toStringTag) return "Proxy";
//       return target[key];
//     },
//   }
// );
// "[object proxy]"
// console.log(Object.prototype.toString.call(p));
```

（2）数据类型转换

类型转换规则：

- 原始值转原始值：
  
  ```
  /**规则
   * 转为 number：
     - boolean: true -> 1 ，false -> 0
     - string: "" " " "\n" -> 0，"3.14" -> 3.14 ，" 2 " -> 2 ，"1 2" -> NaN ，
               "2n" -> NaN ，"true" -> NaN ，"2n" -> NaN
     - undefined -> NaN ，null -> 0
     - Symbol：无法转换，强制类型转换都不行
     - BigInt：无法隐式，但强制可以
  
   * 转为 string：
     - 3.14 -> "3.14" ，true -> "true" ，NaN -> "NaN" ，null -> "null" ，
       undefined -> "undefined"
     - Symbol：无法隐式转换，但是强制类型转换可以
     - BigInt：2n -> "2"
  
   * 转为 boolean
     - 非空值意义时转为 true：如 1 ，"asdf"" ，包括 Symbol
     - 具有空值、否定意义时转为 false ，如 0 ，"" ，" " ，NaN ，null ，undefined
   */
  ```

- 引用类型转原始值：
  
  ```
  /**规则
   * 按照 Symbol.toPrimitive > valueOf > toString 的优先级调用这些函数，其中 valueOf 和 toString 在原型链上有
   * 上一步转为原始值后， 再进行原始值到原始值的类型转换
   * 特殊情况：转为 boolean 直接全部转为 true ，包括空数组、空对象
   */
  // 自定义这 3 个函数 ----------------------------------------------------------------
  var obj1 = {
    [Symbol.toPrimitive]: function () {
      // 必须 re turn 原始值 ，否则在运算时直接报错，不再去找 valueOf 和 toString
      return 123;
    },
  };
  
  var obj2 = {
    valueOf: function () {
      // 自定义 valueOf 不必须 return 原始值，若 return 引用，运算时也不会报错，会直接忽略这次执行结果，这是历史遗留问题
      // 因此 return 引用时，忽略，会再去调用 toString
      return 456;
    },
  };
  
  var obj3 = {
    toString: function () {
      // 自定义 toString 必须 return 原始值，否则运算时直接报错
      return 789;
    },
  };
  
  // 124 457 790
  console.log(obj1 + 1, obj2 + 1, obj3 + 1, "\n");
  
  // 默认的 valueOf 和 toString ---------------------------------------------------------
  // valueOf 都是返回自己，所以一般默认的 valueOf 都无效，会再去找 toString
  var objValueOf = Object.prototype.valueOf,
    arrValueOf = Array.prototype.valueOf,
    funcValueOf = Function.prototype.valueOf,
    setValueOf = Set.prototype.valueOf,
    mapValueOf = WeakSet.prototype.valueOf,
    weakSetValueOf = Map.prototype.valueOf,
    weakMapValueOf = WeakMap.prototype.valueOf;
  
  var obj = {},
    arr = [],
    func = function () {},
    set = new Set(),
    map = new Map(),
    weakSet = new WeakSet(),
    weakMap = new WeakMap();
  
  // 都是 true
  console.log(
    objValueOf.call(obj) === obj,
    arrValueOf.call(arr) === arr,
    funcValueOf.call(func) === func,
    setValueOf.call(set) === set,
    mapValueOf.call(map) === map,
    weakSetValueOf.call(weakSet) === weakSet,
    weakMapValueOf.call(weakMap) === weakMap,
    "\n"
  );
  
  // toString ，Array 和 Function 重写了 toString
  var objToString = Object.prototype.toString,
    arrToString = Array.prototype.toString,
    funcToString = Function.prototype.toString,
    setToString = Set.prototype.toString,
    mapToString = Map.prototype.toString,
    weakSetToString = WeakSet.prototype.toString,
    weakMapToString = WeakMap.prototype.toString;
  
  // "[object Array]"
  console.log(objToString.call({}), "\n");
  
  // “【object Set】” 等,没有重写 toString ，都是 Object.prototype 的 toString
  console.log(setToString.call(new Set([])));
  console.log(mapToString.call(new Map([])));
  console.log(weakSetToString.call(new WeakSet([])));
  console.log(weakMapToString.call(new WeakMap([])), "\n");
  
  // "" "0" "1" "1,2"
  console.log(arrToString.call([]));
  console.log(arrToString.call([0]));
  console.log(arrToString.call([2]));
  console.log(arrToString.call([1, 2]));
  
  // "(a) => a" ，即整个函数的内容
  // ES10 新特性，会保留空格和换行符
  console.log(
    funcToString.call((a) => a),
    "\n"
  );
  ```

表达式运算中的隐式类型转换：

任何运算的双方都必须是原始值，否则将会隐式类型转换，运算结果也是一个原始值：

```
/**算术运算 ---------------------------------------------------------------------------
 * 除了 string 外的原始值运算，全部转为 number ：
 * - NaN 和任何 number 运算都为 NaN ，包括 NaN 自己
 * 有 string 和引用类型参与的运算：
   - 加法运算：全部转为 string ，引用类型转为原始值后再转为 string ，进行字符串拼接
   - 其他运算：全部转为 number ，引用类型转为原始值后再转为 number ，进行算数运算
 */
// NaN NaN
console.log(NaN + 1, NaN + NaN);

// NaN 1
console.log(undefined + 1, null + 1);

// "21" "2n" "3.14" "true" "undefined" "null" "NaN"
console.log(
  2n + "1",
  "2n" + "1",
  3.14 + "",
  true + "",
  undefined + "",
  null + "",
  NaN + ""
);

// "1" "21" "1,21" "[object Object]123" "() => {}123" "null" "NaN"
console.log(
  [] + 1,
  [2] + 1,
  [1, 2] + 1,
  {} + 123,
  (() => {}) + 123,
  [] + null,
  [] + NaN
);

// NaN -1 -1 1 1.14 1 NaN 1
console.log(
  "2n" - 1,
  "" - 1,
  " " - 1,
  " 2 " - 1,
  "3.14" - "2",
  "2" / 2,
  "1" - NaN,
  "1" - null
);

// -1 2 NaN NaN NaN 123,5
console.log(
  [] - 1,
  [2] - 0,
  [1, 1] - 1,
  {} - 1,
  (() => {}) - 1,
  "123" + [4, 5]
);

// err ，Symbol 和 BigInt 无法隐式转为 number ，Symbol 无法隐式转为 string
try {
  // console.log(Symbol() + 1, "\n");
  // console.log(0n + 1, "\n");
  console.log(Symbol() + "", "\n");
} catch (err) {
  console.log("err\n");
}

// 逻辑运算，全部转为 boolean ------------------------------------------------------------
if (
  1 &&
  -1 &&
  1.0 &&
  1n &&
  "false" &&
  Symbol() &&
  [] &&
  {} &&
  (() => {}) &&
  !(0 || -0 || 0.0 || 0n || NaN || "" || undefined || null) &&
  !![]
) {
  console.log("boolean\n");
}

/** 比较运算 ----------------------------------------------------------------------------
 * 类型相同时，直接比较 value （相同引用类型则比较地址），不会类型转换；类型不同时，全部转为 number ：
   - 引用类型先转为原始值，再转为 number
 * 特殊情况：
   - NaN 和任何数值比较都为 false ， 包括和 NaN 自己
   - undefined == null 不转为 number ，直接返回 true
 */
// true
console.log("true" == "true");

// false true
console.log(NaN == NaN, undefined == null);

// false false false
console.log("false" == false, "false" == true, undefined == NaN);

// true false
console.log([0] == false, [0] == [0], "\n");
```

包装类中的隐式类型转换：

```
const str1 = "asdf";

// str 生成一个临时包装类 String 对象，吧 "a" 设置为 “1”
str1.a = "1";

// undefined ，str 和临时生成的 String 包装类不是同一个
console.log(str1.a);

// 同理，生成了临时包装类 String 对象，而且 String 也部署了 iterator
const [s1, s2] = str1;
// "a" "s"
console.log(s1, s2);

const str2 = new String("asdf");
str2.a = "1";
// 1
console.log(str2.a);
```

强制类型转换：

都不改变原始数据：

```
var n = 1;
var str = "3.14";

// "1" "1"
console.log(n.toString(), String(n));

// 3 3.14 3.14
console.log(Number.parseInt(str), Number.parseFloat(str), Number(str));

// 都是 false
console.log(Boolean(null), Boolean(undefined), Boolean(NaN), Boolean(""));

// 都是 true
console.log(Boolean([]), Boolean({}));

// "Symbol()" "Symbol(123)" true ， SYMbol 只能强制转换为 string 、boolean
console.log(String(Symbol()), String(Symbol("123")), Boolean(Symbol()));

// err
try {
  console.log(Number(Symbol()));
} catch (err) {
  console.log("err");
}
```

（3）数组、对象判空

```
const arr = [], obj = {};

// 推荐做法
// true ，数组判空
console.log(Array.isArray(arr) && arr.length === 0);
// true true ，对象判空
console.log(Object.keys(obj).length === 0);
console.log(Object.getOwnPropertyNames(obj).length === 0);

// ------------------------------------------------------------------------
// false false ， 错误做法，因为这是判断两个引用的地址
console.log(arr === [], obj === {});

// true ture ，不推荐，性能差，且 stringify() 本身有些限制，如 undefined 会被忽略
console.log(JSON.stringify(arr) === "[]", JSON.stringify(obj) === "{}");

// 不推荐，for...in 会便利到圆形上的自定义属性，for...of 虽然不会到圆形，但也只能用于 arr ，且麻烦
let arrIsEmpty = true, objIsEmpty = true;
arr.__proto__.a = 123;
obj.__proto__.a = 123;
for (const i of arr) arrIsEmpty = false;
for (const i in obj) objIsEmpty = false;
// true false
console.log(arrIsEmpty, objIsEmpty);
```

（4）判断对象中是否有某属性

以下方法都无法判断 Symbol key 属性：

```
const obj = {
  a: undefined,
};

obj.__proto__.b = undefined;
obj.__proto__.c = 123;

// 判断是否连圆形上都不存在 -----------------------------------------------------------
// 都是 undefined ，原型链上都找不到，但是无法确定是否 a 和 b 本身就是 undefined
console.log(obj.a, obj.b, obj["a"], obj["b"]);
// 123 123
console.log(obj.c, obj["c"]);

// 都是 true ，在原型链上找，同时可以确定是否值本身就是 undefined
console.log("a" in obj, "b" in obj, "c" in obj);

// 只判断对象本身是否有该属性，不去原型链上找 -----------------------------------------------
// true false ，可以判断值本身就是 undefined 的属性
console.log(obj.hasOwnProperty("a"), obj.hasOwnProperty("b"));

// 同上，只是变成获取所有属性，包括非枚举属性
console.log(Object.getOwnPropertyNames(obj));

// ES13 新增 hasOwn() ，等价于 hasOwnProperty
// 写法更简单，且不在 Object 圆形上，就不容易被修改调或意外的不可用
console.log(Object.prototype.hasOwnProperty.call(obj, "a"));
console.log(Object.hasOwn(obj, ""));
```

判断对象中是否有 Symbol key 属性：

常规方法无法看到 Object 中的 Symbol key （Map 可以）：

```
const obj = {
  a: "a",
  [Symbol("b")]: "b",
};

const map = new Map();
map.set("a", "a");
map.set(Symbol("b"), "b");

// 无法看到 Objct 中的 Symbol key
for (const i in obj) console.log(i);
console.log(Object.keys(obj));
console.log(Object.getOwnPropertyNames(obj));
console.log(JSON.stringify(obj), "\n");

// Map 就可以
for (const i of map) console.log(i);
console.log("\n");

// 只能看到 Symbol key
console.log(Object.getOwnPropertySymbols(obj), "\n");

// 全部非圆形属性都能看到
console.log(obj, map);
```

获取所有非圆形 key，包括 Symbol key ：

```
const obj = {
  a: 1,
  [Symbol("b")]: 2,
};
obj.__proto__.c = 3;

// ["a", Symbol(b)]
console.log(Reflect.ownKeys(obj));
```

# 七、JS 编码技巧

（1）条件分支优化

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

（2）变量相关

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

（3）函数

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
