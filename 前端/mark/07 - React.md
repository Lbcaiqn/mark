# 一、React 18

CLI 创建：

```
npx create-react-app projectName
```

Vite 创建：

```
pnpm create vite@latest projectName
```

cli 的入口是 index.js ，vite 的入口是 main.js。里面的严格模式标签笔试 es5 的严格模式，而是用来检查是否有 React 新版本弃用的特性，以作警告，开发时建议注释掉，检查时或生产环境再实用。

jsx 文件后缀是 .js 或 .jsx ，tsx 文件后缀是 .tsx 。

一个组件一个文件夹，分别放 index.tsx 和 index.css ，这样方便引入，可以省去后缀和 index 。

浏览器插件：

React 调试工具：谷歌浏览器插件 React Developer Tools

vscode 插件：

ES7+ React/Redux/React-Native snippets

组件库：

ant-design 和 antd-mobile

## 1 JSX

JSX（Jascript XML），在JS中写HTML，通过 babel 解析。

JSX 中可以写 html ，叫做虚拟DOM，本质是一个对象：

```
const vNode = <div>123<div/>
```

虚拟DOM 有以下规则：

* 用 {} 使用 JS 表达式

* 每个虚拟DOM有且只有一个根节点，也可以用空标签 <></> 或  <Fragment></Fragment> ，这两个都是虚拟的节点，只作包裹作用
  
  * \<\>\</\> ，空标签不能用任何属性
  
  * Fragment，与空标签唯一不同的就是 Fragmentnt 可以用 key 属性，一般在列表渲染需要虚拟节点的时候使用
    
    ```
    import { Fragment } from 'react';
    ```

* 如果遇到了较为复杂的 html 结构，可以用 () 括起来，结构更清晰，如果一行 html 就不用括号了。

### 1.1 基本用法

变量、函数可以写在组件外（全局）或组件内（局部），一般都是放在组件内。

一般会将逻辑抽离成一个自定义 Hook ，类似 Vue 的模板和逻辑分开，这里为了方便就不抽离了。

```
// App.tsx
function App() {
  console.log('函数体相当于旧版本生命周期的 redner ，所以初始化和每次数据修改都会重新执行');
  console.log(this);  // undefined

  const a = 123;
  const b = <strong>123</strong>;
  const arr = [1, 2, 3];
  const obj = { a: 456 };

  function hello() {
    return "hello";
  }

  return (
    <div>
      123456789
      // 注释 1
      {/* 注释 2 */}
      <p>{"asdf"}</p>
      {/* 注意和 Vue 不一样，数组会被遍历出来，对象则直接报错 */}
      <p>{a}</p>
      <p>{b}</p>
      {/* <p>{arr}</p> */}
      {/* <p>{obj}</p> */}
      <p>{hello()}</p>
      <p>{new Date().getDate()}</p>
    </div>
  );
}

export default App;
```

### 1.2 样式

（1）基本使用

```
pnpm install --savae classnames
```

```
/* App.css */
.box1 {
  background-color: red;
}

.box2 {
  font-size: 50px;
}

.box3 {
  color: #fff;
}
```

```
// App.tsx
import classnames from "classnames";
import "./App.css";

function App() {
  return (
    <div>
      <p style={{ backgroundColor: "blue" }}>行内样式，传入一个对象</p>
      <p className={"box1 box2"}>类名，这能写成 className</p>
      <p className={`box1 ${false && "box2"} ${true && "box3"}`}>
        动态绑定类名
      </p>
      <p className={classnames("box1", { box2: false, box3: true })}>
        上面动态绑定类名不方便，可以用 classnames 代替
      </p>
    </div>
  );
}

export default App;
```

（2）css module

因为是单独的 css 文件，就没有 Vue 的 scoped ，这样引入样式如果相同的类名就会有冲突，此时可以使用 css module ，css 文件必须命名为 xxx.module.css ：

```
import AppModule from "./App.module.css";

function App() {
  return (
    <div>
      <p className={AppModule.box}>123</p>
    </div>
  );
}

export default App;
```

不过使用起来挺麻烦的，也可以用 less 嵌套或 scss 的嵌套。

（3）less、scss

装完直接就可以用：

```
pnpm install -D less
pnpm install -D sass
```

### 1.3 列表渲染

原理是利用 JSX 解析数组时会遍历出来。

```
// App.tsx
function App() {
  const myList = [
    { id: "1", text: "a" },
    { id: "2", text: "b" },
    { id: "3", text: "c" },
  ];

  return (
    <div>
      <ul>
        {myList.map((item) => (
          <li key={item.id}>item text is {item.text}</li>
        ))}
      </ul>

      <ul>
        {myList.map((item, itemIndex) => (
          <li key={item.id}>
            item text is {item.text}，index is {itemIndex}
          </li>
        ))}
      </ul>
    </div>
  );
}

export default App;
```

### 1.4 条件渲染

原理是利用 JS 的中断运算和三目运算符，效果类似于 Vue 的 v-if 。

React 没有 v-show，可以通过动态给一个类名控制 display: none;

```
// App.tsx
function App() {
  const isLogin = true;
  const noLogin = false;

  function word(type: number) {
    if (type === 0) return <p>0</p>;
    else return <p>1</p>;
  }

  return (
    <div>
      {/* 方式一，左边 true 则条件成立 */}
      {isLogin && <p>username</p>}
      {noLogin && <p>username</p>}
      {/* 方式二 */}
      {isLogin ? <p>已登录</p> : <span>未登录</span>}
      {noLogin ? <p>已登录</p> : <span>未登录</span>}
      {/*方式三*/}
      {word(0)}
      {word(1)}
    </div>
  );
}

export default App;
```

### 1.5 事件绑定

```
// App.tsx
function App() {
  function func1() {
    console.log(123);
  }

  function func2(e: MouseEvent) {
    console.log("事件对象", e);
  }

  function func3(a: string) {
    console.log(a);
  }

  function func4(a: string, e: MouseEvent) {
    console.log(a, e);
  }

  return (
    <div>
      <ul>
        <li>
          <button onClick={func1}>无任何参数</button>
        </li>
        <li>
          <button onClick={() => console.log("简写")}>
            也可以简写，不用另外定义函数
          </button>
        </li>
        <li>
          <button onClick={func2}>只要事件对象</button>
        </li>
        <li>
          <button onClick={() => func3("参数")}>
            带参数，注意只能写成箭头函数
          </button>
        </li>
        <li>
          <button onClick={(e: MouseEvent) => func4("参数", e)}>
            既要传参又要事件对象
          </button>
        </li>
      </ul>
    </div>
  );
}

export default App;
```

