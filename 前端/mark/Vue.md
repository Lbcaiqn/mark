# 一、Vue2

## 1 基本

### 1.1 基本命令

安装旧版脚手架2（现在基本不用脚手架2）

```
npm install -g vue-cli
```

安装新版脚手架3或更高版本

```
npm uninstall -g vue-cli
npm install -g @vue/cli
```

Vue3最低支持的脚手架版本为4.5

```
npm install -g @vue/cli@4.5
```

查看脚手架版本

```
vue -v
```

### 1.2 浏览器Vue调试工具

浏览器vue调试插件：vue devtools

### 1.3 vscode插件

vue2：使用vetur

vue3：使用volar

在新的语法下，vue2的vetur不再够用，vue3的语法提示插件试验volar

Vue Language Features (Volar)

TypeScript Vue Plugin (Volar)

为了防止冲突，在使用vue3时，启用volar并禁用vetur，在使用vue2时，启用vetur禁用volar

### 1.4 MVVM模式

MVX模式（MVC和MVVM）:
MVC模式：模型+视图+控制器，Angular框架使用。
MVVM模式：把MVC的控制器改成ViewModel，View的变化会自动更新ViewModel，ViewModel的变化也会同步在View上显示。Vue等框架使用。

MVVM：
Model：是vue里面的data、methods、生命周期等等里面的数据访问（ajax），数据操作、业务逻辑等。
View：是<template>的内容。
View Model：就是vue对象，包含 data bindings 和 DOM listeners，根据model的数据来来控制view页面的展示。

### 1.5 Vue使用方式

分为两种，一是script引入使用，二是脚手架构建使用（组件化那部分笔记）

```
<script src="vue.js"></script>   本地引入
<script src="https://unpkg.com/vue@2.6.14/dist/vue.js"></script> 网络
```

## 2 基本语法

data:{},{}可以声明成变量，在vue对象外定义，如var data={}; vue中data:data
方法和计算属性内部使用Vue内部的属性时，一定要加上this.

引号使用规范：

虽然无论是HTML的标签还是js代码单引号和双引号效果都一样，但是为了规范，HTML的属性使用双引号，js代码使用单引号，嵌套引号时需要注意间隔使用单双引号

```
<div xxx="..."></div>
<div :xxx="'...'"></div>

let a = '123'
```

箭头函数的this指向与vue：

* vue自带的api里的回调函数要使用this时，必须使用普通函数，this才能指向vue实

* 不是vue的api函数（如定时器回调，promise回调，事件总线回调等），可以使
  用箭头函数更加简便，this指向window

```
const v = new Vue({
  //控制器，绑定id，等价于vue对象.$mount('...')，两种挂载方式选一种就行
  el: "#xxx 或 .xxx",  
)}

//阻止vue启动时的生产提示
Vue.config.productionTio = false  
```

### 2.1 插值指令和插值语法

指令：指令  v-xxxx 类似标签的属性的写法

{{}}为Mustache语法，内容为JS表达式

```
//插值操作，
{{ 变量名 }}    
{{字符串变量1+' '+字符串变量2}} {{数值变量*2}}
{{ arr[2] }}
{{ obj.age }}
{{ 方法() }}
```

插值指令

| v-once       | 使{{}}里的变量不会改变                                                                    |
| ------------ | -------------------------------------------------------------------------------- |
| v-pre        | 不解析插值语法，直接显示{{ 变量名 }}                                                            |
| v-text=“xxx” | 用xxx的值覆盖标签内的文本变量，会替换掉使用该指令的元素里的所有文本内容 ，若变量为string且string里有html标签，不会解析成标签，只会当成字符串 |
| v-html="xxx" | 在该标签内插入整个html标签，但最好不要使用v-html，非常不安全，容易被窃取cookie中的登录信息                            |
| v-clock      | 还要添加 [v-cloak] {display: none;}的样式，作用是在js未解析出来前隐藏该标签                             |

### 2.2 数据绑定

#### 2.2.1 v-bind

v-bind:属性  可以简写为 :属性    用来动态绑定属性

（1）绑定img的src

只能绑定网络URL，本地URL需要另外处理

（2）绑定绑定class、style控制样式

```
<!-- 1.可以分写css类和变量存储的css类名 -->
<div class="css类名" :class="变量名"></div>

<!-- 2.数组写法，注意引号 -->
<div :class="['css类名',变量名]"></div>

<!-- 3.对象写法，true生效flase失效 -->
<div :class="{'css类名':true,变量名:boolean变量}"></div>

<!-- 4.Vue中方法内：return 数组或对象,当数组或对象太复杂时可使用 -->
<div :class=’方法() '></div>

<!-- 5.变量的值作为样式的属性，若此时不用变量则加上引号，若Vue中变量存的是像素且不带px，则使用时加上+‘px’ -->
<div :style="{样式属性:变量名}"></div>

<!-- 6.数组写法，不常用 -->
<div :style="[对象1,对象2…]">></div>
```

（3）绑定的属性名和值一样时

true生效，如button属性disabled=”disabled”，等同于v-bind:disabled=”true”

#### 2.2.2 v-model

双向绑定表单（input表单，textarea表单）

（1）input

表单的value值（表单显示的文本）是v-model的变量值，当修改变量值时会同时修改value，当修改value时，也会同时修改变量的值，这就是双向绑定

获取过来不管类型都默认为字符串。

textarea表单，password等类型的input表单用法都和这个一样。

```
<input type="text" v-model="变量">
<!--
双向绑定原理，v-model等同于：
<input type="text" :value="name" @input="name=$event.target.value">
-->
```

（2）与radio类型input结合使用：

需要value属性，变量是string类型而不是boolean
若变量的值为radioName，则该radio会被选上；若不同或为空则不选。
当选择该radio时，其value会赋值给变量。
一组radio的v-model里的变量一样时，不用给它们相同的name属性，就能实现单选。

```
<input type="radio" value="radioName" v-model="变量">
```

（3）与checkbox类型input结合使用：

```
<input type="checkbox" v-model="布尔变量">
<!--
单个复选框：一般用于同意协议等
不需要value属性，变量为布尔类型。
该布尔变量true时选上，false或其它类型则不选，以此可设置默认是否选上，选择或取消都会修改变量。
-->

<input type="checkbox" value="cbName" v-model="数组名">
<!--
多个复选框：
需要value属性，变量为数组类型。
可以根据数组内容设置默认选上。选择或取消选项都会自动插入删除数组元素。
-->
```

（4）select

```
<select v-model="xxx" @change=”fun”>
  <option value="xVal">请选择</option>  //xxx=”xVal”,双向绑定了这个op
  <option v-for="i in mVal" :value="i">{{i}}</option>//其他op不管双向绑定
</select>
<!--
v-model绑定的是值和value一样的op，用来默认选中
每个op的id和内容作为一个对象，多个op为一个数组，id给事件获取
@chage=”fun”,当选中时获得id
fun(event){
  this.mVal=event.target.value
}
v-model的变量：
单选，变量为字符串类型
多选，变量为数组，select标签需要添加multiple=”multiple”（页面多选ctrl+拖拽）
-->
```

（5）v-model修饰符

| v-model.lazy   | 只有敲了回车或失去焦点才会动态响应                   |
| -------------- | ----------------------------------- |
| v-model.number | 若输入为数字型则转换为数字型（默认获取过来是字符串，一般与number |
| 类型表单连用）        |                                     |
| v-model.trim   | 删除字符串首尾空格                           |

#### 2.2.3 自定义指令

封装DOM操作成一个指令

xxx为指令名，用v-xxx调用，当xxx为多个单词组成时，-隔开，且xxx不能再简写为不带引号，应为’xxx’

element为指令绑定的真实DOM元素，可以使用所有DOM操作的属性方法，binding为对象，其中一个键 value为 v-xxx=”n” v-xxx:…=”n” 的n

简写形式，在元素与指令绑定完成时候执行一次（此时元素还不在真实DOM上），任何数据更新造成的模板重新解析再执行一次，一些DOM操作必须在真实DOM中有该元素时才能操作，需要完整写法才能完成

完整写法有3个钩子，都有element和binding，可以解决简写形式中需要元素在真实DOM后才能进行的操作（inserted()），因为bind只执行一次，所以update中要复制一份bind代码

无论简写还是完整写法，函数里面的this都指向window

```
//局部指令，Vue的配置项：
directives:{
  //简写
  xxx(element,binding){}
  //完整写法
  Xxx:{
    bind(element,binding){}      //指令与元素完成绑定时回调
    inserted(element,binding){}  //元素插入到真实DOM后回调
    update(element,binding){}    //模板重新解析时回调
  }
}

//全局指令：
Vue.directive(‘xxx’,{//完整写法}) Vue.directive(‘xxx’,()=>{//简写})
```

## 3 计算属性与过滤器，数据监视

### 3.1 计算属性

1通过属性之间的计算得到的属性，具有缓存功能。与methods最大的区别就是缓存，computed多次调用只计算结果一次并保存，而methods多次调用就多次计算结果，所以compted比methods好很多。

Vue会根据计算属性内的值有无变化判断是否重新计算，若值不变，则不改缓存，若值变了，则会重新执行计算属性给新缓存。

优势：比直接写{{ 复杂表达式 }}代码可读性高，比methods性能好。

计算属性的值只有当它依赖的数据变化时才更新并调用一次，所以计算属性不能return一个函数而在函数里面做一些操作，因为函数本身是不会变的，这样计算属性的值就不会更新

```
/*
Vue的配置项computed
语法类似方法，但不是方法，不能带形参，使用时不加括号。其实本质就是个属性。
*/
//1.完整写法：
计算属性名: {
  //调用时回调get，修改时回调set(此时可修改计算属性的依赖属性)
  set: function(){},
  get: function(newVal){
    //get不能带形参
    return …;
 }
}
//2.set很少用到，可以简写：
计算属性名: function(){
  return …;
}
```

### 3.2 过滤器

```
//1.局部过滤器
/*
Vue的配置项filters
语法与计算属性一样，过滤器专门用来格式化文本，如return 形参.toFixed(2);
过滤器必须要有一个形参，但是调用时不带括号，| 语法会自动将前面的变量/表达式作为实参
*/
filters:{
  xxx(val){}
}
用在两处地方：
{{xxx | filtersName}}
v-bind:属性=”xxx | filtersName”    
//2.全局过滤器：
Vue.filter()
```

### 3.3 数据监视

```
/*
vue的配置项之一，watch，当数据发生变化时执行的操作
1.xxx是data属性或计算属性，不加this，若xxx未定义，不报错但是newValue/oldValue都是undefine
2.若xxx为对象obj里的一个属性，则key不能简写为不带引号，必须 'obj.xxx'
3.若xxx为对象，则它里面的属性发生变化，watch默认不监测（想监测使用深度监测），只有它
这个对象本身发生变化，才会监测（vue本身是可以对这种多层级的属性进行监测的，如各种数
据发生变化都会响应式刷新页面，只能说vue给程序员提供的watch默认不能监测这种多层级）
4.深度监测：想要监测对象xxx中的任意属性发生变化，deep;true
*/

watch:{
  xxx:{
    //watchConfig
    immediate:true  //加了之后，初始时就检测一次,由于此时未发生改变，oldValue为undefine
    deep:true       //加了之后，开启深度监测
    handler(newValue,oldValue){
      //检测到数据变化后的操作，newValue/oldValue为变化前/后的值
    }
  }
}
//也可以调用 $watch('xxx',{//watchConfig})


//监测简写：在不需要immediate和deep的前提下才能简写：
watch: {xxx(newValue,oldValue){}}
$watch('xxx',(newValue,oldValue)=>{})
```

监视和计算属性的区别，计算属性能实现的，watch也能实现

* 计算属性一旦数据改变就执行一次，数据不改变不执行，且初始就执行一次

* watch是数据一旦改变就执行，数据不改变不执行，需要immediate:true 初始才会执行一次

* 计算属性不能进行异步操作，watch可以

## 4 生命周期

在vue的创建到销毁的过错中，有一些生命周期函数（也叫钩子），在相应的节点就会回调这些函数，由此可以在vue的相应节点编写代码
生命周期函数与data，methods等同级，函数里面调用data等时也用this

使用示例：

```
created(){
  console.log(''我被创建了)
}
```

（1）el挂载之前

若无el挂载，会在created后停止

| beforeCreate | 数据监测，数据代理创建之前，此时无法调用data，methods |
| ------------ | -------------------------------- |
| created      | 数据监测，数据代理创建之后，组件已创建，此时可网络请求数据    |

（2）el挂载之后

| beforeMount | vue解析完模板，生成虚拟DOM在内存中，但是还未转成真实DOM，所以页面未解析vue语法来渲染，此时若操作DOM，只在这个瞬间有效，                 由于下一流程的影响，此时操作的DOM最终都无效。该钩子将虚拟DOM转真实DOM，并保存一份到 $el 里 

| beforeMount | DOM还未渲染完成              |
| ----------- | ---------------------- |
| mounted     | DOM渲染完成，展示模板，此时才能操作DOM |

（3）数据更新

一旦有数据更新就回调

| beforeUpdate | 此时数据更新完，但是页面还未刷新，就是model和view不同步，根据新数据生成新虚拟DOM，新旧虚拟DOM比较看是否有复用，刷新成新页面 |
| ------------ | --------------------------------------------------------------------- |
| updated      | 数据更新完，页面也刷新完，model和view同步                                             |

（4）组件销毁

调用$destroy()或路由离开就会销毁组件，

$destroy()会完全销毁实例，并清除与其他实例的链接

清除所有指令和自定义事件（原生事件不清)
大部分情况都不是自己主动调$destroy，而是自动调（如路由切换等）

| beforeDstroy | 还未开始销毁，还可以调data，methods，但此时对数据的任何修改都无效,此时宜做收尾工作（清除定时器，事件总线上的监听等） |
| ------------ | ---------------------------------------------------------------- |
| destroyed    | 销毁之后，一般很少用这个钩子                                                   |

