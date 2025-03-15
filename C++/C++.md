# 一、C

文件：

C 和 C++ 的源文件后缀分别是 ,c 和 .cpp，用于编辑源代码。

头文件后缀是 .h 。 

VS 运行和调试：

F5 编译并运行，F10 断电调试。

gcc：

```
# 编译，生成 .out 文件
gcc 1.c

# 运行
./1.out
```

## 1、输入输出、数据类型、变量、运算符

### 1.1 第一个程序

main 函数是程序的入口，有且只有一个，每一条语句结尾都要有分号：

```
#include<stdio.h>

int main() {
    printf("Hello World");
    return 0;
}
```

还有一种很老实的写法，已经不推荐使用了：

```
#include<stdio.h>

void main() {
    printf("Hello World");
}
```

### 1.2 注释

用于说明代码的用意。

```
#include<stdio.h>

// 单行注释

/*
多行注释
*/

int main() {
    printf("Hello World");
    return 0;
}
```

### 1.3 变量

（1）声明一个变量

变量名只能由字符、数字和下划线组成，且数字不能出现在开头。

变量名在同一作用域中不能重复，也不能是关键字（关键字是 C 语言语法中已定义的标识符，如 int ，main 等）。

变量名也叫标识符，变量在声明的时候就赋值也叫初始化。

```
#include<stdio.h>

int main() {
    // 从内存中申请一块空间，用于存放数据类型为整型 int 的数据
    int a = 5;

    // 可以不赋予初始值,，但是无法输出，会报错
    int b;

    // 同一数据类型的数据可以同时声明
    int c = 1, d = 2;

    int e = 100;
    // 修改变量
    e = 200;

    // 在输入输出函数中使用变量需要借助描述符，按顺序一个描述符对应一个变量，整型的描述符是 %d
    printf("a = %d, c = %d, d = %d, e = %d", a, c, d, e);;

    return 0;
}
```

（2）变量命名规范

为了代码有更好的可读性，变量的名字，约定俗成了一些变量命名规范，这不是强制的，但合理运用规范会大大提高代码质量。

最常见的命名规范是驼峰命名法和下划线 + 字符的形式：

```
#include<stdio.h>

int main() {
    // 小驼峰
    int studentAge;

    // 大驼峰
    int StudentAge;

    // 下划线分隔
    int student_age;
    int STUDENT_AGE;

    return 0;
}
```

常见的命名规范应用场景：

| 命名规范       | 应用场景     |
| ---------- | -------- |
| 小驼峰        | 变量、函数    |
| 大驼峰        | 枚举、结构体、类 |
| 下划线 + 大写字母 | 常量       |
| 下划线 + 小写字母 |          |

（3）变量作用域

分为局部变量和全局变量。一切在代码块（大括号的内部区域）内的变量都是局部变量，不被任何代码块包裹的变量就是全局变量，

```
#include<stdio.h>

// 全局变量
int q = 10;

int main() {
    // 局部变量
    int a = 5;

    {
        int b = 1;
    }

    printf("%d", a);

    return 0; // 5
}
```

变量查找的方式：

* 往前找，所以变量的声明一定要在调用之前

* 有内到外，先在自己的局部作用域中找，再到外层的局部作用域，直到全局作用域，由于这个特性，不同作用域的变量就可以有重复的标识符，外部作用域也无法调用内部作用域的变量

在同一个工程项目下的源文件中，一个有.c 文件可以调用另一个 .c 文件的全局变量：

```
// 2.c
int a = 10;
```

```
// 1.c
#include<stdio.h>

int main() {
    extern int a;
    printf("%d", a);
    return 0; // 5
}
```

extern 也可以声明同一工程下其他 .c 文件的全局函数：

```
// 2.c
int add(int a, int b){
    return a + b;
}
```

```
// 1.c
#include<stdio.h>

int main() {
    extern int add(int, int);
    printf("%d", add(5, 7));
    return 0;
}
```

（4）变量的生命周期

* 全局变量在整个程序开始时开始，整个程序结束时结束

* 局部变量在所属的代码块开始时开始，所示的代码块结束时结束时结束

（5）相关的关键字

auto 和 static ：

可以修饰变量、函数等。

```
#include<stdio.h>

// static 修饰的全局变量，无法再在同一工程中的其他 .c 文件用 extern 声明，相当于限制了作用域，只能在此 .c 文件中使用
static int c = 20;

int main() {
    // auto 表示这个局部变量会自动在离开作用域后销毁，可以省略，默认会带上
    auto int a = 10;

    // static 修饰的局部变量在离开作用域后不会被销毁，相当于延长了生命周期，直到整个程序结束才会销毁
    for (int i = 0; i < 5; i++) {
        static int b = 1;
        // 23456
        printf("%d", ++b);
    }

    return 0;
}
```

signed 和 unsigned：

```
#include<stdio.h>

int main() {
    // 有符号数，可以省略，默认会带上
    signed int a = 10;

    // 无符号数。即只能表示正数，优点事正数范围比有符号数多了一倍
    unsigned int b = 10;

    // 由于是无符号数，赋值负数的话符号位会作为数值位表示正数
    unsigned int c = -1;
    printf("%ud", c);

    return 0;
}
```

char 也是分有符号和无符号的，不过 ASCI 就 127 个，有符号也够用，不过 signed char 的负数是一些乱码：

```
#include<stdio.h>

int main() {
    printf("%c", -48);
    return 0;
}
```

register：

将变量放在比内存速度更快的寄存器中，但是由于寄存器数量有限，编译器会自动分配，所以用 register 修饰的变量不一定在寄存器中。也可能还在内存中：

```
#include<stdio.h>

int main() {
    register int a = 10;
    return 0;
}
```

volatile：

主要用于硬件和操作系统编程，防止编译器优化造成的变量意外变化，始终从内存中读取变量。

### 1.4 常量

声明后就无法再修改，所以都会赋予书是指，否则就没有意义了。当一个值确定不用修改时就可以使用常量，优化代码效率。

（1）字面常量

```
#include<stdio.h>

int main() {
    100;
    printf("200");
    return 0; // 5
}
```

（2）标识符常量

也叫宏常量。

define 不是关键字，但是也不推荐作为变量名。

```
#include<stdio.h>

#define N 3.1415926

int main() {
    printf("%lf", N);
    return 0;
}
```

（3）常变量

注意，常变量本质是一个变量，只是具有了不可修改的性质。

```
#include<stdio.h>

int main() {
    const int a = 10;
    printf("%d", a);
    return 0; // 5
}
```

（4）枚举常量

如果没有枚举设置值，则默认按 0,1,2... 给默认值；如果中间某个枚举设置了值 n ，则下一个枚举的值从 n + 1 开始。

枚举占 4 个字节。

```
#include<stdio.h>

enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW = 10,
    ORANGE
};

int main() {
    enum Color r = RED;
    enum Color g = GREEN;
    enum Color b = BLUE;
    enum Color y = YELLOW;
    enum Color o = ORANGE;

    // 0 1 2 10 11
    printf("%d %d %d %d %d", r, g, b, y, o);

    return 0;
}
```

枚举常量是整个枚举无法修改，但是用枚举声明出的变量是可以修改的：

```
#include<stdio.h>

enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW = 10,
    ORANGE
};

int main() {
    enum Color r = RED;
    r = BLUE;
    printf("%d", r);
    return 0; // 5
}
```

枚举优于标识符常量的点：

* 枚举更有可读性，可维护性，比如枚举的场景如果用标识符常量实现，会多起几个名字，容易冲突

* 枚举是一种类型，有类型检查，更好调试，而标识符常量不是类型，只是一种替换的符号

### 1.5 数据类型

（1）基本概念

每个变量都应该根据应用场景使用合适的数据类型，这样可以提高代码执行效率，每种数据类型都会申请不同大小的内存空间，通常以字节为单位。

计算机中最小单位为一个比特（bit），存放 0 和 1 。

同一个字节（1 Bute） = 8 bit ，即 8 个二进制位。

注意比特和字节的单位，比如 1 kb 是 1000 bit，而 1 kB 是 1024 个字节 = 8192 bit 。

数据类型如下：

| 数据类型      | 说明                                                               | 字节数   |
| --------- | ---------------------------------------------------------------- | ----- |
| char      | 字符型，存放一个字符，一个字节刚好存放所有 ASCI 码。也可以作为 1 个字节的整型                      | 1     |
| short     | 短整形                                                              | 2     |
| int       | 整型                                                               | 4     |
| long      | 长整型，不同编译器字节数不同，这是因为 C 标准只规定了 long 的字节数大于等于 int 就可以了，所以不同编译器的实现不同 | 4 或 8 |
| long long | 更长的整型（C99 标准新增）                                                  | 8     |
| float     | 单精度浮点型                                                           | 4     |
| double    | 双精度浮点型，精度更高，小数位更精确                                               | 8     |

```
#include<stdio.h>

int main() {
    int a;

    // 可以输出数据类型的字节数
    printf("%d", sizeof(a));
    return 0;
}
```

关于布尔值（boolean）：

值只有真和假。C 语言中没有专门为布尔值设计一个数据类型，只规定了二进制全 0 表示假，其余都是真，比如数字 0 、'\0'、NULL 都是假，注意 '0' 的 ASCI 是 48 ，所以表示真。

如果是假取反为真，值为 1 。

关于整型：

字面的整数都是 int 。

可以声明 2 进制、 8 进制 和 16 进制：

```
#include<stdio.h>

int main() {
    // 255 173 255，分别是二进制、八进制、十六进制
    short a = 0b0000000011111111,b = 0255, c = 0x00ff;
    printf("%d %d %d\n", a, b, c);

    // 注意，二进制和十六进制如果赋值不全，则会在在左边自动补 0
    // 255 255
    short d = 0b11111111, e = 0xff;
    printf("%d %d", d, e);

    return 0;
}
```

关于浮点数：

float 和 double 也叫实型。

float 和 double 小数位都是 6 位：

```
#include<stdio.h>

int main() {
    // 1.200000 2.400000
    float a = 1.2;
    double b = 2.4;
    printf("%f %lf", a, b);
    return 0;
}
```

```
#include<stdio.h>

int main() {
    // 小数默认是 double 类型，加一个 f 可以减少一次转换过程，提高一点性能
    float f1 = 3.14f;

    // 科学计数法
    float f2 = 3e2, f3 = 3e-2;
    // 300.000000 0.030000
    printf("%f %f \n", f2, f3);

    return 0;
}
```

（2）数据类型转换

分为隐式类型转换（也叫自动类型转换）和显示类型转换（也叫强制类型转换）。

隐式类型转换：

* 赋值时转换：大转小会丢失精度，小转大会自动根据符号位补 0 或 1 提高精度：
  
  ```
  #include<stdio.h>
  
  int main() {
      // 3 3.000000
      int a = 3.14;
      double b = 3;  
      printf("%d %lf", a, b);
      return 0;
  }
  ```

* 整型提升：字节数小于 int 的数据类型在算术运算时会转换为 int 或者 unsigned int ，这是因为 CPU 的 ALU 和通用寄存器都是 32 位：
  
  根据符号位，在左边补0补1
  
  ```
  #include<stdio.h>
  
  int main() {
      // 案例 1
      // 00000000000000000000000000000011 + 00000000000000000000000001111111 = 00000000000000000000000010000010
      // -126，先将 a、b 提升到 32 为，计算得到 c 再截断为 8 位
      char a = 3, b = 127;
      char c = a + b;
      printf("%d\n", c);
      // 4，因为没有截断为 8 位的过程
      printf("%d\n", sizeof(a + b));
  
      // 案例 2
      // 注意整型提升是根据符号位在左边补0补1，而进制转换都是左边补0
      char d = 0xff;
      short e = 0xffff;
      int f = 0xffffffff;
      if (d == 0xff)  printf("d");         // ffffffff 不等于 000000ff
      if (e == 0xffff)  printf("e");       // ffffffff 不等于 0000ffff
      if (e == 0xffffffff)  printf("f\n");   // ffffffff 
  
      // 案例 3
      // 1 4 4 1
      char g = 12;
      printf("%d ", sizeof(c));     // 1 ，没有算术运算
      printf("%d ", sizeof(+c));    // 4 ，转为正数是算术运算
      printf("%d ", sizeof(-c));    // 4 ，转为负数是算术运算
      printf("%d ", sizeof(!c));    // 1 ，逻辑非不是算术运算
  
      return 0;
  }
  ```

* 表达式转换：小的转成大的，如果大小相同就 signed 转 unsigned，整数转小数：
  
  ```
  #include<stdio.h>
  
  int main() {
      int i = -1;
      // f，因为 sizeof 得到无符号数，-1 也就转为无符号数
      printf("%c", i < sizeof(i) ? 't' : 'f');
      return 0;
  }
  ```

```
#include<stdio.h>

int main() {
    // 2 2.500000
    printf("%d ", 5 / 2);
    printf("%f ", 5 / 2.0);
    return 0;
}
```

强制类型转换：

```
#include<stdio.h>

int main() {
    // 3
    double a = 3.14;
    int b = (int)a;
    printf("%d", 3);
    return 0;
}
```

（3）在输入输出函数中对应的描述符

| 描述符 | 数据类型                     | 备注                         |
| --- | ------------------------ | -------------------------- |
| %d  | short、int、long、long long | 还可以用其他进制，如 %x 是 16 进制      |
| #c  | char                     | 无                          |
| #f  | float（double 也可以但不推荐）    | 可以四舍五入保留 n 位小数，如 %f.2 保留两位 |
| #lf | doub                     | 同 %f 可四舍五入保留 n 位小数         |
| %s  | 字符串                      | 无                          |
| %p  | 指针                       | 如果打印的值不是指针，则需要用取地址符 & 获取指针 |

（3）ASCI 码

将数字、字母、符号等等单个字符编码，共编码 128 个，刚好 7 个比特的表示范围，但是为了未来增加其他字符考虑，就用了 8 个比特编码，这也是 1 Byte = 8 bit 的原因。

```
#include<stdio.h>

int main() {
    // 0 10 48 57 65 90 97 122
    printf("%d %d %d %d %d %d %d %d", '\0', '\n', '0', '9', 'A', 'Z', 'a', 'z');
    return 0;
}
```

而中文等其他文字，用 2 个字节编码，也有不同的编码方式，比如 UTF-8 。

（4）输入函数

scanf ：

```
#include<stdio.h>

int main() {
    int a, b;

    // & 是取地址符，通过 & 取得变量的内存地址，然后按照输入的内容给它赋值
    // vs 中 scanf 编译会报错，表示不安全，可以去设置一下，具体百度
    scanf("%d", &a);
    scanf("%d", &b);

    printf("#d", a + b);
    return 0;
}
```

getchar、putchar ：

专门用于输入输出单个 char 字符的函数。

```
#include<stdio.h>

int main() {
    char ch;

    // 程序停下来，等待输入，按回车输入完成
    ch = getchar();

    // 输出
    putchar(ch);

    return 0;
}
```

输入缓冲区：

输入的内容会进入输入缓冲区，scanf 、getchar 按回车后会输入完成，但是 scanf 遇到空格就只会把空格前的内容作为输入内容，空格和空格后面就会留在输入缓冲区，包括回车。

因此当 scanf 后使用 getchar 的时候，如果输入缓冲区还有内容，getchar 就会直接取出输入缓冲区的第一个字符作为输入内容，就接收不到用户的输入内容了，解决方法如下：

```
#include<stdio.h>

int main() {
    char str[] = "";
    scanf("%s", &str);

    // 消耗掉输入缓冲区的全部字符
    while(getchar() != '\n') {}

    int ch;
    ch = getchar();
    putchar(ch);

    return 0;
}
```

当使用多个 getchar 时且输入的时候输入多个字符再回车结束，也会出现这种情况，解决方法同理。

（5）typedef

为数据类型重命名。

```
#include<stdio.h>

int main() {
    typedef int zhengxing;
    zhengxing a = 10;
    return 0;
}
```

不过上面用法比较少见，多用于结构体的重命名，简化代码。

### 1.6 指针

（1）基础

指针是存储内存地址的变量。

内存由一个个 8 比特大小的内存单元组成，32 位系统由 32 根地址线来给每一个内存单元编址（64 位系统就 64 根），可以提供 2 ^ 32 个内存地址。

32 位系统之所以最大只支持 4 GB 的内催，正是因为 4 GB = 2 ^ 32 \* 8 bit 。

```
#include<stdio.h>

int main() {
    int a = 10;

    // 声明一个存储整形变量内存地址的指针，只推荐 p1 和 p3 的方式，p2、p3的声明方式可读性差
    // 用取地址操作符 & 获取变量 a 的内存地址
    int* p1 = &a;
    int * p2 = &a;
    int *p3 = &a;

    // 输出结果是一样的
    printf("%p %p", p1, &a);

    // 通过解引用操作符 * 来根据内存地址读取对应存储的值
    printf("\n%d", *p1);

    return 0;
}
```

声明指针的数据类型只是说明这个内存地址的变量是什么数据类型，如果用 sizeof 判断指针的字节数，食欲数据类型无关的，21 位系统是 4 字节，64 位系统是 8 字节。

注意，当同一个语句声明多个指针的时候：

```
#include<stdio.h>

int main() {
    char a = 'a', b = 'b';

    // 这样是声明了 char* 和一个 char
    char* pa = &a, pb = b;

    // 这样才是声明两个 char*
    char* paa = &a, *pbb = &b;

    // 所以指针声明最常见的是这种
    char *paaa = &a;

    printf("%c", *pbb);

    return 0;
}
```

（2）指针类型

各种指针类型的字节数都是一样的，也可以存放其他类型的指针：

```
#include<stdio.h>

int main() {
    int a = 10;
    char* c = &a;
    return 0;
}
```

但是指针类型还是有自己的意义的，上面的代码是有问题的：

* 指针类型决定了解引用时操作字节数的权限，int\* 是 4 个，char\* 是 1 个，所以上面代码解引用只能修改 1 个字节

* 指针类型决定了指针加减整数的步长，int\* 加 1 是 4 个字节，char\* 加 1 是 1 个字节

因此，每个指针都应该选择正确的指针类型。

如果两个指针类型的字节数相同，也不能乱用，比如 int 指针和 float 指针，flot 有整数部分和小数部分，int 变成 float 的时候低位数值会变成 float 的小数部分，float 变成 int 的时候会把 float 整数部分变成 int 的数值高位：

```
#include<stdio.h>

int main() {
    int n = 7;
    float* p = (float*)&n;

    // 7 很小的小数
    printf("%d %f\n", n, *p);

    // 很大的整数 7.000000
    *p = 7.0;
    printf("%d %f", n, *p);

    return 0;
}
```

指针类型 void\* ：

无类型指针，也叫万能指针，可以存放任何类型的指针。主要是下面你的用途：

* 函数形参需要适配多种数据类型时，可以用 void\*

void\* 无法解引用，也无法加减整数，无法相减，但可以比较大小，但比较没什么意义。

（3）指针运算

指针只有三种运算：

* 指针加减整数：+1 的步长等于该数据类型的字节数
  
  ```
  #include<stdio.h>
  
  int main() {
      int a = 10;
      int* p = &a;
      printf("%p %p", p, p + 1);  // 两者相差 4
      return 0;
  }
  ```
  
  配合 ++ 和 -- ：
  
  ```
  #include<stdio.h>
  
  int main() {
      int arr[3] = {1,2,3};
      int* p = arr;
  
      // 1 3
      printf("%d", *p++);
      printf("%d", *++p);
  
      return 0;
  }
  ```

* 两个指针比较大小：
  
  ```
  #include<stdio.h>
  
  int main() {
      int a = 10, b = 20;
      int* p = &a, q = &b;
  
      // 这样比较没什么意义
      if (p < q) printf("123\n");
      else printf("456\n");
  
      // 通常比较大小会用在数组这种连续空间的地址
      /*/ 注意，C 标准只规定了数组中指针比较的限制
       * 可以对比数组最后一个元素的下一个地址，因此才可以 i < &arr[3]
       * 不可以对比数组第一个元素之前的地址
       */
      int arr[3] = { 1,2,3 };
      for (int* i = &arr[0]; i < &arr[3]; i++) {
          printf("%d", *i);
      }
  
      return 0;
  }
  ```