## 2 状态

### 2.1 useState

这是一个 React Hook 函数，允许向组件添加一个状态变量，从而控制影响组件的渲染结果。每次修改会重新渲染视图。

说白了就是 Vue3 中用 ref 和 reactive 定义响应式变量。

如果不是用 useState 弄的变量，即使修改了变量的值，值在控制台也变了，视图也不会修改，如下是错误写法：

```
// App.tsx
function App() {
  let count = 0;

  function add() {
    console.log(count);
    count++;
  }

  return (
    <div>
      <button onClick={add}>add</button> {count}
    </div>
  );
}

export default App;
```

正确应该是用 useState ：

```
// App.tsx
import { useState } from "react";

function App() {
  // useState 返回一个数组，结构出来，第一个是状态变量，第二个是改变这个变量的函数
  // 一般用 const ，这里为了演示错误写法采用了 let
  let [count, setCount] = useState(0);
  // 注意，虽然 reder 每次状态更新都会重新执行，但是 useState 这些 Hook 内部对吧状态保存下来了，所以 count 不会变成 0
  console.log("初始值", count);

  function add1() {
    setCount(count + 1); // 注意不能写成 count++ ，count 是只读的
    console.log(count)
  }

  /*
    注意，useStete 的原则是状态不可变，它是只读的，必须通过 setXxx 修改 react 才能
    监听到修改，react 将新值与旧值就行比较，若改变了则重新渲染。
    下面这个是错误的写法，这样丢失了响应式，值虽然修改了但是视图并没有重新渲染
  */
  function add2() {
    count++;
  }

  return (
    <div>
      <button onClick={add1}>add</button> {count}
      <button onClick={add2}>add</button> {count}
    </div>
  );
}

export default App;
```

几个注意点：

* ，setXxx 是异步的，但是由于异步的修改逻辑在 setCount 内部，setCount 本身并不返回 Promise，所以用不了 await，可使用 useEffect
  
  ```
  // App.tsx
  import { useState, useEffect } from "react";
  
  function App() {
    const [count, setCount] = useState(0);
  
    function add1() {
      setCount(count + 1); 
      console.log("还是旧值", count);
    }
  
    useEffect(() => {
      console.log("修改完成", count);
    }, [count]);
  
    return (
      <div>
        <button onClick={add1}>add</button> {count}
      </div>
    );
  }
  
  export default App;
  ```
  
  有多个 setCount 后面的也会覆盖前面的，使得只修改一次：

```
function add1() {
  etCount(count + 1); 
  etCount(count + 1); 
}
```

* setCount 的参数还可以写成函数形式，上面的写法其实是语法糖，如果修改不依赖于原状态，则可以写成对象形式，如果依赖于原状态，写成函数形式也行
  
  ```
  setCount((cnt: number) => cnt + 1);
  ```

* useState 还可以传入函数形式，效果一样，且类型限制了 T 也能够传入返回类型为 T 的函数，不过用的少：
  
  ```
  const [count, setCount] = useState(() => 0);
  ```

引用数据类型的用法：

setXxx 是比较新值与旧值是否有变化来决定是否重新 render ，而引用类型如果只是修改堆内存的值，本身的引用不变，那么是不会重新 render 的，所以需要深拷贝。

```
// App.tsx
import { useState } from "react";

function App() {
  const [obj, setObj] = useState({ name: "lgx" });
  const [arr, setArr] = useState([0, 1, 2]);

  function updateObj() {
    // obj.name = "123"; // 错误写法
    // 正确做法，用新的对象去替换
    /* 
       这里因为是自己创建的变量，本质是替换，所以要 ... 扩展出其他属性一起传入，否则新的变量只会有 name 属性 
       不过如果是 React 自己维护的变量就，一般是合并，只需要传入要修改的属性就可以了，比如class API 的 setState，Zustand 的 set 
       */
    setObj({
      ...obj,
      name: "123",
    });
  }

  function updateArr() {
    // arr[1]++; // 错误写法
    // 正确写法
    const newArr = [...arr];
    newArr[1]++;
    setArr(newArr);
  }

  return (
    <div>
      <p>
        <button onClick={updateObj}>update obj</button> {obj.name}{" "}
      </p>
      <p>
        <button onClick={updateArr}>update arr</button> {arr[1]}{" "}
      </p>
    </div>
  );
}

export default App;
```

### 2.2 useReducer

如果一个状态有比较多的操作，那么可以选择用 useReducer 将状态和对应的各个操作封装起来，简化代码，提高代码可读性，比如下面的例子，cnt 可以加一，减一，加十，讲这些都放到一起：

```
// /src/App.tsx
import { useReducer } from "react";

function App() {
  // 定义 reducer
  type ActionType = {
    type: "INC" | "DEC" | "INC_N" | string;
    payload?: number;
  };

  function countReducer(state: number, action: ActionType): number {
    switch (action.type) {
      case "INC":
        return state + 1;
      case "DEC":
        return state - 1;
      case "INC_N":
        return state + action.payload;
      default:
        return state;
    }
  }

  const [cnt, cntDispatch] = useReducer(countReducer, 0);

  return (
    <div>
      <div>{cnt}</div>
      <div>
        <button onClick={() => cntDispatch({ type: "INC" })}>inc</button>
        <button onClick={() => cntDispatch({ type: "DEC" })}>dec</button>
        <button onClick={() => cntDispatch({ type: "INC_N", payload: 10 })}>
          inc 10
        </button>
      </div>
    </div>
  );
}

export default App;
```

### 2.3 useMemo 和 useCallback

React 中没有计算属性，但是有 useMemo 也可以缓存数据，只有在依赖的数据发生变化时才重新执行：

```
// /src/App.tsx
import { useState, useMemo } from "react";

function App() {
  const [a, setA] = useState(0);
  const [b, setB] = useState(0);

  // a 和 b 变化都会执行
  function sumA() {
    console.log("sumA调用了");
    return a + 10;
  }

  // 只有 b 变化时才会重新执行，相当于计算属性；若依赖项为空数组则只在组件渲染完毕后执行一次
  const sumB = useMemo(() => {
    console.log("sumB调用了");
    return b + 10;
  }, [b]);

  return (
    <div>
      <div>
        <button onClick={() => setA(a + 1)}>++a</button>
        <span> {a}</span>
        <span> {sumA()}</span>
      </div>
      <div>
        <button onClick={() => setB(b + 1)}>++b</button>
        <span> {b}</span>
        <span> {sumB}</span>
      </div>
    </div>
  );
}

export default App;
```