（5）路由钩子

只有该组件配置成路由时才会触发

| activated                | 在跳转到该路由后回调（激活）     |
| ------------------------ | ------------------ |
| deactivated              | 在离开该路由后回调（失活）      |
| this.$nextTick(() => {}) | 在数据更新后，元素在真实DOM后回调 |

## 5 Vue响应式原理

（1）响应式

若没有响应式，则数据修改时，只有在script中改了，模板并没有改，只有响应式才会重新解析模板，修改模板的数据

vue在每次有值修改时，都会再解析一次vue模板，所以{{方法()}}会再调用

（2）原理

通过Object.defineProperty()以数据代理的形式实现

数据代理：通过一个对象代理对另一个对象的属性的操作（读写）
vue实例化一个vm（把data改成了_data），在操作_data里的属性，都需

要 _data.xxx 十分麻烦，而事实上我们可以直接 xxx 调用，是因为vue用了数据代理
实例化vm时，给vm增加了data里的所有属性并且都是Object.defineProperty():

* 当访问时，回调get，return _data.xxx

* 当修改时，回调set，_data.xxx = value

Object.defineProperty()的方式给每个key添加set，get，在set中进行修改数据，重新解析模板等操作，最终data转成_data，vm中增加_data里的key，通过数据代理管理_data

注意点：

* 添加set，get时，所有的，所有data下的根属性和对象中的属性都会添加到，若对象中又有对象，则会递归，直到最深处遍历到所有属性为止

* 数组中的非对象属性不会被添加get，set方法，也就是说，通过索引的方式操作数组，值是改了，但是vue无法监测到，也就没有响应式。
   可以通过数组的7个函数（如push）来操作数组，此时vue能监测到，就是响应式，这7个函数是vue对Array原型中的函数重新封装（先调用原生Array函数，后就重新解析模板等操作）
  push()    pop()    shift()    unshift()        splice()    reverse()    sort()
  以及
  Vue.set(this.数组名,下标,新值);     

* 数组和对象自己本身没有get，set，所有对数组，对象自己本身赋值，监测不到
  *因为添加set，get是在vue实例化的时候进行的，所以在代码运行过程中，若想给对象和数组添加key，是监测不到的，此时需要使用 Vue.set()方法，添加key，注意此时数组中新增的非对象元素也没有get，set，但是数组里新增的对象里的属性有

## 6 事件绑定

完整 v-on:click="fun"   
缩写 @click="fun"

* *事件函数没有形参时，调用时可以省略括号

* 多个事件用逗号隔开事件函数

* 当事件函数只有一行时，可以直接写逻辑，如 @click="a++"

（1）参数传递

当事件函数有传参时：

* *有括号无参数，默认全部参数为undefind

* 无括号，由于事件产生后浏览器会自动生成一个event事件对象，所以无括号时，默认参数为该event事件对象。即当需要使用事件对象时可以用这种方法。（当有多个参数时，无括号情况下，第一个为event事件对角，其他为undefind）

* 当想event的位置不在第一个或想传入多个event时，将$event作为实参

（2）事件修饰符

| native  | 使自定义组件可以使用原生Vue事件         |
| ------- | ------------------------- |
| stop    | 防止事件冒泡，只有监听的元素才响应、        |
| once    | 使得事件只触发一次                 |
| prevent | 阻止事件默认行为（如submit标签的点击就提交） |
| 按键编码或英文 | 只监听特定的一个按键，常用于keyup事件     |

（3）事件类型

与js全部一样，分为鼠标，键盘，表单，HTML四种。
常用：
v-on:click=’’        鼠标点击 
v-on:keydown=’’    键盘按下
v-on:keyup=’’        键盘弹起
v-on:input=’’        input，textarea一旦有输入（包括退格，不包括空格）就触发。

## 7 列表、条件渲染

1 条件渲染

（1）v-if="xxx" v-else-if="xxx"    v-else
用来控制该元素以及它的孩子的显示与隐藏（隐藏是直接删除，原位置就空出）
else必须与if连在一起用
（2）v-show
用法与v-if一样，区别在于：v-show不删除元素，不保留位置（等同于display:none;），v-if

直接删除元素（当然也是不保留位置），所以v-show性能高。当切换频率很高时优先使用v-show

（3）Vue中表单的复用：
在控制input显示隐藏时，若表单已经输入了值，则else切换的另一个表单会保留值，这是因为Vue使用虚拟DOM将元素放到内存中，在渲染时，出于性能考虑，Vue会做一些复用，比如input的复用：
当切换表单时，Vue会发现隐藏表单后，显示另一个表单，所以Vue直接使用原来的表单并保留值，但是会把id，type，class属性等替换成新的。虽然控制台看到的id不同，实际上是同一个表单。
若不想保留值：
在各inpuit中添加key=”key名” 属性，标识input，弱两个表单key一样则可以复用，不一样则

不能复用，并创建新表单，值自然就不会保留。

2 列表渲染

（1）基本使用：

-for   生成多个该元素/组件（包括孩子），如li
可以循环生成元素及它的孩子，非常好用，如给tr标签v-for，就能迅速生成表格和数
据，且代码量大大减少。也可父子都给v-for形成双重循环
注意这里的for in和JS中的for in的i有区别
使用v-for时不能同时使用v-if，因为v-if隐藏时会删除v-for，所以使用v-show

```
<!-- 遍历数组 -->
<div v-for=”i in arr”>
  值是：{{ i }}
</div>     
<div v-for=”(i,iIndex) in arr”>
  下标是：{{iIndex}} 值是：{{i}}
</div>                        

<!-- 遍历对象 -->
<div v-for="i in obj">
  值是：{{ i }}
</div>    ）
<div v-for="(i,key) in obj">
  键是：{{ key }} 值是：{{ i }}
</div>
<div v-for="(i,key,index) in obj">
  下标是：{{ index }} 键是：{{ key }} 值是：{{ i }}
</div>


此外
```

此外，也可以遍历数字n/字符串，得到0到n-1的数字/各个字符

若想遍历前n个，可以v-for="i in xxx.length - n"

若想遍历其中几个或者后n个，只能全部遍历出来，再v-show v-if不要的

（2）:key

官方推荐使用v-for时，最好给元素/组件绑定key属性，这是为了更好地复用以及不出错。所以只要用了v-for，就要给其指定 :key 作为唯一标识，key最好为数据里的唯一标识属性 （若没指定，默认 :key="索引"） ，这是为了显示结果不出错和效率（效率体现在复用，复用指元素不用删除再创建，用原来的就行）

:key=”i”    必须是遍历的唯一标识，不能是下标

key工作原理：
初始：数据-虚拟DOM-真实DOM
更新：新数据-新虚拟DOM-新真实DOM
更新数据时，新虚拟DOM与旧虚拟DOM会进行比较算法，根据key进行逐一比较，若有完全相同的元素，就直接复用原来的，增加效率，但是注意输入框的特例，输入框的相同不与文本内容相关，就是文本不同但其他一样，就会复用输入框

若此时使用index作为key

* 新的数据在最后面增删，不影响原本数据顺序，无影响

* 在其他地方增删 就会改变原有数据顺序，例子：在原有数据最前面插入一个新数据，数据分别为索引key，唯一标识，内容，输入框
  
  ```
  旧              新               比较结果
   0 000 a input0 0 002 c input2  0 002 c input0
   1 001 b input1 1 000 a input0  1 000 a input1
                    2 001 b input1  2 001 b input2
  依次根据索引进行比较
  索引0和1 标识和内容不同，不复用：input相同复用
  结果是错误的，且大量的没有用到复用而重新渲染，效率低下
  而采用唯一标识作为key的话，除了新添加的元素，都进行了复用，效率高了很多，且结果正确
  
  若此时使用唯一标识作为key,效率大大提高，且不会出错
  ```

（3）列表的过滤与排序

v-for常用的一个应用，一般用计算属性或watch实现，计算属性更好
效果：输入若干字符形成字符层s，根据s对源数据的内容进行模糊匹配，最终排序显示相应的匹配结果
用到的函数：filter() indexOf() sort()
原理：以indexOf作为返回条件给filter过滤，再对过滤结果进行排序

filter() 不改变源数据

str.indexOf(s):
*若s在str出现，返回s首元素在str的索引
*若s为'',返回0
*若s没有在str出现过，返回-1

sort( (a,b) => {}) 改变源数据 return a-b升序  return b-a 降序

## 8 动画

（1）<transition>

vue动画对css3动画进行了一些封装，写CSS3动画代码，只是类名是固定的。
vue动画显示隐藏元素是立刻执行的，动画只是播放而已，如元素消失了，但是动画在播放

```
<transition>
  属性：
  name 类名的v换成name 如xxx-enter-to
  appear或:appear="true"  页面一刷新就展示动画
  :duration="x ms" 限制自定义动画的时间（动画库无效）,值也可以是 "{enter:..,leave:..}"
</transition>、
```

（2）动画类名

| .v-enter        | 来之前  |
| --------------- | ---- |
| .v-enter-to     | 来之后  |
| .v-leave        | 去之前  |
| .v-leave-to     | 去之后  |
| .v-enter-active | 来的动画 |
| .v-leave-active | 去的动画 |

使用用他们可以替换CSS3动画代码
注意：v-enter v-leave 在获得后生效，马上失去，所以在控制台很难看到这两个类名

```
//若过渡到的状态是原本的样式，如这里的v-enter-to和v-leave,则可以不写
//来之前 = 去之后   来之后 = 去之前
.x-enter,
.x-leave-to {
  width: 0px;
  height: 0px;
}
.v-enter-to,
.v-leave {
  width: 100px;
  height: 100px;
}
//也可以不写下面一段，而把transition属性放在要过渡的元素css里，相同效果，但是不推荐，没这种美观
.v-enter-active,
.v-leave-active {
  transition: 1s;
}
```

（3）修改动画类名

```
<transition enter-to-class="xxx">
  其他类名以此类推
</transition>
```

（4）<transition>生命周期

当需要更加高级复杂的动画时，可以使用生命周期

| before-enter | 相当于.v-enter        |
| ------------ | ------------------ |
| after-enter  | 相当于.v-enter-to     |
| enter        | 相当于.v-enter-active |
| enter-cancel | 来的动画取消时回调          |
| before-leave | 相当于.v-leave        |
| after-leave  | 相当于.v-leave-to     |
| leave        | 相当于.v-leave-active |
| leave-cancel | 去的动画取消时回调          |

使用：

```
<transition @before-enter="enterFrom" @enter="enterActive">
</transition>
<script>
export default {
  methods: {
    enterFrom(el){
      //el为使用动画的组件实例，before，after和cancel都是这样
    },
    enterActive(el,done){
      //done为完成动画时的回调函数，active都是这样
      done(){
        console.log('结束')
      }
    }
  }
}
</script>
```

（5）多个元素的过渡：
只能包裹一个元素，要实现多个元素或者列表渲染的过渡，可以：

- n个元素n个，用不同的name区分，但明显列表渲染的元素不适用

- 用div包裹里的多个元素，但是无法这种实现互斥（布尔值不同）动画效果，极不推荐

- 使用包裹多个元素，必须给每个元素增加独立的key，其他使用与一样

```
<template>
  <div>
    <transition-group>
      <div v-for="i in arr" :key="i" v-show="flag" class="box"></div>
    </transition-group>
</div>
</template>
```

## 9 组件与组件化开发

Vue本身也是一个组件

组件没有配置项el，所有组件组成组件树放到Vue中，由Vue的el挂载

Vue和组件的template必须要有根标签div
组件继承于Vue，基本一样，但是data(){return {}}必须这样写

组件无法使用原生事件，这是因为自定义组件的事件默认都会认为是自定义事件，需要事件修饰符.native让组件认为是原生事件，才能使用

### 9.1 基本使用

分为非单文件组件和单文件组件，非单文件组件了解即可，开发中都是用单文件组件

（1）非单文件组件

```
//非单文件组件
//创建组件构造函数，必须在Vue对象外创建
const cpnConstructor = Vue.extend({
    template: `
      <div>
        html内容
     </div>
   `
});
//注册组件
//在Vue对象外，注册全局组件。Vue内注册是局部组件
Vue.component('cpn',cpnConstructor);
//某个Vue对象内部的components属性，局部组件。    
components: {
  cpn:cpnConstructor
}    
//使用组件
//必须在Vue对象绑定的区域内才能使用。<cpn></cpn>
//全局组件可以在任何Vue对象绑定区域使用。局部组件只能在该Vue对象绑定的区域使用。


//简写和模板抽离：
Vue.component('cpn',{
    template: `
      <div>
        html内容
      </div>
    `
 })

//创建+注册局部组件：Vue对象component属性
cpn: {
  template: `
    <div>
      html内容
     </div>
   `
}

//魔板抽离：将template单独抽离编写，增加可读性。这里只能用id绑定。
//使用时直接 template:’#id名’
//方法一：template标签一般在body外
<template id='id名'>
  <div>
    Html内容
  </div>
</template>

//方法二：该script要在JS代码之前（不常用）
<script type="text/x-template" id="id名">
  <div>
    html内容
  </div>
</script>
```

（2）单文件组件

创建一个单独的.vue文件编写代码，组件文件命名规范：

* 大驼峰或 aaa-bbb 避免与原生标签名冲突

* 为了寻找方便，views组件名一般命名为 ViewsnameXXX，如HomeMain

* 注册子组件时，子组件名不要和子组件内的组件名冲突

```
//单文件组件
//.vue文件  <v回车快速创建结构
<template>
  <div></div>
</template>
<script>
  import cpn from 'xxx'
  export default {
    components: {
      xxx  //注册子组件，底层自动调用Vue.extend()
    }  
  }
</script>
<style scoped lang="less">
//scoped 使组件的样式不受外面营销，也不会影响外面
//lang 指定使用less语法
</style>
```

