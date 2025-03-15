# 一、Python

## 1 基本语法

### 1.1 注释、变量/常量、数据类型、输入输出、标识符

（1）注释

```
# coding=utf-8
# 中文声明注释，表示该文件的编码格式，必须写在第一行，如果代码中有中文就要用

# 当行注释
''' 多行注释，3 个单引号
  语句结尾不加分号
'''

""" 3 个双引号也可以 """
```

（2）变量

必须初始化，不用声明数据类型，字符串可以用单引号或双引号。

```
# 变量
n = 123
str1 = "asdf"
str2 = 'qwer'

# 多个变量同时指向一个内催
n1 = n2 = 100

# 查看内存地址，True
print(id(n1) == id(n2))
```

Python 是动态语言，变量的类型碎石可以改变：

```
v = 10
v = "asdf"
v = 3.14
```

常量：

Python 中没有定义常量的保留字，所以一定要符合命名规范。

```
MAX_SIZE = 10
```

（3）数据类型

数值型：

```
# 数据类型# 数值型，包括整数、浮点数、复数
# 整数
d1 = 5  # 十进制
d1 = 0b101  # 二进制，也可以用 0B
d1 = 0o5    # 八进制，也可以用 0O
d1 = 0x5    # 十六进制，也可以用 

# 浮点数
d2 = 5.6    # 浮点数
d2 = 5.0    # 浮点数
d2 = 3e2    # 科学计数法，300.0

# 浮点数精度问题
# False
print(0.1 + 0.2 == 0.3)
# True ，保留 1 位小数
print(round(0.1 + 0.2, 1) == 0.3)

# 复数，j 表示虚数 i
d3 = 123 + 456j
```

布尔型：

True 是数值 1 ，Fale 是数值 0 。

```
# 布尔型
d4 = True
print(d4 + 10) # 11
d4 = False
print(d4 + 10) # 10

# 0 、0.0 、虚数 0 、空序列（字符串、元祖等等）、None , 自定义类实例化的对象 .bool() .len() 都是 False
# 其他情况均未 T
print(bool(False))
print(bool(0))
print(bool(0.0))
print(bool(0j))
print(bool(""))
print(bool([]))
print(bool(None))
```

字符串型：

```
# 字符串型
d5 = "asdf"
d5 = 'asdf'
d5 = "a"
d5 = 'a'
d5 = '''
  三个单引号，
  用于多行字符串，换行就包含换行符
'''
d5 = """
  也可以 3 个双引号
"""
d5 = "\n 转义字符"
d5 = r"\n 使转义字符失效"
d5 = R"\n 使转义字符失效"

# 索引
d5 = "asdf"
print(d5[0])

# 切片，左闭右开
print(d5[0:2])
print(d5[-2:-2])
print(d5[0:])
print(d5[:-1])
print(d5[:2])
print(d5[-2:])
print(d5[:])

# 连接
d5 = "asdf" + "qwer"
d5 = "asdf""qwer"
print(d5)

# 赋值多次
d5 = "asdf" * 3
print(d5)

# 判断是否为子串
print("as" in "asdf")
```

```
# 格式化字符串
age = 18
name = "asdf"
print("name is %s, age is %d" % (name, age))
print(f"name is {name}, age is {age}")

# 模式字符串
print("模式字符串, {0}，{1}".format(name, age))
print("宽度20左齐不足用*填充，{0:*<20}".format(age))
print("宽度20有对齐不足用+填充，{0:+>20}".format(age))
print("宽度20居中对齐不足用-填充，{0:-^20}".format(age))
print("千位分隔符，{0:3,}".format(1234156789))
print("浮点数，{0:.2}，{0:.2f}，{0:.2e}，{0:2%}".format(3.1415926))
print("二进制:{0:b}，八进制:{0:o}，十进制:{0:d}，十六进制:{0:x}".format(age))
```

