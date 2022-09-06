npm i -g typescript

tsc 查看是否安装成功

tsc xxx.ts   编译出js文件

tsc xxx.ts -w  观察模式，代码已修改就自动编译（单个文件）

tsc编译ts文件后生成js文件，还需要运行js文件才能看到效果，比较麻烦，使用ts-node能够一键编译运行

```
npm install -g ts-node
npm install --save-dev @types/node
ts-node xxx.ts
```

ts.config.json   ts的编译配置文件

有了这个文件后，tsc 就会编译所有ts文件，tsc -w 就会观察所有ts文件的修改

默认情况下，ts编译成es3，且报错后也会编译，可以自己进行配置

ts是js的超集，具备类型，语法检查更方便

js类型是大写开头，而ts是小写开头

# 一、类型

给变量声明数据类型，赋值时只能赋值对应的数据类型

## 1 基本使用

```
let a: number
let b: number = 5
let c = 5   //这样ts会自动给变量number类型
let d; symbpl = Symbol(123)
```

ts中应当尽量避免不同类型的值进行比较，==和===的效果一样了都是先检查类型，如果类型不同，==会得到false

编译器可能会报错 ‘该条件始终为false’

```
let a: number = 123
let b: string = '123'
console.log(a == b)
console.log(a === b)

//若实在有比较不同类型的需求，可以先比较类型，再比较值
if(typeof a === typeof === b){
  if(a === b){}
}
```

## 2 基本类型

js对应的类型是大写开头，而ts对应的类型是小写开头

### 2.1 number,string,boolean,symbol

```
let a: number = 5    //其他进制、NaN，Infinity等都是number类型
let b: string = 'aaa'
let c: boolean = true
let d: symbol = Symbol(123)
```

也能通过构造函数赋值

```
let a: number = Number(5)
//let a: number = new Number(5)  //报错，因为生成的是对象类型，不能赋值给number类型

let b: Number = new Number(5)  //Number是Number对象类型
console.log(b.valueOf())
```

### 2.2 undefined,null,void

```
//void，值只有null和undefined两种，通常作为函数返回值的类型
let v1: void = null
let v2: void = undefined


//undefined
/*
null，它们是所有类型包括void的子类型，计所有类型都可以赋值为null，undefined
undefined类型和null类型都有且只有两种值，undefined和null
与js一样，未赋值的变量输出并不会报错，值为undefined，但这不规范，如number类型的值不应该是undefined
若值有number或undefined等类似情况，可以用联合类型
*/
let a1: number = null
let a2: number = undefined
let b1: undefined = undefined
let b2: undefined = null
let c1: null = null
let c2: null = undefined
let d: number | undefined | null = null

//void类型的变量只能赋值给void类型的变量，而undefiend可以和null类型的变量可以赋值给其他类型的变量
let aaa: void = null
let bbb: void = aaa  //正确
//let ccc: null = aaa   //报错
//let ddd: number = aaa //报错

let xxx: null = null
let yyy: undefined = xxx
let zzz: void = xxx
let mmm: number = xxx
```

为了实现更严格的类型检查，在tsconfig.json配置文件中，

### 2.3 字面量类型

字面量也能作为类型，值职能是这个类型，声明后不能修改，相当于常量

对象属性的键的类型也是字面量类型

```
let a: 5
let b: 'aaa'
a = 5
b = 'aaa'
```

### 2.4 any,unknown

any和unknown是ts的顶级类型

any，表示任意类型，相当于关闭了类型检查（不建议使用，不然使用ts就没意义了）

unknown，表示未知类型，推荐用来替代any，相当于类型安全的any

```
let a1: any = 'hello'  //显式any
let a2                 //隐式any
let b1: unknown = '123'
//可以再次赋值其他类型的值
a1 = 5
b1 = 7

/*any，unknown区别
1.类型检查的区别
2.any类型变量可以赋值给其他任何的类型的变量，而unknown类型的变量只能赋值给any类型变量或unknown类型变量
3.unknown类型变量若是对象，无法访问里面的属性和方法，而any可以
*/
let c1: string = a1  //成功
// let c2: string = b1 //报错
//若确定unknown是什么类型，需要赋值时的办法
let c3: string = b3 as string  //类型断言，告诉编译器我就是string类型(注意，若b3不是string，也会赋值成功，但类型不是string而是真正的类型)
let c4: string = <string>b3    //类型断言另一组写法

let d1:any = {a: 123}
let d2:unknown = {a: 123}
console.log(d1.a)   //正确
//console.log(d2.a) //报错
```

### 2.5 never

表示不存在的状态，或永远无法达到的状态

```
//报错,因为不可能同时是number又是string，推论为never类型并报错
let a: number & string

//返回类型never表示从来没有返回值，如异常了代码直接停止运行，自然没有返回值
function f3(): never{ 
  throw 'never'
}
function f3(): never{ 
  while(true){}
}

/*实际应用
作为兜底逻辑，如switch的default里面never作为兜底逻辑，若到了default则会因为never
而报错，需要修改代码
*/
```

## 3 对象

