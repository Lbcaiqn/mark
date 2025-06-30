# 一、React

与 Vue 的不通电：

* 响应式系统不同，React 用 useState 定义状态，并需要手动 setXxx 才是响应式

* 异步更新不同，React 的异步更新是数据修改和 render 都是异步的；在 useEffect 中就能拿到最新数据，不用像 Vue 需要 nextTick 在微任务中获取

* 虚拟 DOM ，diff 算法 不同

* 没有 Vue 那么多语法糖，如列表、条件渲染、事件绑定等都更接近 JS 、更灵活，也没有 v\-model 这些语法糖

* 逻辑更几种，如 useEffect 就囊括各个生命周期

## 1 基本

创建：

```
# cli
npx create-react-app projectName

# vite
pnpm create vite
```

React 插件：

* chrome 浏览器插件： React Developer Tools 。

* vscode 插件：ES7+ React/Redux/React-Native snippet

组件库：ant-design 和 antd-mobile

cli 的入口是 index.js ，vite 的入口是 main.js。里面的严格模式标签笔试 es5 的严格模式，而是用来检查是否有 React 新版本弃用的特性，以作警告，开发时建议注释掉，检查时或生产环境再实用。

## 2 语法

（1）函数式组件

React 16.8 之后，使用函数式组件 \+ Hook：

```
pnpm add --savae classnames
```

```
/* /src/views/Home/index.css */

.box {
  background-color: #000;
}

.text {
  color: #fff;
}
```

```
// /src/context/index.tsx
import { createContext } from "react";
export const MyContext = createContext("default value");
```

```
// 子组件 /src/components/Cpn/index.tsx

import {
  useRef,
  forwardRef,
  useImperativeHandle,
  useContext,
  memo,
} from "react";
import { MyContext } from "/src/context";

// ---------------------------------------------------------------------------------------
interface Cpn1Props {
  msg: string;
  onSetMsg: (newMsg: string) => void;
  children?: React.ReactNode;
  myRender?: (msg: string) => React.ReactNode;
}

/**
 * 富川字、子传父都是 props
 * 默认插槽在 props.children ；具名插槽用 props 传入一个 render 函数
 */
export function Cpn1(props: Cpn1Props) {
  return (
    <>
      <div>
        <div>组件通信、插槽</div>
        <div>
          <button onClick={() => props.onSetMsg("qwer")}>{props.msg}</button>
        </div>
        {props.children}
        {props.myRender?.(props.msg)}
      </div>
    </>
  );
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
export interface Cpn2Ref {
  cpn2Current: HTMLDivElement | null;
  inpCurrent: HTMLInputElement | null;
  inputFocus: () => void;
}

// 子组件的资源需要 forwardRef + useImperativeHandle ，父组件才能获取
export const Cpn2 = forwardRef<Cpn2Ref>((props, ref) => {
  const cpn2Ref = useRef<HTMLDivElement | null>(null);
  const inpRef = useRef<HTMLInputElement | null>(null);

  function inputFocus() {
    inpRef?.current?.focus?.();
  }

  // 使用 useImperativeHandle 暴露自定义方法
  useImperativeHandle(ref, () => ({
    cpn2Current: cpn2Ref.current,
    inpCurrent: inpRef.current,
    inputFocus,
  }));

  return (
    <div ref={cpn2Ref}>
      <input type="text" ref={inpRef} {...props} />
    </div>
  );
});
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
function DeepComponentTest() {
  const val = useContext(MyContext);
  return <>{val}</>;
}

// 跨城组件通信
export function Cpn3(props) {
  return (
    <>
      {/* 方式一 */}
      {/* <DeepComponentTest {...props} /> */}

      {/* 方式二，使用 context */}
      <DeepComponentTest />
    </>
  );
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
interface MemoCpnProps {
  cnt?: number;
  arr?: number[];
  func?: Function;
}

// 缓存组件，只有 props 变化了才会重新 render ，底层用 Object.is() 判断
export const MemoCpn = memo((props: MemoCpnProps) => {
  console.log("memo cpn render");
  return <>memo cpn</>;
});
// ---------------------------------------------------------------------------------------
```