```
# 编解码

# string 转 bytes
str = "字符串"
print(str.encode())
print(str.encode("gbk", errors = "replace"))
print(str.encode("gbk", errors = "ignore"))
print(str.encode("gbk", errors = "stric"))

# butes 转 string
s = "asdf"
s = s.encode()
s = s.decode("utf-8")
print(s)
```

```
# 字符串函数

print("ASDF".lower())
print("asdf".upper())

print("a,s,d,f".split(","))

print("aaddffff".count("aa"))
print("asdf".find("g"))
print("asdf 找不到会报错".index("a"))
print("asdf".startswith("as"))
print("asdf".endswith("df"))

print("asdf".replace("sdf", "aaa"))

s1 = "asdf".join("fg")
print(s1)

print("填充到指定长度".center(20))

print("  asdf  ".strip(" "))
print("  asdf".lstrip(" "))
print("asdf  ".rstrip(" "))
```

```
# 表单验证
print("是否全是数字，可以使任何十进制数字如罗马数字".isnumeric())
print("是否全是十进制的阿拉伯数字".isdigit())
print("是否全是字母，包括中文".isalpha())
print("是否全是数字和字母".isalnum())
print("是否全是小写，中文不区分大小写".islower())
print("是否全是大写，中文不区分大小写".isupper())
print("是否只有每个分隔符隔开的子串的首字母大写".istitle())
print("是否全是空格或转义字符".isspace())

# 正则表达式
import re
reg = "\d\.\d+"
str = "3.1415926lajhdfljkashj3.14"
# match，找第一个匹配的子串，注意隐藏的条件是必须是起始位置，找到返回 match 对象，找不到返回 None
res1 = re.match(reg, str)
res2 = res1 = re.match(reg, str, re.I)  # 忽略大小写
print(res1, res1.start(), res1.end(), res1.span(), res1.string)
print(res1.group())
# findall，找所有匹配的子串，返回一个列表
print(re.findall(reg, str))
# search，找第一个匹配的结果，不限制是起始位置，返回，找到返回 match 对象，找不到返回 None
print(re.search(reg, str))
# sub，替换
print(re.sub(reg, "*", str))
# split，分割
print(re.split(reg, str))
```

（4）类型转换

```
# 判断数据类型
a0 = 10
print(type(a0))

# 隐式类型转换
a1 = 10 + 10.2  # 20.2
a1 = 10 + True  # 11
a1 = 10 / 3     # 3.33333...


# 显示类型转换
# int() float() bool() str()
a2 = 123
a3 = "asd"
a4 = str(a2) + a3
a4 = int(3.6)  # 3 ，没有四舍五入
# chr() ord() ，unicode 转换
a5 = ord("a")
a5 = chr(97)
# hex() oct() din() ，进制转换
a6 = hex(15) # 16
a6 = oct(7)  # 8
a6 = bin(15) # 2

# eval() 去掉字符串最外层的引号
eval("print('eval 测试')")
str = "hello"
print(eval('str'))
```

（5）运算符

```
# 与 C 的不同

# 没有 ++ 和 --

# 算术运算符, / 变成可以隐式转换，多乐 // 整除、** 幂运算
print(10 / 3)   # 3.333... 
print(10 // 3)  # 3
print(2*2**3)   # 16 ，油叽叽比 * / 高

# 逻辑运算符变成 & | ，没有 ! 按位逻辑运算符，多了 and 、or 、not
print(True & False)
print(True and False)
print(not 0)
# True & print(123)  # 也无法用 & 表达式 来控制

# 复制运算符，多了系列解包复制
a = 5
b = 7
a, b = b, a
c, d = 5, 7

# 没有 ?: ，但是可以用下面的形式代替
print("真" if True else "假")
```

（6）输入输出

