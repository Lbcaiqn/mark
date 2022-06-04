# 一、基本介绍

浏览器vue调试插件：vue devtools

Vue代码最好不加分号
MVX模式（MVC和MVVM）:
MVC模式：模型+视图+控制器，angular框架使用
MVVM模式：把MVC的控制器改成ViewModel，View的变化会自动更新ViewModel，ViewModel的变化也会同步在View上显示。Vue框架

使用。
MVVM：
Model：是vue里面的data
View：是模板
View Model：就是vue对象，包含 data bindings 和 DOM listeners
引入方式：

```
<script src="vue.js"></script>   本地引入
<script src="https://unpkg.com/vue@2.6.14/dist/vue.js"></script> 网络
```

# 二、基本使用

```
//data:{},{}可以声明成变量，在vue对象外定义，如var data={}; vue中data:data
//方法和计算属性内部使用Vue内部的属性时，一定要加上this.
//Vue首选单引号
var或const v=new Vue({
  el: "#xxx 或 .xxx",            //控制器，绑定id
)}
vue对象.$mount('...') 等价于 el:'...',都是挂载

Vue.config.productionTio = false  //阻止vue启动时的生产提示

箭头函数的this指向与vue：
*vue管理的函数里要使用this时，必须使用普通函数，this才能指向vue实例
*不是vue管理的函数（如定时器回调，promise回调，事件总线回调等），可以使用箭头函数更加简便，this指向window
```

1 指令和插值语法

指令：指令  v-xxxx 类似标签的属性的写法
Vue中不带引号解析成变量，带引号解析成字符串。

{{}}为Mustache语法  <标签>{{}}</标签>
{{}}里面只能放一个变量/方法/表达式。

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

2 数据绑定

2.1 v-bind

v-bind:属性  可以简写为 :属性    用来动态绑定属性

（1）绑定img的src

只能绑定网络URL，本地URL需要另外处理

（2）绑定class

```
//1.可以分写css类和变量存储的css类名
class="css类名" :class="变量名"
//2.数组写法，注意引号
:class='["css类名",变量名]'
//3.对象写法，true生效flase失效，一般定义一个布尔变量控制；还可以用三目运算符 布尔变量?”类1”:”类2”     
:class=’{"css类名":true,变量名:布尔变量}'
//4.Vue中方法内：return 数组或对象   当数组或对象太复杂时可使用
:class=’方法() '
//5.变量的值作为样式的属性，若此时不用变量则加上引号，若Vue中变量存的是像素且不带px，则使用时加上+‘px’
:style='{样式属性:变量名}'
//6.数组写法，不常用。
:style='[对象1,对象2…]'>
```

（3）绑定的属性名和值一样时

true生效，如button属性disabled=”disabled”，等同于v-bind:disabled=”true”

2.2 v-model

双向绑定表单（input表单，textarea表单）

（1）基本使用

```
<input type="text" v-model="变量">
<!--
表单的value值（表单显示的文本）是该变量值，当修改变量值时会同时修改value，当修改value
时，也会同时修改变量的值（获取过来不管类型都默认为字符串），这就是双双向绑定。
textarea表单，password等类型的input表单用法都和这个差不多
-->
<!--
双向绑定原理，v-model等同于：
<input type="text" v-bind:value="name" v-on:input="name=$event.target.value">
-->
```

（2）与radio类型input结合使用：

```
<input type="radio" value="radioName" v-model="变量">
<!--
需要value属性，变量是字符串类型。
若变量的值为radioName，则该radio会被选上；若不同或为空则不选。
当选择该radio时，其value会赋值给变量。
一组radio的v-model里的变量一样时，不用给它们相同的name属性，就能实现单选。
-->
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

3 自定义指令

封装DOM操作成一个指令

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
/*
1.xxx为指令名，用v-xxx调用，当xxx为多个单词组成时，-隔开，且xxx不能再简写为不带引号，应为’xxx’
2.element为指令绑定的真实DOM元素，可以使用所有DOM操作的属性方法，binding为对象，其中
一个键 value为 v-xxx=”n” v-xxx:…=”n” 的n
3.写形式，在元素与指令绑定完成时候执行一次（此时元素还不在真实DOM上），任何数据更新
造成的模板重新解析再执行一次，一些DOM操作必须在真实DOM中有该元素时才能操作，需要完整
写法才能完成
4.完整写法有3个钩子，都有element和binding，可以解决简写形式中需要元素在真实DOM后才能
进行的操作（inserted()），因为bind只执行一次，所以update中要复制一份bind代码
5.无论简写还是完整写法，函数里面的this都指向window
*/

//全局指令：
Vue.directive(‘xxx’,{//完整写法}) Vue.directive(‘xxx’,()=>{//简写})
```