useCallback 则是缓存函数的，一般用在缓存组件，详见组件篇。

## 3 表单

双向绑定：

React 没有 v-model ，所以只能用绑定 value 和 change 事件。双向绑定的表单也叫受控表单。

```
// App.tsx
import { useState } from "react";

function App() {
  const [str, setStr] = useState("");

  function changeStr(e: React.ChangeEvent<HTMLInputElement>) {
    setStr(e.target.value);
  }

  return (
    <div>
      <input value={str} onChange={changeStr} /> {str}
    </div>
  );
}

export default App;
```

不过每个表单的 change 事件基本相同，为了简化代码，可以直接在 change 绑定 () => 修改 cvalue ，也可以定义一个函数，通过参数决定修改那个表单的 value 。

## 4 组件

React 的组件是一个首字母大写的函数，内部是组件的逻辑和视图，App.js 中的 App 函数就是一个组件。

根据组件中又无状态（值数据）可分为：

* 简单组件，无状态驱动视图

* 复杂组件，有状态驱动视图的渲染

### 4.1 基本用法：

```
// App.tsx
function MyCpn() {
  return <div>this is a component</div>;
}

function App() {
  return (
    <div>
      <MyCpn></MyCpn>
      <MyCpn />
    </div>
  );
}

export default App;
```

### 4.2 获取 DOM

普通的 DOM 节点：

```
// App.tsx
import { useRef } from "react";

function App() {
  const divRef = useRef<HTMLDivElement | null>(null);

  function getDivRef() {
    console.log(divRef?.current);
  }

  return (
    <div>
      <div ref={divRef}>123</div>
      <button onClick={getDivRef}>click</button>
    </div>
  );
}

export default App;
```

获取子组件的 DOM ：

直接绑定 reef 是获取不到的，还需要在子组件中使用 forwardRef 才行，此外还能再子组件中用 useImperativeHandle 吧函数给父组件用。

下面的例子是在父组件中控制子组件表单的聚焦（类型暂不知道怎么定义）：

```
// App.tsx
import { useRef, forwardRef, useImperativeHandle } from "react";

// 用 forwardRef 定义子组件，参数 ref 就是父组件中子组件标签绑定的 ref
const Son = forwardRef((props, ref) => {
  const inputRef = useRef(null);

  function inputFocus() {
    inputRef.current.focus();
  }

  useImperativeHandle(ref, () => {
    return {
      inputFocus,
    };
  });

  return (
    <div ref={ref}>
      <input type="text" ref={inputRef} />
    </div>
  );
});

function App() {
  let sonRef = useRef(null);

  return (
    <div>
      <Son ref={sonRef} />
      <button onClick={() => sonRef.current.inputFocus()}>focus</button>
    </div>
  );
}

export default App;
```

### 4.3 组件通信

父传子，和 Vue 一样 props 是只读的。

可以传任何数据，包括 JSX。

如果子组件标签内有内容，那么这些内容会全部放到 props.children 中。

```
// App.tsx
type SonPropsType = {
  aaa: string;
  bbb: JSX.Element;
  children: React.ReactNode

}

function Son(props: SonPropsType) {
  return (
    <div>
      <div>{props.aaa}</div>
      <div>{props.bbb}</div>
      <div>{props.children}</div>
    </div>
  );
}

function App() {
  const a = "123";
  const b = <strong>456</strong>;
  const c = (
    <div>
      <ul>
        <li>1</li>
        <li>2</li>
      </ul>
    </div>
  );

  return (
    <div>
      <Son aaa={a} bbb={b}>
        {c}
      </Son>
    </div>
  );
}

export default App;
```

子传父，和 Vue 不一样，React 是父传给子一个函数，子调用这个函数来传值。

```
// App.tsx
type SonPropsType = {
  onGetMsg: (msg: string) => void
}

function Son(props: SonPropsType) {
  const {onGetMsg} = props;

  return (
    <div>
      <button onClick={() => onGetMsg("msg")}>子传父</button>
    </div>
  );
}

function App() {
  function getMsg(msg: string) {
    console.log(msg);
  }

  return (
    <div>
      <Son onGetMsg={getMsg}></Son>
    </div>
  );
}

export default App;
```

兄弟通信（状态提升），先 A 子传父，再父传子给 B 。

```
// App.tsx
import { useState } from "react";

type APropsType = {
  onGetMsg: (msg: string) => void;
};

type BPropsType = {
  msg: string;
};

function A(props: APropsType) {
  const { onGetMsg } = props;

  return (
    <div>
      <button onClick={() => onGetMsg("msg")}>子传父</button>
    </div>
  );
}

function B(props: BPropsType) {
  const { msg } = props;

  return <div>from brother：{msg}</div>;
}

function App() {
  const [m, setM] = useState("");

  function getMsg(msg: string) {
    setM(msg);
  }

  return (
    <div>
      <A onGetMsg={getMsg} />
      <B msg={m} />
    </div>
  );
}

export default App;
```

跨层组件通信（context 机制）

```
// App.tsx
import { createContext, useContext } from "react";

const MsgContext = createContext("默认值");

function B() {
  const msg = useContext(MsgContext);
  return <div>{msg}</div>;
}

function A() {
  return (
    <div>
      <B />
    </div>
  );
}

function App() {
  const msg = "跨层组件通信";

  return (
    <div>
      <MsgContext.Provider value={msg}>
        <A />
      </MsgContext.Provider>
    </div>
  );
}

export default App;
```

### 4.4 插槽

有 children props 和 reder props ，children props 在组件通信笔记记录过，相当于 Vue 的默认插槽。

render props 相当于 Vue 的具名插槽和作用于插槽，使用示例：

```
// App.tsx
type ContentPropsType = {
  msg: string;
};

type SonPropsType = {
  render: (msg: string) => React.ReactNode;
  aaa: (msg: string) => React.ReactNode;
};

function Content(props: ContentPropsType) {
  return <div>{props.msg}</div>;
}

function Son(props: SonPropsType) {
  const { render, aaa } = props;
  const msg1 = "插槽 1";
  const msg2 = "插槽 2";

  return (
    <div>
      <div>{render(msg1)}</div>
      <div>{aaa(msg2)}</div>
    </div>
  );
}

function App() {
  return (
    <div>
      {/* 原理是传给子组件一个函数，通过子传父得到子的数据（作用域插槽），同时子组件也由得到了这个函数返回的虚拟 DOM */}
      {/* 不一定要使用 render 这个名字，如果具名插槽只有一个就用 render ，这是规范，多个插槽就随意了 */}
      <Son
        render={(msg: string) => <Content msg={msg} />}
        aaa={(msg: string) => <Content msg={msg} />}
      />
    </div>
  );
}

export default App;
```

