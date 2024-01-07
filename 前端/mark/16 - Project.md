# 一、项目开发规范

## 1 开发工具

编辑器：vscode，微信开发者工具，HBuildX，代码缩进2个空格

vscode快捷键

```
！+  tab：生成基本骨架
ctrl + + ctrl + -：放大缩小字体
标签名 + tab或者回车：生成双标签
标签名*n + tab或者回车：生成n个相同双标签
鼠标定到某行可以只复制一行
鼠标定到某行，ctrl  +  /：注释和取消注释当前行
标签>标签 + tab：生成包含     标签+标签 + tab：生成并列
标签名.类名 + tab：生成该类名的标签，不加标签默认为div
标签名#id名 + tab：生成该id名的标签，不加标签默认为div
.类名$*n：生成连续类名      标签名{文本}：生成包含文本的标签，文本为$则生成连续数字
CSS可以缩写+tab生成                shift+alt+F：格式化代码
```

其他：浏览器，snipaster，phontoshop，cmder，marktext

操作系统：

目前大量的库，js语法等，在win7支持的最高node版本13.14.0已经不支持，需要更高版本的系统。

vue谷歌浏览器调试工具：vue.js devtools，vue2和vue3使用的版本不一样，为了避免冲突，使用时只保留一个，禁用另一个。

vscode插件：

（1）代码格式化：prettier

能够格式化html，css，js，ts，vue等代码

（2）vue语法、代码提示插件

vetur：vue2使用

volar：vue3使用

为了避免冲突，使用时只保留一个，禁用另一个。

## 2 HTML/CSS/JS规范：

代码缩进：2

Web标准：结构（HTML），表现（CSS），行为（Javascript）

- HTML尽量用语义化标签替代div，属性使用双引号，若属性很多可以换行
  
  ```
  <div 
    aaa="xx" 
    bbb="xxx"
  > 
  </div>
  ```

- css属性按规范的顺序书写，css3中属性值小数0.5可写.5，css属性顺序：display=定位-盒子-文本-文
  
  字-背景-C3

- js字符串使用双引号，每个语句结尾加分号（加了分号避免不必要的错误，尤其是ts）

## 3 各种命名规范

HTML本身没有驼峰标识（标签名、属性无法识别大写，但是属性的值可以），脚手架才会有

css，js，ts都有驼峰标识

* 无驼峰标识的情况下，HTML属性，组件名组件标签，以xxx-yyy命名，有驼峰标识了也尽量使用 xxx-yyy的形式，css类名id名也常用xxx-yyy命名

* js，ts驼峰命名法：变量/函数/对象小驼峰，构造函数/类/接口/组件/大驼峰

* js、ts变量只能用数字、字母、下划线、$命名，且不能数字开头，也不能用-命名，组件标签以xxx-yyy命名时，注意js不能用-命名。

* 子组件以views组件名开头（如HomeMain.vue），hook函数useXXX

## 4 运算符、符号规范

运算符左右两边空一格：

```
let a = 5 + 7;
```

逗号，冒号后空一格：

```
let a = [123, 456];
let b = {a: 123};
```

## 5 Vue最佳实践

（1）风格指南：https://vuejs.org/style-guide/

（2）导航栏-文档-深度指南-最佳实践

## 6 Vue目录结构规范：

```
src
  assets
    img
    style
  common        本项目公用的js文件
    components  公共组件
    common    可以在别的项目用的组件
    content   只能在本项目用的组件
  views       各个页面独立的组件
  router
  store
  network
  App.vue
  main.js
...
package.json
vue.config.js
tsconfig.json
```

webpack和vite的index.html位置不同。

assets和public同样都是存放静态资源，区别是：

* assets中的静态资源build后，会打包处理再放到dist中，如压缩、优化等

* pubilc中的静态资源不会被打包，而是直接复制到dist根目录中，这里说的不会被打包指的是不会做压缩、优化等处理，但是像babel、loader等这些还是会起作用的。
  
  public适合放一些全局样式，icon，全局背景图等这些比较重要的静态资源，保证万无一失的使用，若项目中要引入public的资源：
  
  ```
  // 例如 public 下的 123.jpg
  <img src="/123.jpg" />
  ```

## 7 开发前的项目配置

### 7.1 代码规范

用户代码片段是方便款速创建模板的。

eslint是检查可能出现的逻辑错误和约束代码风格，以及简单的格式化代码的。

stylelint是css版的eslint。

prettier是强大的格式化代码的。

#### 7.1.1 用户代码片段

vscode-文件-首选项-配置用户代码片段-vue-json

```
{
    "Print to console": {
        "prefix": "vue3ts",
        "body": [
            "<script setup lang='ts'>\n",
            "</script>\n",
                        "<template>\n",
            "</template>\n",
            "<style lang='less' scoped>\n",                       
            "</style>",
            "$2"
        ],
        "description": "vueInit"
    }
}
```

这样在.vue文件中，输入vue3ts回车就能生成模板。

#### 7.1.2 prettier

```
npm install -D prettier eslint-plugin-prettier eslint-config-prettier
```

项目下创建 .prettierrc.cjs，也可以是无后缀，json，js，cjs，mjs文件，以 .prettierrc.cjs 为例：

注意：eslint，stylelint的风格和prettier的风格配置必须一样，否则会出现冲突。

```
module.exports = {
  // 2缩进
  tabWidth: 2,

  // 每行最多有几个字符
  printWidth: 120,

  // 换行符为 lf
  endOfLine: "lf",

  //使用双引号
  singleQuote: false,

  // 结尾加分号
  semi: true,

  // 对象花括号周围加空格
  bracketSpacing: true,

  // 忽略 html 的空格
  htmlWhitespaceSensitivity: "ignore",

  // 去掉对象最后一个属性后的逗号
  trailingComma: "none",

  // 箭头函数若参数只有一个就省略括号
  arrowParens: "avoid"
};
```

prettier忽略文件 .prettierignore

```
/dist/*
/html/*
.local
/node_modules/**
**/*.svg
**/*.sh
/public/*
```

格式化代码：

```
npx prettier --write xxx.js
```

package.json 配置运行脚本；

```
"scripts": {
    "format": "prettier --write \"./**/*.{html,vue,ts,js,json,md}\"",
}
```

当然每次格式化都要执行命令非常麻烦，因此可以安装vscode的插件prettier，并且设置保存自动格式化为prettier。

prettier插件有默认的格式化规则，vsocde也可以配置规则，但自定义的配置文件会覆盖默认的规则或vscode配置的规则。

#### 7.1.3 eslint

eslint会检查一些代码中可能出现的逻辑错误，以及约束代码风格。

```
npm install --D eslint
```

相关插件：

```
npm install -D eslint-plugin-import eslint-plugin-vue eslint-plugin-node eslint-plugin-prettier eslint-config-prettier eslint-plugin-node @babel/eslint-parser
```

初始化生成 .eslintrc.cjs：

```
npx eslint --init
```

配置参考：

```
module.exports = {
  // 运行环境和导入导出规范，js版本
  env: {
    browser: true,
    es2021: true,
    node: true,
    jest: true
  },

  // 指定如何解析语法
  parser: "vue-eslint-parser",

  // 优先级低于 parse 的语法解析配置
  parserOptions: {
    ecmaVersion: "latest",
    sourceType: "module",
    parser: "@typescript-eslint/parser",
    jsxPragma: "React",
    ecmaFeatures: {
      jsx: true
    }
  },

  // 继承已有的推荐eslint规则，也可以设置vue等框架的eslint插件。一个值就用字符串，多个值就放到数组中
  extends: [
    "eslint:recommended",
    "plugin:vue/vue3-essential",
    "standard-with-typescript",
    "plugin:@typescript-eslint/recommended"
  ],

  // 插件
  plugins: ["vue", "@typescript-eslint"],

  /* 额外自定义的规则
   * "off" 或 0    ==>  关闭规则
   * "warn" 或 1   ==>  打开的规则作为警告（不影响代码执行）
   * "error" 或 2  ==>  规则作为一个错误（代码不能执行，界面报错）
   * ["error或warn", config] ==> 额外配置更多选项
   */
  rules: {
    // eslint（https://eslint.bootcss.com/docs/rules/）
    quotes: ["error", "double", { avoidEscape: true, allowTemplateLiterals: true }], // 双引号和反引号包裹字符串
    semi: ["error", "always"], // 结尾加分号
    "space-before-function-paren": ["error", "never"], // 函数名和括号之间没有空格
    "no-var": "error", // 要求使用 let 或 const 而不是 var
    "no-multiple-empty-lines": ["warn", { max: 1 }], // 不允许多个空行
    "no-console": process.env.NODE_ENV === "production" ? "error" : "off",
    "no-debugger": process.env.NODE_ENV === "production" ? "error" : "off",
    "no-unexpected-multiline": "error", // 禁止空余的多行
    "no-useless-escape": "off", // 禁止不必要的转义字符

    // typeScript (https://typescript-eslint.io/rules)
    "@typescript-eslint/no-unused-vars": "error", // 禁止定义未使用的变量
    "@typescript-eslint/prefer-ts-expect-error": "error", // 禁止使用 @ts-ignore
    "@typescript-eslint/no-explicit-any": "off", // 禁止使用 any 类型
    "@typescript-eslint/no-non-null-assertion": "off",
    "@typescript-eslint/no-namespace": "off", // 禁止使用自定义 TypeScript 模块和命名空间。
    "@typescript-eslint/semi": "off",

    // eslint-plugin-vue (https://eslint.vuejs.org/rules/)
    "vue/multi-word-component-names": "off", // 要求组件名称始终为 “-” 链接的单词
    "vue/script-setup-uses-vars": "error", // 防止<script setup>使用的变量<template>被标记为未使用
    "vue/no-mutating-props": "off", // 不允许组件 prop的改变
    "vue/attribute-hyphenation": "off" // 对模板中的自定义组件强制执行属性命名样式
  }
};
```

eslint忽略文件：

可以在eslint配置文件中配置项 "ignorePatterns" 配置，也可以单独创建 .eslintignore 文件

```
dist
node_modules
```

在代码中也可以临时修改规则：

```
/* eslint no-console: 0  */
console.log(123);
```

检查：

```
npx eslint xxx.js
```

修复：

只能修复简单的代码风格，如双引号，分好这种对代码运行结果没有影响的，像console.log这种就无法修复，甚至连缩进也不会管。

逻辑错误无法修复，需要自己修改。

```
npx eslint xxx.js --fix
```

也可以在 package.json 中添加一个script，以便于更容易地运行ESLint：

```
"scripts": {
    "eslint": "eslint src",
    "eslint:fix": "eslint src --fix",
    "eslint:lint-and-fix": "eslint src/**/*.{ts,vue} --cache --fix"
}
```

最后，每次执行这个命令进行检查非常麻烦，因此可以安装vscode插件eslint，直接在编辑器报错。

eslint'插件有默认的规则，vscode中也可以配置规则，但自定义的eslintrc文件的配置会覆盖插件的规则或vscode的配置规则。

#### 7.1.4 stylelint

css版的eslint

根据项目使用的css预处理器安装对应的包：

less：

```
npm install -D less less-loader stylelint postcss postcss-less postcss-html stylelint-config-prettier stylelint-config-recess-order stylelint-config-recommended-less stylelint-config-standard stylelint-config-standard-vue stylelint-less stylelint-order stylelint-config-standard-less
```

sass：

```
npm install -D sass sass-loader stylelint postcss postcss-scss postcss-html stylelint-config-prettier stylelint-config-recess-order stylelint-config-recommended-scss stylelint-config-standard stylelint-config-standard-vue stylelint-scss stylelint-order stylelint-config-standard-scss
```

创建配置文件 .stylelintrc.cjs

```
// @see https://stylelint.bootcss.com/

module.exports = {
  // 继承已有的推荐配置
  extends: [
    "stylelint-config-standard", // 配置stylelint拓展插件
    "stylelint-config-html",
    "stylelint-config-standard-less", // 配置stylelint scss插件
    "stylelint-config-recess-order", // 配置stylelint css属性书写顺序插件,
    "stylelint-config-prettier" // 配置stylelint和prettier兼容
  ],

  // 语法解析器
  overrides: [
    {
      files: ["**/*.(scss|css|vue|html)"],
      customSyntax: "postcss-less"
    },
    {
      files: ["**/*.(html|vue)"],
      customSyntax: "postcss-html"
    }
  ],

  //忽略的文件
  ignoreFiles: ["**/*.js", "**/*.jsx", "**/*.tsx", "**/*.ts", "**/*.json", "**/*.md", "**/*.yaml"],

  /* 自定义规则
   * null  => 关闭该规则
   * always => 必须
   */
  rules: {
    "value-keyword-case": null, // 在 css 中使用 v-bind，不报错
    "no-descending-specificity": null, // 禁止在具有较高优先级的选择器后出现被其覆盖的较低优先级的选择器
    "function-url-quotes": "always", // 要求或禁止 URL 的引号 "always(必须加上引号)"|"never(没有引号)"
    "no-empty-source": null, // 关闭禁止空源码
    "selector-class-pattern": null, // 关闭强制选择器类名的格式
    "property-no-unknown": null, // 禁止未知的属性(true 为不允许)
    "block-opening-brace-space-before": "always", //大括号之前必须有一个空格或不能有空白符
    "value-no-vendor-prefix": null, // 关闭 属性值前缀 --webkit-box
    "property-no-vendor-prefix": null, // 关闭 属性前缀 -webkit-mask
    "selector-pseudo-class-no-unknown": [
      // 不允许未知的选择器
      true,
      {
        ignorePseudoClasses: ["global", "v-deep", "deep"] // 忽略属性，修改element默认样式的时候能使用到
      }
    ]
  }
};
```

stylelint忽略文件 .stylelintignore

```
/node_modules/*
/dist/*
/html/*
/public/*
```

package.json 配置运行脚本：

```
"scripts": {
    "stylelint": "stylelint src",
    "stylelint:fix": "stylelint src --fix",
    "stylelint:lint-and-fix": "stylelint src/**/*.{css,scss,vue} --cache --fix"
}
```

安装vscode插件 stylelint

#### 7.1.5 换行符问题

在unix，linux，mac等系统换行符是LF，而windows换行符是LF和CRLF，在windows使用eslint的时候就会有一个 ‘Delete `␍` eslint(prettier/prettier)’ 的警告，虽然实际使用上可能没有问题，但是为了消除eslint的警告和严谨的编码，就需要处理这个问题：

1. vscode下方菜单栏中点击 'CRLF' 选择 “LF‘，就可以把当前文件的所有换行符换成 ”LF’，但是治标不治本

2. git中全局配置：
   
   ```
   git config --global core.autocrlf false
   ```

3. vscode-首选项-设置-搜索 'files.eol' -选择 “\n‘。（ \n 就是 LF，\r\n 就是 CRLF）

4. .prettierrc
   
   ```
   {
     "endOfLine": "lf"
   }
   ```

5. .editorconfig
   
   ```
   [*]
   end_of_line = lf
   ```

执行以上步骤后就基本能解决问题，每次新建文件时只要保存，就会根据prettierrc将换行符换成LF。

不过注意vscode是一定要设置的，否则pretttierrc怎么配置都不行。

### 7.2 git提交规范

#### 7.2.1 git 忽略文件

.gitignore 忽略提交的文件，如：

```
.DS_Store
node_modules/
dist/
npm-debug.log*
yarn-debug.log*
yarn-error.log*
package-lock.json
tests/**/coverage/

# Editor directories and files
.idea
.vscode
*.suo
*.ntvs*
*.njsproj
*.sln
```

