# 动画库

animate.css

动画库

```
npm install --save animate.css
```

使用：

只需要修改enter-active和leave-active类名即可，如动画fadeIn，fadeOut

```
<template>
  <div>
    <transition 
      enter-active-class="animate__animated animate__fadeIn"
      leave-active-class="animate__animated animate__fadeOut"
    >
    </transition>
  </div>    
</template>
<script>
import 'animate.css'
...
</script>
```

若是animate3，则不需要加animate__animated
animate4以上版本需要加上animate__animated
其他动画类名详见官网

动画库gsap

Vue官方推荐的动画库

npm install --save gsap

import gsap from 'gsap'

```
//@before-enter="enterFrom"
enterFrom(el){
 gsap.set(el,{
 width: 0,
 height: 0
 })
},
//@enter="enterActive"
enterActive(el,done){
 gsap.to(el,{
 width: 100,
 height: 100,
 onComplete: done
 })
}
```

# echarts

安装：

```
npm install --save echarts
```

引入

```
//import echarts from 'echarts'       //4及以下版本
import * as echarts from 'echarts'  //5及以上版本
```

基本使用：

首先需要准备可视化区域的盒子，必须具有宽和高，盒子里面不需要有任何内容。

由于echarts需要基于这个盒子进行渲染，所以需要在DOM加载完之后，也就是mounted中写echarts代码。

```

```