### 4.5 缓存组件

每次数据的变化都会重新渲染页面，组件也会，而有些时候重新渲染组件是没有必要得到，比如组件的 props 都没有改变，就没必要重新渲染，浪费资源。

使用 memo 可以缓存组件，memo 会对组件的每个 props 进行新旧比较，如果所有的 props 都没有变化，则混存该组件。

memo 的原理是使用 Objcet.is 进行比较，相同返回 true。

注意，重聚变化 -> 重新渲染页面这个过程中，所有数据都是重新赋值的，且比较引用类型时比较的是引用，这样的话引用类型的引用就和原来不同了，进而使得 Object.is 判断 props 不同而重新渲染组件，解决方案是使用 useMemo 缓存数组/对象，使用 useCallback 缓存函数。值类型就没有这个问题，因为比较的是值。

```
// App.tsx
import { memo, useState, useMemo, useCallback } from "react";

type SonPropsType = {
  msg: string;
  list?: number[];
  func?: () => void;
};

function Son(props: SonPropsType) {
  console.log(props.msg);
  return <div>Son</div>;
}

const MemoSon = memo((props: SonPropsType) => {
  console.log(props.msg);
  return <div>MemoSon</div>;
});

function App() {
  const [cnt, setCnt] = useState(0);
  const num = 100;
  const list1 = [1, 2, 3];
  const func1 = () => {};
  // 缓存下来，看需要给依赖项
  const list2 = useMemo(() => {
    return [1, 2, 3];
  }, []);
  // 缓存函数，一般依赖项都是空数组，因为函数一般不会改变
  const func2 = useCallback(() => {}, []);

  return (
    <div>
      <button onClick={() => setCnt(cnt + 1)}>add</button> {cnt}
      <Son msg="未缓存的组件，每次数据修改重新渲染都会重新渲染该组件" />
      <MemoSon msg="缓存的组件，没有 props 变化，不会重新渲染" />
      <MemoSon msg="缓存的组件，没有 props 变化，不会重新渲染" num={num} />
      <MemoSon msg="缓存的组件，只有 props 变化时才会重新渲染" num={cnt} />
      <MemoSon
        msg="引用类型每次重新渲染都会创建新的引用，使得这里的 list 引用与原来不同"
        list={list1}
      />
      <MemoSon
        msg="引用类型每次重新渲染都会创建新的引用，使得这里的 list 引用与原来不同"
        func={func1}
      />
      <MemoSon msg="useMemo" list={list2} />
      <MemoSon msg="useCallback" func={func2} />
    </div>
  );
}

export default App;
```

类组件通过生命周期钩子 shouldComponentUpdate 可以实现相同的效果。

## 5 生命周期

具体的生命周期见类组件笔记。 

这里使用 useEffect 替代生命周期狗子，根据不同的参数可以当做 componentDidMount、componentDidUpdate 和 componentWillUnMount，有两个参数：

* 第一个参数是回调函数，在这里也叫副作用函数，函数体也叫副作用操作

* 第二个参数是依赖项，有三种情况

用法：

```
// App.tsx
import { useRef, useState, useEffect } from "react";

function App() {
  const divRef = useRef<HTMLDivElement | null>(null);
  const [a, setA] = useState(0);
  const [b, setB] = useState(0);

  // 情况一，依赖项为空数组，相当于 Vue 的 onMounted
  useEffect(() => {
    console.log("情况一，只在组件渲染完毕调用一次", divRef.current);
  }, []);

  // 情况一，不传入依赖项，相当于 Vue 的 onMounted + onUpdated
  useEffect(() => {
    console.log("情况二，组件渲染完毕，a 和 b 改变都会调用", divRef.current);
  });

  // 情况三，依赖项为指定状态变量的数组，相当于 Vue 的 onMounted + 指定状态变量的 onUpdated
  useEffect(() => {
    console.log("情况三，组件渲染完毕，和只有 b 改变才会调用", divRef.current);
  }, [b]);

  return (
    <div>
      <div ref={divRef}>123</div>
      <div>
        <button onClick={() => setA(a + 1)}>++a</button> {a}
      </div>
      <div>
        <button onClick={() => setB(b + 1)}>++b</button> {b}
      </div>
    </div>
  );
}

export default App;
```

清除副作用：

相当于 Vue 的 onUnMounted，在组件销毁时清除一些东西。

```
// App.tsx
import { useRef, useState, useEffect } from "react";

function Cpn() {
  useEffect(() => {
    console.log(666);

    // 定时器类型为 number | null
    const timer = setInterval(() => {
      console.log(123);
    }, 1000);

    // 清除副作用
    return () => {
      clearInterval(timer);
    };
  }, []);

  return <div>子组件</div>;
}

function App() {
  const [isShow, setIsShow] = useState(true);

  return (
    <div>
      <button onClick={() => setIsShow(false)}>删除子组件</button>
      {isShow && <Cpn />}
    </div>
  );
}

export default App;
```

## 6 自定义 Hook 函数

use 开头的函数，实现逻辑的封装和复用。

Hook 函数有两个规定：

* Hook 函数只能在组件内，或 Hook 函数内使用

* Hook 函数只能在顶层使用，不能在 if、for、非组件非 Hook 的函数体等等的内部使用

可以在自定义 Hook 函数，如下是一个点击按钮显示隐藏的 Hook 函数：

```
// App.tsx
import { useState } from "react";

function useShowBox(isShow: boolean): [boolean, () => void] {
  const [show, setShow] = useState(isShow);
  const updateShow = () => setShow(!show);

  return [show, updateShow];
}

function App() {
  const [aShow, updateAShow] = useShowBox(true);
  const [bShow, updateBShow] = useShowBox(true);

  return (
    <div>
      <ul>
        <li>
          <button onClick={updateAShow}>show or hide A</button>{" "}
          {aShow && <span>I am A</span>}
        </li>
        <li>
          <button onClick={updateBShow}>show or hide B</button>{" "}
          {bShow && <span>I am B</span>}
        </li>
      </ul>
    </div>
  );
}

export default App;
```

## 7 类组件

（1）基本使用

之前笔记的 Hoks 是在 React 16.8 版本才有的，更早的版本只能写类组件，或者用不了各种 Hooks 的函数式组件。