#### 7.2.2 husky

可以配置git钩子 pre-commit ，在 git commit 之前触发，可以在这里做代码的格式化，保证提交的代码都是格式化好的。

```
npm install -D husky
```

执行，执行之前确保项目已经有 .git 文件夹，没有就 git init

```
npx husky-init
```

会在根目录下生成个一个.husky目录，在这个目录下面会有一个pre-commit文件，这个文件里面的命令在我们执行commit的时候就会执行

在`.husky/pre-commit`文件添加如下命令：

```
#!/usr/bin/env sh
. "$(dirname -- "$0")/_/husky.sh"
npm run format

# 因为格式化后试一次新的修改，而之前add在暂存区的代码还是未修改的，所以这里需要再次add新的修改
git add .
```

当我们对代码进行commit操作的时候，就会执行命令，对代码进行格式化，然后再提交。

#### 7.2.3 commitlint

规范 git commit 的提交信息。

```
npm install -D @commitlint/config-conventional @commitlint/cli
```

根目录添加配置文件，新建`commitlint.config.cjs`(注意是cjs)，然后添加下面的代码：

```
module.exports = {
  extends: ["@commitlint/config-conventional"],
  // 校验规则
  rules: {
    "type-enum": [
      2,
      "always",
      ["feat", "fix", "docs", "style", "refactor", "perf", "test", "chore", "revert", "build"]
    ],
    "type-case": [0],
    "type-empty": [0],
    "scope-empty": [0],
    "scope-case": [0],
    "subject-full-stop": [0, "never"],
    "subject-case": [0, "never"],
    "header-max-length": [0, "always", 72]
  }
};
```

在`package.json`中配置scripts命令

```
# 在scrips中添加下面的代码
{
"scripts": {
    "commitlint": "commitlint --config commitlint.config.cjs -e -V"
  },
}
```

配置husky

```
npx husky add .husky/commit-msg 
```

在生成的commit-msg文件中添加下面的命令

```
#!/usr/bin/env sh
. "$(dirname -- "$0")/_/husky.sh"
npm run commitlint
```

配置完成，提交的信息举例：

```
'feat',//新特性、新功能
'fix',//修改bug
'docs',//文档修改
'style',//代码格式修改, 注意不是 css 修改
'refactor',//代码重构
'perf',//优化相关，比如提升性能、体验
'test',//测试用例修改
'chore',//其他修改, 比如改变构建流程、或者增加依赖库、工具等
'revert',//回滚到上一个版本
'build',//编译相关的修改，例如发布版本、对项目构建或者依赖的改动
```

提交信息格式是 `xxx: 信息`

```
git commit -m "chore: 提交信息"
```

### 7.3 配置脚手架或 vite

如果是ts环境，需要：

```
npm install -D @types/node
npm install --save path
```

#### 7.3.1 Vue

vue-cli：

vue.config.js

```
const path = require('path');

module.exports = {
  productionSourceMap: false,
  configureWebpack: {
    resolve: {
      alias: {
        '@': path.resolve(__dirname, 'src'),
      },
      extensions: ['.ts', '.json', '.vue', '.less']
    }
  },
  devServer: {
    proxy: {
      //...
    }
  }
  plugins: [
    require('@vitejs/plugin-vue')()
  ]
};
```

vite：

vite.config.js

```
# 这个插件可以配置一些变量，用在 index.html 中，比如配置标题
pnpm install -D vite-plugin-html
```

```
import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import { createHtmlPlugin } from "vite-plugin-html"
import path from "path"

// https://vitejs.dev/config/
export default defineConfig({
  build: {
    sourcemap: false
  },
  plugins: [
    vue(),
    createHtmlPlugin({
      minify: true,
        inject: {
          data: {
            /* 在 index.html 中使用类似插值语法，如：
               <head>
                 <title><%- title %><title/>
                 <%- xxx %>
               </head>
             会解析为：
             <head>
                 <title>asdf<title/>
                 <script>...</script>
               </head>
             */
            title: "asdf",
            xxx: `<script>...</script>`
          }
        }
      }),
    ],
    resolve: {
    alias: {
      '@': path.resolve(__dirname, 'src')
    },
    extensions: ['.ts', '.json', '.vue', '.less'] // 指定可省略的扩展名
  },
  server: {
    proxy: {
      //...
    }
  }
})
```

#### 7.3.2 React

vite：

vite.config.ts：

```
import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import path from "path";

export default defineConfig({
  plugins: [react()],
  resolve: {
    alias: {
      "@": path.resolve(__dirname, "./src"),
    },
  },
});
```

react-cli

React CLI 的配置文件和 Vue CLI 不太一样：

先要装包：

```
pnpm install -D @craco/craco
```

再在根目录创建 craco.config.ts：

```
const path = require("path");

module.exports = {
  webpack: {
    alias: {
      "@": path.join(__dirname, "src"),
    },
  },
};
```

还要在 package.json 中重新配置命令：

```
"scripts": {
  "start": "craco start",
  "build": "craco build",
  "test": "craco test",
  "eject": "react-scripts eject"
},
```

#### 7.3.3 ts

注意，如果项目使用的是 ts，且配置了路径别名，那么还需要在 tsconfig.json 中配置路径别名，否则会出错：

```
//确保已经 npm install -D @types/node

{
  "compilerOptions": {
    //...
    "types": [
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

另外，附上 tsconfig.json 配置参考：

```
{
  "compilerOptions": {
    "target": "ES2020",
    "useDefineForClassFields": true,
    "module": "ESNext",
    "lib": ["ES2020", "DOM", "DOM.Iterable"],
    "skipLibCheck": true,

    /* Bundler mode */
    "moduleResolution": "node",      // 这个配置如果值设为其他，导入模块可能会出错
    "allowImportingTsExtensions": true,
    "resolveJsonModule": true,
    "isolatedModules": true,
    "noEmit": true,
    "jsx": "preserve",

    /* Linting */
    "strict": true,
    "noUnusedLocals": true,
    "noUnusedParameters": true,
    "noFallthroughCasesInSwitch": true,

    "types": [ "node" ],
    "paths": {
      "@/*": [
        "./src/*"
      ]
    },
  },
  "include": ["src/**/*.ts", "src/**/*.d.ts", "src/**/*.tsx", "src/**/*.vue"],
  "references": [{ "path": "./tsconfig.node.json" }],
}
```

### 7.4 配置 node 环境

#### 7.4.1 统一包管理工具

包管理工具有npm，yarn，pnpm等，不同的包管理工具可能安装的包的版本不一样，版本不一样的话就可能出bug，所以必须统一，这里统一强制使用 pnpm：

在根目录创建`scripts/preinstall.js`文件，添加下面的内容

```
if (!/pnpm/.test(process.env.npm_execpath || '')) {
  console.warn(
    `\u001b[33mThis repository must using pnpm as the package manager ` +
    ` for scripts to work properly.\u001b[39m\n`,
  )
  process.exit(1)
}
```

配置命令

```
"scripts": {
    "preinstall": "node ./scripts/preinstall.js"
}
```

配置完成后，安装包之前会触发 preinstall 钩子，根据配置就只能使用 pnpm 了，使用其他包管理工具安装包就会报错。

#### 7.4.2 package.json 配置

（1）配置 npm run dev

vite的话，改一下运行脚本的dev，使得在 npm run dev 的时候可以检查 ts，脚手架目前没找到方法，此外也没找到如何开启ts观察模式：

```
{
    "scripts": {
        "dev": "vue-tsc && vite",
    },
}
```

（2）配置环境变量

分为开发环境（dev），测试环境（test），生产环境（production）等等，代码中可以根据当前处于的环境做对应的事，如以下两个常见例子：

- 开发环境和生产环境用到的后端api不同，就可以根据环境变量切换baseURL

- 某个表单在测试环境测试时需要有一个一键补全表单的内容，方便测试，而生产环境不需要，就可以根据环境变量v-if

配置环境变量的文件有两种形式：

- 一个 .env 统一配置
  
  ```
  .env
  ```

- 多个 .env.xxx单独配置
  
  ```
  .env.development
  .env.production
  .env.test
  ```

不同的环境，变量命名规则不同：

- webpack 环境，vue 的变量命名必须以 VUE_APP 开头，react 变量必须以 REACT_APP 开头

- vite 环境，变量命名必须以 VITE 开头

- node 环境，NODE 开头，webpack 和 vite 也可以使用

比如在 .env-development 文件定义 vite 的环境变量：

```
NODE_ENV = '这是development'
VITE_BASEURL = 'https://xxxx'
```

然后再 package.json 配置：

```
 "scripts": {
    "dev": "vue-tsc && vite",
    "build:test": "vue-tsc && vite build --mode test",
    "build:pro": "vue-tsc && vite build --mode production",
    "preview": "vite preview"
  },
```

在代码中调用：

vue 和 react 都一样：

```
// webpack 
console.log(process.env);

// vite 环境
console.log(import.meta.env);

// node 环境
```

在 webpack，vite 配置文件中使用环境变量和普通代码中不同，具体看文档。

### 7.5 其他配置文件

（1）编辑器配置文件 .editorconfig ：

大多数编辑器都会识别，配置一些像缩进等的编辑器配置：

```
# http://editorconfig.org
root = true

[*]
charset = utf-8
indent_style = space
indent_size = 2
end_of_line = lf
insert_final_newline = true
trim_trailing_whitespace = true

[*.md]
insert_final_newline = false
trim_trailing_whitespace = false
```

（2）README

README.md 是项目的说明文件，在github项目的首页会显示里面的内容。

README-zh.md 和 README.md 同时存在时，github会根据浏览器的语言设置使用对应的README文件。

### 7.6 CSS配置

css预处理器：

```
npm install --D less less-loader
```

normalize.css，统一不同浏览器的标签样式。

reset.css 在 normalize 基础上，还有清除默认样式（如margin，padding都变为0）

一般用 reset.css

```
npm install --save reset.css
npm install --save normalize.css
```

```
/* src/assets/style/global.less */
@import 'reset.css';

/* 自己的其他初始化css */
/* uniapp 中没有通配符选择器 */
* {
  margin: 0;
  padding: 0;
  line-height: 1.5;
  font-size: 16px;
  box-sizing: border-box;
  scrollbar-width: none; /* Firefox */
  -ms-overflow-style: none; /* IE 10+ */
}

.pc-center {
  margin: 0 auto;
  width: 1200px;
}

::-webkit-scrollbar {
  display: none; /* Chrome Safari */
}
```

main.ts

```
// 一定要放在所有引入样式的最前面
import "@/assets/style/global.less";
```

如果开发移动端，可以使用px转v w、vh 的库：

```
npm install -D postcss-px-to-viewport
```

```
// vite.config.ts
import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import PostcssPxToViewport from 'postcss-px-to-viewport';

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [vue()],
  css: {
    postcss: {
      plugins: [
        PostcssPxToViewport({
          unitToComvert: 'px',
          viewportWidth: 750    //设计稿宽度
        })
      ]
    }
  },
})
```

```
.test {
  width: 750px; /* 自动解析为100vw */
}
```

### 7.7 字体图标

在开发项目的时候经常会用到svg矢量图,而且我们使用SVG以后，页面上加载的不再是图片资源,

这对页面性能来说是个很大的提升，而且我们SVG文件比img要小的很多，放在项目中几乎不占用资源。

（1）方式一：云图标

可以在阿里iconfont上，选择需要的字体图标，创建项目，并生成链接，在项目的 index.html 中引入：

```
<link
  type="text/css"
  rel="stylesheet"
  href="https://at.alicdn.com/t/c/font_4068422_mghbaleb6o.css?spm=a313x.7781069.1998910419.52&file=font_4068422_mghbaleb6o.css"
/>
```

使用：

```
<i class="iconfont 字体图标类名" />
```

缺陷是阿里只提供图标和连接，不保证服务器的稳定。

（2）方式二：使用组件库的字体图标

（3）方式三：使用本地svg图标

**安装SVG依赖插件**

```
npm install vite-plugin-svg-icons -D
```

在`vite.config.ts`中配置插件：

```
import { createSvgIconsPlugin } from 'vite-plugin-svg-icons'
import path from 'path'

export default () => {
  return {
    plugins: [
      createSvgIconsPlugin({
        iconDirs: [path.resolve(process.cwd(), 'src/assets/icons')],
        symbolId: 'icon-[dir]-[name]',
      }),
    ],
  }
}
```

入口文件导入

```
import 'virtual:svg-icons-register'
```

上面的配置的意思是，把放在 /src/assets/icons 的svg文件依次标记id，如 /src/assets/icons/aaa.svg 的id就是 ‘#icon-aaa’，/src/assets/icons/sub/aaa.svg 的id就是 ‘#icon-sub-aaa’

然后就可以使用了：

```
<svg style="width: 16px; height: 16px">
  <use xlink:href="#icon-aaa" fill="#000000"></use>
</svg>
```

但是占用了三行，比较冗余，所以可以封装为全局组件：

在 src/components/common 目录下创建一个SvgIcon组件:代表如下：

```
<script setup lang="ts">
withDefaults(
  defineProps<{
    prefix: string; // xlink:href属性值的前缀
    name: string; // svg矢量图的名字
    color?: string;
    width?: string;
    height?: string;
  }>(),
  {
    prefix?: "#icon-",
    name: "",
    color: "#000000",
    width: "16px",
    height: "16px"
  }
);
</script>

<template>
  <div>
    <svg :style="{ width: width, height: height }">
      <use :xlink:href="prefix + name" :fill="color"></use>
    </svg>
  </div>
</template>
```

在 src/components/common 下创建 globalComponent.ts 用来注册全局组件：

```
import SvgIcon from "./SvgIcon.vue";
import type { App, Component } from "vue";

// 准备注册的组件，目前只注册 SvgIcon
const components: { [name: string]: Component } = { SvgIcon };

export default {
  install(app: App) {
    Object.keys(components).forEach((key: string) => {
      app.component(key, components[key]);
    });
  }
};
```

main.ts

```
import gloablComponent from "./components/common/globalComponent";
createApp(App).use(gloablComponent);
```

使用：

```
<SvgIcon name="aaa" />
```

# 二、常用布局。交互效果和业务逻辑

## 1 整体布局

（1）PC端：

- 普通页面，header+居中版心+footer，header和footer与浏览器同宽

- 后台管理系统，居中版心（左（aside）+右（header+content））

（2）移动端：

手机和电脑连一个wifi，手机进入 电脑ip:端口

- 限制屏幕缩放的最大与最小宽度

- 顶部导航+滚动（单滚动或左分类+有内容）+tabBar，开发时页面分类tabBar页面和非tabBar页面，导航栏和tabBar可以根据路由动态显示隐藏荐vw

（3）根据页面v-if，v-show动态显示对应内容

如登录页和404页隐藏全局的一些模块

如移动端的导航栏和tabbar可以根据判断路由来动态显示

- 必须做适配，推

## 2 常用布局

（1）圣杯布局

左右两边固定宽度，中间部分宽度自适应

```
<style>
.box {
  display: flex;
}
.left,.right {
  width: 50px;
  background-color: blue;
}
.middle {
  flex: 1;
  background-color: orange;
}
</style>

<body>
  <div class="box">
    <div class="left">左</div>
    <div class="middle">中</div>
    <div class="right">右</div>
  </div>
</body>
```

![](C:\Users\Administrator\AppData\Roaming\marktext\images\2022-10-24-23-14-50-image.png)

（2）网格布局（也叫分栏布局）

整齐的排列

```
<style>
.box {
  display: flex;
  justify-content: space-around;
  flex-wrap: wrap;
}
.box > .item {
  margin-bottom: 10px;
  width: 28%;
  height: 100px;
  background-color: orange;
}
</style>

