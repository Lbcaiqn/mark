npm i -g typescript

tsc 查看是否安装成功

tsc xxx.ts   编译出js文件

tsc xxx.ts -w  观察模式，代码已修改就自动编译（单个文件）

ts.config.json   ts的编译配置文件

有了这个文件后，tsc 就会编译所有ts文件，tsc -w 就会观察所有ts文件的修改

默认情况下，ts编译成es3，且报错后也会编译，可以自己进行配置

ts是js的超集，具备类型，语法检查更方便

# 一、类型

给变量声明数据类型，赋值时只能赋值对应的数据类型

```
/基本谁用

//变量
let a: number
let b: number = 5
let c = 5   //这样ts会自动给变量number类型
```

```
//比较简单的类型


//可以用typeof检查类型

//1.字面量类型，声明后不能修改，相当于常量
let a1: 5

//2.any,表示任意类型，相当于关闭了类型检查（不建议使用，不然使用ts干嘛）
let b1: any = 'hello'  //显示any
let b2       //隐式any

//3.unknown，表示未知类型，推荐用来替代any，相当于类型安全的anys
let b3: unknown = '123'
//-与any的区别
let b4: string = b1  //成功，可以将any类型赋值给任何的类型，相当于把b4的类型检查也关了
// let b5: string = b3 //报错，不能把unknown类型赋值给其他类型
//--
//--那么我们知道unknown是什么类型，需要赋值时怎么办
let b5: string = b3 as string  //类型断言，告诉编译器我就是string类型(注意，若b3不是string，也会赋值成功，但类型不是string而是真正的类型)
let b6: string = <string>b3 //效果一样
//--

//4.函数返回值void never
//5.1没有指定类型，则类型根基return的类型
function fun1(){  //number类型
  return 123
}
function fun2(){  //没有return或reture; 类型undefined

}
function fun3(): void{ //void表示空返回值，此时不能有return，或return;或returnundefined
  //空返回值也是一种返回值
}
function fun4(): never{ //表示从来没有返回值，如异常了代码直接停止运行，自然没有返回值
  throw 'never'
}

//undefined，null
/*
与js一样，未赋值的变量输出并不会报错，值为undefined，但这不规范，如number类型的值不应该是undefined
undefined，null是never的子类型，它们的值也只能是undefined，null
若值有number或undefined等类似情况，可以用关联类型来
*/
let a:number
let b:undefined
let c:null
let d:number|undefined|null
```

```
//对象定义与赋值

//因为js中number，string甚至函数都是对象，所以这样写其实没什么意义
let obj :object;

//通常这样指定对象类型
let obj1 :{
  name :string,
  age :number
  job? :string  //表示为可选属性，赋值时可赋可不复
}
//注意赋值时，属性必须是对应类型，且属性数量必须给全(?除外)
obj1 = {
  name: 'lgx',
  age: 23
}

//不知道赋值有几个属性，可以这样做，表示属性名为字符串，属性值为any类型
let obj2: {name: string, [xxx: string]: any}
obj2 = {name: 'lgx',a:'5',b:55}
```

```
//定义一个函数结构
let fun: (a: number,b: number) => number
//赋值时，形参名可以不一样，但形参个数和类型必须一样
fun = function(n1: number,n2: number): number{
  return n1+n2
}
```

```
//ts的数组里面都是相同的类型(所以不建议使用any)，有两种声明方式
let arrStr: string[]
let arrNum: Array<number>
arrStr = ['a','f']
arrNum = [5,8]

//元组tuple，即长度固定的数组
let tup: [string,number]
//赋值时，类型和长度必须一样
tup = ['hh',55]

//枚举enum，适合值在几个值选择时使用
enum sexVal{
  Male = 0,
  Female = 1
}
let o: {name: string,sex: sexVal}
o = {name: 'lgx',sex: sexVal.Male}
```

```
//联合类型
// | 表示类型a或类型b都可以
let a2: number|string
let a3: number|'123'
let a4: 100|'hello'|true
// & 表示同时具备两种类型
let obj: {name: string} & {age: number}
obj = {name: 'lgx',age: 23}


//类型别名
type myType1 = string
type myType2 = 1 | 2 | 3
let a: myType2
```

# 二、函数