```
n = 10
str1 = "qwer"
str2 = "asdf"

# 输出，自带一个换行
print(n, str1 + str2)
print("asdf\n")
# 修改输出格式为以逗号分隔，结尾换成不换行而是空格
print(n, n, sep = ",", end = " ")
print(123)

# 编码和字符互相转换，包含 ASCI 和其他编码
print(ord("a"), ord("啊"))
print(chr(97), chr(21834))

# 输入
num = ""
input("请输入数字：" + num)
print(num)
```

（7）标识符和保留字

```
# 查看 python 的保留字，即关键字
import keyword
print(keyword.kwlist)
print("共：" + str(len(keyword.kwlist)))

# 标识符只能是数字/字母/夏华夏，不能数字开头，严格区分大小写，可以用中文但不推荐
变量 = 123
```

Python 标识符命名规范：

| 场景            | 规范             | 实例              |
| ------------- | -------------- | --------------- |
| 变量、函数、类的属性和方法 | 小写 + 下划线       | my\_name        |
| 常量            | 大写 + 下划线       | MAX\_SIZE       |
| 类名            | 大驼峰            | MyClass         |
| 类的内部类或模块中的类   | 大驼峰 + 下划线      | MyClass\_Person |
| 包名            | 纯小写            | numpy           |
| 单下划线开头        | 模块内不允许导出的资源    | \_func          |
| 双下划线开头        | 类的私有成员         | _\_\_name       |
| 双下划线开头和结尾     | Python 中专用的标识符 | \_\_main\_\_    |

### 1.2 流程控制

凡是需要用到作用域的地方，不用大口用，用冒号，以严格的缩进区分作用域。

（1）选择结构

没有 switch ，但是有模式匹配 match 可以代替，case 可以匹配任何数据类型包括列表、字典等。

```
n = 10

if n > 0:
  print("> 0")
elif a > 5:
  print("a > 5")
else:
  print("其他情况")

if n > 0:
  if n > 5:
    print("> 5")


c = 'a'
# 不用 break ，没有 default 用 case_ 代替
match c:
  case "a":
    print(c)
  case_ :
    print("default")
```

（2）循环结构

没有 do while，跳转语句没有 goto 。

```
for i in "asdf":
  print(i)

# range(a, b) a 到 b 的序列，左闭右开
for i in range(1, 10):
  for j in range(1, 5):
    print(i, j)

cnt = 0
while(cnt < 10):
  print(cnt)
  cnt += 1
```

配合 match 的同步迭代：

```

```

（3）pass 空语句

主要用于作用域中占位，保证代码执行，具体作用域的内容以后再实现。

```
a = 5
if a < 10:
  pass
```

### 1.3 组合数据类型

Python 中的序列是用于存储多个值的连续空间，有字符串、列表、元祖、集合和字典，除了字符串都是组合数据类型。

字符串、列表和元祖是有序序列，集合和字典是无需序列（底层用哈希实现）。

序列中的索引可以正向递增和反向递减、n 个元素的序列的正向递增从 0 到 n \- 1 ，反向递减从 \-n 到 \-1  。

列表、集合、字段是可变数据类型，指的是可以 CRUD ，CRUD 后内存地址不变，相对的数值型、布尔型、字符串型、元祖是不可变数据类型。

（1）序列都有的操作

长度：

```
str = "asdf"
print(len(str))
```

索引：

```
str = "asdf"
print(str[0])
print(str[-1])
```

切片：

访问一定范围的元素，左闭右开。

```
# 切片
str = "asdf"
print(str[0:1])
print(str[0:])
print(str[:1])
print(str[:-1])
print(str[-4:-1])
print(str[:])

# 设置步长，默认为 1
print(str[0:3:2])
print(str[::2])
print(str[::-1])
```

运算和常用函数：

```
# 系列解包赋值
a, b, c, d = "asdf"
print(a, b, c, d)

# 拼接
print("asdf" + "qwer")
print("asdf" * 3)

# 判断是否是子串
print("as" in "asdf")
print("qw" not in "asdf")

# 最值
print(max("asdf"))
print(min("asdf"))

# 查找元素第一次出现的索引
# Python 的数据类型都是一个对象，所以可以直接调用成员方法
print("asdf".index("a"))

# 统计某个元素出现的次数
print("aassddff".count("a"))
```