<body>
  <div class="box">
    <div class="item">1</div>
    <div class="item">2</div>
    <div class="item">3</div>
    <div class="item">4</div>
    <div class="item">5</div>
    <div class="item">6</div>
    <div class="item">7</div>
    <div class="item">8</div>
    <div class="item">9</div>
  </div>
</body>
```

![](C:\Users\Administrator\AppData\Roaming\marktext\images\2022-10-24-23-11-22-image.png)

（3）瀑布布局

参差不齐的网格布局

```
<style>
.box {
  column-count: 3;
  column-gap: 20px;
}
.box>.item {
  margin-bottom: 5px;
  background-color: orange;
}
</style>

<body>
  <div class="box">
    <div class="item" style="height: 50px">1</div>
    <div class="item" style="height: 150px">2</div>
    <div class="item" style="height: 70px">3</div>
    <div class="item" style="height: 120px">4</div>
    <div class="item" style="height: 30px">5</div>
    <div class="item" style="height: 90px">6</div>
    <div class="item" style="height: 190px">7</div>
    <div class="item" style="height: 30px">8</div>
  </div>
</body>
```

![](C:\Users\Administrator\AppData\Roaming\marktext\images\2022-10-24-23-04-59-image.png)

（4）水平滑动切换/点击切换布局

切换回来时，高度可以保持也可以到最开始

## 3 常用的交互效果

（1）轮播图

① swiper

```
npm install --save swiper
npm install -D @types/swiper
```

注意，一定要v-if判断img是否有值，否则不会轮播：

封装成MySwiper组件：

```
<script setup lang="ts">
import { ref, watch, nextTick } from 'vue';
import Swiper from 'swiper';
import {
  A11y,
  Autoplay,
  Controller,
  EffectCoverflow,
  EffectCube,
  EffectFade,
  EffectFlip,
  EffectCreative,
  EffectCards,
  HashNavigation,
  History,
  Keyboard,
  Mousewheel,
  Navigation,
  Pagination,
  Parallax,
  Scrollbar,
  Thumbs,
  Virtual,
  Zoom,
  FreeMode,
  Grid,
  Manipulation,
} from 'swiper';
import 'swiper/css';
import 'swiper/css/navigation';
import 'swiper/css/pagination';
import 'swiper/swiper-bundle.css';
import 'swiper/swiper.min.css';

Swiper.use([
  A11y,
  Autoplay,
  Controller,
  EffectCoverflow,
  EffectCube,
  EffectFade,
  EffectFlip,
  EffectCreative,
  EffectCards,
  HashNavigation,
  History,
  Keyboard,
  Mousewheel,
  Navigation,
  Pagination,
  Parallax,
  Scrollbar,
  Thumbs,
  Virtual,
  Zoom,
  FreeMode,
  Grid,
  Manipulation,
]);

interface swiperPropsInterface {
  img?: string[]; // 图片url
  bannerHeight?: number; // 轮播图高度
  loop?: boolean; // 循环轮播
  delay?: number; // 轮播时间
  pagination?: any; // 分页器
  navigation?: boolean; // 前进后退按钮
  slidesPerView?: number; // 每页的图片数
  spaceBetween?: number; // 每页多个图片时，每个图片之间的间距
  effect?: 'slide' | 'fade' | string; // 切换的动画效果
  speed?: number; // 切换时间
  useZoom?: boolean; // 是否使用放大镜
  thumbs?: boolean; // 是否使用缩略图
  thumbsProps?: swiperPropsInterface; // 缩略图配置
}

const props = withDefaults(defineProps<swiperPropsInterface>(), {
  img: () => [],
  loop: false,
  delay: 2000,
  pagination: () => {
    return { clickable: true, type: 'bullets' };
  },
  navigation: false,
  slidesPerView: 1,
  spaceBetween: 0,
  effect: 'slide',
  speed: 500,
  uasZoom: false,
  thumbs: false,
  thumbsProps: () => {
    return {};
  },
});

const thumbsPropsDefault = ref<any>({});

const swiperRef = ref<HTMLElement | null>(null);
const swiperThumbsRef = ref<HTMLElement | null>(null);
const swiper = ref<any>({
  swiper: null,
  swiperThumbs: null,
});

function initSwiper(swiperInstance: any, thumbs: boolean = false) {
  let options: swiperPropsInterface | null = null;
  if (!thumbs) options = props;
  else options = thumbsPropsDefault.value;

  swiper.value[thumbs ? 'swiperThumbs' : 'swiper'] = new Swiper(swiperInstance, {
    loop: options?.loop,
    autoplay: {
      delay: options?.delay,
      disableOnInteraction: false,
      pauseOnMouseEnter: true,
    },
    pagination: {
      el: '.swiper-pagination',
      ...options?.pagination,
    },
    navigation: {
      nextEl: '.swiper-button-next',
      prevEl: '.swiper-button-prev',
    },
    effect: options?.effect as any,
    speed: options?.speed,
    slidesPerView: options?.slidesPerView,
    spaceBetween: options?.spaceBetween,
    thumbs: {
      swiper: thumbs ? null : swiper.value.swiperThumbs,
    },
  });
}

watch(
  () => props.img,
  async () => {
    await nextTick();
    if (props.thumbs) {
      thumbsPropsDefault.value = Object.assign(
        {
          img: [],
          loop: false,
          delay: 2000,
          pagination: { clickable: true, type: 'bullets' },
          navigation: false,
          slidesPerView: 1,
          spaceBetween: 0,
          activeIndex: 1,
          effect: 'slide',
          speed: 500,
        },
        props.thumbsProps
      );
      await nextTick();
      initSwiper(swiperThumbsRef.value, true);
    }
    initSwiper(swiperRef.value);

    if (swiperRef.value && maskRef.value && bigImgRef.value && bigImgBoxRef.value) {
      imgHeight.value = swiperRef.value.children[0].children[0].children[0].clientHeight;
      imgWidth.value = swiperRef.value.children[0].children[0].children[0].clientWidth;
    }
  }
);

// 放大镜效果
const imgHeight = ref<number>(0);
const imgWidth = ref<number>(0);
const smallImgRef = ref<HTMLElement[] | null>(null);
const maskRef = ref<HTMLElement[] | null>(null);
const bigImgRef = ref<HTMLElement | null>(null);
const bigImgBoxRef = ref<HTMLElement | null>(null);
const currentZoomIndex = ref<number>(0);

function mouseMove(e: MouseEvent, index: number) {
  if (!smallImgRef.value || !maskRef.value || !bigImgRef.value || !bigImgBoxRef.value) return;

  currentZoomIndex.value = index;

  maskRef.value[index].style.height = imgHeight.value / 2 + 'px';
  maskRef.value[index].style.width = imgWidth.value / 2 + 'px';
  bigImgBoxRef.value.style.height = imgHeight.value + 'px';
  bigImgBoxRef.value.style.width = imgWidth.value + 'px';
  bigImgBoxRef.value.style.top = '0';
  bigImgBoxRef.value.style.left = imgWidth.value + 10 + 'px';

  maskRef.value[index].style.display = 'block';
  bigImgBoxRef.value.style.display = 'block';

  let innerX = e.clientX - smallImgRef.value[index].getBoundingClientRect().left;
  let innerY = e.clientY - smallImgRef.value[index].getBoundingClientRect().top;
  let l = innerX - maskRef.value[index].offsetWidth / 2;
  let t = innerY - maskRef.value[index].offsetHeight / 2;

  if (l < 0) l = 0;
  if (t < 0) t = 0;
  if (l > smallImgRef.value[0].offsetWidth - maskRef.value[index].offsetWidth)
    l = smallImgRef.value[0].offsetWidth - maskRef.value[index].offsetWidth;
  if (t > smallImgRef.value[0].offsetHeight - maskRef.value[index].offsetHeight)
    t = smallImgRef.value[0].offsetHeight - maskRef.value[index].offsetHeight;

  maskRef.value[index].style.left = l + 'px';
  maskRef.value[index].style.top = t + 'px';

  bigImgRef.value.style.left =
    -maskRef.value[index].offsetLeft * (bigImgRef.value.offsetWidth / smallImgRef.value[index].offsetWidth) + 'px';
  bigImgRef.value.style.top =
    -maskRef.value[index].offsetTop * (bigImgRef.value.offsetHeight / smallImgRef.value[index].offsetHeight) + 'px';
}

function mouseLeave(index: number) {
  if (!smallImgRef.value || !maskRef.value || !bigImgRef.value || !bigImgBoxRef.value) return;
  maskRef.value[index].style.display = 'none';
  bigImgBoxRef.value.style.display = 'none';
}
</script>

<template>
  <div id="my-swiper">
    <div class="swiper" ref="swiperRef">
      <div class="swiper-wrapper">
        <div class="swiper-slide" v-for="(i, iIndex) in img" :key="iIndex">
          <!--  图片懒加载和swiper一起使用可能会出现一个bug 即渲染出空白图,下面是解决方案      -->
          <!-- <img :src="carousel.imageUrl" v-if="index == 0 || index === carouselList.length - 1" /> -->
          <!-- <img v-lazy.container="carousel.imageUrl" alt="" v-else /> -->
          <img
            ref="smallImgRef"
            :src="i"
            :style="{ height: bannerHeight + 'px' }"
            :data-img-index="iIndex"
            @mousemove="mouseMove($event, iIndex)"
          />
          <div
            v-if="useZoom"
            class="mask"
            ref="maskRef"
            :data-mask="true"
            @mousemove="mouseMove($event, iIndex)"
            @mouseleave="mouseLeave(iIndex)"
          ></div>
        </div>
      </div>

      <div class="swiper-pagination" v-if="pagination"></div>

      <div class="swiper-button-prev" v-if="navigation"></div>
      <div class="swiper-button-next" v-if="navigation"></div>

      <!--    <div class="swiper-scrollbar"></div>-->
    </div>

    <div class="swiper" ref="swiperThumbsRef" v-if="thumbs">
      <div class="swiper-wrapper">
        <div class="swiper-slide" v-for="(i, iIndex) in thumbsPropsDefault?.img" :key="iIndex">
          <!--  图片懒加载和swiper一起使用可能会出现一个bug 即渲染出空白图,下面是解决方案      -->
          <!-- <img :src="carousel.imageUrl" v-if="index == 0 || index === carouselList.length - 1" /> -->
          <!-- <img v-lazy.container="carousel.imageUrl" alt="" v-else /> -->
          <img :src="i" :style="{ height: thumbsPropsDefault?.bannerHeight + 'px' }" />
        </div>
      </div>

      <div class="swiper-pagination" v-if="thumbsPropsDefault?.pagination"></div>

      <div class="swiper-button-prev" v-if="thumbsPropsDefault?.navigation"></div>
      <div class="swiper-button-next" v-if="thumbsPropsDefault?.navigation"></div>

      <!--    <div class="swiper-scrollbar"></div>-->
    </div>

    <div class="big-img-box" ref="bigImgBoxRef" v-if="useZoom && img.length !== 0">
      <img
        ref="bigImgRef"
        :src="img[currentZoomIndex]"
        :style="{position: 'relative', width: '200%', height: bannerHeight! * 2 + 'px' }"
      />
    </div>
  </div>
</template>

<style lang="less" scoped>
#my-swiper {
  position: relative;
  img {
    width: 100%;
  }

  .mask {
    display: none;
    position: absolute;
    z-index: 9998;
    cursor: crosshair;
    background-color: rgba(0, 0, 0, 0.5);
  }

  .big-img-box {
    display: none;
    position: absolute;
    z-index: 9998;
    overflow: hidden;
    width: 200px;
    height: 200px;
  }
}
</style>
```

② 自己实现

（1）将所有图片放到一行，通过控制margin-left精选左右轮播

（2）将所有图片绝对定位到同一个位置，通过控制透明度精选淡入淡出轮播

（2）模态框

可拖拽移动的盒子，盒子需要设置为绝对定位：

```
<style>
#box {
  position: absolute;
  left: 100px;
  top: 100px;
  width: 100px;
  height: 100px;
  border: 1px solid #000;
}
</style>

<body>
  <div id="box"></div>
</body>

<script>
let box = document.querySelector('#box');

box.addEventListener('mousedown',function(mouseDown){
  //计算鼠标在盒子内，距离盒子左边和上边的距离
  let innerX = mouseDown.clientX - box.getBoundingClientRect().left;
  let innerY = mouseDown.clientY - box.getBoundingClientRect().top;

  function boxMove(mouseMove){
    box.style.left = mouseMove.clientX - innerX + 'px';
    box.style.top = mouseMove.clientY - innerY + 'px';
  }
  document.addEventListener('mousemove',boxMove);
  document.addEventListener('mouseup',function(){
    document.removeEventListener('mousemove', boxMove)
  });
})
</script>
```

（3）放大镜

```
<style>
  * {
    margin: 0;
    padding: 0;
  }
  .small {
    position: relative;
    overflow: hidden;
    width: 200px;
    height: 200px;
    cursor: crosshair;
  }
  .small img {
    width: 100%;
  }
  .mask {
    display: none;
    position: absolute;
    top: 0;
    left: 0;
    width: 100px;
    height: 100px;
    cursor: crosshair;
    background-color: rgba(0, 0, 0, 0.5);
  }
  .big {
    display: none;
    position: absolute;
    left: 200px;
    top: 0;
    overflow: hidden;
    width: 200px;
    height: 200px;
  }
  .big img {
    position: relative;
    width: 200%;
  }
</style>

<body>
  <div class="small">
    <img src="./1.png" alt="" />
    <div class="mask"></div>
  </div>
  <div class="big">
    <img src="./1.png" alt="" />
  </div>
</body>

<script>
  const small = document.querySelector(".small");
  const smallImg = document.querySelector(".small img");
  const big = document.querySelector(".big");
  const bigImg = document.querySelector(".big img");
  const mask = document.querySelector(".mask");

  small.addEventListener("mouseleave", function () {
    mask.style.display = "none";
    big.style.display = "none";
  });

  small.addEventListener("mousemove", function (e) {
    mask.style.display = "block";
    big.style.display = "block";

    let innerX = e.clientX - small.getBoundingClientRect().left;
    let innerY = e.clientY - small.getBoundingClientRect().top;
    let l = innerX - mask.offsetWidth / 2;
    let t = innerY - mask.offsetHeight / 2;

    if (l < 0) l = 0;
    if (t < 0) t = 0;
    if (l > small.offsetWidth - mask.offsetWidth)
      l = small.offsetWidth - mask.offsetWidth;
    if (t > small.offsetHeight - mask.offsetHeight)
      t = small.offsetHeight - mask.offsetHeight;

    mask.style.left = l + "px";
    mask.style.top = t + "px";

    bigImg.style.left = -mask.offsetLeft * (bigImg.offsetWidth / smallImg.offsetWidth) + "px";
    bigImg.style.top = -mask.offsetTop * (bigImg.offsetHeight / smallImg.offsetHeight) + "px";
  });
</script>
```

（4）计数器

封装成Counter组件：

```
<script setup lang="ts">
import { ref, watch } from 'vue';

const props = withDefaults(
  defineProps<{
    count: number;
  }>(),
  {
    count: 1,
  }
);

const count = ref<number>(props.count);

function countInput(e: Event) {
  if ((e.target as HTMLInputElement).value === '') return;

  let value = Number((e.target as HTMLInputElement).value);
  if (!Number.isInteger(value) || value < 1) value = 1;
  count.value = value;
}

