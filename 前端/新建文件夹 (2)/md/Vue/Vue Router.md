# 一、路由介绍

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



# 二、基本使用

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
    //默认路由，一进入页面就进入该路由
    path: '',   //也可以是 '/'
    redirect: aaa,
    component: aaa
  },
  {
    path: '/aaa',
    name: aaa,
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

* hash兼容性比hidtory好点

* hash的 #以及后面的都是哈希值，不会作为路径给服务器；而history整个url都会给服务器；但是url都是前端路由跳转的，整个url给服务器并没有对应的资源，粗线404。若想使用history且请求正常，需要后端解决。

路由跳转：

跳转方式：

* push，整个url入栈，所以可以返回前一个路由

* replace，直接覆盖原有url，所以无法返回前一个路由

跳转类型：

分为声明式导航和编程式导航

若to内使用了变量，则需要v-bind，否则则不用

```
<!-- 
声明式导航
显示一个a标签，点击会push跳转到/…，跳转后可以返回 
属性：
tag=”标签名”  修改显示的标签，默认a，如button
replace 	使用replace修改url
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

# 三、动态路由与参数传递

1 动态路由

有些情况path是不能写死的，如用户id，此时需要配置动态路由

动态路由是传递参数的方式之一，但一次只能传递一个参数

```
//如user组件
//路由配置中
{
  path:’/user/:aaa’
  component:user
}

//组件中
v-bind:to=”’/user/’+ xxx”
this.$router.push('/user/' + xxx)

//若想获得跳转过来的路由参数，可以
this.$route.params.xxx	
```





2 传递对象参数

路由配置的path正常写就行  path: '/aaa'

```
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



# 四、嵌套路由

使用嵌套路由时，嵌套的路由组件也要再用<router-view>，如：

cpn组件中，使用路由a，a嵌套路由b，则在cpn中用一次<router-view>，a路由组件中也要用一次<router-view>，b不用

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



# 五、导航守卫

也叫路由守卫

可以设置一些条件，在复合条件后才能跳转路由；或跳转后做鉴权或其它属性
路由配置项 meta:{} 在该对象中可自定义属性使用

一般都有三个形参：

* *to 将要跳转的路由

* from 跳转前路由

* next 在函数内部调用 next() 才能继续跳转路由

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



# 六、keep-alive

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



# 七、Vue Router4