```
// 父组件 /src/views/Home/index.tsx

import {
  useState,
  useEffect,
  useReducer,
  useMemo,
  useCallback,
  useRef,
} from "react";

import { MyContext } from "/src/context";
import { Cpn1, Cpn2, Cpn3, MemoCpn } from "/src/components/Cpn";
import type { Cpn2Ref } from "/src/components/Cpn";

// svg 文件中就一个 svg 标签
import viteLogo from "/vite.svg";
// 一个组件一个 css
import classnames from "classnames";
import "./index.css";
// css module ，防止样式冲突，文件名必须有 .module
import HomeCls from "./index.module.css";

// 自定义 Hook ，hook 只能在 function 内使用
function useLazyEffect(
  effect: () => void | (() => void | undefined),
  dependencies: React.DependencyList,
  trigger: boolean
): void {
  // 用一个 boolean 状态控制 effect ，只有 true 时 effect 才会执行

  const hasTriggered = useRef(false);

  useEffect(() => {
    if (trigger) hasTriggered.current = true;
  }, [trigger]);

  useEffect(() => {
    if (hasTriggered.current) return effect();
  }, [effect, ...dependencies]);
}

// 函数式组件，就是一个 render 函数
function Home() {
  // undefined
  // console.log(this);

  // ----------------------------------------------------------------------------------
  // JSX 的变量可以是虚拟 DOM
  const title = "home";
  const myTitle = <div>tis is {title}</div>;

  // 事件函数
  type BtnClickEvent = React.MouseEvent<HTMLButtonElement>;

  const click1 = () => console.log("click1");
  const click2 = (e: BtnClickEvent) => console.log("click2", e);
  const click3 = (num: number) => console.log("click3", num);
  const click4 = (num: number, e: BtnClickEvent) => {
    console.log("click4", num, e);
  };
  // ----------------------------------------------------------------------------------

  // ----------------------------------------------------------------------------------
  /**状态变量，即响应式数据
   * 状态自身不可变，只能通过 setXxx 修改，且这样 react 才能监测到
   * react 会比较新旧值，只有变化了才重新 render
   * render 重新执行，状态的值会保持不变
   */
  const [count, setCount] = useState(0);
  // const [count, setCount] = useState(() => 0);

  const addTwo = () => {
    setCount(count + 2);

    // 完整写法
    // setCount((count) => {
    //   return count + 1;
    // });

    // 无法得到最新值，因为 setXxx 是异步的，但 setXxx 不返回 Promise ，可以用 useEffect 解决
    // console.log(count)
  };

  // 引用类型的状态
  const [list, setList] = useState([
    { id: "1", text: "a" },
    { id: "2", text: "b" },
    { id: "3", text: "c" },
  ]);
  const [obj, setObj] = useState({ name: "asdf", age: 18 });

  // 必须传入新的引用
  const addList = () => setList([...list, { id: "4", text: "d" }]);
  const updateList = () => {
    const newList = [...list];
    newList[0].text = "aaa";
    setList(newList);
  };
  const updateObj = () => setObj({ ...obj, name: "qwer" });

  // 缓存状态，类似 Vue 的 computer
  const doubleCount = useMemo(() => count * 2, [count]);

  // 获取 DOM
  const cntRef = useRef<HTMLButtonElement | null>(null);

  // 生命周期，一个 Hook 多个用途，若依赖项为 undefine ，则默认依赖所有状态
  useEffect(() => {
    // 类似于 Vue 的 mounted、updated、watch ，这些阶段就会回调
    // 不需要 nextTick
    console.log(count, cntRef.current!.innerText);

    // return () => {
    //   // 类似于 beforeUnMount
    //   console.log("unMounted");
    // };
  }, [count, cntRef]);
  // ----------------------------------------------------------------------------------

  // ----------------------------------------------------------------------------------
  // 若状态的修改有很多，可以封装成 reducer
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
        return state + action.payload!;
      default:
        return state;
    }
  }

  const [cnt, cntDispatch] = useReducer(countReducer, 0);
  // ----------------------------------------------------------------------------------

  // ----------------------------------------------------------------------------------
  // 表单，没有 v-model，表单的事件都是 onChange
  const [str, setStr] = useState("abc");
  function changeStr(e: React.ChangeEvent<HTMLInputElement>) {
    setStr(e.target.value);
  }
  // ----------------------------------------------------------------------------------

  // ----------------------------------------------------------------------------------
  // 获取子组件的资源
  // const cpn1Ref = useRef(null)
  const cpn2Ref = useRef<Cpn2Ref | null>(null);

  useEffect(() => {
    // null
    // console.log(cpn1Ref.current)

    // 正常获取
    console.log(cpn2Ref.current!.cpn2Current);
    cpn2Ref.current!.inputFocus();
  }, [cpn2Ref]);

  // 组件通信
  const [msg, setMsg] = useState("aaa");
  const onSetMsg = (newMsg: string) => setMsg(newMsg);

  // 插槽
  const childrenPropsSlot = <h1>默认插槽</h1>;
  const renderPropsSlot = (msg: string) => {
    console.log("作用域插槽", msg);
    return <h1>具名插槽</h1>;
  };
  // ----------------------------------------------------------------------------------

  // ----------------------------------------------------------------------------------
  /**缓存组件，只有 props 变化才会重新 render
   * useState 的状态：
     - 父组件重新 render ，状态自身引用不变，缓存组件只看状态的值是否变化
   * 非 useState 定义的状态：
     - 基本类型父组件 render 后变回初始值，引用类型是新引用
     引用类型可以用 useMemo 、useCallback 缓存，使引用不变
   */
  let num = 0;
  setTimeout(() => (num = 100));

  const arr = [1, 2];
  const func = () => {};

  const [stateArr] = useState([1, 2]);

  // 缓存数据，根据需要传入依赖项
  const memoArr = useMemo(() => {
    return [1, 2];
  }, []);

  // 缓存一个 function ，依赖项一般不需要，因为 function 一般都不需要变
  const memoFunc = useCallback(() => {}, []);
  // ----------------------------------------------------------------------------------

  return (
    /**需要根节点，可以使 <></> 桌 <Fragment></Fragment> ，都不会被渲染，只作包裹作用
     * 空变迁 <></> 不能有任何属性
     * Fragment 需要从 react 导入，可以用 key 属性
     * 复杂的结构可以用小括号 () 包裹，更清晰
     */
    <>
      {/* 用 {} 使用 JS 表达式，与 Vue 不一样的是 reactve 不能直接 {obj} ，会报错 */}
      {myTitle}

      {/* 样式，为了和原生 HTML 区分，用 className 代替 class */}
      <div style={{ margin: "50px 0", border: "1px solid #000" }}>
        <div className="box" style={{ color: "#fff" }}>
          box1
        </div>

        <div className="box text">box2</div>
        <div className={`box ${true && "text"}`}>box3</div>

        <div className={classnames({ box: true, text: true })}>box4</div>

        <div className={`${HomeCls.box} ${HomeCls.text}`}>box5</div>
      </div>

      {/* 列表渲染 */}
      <button onClick={addList}>add list</button>
      <button onClick={updateList}>update list</button>
      <ul>
        {list.map((item, itemIndex) => (
          <li key={item.id}>
            {itemIndex} {item.text}
          </li>
        ))}
      </ul>

      {/* 条件渲染，类似 v-if ，没有 v-show 可以设置样式实现 */}
      {true && <p>if...else</p>}
      {true ? <p>if</p> : <p>else</p>}

      {/* 事件绑定，为了和原生 HTML 区分，用 onClick 代替 onclick */}
      <div>
        <button onClick={click1}>click1</button>
        <button onClick={click2}>click2</button>
        <button onClick={() => click3(123)}>click3</button>
        <button onClick={(e: BtnClickEvent) => click4(456, e)}>click4</button>
      </div>

      {/* 状态 */}
      <div style={{ margin: "20px 0" }}>
        <button onClick={() => setCount((count) => count + 1)}>
          count is {count}
        </button>

        <button ref={cntRef} onClick={addTwo}>
          {count}
        </button>

        <span>useMemo: doubleCount {doubleCount}</span>
      </div>
      <div style={{ margin: "20px 0" }}>
        <button onClick={updateObj}>objName {obj.name}</button>
      </div>

      {/* 表单 */}
      <div style={{ margin: "20px 0" }}>
        <input type="text" value={str} onChange={changeStr} />
        <span>{str}</span>
      </div>

      {/* reducer */}
      <div style={{ margin: "20px 0" }}>
        <button onClick={() => cntDispatch({ type: "INC" })}>
          inc cnt {cnt}
        </button>
      </div>

      {/* svg */}
      <div>
        <img src={viteLogo} />
      </div>

      {/* 子组件 */}
      <div style={{ margin: "20px 0" }}>
        {/* <Cpn1 ref={cpn1Ref} /> */}
        <Cpn2 ref={cpn2Ref} />
      </div>

      {/* 组件通信、插槽 */}
      <div style={{ margin: "20px 0", border: "1px solid #000" }}>
        <Cpn1 msg={msg} onSetMsg={onSetMsg} myRender={renderPropsSlot}>
          {childrenPropsSlot}
        </Cpn1>

        <MyContext.Provider value={"my context"}>
          <Cpn3 />
        </MyContext.Provider>
      </div>

      {/* 缓存组件 */}
      <div style={{ margin: "20px 0", border: "1px solid #000" }}>
        {/* 基本类型就算改了，重新 render 也是初始值，值不变，所以 MemoCpn 就缓存了 */}
        {/* <MemoCpn cnt={num} /> */}

        {/* 父组件重新 render ，arr 和 func 都是新的引用，props 改变，MemoCpn 重新 render */}
        {/* <MemoCpn cnt={num} arr={arr} func={func} /> */}

        {/* useState 的数据，引用不变，看值是否变化 */}
        {/* <MemoCpn arr={stateArr} /> */}

        <MemoCpn arr={memoArr} func={memoFunc} />
      </div>
    </>
  );
}

export default Home;
```