* 两个指针相减：
  
  ```
  #include<stdio.h>
  
  int main() {
      int arr[3] = {1,2,3};
      int* p = arr, * q = &arr[3];
  
      // 3 -3，这也是常见用法
      printf("%d %d", q - p, p - q);
  
      // 这样相减就没什么意义了
      int a = 10;
      int* pa = &a;
      printf("\n%d", pa - p);
  
      return 0;
  }
  ```

（4）指针和 const 结合

```
#include<stdio.h>

int main() {
    int a = 10;

    // 常量指针，指针自身的值可以修改，但是指向指向的那个变量无法修改
    const int *p1 = &a, *p2 = &a;

    // 指针常量，，指针自身的值无法修改，但是指针指向的那个变量可以修改
    // 由于指针在连续声明时每个变量都需要假 * ，而这里 * 又在 const 前面，所以只能同时声明一个变量
    int* const q = &a;

    // 同时修饰，指针自身的值和指向的那个变量的值都无法修改
    // 同上，只能同时声明一个变量
    const int* const r = &a;

    return 0;
}
```

（5）野指针、空指针

当一个指针指向的内存地址是不可知的，就是一个野指针。

变成中应当避免出现野指针，否则会出现不可预知的后果，可以用空指针来规避野指针，空指针指向的内存空间是全 0 的。

野指针和空指针都不能解引用。

产生野指针的场景：

* 指针未赋值：
  
  ```
  #include<stdio.h>
  
  int main() {
      int* p;
  
      // 空指针
      int* q = NULL;
      int* r = (void*)0;
      int* s = 0;
      printf("%p %p %p", q, r, s);
  
      return 0;
  }
  ```

* 指针越界：
  
  ```
  #include<stdio.h>
  
  int main() {
      // arr[3] 及以上就是野指针
      int arr[3] = { 1,2,3 };
      return 0;
  }
  ```
  
  代码中应当具有判断是否越界的逻辑，或者有设置空指针的话就判断到空指针就结束。

* 指针指向的空间已经释放：
  
  ```
  #include<stdio.h>
  
  int* func() {
      int a = 5;
      return &a;
  }
  
  int main() {
      // 这样是不合适的，因为函数调用完，函数内的临时变量就释放了，因此 p 就是一个空指针
      int* p = func();
      // 指向的地址释放了，就应该设置为空指针
      p = NULL;
      return 0;
  }
  ```

（6）多级指针

指针存储的内存地址指向的是也是指针，就是多级指针，以二级指针为例：

```
#include<stdio.h>

int main() {
    int a = 10;
    int* p = &a;

    // 可以 int** p  int **p  int* * p
    int** pp = &p;

    // 解引用
    printf("%p %d", *pp, **pp);

    return 0;
}
```

### 1.7 运算符

语句、表达式的概念：

```
#include<stdio.h>

int main() {
    // 分号结尾的就是一条语句。其中 1 + 2 是一个表达式
    int a = 1 + 2;

    // 空语句
    ;

    return 0;
}
```

根据运算符操作的数量，分为：

* 单目运算符，如 !

* 双目运算符，如 + - \* /

* 三目运算符，如 ?:

* 其他，如 sizeof 、(数据类型)

运算符优先级：

越上面的优先级越高，同一优先级按左右顺序执行。

| 类别         | 优先级        | 运算符                                 | 介绍              | 用法                           | 备注                                              |
| ---------- | ---------- | ----------------------------------- | --------------- | ---------------------------- | ----------------------------------------------- |
| 小括号、用于访问   | 1 左-右      | ()                                  | 小括号、            | (表达式)                        | 可用于优先执行某一段表达式                                   |
|            |            | []                                  | 数组下表            | arr[i]                       | 下表从 0 开始                                        |
|            |            | .  ->                               | 成员选择（对象/指针）     | T.a  T->a                    | 真真也可以先解引用再 . 但 -> 方便点                           |
| 无法分类       | 2 右-左      | -  !  \~                            | 取负、取反、按位置取反     | -a  !a  \~a                  | 无                                               |
|            |            | \*  &                               | 解引用、取地址         | \*a  &a                      | \* 也可以用来声明指针变量                                  |
|            |            | ++  --                              | 递增、递减           | a++  ++a  a--  --a           | 前置的是先递增再赋值、后置反过来                                |
|            |            | (type)  sizeof                      | 类型转换、类型字节数      | (int)  sizeof(a)    sizeof a | sizeof 得到的是无符号数                                 |
| 算术运算符      | 3 左-右      | \*  /  %                            | 乘、除、取模          | a \* b*                      | / 如果两边都是整型就会将结果乡下取整；取模正负被取模数一样，除数不能为0；% 两边只能是整数 |
|            | 4 左-右      | +  -                                | 加、减             | a + b                        | 无                                               |
|            | 5 左-右      | >>  <<                              | 左移、右移           | a << 2                       | 位运算符，算术移位，二进制移位，左一位惩2，右一位除2                     |
| 比较运算符      | 6 左-右      | >  <  >=  <=                        | 大于、小于、大于等于、小于等于 | a < b                        | 无                                               |
|            | 7 左-右      | ==  !=                              | 等于、不等于          | a == b                       | 无                                               |
| 按位逻辑运算符    | 8\~10 左-右  | &  ^  \|                            | 按位与、异或、或        | a & b                        | 二进制计算                                           |
| 逻辑运算符      | 11\~12 左-右 | &&  \|                              |                 | 与、或                          | a && b                                          |
| 条件运算符      | 13 右-左     | ?:                                  | 条件 ? 真执行 : 假执行  | a > b ? a : b                | 唯一的三目运算符，相当于简化的 if...else...                    |
| 赋值/符合赋值运算符 | 14 有-左     | = \*= /= %= += -= >>= <<= &= ^= \|= | 无               | a += 3                       | 无                                               |
| 逗号运算符      | 15 左-右     | ,                                   | 表达式,表达式         | int a, b;                    | 将多个表达式连接成一个新的表达式，这个新表达式的结果就是最后一个逼到试试的结果         |

关于赋值运算符：

带有赋值运算符的表达式的结果就是被赋值的那个变量的结果。

```
#include<stdio.h>

int main() {
    // 12 13 14
    int a, b = 5, c = 7;
    printf("%d ", a = b + c);
    printf("%d ", ++a);
    printf("%d\n", a += 1);

    // 13，因为是先赋值再递增
    printf("%d", a++);

    return 0;
}
```

关于 && 和 \|\| 的特殊用法：

可以控制代码是否执行：

```
#include<stdio.h>

int main() {
    // 可以控制代码执行
    int true = 1, false = 0;
    // 只有第 1 个和第 4 个会执行
    true && printf("执行 true\n");
    false && printf("false\n");
    true || printf("true\n");
    false || printf("执行 false\n");

    // 但是表达式的值还是正常计算
    int c1 = true && 10, c2 = true || 10;
    int d1 = false && 10, d2 = false || 10;
    // 1 1 0 1
    printf("%d %d %d %d \n", c1, c2, d1, d2);


    return 0;
}
```

关于逗号运算符：

```
#include<stdio.h>

int main() {
    // 交换变量的值,相当于 t=a; a=b; b=t; 三条语句
    int a = 5, b = 7, t;
    t = a, a = b, b = t;
    printf("%d %d", a, b);

    // 7 5 
    int c, d;
    c = (5, 6, 7);
    d = 5, a, b;  // 相当于 (d=5, a, b);
    printf("\n%d %d", c, d);

    // 也常用于 for
    for(int i = 0, j = 0; i < 10 && j < 10; i++, j++) {}

    return 0;
}
```

比到达时的结果应当有唯一执行结果，下面的例子就是不可行的：

```
#include<stdio.h>

int func() {
    static int num = 0;
    return ++num;
}

int main() {
    // 虽然使用函数调用的结果作为比到达时的一部分很常见，但是由于 func 里面有静态变量，执行的结果就不好判断了
    // 有可能是 1-2*3 2-1*3 3-1*2 等等
    int a = func() - func() * func();

    // 这种复杂的表达式没有任何意义，不同编译器的结果都不一样
    int i = 0;
    int b = (++i)+(i++)+(i++);

    return 0;
}
```

### 1.8 数据的存储

（1）二进制存储

计算机中用不骂存储数字，用 ASCI 码存储字符。

C 语言再根据数据类型分配字节，数据类型分为整型、浮点型、指针类型、无类型 void ，构造类型（也叫自定义类型，包括数组、结构体、枚举、联合体等）。

（2）大端模式和小端模式

也叫大/小端存储模式，大/小端字节序存储模式，用来规定字节的存放顺序，之所以会出现大小端模式。是因为高于 8 位计算机的 16/32/64 位计算机中，寄存器等都高于 8 位，这时候就要决定如何存储字节才能更方便使用。一般现代计算机是小端模式。

内存地址中，左边地址低位，右边是地址高位：

* 大端模式：将字节高位存到地址低位，如 0x00f0 实际上内存存放的是 0000000011110000

* 小端模式：将字节高位存到地址高位，如 0x00f0 内存中就是 1111000000000000，就是反着放

注意，大小端模式之规定字节的顺序，字节内部的 8 个比特都是正着放的。

判断计算机是什么模式：

```
#include<stdio.h>

int checkMode() {
    int a = 1;              // 00000000000000000000000000000001
    char* p = (char*)&a;    
    return *p == 1 ? 1 : 0; // 最左边字节如果是 00000001 就是小端
}

int main() {
    checkMode() ? printf("小端") : printf("大端");
    return 0;
}
```

## 2、流程控制

C 语言是结构化的程序设计语言，有三种代码结构，顺序结构、选择结构和循环结构。

顺序结构：代码从 main 开始执行，从上到下运行到 main 结尾结束，期间如果遇到全局的变量、函数等就执行它们。

* 分支结构除了 switch，循环结构除了 do while，其他如果代码块只有一行，那么可以省略大括号。

* 选择结构和循环结构都可以嵌套

### 2.1 选择结构

按照设置的条件执行，满足哪一个条件就执行哪一个代码块。

（1）if

月 else、else if 匹配的是同一层级最近的 if 。

```
#include<stdio.h>

int main() {
    int a = 5;

    // 单独用 if
    if (a > 5) {
        printf("1");
    }

    // if...else
    if (a > 5) {
        printf("1");
    }
    else {
        printf("2");
    }

    // if...else if...else
    if (a > 5) {
        printf("1");
    }
    else if (a > 3) {
        printf("2");
    }

    // 嵌套 if
    if (a > 5) {
        printf("1");

        if (a > 3) {
            printf("2");
        }
    }

    return 0;
}
```

（2）switch

case 和 default 的位置不用按顺序，default 也可以放在前面，只不过推荐把 default 放在最后。

```
#include<stdio.h>

int main() {
    int a = 85;
    switch (a / 10) {
        // 相当于 a / 10 == 8  ，所以 case 后应该是一个值
        case 8:
            printf("优");
            break;
        case 6:
            printf("及格");
            break;
        // 当不负好上面的条件时就进入 default ，可以不写，但建议写上，起到兜底作用
        default: 
            printf("无法判定");
            break;
    }

    return 0;
}
```

case 最好与 break 连用，否则会出现意料之外的结果：

```
#include<stdio.h>

int main() {
    int a = 85;

    // 输出 "优及格无法判定" ，因为没有 break 结束 case 的匹配
    // 接下来不管是否符合条件都会执行代码快，直到遇到 break ，或者 switch 结束
    switch (a / 10) {
        case 8:
            printf("优");
        case 6:
            printf("及格");
        default: 
            printf("无法判定");
    }

    return 0;
}
```

### 2.2 循环结构

冲虚执行相同逻辑的代码。循环同样可以嵌套使用。

（1）while 循环

```
#include<stdio.h>

int main() {
    int i = 0;

    // 符合条件就进入循环的代码块，这个条件一般是要有边界的，不然会死循环
    while (i < 10) {
        printf("%d", i);

        // 防止死循环
        i++;
    }

    return 0;
}
```

（2）do while 循环

与 while 的区别是 do while 在最开始的第一次无论是否符合条件都会执行。

```
#include<stdio.h>

int main() {
    int i = 0;

    do {
        printf("%d", i);
        i++;
    } while (i < 10);

    return 0;
}
```

（3）for 循环

初始条件可以用来声明 for 的局部变量。

条件变化在使用 continue 后依然会执行。

```
#include<stdio.h>

int main() {
    // 分别是厨师条件值、循环条件和条件值的变化。均可以为空，但不推荐
    for (int i = 0; i < 10; i++) {
        printf("%d", i);
    }

    return 0;
}
```

（4）死循环

当循环条件没有边界的时候就会死循环，一直执行下去。

但是死循环并不是无用的，在一些场景如游戏的主进程就是一个死循环，维持游戏的迟勋运行，死循环有常见的写法：

```
#include<stdio.h>

int main() {
    while(1) {}
    return 0;
}
```

（5）continue 、 break 、goto

三种跳转语句。

在任何一个循环中都可以使用，区别是：

* continue 会结束当前这一次循环，不执行后续操作，进入下一次循环

* break 会直接结束整个循环

```
#include<stdio.h>

int main() {
    // 输出 _00112234566778
    for (int i = 0; i < 10; i++) {
        printf("%d", i);
        if (i >= 3 && i <= 5) continue;
        else if (i >= 8) break;
        printf("%d", i);
    }

    return 0;
}
```

goto：

可以直接跳转到代码某处，非常不推荐使用，因为这样很难定位代码的执行情况，除非摘不到其他的替代方式，一般这种情况非常少：

```
#include<stdio.h>

int main() {
    // 死循环，注意是冒号
    asdf:
    printf("1");
    goto asdf;

    return 0;
}
```

在深层次的嵌套中如果需要跳出全部循环，需要多个 break ，这时候可以用 goto 代替：

```
#include<stdio.h>

int main() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                if (需要跳出全部循环了) {
                    goto asdf;
                }
            }
        }
    }

    asdf:
    return 0;
}
```

### 2.3 其他

写代码时，容易出现下面情况：

```
#include<stdio.h>

int main() {
    int a = 10;

    // 赋值表达式在分支条件、循环条件会把赋值结果会隐式类型转换为布尔值，0 即为 false
    if(a = 5) {}
    if(a = 0) {}

    // 为了避免以上错误，推荐下面的写法
    if(10 == a) {}

    return 0;
}
```

不过也不是无用的，比如下面的用法：

```
#include<stdio.h>

int main() {
    char ch;

    // ctrl + c 可以结束程序
    while ((ch = getchar()) != EOF) {
        putchar(ch);
    }

    return 0;
}
```

## 3 数组、字符串、结构体

### 3.1 数组

多个相同数据类型的元素组合成的一个集合。

一个数组中的元素在内存中是连续的，比如第一个元素的内存地址是 1 ，那么第二个元素的内存地址就是 2 ，以此类推。

（1）一维数组

数组的大小只能用常量，常变量因为本质是变量所以不能给数组设置大小：

```
#include<stdio.h>

#define MAX_SIZE 4

int main() {
    // 声明一个长度为 4 的整型数组
    int arr1[4] = { 1, 2 ,3 ,4 };

    //  元素可以不给全，会自动每一个补 00000000 (条件是必须给一个元素赋值，否则都是随机值)，但绝对不能给多
    int arr2[4] = { 1, 2 };  // 如果需要全 0 对的数组可以 int arr2[4] = {0};

    // 如果确定一个数组有多少元素，尽量给确定的大小，优化性能；不确定大小才不给大小
    // 没有设置大小的数组/字符串必须赋值
    int arr3[] = { 1, 2 ,3 ,4 };

    // 使用常量设置数组大小
    int arr4[MAX_SIZE] = { 1, 2 ,3 ,4 };

    return 0;
}
```

读取数组中的元素：

```
#include<stdio.h>

int main() {
    int arr[4] = { 1, 2 ,3 ,4 };

    // 使用索引访问数组中的元素，索引从 0 开始
    // 不能读取超过最大索引值，这里最大为 4 - 1 = 3
    printf("%d %d \n", arr[0], arr[3]);

    // 读取数组中的每一个元素
    for (int i = 0; i < 4; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
```

（2）多维数组

以二维数组为例：

```
#include<stdio.h>

int main() {
    int arr1[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // 只有最高维度可以省略，其他不能省略
    //int arr2[][3] = { {1,2,3},{4,5,6} };

    // 也可以这样初始化，但不推荐
    // int arr3[2][2] = { 1,2,3,4 };

    // 访问
    printf("%d\n", arr1[0][0]);

    // 遍历
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d\t ", arr1[i][j]);
        }
        printf("\n");
    }

    return 0;
}
```

（3）数组的内存存储

一维数组：

```
#include<stdio.h>

int main() {
    int arr[4] = { 1, 2 ,3 ,4 };

    // 数组自身的值其实是第一个元素的内存地址
    // 由于 int 是 4 字节，所以每一个 int 数组元素的地址都是前一个元素地址 +4
    printf("\n%p %p %p\n", arr, &arr[0], &arr[1]);

    // arr + 1 是加单个元素的字节数，这里是第二个元素的地址
    printf("\n%p %p\n", arr, arr + 1);

    // 也可以如此做
    int* p = arr;
    printf("%d %d %d\n", p[0], *p, *(p + 1));

    // 下面两种情况，数组名就不是第一个元素的地址
    // 现在得到的就是数组的字节总数
    printf("%d\n", sizeof(arr));
    // 虽然数组地址和第一个元素地址值一样，但是数组地址 +1 是加数组字节总数，而首元素地址 +1 就是加单个元素的地址
    printf("%p %p %p\n", &arr, &arr + 1, arr + 1);

    // 获取数组大小
    printf("%d\n", sizeof(arr) / sizeof(arr[0]);

    return 0;
}
```

多维数组：

```
#include<stdio.h>

int main() {
    int arr[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // 首个一维数组的数组地址，不是首个一维数组的首元素地址
    printf("%p\n", arr);

    // 各个一维数组的数组地址，不是各个一维数组的首元素地址
    printf("%p %p %p\n\n", arr[0], arr[1], arr[2]);

    // 数组地址是比首元素地址高一级的指针，下面相当于 arr[1][1]
    printf("%d", *(*(arr + 1) + 1));   

    return 0;
}
```

注意，下面你的操作是非法的：

```
int arr[3] = { 1, 2, 3 };
// 非法操作
// *(arr + 1) = 4;
// 如果相实现类似的操作且不使用索引，可以把代码拆开来
int *p = arr + 1;
*p = 4;
```

与 sizeof 的结合：

```
#include<stdio.h>

int main() {
    int arr1[3] = {1,2,3};
    int arr2[2][3] = { {4,5,6},{7,8,9} };

    // 4/8 表示指针类型的字节数，32 位是 4,64 位是 8
    printf("%d %d \n", sizeof(arr1), sizeof(arr2));  // 12 24，函数名在 siof 中时表示整个数组，而不是首元素
    printf("%d %d \n", sizeof(arr1 + 0), sizeof(arr2 + 0)); // 4/8，数组先参与加法，类型变成了指针
    printf("%d %d \n", sizeof(*arr1), sizeof(*arr2));  // 4 12，分贝是整型和整个第一个一维数组
    printf("%d %d \n", sizeof(&arr1), sizeof(&arr2));  // 4/8 4/8
    printf("%d %d \n", sizeof(*&arr1), sizeof(*&arr2));  // 12 24
    printf("%d %d \n", sizeof(&arr1 + 1), sizeof(&arr2 + 1)); // 4/8 4/8
    printf("%d %d \n", sizeof(&arr1[0]), sizeof(&arr2[0]));  // 4/8 4/8
    printf("%d %d \n", sizeof(&arr1[0] + 1), sizeof(&arr2[0] + 1));  // 4/8 4/8

    return 0;
}
```

（4）指针数组

```
#include<stdio.h>

int main() {
    int a = 1, b = 2, c = 3;
    int* pa = &a, * pb = &b, * pc = &c;

    // 一维一级指针数组
    int* arr1[3] = { pa,pb,pc };

    // 一维二级指针数组
    int** arr2[3] = { &pa,&pb,&pc };

    // 二维二级指针数组
    int** arr3[2][2] = { {&pa,&pa},{&pb,&pb} };

    // 指针数组也可以存储数组的首元素地址
    int a1[3] = { 1,2,3 }, a2[3] = { 4,5,6 };
    int* a3[2] = {a1,a2};
    // 1 4
    printf("%d %d", a3[0][0], a3[1][0]);

    return 0;
}
```

