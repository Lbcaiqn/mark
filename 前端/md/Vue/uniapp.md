# 一、基本

uniapp用vue的语法开发小程序、安卓、ios等

开发工具-HBuilder：

切换快捷键方案：工具-预设快捷键方案切换-VS Code

主题切换：工具-主题

字体等设置：工具-设置-就能打开settings.json

项目创建和运行：

HBuilder中新建项目，而不是webpack或vite创建

hbuilder保存后微信开发者工具会热更新（json不会），所以最好编译一下

配置文件：

HBuilder的json文件一些会变成图形界面（manifast.json settings.json，点开后可在左侧栏最下面点击源码视图），一些不会

manifast.json是整个项目的配置文件，可配置项目名，Vue版本，小程序的appid，logo等

pages.json类似于原生小程序，配置页面路由、窗口样式、导航栏、tabBar等。

第三方库安装；

部分npm安装

部分在uniapp插件市场安装（如less，sass），若使用时未安装也会自动安装

HBuilder的项目运行到微信开发者工具查看效果：

1. HBuilder-manifaset.json-微信小程序配置-appid

2. HBuilder-工具-设置-运行配置-小程序运行配置-微信开发者工具路径

3. 微信开发者工具-设置-安全-服务端口

4. HBuilder-运行-运行到小程序模拟器-微信开发者工具   就会编译成微信小程序的代码并打开微信开发者工具，HBuilder修改代码保存后微信开发者工具会热更新

.gitignore需要忽略的文件：

```
/node_modules
/unpackage/dist
```

unpackage为了防止没有文件而不提交的本地库，需要在里面新建.gitkeep文件占位

# 语法

采用Vue语法+微信小程序配置文件的开发模式

uniapp的顶级对象是uni，有各个端的api，微信小程序的全部api都可以通过uni调用，

可以通过 uni.xxx = yyy 来挂载到uni

每个页面对应一个.vue文件，可以使用所有的Vue语法，此外还可以使用微信小程序的组件、生命周期

注意：若使用了div，span，img，input，button，编译成微信小程序会变成view，text，image，input，button

Vue3.2

```
//微信小程序的生命周期和上拉加载等等在Vue2 Vue3.0都可以写在配置项中，而Vue3.2的script setup用法如下：
<script setup>
import {onLoad} from '@dcloudio/uni-app'
onLoad((options) => {
    console.log(options)
})
</script>
```

全局样式：

```
//app.vue
<style>
page {
    
}
</style>
```



配置文件：

amnifast.json里的mp-weixin配置项就是微信小程序project.config.json的相关配置

pages.json和微信小程序的app.json用法一样，可配置页面，导航栏，tabBar等，

不同点：

1. window配置项变成了globalStyle

2. pages配置项不是数组，而是对象，每个对象可以放path，style，style里面就是微信小程序各个页面的json文件中的样式属性，会覆盖全局配置的样式

分包的使用与微信小程序相同，但是pages配置项和主包一样可以设置style

如在根目录下创建packageA文件夹作为分包，里面创建 GoodsDetail/GoodsDetail.vue

```
"subpackages": [
  {
    "root":"packageA",
    "pages":[{
      "path": "GoodsDetail/GoodsDetail",
      "style": {}
    }]
  }
],
```

自定义组件都放在 /components 目录下，可通过右键新建组件快速创建

自定义组件不用像vue需要引入注册，也不需要像微信小程序需要配置json，而是直接使用



uni-ui：

跑版本会自动放在components中，新版本需要自己新建一个uni_modules文件夹，栽倒dcloud官网下载uni-ui

uni-ui的组件都不需要引入就可以直接使用

uni-ui可以直接修改源代码
uni-ui直接给class无法修改样式
uni-ui常用：
<uni-icons type="home" :size="18">
<uni-tag>
<uni-number-box>
<uni-goods-nav>
<uni-swipe-action>

# 网络请求

微信小程序无法使用axios，原生小程序的网络请求API功能也不够用（如没有拦截器）

```
npm install --save @escook/request-miniprogram

//main.js
//挂载到uni，可以使用拦截器，里面调用微信小程序的api
import {$http} from '@escook/request-miniprogram'
$http.baseUrl = '...'
//请求拦截器
$http.beforeRequest = (opt) => {
  uni.showLoading({
    title: '加载中...'
  })
}
//响应拦截器
$http.afterRequest = (res) => {
  uni.hideLoading()
}
uni.$http = $http

//用到的地方中
uni.$http.get('/api/public/v1/home/swiperdata').then(res => {
    console.log(res.data)
})
```

注意，由于项目最终运行到微信小程序端，所以网络请求的要求也和微信小程序一样，需要配置合法域名，或勾选不检验合法域名

# 多端兼容

uniapp编写微信小程序，最终是编译成微信小程序代码的，一些微信小程序的限制也会存在，如id选择器，通配符选择器无效

ios设备，即使是ios的小程序对.webp格式的图片支持都不太好



# 发布

uniapp发布微信小程序：
1.微信后台-开发-开发管理-开发设置-服务器域名-来设置合法域名
2.dcloud开发者中心-创建项目-复制项目的appid到manifast.json中
3.复制小程序appid到manifast.json】
4。HBuilder-发行-小程序微信-输入小程序名和小程序appid点击发行
5.弹出的微信开发者工具-上传-输入版本号上传
6.微信后台-管理-版本管理-提交审核

123
