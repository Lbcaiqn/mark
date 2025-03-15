# 一、Vue

## 1 基本

（1）基本使用

Vue 中函数的 this 指向 Vue 实例。

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <script src="https://cdn.jsdelivr.net/npm/vue@2.7.16/dist/vue.js"></script>
  </head>
  <body>
    <div id="app"></div>
  </body>
  <script>
    // 各个配置项叫 OptionsAPI (选项式 API)
    const app = new Vue({
      el: "#app",
      data() {
        return {
          list: [10, 20, 30],
        };
      },

      methods: {
        itemClick(e) {
          console.log(e);
        },
      },

      render(h) {
        return h(
          "ul",
          { attrs: { class: "list" } },

          this.list.map((item) => {
            return h(
              "li",
              {
                attrs: {
                  class: "item",
                },
                on: {
                  click: this.itemClick,
                },
              },
              item
            );
          })
        );
      },
    });
  </script>
</html>
```

通过 el 绑定 Vue 的工作区域，通过 render 使用 data、method 等生成一个虚拟 DOM （Virtual DOM），再把虚拟 DOM 渲染成页面的真实 DOM 。

render 使用比较麻烦，也可以直接在 template 中写 HTML ：注意一旦写了 render ，就会使用 render ，而不会使用 templatre ：

```
const app = new Vue({
  el: "#app",
  template: `
    <ul>
      <li>123</li>
    </ul>
  `,
});
```

template（模板）本质上 render 的语法糖，Vue 会把 template 的内容编译成 render 函数。

（2）脚手架

使用 webpack ，基本上脚手架 2 不再使用了，至少都是 3 以上，Vue3 需要 4.5 版本以上才支持：

```
npm install -g @vue/cli
vue -V
vue create projectname
```

也可以使用 vite ：

```
npm create vite@latest
```

配置文件：

* webpack：vue\.config\.js

* vite：vite\.config\.js

非单文件组件：

```
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <script src="https://cdn.jsdelivr.net/npm/vue@2.7.16/dist/vue.js"></script>
  </head>
  <body>
    <div id="app"></div>
  </body>
  <script>
    const cpn1 = Vue.extend({
      template: `<div>cpn1</div>`,
    });

    // 注册全局组件
    // Vue.component("cpn2", cpn1);

    const app = new Vue({
      el: "#app",
      // 注册局部组件
      components: {
        cpn1,
        cpn2: {
          template: `<div>cpn2</div>`,
        },
      },
      template: `
        <div>
          <cpn1 />
          <cpn2 />  
        </div>
      `,
    });
  </script>
</html>
```

单文件组件（SFC），Vue 允许在 .vue 文件中编写代码：

```
<script>
// cpn.vue

// 引入样式
// import "./1.css";

// 导出组件
export default {
  // 除根组件 App 外，其他组件的 data 必须是函数 return obj 的形式，这是为了防止组件多次使用的 data 冲突
  // Vue3 中 App 若是 OptionsAPI ，data 也必须是函数形式
  data() {
    return {};
  },
};
</script>

<!-- template
  * template 不会渲染到真实 DOM ；在木模板内部也可以用 template 作为包裹的虚拟元素
  * template 只能用 v-if、v-else、v-else-if、v-for、无法使用 v-show
 -->
<template>
  <div>
    <p>template 必须有且只有一个根元素，作为虚拟 DOM 树的根节点</p>
  </div>
</template>

<!-- style
  * scoped: 样式不会影响外部
  * scoped 原理: 是设置 scoped 后组件会多一个自定义属性 data-v-xxx ，再用属性选择器
  * 一般 App 不加 scoped ，做一些全局样式；其他组件加 scoped ，防止冲突
 -->
<style scoped>
/* 引入样式，会收到 scoped 影响加上属性选择器 */
/* @import "./1.css"; */

/**修改有 scoped 的子组件样式，如组件库
 * 在无 scoped 的 App.vue 修改
 * 在这里用样式穿透 /deep/ 修改
 */
/deep/ .el-input__inner {
}
</style>
```

```
<script>
// App.vue

import cpn from "./cpn.vue";

export default {
  components: { cpn },
};
</script>

<template>
  <div>
    <cpn />
  </div>
</template>

<style></style>
```

（3）MVVM 模式

Angular 使用 MVC 模式，而 Vue、React 使用 MVVM 模式：

* Model：模型、即 data、methods、生命周期等

* View：视图，即 render 出的页面

* View Model：视图模型，即 Vue 实例，包含 data binding 和 DOM listeners ，通过 Model 数据驱动 View 的显示和更新

（4）相关工具

浏览器vue调试插件：vue devtools ，Vue2、Vue3 使用的版本不同。

vscode Vue 语法插件：

* Vue2：vetur

* Vue3：volar

为了防止冲突，浏览器、vscoide 插件在使用 Vue3 时最好删除 Vue2 的插件。

## 2 语法

可以关闭生产环境提示：

```
Vue.config.productionTio = false;
```

这个提示意思是在生产环境应使用 min 的 Vue 。

Vue3 中会自动判断是否是生产环境，就不用手动关了。

（1）插值语法、数据绑定、指令

```
<script>
export default {
  data() {
    return {
      hello: "hello",

      inpValue: 123,
      isDisable: true,

      imgUrl: "./1.jpg",
      // imgSrc: require("./1.jpg"),

      title: "title",
      titleClass2: "title2",
    };
  },

  methods: {
    say() {
      return "world";
    },
  },

  // 滴定仪指令
  directives: {
    xxx(e, binding) {
      console.log(binding.value);
    },
    yyy: {
      // 指令绑定到元素时回调
      bind(e, binding) {},

      // 元素 render 为真实 DOM 时回调
      inserted(e, binding) {},

      // 数据更新时回调
      update(e, binding) {},
    },
  },
};
</script>

<template>
  <div>
    <!-- this 可以省略 -->

    <!-- 插值语法，也叫 Mustache 语法，内容为 JS 表达式，作用是使用 Model -->
    <div>{{ hello + " " + say() }}</div>

    <!-- 数据绑定指令，v-bind 可以省略 -->
    <input type="text" v-bind:value="inpValue" :disabled="isDisable" />

    <!-- 绑定图片 src
      * 不能使用绝对路径，只能是相对路径、或 webpack 、vite 配置的路径
      * 只有网络 url 和 static 穆棱下的路径才有效
      * 要解决上面 2 个问题，则在 data 中需要使用 require()
    -->
    <img :src="imgUrl" alt="" />

    <!-- 绑定样式 -->
    <p class="title1" :class="titleClass2">{{ title }}</p>
    <p :class="{ title1: true, [titleClass2]: true }">{{ title }}</p>
    <p :style="{ backgroundColor: '#000', color: '#fff' }">{{ title }}</p>
    <p :style="[{ backgroundColor: '#000' }, { color: '#fff' }]">
      {{ title }}
    </p>

    <!-- v-once ，只 render 一次，并缓存，以后每次 render 都会忽略它 -->
    <div v-once>v-once</div>

    <!-- v-pre ，不解析差值语法 -->
    <div v-pre>{{ 不解析插值语法 }}</div>

    <!-- v-clock ，JS 未解析完成时，隐藏该元素（display: none;） -->
    <div v-clock>v-clock</div>

    <!-- v-text、v-html，即 innerText、innerHTML -->
    <div v-text="'123'"></div>
    <div v-html="'<input />'"></div>

    <!-- 自定义指令 -->
    <div v-xxx="'自定义指令'"></div>
  </div>
</template>

<style scoped>
.title1 {
  background-color: #000;
}

.title2 {
  color: #fff;
}
</style>
```

（2）事件绑定

```
<script>
export default {
  methods: {
    click1() {
      console.log("click1");
    },

    click2(e) {
      console.log("click2", e);
    },

    click3(a, b) {
      console.log(a, b);
    },

    click4(e, a, b) {
      console.log(e, a, b);
    },

    click5(a, e, b) {
      console.log(a, e, b);
    },

    click6(e1, e2) {
      console.log(e1, e2);
    },
  },
};
</script>

<template>
  <div>
    <ul>
      <!-- v-on:name="" v-on: 可以省略成 @ -->
      <li @click="console.log('事件函数只有一行可以简写')">0</li>

      <!-- 无参数 -->
      <li @click="click1">click1</li>

      <!-- 传入事件对象，不传参数默认会传入事件对象 -->
      <li @click="click2">click2</li>
      <li @click="click2($event)">click2</li>

      <!-- 传参 -->
      <li @click="click3(1, 2)">click3</li>

      <!-- 传入事件对象 -->
      <li @click="click4($event, 1, 2)">click4</li>
      <li @click="click5(1, $event, 2)">click5</li>
      <li @click="click6($event, $event)">click6</li>

      <!-- 事件修饰符 -->
      <li @click.stop="console.log('stop')">阻止事件冒泡</li>
      <li @click.prevent="console.log('prevent')">阻止默认行为</li>
      <li @click.once="console.log('once')">只执行一次</li>

      <!-- 使得组件可以监听原生事件、Vue3 已删除
       * 组件绑定的事件默认会认为是自定义事件、Vue3 更是只认 emits 声明的事件
       * .native 其实是给组件根元素绑定事件，不推荐，所以 Vue3 就删除了，让具体触发
         事件的元素 emit 自定义事件即可
      -->
      <li @click.native="console.log('native')">native</li>

      <!-- keycode 修饰符，Vue3 已删除，原因是兼容性差
       * 若要使用 keycode，只能用原生 JS
       * input 的 enter 键，可以用 <form> 包裹 input 、监听 submit 即可
      -->
      <li @keydown.13="console.log('keycode')">keycode，Vue3 已删除</li>
    </ul>
  </div>
</template>
```

（3）v-model 双向绑定

用于绑定表单，是数据绑定、事件绑定的语法糖。

```
<script>
export default {
  data() {
    return {
      inpValue: "input",
      textAreaValue: "textarea",

      radios: {
        // 默认选中
        value: "b",
        items: [
          { value: "a", text: "选项 A" },
          { value: "b", text: "选项 B" },
          { value: "c", text: "选项 C" },
          { value: "d", text: "选项 D" },
        ],
      },

      checkboxs: {
        // 默认选中
        value: ["b", "c"],
        items: [
          { value: "a", text: "选项 A" },
          { value: "b", text: "选项 B" },
          { value: "c", text: "选项 C" },
          { value: "d", text: "选项 D" },
        ],
      },

      agree: true,

      select: {
        // 默认选中
        value: "2000",
        items: [
          { value: "", text: "请选择年份" },
          { value: "1999", text: "1999年" },
          { value: "2000", text: "2000年" },
          { value: "2001", text: "2001年" },
        ],
      },

      inp1: "1",
      inp2: "2",
      inp3: "3",
    };
  },
};
</script>

<template>
  <div>
    <!-- text、textarea :value @input -->
    <div><input type="text" v-model="inpValue" />{{ inpValue }}</div>
    <div><textarea v-model="textAreaValue" />{{ textAreaValue }}</div>

    <!-- radio :value @change -->
    <div>
      <label v-for="i in radios.items" :key="i.value">
        <input type="radio" v-model="radios.value" :value="i.value" />
        <span>{{ i.text }}</span>
      </label>
      <p>我已选中 {{ radios.value }}</p>
    </div>

    <!-- checkbox :value @change -->
    <div>
      <label v-for="i in checkboxs.items" :key="i.value">
        <input type="checkbox" v-model="checkboxs.value" :value="i.value" />
        <span>{{ i.text }}</span>
      </label>
      <p>我已选中 {{ checkboxs.value }}</p>
    </div>

    <!-- 单个 checkbox :value @change -->
    <div><input type="checkbox" v-model="agree" />{{ agree }}</div>

    <!-- select :value @change -->
    <div>
      <select v-model="select.value">
        <!-- <option value="">{{ select.describe }}</option> -->
        <option v-for="i in select.items" :key="i.value" :value="i.value">
          {{ i.text }}
        </option>
      </select>
    </div>

    <!-- v-model 修饰符 -->
    <div>
      <div><input type="text" v-model.lazy="inp1" />{{ inpValue }} 只有失焦、按下回车才响应</div>
      <div><input type="text" v-model.number="inp2" />{{ inpValue }} 转为 number</div>
      <div><input type="text" v-model.trim="inp3" />{{ inpValue }} 去掉首尾空格</div>
    </div>
  </div>
</template>
```

（4）计算属性、watch

```
<script>
export default {
  data() {
    return {
      a: 1,
      b: 2,
      c: 3,

      d: 4,
      e: { e1: 5, e2: { ee: 6 } },
    };
  },

  /**计算属性
   * 看作是属性，所以无法传参；不能 return function
   * 和 function 的区别是，function 每次 render 都会执行，而 computed 具有缓存功能，只有内部用到的数据修改时才会执行
   * computed 一开始会执行一次
   */
  computed: {
    // 简写
    sum() {
      // sum 依赖于 a、b、c ，所以 a、b、c 修改时 sum 执行
      console.log("computed sum run");
      console.log(this.c);
      return this.a + this.b;
    },

    // 完整写法
    total: {
      // 简写的 computed 就是 get
      get(...args) {
        console.log("computed total get run");
        console.log(this.c);
        return this.a + this.b;
      },

      // 修改 computed 时回调
      set(newValue) {
        console.log("computed total get run");
        this.a = newValue;
        this.b = newValue;
      },
    },
  },

  // 过滤器，Vue3 已删除，完全可以用 computed、function 代替
  filters: {
    myToFixed(value) {
      return value.toFixed(2);
    },
  },

  /**侦听器
   * 用于监听数据的变化，数据修改就会回调
   * 一开始不执行，除非设置了 immediate
   * 默认不会深度监听嵌套结构，除非设置了 deep
   */
  watch: {
    // 简写
    d(newVal, oldVal) {
      console.log(newVal, oldVal);
    },

    // 完整写法，可以设置配置项
    e: {
      immediate: true,
      deep: true,
      handler(newVal, oldVal) {
        console.log(newVal, oldVal);
      },
    },

    // 复杂属性要加上 ""
    "e.e1": function (newVal, oldVal) {
      console.log(newVal, oldVal);
    },
  },
};
</script>