（2）类组件

React 16.8 以前的语法：

```
import { Component } from "react";

export class Son extends Component {
  render() {
    return (
      <button onClick={this.props.addCnt}>add cnt {this.props.cnt}</button>
    );
  }
}

export default class Home extends Component {
  state = {
    msg: "hello",
    cnt: 0,
  };

  // 函数
  addCnt = () => {
    // 修改引用类型需要传入新的引用，如 [...arr, 123] ，对象有语法糖可以只传一个需要修改的属性
    this.setState(
      // 也可以是函数形式
      {
        cnt: this.state.cnt + 1,
      },

      // 相当于 useEffect 中获取最新状态
      () => {
        console.log(this.state.cnt);
      }
    );
  };

  // 生命周期钩子
  // constructor() {}
  // componentWillMount() {}
  // componentDidMount() {}
  // render() {}
  // componentWillReceiveProps() {}
  // shouldComponentUpdate() {}
  // componentWillUnmount() {}
  // componentDidUpdate() {}
  // componentWillUnmount() {}

  render() {
    return (
      <>
        <Son cnt={this.state.cnt} addCnt={this.addCnt} />
      </>
    );
  }
}
```

## 3 React Router 6

```
pnpm add --save react-router-dom
```

### 3.1 使用

（1）方式一

