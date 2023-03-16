# 一、基本

## 1 SPA存在的问题

前后端分离的开发模式下，使用Vue开发的SPA（单页面音乐）是CSR（客户端渲染），CSR存在一些问题，主要是以下两个方面：

* SEO不友好，可以看到打包后的index.html的body中只有一个id为app的div，具体的内容是通过script动态渲染的，这样在打开页面的时候审查元素中没有实际内容，而搜索引擎的本质是爬虫，所以SPA的SEO十分不友好

* 性能一般，由于是script动态渲染的，所以首屏加载时间表现一般

* 会暴露请求接口，安全性相对较差，当然接口一般都会做安全性设置

SPA解决SEO问题主要有两种方式：

* 预渲染：打包完成后，用发布机模拟浏览器打开需要预渲染的页面，页面脚本触发渲染时机，渲染当前页面内容并获取所有DOM，生成html文件。

* 服务端渲染：哭护短访问网站时，后端通过网络请求等先获取数据后，通过渲染引擎渲染带有数据的页面，返回到前端展示。

三种解决方案的对比：

| 解决方案   | SEO  | 客户端性能 | 服务端压力 | 应用场景                       |
| ------ | ---- | ----- | ----- | -------------------------- |
| CSR    | 不友好  | 较差    | 小     | 不需要SEO的项目，如小程序，app，后台管理系统等 |
| CSR预渲染 | 几个页面 | 中等    | 中     | 只有某几个页面需要SEO的项目            |
| SSR    | 全部页面 | 较好    | 大     | 全部页面都需要SEO的项目，如新闻网站，电商网站   |

另外还有一种，SSG（静态站点生成），它可以通过提前生成HTML文件，将动态网站变成静态网站，使得页面的加载速度更快。SSG通常用于构建博客、文档网站等，这些网站内容不太频繁变化。

SSG虽然也能解决CSR的SEO问题，但比起预渲染和SSR的不足是生成的是静态页面。

## 2 预渲染

```
npm install --save-dev prerender-spa-plugin
npm install --save-dev vue-meta-info
```

根据它的文档配置 vue.config.js

动态路由无法使用

## 3 原生Vue+express实现简易SSR

这里只是展示SSR的基本原理，还有很多复杂的问题没有处理，这些就需要用到Nuxt。

```
//访问 localhost:8000
const express = require("express");
const Vue = require("vue");
//Vue2才能用
const { createRenderer } = require("vue-server-renderer");

const server = express();
const app = new Vue({
  template: `<div>Hello</div>`,
});

server.get("/", (req, res) => {
  let html;
  createRenderer().renderToString(app, (err, res) => {
    if (err) throw err;
    else html = res;
  });
  console.log(html);
  res.send(html);
});

server.listen("8000", () => {
  console.log("服务器已启动");
});
```

# 二、使用

Nuxt可以实现CSR，SSR，SSG，但是一般都是用来SSR。

## 1 开始

Nuxt就是基于Vue的框架，可以做SSR（服务端渲染）和SSG。

早年的前后端不分离，是用后端的模板引擎来解析前端页面，而Nuxt其实就是模板引擎。

创建Nuxt项目：

```
npx create-nuxt-app xxx
```

运行开发环境：

```
npm run dev
```

打包，运行生产环境：

```
npm run build
npm run start
```

入口文件：/.nuxt/layouts/default.vue，没有main.js

## 2 配置

因为Nuxt没有main.js，所以全局引入的库、样式等都需要借助配置文件。

配置文件是nuxt,config.js，做全局配置；而每个vue文件中也可以做局部配置。

（1）head

SEO相关的配置，局部的配置会覆盖全局的配置，若局部某个配置项没有配置则使用全局的。

全局：