<template>
  <div>
    <!-- 计算属性 -->
    <div>
      <span>{{ sum }}</span>
      <button @click="++a">add a {{ a }}</button>
      <button @click="++b">add b {{ b }}</button>
      <button @click="++c">add c {{ c }}</button>
    </div>
    <div>{{ this.total }}</div>
    <button @click="total = 123">set total</button>

    <!-- 过滤器，Vue3 已删除 -->
    <!-- <div>{{ 3.14 | myToFixed }}</div> -->

    <!-- 侦听器 -->
    <div>
      <span>{{ d }}</span>
      <span>{{ e }}</span>
    </div>
    <div>
      <button @click="++d">add d</button>
      <button @click="++e.e1">add e1</button>
      <button @click="++e.e2.ee">add e2</button>
    </div>
  </div>
</template>
```

computed 和 watch 都会在数据变化时回调，不同的是：

- 应用场景不同：computed 主要是做数据处理，且只能做同步操作；watch 主要是监听数据变化并做一些事，同步、异步操作都可以

- 数据量不同：computed 可以同时监听多个数据，而 watch 只能监听一个

- 初始不同：computed 在模板使用时、一开始执行一次，而 watch 不用在模板使用，只有设置 immediate 才会一开始执行一次

（5）条件渲染、列表渲染

基本使用：

```
<script>
export default {
  data() {
    return {
      isShow: true,
      list: [
        { id: 1, value: 10 },
        { id: 2, value: 20 },
        { id: 3, value: 30 },
      ],
    };
  },
};
</script>

<template>
  <div>
    <!-- 条件渲染 
     * v-show 和 v-if、v-else、v-else-if
     * v-if 优先级高于 v-show ，只有 v-if 显示元素时，v-show 才有意义
     * v-show、v-if 和 v-once 一起使用时，由于 v-once 只渲染一次，所以显示隐藏状态只会是初始状态 
    -->
    <div v-show="isShow">
      v-show，即 display: none; 适合需要频繁切换显示隐藏的场景
    </div>
    <div v-if="isShow">
      v-if，隐藏时直接删除元素，适合不需要频繁切换，或初始不需要显示的场景，提供初始渲染速度s
    </div>

    <!-- 列表渲染 
     * 不需要 index 也可以 i in this.list
     * 也可以遍历 Object ，(value, key, index) in obj
     * 也可以用数字 i in 10
     * key 默认为 index ，最好给 key 唯一的 id ，提高 diff 算法性能 
    -->
    <ul>
      <li v-for="(i, iIndex) in list" :key="i.id">
        {{ `index: ${iIndex}，value: ${i.value}` }}
      </li>
    </ul>
  </div>
</template>
```

v-if、v-for 结合的场景；

```
<script>
export default {
  data() {
    return {
      isShow: true,
      list: [
        { id: 1, value: 10 },
        { id: 2, value: 20 },
        { id: 3, value: 30 },
      ],
    };
  },

  computed: {
    filterList() {
      return this.list.filter((item) => item.value >= 20);
    },
  },
};
</script>

<template>
  <div>
    <!-- 优先级 
     * Vue2: v-for 高于 v-if，Vue2 会有警告，因为 v-for 再 v-if 删除元素其实是没必要的
     * Vue3: v-if 高于 v-for，v-if 先执行但此时 i 还没有遍历出来，所以会报错 
    -->

    <!-- 用计算属性代替 -->
    <ul>
      <li v-for="i in filterList">{{ i.value }}</li>
    </ul>

    <!-- 用 v-show 代替，不推荐 -->
    <ul>
      <li v-for="i in list" v-show="i.value >= 20">{{ i.value }}</li>
    </ul>

    <!-- 如果需要显示隐藏整个列表，可以用 template 代替，template 只能用 v-if ，不能用 v-show -->
    <template v-if="isShow">
      <ul>
        <li v-for="i in list">{{ i.value }}</li>
      </ul>
    </template>
  </div>
</template>
```

长列表渲染，会消耗大量性能，解决方法：

```
<script>
export default {
  data() {
    return {
      list: [],
      page: 1,
      pageSize: 10,
    };
  },

  mounted() {
    for (let i = 0; i < 10000; i++) this.list.push({ id: i, value: i });
  },

  computed: {
    // 可以分页，一页固定 n 条数据，如表格显示
    nowList1() {
      return this.list.slice(
        (this.page - 1) * this.pageSize,
        this.page * this.pageSize
      );
    },

    // 可以分片，数据量主键从 0 增多，如上拉加载更多
    nowList2() {
      return this.list.slice(0, this.page * this.pageSize);
    },
  },
};
</script>

<template>
  <div>
    <!-- 分页或分片 -->
    <ul>
      <li v-for="i in nowList1">{{ i }}</li>
    </ul>

    <!-- 虚拟列表，也叫虚拟滚动
     * 只展示视口能放得下的数据
     * 第三方库：vue-virtual-scroller 或 vue-virtual-scroll-grid 
    -->

    <!-- 优化数据更新 
     * v-once: 若数据不需要更新，可以使用 v-once
     * v-memo: 若数据需要更新，可以使用 v-memo 缓存下来 
    -->
  </div>
</template>
```

（6）生命周期

生命周期函数、也叫生命周期钩子，在 Vue 特定时刻回调。

不能用 async 修饰。

```
<script>
export default {
  data() {
    return {
      a: 1,
    };
  },

  /**初始化
   * el 挂载之前的阶段，组件在此时创建
   * 若 Vue 没有指定 el ，则生命周期在 created 后就停止
   */
  beforeCreate() {
    console.log(
      "beforeCreate，组件还未创建，无法使用 data 等；通常用来做插件开发"
    );
  },
  created() {
    console.log("created，组件创建完毕，可以 ajax 了");
  },

  // el 挂载
  beforeMount() {
    console.log("beforeMount，编译 template 为 render 函数，生成学你 DOM");
  },
  mounted() {
    console.log("mounted，此时真是 DOM 渲染完毕");
  },

  // 数据更新
  beforeUpdate() {
    console.log(
      "beforeUpdate，生成新的虚拟 DOM ，用 diff 算法比较新旧虚拟 DOM"
    );
  },
  updated() {
    console.log("updated，数据更新完毕，但真实 DOM 还未渲染完毕");

    this.$nextTick(function () {
      console.log("真实 DOM 更新完毕");
    });
  },

  // 销毁
  beforeDestroy() {
    console.log("beforeDestroy，用于清除副作用，如定时器等");
  },
  destroyed() {
    console.log("destroyed，销毁完毕");
  },

  // 路由钩子，路由组件才有，路由激活、失活回调
  activated() {},
  deactivated() {},

  // 测试钩子
  errorCaptured() {},
};
</script>

<template>
  <div>
    <button @click="++a">add a {{ this.a }}</button>
  </div>
</template>
```

父子组件生命周期的顺序：

```
初始化、挂载
父：bc -> c -> bm                    | -> m 
子：            |-> bc -> c -> bm -> m

更新
父：bu ->         | -> u
子：   | -> bu -> u 

销毁
父：bd ->         | -> d
子：   | -> bd -> d 
```

多个子组件就按顺序依次走完各个子组件的生命周期。

（7）过渡

```
<script>
export default {
  data() {
    return {
      isShow: true,
    };
  },
};
</script>

<template>
  <div>
    <div>
      <button @click="isShow = !isShow">
        {{ isShow ? "hidden" : "show" }}
      </button>
    </div>

    <!-- 属性
     * name: v-enter 等适用于所有 <transition> ，而 name-enter 只适用于对应 name 的 <transition> 
     * appear: 页面刷新就过渡
     * duration="1000" : 单位 ms ，过渡时间
      -->
    <transition>
      <!-- 只能有一个根元素，要多个可以用 <transition-group> -->
      <div class="box" v-show="isShow"></div>
    </transition>
  </div>
</template>

<style scoped>
.box {
  border: 1px solid #000;
  width: 100px;
  height: 100px;
  background-color: #000;
}

/* vue3 v-enter 改为 v-enter-from */
.v-enter,
.v-leave-to {
  width: 0px;
  height: 0px;
}

/* vue3 v-leave 改为 v-leave-from */
.v-enter-to,
.v-leave {
  width: 100px;
  height: 100px;
}

.v-enter-active,
.v-leave-active {
  transition: 1s;
}
</style>
```

## 3 组件

组件：

- 组件命名：大驼峰，如 AaaBbb ，使用时也可以 ，可用单标签、双标签。

- 自定义组件无法绑定原生事件，除非加上 .native ，因为 Vue 默认认为自定义组件绑定的是自定义事件（Vue3 删除了 .native ，彻底无法绑定原生事件，可以在子组件中具体要触发事件的元素绑定自定义事件代替）

- v-if 都会走一遍组件生命周期；而 v\-show 不会，因为不删除组件；避免大量 v\-if 组件的场景、组件渲染性能消耗比原生 DOM 大得多

### 3.1 组件通信

要保证单向数据流，数据只能从父组件传递给子组件，子组件不会直接修改父组件的数据，只能通过通信让父组件自己修改，这是为了可维护性。

组件通信都是响应式的。

（1）父子组件通信：

props：

```
<script>
// 子组件

export default {
  // 只能是传递 data、methods，不能传 computed

  // 方式一
  // props: ["num", "fn"],

  // 方式二
  // props: {
  //   num: Number,
  //   fn: Function,
  // },

  // 方式三
  props: {
    num: {
      type: Number,
      Required: true,

      // 数组、对象默认值需要写成 default() { return [] 或 {} }
      default: 0,
    },

    fn: Function,
  },

  /**props 和 data、methods 冲突测试
   * template 中：使用顺序靠后的
   * script 中：不按顺序，data、props 冲突时使用 data；props、methods 冲突时使用 props
   */
  // data() {
  //   return {
  //     num: "子组件 num",
  //   };
  // },

  methods: {
    // fn() {
    //   return "子组件 fn";
    // },

    showProps() {
      console.log(this.num, this.fn() === this);
    },
  },
};
</script>

<template>
  <div>
    <div>{{ num }}</div>
    <div>{{ fn() }}</div>
    <div>{{ showProps() }}</div>
  </div>
</template>
```

```
<script>
// 父组件

import cpn from "./cpn.vue";

export default {
  components: { cpn },

  data() {
    return {
      n: 1,
    };
  },

  methods: {
    func() {
      // 传给子组件后，this 依然是父组件
      return this;
    },
  },
};
</script>

<template>
  <div>
    <cpn :num="n" :fn="func" />
  </div>
</template>
```

emit 自定义事件：

```
<script>
// 子组件

export default {
  methods: {
    btnClick() {
      this.$emit("btnClick", {
        a: 1,
      });
    },
  },
};
</script>

<template>
  <div>
    <button @click="btnClick">emit</button>
  </div>
</template>
```

```
<script>
// 父组件

import cpn from "./cpn.vue";

export default {
  components: { cpn },

  methods: {
    func(e) {
      console.log(e.a);
    },
  },
};
</script>

<template>
  <div>
    <cpn @btnClick="func" />
  </div>
</template>
```

组件 v\-model 和 \.sync ：

props、emit 的语法糖，组件 v-model 默认的 props 是 value ，event 是 input ，可以用配置项 model 修改；如果像 v-model 更多数据，需要使用 \.sync 修饰符：

```
<script>
// 子组件

export default {
  // 可以修改默认的 value ，和 input
  // vUE3 已删除，默认的是 modelValue 和 update:modelValue
  model: {
    // prop: "valueValue",
    // event: "inputInput",
  },

  props: ["value", "msg"],

  // Vue3 v-model 可以定义修饰符
  // props: {
  //   modelValue: Number,
  //   msg; String,
  //   modelModifiers: { xxx: Boolean, yyy: Boolean },
  //   msgModifiers: { mmm; Boolean },  
  // }
};
</script>

<template>
  <div>
    <input type="text" :value="value" @input="$emit("input",value)" />
    <input type="text" :value="msg" @input="$emit("update:msg",msg)" />
  </div>
</template>
```

```
<script>
// 父组件

import cpn from "./cpn.vue";

export default {
  components: { cpn },

  data() {
    return {
      inpValue: 123,
      msg: "msg",
    };
  },
};
</script>

<template>
  <div>
    <!-- Vue2，只能由一个 v-model ，其他用 .sync -->
    <cpn v-model="inpValue" :msg.sync="msg" />

    <!-- 等价于 Vue2 
    <cpn
      :value="inpValue"
      @input="value = $event"
      :msg="msg"
      @update:msg="msg = $event"
    /> 
    -->

  <!-- Vue3，删除了 .sync ，用多个 v-model 代替 -->
  <!-- <cpn v-model="inpValue" v-model:msg="msg" /> -->

  <!-- 等价于 Vue2 
  <cpn
    :modelValue="inpValue"
    @update:modelValue="value = $event"
    :msg="msg"
    @update:msg="msg = $event"
  /> 
  -->
  </div>
</template>
```

透传，\$attrs 、\$listeners ：

```
<script>
// 子组件

export default {
  props: ["v1"],

  mounted() {
    this.$emit("e1");

    // 获取非 props 接收的数据，得到 v2
    console.log(this.$attrs);

    // 获取所有自定义事件，不管有没有 emit ，得到 e1、e2
    console.log(this.$listeners);
  },
};
</script>

<template>
  <div></div>
</template>
```

```
<script>
// 父组件

import cpn from "./cpn.vue";

export default {
  components: { cpn },
};
</script>

<template>
  <div>
    <cpn :v1="1" :v2="2" @e1="console.log('e1')" @e2="console.log('e2')" />
  </div>
</template>
```

（2）非父子组件通信：

依赖注入、祖先 provide 数据，后代组件 inject 注入数据：

```
<script>
// 子组件

export default {
  inject: ["num", "obj"],
};
</script>

<template>
  <div>{{ num }} {{ obj }}</div>
</template>
```

```
<script>
// 父组件

import cpn from "./cpn.vue";

export default {
  components: { cpn },

  data() {
    return {
      num: 123,
      obj: { a: 1 },
    };
  },

  // provide、inject 默认不是响应式的，只有 provide 一个对象或函数形式的数据才有响应式
  provide() {
    return {
      num: () => this.num,
      obj: this.obj,
    };
  },
};
</script>

<template>
  <div>
    <cpn />
  </div>