遍历：

```
# 直接遍历
str = "asdf"
for i in str:
  print(i)

# 使用索引，左比右开，如果是单个参数如 range(4) 就是 range(0, 4)
for i in range(0, len(str)):
  print(str[i])

# 使用枚举
for i in enumerate(str):
  print(i)

# 使用枚举 + 解包赋值，并修改枚举的起始序号
for index, item in enumerate(str, start = 10):
  print(index, item)
```

排序：

```
# 不改变原序列，返回一个新列表
s1 = "jkkh"
s2 = sorted(s1)  # 升序
s3 = sorted(s1, reverse = True)  # 降序
```

去重：

```
s = "aassddff"
res = ""
for i in s:
  if i not in res:
    res += i
print(res)

str = "aassddff"
r = list(set(str))
r.sort(key = str.index)
r = "".join(r)
print(r)
```

删除并释放内存：

```
# 删除并释放内存，使用后将会变成未定义
l1 = [1, 2]
del l1
# print(l1)
```

（2）列表、元祖、集合、字典

列表：

即数组。

```
# 字面量创建
l1 = [1, "asdf", 3.14]

# list() 创建，只能传一个序列，会根据序列的元素进行拆分
l2 = list("asdf")

# list() 配合 range ,左闭右开，如下面是创建 1 到 10 的数字，步长为 2
l3 = list(range(1, 10, 2))

# 列表生成式
l4 = [i for i in range(1, 10)]
l5 = [i * 10 for i in range(1, 10)]
l6 = [i for i in range(1, 10) if i % 2 == 0]

# 多维列表
l7 = [[1, 2], [3, 4]]
l8 = [[j for j in range(5)] for i in range(5)]  # i 行 j 列

print(l1)
print(l2)
print(l3)
print(l4)
print(l5)
print(l6)
print(l7)
print(l8)
```

```
l1 = [1, "asdf", 3.14]

# 修改，注意字符串是不支持这个的，下面的所有操作字符串也不支持
l1[0] = 456

# 尾部添加元素
l1.append(123)
# index 处的元素
l1.insert(0, 123)

# 删除 index 处的元素，并返回删除的元素
res = l1.pop(0)
# 删除指定值的元素 
l1.remove(3.14)

# 翻转
l1.reverse()

# 排序
[1, 5, 4].sort()  # 升序
[1, 5, 4].sort(reverse = True)  # 降序
["a", "A"].sort(key = str.lower, reverse = True)  # 忽略大小写并降序

# 深拷贝
newList = l1.copy()

# 清空
newList.clear()
```

元祖：

因为是不可变数据类型，所以性能比列表好。

```
t1 = (1, 2, 2)
t2 = tuple([1, 2, 2])

# 如果元祖只有一个元素，逗号不能省略，否则会换换成其他类型
t3 = (10,)
is_int = (10)

# 元祖生成式，返回一个生成器对象，需要转为元祖才能看到内容
t4 = tuple((i for i in range(10)))
# 生成器对象可以用 __next__() 访问，会自动 +1，但是访问一个就少一个元素
t5 = (i for i in range(10))
print(t5.__next__())
print(t5.__next__())

print(t1)
print(t2)
print(t3, is_int)
print(t4)
print(tuple(t5))
```

字典：

即 map 。键值必须是不可变数据类型。

