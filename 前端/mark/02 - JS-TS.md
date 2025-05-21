# 一、JS

（1）ES5

JS 是面向对象的脚本语言，组成：

* ECMAScript（ES，JS的语法）

* DOM（页面文档对象模型，对标签进行操作实现动态效果）。

* BOM（浏览器对象模型，操作浏览器窗口）

JS 书写位置：

* 行内式，标签内书写 事件=””

* 内嵌式，<script>JS代码</script>

* 外部式，<script src=”xxx.js”>此处不能写代码</script>，

（2）ES6

这里说的 ES6 语法，包含 ES6 之后各个新版本的特性（ES6 - ES13）。

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

## 1 基本

注释、输入输出

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

### 1.1 变量

作用域：

- 全局作用域

- 局部作用域，即函数内部

- 块级作用域，if 、for 等内部，let 、const 具有块级作用域，而 var 没有。

var 以及 ES6 的 let 、const ：

```
/**预编译（预解析）会有提升，提升到当前作用域最前面 --------------------------------------------
 * var 和保存在变量的匿名函数的声明会提升，但不提升值，所以使用不报错且值为 undefined
 * 具名函数也会提升且保留值
 * let 、cosnt 、class 等也会提升，但是在声明之前是暂时性死区（TDZ），不允许使用
 */
// undefined
console.log(a);

// err
try {
  console.log(b, c);
} catch {
  console.log("err");
}

// hasNameFunc undefined
console.log(hasNameFunc, notNameFunc);

// err ，只会提升到当前作用域
try {
  console.log(testVar);
} catch {
  console.log("err");
}

function test() {
  // undefined func
  console.log(testVar, func, "\n");

  var testVar = "test";
  function func() {}
}
test();

/**声明 -----------------------------------------------------------------------------------
 * let 变量、const 敞亮，const 由于不能修改所以必须初始化
 * 未初始化的 var 、let 为 undefined
 * const 声明的引用类型自己的引用无法修改，但是堆内存的数据可以修改
 */
var a = 1;
let b = 2;
const c = 3;

// 标识符命名与 C 语言唯一不同是还可以用 $
var a_1$;

// 具名函数、匿名函数
function hasNameFunc() {}
var notNameFunc = function () {};

/**重复声明 ---------------------------------------------------------------------------------
 * var 设计缺陷，重复声明不报错
 * 用了 let 、const 就不能重复声明，即使是 let 声明之前的 var
 */
// ok
var a = 1;

// err
// let b = 22;
// let a = 11;
// var b = 222;

// 块级作用域 -----------------------------------------------------------------------------
for (var i = 0; i < 10; i++);
for (let j = 0; j < 10; j++);

// 10 err ，var 设计缺陷，没有快级作用域，而 let 、const 都有
console.log(i);
// console.log(j);
```

全局污染：

```
<!DOCTYPE html>
<html lang="en">
  <body></body>

  <script>
    /**全局污染
     * 全局作用域中的 var 和具名函数会加入到 window 中，let 、cosnt 则不会
     * node 则不会加到 node 全局对象中
     */
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
      // undefined ，node 环境
      console.log(
        globalThis.a,
        globalThis.b,
        globalThis.c,
        globalThis.func1,
        globalThis.func2,
        globalThis.func3,
        globalThis.func4
      );
    }
  </script>

  <script>
    // 但是 var 、let 、const 、函数都会跨 script 标签
    console.log(a, b, c, func1, func2);
  </script>

  <script>
    /**若变量未使用 var 、let 、cosnt 声明
     * 此时必须赋值，否则 err
     * 不管哪一个作用域，浏览器都会放到 window ，node 都会放到 node 全局对象
     * 严格模式下，不允许这种情况，直接 err
     */
    // 下面的情况等价于 window.xxx = value 或 globalThis.xxx = value
    aa = 1;
    ff2 = function () {};

    function ff1() {
      bb = 2;
    }
    // 必须运行 ff1 ， bb 才会加入到 window 和 node 全局对象
    ff1();

    // 1 2 func ，当然调用时 globalThis 可以省略
    console.log(globalThis.aa, globalThis.bb, globalThis.ff2);
  </script>
</html>
```

### 1.2 数据类型

（1）ES5 类型

数据类型只有 8 种，7 个基本类型 \+ 1 个引用类型；

* 基本类型：number、string、boolean、null、undefined、以及 ES6 以后的 Symbol、BigInt

* 引用类型：Object、数组、函数等都是对象

null 和 undefined 区别：

* null 是关键字，而 undefined 不是

* null 通常表示空引用，而 undefined 表示未定义、空值

* null 转 number 为 0 ，undefined 转 number 为 NaN

* null 用 typeof 判断为 object ，而 undefined 判断正常

```
// 声明 -----------------------------------------------------------------------------
var t1 = 123;
var t2 = "asdf";
var t3 = true;
var t4 = null;
var t5 = undefined;
var t6_obj = { a: 1 };
var t6_arr = [123, "asdf", true];

// JS 是弱类型语言，赋值可以使其他数据类型
t1 = true;

// PS -----------------------------------------------------------------------------------
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

// ES6 新特性，模板字符串，可以保留换行符，可以嵌入表达式 ----------------------------------------
var nnn = 12;
var s1 = `
  ${nnn}${1 + 2}4
`;
// 1234 且保留换行符
console.log(s1);

// ES12 新特性，数字分隔符，解决长数字的可读性问题 -----------------------------------------
var a1 = 12_34;
var a2 = 123_4;
// 都是 true
console.log(1234 === a1, a1 === a2);
```

循环引用，自己引用了自己：

```
var obj1 = { a: 1 };
var obj2 = { a: 2, myself: obj1 };
```

（2）ES6 基本类型

ES6 新特性，基本类型 Symbol：

- 值唯一，且不可见，可用来解决命名冲突问题

- 无法算术运算，比较运算只能用 == \!= === \!== 比较、可以逻辑运算

```
// 声明 ---------------------------------------------------------------------------------
const s1 = Symbol();
const s2 = Symbol();

// 这个字符串并不是值，只是一个说明，用于注释，字符串相同的 Symbol 也是不同的
const s3 = Symbol("asdf");
const s4 = Symbol("asdf");

// 用函数对象创建，当传入的字符串相同时，两个 Symbol 就相同
const s5 = Symbol.for();
const s6 = Symbol.for("123");
const s7 = Symbol.for("123");

// false "Symbol()" ，值唯一，且不可见
console.log(s1 === s2, s1);
// false "Symbol(asdf)"
console.log(s3 === s4, s3);
// false false true
console.log(s5 === s6, s5 === s7, s6 === s7, "\n");

// "asdf" ， ES10 新特性，可以查看 Symbol 的描述字符串
console.log(s3.description, "\n");

// 应用 -----------------------------------------------------------------------------------
const obj = {
  // 自定义独一无二的 key
  [Symbol("asdf")]: 123,

  // 内置 Symbol ，一些 JS 底层会调用这些 key
  [Symbol.hasInstance]: 123,
};

console.log(obj);
```

ES11 新特性，基本类型 BigInt，用于存放更大的数字，不过只能是整数：

```
// 声明，只能是整数
const a = 123n;
const b = BigInt(456);
const c = BigInt("789");

// err 2n 1 <BigInt 只能和 BigInt 、string 算术运算
try {
  console.log(1n + 1);
} catch {
  console.log("err");
}
console.log(1n + 1n, 1n + "", "\n");

// 1 ，强制转为 number 时需要注意边界
console.log(Number(1n), "\n");

// true false true false
console.log(2n == 2, 2n === 2, 2n > 1, 2n > 2);
```

### 1.3 类型判断、转换

（1）判断数据类型

typeof ，有设计缺陷，null 、Array 、Set 、Map 、WeakSet、WeakMap 等都直接判断为 object ，而函数判断为 function ；

```
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

数组判断：

```
// true ，用底层 C++ 判断数据结果是否符合数组的特征，所以和原型无关
// 伪数组本质是对象所以判断为 false
console.log(Array.isArray([]));
```

toString  ，所有类型都能正常判断：

```
// "[object Arguments]"，伪数组也能判断
(function () {
  console.log(Object.prototype.toString.call(arguments));
})();

// ES6 新特性，自定义输出结果
const obj = { a: 1 };
obj[Symbol.toStringTag] = "MyType";
// "[object MyType]"
console.log(Object.prototype.toString.call(obj));
```

Symbol\.toStringTag 基本上 ES6 后的新对象都有部署；

```
// ES5 这些就能判断了，所以没部署 Symbol.toStringTag ----------------------------------------
const num = (123)[Symbol.toStringTag];
const arr = [][Symbol.toStringTag];
const obj = {}[Symbol.toStringTag];
const func = (() => {})[Symbol.toStringTag];
const args = (function () {
  return arguments[Symbol.toStringTag];
})();

// undefined
console.log(num, arr, obj, func, args, "\n");

// ES6 新增的大部分都有 Symbol.toStringTag ----------------------------------------------------
const sym = Symbol()[Symbol.toStringTag];
const bigInt = 123n[Symbol.toStringTag];

function* genFunc() {}
const gen = genFunc[Symbol.toStringTag];
const genIte = genFunc()[Symbol.toStringTag];
const promise = new Promise(() => {})[Symbol.toStringTag];
const asyncFunc = async function () {}[Symbol.toStringTag];

const set = new Set()[Symbol.toStringTag];
const weakMap = new WeakMap()[Symbol.toStringTag];
const reflect = Reflect[Symbol.toStringTag];

// "Symbol" "BigInt"
// "GeneratorFuncFunction" "Genertor" "Promise" "AsyncFunction"
// "Set" "WeakMap" "Reflect"
console.log(
  sym,
  bigInt,
  gen,
  genIte,
  promise,
  asyncFunc,
  set,
  weakMap,
  reflect,
  "\n"
);

// class 、迭代器 、proxy 则没有 -----------------------------------------------------------
class A {}
const proxy = new Proxy({}, {});
const ite = [][Symbol.iterator];

const cls = A[Symbol.toStringTag];
const pro = proxy[Symbol.toStringTag];
const it = ite[Symbol.toStringTag];

// undefined
console.log(cls, pro, it);
// "[object Function]" "[object Objct]" "[object Function]"
console.log(
  Object.prototype.toString.call(A),
  Object.prototype.toString.call(pro),
  Object.prototype.toString.call(ite)
);
```

判断 Proxy ：

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
     - BigInt：需要注意边界问题
  
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
   - NaN 和任何 number 运算都为 NaN ，包括 NaN 自己
   - Symbol 无法算术运算；BigInt 只能和 BigInt、String 算术运算
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

// err ，Symbol 无法算术运算，BigInt 只能和 BigInt、String 算术运算
try {
  // console.log(Symbol() + 1, "\n");
  // console.log(0n + 1, "\n");
  console.log(Symbol() + "", "\n");
} catch (err) {
  console.log("err\n");
}

/** 比较运算 ----------------------------------------------------------------------------
 * 类型相同时，直接比较 value （相同引用类型则比较地址），不会类型转换；类型不同时，全部转为 number ：
   - 引用类型先转为原始值，再转为 number
 * 特殊情况：
   - NaN 和任何数值比较都为 false ， 包括和 NaN 自己
   - undefined == null 不转为 number ，直接返回 true
   - Symbol 只能比较是否相等，与其他值比较都是 false
 */
// true
console.log("true" == "true");

// false true
console.log(NaN == NaN, undefined == null);

// false false false
console.log("false" == false, "false" == true, undefined == NaN);

// true false
console.log([0] == false, [0] == [0], "\n");

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

### 1.4 运算符

（1）ES5

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

其他和 C 一样。

（2）ES6

扩展运算符：

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

其他：

```
// ES7 ，幂运算 **
const a = 2 ** 3;
// 8
console.log(a), "\n";

// ES11 ，可选链运算符 ? ，当从 undefined 中调用时，直接返回 undefined ，而不报错
// ES5 处理这种问题只能先判断是否存在，非常麻烦
let obj, arr, func;
obj?.a;
arr?.[0];
func?.();
// err ，由于可能是 undefined ，所以不能赋值
// obj?.a = 1;

// ES11 ，空值合并运算符 ?? ，类似 || 但限制更大，只有 null、undefined 才会执行后面代码
// 1 2 0 false ""
console.log(null ?? 1, undefined ?? 2);
console.log(0 ?? 3, false ?? 4, "" ?? 5, "\n");

// ES12 ，逻辑赋值运算符，中断结果会赋值给变量
let a1 = true,
  a2 = false,
  a3 = null;
// 1 2 3 1 2 3
console.log((a1 &&= 1));
console.log((a2 ||= 2));
console.log((a3 ??= 3));
console.log(a1, a2, a3);
```

### 1.5 迭代器

ES5 流程控制除了循环多了 for\.\.\.in 、forEach 外，其他与 C 一样。迭代器是 ES6 新特性。

（1）解构赋值

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

// 此时必须传实参，或者设置默认值，因为从 undefined 解构是语法错误
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

（2）for\.\.\.of

具备 iterator 接口的数据类型才可使用 。除了 Object 外都有 iterator 接口。

for\.\.\.of 、forEach 、for\.\.\.in 异同：

- 遍历出的 key 输出结果的类型都是 string

- 除了 Map 用 for\.\.\.of 、forEach 外，其他情况都无法遍历出 Symbol key

- for\.\.\.in 遍历出 key ，for\.\.\.of 和 forEach 遍历出 value
  
  - forEach 还可以传入第二、三个参数，得到 key 和原始引用
  
  - 对于 Map ，for... 遍历 Map 得到 key ，for\.\.\.of 得到 [key, value] 。forEach 则得到 value

- for\.\.\.in 可以遍历出原型链上的自定义属性；for\.\.\.of 、forEach 不可以

- 使用场景：
  
  - Array 、Object 、Set 、Map 均可以用 for\.\.\.in ；遍历 Set 、Map 只能遍历出原型链上的自定义属性，无法遍历自身的属性
  
  - for\.\.\.of 、forEach 无法便利 Object ；Array 、Set 、Map 则可以
  
  - WeakSet 、WeakMap 由于是弱引用所以无法以任何形式遍历
  
  - map\(\) 等方法只有 Array 可以用

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

（3）迭代器

ES6 提供了 iterator 接口，为不同的数据结构提供统一的访问机制，只有 Object 没有 iterator 接口，其他都有，如 Array、伪数组、String、Set、Map 等

数组解构赋值是按顺序解构出来的，因为底层实现使用的迭代器，扩展运算符和 for\.\.\.of 也只有具备 iterator 接口的数据结构才能使用。

一般 iterator 接口是各数据结构的原型对象中的一个方法：

```
[Symbo.iterator] : function(){}
```

原理与使用

迭代器中有一个 next() 方法，作用是返回当一个对象，对象的内容为当前 value 和是否结束，得到这个信息后，移动到下一个元素：

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

（4）自定义遍历数据

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

### 1.6 异常处理

当代码出错时，会报错并终止运行，可以使用异常处理使报错后不终止运行：

```
// ES5 --------------------------------------------------------------------------------------
try {
  出错了;
  console.log("出现异常后，try 中后续代码不会执行，直接进入 catch");

  // 也可以手动抛出异常
  // throw "myErr";
} catch (err) {
  console.log("err");
}

// 无法捕获异步代码的异常
try {
  setTimeout(() => {
    // throw "async err";
  });
} catch (err) {
  console.log(err);
}

// err2 ，嵌套的异常只有出错的那一层会捕获
try {
  try {
    throw 123;
  } catch {
    console.log("err2\n");
  }
} catch (err) {
  console.log("err1");
}

// ES6 --------------------------------------------------------------------------------------
// ES9 新特性，catch 可以不 用传入参数，此时 catch 小括号必须去掉
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

## 2 函数

### 2.1 函数、作用域

（1）基本

函数也是对象，调用函数本质就是执行了这个函数对象的 call 方法，因此由 call 方法的对象就是一个函数。

基本使用：

```
// 具名函数
function func1() {
  // 可以在 function 内部定义 function ，内部函数只能在外部函数内使用
  // 不要在 if 等块级作用域声明块级函数，ECMA 并没有这个标准，不同浏览器的运行逻辑不同
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

是匿名函数，不用调用，会立即执行，只执行一次，内部会形成局部作用域，可以解决 var 没有快级作用域的问题，也可以防止多个 JS 文件的 var 冲突：

```
(function () {
  console.log("123");
})();

// 0
var i = 0;
(function () {
  for (var i = 0; i < 10; i++) {}
})();
console.log(i);
```

（2）作用域链

用于查找变量，先从自己作用域开始，直到全局，找不到就是 undefined 。规则：

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

- 由于 JS 是解释型语言，所以下面代码不会报错：
  
  ```
  function func() {
    console.log(a);
  }
  
  const a = 1;
  
  // 1
  func();
  ```

### 2.2 ES6 函数

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

箭头函数就是解决方案之一（另一个是 class ）。

与普通函数的区别：

- 只能定义匿名函数

- 没有 arguments，因为 rest 参数是更好的替代

- 由于设计初衷是为了消除二义性，所以箭头函数不能作为构造函数，不能 new、没有原型、没有自己的 this ，使用 this 其实就是在作用域链中找到的

```
const func1 = (a, b) => {
  return a + b;
};

// 形参只有一个时，可以省略 () ，函数体只有一条语句时，可以省略 {} ，此时就是 return 这条语句
// 若没有形参，则必须加上 ()
const func2 = a => a * 2;
const func3 = () => 123;

// 上述情况若 return对象，则需要加上 () ，避免语法错误
const func4 = () => ({ a: 1 });
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

### 2.3 函数式编程

（1）纯函数

相同的输入都能得到同样的结果，且无副作用的函数就是纯函数：

- 如 Array 的 push 会修改原数组，那么每次得到的输出就不一样，就不是纯函数

- 无副作用，即不会修改外部作用域的变量，没有定时器、修改 DOM 等异步操作

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

```
// 多参的柯里化不好标注，这里就标注只允许单参的类型

type PreArgs<A extends any[]> = A extends [...infer PA, any]
  ? A | PA | PreArgs<PA>
  : [];

type CurrvReturn<A, R> = A extends []
  ? () => R
  : A extends [infer ARG]
  ? (param: ARG) => R
  : A extends [infer ARG, ...infer REST]
  ? (param: ARG) => CurrvReturn<REST, R>
  : never;

declare function currv<A extends any[], R, PA extends PreArgs<A>>(
  fn: (...args: A) => R,
  ...preArgs: PA
): CurrvReturn<A, R>;
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

- 有些场景防抖、节流都不合适，如上拉加载更多，这时候就用一个 flag 判断是否执行即可。

```
npm install --save @types/node
```

```
// 防抖
function debunce<A extends any[]>(
  func: (...args: A) => any,
  duration: number = 1000
) {
  let timer: NodeJS.Timeout = null;

  return function (...args: A): void {
    clearTimeout(Number(timer));
    timer = setTimeout(() => func.call(this, ...args), duration);
  };
}

// 节流
function throttle<A extends any[]>(
  func: (...args: A) => any,
  duration: number = 1000,
  immediate: boolean = true
) {
  let timer: NodeJS.Timeout = null;

  return function (...args: A): void {
    if (!timer) {
      immediate && func.call(this, ...args);

      timer = setTimeout(() => {
        timer = null;
        immediate || func.call(this, ...args);
      }, duration);
    }
  };
}
```

## 3 对象

### 3.1 Object

（1）基本

```
// 创建 -------------------------------------------------------------------------------
// 构造函数创建，过程：bnew Object() -> 修改 this -> 执行构造函数 -> return this
function Obj(n) {
  this.a = n;

  // 默认返回值
  // return this;
}
const obj1 = new Obj(123);

// 字面量创建，底层会调用 new Object()
const c = 3;
const func2 = () => {};

const obj2 = {
  a: 1,

  // key 的引号可以省略，如果是复杂的 key 则必须加引号
  "b.b.b": 2,

  // 都是匿名函数
  func1: function () {
    console.log("func");
  },

  // ES6 新特性，若 value 是一个变量且和 key 名字相同，可以简写
  c,
  func2,

  // ES6 新特性，函数简写，等价于 func3: function() {}
  func3() {},

  // ES6 新特性，key 可以用 [] 包裹表达式，若 key 不是 string、Symbol ，会隐式转为 string
  [Symbol()]: "sym",
};

// 调用、添加、删除属性 ----------------------------------------------------------------
// 调用
console.log(obj1.a, obj1["a"]);