```
// /src/router/index.tsx

/*模式*
 * createBrowserRouter 是 history 模式
 * createHashRouter 是 hash 模式
 */
import { createBrowserRouter, Navigate } from "react-router-dom";
import Home from "/src/views/Home";
import Profile from "/src/views/Profile";

// 路由懒加载 -------------------------------------------------------------------------
import { lazy, Suspense } from "react";
const About = lazy(() => import("/src/views/About"));
const AboutSon1 = lazy(() => import("/src/views/About/child/AboutSon1"));
const AboutSon2 = lazy(() => import("/src/views/About/child/AboutSon2"));

// 自定义 loading 组件
function LazyLoad(props: { children: React.ReactNode }) {
  return <Suspense fallback={<div>loading</div>}>{props.children}</Suspense>;
}
// -----------------------------------------------------------------------------------

const router = createBrowserRouter([
  // 默认路由
  {
    path: "/",
    element: <Navigate to="/home" />,
  },

  // 路由
  {
    path: "/home",
    element: <Home />,
  },

  // 嵌套路由
  {
    path: "/about",
    element: (
      <LazyLoad>
        <About />
      </LazyLoad>
    ),
    children: [
      // 默认路由
      {
        index: true,
        element: (
          <LazyLoad>
            <AboutSon1 />
          </LazyLoad>
        ),
      },

      // 路由
      {
        path: "son2",
        element: (
          <LazyLoad>
            <AboutSon2 />
          </LazyLoad>
        ),
      },
    ],
  },

  // 传参
  {
    path: "profile/:uid",
    element: <Profile />,
  },

  // 404
  {
    path: "*",
    element: <div>404</div>,
  },
]);

export default router;
```

```
// /src/App.tes

import { RouterProvider } from "react-router-dom";
import router from "./router";

function App() {
  return (
    <>
      <RouterProvider router={router} />
    </>
  );
}

export default App;
```

```
// /src/views/Home/index.tsx

import { Link, useNavigate } from "react-router-dom";

function Home() {
  const navigate = useNavigate();

  function toProfile() {
    // replace 默认为 false
    navigate("/profile/123", { replace: false, state: { a: 1, b: 2 } });

    // 前进后退
    // navigate(1);
    // navigate(-1);
  }

  return (
    <>
      <p>Home</p>

      <ul>
        <li>
          <Link to="/about">to About son 1</Link>
          {"  --- "}
          <Link to="/about/son2">to About son 2</Link>
        </li>

        <li>
          <button onClick={() => navigate("/about/son2")}>
            to About son 2
          </button>
        </li>
      </ul>

      <ul>
        <li>
          <Link to="/profile/123?a=1&b=2">to Prolfie 1</Link>
          {"  --- "}
          <Link to="/profile/123" state={{ a: 1, b: 2 }}>
            to Prolfie 1
          </Link>
        </li>

        <li>
          <button onClick={toProfile}>to Profile</button>
        </li>
      </ul>
    </>
  );
}

export default Home;
```