```
# 若果有相同的 key， 后面会覆盖前面的
d1 = {"key1": 123, 2: 456, True: 789, (10,): 0}
print(d1)

# 使用映射创建
d2 = dict(zip(["key1", "key2"], [123, 456]))
print(d2)
# zip(0 返回一个映射对象，用完就没有元素了
z = zip(["key1", "key2"], [123, 456])
print(list(z))
print(dict(z))

# 使用参数创建
d3 = dict(my_key1 = 123, my_key2 = 456)
print(d3)

# 字典生成式
d4 = {k:v for k, v in zip(["key1"], [123])}
print(d4)\

# 访问、修改、插入
d1["key1"] = 111             # 若 key 不存在，就是新增一个键值对
print(d1["key1"])            # 若 key 不存在会报错
print(d1.get("key1"))        # 若 key 不存在会返回 None
print(d1.get("k", "不存在"))  # 设置不存在时返回的默认值
print(d1.keys())
print(d1.values())
print(d1.items())

# 删除 key 对应的键值对并返回 value，没有该 key 就返回默认值
pop_res = d1.pop(True, "默认值")
# 随机删除一个键值对并返回键和值的元祖
popitem_res = d1.popitem()
print(pop_res, popitem_res)
# 清空
d2.clear()

# 合并字典
print({"key1":123} | {"key2":456})

# 遍历
for i in d1.items():
  print(i)  # 由键和值组成的元祖
for k, v in d1.items():
  print(k, v)
```

集合：

无序不重复的序列，只能存储不可变数据类型。

```
# 创建，有重复的会去掉
s1 = {12, 12, True, "asd", (10,)}
s2 = set([1, 3.14, "asd"])

# 空集合
s3 = set()
d = {}      # 这种创建得到空字典

# 集合生成式
s4 = {i for i in range(4)}

# 交集
print({1, 2} & {2, 3})
# 并集
print({1, 2} | {2, 3})
# 差集
print({1, 2} - {2, 3})
# 补集
print({1, 2} ^ {2, 3})

# 插入
s1.add("a")
# 删除
s1.remove("a")
# 清空
s2.clear()
```

### 1.4 函数

（1）基本使用

```
def func1(a, b, c = 0):
  r1 = a + b
  r2 = b + c
  # 可以返回多个返回值，多个返回值会变成一个元祖
  return r1, r2

# 位置传参，位置必须相同
n1, n2 = func1(5, 7, 10)
# 关键字参数，参数顺序可以不同
n1, n2 = func1(c = 10, a = 5, b = 7)
# 位置传参和关键字传参时，位置参数必须在前面
n1, n2 = func1(5, 7, c = 10)

# 可变位置参数，得到一个元祖
def func2(*a): 
  print(type(a), a)
func2(1, 3, 2, 5)
func2(*[1, 3, 2, 5])

# 可变关键字参数，得到一个字典
def func3(**a):
  print(type(a), a)
func3(name = "asdf", age = 18)
func3(**{"name": "asdf", "age": 18})
```

（2）作用域

Python 中分支和循环内部不能定义局部变量。

函数中局部变量和全局变量同名时，可以使用 global 。

```
num1 = 10
num2 = 20

# 0
for i in range(10):
  num1 = 0
print(num1)

# 20
def func():
  num2 = 0
func()
print(num2)

# 0
def f():
  global num2
  num2 = 0
f()
print(num2)
```

（3）匿名函数 lambda 表达式

当函数的函数体只有一行 return 且只有一个返回值时，可以简化为 lambda 表达式。

```
res = lambda a, b: a + b
print(res(5, 7))
```

（4）常用内置函数