</template>
```

事件总线，仅 Vue2 可用（Vue3 删除了 \$on 、\$off ，所以无法使用了，可以用第三方库 mitt 代替）：

```
// EventBus.js
import Vue from "vue";
const EventBus = new Vue();
export default EventBus;
```

```
<script>
// 父组件

import EventBus from "./EventBus.js";
import cpn from "./cpn.vue";

export default {
  components: { cpn },

  methods: {
    myEvent(e) {
      console.log(e);
    },
  },

  mounted() {
    EventBus.$on("myEvent", this.myEvent);
  },

  beforeDestroy() {
    EventBus.$off("myEvent", this.myEvent);
  },
};
</script>

<template>
  <div>
    <cpn />
  </div>
</template>
```

```
<script>
// 子组件

import EventBus from './EventBus.js';

export default {};
</script>

<template>
  <div>
    <div @click="EventBus.$emit("myEvent", { a: 1 })">123</div>
  </div>
</template>
```

### 3.2 获取组件实例

也算是组件通信。

只有 mounted 组件挂载完毕后，才能获取：

```
<script>
// 子组件

export default {};
</script>

<template>
  <div>
    <button @click="console.log($parent)">get parent</button>
    <button @click="console.log($root)">get root （new Vue()）</button>
  </div>
</template>
```

```
<script>
// 父组件

import cpn from "./cpn.vue";

export default {
  components: { cpn },

  mounted() {
    // Vue3 已阐述 $children ，但保留 $parent 、$root
    console.log(this.$children);

    // 获取对应 ref 属性的组件实例，若 v-if 隐藏了组件，也可以在 watch 监听 this.$refs.xxx
    console.log(this.$refs.cpn);
  },
};
</script>

<template>
  <div>
    <!-- 
      * ref 和 id 可以同名，不冲突
      * 即使在不同组件中，ref 也不要同名
      * 不要用 - 命名，如 xxx-yyy ，this.$refs.xxxYyy 获取不到
      -->
    <cpn ref="cpn" />
  </div>
</template>
```

### 3.3 组件扩展

（1）逻辑扩展

混入 mixin 、继承 extends ：

```
// mixin.js

export const mixinA = {
  data() {
    return {
      a: 1,
    };
  },
};
```

```
<script>
// 父组件

import { mixinA } from "./mixin.js";

export default {
  /**冲突
   * 非生命周期，不覆盖冲突的，没有的就加入
   * 生命周期，冲突就覆盖
   */
  mixinA: [mixinA],

  // 和 mixin 一样，冲突解决也一样，只不过只能继承一个；若 mixin 、extends 冲突，extends 优先级高
  extends: mixinA,
};
</script>

<template>
  <div>{{ a }}</div>
</template>
```

（2）内容扩展（插槽）

也算是组件通信 。

分为默认插槽、具名插槽、作用域插槽：

```
<script>
// 子组件

export default {};
</script>

<template>
  <div>
    <slot></slot>
    <p>-----------------------------------------------</p>
    <slot name="xxx"></slot>
    <p>-----------------------------------------------</p>
    <slot name="yyy" :msg="'msg'"></slot>
  </div>
</template>
```

```
<script>
// 父组件

import cpn from "./cpn.vue";

export default {
  components: { cpn },

  data() {
    return { slotName: "xxx" },  
  },

  mounted() {
    // 获取未使用的插槽
    console.log(this.$slots);
  },
};
</script>

<template>
  <div>
    <cpn>
      <!-- 方式一，Vue3 删除了 slot 属性，只能用 template 了 -->
      <!-- <p>默认</p> -->
      <!-- <p>默认</p> -->
      <!-- <p slot="xxx">具名</p> -->

      <!-- 方式二，Vue3 中 v-slot: 改为 # -->
      <template v-slot:default>默认</template>
      <template v-slot:xxx>具名</template>
      <template v-slot;yyy="{ msg }">作用域 {{ msg }}</template>

      <!-- 具名插槽可以用动态变量控制 -->
      <template v-slot:[slotName]>具名</template>
    </cpn>
  </div>
</template>
```

### 3.4 插件

Vue3 中不再是用 Vue 构造函数创建 vue ，而是用 createApp 工厂函数创建；Vue 中的各种属性、方法都转移到 app 中：

```
// Vue2
import Vue from "vue";
import App from "./App";
new Vue({
  render: h => h(APP)
}).$mount("#app");

// Vue3
import { createApp } from "vue";
import App from "./App";
createApp(App).mount("#app");
```

（1）全局资源

给全局添加资源：

```
// Vue2，添加到 Vue 原型上
Vue.prototype.xxx = 123;

// Vue3
app.config.globalProperties.xxx = 123;
```

使用；

```
// Vue2 直接用 this 在原型链上找
console.log(this.xxx)

// Vue3
import { getCurrentInstance } from 'vue'
import type { ComponentInternalInstance } from 'vue'
const { appContext } = getCurrentInstance() as ComponentInternalInstance
console.log(appContext.config.globalProperties.xxx)
```

（2）插件

将一个组件注册为插件，在外部使用这个组件的资源，如 loading 。

Vue2 ：

```
import Vue from 'vue'
import Loading from './Loading.vue'

const plugins = [{ name: '$loading', cpn: Loading }]

// main.js 中 Vue.use() 即可
export default {
  install(Vue) {
    for (const item of plugins) {
      const toastConstructor = Vue.extend(item.cpn)
      const DOM = new toastConstructor()

      DOM.$mount(document.createElement('div'))
      document.body.appendChild(DOM.$el)

      Vue.prototype[item.name] = DOM
    }
  },
}
```

Vue3 ：

```
<script setup lang="ts">
// /src/plugin/Loading.vue

import { ref } from 'vue'

const isShow = ref(false)

const expose = {
  show: () => (isShow.value = true),
  hide: () => (isShow.value = false),
}
</script>

<template>
  <div class="box" v-show="isShow">Loading</div>
</template>

<style scoped lang="less">
.box {
  position: absolute;
  z-index: 999;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);
  border: 1px solid #000f;
  width: 200px;
  height: 100px;
  border: 1px solid #000;
  text-align: center;
  line-height: 100px;
}
```

```
// /src/plugin/index.ts

import { createVNode, render } from 'vue'
import type { App } from 'vue'
import Loading from './Loading.vue'

// 所有插件一起注册
const plugins = [{ name: '$loading', cpn: Loading }]

/**两种写法
 * 导出一个 function ，main.ts 中传入 app 执行即可
 * 导出一个 object ，写一个 install 函数，在 main.ts 引入，app.use() 就会自动执行 install 这个对象，这种写法更规范
 */
export default {
  install: (app: App) => {
    for (const item of plugins) {
      // 创建虚拟 DOM，render 成真实 DOM
      const VDOM = createVNode(item.cpn)
      render(VDOM, document.body)

      // 挂到全局，虚拟 DOM 只有 render 后才能获取 component
      app.config.globalProperties[item.name] = VDOM.component!.setupState.expose
    }
  },
}
```

```
// main.ts
// ...
import plugin from './plugin'
// ...

// use 一次即可在任何地方使用，注意 use 必须在 el 挂载之前
app.use(plugin)
```

```
<script setup lang="ts">
// 使用 
import { getCurrentInstance } from 'vue'
import type { ComponentInternalInstance } from 'vue'

const { appContext } = getCurrentInstance() as ComponentInternalInstance
const loading = appContext.config.globalProperties.$loading

loading.show()
</script>

<template></template>
```

## 4 Vue3

从选项式 API（OptionsAPI），替换成组合式 API（CompositionAPI），虽然 Vue3 还是可以用 OptionsAPI ，但不推荐，防止冲突。

### 4.1 setup

Vue3.0 ，使用 defineComponent 是为了得到组件的类型提示，也可以不用；

```
<script lang="ts">
// 子组件

import { inject }, defineComponent from 'vue'

export default defineComponent({
  // 用法不变
  props: ['myValue'],

  // 自定义事件必须这里声明才有效
  emits: ['myEvent'],

  setup(props, context) {
    // 获取 props
    console.log('props', props)

    // 删除了 listeners ，内容转义到 attrs 中
    console.log('context', context.attrs, context.slots)

    // 发射自定义事件
    context.emit('myEvent', 123)

    // 依赖注入，第二个参数为默认值
    const { num, obj } = inject('myData', {})
    console.log('provide-inject', num.value, obj)
  },
})
</script>

<template>
  cpn
  <button></button>
</template>
```

```
<script lang="ts">
// 父组件

// CompositionApi
import {
  ref,
  reactive,
  provide,
  computed,
  onMounted,
  nextTick,
  watch,
  watchEffect,
  toRef,
  toRefs,
  h,
  defineComponent,
} from 'vue'

import type { ComponentPublicInstance } from "vue"
import cpn from './cpn.vue'

export default defineComponent{
  components: { cpn },

  // 自定义指令，指令生命周期和 Vue2 完全不同
  // create beforeMount mounted beforeUpdate updated beforeUnmount unmount
  directives: {
    // 完整写法
    myDir1: {
      mounted(el, dir) {
        console.log('directive 修饰符', dir.modifiers.test)
      },
    },

    // 简写，等价于指令的 mounted、updated
    myDir2(el, dir) {
      el.innerText = el.innerText + ` myDir2: ${dir.value}`
    },
  },

  // setup 相当于 beforeCreate、created 阶段，只执行一次，this 为 undefined
  setup() {
    // 数据 -----------------------------------------------------------------

    /**响应式数据，底层实现是 Proxy
     * ref：定义基本类型，若定义引用类型、底层也会用 reactive；ref 返回一个 ref 对象
     * reactive：定义引用类型；reactive 返回一个 Proxy 对象
     * 只要嵌套有引用类型，都会变成 Proxy 对象
     * 只有需要响应式的数据才需要使用 ref、reactive，提高性能
     * 若取出（如解构赋值） ref、reactive 的值不是引用类型，会失去响应式
     */
    const num = ref<number>(123)
    const arr = ref([1, 2, 3])
    const obj = reactive({ a: 1, deepObj: { deepValue: 2 } })

    // // 失去响应式的例子
    // const d1 = num.value
    // const d2 = obj.a
    // num = 2

    // 取出来是引用类型，还是响应式的
    // const newArr = arr.value

    // 如果重新赋值为响应式数据，则就是另一个数据了
    // 如果是在生命周期中这么做，由于 setup 已经 return 原来的数据了，所以就算是新响应式数据，修改也不起作用，因为两个就不是同一个响应式数据
    // const newObj = reactive({ b: 2 })

    // toRef 可以把引用类型中的基本类型转为 ref 对象，用来解决响应式丢失
    const arrNum = toRef(arr.value[0])

    // 函数、计算属性、wtach ----------------------------------------------------------

    // function
    const showHello = () => 'hello'

    // computed、返回一个 ref 对象
    const sum = computed(() => num.value * 2)

    // 请完整写法 computed
    // const sum = computed({
    //   get: () => num.value,
    //   set: newVal => console.log(newVal),
    // })

    /**watch
     * 监听的是响应式数据，可以使一个数据
     * 若 watch 的不是响应式数据，需要函数形式 () => num.value
     * 也可以用多个数据放在数组中，newVal、oldVal 得到的也是数组
     */
    watch(
      [num, obj],
      (newVal, oldVal) => {
        const [newNum, newObj] = newVal
        const [oldNum, oldObj] = oldVal

        // 引用类型的 oldValue 有 bug ，值和 newValue 一样
        console.log(
          'watch',
          [newNum, oldNum],
          [newObj.deepObj.deepValue, oldObj.deepObj.deepValue],
        )
      },
      {
        // 不一员工的是 Vue3 默认 deep 为 true ，immediate 还是一样默认 false
        // immediate: true,
        // deep: false,
      },
    )

    /**watchEffect
     * 里面 get 的数据会被 track ，所以 trigger 时会回调一次
     * 和 computed 一样，为了最初的 track ，所以最初会执行一次
     */
    watchEffect(() => {
      console.log('vatchEffect', num.value)
    })

    // 获取组件实例、生命周期 -------------------------------------------------------------

    // 组件实例
    const cpnRef = ref<ComponentPublicInstance<typeof cpn> | null>(null)

    /**生命周期
     * 都是 CompositionAPI ，加上 on 前缀
     * 删除了beforeCreate、created （但 OptionsAPI 依然存在这两个，且和 Vue2 不同的是 Vue3 无 el 就不会执行这两个）
     * setup 相当于 beforeCreate、created 这两个阶段
     * 销毁改名：onBeforeUnMpunt、onUnMounted
     * 若同时有 CompositionAPI 和 OptionsAPI 、则 CompositionAPI 先执行，如 setup 在 beforeCreate 之前执行
     */
    onMounted(() => {
      // ref 需要 .value 调用，reactive 不用
      console.log(
        'mounted',
        num.value,
        arr.value[0],
        obj.a,
        sum.value,
        cpnRef.value,
      )

      // 如果不是在生命中期狗子内（生命周期钩子不能 async），可以直接 await nextTick()
      nextTick(() => console.log('nextTick'))
    })

    // 增加了 3 个生命周期
    // renderTracked(() => console.log('track 后执行'))
    // renderTriggered(() => console.log('trigger 后执行'))
    // serverPrefetch(() => console.log('SSR 之前执行'))

    // 依赖注入 --------------------------------------------------------------------
    provide('myData', { num, obj })

    // return -----------------------------------------------------------------------

    // return 后 template 才能使用
    return { num, arr, obj, showHello, sum, cpnRef }

    // 也可以吧所以数据放在一个 reactive 中，用 toRefs 生成各个 ref 对象，更方便
    // return { ...toRefs(obj) }

    // 也可以 return render 函数
    // return () => h('h1', 'render')
  },
})
</script>

<template>
  <p>Vue3 template 不再需要根元素，默认会加上虚拟根元素 Fragments</p>
  <p>ref、reactive 都不用 .value {{ num }} {{ arr }} {{ obj }}</p>
  <p>{{ showHello() }} {{ sum }}</p>

  <div>
    <button @click="++num">add num</button>
    <button @click="++obj.deepObj.deepValue">add deepValue</button>
  </div>

  <p v-my-dir1.test="'value1'" v-my-dir2.test="'value2'">自定义指令</p>

  <cpn ref="cpnRef" :myValue="obj" />