```
//因为js中number，string甚至函数都是对象，所以这样写其实没什么意义
let obj: object;

//通常这样指定对象类型
let obj1: {
  name: string,
  readonly age: number  //只读属性，不能修改
  job?: string          //表示为可选属性，赋值时可赋可不复
}
//注意赋值时，属性必须是对应类型，且属性数量必须给全(可选属性除外)
obj1 = {
  name: 'lgx',
  age: 23
}

//由于对象的类型已经给定了，所以无法增加、删除属性
//若不知道该对象未来有多少属性，表示属性名为字符串，属性值为any类型
let obj2: {
  name: string, 
  [xxx: string]: any  //xxx任意起名，any也可以换成其他类型
}
obj2 = {name: 'lgx',a:'5',b:55}
```

## 4 数组、元组、枚举

ts的数组里面都是相同的类型(所以不建议使用any)，有两种声明方式

```
let arrStr: string[]
let arrNum: Array<number>
arrStr = ['a','f']
arrNum = [5,8]
//多维数组
let xy: number[][] = [[1,2]]
let ab: Array<Array<number>> = [[1,2]]
//接口来实现数组，通常用来实现伪数组
interface myArr {
  [index: number]: number
}
let a:  myArr = [1,2]
//函数arguments是伪数组，类型为IArguments
function(a:number, b:number){
  let arg: IAguments = arguments
}
```

元组tuple，即固定长度，类型不同的元素组合，是数组的变种，每个元素的类型可以不同

```
let tup: [string,number]
//赋值时，类型和长度必须一样
tup = ['hh',55]
//每个元素会被推断为联合类型 string | number
tup.push(true) //报错，不能把boolean赋值给 string | number
//经典应用
let excel: [string,number][] = [
    ['lgx',23]
]
```

枚举enum，适合值在几个值选择时使用

```
//自定义数字枚举
enum sexVal {
  Male = 0,
  Female = 1
}
let o: {name: string,sex: sexVal}
o = {name: 'lgx',sex: sexVal.Male}

//数字枚举，若不给值，则自动重上到下一次从0开始赋值
enum aaa {
  red,   //0
  green, //1
  blue   //2
}

//数字枚举的增长枚举，给第一个赋值，其他的根据这个值一次递增
enum aaa {
  red = 2,   
  green, //3
  blue   //4
}

//字符串枚举，值全部要给，值全部是字符串则是字符串枚举，值可有数字或字符串则是异构枚举
enum aaa {
  a = 'aaa',
  b = 'bbb'
}

//接口枚举
enum aaa {
  a: 1
}
interface int [
  a: aaa.a
]
let obj: int = {
  a: aaa.a  //也可以 a: 1
}
```

枚举可以被const修饰（不能使用let，var）

```
const enum a {
  a = 0,
  b = 1
}
let aaa = a.a
//编译后的js
var aaa = 0

enum b {
  a = 0,
  b = 1
}
let bbb = a.a
//编译后的js
var b;
(function (b) {
  b[b["a"] = 0] = "a";
  b[b["b"] = 1] = "b";
})(b || (b = {}));
var bbb = b.a;
```

枚举的反向映射，可以用key得到value，也可以用value得到key

不能用const修饰enum，值必须是number

```
enum a { 
  a = 0,
  b = 1
}
let value = a.a
let key = a[value]
console.log(key,value)
//编译后js的部分代码
a[a[a] = 0] = 'a'
```

## 5 函数

对象类型，type，类、接口或函数形参若有函数成员，不确定具体的实现，可以给类型为Function

### 5.1 形参、返回值类型

若未指定返回值类型，则返回值类型默认为void

```
//1.返回值类型
//各种形式的写法
let fun1 = function():number{
  return 1
}

function fun2():number{
  return 2
}

//箭头函数若参数只有一个，且此时需要传递类型，则小括号不能省略
let fun3 = (a: number):number => {
  return 3
}

let fun4: (a: number,b: number) => number


//返回值推断，空返回值，never
//若没有给定返回值类型，则会根据return自动推断
function f1(){ return 123 }

//返回类型void，当没有return，或return undefined，return null，return;时使用
function f2(): void{}  //void也可以不写，会自动推断为void类型
//return undefined，return null，return;时使用，没有return不能使用
function f2(): undefined{ return; }
function f2(): null{ return; }
//不能 return void 因为void不是值，而是类型，不能return类型
```

js中，实参少了其他为undefined，多了忽略
ts中，实参少了多了都不行，必须与形参个数一致（可选参数和剩余参数除外），类型也必须一样

可选参数是ts新增的，剩余参数es6就有

```
//形参类型

//给形参指定类型,同时制定默认值
function fun1(a: string = '123'){}  

//可选参数，所有可选参数必须放到必选参数后剩余参数前,若未传且无默认值则为undefined
function fun2(a: string, b?:number, c?:number){} 

//类型必须是数组，放到最后且只有一个，作为数组接收多余的参数
function fun3(a: string,b?:number, ...r:number[]){} 
```

### 5.2 函数重载

js中函数重复声明则会覆盖前面的，ts则可以使用重载
js的重载与java很不同，是因为为了兼容es低版本