类组件官方已不再推荐使用，但考虑到老项目可能使用，所以还是得要了解一下。

这里说的老版本指的是 React16.x ，更早的版本就没必要了解了。

就不写 ts 了，js 演示：

```
import { Component } from "react";

// 类组件三大属性：state，props，ref
class Son extends Component {
  // 状态变量
  state = {
    cnt: 0,
  };

  // 函数
  // render 这些生命周期钩子 thsi 指向组件实例，而自定义的函数 this 为undefiend，所以要用箭头函数
  add = () => {
    // 修改状态变量
    // 对象是合并所以不用 ... 扩展state，但是数组时替换，注意一下
    this.setState(
      {
        cnt: this.state.cnt + 1,
      },
      () => {
        // 这是可选参数，此处可获取修改完成后的数据，不过 useState 得到的 setXxx 去掉了这个参数
        console.log(this.state.cnt);
      }
    );

    // 第一个参数也可以是函数形式，在 useState 中获得的 setXxx 没有第二个参数 props
    // this.setState((state, props) => ({ count: state.count + 1 }));
  };

  // 生命周期钩子
  componentDidMount() {
    console.log("mounted", this.props.msg);
  }

  // 模板
  render() {
    return (
      <div>
        Son：{this.state.cnt} <button onClick={this.add}>add</button>{" "}
        <button onClick={() => this.props.getCnt(this.state.cnt)}>
          getCnt
        </button>
      </div>
    );
  }
}

class Parent extends Component {
  state = {
    msg: "From Parent",
    num: 0,
  };

  getCnt = (n) => {
    this.setState({
      num: n,
    });
  };

  render() {
    return (
      <div>
        <div>Parent num：{this.state.num}</div>
        <Son msg={this.state.msg} getCnt={this.getCnt} />
      </div>
    );
  }
}

function App() {
  return <Parent></Parent>;
}

export default App;
```

（2）生命周期

分类三个阶段：

* 挂载：constructor -> componentWillMount -> render -> componentDidMount

* 更新：父组件 render -> componentWillReceiveProps -> shouldComponentUpdate -> componentWillUpdate -> componentDidUpdate

* 销毁：componentWillUnMount

注意点：

* 函数式组件的函数体就是 render ，所以每次更新都会执行，这要与 Vue3 的 setup 只调用一次区分开，否则会出意外的，比如在函数式组件内用了定时器，定时器里修改了状态，就会进入无限地柜

* setState() 开始触发 shouldComponentUpdate ，内部返回 true 才会允许更新继续往下走生命周期，返回 false 则直接拒绝更新。若没有编写 shouldComponentUpdate，则默认返回 true

* 调用 forceUpdate() 可以不修改状态的前提下直接更新，且不需要经过 shouldComponentUpdate 的允许，所以此时会直接进入 componentWillUpdate

* componentWillReceiveProps 第一次不会执行，只会在 props 修改后才会执行

React 17 删除和新增的钩子：

* 删除3个：componentWillMount、componentWillUpdcate、componentWillReceiveProps 均在前面加上 UNSAFE_ ，且不再推荐使用

* 新增1：getDeriverStateFromProps，替换原来的 UNSAFE_componentWillMount 和 UNSAFE_componentWillReceiveProps ，这个钩子有形参 props ，必须用 static 定义为静态方法，且要返回 nul 或状态对象。使用场景非常少，见文档

* 新增2：getSnapshotBeforeUpdate 替换 UPSAFE_componentWillUpdate ，返回 null 或快照，用的也少，见文档

（3）错误边界

在渲染过程中，如果子组件发生了异常，那么整个 App 都会停止运行，为了防止出现这种情况，可以使用错误边界，使错误限制在一个边界内，当子组件发生异常时，也不影响父组件和其他内容的渲染。

使用方法是在父组件中控制：

```
import { Component } from "react";

class Son extends Component {
  render() {
    错误代码;
    return <div></div>;
  }
}

class Parent extends Component {
  state = {
    isErr: false,
  };

  // 一旦发生异常就会进入回调，但也只能监听生命周期钩子的异常
  static getDerivedStateFromError(err) {
    console.log("出错了");
    return { isErr: true };
  }

  render() {
    return (
      <div>
        <div>父组件内容</div>
        {this.state.isErr ? <h1>出错了</h1> : <Son></Son>}
      </div>
    );
  }
}

function App() {
  return <Parent></Parent>;
}

export default App;
```

# 二、状态管理工具

## 1 Redux

React 最流行的状态管理工具。

Redux 调试工具：谷歌浏览器插件 Redux DevTools

React 使用 Redux 需要两个插件：

* @reduxjs/toolkit（RKT），官方推荐的编写 Redux 逻辑的方式，简化原生 Redux 的写法。RKT 也有一套现成的工具。

* react-redux，react 接入 redux 之间的中间件。

（1）用法

```
pnpm install --save @reduxjs/toolkit react-redux
```

```
// /src/store/modules/aStore/index.tsx
import { createSlice } from "@reduxjs/toolkit";

const aStore = createSlice({
  // 模块名
  name: "aStore",
  // 状态
  initialState: {
    cnt: 0,
  },
  // 同步的修改状态
  reducers: {
    add(state) {
      ++state.cnt;
    },
    // 可传参，传递的参数会放到 action.payload
    clear(state, action) {
      state.cnt = action.payload;
    },
  },
});

// 取出 action
const { add, clear } = aStore.actions;

// 异步修改状态哦，每种修改都要写成函数
function asyncClear(payload: any) {
  return (dispatch) => {
    let timer = setTimeout(() => {
      dispatch(clear(0));
      clearTimeout(timer);
    }, payload.time);
  };
}

export { add, clear, asyncClear };

export default aStore.reducer;
```

```
// /src/store/index.tsx
import { configureStore } from "@reduxjs/toolkit";
import aReducer from "./modules/aStore";

const store = configureStore({
  reducer: {
    aStore: aReducer,
  },
});

export default store;
```

```
// /src/main.tsx
import ReactDOM from "react-dom/client";
import App from "./App";
import store from "./store";
import { Provider } from "react-redux";

const root = ReactDOM.createRoot(document.getElementById("root")!);
root.render(
  <Provider store={store}>
    <App />
  </Provider>
);
```