</template>

<style lang="less" scoped></style>
```

Vue3.2 ，script setup 语法糖：

```
<script setup lang="ts">
// 子组件

import { ref } from 'vue'

type propsType = { myValue: number; myArr: Array<number> }

// 这些API 都只能定义一次，其中 defineProps、withDefaults 只能存在一个 -----------------------

// defineProps<propsType>()
withDefaults(defineProps<propsType>(), {
  // 默认值，引用类型要写成函数形式
  myValue: 0,
  myArr: () => [],
})

const emit = defineEmits(['myEvent'])

// script setup 中，必须 expose 才能让父组件获取子组件实例，expose 也可以实现子传父
// expose 的资源会自动去掉响应式，修改还是要 emit
const divRef = ref<HTMLElement | null>(null)
const sonValue = ref('sonValue')
defineExpose({ divRef, sonValue })
</script>

<template>
  <div ref="divRef">子组件</div>
  <p>cpn {{ myValue }} {{ myArr }} {{ sonValue }}</p>
  <button @click="emit('myEvent', { msg: 'is myEvent' })">emit event</button>
</template>

<style lang="less" scoped></style>
```

```
<script setup lang="ts">
// 父组件

/**script setup
 * 子组件不再需要注册，会自动注册
 * 不再需要 return ，template 就可以使用资源
 * 若 script setup 顶层使用了 await ，setup 会自动变成 async
 * 若像定义组件 name、beforeRouterEnter ，可以多谢一个 OptionsAPI 的 script ；也可以用 vite 插件，直接写成 <script setup name="xxx">
 */

import cpn from './cpn.vue'
import { ref, reactive, onMounted } from 'vue'
import type { 
  Directive, 
  DirectiveBinding, 
  ComponentPublicInstance 
} from 'vue'

const num = ref(123)
const arr = reactive([1, 2])

const cpnRef = ref<ComponentPublicInstance<typeof cpn> | null>(null)

onMounted(() => {
  console.log(cpnRef.value!.divRef, cpnRef.value!.sonValue)
})

// 自定义指令，必须加上 v 前缀
const vMyDir: Directive = {
  mounted(el: HTMLElement, dir: DirectiveBinding) {
    el.innerText = `自定义指令 ${dir.value}`
  },
}
</script>

<template>
  <cpn
    ref="cpnRef"
    :myValue="num"
    :myArr="arr"
    @myEvent="console.log($event)"
  />

  <p v-myDir="'dir'"></p>
</template>

<style lang="less" scoped></style>
```

```
// CustomDirective.ts

// 全局自定义指令，main.ts 中引入，传入 app 执行即可
import type { DirectiveBinding } from 'vue'