```
//例1
function fun1(age:number):number
function fun1(name:string):string
function fun1(a:any):any{
  if(typeof a === 'number') return a
  else return `姓名：${a}`
}
//例2
function fun2(name:string):string
function fun2(name:string, age?:number):string
function fun2(a:any,b?:any):any{
  if(b) return `${a}${b}岁`
  else return `姓名${a}`
}
console.log(fun1('lgx'))
console.log(fun1(23))
console.log(fun2('lgx'))
console.log(fun2('lgx',23))
```

# 二、js内置对象类型和DOM、BOM类型

## 1 js内置对象类型

这些类型ts也内置了

ES5内置对象：

```
//js内置对象
//1.正则
let reg: RegExp = /*/
//2.日期时间
let date: Date = new Date()
let time: number = new Date().getTime() 
//3.Error
let err: Error = new Error('123')
//4.Boolean Number String对象
let b: Boolean = new Boolean()
let n: Number = new Number()
let s: String = new String()
```

ES6↑内置对象

```
//1.Set
let a: Set<number> = new Set([1,2,3])

//2.Map
let b: Nap<string,number> = new Map
b.set('age',23)

//3.迭代器
letarr = [1,2,3]
let c:Iterator<number> = arr[Symbpl.iterator]()

//4.Promise,Promise和res的类型都可以自动退出，而resolve参数的类型就必须用泛型指定
function p(): Promise{
  return new Promise<number>((resolve,reject) => {
    resolve(123)
  })
}
p().then((res :number) => {})
```

## 2 DOM类型

```
//1.HTMLElement，DOM元素
let aaa1: HTMLElement = document.body
let bbb1: HTMLDivElement = document.qurySelect('div')  
let ccc1: HTMLImageElement = document.qurySelect('img') //其他查阅类型表  

//NodeList，DOM元素伪数组
let aaa2: NodeList = document.querySelectAll('ul li') 
let ccc: 

//事件类型
xxx.addEventListener('click',(e: MouseEvent) => {})
```

HTML标签对应的类型：

```
    "a": HTMLAnchorElement;
    "abbr": HTMLElement;
    "address": HTMLElement;
    "applet": HTMLAppletElement;
    "area": HTMLAreaElement;
    "article": HTMLElement;
    "aside": HTMLElement;
    "audio": HTMLAudioElement;
    "b": HTMLElement;
    "base": HTMLBaseElement;
    "basefont": HTMLBaseFontElement;
    "bdi": HTMLElement;
    "bdo": HTMLElement;
    "blockquote": HTMLQuoteElement;
    "body": HTMLBodyElement;
    "br": HTMLBRElement;
    "button": HTMLButtonElement;
    "canvas": HTMLCanvasElement;
    "caption": HTMLTableCaptionElement;
    "cite": HTMLElement;
    "code": HTMLElement;
    "col": HTMLTableColElement;
    "colgroup": HTMLTableColElement;
    "data": HTMLDataElement;
    "datalist": HTMLDataListElement;
    "dd": HTMLElement;
    "del": HTMLModElement;
    "details": HTMLDetailsElement;
    "dfn": HTMLElement;
    "dialog": HTMLDialogElement;
    "dir": HTMLDirectoryElement;
    "div": HTMLDivElement;
    "dl": HTMLDListElement;
    "dt": HTMLElement;
    "em": HTMLElement;
    "embed": HTMLEmbedElement;
    "fieldset": HTMLFieldSetElement;
    "figcaption": HTMLElement;
    "figure": HTMLElement;
    "font": HTMLFontElement;
    "footer": HTMLElement;
    "form": HTMLFormElement;
    "frame": HTMLFrameElement;
    "frameset": HTMLFrameSetElement;
    "h1": HTMLHeadingElement;
    "h2": HTMLHeadingElement;
    "h3": HTMLHeadingElement;
    "h4": HTMLHeadingElement;
    "h5": HTMLHeadingElement;
    "h6": HTMLHeadingElement;
    "head": HTMLHeadElement;
    "header": HTMLElement;
    "hgroup": HTMLElement;
    "hr": HTMLHRElement;
    "html": HTMLHtmlElement;
    "i": HTMLElement;
    "iframe": HTMLIFrameElement;
    "img": HTMLImageElement;
    "input": HTMLInputElement;
    "ins": HTMLModElement;
    "kbd": HTMLElement;
    "label": HTMLLabelElement;
    "legend": HTMLLegendElement;
    "li": HTMLLIElement;
    "link": HTMLLinkElement;
    "main": HTMLElement;
    "map": HTMLMapElement;
    "mark": HTMLElement;
    "marquee": HTMLMarqueeElement;
    "menu": HTMLMenuElement;
    "meta": HTMLMetaElement;
    "meter": HTMLMeterElement;
    "nav": HTMLElement;
    "noscript": HTMLElement;
    "object": HTMLObjectElement;
    "ol": HTMLOListElement;
    "optgroup": HTMLOptGroupElement;
    "option": HTMLOptionElement;
    "output": HTMLOutputElement;
    "p": HTMLParagraphElement;
    "param": HTMLParamElement;
    "picture": HTMLPictureElement;
    "pre": HTMLPreElement;
    "progress": HTMLProgressElement;
    "q": HTMLQuoteElement;
    "rp": HTMLElement;
    "rt": HTMLElement;
    "ruby": HTMLElement;
    "s": HTMLElement;
    "samp": HTMLElement;
    "script": HTMLScriptElement;
    "section": HTMLElement;
    "select": HTMLSelectElement;
    "slot": HTMLSlotElement;
    "small": HTMLElement;
    "source": HTMLSourceElement;
    "span": HTMLSpanElement;
    "strong": HTMLElement;
    "style": HTMLStyleElement;
    "sub": HTMLElement;
    "summary": HTMLElement;
    "sup": HTMLElement;
    "table": HTMLTableElement;
    "tbody": HTMLTableSectionElement;
    "td": HTMLTableDataCellElement;
    "template": HTMLTemplateElement;
    "textarea": HTMLTextAreaElement;
    "tfoot": HTMLTableSectionElement;
    "th": HTMLTableHeaderCellElement;
    "thead": HTMLTableSectionElement;
    "time": HTMLTimeElement;
    "title": HTMLTitleElement;
    "tr": HTMLTableRowElement;
    "track": HTMLTrackElement;
    "u": HTMLElement;
    "ul": HTMLUListElement;
    "var": HTMLElement;
    "video": HTMLVideoElement;
    "wbr": HTMLElement;

圣
```