const emit = defineEmits(['countUpdate']);
watch(count, newVal => {
  if (!Number.isInteger(newVal)) return;
  emit('countUpdate', count.value);
});
</script>

<template>
  <div id="counter">
    <button class="counter-btn" @click="count = count > 1 ? count - 1 : count">-</button>
    <div>
      <input
        class="counter-inp"
        type="text"
        v-model="count"
        @input="countInput"
        @blur="count = !count || count > 999999999 ? 1 : count"
      />
    </div>
    <button class="counter-btn" @click="count = count < 999999999 ? count + 1 : count">+</button>
  </div>
</template>

<style lang="less" scoped>
#counter {
  display: flex;
  align-items: center;
  text-align: center;
  .counter-inp {
    width: 80px;
    height: 40px;
    line-height: 40px;
    text-align: center;
  }

  .counter-btn {
    width: 40px;
    height: 40px;
    line-height: 30px;
    font-size: 25px;
    cursor: pointer;
  }
}
</style>
```

（5）移动端搜索框：

点击假的搜索盒子进入搜索页面，进入时候自动获得焦点

## 4 常用业务逻辑

第三方库 lodash 有很多数组操作函数、以及防抖节流这些。

（1）移动端上拉加载更多/PC端分页

上拉加载更多：

* 正在加载时，应该用一个if阀口来判断是否正在加载中，只有在非加载状态时才发送请求不能用防抖节流

* 上拉加载最后一页的判断，服务器返回一般两种：
  ①状态码，根据状态码判断就行
  ②返回总数，此时可以用 页码*每页数量>=总数来判断，也可以当前总数>=总数来判断

分页：

* 原理差不多，只是变成了按页数切换数据

* 分页器组件Pagination：
  
  ```
  <script setup lang="ts">
  import { computed } from 'vue';
  
  const props = defineProps<{
    // 分别是总数，每页的数量，当前页码，显示几个页码按钮
    total: number;
    pageSize: number;
    pageNo: number;
    pagerCount: number;
  }>();
  
  const emits = defineEmits(['currentPage']);
  
  let totalPage = computed(() => {
    return Math.ceil(props.total / props.pageSize);
  });
  
  const startAndEnd = computed(() => {
    let start = 0,
      end = 0;
    if (totalPage.value < props.pagerCount) {
      start = 1;
      end = totalPage.value;
    } else {
      start = props.pageNo - Math.floor(props.pagerCount / 2);
      end = props.pageNo + Math.floor(props.pagerCount / 2);
      if (start < 1) {
        start = 1;
        end = props.pagerCount;
      }
      if (end > totalPage.value) {
        end = totalPage.value;
        start = totalPage.value - props.pagerCount + 1;
      }
    }
    return { start, end };
  });
  </script>
  
  <template>
    <div class="pagination">
      <button @click="emits('currentPage', pageNo - 1)" :disabled="pageNo <= 1">上一页</button>
      <button v-if="startAndEnd.start > 1" @click="emits('currentPage', 1)">1</button>
      <button v-if="startAndEnd.start > 2">.....</button>
  
      <button
        v-for="page in startAndEnd.end"
        :key="page"
        v-show="page >= startAndEnd.start"
        @click="emits('currentPage', page)"
        :class="{ active: pageNo == page }"
      >
        {{ page }}
      </button>
  
      <button v-if="startAndEnd.end < totalPage - 1">......</button>
      <button v-if="startAndEnd.end < totalPage" @click="emits('currentPage', totalPage)">{{ totalPage }}</button>
  
      <button @click="emits('currentPage', pageNo + 1)" :disabled="pageNo == totalPage">下一页</button>
  
      <button style="margin-left: 30px">共 {{ total }} 条</button>
    </div>
  </template>
  
  <style lang="less" scoped>
  .pagination {
    display: flex;
    justify-content: center;
    align-items: center;
  
    button {
      margin: 0 5px;
      background-color: #f4f4f5;
      color: #606266;
      outline: none;
      border-radius: 2px;
      padding: 0 4px;
      vertical-align: top;
      display: inline-block;
      font-size: 13px;
      min-width: 35.5px;
      height: 28px;
      line-height: 28px;
      cursor: pointer;
      box-sizing: border-box;
      text-align: center;
      border: 0;
  
      &[disabled] {
        color: #c0c4cc;
        cursor: not-allowed;
      }
  
      &.active {
        cursor: not-allowed;
        background-color: #409eff;
        color: #fff;
      }
    }
  }
  </style>
  ```

（2）表单验证

组件库如elementui的表单组件都有表单验证的功能，但是如果不用组件库的话就需要自己写了。可以使用vee-validate。

```
npm install --save vee-validate@next @vee-validate/rules @vee-validate/i18n@next
```

使用：

* 有多重方式，如组件、指令等，这里展示组件的用法

* \<Field /\> 通过 name 使用自定义的校验规则

封装成FormValidate组件：

```
<script setup lang="ts">
import { ref } from 'vue';
import { Form, Field } from 'vee-validate';

interface formInterface {
  name: string;
  type: 'text' | 'password' | 'radio' | 'checkbox' | string;
  value: string | string[] | boolean;
  describe?: string;
  placeholder?: string;
  text?: string;
  withImg?: string;
  items?: {
    value: string | boolean;
    text?: string;
  }[];
  schema?: {
    type: 'notEmpty' | 'reg' | 'same' | string;
    reg?: RegExp[];
    sameName?: string;
    errorMessage: string;
  }[];
}

const props = withDefaults(
  defineProps<{
    formData: formInterface[];
    submitText?: string;
  }>(),
  {
    formData: () => [],
    submitText: '提交',
  }
);

const emit = defineEmits(['codeImgChange', 'submit']);

// // formData 例子
// const data: formInterface[] = ref([
//   {
//     name: 'account',
//     type: 'text',
//     describe: '用户名',
//     placeholder: '请输入用户名',
//     value: '',
//     schema: [{ type: 'notEmpty', errorMessage: '用户名不能为空' }],
//   },
//   {
//     name: 'password',
//     type: 'password',
//     describe: '密码',
//     placeholder: '请输入密码',
//     value: '',
//     schema: [
//       { type: 'notEmpty', errorMessage: '密码不能为空' },
//       {
//         type: 'reg',
//         reg: [/[a-zA-Z0-9]{6,24}/, /[A-Z]/, /[0-9]/],
//         errorMessage: '密码必须是6-24位，由数字和英文字母组成，且必须包含数字和大写字母',
//       },
//     ],
//   },
//   {
//     name: 'passwordConfirm',
//     type: 'password',
//     describe: '确认密码',
//     placeholder: '请输入确认密码',
//     value: '',
//     schema: [
//       { type: 'notEmpty', errorMessage: '确认密码不能为空' },
//       {
//         type: 'reg',
//         reg: [/[a-zA-Z0-9]{6,24}/, /[A-Z]/, /[0-9]/],
//         errorMessage: '密码必须是6-24位，由数字和英文字母组成，且必须包含数字和大写字母',
//       },
//       { type: 'same', sameName: 'password', errorMessage: '密码和确认密码不一致' },
//     ],
//   },
//   {
//     name: 'sex',
//     type: 'radio',
//     describe: '性别',
//     value: 'female',
//     items: [
//       { value: 'male', text: '男' },
//       { value: 'female', text: '女' },
//     ],
//     schema: [{ type: 'notEmpty', errorMessage: '请勾选性别' }],
//   },
//   {
//     name: 'hobbit',
//     type: 'checkbox',
//     describe: '爱好',
//     value: ['opt1'],
//     items: [
//       { value: 'opt1', text: '多选1' },
//       { value: 'opt2', text: '多选2' },
//       { value: 'opt3', text: '多选3' },
//       { value: 'opt4', text: '多选4' },
//     ],
//     schema: [{ type: 'notEmpty', errorMessage: '请勾选兴趣' }],
//   },
//   {
//     name: 'code',
//     type: 'text',
//     describe: '验证码',
//     placeholder: '',
//     value: '',
//     withImg: 'imgurl',
//     schema: [{ type: 'notEmpty', errorMessage: '验证码不能为空' }],
//   },
//   {
//     name: 'agree',
//     type: 'checkbox',
//     text: `我同意<a href="#">xxx协议</a>`,
//     value: false,
//     items: [{ value: true, text: `我同意<a href="#"a>xxx选项</a>` }],
//     schema: [{ type: 'notEmpty', errorMessage: '请同意协议' }],
//   },
// ]);

//校验规则
function schema(value: string, form: any) {
  const formItem = props.formData.find(i => i.name === form.field);
  if (!formItem || !formItem.schema) return true;

  for (let i of formItem.schema) {
    switch (i.type) {
      case 'notEmpty':
        if (!value || value?.length === 0) return i.errorMessage;
        break;
      case 'reg':
        if (!i.reg!.every(r => r.test(value))) return i.errorMessage;
        break;
      case 'same':
        if (value !== props.formData.find((item: formInterface) => item.name === i.sameName)?.value)
          return i.errorMessage;
        break;
      default:
        break;
    }
  }

  return true;
}

// 使用校验规则
const mySchema = ref<any>({});
for (let i of props.formData) mySchema.value[i.name] = schema;

// 提交
function submit(data: any) {
  emit('submit', data);
}
</script>

<template>
  <Form
    id="form-validate"
    v-if="formData.length !== 0"
    :validation-schema="mySchema"
    v-slot="{ errors }"
    @submit="submit"
  >
    <div v-for="i in formData" :key="i.name">
      <div class="form-item" :style="{ 'margin-bottom': errors[i.name] ? 0 : '35px' }">
        <!-- 表头 -->
        <div class="describe">
          <span>{{ i.describe }}</span>
          <span>{{ i.describe ? '：' : ' ' }}</span>
        </div>

        <!-- 输入框 -->
        <div
          class="form-item-type form-item-type-text"
          :class="{ 'with-img': i.withImg }"
          v-if="['text', 'password', 'email'].includes(i.type)"
        >
          <Field v-model="i.value" :name="i.name" :type="i.type" :placeholder="i.placeholder" :validateOnInput="true" />
          <img class="code" v-if="i.withImg" :src="i.withImg" @click="$emit('codeImgChange')" />
        </div>

        <!-- 单选、多选 -->
        <div class="form-item-type form-item-type-options" v-else-if="['radio', 'checkbox'].includes(i.type)">
          <label v-for="(item, itemIndex) in i.items" :key="itemIndex">
            <div class="options-box">
              <div>
                <Field v-model="i.value" :value="item.value" :name="i.name" :type="i.type" :validateOnInput="true" />
              </div>
              <div v-html="item.text"></div>
            </div>
          </label>
        </div>
      </div>

      <!-- 错误提示 -->
      <div class="error-message" v-if="errors[i.name]">
        <span class="describe"></span>
        <span>{{ errors[i.name] }}</span>
      </div>
    </div>

    <div class="form-item">
      <div class="form-submit">
        <button type="submit">{{ submitText }}</button>
      </div>
    </div>
  </Form>
</template>

<style lang="less" scoped>
@common-height: 30px;

#form-validate {
  .form-item {
    display: flex;
    height: @common-height;

    .describe {
      display: flex;
      justify-content: space-between;
      align-items: center;
      height: @common-height;
      line-height: @common-height;

      span {
        width: 20px;
        text-align: right;
        font-size: 17px;
      }

      span:first-child {
        width: 80px;
      }
    }

    .form-item-type {
      display: flex;
      justify-content: space-around;
      align-items: center;
    }

    .form-item-type-text {
      input {
        padding: 0 10px;
        width: 250px;
        height: @common-height;
        font-size: 17px;
      }
    }

    .with-img {
      input {
        width: 100px;
      }

      .code {
        margin-left: 30px;
        height: @common-height;
      }
    }

    .form-item-type-options {
      display: flex;
      align-items: center;
      .options-box {
        display: flex;
        align-items: center;
        margin-right: 30px;

        > div {
          margin-right: 8px;
          height: @common-height;
          line-height: @common-height;
          font-size: 17px;
        }
      }
    }
  }

  .error-message {
    margin: 5px 0 10px 110px;
    height: 20px;
    line-height: 20px;
    color: red;
    font-size: 12px;
  }

  .form-submit {
    margin-left: 100px;
    width: 270px;
    height: 33px;

    button {
      width: 100%;
      height: 100%;
      font-size: 18px;
      border-radius: 10px;
    }
  }
}
</style>
```

也可以以二次封装elementplus的表单：

```
<script setup lang="ts">
import { ref, watch } from "vue";
import MyUpload from "./MyUpload.vue";
import type { FormInstance, FormRules } from "element-plus";

const formRef = ref<FormInstance>();

const props = withDefaults(
  defineProps<{
    formMessage: Array<
      Array<{
        type:
          | "text"
          | "password"
          | "textarea"
          | "number"
          | "radio"
          | "checkbox"
          | "select"
          | "date-picker"
          | "upload-one"
          | "upload-many"
          | string;
        model: string;
        formItemLabel?: string;
        label?: string;
        hide?: boolean;
        unsigned: boolean;
        integer: boolean;
        options?: Array<{ value: string; text: string }>;
        action?: string;

        rules?: Array<{
          type: "required" | "reg" | "same" | string;
          reg?: Array<RegExp>;
          sameName?: string;
          errorMessage: string;
        }>;
      }>
    >;
    formData: any;
    useExtraFormItem?: boolean;
    extraFormItemLabel?: string;
  }>(),
  {
    formMessage: () => [],
    formData: () => {
      return {};
    },
    useExtraFormItem: false,
    extraFormItemLabel: ""
  }
);

const emit = defineEmits(["selectChange", "cancel", "reset", "submit"]);

defineExpose({
  formRef,
  reset
});

/* 由于vue会对表单进行复用，即使v-if也不会删除表单，这样在使用上会有一个问题，若MyForm组件需要
   显示隐藏，哪么若隐藏之前表单验证了并出现错误提示，哪么隐藏后再次显示错误提示依旧会存在。
   所以这里提供父组件一个清空错误提示的函数
*/
function reset(options: { resetValueToo: boolean }) {
  if (!formRef.value) return;

  const { resetValueToo } = options;
  if (resetValueToo) formRef.value?.resetFields();
  else {
    const temp: any = {};
    for (const key in props.formData) temp[key] = props.formData[key];
    formRef.value?.resetFields();
    for (const key in temp) props.formData[key] = temp[key];
  }
}

// 数字是否限制整数和小数 -----------------------------------------------------------------------------
// input类型本来是用number，但是输入 -和. 的时候input事件不毁掉，为了直接不让输入 -和. ，input类型就设置为了text
function formatNumber(form: any) {
  const { model, unsigned, integer } = form;

  if (props.formData[model] === "") return;
  if (props.formData[model] === "-" && !unsigned) return;

  const num = Number(props.formData[model]);

  if (unsigned && integer) {
    if (!/^\d+$/.test(props.formData[model]) || num === 0) {
      if (/^\d+$/.test(props.formData[model].slice(0, -1))) props.formData[model] = props.formData[model].slice(0, -1);
      else props.formData[model] = "";
    }
  } else if (unsigned && !integer) {
    if (!/^[+]?(\d+\.?\d*|\.\d+)$/.test(props.formData[model])) {
      if (/^[+]?(\d+\.?\d*|\.\d+)$/.test(props.formData[model].slice(0, -1))) {
        props.formData[model] = props.formData[model].slice(0, -1);
      } else props.formData[model] = "";
    }
  } else if (!unsigned && integer) {
    if (!/^[-+]?\d+$/.test(props.formData[model])) {
      if (/^[-+]?\d+$/.test(props.formData[model].slice(0, -1))) {
        props.formData[model] = props.formData[model].slice(0, -1);
      } else props.formData[model] = "";
    }
  } else if (!unsigned && !integer) {
    if (!/^-?\d+(\.\d*)?$/.test(props.formData[model])) {
      if (/^-?\d+(\.\d*)?$/.test(props.formData[model].slice(0, -1))) {
        props.formData[model] = props.formData[model].slice(0, -1);
      } else props.formData[model] = "";
    }
  }
}

