# 一、基本介绍

Vuex是一个响应式的状态管理工具
状态其实是一个变量，可以给多个组件共享状态（如登录状态等），状态是一个变量。
自己可以定义一个对象，保存各个组件共享的变量，但是这不是响应式的，修改一个组件内的共享变量不会修改所有组件的共享变量，此时就需要Vuex
一般来说，父子之间共享的变量不适宜放在Vuex，直接父子组件通信就行。
单页面时，Vuex的state是data(){}，view是{{}}，action是事件
npm install vuex -save  

store有五个配置项：state，mutations，actions，getters，modules

# 二、state

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

# 三、mutations

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

# 四、actions

里面额的都是异步操作，如果在mutations中定义异步操作，vuedevtools是无法跟踪的，所以需要在actions定义，就可以跟踪。

过于复杂的mutations操作也是放在actions中更好

使用与mutations类似，但是参数是context (相当于store对象)
组件中通过 this.$store.dispatch(‘…’)提交。

若要修改state的值，则需要在actions方法内部 context.commit(‘…’)
同样可以传递参数，使用与mutations一样

由于是异步操作，也能使用Promise 
return new Promise(  但是then在组件里， this.$store.dispatch().then()

# 五、getters

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

# 六、modules

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

# 七、map语法

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
映射时，加一个moduleName参数  ...mapState('moduleName',[])

# 八、store模块化

将getters，mutations，actions单独放在各自的js文件，导出导入
一般state在insex中不抽离
moduls建立一个文件夹

# 九、Vuex4

vue3使用的vuex版本，但是很不方便，推荐使用pinia

# 十、Pinia

1 基本介绍

npm install --save pinia

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