export function authBtn(app: any) {
  app.directive('AuthBtn', {
    mounted(el: HTMLElement, dir: DirectiveBinding) {
      console.log('mounted', dir.value)
    },
  })
```

script setup 编译后，得到 setup 函数：

- 编译时根据 defineProps 等这些宏生成 props、emits、expose 配置项

- import 的子组件，自动生成 components 配置项

关于 expose ：

```
<script lang="ts">
import { ref } from "vue";

export default {
  /**expose
   * 若不写则默认在父组件可以获取子组件 setup return 的所有资源和子组件实例
   * 加了 expose 就只能获取 expose 中声明的资源，子组件实例也需要声明才能获取
   * script setup 编译后则会默认加上 expose 
     - 所以才需要 defineExpose 暴漏资源，父组件才能使用
     - 这是为了谨慎，保证单项数据流，实在需要使用就自己 defineExpose 暴漏使用
   */
  expose: ["a"],
  setup(props, context) {
    const a = ref(123);

    // 也可以这样使用 expose
    // context.expose({ a });

    return { a };
  },
};
</script>

<template>cpn</template>
```

```
<script setup lang="ts">
import { ref, onMounted } from "vue";
import type { ComponentPublicInstance } from "vue";
import cpn from "./cpn.vue";

const r = ref<ComponentPublicInstance<typeof cpn> | null>(null);
onMounted(() => {
  console.log(r.value.a);
});
</script>

<template>
  <cpn ref="r" />
</template>
```

script setup 配置组件的 name ，需要借助插件：

```
npm install -D vite-plugin-vue-setup-extend
```

```
// vite.config.ts
// ...
import vueSetupExtend from "vite-plugin-vue-setup-extend";

export default defineConfig({
  plugins: [vue(), vueSetupExtend()],
});
```

```
<script setup lang="ts" name="home"></script>
```

### 4.2 hook

即 CompositionAPI ，参考了 React Hook ，一种新的组件扩展方式：

- 可以封装 setup 中用到的任何资源，代码组织更清晰，使得同一个功能的 data、methods、生命周期等封装到一起，而不是 Vue2 OptionsAPI 分散开

- 类似 mixin ，但比 mixin 更强大。hook 互相独立，也不会冲突

- hook 本身是一个 function ，命名规范是加上 use 前缀，常用的第三方 hook 如 vueuse

（1）自定义 hook

若 hook 内有生命周期、外部也有，则按照代码顺序执行：

```
// CustomHook.ts

import { ref, onMounted } from 'vue'

export const useMyHook = (testValue: number) => {
  const myValue = ref(testValue)

  onMounted(() => console.log('hook', myValue.value))

  return myValue
}
```

```
<script setup lang="ts">
import { onMounted } from 'vue'
import { useMyHook } from './CustomHook.ts'

// onMounted(() => console.log('component'))

const myValue = useMyHook(123)

onMounted(() => console.log(myValue.value))
</script>

<template>{{ myValue }}</template>
```

（2）常用 Vue Hook

响应式处理：

```
<script setup lang="ts">
import {
  shallowRef,
  shallowReactive,
  readonly,
  shallowReadonly,
  toRaw,
  markRaw,
  customRef,
} from 'vue'

// 只处理基本类型，引用类型不再用 reactive 做响应式
const d1 = shallowRef([1, 2, 3])

// 只处理引用类型第一层的响应式
const d2 = shallowReactive({ a: 1, obj: { b: 2 } })

/**只读
 * 接收 ref、reactive 数据，变成只读，都是返回 proxy 对象
 * 与非响应式数据区别是，这两个是 Vue 能监听到的，只是不允许修改而已
 * 若修改了原始响应式数据，readonly 也会被修改，因为是浅拷贝
 * 常用于 hook 中导出不允许外部修改的数据
 * shallowReadonly 只处理第一仓
 */
const d3 = readonly(d1)
const d4 = shallowReadonly(d1)

// 将reactive 还原成原始数据（ref 对象无法还原）
const d5 = toRaw(d2)

/**
 * 标记一个原始对象，使其无法用 ref、reactive 变成响应式数据
 * 常用于响应式对象添加某个成员，而这个成员不需要响应式（如第三方数据），就可以 mark 以下，提高性能
 */
const rawObj = { a: 1 }
const d6 = markRaw(rawObj)

// 自定义 ref ，在 track、trigger 时可以自定义一饿处理逻辑，如实现一个防抖的响应式数据
const myRef = (value: string, delay: numebr = 1000) => {
  let timer: number | undefined = undefined

  return customRef((track, trigger) => {
    return {
      get() {
        track()
        return value
      },
      set(newVal) {
        clearTimeout(timer)
        timer = setTimeout(() => {
          value = newVal
          trigger()
        }, delay)
      },
    }
  })
}

const inpValue = myRef('hello')
</script>

<template>
  <div>
    <input type="text" v-model="inpValue" />
    <span>{{ inpValue }}</span>
  </div>
</template>
```

判断是否是响应式数据：

```
<script setup lang="ts">
import {
  ref,
  reactive,
  readonly,
  isRef,
  isReactive,
  isReadonly,
  isProxy,
} from 'vue'

const num = ref(123)
const obj1 = ref({ a: 1 })
const obj2 = reactive({ b: 2 })
const obj3 = readonly({ c: 3 })

// true true false
console.log(isRef(num), isRef(obj1), isRef(obj1.value))

// true true false
console.log(isReactive(obj1.value), isReactive(obj2), isReactive(obj3))

// true
console.log(isReadonly(obj3))

// true true true
console.log(isProxy(obj1.value), isProxy(obj2), isProxy(obj3))
</script>

<template></template>
```

### 4.3 特殊组件

（1）全局组件

```
// main.ts
createApp(App).component(cpn).mount('#app')
```

（1）递归组件

当 v-for 渲染有递归结构的数据时，需要使用多个 v-for ，比较麻烦，可以用递归组件解决：

```
<script setup lang="ts">
// 父组件

import { reactive } from 'vue'
import cpn from './cpn.vue'

interface DataType {
  id: string
  value: string
  children?: Array<DataType>
}

const data = reactive<Array<DataType>>([
  {
    id: '1',
    value: '1',
    children: [
      { id: '1-1', value: '1-1' },
      { id: '1-2', value: '1-2' },
    ],
  },
  { id: '2', value: '2', children: [{ id: '2-1', value: '2-1' }] },
])
</script>

<template>
  <cpn :data="data" />
</template>

<style lang="less" scoped></style>
```

```
<script setup lang="ts">
// 子组件

// 方式一，子组件自引入
import myself from './cpn.vue'

interface DataType {
  id: string
  value: string
  children?: Array<DataType>
}

interface PropsType {
  data: Array<DataType>
}

defineProps<PropsType>()
</script>

<!-- 方式二、子组件起一个 name -->
<script lang="ts">
export default {
  name: 'cpnName',
}
</script>

<template>
  <ul>
    <li v-for="i in data" :key="i.id">
      <span>{{ i.value }}</span>
      <ul v-if="i.children?.length! > 0">
        <myself :data="i.children" />
        <!-- <cpnName :data="i.children" /> -->
      </ul>
    </li>
  </ul>
</template>
```

（2）动态组件

可以用变量动态渲染组件；

```
<script setup lang="ts">
import { ref } from 'vue'
const flag = ref(true)
</script>

<template>
  <button @click="flag = !flag">switch</button>
  <component :is="flag ? 'div' : 'h1'">123</component>
</template>
```

（3）异步组件、分包

由于子组件 mounted 后父组件才会 mounted ，所以当子组件渲染时间过长时会影响父组件的渲染时间。异步的子组件就可以先让父组件 mounted ，子组件再异步渲染。

组件中 setup 用 async 修饰就会变成异步组件，可以 return Promise；script setup 中顶层使用 await ，setup 就会自动加上 async 。

```
<script setup lang="ts">
// 子组件

import { onMounted } from 'vue'

onMounted(() => console.log('子组件'))

const delayRender = new Promise(resolve => setTimeout(() => resolve(), 2000))
await delayRender
</script>

<template>cpn</template>
```

```
<script setup lang="ts">
// 父组件

import { defineAsyncComponent, onMounted } from 'vue'

// 异步组件需要异步引入
const cpn = defineAsyncComponent(() => import('./cpn.vue'))

onMounted(() => console.log('父组件'))
</script>

<template>
  <!-- 一步组件必须放在 Suspense 中 -->
  <Suspense>
    <template #default><cpn /></template>
    <template #fallback><h1>loading</h1></template>
  </Suspense>
</template>
```

分包：

每个异步组件在 build 时会生成一个独立的包，类似路由懒加载，可以提高页面性能。

（4）缓存组件

路由的 keep-alive 可以用在普通组件了，使用 keep-alive 后组件不会被删除、也可以使用路由生命周期 actived、deactived、但无法使用组件内守卫：

```
<script setup lang="ts">
// 子组件

// 缓存后不会走 onBeforeUnMount、 unUnMounted
import { onMounted, onActivated, onDeactivated } from 'vue'

onMounted(() => console.log('mounted'))
onActivated(() => console.log('actived'))
onDeactivated(() => console.log('deactived'))
</script>

<script lang="ts">
export default {
  // 无法使用
  beforeRouteEnter() {
    console.log('beforeRouteEnter')
  },
}
</script>

<template>cpn</template>
```

```
<script setup lang="ts">
// 父组件

import { ref } from 'vue'
import cpn from './cpn.vue'

const isShow = ref(true)
</script>

<template>
  <button @click="isShow = !isShow">click</button>
  <keep-alive>
    <cpn v-if="isShow" />
  </keep-alive>
</template>
```

（5）新内置组件

Fragments：在 template 中会自动加上这个虚拟节点、所以才不需要根元素

Teleport ：

将元素传送到 CSS 选择器选中的位置，Teleport 的父元素若使用 v-show ，则对 Teleport 里面的元素无效，因为父元素变了；若父元素使用 v-if 则有效，因为只有元素创建了才能传送。

to 是传送后的父元素，注意 CSS 中父元素也是 to 指定的元素：

```
<script setup lang="ts">
import { ref } from 'vue'
const isShow = ref(true)
</script>

<template>
  <button @click="isShow = !isShow">click</button>
  <div class="box" v-show="isShow">
    <Teleport to="body">
      <div class="loading">loading</div>
    </Teleport>
  </div>
</template>

<style lang="less" scoped>
.box {
  position: relative;
  border: 1px solid #000;
  width: 100px;
  height: 100px;
  background-color: #000;

  // 无效，因为父元素不是 .box
  // .loading {}
}

.loading {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
  border: 1px solid red;
  width: 100px;
  height: 50px;
  background-color: red;
  color: #fff;
  line-height: 50px;
  text-align: center;
}
</style>
```

### 4.4 其他

（1）style

style v-bind ：

```
<script setup lang="ts">
import { ref, reactive } from 'vue'

// 根据需求，看是否需要响应式
const size = '50px'
const border = ref('1px solid #000')
const center = reactive({
  a: 'center',
})
</script>

<template>
  <div class="box">123</div>
</template>

<style scoped lang="less">
.box {
  font-size: v-bind('size');
  border: v-bind('border');
  text-align: v-bind('center.a');
}
</style>
```

css module ：

```
<script setup lang="ts">
import { useCssModule } from 'vue'

const cssModule = useCssModule()
const m1 = useCssModule('m1')

console.log(cssModule, m1)
</script>

<template>
  <div :class="$style.a">默认 module</div>
  <div :class="[m1.b, m1.c]">m1</div>
</template>

<style module scoped lang="less">
.a {
  width: 100px;
  height: 100px;
  border: 1px solid #000;
}
</style>

<style module="m1" scoped lang="less">
.b {
  width: 50px;
}
.c {
  height: 50px;
  border: 10px solid #000;
}
</style>
```

新选择器：

```
<script setup lang="ts"></script>

<template></template>

<style scoped lang="less">
//  样式穿透，即 Vue2 的 /deep/
:deep(.el-input__inner) {
}

// 插槽选择器，可以设置插槽的样式了
:slotted(.box) {
}

// 忽略 scoped 的效果
:global(.box) {
}
</style>
```

（2）新指令

v-memo ，缓存指令，类似计算属性，只有 v-memo 依赖的数据修改时，才会中心渲染：

```
<script setup lang="ts">
import { ref } from 'vue'

const num = ref(123)
const msg = ref('msg')
</script>

<template>
  <!-- 如果是空数组、就等价于 v-once -->
  <p v-memo="[num, msg]">v-memo</p>

  <ul>
    <!-- v-for 内不能使用 v-memo，只能和 v-for 放在一个元素中 -->
    <li v-for="i in 3" v-memo="num" :key="i">1</li>
  </ul>
</template>
```

（3）Vue 2.7

Vue2 的最后一个版本，已经可以使用 Vue3 特性，2.7 版本主要是为了老项目的迁移过渡。

## 5 Vue 原理

### 5.1 响应式

响应式，即数据修改，依赖该数据的函数重新执行，这些函数包括 render、computed、watch、watchEffect 。

Vue2，使用 Object\.defineProperty 实现：

* 先用 Object\.defineProperty 把 data 第一层代理到 this ，方便以后直接用 this 访问数据，不需要递归

* 再用 Object\.defineProperty 递归对每一个属性设置 get、set ，每个属性维护一个 Dep 对象、Dep 对象用发布\-订阅模式进行依赖收集、派发更新，每隔一依赖是一个 Watcher 对象，每一个 Watcher 对象封装有响应式的函数
  
  * 依赖收集：响应式的函数不直接执行，而是交给 Watcher 处理，Watcher 先把函数挂到全局可获取的位置（如 Dep 静态属性），再执行函数，执行函数触发函数内响应式数据的 get ，get 中即可获取挂到全局位置中的依赖
  
  * 派发更新时，会用调度器处理，调度器会把多次重复的更新过滤掉，只保留一个更新，同时会把更新放到异步队列中，所以在 Vue 开发中才需要 nextTick 拿到最新 DOM

* Object\.defineProperty 只能拦截 value 的访问和修改，无法拦截属性的增加、删除；Set、Map 等操作也无法拦截；数组下标虽然也可以拦截，但是一旦数组长度发生变化，下标和响应式的对应关系就会d打乱，push 等方法也无法拦截。
  
  * 每个引用类型的 value 增加一个 "\_\_ob\_\_" 的 key ，value 为 Observer 对象，里面维护一个 Dep 对象，这样只需要自己实现 \$set、\$delete 函数派发更新即可
  
  * 数组的 push 等函数，在 Array 原型链中插入一个自定义原型，里面重写这些函数，并派发更新

* 不同 watcher 的处理
  
  * watch 只需要 get 以下 watch 的数据即可，所以默认 watch 第一次不会执行；而 render、computed、watchEffect 里有多个响应式数据，所以必须在第一次执行一次才能收集到依赖
  
  * computed 是惰性（lazy）的，只有在用到时才进行依赖收集；只有 computed 依赖的数据修改了，computed 变为脏数据（dirty），computed 才会重新执行，数据没修改则使用缓存 value

简单实现：

```
// type ------------------------------------------------------------------------------------
interface Options {
  [key: string]: any;
}

interface VueOptions {
  el: string;
  data?: Options;
  watch?: { [key: string]: Function };
  computed?: { [key: string]: Function };
  render?: Function;
}

interface WatcherOptions {
  lazy?: boolean;
}
// --------------------------------------------------------------------------------------------

// tool ----------------------------------------------------------------------------------------
// 判断是否为引用类型，为了简单目前只处理 Object 和 Array
const isPointer = (data: any): boolean => {
  return ["[object Object]", "[object Array]"].includes(
    Object.prototype.toString.call(data)
  );
};

// 响应式处理
const defineReactive = (target: Options, key: string) => {
  // 闭包数据
  let value = target[key];
  const dep = new Dep();

  // 递归
  let childOb = observe(value);

  Object.defineProperty(target, key, {
    get: () => {
      dep.depend();
      (childOb as Observer)?.dep?.depend();
      return value;
    },

    set: (newValue) => {
      value = newValue;
      // 如果 newValue 时引用类型，则需要 observe
      childOb = observe(value);

      // 派发更新
      dep.noticy();
      (childOb as Observer)?.dep?.noticy();
    },
  });
};

// Vue 源码会根据环境是否支持，选择使用微任务、宏任务，这里为了方便直接用微任务
const nextTick = (callback: Function): void => {
  Promise.resolve().then(() => callback());
};

// 响应式处理的入口
const observe = (data: unknown): Observer | void => {
  if (!isPointer(data)) return;
  return data!["__ob__"] ?? new Observer(data as Options);
};

/*数组响应式*
 * Object.defineProperty 可以定义数组下标的 get、set ，但是一旦数组长度改变，下标和响应式的关系就会改变
 * 所以数组下标响应式用 Vue.$set() 实现，同 "__ob__" 的 dep 派发更新
 * push 等方法用自定义原型实现，在里面重写方法，同 "__ob__" 的 dep 派发更新
 */
const observeArray = (arr: Array<any>): void => {
  for (const value of arr) observe(value);
};

// 自定义要插入 Array 原型链中间的原型
const ArrayMethods = (() => {
  const result = Object.create(Array.prototype);

  const methods = [
    "push",
    "pop",
    "shift",
    "unshift",
    "splice",
    "sort",
    "reverse",
  ];

  for (const methodName of methods) {
    result[methodName] = function () {
      console.log(methodName);

      let inserted = Array.from(arguments);
      switch (methodName) {
        case "push":
        case "unshift":
          observeArray(inserted);
          break;
        case "splice":
          for (let i = 2; i < inserted.length; i++) observe(inserted[i]);
          break;
        default:
          break;
      }

      const arrRes = Array.prototype[methodName].apply(this, inserted);
      this["__ob__"].dep.noticy();

      return arrRes;
    };
  }

  return result;
})();
// --------------------------------------------------------------------------------------------

// class -----------------------------------------------------------------------------------------
/**
 * 每一个 watcher 就是一个依赖，有 watch、computed、render、watchEffect
 * computed 是惰性的，只有调用时才会计算；computed 会缓存
 * computed 会用在其他 computed、或 render、watch、watchEffect，所以需要创建 Dep、Watcher 多对多
   的关系，Dep 收集到 computed 的各个 Watcher 后，这些 Watcher 再让这些 Dep 区收集其他 Watcher
 */
let watcherId = 0;
class Watcher {
  public static asyncWatcherIds = new Set();

  // 有这个 watcher 的 Dep
  public deps: Set<Dep> | null = null;

  public value: any;
  public lazy: boolean;
  public dirty: boolean;

  private id: number;
  private vm: Vue;
  private exp: string | Function;
  private callback: Function;
  private getter: Function;

  constructor(
    vm: Vue,
    exp: string | Function,
    callback?: Function,
    options: WatcherOptions = {}
  ) {
    this.deps = new Set();

    this.id = watcherId++;
    this.vm = vm;
    this.exp = exp;

    this.getter = typeof exp === "string" ? this.parseExp(vm, exp) : exp;
    this.callback = typeof exp === "string" ? callback : exp;

    this.dirty = this.lazy = !!options.lazy;

    // computed 是 lazy 的
    if (!this.lazy) this.get();
  }

  // 收集 Dep，在 Dep 类中调用
  public addDep(dep: Dep) {
    this.deps.add(dep);
    dep.addSub(this);
  }

  // 如 watch "person.name"
  private parseExp(obj: Vue, exp: string) {
    const childs = exp.split(".");

    return () => {
      let value: any = obj;

      for (const key of childs) {
        try {
          value = value[key];
        } catch {
          throw new Error(`不能从 undefined 访问 ${key}`);
        }
      }
      return value;
    };
  }

  public get() {
    Dep.target = this;
    Dep.targetStack.push(this);

    this.value = this.getter.call(this.vm);

    Dep.targetStack.pop();
    Dep.target =
      Dep.targetStack.length > 0
        ? Dep.targetStack[Dep.targetStack.length - 1]
        : null;
  }

  /**一步更新
   * 用 nextTick 变成异步任务
   * 若有多次更新，则只执行一次即可
   */
  private run() {
    if (!Watcher.asyncWatcherIds.has(this.id)) {
      Watcher.asyncWatcherIds.add(this.id);
      nextTick(() => {
        this.get();
        this.callback.call(this.vm);
        Watcher.asyncWatcherIds.delete(this.id);
      });
    }
  }

  public update() {
    // computed 在 update 时只设置 dirty 为 true ，computed 的 update 由代理实现
    if (this.lazy) this.dirty = true;
    else this.run();
  }
}

// 发布-订阅模式，用于依赖收集、派发更新
class Dep {
  // 当前触发的依赖，全局可用
  public static target: Watcher | null = null;
  // 处理同时收集多个 watcher 的场景
  public static targetStack: Array<Watcher> = [];

  // 依赖
  private subs: Set<Watcher> | null = null;

  constructor() {
    this.subs = new Set<Watcher>();
  }

  // 在 Watcher 类中调用
  public addSub(watcher: Watcher) {
    this.subs?.add(watcher);
  }

  // 依赖收集
  public depend() {
    if (Dep.target) Dep.target.addDep(this);
  }

  // 派发更新
  public noticy() {
    if (!this.subs) return;

    for (const watcher of this.subs) watcher.update();
  }
}

// 响应式
class Observer {
  public dep: Dep | null = null;

  constructor(data: Options) {
    // "__ob__" 不可枚举
    Object.defineProperty(data, "__ob__", {
      value: this,
      enumerable: false,
    });

    // 给 "__ob__" 添加 dep ，处理增加、删除属性的响应式
    this.dep = new Dep();

    if (Array.isArray(data)) {
      Object.setPrototypeOf(data, ArrayMethods);
      observeArray(data);
    } else this.walk(data);
  }

  private walk(data: Options) {
    const keys = Object.keys(data);
    for (const key of keys) defineReactive(data, key);
  }
}

class Vue {
  private _data: Options | null = null;
  [key: string]: any;

  constructor(options: VueOptions) {
    this.initData(options.data);
    this.initComputed(options.computed);
    this.initWatch(options.watch);

    if (options.render) new Watcher(this, options.render);
  }

  private initData(data?: Options) {
    if (!data) return;

    // 数据代理，使得可以直接用 this 调用数据
    this._data = data;
    const keys = Object.keys(this._data);
    for (const key of keys) {
      Object.defineProperty(this, key, {
        get: () => this._data![key],
        set: (newValue) => (this._data![key] = newValue),
      });
    }

    // 开始响应式处理
    observe(this._data);
  }

  private initComputed(computed: { [key: string]: Function }) {
    if (!computed) return;

    const keys = Object.keys(computed);
    for (const key of keys) {
      const watcher = new Watcher(this, computed[key], undefined, {
        lazy: true,
      });

      // computed 也做数据代理，方便 this 调用，也不用加括号了
      Object.defineProperty(this, key, {
        get: () => {
          // 只有 computed 依赖的数据修改了，才更新 computed，否则使用缓存
          if (watcher.dirty) {
            watcher.get();
            watcher.dirty = false;
          }

          if (Dep.target) {
            for (const dep of watcher.deps) dep.depend();
          }

          return watcher.value;
        },

        // computed 的 set 不允许修改自己，只能做其他事
        set: () => {},
      });
    }
  }

  private initWatch(watch: { [key: string]: Function }) {
    if (!watch) return;

    const keys = Object.keys(watch);
    for (const key of keys) new Watcher(this, key, watch[key]);
  }

  public static $set(target: Observer, key: string, value: any) {
    if (!target["__ob__"]) return;

    target[key] = value;
    defineReactive(target, key);
    target["__ob__"].dep.noticy();
  }

  public static $delete(target: Observer, key: string) {
    if (!target["__ob__"]) return;

    delete target[key];
    target["__ob__"].dep.noticy();
  }
}
// --------------------------------------------------------------------------------------------

const vm = new Vue({
  el: "#app",
  data: {
    a: 123,
    person: { name: "asdf" },
    item: [
      { id: 0, name: "a" },
      { id: 0, name: "b" },
    ],
  },

  computed: {
    xxx() {
      console.log("computed 1");
      return `${this.a} ${this.person.name}`;
    },
  },

  watch: {
    xxx() {
      console.log("watch");
    },
  },

  render() {
    // this.a = 1;
  },
});
```

Vue3 的响应式：

ref 用 Object\.defineProperty 实现，reactive 用 Proxy 实现（ref 处理引用类型时，底层会使用 reactive）：

* Proxy 可以拦截所有的对象基本操作（包括增加、删除属性、数组 push 等，Set、Map 等操作）：

* Proxy 的性能更高：
  
  * 同一个嵌套数据，Object\.defineProperty 会递归每一个属性，而 Proxy 虽然也会递归，但处理引用类型就够了，只不过 Proxy 在开始时容易出现响应式丢失，如取出 Proxy 对象中的基本类型属性，可以用 toRef 解决4
  
  * Vue3 可以根据需要定义响应式数据，不想 Vue2 全部放在 data 中；reactive的递归是 lazy 的，只有用到了某个深度的属性，才会处理这个深度的响应式

Vue3 底层会用 Reflect 代替 Object 的操作，这里只是简单实现：

```
// 判断是否是引用类型
const isPointer = (value) => {
  return ["[object Object]", "[object Array]"].includes(
    Object.prototype.toString.call(value)
  );
};

// Proxy 配置项
const proxyHandler = {
  /**参数
   * target：调用 get 的那个对象/数组
   * property：key
   * receiver：整个 proxy 对象
   */
  // 对象调用、数组下标访问
  get: (target, property, receiver) => {
    console.log(`get ${String(property)}`);
    return target[property];
  },

  // set 时回调，第 3 个参数变成 newValue
  // 修改、添加 key
  set: (target, property, newValue) => {
    console.log(`set ${String(property)}`, newValue);

    // 新数据需要再做一次响应式
    target[property] = toProxy(newValue);

    return true;
  },

  // delete 时回调，只有 2 个参数
  deleteProperty: (target, property) => {
    console.log(`delete ${String(property)}`);
    delete target[property];
    return true;
  },
};

const toProxy = (data) => {
  // 判断 proxy 对象时会报错，刚好用来规避已经是 proxy 的对象不再做响应式
  try {
    if (!isPointer(data)) return data;
  } catch {
    return data;
  }

  let proxyData = Array.isArray(data) ? [] : {};

  // 递归
  for (const key in data) proxyData[key] = toProxy(data[key]);

  // 先递归再 new Proxy 是为了防止递归时触发设置好的 get、set ，同时顺便深拷贝原始数据
  proxyData = new Proxy(proxyData, proxyHandler);

  return proxyData;
};

const obj = { a: 1, item: [0, { b: 2 }, { c: 3 }], deepObj: { d: 4 } };

const proxyData = toProxy(obj);

proxyData.deepObj.d = 555;
proxyData.deepObj.dd = 555;
delete proxyData.deepObj.dd;
```

### 5.2 虚拟 DOM、diff 算法

template 的本质是 render 函数的语法糖，template 最终会编译为 render 函数。render 是一个 Watcher ，每次数据更新都再次 render 。

如果 render 函数直接生成真实 DOM ，性能会很低，所以 render 函数只生成虚拟 DOM （Virtual DOM，VDOM），和上次更新的 VDOM 比较，找到变化的部分，进行最小量更新：

- 框架的性能永远比不上原生 JS ，VDOM 只是因为 render 直接渲染真实 DOM 性能低才出现的

- VDOM 还可以实现跨平台，根据平台生成对应的真实 DOM

过程：

* Vue 吃石化时，模板编译得到 render （若写了 render 则直接用 render）

* 把 reder 放到 Watch 中，每次数据更新就会重新执行 render 

* 比较新旧 VNode ，为了提高性能以及结合实际应用场景，只会比较同一层级，若 tag 和 key 相同则是同一个节点

* 相同节点根据 child 的类型进行更新，若新旧 child 等候室子节点数组，则用 diff 算法比较，找到 tag 和 key 相同的节点，相同就只移动和 patch，新增新节点，删除旧节点

代码，Vue 的 VDOM 和 diff 基于第三方库 snabbdom ：

```
class VNode {
  public diffFlag = false;

  constructor(
    public tag: string,
    public attr: { [key: string]: any },
    public child: string | Array<VNode>,
    public elm?: Element,
  ) {}
}

// ----------------------------------------------------------------------------------------------
// to VDOM
const h = (
  tag: string,
  attr: { [key: string]: any },
  child: string | Array<VNode>,
) => new VNode(tag, attr, child);

// VODM to DOM
const createElement = (vnode: VNode): Element => {
  const elm = document.createElement(vnode.tag);
  vnode.elm = elm;

  if (typeof vnode.child === "string") elm.innerText = vnode.child;
  else for (const child of vnode.child) elm.append(createElement(child));

  return elm;
};
// ----------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------
const isSameNode = (oldNode: VNode, newNode: VNode): boolean => {
  return oldNode.tag === newNode.tag && oldNode.attr.key === newNode.attr.key;
};

/**Vue2 diff
 * 使用双端指针，按照 os-ns，oe-ne，os-ne，oe-ns 4 中策略依次找到相同节点，patch，其中后 2 个策略需要 move
 * 若 4 种策略都找不到，则遍历 oldChild 寻找（可用 map 缓存）：
   - 若找到，则 move，patch，并标记为已处理
   - 若找不到，则新增
 * 最后根据双端指针的位置，新增、删除节点
 */
const diff_Vue2 = (oldChild: Array<VNode>, newChild: Array<VNode>): void => {
  let oldStart = 0;
  let newStart = 0;
  let oldEnd = oldChild.length - 1;
  let newEnd = newChild.length - 1;

  const parent = oldChild[0].elm!.parentNode as Element;

  const keyToOldIndexMap: Map<string, number> = new Map();

  // 4 种策略依次对比对比
  while (oldStart <= oldEnd && newStart <= newEnd) {
    // 跳过
    if (oldChild[oldStart].diffFlag) {
      ++oldStart;
      continue;
    } else if (oldChild[oldEnd].diffFlag) {
      --oldEnd;
      continue;
    }

    // 4 种策略
    if (isSameNode(oldChild[oldStart], newChild[newStart])) {
      patchVNode(oldChild[oldStart++], newChild[newStart++]);
      continue;
    } else if (isSameNode(oldChild[oldEnd], newChild[newEnd])) {
      patchVNode(oldChild[oldEnd--], newChild[newEnd--]);
      continue;
    } else if (isSameNode(oldChild[oldStart], newChild[newEnd])) {
      // 移动
      parent.insertBefore(
        oldChild[oldStart].elm!,
        oldChild[oldEnd].elm!.nextSibling,
      );

      patchVNode(oldChild[oldStart++], newChild[newEnd--]);
      continue;
    } else if (isSameNode(oldChild[oldEnd], newChild[newStart])) {
      // 移动
      parent.insertBefore(oldChild[oldEnd].elm!, oldChild[oldStart].elm!);

      patchVNode(oldChild[oldEnd--], newChild[newStart++]);
      continue;
    }
    // 若 4 种策略都没有找到相同节点，则需再次遍历一次 oldChild 未处理节点
    else {
      // 用 map 缓存起来，以后就能快速查询
      if (keyToOldIndexMap.size === 0) {
        for (let oldIndex = oldStart; oldIndex <= oldEnd; oldIndex++) {
          keyToOldIndexMap.set(oldChild[oldIndex].attr.key || "", oldIndex);
        }
      }

      const oldIndex = keyToOldIndexMap.get(newChild[newStart].attr.key);

      if (
        oldIndex !== undefined &&
        isSameNode(oldChild[oldIndex], newChild[newStart])
      ) {
        oldChild[oldIndex].diffFlag = true;
        parent.insertBefore(oldChild[oldIndex].elm!, oldChild[oldStart].elm!);
        patchVNode(oldChild[oldIndex], newChild[newStart]);
      }
      // 如果没找到，说明是新的节点
      else {
        parent.insertBefore(
          createElement(newChild[newStart]),
          oldChild[oldStart].elm!,
        );
      }

      ++newStart;
    }
  }

  /**收尾
   * 如果 oldNode 先遍历完，说明 newNode 有需要新增的节点
   * 如果 newNode 先遍历完，说明 oldNode 有需要删除的节点
   * 如果同时遍历完，就不需要处理
   */
  if (oldStart > oldEnd && newStart <= newEnd) {
    const before = oldChild[oldEnd].elm!.nextSibling
      ? oldChild[oldStart].elm!
      : null;

    for (let i = newStart; i <= newEnd; i++) {
      parent.insertBefore(createElement(newChild[i]), before);
    }
  } else if (oldStart <= oldEnd && newStart > newEnd) {
    for (let i = oldStart; i <= oldEnd; i++) {
      if (!oldChild[i].diffFlag) parent.removeChild(oldChild[i].elm!);
    }
  }
};

// 最长递增子序列
function longestIncreasingSubsequence(nums: number[]): number[] {
  if (nums.length === 0) return [];

  // res 存储 index ，pre 存储前驱 index
  const res: number[] = [];
  const pre: number[] = new Array(nums.length).fill(-1);

  // 这里只处理 >= 0 的数字
  let start = 0;
  for (start = 0; start < nums.length; start++) {
    if (nums[start] >= 0) {
      res[0] = start;
      break;
    }
  }

  // 开始
  for (let i = start + 1; i < nums.length; i++) {
    if (nums[i] < 0) continue;

    const resLastIndex = res[res.length - 1];

    if (nums[i] > nums[res[resLastIndex]]) {
      res.push(i);
      pre[i] = res[resLastIndex];
    }
    // 否则就用二分，找到第一个大于 nums[i] 的数字，用谈心思想，替换得到当前最优解
    else {
      let left: number = 0;
      let right = resLastIndex;
      let mid = Math.floor((left + right) / 2);

      for (; left < right; mid = Math.floor((left + right) / 2)) {
        if (nums[res[mid]] < nums[i]) left = mid + 1;
        else right = mid;
      }

      res[left] = i;
      if (left > 0) pre[i] = res[left - 1];
    }
  }

  // 反向检查
  for (let i = res.length - 1; i > 0; i--) res[i - 1] = pre[res[i]];

  return res;
}

/**Vue3 diff
 * 先用双端指针找到两边相同节点，patch
 * 若上一步结束后，仅有新增、删除节点，直接新增、删除，结束 diff
 * 若 old、new 都还有节点：
   - 删除 new 没有的节点
   - 找出最长递增子序列 sub ，sub 中的节点相对位置在 new 中是不变的，不需要移动，只需要 patch ；
     move，patch 不再 sub 的节点，新增 old 没有的节点
 */
const quickDiff_Vue3 = (
  oldChild: Array<VNode>,
  newChild: Array<VNode>,
): void => {
  let i = 0;
  let oldEnd = oldChild.length - 1;
  let newEnd = newChild.length - 1;

  // 双端指针先找到前后不需要移动的节点
  while (i <= oldEnd && i <= newEnd) {
    if (isSameNode(oldChild[i], newChild[i])) {
      patchVNode(oldChild[i], newChild[i]);
      ++i;
    } else break;
  }
  while (i <= oldEnd && i <= newEnd) {
    if (isSameNode(oldChild[oldEnd], newChild[newEnd])) {
      patchVNode(oldChild[oldEnd--], newChild[newEnd--]);
    } else break;
  }

  // 如果还有未处理的节点
  if (i <= oldEnd || i <= newEnd) {
    const parent = oldChild[0].elm!.parentNode as Element;

    // 全部是要删除的节点i
    if (i <= oldEnd && i > newEnd) {
      for (; i <= oldEnd; i++) parent.removeChild(oldChild[i].elm!);
    }
    // 全部是要新增的节点
    else if (i > oldEnd && i <= newEnd) {
      for (; i <= newEnd; i++) {
        const before = oldChild[oldEnd + 1]?.elm || null;
        parent.insertBefore(createElement(newChild[i]), before);
      }
    }
    // 复杂情况
    else {
      let oldStart = i;
      let newStart = i;

      // map 缓存 newChild
      const keyToNewIndexMap: Map<string, number> = new Map();
      for (; newStart <= newEnd; newStart++) {
        keyToNewIndexMap.set(newChild[newStart].attr.key, newStart);
      }

      // newNode 在 oldChild 中的 index
      const toBePatch = newEnd - i + 1;
      const newNodeInOldIndexMap = Array(toBePatch).fill(-1);

      // 遍历 oldChild
      let needMove = false;
      let newIndexSoFar = -1;
      for (; oldStart <= oldEnd; oldStart++) {
        const newIndex: number | undefined = keyToNewIndexMap.get(
          oldChild[oldStart].attr.key,
        );

        // 如果在 newChild 中找不到，说明要删除
        if (
          newIndex === undefined ||
          !isSameNode(oldChild[oldStart], newChild[newIndex])
        ) {
          parent.removeChild(oldChild[oldStart].elm!);
        }
        // 找到了就记录下来
        else {
          newNodeInOldIndexMap[newIndex - i] = oldStart;

          // 确定后续是否需要移动，一旦不是连续递增就需要移动
          if (!needMove) {
            if (newIndex > newIndexSoFar) newIndexSoFar = newIndex;
            else needMove = true;
          }
        }
      }

      // 处理 newNodeInOldIndexMap ，新增、踢动节点
      const subsequence = needMove
        ? longestIncreasingSubsequence(newNodeInOldIndexMap)
        : [];

      let last = subsequence.length - 1;
      for (let j = newNodeInOldIndexMap.length - 1; j >= 0; j--) {
        const oldIndex = newNodeInOldIndexMap[j];
        const before = newChild[j + i + 1]?.elm || null;

        // 新增
        if (oldIndex === -1) {
          parent.insertBefore(createElement(newChild[j + i]), before);
        }
        // 移动或跳过
        else {
          // 只有不再最长递增子序列中，才需要移动
          if (
            needMove &&
            (last < 0 || oldIndex !== newNodeInOldIndexMap[subsequence[last]])
          ) {
            parent.insertBefore(oldChild[oldIndex].elm!, before);
          } else --last;

          patchVNode(oldChild[oldIndex], newChild[j + i]);
        }
      }
    }
  }
};
// ----------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------
const patchVNode = (oldNode: VNode, newNode: VNode): void => {
  const oldNodeElm = oldNode.elm as Element;
  newNode.elm = oldNodeElm;

  // 若 newNode 是文本，直接覆盖
  if (typeof newNode.child === "string") {
    oldNodeElm.innerHTML = newNode.child;
  }
  // 若 newNode 有子节点，oldNode 是文本或空数组
  else if (typeof oldNode.child === "string" || oldNode.child.length === 0) {
    oldNodeElm.innerHTML = "";
    for (const child of newNode.child) {
      oldNodeElm.appendChild(createElement(child));
    }
  }
  // 若 newNode、oldNode 都有子节点，则适应 diff
  // else diff_Vue2(oldNode.child, newNode.child);
  else quickDiff_Vue3(oldNode.child, newNode.child);
};

const patch = (oldNode: Element | VNode, newNode: VNode): void => {
  if (oldNode === newNode) return;

  // 如果是第一次 render ，传入的 oldNode 是 Element ，就直接渲染 newNode
  if ((oldNode as Element).nodeType) {
    const elm = oldNode as Element;
    elm.appendChild(createElement(newNode));
  }
  // 否则，就比较新旧 vnode
  else {
    oldNode = oldNode as VNode;

    // 只比较同一层级，若 tag 和 key 相同，就认为 2 个 vnode 是相同的
    if (isSameNode(oldNode, newNode)) patchVNode(oldNode, newNode);
    else {
      const oldNodeElm = oldNode.elm as Element;

      const parent = oldNodeElm.parentNode;
      parent!.insertBefore(createElement(newNode), oldNodeElm);
      parent?.removeChild(oldNodeElm);
    }
  }
};
// ----------------------------------------------------------------------------------------------

class Vue {
  public _vnode: Element | VNode | null = null;
  public _data: any;
  public _render: (h: Function) => VNode;

  constructor(options: { [key: string]: any }) {
    this._data = options.data();
    this._render = options.render;

    if (options.el) this.$mount(options.el as string);
  }

  public _update() {
    const newNode = this._render.call(this, h);
    patch(this._vnode!, newNode);
    this._vnode = newNode;
  }

  public $mount(sel: string) {
    const app = document.querySelector(sel);
    if (!app) return;

    this._vnode = app;
    this._update();

    // new Watch(this, () => this._update());
  }
}

const vm = new Vue({
  data: function () {
    return {
      arr: [
        { id: "1", value: "item 1" },
        { id: "2", value: "item 2" },
        { id: "3", value: "item 3" },
        { id: "4", value: "item 4" },
        { id: "5", value: "item 5" },
      ],
    };
  },

  render(h: Function): VNode {
    return h(
      "ul",
      {},
      this._data.arr.map((item: any) => {
        if (typeof item.value === "string")
          return h("li", { key: item.id }, item.value);
        else {
          return h(
            "p",
            { key: item.id },
            item.value.map((i: any) => h("li", { key: i.id }, i.value)),
          );
        }
      }),
    );
  },
});

vm.$mount("#app");

vm._data?.arr?.splice(2, 1, {
  id: "3",
  value: [
    { id: "3-1", value: "item 31" },
    { id: "3-2", value: "item 32" },
  ],
});
vm._update();
```

从 diff 中可以看出，v-for 加了唯一 key 就可以找出新旧 VNode 相同节点，提高性能：

```
<script>
export default {
  data: function () {
    return {
      list: [
        { id: "1", value: "1" },
        { id: "2", value: "2" },
        { id: "3", value: "3" },
      ],

      formChangeTag: true,
    };
  },

  methods: {
    insertListItem() {
      this.list.unshift({ id: "0", value: "0" });
    },
  },
};
</script>

<template>
  <div>
    <button @click="insertListItem">insert list</button>

    <!-- 
      key 默认会传入 index ，但是这样修改数据后会打乱 key 和节点的对应关系，
      把原本不同的节点判断为相同节点，使得进行了很多不必要的 patch ，浪费性能
    -->
    <ul>
      <li v-for="i in list">{{ i.value }}</li>
    </ul>
    <br />

    <!-- 使用唯一的 key 后，数据修改后能快速找到相同节点并 patch ，性能提高，因为相同节点内部的变化通常是很小的 -->
    <ul>
      <li v-for="i in list" :key="i.id">{{ i.value }}</li>
    </ul>
    <br />

    <!-- input 测试可以更明显，加唯一 key 就能解决 -->
    <ul>
      <li v-for="i in list"><input type="text" /></li>
      <!-- <li v-for="i in list" :key="i.id"><input type="text" /></li> -->
    </ul>
  </div>
</template>
```

### 5.3 模板编译

template 本质就是 string ，是 render 的语法糖，template 最终会编译为 render 。

render 函数需要一个根节点，所以 template 才需要根节点，Vue3 会默认加上 Fragment 作为根节点。

# 二、Vue Router

传统的多页面应用，有多个 html 文件，浏览器通过对应的 url 访问服务器中各个 html 资源；但 SPA 只有一个页面，就要解决 4 个问题：

* SPA 展示多个页面组件，把 url 变成响应式数据，通过监听 hashchange 事件或 popstate 事件处理 url ，router\-view 再通过 url 展示对应的组件

* SPA 在修改 url 时不应该刷新页面，因为都是同一个 html ，同时服务器中对应的 url 也没有对应的资源：
  
  * 可以使用 hash 模式，"\#hash" 修改不会刷新页面，也不会，url 也不会带上 hash 区访问服务器
  
  * 若不想使用 hash 的 '\#' ，让 url 跟美观，可以用 history 模式，但是这样修改 url 就会刷新页面，vue\-router 底层已经用 historyAPI 解决；整个 url 区访问服务器，但没有对应的资源，所以服务器也需要处理一下

* SPA 初始化会加载所有要展示的组件，这时候可以用路由懒加载，实现和传统多页面类似的效果，访问对应资源时才加载

* SP 用 JS 生成内容，不利于 SEO ，可以用 SSR 解决

## 1 使用

Vue2，使用 Vue Router 3：

```
// /src/router/index.js

import VueRouter from "vue-router";

// 普通路由，初始化就会加载
import aaa from "./cpn1.vue";
import { beforeEach } from "node:test";

/**路由懒加载
 * 用 webpack、vite 提供的 import 得到导入组件的 Promise
 * 做了分包，只有进入该页面才会加载此路由，提高性能
 */
const bbb = () => import("./cpn2.vue");

const routes = [
  /***默认路由
   * 路径为 "" 或 "/"
   * redirect 重定向，可以设置进入默认路由时重定向到其他路由
   */
  {
    path: "",
    redirect: "/aaa",
  },

  /**
   * path、component 配置路由路径和对应的组件，除了这两个其他都是可选参数
   * name 路由名，alias 路由别名
   * meta 路由元信息，供给导航守卫中使用
   */
  {
    path: "/aaa",
    component: aaa,
    name: aaa,
    alias: ["/aaa1", "/aaa2"],
    meta: { title: "aaa" },

    // 独享守卫，只有次路由有效
    beforeEnter(to, from, next) {
      next({ path: to.path });
    },
  },
  {
    path: "/bbb",
    component: bbb,
    // component: () => import("./cpn2.vue"),
  },

  /**命名视图
   * router-view 默认展示 default 的路由
   * <router-view name="xxx"> 展示 xxx 的路由
   */
  {
    path: "/ccc",
    component: {
      default: aaa,
      xxx: bbb,
    },
  },

  // 嵌套路由，父路由中需要再次使用 <router-view>
  {
    path: "/hime",
    component: () => import("./components/Home/Home.vue"),
    children: [
      {
        path: "",
        redirect: "main",
      },
      {
        path: "main",
        component: () => import("./components/Home/HomeMain.vue"),
      },
    ],
  },

  // 动态路由
  {
    path: "/goods:goodsId",
    component: () => import("./components/goods/goods.vue"),

    // 也可以用 props 传递参数，组件中用 props 配置项接收
    // props: { xxx: 1 },
  },

  // 正则匹配路由，正则不需要 // 包裹
  {
    path: "/:pathMatch(正则)",
    component: () => import("./components/match.vue"),
  },

  // Not Found 路由，路由都不匹配时进入
  {
    // 这种写法，必须在默认路由后面
    path: "/*",

    // 这种写法，就没有位置限制
    // path: "/:catchAll(.*)",

    component: () => import("./components/404.vue"),
  },
];

const router = new VueRouter({
  routes,

  /**默认是 hash 模式
   * 相同点：
     - 代码中 url 都一样
     - 底层实现都是监听 propstate 事件
   * 区别：
     - hash：浏览器 url 会加上 "#" ，"#" 和后面的 hash 值不会用来访问服务器；hash 值修改也不会刷新页面，
       兼容性最好
     - history：没有 "#" ，用整个 url 访问服务器，所以服务器需要特殊处理；一般来说修改 url 会刷新页面，但是
       这里会使用 HTML5 的 historyAPI 实现不刷新页面
     - abstract：非浏览器环境，如小程序、app，没有 BOM 。所以会把 url 存到一个不可见对象中
   */
  mode: "history",

  //*自定义滚动行为，即路由跳转后滚动到的位置，默认是顶部
  scrollBehavior(to, from, savedPosition) {
    if (to.hash) {
      return {
        selector: to.hash,
        behavior: "smooth",
        offset: { x: 0, y: 100 },
      };
    } else return { x: 0, y: 0 };
  },
});

/**导航守卫、也叫路由守卫，在路由进入之前、之后回调
 * fenwe分为全局前置/后置守卫、独享守卫、组件内守卫
 * to：要去的路由
 * from:：from 过来的路由
 * next：前置守卫中，调用了 next 才会继续跳转
 */

// 全局前置守卫，手游路由适用
router.beforeEach((to, from, next) => {
  /**常见应用
   * 判断是否已登录、是否有权限、有才能 next ，否则返回 login
   * 页面自己跳转自己，只有参数变了是不会重新 render 的，可以在这里 next 到一个 empty 页面，再从后置
     守卫判断是否在 empty ，是就跳转回来
      - 也可以 <router-view :key="$route.fullPath"></router-view>
   */

  next({
    path: to.path,
  });
});

// 全局后置守卫，手游路由适用
router.afterEach((to, from) => {
  /**常见应用
   * 修改 title 等
   * empty 页面跳转回去原页面
   */

  document.title = to.meta.title;
});

export default router;
```

```
<script>
// App.vue
// 嵌套路由需要在父路由组件中再次使用 <router-view>

export default {};
</script>

<template>
  <!-- 用于展示路由页面，类似 template 只作包裹作用，所以无法使用 v-show -->
  <!-- <router-view></router-view> -->

  <!-- 缓存路由 
   * 路由切换时不删除原路由组件 
   * include、exclude 声明缓存起作用的组件 name ，注意不是路由 name ；默认全部路由组件适用
   * 若父路由缓存了，离开父路由不想缓存某个子组件，可以在父组件中，可以用变量 v-if 子组件，在 actived、deactived 修改这个便令
  -->
  <keep-alive include="home,goods">
    <router-view></router-view>
  </keep-alive>
</template>
```

```
// main.js
// ,,,
import Vue from "vue";
import VueRouter from "vue-router";
import router from "./router";

// install 插件，使得 Vue 实例获得 router-view、router-link、$router、$route 等
Vue.use(VueRouter);

new Vue({
  // ...
  router,
});
```

```
<script>
// cpn.vue

export default {
  // 组件内守卫
  beforeRouteEnter(to, from, next) {
    next({ path: to.path });
  },

  // 路由钩子
  activated() {},
  deactivated() {},

  mounted() {
    /**
     * $router 是整个路由对象，用于跳转路由等
     * $route  是当前页面的路由，用于获取参数等
     */
    console.log(this.$router, this.$route);

    // 等价于 this.$route
    // Vue3 中，$route 得到 Proxy 对象，currentRoute 得到 ref 对象
    console.log(this.$router.currentRoute);

    /**获取当前路由路径
     * path：url + params
     * fullPath：url + params + query
     */
    console.log(this.$route.path, this.$route.fullPath);
  },

  methods: {
    toPageA() {
      /**都是异步任务
       * push：跳转后可以返回
       * replace：跳转后不可以返回
       */

      // 简写，只能用 path
      this.$router.push("/aaa");
      this.$router.push("/home/main");

      // 完整写法，推荐用 name ，后期更好维护，如改动 path 就不需要改其他代码了
      this.$router.push({ path: "/aaa" });
      this.$router.push({ name: "aaa" });

      // 传参，动态路由 params 只能有一个参数，query 可以有多个和参数

      // 这样 !$route 只能获取 params ，无法获取 query
      // this.$router.push({ path: "/goods:123?a1=1&b2=2" });

      // 传参常见写法
      // this.$router.push({ path: "/goods:123", query: { a1: 1, a2: 2 } });
      this.$router.push({
        path: "/goods",
        params: "123",
        // params: { goodsId: 123 },
        query: { a1: "1", a2: "2" },
      });

      // 获取参数
      console.log(this.$route.params, this.$route.query);
    },
  },
};
</script>

<template>
  <div>
    <p>{{ $router }}</p>
    <p>{{ $route }}</p>
  </div>

  <div>
    <!-- 路由跳转：
     * 可以用 path 或 name ，但嵌套路由只能是 path 
     * 简单跳转或少量参数适合用声明式导航
     * 参数复杂、或业务复杂、或 v-for 的导航适合用编程式导航、加上事件委托
    -->

    <!-- 声明式导航，使用 push ，to 完整写法和编程式导航一样 -->
    <router-link to="/aaa">to page aaa</router-link>

    <!-- 编程式导航 -->
    <button @click="toPageA">to page a</button>
  </div>
</template>
```

Vue3，使用 Vue Router 4 ，修复了 Vue2 路由的 2 个 bug ：

* 当跳转的路由就是当前路由时，不再有警告

* next 再无警告

```
// /src/router/index.ts

import { createRouter, createWebHistory } from "vue-router";
import type { RouteRecordRaw } from "vue-router";
import HomeView from "../views/HomeView.vue";

const routes: RouteRecordRaw[] = [
  {
    path: "/",
    name: "home",
    component: HomeView,
  },
  {
    path: "/about",
    component: () => import("../views/AboutView.vue"),
  },
];

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes,
});