// 表单验证 ----------------------------------------------------------
const validatePass = (rule: any, _: any, callback: any) => {
  // if (value) return;

  const formItem = props.formMessage.find((i: any) => i[0].model === rule.field);
  if (!formItem) return true;

  for (const child of formItem) {
    if (!child.rules) return true;

    for (const i of child.rules) {
      const formDataValue = props.formData[child.model];

      switch (i.type) {
        case "required":
          if (!formDataValue || formDataValue?.length === 0) callback(new Error(i.errorMessage));
          break;
        case "reg":
          if (!i.reg!.every(r => r.test(formDataValue))) callback(new Error(i.errorMessage));
          break;
        case "same":
          if (formDataValue !== props.formData[i.sameName || ""]) callback(new Error(i.errorMessage));
          break;
        default:
          break;
      }
    }
  }

  return true;
};

const rules = ref<FormRules>({});

watch(
  () => props.formMessage,
  () => {
    for (const i of props.formMessage) {
      if (!i[0]?.model) continue;
      if (i.filter((child: any) => child.rules?.length > 0).length === 0) continue;

      rules.value[i[0].model] = [{ validator: validatePass, trigger: "blur" }];
    }
  },
  { immediate: true }
);

function submit(formEl: FormInstance | undefined) {
  if (!formEl) return;
  formEl.validate(valid => {
    if (valid) {
      emit("submit");
    } else {
      return false;
    }
  });
}

function resetForm() {
  if (formRef.value) formRef.value.resetFields();
  emit("reset");
}

// 例子
// const example = {
//   title: "新增SPU",
//   formMessage: [
//     [{ type: "text", formItemLabel: "工号", label: "工号", model: "username" }],
//     [{ type: "password", formItemLabel: "初始密码", label: "初始密码", model: "password" }],
//     [
//       {
//         type: "select",
//         formItemLabel: "国家",
//         label: "国家",
//         model: "area",
//         options: [
//           { value: "s1", text: "opt2" },
//           { value: "s2", text: "opt2" }
//         ]
//       }
//     ],
//     [
//       {
//         type: "select",
//         formItemLabel: "分类",
//         label: "一级分类",
//         model: "c1",
//         options: [
//           { value: "s1", text: "opt1" },
//           { value: "s2", text: "opt2" }
//         ]
//       },
//       {
//         type: "select",
//         label: "二级分类",
//         model: "c2",
//         options: [
//           { value: "s1", text: "opt1" },
//           { value: "s2", text: "opt2" }
//         ]
//       }
//     ],
//     [
//       {
//         type: "radio",
//         formItemLabel: "性别",
//         model: "sex",
//         options: [
//           { value: "male", text: "男" },
//           { value: "remale", text: "女" }
//         ]
//       }
//     ],
//     [
//       {
//         type: "checkbox",
//         formItemLabel: "角色",
//         model: "role",
//         options: [
//           { value: "role1", text: "前端" },
//           { value: "role2", text: "后端" }
//         ]
//       }
//     ],
//     [{ type: "date-picker", formItemLabel: "出生日期", model: "birthday" }],
//     [
//       {
//         type: "upload-one",
//         formItemLabel: "图",
//         action: "https://run.mocky.io/v3/9d059bf9-4660-45f2-925d-ce80ad6c4d15",
//         model: "mainImage"
//       }
//     ],
//     [
//       {
//         type: "upload-many",
//         formItemLabel: "轮播图",
//         action: "https://run.mocky.io/v3/9d059bf9-4660-45f2-925d-ce80ad6c4d15",
//         model: "banner"
//       }
//     ]
//   ],
//   formData: {
//     username: "",
//     password: "123456",
//     area: "",
//     c1: "",
//     c2: "",
//     sex: "",
//     role: [],
//     birthday: "",
//     mainImage: "",
//     banner: {
//       fileList: [
//         {
//           name: "food.jpeg",
//           url: "https://fuss10.elemecdn.com/3/63/4e7f3a15429bfda99bce42a18cdd1jpeg.jpeg?imageMogr2/thumbnail/360x360/format/webp/quality/100"
//         }
//       ]
//     }
//   }
// };
</script>

<template>
  <div v-if="JSON.stringify(formData) !== '{}'">
    <el-form
      class="el-form"
      ref="formRef"
      label-width="120px"
      :model="formData"
      :rules="rules"
      status-icon
      scroll-to-error
    >
      <el-form-item
        v-show="!i[0]?.hide"
        v-for="(i, iIndex) in formMessage"
        :key="iIndex"
        :prop="i[0]?.model || ''"
        :label="i[0]?.formItemLabel + '：'"
      >
        <div
          v-for="(j, jIndex) in i"
          :key="jIndex"
          :style="{ width: i.length === 1 ? '100%' : 'auto', 'margin-right': i.length === 1 ? '0' : '10px' }"
        >
          <el-input
            v-if="['text', 'password', 'textarea'].includes(j.type)"
            :type="j.type"
            v-model="formData[j.model]"
            :placeholder="'请输入' + j.label"
          />

          <el-input
            v-if="['number'].includes(j.type)"
            type="text"
            v-model="formData[j.model]"
            :placeholder="'请输入' + j.label"
            @input="formatNumber(j)"
            @blur="formData[j.model] = isNaN(Number(formData[j.model])) ? '' : String(Number(formData[j.model]))"
          />

          <el-select
            v-if="j.type == 'select'"
            v-model="formData[j.model]"
            :placeholder="'请选择' + j.label"
            @change="emit('selectChange', { rowIndex: iIndex, columnIndex: jIndex })"
          >
            <el-option v-for="opt in j?.options" :key="opt" :value="opt.value" :label="opt.text"></el-option>
          </el-select>

          <el-radio-group v-if="j.type == 'radio'" v-model="formData[j.model]">
            <el-radio v-for="(opt, optIndex) in j.options" :key="optIndex" :label="opt.value" size="large">
              {{ opt.text }}
            </el-radio>
          </el-radio-group>

          <el-checkbox-group v-if="j.type == 'checkbox'" v-model="formData[j.model]">
            <el-checkbox v-for="(opt, optIndex) in j.options" :key="optIndex" :label="opt.value" size="large">
              {{ opt.text }}
            </el-checkbox>
          </el-checkbox-group>

          <el-date-picker
            v-if="j.type == 'date-picker'"
            v-model="formData[j.model]"
            type="date"
            :placeholder="'请选择' + j.label"
            style="width: 100%"
          />

          <MyUpload v-if="j.type == 'upload-one'" type="one" :action="j.action" v-model:imageUrl="formData[j.model]" />

          <MyUpload
            v-if="j.type == 'upload-many'"
            type="many"
            :action="j.action"
            :fileData="formData[j.model]"
          ></MyUpload>
        </div>
      </el-form-item>

      <el-form-item :label="extraFormItemLabel + '：'" v-if="useExtraFormItem">
        <slot name="extraFormItem"></slot>
      </el-form-item>

      <el-form-item>
        <el-button size="large" @click="emit('cancel')">取消</el-button>
        <el-button size="large" @click="resetForm">清空</el-button>
        <el-button type="primary" size="large" @click="submit(formRef)">确定</el-button>
      </el-form-item>
    </el-form>
  </div>
</template>

