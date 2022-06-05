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

3 setup参数

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



（3）具名插槽

Vue3的具名插槽必须这样写，默认插槽用法不变

```
<子组件>
  <template v-slot:asd>
    <div>6666666666</div>
  </template>
  </子组件>
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

4 祖孙组件通信（跨代组件通信）

父子组件通信依旧可用，用法变化详见setup参数

祖孙通信就是，一个组件可以与它的所有后代（包括子组件）进行通信，而不仅仅是孙组件

# 四、生命周期

# 五、其他变化

# Vue3.2

# Vue使用ts