// undefined ， 调用没有的属性得到 undefined
console.log(obj1.aaa);

// err ，无法从 undefined 中调用任何属性
try {
  console.log(o.a);
} catch {
  console.log("err");
}

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
```

对象的 key 只能是 string 或 Symbol ，如果是其他类型则会转为 string ：

```
const obj = {};
const arr = [];

// 等价于 obj["[object Object]"] = "obj"
obj[{ a: 1 }] = "obj";
// "obj"
console.log(obj["[object Object]"]);

// 等价于 arr["0"] = 123
arr[0] = 123;
// 123
console.log(arr[0]);
```

（2）深拷贝

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

（3）ES6 Object 新 API 

```
const obj = {
  a: 1,
  b: 2,
};

Object.defineProperty(obj, "c", {
  value: 3,
  enumerable: false,
  writable: true,
});

// ES6 --------------------------------------------------------------------------------
// 返回 key 或 value 的数组，会过滤掉非枚举属性
// ["a", "b"] [1, 2] [["a", 1], ["b", 2]]
console.log(Object.keys(obj));
console.log(Object.values(obj));
console.log(Object.entries(obj), "\n");

// 判断两个是否相等，可以判断基本类型，会有严格的比较，如 +0 和 -0 不相等
// true false
console.log(Object.is(obj, obj), "\n");
console.log(Object.is(+0, -0), "\n");

// 合并多个 obj ，会改变原始 obj ，若有相同 key ，后面会覆盖前面，被覆盖的属性必须是可写的
const newObj = Object.assign(obj, { a: 11 }, { c: 3 });
console.log(newObj, obj, "\n");

// ---------------------------------------------------------------------------------
// ES10 新特性，用二维数组创建对象
const obj1 = Object.fromEntries([
  ["a", 1],
  ["b", 2],
]);
console.log(obj1);
```

（3）Reflect 反射

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

（4）对象常用操作

数组、对象判空：

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

判断对象中是否有某属性：

* 以下方法都无法判断 Symbol key 属性：
  
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

* 判断对象中是否有 Symbol key 属性：常规方法无法看到 Object 中的 Symbol key （Map 可以）：
  
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

* 获取所有非圆形 key，包括 Symbol key 和非枚举属性：
  
  ```
  const obj = {
    a: 1,
    [Symbol("b")]: 2,
  };
  
  Object.defineProperty(obj, "c", {
    value: 3,
    enumerable: false,
  });
  
  obj.__proto__.d = 4;
  
  // ["a", Symbol(b), "c"]”
  console.log(Reflect.ownKeys(obj));
  ```

### 3.2 class

解决 JS 函数二义性的另一个方案，实例对象专门由 class 的 constructor 构造。

（1）基本

使用：

```
// err ，class 此时是暂时性死区，无法使用
try {
  console.log(A);
} catch {
  console.log("err");
}

// 声明
class A {
  constructor(a) {
    this.a = a;
    this.b = 2;
  }

  // 放到 A 原型上
  func1() {
    return this;  
  }

  // class 是局部作用域，所以箭头函数 this 为实例对象
  func2 = () => this;

  // ES13 新特性 --------------------------------------------------------------------
  // 在 constructor 外给 this 定义属性
  c = 3;
  [Symbol("d")] = 5;

  // 用 # 定义私有属性、私有方法 ，外部无法使用；私有方法是只读的
  #e = 5;
  #func3 = () => 6;
  getPrivate = () => this.#e + this.#func3();
  hasPrivate = (key) => #e in this;

  // 静态属性、静态方法、只能 class 本身使用，静态方法只能使用静态属性和静态方法
  static f = 7;
  static staticFunc = () => this.f;

  // static private
  static #g = 8;
  static getStaticPrivateFunc = () => A.#g;

  // 静态代码块，可以有多个，编译阶段就执行，只能使用静态属性和静态方法
  static {
    // 局部作用域

    // true ，this 指向类本身
    console.log(this === A, "\n");
  }
}

const obj = new A(1);

// 1 2
console.log(obj.a, obj.b);
// true
console.log(obj.func1() === obj.func2(), "\n");

// ，5+6
console.log(obj.getPrivate());
// 7
console.log(A.staticFunc());
// 8
console.log(A.getStaticPrivateFunc(), "\n");

// true true ，in 只能判断 public  的属性方法，private 的只能类提供 get 方法才行
console.log("a" in obj, obj.hasPrivate("e"));
// true ，判断 static 需要类本身
console.log("f" in A);
```

class 转 ES5 构造函数：

```
class A {
  constructor(name) {
    this.name1 = name;
    this.run2 = function () {};
  }

  name2 = "asdf";
  run3 = function () {};
  run4 = () => {};

  run1() {}
  static staticFunc() {}

  static staticProp = "static";
  static run5 = () => {};
  static {
    console.log("staic block");
  }

  #privateFunc() {}
}

// 转化成 ES5 构造函数 --------------------------------------------------------------
// ES13 的 # 私有属性方法，由于是语法底层实现的，所以自己无法实现，原型上也没有
function B(name) {
  "use strict";
  if (!(this instanceof B)) throw new TypeError("只能 new 调用");

  this.name1 = name;
  this.name2 = "asdf";
  this.run2 = function () {};
  this.run3 = function () {};
  this.run4 = () => {};
}

[
  { target: B.prototype, funcs: [{ key: "run1", value: A.prototype.run1 }] },
  { target: B, funcs: [{ key: "staticFunc", value: A.staticFunc }] },
].forEach((item) => {
  for (var i = 0; i < item.funcs.length; i++) {
    var index = i;

    Object.defineProperty(item.target, item.funcs[i].key, {
      value: function () {
        if (typeof this !== "function" && !(this instanceof B)) {
          throw new TypeError("不能 new 调用");
        }

        item.funcs[index].value.call(this);
      },

      writable: true,
      configurable: true,
      enumerable: false,
    });
  }
});

(function () {
  this.staticProp = "static";
  this.run5 = () => {};

  console.log("static block");
}).call(B);
```

（2）类的继承

```
class A {
  constructor(a) {
    this.a = a;
  }

  fatherFunc() {
    console.log("fatherFunc");
  }
}

// 只能单继承
class B extends A {
  constructor(a, b, c) {
    // 子类中必须有 super() 调用父类的 constructor ，否则 new 时会 err
    super(a);
    this.b = b;
    this.c = c;
  }

  sonFunc() {
    // 调用父类的方法
    super.fatherFunc();
    console.log("sonFunc", "\n");
  }

  // 重写父类方法
  fatherFunc() {
    // 可以使用父类同名方法
    // super.fatherFunc();

    console.log("rewrite fatherFunc");
  }
}

const son = new B(1, 2, 3);

// // 1 2 3
console.log(son.a, son.b, son.c, "\n");

son.sonFunc();
son.fatherFunc();
```

（3）实现私有属性

ES6 的访问器使用 _name 在命名上区分私有属性，但约束力不强；用 Symbol key 实现私有属性和也有办法访问。

ES13 有 \# 可以实现，且是运行时，不过由于是新特性，可能有兼容性问题。

TypeScript 中的 private 只是编译时，编译后的 JS 也没有使用 # ，且就算再 ts 中，也有办法可以使用动态属性绕过检查：

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

### 3.3 原型

原型是一个对象，所以也叫原型对象。任何一个实例对象通过隐式原型属性 \_\_proto\_\_ ，任何一个构造函数通过显示原型属性 prototype ，就能访问到原型，实例对象和它的构造函数指向的是同一个原型对象：

```
function Person(name, age) {
  this.name = name;
  this.age = age;
}

const p = new Person("asdf", 18);

// true 
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

- Object.prototype 是最终的原型，没有构造者，网上就是 null

- Function 的 __proto__ 和 prototype 是同一个原型对象

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

obj instanceof Func ，判断 obj 的原型链上是否能找到 Func.prototype ：

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

### 3.4 this

函数中的 this 只有在调用时，才确定 this 的指向。

ES11 新特性，globalThis ，始终指向全局对象：

```
// 浏览器：window ，node：node 全局对象
console.log(globalThis);
```

（1） this 的 4 种绑定规则

优先级：new > 显示 > 隐式 > 默认 。

默认绑定规则：

- 全局作用域中，浏览器 this 指向 window ，node 的 this 指向 {} ：
  
  ```
  // 浏览器中 window window
  // node 中 {} 和 node 全局对象
  console.log(this, globalThis);
  ```

- 函数不通过对象直接调用，而是独立调用，浏览器中指向 window ，node 中指向 node 全局对象，这个 node 全局对象可以用 globalThis 获取。
  
  本质就是独立调用的函数是 window.func() 或 globalThis.func() 调用的，所以才指向它们：
  
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

- 圆形链上的函数，若 obj 是通过隐式的使用隐式圆形属性调用的，指向 obj ；若是主动加上 __proto__ 调用的，指向圆形对象：
  
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

- call ，apply ，bind 显示修改 this ：
  
  ```
  function func(a, b) {
    console.log(this, a, b);
  }
  
  const obj = { a: 1 };
  
  func.call(obj, 1, 2);
  func.apply(obj, [1, 2]);
  
  const fn = func.bind(obj, 1);
  fn(2);
  
  // 实现 call 、apply 、bind --------------------------------------------------------------
  Function.prototype.myCall = function (ctx, ...args) {
    // 原版 call 中传入的 this 是 undefined 、null 时就用 globalThis
    ctx = ctx ?? globalThis;
  
    // 使用后，若 this 为基本类型则转为包装类对象，引用类型则不变
    ctx = Object(ctx);
  
    // 把函数挂到 ctx 中再调用，this 就指向 ctx 了
    const tempKey = Symbol();
    // 防止在函数调用期间用到这个临时 key
    Object.defineProperty(ctx, tempKey, {
      value: this,
      enumerable: false,
    });
  
    ctx[tempKey](...args);
    delete ctx[tempKey];
  };
  
  Function.prototype.myApply = function (ctx, args) {
    if (
      typeof args !== "object" &&
      typeof args !== "function" &&
      args !== undefined
    ) {
      throw "err";
    }
  
    if (
      [
        "[object Undefined]",
        "[object Null]",
        "[object Set]",
        "[object Map]",
      ].includes(Object.prototype.toString.call(args))
    ) {
      args = [];
      console.log(123);
    } else {
      args = Array.from(args);
    }
  
    this.myCall(ctx, ...args);
  };
  
  Function.prototype.myBind = function (ctx, ...args) {
    const fn = this;
  
    return function (...subArgs) {
      const allArgs = [...args, ...subArgs];
  
      // 原版 bind 是支持 new 这个函数的，且最终 new 的是调用 bind 的函数而不是返回的函数
      if (new.target) return new fn(...allArgs);
      else return fn.myCall(ctx, ...allArgs);
    };
  };
  ```

new 绑定：

- this 指向实例对象：
  
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

- 构造函数默认 return this ，使得接收的变量获得实例对象，若修改了 return ，则会得到 retuirn 的对象，不推荐这么做：
  
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

- 箭头函数没有 this ，也不适用 this 的四种绑定规则，使用 this 其实就是在作用域链中找：
  
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

- API 的回调函数的 this 由内部实现决定，如 Vue 的一般都指向 Vue 实例。但如果回调函数是箭头函数，则不管内部如何实现，this 都只看调用 API 的作用域：
  
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

### 3.5 属性描述符、代理

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

- Proxy 的 set 、deleteProperty 这些拦截修改、删除操作的拦截器，需要 return 布尔值表示是否操作成功，通常需要 try...catch ，而 Reflect 内部就有 try...catch ，也 return 布尔值，使用起来更简洁

- 一些情况需要直接使用内部方法修改 this ，Reflect 就可以做到

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

### 3.6 数组

（1）ES5

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

（2）ES6

```
const arr = [1, 2, 3];

// ES6 ----------------------------------------------------------------------------
// true ， 判断是否是一个真正的数组
console.log(Array.isArray(arr));

// 深拷贝数组，纯函数，参数可以是伪数组、Set 、Map ，结果都是真正的 Array
// [1, 2, 3]
console.log(Array.from(arr));
// [1]
console.log(Array.from(new Set([1])));
// [["a", 1]]
console.log(Array.from(new Map([["a", 1]])));
// [] []
console.log(
  Array.from({ a: 1 }),
  Array.from(function () {}),
  "\n"
);

// [2,4,6] ，纯函数，便利原数组并根据自定义条件生成新数组
console.log(arr.map((i) => i * 2));

// [1, 2] ，纯函数，便利原数组并根据条件筛选
console.log(arr.filter((i) => i < 3));

// 6 ，纯函数，便利数组并汇总，pre 为上一次便利的 return；第二个参数为初始值，默认为 0
console.log(arr.reduce((pre, now) => pre + now, 0));

// 6 ，2+4 ， 链式调用 map 、filter 、reduce
console.log(
  arr
    .filter((i) => i < 3)
    .map((i) => i * 2)
    .reduce((pre, now) => pre + now, 0),
  "\n"
);

// 查询元素是否符合条件 ，都是纯函数
// false ，便利整个数组，全部符合条件就返回 true
console.log(arr.every((i) => i > 3));
// true ，便利整个数组或者提前返回，只要一个符合条件就马上返回 true
console.log(
  arr.some((i) => i > 2),
  "\n"
);

// 查找第一个符合条件的元素，找到就马上返回，都是纯函数
// 1 ，找到返回元素值或引用，找不到返回 undefined
console.log(arr.find((value, index, arr) => value < 2));
// 0 ，找到返回 index ，找不到返回 -1
console.log(
  arr.findIndex((value, index, arr) => value < 2),
  "\n"
);

// [0, 2, 3] ，替换，非纯函数，第二、三个参数为开始、结束 index（左闭右开），默认全部替换
console.log(arr.fill(0, 0, 1), "\n");

// ---------------------------------------------------------------------------------------
// ES7 新特性，查询是否有某个元素，纯函数，找到就马上返回 true
// true
console.log(arr.includes(2), "\n");

// ES10 新特性，数组降维，纯函数
const deepArr = [1, [2, [3, 4]]];
// [1, 2, 3, 4] ，[1, 2, [3, 4]] ，参数为降低的维度，默认为 1
console.log(deepArr.flat(2), deepArr.flat());
// [2, NaN] ，等价于 arr.map().flat()
console.log(deepArr.flatMap((i) => i * 2));

// ES13 新特性，纯函数，访问元素，可以传入负数反向索引
const arr13 = [1, 2, 3];
const str13 = "asdf";
// 1 3 "a" "f"
console.log(arr13.at(0), arr13.at(-1), str13.at(0), str13.at(-1));
```

### 3.7 包装类

除了 null 、undefined 、Symbol 的其他 6 个基本数据类型，都有包装类，内置了一些属性和方法。

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

ES6 String API ：

```
// ES8 新特性，填充字符串，纯函数，、(n, c) 填充 c 直到 length 为 n 为止，c 默认为 " "
// "aab" " b"
console.log("b".padStart(3, "a"), "b".padStart(2));
// "qwb"
console.log("b".padStart(3, "qwertyu"));
// "bcs"
console.log("b".padEnd(2, "c"), "\n");

// ES10 新特性，去掉首尾空格，纯函数
// "a" "a"
console.log("  a".trimStart(), "a  ".trimEnd(), "\n");

// ES12 新特性，替换所有符合条件的子串，纯函数
console.log("aaa".replaceAll("a", "b"), "\n");
```

ES6 Number API ：

```
// Number.EPSILON ，用于浮点数运算
if (Math.abs(0.3 - (0.1 + 0.2)) < Number.EPSILON) console.log("相等");

// 进制
const a = 0b1010, b = 0o777, c = 0xff;

// 判断是否是整数
console.log(Number.isInteger(123));

// 判断是否是有理数
console.log(Number.isFinite(123));

// 转化成整数、浮点数
console.log(Number.parseInt(3.14), Number.parseFloat("3"));

// 判断是否是 NaN ，只有 NaN 才返回 true
console.log(Number.isNaN(NaN));
// 而 ES5 的 window.isNaN 会把 undefined ，String 、Object 都返回 true ，因为会进行类型转换
// console.log(window.isNaN(undefined));
```

### 3.8 正则

ES5 ：

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

ES6 ：

```
// ES9 -------------------------------------------------------------------------------
// 增加了负向后行断言，正向后行断言
// 新增匹配模式：dotAll 模式，修饰符 s ，使得可以匹配换行符

// 分组可以命名 左括号后加 ?<name>
const a = /\w+(?<num>\d+)/;

// 为每个字符分配了多个转义属性，比如判断是否存在希腊语字符，可以匹配 Script_Extensions 属性为 Greek 的字符
console.log(/\p{Script_Extensions=Greek}/.test("π"));

// ES11 -----------------------------------------------------------------------------
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

// ES13 --------------------------------------------------------------------------
// 新的修饰符 d，表示想要匹配字符串的开始和结束索引
const matchObj = /(a+)(b+)/d.exec("aaaabb");
// 'aaaa'
console.log(matchObj[1]);
// 'bb'
console.log(matchObj[2]);
// 由于 /d 标识的存在，matchObj 有一个属性 .indices，它用来记录捕获的每个编号组
console.log(matchObj.indices[1]); // [0, 4]
console.log(matchObj.indices[2]); // [4, 6]
```

### 3.9 Set 、Map

ES6 新特性，用红黑树实现。

（1）Set

集合，成员的值是惟一的，有相同的会去重，具有iterator接口 ：

```
const s0 = new Set();
const s1 = new Set([1, 2, 3]);

s0.add(1);
s0.delete(1);
// [] 0
console.log(s0, s0.size);

// true
console.log(s1.has(3));

s1.clear();
// []
console.log(s1);
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

（2）Map

字典，键值对的集合，key 是唯一的，相同的 key 会覆盖前面的 key ，有 iterator 接口。

key 可以是任何数据类型，Symbol 类型的 key 也可以遍历出来：

```
const m1 = new Map();
const m2 = new Map([
  ["name", "asdf"],
  ["age", 23],
]);

// obj 、map 互相转换
const m3 = new Map(Object.entries({ a: 1, b: 2 }));
const obj = Object.fromEntries(m3);

m1.set("name", "qwer");
console.log(m1.get("name"), m1.has("name"), m1.size);

m1.delete("name");
m2.clear();
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

（3）WeakSet 、WeakMap

都是弱引用，若资源不需要再使用，WeakSet 、WeakMap 就不再引用它们：

* WeakSet 的成员必须是引用类型或 Symbol ；WeakMap 的 key 必须是引用类型或 Symbol ，但 value 可以是任何类型

* 由于弱引用的不确定性，WeakSet 、WeakMap 就没有 size 、clear ，也无法便利，因此也没有 iterator 接口

```
// 大部分情况都是强引用，Set 、Map 也是
let obj1 = {};
let obj2 = obj1;

// 不会回收
obj1 = null;

// --------------------------------------------------------------------------------------------
const obj = {
  a: {},
  b: {},
};

const s = new Set([obj.a]);
const m = new Map([[obj.a, 1]]);

// 成员只能是引用类型、Symbol
const ws = new WeakSet([obj.b]);

// key 只能是引用类型、Symbol ；value 可以是任何类型
const wm = new WeakMap([[obj.b, 1]]);

// Set 、Map 是强引用，引用不会被垃圾回收
delete obj.a;
console.log(s, m);

// WeakSet 、WeakMap 是若引用，会被垃圾回收
// 垃圾回收是优先级比较低的县城，所以此时可能还未被回收，但最终都会回收
delete obj.b;
console.log(ws, wm, "\n");

// 都是 undefined
console.log(ws.size, wm.size, ws.clear, wm.clear);
console.log(ws.forEach, wm.forEach);
```

强引用：

ES12 新特性，WeakRef ，获得一个弱引用：

```
const obj = { a: 1 };
const wr = new WeakRef(obj);

// { a: 1 } ，若 obj 被垃圾回收了，则是 undefined
console.log(wr.deref());
```

（4）垃圾回收

为了防止内存泄漏，浏览器的垃圾回收器会对没有使用或不再使用的资源自动地进行回收来释放内存，遵循以下基本规则：

- 全局作用域的资源是否回收不确定，因为垃圾回收器难以判断开发者是否还需要这个资源，可能直到程序结束才回收。所以可以手动释放：
  
  ```
  // 占内存存放 obj 的地址，堆内存存放 a 的值和 o 的地址，b 的值
  let obj = { a: 1, o: { b: 2 } };
  
  // 手动释放，若其他地方都没有再强引用这个对象，就可以回收了
  // obj.o = null;
  // delete obj.o;
  
  // 直接释放 obj
  obj = null;
  ```