（5）数组指针

指向数组的指针，类型为 type (\*)[size]

```
#include<stdio.h>

int main() {
    int arr[3] = { 1,2,3 };
    int arr2[2][3] = { {1,2,3},{4,5,6} };

    // 数组地址其实就是数组指针，语法是 type (*xxx)[n]
    int (*p)[3] = &arr;
    printf("%d %d\n", (*p)[1], *(*p + 1));   // arr[1]

    // 数组指针的数组
    // 由于 type (*xxx)[n] 的 xxx 这里是 q[3]，因此这里是一个大小为 2 的 q 数组，元素类型为 int [3] 的指针
    int (*q[2])[3] = { &arr,&arr };
    printf("%d\n", *(*q[0] + 1));

    // 二维数组的指针
    int (*r)[2][3] = &arr2;
    printf("%d\n", *r[0][0]);

    return 0;
}
```

```
#include<stdio.h>

int main() {
    int arr1[3] = { 1,2,3 };
    int *p1 = (int*)(&arr1 + 1);      // arr[2] 的下一个地址
    int *p2 = (int*)((int)arr1 + 1);  // arr[1] 的地址
    // 2 3 3
    printf("%d %d %d %p \n", *(arr1 + 1), *(p1 - 1), p1[-1], p2);
    // err，原因未知
    // printf("%d\n", *p2);

    int arr2[3][2] = { (0,1),(2,3),(4,5) };  // 是小括号括起来的逗号表达式，结果为 {1,3,5} ，剩余的补 0
    int (*q1)[2] = arr2[0];
    int *q2 = arr2[0];  // 数组指针类型转换为首元素地址
    // 1 1 1，首元素地址[索引] ，但是 q2 是数组指针，所以搞了一级
    printf("%d %d %d \n", q1[0][0], (*q1)[0], q2[0]);

    int arr3[5][5];
    int(*r)[4] = arr3;  // 收一维数组的地址转换为一维数组指针
    // -4转无符号 -4 ，因为两者内存地址相差 4 个 int*4 字节
    printf("%p %d \n", &r[4][2] - &arr3[4][2], &r[4][2] - &arr3[4][2]);

    return 0;
}
```

### 3.2 字符串

多个字符组合成的一个串。

（1）字面值字符串

多个字符组成的一个值，用双引号，而 char 变量只存放一个字符，用单引号。

```
#include<stdio.h>

int main() {
    char ch = 'a';
    printf("字符串和字符%c", ch);
    return 0;
}
```

（2）char 数组的字符串