// 前置守卫新写法，可以用 return 代替 next，但使用 return 时必须不能传入 next
router.beforeEach((to, from) => {
  // next();

  // 等价于 next()
  return true;

  // 也等价于 next()
  // return undefined;

  // next('/login')
  // return "/login";

  // 取消导航
  // return false;

  // 取消导航，并回到 router.onError(() => {})
  // throw new Error('123');
});

export default router;
```

```
<script setup lang="ts">
// App.vue
</script>

<template>
  <!-- <router-view></router-view> -->

  <!-- Vue3 的 router-view 使用 keep-alive、transition 时，必须用插槽 -->
  <router-view #default="{ route, Component }">
    <!-- route: 当前路由  Component: 当前路由组件 -->
    <keep-alive>
      <component :is="Component"></component>
    </keep-alive>
  </router-view>

  <!-- keep-alive、traistion 一起使用时，transition 在外部 -->
  <!-- 
  <router-view v-slot="{ Component }">
    <transition>
      <keep-alive><component :is="Component" /></keep-alive>
    </transition>
  </router-view> 
  -->
</template>
```

```
// main.ts

import { createApp } from "vue";
import App from "./App.vue";
import router from "./router";

const app = createApp(App);
app.use(router);
app.mount("#app");
```

```
<script setup lang="ts">
// /src/views/HomeView.vue