```
// /src/App.tsx
import { useSelector, useDispatch } from "react-redux";
import { add, clear, asyncClear } from "./store/modules/aStore";

function App() {
  const dispatch = useDispatch();
  const { cnt } = useSelector((state: any) => state.aStore);

  return (
    <div>
      <div>
        <button onClick={() => dispatch(add())}>add</button>{" "}
      </div>
      <div>
        <button onClick={() => dispatch(clear(0))}>clear</button>{" "}
      </div>
      <div>
        <button onClick={() => dispatch(asyncClear({ time: 3000 }))}>
          1s clear
        </button>{" "}
      </div>
      <div>{cnt}</div>
    </div>
  );
}

export default App;
```

持久化：

之前使用异步 action 能正常使用，但如果持久化还需要异步 action 就需要中间件 redux-thunk：

```
pnpm install --save redux-persist redux-thunk
```

```
// /src/store/index.tsx
import { configureStore } from "@reduxjs/toolkit";
import aReducer from "./modules/aStore";
import storage from "redux-persist/lib/storage";
// import storageSession from 'reduxjs-toolkit-persist/lib/storage/session'
import { persistReducer, persistStore } from "redux-persist";
import thunk from "redux-thunk";

const persistConfig = {
  key: "root",
  storage,
};

const persistedAReducer = persistReducer(persistConfig, aReducer);

const store = configureStore({
  reducer: {
    aStore: persistedAReducer,
  },
  middleware: [thunk],
});

const persistor = persistStore(store);

export { store, persistor };
```

```
// /src/main.tsx
import ReactDOM from "react-dom/client";
import App from "./App";
import { persistor, store } from "./store";
import { Provider } from "react-redux";
import { PersistGate } from "redux-persist/integration/react";

const root = ReactDOM.createRoot(document.getElementById("root")!);
root.render(
  <Provider store={store}>
    <PersistGate loading={null} persistor={persistor}>
      <App />
    </PersistGate>
  </Provider>
);
```

然后组件里正常使用就行。

（2）原生写法

上面的例子是简化的写法，这里是原生的写法，原生比较繁琐，但可以理解 redux 的设计理念。

创建一个 stiore 管理状态，每次状态修改需要 dispatch 一个 action 通知 store 修改状态，store 根据 reducer 做对应的操作，最后 store 通过 subscribe 通知 react 重新 render 。

```
pnpm install --save redux redux-thunk react-redux
```

```//
// /src/store/modules/aMoudles/actions.tsx
// 创建同步的 createAction
const actions = {
  increment: (payload?: any) => ({ type: "INCREMENT", payload }),
  decrement: (payload?: any) => ({ type: "DECREMENT", payload }),
};

export default actions;
```

```
// /src/store/modules/aMoudles/asyncActions.tsx
import store from "@/store";
import actions from "./actions";

const { increment } = actions;

// 创建异步的 actionCreator
const asyncActions = {
  asyncIncrement: (payload?: any) => {
    return () => {
      const timer = setTimeout(() => {
        store.dispatch(increment());
        clearTimeout(timer);
      }, 3000);
    };
  },
};

export default asyncActions;
```

```
// /src/store/modules/aMoudles/index.tsx
// 创建初始 state
const initalState = {
  cnt: 0,
};

// 创建 reducer
export default function aReducer(
  state = initalState,
  action: { type: string; payload: any }
) {
  switch (action.type) {
    case "INCREMENT":
      return { ...state, cnt: state.cnt + 1 };
    case "DECREMENT":
      return { ...state, cnt: state.cnt - 1 };

    default:
      return state;
  }
}
```

```
// /src/store/index.tsx
import { createStore, applyMiddleware, combineReducers } from "redux";
import thunk from "redux-thunk";
import aReducer from "./modules/aModule";

// 合并 reducer ，如果只有一个 reducer 那就直接传给 createStore 就好了
const reducer = combineReducers({
  aStore:aReducer,
});

// 如果有异步的 action ，就需要 applyMiddleware 使用中间件 redux-thunk
const store = createStore(reducer, applyMiddleware(thunk));

export default store;
```

```
// /src/main.tsx
import ReactDOM from "react-dom/client";
import App from "./App.tsx";
import store from "./store";

const root = ReactDOM.createRoot(document.getElementById("root")!);
root.render(<App />);

// subscribe 在每次 store 维护的状态修改时会对调，必须在这里重新 render
store.subscribe(() => {
  root.render(<App />);
});
```

```
// /src/App.js
import store from "@/store";
import aActions from "@/store/modules/aModule/actions.tsx";
import aAsyncActions from "@/store/modules/aModule/asyncActions.tsx";

function App() {
  const { getState, dispatch } = store;
  const { aStore: { cnt } } = getState();
  const { increment, decrement } = aActions;
  const { asyncIncrement } = aAsyncActions;

  return (
    <div>
      <button onClick={() => dispatch(decrement())}>-</button>
      <span> {cnt} </span>
      <button onClick={() => dispatch(increment())}>+</button>
      <button onClick={() => dispatch(asyncIncrement())}>异步 +</button>
    </div>
  );
}

export default App;
```

再配合 react-redux 写法有一些变化：

react-redux 把组件分为 UI 组件和容器组件，一般自定义的组件都是 UI 组件，react-redux 不允许直接在 UI 组件中使用 redux 的 api ，需要在 UI 组件外部包裹一个容器组件，在容器组件中把状态和操作传给 UI 组件，UI 组件才能间接使用。

当然 @reduxjs/toolkit 提供了一系列 Hooks 来直接在 UI 组件中使用 redux ，这样就不用包一层容器组件了，即 （1）中的写法。

这里的例子是在不仅使用 @reduxjs/toolkit 的情况下如何使用 react-redux ：

```
// /src/App.js
import { connect } from "react-redux";
import store from "@/store";
import aActions from "@/store/modules/aModule/actions.tsx";
import aAsyncActions from "@/store/modules/aModule/asyncActions.tsx";

// UI 组件
function AppUI(props: any) {
  console.log(props);
  const {
    aStoreState: { cnt },
    increment,
    decrement,
    asyncIncrement,
  } = props;
  console.log(increment);

  return (
    <div>
      <button onClick={decrement}>-</button>
      <span> {cnt} </span>
      <button onClick={increment}>+</button>
      <button onClick={asyncIncrement}>异步 +</button>
    </div>
  );
}

// 创建容器组件并把 UI 组件作为子组件
const App = connect((storeState: any) => ({ aStoreState: storeState.aStore }), {
  ...aActions,
  ...aAsyncActions,
})(AppUI);

export default App;
```

```
// /src/main.tsx
import ReactDOM from "react-dom/client";
import App from "./App.tsx";
import store from "./store";
import { Provider } from "react-redux";

const root = ReactDOM.createRoot(document.getElementById("root")!);
root.render(
  <Provider store={store}>
    <App />
  </Provider>

  // 每个容器组件都要传入 store ，但如在根组件上包裹 Provider 拆惹怒 store ，就会自动给每个容器组件传入 store
  // <App store={store} />
);
```