## 3 BOM类型

闭包：

ts没有闭包了，要想实现闭包的功能，有两种方式：

* 定义成全局变量，但是肯定会产生变量冲突问题

* 定义一个class，存放闭包使用的变量和原来闭包的函数

定时器：

```
let timer1: Number | null = null
let timer2: Number | null = null
clearTimeout(Number(timer1))
clearInterval(Number(timer2))
```

# 三、高级类型语法

## 1 联合类型，交叉类型

```
//联合类型
// | 表示类型a或类型b都可以
let a2: number | string
let a3: number | '123'
let a4: 100|'hello' | true

//交叉类型
// & 表示同时具备两种类型
let obj: {name: string} & {age: number}
obj = {name: 'lgx',age: 23}
```

## 2 类型推论，类型断言

```
//类型推论，会根据值来自动推断类型
let a = 5  //相当于 let a: numebr = 5
let b      //未赋值，推论为any类型
let obj = {a: 123}  //相当于 let obj:{a:number} = {a:123}
...其他情况以此类推

//返回值简单可以屯轮出来，但当返回值比较复杂时，可能推论不出来，此时需要手动写类型
let aaa = () => 123   //相当于 let aaa = (): number => 123

//类型断言
//一些情况下，数据需要被确定为某种类型，这时候就使用类型断言
//如下面的例子，num被断言为string类型，才有length
function a(num: number | string): void{
  //console.log(num.length)  报错，因为若是number，则没有length
  console.log((num as string).length) //写法一
  console.log((<string>num).length)   //写法二
}
a('123')
// a(123) //报错
/*
但是，类型断言只是消除了ts编译器的报错，当出入怒number类型时无法避免运行时的错误，
依然会报错，所以类型断言不能滥用
*/
function b(num: any): boolean{
  return num as boolean
}
b(true)
// b(123) 报错
```

## 3 类型别名

```
type myType1 = string
type myType2 = 1 | 2 | 3
type myType3 = {
  a: number,
  b: string
}
type myType4 = (a: number) => number

let a: myType2
```

## 4 类型操作

类型和值要区分开，类型不能像值一样使用，只能用类型自己的实验方式，定义类型的方式只有type，接口和对象的临时定义类型，三者操作一样，以下就以type为例

### 4.1 查看类型：

```
type myType = {
  name: string,
  age: number
}
console.log(type) //报错，类型不是值，不能输出
//需要查看类型，可以把鼠标放到myType上就会展示
```

### 4.2 获取类型：

```
//通过索引获对象类型的某个属性的类型
type myType = {
  a: number
}
type a = myType['a]

//获取数组类型每个元素的类型
type arr = Array<number>
type fun1 = arr[number]
type fun2<T> = T extends Array<any> ? T[number] : never
type fun3<T> = T extends arr ? number : never

//typeof获取变量的类型
let obj = {
  a: 123
}
//获取正确的ts类型
type objType = typeof obj
//console只会输出object，不会输出具体的ts类型
console.log(typeof obj)

//获取函数返回值类型
const fun = () => 123
type funType = ReturnType<typeof fun>
```

### 4.3 keyof

用于将某类型所有属性的字面量类型组合成一个联合类型

```
type myType = {
  name: string,
  age: number
}
// 'name' | 'age'
type p1 = keyof myType
```

对象属性的键的类型只能是number,string,symbol或字面量，所以keyof any获得的联合类型是 number | string | symbol

```
type p2 = keyof any
```

for，forEach，for...in...，for...of...遍历时，遍历的那个临时变量不能也不需要指定类型，它会自己类型推论，唯一的特殊情况就是for...in...遍历对象的key时，由于对象的key可能是number，string，symbol或字面量，所以会类型推论隐式具有any类型