- 函数、块级作用域执行完，就会释放内部资源

- 闭包资源直到闭包的函数被回收才会回收

### 3.10 其他内置对象

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

// ES6 ---------------------------------------------------------------------------------
// 去掉小数部分
console.log(Math.trunc(3.14));

// 正数/负数/0返回 1/-1/0
console.log(Math.sign(123));
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

## 4 异步编程

ES5 中异步使用回调函数，如果嵌套很多，可读性就很差，称为毁掉地狱：

```
setTimeout(() => {
  console.log(1);

  setTimeout(() => {
    console.log(2);

    setTimeout(() => {
      console.log(3);
    }, 1000);
  }, 1000);
}, 1000);
```

ES6 提供了生成器、Promise、async/await ，使异步代码更清晰。

### 4.1 生成器

（1）基本

将函数氛围多个代码块，手动决定是否执行：

```
// 定义
function* func1() {}
function*func2() {}
function *fun3() {}

// GeneratorFunction
console.log(func1[Symbol.toStringTag]);
console.log(Object.prototype.toString.call(func1), "\n");

// 用 yield 分割代码块
function* func() {
  console.log(0);

  yield "block 1";
  console.log(1);

  // 接收 next 传入的参数
  const x = yield "block 2";
  console.log(x);
}

// 调用生成器会得到一个迭代器对象
const ite = func();

// 每次 next 会执行当前代码块，并吧指针指向下一个代码块
// 0 1 2
const block1 = ite.next();
const block2 = ite.next();
const end = ite.next(2);

// { value: 'block 1', done: false }
// { value: 'block 2', done: false }
// { value: undefined, done: true }
console.log(block1, block2, end, "\n");

// 不再输出
const endend = ite.next();

// for...of
const it = func();
// 0 "block1" 1 "block2" undefined
for (const i of it) console.log(i);
```

（2）异步

只使用生成器：

```
// 回调地狱 ---------------------------------------------------------------------------------
setTimeout(() => {
  console.log(1);

  setTimeout(() => {
    console.log(2);

    setTimeout(() => {
      console.log(3);
    }, 1000);
  }, 1000);
}, 1000);

// 改写成生成器 ----------------------------------------------------------------------
function* func() {
  yield (step) => {
    setTimeout(() => {
      console.log(1);
      step();
    }, 1000);
  };

  yield (step) => {
    setTimeout(() => {
      console.log(2);
      step();
    }, 1000);
  };

  yield (step) => {
    setTimeout(() => {
      console.log(3);
      step();
    }, 1000);
  };
}

function run(genFunc) {
  const gen = genFunc();

  (function step() {
    const result = gen.next();
    if (!result.done) result.value(step);
  })();
}

run(func);
```

也可以结合 Promise ：

```
function wait(ms) {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

function* func() {
  yield wait(1000);
  console.log(1);

  yield wait(1000);
  console.log(2);

  yield wait(1000);
  console.log(3);
}

function run(genFunc) {
  const gen = genFunc();

  function step() {
    const result = gen.next();
    if (!result.done) result.value.then(step);
  }

  step();
}

run(func);
```

### 4.2 Promise

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
 * ES9 新特性，可以再加一个 finally(() => {}) ，除了 pedding 无论成功失败都会在 then 、catch 后面回调；
   但 then 还是最多只能传两个参数
 */
new Promise((resolve, reject) => {
  setTimeout(() => {
    /* resolve, reject
     * resolve: 表示成功，状态变成 fullfilled ，若 then 已注册则把 then 的回调放到微任务，没有则等到 then 注册了再放到微任务
     * reject： 表示失败，状态变成 rejected ，其他同上，只是变成 catch
     * 若 resolve、reject 都没有，则状态为 Pending， thern、catch 都不执行
     */
    if (flag) resolve("this is res");
    else reject("err");

    // resolve ，reject 后面的代码也会执行，而不是直接截断
    console.log("run");
  }, 1000);
})
  .then((res) => {
    console.log(111, res);
  })
  .catch((str) => {
    console.log(str);
  })
  .finally(() => {
    console.log("this is finally");
  });

//

// 若 resolve 时还没有注册 then ，则只有到了 then 才会放到微任务 ---------------------------------
// 2 1 ，第一个 resolve 时还没有 then 所以无法放到微任务
new Promise((resolve) => {
  resolve(1);

  new Promise((resolve) => {
    resolve(2);
  }).then((res) => console.log(res));
}).then((res) => console.log(res, "\n"));

// 1 2 ，第一个 resolve 时，then 已经有了，直接放到微任务
new Promise((resolve) => {
  setTimeout(() => {
    resolve(1);

    new Promise((resolve) => {
      resolve(2);
    }).then((res) => console.log(res, "\n"));
  });
}).then((res) => console.log(res));

// 可以用 Promise 把任务放到微任务 -----------------------------------------------------
Promise.resolve().then(() => {});
Promise.reject().catch(() => {});
```

then ，catch 、finally 返回 Promise ，此 Promise 的状态由 then 、catch 返回值决定，

* 正常 return 则 fullfilled ，throw 则 rejected 

* 若 return 的又是一个 Promise ，则需要状态吸收，生成一个微任务，内部调用 then 让状态保持一致。

* finally 特殊，正常 return 或 return 非 rejected 的 Promise ，就穿透前一个 Promise 的值；若 finally 回调异常或 return rejected 的 Promise ，finally 就是 rejected

（2）async 、await

ES8 新特性，简化 Promise ，以类似同步代码的方式编写异步代码：

```
const testP = new Promise((resolve, reject) => {
  resolve(1);
  // reject(2);
  // resolve({ data: 123 });
});

// async 函数返回一个 Promise ，状态由返回值决定，规则和 then 返回值一样 ---------
async function func1() {
  // console.log(0);

  return 1;
  // throw 2;
  // return testP;
}

// 等价于
function func2() {
  return new Promise((resolve, reject) => {
    // console.log(0);

    resolve(1);
    // reject(2);
    // Promise.resolve().then(() => testP.then(resolve, reject));
  });
}

func1().then(
  (res) => console.log(res),
  (err) => console.log(err)
);

// await 只能用在 async 函数中，用于等待一个 Promise 完成 ----------------------------------------
async function func3() {
  // console.log(0);

  let result;
  try {
    result = await testP;

    // 若 await value ，value 不是一个 Promise ，则会转化为 Promise.resolve(value)
    // result = await 3;

    // await 的优先级闭 . [] () 等低
    // result = (await testP).data;
  } catch (err) {
    result = err;
  } finally {
    console.log("finally", result);
  }

  // 下面都是 then 、catch 中的代码，多个 wait 则相当于嵌套 then 、catch
  console.log("ok");
  return result;
  // throw result;
}

// 等价于
function func4() {
  return new Promise((resolve, reject) => {
    // console.log(0);

    let result;
    testP.then(
      (res) => {
        result = res;
        resolve(result);

        // 不是放在 .finally
        console.log("finally", result);
        console.log("ok");
      },
      (err) => {
        result = err;
        reject(err);

        // 不是放在 .finally
        console.log("finally", result);
        console.log("ok");
      }
    );
  });
}

func3().then(
  (res) => console.log(res),
  (err) => console.log(err)
);
```

表达式中不要混合同步代码和异步代码，会出问题：

```
let sum1 = 0;
let sum2 = 0;

async function getData(data, duration) {
  return new Promise((resolve) => {
    setTimeout(() => resolve(data), duration);
  });
}

async function add1(data, duration) {
  sum1 = sum1 + (await getData(data, duration));
  console.log(sum1);
}

// 2 3 ，同步异步混合一起运算，两次分别是 0+2 0+3 ，导致结果出错
add1(2, 1000);
add1(3, 2000);

// 正确做法，同步异步分开
async function add2(data, duration) {
  const n = await getData(data, duration);
  sum2 += n;
  console.log(sum2);
}

// 2 5 ，0+2 和 2+3
add2(2, 3000);
add2(3, 4000);
```

ES9 新特性，异步迭代器 for await of ：

```
const p = new Promise((resolve) => {
  resolve(0);
});

// "start" "sync" 1 0 2 0 "end" ，其中 "start" "sync" 是同步任务
(async function () {
  console.log("start");

  /**等价于
   * for await of start
     const res1 = await p;
     console.log(res1);
     const res2 = await p;
     console.log(res2);
   */
  for await (const i of [1, 2]) {
    console.log(i);
    const res = await p;
    console.log(res);
  }

  console.log("end");
})();

// 其他 for 结合异步的情况 -----------------------------------------------------------
// "start" 1 "sync" 0 2 0 "end" ，其中 "start" 1 "sync" 是同步任务
(async function () {
  // console.log("start");

  for (const i of [1, 2]) {
    // console.log(i);
    const res = await p;
    // console.log(res);
  }

  // console.log("end");
})();

// 1 2 "sync" 0 0 ，其中 1 2 "sync" 是同步任务
for (const i of [1, 2]) {
  // console.log(i);
  // p.then((res) => console.log(res));
}

console.log("sync");
```

（3）实现 Promise

通过自己实现一个 Promise ，可以完整理解 Promise 的执行过程，其中特别需要注意的是 then 、catch 返回 Promise 的情况、 static resolve 的情况和 \.finally ：

```
/**两个与原版 Promise 不同的地方
 * 微瑞列的实现不同，所以和原版 Promise 混用的话执行顺序会有问题，await 也是
 * 原版 rejected 若没有 catch 会抛出异常，这里没有处理，比较难实现
 */

const MY_PROMISE_STATU = {
  PEDDING: "pedding",
  FULLFILLED: "fullfilled",
  REJECTED: "rejected",
};

class MyPromise {
  #statu = MY_PROMISE_STATU.PEDDING;
  #result = undefined;
  #handler = [];

  constructor(executor) {
    try {
      executor(this.#resolve, this.#reject);
    } catch (err) {
      this.#reject(err);
    }
  }

  #resolve = (data) => {
    this.#changeStatu(MY_PROMISE_STATU.FULLFILLED, data);
  };