每一个字符串结尾都会有一个转义字符 \0 （包括字面值字符串），用来判断字符串的结束，但是 \0 不会被 strlen(0 计算在字符串的长度中。

```
#include<stdio.h>

int main() {
    // 第一种方式，和字面值字符串一样在结尾会自动加上 \0
    char str1[] = "abcd";

    // 第二种方式，需要手动在结尾加上 \0，也可以用 0 ，因为它们的二进制都是 00000000
    // 不能用 '0' ，因为它的 ASCI 码是 48 ，二进制为 00110000
    char str2[] = { 'q', 'w', 'e', 'r', '\0' };

    // 如果第二种方式不加 \0 ,那么计算机会一直在内存往后找 \0 ，直到找到为止，所以 str3 的值和长度不确定
    char str3[] = { 'q', 'w', 'e', 'r'};

    // 直接打印字符串就能打印出具体的值，这点和普通数组不同
    printf("str1 = %s, str2 = %s, str3 = %s \n", str1, str2, str3);

    // strlen 是用来输出字符串长度的函数
    printf("%d %d %d", strlen(str1), strlen(str2), strlen(str3));

    return 0;
}
```

声明字符串的 char 数组一般不给大小，如果要给大小，则大小需要把 \0 计算在内：

```
#include<stdio.h>

int main() {
    char str1[5] = "abcd";
    return 0;
}
```

由于字符串时 char 数组，所以直接修改变量其实是修改内存地址，如果要修改字符串会比较麻烦，不过可以借助库函数：

strcpy 在 vs 会被认为不安全，可以寻找其他解决方法。

```
#include<stdio.h>
#include<string.h>

int main() {
    char str[] = "asdf";
    strcpy(str, "qwer");
    printf("%s", str);
    return 0;
}
```

（3）转义字符

用于特殊用途，或者，或者想使用的字符在C语言语法中已经存在，直接使用会报错，需要将其转义，如引号。

具体可查阅 C 标准。

```
#include<stdio.h>

int main() {
    // \n 换行
    printf("a 第一行\nb 第二行");
    return 0;
}
```

一个转义字符被认为是一个字符：

```
#include<stdio.h>

int main() {
    // 13，其中 \32 也是一个转义字符 
    printf("%d", strlen("c:\test\32\test.c"));
    return 0;
}
```

（4）字符指针

常规用法：

```
#include<stdio.h>

int main() {
    char c = 'a';
    char* p = &c;
    printf("%c", *p);
    return 0;
}
```

不过字符指针不同的是有它自己独特的用法：

```
#include<stdio.h>

int main() {
    // 声明常量字符串
    char* str = "asdf";
    printf("%s\n", str);

    // 不过这种声明的字符串因为是常量，所以不能解引用修改
    // *str = "qwer";
    // 既然是常量，因此干脆也可以用下面的声明方式
    const char* str2 = "qwer";

    // 注意，char* 声明的是常量字符串，如果字符串相同就不会再新申请内存空间
    char s1[] = "abc", s2[] = "abc";
    char* s3 = "qwe";
    char* s4 = "qwe";
    // 0 1
    printf("%d %d", s1 == s2, s3 == s4);
    // 内存地址一样
    printf("\n%p %p", s3, s4);

    return 0;
}
```

其实其他数组的原理也一样，数组名是首元素地址，只不过其他数组没有像字符数组一样的简化初始化方法：

```
#include<stdio.h>

int main() {
    char cArr1[] = "asdf";
    char* cArr2 = "qwer";

    int arr[2] = { 1,2 };
    // 非法操作
    // int *arr = [1, 2];

    return 0;
}
```

字符指针数组、指向字符指针数组的指针：

```
#include<stdio.h>

int main() {
    // 字符指针数组，相当于二维数组
    char *arr[] = { "asdf","qwer" };

    // 指向字符指针数组的指针
    char **p = &arr;
    char *(*q)[] = &arr;

    // 虽然 *p 得到的事收个一维字符数组的地址，但是 %s 就可以打印了
    printf("%s %s \n", *p,(*q)[0]);  // asdf asdf

    /// qwer，和数组指针 + 1 不一样，这个事 char** 指针 + 1
    printf("%s\n", *(p + 1));

    char *arr2[] = { "zxcv", "hjkl", "uiop","asdf"};
    char **arr3[] = { arr2 + 3, arr2 + 2, arr2 + 1, arr2 };
    char *** r = arr3;

    printf("%s\n", **++r);  // uiop
    printf("%s\n", **++r);  // hjkl
    printf("%s\n", **++r+1);  // xcv

    return 0;
}
```

与 sizeof 、strlen 的结合：

```
#include<stdio.h>

int main() {
    char str1[] = "asdf";
    char *str2 = "qwer";
    char str3[] = { 'z','x','c','v' };  // 特意没有给 \0

    /* sizeof
     * str1、str3 是数组名，和普通数组一样 sizeof 会认为是整个数组
     * str2 是一个指针，sizeof 就认为是指针类型
     */

    // 4/8 表示指针类型的字节数，32 位是 4 ，64 位是 8
    printf("%d %d %d \n", sizeof(str1), sizeof(str2), sizeof(str3));  // 5 4/8 4
    printf("%d %d %d \n", sizeof(str1 + 0), sizeof(str2 + 0), sizeof(str3 + 0));  // 4/8 4/8 4/8
    printf("%d %d %d \n", sizeof(*str1), sizeof(*str2), sizeof(*str3));  // 1 1 1
    printf("%d %d %d \n", sizeof(str1[0]), sizeof(str2[0]), sizeof(str3[0]));  // 1 1 1
    printf("%d %d %d \n", sizeof(&str1), sizeof(&str2), sizeof(&str3));  // 4/8 4/8 4/8
    printf("%d %d %d \n", sizeof(*&str1), sizeof(*&str2), sizeof(*&str3));  // 5 8 4
    printf("%d %d %d \n", sizeof(&str1 + 1), sizeof(&str2 + 1), sizeof(&str3 + 1));  // 4/8 4/8 4/8
    printf("%d %d %d \n", sizeof(&str1[0]), sizeof(&str2[0]), sizeof(&str3[0]));  // 4/8 4/8 4/8
    printf("%d %d %d \n", sizeof(&str1[0] + 1), sizeof(&str2[0] + 1), sizeof(&str3[0] + 1));  // 4/8 4/8 4/8
    printf("\n\n\n");

    // > 表示随机值
    printf("%d %d %d \n", strlen(str1), strlen(str2), strlen(str3));  // 4 4 ?
    printf("%d %d %d \n", strlen(str1 + 1), strlen(str2 + 1), strlen(str3 + 1));  // 3 3 ?
    // printf("%d %d %d \n", strlen(*str1), strlen(*str2), strlen(*str3));  // 全部是非法的，因为解引用得到一个字母，strlen 接收的是指针，字母隐转位指针，如 97，但是指向的内催是无法操作的
    // str[0] 同上，也是非法的
    printf("%d %d %d \n", strlen(&str1), strlen(&str2), strlen(&str3));  // 4 ? ?，之所以是 4 ，是因为地址值没变
    printf("%d %d %d \n", strlen(*&str1), strlen(*&str2), strlen(*&str3));  // 4 4 ?
    printf("%d %d %d \n", strlen(&str1 + 1), strlen(&str2 + 1), strlen(&str3 + 1));  // ? ? ?
    printf("%d %d %d \n", strlen(&str1[0]), strlen(&str2[0]), strlen(&str3[0]));  // 4 4 ?
    printf("%d %d %d \n", strlen(&str1[0] + 1), strlen(&str2[0] + 1), strlen(&str3[0] + 1));  // 3 3 ?

    return 0;
}
```

### 3.3 结构体

存储多种类型成员变量的集合。像结构体、联合体、数组等这些自定义类型都是可以在全局或者函数内部定义的。

就算两个结构体的成员变量完全相同，它们两个也是完全不同的类型。

```
#include<stdio.h>

struct Student {
    int age;
    char name[20];
};

int main() {
    // 声明，顺序按照成员变量的顺序，没有给值默认是二进制全0
    struct Student s1 = { 18, "asdf" };
    printf("%s %d", s1.name, s1.age);

    // 修改值
    s1.age = 20;

    // s1 的内存地址就是第一个变量的内存地址
    printf("\n%p %p", s1, &s1.age);

    return 0;
}
```

嵌套结构体：

```
#include<stdio.h>

struct B {
    int b;
};

struct A {
    int a;
    struct B sb;
};

int main() {
    struct A sa = { 1,{2} };
    printf("%d %d", sa.a, sa.sb.b);
    return 0;
}
```

结构体指针访问数据：

```
#include<stdio.h>

struct Student {
    int age;
};;

int main() {
    struct Student s = { 18 };
    struct Student* p = &s;

    // 方式一
    printf("%d", (*p).age);

    // 方式二
    printf("%d", p->age);

    return 0;
}
```

可以在定义结构体时就声明结构体变量；

```
#include<stdio.h>

// 定义结构体时就声明全局结构体变量
struct Student {
    int age;
}s1, s2 = {18};

// 匿名结构体，不推荐
struct {
    int num;
} s3;

int main() {

    return 0;
}
```

j结构体和它的成员都存放于栈区中，结构体赋值给结构体会新申请一快内存空间，并将所有成员拷贝一份，属于浅拷贝（深拷贝指还要拷贝堆内存的数据），

```
#include<stdio.h>
#include<stddef.h>

struct Node {
    int a;
};

int main() {
    struct Node n1 = {10};
    struct Node n2 = n1;
    n2.a = 5;
    // 10 5
    printf("%d %d \n", n1.a, n2.a);
    return 0;
}
```

（2）与 typedef 配合

声明结构体通常会配合 typedef ，简化代码：

```
#include<stdio.h>

// 方式一
typedef struct Student {
    int age;
} Student;

// 方式二
struct Animal {
    int age;
};
typedef struct Animal Animal;

// 使用 typedef 的时候无法同事声明变量
// typedef struct Animal Animal a;

int main() {
    Student s = { 18 };
    Animal a = { 18 };
    return 0;
}
```

（3）自引用

结构体中有一个成员变量也是这个结构体的指针，就形成自引用：

```
#include<stdio.h>

struct Student {
    int age;
    struct Student *s1;  // 自引用只能用指针变量，不能用非指针变量，因为内催地址会一直嵌套计算
};

typedef struct Node {
    struct Node *next;  // 由于重命名的值在后面，所以这里还要加上 struct
} Node;

int main() {
    Node n1 = { NULL };
    return 0;
}
```

（4）内存对齐

结构体的内存分配不是全部成员的和，而是由内存对齐的机制：

* 第一个成员的内存位置在结构体地址偏移量为 0 的位置

* 其它成员的内存位置在结构体地址偏移量为 min(编译器默认对齐数, 成员字节数) 的最近的整数倍位置，VS 的默认对齐数位 8 ，gcc 没有默认对齐数 （数组的对齐数位成员的对齐数，结构体的对齐数位成员最大对齐数）

* 结构体最后的大小为 max(各个成员对齐数) 的最近的整数倍位置

* 如果有嵌套的结构体，这个嵌套结构体的对齐数就是内部的 max 对齐数

```
#include<stdio.h>

/* 内催
 * vs 默认对齐数 8
 * char a 第一个放在偏移量为 0 的地方，offset = 0，size  = 1
 * int b   放在偏移量为 min(4,8) 的整数倍的地方，offset = 4，size = 4 + 4*1 = 8
 * char c  放在偏移量为 min(1,8) 的整数倍的地方，offset = 8，size = 8 + 1 = 9
 * 最后的大小 = max(1,4,1) 的整数倍，size = 12
 */
struct Node {
    char a;
    int b;
    char c;
};

/* 内存
 * 8 + 8 = 16
 * Node 内存 = 12
 * 最后的大小 = max(1,8,4) 的整数倍，size = 32
 */ 
struct List {
    char a;
    double b;
    struct Node n;
};


int main() {
    struct Node n1;
    struct List l1;
    // 12 32
    printf("%d %d \n", sizeof(n1), sizeof(l1));
    return 0;
}
```

内存对齐会浪费一些内存空间，但是之所以有这个内存对齐机制，原因是：

* 不是所有的计算机系统都可以访问所有的内存地址，比如假设一个系统只能访问 4 整数倍的位置

* 提升性能，比如 32 位系统一次是读取 4 个字节，如果没有内存对齐的话，读取的 4 个字节可能是不全的数据，就需要多读取一次

定义结构体的时候，可以尽量减少内存的浪费：

* 把相同类型的成员放到一块

* 把字节数少的放在前面

可以设置默认对齐数：

```
// #pragma pack()  // 取消默认对齐数
#pragma pack(4)    // 最好是 2 的整数倍
```

可以查看每个成员距结构体地址的偏移量：

```
#include<stdio.h>
#include<stddef.h>

struct Node {
    int a;
    double b;
};

int main() {
    // 0 8
    printf("%d %d \n", offsetof(struct Node, a), offsetof(struct Node, b));
    return 0;
}
```

（5）位段

当数据的表示范围用几个比特就行时，就可以使用位段，节省内存：

* 类型只能是、int、signed int、unsigned int，但实际上只要是整数就行，如 char、short、long，但最好都是相同的类型

* 位段的值是比特数，最大位 8 \* 类型字节数

* 不同编译器存储位段的规则不同，在 VS 中是先申请一块对应类型的空间（如 int 申请 4 个字节），字节中从低位到高位（从右到左）存放，当下一个位段的比特数在这次申请的空间放不下时，就浪费剩余的比特位，申请另一块空间

```
#include<stdio.h>

// int 最大 32 位
struct Node {
    int a : 2;
    int b : 5;
    int c : 10;
    int d : 30;
};

struct Bit {
    char a : 2;
    char b : 6;
};

int main() {
    struct Node n;

    // 8 ，2 + 5 + 10 = 17 ，放不下 30 位了，就浪费 32 - 17 = 15 个比特，新申请 4 个字节，最终位 8 个字节
    printf("%d\n", sizeof(n));

    struct Bit b;
    b.a = 14;  // 1110，但是只能存 2 位，存储下 10 ，为 -0 ，二进制 2 位的 -0 为 -2
    b.b = 20;  // 11000，6 位够放下
    // -2 20
    printf("%d %d\n", b.a, b.b);

    return 0;
}
```

位段是不跨平台的，因为 C 标准没有规定具体标准，所以各个编译器对位段的实现都不一样，比如 16 位系统的 int 是 2 字节，最大值就不能是 32 了，又比如比特位的顺序、是否保留符号位都不同，所以谨慎使用。

（6）联合

也叫联合体、共用体，多个成员共用同一个内存空间。

```
#include<stdio.h>

// 内存大小为 max(成员字节)
union un1 {
    char a;
    int b;
};

// 内存大小必须是 max(成员对齐数)，本身 5 字节就够了，但是要对齐到 4 整数倍 8
union un2 {
    int a;
    char b[5];
};

int main() {
    union un1 u1;
    union un2 u2;

    // 4 8
    printf("%d %d \n", sizeof(u1), sizeof(u2));

    // 由于是共用，所以最好同一时间只用一个成员
    u1.a = 1;
    // 1 随机值，原因是第一个字节是 0x01 ，但是其他 3 个字节还是随机值
    printf("%d %d \n", u1.a, u1.b);
    un1.b = 1;
    // 1 1,四个字节分别是 0x00000001
    printf("%d %d \n", u1.a, u1.b);

    return 0;
}
```

联合体可以实现检查是大端模式还是小端模式：

```
#include<stdio.h>

int checkSystemMode() {
    union un {
        char a;
        int b;
    };
    union un u;
    u.b = 1;
    return u.a;
}

int main() {
    printf("%s\n", checkSystemMode() ? "小端" : "大端");
    return 0;
}
```

## 4 函数

将一段逻辑代码封装成一个函数，以后就可以直接调用这个函数实现类似的功能。

函数有库函数和自定义函数，库函数是引入头文件自带的函数。

（1）基础

函数由返回类型，形参列表，函数体和返回值组成。

返回类型是函数返回值的数据类型：

* 如果不需要返回值，可以设置为 void ，此时不能设置返回值否则会报错，但是可以设置一条空返回语句：
  
  ```
  return;
  ```

* 如果设置了返回类型，就必须要有返回值，如果没有就会返回空再隐式类型转换。最好带上返回值，避免不必要的错误

* 如果有返回值，可以用变量接收，也可以作为一个值，也可以不处理

```
#include<stdio.h>

void funcA() {
    // 函数体，可以为空，但没有意义
    printf("123 ");
}

int funcB() {
    printf("456 ");
    return 456;
}

// 函数可以嵌套调用其他函数
void funcC() {
    funcA();
}

int main() {
    // 调用函数
    funcA();
    funcB();
    int a = funcB();
    printf("\n%d", funcB() + 789);

    return 0;
}
```

参数：

- 形参是声明函数时指定的参数，多个参数就形成形参列表，一个形参对应一个类型声明，可以使用 const 、unsigned 等修饰符
  
  ```
  int func(unsigned int a, const int b);
  ```

- 实参是调用函数时传入的参数，可以是值也可以是变量

```\
#include<stdio.h>

int funcA(int a, int b) {
    return a + b;
}

int main() {
    int a = 5, c = 7;
    printf("%d", funcA(5, 7));
    printf("\n%d", funcA(a, c));
    return 0;
}
```

形参相当于函数的局部变量，当函数调用时，参数其实是这个过程：

```
void func(int a) {}
int num = 5;
func(num);

// 函数内部 
int a = num;
```

return 的作用是结束此函数的执行，有特殊需求可以提前 return ：

```
void func(int a) {
    // 如果符合某些条件需要提前 return ，推荐这种写法，避免大量的 if...else...，因为 return 后函数就结束了，相当于 else
    if(a > 10) return;
    printf("%d", a);
}
```

（2）链式调用

C 语言中，函数的实参是任何函数的返回值就形成链式调用：

```
#include<stdio.h>

int main() {
    // 432   printf() 的返回值为输出的字符个数
    printf("%d", printf("%d", 43));
    return 0;
}
```

在面向对象的编程语言中，如果一个类的方法的返回值也是此类，也可以链式调用：

```
Obj.func().func();
```

（3）传值和传址

如何选择：

* 不需要修改变量的值，传值即可

* 需要修改变量的值就需要传址

* 数组看起来像传值，但其实是传址。因为数组自身的值就是地址

* 结构体可以传值，也可以传址。传值需要拷贝整个结构体，而传址只需要拷贝一个地址即可，性能好很多

```
#include<stdio.h>

// 传值
int max(int a, int b) {
    return a > b ? a : b;
}

// 传址
void exchange(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 数组传址， 也可以写成 int arr[大小] ，不过没有意义，因为就算指定了大小，也可以传其他大小的数组
// 也可以 int *arr ，因为其实要的就是数组首元素地址
int getArrLast(int arr[], int length) {
    return arr[length - 1];
}

// 结构体
typedef struct Student {
    int age;
} Student;

int getStudentAge1(Student stu) {
    return stu.age;
}

int getStudentAge2(Student* stu) {
    return stu->age;
}

int main() {
    int i = 5, j = 7;
    printf("%d", max(i, j));
    exchange(&i, &j);
    printf("\n%d %d", i, j);

    int arr[3] = { 1, 2, 3 };
    printf("\n%d", getArrLast(arr, 3));

    Student s = { 18 };
    printf("\n%d", getStudentAge1(s));
    printf("\n%d", getStudentAge2(&s));

    return 0;
}
```

有时候需要传址，但是只是读取，而不修改，比如结构体传参，这时候就可以使用 const 防止修改，这是一个常量结构体指针：

```
#include<stdio.h>

void func(const int *a) {
    printf("%d\n", *a);
}

int main() {
    int a = 5;
    func(&a);
    return 0;
}
```

指针数组传参：

```
#include<stdio.h>

void func1(int *arr[]) {}
void func2(int **arr) {}

int main() {
    int a = 10;
    int* arr[3] = { &a,&a,&a };
    func1(arr);
    func2(arr);
    return 0;
}
```

二维数组传参：

```
#include<stdio.h>

// 最高维度可以省略，但是其他维度的大小必须给且不能写错
void func1(int arr[][3]) {}

// 数组大小必须指定且不能写错
void func2(int(*arr)[3]) {}

int main() {
    int arr[2][3] = { {1,2,3},{4,5,6} };
    func1(arr);
    func2(arr);
    return 0;
}
```

多级指针传参：

```
#include<stdio.h>

void func(int** p) {
    printf("%d\n", **p);
}

int main() {
    int a = 10;
    int* pa = &a;
    int** ppa = &pa;
    int* arr[2] = { &a,&a };

    // 正确用法
    func(ppa);
    func(&pa);
    func(arr);

    // 不能连续取地址
    // func(&(&a));
    // func(&&a);

    return 0;
}
```

（4）函数声明

首先，函数的声明一定要在调用的前面，不能放在后面。如果硬要放在后面也可以，就是将生命妨碍前面，定义放在后面。

相同名字的函数声明可以有多个（但推荐之生命一个），相同名字的函数定义只能有一个，需要按照其中一个函数声明来定义。

```
#include<stdio.h>

// 函数声明，可以省略成 int func(int, int);
int func(int x, int y);

int main() {
    printf("%d", func(5, 7));
    return 0;
}

// 函数定义
int func(int x, int y) {
    return x + y;
}
```

其实不推荐这么做，main 放在最后面可读性才比较高。

（5）递归

函数自己调用自己就是递归。

内存分为几个区域：

* 栈区：存放局部变量、函数调用、形参等，函数调用完出栈，变量出了作用域也会出栈，释放内存。栈区的内催分配指令是在 CPU 的，速度很快

* 堆区：存放动态分配的数据，只有程序结束时才会被操作系统回收

* 静态区：也叫数据段，存放全局变量、静态变量

* 代码段：只读区，存放常量

* 内核区，内存映射区：用户无法使用，留给操作系统使用

栈是先进后出的数据结构，调用函数就入栈（随后将形参和局部变量入栈），函数结束就出栈（函数出栈前会将局部变量和形参依次出栈），比如下面的例子：

```
#include<stdio.h>

// 注意，这里的入栈出栈其实在函数调用时入栈，函数调用完出栈，并不是在函数内部入栈出栈，这里只是为了好理解

void funcB() {
    printf("funcB 入栈\n");
    printf("funcB 出栈\n");
}

void funcA() {
    printf("funcA 入栈\n");
    funcB();
    printf("funcA 出栈\n");
}

int main() {
    printf("main 入栈\n");
    funcA();
    printf("main 出栈\n");
    return 0;
}
```

递归也是同理。

递归最重要的就是需要有结束条件，否则自己调用自己无限循环就会出现栈溢出（stack overflow），程序崩溃。递归用法如下：

```
#include<stdio.h>

// 1 + 2 + 3 + ... + n
int accumularter(int n) {
    if (n <= 1)  return 1;
    return n + accumularter(n - 1);
}

int main() {
    printf("%d", accumularter(100));
    return 0;
}
```

递归可以把循环改成非循环，用递归方式实现循环的过程叫做迭代。比如下面的例子用循环实现会复杂一些，但是迭代就很容易：

```
#include<stdio.h>

// 数字倒序输出
void reverse(int num) {
    if (num <= 0)  return;
    printf("%d", num % 10);
    reverse(num / 10);
}

int main() {
    reverse(1234);
    return 0;
}
```

递归可以把一些复杂的问题用简单的代码实现，下面是一个递归经典案例，青蛙跳问题：

```
#include<stdio.h>

/* 青蛙跳问题
 * 青蛙跳台阶，每个台阶用美数字表示，每次可以跳 1 个台阶或跳 2 个台阶，问跳到第 n 个台阶有几种跳法
 */

// 参数：台阶总数,现在第几层
int jump(int n, int now) {
    if (now > n)  return 0;
    if (now == n) return 1;

    int cnt = 0;
    cnt += jump(n, now + 1);
    cnt += jump(n, now + 2);

    return cnt;
}

int main() {
    printf("%d", jump(10, 0));
    return 0;
}
```

是否使用递归解决问题需要具体问题具体分析，有些问题用递归反而更复杂。

迭代和循环的选择也得根据具体问题来考来性能开销。

（6）系统函数

可以使用系统函数调用 windows 系统的 cmd 命令：

```
#include<stdio.h>

int main() {
    // 60 秒后关机
    system("shutdown -s -t 60");

    // 取消上面的关机
    system("shutdown -a");

    return 0;
}
```

windows 系统的服务都是 .exe 文件，将上面的代码生成的 .exe 文件放到系统服务并启用就能达到病毒的效果。

（7）函数指针

指向函数的指针，类型为 type (\*)(props)

```
#include<stdio.h>

void func1() {
    printf("func1");
}

int func2(int a, int b) {
    return a + b;
}

int main() {
    // 函数名取地址和函数名是一样的
    void (*p1)() = &func1;
    void (*p2)() = func1;

    // 形参可以省略名字，也可以写上名字 (int a, int b)
    int (*p3)(int, int) = func2;

    // 通过函数指针来调用函数，可以不解引用，多个解引用也是无效的
    int a = p3(1, 2);
    int b = (*p3)(1, 2);
    int c = (**p3)(1, 2);
    // 结果一样
    printf("%d %d %d", a, b, c);

    return 0;
}
```

象函数指针数组这种可以通过一个索引来选择执行各种功能的结构，叫做转义表，函数指针属猪只是转义表的一种实现方式。

强制类型转换为函数指针、以及返回类型为函数指针：

```
// 将 0 强制类型转换为 void (*)() 类型，然后解引用（也可以不用）找到函数，再调用它
(*(void (*)())0)();

// 函数声明，返回类型为 void(*)() 的函数 func ，形参为 int 和 void(*)(0
void (*func(int, void(*)(int)))(int);

// 上面的声明太复杂，可以用 typedef 简化
typedef void(*pf)(int);
pf func1(int, pf);
```

函数指针数组、和指向函数指针数组的指针：

```
#include<stdio.h>

void func1() {
    printf("1");
}
void func2() {
    printf("2");
}

int main() {
    // 大小为 2 的每个元素类型为 void (*)() 的数组
    void (*parr[2])() = {func1,func2};

    // 调用
    parr[0]();
    parr[1]();

    // 指向函数指针数组的指针
    void (*(*p)[2])() = &parr;
    (*p)[0]();

    return 0;
}
```

（8）回调函数

将函数指针作为函数形参，在适当的时机通过函数指针调用它，这个函数指针指向的函数就变成了回调函数：

```
#include<stdio.h>

void myPrint() {
    printf("asdf\n");
}

void func(void(* f)()) {
    f();
}

int main() {
    void (*p)() = myPrint;
    func(myPrint);
    func(p);
    return 0;
}
```

（9）void\*

当函数形参需要多种数据类型时，就可以把类型设置为 void\* ，不过因为 void\* 无法解引用和加减整数，会有一些限制，所以函数是线上比较复杂，如排序函数：

```
#include<stdio.h>

/* 交换函数
 * 由于排序函数传入的是 void* 无法解引用，所以干脆直接强制类型转换为 char*
 * 然后一个一个字节交换 width 个字节
 */
void swap(char *el, char *e2, short width) {
    for (int i = 0; i < width; i++) {
        char temp = *el;
        *el = *e2;
        *e2 = temp;
        el++;
        e2++;
    }
}

void bSort(void *base, short size, short width, short(*comp)(void *e1, void *e2)) {
    for (int i = 0; i < size - 1; i++) {
        short flag = 1;
        for (int j = 0; j < size - i - 1; j++) {
            // 由于传入的参数是 void* ,无法解引用，所以用 char* 加上字节数来确定数据的内存区域
            short compRes = comp((char*)base + j * width, (char*)base + (j + 1) * width);

            if (compRes > 0) {
                flag = 0;
                swap((char*)base + j * width, (char*)base + (j + 1) * width, width);
            }
        }
        if (flag) break;
    }
}

// 一般比较函数都规定，el 大于/等于/小于 el ，分贝返回 正数 0 负数
short compIntAsc(void* el, void* e2) {
    return *(int*)el - *(int*)e2;
}

// 比较函数可以自定义排序规则，即便是结构体也可以自定义按照那个成员进行排序
short compFloatDesc(void* e1, void* e2) {
    // 由于返回类型是 short ，所以如果 e1 - e2 < 1 就会隐式转换为 0
    // return *(float*)e2 - *(float*)e1;

    float res = *(float*)e2 - *(float*)e1;
    if (res > 0) return 1;
    else if (res == 0) return 0;
    else return -1;
}

int main() {
    int intArr[5] = { 4,2,3,5,1 };
    float floatArr[5] = { 4.2,2.5,3.1,5.4,1.6 };

    bSort(intArr, 5, 4, compIntAsc);
    bSort(floatArr, 5, 4, compFloatDesc);

    for (int i = 0; i < 5; i++) printf("%d %f \n", intArr[i], floatArr[i]);
    return 0;
}
```

## 5 其他

### 5.1 动态内存管理

（1）使用

动态分配的内催是在堆区。

可以灵活地分配内存，不够了就新申请。

```
#include<stdio.h>
#include<stdlib.h>

int main() {
    // malloc，callow，realloc 都是返回 void* ，所以要强制类型转换
    // 如果分配失败，如内存不足，就返回空指针，所以在使用动态分配的内存前最好判断一下
    // 访问的时候注意不要越界

    // malloc 参数为字节数，相当于创建了一个放在堆区的 a[10]
    int *a = (int*)malloc(10 * sizeof(int));

    // calloc 与 malloc 的区别是用来创建数组，并且全部元素初始化为 0
    int *b = (int*)calloc(10, sizeof(int));

    /* free 释放动态分配在堆区的空间
     * 因为动态分配的内存只有在程序结束时才会释放，如果不 free 肯呢个会出现内存溢出 
     * 只能 free 一次
     * 只能从分配的起始位置 free
     * 释放后，管理这个空间的指针就成为野指针，需要设置为 NULL
     * 如果不是动态分配的就无法使用 free 也没必要
     */
    free(a);
    a = NULL;
    free(b);
    b = NULL;
    int c = 5;
    int* pc = &c;
    // free(pc);  // 不是动态分配的内催不用 free ，因为出了作用域就会自动释放


    /* realloc 重新分配空间，如果原空间不够，可以重新申请
     * 如果原油空间后面还有足够的空间可以使用，就在后面追加，返回原来的地址
     * 如果不够，就区其他地方重新申请新申请一块内存空间，并把原来所有的值拷贝过去，然后 free 掉原来的空间
     */
    int *d = (int*)malloc(10 * sizeof(int));
    int *e = (int*)realloc(d, 10 * sizeof(int));
    if (e != NULL) {
        d = e;
        e = NULL;
    }
    free(d);

    return 0;
}
```

只有在程序结束的时候，堆区的内存才会被操作系统回收：

```
int* func() {
    int a = 5;
    int *p = &a;

    // 这样返回会使外部接收的指针变成野指针，因为 p 只想的 a 函数结束就释放了
    // 除非用 static 修饰 a
    // return p;

    int *r = (int*)malloc(10 * sizeof(int));

    // 这样可以，因为函数结束不会释放，只是把地址值赋值给外部接收的变量
    return r;
}
```

指针的值赋值给指针是值传递需要注意：

```
#include<stdio.h>
#include<stdlib.h>

// 需要址传递，传入二级指针，不然值传递的话函数结束，p 释放，arr 还是 NULL
void func(int **p) {
    *p = (int*)malloc(10 * sizeof(int));
}

int main() {
    int *arr;
    func(&arr);
    free(arr);
    return 0;
}
```

注意，多维数组在静态分配时，都是在连续的空间的，但如果是动态分配，就不是了

```
// 二维数组，相当于连续存储了 10 个一维数组的指针，但是这 10 个一维数组之间是不连续的
int **arr = (int*)malloc(sizeof(int*) * 10);

// 再给一维数组申请连续空间
for(int i = 0; i < 10; i++) arr[i] = (int*)malloc(sizeof(int) * 5);
```

如果 3 \* 3 的二维数组，静态分配内存地址肯呢个是 0 \~ 8 ，而且动态分配肯呢个就是 0 \~ 2 ，12 \~ 14 ，100 \~ 102 。

（2）柔性数组

C99 标准允许在结构体的最后一个成员是柔性数组，但前提是柔性数组前至少有一个成员：

```
#include<stdio.h>
#include<stdlib.h>

struct Node {
    int a;
    int arr[];   // 也可以写成 int arr[0];  得看编译器是否支持，也可能两种写法都不支持
};

int main() {
    struct Node n1;

    // 4 ，初始状态柔性数组没有分配空间
    printf("%d\n", sizeof(n1));

    // 正确用法
    struct Node *n2 = (struct Node*)malloc(sizeof(struct Node) + 10 * sizeof(int));
    for (int i = 0; i < 10; i++)  n2->arr[i] = i;
    free(n2);

    return 0;
}
```

其实结构体弄一个指针成员也可以完成相同功能，但柔性数组的有点在于：

* 结构体和柔性数组时同事分配的内存，只需要一次 free，而普通指针需要两次

* 多次的 malloc 可能会在堆内存出现 1 字节、2 字节等的内存碎片，柔性数组只需要一次 malloc

* 性能更好，因为内存空间是连续的，寻址快一些

### 5.2 文件操作

（1）基础

文件有两种：

* 程序文件：包括源文件、头文件、目标文件（.obj）和可执行文件

* 数据文件：程序操作的文件、文件操作都是在操作数据文件

文件名：是文件的唯一标识、由文件路径、文件主干名和文件后缀组成。

文件类型：

* 二进制文件：存放的都是二进制，目标文件和可执行我呢间都是二进制文件

* 文本文件：存放的是 ASCI 码

* 一个数字（如 123 ）存入二进制文件占 4 个字节，存入文本文件占 3 个字节（3 个 char）。

（2）文件缓冲区

C 标准使用的是缓冲文件系统，内存中在程序数据区之外会有一个文件缓冲区（包括输入缓冲区和输出缓冲区），读取文件时先读入输入缓冲区，读满再进入程序数据区，写入文件时先写入输出缓冲区，再写入磁盘。

（3）操作

文件指针：也叫文件类型指针（FILE\*），当读写文件时，会再内存中申请一块空间作为文件信息区，其本质是一个结构体 FILE 类型的变量（不同编译器的 FILE 成员不同，程序员不需要关心），文件指针用来指向这一块区域，进行读写操作。

```
#include<stdio.h>
#include<stdlib.h>

int main() {
    /* 参数
     * 文件路径，绝对路径/相对路径均可，这里用相对路径
     * 打开方式，r 位去读，w 位写入，wb 为二进制写入等等
     */ /
    // 开失败时（如读取文件时文件不存在），返回空指针，写入文件时如果文件不存在会新建文件
    FILE* pf = fopen("test.txt", "r");
     if (pf == NULL)  return 0;

     /* 顺序读写函数
      * fgetc、fputc，读写单个字符
      * fgets，fputs，读写一行，fgets 换行符也会读取，fputs 会自带一个换行符
      * fscanf，fprintf，格式化读写
      * frerad，fwrite，二进制方式进行读写
      */
     fgetc(pf);

     /* 流
      * 读取文件的指针叫文件输入流，文件写入的指针叫文件输出流
      * 在没有 fopen 时，程序默认的标准输入流（键盘，stdin）和标准输出流（屏幕，stdout）
      * 如果没有使用 fopen 打开文件，那么上面的读写函数都可以操作标准输入输出
      */
     // char c = fgets(stdin);  // 等价于 getchar()

     /* 随机读写，可以从文件任意位置进行读写
      * fseek ，从某个偏移量开始读写
      * ftell ，判断文件指针当前偏移量
      * rewind ， 文件指针回到起始位置
      */

     /* 文件结束
      * 每EOF ,一个标识符常量，值为 -1 ，每个文件最后面都有一个 EOF
      * feof，当文件已经结束时，判断结束原因
      * feetc 判断当前读取字符是否是文件字符总数，判断是否结束
      */

     // 关闭文件
     fclose(pf);
     free(pf);

    return 0;
}
```

### 5.3 程序环境

（1）翻译环境

程序从存储代码的源文件到存储可执行的二进制机器指令的可执行文件所依赖的环境。

* 编译阶段：每一个源文件都会单独作为一个单元被编译器进行处理，生成各自的目标文件（.obj），编译有三个过程
  
  * 预编译：处理头文件、预定义替换、删除注释（用空格替换）等，生成 .i 文件
  
  * 编译：将 .i 文件编译成汇编代码 .s 文件
  
  * 汇编：将 .s 文件汇编成二进制指令 .obj 文件

* 链接阶段：链接器将各个目标文件处理后生成一个单独完整的可执行文件，链接过程中也会把程序用到的 C 标准库函数（在链接库 .lib 文件中）和程序员自己的程序库中用到的函数链接在可执行文件中

（2）执行环境

* 执行程序后，操作系统将程序加载如内存中，如果没有操作系统就需要手动载入（如单片机），然后开始执行

* 程序使用一个运行时堆栈和静态内，从 main 开始执行，并为变量和函数分配空间

* 在堆区分配动态分配的内存

* 正常终止或意外终止程序

### 5.4 预处理

也叫预编译。

（1）预定义符号

```
#include<stdio.h>

int main() {
    printf("文件名：%s\n", __FILE__);
    printf("当前在代码第 %d 行\n", __LINE__);
    printf("日期：%s\n", __DATE__);
    printf("时间：%s\n", __TIME__);
    printf("当前在 %s 函数中\n", __FUNCTION__);
    // printf("%d", __STDC__);  // 部分编译器不支持，比如 VS
    return 0;
}
```

命令行定义：

可以通过命令行传参的方式定义预定义符号：

```
gcc 123.c -D SZ=10

// .c 文件中
printf("没有定义 SZ 也可以使用，SZ = %d\n", SZ);
```

（2）预处理指令

这里只记录最常用的预处理指令。

① \#define

\#define 用来声明标识符常量，不过因为是完全替换，最好不要加分号，否则肯呢个在替换时会拆分语句。

此外，\#define 还可以用于宏定义：

* \#define 支持参数，左括号要与名字相连

* 由于参数是完全替换，为了防止打乱运算符优先级，最好加上括号

```
#include<stdio.h>

/* 宏的匹配规则
 * 声明或者使用宏的时候，如果其中有其他 #define 的标识符和宏，也会替换
 * 参数也可以是 #define 定义的标识符和宏，但注意不能递归'
 * 声明宏的字符串中，以及程序中的字符串如果遇到了和宏一样的字符子串，是不会替换的
 */
#define CALC(x, y) ((x) * (y))

int main() {
    // 48 ，如果宏不加括号，就会替换成 5 + 7 * 4 = 140
    printf("%d", CALC(5 + 7, 4));
    return 0;

}
```

宏和函数的优缺点：

* 宏不需要调用，只是替换，而函数需要调用并占用一定的开销

* 宏是完全替换，因此可以传入一些函数无法传入的参数，不如类型

* 宏如果比较复杂，且使用的多，在代码中就会替换很多重复的复杂功能，代码体积变大，而函数的函数体只需要一个

* 宏因为是完全替换，所以参数没有类型；为了保护运算符优先级，有需要大量的括号，可读性查；宏不方便调试

② \# 和 \#\# ：

丰富宏的功能。

```
#include<stdio.h>

#define PRINT(c) printf("The value of"#c" is %d\n", c)
#define CONCAT(x, y) x##y

// 宏参数需要注意副作用参数，如 ++ -- 作为参数就是副作用参数，是完全替换，而不像函数是把值传入函数体
#define MY_MAX(a, b) (((a) > (b)) ? (a) : (b))
int myMax(int a, int b) {
    return a > b ? a : b;
}

int main() {
    // # ，#c 会替换成 "c"
    // printf 这种用法会自动连接字符串
    printf("hello""world\n");
    // 如果用函数实现，就需要传入两个参数
    int a = 5, b = 7;
    PRINT(a);
    PRINT(b);

    // ## ，可喜的是宏参数完全替换，用不了变量
    int num12 = 12, num15 = 15;
    printf("%d\n", CONCAT(num, 12));

    printf("%d\n", CONCAT(num, 15));

    // # 需要注意副作用参数，否则会出现以外的结果
    int n1 = 10, n2 = 11;
    int n3 = 10, n4 = 11;
    // 11 11 12
    printf("%d %d %d \n", myMax(n1++, n2++), n1, n2);
    // 12 11 13
    printf("%d %d %d \n", MY_MAX(n3++, n4++), n3, n4);

    return 0;

}
```

③ 条件编译

可以啊按照某种条件选择编译哪一块代码。

```
#include<stdio.h>

#define TEST 123

int main() {
    // 如果定义了 TEST 就编译，等价于 #if define(TEST)
    #ifdef TEST
        printf("123\n");
    #endif

    // 如果没有定义 TEST ，就编译，等价于 #if !define(TEST)
    #ifndef TEST
        printf("456\n");
    #endif

    // 只能用常量表达式
    #if 1
        printf("789\n");
    #endif

    // 多分支
    #if 1
        printf("1\n");
    #elif 13 == 1 + 1
        printf("0");
    #else
        printf("-1");
    #endif

    // 嵌套
    #if 1
        #if 1
            printf("888");
        #endif
    #endif

    return 0;
}
```

④  \#include

当需要用到库函数或者自己头文件中的函数，就需要引入头文件：

- #include<xxx.h> 从标准库中查找头文件

- #include"my.h" ，先从自己的工程目录中找，再去标注库中找，所以引入自己的头文件必须用双引号

引入标准库的头文件也可以用双引号，但不推荐，原因是：

- 引入标准库头文件用尖括号，引入自己头文件用双引号，这样可读性更高

- 减少编译时间，因为角括号会直接从标准库中找，不会从自己工程项目中找

工程化的项目中，一个功能模块在头文件 .h 中惊醒函数声明，在源文件 .c 进行函数定义，这样头文件就能大概知道有什么功能，具体实现再去源文件看：

```
// 工程中头文件新建 computed.h
#pragma once
int add(int, int);
```

```
// 工程中源文件新建 computed.c
int add(int a, int b){
    return a + b;
}
```

```
#include<stdio.h>
#include "computed.h"   // 引入自定义头文件要用双引号

int main() {
    printf("%d", add(5, 7));
    return 0;
}
```

关于 \#pragma once ：

在项目中，不同的文件可能会多次引入同一个头文件，而头文件引入时直接把头文件的内容拷贝过来，如果多次拷贝相同的内容，就既没有必要性能也变低。因此 #pragma once 就限制不管引入了多少次该头文件，就只会引入一次。

\#pragma once 其实是C语言预定义的简写：

如果没有定义...就定义它

```
#ifndef __COMPUTED_H__
#define __COMPUTED_H__

int add(int, int);

#endif
```

# 二、C++ 面向对象

## 1 C++ 基础

C++ 乡下箭筒全部 C 语法，这里记录与 C 语法的一些不同。

（1）输入输出和布尔值

```
#include<iostream>
using namespace std;

int main() {
    int a;

    // 输入
    cin >> a;

    // 输出，endl 是换行
    cout << a << endl;

    // cout 浮点数时，只有真正的小数才会输出小数位，比如 5.0 只输出 5 
    // 小数位有几位就输出几位，最多输出 5 个小数位
    float f1 = 5, f2 = 5.0, f3 = 5.5;
    float d1 = 5, d2 = 5.0, d3 = 5.5;
    // 5 5 5.5
    cout << f1 << " " << f2 << " " << f3 << endl;
    // 5 5 5.5
    cout << d1 << " " << d2 << " " << d3 << endl;

    // 新增了布尔值的数据类型，占 1 个字节，true 值为 1 ，false 值为 0
    bool t = true, f = false;
    // 1 0
    cout << t << " " << f << endl;

    // true，false 能作为字面常量
    while (false) {}

    return 0;
}
```

（2）引用

引用是变量的别名，本质是一个指针常量，引用可以简化指针的操作。

```
#include<iostream>
using namespace std;

int main() {
    int a = 10, b = 5;

    /* 引用是变量的别名
     * 引用的类型必须和变量一样
     * 引用必须初始化，且不能再作为其他变量的引用
     * 引用的本质是一个指针常量，下面的代码编译器会处理成 int* const r = &a;
     */
    int& r = a;

    // 编译器会处理为 *r = 20;
    r = 20;  // a = 20; 也一样，因为是同一个内存空间
    // 20 20
    cout << r << " " << a << endl;

    // 这样不是修改引用的变量变成  ，而是把 c 的值赋给引用 r ，是合法的
    r = b;
    b = 12;
    // 5 5 12
    cout << r << " " << a << " " << b << endl;

    // 引用不能直接复制常量，但是加了 const 就可以，相当于 const int* const
    // const 引用也可以接受非 cosnt 和 const 的变量
    int c = 10;
    const int d = 20;
    const int& e1 = c;
    const int& e2 = d;
    const int& e3 = 30;
    // 10 20 30
    cout << e1 << " " << e2 << " " << e3 << endl;;

    // 将引用赋值给另一个引用，相当于起了两个别名
    // 注意引用没有多级的概念，没有 &&
    int f = 0;
    int &g = f;
    int &h = g;

    return 0;
}
```

函数参数的引用传递：

相当于简化后的址传递。

```
#include<iostream>
using namespace std;

// 若果要防止被修改，可以加上 const，变成 const int &a
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int a = 5, b = 7;
    swap(a, b);
    // 7 5
    cout << a << " " << b << endl;

    return 0;
}
```

函数返回类型为引用：

```
#include<iostream>
using namespace std;

int& func() {
    // 如果不用 static 的话，a 在函数调用完就释放了，相当于野指针
    static int a = 10;
    return a;
}

int main() {
    int &r1 = func(), &r2 = func();
    // 10 10
    cout << r1 << " " << r2 << endl;
    r1 = 20;
    // 20 20
    cout << r1 << " " << r2 << endl;

    // 当返回类型是引用时，该函数就可以作为表达式的左值
    func() = 30;
    // 30 30
    cout << r1 << " " << r2 << endl;

    return 0;
}
```

（3）new 和 delete

新增的动分配和释放内存的方式：

```
#include<iostream>
using namespace std;

int main() {
    // new 一个整型
    int *a = new int(5);
    // 5 4
    cout << *a << " " << sizeof(*a) << endl;;

    // new 一个数组
    int *arr = new int[10];
    arr[0] = 10;
    cout << arr[0] << endl;

    // delete 释放内存
    delete a;
    delete[] arr;

    return 0;
}
```

（4）函数新特性

参数默认值：

```
#include<iostream>
using namespace std;

void func(int a = 10) {
    cout << a << endl;
}

int main() {
    // 如果不传参数，就是用默认值
    func();
    // 传了参数就是用传入的
    func(20);
    return 0;
}
```

占位参数：

```
#include<iostream>
using namespace std;

// 占位参数也可以有默认值，如 int = 10
// 占位参数位置可以随意，如 int, int a
void func(int a, int) {
    cout << a << endl;
}

int main() {
    // 占位参数同样需要传参
    func(10, 20);
    return 0;
}
```

函数重载：

在同一个作用域中，相同返函数名的函数可以有多个，条件是：

* 返回类型必须相同

* 形参的类型、个数、顺序不同

```
#include<iostream>
using namespace std;

// 测试 1
void func() {
    cout << "五参数" << endl;
}
void func(int a) {
    cout << "一个整型参数" << endl;
}

// 测试 2
void func(double a) {
    cout << "一个 double 参数" << endl;
}
void func(double a, double b = 10) {
    cout << "有默认参数需要注意" << endl;
}

// 测试 3 
// 传值的话普通类型和 const 修饰的不能重载，但是传址和传引用就可以
void func(char &a) {
    cout << "一个 char 参数" << endl;
}
void func(const char &a) {
    cout << "一个 const char 参数" << endl;
}

// 测试 4
// 这样只是参数名顺序不同，无法重载，因为编译器无法分辨
void func(float a,float b) {}
// void func(float b, float a) {}
// 这样才是顺序不同
void func(int a, double b) {
    cout << "int double" << endl;
}
void func(double a, int b) {
    cout << "double int" << endl;
}

int main() {
    // 编译器根据调用传入的实参判断要调用哪个函数
    func();
    func(10);

    // 如果参数有默认值需要注意，这里必须传入链 2 个参数，因为只传 1 个的话编译器不知道要调用哪一个函数
    func(10.2, 20.4);

    // const 引用只能传字面常量，或者 const 修饰的变量
    char c1 = 'a';
    const char c2 = 'b';
    func(c1);
    func(c2);
    func('c');  // 如果这里是传址，用字面常量的地址会变成整型，浮点型等，所以不能像传引用一样这么用

    func(5, 3.14);
    func(3.14, 5);

    return 0;
}
```

引用参数重载时也要注意：

```
#include<iostream>
using namespace std;

void func(int a) {}
void func(int &a) {}

int main() {
    int num = 5;
    // 不知道调用哪个函数
    // func(num);

    int &n = num;
    // 这样也不行
    // func(n);

    return 0;
}
```

## 2 类和对象

### 2.1 基本使用

（1）基础

类是一个事物的抽象结构，内部的成员有属性和方法。属性又叫成员变量/成员属性，方法又叫行为/成员函数/成员方法。

类乐意实例化出一个个具体的对象。

```
#include<iostream>
using namespace std;

class LinkList {
    public:
        int date1;
        int date2 = 10;  // 可以有默认值
        int getDate() {
            return date1;
        }
};

int main() {
    // 类实例化一个对象
    LinkList  list;
    list.date1 = 5;
    cout << "date1 is " << list.getDate() << ", date2 is " << list.date2 << endl;
    return 0;
}
```

（2）构造函数、析构函数

也叫构造器和析构器，用来做初始化和清理的操作。

* 在实例化对象的时候会自动调用构造函数，在对象释放前会自动调用析构函数，自己无需调用也无法调用。

* 默认情况下构造函数和析构函数都是空参数空实现，没有什么功能

规则：

* 必须在 public 内

* 没有返回值也无法写返回类型

* 构造函数名为类名，析构函数名为 \~类名

* 构造函数可以有形参可以重载，析构函数不能有形参不能重载

```
#include<iostream>
using namespace std;

class LinkList {
    public:
        LinkList() {
            cout << "对象实例化完成" << endl;
        }

        ~LinkList() {
            cout << "对象即将被释放" << endl;
        }
};

void test() {
    LinkList list;
}

int main() {
    test();
    return 0;
}
```

拷贝构造函数和三种实例化方式：

默认情况下，还会有一个拷贝构造函数，参数为 const 引用，且实现了拷贝所有属性：

* 当自定义了靠北构造函数，编译器就不再提供默认的拷贝构造函数和空参数构造函数

* 自定义了有参构造函数，编译器就不再提供默认的空参数构造函数

```
#include<iostream>
using namespace std;

class LinkList {
public:
    int date;

    LinkList() {

    }

    LinkList(int n) {
        date = n;
    }

    // 拷贝构造函数
    LinkList(const LinkList& list) {
        date = list.date;
        cout << "拷贝" << endl;
    }

    ~LinkList() {
        cout << "销毁" << endl;
    }
};

int main() {
    // 调用无参构造函数，注意不能用 list()  ，因为编译器会认为是函数声明
    LinkList list;

    // 调用有参构造函数
    LinkList list1(10);
    LinkList list11 = LinkList(11);
    LinkList list111 = 111;  // 等价于 LinkList list111 = LinkList(111)

    // 匿名对象，执行完这一行就立刻销毁
    LinkList(11);
    cout << "匿名对象已销毁，析构函数已调用完" << endl;

    // 都是调用拷贝构造函数，此外，函数形参是类，或者返回值是类也会调用拷贝构造函数
    LinkList list2 = list1, list3 = LinkList(list1);
    cout << list1.date << " " << list2.date << " " << list3.date << endl;

    // 不能用拷贝构造函数声明匿名对象
    // LinkList(list1);  // 编译器会认为是 LinkList list1 = LinkList();  即重定义了

    return 0;
}
```

初始化列表：

可以简化构造函数的视线：

```
class LinkList {
    public:
        int date1, date2;

        // 无参，等价于函数体内实现 dtae1 = 10; date2 = 20;
        LinkList(): date1(10), date2(20) {}

        // 有参
        LinkList(int a, int b) : date1(a), date2(b) {}
};
```

（3）成员属性也可以是另一个类

```
#include<iostream>
using namespace std;

class A {
    public:
        int a;

        A() {
            cout << 123 << endl;
        }

        A(int n) {
            a = n;
            cout << "A 构造函数" << endl;
        }

        ~A() {
            cout << "A 析构函数" << endl;
        }
};

class LinkList {
    public:
        A aaa;

        // 注意，aaa = n 等价于 aaa = A(n)
        LinkList(int n): aaa(n) {
            cout << "LinkList 构造函数" << endl;
        }

        ~LinkList() {
            cout << "LinkList 析构函数" << endl;
        }
};

int main() {
    LinkList list(10);
    return 0;
}
```

构造函数和析构函数的执行顺序：

* 调用外部类的构造函数时，会先调用内部类的构造函数，所以顺序是 内部 - 外部，如果外部类构造函数对内部类的赋值操作不是用初始化列表实现的，就会先调用内部类的空参数构造函数：
  
  ```
  // 顺序：内部类空参数构造函数 - 外部类拷贝构造函数 - 内部类构造函数
  LinkList(int n){
      cout << "LinkList 构造函数" << endl;
      aaa = n;
  }
  ```

* 析构函数顺序：外部 - 内部

（4）深拷贝与浅拷贝

实例化对象和它的成员都是在栈区，对象直接赋值给对象就是浅拷贝，两个对象是1栈区的两个两个不同内存空间：

```
#include<iostream>
using namespace std;

class LinkList {
    public:
        int date = 10;
};

int main() {
    LinkList list1;
    LinkList list2 = list1;
    list2.date = 20;
    // 10 20
    cout << list1.date << " " << list2.date << endl;
    return 0;
}
```

因此当函数形参是类时，和结构体一样可以传址传引用来防止多拷贝一份对象，提高性能：

```
#include<iostream>
using namespace std;

class LinkList {
    public:
        int date = 10;
};

void func1(LinkList &list) {
    cout << list.date << endl;
}

void func2(LinkList *list) {
    cout << list->date << endl;
}

int main() {
    LinkList list;
    func1(list);
    func2(&list);
    return 0;
}
```

而深拷贝是指一并拷贝推区中的数据。如果成员属性有动态分配内存，拷贝构造函数又不做深拷贝处理，会出问题的：

```
#include<iostream>
using namespace std;

class LinkList {
    public:
        int* date;

        LinkList() {
            date = new int(10);
        }

        LinkList(const LinkList& list) {
            /* 默认实现
             * 只拷贝了地址但未靠北堆内存数据，两个对象指向的是同一个堆内存空间，修改其中一个对象的属性会同步到另一个对象
             * 此外还会出现一个问题，当释放的时候，list2 先出栈 delete ，后面的 list1 出栈再次 delete 就出错了，delete 不能重复测试房同一个内存空间
             */ 
            // date = list.date;

            // 正确实现深拷贝
            date = new int(*list.date);
        }

        ~LinkList() {
            if(date != NULL) {
                delete date;
                date = NULL;
            }
        }
};

int main() {
    LinkList list1;
    LinkList list2 = list1;
    return 0;
}
```

（5）new 实例化对象

new 实例化的对象存储在堆区中：

```
#include<iostream>
using namespace std;

class LinkList {
    public:
        int date;

        LinkList() {
            cout << "无参" << endl;
        }

        LinkList(int n) {
            date = n;
            cout << "有参" << endl;
        }

        LinkList(const LinkList& list) {
            date = list.date;
            cout << "拷贝" << endl;
        }

        ~LinkList() {
            cout << "销毁" << endl;
        }
};

int main() {
    // 无参构造函数
    LinkList *l1 = new LinkList;
    LinkList *l2 = new LinkList();

    // 有参构造函数
    LinkList *l3 = new LinkList(5);

    // 注意 new 没有这种简化的实例化方式
    // LinkList *l = 5;

    // 匿名对象
    new LinkList();
    cout << "匿名对象穿管完后就销毁" << endl;

    //深拷贝
    LinkList *l4 = new LinkList(*l3);
    l4->date = 20;
    // 20 5
    cout << l4->date << " " << l3->date << endl;

    // 浅拷贝，也不会调用构造函数
    LinkList *l5 = l3;
    l5->date = 30;
    // 30 30
    cout << l5->date << " " << l3->date << endl;

    // 销毁
    delete l1;
    delete l2;
    delete l3;
    delete l4;
    // 浅拷贝的不要重复 delete
    // delete l5;

    return 0;
}
```

（6）static 静态成员

特点：

* 在编译阶段就存放于内存的静态区，所有该类实例化的对象共享同一份，是独属于类本身的，类可以直接调用静态属性和静态方法

* 静态属性、静态方法都受访问权限控制

* 静态属性需要类内声明，类外初始化；静态方法直接实现即可

* 静态方法只能访问静态属性，因为静态方法只有一份，调用非静态属性的话不知道调用的是哪一个对象；非静态方法可以访问静态属性

```
#include<iostream>
using namespace std;

class LinkList {
    public:
        static int date;
        static int getDate() {
            return date;
        }
};

// 类外初始化静态属性
int LinkList::date = 10;

int main() {
    LinkList list;
    list.date = 20;
    cout << list.getDate() << endl;

    // 类直接访问
    LinkList::date = 30;
    cout << list.getDate() << endl;

    return 0;
}
```

（7）类声明

可以先声明再定义：

```
#include<iostream>
using namespace std;

// 类声明
class LinkList;

// 声明类的成员函数
class LinkList {
public:
    int date;
    LinkList();
    ~LinkList();
    int getDate();
};

// 实现函数，要加上类的作用域
LinkList::LinkList(){
    cout << "构造" << endl;
}

LinkList::~LinkList(){
    cout << "析构" << endl;
}

int LinkList::getDate(){
    return date;
}

int main() {
    LinkList list;
    return 0;
}
```

（8）class 和 struct 的区别

C++ 中结构体的功能得到了提升，基本和 class 一样了：

```
#include<iostream>
using namespace std;

class LinkList {
public:
    int date;
    int getDate() {
        return date;
    }
};

int main() {
    struct LinkList  list;
    list.date = 5;
    cout << "date is " << list.getDate() << endl;

    return 0;
}
```

唯一的区别在于 struct 默认是 public ，class 默认是 private 。

### 2.2 this 指针

（1）C++ 对象模型

对象只存放非静态属性，方法存放于其他地方，同一个类的所有对象共享同一份方法，方法通过 this 指针区分是哪一个对象调用了自己，静态属性和静态方法存放于静态区中。

空对象用 1 个字节来区分是哪一个个空对象，不是空对象就不需要这 1 个字节。

```
#include<iostream>
using namespace std;

class A {

};

class B {
    char a;
    int b;
};

class C {
    static int a;
};

class D {
    int date1;
    static int date2;
};

class E {
    void func1(){}
    static void func2(){}
};

int main() {
    A a;
    B b;
    C c;
    D d;
    E e;

    // 1 1 ，用一个字节来区分每个空对象
    cout << sizeof(A) << " " << sizeof(a) << endl;

     // 8 8 ，和结构体一样时内存对齐
    cout << sizeof(B) << " " << sizeof(b) << endl;

    // 1 1，静态属性存放于静态区
    cout << sizeof(C) << " " << sizeof(c) << endl;

    // 4 4 ，不是空对象就不用 1 字节区分空对象
    cout << sizeof(D) << " " << sizeof(d) << endl;

    // 1 1 ，函数不存放于对象中
    cout << sizeof(E) << " " << sizeof(e) << endl;

    return 0;
}
```

（2）this 

成员函数（包括构造函数、析构函数）内部都有一个默认定义的 this 指针，指向调用这个函数的对象。

this 指针本质是一个指针常量。

```
#include<iostream>
using namespace std;

class Person {
    public:
        int age;
        double height;

        Person(int a,double height) {
            // 默认加上 this ，变成 this.age
            age = a;

            // 但是如果属性名和参数名相同，就不会自动加上 this
            // height = height;
            // 手动加上
            this->height = height;
        }

        // 返回 this 指向的对象，就可以链式调用了
        Person& addAge() {
            age += 10;
            return *this;
        }
};

int main() {
    Person p(18, 178.5);
    p.addAge().addAge();
    // 38
    cout << p.age << endl;
    return 0;
}
```

由于成员函数不是存放于对象中，成员函数是通过 this 区分对象的，所以空指针可以直接调用成员函数，但是因为 NULL 的地址不是对象，会出错：

```
#include<iostream>
using namespace std;

class Person {
    public:
        int date;
        int getDate() {
            // 当空指针调用时会出错，所以需要加一个判断
            if (this == NULL)  return 0;
            return date;
        }
};

int main() {
    Person *p = NULL;
    cout << p->getDate() << endl;
    return 0;
}
```

（3）常函数和常对象

常函数：

用 const 修饰成员函数，使 this 变成常量指针常量，作用是湿的成员函数内无法修改属性，不过属性可以通过 mutable 修饰来摆脱这个限制：

```
#include<iostream>
using namespace std;

class LinkList {
    public:
        int date1;
        // 如果是静态属性，statuc 要放在 mutable 前面
        mutable int date2;

        // 常函数
        void setDate(int date) const {
            // 无法修改
            // date1 = date;
            // 可以修改
            date2 = date;
        }
};

int main() {
    LinkList list;
    list.setDate(10);
    cout << list.date2 << endl;
    return 0;
}
```

常对象：

无法修改除 mutable 的属性，也只能调用常函数（不然调用普通函数修改了属性就破坏规则了）：

```
int main() {
    const LinkList list;
    // 无法修改
    // list.date1 = 20;
    list.setDate(10);
    cout << list.date2 << endl;
    return 0;
}
```

### 2.3 三大特性

面向对象三大特性：封装、继承、多态。

#### 2.3.1 封装

将一个事物的属性和方法封装成一个类，并设置访问权限，为私有属性提供公共的 get 。set 方法来访问和修改私有属性。

（1）访问权限

- public：公共权限，类内外均可以调用

- protected：保护权限，类外不可调用，子类和雷内可以调用

- private：私有权限，类外和子类不可调用，雷内可以调用

```
#include<iostream>
using namespace std;

class LinkList {
    // 默认是 private
    int test = 1;

    private:
        int date;

    protected:
        int dateProtected = 2;

    public:
        void setDate(int value) {
            date = value;
        }

        int getDate() {
            return date;
        }
};

int main() {
    // 类实例化一个对象
    LinkList  list;
    list.setDate(123);
    cout << list.getDate() << endl;
    return 0;
}
```

（2）友元

设置了友元就可以让别人放在自己的 private 属性：

```
#include<iostream>
using namespace std;

// 需要先声明
class LinkList;
class A;
class B {
public:
    void getDate(LinkList);
};

class LinkList {
    // 友元全局函数
    friend void getDate(LinkList);

    // 友元类，类中都可以访问
    friend A;

    // 友元成员函数，只有该成员函数可以访问
    friend void B::getDate(LinkList);

    private:
        int date = 10;
};

void getDate(LinkList list) {
    cout << list.date << endl;
}

class A {
public:
    void getDate(LinkList list) {
        cout << list.date << endl;
    }
};

void B::getDate(LinkList list) {
    cout << list.date << endl;
}

int main() {
    LinkList list;
    A a;
    B b;
    getDate(list);
    a.getDate(list);
    b.getDate(list);
    return 0;
}
```

#### 2.3.2 继承

（1）基本使用

```
#include<iostream>
using namespace std;

// 父类，也叫基类
class A {
private:
    int a;
protected:
    int b;
public:
    int c;
    A() {
        cout << "父类构造函数" << endl;
    }
    ~A() {
        cout << "父类析构函数" << endl;
    }
};

// 子类，也叫派生类
// 三种继承方式都无法访问父类的 private 成员
// 公共继承，public 和 protected 保持原样
class B : public A {
public:
    B() {
        cout << "子类构造" << endl;
    }
    ~B() {
        cout << "子类析构" << endl;
    }
};

// 保护继承，public 和 protected 成员都变成 protected
class C : protected A {};
// 私有继承，public 和 protected 成员都变成 private
class D : private A {};
// 默认是私有继承
class E : A {};

int main() {
    // 12 12 12 12，继承的对象模型是子类中有父类的所有成员包括 private 成员，只是无法访问
    cout << sizeof(A) << " " << sizeof(B) << " " << sizeof(C) << " " << sizeof(D) << endl;

    // 构造/析构顺序：父构造-子够奥-子析构-父析构
    B b;

    return 0;
}
```

（2）同名成员的处理

```
#include<iostream>
using namespace std;

class A {
public:
    int a = 5;
    static int b;
    void func1() {
        cout << "父类 func" << endl;
    }
    static void func2() {
        cout << "父类 static func" << endl;
    }
};
int A::b = 10;

class B : public A {
public:
    int a = 50;
    static int b;
    void func1() {
        cout << "子类 func" << endl;
    }
    static void func2() {
        cout << "子类 static func" << endl;
    }
};
int B::b = 100;

int main() {
    // 4 8 ，子类多存储一份同名成员
    cout << sizeof(A) << " " << sizeof(B) << endl;

    B b;
    // 子类调用子类中的同名成员
    cout << b.a << " " << b.b << " " << B::b << endl;
    b.func1();
    b.func2();
    B::func2();

    // 子类调用父类中的同名属性
    cout << b.A::a << " " << b.A::b << " " << B::A::b << endl;
    b.A::func1();
    b.A::func2();
    B::A::func2();

    return 0;
}
```

重写：

当子类中有父类中的同名函数时，叫做重写，重写即把父类中返回类型、函数名、形参列表都相同的函数的函数体重新定义成子类的函数。

注意：

* 一旦子类中出现了返回类型和函数名相同，但是形参列表不同的函数，子类中集成下来的返回类型、函数名、形参列表都相同的函数就没有了。

* 父类和子类重写的函数的重载是分开的，父类只重载父类的函数，子类只重载子类的函数。

* 构造/析构函数无法继承，但子类写构造/析构函数时，相当于重写，要求父类中也要存在自定义的或默认存在的同样形参列表的构造/析构函数

（3）多继承

```
#include<iostream>
using namespace std;

class A {
public:
    int a, date;
    A() {
        cout << "父类 A 构造" << endl;
    }
    ~A() {
        cout << "父类 A 析构" << endl;
    }
};

class B {
public:
    int b, date;
    B() {
        cout << "父类 B 构造" << endl;
    }
    ~B() {
        cout << "父类 B 析构" << endl;
    }
};

class C : public A, public B {
public:
    int c, date;
    C() {
        cout << "子类 C 构造" << endl;
    }
    ~C() {
        cout << "子类 C 析构" << endl;
    }
};



int main() {
    // 24 ， 来源不同父类的同名属性各存一份
    cout << sizeof(A) << " " << sizeof(C) << endl;

    // 构造/析构顺序：第一个父类构造 - 第二个父类构造 - 子类构造 - 子类析构 - 第二个父类析构 - 第一个父类析构
    C c;

    return 02;
}
```

（4）菱形继承

B、C 类各自集成于 A 类，D 多继承于 B 和 C 类、形状类似菱形和钻石，也叫钻石继承。

```
#include<iostream>
using namespace std;

class A {
public:
    int date = 10;
};

class B : public A {};
class C : public A {};
class D : public B, public C {};


int main() {
    // 8 ，因为 date 从 B、C 各继承了一份
    cout << sizeof(D) << endl;

    // 必须指定作用域才能访问
    D d;
    cout << d.B::date << " " << d.C::date << " " << d.A::date << endl;
    cout << d.B::A::date << " " << d.C::A::date << endl;
    // 无法访问，因为不明确是哪里的 date
    // cout << d.date << endl;

    return 02;
}
```

菱形继承会有一个问题，即会重复继承相同的成员，造成了冗余。可以使用虚继承解决，虚继承只保留一份数据，通过 vbptr 指针访访问：

```
#include<iostream>
using namespace std;

// A 变成了虚基类
class A {
public:
    int date = 10;
};

class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};


int main() {
    // 这里使用虚继承后占用的字节数更大了，是因为这是只有一个成员，当相同的成员很多时，就会大大减少占用的字节
    // 4 
    cout << sizeof(A) << endl;
    // 16 16
    cout << sizeof(B) << " " << sizeof(C) << endl;
    // 24
    cout << sizeof(D) << endl;

    /* 可以直接访问
     * B、C 中都有个虚基类指针（vbptr，virtual base pointer）指向各自的虚基类表（vbtable，virtual base table）
     * 细积累表存储的内容是到虚基类的偏移量
     */
    D d;
    cout << d.date << endl;

    return 02;
}
```

#### 2.3.3 多态

（1）基本使用

即多重形态，分为：

* 静态多台：函数重载、运算符重载。静态多态的函数是早绑定的，即在编译阶段就确定了函数地址

* 动态多台：通过派生类和重写虚函数实现，即需要继承。动态多态的函数是晚绑定的，函数地址在运行时才会确定

这里说的多台都是动态多态。

动态多态的条件：

* 子类继承父类

* 父类有一个虚函数，子类重写这个虚函数

* 父类的指针或引用指向子类，如把子类对象或子类对象地址通过形参、返回值或直接赋值给父类引用或父类指针

```
#include<iostream>
using namespace std;

// 未使用多台的情况 ------------------------------------------------------
class A {
public:
    void func() {
        cout << "父类 func" << endl;
    }
};

class B : public A {
public:
    void func() {
        cout << "子类 func" << endl;
    }
};
// -----------------------------------------------------------------------------

// 动态多态 --------------------------------------------------------------------
class AA {
public:
    // 定义成一个虚函数
    virtual void func() {
        cout << "父类 func" << endl;
    }
};

class BB : public AA {
public:
    // 重写父类虚函数，virtual 可写可不写
    void func() {
        cout << "子类 func" << endl;
    }
};
// -----------------------------------------------------------------------------

int main() {
    // 未使用多态，调用的都是 A 的 func
    B b;
    A a1 = b, & a2 = b, * a3 = new B;
    a1.func();
    a2.func();
    (*a3).func();

    // 使用动态多态后，调用的就是对应对象的 func
    BB bb;
    AA aa1 = bb, & aa2 = bb, * aa3 = new BB;
    aa1.func();  // 注意，多态的条件是父类的指针或引向子类，这里是值传递，所以不是多态，调用的是父类 func
    aa2.func();
    (*aa3).func();

    // 父类的也虚函数可以调用，不影响
    AA aa;
    aa.func();
    aa2.AA::func();

    delete(a3);
    delete(aa3);
    a3 = NULL;
    aa3 = NULL;

    return 0;
}
```

动态多台可以很方便的视线开闭原则，即对于功能只开放扩展，关闭修改，这样有利于后期的维护，如：

```
#include<iostream>
using namespace std;

// 未使用多台的情况 ------------------------------------------------------
class Calc1 {
public:
    int date1;
    int date2;

    Calc1(int date1, int date2) {
        this->date1 = date1;
        this->date2 = date2;
    }

    int calc(char opt) {
        switch (opt) {
        case '+':
            return date1 + date2;
        case '-':
            return date1 - date2;
        default:
            return 0;
        }
    }
};
// -----------------------------------------------------------------------------

// 动态多态 --------------------------------------------------------------------
// 虽然会增加一些代码量，但是扩展功能时不需要修改源代码
class Calc2 {
public:
    int date1;
    int date2;

    Calc2() {}

    Calc2(int date1, int date2) {
        this->date1 = date1;
        this->date2 = date2;
    }

    virtual int calc() {
        return 0;
    }
};

class Add : public Calc2 {
public:
    Add(int date1, int date2) {
        this->date1 = date1;
        this->date2 = date2;
    }

    int calc() {
        return date1 + date2;
    }
};

class Div : public Calc2 {
public:
    Div(int date1, int date2) {
        this->date1 = date1;
        this->date2 = date2;
    }

    int calc() {
        return date1 - date2;
    }
};
// -----------------------------------------------------------------------------

int main() {
    // 未使用多态
    Calc1 obj1(10, 7);
    cout << obj1.calc('+') << " " << obj1.calc('-') << endl;

    // 使用动态多态
    Calc2 *obj2 = new Add(10, 7);
    Calc2 *obj3 = new Div(10, 7);
    cout << obj2->calc() << " " << obj3->calc() << endl;

    delete(obj2);
    delete(obj3);
    obj2 = NULL;
    obj3 = NULL;

    return 0;
}
```

（2）动态多台的本质

当使用动态多态度后，父类和子类都会多处一个虚函数表指针（vfptr，virtual function opinter），指向它们各自维护的一个虚函数表（vftable，virtual function table），虚函数表存放了这个类中所有的虚函数地址。

当子类未重写虚函数时，子类的虚函数表存放的是继承下来的父类虚函数，所以调用时就会调用父类的函数；若子类重写了父类虚函数，那么子类虚函数表中就会用重写的这个函数去覆盖掉父类虚函数，因此就实现了多态。

调用时，通过 vfptr 寻找到对应的函数并调用，即动态多态中的函数地址晚绑定。

```
#include<iostream>
using namespace std;

class A {
public:
    virtual void func1() {    }
    virtual void func2() {    }
};

class B : public A {
public:
    void func1() {}
    void func2() {}
};

int main() {
    // 4/8 4/8 ，各自存放一个指针 vfptr
    cout << sizeof(A) << " " << sizeof(B) << endl;
    return 0;
}
```

（3）纯虚函数和抽象类

动态多态中，父类的虚函数的函数体一般没必要实现，这时候就可以将其定义为纯虚函数。

当类中只要有一个纯虚函数时，这个类就是抽象类：

* 抽象类无法实例化

* 抽象类的字类必须重写父类的纯虚函数，否则该子类还是一个抽象类，无法实例化

```
#include<iostream>
using namespace std;

// 抽象类
class A {
public:
    // 纯虚函数，在后面加上 = 0 ，和返回类型无关
    virtual void func() = 0;
};

class B : public A {
public:
    void func() {
        cout << "asdf" << endl;
    }
};

int main() {
    A *b = new B;
    b->func();
    delete(b);
    b = NULL;
    return 0;
}
```

（4）虚析构和纯虚析构

动态多态中，如果把子类对象地址赋值给父类指针，释放父类是不会执行子类的析构函数的（如果是子类对象赋值给父类引用则会执行），所以当子类中有动态分配内存的成员时，就需要使用虚析构解决，加上 = 0 就变成纯虚析构。

由于纯虚析构也是纯虚函数，所以有纯虚析构的类也是抽象类，子类也必须重写纯虚析构，否则也还是抽象类：

```
#include<iostream>
using namespace std;

// 抽象类
class A {
public:
    // 虚析构
    // virtual ~A() {};

    // 纯虚泥垢，必须需要类外实现
    virtual ~A() = 0;
};

// 类外实现纯虚析构
A::~A() {};

class B : public A {
public:
    ~B() {
        cout << "子类析构" << endl;
    }
};

int main() {
    A* b = new B;
    delete(b);
    b = NULL;
    return 0;
}
```

### 2.4 运算符重载

可以让运算符有自定义的功能，注意点：

* 可以通过成员函数或全局函数实现，成员函数实现需要再 public 中，全局函数如果操作 private 属性需要设置友元

* 用来实现运算符重载的函数名为 operatore运算符 ，这个函数本身也可以重载

* 对内置数据类型的运算无法重载

* 运算符重载精良和运算符本身意义靠拢，比如 + 就是加

这里只记录几个常用的运算符。

（1）算术运算符重载、关系运算符重载

例如实现两个对象所有相同属性的相加和比较大小：

```
#include<iostream>
using namespace std;

class LinkList {
    // 给全局函数设置友元
    friend bool operator>(LinkList& list1, LinkList& list2);

private:
    int date1;
    int date2;

public:
    LinkList(int date1, int date2) {
        this->date1 = date1;
        this->date2 = date2;
    }

    void coutDate() {
        cout << date1 << " " << date2 << endl;
    }

    // 通过成员函数实现运算符重载
    // 实现后效果是：本对象 + 传入的对象
    LinkList& operator+(LinkList& list) {
        LinkList res(0, 0);
        res.date1 = this->date1 + list.date1;
        res.date2 = this->date2 + list.date2;
        return res;
    }
};

// 通过全局函数重载，效果为：list1 > list2
bool operator>(LinkList& list1, LinkList& list2) {
    return list1.date1 > list2.date1
        ? true
        : list1.date1 == list2.date1
        ? list1.date2 > list2.date2
        : false;
}

int main() {
    LinkList list1(5, 5), list2(10, 10);

    // 等价于 list3.operator+(list1, list2);
    LinkList list3 = list1 + list2;

    // 15 15
    list3.coutDate();

    // 0
    cout << (list1 > list2) << endl;

    return 0;
}
```

（2）左移运算符重载

如输出所有属性：

```
#include<iostream>
using namespace std;

class LinkList {
    // 给全局函数设置友元
    friend ostream& operator<<(ostream &cout, LinkList& list);

private:
    int date1;
    int date2;

public:
    LinkList(int date1, int date2) {
        this->date1 = date1;
        this->date2 = date2;
    }
};

// 通过全局函数重载，效果为：cout << list...
// 如果用成员函数实现的话，只能实现 list... << cout ，所以这里用全局函数实现
// cout 对象全局只允许有一个，所以参数和返回值都是 cout 引用
// 为了实现能够链式调用，即 cout << xxx << cout << xxx ，需要返回 cout 引用
ostream& operator<<(ostream &cout, LinkList& list) {
    cout << list.date1 << " " << list.date2;
    return cout;
}

int main() {
    LinkList list(5, 7);
    // 5 7
    cout << list << endl;
    return 0;
}
```

（3）++ -- 重载

```
#include<iostream>
using namespace std;

class MyInt {
    friend ostream& operator<<(ostream& cout, MyInt mi);

private:
    int date;

public:
    MyInt(int date) {
        this->date = date;
    }

    // 前置 ++ ，为了能够实现练市调用，即 ++(++a) ,需要返回对象本身
    MyInt& operator++() {
        ++this->date;
        return *this;
    }

    // 后置 ++ ，为了能够重载，加了个占位参数，这是 C++ 特意规定的后置 ++ 做法
    // C++ 语法本身后置 ++ 没有链式调用，所以这里返回一个值，而这里也实现不了返回引用，因为返回时一个临时的引用
    MyInt operator++(int) {
        MyInt temp = this->date;
        this->date += 1;
        return temp;

    }
};

// Wiley实现 cout 输出 MyInt ，还需要重载 cout
ostream& operator<<(ostream &cout, MyInt mi) {
    cout << mi.date;
    return cout;
}

int main() {
    MyInt a = 10;
    cout << ++(++a) << endl;  // 12
    cout << a++ << endl;      // 12
    cout << a << endl;        // 13
    return 0;
}
```

（4）赋值运算符重载

编译器除了默认的空参数构造函数、默认的拷贝构造函数，还会给每个类一个默认的赋值运算符重载函数，作用是浅拷贝所有属性。

可以利用赋值运算符重载，实现深拷贝：

```
#include<iostream>
using namespace std;

class LinkList {
private:
    int *date;

public:
    LinkList(int date) {
        this->date = new int(date);
    }

    ~LinkList() {
        if (this->date != NULL) {
            delete this->date;
            this->date = NULL;
        }
    }

    int* getDateAddr() {
        return this->date;
    }

    LinkList& operator=(LinkList &list) {
        if (this->date != NULL) {
            delete this->date;
            this->date = NULL;
            cout << "asdfqqwe" << endl;
        }
        this->date = new int(*list.date);
        return *this;
    }
};

int main() {
    LinkList list1(10);

    // 注意，这里不会调用赋值运算符重载的函数，只会调用拷贝构造函数
    // 如果拷贝构造函数不做深拷贝处理，这行代码会出问题，因为 = 重载函数哪里会 delete 浅拷贝的空间
    // LinkList list2 = list1;

    // 这样才会调用赋值运算符重载的函数，不会调用拷贝构造函数
    LinkList list2(15);
    list2 = list1;
    cout << list1.getDateAddr() << endl;
    cout << list2.getDateAddr() << endl;

    return 0;
}
```

（5）数组访问运算符重载

```
#include<iostream>
using namespace std;

class MyArray {
private:
    int *arr;
    int size;

public:
    MyArray(int size) {
        this->arr = new int[size];
        this->size = size;
    }

    ~MyArray() {
        delete[] arr;
        this->arr = NULL;
    }

    // 返回引用，使得可以作为左值，如 arr[0] = 0
    int& operator[](int index) {
        return this->arr[index];
    }
};

int main() {
    MyArray arr(10);
    arr[0] = 2;
    cout << arr[0] << endl;
    return 0;
}
```

（6）函数调用运算符重载

很灵活，返回类型和参数都不固定，可以做很多功能。

因为使用方式类似函数调用，所以也叫访函数。

```
#include<iostream>
using namespace std;

class LinkList {
public:
    void operator()() {
        cout << "asdf" << endl;
    }
};

int main() {
    LinkList list;
    list();
    // 用匿名对象也可以调用
    LinkList()();
    return 0;
}
```

### 2.5 工程化

```
// linklist.h

#pragma once

class LinkList {
    public:
        int date;
        int getDate();
};
```

```
// linklist.cpp
// 需要引入头文件
#include"linklist.h"

// :: 用来指定这个函数实现是哪一个类的
int LinkList::getDate() {
    return date;
}
```

```
#include<iostream>
#include"linklist.h"
using namespace std;

int main() {
    LinkList list;
    return 0;
}
```

## 3 文件操作

```
#include<iostream>
#include<fstream>
using namespace std;

int main() {
    /* 文件流对象
     * ofstream ，文件输出流，写入文件
     * ifstream ，文件输入流，读取文件
     * fstream  ，文件输入输出流，可读可写
     */

    ofstream ofs;
    ofs.open("test.txt", ios::out);
    ofs << "内容1" << endl;
    ofs << "内容2" << endl;
    ofs.close();

    ifstream ifs;
    char text[100] = { 0 };
    ifs.open("test.txt", ios::in);
    if (ifs.is_open()) {
        while (ifs >> text)  cout << text << endl;
    }
    ifs.close();

    return 0;
}
```

# 三、C++ 泛型

## 1 函数米板

（1）基本使用

```
#include<iostream>
using namespace std;

// typename 和 class 都可以，都一样，不过一般函数模板用 typename ，类模板用 class
template<typename T>
T func(T a, T b) {
    // 可以查看 T 时什么类型
    cout << typeid(T).name() << endl;
    return a + b;
}

// 可以传多个泛型
template<class T, typename U>
void func() {

}

int main() {
    int a = 5, b = 7;
    double c = 3.4, d = 5.8;

    /* 自动类型推导
     * 类型推导的各个类型必须一样，即传入的类型必须一样
     * 因此，没有隐式类型转换
     */
    cout << func(a, b) << endl;

    /* 显示指定类型
     * 当函数模板没有自动类型推导时，也必须显示指定类型
     * 和普通函数一样，有隐式类型转换
     */
    cout << func<double>(c, d) << endl;
    func<int, int>();  // 虽然函数模板内部没有用到泛型，，但是这种没有自动类型推导的情况下必须要显示指定类型
    cout << func<double>(a, b) << endl;  // 有隐式类型转换

    return 0;
}
```

（2）函数模板和普通函数的重载和执行优先级

函数模板可以重载，泛型列表也可以是重载的条件。函数模板和普通函数也可以重载，且是各自分开的：

```
#include<iostream>
using namespace std;

// 普通函数和函数模板的重载是各自分开的 -----------------------------------------------------------------
void func1() {
    cout << "普通函数" << endl;
}

template<typename T>
void func1() {
    cout << "函数模板 1" << endl;
}

template<typename T>
void func1(T a) {
    cout << "函数模板 2" << endl;
}

// 泛型列表也可以是重载的条件
template<typename T, typename U>
void func1(T a) {
    cout << "函数模板 3" << endl;
}
// ------------------------------------------------------------------------------------

int main() {
    int a = 10;
    double b = 5.6;

    // 重载
    func1();
    func1<int>();
    func1<int>(a);
    func1<int, int>(a);

    return 0;
}
```

当普通函数和函数模板：

* 同时满足执行条件时，优先执行普通函数，即使普通函数只是一个函数声明（这时就会报错）

* 如果像优先执行函数模板，可以用空模板参数列表

* 当函数模板条件更优时，执行函数模板，比如函数模板不需要隐式类型转换就可以执行的时候；当两个函数模板同时符合条件时，也是优先执行条件更优的那个，比如类型更明确

```
#include<iostream>
using namespace std;

void func(int a) {
    cout << a * 10 << endl;
}

template<typename T>
void func(T a) {
    cout << a << endl;
}

int main() {
    int a = 10;
    double b = 5.6;

    // 优先执行普通函数
    func(a);

    // 空模板参数列表，通过自动类型推导执行函数模板
    func<>(a);

    // 普通函数需要隐式类型转换，而函数模板则可以直接执行，条件更好，所以执行函数模板
    func(b);

    return 0;
}
```

（3）模板的局限性

比如相加，int、double 这些可以，但是数组、类就不行，类可以通过运算符重载解决，但是比较麻烦，这里使用模板具体化的方法解决：

```
#include<iostream>
using namespace std;

class LinkList {};

template<typename T>
void func(T a, T b) {
    cout << a + b << endl;
}

// 具体化
void func(LinkList &list1, LinkList &list2) {
    cout << "class + class" << endl;
}


int main() {
    int a = 5, b = 7;
    LinkList list1, list2;

    func(5, 7);
    func(list1, list2);

    return 0;
}
```

## 2 类模板

（1）基本使用

* 类模板没有自动类型推导

* 类模板可以使用默认值，函数模板不可以

* 类模板的成员函数也可以是函数模板，且泛型参数不冲突

```
#include<iostream>
using namespace std;

// 可以有默认值
template<class T, class U = int>
class LinkList {
public:
    T a;
    U b;

    LinkList(T a, U b) {
        this->a = a;
        this->b = b;
    }

    // 这列的 T 和类模板的 T 不同
    template<typename T, typename V>
    void func(T n,V m) {
        cout << n << " " << m << endl;
    }
};


int main() {
    // 必须显示指定类型
    LinkList<int, int> list(5, 7);

    int a = 10;
    double b = 20.6;
    list.func(a, b);
    list.func<double, double>(b, b);

    return 0;
}
```

类模板的继承和外部实现成员函数：

```
#include<iostream>
using namespace std;

template<class T>
class A {
public:
    void func();
};

// 继承需要指定类型，或者把继承也写成一个类模板
class B : A<int> {};

template<class T>
class C : A<T> {};

// 外部实现成员函数需要指定类型，或者写成一个函数模板
void A<int>::func(){
  cout << "当 A 传入 int 时优先执行这个" <<endl;
}

template<typename T>
void A<T>::func() {
    cout << "其他情况" << endl;
}

int main() {
    A<int> a1;
    A<double> a2;
    a1.func();
    a2.func();
    return 0;
}
```

类模板和友元：

```
#include<iostream>
using namespace std;

template<class T>
class LinkList;

template<typename T>
void func(LinkList<T> &list) {
    cout << list.date << endl;
}


template<class T>
class LinkList {
    // 可以直接类内实现
    // friend void func(LinkList<T> &list) {}

    // 类外实现，注意要加上空模板参数 <>
    friend void func<>(LinkList<T> &list);

private:
    T date = 10;
};

int main() {
    LinkList<int> list;
    func(list);
    return 0;
}
```

（2）类模板作为函数形参

三种形式：

```
#include<iostream>
using namespace std;

template<class T>
class LinkList {};

// 三中方式可以重载，但是调用时是执行第一个普通函数（如果没有第一个普通函数，就会执行第二个参数也是泛型的函数模板），所以函数名要区分开
void func1(LinkList<int> &list) {
    cout << "指定模板参数，最常用" << endl;
}

template<typename T>
void func2(LinkList<T> &list) {
    cout << "类模板参数也是泛型" << endl;
}

template<typename T>
void func3(T &list) {
    cout << "整个类作为泛型" << endl;
}

int main() {
    LinkList<int> list;
    func1(list);
    func2(list);
    func3(list);
    return 0;
}
```

（3）类铭板的成员函数的创建时机和份文件编写

只有在调用这个函数时，才会创建这个函数。因此可能会出现编译时难以发现的错误，因为语法没有错误：

```
#include<iostream>
using namespace std;

class A {
public:
    void func1() {
        cout << "A func1" << endl;
    }
};

template<class T>
class B {
public:
    T obj;

    B(T &obj) {
        this->obj = obj;
    }

    void func1() {
        this->obj.func1();
    }

    void func2() {
        // A 类中并没有 func2 ，但是不会报错，因为编译时还不知道 T 时什么类型
        this->obj.func2();
    }
};

int main() {
    A a;
    B<A> b(a);
    b.func1();
    // b.func2();
    return 0;
}
```

由于类模板的成员函数在执行时才会创建，所以份文件编写 .h 和 .cpp 时，.h 不会成员函数编译，在链接时就会找不到对应的成员函数就会报错，因为此时还没有到执行。

解决方法是把 .h 的声明和 .cpp 的视线全部放在一个 .hpp 文件中，一个功能一个 .hpp ，引入这个 .hpp 头文件就行。

# 四、C++ STL

STL（Stander Template Library ，标准模板库），提供了一套统一的数据结构和算法，方便开发使用。

分为 6 大组件：

* 容器：存储数据，即数据结构，分类：
  
  - 序列式容器：每个数据都有固定的位置
  
  - 关联式容器：每个数据的位置不固定

* 算法：常用的算法、如排序、遍历等，分类：
  
  - 质变算法：运算过程中会更改元素的内容
  
  - 非质变算法：运算过程中不改变元素的内容

* 迭代器：容器和算法之间通过迭代器无缝连接，是容器和算法之间的胶合剂，算法需要通过迭代器才能访问容器中的元素，每个容器都有自己的专属迭代器，分类：
  
  - 输入：只读
  
  - 输出：只写
  
  - 向前：往前递增
  
  - 双向：可读可写可递增
  
  - 随机访问：可跳跃式地读取容器中的任何数据
  
  双向和随机访问最常见。

* 访函数：协助算法完成不同的策略变化

* 适配器：修饰容器的接口

* 空间配置器：负责空间的配置和管理，如容器中有动态分配的内存，会自动释放

容器、算法和迭代器是最重要的三个组件，三者之间的配合实例：

```
#include<iostream>
#include<vector>
#include<algorithm>  // 为了使用 for_each()
using namespace std;

void myPrint(int num) {
    cout << num << " ";
}

int main() {
    // vector 容器
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    // 遍历方式 1
    // 迭代器，是一个指针
    vector<int>::iterator begin = v.begin();  // 指向顶一个元素的地址
    vector<int>::iterator end = v.end();      // 指向最后一个元素的下一个地址
    while (begin != end) {
        cout << *begin << " ";
        ++begin;
    }
    cout << endl;

    // 遍历方式 2
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // 遍历方式 3 ，使用 STL 提供的遍历算法
    for_each(v.begin(), v.end(), myPrint);
    cout << endl;

    // 常对象，不能修改/插入/删除元素，常用语函数形参，防止修改，
    const vector<int> cv(10, 1);
    for_each(cv.begin(), cv.end(), myPrint);
    // 但是迭代器一起要用 const 的
    vector<int>::const_iterator cvBegin = cv.begin();

    return 0;
}
```

## 1 vector

对 C++ 数组进行了封装，提供了一些列操作数组的函数，是一个序列式容器，具有随机访问的迭代器。与数组的区别：

* vector 是单端数组，只能从尾部插入和删除元素

* C++ 数组的空间是定死的，除非手动动态分配内存；vector 会自动动态分配和释放内存，规则是申请一块新的空间并拷贝所有元素，然后释放原空间，当使用 push_back\(\) 添加元素时，若空间不足则会申请空间，申请多大的空间由 vector 底层决定

（1）基本使用

```
#include<iostream>
#include<vector>
#include<algorithm>  // 为了使用 for_each()
using namespace std;

class Person {
public:
    int age;
    Person(int age) {
        this->age = age;
    }
};

void myPrint(Person &p) {
    cout << p.age << " ";
}

int main() {
    // 一位 vector
    Person p1(18), p2(28);
    vector<Person> v1, v2;
    v1.push_back(p1);
    v1.push_back(p2);
    v2.push_back(p1);
    v2.push_back(p2);

    // 二维 vector
    vector<vector<Person>> v;
    v.push_back(v1);
    v.push_back(v2);

    // 遍历
    for (vector<vector<Person>>::iterator it = v.begin(); it != v.end(); it++) {
        for_each(it->begin(), it->end(), myPrint);
        cout << endl;
    }

    return 0;
}
```

（2）构造函数

```
#include<iostream>
#include<vector>
#include<algorithm>  
using namespace std;

void myPrint(int num) {
    cout << num << " ";
}

int main() {
    /* 构造函数
     * vector<T>()                    默认构造 
     * vector<T>(v.begin(), v.end())  左闭右开
     * vector<T>(int size, T ele)     size 个 ele
     * vector<T>(const vector<T> &v)  拷贝构造
     */

    // 1 2 3 4 5
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    for_each(v1.begin(), v1.end(), myPrint);
    cout << endl;

    // 3 4 5
    vector<int> v2 = vector<int>(v1.begin() + 2, v1.end());
    for_each(v2.begin(), v2.end(), myPrint);
    cout << endl;

    // 5 5 5
    vector<int> v3 = vector<int>(3, 5);
    for_each(v3.begin(), v3.end(), myPrint);
    cout << endl;

    // 5 5 5
    vector<int> v4 = v3;
    for_each(v4.begin(), v4.end(), myPrint);
    cout << endl;

    return 0;
}
```

（3）赋值

```
#include<iostream>
#include<vector>
#include<algorithm>  
using namespace std;

void myPrint(int num) {
    cout << num << " ";
}

int main() {
    /* 赋值
     * vector<T>& operator=(const vector<T> &v)   重载 =
     * assign(v.begin(), v.end())                 左闭右开
     * assign(int size, T ele)                    size 个 ele
     */

     // 1 2 3 4 5
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    for_each(v1.begin(), v1.end(), myPrint);
    cout << endl;

    vector<int> v2, v3, v4;

    // 1 2 3 4 5 
    v2 = v1;
    for_each(v2.begin(), v2.end(), myPrint);
    cout << endl;

    // 3 4 5
    v3.assign(v1.begin() + 2, v1.end());
    for_each(v3.begin(), v3.end(), myPrint);
    cout << endl;

    // 5 5 5
    v4.assign(3, 5);
    for_each(v4.begin(), v4.end(), myPrint);
    cout << endl;

    return 0;
}
```

（4）空间大小

```
#include<iostream>
#include<vector>
#include<algorithm>  
using namespace std;

void myPrint(int num) {
    cout << num << " ";
}

int main() {
    /* 空间大小
     * empty()           判断是否为空
     * capacity()        内存空间大小
     * size()            元素数量，<= 内存空间大小
     * resize(int size)  重新设置大小，比原来小就删除多的元素，比原来大就扩大空间并补 0
     */

    // 1 2 3 4 5
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    for_each(v1.begin(), v1.end(), myPrint);
    cout << endl;

    // 0
    cout << v1.empty() << endl;

    // ? 5
    cout << v1.capacity() << " " << v1.size() << endl;

    // ? 2
    v1.resize(2);
    cout << v1.capacity() << " " << v1.size() << endl;

    return 0;
}
```

（5）插入、删除元素

```
#include<iostream>
#include<vector>
#include<algorithm>  
using namespace std;

void myPrint(int num) {
    cout << num << " ";
}

int main() {
    /* 插入、删除元素，erase 和 clear 只是删除元素，但是还会保留内存空间
     * push_back(T ele)                                 尾部插入
     * pop_back()                                       尾部删除
     * insert(const iterator pos, T ele)                指定位置插入一个元素
     * insertconst (iterator pos, int count, T ele)     指定位置插入多个元素
     * erase(const iterator pos)                        删除指定位置的元素
     * erase(const iterator begin, const iterator end)  删除，左闭右开
     * clear()                                          清空
     */

     // 1 2 3 4 5
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    for_each(v1.begin(), v1.end(), myPrint);
    cout << endl;

    // -1 -1 0 1 2 3 4 5
    v1.push_back(6);
    v1.pop_back();
    v1.insert(v1.begin(), 0);
    v1.insert(v1.begin(), 2, -1);
    for_each(v1.begin(), v1.end(), myPrint);
    cout << endl;
    cout << v1.capacity() << endl;

    // 1 2 3 4 5
    v1.erase(v1.begin());
    v1.erase(v1.begin(), v1.begin() + 2);
    for_each(v1.begin(), v1.end(), myPrint);
    cout << endl;
    cout << v1.capacity() << endl;

    v1.clear();
    cout << v1.capacity() << endl;

    return 0;
}
```

（6）访问

```
#include<iostream>
#include<vector>
#include<algorithm>  
using namespace std;

void myPrint(int num) {
    cout << num << " ";
}

int main() {
    /* 访问
     * vector<T>& operator[](int index)
     * at(int index)                  
     * front()
     * back()
     */

     // 1 2 3 4 5
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    for_each(v1.begin(), v1.end(), myPrint);
    cout << endl;

    v1[3] = 6;
    cout << v1[2] << endl;
    cout << v1.at(2) << endl;
    cout << v1.front() << endl;
    cout << v1.back() << endl;

    return 0;
}
```

（7）交换

```
#include<iostream>
#include<vector>
#include<algorithm>  
using namespace std;

void myPrint(int num) {
    cout << num << " ";
}

int main() {
    /* 交换
     * swap(vector<T> &v) 
     */

     // 1 2 3
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    for_each(v1.begin(), v1.end(), myPrint);
    cout << endl;


    // 4 5 6
    vector<int> v2;
    v2.push_back(4);
    v2.push_back(5);
    v2.push_back(6);
    for_each(v2.begin(), v2.end(), myPrint);
    cout << endl;

    // 交换
    v1.swap(v2);
    for_each(v1.begin(), v1.end(), myPrint);
    cout << endl;
    for_each(v2.begin(), v2.end(), myPrint);
    cout << endl;

    // 利用 swap 可以压缩空间，因为 resize、erase、clear 都会保留原有空间、造成浪费
    vector<int> v3 = vector<int>(10000, 5);
    v3.clear();
    cout << v3.capacity() << " " << v3.size() << endl;
    // 通过拷贝构造创建一个匿名对象，然后交换，交换完成匿名对象就销毁
    vector<int>(v3).swap(v3);
    cout << v3.capacity() << " " << v3.size() << endl;

    return 0;
}
```

（8）预留空间

插入元素时，若 vector 容量不够会自动扩容，但如果插入大量元素会执行大量的扩容操作，效率不高，所以可以使用预留空间，先创建好一个大空间：

```
#include<iostream>
#include<vector>
using namespace std;

int main() {
    /* 预留空间
     * reserve(int len0
     */

    vector<int> v1 = vector<int>(10, 1);
    int cnt = 0;
    for (int i = 0; i < 10000; i++) {
        int *p = &v1[0];
        v1.push_back(1);
        if (p != &v1[0])  cnt++;
    }
    cout << cnt << endl;

    v1.reserve(20000);
    for (int i = 0; i < 10000; i++) {
        int* p = &v1[0];
        v1.push_back(1);
        if (p != &v1[0])  cnt++;
    }
    cout << cnt << endl;

    return 0;
}
```

（9）deque

双端数组，实现原理是内部有一个中控器，管理多个存储若干元素的缓冲区，当头部/尾部插入元素空间不足时，就会新申请一块空间作为缓冲区。说白了相当于数组 + 链表，链表的每一个结点事一个缓冲区，缓冲区是一个数组。

与 vector 的区别：

* 可以从头部或者尾部插入、删除元素，且速度很快，但是访问速度慢。vectore 虽然也能从头部 insert 元素，但是需要移动后面的所有元素，但是访问速度很快

* 插入/删除方式读【了 push_front\(\) 、pop_front\(\)

* 由于 deque 的特性，没有空间限制，所以没有 capacity\(\) 和预留空间

其他和 vector 差不多。

## 2 string

对 C++ 的 char\* 进行了封装，序列式容器，随机访问迭代器。

（1）构造函数

```
#include<iostream>
#include<string>
using namespace std;

int main() {
    /* 构造函数
     * string()
     * string(const char *s)
     * string(const string &s)
     * string(int size, char c)
     */

    string s1;
    string s2("asdf");
    string s3(s2);
    string s4(5, 'a');

    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;

    return 0;
}
```

（2）赋值

```
#include<iostream>
#include<string>
using namespace std;

int main() {
    /* 赋值
     * string& operator=(char *s)
     * string& operator=(string &s)
     * string& operator=(char c)
     * string& assign(char *s)
     * string& assign(char *s, int n)     截取前 n 个字符
     * string& assign(string &s)
     * string& assign(int size, char c)
     */

    string s1, s2, s3, s4, s5, s6, s7;
    s1 = "asdf";
    s2 = s1;
    s3 = 'a';
    s4.assign("asdf");
    s5.assign("asdf", 3);
    s6.assign(s5);
    s7.assign(5, 'a');

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
    cout << s5 << endl;
    cout << s6 << endl;
    cout << s7 << endl;

    return 0;
}
```

（3）拼接

```
#include<iostream>
#include<string>
using namespace std;

int main() {
    /* 拼接
    * string& operator+=(const char *s)
    * string& operator+=(const string &s)
    * string& operator+=(const char c)
    * string& append(const char *s)
    * string& append(const char *s, int n)            截取 s 的前 n 个字符进行拼接
    * string& append(const string &s)
    * string& append(const string &s, int pos, in n)  截取 s 索引 pos 开始的 n 个字符进行拼接
     */

    string s1("asdf");
    s1 += 'g';
    cout << s1 << endl;
    s1.append("qwer", 2);
    cout << s1 << endl;
    s1.append("zxcv", 1, 2);
    cout << s1 << endl;

    return 0;
}
```

（4）查找和替换

```
#include<iostream>
#include<string>
using namespace std;

int main() {
    /* 查找和替换，find 从左边开始找，rfind 从右边开始找
     * int find(const char c, int pos = 0)
     * int find(const string &s, int pos = 0)
     * int find(const char *s, int pos = 0)
     * int find(const char *s, int pos, int n)
     * string& replace(int pos, int n, string *s)
     * string& replace(int pos, int n, char *s)
     */

    return 0;
}
```

（5）比较

根据字符的 ASCI 大小比较，若相等则比较下一个字符。

```
#include<iostream>
#include<string>
using namespace std;

int main() {
    /* 比较，>、=、< 返回 1 0 -1
     * int compare(const string &s)
     * int compare(const char *s)
     */

    string s1("asdf");
    string s2("qwer");
    string s3("中文");

    // -1
    cout << s1.compare(s2) << endl;

    // 非 ASCI 比较不确定，要根据编码规则
    cout << s1.compare(s3) << endl;

    return 0;
}
```

（6）访问

```
#include<iostream>
#include<string>
using namespace std;

int main() {
    /* 访问
     * char& operator[](int index)
     * char& at(int index)
     */

    return 0;
}
```

（7）插入删除

```
#include<iostream>
#include<string>
using namespace std;

int main() {
    /* 插入、删除
     * string& insert(int pos, char *s)
     * string& insert(int pos, string &s)
     * string& insert(int pos, int n, char c)
     * string& erase(int pos, int n = npos)
     */

    return 0;
}
```

（8）截取

```
#include<iostream>
#include<string>
using namespace std;

int main() {
    /* 截取
     * string substr(int pos = 0, int n = npos)
     */

    // asd
    string s1("asdfghjkl");
    cout << s1.substr(0, 3) << endl;

    return 0;
}
```

## 3 stack、queue、list、set、map

（1）stack、queue、list

即栈。队列和链表，其中链表是双向循环链表，都是序列式容器。

* stack 和 quque 迭代器是向前，在 STL 中没有遍历，因为遍历就需要出栈、出队，而 STL 的遍历算法是非质变的，遍历过程不允许修改

* list 的迭代器是双向，而不是随机访问，这也是因为链表不能像数组一样用索引访问，像 list 这种不能随机访问的容器，内部都会实现自己的算法而不是用通用的 algorithm，如排序

stack：

```
#include<iostream>
#include<stack>
using namespace std;

int main() {
    // 构造函数
    stack<int> s1;
    stack<int> s2(s1);

    // 赋值
    stack<int> s3;
    s3 = s1;

    // 存取
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.pop();
    // 2
    cout << s1.top() << endl;

    // 大小
    cout << s1.empty() << endl;
    cout << s1.size() << endl;

    return 0;
}
```

queue：

```
#include<iostream>
#include<queue>
using namespace std;

int main() {
    // 构造函数
    queue<int> q1;
    queue<int> q2(q1);

    // 赋值
    queue<int> q3;
    q3 = q1;

    // 存取
    q1.push(1);
    q1.push(2);
    q1.push(3);
    q1.pop();
    // 2 3
    cout << q1.front() << " " << q1.back() << endl;

    // 大小
    cout << q1.empty() << endl;
    cout << q1.size() << endl;

    return 0;
}
```

list：

接口基本和 deque 一样，只是少了 \[\] 和 at ，多了 reverse 和 sort

（2）set、multiset 和 pair

底层实现是二叉排序树，插入就排好序，是一个关联式容器。

set 不允许有重复元素，而 multiset 允许，这是两者唯一的区别。

```
#include<iostream>
#include<set>  // set、multiset 都有
#include<algorithm>
using namespace std;

void myPrint(int num) {
    cout << num << " ";
}

int main() {
    // 构造函数
    set<int> s1;
    multiset<int> ms1;
    set<int> s2(s1);

    // 赋值
    set<int> s3;
    s3 = s1;

    // 插入
    s1.insert(1);
    s1.insert(3);
    s1.insert(2);
    s1.insert(2);
    s1.insert(2);

    // 遍历
    // 1 2 3
    for_each(s1.begin(), s1.end(), myPrint);
    cout << endl;

    // 大小、删除，insert 、 erase 、 clear
    cout << s1.empty() << endl;
    cout << s1.size() << endl;

    // 交换
    s2.insert(10);
    s1.swap(s2);
    s2.swap(s1);

    // 查找，返回迭代器，找不到返回 end 迭代器
    set<int>::iterator res = s1.find(2);
    cout << (res != s1.end()) << endl;

    // 统计个数，set 只有0 或 1 ，multiset才可能 > 1
    cout << s1.count(2) << endl;

    return 0;
}
```

修改排序规则：

默认是升序，可以修改排序规则，通过访函数实现。当 set 存储自定义数据类型时，必须修改排序规则，否则 set 不知道怎么插入：

```
#include<iostream>
#include<set>
#include<algorithm>
using namespace std;

class Person {
public:
    int age;
    Person(int age) {
        this->age = age;
    }
};

// 修改排序规则需要使用访函数，所以需要随便定义一个类，当然也可以在 Person 中定义访函数
class MyRule {
public:
    bool operator()(const Person &p1, const Person &p2) const {
        return p1.age > p2.age;
    }
};

void myPrint(const Person &p) {
    cout << p.age << " ";
}

int main() {
    Person p1(18), p2(28);
    set<Person, MyRule> s;
    s.insert(p1);
    s.insert(p2);
    for_each(s.begin(), s.end(), myPrint);
    return 0;
}
```

pair：

对组，成对出现的一组数据，两个数据类型可以不同。

set 插入时内部会检测是否是重复数据，返回值是一个 pair，存储插入到哪的迭代器和是否插入成功的布尔值。

```
#include<iostream>
#include<set>  // set、multiset 都有
#include<algorithm>
using namespace std;

void myPrint(int num) {
    cout << num << " ";
}

int main() {
    // pair 不需要头文件
    // 创建
    pair<int, double> p1(12, 5.6);
    pair<int, int> p2 = make_pair(10, 15);

    // 访问
    cout << p1.first << " " << p1.second << endl;

    // set 中 insert 的返回值是一个 pair，存储插入到哪的迭代器和是否成功的布尔值
    set<int> s;
    pair<set<int>::iterator, bool> res = s.insert(1);
    cout << res.second << endl;

    return 0;
}
```

（3）map、multimap

map 是性能很高的容器，每个元素是一个 pair ，第一个为 key 也叫键值，第二个为 value 也叫实值，所以这个 pair 也叫键值对，通过 key 可以索引。

map 和 multimap 时关联式容器，会按照 key 排序。

map、mutimap 的唯一区别是 map 不允许重复 key ，multimap 允许。value 不管是 map 还是 multimap 都允许重复。

```
#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

void myPrint(const pair<int, int> &p) {
    cout << p.first << " " << p.second << endl;
}

int main() {
    // 构造函数
    map<int, int> s1;
    multimap<int, int> ms1;
    map<int, int> s2(s1);

    // 赋值
    map<int, int> s3;
    s3 = s1;

    // 插入、删除，insert 、 erase 、clear
    s1.insert(pair<int, int>(0, 123));
    s1.insert(pair<int, int>(1, 456));
    s1.insert(pair<int, int>(2, 789));

    // 遍历
    for_each(s1.begin(), s1.end(), myPrint);

    // 大小
    cout << s1.empty() << endl;
    cout << s1.size() << endl;

    // 交换
    s2.insert(pair<int, int>(0, 123));
    s1.swap(s2);
    s2.swap(s1);

    // 查找，按照 key，返回迭代器，找不到返回 end 迭代器
    map<int, int>::iterator res = s1.find(1);
    cout << (res != s1.end()) << endl;

    // 统计个数，按照 key
    cout << s1.count(1) << endl;

    return 0;
}
```

修改排序规则：

默认是升序。

```
#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

class MyRule {
public:
    bool operator()(int key1, int key2) const {
        return key1 > key2;
    }
};

void myPrint(const pair<int, int> &p) {
    cout << p.first << " " << p.second << endl;
}

int main() {
    map<int, int, MyRule> m;
    m.insert(pair<int, int>(0, 123));
    m.insert(pair<int, int>(1, 456));
    for_each(m.begin(), m.end(), myPrint);
    return 0;
}
```

## 4 访函数

（1）基本使用

本质是重载了函数调用操作符的类，因为时很想函数调用，所以叫仿函数，使用时实例化出的对象叫函数对象。相当于把函数封装成一个类。

仿函数很灵活，返回类型形参函数体都不固定，但是仿函数不超出了普通函数的概念，这个类内部可以有自己的成员属性和成员函数等来记录状态。

仿函数也可以作为函数形参，泛型。

```
#include<iostream>
using namespace std;

class MyFunc {
public:
    int cnt = 0;
    void operator()() {
        cout << "仿函数调用" << endl;
        ++cnt;
    }
};

int main() {
    MyFunc mf;
    mf();
    mf();
    MyFunc();  // 匿名函数对象并调用
    // 2 ，调用次数
    cout << mf.cnt << endl;
    return 0;
}
```

谓词：返回 bool 的访函数，有 n 个形参也叫 n 元谓词。

（2）内建函数对象

STL 内置的访函数，分为算术访函数、关系访函数和逻辑访函数。操作 n 个数的叫 n 元运算。

常用于 STL 中需要传入访函数的场景。

```
#include<iostream>
#include<functional>
using namespace std;

int main() {
    // 取相反数
    negate<int> n;
    cout << n(50) << endl;

    // 加法
    plus<int> p;
    cout << p(1, 1) << endl;

    // 大于、小于
    greater<int> g;
    less<int> l;
    cout << g(7, 5) << " " << l(7, 5) << endl;

    // 逻辑非
    logical_not<int> ln;
    cout << ln(1) << endl;

    return 0;
}
```

## 5 常用 STL 算法

（1）遍历

```
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

class MyPrint {
public:
    void operator()(int n) {
        cout << n << " ";
    }
};

int main() {
    /* 遍历
     * for_each()
     * transform()  拷贝并对每个元素做处理，目标必须有足够的空间
     */

    vector<int> v1(10, 5);
    vector<int> v2;
    v2.resize(10);
    transform(v1.begin(), v1.end(), v2.begin(), negate<int>());
    for_each(v2.begin(), v2.end(), MyPrint());

    return 0;
}
```

（2）查找

```
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

class Person {
public:
    int age;

    Person(int age) {
        this->age = age;
    }

    bool operator==(const Person &p) const {
        return this->age == p.age;
    }

    bool operator>(const Person& p) const {
        return this->age > p.age;
    }

    bool operator<(const Person& p) const {
        return this->age < p.age;
    }
}; 

class IntCompare3 {
public:
    bool operator()(int a) const {
        return a > 3;
    }
};

class PersonCompare20 {
public:
    bool operator()(Person &a) const {
        return a.age > 20;
    }
};

int main() {
    /* 查找，
     * find()              查找，返回迭代器
     * find_if()         按条件查找，返回迭代器
     * adjacent_find()   查找相邻重复元素，返回迭代器
     * binary_search()   二分查找，只能用于有序的，返回 bool
     * count()           统计，返回 int
     * count_if()        按条件统计，返回 int
     */

    vector<int> v1;
    vector<Person> v2;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v2.push_back(Person(8));
    v2.push_back(Person(18));
    v2.push_back(Person(28));
    v2.push_back(Person(38));
    v2.push_back(Person(48));

    cout << (find(v1.begin(), v1.end(), 3) != v1.end()) << endl;
    cout << (find(v2.begin(), v2.end(), Person(48)) != v2.end()) << endl;

    cout << (find_if(v1.begin(), v1.end(), IntCompare3()) != v1.end()) << endl;
    cout << (find_if(v2.begin(), v2.end(), PersonCompare20()) != v2.end()) << endl;

    cout << (adjacent_find(v1.begin(), v1.end()) != v1.end()) << endl;
    cout << (adjacent_find(v2.begin(), v2.end()) != v2.end()) << endl;

    cout << binary_search(v1.begin(), v1.end(), 3) << endl;
    cout << binary_search(v2.begin(), v2.end(), Person(48)) << endl;

    cout << count(v1.begin(), v1.end(), 3) << endl;
    cout << count(v2.begin(), v2.end(), Person(48)) << endl;

    cout << count_if(v1.begin(), v1.end(), IntCompare3()) << endl;
    cout << count_if(v2.begin(), v2.end(), PersonCompare20()) << endl;

    return 0;
}
```

（3）排序

```
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

class Person {
public:
    int age;

    Person(int age) {
        this->age = age;
    }
}; 

class IntCompare {
public:
    bool operator()(int a, int b) const {
        return a > b;
    }
};

class PersonCompare {
public:
    bool operator()(Person &a, Person &b) const {
        return a.age > b.age;
    }
};

int main() {
    /* 排序
     * sort()            排序
     * random_shuffle()  打乱顺序，需要设置随机种子
     * merge()           合并，要求两个容器必须有序且都是升序或是降序，目标容器也必须有足够空间，合并后依然有序
     * reverse()         翻转
     */

    vector<int> v1;
    vector<Person> v2;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v2.push_back(Person(8));
    v2.push_back(Person(18));
    v2.push_back(Person(28));
    v2.push_back(Person(38));
    v2.push_back(Person(48));

    sort(v1.begin(), v1.end());
    sort(v1.begin(), v1.end(), IntCompare());
    sort(v2.begin(), v2.end(), PersonCompare());

    srand((unsigned int)time(NULL));  // 设置随机种子
    random_shuffle(v1.begin(), v1.end());
    random_shuffle(v2.begin(), v2.end());

    vector<int> v11(10, 1), v111;
    v111.resize(20);
    sort(v1.begin(), v1.end());
    merge(v1.begin(), v1.end(), v11.begin(), v11.end(), v111.begin());

    reverse(v1.begin(), v1.end());
    reverse(v2.begin(), v2.end());

    return 0;
}
```

（4）拷贝和替换

```
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

class Person {
public:
    int age;
    Person() {}
    Person(int age) {
        this->age = age;
    }

    bool operator==(const Person &p) const {
        return this->age == p.age;
    }
}; 

class IntCompare3 {
public:
    bool operator()(int a) const {
        return a > 3;
    }
};

class PersonCompare20 {
public:
    bool operator()(const Person &a) const {
        return a.age > 20;
    }
};

int main() {
    /* 拷贝和替换
    * copy()
    * replace()
    * replace_if()
    * swap()
     */

    vector<int> v1;
    vector<Person> v2;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v2.push_back(Person(8));
    v2.push_back(Person(18));
    v2.push_back(Person(28));
    v2.push_back(Person(38));
    v2.push_back(Person(48));

    vector<int> v11;
    vector<Person> v22;
    v11.resize(10);
    v22.resize(10);

    copy(v1.begin(), v1.end(), v11.begin());
    copy(v2.begin(), v2.end(), v22.begin());

    replace(v1.begin(), v1.end(), 3, 33);
    replace(v2.begin(), v2.end(), Person(488), Person(58));

    replace_if(v1.begin(), v1.end(), IntCompare3(), 33);
    replace_if(v2.begin(), v2.end(), PersonCompare20(), Person(488));

    swap(v1, v11);
    swap(v2, v22);

    return 0;
}
```

（5）算术生成算法

比较小型的算法，这种小型的算法的头文件是 numeric ，不是 algorithm 。

```
#include<iostream>
#include<vector>
#include<numeric>
using namespace std;

int main() {
    /* 算术生成算法
     * accumulate() 累加，可以给初始值
     * fill()       指定范围填充
     */

    vector<int> v1, v2;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v2.resize(10);

    cout << accumulate(v1.begin(), v1.end(), 0) << endl;

    fill(v2.begin(), v2.end(), 1);

    return 0;
}
```

（6）集合算法

```
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class MyPrint {
public:
    void operator()(int n) {
        cout << n << " ";
    }
};

int main() {
    /* 集合算法，两个容器必须有序
     * set_intersection()  交集
     * set_union()         并集
     * set_difference()    差集
     */

    vector<int> v1, v2, v3, v4, v5;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v2.push_back(1);
    v2.push_back(6);
    v2.push_back(7);

    v3.resize(min(v1.size(), v2.size()));
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
    for_each(v3.begin(), v3.end(), MyPrint());
    cout << endl;

    v4.resize(v1.size() + v2.size());
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v4.begin());
    for_each(v4.begin(), v4.end(), MyPrint());
    cout << endl;

    v5.resize(max(v1.size(), v2.size()));
    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v5.begin());
    for_each(v5.begin(), v5.end(), MyPrint());
    cout << endl;

    return 0;
}
```