```
// /nuxt/config.js
export default {
  head: {
    title: "nuxt001",
    htmlAttrs: {
      lang: "en",
    },
    meta: [
      { charset: "utf-8" },
      { name: "viewport", content: "width=device-width, initial-scale=1" },
      { hid: "description", name: "description", content: "" },
      { name: "format-detection", content: "telephone=no" },
    ],
    link: [{ rel: "icon", type: "image/x-icon", href: "/favicon.ico" }],
  },
}
```

局部：

```
// /pages/xxx.vue
<script>
export default {
  //...
  head: {
    title: "home",
    htmlAttrs: {},
    meta: [],
    link: [],
  },
}
</script>
```

（2）css

使用全局样式，可以是自己的样式，也可以是第三方库放在node_modules的css

```
// /nuxt/config.js
export default {
  //...
  css: [
    "路径"  
  ]
}
```

局部样式scoped：

与vue一样，但是有一点需要注意，nuxt认为pages目录下的页面都是独立的，所以每个页面的样式都是独立的，不加scoped也行，但是有子组件的话还是得加scoped。

（3）plugins

在页面加载前需要调用的js，相当于main.js，如使用elementui需要的那一段js代码。

需要在根目录下创建plugins文件夹，放对应的js文件。

默认情况下在服务端和客户端都会执行一次，且参数context.app能拿到app，能拿到路由，因此也可以拿到路由作导航守卫

```
// /plugins/xxx.js
export default function(context){
  console.log('plugins')
}
```

```
// /nuxt/config.js
export default {
  //...
  plugins: [
    "@/plugins/xxx.js",
    //对象形式
    {
      src: '@/plugins/yyy.js',
      ssr: true   //默认为true，false的话只会在客户端执行
    }  
  ]
}
```

（4）modules

相当于在main.js中，import name from ‘xxx’ 并绑定到服务端上下文context和Vue原型上，这样就可以用 this.$name使用了，当然name具体是什么得看库，不如 @nuxt/axios 是 this.$axios ，cookie-universal-nuxt 是 this.$cookies

```
// /nuxt/config.js
export default {
  //...
  modules: [
    "xxx"  
  ]
}
```

（5）本地代理实现前端跨域

```
npm install --save @nuxtjs/proxy
```

```
// /nuxt/config.js
export default {
  modules: [
    '@nuxtjs/proxy'
  ],
  proxy: {
    '/api': {
      target: 'http://xxx',
      pathRewrite: {
        '^/api' : ''
      }
    }
  }
}
```

（6）loading

页面顶部的进度条，默认是开启的，可以关闭，也可以自定义

```
// /nuxt/config.js
export default {
  //...
  //loading: false;
  /*自定义loading
  loading: {
    color: 'blue',
    //...  
  }
  */

  /*自定义loading组件
  loading: '路径'   //自定义必须要有start()和finish()，函数名不嫩改
  */
}
```

（7）components

默认为true，true时，components目录下的组件不需要导入就能使用

## 3 项目上线

不同于之前SPA项目只需要把打包后的dist文件夹的内容放到express项目的public文件夹，Nuxt项目因为本身就是有服务端的，所以把.nuxt，static，package.json，nuxt.config.js放到服务器后，安装依赖，npm run start就部署完毕。

# 三、Nuxt的生命周期

分为三类，执行顺序：服务端-共有-客户端

* 服务端生命周期：只会在服务端执行，有nuxtServerInit，middleware，validate，asyncData/fetch
  
  * 服务端生命周期结束后开始SSR，所以在这之前要把数据准备好
  
  * 每次页面加载前或路由后，会从middleware开始再次执行
  
  * 每次数据更新都会重新SSR，但不会再执行服务端钩子，和vue一样只会执行update

* 服务端和客户端共有的生命周期：服务端/客户端都会执行，beforeCreate，created，

* 客户端生命周期：只会在客户端执行，就是剩余的Vue生命周期，但是由于SSR没有\<keep-alive /\>，所以没有actived和deactived

之所以会有比Vue多出这些生命周期，正是因为SSR，如判断token来是否展示页面，或根据id信息请求数据，这些都需要在服务器端完成，因为在客户端完成的话就和SPA没区别了。