解决：在使用i的地方使用类型断言为obj属性键字面量类型组合成的联合类型

```
let obj = {
  name: 'lgx',
  age: 23
}
for(let i in obj){
  //console.log(obj[i])
  console.log(obj[i as keyof typeof obj])
}
```

### 4.4 索引签名

一个对象一旦指定了类型，或未指定由类型推论退出，它的类型就已经定好，若不做一定的处理就无法添加和删除属性

当不知道一个对象未来会有多少属性时，可以使用可选属性索引签名，解决添加属性的问题

删除属性只能删除可选属性或索引签名的恶属性，若想删除必选属性，只能根据该对象的类型新创建一个删除属性后的类型，用这个新类型创建新对象并赋对应的值

索引签名无法用?修饰，可以用readonly修饰

```
type objType = {
  //索引签名不一定要放到首位，可以放到任意位置，键类型也可以是number，symbol
  //key只是一个标识，可以换成其他名字，any也可以换成其他类型
  [key: string]: any,
  name: string,
  age: number
}
//多出的属性可以写在任意地方
let obj: objType = {
  name: 'lgx',
  sex: true,
  age: 23
}
console.log(obj)
```

因为数组的对象的一种，所以若里面只有索引签，则是定义数组

```
//number也可以换成string，symbol，但是使用时还是arr[0]，所以一般都用number
type arrType = {
  [index: number]: any
}
let arr: arrType = [1,'a']
console.log(arr[0])
```

用对象的形式定义数组，可以增加一些属性

```
type arrType = {
  [index: number]: string
  length: number
}
let arr: arrType = {
  0: 'a',
  1: 'b',
  length: 2
}
console.log(arr[0])
```

### 4.5 映射类型

类型内使用in可用于映射遍历联合类型

映射类型可以用?和readonly修饰

```
type myType = {
  //使用映射类型后，不能再有其他属性
  //P只做标识作用，可以换成其他名字
  [P in 'aaa' | 'bbb' | 'ccc']: string,
}
/*
{
  'aaa': string,
  'bbb': string,
  'ccc': string
}
*/
```

### 4.6 infer

用于泛型约束后面，充当一个占位符，相当于别名,infer不是泛型

若得到了never，说明传入的类型不对，报错

获取数组是什么类型的数组

```
type arr = number[]
//使用infer前
type getArrType1<T> = T extends Array<any> ? T[number] : never
type get1 = getArrType1<arr>
//使用infer后
type getArrType2<T> = T extends Array<infer U> ? U : never
type get2 = getArrType2<arr>

//用于元组，会反悔联合类型 number | string
type tup = [number,string]
type get3 = getArrType2<tup>
```

类型提取与剔除

```
type tup = [number,string,boolean]

//提取类型，使用infer后...的剩余参数可以不放到最后面
type getFirst<T> = T extends [infer xxx, ...any[]] ? xxx : never
type getSecond<T> = T extends [infer xxx, infer yyy, ...any[]] ? yyy : never
type getLast<T> = T extends [...infer rest, infer xxx] ? xxx : never

type first = getFirst<tup>
type second = getSecond<tup>
type last = getLast<tup>

//类型剔除
type popTup<T> = T extends [...infer rest, infer last] ? rest : never
type shiftTup<T> = T extends [infer first, ...infer rest] ? rest : never

type pop = popTup<tup>
type shift = shiftTup<tup>
```

递归infer，以翻转元组里的类型为例

```
type tup = [number,string,boolean]
type reverse<T> = T extends [infer xxx, ...infer rest] ? [...reverse<rest>,xxx] : []
type res = reverse<tup>
```

## 5 Utility Types

ts内置的实用类型，用于类型转换

简单的类型转换就和js一样

```
let a: string = '123'
let b: number = Number(a)
console.log(b)
```

复杂的类型转换就可以使用Utility Types

```
//测试代码
type Person = {
  name; string,
  age: number,
  sex: boolean
}
```

Partial<T>，将所有属性变成可选属性

```
type p1 = Partial<Person>
/*
{
  name?: string,
  age?: number,
  sex?: boolean
}
*/
/*ts原码
type Partial<T> = {
  [P in keyof T]?: T[P]
}
*/
```

Required<T>，将所有属性变成必选

```
type p1 = Partial<Person>
/*
{
  name: string,
  age: number,
  sex: boolean
}
*/
/*ts原码
type Partial<T> = {
  [P in keyof T]-?: T[P]
}
*/
```

Readonly<T>，将所有属性变成readonly

```
type p2 = Readonly<Person>
/*
{
  readonly name: string,
  readonly age: number,
  readonly sex: boolean
}
*/
/*ts原码
type Readonly<T> = {
  readonly [P in keyof T]: T[P]
}
*/
```

Pck<T,K>，根据传入的泛型取出对应的属性

```
type p3 = Pick<Person,'name' | 'age'>
/*
{
  name: string,
  age: number
}
*/
/*ts原码
type Pick<T,K extends keyof T> = {
  [P in K]: T[P]
}
*/
```

