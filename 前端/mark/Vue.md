Vue官网：https://cn.vuejs.org/

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

其他指令：

| v-once       | 使得该元素仅渲染一次并缓存起来，在未来数据更新时看到缓存里有就直接跳过，比如使{{}}里的变量不会改变，适合用于数据不会变的场景，可以提高性能          |
| ------------ | -------------------------------------------------------------------------------- |
| v-pre        | 不解析插值语法，直接显示{{ 变量名 }}                                                            |
| v-text=“xxx” | 用xxx的值覆盖标签内的文本变量，会替换掉使用该指令的元素里的所有文本内容 ，若变量为string且string里有html标签，不会解析成标签，只会当成字符串 |
| v-html="xxx" | 在该标签内插入整个html标签，但最好不要使用v-html，非常不安全，容易被窃取cookie中的登录信息                            |
| v-clock      | 还要添加 [v-cloak] {display: none;}的样式，作用是在js未解析出来前隐藏该标签                             |

### 2.2 数据绑定

#### 2.2.1 v-bind

v-bind:属性  可以简写为 :属性    用来动态绑定属性

（1）绑定img的src

只能绑定网络URL，若绑定本地URL无法解析

```
...template
<img src="...网络">   正常
<img src="...本地">   正常
<img :src="netURL">  正常
<img :src="devURL">  无法解析
...
...script
data(){
  return {
    netURL: '...',
    devURL: '...'  
  }
}
...
```

动态绑定本地图片URL无法解析的两种解决办法：

* 将图片放到 /src/static 下就行

* 图片放哪里都行，代码里url放require()里面
  
  ```
  devURL: require('...')
  ```

此外，Vue为了安全，静态的src的url也必须是相对路径或webpack配置的路径，无法使用绝对路径

```
<img src="相对路径如../" />         正常
<img src="文本pack配置的路径如@/" />  正常
<img src="绝对路径如e://" />        无法解析
```

解决方法也是有的，就是动态绑定本地路径，但是由于动态绑定本地URL无法解析，还需要配合require()

```
<img :src="require('e:/...')" />
```

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

双向绑定表单（input表单，textarea表单），不同的表单由不同的效果，v-model绑定type="text"就是:value和@input的语法糖，其他类型的表单时怎样的语法糖详见vue源码。

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
  yyy:{
    bind(element,binding){}      //指令与元素完成绑定时回调
    inserted(element,binding){}  //元素插入到真实DOM后回调
    update(element,binding){}    //模板重新解析时回调
  }
}