## 2 Zustand

代码比 Redux 简洁很多。

```
pnpm install --save zustand
```

基本使用：

这里为了方便就写在一个文件里面了，也不用挂载，当然项目中还是要放到 store 文件夹 中的。

```
// App.tsx
import { create } from "zustand";

const store = create((set: any) => ({
  cnt: 0,
  add: () => set((state) => ({ cnt: state.cnt + 1 })),
  asyncAdd: async () => {
    let timer = setTimeout(() => {
      set((state) => ({ cnt: state.cnt + 2 }));
      clearTimeout(timer);
    }, 1000);
  },
}));

function App() {
  const { cnt, add, asyncAdd } = store();
  return (
    <div>
      <div>{cnt}</div>
      <div>
        <button onClick={add}>add 1</button>
        <button onClick={asyncAdd}>1s add 2</button>
      </div>
    </div>
  );
}

export default App;
```

切片模式：

就是分成分模块。

```
// App.tsx
import { create } from "zustand";

const store1 = (set: any) => ({
  cnt1: 0,
  add1: () => set((state) => ({ cnt1: state.cnt1 + 1 })),
});

const store2 = (set) => ({
  cnt2: 0,
  add2: () => set((state) => ({ cnt2: state.cnt2 + 1 })),
});

const store = create((...args: any[]) => ({
  ...store1(...args),
  ...store2(...args),
}));

function App() {
  const { cnt1, add1, cnt2, add2 } = store();
  return (
    <div>
      <div>{cnt1}</div>
      <div>
        <button onClick={add1}>add1</button>
      </div>

      <div>{cnt2}</div>
      <div>
        <button onClick={add2}>add2</button>
      </div>
    </div>
  );
}

export default App;
```

# 三、React Router 6

```
pnpm install --save react-router-dom
```

## 1 基本使用

（1）方式一

路由配置与跳转、默认路由、嵌套路由、路由传参（ params，search，location state ）、404 路由：

```
// /src/psges/Home/index.tsx
import { Link, useNavigate } from "react-router-dom";

function Home() {
   // 变成式导航
   const navigate = useNavigate();

   function func(){
     // 不传参
     // navigate('/about');  

    // 传参
    // navigate('/profile/123');  
    // navigate('/aticle?type=hot&page=1');  
    // navigate('/about',{ replace: false, state: { type: 'hot', page: 1 } });  // replace 默认为 false  

    // 前进后退
    // navigate(1);
    // navigate(-1);
  }

  return (
    <div>
      <div>Home</div>
      <div>
        <Link to="/about">to About</Link>
      </div>
      <div>
        <Link to="/profile/123">to Profile</Link>
      </div>
      <div>
        <Link to="/aticle?type=hot&page=1">to Aticle by search</Link> 
        <Link to="/aticle" state={ type: 'hot', page: 1 }>to Aticle by state</Link>
      </div>
    </div>
  );
}

export default Home;
```

```
// /src/pages/About/index.tsx
import { Outlet } from "react-router-dom";

function About() {
  return (
    <div>
      <div>About</div>
      <Outlet />
    </div>
  );
}

export default About;
```

```
// /src/pages/About/child/About1/index.tsx
import { Link } from "react-router-dom";

function About() {
  return (
    <div>
      <div>About 1</div>
      <div>
        <Link to="/home">to Home</Link>
      </div>
      <div>
        {/* 可省略为 to="about2" */}
        <Link to="/about/about2">to About 2</Link>
      </div>
    </div>
  );
}

export default About;
```

```
// /src/pages/About/child/About2/index.tsx
import { Link } from "react-router-dom";

function About() {
  return (
    <div>
      <div>About 2</div>
      <div>
        <Link to="/about/123">to About 1</Link>
      </div>
    </div>
  );
}

export default About;
```

```
// /src/pages/Profile/index.tsx
import { Link, useParams } from "react-router-dom";

function Profile() {
  const { uid } = useParams();

  return (
    <div>
      <div>Profile</div>
      <div>userid is：{uid}</div>
      <div>
        <Link to="/home">to Home</Link>
      </div>
    </div>
  );
}

export default Profile;
```

```
// /src/pages/Aticle/index.tsx
import { Link, useSearchParams, useLocation } from "react-router-dom";

function Aticle() {
  // setSearch 是用来修改 search 参数的，有些情况会用到，用法 setSearch('a=1&b=2')
  const [search, setSearch] = useSearchParams();
  const type = search.get("type");
  const page = search.get("page");

  // 获取 state 参数，path 等
  console.log(useLocation());

  return (
    <div>
      <div>Aticle</div>
      <div>
        type is：{type}，page is：{page}
      </div>
      <div>
        <Link to="/home">to Home</Link>
      </div>
    </div>
  );
}

export default Aticle;
```

```
// /src/router/index.tsx
// createBrowserRouter 是 history 模式，createHashRouter 是 hash 模式
import { createBrowserRouter, Navigate } from "react-router-dom";
import Home from "../pages/Home";
import About from "../pages/About";
import About1 from "../pages/About/child/About1";
import About2 from "../pages/About/child/About2";
import Profile from "../pages/Profile";
import Aticle from "../pages/Aticle";

const router = createBrowserRouter([
  // 默认路由写法一，重定向
  {
    path: '/',
    element: <Navigate to='/home' />
  },
  {
    path: '/home',
    element: <Home />,
  },
  // 嵌套路由
  {
    path: "/about",
    element: <About />,
    children: [
      // 默认路由写法二， index: true 设置默认路由，去掉 path
      {
        index: true,
        element: <About1 />,
      },
      {
        path: "about2",
        element: <About2 />,
      },
    ],
  },
  // 路由传参
  {
    path: "profile/:uid",
    element: <Profile />,
  },
  {
    path: "/aticle",
    element: <Aticle />,
  },
  // 404 路由
  {
    path: "*",
    element: <div>404</div>,
  },
]);

export default router;
```

```
// /src/App.tsx
import { RouterProvider } from "react-router-dom";
import router from "./router";

function App() {
  return (
    <div className="App">
      <div>header</div>
      <RouterProvider router={router}></RouterProvider>
      <div>footer</div>
    </div>
  );
}

export default App;
```

其他 Hooks ：