# 三、计算属性与过滤器，数据监视

1 计算属性
1通过属性之间的计算得到的属性，具有缓存功能。与methods最大的区别就是缓存，computed多次调用只计算结果一次并保存，而methods多次调用就多次计算结果，所以compted比methods好很多。
Vue会根据计算属性内的值有无变化判断是否重新计算，若值不变，则不改缓存，若值变了，则会重新执行计算属性给新缓存。
优势：比直接写{{ 复杂表达式 }}代码可读性高，比methods性能好。

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

2 过滤器

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

3 数据监视

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

# 四、生命周期

在vue的创建到销毁的过错中，有一些生命周期函数（也叫钩子），在相应的节点就会回调这些函数，由此可以在vue的相应节点编写代码
生命周期函数与data，methods等同级，函数里面调用data等时也用this

使用示例：

```
created(){
  console.log(''我被创建了)
}
```

1 el挂载之前

若无el挂载，会在created后停止

| beforeCreate | 数据监测，数据代理创建之前，此时无法调用data，methods |
| ------------ | -------------------------------- |
| created      | 数据监测，数据代理创建之后，组件已创建，此时可网络请求数据    |

2 el挂载之后

| beforeMount | vue解析完模板，生成虚拟DOM在内存中，但是还未转成真实DOM，所以页面未解析vue语法来渲染，此时若操作DOM，只在这个瞬间有效，                 由于下一流程的影
响，此时操作的DOM最终都无效。该钩子将虚拟DOM转真实DOM，并保存一份到 $el 里 |
| ----------- | ----------------------------------------------------------------------------------------------------------------------------------------- |
| mounted     | DOM渲染完成，展示模板，此时才能操作DOM                                                                                                                    |

3 数据更新

一旦有数据更新就回调

| beforeUpdate | 此时数据更新完，但是页面还未刷新，就是model和view不同步，根据新数据生成新虚拟DOM，新旧虚拟DOM比较看是否有复用，刷新成新页面 |
| ------------ | --------------------------------------------------------------------- |
| updated      | 数据更新完，页面也刷新完，model和view同步                                             |

4 组件销毁

调用$destroy()或路由离开就会销毁组件，

$destroy()会完全销毁实例，并清除与其他实例的链接

清除所有指令和自定义事件（原生事件不清)
大部分情况都不是自己主动调$destroy，而是自动调（如路由切换等）

| beforeDstroy | 还未开始销毁，还可以调data，methods，但此时对数据的任何修改都无效,此时宜做收尾工作（清除定时器，事件总线上的监听等） |
| ------------ | ---------------------------------------------------------------- |
| destroyed    | 销毁之后，一般很少用这个钩子                                                   |

5 路由钩子

| activated                | 在跳转到该路由后回调（激活）     |
| ------------------------ | ------------------ |
| deactivated              | 在离开该路由后回调（失活）      |
| this.$nextTick(() => {}) | 在数据更新后，元素在真实DOM后回调 |

# 五、Vue响应式原理

1响应式

若没有响应式，则数据修改时，只有在script中改了，模板并没有改，只有响应式才会重新解析模板，修改模板的数据

vue在每次有值修改时，都会再解析一次vue模板，所以{{方法()}}会再调用

2 原理

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

# 六、事件绑定

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

# 七、渲染

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

（2）:key

官方推荐使用v-for时，最好给元素/组件绑定key属性，这是为了更好地复用以及不出错。所以只要用了v-for，就要给其指定 :key 作为唯一标识，key最好为数据里的唯一标识属性 （若没指定，默认 :key="索引"） ，这是为了显示结果不出错和效率（效率体现在复用，复用指元素不用删除再创建，用原来的就行）