```
// /src/views/Profile/index.tsx

import { useParams, useSearchParams, useLocation } from "react-router-dom";

function Profile() {
  /**path、参数等信息
   * 参数有 3 种，params、search、state
   * params 、search 直接通过 path 传入
   * state 参数通过 state 配置项传入
   */
  const { uid } = useParams();

  const [search, setSearch] = useSearchParams();
  const searchA = search.get("a");
  const searchB = search.get("b");

  const loc = useLocation();
  const { pathname, state } = loc;
  const stateA = state?.a;
  const stateB = state?.b;

  return (
    <div>
      <p>Profile</p>

      <p>{`params: ${uid}`}</p>
      <p>{`search: ${searchA} ${searchB}`}</p>
      <p>{`state: ${stateA} ${stateB}`}</p>

      <p>{`pathname: ${pathname}`}</p>
    </div>
  );
}

export default Profile;
```

```
// /src/views/About/index.tsx

import { Outlet } from "react-router-dom";

function About() {
  return (
    <>
      <p>About</p>
      <Outlet />
    </>
  );
}

export default About;
```

```
// /src/views/About/child/AboutSon1/index.tsx

import {
  useMatch,
  useInRouterContext,
  useNavigationType,
  useOutlet,
  useResolvedPath,
} from "react-router-dom";

function AboutSon1() {
  // 获取某个路由的 match 信息
  console.log(useMatch("/about"));

  // 判断该组件是否在 RouterProvider 组件内，返回布尔值哦
  console.log(useInRouterContext());

  // 判断是什么方式进入的该路由，返回 'POP' | 'PUSH' | 'REPLACE' ，'POP' 表示是刷新页面进入的路由
  console.log(useNavigationType());

  // 获取该路由的嵌套路由对象,没有或还未挂载就返回 null
  console.log(useOutlet());

  // 解析某个路由的 path 、search、hash
  console.log(useResolvedPath("/home"));

  return <>about son 1</>;
}

export default AboutSon1;
```

（2）方式二

React Router 6 早期的写法：

```
// /src/router/index.tsx

import { BrowserRouter, useRoutes, Navigate } from "react-router-dom";
import Home from "/src/views/Home";

const routes = [
  {
    path: "/",
    element: <Navigate to="/home" />,
  },
  {
    path: "/home",
    element: <Home />,
  },
];

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
// /src/App.tes

import RouterView from "./router";

function App() {
  return (
    <>
      <RouterView></RouterView>
    </>
  );
}

export default App;
```

（3）方式三

React Router 6 之前老版本的用法，不推荐，这里只简单示例：

```
// /src/router/index.tsx

import { BrowserRouter, Routes, Route, Navigate } from "react-router-dom";
import Home from "/src/views/Home";

function RouterView() {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Navigate to="/home" />}></Route>
        <Route path="/home" element={<Home />}></Route>
      </Routes>
    </BrowserRouter>
  );
}

export default RouterView;
```

```
// /src/App.tes

import RouterView from "./router";

function App() {
  return (
    <>
      <RouterView></RouterView>
    </>
  );
}

export default App;
```

### 3.2 导航守卫

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

### 3.3 动态修改路由

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

## 4 全局状态管理

### 4.1  Redux

React 最流行的状态管理工具。

Redux 调试工具：chrome 浏览器插件 Redux DevTools

React 使用 Redux 需要两个插件：

* @reduxjs/toolkit（RTK），官方推荐的编写 Redux 逻辑的方式，简化原生 Redux 的写法。RKT 也有一套现成的工具。

* react\-redux，react 接入 redux 之间的中间件。

（1）使用

```
pnpm add --save @reduxjs/toolkit react-redux
```

```
pnpm add --save redux-persist redux-thunk
```

```
// /src/main.tsx
// ...
import store from "./store";
import { Provider } from "react-redux";

createRoot(document.getElementById("root")!).render(
  <StrictMode>
    <Provider store={store}>
      <App />
    </Provider>
  </StrictMode>
);
```

持久化

之前使用异步 action 能正常使用，但如果持久化还需要异步 action 就需要中间件 redux-thunk：

（2）原生写法

上面的例子是简化的写法，这里是原生的写法，原生比较繁琐，但可以理解 redux 的设计理念。

创建一个 stiore 管理状态，每次状态修改需要 dispatch 一个 action 通知 store 修改状态，store 根据 reducer 做对应的操作，最后 store 通过 subscribe 通知 react 重新 render 。

```
pnpm add --save redux redux-thunk react-redux
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

### 4.2 Zustand

代码比 Redux 简洁很多。

```
pnpm add --save zustand
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