Record<K,T>，构造一个类型，该类型具有一组属性K，每个属性的类型为T。可用于将一个类型的属性映射为另一个类型

```
type p4 = Record<'a' | 'b',Person>
/*
{
  'A': Person,
  'B': Person
}
*/
/*ts原码
type Record<K extends keyof any,T> = {
  [P in K]: T
}
*/
```

Exclude<T,U>，从T中排除可分配给U的属性，剩余的属性构成新的类型

```
type T0 = Exclude<'a' | 'b' | 'c', 'a'>;  // "b" | "c"
type T2 = Exclude<string | number | (() => void), Function>;  // string | number
/*ts原码
type Exclude<T, U> = T extends U ? never : T
*/
```

Extract<T,U>，从T中抽出可分配给U的属性构成新的类型。与Exclude相反

```
type T0 = Extract<'a' | 'b' | 'c', 'a'>;  // "a"
/*ts原码
type Extract<T, U> = T extends U ? T : never
*/
```

Omit<T,K>，从T中取出除去K的其他所有属性。与Pick相对

```
type P = Omit<MYtYPE, 'sex'>
/*
{
  name: string,
  age: number
}
*/
/*
//结合Exclude和Pick实现
type Omit<T, K extends keyof any> = Pick<T, Exclude<keyof T, K>>;
*/
```

NonNullable<T>，去除T中的 null 和 undefined 类型

```
type T0 = NonNullable<number | string | undefined> // number | string
type T1 = NonNullable<number | null | undefined> // number
/*ts原码
type NonNullable<T> = T extends null | undefined ? never : T
*/
```

Parameters，返回类型为T的函数的参数类型所组成的数组

```
declare function f1(arg: { a: number, b: string }): void
type T0 = Parameters<() => string>;  // []
type T1 = Parameters<(s: string) => void>;  // [string]
type T2 = Parameters<(<T>(arg: T) => T)>;  // [unknown]
type T4 = Parameters<typeof f1>;  // [{ a: number, b: string }]
type T5 = Parameters<any>;  // unknown[]
type T6 = Parameters<never>;  // never
type T7 = Parameters<string>;  // Error: 类型“string”不满足约束“(...args: any) => any”
type T8 = Parameters<Function>;  // Error: 类型“Function”不满足约束“(...args: any) => any”。类型“Function”提供的内容与签名“(...args: any): any”不匹配

/*ts原码
type Parameters<T extends (...args: any) => any> = T extends (...args: infer P) => any ? P : never
*/
```

ReturnType<T>，function T的返回类型

```
declare function f1(): { a: number, b: string }
type T0 = ReturnType<() => string>;  // string
type T1 = ReturnType<(s: string) => void>;  // void
type T2 = ReturnType<(<T>() => T)>;  // {}
type T3 = ReturnType<(<T extends U, U extends number[]>() => T)>;  // number[]
type T4 = ReturnType<typeof f1>;  // { a: number, b: string }
type T5 = ReturnType<any>;  // any
type T6 = ReturnType<never>;  // any
type T7 = ReturnType<string>;  // Error: 类型“string”不满足约束“(...args: any) => any”
type T8 = ReturnType<Function>;  // Error:类型“Function”不满足约束“(...args: any) => any”。类型“Function”提供的内容与签名“(...args: any): any”不匹配

/*ts原码
type ReturnType<T extends (...args: any) => any> = T extends (...args: any) => infer R ? R : any
*/
```

InstanceType<T>，返回构造函数类型T的实例类型

```
class C {
  x = 0;
  y = 0;
}
type T0 = InstanceType<typeof C>;  // C
type T1 = InstanceType<any>;  // any
type T2 = InstanceType<never>;  // any
type T3 = InstanceType<string>;  // error:类型“string”不满足约束“new (...args: any) => any”
type T4 = InstanceType<Function>; // error:类型“Function”不满足约束“new (...args: any) => any”。类型“Function”提供的内容与签名“new (...args: any): any”不匹配

/*ts原码
type InstanceType<T extends new (...args: any) => any> = T extends new (...args: any) => infer R ? R : any
*/
```

## 6 声明文件：

在使用第三方库时，需要从第三方库的声明文件中引入它里面要用的一些类型，一般格式为 @types/xxx，如nodejs需要@types/node    express需要@types/express

```
npm install --save @types/node
npm install --save @types/express
```

这是由于历史原因，比较新的第三方库直接使用就行，而较老的第三方库就需要声明文件

自定义声明文件：

```
// xxx.d.ts
declare var xxx: yyy
```

# 四、面向对象

## 1 类

与ES6的class有些区别

* 属性方法，以及构造器的形参都可以指定类型

* 定义的属性必须要使用

* 构造器内 this.xxx = ...   xxx必须在类内已经定义，如 xxx: number

* 新增修饰符readonly，表示该属性只读，若readonly和static同时使用，则 static readonly，readonly只能修饰属性

```
//类也可以作为类型使用
class user {
  constructor(public username:string, public password: string){}
}
function fun(u:user){
  console.log(u)
}
let u1 = new user('lgx','123456')
let u2:user = u1
fun(u2)
```