```
//1.使用返回值类型下的函数形式
let fun1 = function():number{
  return 1
}
function fun2():number{
  return 2
}
let fun3 = ():number => {
  return 3
}

//2.函数形参
/*
js中，实参少了其他为undefined，多了忽略
ts中，实参少了多了都不行，必须与形参个数一致（可选参数和剩余参数除外）
*/
function fun4(a: string = '123'){}  //给形参指定类型,同时制定默认值
//可选参数，所有可选参数必须放到必选参数后剩余参数前,若未传且无默认值则为undefined
function fun5(a: string, b?:number, c?:number){} 
function fun6(a: string,b?:number,...r:number[]){} //类型必须是数组，放到最后且只有一个，作为数组接收多余的参数
//可选参数是ts新增的，剩余参数es6就有

//3.重载
//js中函数重复声明则会覆盖前面的，ts则可以使用重载
//js的重载与java很不同，是因为为了兼容es低版本
//例1
function fun7(age:number):number
function fun7(name:string):string
function fun7(a:any):any{
  if(typeof a === 'number') return a
  else return `姓名：${a}`
}
//例2
function fun8(name:string):string
function fun8(name:string, age?:number):string
function fun8(a:any,b?:any):any{
  if(b) return `${a}${b}岁`
  else return `姓名${a}`
}
console.log(fun7('lgx'))
console.log(fun7(23))
console.log(fun8('lgx'))
console.log(fun8('lgx',23))
```

# 三、面向对象

1 类

属性方法以及构造器的形参都用每 :类型

构造器内 this.xxx = ...   xxx必须在类内已经定义，如 xxx: number

新增修饰符readonly，表示该属性只读，若readonly和static同时使用，则 static readonly

readonly只能修饰属性

```
//类也可以作为类型使用
class user {
  constructor(public username:string, public password:string){}
}
function fun(u:user){
  console.log(u)
}
let u1 = new user('lgx','123456')
let u2:user = u1
fun(u2)
```

其他一样

2 抽象类

```
/*
当父类涵盖的范围比较大，具体的属性方法不好定义，而且我们也不想实例化这个父类，这时候
就可以使用抽象类，专门用来做继承。抽象类不能被实例化
*/
abstract class a {
  //抽象类可以有普通类的属性方法构造器
  /* 抽象方法，只定义方法的结构，不做具体实现
  不知道方法具体要怎么实现，就先不实现，使用抽象方法
  抽象方法没有方法体，只能在抽象类/接口内定义，继承的子类必须重写抽象方法来实现
  */
 abstract fun(a: number): void
}
class ch extends a {
  //抽象方法必须重写
  fun(a: number): void{
    console.log('123')
  }
}
```

3 接口

```
/*
接口用来定义类或对象的结构，属性不能赋值，方法都是抽象方法噶
接口可以重复声明，类或对象使用接口时是同名接口合在一起（属性方法相同则忽略，使用代码靠前的）
类和对象使用接口时，属性方法必须类型相同，且必须全部给到(但方法的形参不一定要给，类型也不一定要一样)
注意，接口内的方法虽然都是抽象方法，但是不加abstract
*/
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
type不能呢个重复声明，而接口可以
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

4 属性的封装

```
/*属性/方法的新增修饰符 public，private，protected
不加这些修饰符的属性和方法默认是public，public类内外都可以访问
private只能在类内访问，可以类内定义getxxx，setxxx方法给类外访问，此外，子类中也无法访问（相当于无法继承private）
protected在类外无法访问，在类内以及子类可以访问
修饰符顺序：private static readonly
*/

/*此外，就public可以修饰构造函数的形参
这样就相当于直接声明赋值了，不用再this也不用先声明属性
可以看成语法糖
*/
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

5 多态

父类不对方法具体实现，而由子类来进行实现，使得每个子类都有不同的形态，这就是多态。可以看出，多态是基于继承的重写

# 四、泛型

```
//当不知道未来将会使用什么类型，就可以使用泛型
//使用前，未来使用这个方法不一定是number类型
function fun0(a: number): number{
  return a
}
//使用后
function fun1<xxx>(a: xxx): xxx{
  return a
}
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

/*
可以同时定义多个泛型   <xxx,yyy,www>
泛型可以根据接口等等做一些限制  <xxx extends 接口/类/抽象类>  注意都用extends
*/
```

```
/*泛型应用举例
MySQL和MongoDB的操作可能不同，可以统一一下操作
以对用户的增改查删为例
*/
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

# 五 模块

ts的模块分为内部模块（也叫命名空间）和外部模块（也叫模块）

外部模块与es6是一样的

命名空间用于组织代码和避免命名冲突

```

```

namespace aaa {
  export let a:number = 123
}
namespace bbb {
  export let a:number = 456
}
console.log(aaa.a)
console.log(bbb.a)

```

```

命名空间也可以放到外部模块中，再导出使用