### 9.2 父子组件通信

2.1 props,emit

（1）props接收父组件参数实现父传子

子组件中的props的变量就能显data()的变量一样使用

//props和data的变量是放在内存不同地方的，但使用方法相同

```
//1.Vue的配置项props，子组件中配置子组件接收的变量
//方式一
props: ['xxx','yyy']
//方式二
props: {
  xxx: Number,
  yyy: String
}
//方式三
props: {
  xxx: {
    type: Number
    //基本数据类型的默认值写法如下，引用数据类型则需要函数形式，如数组默认值 default:()=>[1,2]
    default: 789                //默认值，为了严禁，最好要设置默认值
    require: true               //是否必须传入，默认false
    validator(){return 123,456} //限定传入的值
  }
}
//若设置默认值时数组或对象时，需要这样写，否则高版本的Vue会报错
default(){
  return [] 或 {}
}

//2.父组件中
<子组件 :xxx="父组件的变量"><子组件>
<!--
若传入的是字符串'aaa'，则 xxx="aaa"
若传入的是非字符串或变量，则 :xxx="5" :xxx="str" :xxx="'aaa'"
-->
```

当父组件传给子组件的数据很复杂时，如：

```
//父组件中：
<子组件 :xxx="{a: {aa: {aaa: 123}"></子组件>

//子组件接收
props: {
  xxx: {
    type: Object,
    default(){
      return {}
    }
  }
}

//子组件的模板中使用：
{{xxx.a.aa.aaa}}
```

会出问题，不能从undefine中读取undefine，这是因为有一个时间节点，子组件还未获取到践传过来的数据，此时xxx为空对象，在模板中展示就是从undefine的属性中.undefind
解决：

```
//方式一,props先定义好复杂的数据(不推荐)：
props: {
  xxx: {
    type: Object,
    default(){
      return {
        aa: {aaa: 0}
      }
    }
  }
}
//子组件的模板中使用：
{{xxx.a.aa.aaa}}

//方式二，使用可选链操作符(推荐)：
props: {
  xxx: {
    type: Object,
    default(){
      return {}
    }
  }
}
//子组件的模板中使用：
{{xxx?.a?.aa?.aaa}}

//方式三：方式二 + v-if，更加安全
/*
有些时候用了方式二还是会报错，这可能是子组件内部拿到undefined的原因，可以直接用v-if，
如果数据为undefined就直接不创建DOM了，一劳永逸（v-show不行，因为show是隐藏但不删除
，if是不符合直接删除）
*/
```

同理，数组也会出现undefined的情况，使用数组时{{xxx[0]}}，若xxx还未传入也会报错，可以在父元素中v-if解决。

在网络请求数据等情况也会出现，解决方法一样

（2）emit发射给父组件自定义事件实现子传父

```
//子传父
//1.子组件内，触发子组件的事件，发射自定义事件
<div @click="fun"></div>
fun(){
  //方式一
  this.$emit('xxx')
  //方式二
  this.$emit('yyy',{
    a: 123
  )
}

//2.父组件中
<子组件 @xxx="fun"></子组件>
<子组件 @yyy="fun"></子组件>
fun1(){}
fun2(i){
  //自定义事件的事件对象就是参数对象，所以$event就是被发射事件的参数对象
}

//自定义事件解除，有时会用的高，在子组件中
this.$off('xxx')
```

### 9.3 自定义组件上使用v-model

v-model也可以用在自定义组件上，是结合props和emit的语法糖

v-model的props的默认值是value，emit默认是input，可以通过子组件的model配置项修改默认值

```
<template>
  父组件
  <son1 v-model="msg" />
  <!-- 相当于
  <son1 :value="msg" @input="msg = $event" />
  -->
</template>

<script>
import son1 from './son1.vue'
export default {
  components: {
    son1
  },
  data(){
    return {
      msg: false
    }
  }
}
</script>

<template>
  子组件
  <div @click="$emit('input',value)">{{value}}</div>
</template>

<script>
export default {
  model:{
    //prop: 'pp',  //将value改为pp
    //event: 'ee'  //将input改为ee
  },
  props: {
    value: Boolean
  }
}
</script>
```

### 9.4 非父子组件通信

（1）事件总线

可以js文件中return再引入使用，也可以绑定到vue原型上

```
//1.EventBus.js,使用时导入这个js文件
import Vue from 'vue'
const EventBus = new Vue()
export default EventBus
//2.使用，发射事件的组件中
import EventBus from '...'
EventBus.$emit('...',参数) //参数可不写
//3.在接收的组件中
import EventBus from '...'
EventBus.$on('...',参数 => {})     //参数是发发射里的参数
/*4.在接收的组件中，离开当前组件时，一定要$off将该组件的事件总线监听的事件关掉，否则
会出现一些难以解决的报错（如找不到better-scroll），一般在beforeDestroy中关闭*/
beforeDestroy(){
  EventBus.$off('xxx')     //关闭所有组件中xxx的监听
  EventBus.$off('xxx',fun) //只关闭该组件监听xxx的fun事件函数，监听也需要$on('xxx',fun)
```

第三方库mitt的用法的emit，on，off用法完全一样

（2）Vuex，和订阅者观察者模式的第三方库也是非父子组件通信

### 9.5 获取组件实例对象

组件在mounted后才完全渲染完，所以获取组件实例对象必须在mounted()中或之后

```
//父访问子,返回对象数组
this.$children 
//返回对象数组，是带有ref属性的子组件，以对象的属性形式存放，ref=”key”，key有重名也只返回一个。
this.$refs  
//返回 ref="refname" 子组件实例对象，refname即使是不同组件中也不能重名
this.$refs.refname


//子访问父：
this.$parent //返回父组件对象
this.$root   //返回根组件对象
```

### 9.6 混入mixin

Vue配置项 mixins
两个组件中有完全相同的代码，将其抽离成一个js文件，组件中所有的配置项包括生命周期函数都可以抽离

```
//mixinA.js中
export xxx {
  data(){return {...}},
  methods: {...},
  ...
}
//用到的组件中
import {mixinA} from '...'

mixins: [mixinA]

//全局混入在main.js的Vue配置项mixin: []中,使得所有组件都用到
```

混入规则：

* 若组件中没有的配置项，直接混入

* 有冲突的配置项
  
  1. 非钩子：相同的属性，方法不替换，没有的属性方法混入
  
  2. 钩子：  不管原来有没有，都在原来的基础上直接混入

### 9.6 组件插槽

使组件具有扩展性，用<slot>定义，<slot>没有id，class属性，所以要给插槽样式可以给包含插槽的div样式

```
//默认插槽
//子组件中
<template>
  <div>
    <slot></slot>  
  </div>
</template>

//父组件中
<子组件>
  <h1>123</h1>
  <h2>456</h2>
</子组件>
//或者
<子组件>
  《<h1>123</h1>
  <h2>456</h2>
</子组件>
/*
父组件中的子组件标签内的全部html会替换掉且只会子组件的其中一个<slot>，子组件的<slot>可以有多个
<slot>内可以有html作为默认值
*/
```

```
//具名插槽
//子组件中
<template>
  <div>
    <slot name="aaa"></slot>
    <slot name="bbb"></slot>   
  </div>
</template>
//父组件中
<子组件>
  <h1 slot="aaa">123</h1>
  <h2 slot="bbb">456</h2>
  <h2>456</h2>
</子组件>
//或者
<子组件>
  <template v-slot:aaa>
   123   
  </template>
</子组件>
/*
有名字只会替换对应名字的，没名字的只能替换没名字
*/
```

```
//作用域插槽，子组件的数据可以通过作用域插槽传给父组件
//子组件
<slot :aaa="..."></slot>
//父组件
<子组件>
  <template v-slot:default="ddd">  或者解构出来 {aaa}  使用时 {{aaa}}
    {{ddd.aaa}}
  </template>
</子组件>
//高版本的vue这里template也可以用div
```

### 9.7 全局变量/函数和插件

6.1 全局变量/函数

Vue.prototype = xxx

6.2 插件

组件定义后，使用时要导入，注册，定义变量等，十分麻烦，若一个组件几乎哪里都用到，可以进一步封装成插件，就能this.$xxx直接调用

```
//index.js内
//导入要封装成插件的组件
import Toast from './Toast.vue'
export default {
  //Vue.use()会自动执行install()，并自动传入参数Vue
  install(Vue){
    //创建组件构造器，并实例化
    const toastConstructor = Vue.extend(Toast)
    const toast = new toastConstructor()
    //手动挂载，并创建一个元素
    toast.$mount(document.createElement('div'))
    //将组件的模板添加到body
    document.body.appendChild(toast.$el)
    //添加到Vue原型
    Vue.prototype.$toast = toast
  }
}
//main.js内
import Vue from 'vue'
import ... from ...
Vue.use(...)
//使用
this.$toast.方法()
```

## 10 其他

7.1 Vue.use()

使用需要use的库时，在任何地方use一次就行

不需要use的库，则在每一个需要的组件都要import

7.2 render

render: h => h('App')
功能：没有模板解析器的vue中，解析模板
vue由vue核心和模板解析器组成，但是模板解析器相对有点大，且webpack打包后代码都转化完能解析的，也不需要模板解析器
vue的精简版没有模板解析器，正是考虑到它大且只在开发时用到。
既然没有模板解析器，在开发时，就需要render函数解析模板

7.3 Vue原型对象

```
Vue.prototype指向vue原型对象，vue原型对象._proto_指向Object原型对象
原本VueComponet.prototype._proto_指向Object，但是vue强行把它指向了Vue原型对象
这是为了组件能够调用vue原型对象中的 $xxx 
所以 VueComponent.protype._proto_ === Vue.propotype
也就是，VueComponent new的vc  vc._proto_._proto_指向原型对象 ，而_proto_省略 vc.
$xxx一直找到vue原型对象
```

# 二、Vue模块化

## 1 基本介绍和npm，yum

Vue是一定要打包的，否则页面加载会很慢

```
npm install -g xxx   全局安装xxx
npm install --save xxx  局部安装xxx，只在本项目中使用
npm insyall --save xxx@3.2    安装指定版本 @3 的 3.x.x 的x都是最高，以此类推
npm install --save xxx@latest 安装最新版本
npm install                   根据package.json安装包

没有梯子可以用淘宝镜像源  cnpm

node -v  查看node版本
vue -v   vue脚手架版本，vue的版本在package.json看

vue init webpack xxx   脚手架2创建项目
vue create xxx         脚手架3/4 创建项目

npm run dev     脚手架2运行vue
npm run serve   脚手架3/4 运行vue

npm run build   打包项目的dist文件夹           
```

npm缺点：

- 下载速度慢

- 由于package.json版本号的特点，不同人安装的版本可能小版本不同，可能会出问题

- 装多个包时，若一个包出错了，会把这个出错的日志和其他成功安装的日志混在一起，就很难看出是哪里出错了

yarn就是为了解决npm的这些缺点：

- 下载速度快，yum采用并行安装（npm的单线程）和离线模式（从缓存中读取之前的包）

- yarn的版本号同意了，有一个lock文件，每次装包都会更新lock文件，使得每次拉取下来的项目第三方库的版本号就能统一

- 命令行输出日志简化，命令简化

- 一个包不管被多少包依赖了多少次，安装这个包时，只会从npm来源或yum来源安装

yarn安装和命令：

```
//安装
npm install -g yarn
//查看是否安装成功
yarn

//命令
npm install xxx --save      --->  yarn add xxx
npm install xxx --save-dev  --->  yarn add xxx --dev
npm uninstall xxx --save    --->  yarn remove xxx
npm update --save           --->  yarn upgrade
npm install                 --->  yarn
```

## 2 webpack

```
npm install -g webpack
```

Webpack可以热更新：代码一修改保存后页面自动刷新，但有时不靠谱，还需要自己冷更新，自

己主动刷新页面。
可以兼容任何语法的html，css，js，管理包，并将他们压缩打包
与Grunt和Gulp对比：
Grunt和Gulp可以优化前端开发流程，而webpack是模块化的解决方案，没有可比性，大多数场合webpack都能替代Grunt和Gulp。
Grunt和Gulp的工作方式：一个配置文件中，能明确对某些文件的编译，组合，压缩等操作的具体步骤。
webpack优点：

- 很好的应用于单页面应用

- 同时支持require和import

- 让react，vue等框架在本地开发更快

- 目前最受欢迎的构建工具

（1）package.json

npm init 创建package.json

package.json可以对项目进行各项配置，保存包的信息

（2）webpack.config.js和vue.config.js

分贝是脚手架爱2和脚手架爱3/4的webpack配置文件，内容差不多，webpack.config.js创建项目自带，vue.config.js需要自己创建

```
module.exports={
  //入口，//默认为 ./src/index.js
  entry:'./src/js/main.js',
  //输出  //默认为 ./dist/main.js
  output:{
    path:path.resolve(__dirname,'dist'),//目录
    filename:'m.js' //文件名
  },
  //定义loader，处理非js代码
  module:{
    rules:[
      {
        test:/\.css$/, //要使用loader的文件类型
        use:[‘style-loader’] //使用的loader
      }
    ]
  },
  //解析：即路径映射，省略文件后缀名等
  resolve:{},
  //插件
  plugins:{},
  //开发服务器，用于配置webpack-dev-server选项
  devServer:{}
}
```

loader：

是webpack解析css，less，图片，es6，ts，vue等的工具

## 3 vue-cli

脚手架自动创建目录，自动安装依赖，自动配置webpack

脚手架配置了HTML驼峰标识

es-lint是强制的代码规范，不规范会报错
runtime-compiler runtime-only区别在于template的渲染上
runtime-compiler template-ast-render-vdom-UI
runtime-only render-vdom-UI 效率高些且代码更少，使用这种的更多
虽然only无法解析template，但是vue-loader会把所有template编译成render函数，就能使用。