  #reject = (reson) => {
    this.#changeStatu(MY_PROMISE_STATU.REJECTED, reson);
  };

  // 修改状态，只能修改一次
  #changeStatu(statu, result) {
    if (this.#statu !== MY_PROMISE_STATU.PEDDING) return;

    if (this.#isPromiseLike(result)) {
      this.#statuAssimilater(result, this.#resolve, this.#reject);
    } else {
      this.#statu = statu;
      this.#result = result;
      this.#run();
    }
  }

  // 最核心的 then 方法
  then(onFullfilled, onRejected) {
    return new MyPromise((resolve, reject) => {
      /**
       * then 的时候肯呢还没有 resolve ，reject ，先记录起来
       * handler 是一个数组，因为 Promise 对象肯呢个会调用多次 then
       * 保存 resolve ，reject 是为了控制 then 链式调用返回的 Promise 的状态
       */
      this.#handler.push({
        onFullfilled,
        onRejected,
        resolve,
        reject,
      });

      this.#run();
    });
  }

  // Promise 规范规定只要有一个符合规范的 then 方法，就是一个 Promise ，也叫 thenable
  // 只要都是 thenable ，就具有互操作性，如都可以使用 await 等
  #isPromiseLike(value) {
    if (
      typeof value !== null &&
      (typeof value === "object" || typeof value === "function")
    ) {
      return typeof value.then === "function";
    }
  }

  // 放到微队列
  #runMicroTask(func) {
    try {
      // node
      process.nextTick(func);
    } catch (err) {
      // 浏览器
      if (typeof MutationObserver === "function") {
        const ob = new MutationObserver(func);

        const textNode = document.createTextNode("1");
        ob.observe(textNode, {
          characterData: true,
        });
        textNode.data = "2";
      }
      // 不支持微队列
      else setTimeout(func);
    }
  }

  // 状态吸收，当 then 、catch 、async 函数返回一个 Promise ，或 resolve 、reject 接收一个 Promise ，就需要状态吸收
  #statuAssimilater(myPromise, resolve, reject) {
    if (!this.#isPromiseLike(myPromise)) return;
    this.#runMicroTask(() => myPromise.then(resolve, reject));
  }

  // 处理 then 的回调
  #runOne(callback, resolve, reject) {
    if (this.#statu === MY_PROMISE_STATU.PEDDING) return;

    // 若没有传入回调，则 return 的 Promise 状态要和之前的 Promise 保持一致，达成穿透
    this.#runMicroTask(() => {
      if (typeof callback !== "function") {
        if (this.#statu === MY_PROMISE_STATU.FULLFILLED) resolve(this.#result);
        else reject(this.#result);
      } else {
        // 正常 return 则 resolve ，throw 则 reject
        // 若 return Promise ，则这个 Promise 状态要和 then 的 Promise 保持一致
        try {
          const data = callback(this.#result);

          if (this.#isPromiseLike(data)) {
            this.#statuAssimilater(data, resolve, reject);
          } else resolve(data);
        } catch (err) {
          reject(err);
        }
      }
    });
  }

  // 处理 then 的回调
  #run() {
    // 只有 fullfilled 、rejected 才 run

    if (this.#statu === MY_PROMISE_STATU.PEDDING) return;

    while (this.#handler.length !== 0) {
      const { onFullfilled, onRejected, resolve, reject } =
        this.#handler.shift();

      this.#runOne(
        this.#statu === MY_PROMISE_STATU.FULLFILLED ? onFullfilled : onRejected,
        resolve,
        reject
      );
    }
  }

  // Promise 规范之外的方法 ----------------------------------------------------------------
  catch(onRejected) {
    return this.then(null, onRejected);
  }

  /**finally
   * onFinally 不接收参数，正常情况下状态要和之前的 Promise 保持一致
   * 若 finally 正常 return 或 return 一个非 rejected 的 Promise ，就穿透前一个 Promise 的值
   * 若 finally 回调异常，或 return 一个 rejected 的 Promise ，那 finally 就是 rejected
   */
  finally(onFinally) {
    return this.then(
      (data) => {
        // 用 Promise.resolve 就能处理 finally 的所有情况
        return MyPromise.resolve(onFinally()).then(() => data);
      },
      (err) => {
        return MyPromise.resolve(onFinally()).then(() => {
          throw err;
        });
      }
    );
  }

  static resolve(value) {
    // 如果传入的是自己实现的 Promise ，就直接 return
    if (value instanceof MyPromise) return value;

    let tempResolve;
    let tempReject;
    const temp = new MyPromise((resolve, reject) => {
      tempResolve = resolve;
      tempReject = reject;
    });

    // 如果是其他人实现的 Promise，返回自己的 Promise 且状态和 value 保持一致
    if (temp.#isPromiseLike(value)) value.then(tempReject, tempReject);
    // 其他情况
    else tempResolve(value);

    return temp;
  }

  static reject(value) {
    // 不管 value 是什么，都返回一个新的 Promise
    return new MyPromise((resolve, reject) => {
      reject(value);
    });
  }
```

测试：

```
// 测试 1 ，调用多次 then -----------------------------------------------------------
const p1 = new MyPromise((resolve, reject) => {
  // 状态只能改变一次
  // resolve(1);
  // reject(2);
  // throw 3
  // 和原版 Promise 一样无法捕获异步异常
  // setTimeout(() => {
  //   throw 4;
  // });
});

p1.then(
  (res) => console.log(res),
  (err) => console.log(err)
);

p1.then(
  (res) => console.log(res),

  (err) => console.log(err)
);

// 测试 2 ，Promise 静态方法 ------------------------------------------------------------
const temp = new MyPromise(() => {});

// true
// console.log(MyPromise.resolve(temp) === temp);

// 其他 thenable
MyPromise.resolve(
  new Promise((resolve, reject) => {
    // resolve("resolve");
    // reject("reject");
  })
).then(
  (res) => console.log(res),
  (err) => console.log(err)
);

// 其他情况
// MyPromise.resolve(123).then((res) => console.log(res === 123));
// MyPromise.reject(123).catch((res) => console.log(res === 123));

// 测试 3 ，resolve 、then 先后顺序不同影响执行顺序 -----------------------------------------------
// "b" "a" ，resolve("b") -> resolve("a") -> then("a") -> then("b")
new MyPromise((resolve, reject) => {
  // resolve("a");
  // reject("a");

  new MyPromise((resolve, reject) => {
    // resolve("b");
    // reject("b");
  }).then(
    (res) => console.log(res),
    (err) => console.log(err)
  );
}).then(
  (res) => console.log(res),
  (err) => console.log(err)
);

// "a" "b" ，then("a") -> resolve("a") -> resolve("b") -> then("b")
new MyPromise((resolve, reject) => {
  setTimeout(() => {
    // resolve("a");
    // reject("a");

    new MyPromise((resolve, reject) => {
      // resolve("b");
      // reject("b");
    }).then(
      (res) => console.log(res),
      (err) => console.log(err)
    );
  });
}).then(
  (res) => console.log(res),
  (err) => console.log(err)
);

// 测试 4 ，穿透 ----------------------------------------------------------------------------
new MyPromise((resolve, reject) => {
  // resolve(1);
  // reject(2);
})
  .then()
  .then(
    (res) => console.log(res),
    (err) => console.log(err)
  );

// 2
new MyPromise((resolve, reject) => {
  // reject(2);
})
  .then(
    () => {},
    (err) => console.log(err)
  )

  .catch((err) => console.log(err + 1));

// 测试 5 ，finally 返回值 ---------------------------------------------------------------
const pf = new MyPromise((resolve, reject) => {
  resolve("ok");
  // reject("err");
});

new MyPromise((resolve) => {
  // resolve(0);
})
  .then((res) => console.log(res))
  .finally(() => {
    return pf;
  })
  .then(
    (res) => console.log(res),
    (err) => console.log(err)
  );

// 测试 6 ，结合 finally 的穿透 ------------------------------------------------------------
// 1 2 4 3
const f1 = new MyPromise((resolve, reject) => {
  // resolve();
})
  .then(() => console.log(1))
  .catch(() => console.log(1))
  .catch(() => console.log(1))
  .catch(() => console.log(1))
  .then(() => console.log(3));

const f2 = new MyPromise((resolve, reject) => {
  // resolve();
})
  .finally(() => console.log(2))
  .then(() => console.log(4));

// 测试 7 ，状态吸收 ----------------------------------------------------------------------
// 1 2 3 4
const pa = new MyPromise((resolve) => {
  resolve(3);
});

const pb = new MyPromise((resolve) => {
  // resolve(pa);
}).then((res) => console.log(res));

new MyPromise((resolve) => {
  // resolve();
})
  .then(() => console.log(1))
  .then(() => console.log(2))
  .then(() => console.log(4));

// // 0 1 2 3 4 5
// MyPromise.resolve()
//   .then(() => {
//     console.log(0);
//     return MyPromise.resolve(4);
//   })
//   .then((res) => console.log(res));

// MyPromise.resolve()
//   .then(() => {
//     console.log(1);
//   })
//   .then(() => {
//     console.log(2);
//   })
//   .then(() => {
//     console.log(3);
//   })
//   .then(() => {
//     console.log(5);
//   });
```

（4）处理多个 Promise

这些函数接收一个可迭代对象，返回 Promise，若成员不是 Promise 则会转为 Promise 。

当所有 Promise resolve 或 reject 后才决定返回的这个 Promise 的状态。

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

/**all -----------------------------------------------------------------------------------------
 * 所有 Promise fullfilled 时才 fullfilled ，总时间为最晚完成的 Promise ，或最早 rejected 的时间
 * res 为数组，err 为单个值
 */
// [1, 2] ，fillfilled
Promise.all([p1, p2]).then(
  (res) => console.log(res),
  (err) => console.log(err)
);

// 3 ，rejected
Promise.all([p1, p2, p3]).then(
  (res) => console.log(res),
  (err) => console.log(err, "\n")
);

/**allSettle ，ES11 新特性 ------------------------------------------------------------------------
 * 所有 Promise 完成后，不管成功失败，返回的 Promise 状态都是 fullfilled
 * res 为数组，保存每个 Promise 成功失败的信息
 */
// [ { statu: "fullfilled", value: 1 }, ... ]
Promise.allSettled([p1, p2, p3]).then((res) => console.log(res, "\n"));

/**any ，ES12 新特性 -----------------------------------------------------------------------------
 * 所有 Promise rejected 时才 rejected ，总时间为最晚完成的 Promise ，或最早 fullfilled 的时间
 * 只要有 Promise fullfilled 就直接 fullfilled ，类似竞速
 * res 为单个值；err 为对象，有个 key 保存失败值的数组
 */
// 1 ，fullfilled
Promise.any([p1, p2, p3]).then(
  (res) => console.log(res),
  (err) => console.log(err)
);

/** 这些 key 都是不可枚举的
 * {
     stack: "AggregateError: All promises were rejected"
     message: "All promises were rejected"
     errors:  [ 3 ]
   }
 */
Promise.any([p3]).then(
  (res) => console.log(res),
  (err) => {
    for (const key of Reflect.ownKeys(err)) console.log(key, ": ", err[key]);
    console.log("\n");
  }
);
```

实现 all（any 、allSettle 都差不多）：

```
// 接收一个可迭代对象
function myAll<T>(promiseList: Iterable<any>) {
  return new Promise((resolve, reject) => {
    const result: any[] = [];

    let cnt = 0;
    for (const promise of promiseList) {
      const index = cnt++;

      // 若成员不是 Promise 就转为 Promise
      Promise.resolve(promise).then((res) => {
        result[index] = res;
        if (--cnt <= 0) resolve(result);
      }, reject);
    }

    if (cnt <= 0) resolve(result);
  });
}
```

控制并发两；

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

## 5 模块化

### 5.1 基本

（1）基本

模块化可[以解决多个 script 变量冲突的问题：]()

```
<!DOCTYPE html>
<html lang="en">
  <body></body>

  <!-- 不使用模块化，多个 script 会有变量冲突 -->
  <script>
    const a = 1;
  </script>
  <script>
    // 1
    console.log(a);
  </script>

  <!-- 使用模块化，形成独立的作用域 -->
  <script type="module">
    const b = 2;
  </script>
  <script>
    // err
    try {
      console.log(b);
    } catch {
      console.log("err");
    }

    const c = 3;
  </script>

  <!-- 但是模块也可以使用非模块化的变量，所以最好都加上 type = "module" -->
  <script type="module">
    // 3
    console.log(c);
  </script>
</html>
```

文件路径：

* ,相对路径：\./ 当前目录 ，\.\./ 上一级目录 ，\.\./\.\./ 上两级目录

* 绝对路径

（2）模块化规范

模块化规范，其中最常用的是 esmodule 和 CommonJS 。：

- ES6 的 esmodule

- node 的 CommonJS

- requireJS 的 AMD

- sealS 的 CMD

CommonJS ，node 环境的默认模块化方式，是早期没有 ESM 时社区自己提供的 API ，因此没有语法层面的改变，也只能支持运行时，且是同步的：

```
// 2.js 导出

const a = 1, b = 2, c = 3;

module.exports = { a, b, c };

// 或者
// this.a = a;
// exports.b = b;
// module.exports.c = c;
```

```
// 1.js 导入，导入的是一个对象，可以解构赋值
const m = require("./2.js");
const { a, b, c } = require("./2.js");

// 1 2 3
console.log(m.a, m.b, m.c);

// 1 2 3
console.log(a, b, c);
```

esmodule ，适用于浏览器环境，是 ECMA 在语法层面上的新特性，支持静态依赖（编译时）和动态依赖（运行时，ES11）。

若在 node 环境使用 esmodule ，需要在 package\.json 中：

```
{
  "type": "module"
}
```

```
// 2.js 导出 
const a = 1, b = 2;

// 可以声明时就导出
export const c = 3;

const d = 4;

// 导出多个，要求之前不能已经 export
export { a, b };

// 默认导出，每个文件只允许有一个
export default d;
```

```
/**1.js 导入，导入的都是 const

// 按需导入，语法不是解构赋值，只是 import 的语法
import { a, b, c } from "./2.js";

// 导入全部并重命名，js2 本身是 const ，成员也是导出的资源所以也是 const 但成员的成员就不是了
import * as js2 from "./2.js";

// 导入 export default 的资源
import d from "./2.js";

// 导入全部后再导出
export * from "./2.js";

// 1 2 3
console.log(a, b, c);

// { a: 1, b: 2, c: 3, default: 4 }
console.log(js2);

// 4
console.log(d);
```

```
<!DOCTYPE html>
<html lang="en">
  <body></body>

  <!-- 
    html 中导入模块，需要通过 http 或 localhost 导入，所以需要 express 
    弄一个静态资源文件夹才行，且需要同源
  -->
  <script type="module">
    import { a } from "./2.js";

    // 1
    console.log(a);
  </script>
</html>
```

（3）符号绑定

ESM 的导入导出会形成符号绑定（即 C++ 中的引用），会共享内存空间，所以 ESM 才不允许导入的资源进行修改，但若模块导出了 set 函数就容易出问题，因此最好导出的资源都设置为 const ：

```
// 2.js

export let cnt = 0;
export const obj = { a: 0 };

export const add = () => {
  cnt++;
  console.log("2.js", cnt);
};

setTimeout(() => console.log("2.js", obj.a));
```

```
// 1.js

import { cnt, obj, add } from "./2.js";

// err ，无法修改
try {
  // cnt++;
  // obj = null;
} catch {
  console.log("err");
}

// 2.js 的 cnt 变为 1 ，没问题，但由于符号绑定，1.js 的 cent 也变为 1
add();
console.log(cnt);

// 2.js 的 obj.a 也变为 1 ，这就和符号绑定无关了，本身就是浅拷贝
obj.a = 1;
```

CommonJS 中不会符号绑定，导入的资源和导出的那个模块是不同的内存空间，不会冲突，但导入引用类型也是浅拷贝：

```
// 2.js

const obj = { a: 1 };

setTimeout(() => console.log(obj.a));

module.exports = { obj };
```

```
// 1.js

const { obj } = require("./2.js");

// 定时器输出 2
obj.a = 2;
```

（4）ESM 动态依赖

ES11 新特性，运行时异步加载模块：

```
// 2.js
export const a = 1;

// ES11 新特性，包含了该模块的原信息，如 url
console.log(import.meta, import.meta.url);
```

```
// ES11 新特性，动态 import ，可以实现运行时按需加载、按条件加载等，如懒加载
import("./2.js")
  .then((module) => {
    // 1
    console.log(module.a);
  })
  .catch((err) => {
    console.error("加载模块失败", err);
  });

// 2 ，ES13 新特性，顶层 await，允许在全局作用域使用 await
try {
  const module = await import("./2.js");
  console.log(module.a + 1);
} catch {
  console.log("err");
}

const p = new Promise((resolve) => {
  resolve(3);
});

// 3
const c = await p;
console.log(c);
```

### 5.2 原理

（1）node 模块查找策略

和模块化规范无关。ts 、工程化都会用到：

- 文件查找、文件夹查找，当使用绝对路径、相对路径时的查找策略：
  
  - ```
    import { a } from "./xxx";
    ```

- 先再目标路径中查找。若没有则补上后缀名 .js ，再没有就补 .json ，

- 若没有，则把路径看成文件夹，默认情况下找 index.js ，可以在 package.json 中修改：
  
  ```
  {
    "name": "main"
  }
  ```
  
  配置之后若找不到 main.js ，则再去找 index.js

- 再找不到就 err

- 内置模块查找、第三方模块查找，当只写了模块名的查找策略：
  
  - ```
    import express from "express";
    ```

- 先看是否为内置模块，若不是则认为是第三方模块，先看当前目录是否有 node_modules 文件夹，若没有则去上一级找，直到根目录为止，若都没有 node_modules 则 err

- 进入 node_module 并使用文件、文件夹的查找策略

（2）CommonJS 工作流程

运行时才确定依赖关系；

* 核心就是 require 函数，require 是 node 本地实现的，这里只能伪代码模拟：
  
  ```
  const path = require("path");
  
  const cache = new Map();
  
  function myRequire(modulePath) {
    // JS 的文件路径作为 moduleId
    const moduleId = "绝对路径" + modulePath;
  
    // 判断 JS 是否执行过，执行过就使用缓存的导出结果，不在执行
    if (cache.has(moduleId)) return cache.get(moduleId);
  
    // 将整个 JS 文件的代码放入一个函数内执行
    function _require(exports, require, module, __filename, __dirname) {
      // 防止循环依赖进入死循环
      cache.set(moduleId, {});
  
      // 运行模块 ...
  
      // 运行完成，缓存导出结果
      cache.set(moduleId, module.exports);
  
      return module.exports;
    }
  
    const module = { exports: {} };
  
    return _require.call(module.exports, [
      module.exports,
      myRequire,
      module,
      moduleId,
      path.dirname(moduleId),
    ]);
  }
  ```

* node 执行任何一个 JS 其实都是在 require 环境内：
  
  ```
  // 5
  console.log(arguments.length);
  
  // {} true
  console.log(this, this === exports && this === module.exports);
  
  // require 导入函数
  console.log(require);
  
  // 文件绝对路径，目录绝对路径
  console.log(__filename, __dirname);
  
  // 最终导出的是 { a: 1, b: 2, c: 3}
  this.a = 1;
  exports.b = 2;
  module.exports.c = 3;
  
  // exports 指向新对象，就和导出无关了
  // exports = {};
  
  // 这样导出的就是一个新对象 { d: 4 }
  // module.exports = { d: 4 };
  ```

* 执行顺序和 ESM 一样，输出 2 1 main 
  
  ```
  // main.js
  const m1 = require("./1.js");
  const m2 = require("./2.js");
  
  console.log("main");
  ```
  
  ```
  // 1.js
  const m2 = require("./2.js");
  console.log("1");
  ```
  
  ```
  // 2.js
  console.log("2");
  ```

（3）ESM 工作流程

在编译时就确定依赖关系，以浏览器环境为例，node 会略有不同：

* ```
  <script type="module" src="./main.js"></script>
  ```
  
  ```
  // main.js
  import { a } from "./1.js";
  import { b } from "./2.js";
  console.log("main");
  ```
  
  ```
  // 1.js
  import { b } from "./2.js";
  console.log("1");
  export const a = 1;
  ```
  
  ```
  // 2.js
  console.log("2");
  export const b = 2;
  ```

* 解析模块（不会执行 JS）：
  
  * 从入口 JS 开始，将路径转为 url 并进行下载，下载完成后解析入口 JS ，下载所有顶层静态依赖，并把导入语句放到代码最前面
  
  * 下载完成后先解析 1\.js ，发现导入的 2\.js 已下载或下载中，就不用重复下载

* 执行模块：
  
  * 从入口 JS 文件开始，发现导入语句就先执行导入的 JS ，上例会先执行 1\.js ，里面发现 2\.js ，就执行，所以 JS 执行完成的顺序是 2\.js ，1\.js ， main\.js 
  
  * 执行过程中遇到动态模块就异步解析下载执行，执行完成后导出和导入会进行符号绑定，共享内存空间
  
  * 每执行完一个 JS ，浏览器就把导出结果缓存起来，每个模块都用一个独立的缓存表保存所友导出的资源，后续如果其他文件再次导入此模块，就直接使用缓存，不在执行 JS ，所以上例的输出结果为 2 1 main 而不是 2 1 2 main

（4）循环依赖

当模块之间互相依赖，就会形成循环依赖，这种情况不会死循环，但获取不到未执行完成模块的资源：

```
// 1.js

// const m2 = require("./2.js");
// module.exports = { a: 1 };

import m2 from "./2.js";
export default { a: 1 };

// 正常，因为此时 2.js 执行完了
console.log(m2);
```

```
// 2.js

// const m1 = require("./1.js");
// module.exports = { b: 2 };

import m1 from "./1.js";
export default { b: 2 };

// ESM：err ，CommonJS：{} 不报错但有提示
try {
  console.log(m1);
} catch {
  console.log("err");
}
```

```
node ./1.js
```

解决方法：

* 运行时异步加载：
  
  ```
  // 2.js
  
  // CommonJS
  // module.exports = { b: 2 };
  // setTimeout(() => {
  //   const m1 = require("./1.js");
  //   console.log(m1);
  // });
  
  // ESM
  export default { b: 2 };
  import("./1.js").then((m1) => {
    console.log(m1);
  });
  ```

* 解开循环依赖，全局导入，模块使用全局传入的资源：
  
  ```
  // 1.js
  
  // module.exports = {
  //   a: 1,
  //   show: (m) => console.log(m),
  // };
  
  export default {
    a: 1,
    show: (m) => console.log(m),
  };
  ```
  
  ```
  // 2.js
  
  // module.exports = {
  //   b: 2,
  //   show: (m) => console.log(m),
  // };
  
  export default {
    b: 2,
    show: (m) => console.log(m),
  };
  ```
  
  ```
  // main.js
  
  // const m1 = require("./1.js");
  // const m2 = require("./2.js");
  
  import m1 from "./1.js";
  import m2 from "./2.js";
  
  m1.show(m1);
  m2.show(m2);
  ```

# 二、Web API

## 1 DOM

DOM ，文档对象模型，使 JS 可以操作 HTML。

DOM 树：整个html页面是一个 DOM 树，根元素是 \<html\>，叫文档 document ，每一个html 标签，叫元素 element ，所有页面内容，包括每个标签/属性/文本/注释等，叫节点 node 。

### 1.1 基本操作

（1）获取元素、节点操作

```
<!DOCTYPE html>
<html lang="en">
  <body>
    <ul id="box">
      <li class="item"></li>
      <li class="item"></li>
    </ul>
  </body>

  <script>
    // 获取元素 --------------------------------------------------------------------------
    // 单个 ul 元素
    const box1 = document.getElementById("box");

    // 伪数组 HTMLCollection
    const itemArr1 = document.getElementsByClassName("item");
    const itemArr2 = document.getElementsByTagName("li");

    // html 和 body
    const html = document.documentElement;
    const body = document.body;

    // 获取父子 node 、元素 ----------------------------------------------------------------
    // 获取子 node ，node 即元素、属性、文本等，nodeType 为节点类型
    const firstNode = box1.firstChild;
    const lastNode = box1.lastChild;
    console.log(firstNode, firstNode.nodeType);

    // 获取所有子 node ，结果为伪数组 NodeList
    const ietmNodes = box1.childNodes;

    // 获取子元素
    const firstElement = box1.firstElementChild;
    const lastElement = box1.lastElementChild;
    console.log(firstElement, firstElement.nodeType);

    // 获取所有子元素，结果为伪数组 HTMLCollection
    const itemElements = box1.children;

    // 父 node 、父元素
    const parentNode = itemArr1[0].parentNode;
    const parentElement = itemArr1[0].parentElement;

    // true true true ，判断是否为所包含的节点，如果就是本身也是 true
    console.log(
      box1.contains(box1),
      box1.contains(firstNode),
      box1.contains(firstElement)
    );

    // 获取兄弟 node 、元素 ----------------------------------------------------------------
    // 下一个兄弟 node 、元素
    const nextNode = itemArr1[0].nextSibling;
    const nextElement = itemArr1[0].nextElementSibling;

    // 上一个兄弟 node 、元素
    const preNode = itemArr1[1].previousSibling;
    const preElement = itemArr1[1].previousElementSibling;

    // 创建、添加、删除元素 ---------------------------------------------------------------
    // 添加、插入元素时，若待添加、待插入的是已存在的元素，则会移动，添加、插入到其他容器也是移动

    const newItem1 = document.createElement("li");
    const newItem2 = document.createElement("li");
    newItem1.innerText = 123;
    newItem2.innerText = 456;

    // push 到最后面
    box1.appendChild(newItem2);

    // 插入到某元素前面
    // box1.insertBefore(newItem1, itemArr1[0]);

    // 删除元素
    // box1.removeChild(itemArr1[1]);

    // 拷贝所有 node
    const newBox1 = box1.cloneNode(true);
    // 只拷贝元素本身，不拷贝子元素、文本等信息
    const newBox2 = box1.cloneNode();

    // HTML5 新特性 ，获取元素 ------------------------------------------------------------
    // 获取第一个符合条件的元素，可以传入任何 CSS 选择器，如属性选择器 ".box[data-item-id]"
    const box2 = document.querySelector("#box");

    // 伪数组 NodeList
    const itemArr3 = document.querySelectorAll(".item");
    const itemArr4 = document.querySelectorAll("li");

    // HTMLCollection 和 NodeList 区别 ---------------------------------------------------
    // HTMLCollection 的数据和页面实施绑定，如下会死循环
    // for (const ietm of itemArr2) {
    //   const newItem = document.createElement("li");
    //   box1.appendChild(newItem);
    // }

    // NodeList 则不绑定，就不会死循环
    for (const item of itemArr4) {
      const newItem = document.createElement("li");
      box2.appendChild(newItem);
    }

    // 但是，有时候获得的 NodeList 也是动态的，如 childNodes
    // 解决方法是用 ... 或者 Array.from 生成一个新数组再使用
    const itemArr5 = [...box2.childNodes];
  </script>
</html>
```

（2）读写节点值，样式、属性

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      #box2 {
        font-weight: 700;
        background-color: gray;

        /* CSS3 新特性，CSS 变量，也叫 CSS 自定义属性，用 -- 定义 */
        /* 这个变量会放在当前选中的元素中 */
        /* CSS 变量也有作用域链，当前作用域没有就会往上找 */
        --my-width: 10px;

        /* 使用变量 */
        border: var(--my-font-size) solid #000;

        /* 运算 */
        border: calc(var(--my-font-size) / 2) solid #000;

        /* 若变量不存在，就会使用默认值 */
        border-radius: var(--my-radius, 100px);
      }

      .box::before {
        color: red;
      }

      /* 设置 <html> 的样式 */
      :root {
        --my-font-size: 15px;
        border: 1px solid #000;
      }
    </style>
  </head>

  <body>
    <div id="box1">
      <!-- desc -->
      <span>123</span>
      <span style="display: none">456</span>
      <script>
        let a;
      </script>
    </div>

    <div id="box2" style="font-size: 50px">123</div>

    <input id="inp" type="text" data-inp-id="0" />
  </body>

  <script>
    const box1 = document.querySelector("#box1");
    const box2 = document.querySelector("#box2");
    const inp = document.querySelector("#inp");

    // HTMLDivElement -> HTMLElement -> Element -> Node -> EventTarget -> Object 原型 -> null
    let proto = box1.__proto__;
    while (proto) {
      console.log(proto);
      proto = proto.__proto__;
    }

    // 读写节点值 ----------------------------------------------------------------------
    // 123 ，获取所有非隐藏节点、非注释节点的内容C
    console.log(box1.innerText);
    // undefined ，获取不到注释节点的内容
    console.log(box1.childNodes[1].innerText);

    // 123 456 let a; ，获取包括隐藏节点，不包括注释节点所有子节点内容
    console.log(box1.textContent);
    // desc ，只有当前就是注释节点时，才能获取注释内容
    console.log(box1.childNodes[1].textContent);

    // null
    console.log(box1.nodeValue);
    // desc ，nodeValue 专门用来获取注释节点、文本节点的内容
    console.log(box1.childNodes[1].nodeValue);

    // 整个 HTML 的内容
    console.log(box1.innerHTML);
    // undefined ，如果当前是注释节点就获取不到注释内容，但文本节点可以
    console.log(box1.childNodes[1].innerHTML);

    // 修改注释内容
    box1.childNodes[1].nodeValue = " csed ";

    // 无论哪种方式，修改后都只有修改后内容
    // box1.innerText = 789;
    // box1.textContent = 789;
    // box1.innerHTML = 789;

    // 尽量不要这样修改 HTML 内容，容易被 XSS 攻击
    // box1.innerHTML = "<div>000</div>";

    // 读写样式 ---------------------------------------------------------------------------
    // 获取样式表
    console.log(document.styleSheets);

    /**读写 DOM 树行内样式
     * 单个：dom.style.color
     * 多个：都会覆盖所有行内样式，dom.style.cssText ，后续可以 += 追加属性；setAttribute 后续无法通过 cssText += 追加
     * 增加、删除：dom.style.setProperty() ，dom.style.removeProperty()
     */
    box2.style.fontSize = "100px";
    box2.setAttribute("style", "font-size:100px");
    box2.style.cssText = "font-size: 100px; border: 50px solid #000";
    box2.style.cssText += "text-align: center";
    box2.style.setProperty("height", "1000px");
    box2.style.removeProperty("height");

    /**getComputedStyle() ，window 的 API
     * 获取 SOM 树最终显示在页面的非几何样式，如黑色模式下获取的背景色都是黑色；样式修改后需要重新获取
     * 几何样式至少都需要在布局树后的阶段才能获取正确值；transition 变化后的样式都无法获取
     * 不符合 JS 命名规范的 CSS 属性需要 getPropertyValue() 获取
     */
    console.log(getComputedStyle(box2).fontSize);
    console.log(getComputedStyle(box2).backgroundColor);
    console.log(getComputedStyle(box2).getPropertyValue("--my-width"));
    // 获取伪元素的样式
    console.log(getComputedStyle(box2, "::before").color);
    // 读写 CSS 变量
    box2.style.setProperty("--my-color", "black");
    console.log(box2.style.getPropertyValue("--my-color"));

    /**读写 class
     * className 会覆盖所有 class
     * HTML5 新特性 classList ，可以单独读写 class
     */
    box2.className = "cls1 cls2";
    box2.className += "cls3";
    box2.classList.add("cls3");
    box2.classList.remove("cls1");
    console.log(box2.classList);
    // 切换，即存在就删除，不存在就添加
    box2.classList.toggle("cls4");

    /**读写属性 ---------------------------------------------------------------------------
     * 获得的结果都是 string ，不存在则 undefined
     * dom.propName 只能读取原生属性
     * setAttribute() ，removeAttribute() ，getAttribute() 原生属性、自定义属性都可以读写，自定义属性通常在标签中以 data-xxx 命名
     * HTML5 新特性 dataset ，专门用于读写自定义属性，省略 data- ，且会变成小驼峰
     *
     */
    inp.disabled = true;
    inp.value = 123;
    inp.setAttribute("data-inp-name", "name1");
    console.log(inp.getAttribute("data-inp-name"));
    inp.removeAttribute("data-inp-name");
    inp.dataset.inpId = "1";
    console.log(inp.dataset.inpId);
  </script>