//全局指令：
Vue.directive(‘xxx’,{//完整写法}) Vue.directive(‘xxx’,()=>{//简写})
```

常用的自定义指令有：赋值粘贴、长按、防抖/节流、图片懒加载、按钮权限、页面水印、拖拽。

## 3 计算属性/过滤器/侦听器

### 3.1 计算属性

Vue的配置项computed，通过属性之间的计算得到的属性，具有缓存功能。计算属性只能在template只能怪使用，无法在script中使用。

* 比直接在模板中写{{ 复杂表达式 }}代码可读性高

* 与methods最大的区别就是缓存，computed多次调用只计算结果一次并保存，而methods多次调用就多次计算结果，所以compted比methods好很多。

语法类似方法，但不是方法，不能带形参，使用时不加括号。其实本质就是个属性。

```
...template
{{xxx1}}  {{xxx2}}
...

...script
export default {
  ...
  computed: {
    //简写，只有get
    xxx1: function(){
      return ...;
    },
    //完整写法，有get/set
    xxx2: {
      //调用时回调get，修改时回调set(此时可修改计算属性的依赖属性)
      set: function(newVal){
        //newVal是计算属性被修改后的值
      },
      get: function(){
        //get不能带形参
        return ...;
      }
    }
  }
}

...
```

计算属性何时回调：

当计算属性中被调用的数据被修改时，就重新执行一次计算属性并更新缓存。

* 这里说的调用值的是get而不是set，如下面的代码，abc都是get，所以abc被修改时就会重新执行计算属性，而d是set，即使d被修改了也不会重新执行计算属性

* 这里说的被修改指的是，被修改后的值和原来的值不一样，如下面的代码，若a被修改为1，虽然是有修改的操作，但是a的值没有变，所以不会重新执行计算属性

* 计算属性不能return一个函数用于在函数里面做一些操作，因为函数本身是不会变的，这样计算属性的值就不会更新

```
export default {
  data(){
    return {
      a: 1,
      b: 2,
      c: 3,
      d: 4
    }
  },
  computed: {
    //简写，只有get
    xxx1: function(){
      let x = this.c;
      this.d = 123;
      return this.a + this.b;
    }
  }
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

### 3.3 侦听器

vue的配置项，watch。

当侦听的数据修改时回调。

```
/*
1.xxx是data属性或计算属性，不加this，若xxx未定义，不报错但是newValue/oldValue都是undefine
2.若xxx为对象obj里的一个属性，则key不能简写为不带引号，必须 'obj.xxx'
3.若xxx为对象，则它里面的属性发生变化，watch默认不监测（想监测使用深度监测），只有它
这个对象本身发生变化，才会监测（vue本身是可以对这种多层级的属性进行监测的，如各种数
据发生变化都会响应式刷新页面，只能说vue给程序员提供的watch默认不能监测这种多层级）
4.深度监测：想要监测对象xxx中的任意属性发生变化，deep;true
5.和计算属性一样，若修改前后值不变，则不会回调
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

### 3.4 计算属性与侦听器的区别与选择

相同点：

计都是数据需改就会调用一次，数据不变不调用。

不同点：

* 一个计算属性可以侦听多个属性的变化，而一个watch只侦听一个属性的变化。

* 计算属性侧重于几个数据派生出一个新数据并在模板使用；watch侧重于监听数据的变化并处理。

* 计算属性和watch都是懒处理，但是方式不同。计算属性初始时若未在模板使用则不执行，若在模板使用就执行一次；watch初始不执行，需要immediate:true 初始才会执行一次。

* 计算属性只能进行同步操作，watch同步异步都可以

选择：

当需要几个数据通过复杂的表达式派生出一个数据并在模板中使用时，就使用计算属性。

当需要关注数据的变化，并捕获这次变化做一些事情，就使用watch

## 4 生命周期

在vue的创建到销毁的过错中，有一些生命周期函数（也叫钩子），在相应的节点就会回调这些函数，由此可以在vue的相应节点编写代码，实现在特定的时间做特定的事。
生命周期函数与data，methods等同级，函数里面调用data等时也用this

使用示例：

```
created(){
  console.log(''我被创建了)
}
```

（1）组件初始化

① el挂载之前，会创建组件

若无el挂载，会在created后停止。

OptionsAPI在beforeCreated后created前初始化

| 生命周期         | 简介                               | 适合做的事              |
| ------------ | -------------------------------- | ------------------ |
| beforeCreate | 数据监测，数据代理创建之前，此时无法调用data，methods | 插件开发，如在app上注入一些东西。 |
| created      | 数据监测，数据代理创建之后，数据已经全部初始化好，组件创建完毕。 | 网络请求数据、修改数据。       |

② el挂载

beforeMount之前，检查是否有未编译的模板，有则继续无则在运行时实施编译模板得到render函数。

| 生命周期        | 简介                                                                         | 适合做的事        |
| ----------- | -------------------------------------------------------------------------- | ------------ |
| beforeMount | 此时Vue解析完模板，生成虚拟DOM放在内存中，但是还未转成真实DOM，页面也未解析vue语法来渲染。此时若操作DOM无效              | 无            |
| mounted     | 虚拟DOM已经转为真实DOM，并保存一份到 $el 里。此时DOM渲染完成，展示模板，可以操作DOM。mounted之后，一个组件的初始化才真正结束 | 操作DOM、获取组件实例 |

（2）数据更新

此阶段会不断轮循，一旦有数据更新就回调

| 生命周期         | 简介                                                                    | 适合做的事      |
| ------------ | --------------------------------------------------------------------- | ---------- |
| beforeUpdate | 此时数据更新完，但是页面还未刷新，就是model和view不同步，根据新数据生成新虚拟DOM，新旧虚拟DOM比较看是否有复用，刷新成新页面 | 获取更新前的各种状态 |
| updated      | 数据更新完，页面也刷新完，model和view同步                                             | 获取新数据      |

此外，数据更新有一个特殊的钩子

| this.$nextTick(callback) | 在数据更新完，并且真实DOM更新完毕后回调 |
| ------------------------ | --------------------- |

要搞懂nextTick，需要了解数据更新的机制。

Vue中，数据是异步更新的，在数据修改后，并不是立马重新渲染页面的，而是开启一个异步队列并且缓存同一轮事件循环中的**所有数据改变**。在缓冲时会**除去重复**的操作,等到下一轮事件循环时，才开始更新。

来看一个例子就明白了：

```
<template>
  <div>
    <div ref="box">{{msg}}</div>
    <button @click="changeMsg">修改数据</button>
  </div>
</template>

<script>
export default {
  data(){
    return {
      msg: 0
    }
  },
  methods(){
    changeMsg(){
      this.msg++;
      console.log(this.msg);
      //问你题就出在这，数据变了模板也变为1，维度这样从DOM取出来还是0
      //原因是此时DOM还未更新
      console.log(this.$refs.box.innerText);
    }
  }
}
</script>
```

为了能够正确取得值，需要使用nextTick，nextTick回调的时机在数据更新DOM更新完毕后。

```
//解决
...
methods(){
  changeMsg(){
    //为了this指向该组件实例，回调函数不能使用箭头函数
    this.$nextTick(function(){
      this.msg++;
      console.log(this.msg);
      console.log(this.$refs.box.innerText); //1
    });
  }
}
...
```

在nextTick内部，Vue会根据当前浏览器环境优先使用原生的`Promise.then`和`MutationObserver`（现已经换为`MessageChannel` ,是宏任务），如果都不支持，就会采用setTimeout代替。

nextTick应用场景主要有两个：

* 几乎所有更新数据后操作dom的操作，都需要用到nextTick

* mounted之前的钩子DOM都是未挂载完的，如果非要在mounted之前操作DOM，可以使用nextTick

（3）组件销毁

此阶段适合清除定时器、订阅等，防止内存泄漏。

调用$destroy()或路由离开就会销毁组件，

$destroy()会完全销毁实例，并清除与其他实例的链接

清除所有指令和自定义事件（原生事件不清)
大部分情况都不是自己主动调$destroy，而是自动调（如路由切换等）

| 生命周期         | 简介                                      | 适合做的事                        |
| ------------ | --------------------------------------- | ---------------------------- |
| beforeDstroy | 还未开始销毁，还可以调data，methods，但此时对数据的任何修改都无效, | 收尾工作（清除定时器，事件总线上的监听等），防止内存泄漏 |
| destroyed    | 销毁之后，一般很少用这个钩子                          | 清除与其他实例的连接，解绑所有指令和事件监听       |

（4）调试钩子

| errorCaptured | 后代组件出现错误时回调 |
| ------------- | ----------- |

（5）路由钩子

只有该组件配置成路由时才会触发

| activated   | 在跳转到该路由后回调（激活） |
| ----------- | -------------- |
| deactivated | 在离开该路由后回调（失活）  |

（6）父子组件生命周期的顺序

所有组件形成一个组件树，而组件生命周期的顺序就有点像树的后序遍历：

```
function 创建挂载组件(cpn){
  beforeCreate
  created
  beforeMount
  if(有子组件){
    创建挂载组件(子组件A);
    创建挂载组件(子组件B);
  }
  mounted
}
创建挂载组件(根组件);
```

父beforeCreate->

父created->

父beforeMount->

子beforeCreate->

子->created->

子beforeMount->

子mounted->

父mounted->

父beforeUpdate->

子beforeUpdate->

子updated->

父updated->

父beforeDestory->

子beforeDestory->

子destoryed->

父destoryed->

若父组件内有多个子组件，则按照子组件的向后顺序，如：

...->A子beforeCreate->A子->created->A子beforeMount->A子mounted->BbeforeCreate->B子->created->B子beforeMount->B子mounted->...

（7）生命周期小技巧

若每个组件的body样式不同，比较容易想到的解决方式是在每个组件的style设置body，但是由于组件的style一般都会设置scoped，使得body选择器变成body[属性]选择器使得样式无法命中，设置失效。

可以在每个组件的beforeCreate中修改，在beforeDestroy中恢复。

## 5 事件绑定

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

## 6 列表、条件渲染

### 6.1 条件渲染

（1）v-if="xxx" v-else-if="xxx"    v-else
用来控制该元素以及它的孩子的显示与隐藏（隐藏是直接删除，原位置就空出）
else必须与if连在一起用
（2）v-show

v-show="boolean"

原理是根据布尔值来动态修改样式 display: none | block;

（3）v-if，v-show区别

* v-show初始时就创建，根据条件显示隐藏，隐藏时不删除元素，不保留位置（等同于display:none;），<template>无法使用

* v-if初始时不创建，只有true时才创建，false时删除，是直接删除元素（当然也是不保留位置），<template>可以使用

* 需要频繁切换显示隐藏的场景，v-show性能高于v-if，有效防止频繁创建删除；
  
  在不需要频繁切换的场景，由于v-show初始时就会创建，而v-if是俺需创建，所以此时v-if性能高于v-show，有效防止初始时加载过大。

（4）条件渲染与v-once结合

当v-once与 `v-if` 或 `v-show` 一起使用时，一旦我们的元素被渲染一次，`v-if` 或 `v-show` 将不再适用，这意味着如果它在第一次渲染时可见，它将始终可见。如果它是隐藏的，它将永远是隐藏的。

（5）Vue中表单的复用：
在控制input显示隐藏时，若表单已经输入了值，则else切换的另一个表单会保留值，这是因为Vue使用虚拟DOM将元素放到内存中，在渲染时，出于性能考虑，Vue会做一些复用，比如input的复用：
当切换表单时，Vue会发现隐藏表单后，显示另一个表单，所以Vue直接使用原来的表单并保留值，但是会把id，type，class属性等替换成新的。虽然控制台看到的id不同，实际上是同一个表单。
若不想保留值：
在各inpuit中添加key=”key名” 属性，标识input，弱两个表单key一样则可以复用，不一样则

不能复用，并创建新表单，值自然就不会保留。

### 6.2 列表渲染

（1）基本使用：

-for   生成多个该元素/组件（包括孩子），如li
可以循环生成元素及它的孩子，非常好用，如给tr标签v-for，就能迅速生成表格和数
据，且代码量大大减少。也可父子都给v-for形成双重循环
注意这里的for in和JS中的for in的i有区别

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

官方推荐使用v-for时，最好给元素/组件绑定key属性，这是为了更高效更新虚拟DOM以及diff算法通过key比对不出错。

所以只要用了v-for，就要给其指定 :key 作为唯一标识，key最好为数据里的唯一标识属性（如id），若没指定，默认 :key="索引" 。

key工作的原理：

diff算法中，通过key比对。
挂载阶段：数据-虚拟DOM-真实DOM
更新阶段：新数据-新虚拟DOM-新真实DOM
更新数据时，新虚拟DOM与旧虚拟DOM会进行diff算法，根据key进行逐一比较，若有完全相同的元素，就直接复用原来的，增加效率，但是注意输入框的特例，输入框的相同不与文本内容相关，就是文本不同但其他一样，就会复用输入框

若此时使用index作为key，时有一定风险的：

* 新的数据在最后面增删，不影响原本数据顺序，无影响

* 在其他地方增删 就会改变原有数据顺序，或通过排序改变顺序，就会出错
  
  例子：在原有数据最前面插入一个新数据，数据分别为索引key，唯一标识，内容，输入框
  
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

在处理相同元素标签过得时有transition时，相同的元素标签也会使用key，这也是为了Vue能区分它们，否则Vue只会替换其内部属性而不会触发过渡效果。原因是此处不设置key则key都是undefined，通过比对为true，则认为是相同的东西，就会替换，不仅没有过渡，还带来了大量DOM操作。

（3）列表的过滤与排序

v-for常用的一个应用，一般用计算属性或watch实现，计算属性更好。

应用一：列表数据过滤

根据条件，用filter()过滤列表数据。

应用二：搜索内容模糊匹配
效果：输入一个字符串，根据字符串对源数据的内容进行模糊匹配，最终排序显示相应的匹配结果
用到的函数：数组的filter()和sort()，字符串的indexOf() 自定义的防抖函数
原理：以indexOf作为返回条件给filter过滤，再对过滤结果进行排序。

（4）大量数据的列表渲染

所有的前端应用中最常见的性能问题就是渲染大型列表。无论一个框架性能有多好，渲染成千上万个列表项**都会**变得很慢，因为浏览器需要处理大量的 DOM 节点。

```
<div v-for="(i,iIndex) in 100000" :key="iIndex">{{i}}</div>
```

我们并不需要立刻渲染出全部的列表，目前有两种解决方式：

① 分页渲染

有时候后端可能不会帮我们给数据分页，而返回全部数据，我们可以在前端将数据分页，通过切换页数来切换数据渲染。

```
<template>
  <div id="List">
      <div>
        <div v-for="(i,iIndex) in nowPageData" :key="iIndex">{{i}}</div>
      </div>
      <div class="btn">
        <button @click="page <= 1 ? 1 : --page">-</button>
        {{page}}
        <button @click="totalData.length <= size * page ? page : ++page">+</button>
      </div>
  </div>
</template>

<script>
export default {
  data(){
    return {
      page: 1,
      size: 12,
      totalData: []
    }
  },
  computed: {
    nowPageData(){
      return this.totalData.slice((this.page - 1) * this.size, this.size * this.page)
    }
  },
  mounted(){
    //模拟数据
    for(let i =0; i < 1000000; i++)  this.totalData.push(i);
  }
}
</script>

<style scoped lang="less">
#List {
  display: flex;
}
</style>
```

适合用于通过点击页数切换数据的场景，无论页数多大，页面始终显示限定的数量，大大提高性能。

② 长列表分片渲染

有时候后端可能不会帮我们给数据分页，而返回全部数据，我们可以在前端将数据分页，通过懒加载的形式按需添加数据来渲染。

只需要修改①部分代码即可：

```
computed: {
    nowPageData(){
      return this.totalData.slice(0, this.size * this.page);
    }
  },
```

适合用于上拉加载更多或数据量不多的场景。

需要注意的是，若数据量很大，随着页数的不断增加，页面的数据会不断增多，性能会越来越差，页面越来越卡顿。为了解决这个问题，我们使用虚拟列表。

虚拟列表：

虚拟列表（也叫虚拟滚动），效果是始终显示视口区域放得下的数据，其他数据不显示都是空白。

与②懒加载的区别实：②懒加载中数据会随着页数增多而增多，而虚拟列表始终是限制的数据数量。

自己实现虚拟列表不是很容易，可以使用第三方库，主要有两个：

* vue-virtual-scroller，文档：https://github.com/Akryum/vue-virtual-scroller

* vue-virtual-scroll-grid，文档：https://github.com/rocwang/vue-virtual-scroll-grid

以vue-virtual-scroller为例：

```
npm install --save vue-virtual-scroller
```

注册：

```
//main.js
...
import 'vue-virtual-scroller/dist/vue-virtual-scroller.css'
//vue-virtual-scroller@1.x版本的引入方式，2.x引入方式不明
import VueVirtualScroller from 'vue-virtual-scroller'
Vue.use(VueVirtualScroller)
```

使用：

```
<template>
  <div
>   <!-- 未使用虚拟列表 -->
    <!-- <div v-for="(i,iIndex) in list" :key="iIndex">{{i.name}}</div> -->

  <!-- 使用虚拟列表 -->
  <RecycleScroller
    style="height: 200px;"
    :items="list"
    :item-size="32"
    key-field="id"
    :buffer="200"
  >
    <template v-slot="{item}">
      <div class="user">{{ item.name }}</div>
    </template>
  </RecycleScroller>
</div>
</template>

<script>
export default {
  data(){
    return {
        list: []
    }

  },
  mounted(){
    //若页面加载慢，不是因为虚拟列表的原因，而是for循环阻塞了渲染
    //测试数据
    for(let i = 0; i <= 100000; i++){
      this.list.push({
        id: i,
        name: i
      })
    }
  }
}
</script>

<style scoped>
.scroller {

}

/* .user {
  height: 32%;
  padding: 0 12px;
  display: flex;
  align-items: center;
} */
</style>
```

注意事项：

* RecycleScroller必须要设置高度，item-size为每个item的高度也要给，否则会报错

* key-field为item的唯一标识，若不设置默认为'id'；列表数据里面必须邀有一个唯一标识，所以数据必须是对象数组。

* buffer为缓存的item数，适当的设置可以防止滚动时加载数据时的空白。

如果想自己实现虚拟列表，参考以下思路：

1. 准备一个固定高度的父盒子用来展示数据，设置overflow允许y轴滚动

2. 设置每条数据的高度，通过 父盒子高度 / 每条数据高度 计算得出可视区域可以放几条数据，这里记为n

3. 父盒子监听滚动事件并节流，通过 父盒子scrollTop / 每条数据的高度 计算得出被卷去的数据条数，记为m

4. xxx.slice(m,m+n) 取出当前要展示的数据，并在父盒子scrollTop值的地方展示，并清空可视区域外的数据。

5. 功能基本实现，可以继续优化如数据高度不同的情况，数据缓存等

③ 优化数据更新

若数据不会更新，使用v-once

若数据需要更新，可以优化更新的方式，使用v-memo缓存下来，实现有条件的更新。如数据中某些数据不需要更新就永远不给它更新，需要更新的才允许它更新，以此来提高数据的复用率避免不必要的更新

### 6.3 v-if，v-show，v-for两两之间结合使用

（1）v-if，v-for集合使用

应该避免同时使用v-for和v-if。一般有两种情况你会想到同时用v-if和v-for：

```
<!-- 情况一，不想渲染列表的某些子项 -->
<div v-for="i in [1,2,3]" v-if="i > 1"></div>

<!-- 情况二，通过布尔值来控制整个列表的显示隐藏 -->
<div v-for="i in [1,2,3]" v-if="false"></div>
```

情况一：

Vue2中，v-for的优先级高于v-if，这样就会v-for创建每个item，然后再根据v-if删除item，非常浪费性能。不过这样并不会报错，只会有一个警告。

Vue3中，v-if的优先级高于v-for了，底层会先v-if判断再v-for循环创建DOM。先执行v-if，此时i是未定义的，会直接报错。Vue3这样其实更好，直接规避v-if和v-for一起使用。

如果想实现情况一，可以：

* 最佳实现：用计算属性根据条件过滤列表再v-for展示，参考v-for笔记（3），计算属性的性能开销远比v-for与v-if一起使用少得多。

情况二：

虽然Vue2，Vue3都不会报错，但是也不要这样做，有两种更好的实现方式：

* v-for外层包裹一个div或template，或者是li的ul等等
  
  ```
  <template v-if="xxx">
    <div v-for="..." :key="..."></div>
  </template>
  ```

* v-show代替v-if
  
  ```
  <div v-show="xxx" v-for="..." :key="..."></div>
  ```

（2）v-if，v-show同时使用

若v-if为false，那DOM不创建，v-show无意义，只有v-if为true时，v-show才有意义，即v-if优先级高于v-show，这和v-if，v-show的顺序无关。

极不推荐这样做，但还是要了解下

```
<div v-if="false" v-show="false">DOM不创建</div>
<div v-if="false" v-show="true">DOM不创建</div>
<div v-if="true" v-show="false">DOM创建，display:none;</div>
<div v-if="true" v-show="true">DOM创建，display:block;</div>
```

（3）其他

v-show和v-for已经说过，至于v-if，v-show，v-for没有意义。

## 7 动画

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

## 8 组件与组件化开发

Vue本身也是一个组件

组件没有配置项el，所有组件组成组件树放到Vue中，由Vue的el挂载

Vue和组件的template必须要有根标签div
组件继承于Vue，基本一样，但是data(){return {}}必须这样写

组件无法使用原生事件，这是因为自定义组件的事件默认都会认为是自定义事件，需要事件修饰符.native让组件认为是原生事件，才能使用。

子组件分割策略：大组件分为多个小组件，通过props达到更好的复用性。但注意不要过度分割，尤其是为了所谓的组件抽离将一些不需要渲染的组件特意抽出来，实际上组件的性能小号远大于DOM；

需要提醒的是，只减少几个组件实例对于性能不会有明显的改善，所以如果一个用于抽象的组件在应用中只会渲染几次，就不用操心去优化它了。考虑这种优化的最佳场景还是在大型列表中。想象一下一个有 100 项的列表，每项的组件都包含许多子组件。在这里去掉一个不必要的组件抽象，可能会减少数百个组件实例的无谓性能消耗。

### 8.1 基本使用

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

（2）单文件组件（SFC）

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
/*lang 指定使用less语法,若不指定默认为css*/
</style>
```

export default 的对象里面的一个个属性，叫做配置项，也叫做OptionsAPI，有data，methods等，即前面笔记的内容。

单文件组件的几个注意点：

① template

* template不会被渲染成真实DOM，只作代码包裹作用，也可以在HTML里使用，可以使用v-if，v-else-if和v-for，无法使用v-show。由于其不会被渲染的特性，在使用组件库的一些特殊情况也可以使用。

* template必须且只能有一个根标签，原因是虚拟DOM的数据结构就是单根的属性结构。之所以这么设计是因为多跟的话diff不知道新的虚拟DOM子树对应旧虚拟DOM哪个子树

② script

* 除了根组件App.vue的data不用return {}外，其他所有组件都需要return {}
  
  ```
  export default {
    data(){
      return {
        //数据
      }  
    }
  }
  ```
  
  这是因为一个组件可能会在多个地方复用而创建多个组件实例，如果data是一个对象的话就浅拷贝了，使得一个组件实例的数据修改会影响所有该组件的组件实例，data(){return {}} 是为了防止不同组件的data数据之间的冲突，每次创建组件实例调用data函数，return出去后data对象都是独立的了，相当于深拷贝。

③ style

* scoped
  
  scoped 使组件的样式不受外面营销，也不会影响外面，实现style模块化
  
  原理：选择器最后面加上属性选择器[data-v-xxx]，且该组件的每个DOM元素都增加一个相同的属性data-v-xx，xxx为随机哈希值，每个组件的哈希值是唯一的。
  
  注意，若有子组件，则子组件的根会加上父的哈希值，而子组件内部的DOM不加父组件的哈希值。
  
  也就是说，父子同时加了scoped，则父用父的哈希值，子用子的哈希值，子组件的根同时有父子的哈希值
  
  未加scoped的情况：
  
  ```
  <template>
    <div>
      <div class="box"></div>
    </div>
  </template>
  
  <style>
  .box {}
  </style>
  
  <!-- 页面正常渲染 -->
  ```
  
  加了scoped的情况：
  
  ```
  <template>
    <div id="home">
      <div class="box"></div>
    </div>
  </template>
  
  <style>
  .box {}
  </style>
  
  <!-- DOM如下 -->
  <head>
    <style>
      .box[data-v-xxx] {}
    </style>
  </head>
  <body>
    <div id="home" data-v-xxx>
      <div class="box" data-v-xxx></div>  
    </div>
  </body>
  ```
  
  每个组件的style都会单独渲染为一个单独的style标签
  
  scoped的影响总结，以下a代表某组件，b代表a的所有后代组件：
  
  - a，b都没有scoped，样式按照正常的层叠性覆盖，一般都是b比较靠后，所以b福噶a。
  
  - a无scoped，并有，a的样式会影响b，b不影响a，也就是全局样式也会影响有scoped的组件，原因：
    
    ```
    <!-- F12查看 -->
    <!--
    a的样式影响b是因为a的样式没有属性选择器的限制
    b不影响a是因为，a没有属性data-v-b
    -->
    
    <style>
    /*a*/
    .box {}
    </style>
    <style>
    /*b*/
    .box[data-v-b] {}
    </style>
    ```
  
  - a有scoped，b无，a不会影响b，b会影响a
    
    a，b都有scoped，a和b互不影响。
    
    综上，一般开发中，App.vue不加scoped作为全局样式，其他组件一律加scoped。

* 组件库修改样式：
  
  以下a是App.vue，b是App.vue子组件，c是b子组件。
  
  a不加scoped，b、c加。
  
  在b中使用组件库，有两种方式：
  
  * nApp.vue写对应的全局样式，缺点是全局的组件库都修改了。
  
  * 样式穿透 /deep/，在保证不影响其他组件库组件的情况下修改样式
    
    ```
    <template>
      <div>
        <el-input />
      </div>
    </template>
    <!--F12查看HTML
    <div data-v-xxx>
      <div data-v-xxx ...>
        <input class="el-input-inner" ... />
      </div>
    </div>
    -->
    
    <!-- 
    未使用样式穿透前，无法修改样式
    因为scoped使选择器变成 .el-input__inner[data-v-xxx]
    但<el-input>内部没有这个data-v-xxx
    -->
    <style scoped>
    .el-input__inner {}
    </style>
    
    <!--
    使用样式穿透后，选择器变成[data-v-xxx] .el-input__inner
    也就是想找到[data-v-xxx]再找到.el-input__inner
    -->
    <style>
    /deep/ .el-input__inner {}
    </style>
    ```

* 样式引入；
  
  1. script标签内或main.js或被使用的js文件内引入，只要引入了就会作用到全局，引入less会自动解析
     
     ```
     <script>
     import '...'
     </script>
     ```
2. style标签内引入，会受到scoped的影响。less可以引入less和css，css可以引入css和less但less只会解析没有less语法的部分
   
   ```
   <style>
   @import '...';
   </style>
   ```

④ 组件标签

* 自定义组件绑定事件都会认为是子组件发射的自定义事件，所以如果要绑定原生事件的话就需要加修饰符来表明它是原生事件
  
  ```
  <子组件 @click.native="..."></子组件>
  ```

### 8.2 父子组件通信

props,emit，都是响应式的。

（1）props接收父组件参数实现父传子

子组件中的props的变量就能显data()的变量一样使用

//props和data的变量是放在内存不同地方的，但使用方法相同

props除了传递变量外，还能传递函数，但是计算属性不能传。

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

这样会出问题，不能从undefine中读取undefine，这是因为有一个时间节点，子组件还未获取到践传过来的数据，此时xxx为空对象，在模板中展示就是从undefine的属性中.undefind
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

同理，若展示简单的数据但是未及时传过来时，页面会显示undefined，也可以v-if解决

父组件传值时，若传的是对象里面的属性，为了避免出现上述情况，也是用可选链操作符

```
<cpn :xxx="obj?.a" />
```

此外，提高props的稳定性可以提高一些性能：

在 Vue 之中，一个子组件只会在其至少一个 props 改变时才会更新。思考以下示例：

```
<ListItem
  v-for="item in list"
  :id="item.id"
  :active-id="activeId" 
/>
```

在 ListItem组件中，它使用了 `id` 和 `activeId` 两个 props 来确定它是否是当前活跃的那一项。虽然这是可行的，但问题是每当 `activeId` 更新时，列表中的**每一个** ListItem都会跟着更新！

理想情况下，只有活跃状态发生改变的项才应该更新。我们可以将活跃状态比对的逻辑移入父组件来实现这一点，然后让 ListItem改为接收一个 active prop：

```
<ListItem
  v-for="item in list"
  :id="item.id"
  :active="item.id === activeId" 
/>
```

现在，对于大多数的组件来说，activeId改变时，它们的 active prop 都会保持不变，因此它们无需再更新。总结一下，这个技巧的核心思想就是让传给子组件的 props 尽量保持稳定。

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

props的数据与data一样，可以在computed，watch等等中使用

（3）单项数据流

父子组件之间，所有属性都应该满足单向的自上而下的绑定，也就是说，父组件数据的更新能流向子组件，反过来则不行。可以避免子组件意外修改父组件的状态，防止数据流向变得复杂。如通过$parent修改父组件的数据是不合理的。若想修改父组件的数据，只推荐用emit派发自定义事件来修改。

此外，子组件中修改props也是不合理的，每次父组件传入数据更新时，子组件所有属性都会刷新成最新值，这意味着子组件不应该修改props：

在子组件中，通过this或v-model是可以修改props的。虽然修改只会改子组件，不会修改父组件的值，但是应该尽量避免这样做，props应该是只读的。

若修改的是基本类型，Vue也会报一个警告来提示。

若修改的是引用类型，Vue为了节约性能就不会检测，就不会警告，但自己要知道不能这么做。

```
...
<input type="text" v-model="xxx">
{{xxx}}
...
props: ['xxx'],
mounted(){
  this.aaa = 123
}
...
```

一般这种修改props的情况有两种：

* props传过来的作为初始值使用，此时推荐将props的值赋值给data里面的某个属性。

* props传过来的值可能做一些操作，此时推荐使用计算属性。

### 8.3 组件v-model

v-model也可以用在自定义组件上，是结合props和emit的语法糖。

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

Vue2的组件v-model的缺点是只能v-model一个props属性，且若要修改props和emit默认值则需要在子组件里面改，控制权在子组件里。

如果想双向绑定多个，可以使用.sync修饰符。xxx.sync的props的就是xxx，emit为update:xxx。需要双向绑定哪个props由父组件决定，控制权在父组件。

```
<template>
  父组件
  <son1 :xxx.sync="msg" />
  <!-- 相当于
  <son1 :xxx="msg" @update:xxx="msg = $event" />
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
  <div @click="$emit('update:xxx',xxx)">{{value}}</div>
</template>

<script>
export default {
  props: {
    xxx: Boolean
  }
}
</script>
```

虽然组件v-model和sync都是双向绑定，但是也要符合单向数据流的原则（详见8.2），避免通过this直接修改props。正确的做法是通过emit来修改，如上面的代码

### 8.4 非父子组件通信

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

（2）Vuex，数据是响应式的，和订阅者观察者模式的第三方库也是非父子组件通信

（3）透传：attrs和listeners

可以实现父子/祖孙组件通信。父子/祖孙通信方式不同。

子组件中：

可以通过$attrs获取父组件中的子组件标签 :aaa = "xx" 传入数据，子组件若

- 有props接收，放到this，且可以限制类型，设置默认值等操作

- 没有props接收，都会放到 this.$attrs，无法限制类型，设置默认值等操作

可以通过$listeners获取父组件中标签子组件标签中的除了.navtie的事件的相关信息，且不管子组件有没有emit对应的自定义事件也会获取。此外，也可以实现祖孙组件通信。

```
...父组件
<子组件 :aaa="'aaa'" :bbb="'bbb'" @e1="xxx" @e2="xxx" @click.native="xxx"/>
...

...子组件
...
<孙组件 v-bind="$attrs" v-on="$listeners" />
...

<script>
...
export default {
  ...
  props: ['aaa'],
  mounted(){
    this.$emit('el');
    console.log(this.$attrs);  //{bbb: 'bbb'}
    console.log(this.$listeners); //{e1:...,e2:...}
  }
}
</script>
...

...孙组件
<script>
export default {
  mounted(){
    console.log(this.$attrs)
    console.log(this.$listeners)
  }
}
</script>
...
```

（4）依赖注入

实现祖孙组件通信（跨代组件通信）

祖孙通信就是，一个组件可以与它的所有后代（包括子组件）进行通信，而不仅仅是孙组件。

```
...某祖组件中，通过配置项privide提供数据
<script>
export default {
  data(){
    return {
      aaa: 123,
    }
  },
  //provide里面的数据只有提供给后代的作用，不能在该组件中使用
  provide(){
    return {
      aaa: this.aaa,
      bbb: 456
    }
  },
  //测试是否是响应式
  mounted(){
    setInterval(() => {
      this.aaa += 1;
    },1000);
  }

}
</script>
...

...某后代组件中，通过jnject注入数据
<template>
  <div>
    {{aaa}} {{bbb}}
  </div>
<template>
<script>
export default {
  inject: ['aaa','bbb'],
  //inject里面的数据可以像data里面的数据一样使用
  mounted(){
    console.log(this.aaa);
    console.log(this.bbb);
  }
}
</script>
...
```

可以看到，组组件的aaa修改了但是后代组件并没有修改，也就是没有响应式。有两种方式可以解决：

方式一：

传递的参数用一个函数返回

```
...某祖组件中
<script>
export default {
  data(){
    return {
      aaa: 123,
    }
  },
  provide(){
    return {
      aaa: () => this.aaa
    }
  },
  //测试是否是响应式
  mounted(){
    setInterval(() => {
      this.aaa += 1;
    },1000);
  }

}
</script>
...

...某后代组件中，通过jnject注入数据
<template>
  <div>
    {{aaa()}}
  </div>
<template>
<script>
export default {
  inject: ['aaa'],
  //inject里面的数据可以像data里面的数据一样使用
  mounted(){
    //mounted由于只调用一次，看不是有没有变化
    //updated不监听inject数据的修改，所以updated是不会回调的。
    console.log(this.aaa());
  }
}
</script>
```

方式二：

将需要传递的参数定义成一个对象。

官方解释：provide 和 inject 绑定并不是可响应的。这是刻意为之的。然而，如果你传入了一个可监听的对象，那么其对象的 property 还是可响应的。

```
...某祖组件中
<script>
export default {
  data(){
    return {
      aaa: {a: 123},
    }
  },
  provide(){
    return {
      aaa: this.aaa
    }
  },
  mounted(){
    setInterval(() => {
      this.aaa.a += 1;
    },1000);
  }

}
</script>
...

...某后代组件
<template>
  <div>
    {{aaa.a}} {{bbb}}
  </div>
<template>
<script>
export default {
  inject: ['aaa'],
  mounted(){
    console.log(this.aaa.a);
  }
}
</script>
```

此外，依赖注入还可以传入methods的函数，传递与使用方式与data数据一样。但是不能传递计算属性。

传递的函数内部调用的资源都是provide的那个组件的资源。

（5）获取组件实例来实现父子组件通信/兄弟组件通信

### 8.5 获取组件实例对象

获取组件实例对象后，可以访问该组件实例的属性和方法，可以看做是一种组件通信方式，只是比较繁琐。

注意，组件在mounted后才完全渲染完，所以获取组件实例对象必须在mounted()中或之后

普通方法：

```
//父组件获得子组件实例,返回对象数组
this.$children

//子组件获得父组件实例：
this.$parent //返回父组件对象

/*获取根组件实例
这里的根组件并不是根组件App.vue，而是main.js中的
new Vue()，可以获取这个Vue实例中的data数据等。
*/
this.$root
```

ref

```
...
<div ref="xxx"></div>
...
//返回带有ref属性的子组件的对象数组，ref=”key”，key有重名也只返回一个。
this.$refs  
//返回 ref="xxx" 子组件实例对象
this.$refs.xxx
```

注意点：

* ref和id相同名字，不冲突。

* 父组件使用子组件时，即使在不同的组件，子组件里面的ref也不要重名。

* 可以实现父子组件、兄弟组件通信，但都比较繁琐，跟推荐用其他方式。

* 标签里面的ref值和this.$refs.的值必须完全一样，如：
  
  ```
  ...
  <div ref="xxxYyy"></div>
  <div ref="aaa-bbb"></div>
  ...
  console.log(this.$refs.xxxYyy)    //正确
  //console.log(this.$refs.aaaBbb)  //报错
  ```

### 8.6 组件扩展

（1）逻辑扩展

方案有mixin，entends

① 混入mixin

Vue配置项 mixins
两个组件中有完全相同的代码，将其抽离成一个js文件，组件中所有的配置项包括生命周期函数都可以抽离

```
//mixinA.js中
export xxx {
  data(){return {...}},
  methods: {...},
  ...
}
//用到的组件中，局部混入
import {mixinA} from '...'
export default [
  ...
  mixins: [mixinA]
]

//全局混入在main.js
//局部mixin和全局mixin冲突时，局部优先级高
Vue.mixin(...);
```

混入规则：

* 若组件中没有的配置项，直接混入

* 有冲突的配置项
  
  1. 非钩子：相同的属性，方法不替换，没有的属性方法混入
  
  2. 钩子：  不管原来有没有，都在原来的基础上直接混入

缺陷；

当mixin比较多的时候，就需要考虑大量的冲突问题。

② extends

配置项extedns，使用与mixin差不多，区别在于extends只能扩展一个：

```
import {xxx} from '...'
export default {
  ...
  extends: xxx
}
```

extends的冲突规则和mixin一样；若extends与mixin发生冲突，extends优先级高。

Vue构造器Vue.extends()也能实现扩展：

```
let V = Vue.extends(options1);

//options2就是扩展
let vm = new V(options2);
```

（2）内容扩展

扩展方案有组件插槽。

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

Vue2中，只要给父组件中的子组件标签里面放了html，子组件若：

- 有定义插槽接收，则不会放到this.$slot，而是渲染出来真实DOM

- 没有定义插槽接收，以虚拟DOM形式放到this.$slot

### 8.7 全局变量/函数和插件

（1）全局变量/函数

Vue.prototype = xxx

（2）插件

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

（3）Vue.use() 和 import

使用需要use的库时，在任何地方use一次就行，以后在哪里都可以用，但是必须要在app挂载之前use

不需要use的库，则在每一个需要的组件都要import

## 9 Vue底层原理

### 9.1 响应式原理

（1）啥事响应式

数据修改，视图同时会改就是响应式。

原生JS中，修改一个数据后，每个用到该数据的地方都要操作一次DOM来修改视图，十分麻烦。Vue的响应式实现了修改数据就能同步到视图，节省了大量DOM操作，其实这就是MVVM中的数据驱动，开发者只需要关注数据，视图只需要随着数据变化即可。

若Vue没有响应式或某些情况丢失了响应式，则数据修改时，在script中确实改了，当Vue没有监听，视图就不会改。

vue在每次有值修改时，都会再解析一次vue模板，所以{{方法()}}会再调用

（2）原理

通过getter/setter和数据代理实现，Object.defineProperty()同时具备getter/setter和数据代理的功能，所以Vue2选择它来实现响应式。

数据代理：通过一个对象代理对另一个对象的属性的读写操作。
vue实例化一个vm（把data改成了_data），在操作_data里的属性，都需要 _data.xxx 十分麻烦，而事实上我们可以直接 xxx 调用，是因为vue用了数据代理

实例化vm时，给vm增加了data里的所有属性并且都是Object.defineProperty()：

```
let data = {a: 1,b: 2};

function react(data){
  //每个属性都要失业Object.definedProperty()，所以嵌套的需要递归
  for(let k in data){
    if(...) reactive(data[k]);
    else {
      Object.defineProperty(data,k,{
        get(){
          //依赖收集，依赖就是用到该数据的地方
          ...
          return data[k]
        },
        set(newVal){
          data[k] = newVal;
          //根据收集的依赖，通知依赖更新
          ...
        }
      ))
    }
  }
}
```

最终data转成_data，vm中增加_data里的key，通过数据代理管理_data

缺点：

- 数组中的非对象属性不会被添加get，set方法，也就是说，通过索引的方式操作数组，值是改了，但是vue无法监测到，也就没有响应式。
   可以通过数组的7个函数（如push）来操作数组，此时vue能监测到，就是响应式，这7个函数是vue对Array原型中的函数重新封装（先调用原生Array函数，后就重新解析模板等操作）
  push() pop() shift() unshift() splice() reverse() sort()
  以及
  Vue.set(this.数组名,下标,新值);

- 因为添加set，get是在vue实例化的时候进行的，所以在代码运行过程中，若想给对象和数组添加/删除key，是监测不到的，此时需要使用 Vue.set()方法，添加key，注意此时数组中新增的非对象元素也没有get，set，但是数组里新增的对象里的属性有

- Set/Map/WeakSet/WeakMap没有响应式，Vue也没有提供对应的API，但可以通过计算属性解决，通过在聚酸属性中调用一个有响应式的数据使得计算属性收集这个依赖，在每次修改Set/Map/WeakSet/WeakMap的同时修改这个响应式数据，就能间接实现它们的响应式：
  
  ```
  ...template
  {{getSetList}}
  ...
  
  <script>
  export default {
    data(){
      return {
        s: new Set([5]),
        sTrack: false,
      }
    },
    computed: {
      getSetList(){
        let x = this.sTrack;
        return Array.from(this.s)
      }
    },
    mounted(){
      setTimeout(() => {
        this.s.add(6);
        this.sTrack = !this.sTrack;
        console.log(this.s,this.sTrack);
      },2000);
    }
  }
  </script>
  ```

- 由于需要对所有data数据做响应式，嵌套的数据还需要递归，所以性能开销是很大的，降低了项目初始化速度。

（3）去除响应式

在data定义的数据都会变成响应式数据，但是有些数据并不需要响应式，为了节约性能可以去除响应式：

```
export default {
  data: () => ({
    users: {}
  }),
  async created() {
    const users = await axios.get("/api/users");
    this.users = Object.freeze(users);
  }
};
```

### 9.2 虚拟DOM（vdom）

（1）什么是虚拟DOM

虚拟DOM就是一个虚拟的DOM对象，本身是一个JavaScript对象，通过不同的属性描述一个视图结构。

（2）虚拟DOM的好处

将真实元素节点抽象成VNode，有效减少直接操作DOM的次数，从而提高程序的性能：

* 直接操作DOM会额外消耗一些性能去做不必要的事，如diff，clone等操作，一个真实元素上有很多内容，如果对其进行diff操作，会额外diff一些没有必要的内容；同样的若果对其进行clone操作会clone全部内容，这也是没有必要的。但是，如果将这些操作转移到JavaScript对象上，就会变得简单很多。

* 操作DOM是比较消耗性能的，频繁地操作DOM容易引起页面的重绘和回流，但是通过抽象VNode进行中间处理，可以有效减少操作DOM的次数。

方便实现跨平台：

* 同一个VNode可以渲染成不同平台对应的内容，如渲染在浏览器是DOM，渲染在ios、安卓则是对应的控件、可以实现SSR、渲染到WebGL中等等

* Vue3允许开发者基于VNode实现自定义渲染器（render），针对不同平台进行渲染，uniapp就是这么做的。

（3）虚拟DOM如何生成，又如何转为真实DOM

template会被编译器-compiler编译为渲染函数，在接下来的挂载过程中会调用render函数，返回的就是虚拟DOM，在后续的patch过程中转化为真实DOM。

挂载结束后，进入更新流程，一旦响应式数据发生变化，就会引起组件重新render，生成新的虚拟DOM，随后新的虚拟DOM和上一次的渲染结果进行diff算法就能找到变化的地方，从而转化成最小量的DOM操作，高效更新视图。

（4）在diff算法中的作用

### 9.3 diff算法

### 9.4 vue-loader

（1）介绍

vue-loader是用于处理单文件组件（SFC）的webpack loader。

欧了vue-loader后，我们就可以在项目中以SFC的形式编写组件，集合其他loader还可以pug的template，ts的script，less/sass的style

（2）何时生效

webpack预打包、打包的时候以loader的形式调用vue-loader

（3）工作流程

vue-loader执行时，会根据SFC中的template，script，style使用各自的loader处理，最终将这些处理完的块组装为组件模块。

vue-loader底层调用的是vue编译器 @vue/compiler-sfc

### 9.5 template到render的编译过程

（1）渲染函数（render函数）

使用js代码生成HTML

如main.js中的 render: h => h('App')

（2）Vue编译器

Vue中有个独特得编译器模块compolter，主要作用是将template编译为js中可执行的render函数。

这个编译器是非常有必要的，毕竟开发者更愿意编写html的template，而不是手写render函数，手写render函数不仅开发效率低，可读性差，也失去了编译中的优化能力。

（3）编译过程

1. 先对template进行解析（也叫parse），解析结束后得到一个js对象（也叫抽象语法树AST）

2. 然后对AST进行深加工的转换过程（也叫transform），得到深加工的AST

3. 深加工的AST转换为render函数。

（4）Vue编译器执行时机

引入的Vue是开发时还是运行时，执行时机也不同。

Vue由vue核心和编译器组成，但是编译器相对有点大，且webpack打包后代码都转化完能解析的，不再需要编译器，

* webpack引入vue的是精简版，也就是开发时，源码中没有编译器模块，template编译时靠vue-loader来预打包，vue-loader会提前编译template，所以执行时机在预打包阶段。

* 引入带有编译器模块的vue，也就是运行时，编译器的执行阶段在组件的创建阶段

### 9.6 实例的挂载过程

通常指的是app.mount()的过程，主要做了初始化和建立更新机制。

（1）初始化

创建app实例以及各个组件实例，创建过程中进行数据状态的初始化，Options的处理，数据响应式等。

（2）建立更新机制

该步骤会立即执行一个组件更新函数，这回首次执行组件渲染函数得到虚拟DOM，随后执行patch将虚拟DOM渲染完真实DOM；

同时此时组件渲染函数会创建响应式数据和组件更新函数之间的依赖关系，使得数据更新会调用组件更新函数。即在数据和视图之间创建了关联，使得数据变化时视图可以更新

### 9.6 Vue原型

```
Vue.prototype指向vue原型对象，vue原型对象._proto_指向Object原型对象
原本VueComponet.prototype._proto_指向Object，但是vue强行把它指向了Vue原型对象
这是为了组件能够调用vue原型对象中的 $xxx 
所以 VueComponent.protype._proto_ === Vue.propotype
也就是，VueComponent new的vc  vc._proto_._proto_指向原型对象 ，而_proto_省略 vc.
$xxx一直找到vue原型对象
```

# 二、Vue模块化

模块化是在代码层面上，将各类代码或各类功能分成各个模块。

组件化是在UI层面上，布局分成各个小组件。

## 1 npm，yum，pnpm

（1）npm

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

（2）yarn

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

yarn和npm切换；C盘搜索找到.vuerc文件，打开，修改

节点 "packageManager": "npm"

（3）pnpm

performant npm ，意味“高性能的 npm”。pnpm由npm/yarn衍生而来，解决了npm/yarn内部潜在的bug，极大的优化了性能，扩展了使用场景。被誉为“最先进的包管理工具”。

特点：

速度快、节约磁盘空间、支持monorepo、安全性高

pnpm 相比较于 yarn/npm 这两个常用的包管理工具在性能上也有了极大的提升，根据目前官方提供的 benchmark 数据可以看出在一些综合场景下比 npm/yarn 快了大概两倍。

安装：

```
npm install -g pnpm

#查看版本信息
pnpm -v
#升级版本
pnpm add -g pnpm to update
```

设置镜像源：

```
pnpm config get registry   #查看源
pnpm config set registry https://registry.npmmirror.com    #切换淘宝源 
```

其他的像安装依赖、运行项目都和npm一样。

## 2 webpack

webpack是一个模块打包工具，Vue是一定要打包的，否则页面加载会很慢，打包会进行代码压缩等等

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
module.exports = {
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

npm run serve 是根据package.json的entry运行

配置绝对路径：

绝对路径的别名，若保存给变量或拼接字符串时无效

配置忽略后缀：

index.html

loader：

是webpack解析css，less，图片，es6，ts，vue等的工具

（3）配置文件的注意点

配置文件有.js，.ts，.json等格式，都放在项目目录下。

只要是配置文件，一旦修改必须重启项目才会生效

## 3 vue-cli

（1）功能

脚手架自动创建目录，自动安装依赖，自动配置webpack

脚手架配置了HTML驼峰标识

（2）es-lint

es-lint是强制的代码规范，不规范会报错

（3）runtime
runtime-compiler runtime-only区别在于template的渲染上
runtime-compiler template-ast-render-vdom-UI
runtime-only render-vdom-UI 效率高些且代码更少，使用这种的更多
虽然only无法解析template，但是vue-loader会把所有template编译成render函数，就能使用。

（4）配置文件相关

脚手架2的配置文件：webpack.config.js 与src同级目录

脚手架3及以上的配置文件：

被隐藏了不可见，可以在项目目录输入命令，会在项目目录创建xxx.js文件，查看webpack默认配置

```
vue inspect > xxx.js
```

默认配置比较重要的有：

* 绝对路径 @/

* 

若想要自定义webpack配置，要在项目目录下创建vue.config.js文件，编写webpack配置，若默认配置也有对应的配置，则vue.config.js会覆盖默认配置

```
module.exports = {
  ...
}
```

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

（1）使用

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

若想在js文件中引入：

```
import router from '...'
```

（2）路由懒加载

将路由分包，初始时不加载全部的路由，只有用到时才会加载，极大地提高首屏加载性能。

路由配置的component给一个异步的promise导入组件即可。

```
{
  path: '...',
  component: () => import('...')
}
```

这个import()是webpack提供的，作用是返回一个导入组件的Promise，自己也可以用动态import实现

import()还可以结合注释，将大模块的几个页面放到一起。

vite类似的有 rollupOptions 定义分块

```
component: () => import(/*webpackChunkName:"xxx"*/'...')
```

（3）模式

vue-router中，有三种模式，分别是hash，history，memory，其中memory用的比较少。

默认是hash模式，可以在router配置项中修改为history模式或memory模式。

```
mode: 'history'
```

hash，history，memory区别：

相同点：

* 代码中使用的url形式都是一样的。

* 底层实现上都是一样的，最终都是通过监听popstate事件触发路由跳转处理。

它们三者的区别主要是浏览器中地址栏的展示和服务器部署上。

* hash模式，浏览器地址栏会带上 '#' ，‘#’ 以及后面的都是哈希值，兼容性是最好的。
  
  ```
  // '#/home' 就是哈希值
  https://xxx.com/#/home
  ```
  
  哈希值不会不会作为路径给服务器，所以服务器部署上比较简单。

* history模式没有 '#' ，显得更好看。
  
  ```
  http://xxx.com/home
  ```
  
  但是在服务器部署上要做一些特殊的配置和处理。
  
  整个url都会给服务器，但url都是前端路由跳转的，整个url给服务器并没有对应的资源，所以需要做url回退处理，将url去掉后面的前端路由变为正确的域名，否则刷新页面出现404。总之，history模式需要后端去处理。

* memory路由则是把url存到一个对象里，是不可见的，适合于非浏览器（小程序，app），但也不是必须的。

（4）路由跳转

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
fun(0}{
  if(this.$route.path != xxx)        //只有当前路由与跳转路由不同是才跳转，否则会报错
    this.$router.push('/xxx')   //也可以是replace
    /*简写形式下
    普通路由，push()可以是path也可以是name，底层会自动区分
    嵌套路由，push()只能是path，因为name无法区分
    */
}
```

router-link的to和this.$router.push里完整写法是{path:’/…’}或{name:’…’}，只有path可简写成’/…’

跳转之后，编程式导航后面的代码也会执行。

（5）router-link和router-view的原理

router-link实现路由跳转，router-view渲染对应的组件，vue-router初始化会监听popstate事件以此监听编程式导航。

router-link默认生成a标签，点击后是取消默认跳转行为，并执行navigate方法来pushState以激活事件处理函数，点击router-link后页面不会刷新（阻止了浏览器默认行为），而是拿出当前的path和routes中的path匹配，匹配成功后，拿出component给router-view渲染。

## 3 命名视图

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

## 4 动态路由

有些情况path是不能写死的，如用户id，此时可以给路由配置一个params参数变成动态路由。

params是传递参数的方式之一，但一次只能传递一个参数。

```
//如user组件
//路由配置中
{
  //配置动态路由后，必须携带参数才能访问该路由
  //如果动态路由想不携带参数也能访问，可以配置可选参数 path: 'user/:aaa?'
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

注意事项：

一般情况下，路由跳转会销毁跳转前的组件，除非使用了keep-alive，但如果是在动态路由内跳转该动态路由，只是params不一样，该组件不会重新销毁再创建，这会带来一些问题，比如无法进入created请求数据。

解决方法：给router-view一个唯一标识的key，使Vue认为上面的情况跳转前后的组件时不一样的

```
<router-view :key="$route.fullPath" />
```

还有两种特殊的动态路由，不需要params参数：

* path: '/:pathMatch(正则)‘，注意这里的正则不需要//包裹

* NotFound路由，若访问了没有配置的路由，则不显示任何内容，外面的正常显示，此时可以路由到自己的404页面
  
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

## 5 路由参数传递

除了动态路由传递一个params参数外，还可以传递一个对象参数query。

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

路由配置项 props

1. 路由中 props:{key:’val’} 组件中 props:[‘key’] 获得写死的参数

2. 路由中 props:true 组件中 props:[‘xxx’] 获得所有的params参数（无法获得query参数）

3. 路由中 props(){}
   
   * props(){key:’val’} 组件中 props:[‘key’] 获得写死的参数
   
   * props(router){ xxx:router.params或query.xxx } 组件中 props:[‘xxx’]
   
   * 获得params或query参数，形参$router可以解构赋值

## 6 嵌套路由

使用嵌套路由时，嵌套的路由组件也要再用，如：

cpn组件中，使用路由a，a嵌套路由b，则在cpn中用一次，a路由组件中也要用一次，b不用

注意，嵌套路由的name也是全局唯一的，不能和任何路由的name相同。name可以和普通路由一样用作跳转等。

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

应用场景：

当页面足够复杂，有公共的部分希望能够复用使用的时候，就可以使用嵌套路由。

如项目的某些是由多层级组件组合而来的（如左侧菜单栏跳转的页面），在这种情况下，url各部分通常对应某个嵌套的组件。

```
菜单栏    |              主视图
...      |       这是一个管理页面，这部分是不变的
管理      |     
--商品管理 | 点击切换商品管理或者订单管理，这部分是会百年的
--订单管理 |
...       |
```

底层实现原理：

vue-router内部有一个deep属性，是通过provide，inject传递下去的，每个层级都能拿到对应的深度，再从match的匹配数组中根据deep得到对应的组件并渲染之。

## 7 动态添加/删除路由

这个和前面的动态路由不是一个东西，注意区分。

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

## 8 导航守卫

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

## 9 keep-alive

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

## 10 如何从零开始写一个vue-router

需求分析：

首先思考vue-router解决的问题：url的变化和组件之间产生映射关系，当用户点击跳转控件，内容就会切换，并且不刷新页面。

实现思路：

1. 自定义一个createRouter函数创建一个router实例，实例里面需要做几件事：
   
   * 保存用户传入的配置项
   
   * 监听hashchange事件或popstate事件处理跳转
   
   * 定义一个响应式数据url，给router-view监听使用
   
   * 回调里根据path匹配对应的component并渲染之
   
   * 借助hash或history.api实现url跳转页面不刷新

2. 将router定义成一个Vue插件，即实现install方法，内部要做两件事：
   
   * 实现两个全局组件router-link和router-view
   
   * 实现亮哥哥全局变量，$route/r

# 四、vuex

## 1 基本

Vuex是一个响应式的状态管理工具
状态其实是一个变量，可以给多个组件共享状态（如登录状态等），状态是一个变量。
自己可以定义一个对象，保存各个组件共享的变量，但是这不是响应式的，修改一个组件内的共享变量不会修改所有组件的共享变量，此时就需要Vuex
一般来说，父子之间共享的变量不适宜放在Vuex，直接父子组件通信就行。
单页面时，Vuex的state是data(){}，view是{{}}，action是事件
npm install vuex -save

store有五个配置项：state，mutations，actions，getters，modules

## 2 注册使用和state

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
//与peops一样可以在computed，watch中使用
```

若想在js文件中使用：

```
import store from '...'
```

## 3 mutations

官方推荐不应该直接对state进行修改，而是应该通过mutations提交进行修改，这样在Vue开发者工具才能看到数据的变化，mutations也只是为了devtools能追踪到修改，mutations是vuex修改state数据的唯一途径。

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

监听vuex状态的变化：

vue devtools是追踪vuex状态的变化，如果现在代码里监听并回调处理，有两种办法：

* watch，可以监听单个状态，且可以获得修改前的值

* vuex的API，store.subscribe()，但是所有的mutations修改都会回调，所以需要根据是哪个mutations来判断是哪个状态变化了，且无法获得修改前的值
  
  ```
  store.subscribe((mutation,state) => {
    if(mutation.type === 'add'){
      console.log('add被提交了')  
    }
  })
  ```

watch更简单易用，store.subscribe适合开发vuex插件

## 4 actions

里面额的都是异步操作，如果在mutations中定义异步操作，vuedevtools是无法跟踪的，所以需要在actions定义，就可以跟踪。

过于复杂的mutations操作也是放在actions中更好

即actions放异步和复杂的mutations，但最终还是需要

通过mutations来修改数据。

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

store是单一状态树，只定义一个store，但是有时候确实又要将共享状态进行划分，比如当项目很大时就一定是需要粉模块的。
在modules里，每个属性就是一个store对象，可以定义state等，但是一般不在modules里面再定义modules，也就是store一般就两层，这是为了不让store更复杂。

modules里定义的状态不要与rootstore的同名

```
// /store/moduleA.js
...

//// /store/index.js
import {moduleA} from '...'
...
module: [moduleA]
...
```

注意事项：

* 模块里面的state参数都是本模块的state，但是模块里面的state会编译成一个对象放在rootstore中，所以使用时：this.$store.state.模块名.属性

* 而getters则编译后直接放在root：this.$store.getters.模块的方法，第二个参数getters是root的getters；只有模块内的getters有第三个参数rootState，调用root的state

* mutations的提交一样，事件类型的先在root找，再到模块内找，这也是不起同名的原因

* actions的参数context此时是本模块store

命名空间namespace：

给模块开启命名空间，使用更方便：

```
...
modules: [
  moduleA: {
    namespace: true,
    ...  
  }
]
...
```

...

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

Vuex的数据在页面刷新后就会全部丢失，想要持久化存储

就需要将Vuex的数据保存到storage中，或存到数据库中（存到数据库中比较少见就不赘述了）

```
//store/index.js
...
state: {
  a: localStorage.getItem('a') ? JSON.parse(localStorage.getItem('a')) : null
},
mutations: {
  updateA(state,payload){
    state.a = payload.a;
    localStorage.setItem('a',JSON.stringify(a));;  
  }
}
...
```

可以看到，虽然实现了持久化，但是state里面都要获取storage的值，且每次修改数据都要在state和storage里修改一次，十分繁琐。

推荐的做法就是使用Vuex插件来管理这些操作，有第三方的插件，也可以自己写插件。

实现方式：

（1）每次存取都调用storage，缺点已经说了不再赘述。

（2）第三方vuex插件：

有vuex-persistedstate和vuex-persist，这里只介绍vuex-persistedstate

```
npm install --save vuex-persistedstate
```

使用：

```
// /store/index.js
...
import createPersistedstate from 'vuex-persistedstate'
...
export default new Vuex.Store({
  state: {
    aaa: 0;
  },
  mutations: {
    updateAaa(state,payload)[
      state.aaa = payload.aaa;
    ]
  }
  plugins: [
    //默认情况下，使用localStorage持久化所有state数据
    createPersistedstate(),
    //使用指定的存储方式，指定存储什么数据
    /*
    createPersistedstate({
      storage: window.sessionStorage,
      reducer(state){
        return {
          aaa: state.aaa
        }
      }
    })
    */
  ]
  ...
})
...
```

注意点：

* 这么配置后，vuex照旧操作就能实现持久化

* 必须通过mutations修改数据，createPersistedstate才生效。

* 数据保存在 localStorage.vuex 中

（3）自定义vuex插件，用的比较少，毕竟有现成的库。

（4）还有一种方式是把vuex的数据存到数据库中，但是用的比较少

## 10 如何从零开始实现Vuex

需求分析：

vuex是一个状态管理工具，需要确保管理的状态以可预见的方式变更。需要实现：

* 一个store存储全局状态

* 修改状态的API commit(type,payload) 和 dispatch(type,payload)

实现思路：

* 定义store类，构造函数接收options，设置state并对外暴露，state里面需要设置成响应式数据，提供commit和dispatch，同时store要定义我一个Vue插件

* commit可以根据传入的typr调用对应的mutations来修改数据；dispatch类似，不过要考虑可能是异步的，需要返回一个Promise给用户处理结果。

# 五、Vue3

## 1 Vue3语法

### 1.1 基本

Vue版本更新：https://github.com/vuejs/core/releases?after=v3.0.3

Vue3的脚手架最低版本为4.5

查看cue=cli版本：vue -V

创建项目：vue create xxx 里面可以选择vue版本

运行：npm run serve

打包：npm run build

配置文件：vue.config.js

vue3开发者工具：vue.js devtools vue3的版本

z总体特点：

比Vue2：

* 更轻（更好的摇树优化）

* 更快（使用CompositionAPI（组合式API），更好的响应式系统等等）

* 更易维护（hook，更好支持ts+ts模块化）

* 更容易扩展（hook，自定义渲染器）

* 更易用，开发体验更好，可读性更好（setup）

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

Vue3增加了很多新特性，在回答Vue2与Vue3区别的问题时，可以参考：Vue官网导航栏-文档-从Vue2迁移（https://v3-migration.vuejs.org/）

最快速从Vue2迁移到Vue3，列举了最值得关注的新特性和破坏性的更新，以及插件、库的迁移指南。

里面介绍了Vue3最值得注意的几个特性，回答时围绕这几个最重要的特性即可：

重要性从上往下，越上面越重要

* Composition API

* script setup语法糖

* Teleport

* Fragments

* 子组件配置项emits

* 自定义渲染器

* v-bind绑定CSS

* style scoped现在可包含全局规则，以及只作用于插槽的内容

* Suspense

其他的比如框架更快更轻，虚拟DOM重写，编译器优化，响应式系统

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

setup里面的数据默认是非响应式的，响应式的数据需要自己定义：

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

ref()的响应式原理与Vue2的那一套getter/setter：

```
//大致的ref响应式原理代码如下
function ref(value) {
  const refObject = {
    get value() {
      track(refObject, 'value')
      return value
    },
    set value(newValue) {
      value = newValue
      trigger(refObject, 'value')
    }
  }
  return refObject
}
```

ref()将数据封装成refImpL对象，也叫ref引用对象，简称ref对象

- ref()封装基本数据类型使用getter/setter，封装引用数据类型时，底层使用了reactive()

- ref对象在setup使用需要.value，在模板中不用，需要.value是因为Object.defindProperty的数据代理

（2）reactive()

使用es6的Proxy对象对数据进行封装，封装称为Proxy对象

- reactive()只能封装引用数据类型，基本数据类型为了方便不用.value，可以将基本数据类型放到一个对象，再把这个对象给reactive()

- setup中和模板中都不用.value

（3）常见的丢失响应式的情况

情况一，取值再赋值给新变量，若取出基本数据类型则丢失响应式，取出引用数据类型则不会

因为在一个响应式的数据里，基本类型就是基本类型，而引用类型始终是一个Proxy对象。

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

- 情况一取出的值是引用类型一定是Proxy对象，所以赋值的变量一定是响应式数据。

- 响应式数据不要整个重新赋值，如果遇到类似的情况，可以采用下面的做法：
  
  ```
  let a = ref({a:1});
  let b = reactive({a:1});
  let newData = {aaa: 123};
  
  //错误做法，这样就是整个ref，reactive重新赋值
  //b = newData;
  //b = reactive(newData);
  //a = newData;
  //a = ref(newData);
  
  //正确做法，这样就不是整个ref重新赋值
  a.value = newData;
  b.data = newData;
  ```

- 在给ref对象.value赋值为引用类型，和reactive对象增加属性时，都不需要给ref和reactive
  
  ```
  let r1 = ref(null);
  let r2 = reactive({a:1});
  r1.value = 1;
  console.log(r1.value);
  r1.value = {a:1};
  r1.value.b = 2;
  r2.b = 2;
  console.log(r1.value);
  console.log(r2);
  ```
  
  像下面这种，是既没有必要又浪费性能
  
  ```
  let a = ref(1);
  a.value = ref(2);
  a.value = reactive({a:1});
  console.log(a.value);
  
  let b = reactive({a:1});
  b.xxx = ref(123);
  b.yyy = reactive([1,2]);
  console.log(b);
  
  //若果遇到类似的情况，解决办法也是有的
  let oldData1 = ref(123);
  let oldData2 = reactive({a:1});
  let aaa = ref(null);
  let bbb = reactive({));
  aaa.value = oldData1.value;
  aaa.value = 深拷贝(toRaw(oldData2));
  bbb.b = oldData1.value;
  bbb.b = 深拷贝(toRaw(oldData2));
  ```

- 由于JSON的api本身的限制，若用JSON.stringify()序列化整个ref创建的ref对象或整个reactive创建的proxy对象，会丢失一些成员，所以用JSON.parse()恢复时不再是ref对象或proxy对象

（3）深拷贝浅拷贝

如果ref和reactive的参数不是字面量而是变量，就需要考虑浅拷贝的问题了。

```
//reactive和ref形参为引用数据类型，是浅拷贝
let a1 = {a: 1}
let b1 = reactive(a1)
let c1 = ref(a1)

//ref的参数是基本数据类型，是深拷贝
let a2 = 5
let b2 = ref(a2)

b1.a = 3
b2.value = 8
console.log(a1)
console.log(b1)
console.log(c1.value)
console.log(a2)
console.log(b2)
```

（4）Proxy响应式

Vue2实现响应式用Object.defineProperty()是为了兼容性，但是这个实现响应式最大的问题就是性能开销大，数组索引修改，对象增加删除属性，Set/Map/WeakSet/WeakMap不能实现响应式，而能实现响应式的push，pop，Vue.set()，Vue.delete()等都是vue2二次封装或自己的API

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
    //依赖收集
    return Reflect.get(target,propName)
  },
  set(target,propName,value){
    //通知更新
    return Reflect.set(target,propName,value)
  },
  deleteProperty(target,propName){
    //通知更新
    return Reflect.delete(terget,propName)
  }
})
```

引用数据类型无论是用ref()还是reactive()封装，最终都是用reactive()封装成Proxy对象，所以，数组索引修改，对象增加删除属性都是响应式的了

比起Vue2响应式：

* 优点1：响应式数据自己按需定义；Proxy响应式懒处理，初始不对深层次的数据做处理，只有访问时了才会做深层次的递归，以上这两点使得性能提升非常明显。

* 有点2：数组索引修改，对象增加/删除属性，Set/Map/WeakSet/WeakMap也是响应式

* 优点3：自定义库需要做响应式时，只需要引入ref，reactive，不像Vue2要引入整个Vue

* 缺点：Proxy是ES6的特性，IE浏览器有兼容性问题

（5）判断是否为响应式数据

```
import {isRef,isReactive,isReadonly,isProxy}
/*
由于ref对象和Proxy对象使用readonly和shallowReadonly都会变成Proxy对象，所以
isProxy还是有意义的
*/
```

#### 1.2.3 toRef()与toRefs()

toRef()以某proxy对象里的某个属性作为值创建一个ref对象，toRefs()将某proxy对象的所有属性都做一次toRef()并返回一个普通对象

toRef和toRefs都是浅拷贝

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

（1）setup参数props，context

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
    此外，vue3删除了$listeners,$listeners的相关内容翻到了attrs中
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

（2）父组件中获取子组件实例

由于setup中的this指向undefined，有两种方式来获取组件实例。

方式一：

在OptionsAPI中使用this：

```
...
mounted(){
  //删除了this.$children
  console.log(this.$parent);
  console.log(this.$root);
  console.log(this.$refs);
}
...
```

但是都Vue3了，就不推荐这种方式

方式二：

在setup中获取组件实例

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

（3）组件v-model

Vue3的组件v-model非常类似Vue2的sync，基本与sync区别不大。sync可以不用了。

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

（4）Vue3中，父传子响应式数据，子组件修改该响应式数据父组件也会修改。

如直接修改，表单v-model修改都会同时修改父组件的数据。其实这是不符合单项数据流原则的，视情况看是否要使用。

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

由于Vue3的createApp创建的app没有了$on，所以Vue2的写法不再适用。可以自己实现一个Vue3的EventBus但是十分的麻烦，所以官方推荐使用mitt

```
npm install --save mitt
```

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

计算属性会返回一个响应式对象。

若依赖的数据不是字面量而是变量，则该变量必须是响应式数据，否则监听不到该依赖数据的变化，计算属性也就不会变。

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

#### 1.3.2 watch

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

可以看做高级的watch，会自动侦听回调函数内有调用get()的数据（ref()和reactive()的get()都行），初始调用一次

```
export default {
  setup(){
    let obj = reactive({
      a: 1
    })
    let arr = reactive([1,2])

    watchEffect(() => {
     //这里只调用了arr[0]，进而调用了内部的get()，所以只监视arr[0]
     let w = arr[0]
      console.log('watchEffect')
    })
    return {obj,arr}
  }
}
```

watchEffect与计算属性区别：

相同点：

* 都是被依赖的数据被修改就回调一次

* 都可以侦听多个数据的变化

不同点：

- 计算属性初始若没有在模板使用不调用，初始若有在模板使用就调用一次，当计算属性依赖的属性修改时再调用一次

- watchEffect初始调用一次，当waychEffect函数用到数据get，且数据修改时回调一次

#### 1.3.3 依赖注入

provide，inject变为组合式API

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

#### 1.3.4 自定义指令

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

3. 组合式API的生命周期名字前加on。Vue3依旧可以使用OptionsAPI的生命周期钩子，但也符合上面2条。组合式API和OptionsAPI混着写时，顺序：
   
   setup-beforeCreate(opt)-created(opt)-onBeforeMount(com)-beforeMount(opt).....

4. setup的执行是最早的，在beforeCreate之前执行，setup过时组件实例已经创建好了，相当做了beforeCreate和created，因此组合式API没有也没必要有beforeCreated和created

5. 增加了3个在调试和服务端渲染的生命周期，分别是：
   
   | renderTracked   | 调试钩子，响应式依赖被收集时回调      |
   | --------------- | --------------------- |
   | renderTriggered | 调试钩子，响应式依赖被触发时回调      |
   | serverPrefetch  | ssr only，组件在服务端渲染之前回调 |

（2）使用：

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

nextTick也变为组合式API，用法也有些许变化但功能还是一样的，功能可以解释成等待下一次DOM更新刷新的工具方法：

```
...tempalate
<div ref="box">{{msg}}</div>
<button @click="changeMsg">修改数据</button>
...

...script
import {ref,nextTick} from 'vue'
...setup
async function changeMsg(){
  msg.value = 456
  console.log(msg.value)
  await nextTick()
  console.log(box.value.innerText)
  //也可以写成Vue2的写法 nextTick(callback)
}
...
```

### 1.5 hook函数

将setup中的代码进行封装，类似于mixin和extends，是一种新的组件扩展方式，优点是每个hook都是独立封装的，不会产生冲突问题。

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

vue自己也自带一些hook函数，如 import {useAttr} from 'vue'，也有hook库如vueuse

hook函数就是组合式API的强有力体现，将某功能用到的东西组合起来，在组件中又将一个个功能组合起来使用。，CompositionAPI和OptionsAPI的区别在于：

代码组织更规范，可读性更强，简洁高效地复用逻辑

Vue2中，一个组件可能会有多个功能，但是这些功能的数据，函数，生命周期等都分散在各个OptionsAPI中，维护起来很不方便。起初Vue是为了开发者能规范地写代码，但是后来发现项目越来越复杂的时候，代码会显得非常复杂，难以维护。

Vue3中，将每个功能的数据，函数，生命周期等封装在一个hook函数中，需要使用的组件再将其导入，这样每个功能用到的东西都集中在一个文件，维护以及复用都很方便。在不使用hook的情况下，也建议在setup内将同一个功能的属性、方法、生命周期等写在一块。

总之，如果项目比较小，也不用经常维护，使用OptionsAPI仍是一个好的选择，但是只要项目足够大足够复杂，使用CompositionAPI会更好

### 1.6 其他组合式API和新的内置组件

#### 1.6.1 其他组合式API

（1）shallowReactive()和shallowRef()

深浅拷贝和ref、reactive一样

```
shallowReactive() //只处理数组/对象第一层成员的响应式
shallowRef() //处理基本数据类型与ref()，处理数组/对象时不再做响应式（但由于数组/对象本身是ref对象，所以修改本身是响应式的）
```

（2）readonly()和shallowReadonly()

参数必须是ref对象或proxy对象。

都是浅拷贝

```
//不管是ref对象还是Prosy对象，使用了readonly()或shallowReadonly()最终都会变成Proxy对象

/*
接收一个响应式数据，加工成只读，与非响应式不同，非响应式时数据改了但Vue没监测到，
readonly是Vue监测到了，但是Vue让它不能修改，数据页面都没改；此外，常用于hook函数
导出不允许修改的数据时使用
*/
readonly()

//接收reactive对象，使得数组/对象第一层是只读；接收ref对象与readonly一样
shallowReadonly()
```

readonly后无法修改，但是源响应式数据可以修改，且由于是浅拷贝，readonly的数据也会变

```
let a = reactive({a:1})
let b = readonly(a)
//b.a = 5  //报错
a.a = 5    //成功
```

（3）tioRaw()和markRaw()

toRaw和markRaw都是浅拷贝

```
//将reactive()对象还原成非响应式的源对象（不能还原ref对象）
toRaw()

/*
标记一个普通对象，使其以后不能变成响应式数据.若对标记后的
的数据使用了ref或reactive，不会报错，知识不再进行响应式操作。
用途一，给一个响应式数组/对象添加一个成员时，若这个成员深度很深且也不需要做相遇ing是，
则可以使用markRaw这个新成员，提高效率；
用途二，某数组/对象有一个成员是第三方库（如PromiseAll封装多个axios），若将此数组/对象
封装成响应式数据，那作为成员的第三方库里面的数据都会处理一遍，效率大打折扣且这样也没有意
义，对这个成员使用markRaw()就能解决
*/
markRaw()
```

toRaw和markRaw虽然都是浅拷贝，但是结果不同

toRaw后，由于浅拷贝，修饰数据会同步，但是原来的proxy对象还是proxy对象，toRaw后的是普通对象

```
let a = reactive({a: 1})
let b = toRaw(a)
b.a = 5
console.log(a)
console.log(b)
```

markRaw标记后，数据修改也会同步，但是b和a都会多一个标记属性，都无法变成响应式数据

```
let a = {a: 1}
let b = markRaw(a)
b.a = 5
b.a = 5
console.log(a)
console.log(b)
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

用途：

* 动态改变组件标签名来改变组件

* 通过父传子的配置项来动态显示对应的form表单。

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

异步组件是为了防止子组件过大而影响父组件的显示，普通引入子组件时，只有子组件渲染完才会开始渲染父组件；而使用异步组件后，即使子组件未渲染完，父组件也会开始渲染。

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

- 路由组件不能使用async setup()。虽然懒加载是异步的，但只是异步加载，并不意味着这是个异步组件
  
  解决：路由组件内异步引入普通子组件并使用，在该子组件里使用await

（6）缓存组件

keep-alive里面也可以放普通组件了，使得里面的组件不会被销毁，能缓存状态。

同时，生命周期发生了变化，不再走onBeforeUnMounted和onUnMounted，可以使用onActivated，onDeactivated，beforeRouteEnter了。

在页面初次加载时，同时走onMounted和onActivated，在以后的每次展示和销毁缓存组件时走onActivate和onDeactivate

因此，缓存组件内只执行一次的操作（如请求数据）可在onMounted内写

属性

max="整数" 限制缓存组件的最大个数

include和exclude 包含和排除组件，值为该组件的name，多个用空格隔开

#### 1.6.4 其他新的内置组件

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

4. v-if的优先级变得高于v-for了，底层先v-if判断再v-for渲染。

5. 删除了过滤器，因为写法不友好，完全可以用计算属性和函数替代

6. 过渡类名变更：v-enter v-leave 变为 v-enter-from v-leave-from

7. 删除了按键编码作为事件修饰符，因为兼容性差。删除了案件编码，只能用DOM的addEventListen拿到事件对象中的按键码来监听了

8. 删除了事件修饰符.native，如果自定义组件想要绑定原生事件，只能在子组件对应的DOM发射自定义事件来模拟原生事件。
   
   此外，Vue3的自定义组件只会监听在子组件emits中声明过的自定义事件。

9. 其他变化详见官方文档

### 1.7 Vue3↑ 新特性

#### 1.7.1 Vue2.7

尽管现在 Vue3 是默认版本，但还有许多用户、相关库、周边生态使用的是 Vue2，且由于依赖兼容性、浏览器支持要求或没有足够的带宽升级，导致不得不继续使用 Vue2。 Vue2.7 中，从 Vue3 向后移植了一些最重要的功能，以便 Vue2 用户也可以从中受益



在 Vue2.7 中，Vue3 的很多功能将会向后移植，以便于 Vue2 的很多项目可以使用 Vue3 的一些很好用的新特性，点型的例如：



* Composition API 

* Vue3.2的script setup

* Vue3.2中的CSS v-bind 

如果有需要使用，就去看文档，主要关注那些VUe3特性可用，那些不可用。

#### 1.7.2 Vue3.2

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

如果还想使用组件name，beforeRouterEnter，可以多弄一个script标签，但是注意lang要一样

```
<script setup lang="ts">
</script>

<script lang="ts">
export default {
  name: 'xxx',
  beforeRouterEnter(to,from,next){

  }
}
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

新选择器，其中包括样式穿透的选择器

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

（3）新指令v-memo

相当于可以设置条件的v-once，它接受一个依赖数组，并且只有在数组中的一个值发生变化时才会重新渲染。

v-once是始终只渲染一次，v-memo是依赖数组的一个值改变就重新渲染，不改变就不重新渲染，连虚拟DOM也不会生成。

```
<template>
  <p v-memo="[msg]">{{ msg }}</p>
  <el-button @click="msg = 'change msg'">切换</el-button>
</template>

<script setup>
import { ref } from 'vue'

const msg = ref('hello')
</script>
```

如果传入一个空的依赖项数组，它将与使用 `v-once` 相同，它永远不会重新渲染。

**注意**，v-memo在v-for循环内部中不起作用，所以如果我们想用 `v-for` 记忆一些东西，我们必须把v-memo和v-for放在同一个元素上。

## 2 vue router4

vue3使用的路由版本

（1）基本使用

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

（2）导航守卫的一些小变化

① next不再是必选参数

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

② 组件内守卫

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

（3）路由相关组件的插槽

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

（4）修复了vue2路由的两个bug

bug1：当跳转的路由就是当前路由时，不再像vue2会有警告

bug2：nest()跳转路由时功能正常却有警告

其他的用法基本与vue2一样

## 3 pinia

Vuex4是vue3使用的vuex版本，但是很不方便，推荐使用pinia

```
npm install --save pinia
```

官方推荐的Vuex的代替品，解决了Vuex的痛点，优点：

1. Vue2，Vue3都可以使用

2. 抛弃了mutations，使用state，actions，getters就可以了，数据也可以直接修改因为vue devtools能够追踪

3. 不需要嵌套模块，且分模块也非常方便

4. 完全支持ts，且js和ts代码都很简洁，无论是在store文件中还是在组件中使用都很方便。

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

Vue3.0中实例化的pinia需要return才能在template使用，Vue3.2的script setup会自动return就不要管。

```
<script>
import {mainStore} from './store'
export default {
  setup(){
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

    return {
      store
    } 
  }
}
</script>
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
//0 $id store的
//1 $patch
//2 $reset  将state的数据还原成初始值
store.$reset()
//3 $subscrib  每当state的任一属性值发生变化就回调
store.$subscrib((args,state) => {

})
//4 $onAcition 每当action的方法被调用就回调
store.$onAction((args) => {})
```

pinia持久化：

（1）第三方插件

```
npm install --save pinia-plugin-persistedstate
```

 使用：

```
// /store/index.js
import {createPinia,defineStore} from 'pinia'
import piniaPluginPersistedstate from 'pinia-plugin-persistedstate'
const pinia = createPinia()
pinia.use(piniaPluginPersistedstate)


const XxxStore = defineStore('Xxx',{
  state(){
    return {}
  },
  //默认情况下，存储名为Xxx，存储方式为localStorage，存储所有state数据
  persist: true,
  //自定义存储名，存储方式
  /*   
  persist: {
    key: 'longtimepinia',
    storage: window.localStorage
  }
  */
  ...
})
...
```

注意点：

* 这样配置后，pinia照旧操作就能实现持久化

* 可以单独defineStore一个store来专门存放持久化的数据

* 数据存储在 localStorage.Xxx（默认） 或 localStore.longtimepinia（自定义）

（2）自定义插件：

以下是ts写法

```
// /store/index.js
...
const myPluginTest = (context: PiniaPluginContext) => {
  //如果自定义的插件不需要传入自定义参数，就这样写
  ...
}

type Options = {
  key?: string
}
const myPlugin = (options:Options) => {
  //如果需要自定义参数就这样写
  //之所以这么写，是因为自定义插件这个函数是pinia调用的，我们无法控制它，所以需要传入自己的参数的时候就需要外包一个自己可以操作的函数
  return (context: PiniaPluginContext) => {
    const {store} = context;
    store.$subscribe(() => {
      console.log(‘每次数据被修改都会回调’);
      localStorage.setItem(Options?.key ?? store.$id,JSON.stringify(toRaw(store.$state)));
    });
    const data = 
JSON.getItem(Options?.key ?? store.$id) ? JSON.parse(localStorage.getItem(Options?.key ?? store.$id) as string) : {}
    return {...data}
  }
}

//无参数
pinia.use(myPlugin);
//有参数
pinia.use(myPlugin({
  key: 'xxx'
}))
...
```

根据需要可以再自定义一些功能，如自定义存储方式。

# 三、Vue使用ts

（1）用前须知：

不推荐vue+ts使用vue-cli构建项目，推荐vite，因为vue-cli编译ts反应非常慢，且一旦使用了script setup语法就会关闭类型检查，即使用回V，ue3.0语法也不行，需要重启run才行。
目前vite的版本使用的js语法，如可选链操作符，vin7最高支持的node版本13.14已经识别不出，必须要更高的系统

（2）Vue2使用ts

Vue2以及Vue3中使用OptionsAPI，要用ts需要借助vue-class-component或vue-class-decoretor

vue-class-compoennt是vue官方出的

vue-class-decorator是社区出的，具有vue-class-compoennt的全部功能，在此之上又增加了一些新功能

（3）Vue3使用ts

defineComponent定义组件：

Vue3.0中，使用defineComponents定义组件可以有更好的类型提示，Vue3.2的script setup语法糖则不需要

```
<script lang="ts">
import {defineComponent} from 'vue'
export default defineComponent({
  ...
})
</script>
```

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