```
import {
  useMatch,
  useInRouterContext,
  useNavigationType,
  useOutlet,
  useResolvedPath,
} from "react-router-dom";

/* 路由对象三大属性
 * match，使用 useMatch 获取
 * history，用于跳转，用 useNavigate 获取
 * location，用 useLocation 获取
 */
function Home() {
  // 获取某个路由的 match 信息
  console.log(useMatch("/home"));

  // 判断该组件是否在 RouterProvider 组件内，返回布尔值哦
  console.log(useInRouterContext());

  // 判断是什么方式进入的该路由，返回 'POP' | 'PUSH' | 'REPLACE' ，'POP' 表示是刷新页面进入的路由
  console.log(useNavigationType());

  // 获取该路由的嵌套路由对象,没有或还未挂载就返回 null
  console.log(useOutlet());

  // 解析某个路由的 path 、search、hash
  console.log(useResolvedPath('/home'));

  return <div>Home</div>;
}
export default Home;
```

（2）方式二

React Router 6 早期的写法。

```
// /src/router/index.tsx
import { BrowserRouter, useRoutes, Navigate } from "react-router-dom";
import Home from "@/pages/Home";
import About from "@/pages/About";

const routes = [
  {
    path: "/",
    element: <Navigate to="/home" />,
  },
  {
    path: "/home",
    element: <Home />,
  },
  {
    path: "/about",
    element: <About />,
  },
];

// 因为 useRoutes 只能用在被 BrowserRouter Hu哦 HashRouter 的后代组件的函数体中，所以才多了这一层
function RoutesElement() {
  const element = useRoutes(routes);
  return <>{element}</>;
}

function RouterView() {
  return (
    <BrowserRouter>
      <RoutesElement />
    </BrowserRouter>
  );
}

export default RouterView;
```

```
// /src/App.js
import RouterView from "./router";

function App() {
  return (
    <div className="App">
      <div>header</div>
      <RouterView></RouterView>
      <div>footer</div>
    </div>
  );
}

export default App;
```

（3）方式三

React Router 6 之前老版本的用法，不推荐，这里只简单示例：

```
// /src/router/index.tsx
import { BrowserRouter, Routes, Route, Navigate } from "react-router-dom";
import Home from "@/pages/Home";
import About from "@/pages/About";

// 也可以将路由配置抽离成对象数组，再 map 遍历出来 <Route>
function RouterView() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Navigate to="/home" />}></Route>
        <Route path="/home" element={<Home />}></Route>
        <Route path="/about" element={<About />}></Route>
      </Routes>
    </BrowserRouter>
  );
}

export default RouterView;
```

```
// /src/App.js
import RouterView from "./router";

function App() {
  return (
    <div className="App">
      <div>header</div>
      <RouterView></RouterView>
      <div>footer</div>
    </div>
  );
}

export default App;
```

## 2 路由懒加载

使用：

```
// /src/router/index.tsx
import { lazy, Suspense } from "react";
import { createBrowserRouter, Navigate } from "react-router-dom";

// 懒加载
const Home = lazy(() => import("../pages/Home"));
const About = lazy(() => import("../pages/About"));

type LazyLoadPropsType = {
  children: React.React
Node;
};

// 需要 Suspense 包裹懒加载的组件，并指定 loading
function LazyLoad(props: LazyLoadPropsType) {
  return <Suspense fallback={<div>loading</div>}>{props.children}</Suspense>;
}

const router = createBrowserRouter([
  {
    path: "/",
    element: <Navigate to="/home" />,
  },
  {
    path: "/home",
    element: (
      <LazyLoad>
        <Home />
      </LazyLoad>
    ),
  },
  {
    path: "/about",
    element: (
      <LazyLoad>
        <About />
      </LazyLoad>
    ),
  },
]);

export default router;
```

## 3 导航守卫

React Router 并没有提供导航守卫，需要自己实现，社区中提供了一种解决方案，就是使用高阶组件（又叫HOC，能接收组件参数并返回组件的组件），示例：

```
// /src/components/AuthRoute/index.tsx
import { Navigate } from "react-router-dom";

type AuthRoutePropsType = {
  children: React.ReactNode;
};

/* 说明
 * 这里其实属于后置守卫了，所以 useLocation 可以获取 to 的路由
 * 没有办法获取 from 的路由，可以在需要 from 路由精选判断的时候，那个 from 路由跳转时传递参数
 * 如果需要其他参数进行判断，就传递 props 参数进来
 */
function AuthRoute(props: AuthRoutePropsType) {
  const token = localStorage.getItem("token");

  if (!token) return <Navigate to="/login"></Navigate>;
  else return <>{props.children}</>;
}

export default AuthRoute;
```

```
// /src/router/index.tsx
import { lazy, Suspense } from "react";
import { createBrowserRouter, Navigate } from "react-router-dom";
import AuthRoute from "@/components/AuthRoute";
const Home = lazy(() => import("@/pages/Home"));
const Login = lazy(() => import("@/pages/Login"));

const router = createBrowserRouter([
  {
    path: "/",
    element: <Navigate to="/home" />,
  },
  {
    path: "/home",
    element: (
      <Suspense fallback={<div>loading</div>}>
        <AuthRoute>
          <Home />
        </AuthRoute>
      </Suspense>
    ),
  },
  {
    path: "/login",
    element: (
      <Suspense fallback={<div>loading</div>}>
        <Login />
      </Suspense>
    ),
  },
]);

export default router;
```

## 4 动态修改路由

三种配置路由的方式中，方式一没找到动态修改路由的 API，方式三可以直接遍历路由配置生成路由组件。

这里用方式二，将 routes 定义成响应式的状态变量，通过 setRoutes 修改路由：

```
// /src/router/index.tsx
import { useState, useEffect } from "react";
import { BrowserRouter, useRoutes,Link } from "react-router-dom";

function useUpdateRoutes() {
  const [routes, setRoutes] = useState([
    {
      path: "/",
      element: <div>Home <Link to='/about'>to About</Link></div>,
    },
  ]);

  // 测试是否能够添加路由
  useEffect(() => {
    const timer = setTimeout(() => {
      console.log("开始添加路由");
      setRoutes([
        ...routes,
        {
          path: "/about",
          element: <div>about</div>,
        },
      ]);
    }, 5000);

    return () => clearTimeout(timer);
  }, []);

  return { routes, setRoutes };
}

function RoutesElement() {
  return <>{useRoutes(useUpdateRoutes().routes)}</>;
}

function RouterView() {
  return (
    <BrowserRouter>
      <RoutesElement />
    </BrowserRouter>
  );
}

export { useUpdateRoutes };

export default RouterView;
```