</html>
```

（3）读写几何信息

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      * {
        margin: 0;
        padding: 0;
      }

      .container {
        position: relative;
        margin: 50px;
        padding: 50px;
        border: 5px solid #000;
      }

      .box1 {
        margin: 2px;
        padding: 2px;
        width: 100px;
        height: 100px;
        border: 10px solid #000;
        background-color: blue;
      }

      .box2 {
        overflow: scroll;
      }

      .box2 > .item {
        height: 30px;
      }

      .box3 {
        margin-top: 300px;
        transform: scale(2);
      }

      .box4 {
        transition: all 1s;
      }

      .box4-move {
        display: flex;
        border-width: 0;
      }
    </style>
  </head>
  <body>
    <div class="container">
      <div class="box1"></div>
    </div>

    <div class="box1 box2">
      <div class="item">1</div>
      <div class="item">2</div>
      <div class="item">3</div>
      <div class="item">4</div>
      <div class="item">5</div>
    </div>

    <div class="box1 box3"></div>

    <div class="box1 box4"></div>
  </body>

  <script>
    const box1 = document.querySelector(".box1");
    const box2 = document.querySelector(".box2");
    const items = document.querySelectorAll(".item");
    const box3 = document.querySelector(".box3");
    const box4 = document.querySelector(".box4");

    // "" ，可读写，获取行内样式，即 DOM 树 -------------------------------------------------
    console.log(box1.style.width);

    // "100px" ，只读，获取 SOM 树样式 ------------------------------------------------------
    console.log(getComputedStyle(box1).width);

    // 获取布局树样式 ----------------------------------------------------------------------
    /**滚动条
     * 无论什么盒子模型，滚动条都会压缩 content 大小
     * 滚动条大小会随着视口缩放而改变
     */
    // offset ，只读 ------------------------
    // 124 ，content + padding + border + 滚动条
    console.log(box1.offsetWidth);

    // 52 ，margin + 最近一级非 static 祖先 padding ，直到 body 为止，即使 body 是 static 也不会网上找了
    // 若该祖先是 body ，还需要加上 body 的 border
    console.log(box1.offsetLeft);

    // .container ，最近一级非 static 祖先
    console.log(box1.offsetParent);

    // client ，只读 ---------------------------
    // 104 ，content + padding - 注意 content 会被滚动条压缩
    console.log(box1.clientWidth);

    // 10 ，border
    console.log(box1.clientLeft);

    // scroll 。只读 ----------------------------
    // 154 ，滚动总高度 + padding ，即 30*5+2*2 ，此时不计算滚动条大小
    console.log(box2.scrollHeight, box2.clientHeight);

    // 输出一样 ，若内容没有溢出形成滚动，则的 clientWidth 相同，content 被滚动条压缩
    console.log(box2.scrollWidth, box2.clientWidth, box2.clientHeight);

    // 0 随滚动变化，获取滚动元素距滚动开始的偏移
    console.log(box2.scrollTop);
    box2.addEventListener("scroll", function () {
      console.log(box2.scrollTop);
    });

    // 获取最终当前显示的样式，即渲染流程的最终结果，但无法获取 transition 后的样式 ---------------
    // 获取的是当前举行区域，如果后续元素移动了，新位置需要重新获取举行
    const rect = box3.getBoundingClientRect();

    // 248 ，offsetWidth * transform: scale(2)
    // 如果旋转了，则得到的是外接举行的 width
    console.log(rect.width);

    // -60 ，计算 transform 后距 body border 外边缘的偏移，类似于相对于 body 的 offsetLeft ，只是 offset 得不到 transform 后的结果
    console.log(rect.left, box3.offsetLeft);

    // 获取到视口的偏移
    window.addEventListener("scroll", function () {
      // console.log(rect.top - document.documentElement.scrollTop);
    });

    // 获取 transition 后的样式 ---------------------------------------------------------
    box4.addEventListener("click", function (e) {
      e.target.style.backgroundColor = "red";
      e.target.style.transform = "translateX(100px)";
      e.target.classList.add("box4-move");

      // 已经写入的属性和无法 transition 的属性就能马上获取到
      console.log(
        e.target.style.backgroundColor,
        e.target.style.transform,
        getComputedStyle(e.target).display
      );

      // 无法获取 transition 后的样式
      requestAnimationFrame(() => {
        const { backgroundColor: bgc, border: bd } = getComputedStyle(e.target);
        const x = e.target.getBoundingClientRect().left;
        console.log(bgc, bd, x);
      });
    });

    // 正确做法
    box4.addEventListener("transitionend", function (e) {
      const { backgroundColor: bgc, border: bd } = getComputedStyle(e.target);
      const x = e.target.getBoundingClientRect().left;
      console.log(bgc, bd, x);
    });
  </script>
</html>
```

### 1.2 事件

事件三要素：事件源、事件类型、事件函数。事件函数的 this 指向事件源。

（1）绑定

```
<!DOCTYPE html>
<html lang="en">
  <body>
    <ul>
      <li class="item" onclick="func1(event, 1)">1</li>
      <li class="item">2</li>
      <li class="item">3</li>
      <li class="item">4</li>
    </ul>
  </body>

  <script>
    // 可以直接在元素标签内绑定，如果需要事件对象则必须传入 event
    // 其实就是在标签内写一个表达式，如也可以是 cnt++
    function func1(e, num) {
      console.log(e, "click" + num);
    }

    const items = document.querySelectorAll(".item");

    // JS 绑定，这种方式无法传入自己的参数
    items[1].onclick = function (e) {
      console.log(e, "click2");
    };

    // 可以 JS 主动触发事件，不用传参数会自动带上 event ，无法传入自定义参数
    items[1].click();

    // 删除绑定
    // items[1].onclick = null;

    // HTML5 新特性 --------------------------------------------------------------------
    items[2].addEventListener("click", function (e) {
      console.log(e, "click3");
    });

    // 可以多次绑定不同的函数引用，若之前 onclick 绑定了也会触发，所以执行三次
    items[2].onclick = function (e) {
      console.log('click3"');
    };
    items[2].addEventListener("click", function (e) {
      console.log("click3");
    });

    // 如果是相同的函数引用，则只保留一个，但 onclick 不会去掉，所以下面执行两次
    function func() {
      console.log("click4");
    }

    items[3].onclick = func;

    items[3].addEventListener("click", func);
    items[3].addEventListener("click", func);

    // 删除绑定
    // items[3].removeEventListener("click", func);
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

自定义事件：

Vue 、React 的自定义事件并不是使用这种方法实现的，有自己的机制。

```
<!DOCTYPE html>
<html lang="en">
  <body></body>

  <script>
    // 创建自定义事件
    const myEvent = new CustomEvent("myCustomEvent", {
      // 通信的数据，必须写在 detail
      detail: { a: 1 },
    });

    // 监听该事件
    document.addEventListener("myCustomEvent", function (e) {
      console.log(e.detail.a);
    });

    // 触发该事件
    document.dispatchEvent(myEvent);

    // 如果需要添加属性方法，则需要 继承 ---------------------------------------------------
    class MyCustomEvent extends CustomEvent {
      constructor(type, options) {
        super(type, { detail: options.detail });

        for (const key in options) {
          if (key === "detail") continue;
          this[key] = options[key];
        }
      }
    }

    const myE = new MyCustomEvent("myE", {
      detail: { a: 1 },
      b: 2,
    });

    document.addEventListener("myE", function (e) {
      console.log(e.detail?.a, e.b);
    });
    document.dispatchEvent(myE);
  </script>
</html>
```

（3）事件对象

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      .box {
        margin: 20px;
        border: 5px solid #000;
        width: 60px;
        height: 30px;
      }
    </style>
  </head>
  <body>
    <div class="box"></div>
    <div class="box"></div>
  </body>

  <script>
    const box = document.querySelectorAll(".box");

    // 通用的属性方法 -----------------------------------------------------------------
    box[0].addEventListener("click", function (e) {
      // 阻止浏览器对该事件的默认行为
      e.preventDefault();

      // 阻止事件冒泡
      e.stopPropagation();

      // 事件类型\，事件触发时的时间戳
      console.log(e.type, e.timeStamp);

      // 监听此事件的元素
      console.log(this, e.currentTarget);

      // 触发此事件的元素，注意事件冒泡中 e.target 也始终是触发事件的元素
      console.log(e.target);
    });

    // 鼠标相关事件中的事件对象，如拖拽 ---------------------------------------------------
    box[1].addEventListener("mouseenter", function (e) {
      // 鼠标点击相关的事件特有 ------------------------------------------------------------------
      // 点击的鼠标键，左中右分别为 0 1 2 ，不是点击事件就为 0
      console.log(e.button);

      // 是否按下了修饰键，布尔值
      console.log(e.ctrlKey, e.shiftKey, e.altKey, e.metaKey);

      // enter、leave 等进入离开相关的事件特有 -----------------------------------------------
      // enter 等进入的事件为从何处进入的元素；leave 等事件为离开后到达的元素
      console.log(e.relatedTarget);
      // 低版本 IE 中没有 relateedTarget ，但类似的有非标准属性 toElement
      // console.log(e.toElement);

      // 所有鼠标事件都有，左上角为坐标轴的原点 --------------------------------------------------------
      // 鼠标距 e.target 元素 content + padding 的偏移
      console.log(e.offsetX, e.offsetY);
      // 鼠标距视口的偏移
      console.log(e.clientX, e.clientY);
      // 鼠标距视口的偏移 + 页面滚动的偏移，即距整个页面的偏移
      console.log(e.pageX, e.pageY);
      // 鼠标距显示器的偏移
      console.log(e.screenX, e.screenY);
    });

    // 键盘事件对象 ------------------------------------------------------------------------
    window.addEventListener("keydown", function (e) {
      // 如 "1" "Numberpad1" 97
      // keyCode 已弃用
      console.log(e.key, e.code, e.keyCode);

      // 是否按下了修饰键，布尔值
      console.log(e.ctrlKey, e.shiftKey, e.altKey, e.metaKey);

      // 是否正在长按
      console.log(e.repeat);
    });
  </script>
</html>
```

（3）事件流

事件处理包括事件捕获、事件冒泡两个阶段。默认情况下，事件在冒泡阶段触发。

- 事件捕获：从 DOM 树根结点出发到叶子结点捕获事件

- 事件冒泡：从触发事件的对象出发，到根结点，若该事件对象的祖先有定义相同事件，则也会触发，注意 e\.target 始终为触发事件的元素，和冒泡无关：
  
  ```
  <!DOCTYPE html>
  <html lang="en">
    <head>
      <style>
        .box {
          border: 1px solid #000;
        }
  
        .big {
          display: flex;
          justify-content: center;
          align-items: center;
          width: 200px;
          height: 200px;
          background-color: #000;
        }
  
        .mid {
          display: flex;
          justify-content: center;
          align-items: center;
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
  
      big.addEventListener("click", function (e) {
        console.log("big", e.target);
      });
  
      mid.addEventListener("click", function (e) {
        console.log("mid", e.target);
      });
  
      small.addEventListener("click", function (e) {
        // e.stopPropagation();
        console.log("small", e.target);
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

### 1.3 常用 API

（1）拖拽

需要在元素标签添加 draggable="true" ：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      .container {
        display: flex;
        flex-wrap: wrap;
      }

      .box {
        margin: 20px 0;
        border: 10px solid #000;
        width: 300px;
        height: 300px;
      }

      .item {
        margin: 20px;
        height: 30px;
        border: 1px solid #000;
        background-color: red;
        line-height: 30px;
        text-align: center;
        color: #fff;
        transition: margin-top 0.5s;
      }

      .hidden {
        display: none;
      }

      .enter {
        margin-top: 50px;
      }
    </style>
  </head>

  <body>
    <div class="container">
      <div class="box" data-can-dragged="true">
        <div class="item" draggable="true" data-item-id="0">1</div>
        <div class="item" draggable="true" data-item-id="1">2</div>
        <div class="item" draggable="true" data-item-id="2">3</div>
        <div class="item" draggable="true" data-item-id="3">4</div>
        <div class="item" draggable="true" data-item-id="4">5</div>
      </div>

      <div class="box" data-can-dragged="true"></div>
      <div class="box" data-can-dragged="true"></div>
    </div>
  </body>

  <script src="./1.js"></script>

  <script>
    const boxes = document.querySelectorAll(".box");
    const items = document.querySelectorAll(".item");
    const flip = new Flip(items);

    /**拖拽
     * 被拖拽元素的标签才需要加 draggable 属性，目标不用
     * 最好写成 draggable="true" ，若简写成 draggable ，拖拽会有问题
     * 被拖拽元素监听 dragstart 、drag 、dragend ；目标监听 dragenter 、dragover ，dragleave，drop ，dragend
     */
    let activateBox = null;
    let activateItem = null;
    let enterItem = null;

    for (const box of boxes) {
      // 拖拽开始时触发一次，draggable 的元素才会触发
      box.addEventListener("dragstart", function (e) {
        // 被拖拽的元素
        // console.log("start", e.target);

        // 修改鼠标行为，即拖拽时鼠标的样式
        // e.dataTransfer.dropEffect = "copy";

        // 修改拖拽缩略图，需要创建一个 img 元素并设置 src
        // e.dataTransfer.setDragImage(myImgElement, 0, 0);

        activateItem = e.target;
        activateBox = box;

        // 拖拽开始时，会产生一个样式基于被拖拽元素的拖拽缩略图，所以才需要异步修改被拖拽元素的样式，才不影响拖拽缩略图
        setTimeout(() => {
          e.target.classList.add("hidden");
          flip.play();
        });
      });

      // 拖拽时一直触发
      // box.addEventListener("drag", function (e) {
      //   // 被拖拽的元素，不是拖拽缩略图
      //   // console.log(e.target);
      // });

      // 拖拽结束时触发一次
      box.addEventListener("dragend", function (e) {
        // 被拖拽的元素
        // console.log(e.target);

        flip.refreshPosition();
        flip.refreshPosition(e.target, e.clientX, e.clientY);
        e.target.classList.remove("hidden");

        flip.play();
      });

      // 拖拽到刚进入某个元素后触发一次
      box.addEventListener("dragenter", function (e) {
        // 拖拽经过的元素
        // console.log("enter", e.target);

        if (!e.target.dataset.itemId) return;
        if (enterItem) enterItem.classList.remove("enter");
        if (e.target === enterItem) {
          enterItem = null;
          return;
        }

        enterItem = e.target;
        e.target.classList.add("enter");
      });

      // 拖拽经过某个元素后触发多次
      box.addEventListener("dragover", function (e) {
        e.preventDefault();

        // 拖拽经过的元素
        // console.log("over", e.target);
      });

      // 拖拽离开某个元素后触发一次
      box.addEventListener("dragleave", function (e) {
        // 拖拽离开的元素
        // console.log(e.target);

        if (enterItem && !box.contains(e.relatedTarget)) {
          enterItem.classList.remove("enter");
          enterItem = null;
        }
      });

      // 松手后触发一次，闭 dragend 执行早
      // 有些元素如 div ，table 、td 等不允许其他元素被拖拽到它们上面，不会触发 drop，需要在 dragover 事件中取消默认行为
      box.addEventListener("drop", function (e) {
        // 松手后被压在下面的元素
        // console.log("drop", e.target);

        const parentEl =
          e.target.dataset.canDragged === "true"
            ? e.target
            : e.target.parentElement;

        if (enterItem?.parentElement === box) {
          parentEl.insertBefore(activateItem, enterItem);
        } else parentEl.appendChild(activateItem);

        enterItem?.classList?.remove("enter");
      });
    }
  </script>
</html>
```

（2）剪切板

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      .img-box {
        width: 100px;
        height: 100px;
        border: 1px solid #000;
      }
    </style>
  </head>
  <body>
    <p class="text">123456789</p>
    <input type="text" />

    <div class="img-box" contenteditable="true"></div>
  </body>

  <script>
    const text = document.querySelector(".text");

    // 监听复制并添加内容 -----------------------------------------------------------------
    text.addEventListener("copy", function (e) {
      // 阻止复制的内容
      e.preventDefault();

      // 复制的内容，阻止了默认行为也能获取，因为得到的其实是选中的内容
      const selectedText = window.getSelection().toString();
      console.log(selectedText);

      // 添加内容
      navigator.clipboard.writeText(selectedText + "hello world");
    });

    // 获取剪切板内容，如根据剪切板内容进入某个页面 ---------------------------------------------
    // 为了隐私安全，浏览器会提示用户剪切板内容正在被读取，所以是一个 Promise
    navigator.clipboard
      .readText()
      .then((text) => {
        console.log(text);
      })
      .catch((err) => console.log("用户拒绝"));

    // 粘贴图片 ------------------------------------------------------------------------
    // 设置了 contenteditable="true" 的元素会变成可粘贴图片的 input ，但如果不用 JS 处理，不能保证每个浏览器都支持，且只能粘贴截图，不能粘贴复制的图片文件
    const imgBox = document.querySelector(".img-box");

    imgBox.addEventListener("paste", function (e) {
      // 若粘贴的是文本，则长度为 0
      if (e.clipboardData.files.length === 0) return;

      e.preventDefault();

      const reader = new FileReader();
      reader.onload = (res) => {
        const base64 = res.target.result;

        const img = document.createElement("img");
        img.src = base64;

        imgBox.appendChild(img);
      };

      for (const file of e.clipboardData.files) reader.readAsDataURL(file);
    });
  </script>
</html>
```

（3）IntersectionObserver

观察两个元素是否交叉，即被观察元素是否已经进入、离开某个元素，可以替代需要监控浏览器滚动的需求；

```
<!DOCTYPE html>
<html lang="en">
  <body>
    <ul class="list"></ul>
    <div class="loading">loading...</div>
  </body>

  <script>
    const list = document.querySelector(".list");
    const loading = document.querySelector(".loading");

    function addItem(num) {
      const start = document.querySelectorAll("li").length + 1;
      const frag = document.createDocumentFragment();

      for (let i = start; i < num + start; i++) {
        const li = document.createElement("li");
        li.textContent = "" + `${i}`;
        frag.appendChild(li);
      }

      list.appendChild(frag);
    }

    const ob = new IntersectionObserver(
      // 交叉到不交叉，或者不交叉到交叉就执行
      (entries) => {
        // 参数为一个数组，保存了这个 ob 对象所有 sbserve 的对象
        console.log(entries.length);

        // 如果不需要观察了，如图片懒加载，可以卸载
        // ob.unobserve(entries[0].target);

        if (entries[0].isIntersecting) {
          // 被观察的元素
          console.log(entries[0].target);

          addItem(50);
        }
      },

      {
        // 和哪个元素交叉，只能是祖先元素，默认为 null ，即视口
        root: null,

        // 交叉范围，默认 0 ，即被观察元素的大小
        rootMargin: "0px",

        // 交叉阈值，默认 0 ，范围从 0 ~ 1 ，交叉到交叉范围多少百分比才触发
        threshold: 1,
      }
    );

    ob.observe(loading);
  </script>
