# 一、基本介绍

V版本更新：https://github.com/vuejs/core/releases?after=v3.0.3

Vue3的脚手架最低版本为4.5

查看cue=cli版本：vue -V                  

创建项目：vue create xxx         里面可以选择vue版本

运行：npm run serve

打包：npm run build

配置文件：vue.config.js

vue3开发者工具：vue.js devtools     vue3的版本

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

# 二、setup与响应式

1 setup

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

2 Vue3响应式

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

* ref()封装基本数据类型使用Object.defindProperty()，封装引用数据类型时，底层使用了reactive()

* ref对象再setup使用需要.value，在模板中不用，需要.value是因为Object.defindProperty的数据代理

（2）reactive()

使用es6的Proxy对象对数据进行封装，封装称为Proxy对象

* reactive()只能封装引用数据类型，基本数据类型为了方便不用.value，可以将基本数据类型放到一个对象，再把这个对象给reactive()

* setup中和模板中都不用.value

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

* 情况一取出的值是响应式数据，赋值的变量才是响应式数据

* 响应式数据不要整个重新赋值

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

3 toRef()与toRefs()

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

4 setup参数与父子组件通信、插槽

（1）Vue2回顾

props：

Vue2中，只要给父组件中的子组件标签 :aaa = "xx" 传入数据，子组件若

- 有props接收，放到this，且可以限制类型，设置默认值等操作

- 没有props接收，都会放到 this.$attrs，无法限制类型，设置默认值等操作

插槽：

Vue2中，只要给父组件中的子组件标签里面放了html，子组件若：

* 有<slot>接收，则不妨到this.$slot，而是渲染出来真实DOM

* 没有<slot>接收，以虚拟DOM形式放到this.$slot

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

* 删除了model配置项

* props默认值value改为modelValue，emit默认值input改为update:modelValue

* 组件可使用多个v-model

* 除了v-model自带的修饰符外，还可以自定义修饰符

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

作用域插槽的 v-slot:defalt="..."  变成了  v-slot="..."  可简写为 #defalut="..."

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

# 三、常用的组合式API

1 计算属性

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

2 过滤器

Vue3删除了过滤器，因为写法不好，也可以完全可以用计算属性和函数替代

3 watch

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

* 计算属性初始调用一次，当计算属性依赖的属性修改时再调用一次

* watchEffect初始调用一次，当waychEffect函数用到数据get，且数据修改时回调一次

4 祖孙组件通信（跨代组件通信，也叫依赖注入）

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

5 自定义指令

5.1 Vue3.0

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

5.2 Vue3.2

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

3.3 应用案例

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

# 四、生命周期

1 基本变化

1. beforeDestroy和destroyed变成了beforeUnmount和unmounteed

2. Vue2的el未挂载也会走beforeCreate和created，而Vue3不会

3. 依旧可以使用OptionsAPI的生命周期钩子，但也符合上面2条

4. 由于setup在beforeCreate之前执行，Vue3也就把setup认为是beforeCreate和created，因此组合式API没有beforeCreated和created

5. 组合式API的生命周期名字前加on

6. 组合式API和OptionsAPI混着写时，顺序：
   
   setup-beforeCreate(opt)-created(opt)-onBeforeMount(com)-beforeMount(opt).....

2 使用：‘

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

# 五、hook函数

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

# 六、其他组合式API和新的内置组件

1 其他组合式API

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

2 全局变量/函数和插件

（1）全局变量/函数

从Vue.prototype  变成 app.config.globalProperties

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

3 组件新用法

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

需要用到Vue3内置组件 <component />

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

异步组件需要配合<Suspense>和异步引入组件才能使用

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

Vue3新的内置组件<Suspense>

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

* setup()使用async修饰后（Vue3.2 script setup 内，函数外使用await后setup()直接变async）,必须使用defineAsyncComponent引入组件，且在<Suspense>内使用引入的异步组件

* 由于路由js文件无法使用<Suspense>，所以路由组件不能使用async setup()。解决：路由组件内异步引入普通子组件并使用<Suspense>，在该子组件里使用await

（6）缓存组件

<keep-alive>里面也可以放普通组件了，使得里面的组件即便被销毁了也能缓存状态。

同时，生命周期发生了变化，不再走onUnMounted，新增了onActivated和onDeactivated

在页面初次加载时，同时走onMounted和onActivated，在以后的每次展示和销毁缓存组件时走onActivate和onDeactivate

因此，缓存组件内只执行一次的操作（如请求数据）可在onMounted内写

<keep-alive>属性

max="整数"   限制缓存组件的最大个数

include和exclude  包含和排除组件，值为该组件的name，多个用空格隔开

3 其他新的内置组件

（1）<Fragment>

这个标签不用写，是内置在Vue中的

它使得template中默认放一个<Fragment>作为根标签，它是不会渲染出来DOM的。

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

<Teleport>的父元素使用了v-show对其无效，但是v-if有效

# 六、其他变化

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

2. <template>中不再需要根标签

3. data配置项应始终声明为 data(){return{}}

4. 删除了过滤器

5. 过渡类名变更：v-enter v-leave 变为 v-enter-from  v-leave-from

6. 删除了按键编码作为事件修饰符，因为兼容性差。删除了案件编码，只能用DOM的addEventListen拿到事件对象中的按键码来监听了

7. 删除了事件修饰符.native，Vue2中自定义组件会将绑定的事件都认为是自定义事件，所以才需要.native告诉他是原生事件；Vue3的自定义组件绑定的事件都认为是原生事件，自定义事件需要在子组件的配置项emits中声明

8. 其他变化详见官方文档

# 七、vscode插件

在新的语法下，vue2的vetur不再够用，vue3的语法提示插件试验volar

Vue Language Features (Volar)

TypeScript Vue Plugin (Volar)

为了防止冲突，在使用vue3时，启用volar并禁用vetur，在使用vue2时，启用vetur禁用volar

# 八、Vue3↑ 新特性

1 Vue3.2

1.1 <script setup>语法糖

（1）基本

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

（2）setup语法糖的父子组件通信写法

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

（3）script setup语法下获取子组件实例或子组件的资源

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

1.2 <style>新特性

（1）<style>内使用v-bind

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

（2）新选择器

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

（3）<style module>

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

# 十、Vue使用ts

Vue2以及Vue3中使用OptionsAPI，要用ts需要借助vue-class-component或vue-class-decoretor

vue-class-compoennt是vue官方出的

vue-class-decorator是社区出的，具有vue-class-compoennt的全部功能，在此之上又增加了一些新功能

Vue3中ts直接用就行，写在setup里面或者export default{}外面都行

1. 定义了变量但未赋值，需要指定ts类型

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