import {
  useRoute,
  useRouter,
  onBeforeRouteUpdate,
  onBeforeRouteLeave,
} from "vue-router";

const route = useRoute();
const router = useRouter();

console.log(route);
console.log(router);

const toAbout = () => router.push("/about");

// 新增 2 个组件内守卫，都是前置守卫，可以用 next 、return
onBeforeRouteUpdate((to, from) => {
  // params 或 query 改变时回调
  console.log("update");
});
onBeforeRouteLeave((to, from) => {
  // 离开当前路由时回调
  console.log("leave");
});
</script>

<script lang="ts">
export default {
  // beforeRouteEnter(to, from) {},
  // beforeRouteUpdate(to, from) {},
  // beforeRouteLeave(to, from) {},
};
</script>

<template>
  <div>Home</div>
  <div>{{ $route }}</div>
  <div>{{ $router }}</div>

  <p>
    <button @click="toAbout">to about</button>
    <router-link to="/about">to about</router-link>
  </p>
</template>
```

## 2 JS 文件中使用

有时候可能需要再 JS 文件中处理路由，如权限系统中动态添加、删除路由配置。

Vue2，Vue Router 3 ：

```
// 等价于组件中的 this.$router
import router from "./router";

// add
router.addRoute({
  path: "/manager",
  name: "manager",
  component: () => import("./components/Manager"),
});