```
# 数学函数
print("相反数", abs(-5))
print("商和余数", divmod(10, 3))
print("保留 2 位小数并四舍五入", round(3.14159, 2))
print("求和", sum([1, 3, 5]))
print("幂运算", pow(2, 3))
print("最大值", max([1, 5]))
print("最小值", min([1, 5]))

# 迭代器操作函数
l = [1, 8, 5, 6 ,4 ,3 , 7]
print("排序", sorted(l))
print("反转", list(reversed(l)))
print("压缩成映射对象，一一对应", list(zip(l, l)))
print("枚举", list(enumerate(l)))
print("判断所有元素的布尔值是否都是 True", all(l))
print("判断所有元素的布尔值是否至少有一个 T", any(l))
print("下一个元素", next(zip(l, l)))
print("筛选", list(filter(lambda i: i > 5, l)))
print("生成新迭代器对象", list(map(lambda i: i * 10, l)))

# format ，除了模式字符串，还有下面的用法
print("数字默认右对齐", format(3.14, "20"))
print("字符串默认左对齐", format("hello", "20"))
print("用法和模式字符串差不多", format("hello", "*>20"))

# 其他函数
print("生成序列", list(range(1, 10)))
print("计算元素个数", len([1, 2, 3]))
print("查看数据类型", type("asdf"))
print("去掉最外层双引号", eval("1 + 1"))
num = 0
print("内存地址", id(num))
```

#### 1.5 面相对象

（1）基本使用

```
# () 可以省略
class LinkList():
  # 类属性，必须初始化
  data = 0
  
  # 初始化方法，即构造函数
  def __init__(self, data):
    self.data = data
    # 实例属性
    self.age = 18

  # 实例方法
  def get_data(self):
    return self.data
  def set_data(self, data):
    self.data = data

  # 静态方法
  @staticmethod
  def static_func1():
    print("静态方法没有 self")
  def static_func2():
    LinkList.static_func1()

  # 类方法，只能类自己调用
  @classmethod
  def class_func1(self):
    print("类方法有 self，但是访问的是类初始化的类属性和实例方法")
    print("只能在类外调用，所以类内的类方法无法调用另一个类方法")
    print(self.get_data(self))
    LinkList.static_func1()
    return self.data

  

# 实例化，调用类属性和实例属性
l = LinkList(123)
print(l.data, l.age)
l.data = 456
l.age = 28
print(l.data, l.age)

# 调用实例方法，实例化对象调用方法会自动传入 self 参数，类内调用就要自己传入
print()
print(l.get_data())
l.set_data(789)
print(l.get_data())

# 调用静态反复噶
print()
l.static_func1()
LinkList.static_func2()

# 类方法调用
print()
print(LinkList.class_func1())
```

Python 是动态语言，对类型没有很大的限制，所以实例化的对象可以动态绑定实例属性和实例方法，只不过调用动态绑定的实例方法时不再会自动传入 self ，需要手动传入：

```
# () 可以省略
class LinkList():
  pass

l = LinkList()
l.data = 123
l.get_data = lambda self: self.data

def set_data(self, data):
  self.data = data
l.set_data = set_data

print(l.data)
l.set_data(l, 456)
print(l.data, l.get_data(l))
```



（2）三大特性

封装：

用下划线命名变量来设置访问权限。

```
class A:
  # public
  a = 0
  # protected
  _b = 0
  # private
  __c = 0

  def get_c(self):
    return self.__c
  
  def set_c(self, value):
    self.__c = value

  # 也可以用装饰器把 set get 转化成属性一样使用
  @property
  def c(self):
    return self.__c
  @c.setter
  def c(self, value):
    self.__c = value

obj = A()

# 虽然是 protect ，但是还是可以强行访问
print(obj.a, obj._b)

# 也能强行访问 private
print(obj._A__c)

# get set
obj.set_c(123)
print(obj.get_c())\

# 转化成属性的 set get
obj.c = 456
print(obj.c)
```



继承：

```
class A:
  data1 = 1
  data2 = 1

  def __init__(self):
    print("A init")

  def func1(self):
    print("A func1")

  def func2(self):
    print("A func2")

class B:
  data1 = 2
  data2 = 2

  def __init__(self):
    print("B init")

  def func1(self):
    print("B func1")

  def func2(self):
    print("B func2")

class C(A, B):
  data2 = 3

  def __init__(self):
    print("C init")
    # 需要手动调用父类 init ，单继承直接用 super().__init__() 就可以了
    # 多继承就不能用 super() 了，因为 super() 优先指向先继承的 A 类
    # 其他方法内也可以用 super() 
    # super().__init__()
    A.__init__(self)
    B.__init__(self)

  def func2(self):
    # B.func2(self)
    print("C func2")

  

c = C()

# 如果多继承有重复的属性和方法，优先调用先继承的，这里先继承 A 类
print()
c.func1()
print(c.data1)

# 如果子类有重复的属性和重写的方法，就调用子类的
print()
print(c.data2)
c.func2()
```