<style lang="less" scoped>
.el-form {
  margin: 0 auto;
}
</style>
```

（3）注册/登录/权限管理

详见nest笔记

（4）支付

1. 防止恶意下单减少库存
   
   * 每个商品由商家设置单次最大购买数量
   
   * 如果有重复商品的订单，就不再允许下单，不过为了用户体验可以允许有几个重复商品的订单
   
   * 长时间（如2小时内）未支付的订单需要系统取消交易，释放库存，可以在创建订单时设置定时器实现

2. 创建订单：前端确认订单后，发过去商品信息、价格、收货地址等信息。若成功则扣减库存，创建订单，返回订单编号；若失败（如库存不足）则返回错误信息。

2.预支付：给自己的后端发请求，发过去订单编号，返回支付需要的参数

3.支付：发情支付的请求，返回二维码，通常后端返回的二维码不是图片的网络地址，而是普通的字符串，前段需要将其转化为二维码的网络地址才能在img标签使用：

```
pnpm install --save qr-image querystring
```

```
// 后端
import { imageSync } from 'qr-image';
import * as queryString from 'querystring'
;//...
const url = 'https://www.baicu.com';
const query = {aaa: 123};
const qrcode = imageSync(url, { type: 'svg});
const qrcodeWithQuery = imageSync(url + '?' + queryString.stringify(query), { type: 'svg});

// 前端
<div v-html="..."></div>
```

* 微信支付：wx.requestPayment({参数}) 参数为2得到的

4.查看订单是否支付成功：设定一个setInterval定时器，不断给自己的后端发请求，直到支付成功为止；在点击'我已支付成功'等其他情况也需要判断。

（5）刷新页面

在一些情况下有刷新页面的需求，不可能让用户自己按F5，所以需要代码中实现。

刷新页面也能够方便清除数据。

push和replace都不能从当前页面跳转到当前页面，所以无法实现刷新。

① 强制刷新

强制刷新等同于F5的效果，页面会重新加载。

route的params和query依然保留，没找到清除的方法。

刷新代码的后面不知道会不会执行，但是执行也没有意义了，因为是强制刷新。

```
location.reload()   //BOM
this.$router.go(0)  //Vue
uni.redirectTo({url: '你的当前页面路径'});  //uniapp
```

② 非强制刷新

我们刷新的目的是为了重置数据，所以可以利用重新加载组件和router-view，通过v-if的布尔值来控制重新加载。

route的params和query会保留。

刷新代码的后面会执行。

```
<template>
  <div> 
      <!-- <router-view v-if="isReload" /> -->
      <cpn v-if="isReload" />
      <button @click="myReload">刷新</button>
  </div>
</template>

<script>
import cpn from './cpn.vue'
export default {
  components: {
    cpn  
  },
  data(){
    return {
      isReload: true
    }
  },

  methods: {
    myReload(){
      // location.reload();
      // this.$router.go(0)

      this.isReload = false;
      //如果不写在nextTick里面而是写在外面，由于数据是异步更新，同步执行完后最后是true，相当于没变
      //this.isReload = true;
      this.$nextTick(() => {
        this.isReload = true;
      })
    }
  },


}
</script>


...子组件
export default {
  data(){
    return {a: 0}  
  },
  mounted()[
    setInterval(() => {
      this.a++;
    },100);
  ]
}
...
```

如果想在后代组件中控制刷新，可以通过provide、inject进行依赖注入：

```
<template>
  <div> 
      <!-- <router-view v-if="isReload" /> -->
      <cpn v-if="isReload" />
  </div>
</template>

<script>
import cpn from './cpn.vue'
export default {
  components: {
    cpn  
  },
  data(){
    return {
      isReload: true
    }
  },
  methods: {
    myReload(){
      // location.reload();
      // this.$router.go(0)

      this.isReload = false;
      //如果不写在nextTick里面而是写在外面，由于数据是异步更新，同步执行完后最后是true，相当于没变
      //this.isReload = true;
      this.$nextTick(() => {
        this.isReload = true;
      })
    },
    provide(){
      return {
        myReload: this.myReload
      }
    }
  },


}
</script>


...后代组件
<template>
  <div>
    <button @click="myReload">刷新</button>
  </div>
</template>

<script>
export default {
  inject: ['myReload'],
  data(){
    return {a: 0}  
  },
  mounted()[
    setInterval(() => {
      this.a++;
    },100);
  ]
}
</script>
```

如果有已进入页面就刷新一次的需求，不要放到生命周期里面，否则会一直死循环，解决方法：可以在父组件data或路由meta中用一个变量控制只刷新一次。

③ 其他

上面的方法都会保留params和query，如果想去除他们，可以先跳到其他路由再跳回来。

（也可以watch监听route解决）

```
router.push('/').then(() => {
  router.push('/Search').then(() => {
    router.go(0);  
  });
});
```

## 5 常用动画

（1）当滚动到所在位置时的弹出动画

```
<script setup lang="ts">
import { ref, onMounted } from "vue";

//节流
function throttle(fn: Function, delay: number = 1000) {
  let flag: boolean = true;
  return function (...rest: any[]) {
    if (flag) {
      setTimeout(() => {
        fn(...rest);
        flag = true;
      }, delay);
      flag = false;
    }
  };
}

//距离页面顶部的偏移，如果祖先都没有设置定位的话可以用offsetTop代替
function offsetPage(el: HTMLElement | null) {
  const rect = el.getBoundingClientRect();
  const scrollLeft = window.scrollX || document.documentElement.scrollLeft;
  const scrollTop = window.scrollY || document.documentElement.scrollTop;
  return {
    left: rect.left + scrollLeft,
    top: rect.top + scrollTop,
  };
}

let isShow = ref<boolean>(false);
let boxRef = ref<HTMLElement | null>(null);

onMounted(() => {
  if (window.scrollY + window.innerHeight / 2 > offsetPage(boxRef?.value).top) {
    isShow.value = true;
  }

  window.addEventListener(
    "scroll",
    throttle(() => {
      console.log(111);
      if (
        window.scrollY + window.innerHeight / 2 >
        offsetPage(boxRef?.value).top
      ) {
        isShow.value = true;
      }
    }, 100)
  );
});
</script>

<template>
  <!-- 
    注意v-show隐藏的元素的偏移一直为0，v-if更是没有创建实例，
    所以滚动距离要和外面的盒子的offsetTop比较 
  -->
  <div ref="boxRef">
    <transition name="box" v-show="isShow">
      <slot name="transition"></slot>
    </transition>
  </div>
</template>

<style lang="less" scoped>
.box-enter-from {
  opacity: 0;
  transform: translatey(100%);
}
.box-enter-to {
  opacity: 1;
  transform: translatey(0);
}
.box-enter-active {
  transition: all 1s;
}
</style>
```

## 6 常见应用

（1）电商

（2）后台管理系统

后台管理系统可以简化使用者对数据库的操作，如电商的卖家、企业员工管理等。

整个系统只有一个超级管理员，拥有全部权限，用户不是注册来的而是管理员添加的，但用户可修改密码。
管理员主要有对用户、角色、权限、菜单的管理，用户具备角色的权限+管理员单独给的权限=该用户权限列表。

一般初始不需要默认路由，初始只需要配置登录页面，404页面等基本页面的路由，其他路由和默认路由都根据权限动态添加。

github上有模板，可以基于模板进行二次开发：

* vue-admin-template    简洁版

* vue-element-admin    加强版

（3）音频/视频

（4）网盘

# 三、异常处理

为了项目稳定，在出现错误时不停止服务，在可能出错的代码做异常处理。

（1）错误类型

主要分为接口异常和代码逻辑异常

接口异常是在请求后端接口时出现的异常，可能是请求失败、也可能是请求得到状态码表示错误。一般的处理办法是在相应拦截器中统一处理请求失败和根据状态码做相应的处理。

代码逻辑错误是前端逻辑上的错误发生的异常，js代码通过try...catch...处理，而Vue最常见的方法是使用全局错误处理函数app.config.errorHandler收集错误。

（2）错误上报给后端

收集到错误后需要处理异常，分析错误信息。

如果是接口错误，需要上报接口信息、参数、状态码等。

如果是前端代码异常，收集错误信息即可。

还可以收集项目名称、版本、环境、用户信息、所在页面等，这些在vuex获取即可。

收集完错误就上报给后端。

# 四、常用第三方库

## 1 CSS库

（1）tailWindCss

```
npm install --save-dev tailwindcss postcss autoprefixer
```

初始化配置文件：

```
npx tailwindcss init
```

（2）动画库animate.css

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

（3）unoCss

css原子化，集成了tailwindcss，bootstarp等css框架

## 2 数据可视化

echarts

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

封装成组件：

```
<script setup lang="ts">
import { ref, onMounted } from "vue";
import * as echarts from "echarts";

const props = withDefaults(
  defineProps<{
    width?: number;
    height?: number;
    options: any;
  }>(),
  {
    width: 300,
    height: 200,
    options: () => {
      return {};
    }
  }
);

const echartsRef = ref<HTMLElement | null>(null);

onMounted(() => {
  echartsRef.value!.style.width = props.width + "px";
  echartsRef.value!.style.height = props.height + "px";

  const myChart = echarts.init(echartsRef.value!);
  myChart.setOption(props.options);
});
</script>

<template>
  <div ref="echartsRef"></div>
</template>
```

数据大屏：

即数据可视化的大屏幕，因为可能会展示在不同大小的屏幕上，所以需要做适配，但是vw，vh对目前echars中的文本无效，所以需要采用别的方法，这里使用 transform: scale() 的方法实现适配。

需要注意的是，scale的的缩放是基于缩放目标的中心点的，所以缩放后相对位置不会在原处，所以需要先将缩放目标水平垂直居中在屏幕中心。

flex的水平垂直居中配合scale不知道为什么会改变缩放目标的宽高比，所以不能用flex做居中，这里采用固定定位的方式做居中，下面是一个例子：

```
<script setup lang="ts">
import { ref, watch, onMounted, onBeforeUnmount } from "vue";

const containerRef = ref<HTMLElement | null>(null);

function windowResize() {
  if (!containerRef.value) return;

  const scaleX = window.innerWidth / 1920;
  const scaleY = window.innerHeight / 1080;

  containerRef.value.style.transform = `scale(${scaleX < scaleY ? scaleX : scaleY})`;
}

/* 在进入页面时就进行适配
  本来可以在onMounted里面的，但是一般数据都是后端请求来的，而echarts对数据变化时不会
  更新图表的，所以需要v-if等数据请求完再渲染图标，但是如果用了v-if的话，onMounted的时
  机是在v-if为false的时候，而不是在v-if为true的时机，所以onMounted中ref实例还是null
  ，所以只能在watch监听ref实例，等ref实例有了再进行第一次适配  
*/
watch(
  () => containerRef.value,
  () => {
    if (containerRef.value) windowResize();
  }
);

onMounted(() => {
  window.addEventListener("resize", windowResize);
});

onBeforeUnmount(() => {
  window.removeEventListener("resize", windowResize);
});
</script>

<template>
  <div id="sales-data">
    <div class="container" ref="containerRef"></div>
  </div>
</template>

<style lang="less" scoped>
#sales-data {
  height: 100vh;
  background: url("@/assets/img/common/salesData_background.jpg") no-repeat;
  background-size: 100% 100%;

  .container {
    position: absolute;
    top: 50%;
    left: 50%;
    margin-left: -960px;
    margin-top: -540px;
    width: 1920px;
    height: 1080px;
    border: 10px solid #fff;
  }
}
</style>
```

## 3 富文本编辑器

## 4  组件库

Vue的template和uniapp的block，由于只作包裹作用而不渲染，无论是否使用组件库，在某些情况（如需要一个不渲染的盒子来用v-if，v-for等）都可以使用。

elementui和elementplus

ant-design

vant

组件库修改样式：

F12找到组件库DOM对应的类名

- App.vue全局修改，缺点是会影响所有组件

- 样式穿透，详见Vue，Vue2使用 /deep/ 选择器，Vue3推荐使用 :deep(选择器)

# 五、前端性能优化

（1）概念

前端性能指的就是各个方面的快不快、流不流畅。按照官方的说法，性能就是网站或应用的客观度量和可感知的用用户体验。

客观度量：加载快不快，DOM元素是否可用（比如表单有时候因为加载慢导致不可用），平滑交互（动画、滚动等留不流畅）。

可感知的用户体验：在性能已经做到极致了，无法继续优化的时候，需要提供感知表现给用户，如loading，进度条等。

（2）知识体系结构

前端性能优化总体需要了解四个部分，性能指标、性能检测工具、前端生命周期和具体的优化方案。

熟悉各种性能指标后，才能看懂性能检测工具的报告、然后法根据报告分析前端生命周期的各个部分，使用具体的优化方案。

（3）迭代优化

性能优化不是一锤子买卖，而是持续性的过程，因为项目是会不断更新的，更新可能会使性能有不同程度的变化。

迭代优化可以做一个性能监测来持续监测性能。

# 1 性能指标

性能指标可以清晰地评估性能多快算快，多慢算慢。性能指标不是单一的，而是有很多的指标。Google总结开发者需要重点关注的几个指标：

## 1.1 RAIL性能模型

R（Response响应）：网站应当尽可能块地响应用户，通常要在100ms以内。响应指的是各种交互的回馈，在需要较长时间才能响应时需要提供给用户感知体验（进度条，loading等）。

A（Animation动画）：动画要求在每秒60帧以上（16ms以内）

I（Idle空闲）：js是单线程的，如果某个js执行片段执行过久（如百万次的for循环），就会占用js主线程导致下面的代码很久后才会执行。所以要求每个任务需要在50ms内完成，超过50ms的就是长任务，需要把长任务划分到50ms以内的片段中，

L（Load加载）：就可能在1s内完成网站的加载并且用户能搞开始交互，若网络条件和计算机硬件比较差，也需要在5s内。

## 1.2 基于用户体验的性能指标

（1）FCP（First Contentful Paint 首次内容绘制）

指的是从空白到浏览器首次绘制第一个DOM内容的时间（也叫白屏时间），内容包括文本、图片、非白色的canvas/svg等这些有意义的内容。

指标：

| 2s以内  | 较好        |
| ----- | --------- |
| 2s-4s | 中等，要开始优化了 |
| 超过4s  | 差         |

（2）LCP（Largest Contentful Paint 最大内容绘制）

指的是当前屏幕中，最大的内容加载的时间，最大内容通常情况下图片居多。

最大内容会随着屏幕滚动而变化，由于屏幕的滚动不断出现新内容，所以最大内容也不一定是最后加载完的。

指标：

| 2.5s以内  | 较好        |
| ------- | --------- |
| 2.5s-4s | 中等，要开始优化了 |
| 超过4s    | 差         |

（3）FID（First Input Delay 首次输入延迟）

有时候DOM已经渲染出来了，但是用户并不能马上去交互，需要等一段时间，这就是首次输入延迟。造成的原因是浏览器的主线程忙于做其他事情（如百万次for循环），不能及时响应用户。

主要是表单受首次输入延迟影响。

指标：

| 100ms以内     | 较好        |
| ----------- | --------- |
| 100ms-300ms | 中等，要开始优化了 |
| 超过300ms     | 差         |

（4）TTI（Time to Interactive 网页第一次完全达到可交互状态的时间点）

从空白到第一次能流畅完全交互的时间。具体衡量的标准是最后一个长任务完成且随后的5s内网络和主线程是空闲的（超过50ms的就是长任务）。

指标：

| 3.8s以内    | 较好        |
| --------- | --------- |
| 3.8s-7.3s | 中等，要开始优化了 |
| 超过7.3s    | 差         |

（5）TBT（Total Block Time 总阻塞时间）

度量FCP到TTI的总阻塞时间，即每个长任务造成的阻塞时间（长任务完成时间-50ms）之和。

指标：

| 300ms以内     | 较好        |
| ----------- | --------- |
| 300ms-600ms | 中等，要开始优化了 |
| 超过600ms     | 差         |

（6）CLS（Cumulative Layout Shift 累计布局偏移）

测量珍整个生命周期中发生的每个意外的布局偏移位的所有单独布局移位分数的总和，也就是页面视觉稳定性提升的指标。

比如，页面有两个盒子A，B，B在A上面。A渲染完毕并可交互，B未渲染，当B渲染完时，会把A定到下面去，这就是布局偏移，也叫布局抖动。

指标衡量抖动时间总和

指标：

| 100ms以内     | 较好        |
| ----------- | --------- |
| 100ms-200ms | 中等，要开始优化了 |
| 超过200ms     | 差         |

（7）Speed Index

首屏加载时间

## 1.3 Web Vitals和Core Web Vitals

Google在2020年推出的为了降低学习成本，为网站提供了统一的性能衡量标准Core Web Vitas。就是对基于用户体验的呢几个性能指标的简化，简化成了三个指标：LCP、FID和CLS。

## 2 性能检测工具

各个性能指标都是三个级别，较好（绿色），中等（橙色），差（红色）。

## 3 前端生命周期

需要具备操作系统和计算机网络的相关知识。

### 3.1 浏览器

早期的浏览器是单进程+多进程，网络、渲染等都是一个线程。由于进程中的某个线程出现错误会导致整个进程当机，所以早期的浏览器非常容易崩，如一个页面崩溃整个浏览器都会崩溃。

2008年推出的chrome及以后的浏览器是多进程+多线程，有一个主进程负责浏览器菜单栏，前进后退，管理子进程等，网络、渲染等都变成了一个个子进程，每个tab标签都会开启一个独立的渲染进程，进程间通过IPC通信。chrome中，shift+esc 可以打开浏览器的任务管理器，查看各个进程。

### 3.2 前端生命周期

就是从输入url到页面展示的整个过程：

（1）输入url

url：统一资源定位符，用于定位互联网上的资源，又称网址。

输入时，会根据历史记录和书签来只能提示。

输入完成按下回车后，首先检查是否是合法的url：

- 若合法，判断url是否完整，若不完整会自动补全前缀/后缀

- 若不合法，将输入内容作为搜索条件适宜用户默认的搜索引擎进行搜索

（2）开启网络请求进程，DNS解析

上一步若url合法，则会开启网络请求进程。

浏览器无法通过url直接找到ip地址，所以需要进行DNS解析。

DNS解析过程详见计算机网络笔记

（3）浏览器开启网络请求线程，与服务器建立TCP连接

根据ip地址，浏览器会用一个随机的端口和服务器的80端口发起TCP连接请求。请求到达服务器后，通过三次握手建立TCP连接。

（4）发送http请求或https请求

发送一个初始的get请求，通常是请求html文件。请求进入无武器之前一般会进入反向代理服务器（反向代理服务器的功能主要是负载均衡、安全防火墙、数据压缩等），再转发到对应的应用服务器。

（5）服务器响应请求

服务器返回http响应报文，内容包含响应头和html正文。

（6）浏览器解析、渲染页面

不同的浏览器引擎渲染过程是不同的，以谷歌浏览器为例：

1. 处理HTML标记构建DOM树，处理CSS标记构建CSS OM树

2. 将DOM树和CSS OM树合并为一颗渲染树（Render Tree），渲染树不会包含隐藏（如display: none）的元素。因此渲染树和DOM树的节点数可能不一样。

3. 根据渲染树来布局，以计算每个节点的几何信息，最终将各个节点渲染到页面上，此阶段可能会发生回流或重绘

（7）请求结束，断开TCP连接

现在的浏览器为了优化请求耗时，默认都会开启持久链接，只有在页面关闭时才会四次挥手断开TCP连接。

## 4 具体的优化方案

https://segmentfault.com/a/1190000041753539

### 4.1 请求与响应优化

（1）DNS优化

一个项目为了提高请求的并发量，通常会有多个域名（一般2-4个）。

DNS的优化主要有几个方面：

* dns-prefetch（dns预取），利用空白时间来预解析DNS
  
  ```
  <!--
  设现在网站有亮哥哥域名，a.com和b.com
  html是从上到下解析，解析到<body>时才会开始NDS解析去请求资源，那<body>之前花费时间
  都是空白时间，可以利用这段空白时间先进行DNS的预解析
  dns-prefetch是异步的，不用担心阻塞
  -->
  <head>
    <link rel="dns-prefetch" href="//a.com" />
    <link rel="dns-prefetch" href="//b.com" />
  </head>
  <body>
  </body>
  ```

* 使用CDN加速域名，自己搭建DNS服务，尽可能使用A或AAAA标记代替CNAME，增加DNS的缓存时间以此减少DNS查找次数。这几个都是在后端优化的。

在测试DNS优化的时候，需要清除DNS缓存来测试优化效果。

（2）http长连接和管道机制

目前，请求默认都是长连接并有管道机制，不需要代码处理，此处制作了解即可。

早期的http都是短连接，一次请求一次相应，所以每次请求都要反复建立断开连接，非常消耗性能。在1997年http1.1发布之后加入了长连接，只需要建立一次连接在里面进行多次的请求响应，不需要重复建立断开连接，提升了数据传输的效率。

此外，http1.1还推出了管道机制，在一个连接中可以并发发送多个请求，但是响应不是并发的。http2后响应也是并发的。

长连接有两个缺陷：

* 由于http2之前长连接的响应不是并非噶的，虽然请求并发，但是服务器也只能处理完一个响应后再处理下一个，因此响应会出现对头堵塞。解决方案是尽可能减少请求，或多开TCP连接（使用一个项目使用多个域名），或使用http2

* 请求并发的数量也是有限制的，解决方案是多开TCP连接。

（3）尽可能减少非必要的请求

除了解决对头堵塞外，还能较少服务器的压力。

* 项目打包后，会自动合并文件，减少请求次数。这个了解即可。

* 业务逻辑中使用防抖和节流，详见JavaScript笔记。

（4）http缓存

（5）减少不必要的重定向

（6）静态资源使用CDN

内容分发网络（CDN）是一组分布在多个不同地理位置的 Web 服务器。我们都知道，当服务器离用户越远时，延迟越高。CDN 就是为了解决这一问题，在多个位置部署服务器，让用户离服务器更近，从而缩短请求时间。

### 4.2 指标优化

（1）LCP

- 服务端响应时间
- Javascript和CSS引起的渲染卡顿
- 资源加载时间
- 客户端渲染

（2）FID

- 减少第三方代码的影响
- 减少Javascript的执行时间
- 最小化主线程工作
- 减小请求数量和请求文件大小

（3）CLS

- 图片或视屏元素有大小属性，或者给他们保留一个空间大小，设置width、height，或者使用 [unsized-media feature policy](https://link.segmentfault.com/?enc=x0b1tWIw7HNM%2FWoFjUubgg%3D%3D.GnEEoFO3q3OHGvCxgsei6DwcMBHwsgyzSrAUVKGqRzp9ZCkhF5j2AcNjjrJz1I6jNqS4UE%2FGdYQKl%2B85mn43Gn%2BsA2Aua%2FsBJ0XgNKzDgxF27qxy%2FZ3NTLsBRRYTNSX0YAT2Y8J%2FVwaZ9eyjXnFJ8jejVyMJueaGtInp%2B5K8Fhl19cXKLKUwW4PUtPzROFCF) 。
- 不要在一个已存在的元素上面插入内容，除了相应用户输入。
- 使用animation或transition而不是直接触发布局改变。

### 4.3 渲染优化

（1）较少JS阻塞

JS 的作用在于修改网页的方方面面：内容、样式以及它如何响应用户交互。这“方方面面”的修改，本质上都是对 DOM 和 CSSDOM 进行修改。因此 JS 的执行会阻止 CSSOM，在我们不作显式声明的情况下，它也会阻塞 DOM。

加载或者执行JS时会阻塞对标签的解析，也就是阻塞了DOM 树的形成，只有等到JS执行完毕，浏览器才会继续解析标签。没有DOM树，浏览器就无法渲染，所以当加载很大的JS文件时，可以看到页面很长时间是一片空白。

优化方案：

- CSS 资源优于 JavaScript 资源引入

- 避免开销较大的同步任务，如十万次的for循环

- JS 应尽量少影响 DOM 的构建，即减少DOM操作

- 不要重复造轮子，自己写的代码再如何优化，都比不上原生方法。因为原生方法是用低级语言写的（C/C++），并且被编译成机器码，成为浏览器的一部分。当原生方法可用时，尽量使用它们，特别是数学运算和 DOM 操作。

- 尽量避免添加大量的JS动画，CSS3动画和 Canvas 动画都比 JS 动画性能好。  
  使用`requestAnimationFrame`来代替`setTimeout`和`setInterval`，因为`requestAnimationFrame`可以在正确的时间进行渲染，`setTimeout` 和`setInterval`无法保证渲染时机。不要在定时器里面绑定事件。

- 使用事件委托

- 使用防抖和节流

- defer（延缓）模式，defer方式加载 script, 不会阻塞 HTML 解析，等到 DOM 生成完毕且 script 加载完毕再执行 JS。
  
  ```
  
  ```
  
  <script defer></script>
  
  ```
  
  ```

- async（异步）模式,async属性表示异步执行引入的 JS，加载时不会阻塞 HTML解析，但是加载完成后立马执行，此时仍然会阻塞 load 事件。
  
  ```
  <script async></script>
  ```

（2）较少CSS阻塞

上面提到 DOM 和 CSSOM 合力才能构建渲染树。这一点会给性能造成严重影响：默认情况下，CSS 是阻塞的资源。浏览器在构建 CSSOM 的过程中，不会渲染任何已处理的内容，即便 DOM 已经解析完毕了。

只有当我们开始解析 HTML 后、解析到 link 标签或者 style 标签时，CSS 才登场，CSSOM 的构建才开始。** 很多时候，DOM 不得不等待 CSSOM。因此我们可以这样总结：

CSS 是阻塞渲染的资源。需要将它尽早、尽快地下载到客户端，以便缩短首次渲染的时间。**尽早（将 CSS 放在 head 标签里）和尽快（启用 CDN 实现静态资源加载速度的优化）

优化方案：

* 使用字体图标，而非图片图标

* 尽量降低CSS选择器的复杂性，浏览器读取选择器，遵循的原则是从选择器的右边到左边读取。看个示例：
  
  ```
  #block .text p {
    color: red;
  }
  /*
  1.查找所有 P 元素。
  2.查找结果 1 中的元素是否有类名为 text 的父元素
  3.查找结果 2 中的元素是否有 id 为 block 的父元素
  CSS 选择器优先级：内联 > ID选择器 > 类选择器 > 标签选择器
  根据以上两个信息可以得出结论：
  减少嵌套。后代选择器的开销是最高的，因此我们应该尽量将选择器的深度降到最低（最高不要超过三层），尽可能使用类来关联每一个标签元素
  关注可以通过继承实现的属性，避免重复匹配重复定义
  尽量使用高优先级的选择器，例如 ID 和类选择器。
  避免使用通配符，只对需要用到的元素进行选择
  */
  ```

* 较少回流与重绘

* 使用 flexbox 而不是较早的布局模型，flex的性能更好

（3）图片资源优化

一般来说，图片资源时网站中最花费性能的资源

优化方案：

* 使用雪碧图（精灵图），雪碧图的作用就是减少请求数，而且多张图片合在一起后的体积会少于多张图片的体积总和，这也是比较通用的图片压缩方案

* 图片压缩，压缩方法有两种，一是通过在线网站进行压缩，二是通过 webpack 插件 image-webpack-loader。它是基于 imagemin 这个 Node 库来实现图片压缩的。使用很简单，我们只要在`file-loader`之后加入 `image-webpack-loader` 即可：
  
  ```
  npm install --save-dev image-webpack-loader
  
  //webpack配置
  module: {
      rules: [
        {
          test: /\.(png|jpe?g|gif|svg)(\?.*)?$/,
          use: [
            {
              loader: 'file-loader',
              options: {
                name: '[name]_[hash].[ext]',
                outputPath: 'images/'
              }
            },
            {
              loader: 'image-webpack-loader',
              options: {
              // 压缩 jpeg 的配置
              mozjpeg: {
                progressive: true,
                quality: 65
              },
              // 使用 imagemin**-optipng 压缩 png，enable: false 为关闭
              optipng: {
                enabled: false
              },
              // 使用 imagemin-pngquant 压缩 png
              pngquant: {
                quality: '65-90',
                speed: 4
              },
              // 压缩 gif 的配置
              gifsicle: {
                interlaced: false
              },
              // 开启 webp，会把 jpg 和 png 图片压缩为 webp 格式
                webp: {
                quality: 75
              }
            }
          }
        ]
      }
    ];
  }
  // ...
  ```

* 图片懒加载，若图片未进入可视区域则不加载，当图片进入可视区域后才开始加载。
  
  可以直接使用图片懒加载插件：
  
  ```
  # 在图片需要在屏幕上显示时，才加载图片，优化性能。
  npm install --save vue-lazyload 
  
  //main.js
  impoet VueLavyLoad from 'vue-lazyload'
  Vue.use(VueLazyLoad,{
    //此对象可写可不写，用来设置加载时显示的图片，加载失败时的图片等
  })
  
  //用到的地方中
  <img v-lazy="图片的url" />
  ```
  
  uniapp的image直接有一个属性可以设置懒加载，但是有平台限制，具体看文档：
  
  ```
  <image src="..." lazy-load />
  ```
  
  自己实现图片懒加载：
  
  初始时，将图片url放到自定义属性data-src中，当滚动到该图片出现时，再将url赋值给src加载图片。
  
  此方法的致命缺点是图片加载完后，还会继续监听，且必须使用节流否则监听太频繁了。
  
  ```
  <body>
      <div><img data-src="e://lgx/1.png"></div>
      <div><img data-src="e://lgx/1.png"></div>
      <div><img data-src="e://lgx/1.png"></div>
      ...
  </body>
  
  <script>
  /*
  可视区域高度：
  window.innerHeight
  document.body.clientHeight
  图片是否进入可视区域：
  img.getBoundingClientRect().top < window.innerHeight
  img.offsetTop < document.body.scrollTop + window.innerHeight
  */
  
  let imgs = document.querySelectorAll('img');
  function lazyLoad(){
    imgs.forEach(i => {
        //获取图片当前距离视口顶部的距离
      let top = i.getBoundingClientRect().top;
      //如果top < 视口高度,说明图片已在可视区域或在可是区域上方,可以加载图片了
      if(top < window.innerHeight){
        i.setAttribute('src',i.getAttribute('data-src'));
      }
    });
  }
  //初始没有滚动时执行一次
  lazyLoad();
  window.addEventListener('scroll',lazyLoad);
  </script>
  ```
  
  更好的实现方式是使用IntersectionObserver，它是浏览器提供的构造函数（一些低版本浏览器可能不支持如IE），它的功能是交叉观察，也就是观察的元素出现在可视窗口后会发生回调，因此可处理图片懒加载。
  
  优点是不需要节流，且图片加载后可以取消对该图片的观察，以后都不再观察该图片：
  
  ```
  <body>
      <div><img data-src="e://lgx/1.png"></div>
      <div><img data-src="e://lgx/1.png"></div>
      <div><img data-src="e://lgx/1.png"></div>
      ...
  </body>
  
  <script>
  let imgs = document.querySelectorAll('img');
  let observer = new IntersectionObserver(entry => {
    //当被观察的DOM与可视窗口交叉哦，也就是出现在可视窗口后，回调该函数，entry为所有被观察的DOM
    entry.forEach(i => {
      //isIntersecting的值若为true，则说明该DOM已进入过可视窗口
      if(i.isIntersecting){
        //target为被观察的DOM实例
        const image = i.target;
        image.setAttribute('src',image.getAttribute('data-src'));
        console.log('懒加载完一张图片');
        //懒加载完成后，不再观察此DOM实例
        observer.unobserve(image);
      }
    });
  })
  //对每个图片进行交叉观察
  imgs.forEach(i => {
    observer.observe(i); 
  });
  </script>
  ```

* 使用CSS3 代替图片，有很多图片使用 CSS 效果（渐变、阴影等）就能画出来，这种情况选择 CSS3 效果更好。因为代码大小通常是图片大小的几分之一甚至几十分之一。

* 使用 webp 格式的图片，WebP是 Google 团队开发的加快图片加载速度的图片格式，其优势体现在它具有更优的图像数据压缩算法，能带来更小的图片体积，而且拥有肉眼识别无差异的图像质量；同时具备了无损和有损的压缩模式、Alpha 透明以及动画的特性，在 JPEG 和 PNG 上的转化效果都相当优秀、稳定和统一。

### 4.4 Vue优化

相关的内容详见Vue笔记

* 使用TypeScript
- 路由懒加载和异步组件defineAsyncComponent，Suspense

- 适当使用keep-alive缓存组件、缓存路由，避免重复销魂/删除组件，且能保留状态

- 视情况选择v-show，v-if，视情况选择computed，watch，watchEffect；使用watch时需谨慎使用deep，因为开销挺大，仅在必要时使用。

- 使用v-for时，避免与v-if同时使用；必须要给key；数据分页/长列表使用虚拟列表

- 对不再改变的内容使用v-once/v-memo

- 按需定义响应式数据，不需要响应式的数据就不适用ref，reactive；减少大型不可变数据的响应性开销，如果数据非常多（如10w条），深层地递归做响应式有很大的性能开销，对于这种场景，可以使用shallowRef，shallowReactive

- 提高props的稳定性，稳定性值的是减少不必要的props，避免子组件过多更新；props尽量设置准确的类型和默认值，减少组件因为数据而出错

- 使用provide和inject解决数据多级传递问题，如果数据仅在多层嵌套的父子级组件中使用，那么就不用麻烦Vuex

- 不要为了使用Vuex而使用Vuex，能在组件内解决的问题就不要麻烦Vuex。Vuex中的数据需要绑定更多的依赖，所以Vuex中的数据越少越好；Vuex需要模块化

- 销毁组件前，必须要清空定时器、订阅，addEventListener等，防止内存溢出。因为组件销毁时只解绑指令，watch和组件的事件等

- 避免意外的全局变量，使用不当的闭包以及不使用的数据，防止内存泄漏

- 组件化开发，但不要过度分割，尤其是为了所谓的组件抽离将一些不需要渲染的组件特意抽出来，实际上组件的性能小号远大于DOM

- 模块化开发（代码分割），代码分割是指构建工具将构建后的 JavaScript 包拆分为多个较小的，可以按需或并行加载的文件。通过适当的代码分割，页面加载时需要的功能可以立即下载，而额外的块只在需要时才加载，从而提高性能。

- 按需引入，在使用任何东西时，若果能够按需引入就一定要按需引入，会提升很多性能，如Vue3的CompositionsAPI，组件库/字体图标/echarts等等第三方库的按需引入。此外，Vue3和一些第三方库都有自动按需引入的插件，自动按需引入就是不需要自己手动import {} 来引入，当代码写到的时候就会自动引入。

- 第三方库的开发时和运行时，npm装包时，默认是安装运行时依赖，只有加上参数-dev时才会安装开发时依赖。
  
  在装包的时候需要考虑该包是否需要在项目运行时使用，弱不需要就安装开发时依赖，这也是提升性能的一个点。

## 5 SEO优化

SEO（搜索引擎优化），搜索引擎本质是爬虫，SEO优化可以使得搜索引擎能更好地搜索到自己的网站。

不过像后台管理系统，小程序，app等这些不需要经过搜索引擎的项目，就不需要SEO了。

前端SEO只是在代码层面上的一些优化，只是SEO的一部分，更具体的就不是代码层面了。

常用方法：

* 尽量优化前端性化，防止加载超时使得爬虫放弃爬取网站内容

* TDK和favicon图标：
  
  TDK是网站的标题、关键字、描述，每个页面都可能不相同
  
  ```
  <head>
    <title>网站名(产品名)-介绍(不要超过30个汉字)</title>
    <meta name=”description” content=”网站详细说明，服务，特色，电话等”>
    <meta name=”keywords” content=”英文逗号隔开的6-8个关键词，方便搜索引擎搜索”>
  </head>
  ```
  
  favicon图标：
  
  一般作为缩略的网站标志，显示在浏览器的地址栏或tab标签上。
  
  需要将png的图片转换成.ico格式的图片并放到项目根目录中 [https://www.bitbug.net/](https://www.bitbug.net/) 引入：必须在放在head标签：
  
  ```
  <link rel=”shortcar icon” href=”xx.ico” type=”image/x-icon”>
  ```

* HTML标签：
  
  * 使用语义化标签而不是div
  
  * 使用合理的标签，如文本使用h1-h6，p，span
  
  * img：
    
    * alt属性：alt 属性可以在图片未成功显示时候，使用文本来代替图片的呈现，使“蜘蛛”可以抓取到这个信息。此外它还可以解决浏览器禁用图像或屏幕阅读器解析等问题。
    
    * 需要定义宽高，否则会引起页面重新渲染，影响加载速度
  
  * a：
    
    * a链接的rel='nofollow： 如果某个 <a>的链接不需要跟踪，那么添加 rel='nofollow' 即可通知“蜘蛛”忽略跟踪。因为“蜘蛛”分配到每个页面的权重是一定的，为了集中网页权重并将权重分给其他必要的链接，为不必跟踪的链接添加这个属性就显得很必要了。

* HTML结构：
  
  * HTML、CSS，JavaScript三者分离：如果在一个 HTML 页面中，编写大量的 CSS 样式或脚本，会拖慢其加载速度。
  
  * 扁平化结果：尽量减少HTML结构的层次，代码简洁清晰

* 内容：
  
  * 尽量独特丰富：如合理插入图片说明等，会被认为质量较高符合用户需求，从而提高 SEO 的排名。
  
  * 内容放到合适的位置：
  
  * * 重要内容的 HTML 代码放在最前面，h标签可以增加重要性
    
    * 重要内容不应该由 JavaScript 或 iframe 输出，爬虫没有办法读取 JavaScript ，一般不会去读取 iframe 中的内容。（SPA就会有这个问题，解决方法是SSR）
    
    * logo：h1提高重要性，a返回首页，a里面的文字会被搜索引擎收录（但是为了美观需要隐藏 font-size: 0; 或 text-indent: -99999px; overflow: hidden;）
      
      ```
      <div class=”logo”>
          <h1><a href=”index.html” title=”网站名称” >网站title</a></h1>
      </div>
      ```

# 六、前端网络安全

## 1 XSS攻击

Cross Ste Scripting（跨站脚本攻击），缩写就不是CSS是为了避免与css样式混淆。

# 七、兼容性与跨平台

## 1 浏览器兼容性

手机浏览器几乎没有兼容性问题，常见的PC浏览器如chroime、firefox、edge等也很少兼容性问题，浏览兼容性主要是指IE浏览器。

（1）HTML

首先可以将版本较新的IE浏览器的渲染模式换成edge或chrome浏览器的：

```
<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
```

（2）CSS

① 统一不同浏览器的标签样式

不同浏览器的HTML标签样式各不相同，需要统一它们的样式：

```
npm install --save normalize.css
```

```
// App.vue
<script>
import 'normalize.css'
</script>
```

② CSS属性前缀

css是会不断发布新特性的，但是把这些新特性纳入规范需要一段时间，而在这段时间中各家浏览器都可以自己实现这些新特性，但是由于没有CSS规范的约束，使得这个CSS属性在不同的浏览器中可能会出现解析不了的星狂。

解决方法是添加CSS属性前缀，前缀有：

* -webkit- (Chrome, Safari, Edge)

* -moz- (Firefox)

* -ms- (Internet Explorer, Microsoft Edge)

* -o- (Opera)

举个例子，如果你要使用 CSS3 动画

使用：

```
/* 没有前缀 */
.box {
  border-radius: 10px;
}

/* 加上前缀以保证在各家浏览器都能正常解析 */
-webkit-border-radius: 10px;
  -moz-border-radius: 10px;
  -ms-border-radius: 10px;
  -o-border-radius: 10px;
  border-radius: 10px;
```

但是十分的麻烦，所以需要借助postcss，postcss可以自动加前缀，且还附带转化css的功能

webpack、vite等的postcsss默认配置基本够用，如果需要另外配置，则配置 .postcss.config.js

③ 根本不支持的css属性

低版本IE浏览器对这些新特性没有进行实现，所以加前缀没有用，解决方法有以下几种：

* 使用条件注释：条件注释是一种只在特定版本的 IE 浏览器中执行的注释语句。你可以使用条件注释来针对不同版本的 IE 浏览器提供不同的 CSS 样式表。例如，你可以使用如下代码来为 IE6 提供专门的样式表：
  
  ```
  <!--[if IE 6]>
    <link rel="stylesheet" type="text/css" href="ie6.css" />
  <![endif]-->
  ```

* 使用 CSS Hack：CSS Hack 是一种通过使用浏览器私有属性来实现不同浏览器间的兼容性。但是，使用 CSS Hack 可能会导致代码可读性变差，不利于维护，需要谨慎使用。

* 使用 Polyfill 或 JavaScript 库：一些 Polyfill 或 JavaScript 库，例如 Respond.js、CSS3PIE 等，可以让低版本的 IE 浏览器支持某些新的 CSS 属性或特性。

（3）JS

使用babel将js转换指定版本，如es5或更低的版本，webpack、vite等的默认配置基本够用，如果需要另外配置，则配置 .babel.config.js

## 2 移动端跨平台

各种小程序、安卓、ios的兼容。

# 八、项目部署到Linux服务器

node开发的后端启动后就行

vue项目需要先打包，打包得到的所有文件放到了另一个express项目的public文件夹中，并修改访问端口为80，然后npm start

## 1 环境搭建

购买云服务器，修改密码，开放端口，连接ssh

windows上的cmd：

```
ssh root@服务器ip
```

windows的cmd非常不好用，推荐自行下载cmder，也可以用xshell，宝塔等。

连接到服务器后，配置Linux服务器的系统环境：

安装软件：

yum安装后会放在 /etc ，wget下载后解压安装后放在 /usr/local，wget下载的压缩包可以统一放到一个地方，如 /usr/src，方便管理：

```
yum update
yum install -y git gcc gcc-c++ cmake ncurses ncurses-devel bison
yum install -y openssl openssl-devel pcre pcre-devel zlib zlib-devel
yum install -y p7zip
# 7z 的解压命令 7za x 文件

# 创建公钥，并安装git：
cd ~/.ssh
ssh-keygen -t rsa -C "邮箱" 回车执行，再回车三次
cat ~/.ssh/id_rsa.pub 复制输出得到内容到github
//安装git：
yum install git
git config --global user.name "xxx"
git config --global user.email "xxx"
```

安装node：

```
cd /usr/src 
wget https://nodejs.org/dist/v9.3.0/node-v9.3.0.tar.gz
tar -xf node-v9.3.0.tar.gz
cd node-v9.3.0
./configure
make && make install

# 更新node到较新版本，n也可以款速切换node版本，并安装pnpm，ts
npm install -g n pnpm typescript ts-node

# 不要用n latest安装最新版本，最新版本node17不稳定
# 安装node16版本
n 16

# n的使用：https://segmentfault.com/a/1190000015302680
```

python：

```
# linux自带python，不过使用python3需要戴上3
pip3 install --upgrade pip
pip3 install numpy==1.19.3
pip3 install pandas==0.23.4
pip3 install matplotlib
```

安装nginx：

```
cd /usr/src
wget https://nginx.org/download/nginx-1.19.9.tar.gz
tar -zxvf nginx-1.19.9.tar.gz
cd nginx-1.19.9
./configure --with-http_gzip_static_module
make && make install

# 查看是否安装成功
whereis nginx

# 开启nginx服务
cd /usr/local/nginx/sbin
./nginx

# 查看服务是否开启成功
ps -ef | grep nginx

# 浏览器输入服务器ip，若出现nginx欢迎页面则说明配置成功

# 重启nginx
cd /usr/local/nginx/sbin
./nginx -s reload
```

安装mysql8：

```
mkdir /usr/local/mysql8
cd /usr/local/mysql8

wget https://dev.mysql.com/get/mysql80-community-release-el7-2.noarch.rpm

yum -y install mysql80-community-release-el7-2.noarch.rpm
# 如果这一步报错，就需要从CentOS 8 迁移到CentOS Stream 8，换成下面命令
# dnf --disablerepo '*' --enablerepo=extras swap centos-linux-repos centos-stream-repos
# yum -y install mysql80-community-release-el7-2.noarch.rpm

yum -y install mysql-community-server
# 如果这一步报错，就换成执行下面命令
# yum module disable mysql
# yum -y install mysql-community-server --nogpgcheck

# 启动mysql服务
systemctl start  mysqld.service

# 查看mysql初始密码，输出的最后面是 root@localhost: xxx   xxx就是初始密码
grep "password" /var/log/mysqld.log

# 修改mysql密码
mysql -u root -p
ALTER USER '用户名'@'localhost' IDENTIFIED BY '新密码';
quit;

# 最后，可以查看mysql状态
systemctl status mysqld.service 
```

安装宝塔，方便操作服务器，并能上传文件到服务器：

```
cd /usr/src
yum install -y wget && wget -O install.sh https://download.bt.cn/install/install_6.0.sh && sh install.sh ed8484bec
```

查看宝塔面板地址，账号和密码：

```
# 外网宝塔地址就是可以在浏览器访问自己服务器的宝塔面板
/etc/init.d/bt  default
```

注意需要打开对应的端口才能访问。

其他操作，如修改宝塔密码：

```
bt
```

## 2 打包

### 2.1 后端

```
pnpm run build
```

按理说打包出来 dist 中应该只有一个 main.js，但是却有很多文件，而且也没有打包 node_modules 中的依赖，使用依赖是靠 ./node_modules，可能是官方的一些考虑才这样做。如何想打包成单独的 main.js ，可以在 package.json 的 build 命令增加 --webpack 参数，想要打包 node_modules 的依赖需要自行配置 webpack.config.js（但是没有成功）。

所以，只能在服务器中 git clone 下来整个项目，pnpm install 安装依赖，再 pnpm run build 打包，最后执行 node ./dist/main.js

### 2.2 前端

（1）减小打包体积

先确保代码中均使用了路由懒加载，图片懒加载，第三方库按需加载。

查看打包分析报告：

```
pnpm install -D rollup-plugin-visualizer
```

```
// vite.config.ts
import { visualizer } from "rollup-plugin-visualizer";

export default defineConfig({
  plugins: [
    visualizer()
  ]
})
```

配置完成后，npm run build 项目根目录就会生成打包报告 stats.html

接下来继续减小打包体积：

① 使用CDN

若不适应CDN，则项目中使用的库如vue，elementplus按需引入的资源会被打包到dist中，这会大大增加打包体积，所以可以使用CDN。

```
pnpm install -D vite-plugin-cdn-import
```

```
// vite.config.ts
import { Plugin as importToCDN } from "vite-plugin-cdn-import";

/* 注意
 * 如果某包使用了CDN，那么它的依赖的包也要CDN，比如elementplus使用了CDN，那么
   它依赖的vue也要使用cdn，且需要注意先后顺序
 * pinia中会用到 vue-demi包，所以也需要 cdn 引入 vue-demi
 * 使用 cdn 的库，就不能再将其配置为 autoimport
 * name是库的名字，var是导入该库的变量名，path是cdn链接，css是css的cdn链接，比如：
   import * as echarts from 'echarts'; name 和 var 就是 echarts
   import ElementPlus from 'element-plus'; name 就是 element-plus 和 var 就是 ElementPlus
 * 使用 cdn 后，打包后的 index.html 就会自动加上 cdn，而在项目代码中各种 import 
   都不用修改，该 import 的额import， 该 use 的 use。

 */

export default defineConfig({
  plugins: [
    importToCDN({
      modules: [
        {
          name: "vue",
          var: "Vue",
          path: "https://cdn.jsdelivr.net/npm/vue@3.2.47/dist/vue.global.prod.js"
        },
        {
          name: "vue-demi",
          var: "VueDemi",
          path: "https://cdn.bootcdn.net/ajax/libs/vue-demi/0.14.0/index.iife.js"
        },
        {
          name: "vue-router",
          var: "VueRouter",
          path: "https://unpkg.com/vue-router@4.2.1"
        },
        {
          name: "pinia",
          var: "Pinia",
          path: "https://cdn.bootcdn.net/ajax/libs/pinia/2.0.36/pinia.iife.prod.min.js"
        },
        {
          name: "axios",
          var: "axios",
          path: "https://cdn.bootcdn.net/ajax/libs/axios/1.4.0/axios.js"
        },
        {
          name: "element-plus",
          var: "ElementPlus",
          path: "//unpkg.com/element-plus@2.3.5",
          css: "//unpkg.com/element-plus/dist/index.css"
        },
        {
          name: "element-plus/icons-vue",
          var: "ElementPlusIconsVue",
          path: "https://cdn.bootcdn.net/ajax/libs/element-plus-icons-vue/2.1.0/global.iife.min.js"
        },
        {
          name: "echarts",
          var: "echarts",
          path: "https://cdn.bootcdn.net/ajax/libs/echarts/5.4.2/echarts.common.js"
        }
      ]
    })
  ]
})
```

② gzip压缩

进一步减小打包体积。

```
pnpm install -D vite-plugin-compression
```

```
// vite.config.ts
import viteCompression from "vite-plugin-compression";

export default defineConfig({
  plugins: [
    viteCompression({
      filter: /.(js|mjs|json|css|html|jpg|png)$/i, // 需要压缩什么文件，默认为 /.(js|mjs|json|css|html)$/i
      // deleteOriginFile: true, // 压缩完成后 dist 中是否删除原文件，默认为false
      verbose: true, // build 完成后是否显示压缩结果，默认为true
      disable: false, // 是否禁用压缩，默认值为false
      threshold: 10240, // 超过多少B才进行压缩，这里设置为10kB，默认值不知道是多少
      algorithm: "gzip", // 压缩算法，默认为 gzip
      ext: ".gz" // 压缩文件后缀
    })
  ]
})
```

```
# nginx.conf
user  root;
worker_processes  1;

events {
    worker_connections  1024;
}


http {
    include       mime.types;
    default_type  application/octet-stream;

    sendfile        on;

    keepalive_timeout  65;

    # 开启gzip功能
    gzip on;
    # 开启gzip静态压缩功能
    gzip_static on;
    # gzip缓存大小
    gzip_buffers 4 16k;
    # gzip http版本
    gzip_http_version 1.1;
    # gzip 压缩级别 1-10
    gzip_comp_level 5;
    # gzip 压缩类型
    gzip_types text/plain application/javascript text/css application/xml text/javascript application/x-httpd-php image/jpeg image/gif image/png;
    g zip_vary on;

    server {
        listen       80;
        server_name  localhost;

        location / {
            # 前端路径
            root   /root/gxbuy/gxbuy-client-manager-dist;
            # 入口       
            index  index.html;
        }

        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   html;
        }
    }
}
```

（2）测试生产环境

为了省事不多次部署，可以先将打包好的前段部署到服务器前，可以测试一下生产环境中有没有问题。

直接打开 dist 中的 index.html 会有一些问题，比如路径问题，跨域问题，这里只是测试生产环境，就不管它了，直接将 dist 的所有文件放到 express 项目的 public 文件夹中即可。

创建一个 express 项目：

```
pnpm init
pnpm install --save express nodemon compression
```

项目根目录创建 index.js 和 public 文件夹，将 dist 中的所有文件放到 public 中：

```
// index.js
const express = require("express");
const compression = require("compression");

const app = express();
app.use(compression());
app.use(express.static("./public"));

app.all("*", (req, res, next) => {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Methods", "*");
  res.setHeader("Access-Control-Allow-Headers", "content-type,Authorization");
  if (req.method == "OPTIONS") res.send(200);
  else next();
});

app.listen("8000", () => {
  console.log("服务器已启动");
});
```

启动 express：

```
npx nodemon index.js
```

浏览器访问 localhost:8000

## 3 部署

为了同时启动vue和node，且断开ssh连接不结束服务，需要将他们挂到后台中

```
yum -y install screen

screen -ls    #查看当前已创建的会话 数字.会话名 是-r 的xxx
screen -S xxx #创建xxx会话并进入，在里面 ctrl+a+d 离开当前会话并挂载后台， 输入exit则删除该会话并退出
screen -r xxx #进入xxx会话
```

开启端口：

```
# 开启端口，一 3001 为例
firewall-cmd --zone=public --add-port=3001/tcp --permanent

# 重启防火墙
firewall-cmd --reload

# 验证是否开启成功
firewall-cmd --zone=public --list-ports
```

然后还要去云服务器控制台开启对应的安全组。

（1）启动后端

```
screen -S xxx
cd 项目目录
node ./dist/main.js
# ctrl+a+d 离开回话
```

（2）部署前端

```
cd /usr/local/nginx/conf
vim nginx.conf

# 将 user 改为 root，
# http -> server -> location -> root 改为 前端项目路径
# http -< server -> location -> index 改为 入口html名
```

## 4 Linux可能遇到的问题

（1）如果是express部署而不是nginx，解决刷新后找不到网页的问题：

```
npm install --save connect-history-api-fallback
```

```
const history = require('connect-history-api-fallback')
...
app.use(history())
```

（2）windows和Linux回车符不同的问题

（3）若想用Linux命令行执行某个程序时传递参数

命令行的参数有个数和长度限制，所以参数多可以将参数保存到txt文件，读写这个文件获取参数

（4）编码问题
在上传/创建/读取/写入文件时，一定要首先考虑编码，否则遇到中文出现bug非常难发现

（5）linux中没有中文字体SimHei

所以 plt.rcParams['font.sans-serif'] = ['SimHei'] 无效，以下python代码查看现有字体

```
from matplotlib import font_manager
a = sorted([f.name for f in font_manager.fontManager.ttflist])
for i in a:
 print(i)
```

解决方法：

将win系统的 c:/windows/fonts 下的字体copy到linux，放到linux系统并情空系统字体缓存，放到matploylib文件中并修改配置文件，清空matplotlib字体缓存。

（6）python程序相关

node用exec调用python程序的问题：

exec的er回调中，服务器会停在这里，需要 return next(err)  或直接return  来继续运行服务器。

中文问题：

linux中py代码注释若有中文会报错（即使是注释也会），解决：最前面加上 #coding=utf-8