以下只介绍服务端的生命周期。

## 1 服务端生命周期

（1）nuxtServerInit

特点：

* 第一个执行，只执行一次

* 通常用来操作store，如初始化、判断token等

* 只能写在vuex的根模块的actions

* this指向undefined

代码：

```
// /store/index.js
export const actions = {
  nuxtServerInit(store, context) {
    //store是vuex，context是服务端上下文
    console.log("nuxtServerInit");
  },
};
```

（2）middleware

特点：

* 第二个执行

* 功能类似于导航守卫，分为全局和局部，全局比局部先执行。

* 只有pages下的vue才能使用局部middleware

* this指向undefined

代码：

全局middleware，所有页面都会执行：

```
// nuxt.config.js
export default {
  //...
  router: {
    middleware: "xxx",
  },
}
```

```
// /middleware/xxx.js
export default function(context){
  console.log('全局middleware');
}
```

局部middleware，只有这个页面会执行：

不需要配置nuxt.config.js也能使用

```
// nuxt.config.js
export default {
  //...
  //router: {
  //  middleware: "xxx",
  //},
}
```

在某个页面的.vue文件：

```
<script>
export default {
  //...
  middleware: "yyy",
  //或者这样写，就不需要另外在middleware下创建文件了
  //middleware(context){};
};
</script>
```

同样的，在middleware下创建文件：

```
// /middleware/yyy.js
export default function (context) {
  console.log("局部middleware");
}
```

（3）validate

特点：

* 第三个执行

* 通常用来做路由的参数验证，比如跳转到商品详情页时，若id不对可以覅转到404。

* 只有pages下的vue文件才能使用

* this指向当前组件实例，但是获取不到data()

代码：

在某个页面的.vue文件中：

```
<script>
export default {
  //...
  validate(context) {
    console.log("validate", context.params, context.query);
    //if(验证不通过)  return false;
    return true;  //如果不return true会到nuxt的默认404页面
  },
};
</script>
```

（4）asyncData 和 fetch

① asyncData

特点：

* 第四个执行

* SSR为了SEO，网络请求数据是必须要在服务端生命周期完成的，有asyncData和fetch

* 只能在pages下的页面.vue文件使用

* this指向undefined

代码：

```
<script>
export default {
  //...
  async asyncData(context) {
    //app是Vue
    console.log("asyncData");
    let list = 网络请求().data;
    //return后混入到data()
    return {list};
  }
};
</script>
```

② fetch

特点：

* 第五个执行

* 类似于asyncData

* 所有的.vue文件都可以用

* this，指向组件实例，且能获取到data()

```
<script>
export default {
  //...
  data(){
    return {
      list: []
    }
  },
  async fetch(context) {
    console.log("fetch");
    this.list = await 网络请求();
  },
};
</script>
```

总结：

* pages目录下的页面使用asyncData

* 其他目录下的组件使用fetch

## 2 注意事项

* 路由的导航守卫、middleware都可以做导航守卫

* 路由的导航守卫在第一次进入网站执行一次，时机比nuxtServerInit都早。随后的路由跳转就会再执行，比的middleware早。

* context和window
  
  服务端上下文context：
  
  每个服务端钩子都有这个参数，是一个对象，包含store，路由，redirect跳转，query，res，req等。
  
  window：
  
  路由自身的导航守卫，服务端的钩子，plugins执行的时机还没有到浏览器，所以都没有window对象，无法使用cookie，localStorage等，需要借助一些库，如 coolie-yniversal-nuxt
  
  ```
  npm install --save coolie-universal-nuxt
  ```
  
  ```
  // /nuxt/config.js
  export default {
    //...
    modules: ['cookie-universal-nuxt']
  }
  ```
  
  ```
  context.$cookies.set('token','123');
  context.$cookies.get('token');
  this.$cookies.set('token','123');
  this.$cookies.get('token');
  ```
  
  123