// 给某个路由 add 嵌套路由
router.addRoute("manager", {
  path: "goodsManager",
  name: "goodsManager",
  component: () => import("./components/Manager/GoodsManager"),
});

// add 多个路由
router.addRoutes([]);

// remove
router.removeRoute("manager");

// read
onsole.log(router.hasRoute("manager"));
console.log(router.getRouters());

// update
router.getRoutes[0].redirect = "/home";
```

Vue3，Vue R    outer 4 ：

# 三、Vuex、Pinia

响应式的全局状态管理工具，状态即响应式数据，状态在全局，可实现非父子组件通信。

单一状态树：只允许有一个 store 对象，方便维护。

Vuex、Pinia 在 Vue2、Vue3 都可以使用，Vue3 需要 Vuex4 ，不过 vue3 用 Pinia 更方便。

## 1 Vuex

（1）使用

```
// /src/store/index.js

import Vuex from "vuex";

// 为了方便维护，也会把 state 等抽离成 js 文件，modules 抽离成文件夹
const store = new Vuex.Store({
  state: {
    num1: 123,
    num2: 45,
  },

  // 类似于计算属性
  getters: {
    sum(state, getters) {
      return state.num1 + state.num2;
    },
  },

  /**
   * 为了让 VueDevTools 能够监控到修改，任何地方对 state 的修改都必须使用 mutations
   * mutations 只能处理同步任务，异步监听不到；且逻辑应该尽量简单
   * 通过数组下标修改、对象增加、删除属性，也需要使用 Vue.$set() Vue.$delete
   * mutations 中使用别的 js 文件 export const xxx 的类型常量，需要如此使用 [xxx]
   */
  mutations: {
    setNum1(state, payload) {
      state.num1 = payload.xxx;
    },

    setNum2(state, payload) {
      state.num2 = payload.xxx;
    },
  },

  /**
   * 同步、异步任务均可，适合对 state 做较为复杂修改
   * 内部也需要通过 mutations 修改 state
   */
  actions: {
    astncS0etNum2(context, payload) {
      return new Promise(resolve => {
        setTimeout(() => {
          context.commit({
            type: "setNum2",
            data: { xxx: payload.xxx },
          });
        }, 1000);
      });
    },
  },

  /**子模块
   * state 不能和 rootStore 重复
   * 形参中的state 、context、getters 都是本子模块中的
   */
  modules: {
    moduleA: {
      // 若 moduleA 对象在独立的 JS 文件中，设为 true 可以让 map 语法直接使用 JS 文件名作为模块名
      namespace: true,

      state: { num3: 789 },

      // 多了 2 个参数
      getters: {
        getSum(state, getters, rootState, rootGetters) {
          return state.num3 + rootState.num1;
        },
      },

      mutations: {},

      // context.commit 会去 root 中找
      mutations: {},
      actions: {},
    },
  },
});

/**监听 mutations
 * VueDevTools 可以看到修改，代码中也可以用 subscribe 监听，通常用来做 vuex 插件开发
 * 组件中也可以 watch 某个 state ，因为是响应式数据
 */
store.subscribe((mutation, state) => {
  // 任何一个 mutations 调用都会回调，可以用 type 判断具体是哪一个 mutations
  console.log(mutation.type);
});

export default store;
```

```
// main.js

import Vue from "vue";
import Vuex from "vuex";
import store from "./store";

// 使得 vue 可以使用 $store
Vue.use(Vuex);

new Vue({
  // ...
  store,
})
```

```
<script>
// mapXxx 返回一个队 store 的映射对象，使用更方便
import { mapState, mapGetters, mapMutations, mapActions } from "vuex";

export default {
  methods: {
    // 如果 commit、dispatch 的 type 在子模块中，会自动取子模块找

    addNum1() {
      // this.$store.commit("setNum1");

      this.$store.commit({
        type: "setNum1",
        data: {
          xxx: this.$store.state.num1 + 1,
        },
      });
    },

    addNum2() {
      this.$store
        .dispatch({
          type: "setNum2",
          data: {
            xxx: this.$store.state.num2 + 1,
          },
        })
        .then(() => {});
    },

    ...mapMutations("setNum1"),
    ...mapActions("setNum2"),
  },

  getters: {
    // mapState 起别名必须是函数形式，其他 map 则 string 就行
    ...mapState({
      num1NewName: state => state.num1,
    }),

    ...mapState(["num2"]),
    ...mapState("moduleA", ["num3"]),

    ...mapGetters(["sum"]),
  },

  mounted() {
    console.log(this.$store.state.num1, this.num1NewName);
    console.log(this.$store.state.num2, this.num2);

    console.log(this.$store.state.moduleA.num3, this.num3);
  },
};
</script>

<template>
  <div>
    <div>
      {{ $store.state.num1 }} + {{ $store.state.num2 }} =
      {{ $store.getters.sum }}
    </div>
    <div>
      <button @click="addNum1">add num1</button>
      <button @click="addNum2">add num21</button>
    </div>
  </div>
</template>
```

（2）持久化存储

一旦刷新页面，vuex 的数据就会刷新，如果像实现持久化，可以把 state 存储在 WebStorage 中 中：

```
// /src/store/index.js

import Vuex from "vuex";

const rootStoreState = JSON.parse(localStorage.getItem("rootStore") ?? "{}");

const store = new Vuex.Store({
  state: { num1: 123, ...rootStoreState },

  mutations: {
    setNum1(state, payload) {
      state.num1 = payload.xxx;
      localStorage.setItem("rootStore", JSON.stringify(state));
    },
  },
});

export default store;
```

不过每次都要 getItem、setItem 很麻烦，也不好维护，所以一般都是用插件实现，只要通过 mutations 修改就能同步修改 storage ，反之亦然：

```
npm install --save vuex-persistedstate
```

```
// /src/store/index.js

import Vuex from "vuex";
import createPersistedstate from "vuex-persistedstate";

const store = new Vuex.Store({
  state: { num1: 123 },

  mutations: {
    setNum1(state, payload) {
      state.num1 = payload.xxx;
    },
  },

  plugins: [
    // 默认使用 localStorage ，持久化所有 state 的状态，保存在 storage 的字段 "vuex" 中
    // createPersistedstate(),

    // 自定义存储方式和 state 状态，和保存在 storage 的字段
    createPersistedstate({
      key: "rootStore",
      storage: window.sessionStorage,
      reducer: state => ({ num1: state.num1 }),
    }),
  ],
});

export default store;
```

也可以自定义 Vuex 插件，或者存到数据库中，但用的比较少。

## @ Pinia

Pinia 对 ts 支持更好，且使用更方便，状态可以直接修改，VueDevTools 也能监听到，模块也更侵袭，所以去掉了 mutations 和 modules 。组件中使用更简洁，也不需要 map 语法。

（1）使用

```
// /src/store/counter.ts

import { ref, computed } from "vue";
import { defineStore } from "pinia";

// 通常一个模块一个文件
export const useCounterStore = defineStore("counter", () => {
  // state ，可以用 ref、reactive、readonly 等
  const count = ref(0);

  // getters
  const doubleCount = computed(() => count.value * 2);

  // actions
  function increment() {
    count.value++;
  }

  return { count, doubleCount, increment };
});

// 也可以使用 Options ，但不方便
// export const counterStore = defineStore("counterStore", {
//   state() {
//     return { count: 0 };
//   },

//   getters: {
//     doubleCount(): number {
//       return this.count * 2;
//     },
//   },

//   actions: {
//     func() {
//       console.log(this.count);
//     },
//   },
// });
```

```
// main.ts

import { createApp } from "vue";
import { createPinia } from "pinia";
import App from "./App.vue";

const app = createApp(App);
app.use(createPinia());
app.mount("#app");
```

```
<script setup lang="ts">
import { storeToRefs } from "pinia";
import { useCounterStore } from "./stores/counter";

const counterStore = useCounterStore();

// 每次 state 修改回调
// counterStore.$subscribe((args, state) => {});

// 每次触发 actions 回调
// counterStore.$onAction(arg => {});

// ref 对象这里不用 .value
// 0
console.log(counterStore.count);

// 2
++counterStore.count;
console.log(counterStore.doubleCount);

// 4，复杂的修改就用 actions
counterStore.increment();
console.log(counterStore.doubleCount);

// 多个状态的修改推荐使用 &patch ，性能会高一点
counterStore.$patch({ count: counterStore.count + 1 });
// counterStore.$state = { count: counterStore.count + 1 };
// 3
console.log(counterStore.count);

// 多数据的复杂修改
counterStore.$patch(state => {
  if (true) state.count++;
});
// 4
console.log(counterStore.count);

// 解决响应式丢失，storeToRefs 类似 toRefs ，所以结构出来后需要 .value
const { count } = storeToRefs(counterStore);
++count.value;
// 5
console.log(counterStore.count);

// 如果不是 script setup ，需要手动 return
// return { counterStore };
</script>

<template></template>
```

（2）持久化存储

```
npm install --save pinia-plugin-persistedstate
```

```
// main.ts
// ...
import piniaPluginPersistedstate from "pinia-plugin-persistedstate";
// ...
app.use(createPinia().use(piniaPluginPersistedstate));
// ...
```

```
// /src/store/counter.ts

import { ref, computed } from "vue";
import { defineStore } from "pinia";

// 通常一个模块一个文件
export const useCounterStore = defineStore(
  "counter",
  () => {
    const count = ref(0);
    return { count };
  },
  {
    // 默认 key 为 counter ，使用 localStorage ，持计划所有 state
    // persist: true,
    persist: {
      // 默认是 counter
      key: "counterStore",
      storage: window.localStorage,
    },
  },
);

// export const counterStore = defineStore("counterStore", {
//   state() {
//     return { count: 0 };
//   },

//   // persist: true,
//   persist: {
//     key: "counterStore",
//     storage: window.localStorage,
//   },
// });
```

（3）自定义 Pinia 插件

```
import { toRaw } from "vue";
import type { PiniaPluginContext } from "pinia";

interface MyPluginOptions {
  key?: string;
}

// 不需要参数的写法
// const myPluginTest = (context: PiniaPluginContext) => {};

// 需要参数
export const myPlugin = (options: MyPluginOptions) => {
  return (context: PiniaPluginContext) => {
    const { store } = context;

    // 每次 state 修改都会回调
    store.$subscribe(() => {
      localStorage.setItem(
        options?.key ?? store.$id,
        JSON.stringify(toRaw(store.$state)),
      );
    });

    const data = JSON.parse(
      localStorage.getItem(options?.key ?? store.$id) ?? "{}",
    );

    return { ...data };
  };
};

// pinia.use(myPlugin);

// pinia.use(
//   myPlugin({
//     key: "xxx",
//   }),
// );
```

# 四、工程化

## 1 使用

（1）基本

常用的有 webpack、vite：

* webpack 配合 cli ，安装 vue-cli 或 react-cli 会自动安装 webpack 

* vite 不需要安装，直接 pnpm create

除了 webpack 2 （基本不再使用了）在目录中会显示配置文件外，webpack 3 以上以及 vite 都隐藏了默认的配置文件，默认配置如：

* 热更新，代码修改页面同步刷新

* HTML 识别大写

* 支持 es\-module

* 自带一些 loader ，解析编译 vue 、react 等

配置文件有 json、js、ts ，只要修改了配置文件，就需要重启项目才会生效：

* node ：package\.json ，package\-lock\.json

* vite：vite\.config\.ts

* vue-cli、react\-cli ：vue\.config\.ts ，react\.config\.ts

* 其他：tsconfig\.json 、eslint。prettier 等配置文件

（2）配置

vue\.config.js ：

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

vite\.config\.ts ：

（3）其他配置：

tsconfig.json ：

```
{
  "compilerOptions": {
    //...
    "types": [
      // webpack
      // "webpack-env"

      // vite ，需要 npm install -D @types/node
      "node"
    ],
    "paths": {
      "@/*": [
        "./src/*"
      ]
    }
  }
}
```

## 2 打包

map 文件

（1） node 包管理工具

npm：

```
# 全局安装
npm install -g xxx

# 局部安装，放到当前目录的 node_modules 中
npm install --save xxx

# 安装开始时依赖，只在开发使用，不会打包，如 webpack 插件
npm install --save-dev xxx
npm install -D xxx

# 安装指定版本
npm insyall --save xxx@3.2
npm install --save xxx@latest

# 根据当前目录中的 package.json 安装所有依赖
npm install

# 根据 package.json 的 script 配置项执行脚本
npm run xxx         
```

yarn，命令和 npm 差不多：

```
npm install -g yarn
yarn
```

pnpm（performant npm），命令和 npm 差不多：

```
npm install -g pnpm
pnpm -v
```

npm 、yarn 、pnpm 设置镜像源：

```
# 查看源
pnpm config get registry

# 设置
pnpm config set registry https://registry.npmmirror.com
```

（2）node 配置文件

当前目录下生成 package.json ：

```
npm init
```

package.lock.js 中记录了各个依赖的精确版本和位置，保证每个开发者在 npm install 时都能安装到相同的版本。