:key=”i”    必须是遍历的唯一标识，不能是下标

key工作原理：
初始：数据-虚拟DOM-真实DOM
更新：新数据-新虚拟DOM-新真实DOM
更新数据时，新虚拟DOM与旧虚拟DOM会进行比较算法，根据key进行逐一比较，若有完全相同的元素，就直接复用原来的，增加效率，但是注意输入框的特例，输入框的相同不与文本内容相关，就是文本不同但其他一样，就会复用输入框

若此时使用index作为key

* *新的数据在最后面增删，不影响原本数据顺序，无影响

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

# 八、动画与过渡

1 动画

vue动画：对css3动画进行了一些封装

```
1.<transition></transition>包住要实现动画的元素
2.写CSS3动画代码，只是类名是固定的，来是 .v-enter-active 走势是 .v-leave-active 当
<transition>有name属性时，v换成相应的name
3.当页面一刷新就展示动画，<transition>增加 appear 或 :appear="true"
vue动画显示隐藏元素是立刻执行的，动画只是播放而已，如元素消失了，但是动画在播放
```

2过渡

vue过渡：
<transition>除了上面两个类名，还有v-enter/leave (to) 这四个类名，因此，用他们上面就

可以替换上面一坨CSS3代码
注意：v-enter v-leave 在获得后生效，马上失去，所以在控制台很难看到这两个类名

```
.v-enter,
  .v-leave-to {
    transform: translateX(-100%)
  }
  .v-leave,
  .v-enter to {
    transform: translateX()
  }
  //也可以不写下面一段，而把transition属性放在要过渡的元素css里，相同效果，但是不推荐，没这种美观
  .v-enter-active,
  .v-leave-active {
    transition: 1s;
  }
```

多个元素的过渡：
<transition>只能包裹一个元素，要实现多个元素或者列表的过渡，可以：
*n个元素n个<transition>，用不同的name区分，但明显列表不适用
*用div包裹<transition>里的多个元素，但是无法这种实现互斥（布尔值不同）动画效果，极不推荐
*使用<transition-group>包裹多个元素，并给每个元素增加独立的key属性

第三方动画库：Animate.css  使用见官网

# 九、组件

Vue本身也是一个组件

组件没有el，所有组件组成组件树放到Vue中，由Vue的el挂载

Vue和组件的template必须要有根标签div
组件继承于Vue，基本一样，但是data(){return {}}必须这样写

组件无法使用原生事件，这是因为自定义组件的事件默认都会认为是自定义事件，需要事件修饰符.native让组件认为是原生事件，才能使用

1 基本使用

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

```
//单文件组件
/*命名
大驼峰或 aaa-bbb 避免与原生标签名冲突
为了寻找方便，views组件名一般命名为 ViewsnameXXX，如HomeMain
注册子组件时，子组件名不要和子组件内的组件名冲突
*/

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

2 父子组件通信

```
//父传子 

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
    tupe: Number
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

//3.子组件中的props的变量就能显data()的变量一样使用

//props和data的变量是放在内存不同地方的，但使用方法相同
```

```
//子传父
//1.子组件内，触发子组件的事件，发射自定义事件
<div @click="fun"></div>
fun(){
  //方式一
  this.$emit('xxx')
  //方式二
  this.$emit('yyy',{}
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

3 非父子组件通信

（1）事件总线

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
  EventBus.$off('xxx')
```

（2）Vuex，和订阅者观察者模式的第三方库也是非父子组件通信

4 获取组件实例对象

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

4 混入

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

5 插槽

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
/*
有名字只会替换对应名字的，没名字的只能替换没名字
*/
```

```
//作用域插槽
作用域插槽：
替换的内容由子组件决定。
编译作用域：一个模板内的变量只在使用该模板的组件有效。
如替换的内容带有子组件的属性，父组件无法直接调用，此时，
slot增加自定义属性  v-bind:自定属性名d=”子组件data内属性”
组件标签内，<template slot-scope=”自定对象名s”>… 使用s.d ..</template>
高版本的vue这里template也可以用div
```

6 插件

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

7 其他

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
