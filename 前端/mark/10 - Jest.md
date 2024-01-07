# 一、开始

Jest是一个前端自动化测试框架，可以测试js和ts，node后端的代码也可以测试。

安装：

```
npm install --save-dev jest
npm install --save-dev jest-environment-jsdom
```

在package.json中配置，配置完后 npm run test 就能开始测试：

```
{
  "scripts": {
    //...
    "test": "jest"
    // "test": "jest --watchAll"  //每次保存会自动执行
  },
}
```

最基本的测试案例：

创建一个 aaa.js 和 aaa.test.js，npm run test测试的时候自动找到文件名有 .test.js 的文件进行测试，这两个文件要相同的文件名如aaa。

```
// aaa.js
function func1(money) {
  return money >= 100 ? "多" : "少";
}

module.exports = {
  func1,
};
```

```
// aaa.test.js
const { func1 } = require("./aaa.js");

test("测试func1", () => {
  // toBe() 是预期的结果
  expect(func1(300)).toBe("多");        //测试通过
  // expect(func1(300)).toBe("多1");    //测试不通过
});
```

# 二、配置和代码覆盖率

（1）配置

生成配置文件：

```
npx jest --init
```

分别会选择配置文件是否是ts，node还是浏览器，是否生成代码覆盖率文件(y)，用v8还是 babel来测量代码覆盖率，是否再测试结束后清除模拟调用(y)

在新版本的 Jest 中，默认创建一个名为 `jest.config.mjs` 的配置文件，mjs的配置文件使用的模块导入导出是es6的语法。

如果你想使用旧版本的 CommonJS 配置文件，你可以手动创建一个名为 `jest.config.js` 的文件。

（2）代码覆盖率

代码覆盖率指的是测试代码对功能性的代码和业务逻辑代码做了多少百分比的测试。

在配置文件中的选项 coverageDirectory: "coverage" 指定代码覆盖率报告文件夹的名称。

生成代码覆盖率报告：

```
npx jest --coverage
```

会生成代码覆盖率报告的文件夹，可以找到 index.html 展示报告。

# 三、匹配器

这里只是列举常用的匹配器，其他的详见文档。

## 1 相等

toBe汽配器，结对相等：

```
test("tobe测试效果", () => {
  const a = 5;
  const obj = { number: 123 };
  expect(a).toBe(5);                      //测试通过
  // expect(obj).toBe({ number: 123 });   //测试不通过，因为引用不同
});
```

toEqual匹配器，值相等：

```
test("toEqual测试效果", () => {
  const obj = { number: 123 };
  expect(obj).toEqual({ number: 123 });   //测试通过
  // expect(obj).toBe({ number: 123 });   //测试不通过，因为引用不同
});
```

toBeNull匹配器，toBeUndefined匹配器：

```
test("toBeNull,toBeUndefined测试效果", () => {
  const a = null;
  const b = undefined;
  expect(a).toBeNull();       //测试通过
  // expect(b).toBeNull();    //测试不通过
  expect(b).toBeUndefined();  //测试通过
});
```

toBeDefined匹配器，只要不是undefined都能通过：

```
test("toBeDefined测试效果", () => {
  const b = undefined;
  const c = 123;
  // expect(b).toBeDefined(); //测试不通过
  expect(c).toBeDefined();    //测试通过
});
```

toBeTruthy佩佩琦，toBeFalsy匹配器，判断真假：

```
test("toBeTruthy,toBeFalsy测试效果", () => {
  const a = 0;               //'',null等都是一样的
  const b = 123;
  // expect(a).toBeTruthy(); //测试不通过
  expect(a).toBeFalsy();     //测试通过
  expect(b).toBeTruthy();    //测试通过
  // expect(b).toBeFalsy(); //测试不通过
});
```

## 2 大小

大于，小于，大于等于，小于等于：

```
test("x大小测试效果", () => {
  const a = 10;
  expect(a).toBeGreaterThan(9);             // >
  expect(a).toBeLessThan(11);               // <
  expect(a).toBeGreaterThanOrEqual(10);     // >=
  expect(a).toBeLessThanOrEqual(10);        // <=
});
```

toBeCloseTo匹配器，解决js浮点数精度问题：

```
test("xtoBeCloseTo测试效果", () => {
  const a = 0.1;
  const b = 0.2;
  expect(a + b).toBeCloseTo(0.3);   //测试通过
  // expect(a + b).toBeEqual(0.3);  //测试不通过
});
```

## 3 存在

toMatch匹配器，匹配字符串：

```
test("toMatch测试效果", () => {
  const str = "红色绿色蓝色";
  expect(str).toMatch("红色");
  expect(str).toMatch(/红色/);
});
```

toContain匹配器，匹配数组/Set是否存在某个元素：

```
test("toContain测试效果", () => {
  const arr = [1, 7, 11];
  const set = new Set(arr);
  expect(arr).toContain(7);
  expect(set).toContain(7);
});
```

toThrow匹配器，测试是否存在异常：

```
test("toThrow测试效果", () => {
  function func() {
    throw "出错了";
  }
  expect(func).toThrow();           //测试通过
  // expect(func).toThrow("123");   //测试不通过，因为异常信息不是123

  //但是，有异常才测试通过不合常理，可以用.not匹配器
  // expect(func).not.toThrow();   //有异常，测试不通过
});
```

其中，not也是一种匹配器，也可以配合其他匹配器使用。

# 四、

单元测试：对软件中最小可测试单元进行检查和验证，通常是一个导出的模块。

集成测试：也叫组装测试或联合测试，在做完一些或所有单元测试后，将这些或所有模块按照设计要求组装成一个子系统或完整系统进行集成测试。

端到端测试：