面向对象三大特性之封装：

属性/方法的新增修饰符 public，private，protected

* 不加这些修饰符的属性和方法默认是public，public类内外都可以访问

* private只能在类内访问，可以类内定义getxxx，setxxx方法给类外访问，此外，子类中也无法访问（相当于无法继承private）

* protected在类外无法访问，在类内以及子类可以访问

* 修饰符顺序举例：private static readonly

* 只有public可以修饰构造函数的形参，这样就相当于直接声明赋值了，不用再this也不用先声明属性，是一个语法糖
  
  ```
  class a {
    // x: number
    // constructor(x: number){
      // this.x = x
    // }
    //简写
    constructor(public x:number){
  
    }
  }
  let aa = new a(5)
  console.log(aa.x)
  ```

面向对象三大特性之多态：

父类不对方法具体实现，而由子类来进行实现，使得每个子类都有不同的形态，这就是多态。可以看出，多态是基于继承的重写

继承、重写和其他特性与ES6的类一样

## 2 抽象类

当父类涵盖的范围比较大，具体的属性方法不好定义，而且我们也不想实例化这个父类，这时候，就可以使用抽象类，专门用来做继承。抽象类不能被实例化

抽象类无法new实例化

抽象类可以有普通类的属性方法构造器，抽象类内还可以写抽象方法

抽象方法：

* 抽象方法，只定义方法的结构，不做具体实现，若不知道方法具体要怎么实现，就先不实现，使用抽象方法

* 抽象方法没有方法体，只能在抽象类/接口内定义，继承的子类必须重写抽象方法来实现

* 抽象方法箭头函数写法：(n: number) => number

```
abstract class a {
 abstract fun(a: number): void
}
class ch extends a {
  //抽象方法必须重写
  fun(a: number): void{
    console.log('123')
  }
}
```

## 3 接口

接口用来定义类或对象的结构，属性不能赋值，方法都是抽象方法噶
接口可以重复声明，类或对象使用接口时是同名接口合在一起（属性方法相同则忽略靠后的，使用代码靠前的）
类和对象使用接口时，属性方法必须类型相同，且必须全部给到(（可选属性除外），但方法的形参不一定要给，类型也不一定要一样)
注意，接口内的方法虽然都是抽象方法，但是不加abstract

```
interface a {
  name: string
  fun(): number
}
interface a {
  name: string  //已经声明过name了，所以此处会被忽略
  age: number
  fun(a: number): void   //已经声明过fun了，所以此处会被忽略
}
//给对象使用
let obj: a = {
  name: 'lgx', 
  age: 23,
  fun(): number{
    console.log('123')
    return 1
  }
}
/*与type定义类型别名的区别
type不能重复声明，而接口可以
*/

//给类使用
//类实现接口，与类继承于抽象类很类似
class c implements a {
  name: string
  constructor(name: string){
    this.name = name
  }
  age = 23
  fun(): number{
    console.log('123')
    return 1
  }
}
/*与抽象类区别
抽象类可以有正擦好难过的属性方法，而接口的属性不能赋值，方法都是抽象方法噶s
*/

//上面的是类类型接口，还有其他不常用的接口类型--------------------------------

//属性接口，接口内只约束属性，此外，类似 let a:number 的number其实也是属性接口

//函数接口，作用其实就是规范自己写代码，不容易出错
interface fun {
  (a:number):number  //只能是箭头函数的形式
}

let a:fun = function(num:number):number{
  return num
}

//可索引接口，约束数组/对象
interface arr {
  [index:number]:boolean
}
let arr1:arr = [true,false]
//此外，let a:number[] 的number[]其实也是可索引接口

interface obj {
  [index:string]:number
}
let obj1:obj = {'age':23}

//接口扩展（即接口继承）-------------------------------------------------
interface Person {
  name:string
  run(str:string)
}
interface lgx {
  swim(str:string)
}
class my implements lgx {
  constructor(public name:string){}
  run(str:string){
    console.log(str)
  }
  swim(str:string){
    console.log(str)
  }
}

//子类继承父类，同时也可以实现接口
class coder {
  constructor(public job:string){}
}
class mymy extends coder implements lgx {
  name:string
  constructor(job:string, name:string){
    super(job)
    this.name = name
  }
  run(str:string){
    console.log(str)
  }
  swim(str:string){
    console.log(str)
  }
}
```

## 4 混入

```
//1.对象混入
let a: {name: string} = {name: 'lgx'}
let b: {age: number} = {age: 23}
let c: {sex: boolean} = {sex: true}
//a,b,c混入到obj，obj的类型被推论为a，b，c的交叉类型 a & b & c
//若有重复的属性，即使类型不同，后面的也会覆盖前面的
let obj = Object.assign(a,b,c)
console.log(obj)

//2.类的混入
...
```

## 5 装饰器

可以给属性，方法，类等等添加默认的一些东西

类装饰器：

可以给类添加属性方法