## 4 Vite

1 创建项目

vite不需要安装，直接使用即可

1.1 式一，需要自己安装路由、pinia等

```
npm init vite@latest
```

安装依赖

```
npm install less less-loader --save-dev
```

1.2 方式二，创建时可以选择是否安装路由，pinia等

```
npm init vue@latest
```

2 必要步骤

设置项目名并选择框架后就创建项目，创建完成后，需要安装依赖

```
cd projectname
npm install
```

3 启动，打包

启动：

```
npm run dev
```

打包：

```
npm  run build
```

3 与webpack的区别

# 三、vue-router

## 1 路由介绍

url的完整写法：协议://服务器地址:端口/….?...
其中?后面的内容就是query，可以通过 $route.query 得到
端口号一般为80

这里的路由指的是一种映射关系
网站开发发展过程：
①后台渲染：html,css,js与后端一起开发。当访问一个网站时，会有JSP等发送一个url，根据

url在后端服务器中取得网站的内容（此时的html，css，js都是在后台先渲染好在发送给客户端），每个网页都有一个url，后台服务器中的url和网页的映射关系就是后台路由。
缺点很明显，前后端混合，不好开发。

②前后端分离，前台渲染：此时的html，css，js放在静态后台服务器中，后台服务器只负责发送数据，访问网站时，先从静态后台服务器中获取网页内容，在浏览器中解析js渲染出网页。当需要请求数据时，再用ajax请求后台服务器的数据。
每访问一个新网页，就会从静态后台服务器中取得相应的html，css，js。本质还是后台路由。

③前端路由：单网页富应用（各个网页实际上是一个个组件），静态后台服务器只有一个html文件，甚至css，js都只有一个。
访问网站时，会一次性从后台服务器得到所有的网页资源。当访问相应的网页时，相应的内容就会显示，其他隐藏，各个网页组件也对应一个url，此时的映射关系都在前端中，就叫做前端路由。

## 2 基本使用

路由的组件不需要注册
未使用的路由组件不创建；跳转新路由后，旧路由销毁。
router是所有路由共有，route是当前激活的路由独有。

```
//1.路由文件一般放在/src/router/index.js
import Vue from 'vue'
import VueRouter from 'vue-router'
Vue.use(VueRouter)

import aaa from '...'            //普通方式导入组件，任何时候都有该组件
const bbb = () => import('...')  //懒加载导入组件，只有使用该组件时才导入

const routes = [
  //name可不写，name在路由跳转时可替代path
  {
    //默认路由，一进入页面就进入该路由，写在普通路由的前面后面都行
    //默认路由不是必须的
    path: '',   //也可以是 '/'
    redirect: ‘/aaa’,  //有多钟写法，但这种最常用
  },
  {
    path: '/aaa',
    name: aaa,
    alias: ['/aaa1','/aaa2'],  //可选参数，路由路径别名
    component: aaa
  },
  {
    path: '/bbb',
    name: bbb,
    component: bbb
  },
  {
    path: '/ccc',
    name: ccc,
    component: () => import(''...)
  },

]
const router = new VueRouter({
  routes
}) 

export default router

/2.main.js中
import router from '...'
... new Vue({
  ...
  router,
  ,,,  
})

//3.用到的组件的template中，router-view可以有多个，一个router-view展示一次路由组件
<router-view></router-view>
```

路由跳转默认是hash模式（url带#），可以在router配置项中修改为history模式（不带#）

```
mode: 'history'
```

hash与history区别：

- hash兼容性比hidtory好点

- hash的 #以及后面的都是哈希值，不会作为路径给服务器；而history整个url都会给服务器；但是url都是前端路由跳转的，整个url给服务器并没有对应的资源，粗线404。若想使用history且请求正常，需要后端解决。

路由跳转：

跳转方式：

- push，整个url入栈，所以可以返回前一个路由

- replace，直接覆盖原有url，所以无法返回前一个路由

跳转类型：

分为声明式导航和编程式导航

编程式导航，后面的代码还会执行

若to内使用了变量，则需要v-bind，否则则不用

```
<!-- 
声明式导航
显示一个a标签，点击会push跳转到/…，跳转后可以返回 
属性：
tag=”标签名”  修改显示的标签，默认a，如button
replace     使用replace修改url
点击route-lick后，会得到router-link-active类，可以在style修改样式，若想重命名该该类：
1.router-link属性active-class=”重命名”，每个都得加或
2.router/index.js中，增加属性linkActiveClass:’重命名’  所以router-link都适用
-->

<router-link to=”/…”>点击</router-link> 
```

```
//编程式导航，如点击事件的事件函数
fun(0}{、
  if(this.$route.path != xxx)        //只有当前路由与跳转路由不同是才跳转，否则会报错
    this.$router.push('/xxx')   //也可以是replace
}
```

router-link的to和this.$router.push里完整写法是{path:’/…’}或{name:’…’}，只有path可简写成’/…’

## 3 路由参数传递

1 params

有些情况path是不能写死的，如用户id，此时需要配置params参数

params是传递参数的方式之一，但一次只能传递一个参数（params）

```
//如user组件
//路由配置中
{
  path:’/user/:aaa’
  component:user
}

//组件中
//第一种
v-bind:to=”’/user/’+ xxx”
this.$router.push('/user/' + xxx)
//第二种，这里只能用name不能用path
v-bind:to=”{name:'...',params:{...}}”
this.$router.push({name:'...',params:{...}})

//若想获得跳转过来的路由参数，可以
this.$route.params.xxx    
```

2 传递对象参数（query）

路由配置的path正常写就行 path: '/aaa'

```
//path name都可以
v-bind:to="{path:'/aaa',query:{a:1,b:2}}"
this.$router.push({}
  path: '/aaa',
  query: {
    a: 1,
    b: 2  
  }
)

//获取传过来的参数
this.$query.a
```

props传递路由参数：

```
 //路由配置项 props
 1.路由中 props:{key:’val’}  组件中 props:[‘key’] 获得写死的参数
 2.路由中 props:true  组件中 props:[‘xxx’] 获得所有的params参数（无法获得query参数）
 3.路由中 props(){}
  3.1 props(){key:’val’}  组件中 props:[‘key’] 获得写死的参数
  3.2 props($router){ xxx:$router.params或query.xxx } 组件中 props:[‘xxx’]
  获得params或query参数，形参$router可以解构赋值
```

## 4 嵌套路由

使用嵌套路由时，嵌套的路由组件也要再用，如：

cpn组件中，使用路由a，a嵌套路由b，则在cpn中用一次，a路由组件中也要用一次，b不用

```
//路由js中
{
  path: '/aaa',
  compoenent: aaa,
  children: [   //使用与 routers: [] 一样，但path不加/，也可以使用默认路由
    {
       path: 'bbb',
       component: bbb
    }
  ]   
}

//用到的组件中
to="/aaa/bbb"
this.$router.push('/aaa/bbb')
```

## 5 动态路由

通常用于权限管理

```
//新增路由，传入的对象和路由配置一样，若添加的路由已存在则会忽略
this.$router.addRoute({
  //添加路由
  path: '/aaa',
  name: 'aaa',
  component: () => import('...')
  ...
))
this.$router.addRoute('aaa',{
  //新增嵌套路由'/aaa/bbb'，第一个参数aaa必须是路由的name
  path: 'bbb',
  ...
))
this.$router.addRoutes(...)  //同时添加多个路由，不过vue3的router4删除了这个

//删除路由，参数必须是路由的name
this.$router.removeRoute('aaa')

//判断是否有某个路由，参数必须是路由的name
onsole.log(this.$router.hasRoute('aaa')

//查看所有路由
console.log(this.$router.getRouters())
```

也可以设置动态默认路由，addRouter添加默认路由或getRoutes[0].redirect = '/xxx'，若修改默认路由时默认路由不在首位则需要找出来

## 6 NotFound路由

ruo访问了没有配置的路由，则不显示任何内容，外面的正常显示，此时可以路由到自己的404页面

```
[
  ...
  {
    path: '/*',
    //或 path: '/:catchAll(.*)',
    component: () => import('...')    
  }
 ...
]
```

和默认路由一样可以写在蹼泳路由前面后面都行

若是 '/*'，NotFound路由必须写在默认路由之后，否则默认路由会是NotFound

若是 '/:catchAll(.*)' 则没有这个问题

## 7 导航守卫

路由元数据：路由配置项meta，可以定义该路由需要用到的数据

也叫路由守卫

可以设置一些条件，在复合条件后才能跳转路由；或跳转后做鉴权或其它属性
路由配置项 meta:{} 在该对象中可自定义属性使用

一般都有三个形参：

- *to 将要跳转的路由

- from 跳转前路由

- next 在函数内部调用 next() 才能继续跳转路由

全局导航守卫

```
//路由index.js 在路由index的全局中
//全局前置守卫（前置钩子）：常用来鉴权
r.beforeEach((to,from,next) => {  //每次切换路由之前与初始化时回调
  //权限校验
  next('/login')
})
/*
next跳转到登录页能成功但会报错，是bug，目前只能catch解决
*/

//全局后置守卫（后置钩子）：常用来设置新路由的网页标题
r.afterEach( (to,from) => { //在跳转完路由后回调
  document.title = to.meta.title
})
/*
在嵌套路由中，若想跳转到子路由中仍然使用父路由的标题，
document.title = to.match[0].meta.title
*/
```

独享守卫

```
//只有跳转该路由才享有
//只有前置守卫，没有后置守卫
{
  path: '/aaa',
  component: aaa,
  beforeEnter((to,from,next) => {})
}
```

组件内守卫

```
/组件的配置项
//只有通过路由方式进入该组件时才会回调这两个钩子
beforeRouteEnter((to,from,next)=>{})
afterRouteLeave((to,from)=>{})
```

## 8 keep-alive

keep-alive：缓存路由
当在一个父路由a中访问了子路由，切换到另一个父路由b再访问路由a，由于a的子路由不使用则被destory()了，不会显示。keep-alive就是不destory，使得再次访问a时，显示子路由

```
<!--
属性：
include="aaa,bbb"   只有name为aaa或bbb的路由才生效
exclude="ccc"       除了name为ccc的路由无效，其他都生效
-->
<keep-alive>
  <router-view></router-view>
</keep-alive>
```

一般会配合路由钩子activated和deactivated使用

# 四、vuex

## 1 基本

Vuex是一个响应式的状态管理工具
状态其实是一个变量，可以给多个组件共享状态（如登录状态等），状态是一个变量。
自己可以定义一个对象，保存各个组件共享的变量，但是这不是响应式的，修改一个组件内的共享变量不会修改所有组件的共享变量，此时就需要Vuex
一般来说，父子之间共享的变量不适宜放在Vuex，直接父子组件通信就行。
单页面时，Vuex的state是data(){}，view是{{}}，action是事件
npm install vuex -save

store有五个配置项：state，mutations，actions，getters，modules

## 2 state

state单一状态树：
只创建使用一个store对象，方便管理，就是单一状态树

```
//src/store/index.js
import Vue from 'vue'
import Vuex from 'vuex'
Vue.use(Vuex)

const store = new Vuex.Store({
  state:{
    //共享变量
  }
})
export default store

//main.js
import store from '...'
... = new Vue({
  ...
  store,
  ...
})

//组件中
this.$store.state.xxx
```

## 3 mutations

官方推荐不应该直接对state进行修改，而是应该通过mutations提交进行修改，这样在Vue开发者工具才能看到数据的变化。

mutations里面的函数都是同步函数

```
mutations: {
  //xxx叫事件类型，(){}叫该事件类型回调函数
  xxx(state){
    state.a = 123
  },
  yyy(state,payload){
    state.b = payload.aaa + payload.bbb
  }
}

//组件中
this.$store.commit('xxx')
this.$store.commit({
  type: 'yyy',
  aaa: 1,
  bbb: 2
})
```

当修改state本来就有的变量，是响应式的；但是如果给state里面的数组/对象增加或删除成员，就不是响应式的，可通过Vue.set()解决

类型常量

```
//为了方便，一般将事件类型在单独的js文件中定义成常量导出
export const xxx = ’xxx’
//在vuex和组件中都导入使用
import {xxx} from ‘...’
//在组件中直接调用，而在mutations中，需要[xxx]调用
```

## 4 actions

里面额的都是异步操作，如果在mutations中定义异步操作，vuedevtools是无法跟踪的，所以需要在actions定义，就可以跟踪。

过于复杂的mutations操作也是放在actions中更好

使用与mutations类似，但是参数是context (相当于store对象)
组件中通过 this.$store.dispatch(‘…’)提交。

若要修改state的值，则需要在actions方法内部 context.commit(‘…’)
同样可以传递参数，使用与mutations一样