# 四、Nuxt的路由

（2）路由配置

Nuxt中的路由是自动配置的，在 /pages 下创建.vue文件后就会自动配置。

具体的路由配置可以看 /.nuxt/router.js

\<router-view /\>变成了\<nuxt /\>，入口在 /.nuxt/layouts/default.vue

一级路由的目录结构和对应的路由配置

```
pages/
--| user/
-----| index.vue
-----| one.vue
--| index.vue
```

```
router: {
  routes: [
    {
      name: 'index',
      path: '/',
      component: 'pages/index.vue'
    },
    {
      name: 'user',
      path: '/user',
      component: 'pages/user/index.vue'
    },
    {
      name: 'user-one',
      path: '/user/one',
      component: 'pages/user/one.vue'
    }
  ]
}
```

嵌套路由：

在父级组件中使用\<nuxt-child /\>而不是\<router-view /\>

```
pages/
--| users/
-----| _id.vue
-----| index.vue
--| users.vue
```

```
router: {
  routes: [
    {
      path: '/users',
      component: 'pages/users.vue',
      children: [
        {
          path: '',
          component: 'pages/users/index.vue',
          name: 'users'
        },
        {
          path: ':id',
          component: 'pages/users/_id.vue',
          name: 'users-id'
        }
      ]
    }
  ]
}
```

动态路由：

```
pages/
--| _slug/
-----| comments.vue
-----| index.vue
--| users/
-----| _id.vue
--| index.vue
```

```
router: {
  routes: [
    {
      name: 'index',
      path: '/',
      component: 'pages/index.vue'
    },
    {
      name: 'users-id',
      path: '/users/:id?',
      component: 'pages/users/_id.vue'
    },
    {
      name: 'slug',
      path: '/:slug',
      component: 'pages/_slug/index.vue'
    },
    {
      name: 'slug-comments',
      path: '/:slug/comments',
      component: 'pages/_slug/comments.vue'
    }
  ]
}
```

（2）手动配置路由

如果想自己配置路由，或者SPA项目重构成Nuxt项目觉得呢种目录配置路由十分麻烦，则采用下面的方法：

```
npm install --save @nuxtjs/router
```

```
// nuxt.config.js
export default {
  //...
  modules: [
    //...
    '@nuxtjs/router'  
  ],
}
```

再在根目录下创建 router.js：

```
import Vue from 'vue';
import VueRouter from 'vue-router';
Vue.use(VueRouter);

const routes = [];

//与Vue不同的是需要导出函数
export function createRouter(){
  return new VueRouter({
    routes
  ));
}
```

（3）路由懒加载

SSR不需要懒加载，因为都是客户端需要什么页面，后端再渲染完给客户端。

（4）路由跳转与传参：

传参和获取参数和Vue一样，只是声明式导航多了个a，router-link变成了nuxt-link

```
<!-- 会刷新页面 -->-->
<a href="/about">跳转</a>
<!-- 不会刷新页面 -->-->
<nuxt-link to="/about">跳转</nuxt-link>
```

# 五、Nuxt的vuex

store目录下的每个js文件是一个module，index为根模块，js文件内容如下：

```
export const state = () => {};
export const getters = {};
export const mutations = {};
export const actions = {};
```

如果是想Vue那样的使用方式或者Vue项目重构构为Nuxt项目，只需要改动一个地方：

```
//原本
const store = new ...;
export default store;

//改为
const store = function(){
  return new ...
};
export default store
```

## 六、Nuxt3

支持Vue3

## 1 初始化

```
npx nuxi init xxx
```

如果科学上网页无法初始化，那就是bug还没修复，那就直接从github的nuxt的v3分支上clone下来：

```
git clone -b v3 https://github.com/nuxt/starter.git
```

```
cd xxx
npm install
```

## 2 路由

动态路由变为：

```
pages/
--| about.vue
--| posts/
----| [id].vue
```
