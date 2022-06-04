# 一、基本介绍和npm

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



# 二、webpack

npm install -g webpack

Webpack可以热更新：代码一修改保存后页面自动刷新，但有时不靠谱，还需要自己冷更新，自

己主动刷新页面。
可以兼容任何语法的html，css，js，管理包，并将他们压缩打包
与Grunt和Gulp对比：
Grunt和Gulp可以优化前端开发流程，而webpack是模块化的解决方案，没有可比性，大多数场合webpack都能替代Grunt和Gulp。
Grunt和Gulp的工作方式：一个配置文件中，能明确对某些文件的编译，组合，压缩等操作的具体步骤。
webpack优点：

* 很好的应用于单页面应用

* 同时支持require和import

* 让react，vue等框架在本地开发更快

* 目前最受欢迎的构建工具

（1）package.json

npm init   创建package.json

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

# 三、Vue CLI

脚手架自动创建目录，自动安装依赖，自动配置webpack

脚手架配置了HTML驼峰标识

es-lint是强制的代码规范，不规范会报错
runtime-compiler  runtime-only区别在于template的渲染上
runtime-compiler template-ast-render-vdom-UI
runtime-only render-vdom-UI 效率高些且代码更少，使用这种的更多
虽然only无法解析template，但是vue-loader会把所有template编译成render函数，就能使用。

# 四、Vite