多态：

不需要继承。

```
class A:
  data = 1

class B:
  data = 2

def get_data(obj):
  print(obj.data)

a = A()
b = B()

get_data(a)
get_data(b)
```

（3）Object

所有类的直接或间接父类。

```
class A:
  data = 0

  # 重写 Object 的 __init__
  def __init__(self, data):
    self.data = data

  # 重写 Object 的 __str__
  def __str__(self):
    # 未重写前返回内存地址
    return "A 类"
  
  # 重写 Object 的计算方法，实现运算符重载
  def __add__(self, obj):
    return self.data + obj.data

# 查看类中的信息
print(dir(A))

a = A(1)
print(a)

b = A(2)
print(a + b)
```

（4）深拷贝

```
class A:
  data = 0

# 自动调用 Object 的 __new__() 将对象创建在堆区
a = A()

# 浅拷贝
b = A

# 深拷贝
import copy
c = copy.copy(a)
```



### 1.6 其他

（1）异常处理

捕获异常：

常见错误类型有：ZeroDivisionError 、indexError 、KeyError‘ 、NameError 、SynctaxError 、ValueError 、AttributeError 、TypeEoor 、IndentationError 、BaseException 。其他的用到再查阅。

```
# 基本用法
try:
  a = " " + 123
except:
  print("出错了")

# 根据异常类型进行捕获，注意只能捕获已写出的类型的错误，且只能补货一个最大的异常
# 铺货能力越强的写在越后面
try:
  a = "" + 123
  b = 5 / 0
except ZeroDivisionError:
  print("除数不能为 0")
except ValueError:
  print("值错误")
except BaseException:  # 不写错误类型默认就是 BaseException
  print("出错了")

# try...except...else，没有异常就执行 else
try:
  a = 1 + 1
except:
  print("出错了")
else:
  print("没问题")

# try...except...else...finally，无论是否异常都会执行 finally
try:
  a = 5 / 0
except:
  print("出错了")
else:
  print("没问题")
finally:
  print(123)
```

抛出异常：

```
a = 0

try:
  if a == 0:
    raise Exception("除数不能为 0")
except Exception as my_err:
  print(my_err)
```

（2）文件操作

```

```



（3）模块化

（1）模块和包

一个 \.py 文件就是一个模块：

```
# ./mymod.py
my_name = "mymod"
def func():
  print("mymod func")
```

```
# ./1.py
# as 起别名，可以不用，逗号用来导入多个和模块
import mymod as mm, time as tm
mm.func()

# 导入模块中的某个变量、函数、类等，容易冲突
from mymod import func as f, my_name as mn
f()
print(mn)

# 导入全部，更容易冲突，冲突了后面就覆盖前面的
from mymod import *
func()
```

一个文件夹就是一个包，里面有一个 \_\_init\_\_.py 文件和若干 .py 模块文件：

```
# ./mymod/__init__.py
print("只执行一次")
```

```
# ./mymod/mod1.py
my_name = "mod1"
def func():
  print("mod1 func")
```

```
# ./1.py
import mymod.mod1 as m1
m1.func()

from mymod import mod1 as m
m.func()

from mymod.mod1 import func
func()
```

主程序运行：

限制代码只能在本模块内执行，其他地方导入就不会执行。

```
# ./mymod.py
if __name__ == "__main__":
  print(123)
```

```
# ./1.py
import mymod
```

（2）常用内置模块

random、time、datetime、re、json

（3）第三方包

# 二、自动化工具