</html>
```

（4）监听页面显示隐藏

```
<!DOCTYPE html>
<html lang="en">
  <body></body>

  <script>
    // 浏览器兼容性
    let hidden, visibilityChange;
    if (document.hidden !== undefined) {
      hidden = "hidden";
      visibilityChange = "visibilitychange";
    }
    // 低版本 chrome
    else if (document.webkitHidden !== undefined) {
      hidden = "webkitHidden";
      visibilityChange = "webkitvisibilitychange";
    }
    // IE
    else if (document.msHidden !== undefined) {
      hidden = "msHidden";
      visibilityChange = "msvisibilitychange";
    } else throw "不支持";

    // 页面显示、隐藏后触发
    document.addEventListener(visibilityChange, function (e) {
      const info = document[hidden] ? "隐藏" : "显示";
      console.log(info);
    });
  </script>
</html>
```

## 2 BOM

BOM，浏览器对象模型，API 都放在 window ，使用时可以省略 window 。

（1）BOM 常用事件

window 和 document 可注册的事件有些不同，但如果是都可以注册的事件如 click ，则区别在于时间补货和事件冒泡， window 是 document 的外层。

页面加载：

```
<!DOCTYPE html>
<html lang="en">
  <script>
    // 执行顺序：readystatechange - DOMContentLoaded - readystatechange - load - pageshow ------------

    // 不太常用，文档状态变化时触发，如 loading → interactive → complete
    document.onreadystatechange = function () {
      console.log("readyState:", document.readyState);
    };

    // DOM 树构建完成，不等待图片、CSS 加载，可以安全操作 DOM 元素
    document.addEventListener("DOMContentLoaded", function () {
      console.log("DOMContentLoaded");
    });

    // 页面所有资源（图片、CSS、iframe、音视频等）完全加载完后触发，当 script 在 body 之前拿不到最终 DOM 就可以用 load
    window.addEventListener("load", function () {
      console.log("load");
    });

    // 与onload基本一样，但是在火狐浏览器中，前进页面后，之前的页面会缓存，再后退不会触发 load，而pageshow可以
    window.addEventListener("pageshow", function () {
      console.log("pageshow");
    });

    // 用户试图离开页面前触发，可用于弹出“是否确定离开”的提示
    window.addEventListener("beforeunload", function () {
      console.log("beforeunload");
    });

    // 页面完全卸载时触发。现在常用于性能分析，不建议做复杂操作
    window.addEventListener("unload", function () {
      console.log("unload");
    });
  </script>

  <body></body>
</html>
```

窗口：

```
<!DOCTYPE html>
<html lang="en">
  <body></body>

  <script>
    // 滚动
    window.addEventListener("scroll", function () {
      console.log("scroll");
    });

    // 缩放
    window.addEventListener("resize", function () {
      console.log("resize");
    });
  </script>
</html>
```

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

## 3 Web 原理

执行上下文：就是执行栈。

### 3.1 事件循环

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

* 定时器设置为 0ms 也是异步任务，延时参数默认值是 0m s 

* 相同延时的定时器，按照代码先后顺序入队

* 定时器无法做到精确计时，因为：
  
  * 计算机硬件本身就有微小偏差；定时器函数调用的操作系统的函数，本身也有微小偏差
  
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
  
  * 切换页面后，浏览器为了优化性能，会吧隐藏页面的定时器延长
  
  * 执行同步任务也需要时间，计时完成可能同步任务还没有完成

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

### 3.2 渲染帧

渲染任务的优先级比微任务低，但和宏任务的优先级不好比较，不同浏览器的处理不同，有的比宏任务高，有的在宏任务中间适合的时间段渲染，因此执行顺序不好判断。

浏览器帧数为 60 帧，及约 16.67 ms 为 1 帧，

（1）API

虽然 CSS 动画已经很强大，但一些情况下还是需要 JS 做动画，此时不能使用定时器 setInterval 定时 16.67 ms 。因为浏览器会受到机器配置、卡顿等各种原因导致浏览器分配的渲染帧并不平均，就会导致空帧（小于 16.67 ms ，多个渲染帧没有做任何动画）和跳帧（大于 16.67 ms ，一个渲染帧做了多次动画，只保留了最后一个动画），

HTML5 新特性提供了两个渲染帧相关的 API 。注意只有渲染任务开始了，才会有渲染帧，及也是异步的，顺序在微任务后面，一次渲染帧不一定为 16\.67 ms :

* requestAnimationFrame ：简称 raf，每次渲染帧开始之前毁掉

* requestIdleCallback ：渲染帧结束后，若此次渲染帧小于 16\.67 ms ，即还有剩余时间，就回调，兼容性比 raf 差一点

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

有些动画是必须使用 JS 的，如修改元素的内容，现在 JS 动画主要通过渲染帧 API 或 Web Animation API 实现，都是 HTML5 新特性。

动画的本质就是数值的变化，因此无论是 JS 还是 CSS 动画，都只能以数值变化作为动画的基础：

```
.box {
  width: 10px;
  border: 1px solid #000;
  background-color: blue;
  transition: all 1s;
}

.box-click {
  /* 这些都有数值变化，就有动画 */
  width: 100px;
  border-width: 0;
  background-color: red;
  transform: translate((100px, 100px));

  /* 没有数值变化就不能做动画 */
  display: none;

  /* 复合属性需要注意，要么写全，要么单独写数值属性 */
  /* 没有动画 */
  /* border: 0; */
  border-width: 0;
  border: 0 solid #000;
}
```

下面虽然使用了 raf 和 transform ，但 raf 终究是工作在渲染主线程中，还是会有阻塞渲染的风险：

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

Web Animation API ，性能接近 CSS3 动画，通过 keyframs 实现，而不是修改 DOM 的 style ：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      .box {
        width: 100px;
        height: 100px;
        border: 5px solid #000;
        border-radius: 50px;
      }
    </style>
  </head>
  <body>
    <div class="box"></div>
  </body>

  <script>
    const box = document.querySelector(".box");

    window.addEventListener("click", function (e) {
      const x = e.clientX - box.offsetWidth / 2;
      const y = e.clientY - box.offsetHeight / 2;
      const { left, top } = box.getBoundingClientRect();

      // 动画对象会保存，为了防止对象越来越多，可以手动删除不用的动画对象
      // console.log(box.getAnimations().length);
      box.getAnimations().forEach((i) => i.cancel());

      /**两个参数
       * keyframs ，默认不用写百分比，会平均分配，也可以用 offset 设置百分比（0 ~ 1）
       * animation options ，可以写一个 ms 数值，也可以写一个对象
       */
      box.animate(
        [
          {
            transform: `translate(${left}px, ${top}px)`,
          },
          {
            transform: `translate(${left}px, ${top}px) scale(2)`,
            offset: 0.5,
          },
          {
            transform: `translate(${x}px, ${y}px)`,
          },
        ],
        {
          duration: 1000,
          fill: "forwards",
        }
      );
    });
  </script>
</html>
```

Flid 动画（First Last Invert Play），一种元素结构变化的动画解决方案，元素结构变化是非数值变化，一般无法做动画，而 flip 的思路是先记录 first 的偏移，元素结构变化后根据 last 偏移和 first 偏移计算变化偏移，在渲染之前移动到 first 位置，再动画移动到 last 位置，形成偏移数值的变化，就能做动画，Vue 的 transition 组件用的就是 flip ：