由于是异步操作，也能使用Promise 
return new Promise( 但是then在组件里， this.$store.dispatch().then()

## 5 getters

类似于计算属性但有形参，适合重复的操作使用，调用时也不加括号

```
getters: {
  aaa(state){return state.a},
  bbb(state,getters){return state.a + getters.aaa},
  ccc(state,getters){
    return (a,b) => {return state.a + a + b}  
  }
}

//组件中
this.$store.getters.aaa
this.$store.getters.bbb
this.$store.getters.ccc(123,456)
```

## 6 modules

Store是单一状态树，只定义一个store，但是有时候确实又要将共享状态进行划分。
在modules里，每个属性就是一个store对象，可以定义state等
但是一般不在里面再定义modules，也就是store一般就两层模块里定义的，不要与rootstore的同名

模块里面的state参数都是本模块的state
模块里面的state会编译成一个对象放在rootstore中，所以使用时：
this.$store.state.模块名.属性

而getters则编译后直接放在root
this.$store.getters.模块的方法
第二个参数getters是root的getters
只有模块内的getters有第三个参数rootState，调用root的state

mutations的提交一样，事件类型的先在root找，再到模块内找，这也是不起同名的原因

actions的参数context此时是本模块store

## 7 map语法

调用getters时，需要$store.来调用,显得很长，此时想将其映射成计算属性，减少代码。

```
//组件中，以getters为例
import {mapGetters} from 'vuex'

//computed中
//用法1：
...mapGetters(['getters函数','..',...])     //就能直接用getters函数名调用
//用法2：
...mapGetters({
  别名: 'getters函数'            //就能直接用别名调用
})

/*
mapState也是在computed中
还有mapMutations,mapActions，但...mapActions要在methods里面写，注意在vue对象里调用
也要加this
funcname(payload)
*/
```

当vuex中使用modules时，使用了map映射后，依然要使用 moduleName.xxx 调用，若想xxx调用，则：
每个module都要加上与state等同级的 namespaced:true
映射时，加一个moduleName参数 ...mapState('moduleName',[])

## 8 store模块化

将getters，mutations，actions单独放在各自的js文件，导出导入
一般state在insex中不抽离
moduls建立一个文件夹

## 9 vuex数据持久化

# 五、Vue3

## 1 Vue3语法

### 1.1 基本

V版本更新：https://github.com/vuejs/core/releases?after=v3.0.3

Vue3的脚手架最低版本为4.5

查看cue=cli版本：vue -V

创建项目：vue create xxx 里面可以选择vue版本

运行：npm run serve

打包：npm run build

配置文件：vue.config.js

vue3开发者工具：vue.js devtools vue3的版本

比Vue2更轻，更快，使用CompositionAPI（组合式API），更好支持ts

Vue2中的各个配置项叫做OptionsAPI，Vue3都变成了CompositionAPI（组合式API）

一些变化：

```
//main.js
//引入的不再是vue构造函数，而是创建vue的工厂函数
//不能再引入vue import Vue from 'vue' 也就是不兼容一些vue2的写法
import { createApp } from 'vue'
import App from './App.vue'

//创建应用实例对象，类似于vue2的vm，但更轻，少了很多属性方法
const app = createApp(App)   
//挂载，没有$
app.mount('#app')
//使用库
app.use(...)   
```

```
//无论是Vue还是组件，data都是函数形式
data(){
  return {}
}
```

```
<template>
  可以不用根标签了
</template>
```

## 1.2 setup与数据响应式

#### 1.2.1 setup

Vue3使用了CompositionAPI，所有的变量，函数，生命周期钩子等等都用CompositionAPI写在Vue配置项setup中，CompositionAPI需要导入

```
<template>
  {{a}}
  {{fun()}}
</template>

<script>
export default {
  //setup的执行在beforeCreate之前,且只执行一次
  setup(){
    //setup中不需要使用this，setup的this指向undefined
    console.log(this)
    let a = 123
    function fun(){
      return a
    }
    //要在页面上展示的东西必须要return
    return {
      a,
      fun
    }
    /*
    return 的第二种写法，返回渲染函数，需要impoet {h} from 'vue'
    return () => h('h1','abc')   //此时h1就会覆盖全部模板内容
    */ 
  }
}
</script>
```

Vue3中也是可以写Vue2的OptionsAPI，但是Vue3和Vue2的写法不要混着写，如果混着写，变量函数等等Vue3会覆盖Vue2；setup能读取OptionsAPI的东西，反之不能

#### 1.2.2 Vue3响应式

setup里面的数据默认是非响应式的，响应式的数据需要自己定义，这样性能提高了

```
<template>
  <div>模板中使用，都不用.value</div>
  <div>{{a}}</div>
  <div>{{arrRef}}</div>
  <div>{{objRef}}</div>
  <div>{{arrReactive}}</div>
  <div>{{objReactive}}</div>
  {{showData()}}
</template>

<script>
import {ref,reactive} from 'vue'
export default {
  setup(){
    let a = ref(123)
    let arrRef = ref([1,2,3])
    let objRef = ref({
      name: 'lgx'
    })

    let arrReactive = reactive([1,2,3])
    let objReactive = reactive({
      name: 'lgx'
    })
    function showData(){
      //setup中使用，ref对象需要.value，而reactive对象不用
      a.value = 456
      console.log(a.value)

      console.log(arrRef.value[0], objRef.value.name)

      console.log(arrReactive[0], objReactive.name)
    }
    return {
      a,
      arrRef,objRef,
      arrReactive,objReactive,
      showData}
  }
}
</script>

<style>

</style>
```

（1）ref()

ref()与Vue2的ref不一样，Vue2的ref也还可以用

ref()的响应式原理与Vue2的Object.defindProperty()一样，ref()将数据封装成refImpL对象，也叫ref引用对象，简称ref对象

- ref()封装基本数据类型使用Object.defindProperty()，封装引用数据类型时，底层使用了reactive()

- ref对象再setup使用需要.value，在模板中不用，需要.value是因为Object.defindProperty的数据代理

（2）reactive()

使用es6的Proxy对象对数据进行封装，封装称为Proxy对象

- reactive()只能封装引用数据类型，基本数据类型为了方便不用.value，可以将基本数据类型放到一个对象，再把这个对象给reactive()

- setup中和模板中都不用.value

（3）常见的丢失响应式的情况

情况一，取值再赋值给新变量，若取出基本数据类型则丢失响应式，取出引用数据类型则不会

```
<script>
export default {
  setup(){
    let a1 = ref(111)
    let a2 = ref(['111'])
    let a3 = reactive({val: 111, arr: ['111']})

     let b1 = a1.value   //取出基本数据类型，bbb3不是响应式数据
     let b2 = a2.value   //取出引用数据类型，bbb4是响应式数据
     let {val,arr} = a3    //val不是响应式数据，arr是

     return {b1,b2,val,arr}
  }
}
</script>
```

情况二，整个重新赋值，已经不是原来的ref，reactive了

```
<script>
export default {
  setup(){
    let a1 = ref(111)
    let a2 = reactive({val: 111})
    function changeData(){
      a1 = 222
      a2 = {val: 222}
    }
    return {a1,a2}
  }
}
</script>
```

情况三，用ref，reactive来整个重新赋值，这种情况下也会丢失响应式

```
<script>
export default {
  setup(){
    let a1 = ref(111)
    let a2 = reactive({val: 111})
    let a3 = reactive({val: 111)
    let a4 = reactive({val: 111)

    a3 = reactive({val: 222)
    /*在此处重新赋值成另一个reactive
    发现页面还是会正常修改，这是因为此时a3还未return出去
    最终return出去时，是return了最新修改的3
    */
    a4 = {val: 222}
    /*a4则不是响应式的数据
    因为最终return的只是一个普通的对象而已
    */
    function changeData(){
      /*在生命周期钩子或事件函数中修改
      此时a1，a2已经早就return出去了，如果再赋值就不行
      因为重新赋值的话，就算是ref，reactive，也不是原来return出去的那个
      ref，reactive了，Vue只劫持return的数据
      */
      a1 = ref(222)
      a2 = reactive({val: 222})
      /*正确的赋值方式
      a1.value = ref(222)
      a2.val = reactive({val: 222})
      */
    }
    return {a1,a2,a3}
  }
}
</script>
```

总结：

- 情况一取出的值是响应式数据，赋值的变量才是响应式数据

- 响应式数据不要整个重新赋值

（3）Proxy响应式

Object.defineProperty()实现响应式最大的问题就是数组索引修改和对象增加删除属性不能实现响应式，是因为它的set监听不到这些修改，而能实现响应式的push，pop，Vue.set()，Vue.delete()等都是vue2二次封装或自己的API

Vue3响应式通过Proxy和Reflect实现

Proxy：

reatcive()会将数组/对象都封装成Proxy对象，若有嵌套的数组/对象也同样变成Proxy对象

```
 setup(){
      let person = {
        name: 'lgx'
      }
      //第二个参数必填，没有操作就空对象
      //这样就实现了对person对象的代理，对p0的任何操作能都映射到person对象，但还未实现响应式
      let p0 = new Proxy(person,{})
      //实现响应式，由自己定义当p修改时，person对象如何操作
      let p = new Proxy(person,{
        //target是被代理的源对象
        get(target,propName){
          console.log(`读取了${target}对象的属性${propName}`)
          return target[propName]
        },
        set(target,propName,value){
          console.log(`修改了或增加了${target}对象的属性${propName}`)
          return target[propName] = value
        },
        deleteProperty(target,propName){
          console.log(`删除了${target}对象的属性${propName}`)
          return delete target[propName]
        }
      })
      return {p}
    }
```

Reflect：

```
let person = {
  name: 'lgx'
}
//调用
Reflect.get(person,'name')
//修改
Reflect.set(person,'name','aaa')

//Eeflect会返回一个布尔值，表示代码是否出错，进而可以代替try，catch
//不做异常处理，代码出错项目停止
console.log(aaa.name)
//try,catch
try {
  //出错，aaa对象未定义
  console.log(aaa.name)
}
catch(err) {}
//Reflect
if(Reflect.get(aaa,'name'){
  //代码不出错才到这里
}

/*
虽然麻烦，但是Reflect的作用是防止代码出错而停止项目运行，以前是使用大量的try，catch来
防止代码出错停止项目运行，现在使用Reflect会简便很多，且ECMA也陆续将Object的api转移到
Reflect
*/
```

Proxy和Reflect结合：

```
let p = new Proxy(person,{
  get(target,propName){
    return Reflect.get(target,propName)
  },
  set(target,propName,value){
    return Reflect.set(target,propName,value)
  },
  deleteProperty(target,propName){
    return Reflect.delete(terget,propName)
  }
})
```

引用数据类型无论是用ref()还是reactive()封装，最终都是用reactive()封装成Proxy对象，所以，数组索引修改，对象增加删除属性都是响应式的了

（4）判断是否为响应式数据

```
import {isRef,isReactive,isReadonly,isProxy}
/*
由于ref对象和Proxy对象使用readonly和shallowReadonly都会变成Proxy对象，所以
isProxy还是有意义的
*/
```

#### 1.2.3 toRef()与toRefs()

先来看一个需求：

```
//此时在模板中使用就需要  {{obj.a}}
import {reactive, reatcive,toRef,toRefs} from 'vue'
setup(){
  let obj = reactive({
    a: 123,
    b: {c: 456}
  })
  return {obj}
}

//为了方便，省去obj，会有如下思路：
/* 此时在模板中使用 {{a}}
但是此时丢失了响应式，原因是a是新的变量，初始值为 obj.a 也就是123
一个普通的变量a当然是没有响应式的
*/
return {
  a: obj.a
}

//此时，就用到了toRef()
/*
此时在模板中使用 {{a}}  {{c}}
toRef的作用是，将a和c变成ref对象，且这个ref对象的地址指向obj对应的属性，a和c不仅仅是
响应式的数据，且对a和c的修改也会同时修改obj中对应的属性
所以不能用ref()，因为ref()只能将a和c变成新的独立的ref对象，虽然a和c是响应式的，但是对
a和c的修改不能修改obj对应的属性
总结：
toRef()的ref对象的地址与obj一样 
ref()的ref对象的地址与obj的不一样，它在内存中新开辟了空间
*/
return {
  a: toRef(obj,'a')
  c: toRef(obj.b,'c')
}

//toRefs()，对obj第一层的全部属性都使用一次toRef()，简化toRef()操作：
/*
此时模板中使用 {{a}}  {{b.c}}
扩展运算符取出toRefs()返回的属性全是ref对象的对象
*/
return {
  ...toRefs(obj)
}

/*
由于setup只执行一次，所以...toRefs()的属性只有初始的，若以后给obj对象添加了新属性，
没有return，就用不了，为了防止这种情况，应该多return出obj
*/
return {
  ...toRefs(obj),
  obj  
}
```

#### 1.2.4 setup参数与父子组件通信、插槽

（1）Vue2回顾

props：

Vue2中，只要给父组件中的子组件标签 :aaa = "xx" 传入数据，子组件若

- 有props接收，放到this，且可以限制类型，设置默认值等操作

- 没有props接收，都会放到 this.$attrs，无法限制类型，设置默认值等操作

插槽：

Vue2中，只要给父组件中的子组件标签里面放了html，子组件若：

- 有接收，则不妨到this.$slot，而是渲染出来真实DOM

- 没有接收，以虚拟DOM形式放到this.$slot

（2）setup参数props，context

```
export default {
  //props的用法不变，但是如果父组件传入了，就必须接受，否则会有警告
  //父组件传入了aaa
  props:['aaa'],
  //新配置项，发射的自定义事件需要在emiys中声明，否则会有警告
  emits:['hello'],
  setup(props,context){
    //props参数存放父组件传入的参数，是一个Proxy对象，所以props也是响应式的
    console.log(props)
    /*context是一个普通对象，其中3个比较重要的属性方法
    1.attrs，相当于Vue2的$attrs
    2.slots，相当于Vue2的$slots
    3.emit，用来发射自定义事件
    */ 
    console.log(context)
    function fun(){
      context.emit('hello')
    }
    return {fun}
  }
}
```

使用ts时，父组件接收自定义事件的$event参数的类型是 xxx: Event

（3）父组件中获取子组件实例

由于setup中的this指向undefined，所以不能像Vue2一样使用this.$refs，Vue3使用的方法如下：

```
<template>
  父组件
  <son1 ref="son1" />
</template>

<script>
import {ref,onMounted} from 'vue'
import son1 from './son1.vue'

export default {
  components: {
    son1
  },
  setup(){
    let son1 = ref(null)  //子组件实例
    onMounted(() => {
      //模板加载完才能获得子组件实例
      console.log(son1Ref.value.sonName)
      //子组件中return的属性和方法噶，父组件才能获取到
      console.log(son1Ref.value.sonName)
    })
    //必须return才能获取到子组件
    return {son1Ref}
  }
}
</script>
```

nextTick的应用，解决一个问题

```
<template>
  <div ref=box @click="changeMsg">{{msg}}</div>
</template>

<script>
import {ref,nextTick} from 'vue'
export default {
  setup(){
    let msg = ref(123)
    let box = ref(null)
    function changeMsg(){
      msg.value = 456
      console.log(msg.value)
      //问你题就出在这，数据变了模板也变了456，维度这样从DOM取出来还是123
      console.log(box.value.innerText)
    }
    return {msg,box,changeMsg}
  }
}
</script>
```

```
//解决
import {ref,nextTick} from 'vue'
...
async function changeMsg(){
  msg.value = 456
  console.log(msg.value)
  await nextTick()
  console.log(box.value.innerText)
}
...
```

（4）组件v-model

与Vue2相比：

- 删除了model配置项

- props默认值value改为modelValue，emit默认值input改为update:modelValue

- 组件可使用多个v-model

- 除了v-model自带的修饰符外，还可以自定义修饰符

使用：

```
<template>
  父组件
  <son1 v-model="msg" v-model:num="num" />
  <!-- 相当于 
   <son1 :modelValue="msg" @update:modelValue="msg = $event" :num="num" @update:num="num = $event" /> 
  -->
</template>

<script>
import {ref} from 'vue'
import son1 from './son1.vue'
export default {
  components: {
    son1
  },
  setup(){
    let msg = ref(false), num=ref(100)
    return {msg,num}
  }
}
</script>


<template>
  子组件
  <div @click="fun1">{{modelValue}}</div>
  <div @click="fun2">{{num}}</div>
</template>

<script>
export default {
  props:{
    modelValue: Boolean,
    num: Number
  },
  emits: ['update:modelValue','update:num'],
  setup(props,context){
    function fun1(){
      context.emit('update:modelValue',!props.modelValue)
    }
    function fun2(){
      context.emit('update:num',props.num + 1)
    }
    return {fun1,fun2}
  }
}
</script>
```

自定义修饰符：

```
<template>
  父组件
  <son1 v-model.aaa="msg" v-model:num.bbb="num" />
</template>

<script>
...
</script>

<template>
  子组件
  ...
</template>

<script>
export default {
  props:{
    modelValue: Boolean,
    num: Number,
    modelModifiers: {
      aaa: Boolean
    },
    numModifiers: {
      bbb: Boolean
    }
  },
  setup(props,context){
    //当传入了自定义修饰符时，值为true，没有传时modelModifiers为undefined（所以要用可选链操作符）
    //就可以根据true和undefined来进行操作
    console.log(props.modelModifiers?.aaa)
    console.log(props.numModifiers?.bbb)
    ...
  }
}
</script>
```

（5）插槽

默认插槽写不写template都行，但是具名插槽必须这样写，无法再用Vue2的 <子组件 slot="asd">...<子组件>

```
<子组件>
  <template v-slot:asd>
    <div>6666666666</div>
  </template>
</子组件>

<!--
v-slot:[变量]  可以用字符串的变量来控制插槽的名字，此时也叫动态插槽，注意这里只能用变量，不能用字面量
v-slot: 可以简写为 #  如 v-slot:aaa 简写为 #aaa  v-slot:[xxx] 简写为 #[xxx]
-->
```

作用域插槽的 v-slot:defalt="..." 变成了 v-slot="..." 可简写为 #defalut="..."

（6）事件总线

由于Vue3的createApp创建的app没有了$emit，所以Vue2的写法不再适用，官方推荐使用mitt

npm install --save mitt

监听要在派发之前，多注意生命周期

```
// /src/EventBus/index.js
import mitt from 'mitt'
export default new mitt()

//mitt是比较老的库了，实现基于ES5的构造函数且没有做ts支持，会报错，这里童年过类型断言为any解决
//export default new (mitt as any)()


//用到的组件中
import EventBus from '...'
EventBus.emit('xxx',aaa)
function func(aaa){}
EventBus.on('xxx',func)
EventBus.off('xxx',func)
```

### 1.3 常用的组合式API

#### 1.3.1 计算属性

```
import {ref,reactive,computed} from 'vue'
export default {
  setup(){
    let obj = reactive({
      a: 'l',
      b: 'gx'
    })
    //简写 
    obj.c = computed(() => obj.a + obj.b)
    //完整写法
    obj.d = computed({
      get(){
        return obj.a + obj.b
      },
      set(value){
        console.log('该计算属性被修改了')
      }
    })

    //计算属性即可以作为对象的属性，也可以作为单独的变量
    let aaa = ref(computed(() => 123))
    return {obj,aaa}
  }
}
```

#### 1.3.2 过滤器

Vue3删除了过滤器，因为写法不好，也可以完全可以用计算属性和函数替代

#### 1.3.3 watch

必须要ref()，reactive()封装的响应式数据才能使用watch，否则报错

```
setup(){
    //1.监视一个基本数据类型
    let a = ref(123)
    watch(a,(newVal,oldVal) => {
      console.log(newVal)
      //第一次oldVal为undefined
      console.log(oldVal)
    })

    //2.监视多个基本数据类型，并进行配置
    let b = ref(456), c = ref(789)
    watch([b,c],(newVal,oldVal) => {
      //newVal,oldVal都是数组，下标一一对应
      console.log(newVal)
      //第一次oldVal不再是undefined，而是空数组
      console.log(oldVal)
    },{immediate:true})

    //3.监视reatcive()引用数据类型数据
    let d = ref(666)
    let obj = reactive({
      name: 'lgx'
    })
    let arr = reactive([1,2])
    watch([d,obj,arr],(newVal,oldVal) => {
      console.log(newVal)
      //reacive()数据的oldVal无法正常获取（bug），但ref()的oldVal依旧正常
      console.log(oldVal)
    })

    //4.监视ref()引用数据类型数据
    /*
    监视ref()基本数据类型数据，不用.value，因为本身是ref对象
    监视ref()引用数据类型数据，需要.value，从ref对象内拿到Proxy对象
    */
    let arrRef = ref([3])
    watch(arrRef.value,(newVal,oldVal) => {
      //因为底层是借助reatcive()，所以oldVal依旧有bug
      console.log(oldVal)
    })

    //5/深度监视
    /*
    深度监视默认是开启，而且关闭掉
    */
    //6.监视引用数据类型中的某个成员
    /*
    watch只能监视ref()或reactive()数据，因为由reactive()封装的数组/对象的成员中，基本
    数据类型只是普通的变量，而嵌套的数组/对象还是Proxy
    所以，监视数组/对象的成员，其中基本数据类型成员要 () => xxx ，引用数据类型直接监视就行
    */
    let arrOne = reactive([3,4])
    let objOne = reactive({
      a: 123,
      objobj: {b: 12}
    })
    watch([() => arrOne[0], () => objOne.a, objOne.objobj], (newVal,oldVal) => {
      //() => xxx 的oldVal正常了，但是嵌套对象的oldVal依旧有bug
      console.log(oldVal)
    })
    /*这里要监视objOne.objobj，由于它是嵌套对象，有两种写法：
    直接写objOne.objobj，因为它本身就是Proxy对象。此时深度监视适用
    () => objOne.objobj，这样写也行，但是此时需要自己开启深度监视

    */

    return {
      a,
      b,c,
      d,obj,arr,
      arrRef,
      arrOne,objOne
    }
  }
```

虽然情况很复杂，但只要注意以下几点就能理解：

1. 使用watch时，什么时候要.value
   
   watch的数据比必须是ref对象或Proxy对象，若是ref()通过reactive()创建的Proxy对象则需要取出来Proxy对象，所以，ref()基本数据类型和reactive()引用数据类型不用.value，而ref()引用数据类型需要.value

2. 监视数组/对象的某个成员时，什么时候用 ()=>xxx
   
   监听数组/对象某个成员时，需要()=>xxx，而由于reactive()生成的Proxy对象中的嵌套数组/对象也是Proxy对象，所以，监听的成员是基本数据类型时，需要()=>xxx，而监听的是引用数据类型时，可以直接. 也可以()=>xxx

3. ()=>xxx使用与否，oldVal的bug和深度监视的bug是否存在
   
   使用watch时有两个bug，一是监视引用数据类型时oldVal失效，二是深度监视默认开启且无法关闭。而()=>xxx可以看做监视的另一种实现，这两个bug都没有了，所以，监听数组/对象的成员也是数组/对象时，使用. oldVal失效且深度监视默认开启，使用()=>xxx时oldVal正常且需要手动开启深度监视。

watchEffect：

```
export default {
  setup(){
    let obj = reactive({
      a: 1
    })
    let arr = reactive([1,2])

    watchEffect(() => {
      /*
      1.初始调用一次
      2.只监视该函数里面有调用get()的数据（ref()和reactive()的get()都行）
      这里只调用了arr[0]，进而调用了内部的get()，所以只监视arr[0]
      */
     let w = arr[0]
      console.log('watchEffect')
    })
    return {obj,arr}
  }
}
```

watchEffect与计算属性有点类似：

- 计算属性初始调用一次，当计算属性依赖的属性修改时再调用一次

- watchEffect初始调用一次，当waychEffect函数用到数据get，且数据修改时回调一次

#### 1.3.4 祖孙组件通信

也叫跨代组件通信，也叫依赖注入

父子组件通信依旧可用，用法变化详见setup参数

祖孙通信就是，一个组件可以与它的所有后代（包括子组件）进行通信，而不仅仅是孙组件

```
//祖组件
import {ref,reactive,provide} from 'vue'
export default {
  setup(){
    let a = ref(123)
    let b = reactive([1,2])
    let c = 666
    //祖组件提供参数，给的是ref对象/Proxy对象/普通数据那传过去的也是一样的
    provide('a',a)
    provide('bc',{
      b,
      c
    })
  }
}
//后代组件
import {inject} from 'vue'
export default {
  setup(){
    //将祖组件传入的参数注入到后代组件中
    let a = inject('a')
    let b = inject('bc').b
    let c = inject('bc').c
    console.log(a,b,c)
    return {a,b,c}
  }
}
/*
jnject()可以有第二个参数，设置默认值
使用ts时需要限制类型，如分别接收number，ref的number，reactive的xxx
import {Ref,Reactive} from 'vue'
inject<number>()
inject<Ref<number>>()
inject<Reactive<xxx>>()
注意，值也有可能是undefined（未传值时）,要么就设置联合类型，要么给默认值，如：
```

#### 1.3.5 自定义指令

（1）Vue3.0的自定义指令

相比起Vue2，更换了全部生命周期钩子，现在共有7个，分别是：

create,beforeMount,mounted,beforeUpdate,updated,beforeUnmount,unmount

在指令绑定的元素对应的时间节点回调

使用：

```
<template>

  <!-- 传入的参数是字面量，不是变量 -->
  <div v-big.tag="'asdf'">123</div>
</template>

<script>

export default {
  directives: {
    //在模板中使用 v-big
    big: {
      //每个钩子的形参都一样，这是其中比较重要的两个参数
      mounted(el,dir,a,b,c,d){
        //绑定该指令的元素实例
        console.log(el)
        //自定义修饰符
        console.log(dir.modifiers?.tag)
        //参数
        console.log(dir.value)
      }
    }，
    //简写，只在mounted和updated时回调
    small(el,dir){
      console.log('mounted or updated')
    }
  },

}
</script>
```

全局指令：

（2）Vue3.2的自定义指令

```
<script setup>
//命名必须是 vXxx 的形式，在模板中使用 v-xxx
const vBig = {
  mounted(el,dir){
    console.log('mounted')
  }
}
//简写
const small = (el,dir) => {}
</script>
```

ts：

```
<script setup lang="ts">
import {Directive,DirectiveBinding} from 'vue'
const vBig: Directive = {
  mounted(el: HTMLElement, dir: DirectiveBinding){
    /*如果参数传的是对象，如 v-big="{aaa: 123}"
    dir: DirectiveBinding<{aaa: number}>
    */
    console.log('mounted')
  }
}
</script>
```

（3）应用案例

拖拽盒子

```
<template>
  <div v-move class="box"></div>
</template>

<script setup>
const vMove = (el,dir) => {
  el.addEventListener('mousedown',(initE) => {
    let initClientX = initE.clientX - el.offsetLeft
    let initClientY = initE.clientY - el.offsetTop
    function move(e){
      el.style.left = e.clientX - initClientX + 'px'
      el.style.top = e.clientY - initClientY   + 'px'
    }
    document.addEventListener('mousemove',move)
    document.addEventListener('mouseup',() => {
      document.removeEventListener('mousemove',move)
    })
  })
}
</script>

<style scoped>
.box {
  position: absolute;
  top: 0;
  left: 0;
  width: 100px;
  height: 100px;
  border: 1px solid #000;
}
</style>
```

### 1.4 生命周期

（1）基本变化：

1. beforeDestroy和destroyed变成了beforeUnmount和unmounteed

2. Vue2的el未挂载也会走beforeCreate和created，而Vue3不会

3. 依旧可以使用OptionsAPI的生命周期钩子，但也符合上面2条

4. 由于setup在beforeCreate之前执行，Vue3也就把setup认为是beforeCreate和created，因此组合式API没有beforeCreated和created

5. 组合式API的生命周期名字前加on

6. 组合式API和OptionsAPI混着写时，顺序：
   
   setup-beforeCreate(opt)-created(opt)-onBeforeMount(com)-beforeMount(opt).....

（2）使用：‘

```
/*
//Vue2就有
setup (beforeCreate,created)
onBeforeMount
onMounted
onBeforeUpdate
onUpdated
onBeforeUnmount
onUnmounted
onErrorCaptured
onActivated
//Vue3新增
onDeactivated
onRenderTracked
onRenderTriggered
*/
import {onMounted} from 'vue'
export default {
  setup(){
    onMounted(() => {
      console.log('mounted')
    })
  }
}
```

### 1.5 hook函数

将setup中的代码进行封装

Vue2中，一个组件可能会有多个功能，但是这些功能的数据，函数，生命周期等都分散在各个OptionsAPI中，维护起来很不方便。

Vue3中，将每个功能的数据，函数，生命周期等封装在一个hook函数中，需要使用的组件再将其导入，这样每个功能用到的东西都集中在一个文件，维护以及复用都很方便。

hook函数就是组合式API的强有力体现，将某功能用到的东西组合起来，在组件中又将一个个功能组合起来使用。

很类似Vue2中的混入，但由于是封装起来了就不像混入有冲突问题

使用，以获取鼠标坐标的功能为例：

未封装时：

```
<template>
  {{point.x}},{{point.y}}
</template>

<script>
import {reactive,onMounted,onBeforeUnmount} from 'vue'
export default {
  setup(){
    let point = reactive({
      x: 0,
      y: 0
    })
    function clickWindow(e){
      point.x = e.pageX
      point.y = e.pageY
    }
    onMounted(() => {
      window.addEventListener('click',clickWindow)
    })
    onBeforeUnmount(() => {
      window.removeEventListener('click',clickWindow)
    })
    return {point}
  }
}
</script>
```

封装后：

```
// /src/hooks/useXxx.js
import {reactive,onMounted,onBeforeUnmount} from 'vue'

export default function(){
  let point = reactive({
    x: 0,
    y: 0
  })
  function clickWindow(e){
    point.x = e.pageX
    point.y = e.pageY
  }
  onMounted(() => {
    window.addEventListener('click',clickWindow)
  })
  onBeforeUnmount(() => {
    window.removeEventListener('click',clickWindow)
  })
  return point
}


// 用到的组件中
<template>
  {{point.x}},{{point.y}}
</template>

<script>
import usePoint from '../hooks/usePoint.js'
export default {
  setup(){
    let point = usePoint()
    return {point}
  }
}
</script>
```

vue自己也自带一些hook函数，如 import {useAttr} from 'vue'

hook库如vueuse

### 1.6 其他组合式API和新的内置组件

#### 1.6.1 其他组合式API

（1）shallowReactive()和shallowRef()

```
shallowReactive() //只处理数组/对象第一层成员的响应式
shallowRef() //处理基本数据类型与ref()，处理数组/对象时不再做响应式（但由于数组/对象本身是ref对象，所以修改本身是响应式的）
```

（2）readonly()和shallowReadonly()

```
//不管是ref对象还是Prosy对象，使用了readonly()或shallowReadonly()最终都会变成Proxy对象

/*
接收一个响应式数据，加工成只读，与非响应式不同，非响应式时数据改了但Vue没监测到，
readonly是Vue监测到了，但是Vue让它不能修改，数据页面都没改；此外，常用于hook函数
导出不允许修改的数据时使用
*/
readonly 

//接收reactive对象，使得数组/对象第一层是只读；接收ref对象与readonly一样
shallowReadonly 
```

（3）tioRaw()和markRaw()

```
//将reactive()对象还原成非响应式的源对象（不能还原ref对象）
toRaw()

/*
标记一个对象，使其以后不能变成响应式数据.
用途一，给一个响应式数组/对象添加一个成员时，若这个成员深度很深且也不需要做相遇ing是，
则可以使用markRaw这个新成员，提高效率；
用途二，某数组/对象有一个成员是第三方库（如PromiseAll封装多个axios），若将此数组/对象
封装成响应式数据，那作为成员的第三方库里面的数据都会处理一遍，效率大打折扣且这样也没有意
义，对这个成员使用markRaw()就能解决
*/
markRaw()
```

（4）customRef()

用来创建自定义的ref()，可以在set，get中添加自定义的逻辑

```
//实现与ref()功能完全一样的myRef()
import {customRef} from 'vue'
export default {
  setup(){
    function myRef(value){
      return customRef((track,trigger) => {
        return {
          get(){
            track()  //跟踪value的修改
            return value
          },
          set(newVal){
            value = newVal
            trigger()  //通知Vue触发模板的重新解析
          }
        }
      })
    }
    let a = myRef(123)
    return {a}
  }
}

//实现延时2秒再触发的ref()，并做防抖处理
function myRef(value){
  let timer = null
  return customRef((track,trigger) => {
    return {
      get(){
        track() 
        return value
      },
      set(newVal){
        if(timer)  clearTimeout(timer)
        timer = setTimeout(() => {
          value = newVal
          trigger()  
        },2000)
      }
    }
  })
}
```

#### 1.6.2 全局变量/函数和插件

（1）全局变量/函数

从Vue.prototype 变成 app.config.globalProperties

（2）插件

以loading为例

开发组件-挂载-use

```
<template>
  /src/plug/Loading/Loading.vue
  <div class="box" v-show="isShow">loading...</div>
</template>

<script>
import {ref} from 'vue'
export default {
  setup(){
    let isShow = ref(false)

    const show = () => isShow.value = true
    const hide = () => isShow.value = false
    return {isShow,show,hide}
  }
}
</script>

<style scoped>
.box {
  position: absolute;
  z-index: 999;
  left: 50%;
  top: 50%;
  transform: translate(-50%,-50%);
  width: 200px;
  height: 100px;
  border: 1px solid #000;
  text-align: center;
  line-height: 100px;
}
</style>
```

```
// /src/plug/Loading/Loading.js
import {createVNode,render} from 'vue'
import Loading from './index.vue'
export default {
  install(app){
    //创建虚拟DOM
    const LoadingVNode = createVNode(Loading)
    //渲染成真实DOM
    render(LoadingVNode,document.body)
    //Vue2直接挂载Loading本身就好了，因为里面没有其他多余的东西
    //挂载，Vue3由于LoadingVNode里面东西很多，只需要将要用到的东西挂上去
    app.config.globalProperties.$loading = {
      show: LoadingVNode.component.setupState.show,
      hide: LoadingVNode.component.setupState.hide
    }

    //Vue3.0用setupState(此时只能获得return出来的东西)
    //Vue3.2的script setup自动return，所以可以获得所有
    console.log(LoadingVNode.component.setupState)
  }
}

/*ts
import {createVNode,render,App,VNode} from 'vue'
...
install(app: App){
  const LoadingVNode: VNode = createVNode(Loading)
  ...
}
...
*/
```

```
//main.js
...
import Loading from '.../index.js'
createApp(App).use(Loading).mount('#app')
...
```

在需要的组件中使用：

```
<script>
//vUE2中可以直接 this.$loading 使用，而Vue3由于setup的this指向undefine，所以需要以下操作
import {getCurrentInstance} from 'vue'
export default {
  setup(){
    const {appContext} = getCurrentInstance()
    appContext.config.globalProperties.$loading.show()
  }
}
/*ts
import {getCurrentInstance,ComponentInternalInstance} from 'vue'
...
const {appContext} = getCurrentInstance() as ComponentInternalInstance
...
*/
</script>
```

#### 1.6.3 组件新用法

（1）局部组件：就是在父组件中引入的子组件

（2）全局组件，在main中引入并注册，使得在任何的组件中都能直接使用该组件

```
//main.js
...
import cpn from '...'
createApp(App).component(cpn).mount('#app')
```

（3）递归组件：、

情景：父组件中，有如下数据

```
let data = [
  {
    title: '1',
    children: [
      {title: '1.1'},
      {title: '1.2'},
    ]
  },
  {
    title: '2',
    children: []
  }
]
```

传入到子组件中展示，需要好几个v-for，非常不便，此时就可使用递归组件，递归组件一定要有结束条件。

方式一，子组件自己引入自己并使用：

```
<template>
  这是子组件son1
  <div v-for="i in data">
    {{i.title}}
    <son1 v-if="i?.children?.length" :data="i.children" />
  </div>
</template>

<script>
import son1 from './son1.vue'  //son1里面引入自己son1
export default {
  props: {
    data: Object
  }
}
</script>
```

方式二，使用name作为标签：

```
<template>
  <div v-for="i in data">
    {{i.title}}
    <xxx v-if="i?.children?.length" :data="i.children" />
  </div>
</template>

<script>
export default {
  name: 'xxx',
  props: {
    data: Object
  }
}
</script>

<! --
如果使用script setup语法糖，则没有name配置项，所以
需要再弄一个script标签来给name
<script setup>
defineProps({
  data: Object
})
</script>
<script>
export default {
  name: 'xxx'
}
</script>
-- >
```

（4）动态组件：

可以实现多个组件的互相切换，功能类似于tabBar

需要用到Vue3内置组件

```
<template>
  <button @click="cpnIndex = cpnIndex == 0 ? 1 : 0">点我切换组件</button>
  <component :is="cpnArr[cpnIndex]" />
  <!-- 
  若在配置项components注册了，如：
  components: {
    xxx: son1  
  }
  那也可以这样用 is="xxx" 
  -->
</template>

<script>
import {ref} from 'vue'
import son1 from './son1.vue'
import son2 from './son2.vue'
export default {
  setup(){
    let cpnIndex = ref(0)
    let cpnArr = [son1,son2]
    return {cpnIndex,cpnArr}
  }
}
</script>
```

（5）异步组件和分包：

setup()被async修饰，该组件就会变成异步组件

script setup语法糖里使用await，则setup会自动加上async，就会变成异步组件

异步组件需要配合和异步引入组件才能使用

异步引入组件：

引入同步组件：此时只有当子组件引入完时，父组件才会引入，否则就会一直等待子组件引入

```
import xxx from '...'
```

动态引入异步组件：即使子组件没有引入完，父组件也会直接先引入

```
import {defineAsyncComponent} from 'vue'
const xxx = defineAsyncComponent(() => import('...'))
```

Vue3新的内置组件

动态引入异步组件时，子组件还未引入完时，应该给用户提示还在加载中

有两个具名插槽

```
<Suspense>
  <template v-slot:default>
    <xx></xxx>
  </template>
  <template v-slot:fallback>
    <h3>loading...</h3>
  </template>
</Suspense>
```

此外，使用异步组件和后，setup中就可以return一个Promise了，setup当然也可以用async修饰，使得setup里面可以使用await

在没有使用异步组件和之前，setup不能return一个Promise，因为这样模板就拿不到setup中的东西，setup自然也不能用async修饰

分包：

若不使用异步组件，则打包时所有的组件的资源都会放到一起，用户在加载时由于文件过大，页面就会有一段时间的空白，用户体验性差。

使用异步组件后，每个一部组件打包时都会单独抽离它的资源称为另一个包，只有在使用这个组件时才会加载，这样就节省了主包的体积，加载每个包时都加快了速度。

如tabBar对应的页面都会分为独立的包

总结：

- setup()使用async修饰后（Vue3.2 script setup 内，函数外使用await后setup()直接变async）,必须使用defineAsyncComponent引入组件，且在内使用引入的异步组件

- 由于路由js文件无法使用，所以路由组件不能使用async setup()。解决：路由组件内异步引入普通子组件并使用，在该子组件里使用await

（6）缓存组件

里面也可以放普通组件了，使得里面的组件即便被销毁了也能缓存状态。

同时，生命周期发生了变化，不再走onUnMounted，新增了onActivated和onDeactivated

在页面初次加载时，同时走onMounted和onActivated，在以后的每次展示和销毁缓存组件时走onActivate和onDeactivate

因此，缓存组件内只执行一次的操作（如请求数据）可在onMounted内写

属性

max="整数" 限制缓存组件的最大个数

include和exclude 包含和排除组件，值为该组件的name，多个用空格隔开

#### 1.6.3 其他新的内置组件

（1）<Fragment>

这个标签不用写，是内置在Vue中的

它使得template中默认放一个作为根标签，它是不会渲染出来DOM的。

这就是Vue3的template不需要根标签的原因

（2）<Teleport>

用来传送DOM结构，to="css选择器"，里面的html就会传送到对应的位置作为子元素，如to="body"将会把里面的html传送到body作为body的子元素，此时style里面设置对应的样式将会以body作为父元素

但是，动态绑定的数据和事件函数等还是以所在组件的script内为准

经典应用是带有遮蔽层的弹窗

```
<Teleport to="body">
  ...
</Teleprot>
```

的父元素使用了v-show对其无效，但是v-if有效

### 1.7 其他变化

（1）全局API的转移与去除

Vue2中的Vue中的属性方法有些删除了，有些转移到了app

| Vue2                     | Vue3                                                                                      |
| ------------------------ | ----------------------------------------------------------------------------------------- |
| Vue.config.xxx           | app.config.xxx                                                                            |
| Vue.component            | app.component                                                                             |
| Vue.use                  | app.use                                                                                   |
| Vue.directive            | app.directive                                                                             |
| Vue.mixin                | app.mixin                                                                                 |
| Vue.prototype            | app.config.globalPropertise                                                               |
| Vue.config.productionTip | Vue2中之所以会有这个提示，是因为要提示开发者在生产环境中不要使用完整的Vue而应嘎嘎ishi用min的Vue。   删除，因为Vue3会自动判断项目时处于开发环境还是生产环境 |

（2）其他小变化

1. main.js不是引入vue，而是引入createVue工厂函数

2. template里面不再必须根标签

3. data配置项应始终声明为 data(){return{}}

4. 删除了过滤器

5. 过渡类名变更：v-enter v-leave 变为 v-enter-from v-leave-from

6. 删除了按键编码作为事件修饰符，因为兼容性差。删除了案件编码，只能用DOM的addEventListen拿到事件对象中的按键码来监听了

7. 删除了事件修饰符.native，Vue2中自定义组件会将绑定的事件都认为是自定义事件，所以才需要.native告诉他是原生事件；Vue3的自定义组件绑定的事件都认为是原生事件，自定义事件需要在子组件的配置项emits中声明

8. 其他变化详见官方文档

### 1.7 Vue3↑ 新特性

#### 1.7.1 Vue3.2

（1）script setup语法糖

语法特性：

1. 引入子组件不需要注册就能使用

2. script setup中的数据，函数等不再需要return就能在模板中使用

3. script setup内，函数外若使用了await，则setup会自动变成async函数（注意，是script setup里面的函数外使用await后setup才变async，函数内使用await则是正常的async，await语法）

```
<template>
  <xxx></xxx>
  {{a}}
</template>
<script setup>
import xxx from '...'
import {ref} from 'vue'
let a = ref(123)
</script>
```

setup语法糖的父子组件通信写法

由于script setup语法下无法写PotionsAPI，也拿不到setup()的参数，这样之前Vue3.0的父子组件写法就需要新的写法，需要defineProps()和defineEmits()，这两个函数不需要引入。

props

```
//js写法
defineProps({
  aaa: String,
  arr: Number
})
//ts写法一
defineProps<{aaa: string, arr: number[]}>()
//ts写法二
type props = {aaa: string, arr: number[]}
defineProps<props>()
/*
defineProps接收的变量可以在<template>和<style>中直接使用，但是无法直接在setup中使用，解决：
可以 const aaa = defineProps()  然后在 aaa. 来使用
*/
```

带默认值的props

```
//js写法与原来一样
//ts写法
type props = {
  aaa: string
  bbb: number[]
}
withDefaults(defineProps<props>(),{
  //引用数据类型需要函数形式
  aaa: 'asdf',
  bbb: () => [1,2,3]
})
```

emit

```
const emit = defineEmits(['aaa','bbb']) //这条相当于Vue3.0的emits配置项
//某事件函数
const clickEvent = () => {
  emit('aaa')
}
/*
当需要传递多个参数时，js直接传对象，而ts因为不好限定这个对象的类型，所以分多个参数
emit('aaa',{a:1,b:2})   //js，父组件接收时一个对象形参
emit('aaa',a:number,b:number)  //ts，父组件接收时多个形参
*/
```

script setup语法下获取子组件实例或子组件的资源

若子组件使用了script setup，那么父组件默认是可以拿到子组件实例，但是拿不到子组件的任何属性和方法，需要在子组件中主动暴露才能拿到：

由于默认拿不到资源，所以子组件本身的样式也是拿不到的，需要暴露子组件实例

```
<script setup>
import {ref} from 'vue'
let sonRef = ref(null)
let sonName = '157894'
//不需要引入，可直接使用
defineExpose({
  sonRef,
  sonName
})
</script>
```

但是defineExpose暴露的变量不是响应式的（即使是ref和reactive也不行），要想获得子组件实例且是响应式的，可以用发射自定义事件传递响应式数据来代替

（2）style新特性

style内使用v-bind

以script setup的写法为例

```
<template>
  <div class="box">123</div>
</template>

<script setup>
import {ref,reactive} from 'vue'
const size = '50px'
let border = ref('1px solid #000')
let center = reactive({
  va: 'center'
})
</script>

<style>
.box {
  font-size: v-bind('size');
  border: v-bind('border');
  text-align: v-bind('center.va');
}
</style>
```

新选择器

```
<style>
:deep(选择器){
  /* 样式穿透，用于修改第三方组件UI库的样式 */
}
:slotted(选择器){
  /* 插槽选择器，可以设置插槽的样式了 */
}
:global(选择器){
  /* 全局选择器，
     Vue2是在App.vue的style不设置scoped来设置全局样式
     现在可以在让任何组件中设置全局样式了(scoped里面也可以)
  */
}
</style>
```

style module

```
<template>
  <div :class="$style.a">默认module</div>
  <div :class="[m1.b,m1.c]">m1</div>
</template>

<script setup>
//下面的常用于render函数
import {useCssModule} from 'vue'
console.log(useCssModule)  //默认module
console.log(useCssModule('m1'))  //m1
</script>

<style module>
.a {
  width: 100px;
  height: 100px;
  border: 1px solid #000;
}
</style>
<style module="m1">
.b {
  width: 50px;
}
.c {
  height: 50px;
  border: 10px solid #000;
}
</style>
```

## 2 vue router4

vue3使用的路由版本

### 2.1 基本使用

js的路由写法

```
import {createRouter,createWebHashHistory} from 'vue-router'

const routes = [
  {
    path: '/Home',
    component: () => import('../views/Home/Home.vue')
  }
]

const router = createRouter({
  //使用什么模式就要引入什么模式的函数
  history: createWebHashHistory(),   //hash模式
  //history: createWebHistory(),     //history模式
  //history: createMemoryHistory(),  //abstract模式
  routes
})

export default router
```

ts的路由写法，只需要限制routes的类型，routes里面的写法和js一样（嵌套路由也不用限制类型）

```
import {createRouter,createWebHashHistory,RouteRecordRaw} from 'vue-router'

const routes: Array<RouteRecordRaw> = [
  {
    path: '/',
    redirect: '/Home'
  },
  {
    path: '/Home',
    component: () => import('../views/Home/Home.vue')  
  }
]

const router = createRouter({
  history: createWebHashHistory(),  
  routes
})

export default router
```

main中导入并use，注意use要在mount之前

```
...
import router from '...'
createApp(App).use(router).mount('#app')
```

组件里使用（获取参数，跳转等）

在组件的setup的this指向undefine，所以vue2中的this.$route等用不了，新的用法如下

```
<template>
模板中直接$route使用，不需要借助useRoute和useRouter
{{$route}}
{{$router}}
</template><>
<script>
import {useRoute,useRouter} from 'vue-router'
export default [
  setup(){
    const route = useRoute(), router = useRouter()
    /*
    然后就可以用route,router来替代vue2的this.$route和this.$router
    如获取当前url route.path
    如编程式导航就 router.push()
    */  
  }
]
</script>
```

### 2.2 命名视图

```
/ /src/router/index.js
...
{
  path: '/Home',
  components: {
    default: () => import('../views/Home/Home.vue'),
    aaa:() => import('../views/Home/aaa.vue')
  }
},
...

//组件中
<router-view />   展示deafult的组件
<router-view name="aaa" />  展示名为aaa的组件
```

### 2.3 动态路由新增

（1）可选参数

path: '/Home:id?'

（2）pathMatch(正则)，如

path: '/:pathMatch(.*)

### 

### 2.4 导航守卫的一些小变化

（1）next不再是必选参数

```
//老写法，也支持
router.beforeEach((to,from,next) => {
  if(true) next()
})
//新方式，此时参数一定不能有next
router.beforeEach((to,from) => {
  return true
  /* return 的类型
  1. false：取消当前导航。如果浏览器URL被更改（由用户手动或通过后退按钮更改），它将被重置
  为该from路由的URL
  2. '/aaa'：跳转到对应路由
  3. 什么也不返回，undefined或者true  等同于next()
  4. 引发异常：取消导航并调用回调router.onError()
*/
})
```

（2）组件内守卫

变为组合式API，onBeforeRouteUpdate，onBeforeRouteLeave，但是没有onBeforeRouteEnter，只能写成OptionsAPI

使用多个script标签，语言必须相同

```
<script>
import {onBeforeRouteUpdate,onBeforeRouteLeave} from 'vue-router'
export default {
  beforeRouteEnter(to,from){
    console.log('123')
  },
  setup(){
    onBeforeRouteLeave((to,from) => {
      console.log(123)
    })
  }
}
</script>
```

Vue3.2 script setup

```
<script setup>
import {onBeforeRouteUpdate,onBeforeRouteLeave} from 'vue-router'
onBeforeRouteLeave((to,from) => {
  console.log(123)
})
</script>
<script>
export default {
  beforeRouteEnter(to,from){
    console.log('123')
  }
}
</script>
```

### 2.5 路由相关组件的插槽

router-view的默认+作用域插槽，route是当前路由配置，可以获取route.meta等，Component是当前路由使用的组件实例

```
<router-view v-slot:default="{route,Component}">
  <component :is="Component"></component>
</router-view>
```

Vue3要对router-view使用transition和keep-alive，必须是这种写法

```
<router-view v-slot:default="{route,Component}">
  <keep-alive>
    <component :is="Component"></component>
  </keep-alive>
  </router-view>
```

### 2.6 修复了vue2路由的两个bug

bug1：当跳转的路由就是当前路由时，不再像vue2会有警告

bug2：nest()跳转路由时功能正常却有警告

其他的用法基本与vue2一样

## 3 pinia

Vuex4是vue3使用的vuex版本，但是很不方便，推荐使用pinia

```
npm install --save pinia
```

官方推荐的Vuex的代替品，优势：

1. Vue2，Vue3都可以使用

2. 抛弃了mutations，使用state，actions，getters就可以了

3. 不需要嵌套模块

4. 完全支持ts

5. 代码简洁

Pinia支持Vue2和Vue3，下面只记录Vue3的写法

创建store：

```
// /src/store/index.js
import {createPinia,defineStore} from 'pinia'
const pinia = createPinia()

const mainStore = defineStore('main',{
  state(){
    return {
      aaa: 100,
      phoneNumber: 18312345678
    }
  },
  getters: {
    //功能类似于计算属性，也有缓存
    //通过this可调用state，getters
    phoneNumberHide(){
      return this.phoneNumber.toString().replace(/^(\d{3})\d{4}(\d{4})$/,'$1****$2')
      //使用ts时，ts无法根据return自动判断类型，所以需要自行设置返回类型，如 xxx
    }  
  },
  actions: {
    //可定义同步/异步函数
    xxx(){
      //通过this调用store自己的state，actions，getters
      this.aaa += 10
    }  
  }
})

export {
  pinia,
  mainStore
}

//main.js
import {pinia} from './store'
...
app.use(pinia)

//用到的组件中
import {mainStore} from '...'
//store是一个Proxy响应式对
const store = mainStore()
```

steate变量的调用与修改，getters：

```
import {mainStore} from './store'
//store是一个Proxy响应式对象
const store = mainStore()

//1.使用state的变量
//1.1 直接使用
console.log(store.aaa)
//1.2 解构使用
/*
注意，如果再从store结构出来state变量，取出来的不是响应式数据
let {aaa} = store
console.log(aaa)
解决方法,类似于toRef()
import {storeToRefs} from 'pinia'
let {aaa} = storeToRefs(store)
console.log(aaa.value)
*/

//2.修改state的变量
//2.1 修改单个，可以这样修改，因为Vue.js devtools可以检测到
store.aaa++
//2.2 修改多个，同时修改多个时用这种方式，性能会高些
store.$patch({
  aaa: store.aaa + 1
})
//2.3 $patch修改多个的另一种方式，由于是函数，可以写一些业务逻辑
store.$patch((state) => {
  if(state.aaa > 0) state.aaa++
})
//2.4 当球盖的业务逻辑很复杂时，使用actions修改
store.xxx()
//2.5 修改整个state，不常用
store.$state = {
  //全部属性都要改，否则报错
  aaa: 666,
  ...
}

//3 getters
console.log(state.phoneNumber)
console.log(state.phoneNumberHide)
```

store之间的调用：

Vuex的modules用来定义多个store，而pinia删除了modules，使用更好的方式：

多个store用多个defineStore()，若store在另外的文件，引入使用即可

```
const store1 = defineStore('store1',{
  state(){
    return {
      store1Num: 123
    }  
  }
})
const store2 = defineStore('store2',{
  state(){
    return {
      store1Num: store1().store1Num
    }  
  }
})
```

store实例上的API

除了$patch外，还有其他几个

```
//1 $patch
//2 $reset  将state的数据还原成初始值
store.$reset()
//3 $subscrib  每当state的任一属性值发生变化就回调
store.$subscrib((args,state) => {

})
//4 $onAcition 每当action的方法被调用就回调
store.$onAction((args) => {})
```



pinia-plugin-persistedstate 

## 4 Vue使用ts

Vue2以及Vue3中使用OptionsAPI，要用ts需要借助vue-class-component或vue-class-decoretor

vue-class-compoennt是vue官方出的

vue-class-decorator是社区出的，具有vue-class-compoennt的全部功能，在此之上又增加了一些新功能

Vue3中ts直接用就行，写在setup里面或者export default{}外面都行

1. 定义了变量但未赋值，需要指定ts类型，或者定义了对象，未来会给这个对象增加/删除属性，或者用来接收网络请求的数据，就需要预先指定类型

2. 定义了变量且赋值了，则不需要指定ts类型，它自己类型推论就行，但是有时候推论不出来就需要指定ts类型

3. 定义了变量且赋了初始值（如null），但未来可能会赋别的类型，此时需要制定联合类型如 xxx | null

4. 函数形参都要指定ts类型，而返回值一般不用，它自己类型推论就行（但有时候推论不出来就需要指定ts类型）

5. 是在不知道用什么类型那就用any或unkown凑合，如网络请求的数据，传给子组件的网络请求数据等。

使用示例：

```
<script setup lang="ts">
//父子组件通信是传递值，所以props给普通类型
//祖孙组件通信传递响应式数据是传递引用，所以接收时的类型时ref对象或reactive对象
//Ref,Reactive是ref类型和reactive类型，在需要这些类型时可以使用，如Ref<number>

import {ref,Ref,reactive,Reactive} from 'vue'
//基本数据类型以及基本数据类型的数组
const name: string = 'lgx'
let age = ref<number>(23)
let hobbit: Ref<string[]> = ref(['music','play']) 
let useCode = reactive<string[]>(['js','c++'])

//对象以及对象数组
//定义类型
type lgxType = {
  name: string,
  age: number
}
interface LgxInt {
  name: string,
  age: number
}
//有了类型，就可以使用了
//方式一
class LgxClass {
  aaa: LgxInt = { //或者aaa: lgxType 也行
    name: 'lgx',
    age: 23
  }
}
let b = reactive(new LgxClass)
//方式二
let a = reactive<lgxType>({  //或者reactive<LgxInt>()也行
  name: 'a',
  age: 1
})

</script>
```