```
//不带参数
const xxx: ClassDecorator = (target: Function) => {
  console.log(target)  //使用该装饰器的class的构造函数
  //可以给原型上添加属性方法
  target.prototype.aaa = (a: number) => a
}
//带参数
const yyy: ClassDecorator = (canshu: string): ClassDecorator => {
  return (target: Function) => {
    target.prototype.aaa = (a: number) => a
  }
}


@xxx
class A {}
let obj = new A()
console.log(obj.aaa(123))

@yyy('asdf')
class B {}

@xxx @yyy('asdf')
class C {}

@xxx
@yyy('asdf')
class D {}
```

属性装饰器，方法噶装饰器和参数装饰器：

```
const propD: PropertyDecorator = (target,propName) => {

}
const funcD: MethodDecorator = (target,funcName,tag) => {

}
const paramsD: ParameterDecorator = (target,paramsName,paramsLoc) => {

}

class A {
  @propD
  aaa: string
  @funcD
  fun(@paramsD n: numebr): number{ return n }
}
```

# 五、泛型

当不知道未来将会使用什么类型，就可以使用泛型。

```
//未使用泛型前，未来使用这个方法不一定是number类型
function fun0(a: number): number{
  return a
}
//使用后
function fun1<xxx>(a: xxx): xxx{
  return a
}
//或 const fun1 = <xxx>(a: xxx): xxx => a
fun1(5)             //会自动判断类型，但有时不一定奏效
fun1<string>('123') //手动设置类型

//类也可以使用，泛型类
class c<xxx> {
  constructor(public a: xxx){

  }
}
let obj1 = new c(5)
let obj2 = new c<string>('123')

//泛型接口
interface i<xxx>{
  //接口的抽象方法也可以自己使用泛型
  a:xxx
}
let o:i<number> = {a:123}

//同时传入多个泛型
function aaa<xxx,yyy>(a:xxx,b:yyy){}
```

泛型约束

有时需要对泛型进行约束，泛型可以根据接口等等做一些限制 <xxx extends 接口/类/抽象类> 注意都用extends，只有符合条件才不会报错

```
//若不做泛型约束，如下，a是number就会出问题
let getLength<T> = (a:T) => a.length  

//泛型约束后
interface len {
  length: number
}
let getLength<T extends len> = (a:T) => a.length

//配合keyof进行约束
//先看个例子
let o1 = {
  name: 'lgx'
}

function getValue<T>(obj:T,key:string){
  return obj[key]
}
console.log(getValue(o1,'name'))  //OK
console.log(getValue(o1,'age'))   //不报错，但是因为o1没有age属性，返回undefined

//若有一个需求，当取的属性该对象没有时，需要报错，就可以使用 extends keyof 来限制
function get<T,K extends keyof T>(obj:T,key:K){
  return obj[key]
}
// console.log(get(o1,'age'))  报错，达到需求
```

泛型应用举例：

MySQL和MongoDB的操作可能不同，可以统一一下操作，以对用户的增改查删为例

```
interface DB<T> {
  add(info:T):boolean
  update(info:T, id:number):boolean
  get(id:number):boolean
  delete(id:number):boolean
}
class MySQL<T> implements DB<T> {
  add(info:T):boolean{return true}
  update(info:T, id:number):boolean{return true}
  get(id:number):boolean{return true}
  delete(id:number):boolean{return true}
}
class MongoDB<T> implements DB<T> {
  add(info:T):boolean{return true}
  update(info:T, id:number):boolean{return true}
  get(id:number):boolean{return true}
  delete(id:number):boolean{return true}
}
```

# 六、模块

ts的模块分为内部模块（也叫命名空间）和外部模块（也叫模块）

外部模块与es6是一样的

## 1 命名空间

用于组织代码和避免命名冲突

```
//基本使用
//若有重名的namespace，则与接口合并一样的规则合并
namespace aaa {
 export let a:number = 123
}
namespace bbb {
 export let a:number = 456
}
console.log(aaa.a)
console.log(bbb.a)

//命名空间可以嵌套
namespace A {
  export namespace B {
    export let C = 123  
  }
}
console.log(A.B.C)
//起别名来简化
import AAA = A.B
console.log(AAA.C)

//导出给外部文件使用
export namespace asd {...}
//使用的文件中
import {asd} from '...'
```

命名空间也可以放到外部模块中，再导出使用

## 2 三斜线指令

用于引入ts文件，引入后可以直接使用那个文件里面的资源，缺点就是会产生命名冲突

```
///<reference path="./aaa.ts" />
console.log(a)  //a是aaa.ts里面的变量，可以直接使用
```

也可引入声明文件，如nodejs的声明文件 @types/node

```
///<reference types="node" />
```

# 七、ts配置文件

tsconfig.json

为了兼容性，将js编译的版本设置为ES5

为了达到更严格的类型检查

* compilerOptions.noImplicitAny: true，开启后，不再允许隐式any，除非手动设置类型为any变为显式any

* compilerOptions.strictNullChecks: true，开启后，不再允许所有类型都可以赋值为undefined和null，若想赋这两个值，必须是联合类型，如 number | undefined，或者使用类型断言，如 as number