```
// flip.js

class Flip {
  constructor(dom, duration = ".5s") {
    this.#duration = typeof duration === "number" ? `${duration}s` : duration;
    this.#init(dom);
  }

  #dom = [];
  #duration = "";

  #getPosition(el) {
    const rect = el.getBoundingClientRect();

    return {
      x: rect.left,
      y: rect.top,
    };
  }

  #createDomInfo(dom) {
    return {
      el: dom,
      transition: `${getComputedStyle(dom).transition},transform ${
        this.#duration
      }`,
      firstPos: this.#getPosition(dom),
    };
  }

  // 获取初始偏移
  #init(dom) {
    if (!dom) return;

    if (!dom.length) {
      this.#dom.push(this.#createDomInfo(dom));
      return;
    }

    for (const el of dom) this.#dom.push(this.#createDomInfo(el));
  }

  // 获取变化后的偏移，并开始动画
  play(options = {}) {
    const defaultOptions = {
      refresh: true,
    };
    const { refresh } = { ...defaultOptions, ...options };

    for (const info of this.#dom) {
      const { el, firstPos } = info;

      const { x, y } = this.#getPosition(el);
      const dx = firstPos.x - x;
      const dy = firstPos.y - y;

      // 如果需要刷新新位置
      if (refresh) info.firstPos = { x, y };

      // 此时还没有到渲染任务，先让元素回到原来的位置
      el.style.removeProperty("transition");
      el.style.transform = `translate(${dx}px, ${dy}px)`;

      // 在回到目标位置，形成数值的变化，就可以做动画了
      requestAnimationFrame(() => {
        el.style.transition = info.transition;
        el.style.removeProperty("transform");
      });
    }
  }

  // 有时候外部可能需要手动刷新新位置
  refreshPosition(el, x, y) {
    if (!el) {
      for (const info of this.#dom) info.firstPos = this.#getPosition(info.el);
      return;
    }

    const info = this.#dom.find((i) => i.el === el);
    if (info) info.firstPos = { x, y };
  }
}
```

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      .item {
        margin: 20px 0;
        height: 50px;
        border: 5px solid #fff;
        line-height: 50px;
        text-align: center;
      }
    </style>
  </head>
  <body>
    <div class="box">
      <div class="item">1</div>
      <div class="item">2</div>
      <div class="item">3</div>
      <div class="item">4</div>
      <div class="item">5</div>
    </div>

    <button id="btn">click</button>
  </body>

  <script src="./flip.js"></script>

  <script>
    const btn = document.querySelector("#btn");
    const items = document.querySelectorAll(".item");
    const flip = new FliP(items);

    btn.addEventListener("click", function () {
      // 乱序
      for (const item of items) {
        const index = Number.parseInt((Math.random() * 10) / 2);
        item.parentElement.insertBefore(item, items[index]);
      }

      flip.play();
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
         * 如果在一个渲染帧中，渲染任务在 16.67 ms 内完成了，就没必要马上开始下一个渲染任务，
           可以利用剩余空闲时间执行分片任务
         * 之所以用 while 是因为想在下一个渲染任务前，尽量利用空闲时间执执行分片任务，当然
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

（4）性能监控

服务监控，监控用户在使用软件中遇到的问题，提供给后台进行数据分析。

数据埋点是服务监控的其中一个环节，在客户端实现，主要分为：

* 非侵入式：程序错误、性能监控。通常封装为一个库，直接在入口文件调用，不影响原本的代码

* 侵入式：行为监控，用户哪些行为导致不继续使用软件，需要在具体的代码中嵌入，开发成本较高

性能监控的简单实现：

```
<!DOCTYPE html>
<html lang="en">
  <body></body>

  <script>
    function delay(ms) {
      const now = Date.now();
      while (1) {
        if (Date.now() - now >= ms) break;
      }
    }

    // 方式一，监控 FPS ，但很局限，很多用户感受的卡顿并不一定是 PDS ，如事件延迟，图片加载，布局等
    function FPSobserver() {
      const now = Date.now();

      requestAnimationFrame(() => {
        if (Date.now() - now > 17) console.log("没有 60 帧");
        FPSobserver();
      });
    }
    // FPSobserver();

    // 方式二，推荐使用
    const ob = new PerformanceObserver((list) => {
      // 便利所有需要监控的类型，目前只监控了 longtask
      for (const i of list.getEntries()) {
        console.log(`类型: ${i.entryType}，耗时：${i.duration} ms`);

        // 如果耗时过长，就判定为卡顿，上报监控中心
        if (i.duration > 100);
      }
    });

    // 配置
    ob.observe({
      // 监控类型，其他类型查阅文档
      entryTypes: ["longtask"],
    });

    delay(3000);
    console.log(123);

    // 网络监控 -----------------------------------------------------------------------------
    function getNetworkInfo() {
      let info;

      if (navigator.onLine) {
        info = {
          type: navigator.connection.effectiveType,
          rtt: navigator.connection.rtt,
          downlink: navigator.connection.downlink,
        };
      } else info = { type: "offline" };

      return info;
    }

    // 分别是在线、离线、改变网络类型触发
    window.addEventListener("online", function (e) {});
    window.addEventListener("offline", function (e) {});
    navigator.connection.addEventListener("change", function (e) {});

    setInterval(() => {
      console.log(getNetworkInfo());
    }, 1000);
  </script>
</html>
```

### 3.3 Web Worker

HTML5 新特性，开启一个新县城，缺点是无法操作 DOM 。

### 3.4 浏览器渲染原理

渲染，将一个 HTML 字符串（HTML 文档）转变成页面像素信息的过程。

（1）解析 HTML 字符串

浏览器的网络进程拿到 HTML 文档后，产生一个渲染任务，交给渲染主线程的消息队列，在事件循环机制的作用下，渲染主线程取出渲染任务并处理：

```
const html = "<div>...</div>";
```

渲染主线程解析 HTML 字符串：

```
const doc = new DOMParser().parseFromString("<div>123</div>", "text/html");

// 123;
console.log(doc.body.textContent);
```

当解析到 \<style\> 和 \{link\> 的 CSS 时，会交给渲染进程中的预解析现成异步解析 CSS ，解析完成后再交给渲染主线程去生成 SOM 树，所以 CSS 不会阻塞 HTML 的解析。

而解析到 \<script\> 时，渲染主线程会等待 JS 下载执行完毕，之所以解析 JS 不是异步的，是因为 JS 可能修改 DOM 。

因此 JS 就会造成渲染主线程的阻塞：

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

script 可以使用 async 和 defer 实现异步下载、异步执行；

```
// 1.js
const now = Date.now();

while (1) {
  if (Date.now() - now >= 3000) break;
}
```

```
<!DOCTYPE html>
<html lang="en">
  <!-- 阻塞渲染主线程 -->
  <!-- <script src="./1.js"></script> -->

  <!-- async 、defer 只有存在 src 时才生效 ---------------------------------------->
  <!-- async
    * 异步下载，下载完马上在渲染主线程执行，若此时 html 还未渲染完就会阻塞
    * 每个 script 下载完的时间不同，所以 script 顺序会改变 
    * 适用于独立脚本，如广澳
  -->
  <!-- <script async src="./1.js"></script> -->

  <!-- 
    * 异步下载异步执行
    * script 顺序不变，在 DOMContentLoader 之前执行
    * 适用于依赖 DOM 的 JS 
  -->
  <script defer src="./1.js"></script>
  <body>
    123
  </body>
</html>
```

（2）解析完成后，完成 DOM 树 、SOM 树的生成

DOM Object Model 、 CSS Object Model ，都是对象，方便后续处理，同时让 JS 有操作 HTML 、CSS 的能力。

JS 不会生成一个树，因为 JS 只执行一次就行了，异步也有事件循环处理。

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      .box {
        font-size: 50px;
      }
    </style>
  </head>
  <body>
    <div class="box" style="font-weight: 700">123</div>
  </body>

  <script>
    // DOM 树根节点，即 <html>
    console.log(document.documentElement);

    // SOM 树，根结点保存了一个存储各个样式表的数组，得到样式表后，除了默认样式表外都可以 CURD选择器、属性等
    // 获取内联样式表
    console.log(document.querySelector(".box").style);
    // 获取内部样式表、外部样式表形成的数组
    console.log(document.styleSheets);
  </script>
</html>
```

样式计算：遍历 DOM 树，每个结点进行样式计算，得到每个节点计算后的最终的样式 computed style（所有 CSS 属性都要有 value ，且都是绝对单位，如 em 变 px ，string 的 color 变 rgb\(\)），最后得到有样式的 DOM 树：

```
// 得到计算后的样式
getComputedStyle();
```

（3）生成布局树

Layout Tree ，有些 CSS 属性值如百分比， auto 到这里才能计算出来，content 的大小也在这里根据盒子模型进行计算。

遍历 DOM 树，根据样式计算出几何信息（尺寸、相对于包含块的位置），得到布局树，大部分时候 DOM 树和布局树会不同，因为：

- 隐藏的节点如 \<head\> 没有几何信息，不会出现在布局树中

- 伪元素是 CSS 产生的，不会出现在 DOM 树中，但会出现在布局树中

- 内容只能在行盒中，行盒、块盒不能在同一级，若出现了这些情况，布局树中会用匿名行盒、匿名快盒填充，这些匿名盒子是不会渲染的

布局中的对象也不是 DOM 对象，而是如浮动对象、flex 对象等，这些对象无法用 JS 获取，但是可以获取部分信息：

```
// offset 、client 、scroll 获取的都是布局树的信息
console.log(body.clientWidth);
```

（4）分层

渲染主线程使用一条复杂的规则进行分层，好处是在将来某一层改变时仅会处理该层，提升性能，但分层不会太多，因为会加大内存消耗，具体分几层由浏览器决定：

```
.box {
  /* 堆叠上下文的属性可能会影响分层，是否分层浏览器视情况而定，如以下属性 */
  opacity: 1;
  z-index: 9;
  transform: translate(-50%, -50%);

  /* 这个属性告诉浏览器可能会经常变动，需要单独分一层，但具体分不分，由浏览器决定 */
  /* 不要滥用，分层太多也不好 */
  will-change: transform;
}
```

（5）生成绘制指令

每一层单独生成绘制指令集，用来描述这一层如何绘制。

canvas 用的就是浏览器提供的绘制指令。

关于回流、重绘：

* 重绘（repaint）：当修改非几何属性如 color ，就引起 repaint ，在渲染流程中，重新计算样式后，跳过布局阶段，可能重新分层，一定生成新的绘制指令
- 回流（reflow）：也叫重排，当修改了几何属性后或新增、删除、移动元素、修改元素位置，就会 reflow ，渲染过程中和 repaint 唯一不同的就是会更新布局树，性能较差，所以 reflow 一定会 repaint ，反之不会

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <style>
      .box {
        font-size: 10px;
        transition: all 3s;
      }

      .text {
        font-size: 50px;
      }
    </style>
  </head>

  <body>
    <div>
      <button id="btn1">回流、重绘 1</button>
      <button id="btn2">强制回流、重绘 2</button>

      <div>
        <span class="text">456</span>
        <button id="btn3">变小后变大</button>
      </div>
    </div>
  </body>

  <script>
    var btn1 = document.querySelector("#btn1");
    var btn2 = document.querySelector("#btn2");
    var btn3 = document.querySelector("#btn3");
    const text = document.querySelector(".text");

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

      // 更好的方式是使用 raf ，效率高，原理是 raf 在渲染任务前回调，里面修改样式产生一个新的渲染任务，使得两个渲染任务的样式不同
      // requestAnimationFrame(() => {
      // box.style.fontSize = "50px";
      // box.style.backgroundColor = "#000";
      // });
    });

    // transition 同一时段只能有一次，于是下面的先变小后变大就变成了只有变大
    btn3.addEventListener("click", function () {
      text.style.fontSize = "25px";
      text.style.transition = "all 1s";

      // 效果：只有从 50px 到 100px ，实际上应该从 25px 开始
      // requestAnimationFrame(() => {
      //   text.style.fontSize = "100px";
      // });

      // 解决方法：先不设置 transition（设置了就去掉），到了第二段才开始动画
      text.style.fontSize = "25px";
      text.style.transition = "";

      requestAnimationFrame(() => {
        text.style.fontSize = "100px";
        text.style.transition = "all 1s";
      });
    });
  </script>
</html>
```

添加 DOM 的性能：

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

（6）合成线程

至此，渲染主线程工作结束，将每层的绘制指令交给渲染进程的合成线程。

* 分块：合成线程从线程池中启动多个线程，共同将每一层分成一个个小块，并把每一个小块交给 GPU 进程进行光栅化

* 光栅化：生成包含像素信息的位图（优先光栅化视口附近的分块），交换给合成线程，合成线程生成指引信息（指引把位图花在屏幕的位置），交给硬件

关于浏览器滚动：

浏览器滚动不会修改任何 DOM 和样式，只在合成线程中再次分块、光栅化就行，所以不会被 JS 阻塞，也不会回流重绘。

关于 transform ：

transform 都是对位图的数学矩阵运算，这个过程其实就发生在合成线程的光栅化，且 GPU 处理矩阵运算效率很高，整个过程都不会再渲染主线程中，不会回流重绘、所以性能很高。

transform 后的信息只能通过 getBoundingClientRect 获取。

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

# 三、TS

typescript 是 javascript 的超集，具有类型检查等功能。

安装；

```
npm install -g typescript @types/node

# 编译 ts 文件
tsc 1.ts
```

ts\-node ，直接编译运行 ts ：

```
npm install -g ts-node

# 运行 ts
ts-node xxx.ts
```

@types/xxx 是类型声明文件，当 TS 需要使用 JS 文件的资源时就需要声明文件，一些老的第三方库没有升级为 TS ，则会提供 @types/xxx ，若没有提供，则需要自己声明：

```
// utils.js
function add(a, b) {
  return a + b;
}
```

```
// 1.ts

import { add } from "./utils.js";

// declare 声明类型
export declare function add(a: number, b: number): number;

console.log(add(1, 2));
```

也可以单独把类型声明放到 \.d\.ts 文件中：

```
// utils.d.ts
export declare function add(a: number, b: number): number;
```

```
// 1.ts ，不需要导入 .d.ts 文件，会自动识别
import { add } from "./utils.js";
console.log(add(1, 2));
```

## 1 类型

### 1.1 基本

JS 类型在 TS 的写法：

```
// 声明变量 --------------------------------------------------------------------------
let num: number = 1;

// 类型转换
const num1: number = Number("2");

// err ，不能吧包装类对象赋值给 number 类型
// const num2: number = new Number(3);

// 包装类对象
const num3: Number = new Number(3);

// 类型检查 -------------------------------------------------------------------------
const str: string = "a";
const bool: boolean = true;
const u: undefined = undefined;
const n: null = null;
const sym: symbol = Symbol();

const obj: { a: number } = { a: 1 };

const arr1: numebr[] = [1, 2]
const arr2: Array<number> = [1, 2];

function func1(a: number): void {}
const func = function (a: number): number {
  return a;
};
const func3 = (a: number): number => a;

// err ，ts 具有类型检测，只能赋值相同类型的值
// num = 2;

// err ，不同类型无法比较
// console.log(num == str, num > str);

// err ，不同类型用 === 比较，始终为 false
// console.log(num === str);

// 若实在有比较不同类型的需求，可以先判断类型
if (typeof num === typeof str) {
}
```

type 可以给类型起别名：

```
type Obj = { a: number; b: number };

const obj: Obj = { a: 1, b: 2 };

// err ，type 无法重新赋值，无法输出
// Obj = string;
// console.log(Obj);
```

联合类型、获得并集，可以使用 keyof ：

```
// 联合类型 ------------------------------------------------------------------------------
type Test1 = number | string;

// type：string
type test2 = "a" | string;

// type：number
type Test3 = number | never;

// 联合类型，获得 obj 并集，并的是 obj 而不是 key ---------------------------------------------
type T1 = { a: number; b: number };
type T2 = { b: number; c: number };
type T3 = { b: string; c: number };
type U1 = T1 | T2;

// 只能是这三种，其他都是 err
const uo1: U1 = { a: 1, b: 2 };
const uo2: U1 = { b: 2, c: 3 };
const uo3: U1 = { a: 1, b: 2, c: 3 };

// 1 2 2 3
console.log(uo1.a, uo1.b);
console.log(uo2.b, uo2.c);
// 2
console.log(uo3.b);

// err ，并集后，只能使用 "b" ，因为 "a" 、"c" 不在另一个子集
// console.log(uo3.a, uo3.c);

// 若有相同的 key 且类型不同，则这个 key 的类型变成联合类型
// 相同的 key ，保留 readonly 和 ? ，因为并集
type U2 = { a: number; b: number } | { b: string; c: number };
const uo4: U2 = { a: 1, b: 2, c: 3 };
const uo5: U2 = { a: 1, b: "a", c: 3 };
```

交叉类型，获得交集；

```
// 交叉类型 ----------------------------------------------------------------------------
// type："a""
type Test4 = "a" | string;

// type：never
type Test5 = number & string;

// type：never
type Test6 = "a" | never;

// 交叉类型，获得 obj 焦集，交的是 obj 而不是 key ------------------------------------------------
type T1 = { a: number; b: number };
type T2 = { b: number; c: number };
type A1 = T1 & T2;

// 只能是这种情况，因为交集必须有两个子集的所有属性
const ao1: A1 = { a: 1, b: 2, c: 3 };

// 若有相同的 key 且类型不同，则这个 key 变成交叉后的结果，下面是 "2" & string
// 相同的 key ，去掉 readonly 和 ? ，因为交集
type T3 = { b: string; c: number };
type T4 = { b: "2"; c: number };
type A2 = T3 & T4;

const ao2: A2 = { b: "2", c: 3 };

// 混入，得到交叉类型
// type：{ a:number, b: never, c: number }
const ao3 = Object.assign({ a: 1, b: 2 }, { b: "2", c: 3 });
```

类型推断，当未指定类型时，会自动根据值推断出类型，开发中可以多用这种方式；

```
// type: number
let num1 = 1;

// type: 2 ，因为是 const 的基本类型敞亮，类型就被推断为字面量了
const num2 = 2;

// type: number[]
const arr1 = [1];

// type：(number | string)[]
const arr2 = [1, "a"];

// type：{ a: number }
const obj = { a: 1 };

// type：() => void
const func1 = () => {};

// type：() => number
const func2 = () => 123;

// 匿名函数指定了类型，就类型推断
const func3: (a: number) => void = (a) => {};

// 回调函数也会推断
type Fn = (a: number) => void;
const func4 = (fn: Fn) => {};
// type: a; number
func4((a) => {});
```

类型收缩，在运行时当分支中判断具体类型时，会自动收缩类型，这也叫类型守卫：

```
let method: "GET" | "POST";

// type："GET"
if (method === "GET") console.log(method);
// type："POST"
else if (method === "POST") console.log(method);

switch (method) {
  case "GET":
    // type："GET"
    console.log(method);
  case "POST":
    // type："POST"
    console.log(method);
}
```

类型断言，告诉编译器类型，谨慎使用：

```
// 类型断言 -------------------------------------------------------------------------
type T1 = { a: number; b: number };
type T2 = { b: number; c: number };
type Obj = T1 | T2;

const obj: Obj = { a: 1, b: 2, c: 3 };

// err ，并集只能使用 "b"
// console.log(obj.b);

// 梁总方式的类型断言
console.log((obj as T1).a);
console.log((<T2>obj).c);

// 非空断言 ----------------------------------------------------------------------------
type T3 = { a?: { aa: number } };

function func(obj: T3) {
  // warn ，obj.a 是可选参数，可能为 undefined
  // console.log(obj.a.aa);

  // 如果确定不为 undefined ，就可以用非空断言
  console.log(obj.a!.aa);
}
```

（2）TS 中与 JS 略有不同以及新增的类型

字面量类型：

```
// 字面量类型的值只能是这个字面量，相当于无法修改，成为一个敞亮
let num: 123 = 123;

// err
// num = 456;

let obj: { a: 1 } = { a: 1 };

// err
// obj = {};

// as const ，将成员转为字面量类型 -----------------------------------------------------
// 类型推断为 { a: string }
const obj1 = {
  a: "a",
};

// 类型推断为 { a: "a" }
const obj2 = {
  a: "a" as const,
};

// 放在最后面则所有成员变为字面量类型
// type；{ :: "a", b: "b" }
const obj3 = {
  a: "a",
  b: "b",
} as const;

// 类型推断为联合类型的数组
const arr1 = [1, "a"];

// type：[1, "a"] 的字面量元祖
const arr2 = [1, "a"] as const;
```

void 、undefined 、null ：

```
// void 的值只有 undefined 、null 两种，通常作为函数的空返回类型
const v1: void = undefined;
const v2: void = null;
const func = (): void => {};

// 但是 void 类型不 能赋值给 undefined 、null ，联合类型也不行
const v: void = null;
// err
// const u: undefined = v;
// const n: null = v;
// const un: undefined | null = v;

// undefined 、null 的值只有 undefined 、null 两种
const u1: undefined = undefined;
const u2: undefined = null;
const n1: null = null;
const n2: null = undefined;

// undefined 、null 是任何类型的子类型，所有类型都可以是这两种值
// 在 tsconfig.json 中也可以配置不允许这种情况，达到更严格的类型检查
const num1: number = undefined;
const num2: number = null;

// 但上述情况并不规范，可以使用联合类型
const num4: number | undefined = undefined;

// 为负值为 undefined
let num3: number;
console.log(num3);
```

any 、unknown ：

```
// any 可以是任何类型，不推荐使用，相当于关闭了类型检查
// 显示 any
const num1: any = "a";
// 隐式 any
let num2;

// unknown 是未知类型，有类型检查，相当于类型安全的 any
let num3: unknown;
num3 = 1;
num3 = "a";
// unknown 类型无法访问属性，而 any 可以
const obj: unknown = { a: 1 };
// err
// obj.a;

// any 类型的值可以赋值给任何的类型
const n1: number = num1;
// err ，unknown 类型的值只能赋值给 unknown 、any
// const n2: number = num3;

// 若 unknown 想要赋值给其他类型，，可以使用类型断言
const n3 = num3 as number;
const n4 = <number>num3;
```

never ，表示不存在的状态，或永远无法达到的状态：

```
// never 表示不存在的类型
// type：never ，不存在既是 number 又是 string 的类型
type T = number & string;

// 应用一，提高代码可维护性 --------------------------------------------------------------
type Method = "GET" | "POST";
// type Method = "GET" | "POST" | "DELETE";

const func1 = (method: Method) => {
  switch (method) {
    case "GET":
      break;
    case "POST":
      break;
    default:
      // 类型收缩，此时 method 只能是 never
      // 当给联合类型 Method 添加类型时，default 的类型收缩得到的就不是 never ，此时就会报错，不能把不是 never 的类型赋值给 never
      const tag: never = method;
      break;
  }
};

// 应用二，类型取反 ------------------------------------------------------------------
type Not<T, U> = T extends U ? never : T;

// number 取反，除了 number 的类型都接受
const func2 = <T>(a: Not<T, number>) => {};
func2("a");

// err
// func2(123);
```

### 1.2 对象、枚举、数组、函数

（1）对象

```
const oobj1: object = {};

const obj2: {
  a: number;

  // 只读属性
  readonly b: number;

  // 可选属性
  d?: number;

  // 索引签名，允许添加属性，xxx 可以是任何名字，只是一个描述，通常用 key
  // key 的类型可以是任何类型，但只是编译时，编译称 JS 后还是 JS 的规则
  // 索引签名可以用 readonly ，不能用 ?
  // 若未来需要删除必选属性，只能定义一个新对象类型
  [xxx: string | symbol]: any;
  // readonly [xxx: string | symbol]: any;
} = { a: 1, b: 2 };
```

（2）枚举

枚举enum，适合在几个值选择时使用：

```
// 枚举
enum Method {
  GET = 0,
  POST = 1,
}

// 数字枚举，若不给值，则从 0 开始
enum E1 {
  A,
  B,
  C,
}

// 数字增长枚举，无值的会是上一个值 + 1
enum E2 {
  A = 1,
  B = 5,
  C,
}

// 字符串枚举，每个都必须有值
enum E3 {
  A = "a",
  B = "b",
}

const method: Method = Method.GET;
const e1: E1 = E1.B;
const e2: E2 = E2.C;
const e3: E3 = E3.A;

// 0 1 6 "a"
console.log(method, e1, e2, "a");
```

枚举可以被 const 修饰，但不能使用 let 、var ：

```
const enum E1 {
  A = 0,
  B = 0,
}

enum E2 {
  A = 0,
  B = 1,
}

const e1: E1 = E1.A;
const e2: E2 = E2.A;

// 编译后不同，const 的枚举其实就是单纯赋值
// var E2;
// (function (E2) {
//   E2[(E2["A"] = 0)] = "A";
//   E2[(E2["B"] = 1)] = "B";
// })(E2 || (E2 = {}));
// var e1 = 0;
// var e2 = E2.A;
```

数字枚举的反向映射：

```
// 编译会有 E1["A"] = "a" 的过程
enum E1 {
  A = "a",
}

// 编译会有 E2[E2["A"] = 0] = "A" 的过程，就形成了反向映射
enum E2 {
  A = 0,
}

// { "a": "A", "A": 0 }
console.log(E2);

// err ，但是无法使用
// const e: E2 = E2["0"];
```

（3）数组

数组、伪数组：

```
// 数组，不定长度 --------------------------------------------------------------------
// 一维数组
const arr1: number[] = [];
const arr2: Array<number> = [];

// 二维数组
const arr3: number[][] = [];
const arr4: Array<Array<number>> = [];

// 多种类型的数组
const arr5: (number | string)[] = [];

// 伪数组 ，number 、string 都行，nember 更直观一点
// arguments 的类型就是 Arguments
type Arr1 = {
  [index: number]: any;
};

// 数组对象都行，只是对象的 key 要写成 number
const arr6: Arr1 = [];
const tup1: Arr1 = [];
const obj1: Arr1 = {};
const obj2: Arr1 = { 0: "a" };

// string 也行
type Arr2 = {
  [index: string]: any;
};

const arr7: Arr2 = [];
```

元祖：

```
// 元祖、固定长度，且每个元素都固定类型 -------------------------------------------------
const tup: [number, string, boolean] = [1, "a", true];

// 形参列表也是元祖，"a" 、"b" 只是标识作用
const args: [a: number, b: string] = [1, "a"];

// 元祖数组
const tupArr: [number, string][] = [];

// TS 只有元祖可以使用扩展运算符，数组类型、对象类型无法使用 -------------------------------------
type T1 = [number, string];

// type：[number, string, boolean]
type T2 = [...T1, ...[boolean]];
```

（4）函数

```
const func1: Function = () => {};

// 可以设置可选参数，必须放在必选参数后，剩余参数前
// 设置了默认值就是可选参数了，不用加 ?
const func2 = (a: number, b?: number, ...args: any[]) => {};

// 使用元祖实现前置不定量参数
function func3(...args: [...preArgs: any[], a: number]) {}
func3("a", 1);
func3("a", "b", 1);
```

函数重载，只能重载具名函数：

```
// 多个函数签名
function func(): number;
function func(a: string): string;
function func(a: boolean): boolean;
function func(a: number, b: number): void;

// 实现只能有一个，且类型必须涵盖所有重载
function func(
  a?: number | string | boolean,
  b?: number
): number | string | boolean | void {
  // 类型守卫
  if (typepf a === "undefined" && typeof b === "undefined") return 123;
  else if (typeof a === "string") return "asdf";
  else if (typeof a === "boolean") return true;
  else if (typeof a === "number" && typeof b === "number") return;
}

func();
func("a");
func(true);
func(1, 2);
```

对象、class 内的函数重载：

```
// type 也行，只是 class 只能实现接口
interface Obj {
  func(): number;
  func(a: string): string;
}

function func(a?: string): any {
  if (typeof a === "undefined") return 123;
  else if (typeof a === "string") return "asdf";
}

const obj: Obj = { func };

class A implements Obj {
  public func = func;
}
```

当函数形参是子类型，而实参是父类型无法传入时，可以用重载解决：

```
type Method = "GET" | "POST";

function func1(method: Method) {}

// 正常
func1("GET");

// err ，因为 obj 的 method 类型推断为 string ，string 无法传给子类型 "get" | "post"
const obj = { method: "GET" };
// func1(obj.method);

// 方法一，用类型断言解决 ---------------------------------------------------------
func1(obj.method as Method);

// 方法二，函数重载 -----------------------------------------------------------------
// 类型守卫函数，本来返回值是 boolean ，使用 is 后有更好的提示
function isMethod(value: any): value is Method {
  return value === "GET" || value === "POST";
}

function func2(method: Method): any;
function func2(method: string): any;
function func2(method: any) {
  if (!isMethod(method)) new Error();
}

func2(obj.method);
```

### 1.3 其他

（1）JS 内置对象的额类型

```
const reg: RegExp = /1/;

const date: Date = new Date();
const now: number = Date.now();

const err: Error = new Error();

const set = new Set<number>([1, 2]);
const map = new Map<string, number>([["a", 1]]);

const ite: () => ArrayIterator<number> = [1, 2][Symbol.iterator];

new Promise<number>((resolve, reject) => {
  resolve(123);
});
```

（2）DOM 、BOM 类型

```
const body: HTMLElement = document.body;

const div: HTMLDivElement = document.querySelector("#box");

const items: NodeList = document.querySelectorAll(".item");

div.addEventListener("click", function (e: MouseEvent) {});

const t1: NodeJS.Timeout = setTimeout(() => {});
```

## 2 类、接口

### 2.1 类

（1）基本

与 JS 略有不同：

```
class Person {
  // 省略默认为 public
  public name: string;
  private age: number;
  protected password;

  // readonly 只能修饰属性
  public readonly sex;

  // 多个修饰符一起使用
  public static readonly xxx;

  constructor(name: string, age: number) {
    this.name = name;
    this.age = age;

    // err ，设置的属性必须已经在类内声明
    // this.a = 1;
  }
}

const obj: Person = new Person("asdf", 18);

// "asdf"
console.log(obj.name);

// err ，无法访问 private 属性
// console.log(obj.age);

// 但 private 不是 ES13 的 # 语法层面上的约束，只是类型检查而已，而下面这种方式就能访问 private 属性
console.log(obj["age"]);
```

构造函数可以简写：

```
class Person {
  // 声明并赋值，除了 static 外都可以
  constructor(
    public name: string,
    private age: number,
    protected password: string,
    public readonly sex
  ) {}
}

const obj = new Person("asdf", 18, "123456", "male");
console.log(obj);
```

（2）装饰器

类似于面向切面编程，若报错，则说明该语法还在实验阶段，需要在 tsconfig\.json 配置：

```
{
  "compilerOptions": {
    "target": "ES5",
    "experimentalDecorators": true
  }
}
```

使用：

```
// 类装饰器
const classDes1: ClassDecorator = (target: Function) => {
  // target 为类的构造函数，可以给原型添加属性方法
  target.prototype.a = 1;
};
const classDes2 = (target: any) => {};

// 属性装饰器
const propDes: PropertyDecorator = (target: any, propName: string) => {
  // target 是类的原型
};

// 方法装饰器
const funcDes: MethodDecorator = (
  target: any,
  funcName: string,
  tag: PropertyDescriptor
) => {
  // target 是类的原型，tag 是修饰符如 public
};

// 参数装饰器
const paramsDes: ParameterDecorator = (
  target: any,
  funcName: string,
  paramsLoc
) => {
  // target 是类的原型，paramsLoc 是参数在形参列表的索引
};

// 可以同时用多个装饰器
@classDes1
@classDes2
class A {
  // @propDes
  public name: string;

  @funcDes
  public func(@paramsDes a: number) {}
}

const obj = new A();
console.log((obj as any).a);
```

装饰器工厂：

（3）控制反转

控制反转（Inversion of Control，IoC）是面向对象的一种设计原则，可以降低代码之间的耦合度，最常见的一种实现方法是依赖注入（Dependency Injection，DI）。

依赖注入就是在创建对象时，将该对象所依赖的其他对象通过参数、属性等方式传递进去，而不是让该对象自己去创建这些依赖对象。这样做的好处是，使得对象之间的依赖关系更加清晰，降低代码的耦合度，同时也更容易进行单元测试和模块化设计。

```
// 未使用依赖注入的例子 ---------------------------------------------------------------------
// B 类使用 A 类的属性方法，如果修改了 A 类，就需要改动 B 类，形成了耦合
class A {
  constructor(public name: string) {}
}

class B {
  public name: string;

  constructor() {
    this.name = new A("asdf").name;
  }
}

const obj1 = new B();
console.log(obj1.name);

// 使用依赖注入 ----------------------------  ----------------------------------
// 定义一个依赖注入容器
class Container {
  private module: any;

  constructor() {
    this.module = {};
  }

  public provide(key: string, instance: any) {
    this.module[key] = instance;
  }

  public inject(key: string) {
    return this.module[key];
  }
}

const container = new Container();

// 使用
class C {
  constructor(public name: string) {}
}

container.provide("class_A_instance", new A("asdf"));

class D {
  public name: string;

  constructor(instance: string) {
    this.name = container.inject(instance).name;
  }
}

const obj2 = new D("class_A_instance");
console.log(obj2.name);
```

（4）抽象类

当父类涵盖的范围比较大，具体的属性方法不好定义，而且我们也不想实例化这个父类，这时候，就可以使用抽象类，专门用来做继承。抽象类不能被实例化。

抽象类可以有普通类的属性方法构造器，抽象类内还可以写抽象方法

抽象方法：

- 抽象方法，只定义方法的结构，不做具体实现，若不知道方法具体要怎么实现，就先不实现，使用抽象方法

- 抽象方法没有方法体，只能在抽象类/接口内定义，继承的子类必须重写抽象方法来实现

```
abstract class Person {
  public abstract func: (a: number) => void;
}

class A extends Person {
  // 抽象方法必须重写
  public func = (a: number): void => {};
}
```

### 2.2 接口

接口用来定义类或对象的结构，和 type 的区别：

* 接口只能定义对象类型，而type 可以定义任何的类型

* 接口可以重复声明，type 不行

* 接口可以继承，而 type 不行，但type 也可以用交叉类型实现类似效果

和抽象类的区别：

* 接口的属性不能初始化，而抽象类可以

* 接口的方法不加 abstract 但都是抽象方法，而抽象类可以有普通方法

* 接口的属性方法不能加除 readonly 外的修饰符，而抽象类都可以加

```
interface A {
  name: string;
  func(): void;
}

/**若重复声明接口
 * 相同的属性类型、readovly、是否可选必须一样；会加上没有的属性
 * 相同的方法会被忽略，不会重载
 */
interface A {
  name: string;
  age: number;
  func(a: number): void;
}

interface B {
  age: string;
  sex: "male";
}

// 给对象使用
const obj: A = {
  name: "asdf",
  age: 18,
  func() {},
};

// class 实现接口，可以多实现，相当于接口的交叉类型
class Person implements A, B {
  constructor(public name: string) {}
  public age: never;
  public sex: "male";
  public func() {}
}

// 类可以在继承的同时实现接口，也是相当于交叉类型
// 类无法多继承
interface C {
  sex: string;
}
class Child extends Person implements C {
  public sex: "male";
}
```

接口扩展，即继承：

```\
interface A {
  name: string;
  func(): void;
}

interface B {
  age: number;
}

// 可以多继承，若有相同的属性则类型必须相同
interface C extends A, B {
  // err ，若子接口有相同的属性，则类型必须相同，只能从可选变成必选（反之不行），readonly 无所谓
  // age: string;
  // age?: number;

  // err ，子接口不能有同名方法，即不能重写
  // func(a: number): void;

  sex: boolean;
}

const obj: C = { name: "asdf", age: 18, sex: true, func() {} };
```

## 3 泛型

### 3.1 基本

用于建立类型的联系：

```
function func1<T>(a: T) {}

const func2 = <T>(a: T, b: T) => {};

// 可以使用多个泛型，也可以设置默认类型如 <T = number>
function func3<T, U>(a: T, b: U) {}

// 传入类型
func1<number>(123);
func3<number, string>(1, "a");

// 不传入则类型推断，推断第一个 T 后，后面的所有 T 也会适用
func2(123, 456);

// class 、。interface 、type 也可以使用泛型
class Person<T> {}

interface Int<T> {}

type T1<T> = T;
```

泛型约束，限制泛型只能是某个范围内的类型：

```
// 限制 T 必须是引用类型 --------------------------------------------------------------
function func1<T extends object>(obj: T) {}

func1([]);

// err
// func1(123);

// 限制 K 必须是 T 的 key -------------------------------------------------------------
function func2<T extends object, K extends keyof T>(obj: T, key: K): any {
  return obj[key];
}

// T 、K 都自动推断出来了
func2({ a: 1 }, "a");

// 类型取反 -------------------------------------------------------------------------------
type Not<T, U> = T extends U ? never : U;

// 除了 number 外的类型都可以
function func3<T>(a: Not<number, T>) {}

func3("123");

// err
// func3(123);
```

泛型应用举例，MySQL 和 MongoDB 的操作可能不同，可以统一一下：

```
interface DB<T> {
  add(info: T): boolean;
  update(info: T, id: number): boolean;
  get(id: number): boolean;
  delete(id: number): boolean;
}

class MySQL<T> implements DB<T> {
  public add(info: T): boolean {
    return true;
  }

  public update(info: T, id: number): boolean {
    return true;
  }

  public get(id: number): boolean {
    return true;
  }

  public delete(id: number): boolean {
    return true;
  }
}

class MongoDB<T> implements DB<T> {
  public add(info: T): boolean {
    return true;
  }

  public update(info: T, id: number): boolean {
    return true;
  }

  public get(id: number): boolean {
    return true;
  }

  public delete(id: number): boolean {
    return true;
  }
}
```

### 3.2 类型安全

（1）子类型

泛型约束 extends 判断是否是子类型，子类型如：

```
interface Parent {
  name: string;
}

interface Child extends Parent {
  age: number;
}

// type：Child ，Child 是 Parent 的子类型
type T1 = Child & Parent;

// type: "a" ，"a" 是 string 的子类型"
type T2 = "a" & string;

// type："a" ，"a" 是 "a" | "b" 的子类型
type T3 = ("a" | "b") & "a";

type O1 = { a: number };
type O2 = { b: number };
// type：O1 & O2 ，交叉类型是联合类型的子类型
type T4 = (O1 & O2) & (O1 | O2);

// type：any[] ，数组是对象的子类型
type T5 = any[] & object;

// type：[] ，空数组、元祖是数组的子类型
type T6 = [number] & any[];

// type：never [number] ，元祖的子类型只能是自己
type T7 = [] & [number];
type T8 = [number] & [number];

// 泛型约束长度为 n 的元祖时，需要得到 n-1 ，n-2 ... [] 的联合类型 -------------------------------
type SubArgs<A extends any[]> = A extends [...infer PA, any]
  ? A | PA | SubArgs<PA>
  : [];

// type：[] | [number] | [number, string]
type T9 = SubArgs<[number, string]>;

// 测试元祖的泛型约束 extends
type T10<Tup extends any[], SubTup> = SubTup extends SubArgs<Tup>
  ? SubTup
  : never;

// type：[number] ，可以正确判断
type T11 = T10<[number, string], [number]>;
```

（2）类型安全

类型安全，保证成员始终可用：

```
interface Parent {
  name: string;
}

interface Child extends Parent {
  age: number;
}

// 协变，父类型只能接受子类型，反之不行 -------------------------------------------------------
const c: Child = { name: "c", age: 1 };

// 类型安全，p 只需要调用 name
const p: Parent = c;

// err ，类型不安全，因为可能没有 age
// const cc: Child = p;

// 逆变，协变反过来，但其实还是协变，如下只要关注函数参数，保证类型安全即可 -----------------
type ReadParent = (p: Parent) => any;
type ReadChild = (c: Child) => any;

const readParent: ReadParent = (p: Parent) => {};
const readChild: ReadChild = (c: Child) => {};

// 类型安全，因为 readC 传入的是 Child ，接收的是 Parent
const readC: ReadChild = readParent;
// 在 readParent 逆变为 { name: "child" }
readChild({ name: "child", age: 1 });

// 类型不安全，readP 传入的是 Parent ，接收的是 Child
// const readP: ReadParent = readChild;

// 如果是返回值，就又是协变了，因为要传给外部 ---------------------------------------------
type GetParent = () => Parent;
type GetChild = () => Child;

const getParent: GetParent = () => ({ name: "parent" });
const getChild: GetChild = () => ({ name: "child", age: 1 });

// 类型安全
const getP: GetParent = getChild;

// 类型不安全
// const getC: GetChild = getParent;

// 如果参数和返回值都有，优先协变 ---------------------------------------------------------
type Func = (p: Parent) => Parent;
type SubFunc = (c: Child) => Child;

const func: Func = (p: Parent) => ({ name: "name" });
const subFunc: SubFunc = (c: Child) => ({ name: "child", age: 1 });

// 虽然是协变不报错，但是参数船进去会有问题，因为也存在逆变
const f: Func = subFunc;

// err
// const sf: SubFunc = func;
```

逆变的应用：

```
/**联合类型转交叉类型
 * 第一步得到 ((x: Obj1) => any) | ((x: Obj2) => any)
 * 第二部本该得到 O1 | O2 ，但由于函数参与了运算，逆变成子类型 O1 & O2
 */
type Obj1 = { a: number };
type Obj2 = { b: number };

type UnionToIntersection<U> = (U extends any ? (x: U) => any : never) extends (
  x: infer R
) => any
  ? R
  : never;
// type：O1 & O2
type T1 = UnionToIntersection<Obj1 | Obj2>;

// 元祖转联合类型 -----------------------------------------------------------------
type LastOf<T> = UnionToIntersection<
  T extends any ? () => T : never
> extends () => infer R
  ? R
  : never;

type Push<T extends any[], V> = [...T, V];

type UnionToTuple<T, L = LastOf<T>> = [T] extends [never]
  ? []
  : Push<UnionToTuple<Exclude<T, L>>, L>;

// type：["a", "b"]
type T2 = UnionToTuple<"a" | "b">;

// 元祖转联合类型
type T3 = T2[number];
```

### 3.3 类型运算

（1）type

```
type Obj = { a: number };

// type：number ，可以用索引获取类型，若不存在则 err
type ObjA = Obj["a"];

// type：string ，数组类型用 number 类型作索引得到元素的类型
type ObjK = string[][number];

// 配合泛型约束 extends 可以用三目运算符
type Not<T, U> = T extends U ? never : U;

// typeof value ，获取值的类型
const obj = { a: 1 };
const f = () => {};
type Obj1 = typeof obj;
type F = typeof f;

// 具名函数和 class 构造函数的类型也可以用 typeof 获取
function func() {}
class A {}
type Constructor1 = typeof func;
type Constructor2 = typeof A;
```

（2）keyof

```
type Obj = { a: number; b: number };

// 得到所有 key 形成的联合类型 ----------------------------------------------------------
// type："a" | "b"
type K1 = keyof Obj;

// type：string | symbol | number ，内置类型有些是对象类型
type K2 = keyof any;
type K3 = keyof never;

// 得到一堆 key 形成的联合类型，因为也是对象类型
// number ，string ，boolan ，symbol
type K4 = keyof number;

// type："length" | ... 等等
type K5 = keyof Number[];

// type："0" | "1" | "length" | ... 等等
type K6 = keyof [number, string];
type K7 = keyof [a: number, b: number];

// type：never
type K8 = keyof unknown;
type K9 = keyof void;
type K10 = keyof null;
type K11 = keyof undefined;
```

（3）\|

前置的 \| 会分开运算，如：

```
// 联合类型、交叉类型运算 --------------------------------------------------------------
// type："a" | "b" ，等价于 ("a" & string) | ("b" & string) | (1 & string)
type T1 = "a" | "b" | (1 & string);

// 去掉 Symbol key
// type："a"
type T2 = keyof { a: number; [sym: symbol]: number } & string;

// 模板字符串，只能用于字面量字符串类型，通常配合联合类型，运算规则和上面一样
// symbol 无法做任何运算，所以也会配合 T2
// type："mouseEvent" | "inputEvent"
type T3 = `${"mouse" | "input"}Event`;

// 联合类型、extends 运算 ----------------------------------------------------------
type MyExclude<T, U> = T extends U ? never : T;

/**type："a" | "c"" ，等价于：
 * ("a" extends "b") ? never : "a" |
   ("b" extends "b") ? never : "b" |
   ("c" extends "b") ? never : "c"
 */
type T4 = MyExclude<"a" | "b" | "c", "b">;
```

（4）in

```
// 映射类型，便利一个联合类型并得到各个 key ，相当于反向 keyof -------------------------------
type T1 = {
  // 设置了映射类型就不能设置其他 key
  // 可以用 readonly 和 ? 修饰
  [xxx in "a" | "b"]: number;

  // 与上面等价，有 & 就先运算为联合类型
  // [xxx in "a" | ("b" & striung)]: number;
};
const obj: T1 = { a: 1, b: 2 };

// type：number ，内置类型有些也是对象类型，下面这么做其实还是得到 number
type T2 = {
  [key in keyof number]: number[key];
};
const num: T2 = 123;

// 数组也是一样得到数组
type Tup = [number, string];
type T3 = {
  [Index in keyof Tup]: Tup[Index];

  // 两种等价，比起上面少了 "length" 等
  // [Index in "0" | "1"]: Tup[Index];
  // [Index in 0 | 1]: Tup[Index];
};
const tup: T3 = [1, "a"];

// 可以起别名和过滤属性
type T4 = {
  // type：{ keyA: any, keyB: any } ，Capitalize 是字面量字符串首字母大写的内置泛型工具
  // [key in "a" | "b" as `key${Capitalize<key>}`]: any;

  // type：{} ，key 为 never 就去掉
  // [key in "a" | "b" as never]: any;

  // type：{ a: any, c: any } ，筛选属性
  [key in "a" | "b" | "c" as key extends "a" | "c" ? key : never]: any;
};
```

（5）infer

借助 TS 的类型推断，设计类型工具：

```
// 获取函数返回值类型
type Reture<T> = T extends (...args: any[]) => infer R ? R : T;
// type：number
type R = Reture<() => number>;

// 获取函数第一个形参的类型
type First<T> = T extends (first: infer F, ...args: any[]) => any ? F : T;
// type：number
type F1 = First<(a: number) => void>;
// type：unknown
type F2 = First<() => void>;

// 获取数组元素的类型
type ArrayType<T> = T extends (infer U)[] ? U : T;
// type：number
type U1 = ArrayType<number[]>;
// type：number | string
type U2 = ArrayType<[number, string]>;

// 获取元祖首尾元素形成的联合类型，可以配合扩展运算符
type TupleFirst<T> = T extends [infer first, ...infer args, infer last]
  ? first | last
  : T;
// type：number | boolean
type TU1 = TupleFirst<[number, string, boolean]>;

// 获取元祖剩下的元素
type RemainArgs<A extends any[], PA extends PreArgs<A> | A> = A extends
  | [...PA, ...infer Reamin]
  | A
  ? Reamin
  : A;
// type：[a: number, c:number]
type TU2 = RemainArgs<[a: number, b: number, c: number], [a: number]>;

// 递归 infer --------------------------------------------------------------------------
// 多维数组需要递归
type DeepArrayType<T> = T extends (infer F)[] ? DeepArrayType<F> : T;
// type：number
type D = DeepArrayType<number[]>;

// 获取 Promise resolve 的类型，因为 resolve 的参数肯呢还是 Promise ，所以需要递归 infer
type PromiseType<T> = T extends Promise<infer V> ? PromiseType<V> : T;
// type：number
type V = PromiseType<Promise<Promise<number>>>;

// 翻转元祖类型
type ReverseTuple<T> = T extends [infer first, ...infer args]
  ? [...ReverseTuple<args>, first]
  : T;
// type：[string, number]
type rt = ReverseTuple<[number, string]>;
```

### 3.4 Utility Types

TS 内置的类型工具。

（1）基本

```
// 筛选联合类型的某些类型
// type："a" | "b"
type T1 = Extract<"a" | "b" | "c", "a" | "b">;
type MyExtract<T, U> = T extends U ? T : never;

// 去掉联合类型的某些类型
// type："a" | "b"
type T2 = Exclude<"a" | "b" | "c", "c">;
type MyExclude<T, U> = T extends U ? never : T;

// 去掉联合类型的 null 和 undefined
// type：number
type T3 = NonNullable<number | null | undefined>;
type MyNonNullable<T> = T extends null | undefined ? never : T;
```

（2）函数相关

```
// 获得返回值类型
// type：number
type T1 = ReturnType<() => number>;
type MyReturnType<T> = T extends (...args: any[]) => infer R ? R : T;

// 获得形参列表
// type：[a:number, b:number]
type T2 = Parameters<(a: number, b: number) => void>;
type MyParameters<T> = T extends (...args: infer A) => any ? A : never;

// 获得构造函数实例化对象的类型 ---------------------------------------------------------
class Obj {
  public a: number = 1;
}

// type：{ a: number }
type T3 = InstanceType<typeof Obj>;
type MyInstanceType<T> = T extends new (...args: any[]) => infer R ? R : T;
```

（3）对象类型相关

```
// 所有属性变成可选属性
// type：{ a?: number}
type T1 = Partial<{ a: number }>;
type MyPartial<T> = { [key in keyof T]?: T[key] };

// 所有属性变成必选属性
// type：{ a: number }
type T2 = Required<{ a?: number }>;
type MyRequired<T> = { [key in keyof T]: T[key] };

// 所有属性变成 readonly
// type：{ readonly a: number }
type T3 = Readonly<{ a: number }>;
type MyReadonly<T> = { readonly [key in keyof T]: T[key] };

// 筛选需要的对象属性
// type: { a: number, b: number }
type T4 = Pick<{ a: number; b: number; c: number }, "a" | "b">;
type MyPick<T, K extends keyof T> = { [key in K]: T[key] };

// 去掉不需要的对象属性
// type：{ c: number }
type T5 = Omit<{ a: number; b: number; c: number }, "a" | "b">;
type MyOmit<T, K extends keyof any> = Pick<T, Exclude<keyof T, K>>;

// 生成一个所有 key 都是相同 value 的类型
// type：{ a: number, b: number }
type T6 = Record<"a" | "b", number>;
type MyRecord<K extends keyof any, T> = { [key in K]: T };
```

（4）自定义

```
// 部分可选
type SubPartial<T, K extends keyof T> = Partial<Pick<T, K>> & Omit<T, K>;
// type：{ a?: number, b?:number, c:number }
type T1 = SubPartial<{ a: number; b: number; c: number }, "a" | "b">;

// 深度可选
type DeepPartial<T> = {
  [key in keyof T]: DeepPartial<T[key]>;
};

// 筛选出可选属性，{} 是 {a?: any} 的子类型
type PickPartial<T extends object> = {
  [key in keyof T as {} extends Pick<T, key> ? key : never]: any;
};
// type：{ a?: number }
type T2 = PickPartial<{ a?: number; b: number }>;
```

## 4 模块、配置

（1）模块

node 环境也可以直接使用 ESM ：

```
// 2.ts

export let a = 1;
export type T1 = number;
```

```
// 1.ts

// 不要加后缀 .ts ，会自动识别，加了就 err ，因为编译后 JS 文件导入 TS 就出错了
import { a } from "./2";

// 不加 type 也可以导入类型，加了有更好的类型提示
import type { T1 } from "./2";

// 一起导入时也可以加上 type 同样的也可以不加
// import { a, type T1 } from "./2";

// 如果没有导入，点击快速修复也能加上导入语句，前提不能是 export default ，因为需要知道名字
console.log(a);
```

如果使用 CommpnJS ，会失去类型提示，全部变成 any ，需要改一下代码：

```
// ts

let a = 1;

// 失去类型提示
// module.exports = { a };

// 修改后
export = { a };
```

```
// 1.ts

// 失去类型提示
// const { a } = require("./");

// 修改后
import MyModule = require("./2");

// 1
console.log(MyModule.a);
```

命名空间，可以实现内部模块，内部是独立的作用域，其实编译成 JS 后就是立即执行函数：

```
namespace A {
  export type T1 = number;
  export let a = 1;
}

// 重复声明则加上没有的 export 资源，export 的资源不能相同，否则 err
namespace A {
  export let b = 2;
}

namespace B {}

// { a: 1, b: 2 } 1
console.log(A, A.a);
// err ，空的 namespace 不会编译
// console.log(B);

// 可以嵌套
namespace C {
  export namespace CC {
    export let a = 1;
  }
}

// { CC: {a: 1} }
console.log(C);

// 起别名
import CCa = C.CC.a;
// 1
console.log(CCa);

// 也可以 export 给其他文件使用
exports = {
  A,
  C,
};
```

（2）配置

tsconfig\.json ，与其他 json 文件不同的是这个可以写注释：

```
{
  "compilerOptions": {
    // 编译的 JS 版本，默认是 ES3
    "target": "ES5",
    // 去掉编译后的注释，默认 false
    "removeComments": true,

    // 模块解析方式，默认 node ，老版本是 classic
    "moduleResolution": "node",
    // 编译后的模块化语法，默认跟随 TS 代码
    "module": "es2015",
    // 是否允许导入时加上 .ts ，默认 false
    "allowImportingTsExtensions": false,

    // 开启所有严格的类型检查（如不允许 null 和 undefined 为子类型），默认 false
    // 也可以单独设置各种类型检查，默认部分为 true
    // 注意，这些只是编码时的提示，不影响编译
    "strict": true
  }
}
```

有时候可以临时关闭类型检查：

```
const a: number = 1;

// 只有下面一行会关闭类型检查
// @ts-ignore
const b: string = a;
```
