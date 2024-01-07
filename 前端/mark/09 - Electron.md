# 一、基本

electron 可以开发 windows，mac，linux 桌面应用程序，核心是把 chrome 浏览器内核和 nodejs 结合。Vue 和 React 均可使用。

nodejs 作为主进程，可以使用 node 的 api 操作文件、获取系统信息等等；chrome 内湖作为渲染进程渲染页面。

使用：

vue + ts + vite 项目：

```
npx degit alex8088/electron-vite-boilerplate projectName
```

目录结构：

* /src/main：主进程

* /src/render：渲染进程

* /src/preload：使渲染进程可以使用主进程的 api ，实现他们之间的通信

根目录下创建 plugins 文件夹，并在里面创建 vite.electron.dev.ts 文件和 vite.electron.build.ts 文件，作用是在 pnpm run dev 的时候同时打开 electron 程序，不然只能用两个 shell ：

先在 tsconfig.node.json 配置 plugins 文件夹，获得代码提示：

```
{
  "include": ["其他...", "plugins/**/*.ts"]
}
```

配置 plugin ：





在 /src/background.ts 文件，写主进程代码：

# 二
