# 一、开始

目前主流的版本有5.7和8。

端口默认是3306。

查看版本：

```
mysql -V
```

```
mysql --version
```

启动：

root是mysql的用户名，输入完后就输入密码

```
mysql -u root -p
```

退出：

```
quit
```

每条sql语句结尾都需要分号，不区分大小写。

查看所有数据库：

```
show databases;
```

mysql默认存在的数据库：

* infomation_schema：保存数据库服务器的基本信息，如名称。

* mysql：保存数据库服务器在运行时需要的系统消息

* performance_schema：保存监控mysql的各种性能指标

* sys：保存性能指标

新建一个数据库：

```
create database xxx;
```

导入数据库：

```
source 路径;
```

进入某个数据库：

```
use xxx;
```

进入数据库后，查看该数据库的所有表：

```
show tables;
```

新建一个表：

```
create table xxx(id int, name varchar(20));
```

```
desc xxx;
```

给表插入内容：

```
insert into xxx values(001, 'lgx');
```

注意：8中字符集默认是utf8所以可以插入中文，但是5.7默认是latin1，可以查看字符集：

```
show variables like 'character_%';
```

```
show create table xxx;
```

5.7想要插入中文，需要修改配置文件 my.ini，修改后重启mysql生效，不过旧表还是latin1。新创建的表才是utf8。

查看表的内容：

```
select * from xxx;
```

删表，删库：

```
drop table xxx;
drop database xxx;
```

# 二、基本SQL

SQL（Structured Query Language，结构化查询语言）。

SQL分为三种：

* DDL：数据定义语言，create，drop等这些定义结果的

* DML：数据操作语言，insert，select，update，delete等这些操作数据的

* DCL：数据控制语言，commit，rollback等

SQL规则：

* windows不区分大小写（包括表内的数据），linux区分，所以一般规范是关键字这种大写，自定义的库名，表名，字段名这些小写

* 结尾加分号，可以换行写

* 单引号，双引号都行，但规范是单引号

* 字段命名：多个单词用 \_ 连接_

* 查询条件两个空格缩进

* 注释，\# 和 /\*\*/

## 1 查询

## 1.1 基本查询

列也叫字段，查询结果叫结果集。

查所有列的内容：

```
SELECT * FROM xxx;
```

查某一个列：

```
SELECT age FROM xxx;
```

查找多个列：

```
SELECT name, age FROM xxx;
```

查询结果运算：

```
SELECT age * 10 FROM xxx;
SELECT age * age FROM xxx;
```

算术运算符注意点：

* NULL运算后依然为NULL

* \+ 不能连接字符串，\+ 字符串 会将字符串转为数值，'02' 转为 2 ，不能转的转为0

* 取模一律为整型，除法结果一律为浮点型，初一0结果为NULL

如果NULL想用0替换：

```
SELECT IFNULL(age, 0) * 10 FROM xxx;
```

查询结果的列取别名：

如果别名有空格的话，一定要加引号

```
SELECT name n, age a FROM xxx;
SELECT name 'n', age 'a' FROM xxx;
SELECT name AS n, age AS a FROM xxx;
SELECT name 'n n', age AS 'a a' FROM xxx;
```

着重号，如果字段名不小心用了关键字，可以用着重号区分：

```
SELECT `from` FROM xxx;
```

查询常数：

填充一列的常数

```
SELECT '数据' age FROM xxx;
```

## 1.2 过滤数据

去重：

SELECT DISTINCT必须连接写，如果有多列，效果结合各列情况去重，如果前一列有重复的会看看后面的列有没有重复，有才会去重。

```
SELECT DISTINCT age FROM xxx;
SELECT DISTINCT age, name FROM xxx;
```

条件查询：

```
SELECT * FROM xxx 
WHERE age >= 20 AND age <= 30;
```

比较和逻辑运算符：

* 比较： 
  
  * == 变成 = 
  
  * != 也可以写成 <>
  
  * 与字符串与数值比较，若字符串能数值就转，不能就转为0
  
  * NULL与任何比较包括NULL结果都是NULL，<>比较也不行，结果为NULL会过滤掉
  
  * <=> 安全等于，可以用来比较是否等于NULL，但windows下依然不会区分大小写
  
  其他与C语言一样

* 逻辑：NOT 不能用 !，AND 和 &&，OR 和 ||，XOR 异或

* 其他关键字：
  
  * IS NULL ， IS NOT NULL 和 ISNULL()，常来判断是否是NULL
    
    ```
    SELECT * FROM xxx where age IS NULL;
    SELECT * FROM xxx where age IS NOT NULL;
    SELECT * FROM xxx where ISNULL(age);
    ```

* LEAST()，GREATEST()，多个列比较，找到最小值，最大值
  
  ```
  SELECT * FROM xxx where LEAST(age, age);
  SELECT * FROM xxx where GREATEST(age, age);
  ```

* BETWEEN...AND...，等价于 ... >= ... AND ... <= ...，不过BETWEEN...AND...要求左边是下限右边是上线
  
  ```
  SELECT * FROM xxx where age BETWEEN 20 AND 30;
  ```

* IN，查看是否是这些数值：
  
  ```
  SELECT * FROM xxx where age IN(25,30,35);
  ```

* LIKE，模糊查询，% 代表不确定个数（包括0个）的字符，\_ 代表一个不确定的字符。% 和 \_ 前面加 \ 可以转义
  
  如下分别是a开头，有a就行，a结尾，a在b前面，第二个字符是a的模糊糊查询：
  
  ```
  SELECT * FROM xxx WHERE name LIKE 'a%';
  SELECT * FROM xxx WHERE name LIKE '%a%';
  SELECT * FROM xxx WHERE name LIKE '%a';
  SELECT * FROM xxx WHERE name LIKE '%a%b%';
  SELECT * FROM xxx WHERE name LIKE '_a%';
  ```

* REGEXP，正则匹配：
  
  ```
  SELECT * FROM xxx where name REGEXP '正则';
  ```

## 1.3 排序与分页

（1）排序

排序会把NULL当成最小值。

AST升序，DESC降序，没有指定默认是升序：

```
SELECT * FROM xxx ORDER BY age ASC;
SELECT * FROM xxx ORDER BY age DESC;
```

多级排序，如先按age降序，相同的话再按id升序：

```
 SELECT * FROM xxx ORDER BY age DESC, id ASC;
```

排序条件可以用已定义的别名（where的过滤条件不能）：

这是因为SQL的执行顺序：from-select-as-order by，from-where-select-as

```
SELECT age as a FROM xxx ORDER BY a DESC;
```

但并不是说where前面不能用别名，这要区分开，其实就是执行顺序的问题：

```
SELECT age as a FROM xxx WHERE age > 20;
```

（2）分页

行的序号从0开始，第一个参数是起始索引，第二个参数是查找几条数据。

如下分别是查找第1条到10条共10条数据（索引0-9）和第11条到20条共10条数据（索引10-19）：

```
SELECT * FROM xxx LIMIT 0, 10;
SELECT * FROM xxx LIMIT 10, 10;
```

如果只有一个参数，那就是前 n 条数据：

```
SELECT * FROM xxx LIMIT 10;
```

8.0新特性：limit展示多少数据，offset第几条开始：

如下是从第16条开始展示10条：

```
SELECT * FROM xxx LIMIT 10 OFFSET 15;
```

## 1.4 多表查询

也叫关联查询。

#### 1.4.1 基本用法

现在有两张表students和classes。

| id  | name | age | class_id |
| --- | ---- | --- | -------- |
| 1   | John | 18  | 1        |
| 2   | Jane | 17  | 2        |
| 3   | Bob  | 16  | 1        |

**Table B: classes**

| id  | name    |
| --- | ------- |
| 1   | Class A |
| 2   | Class B |
| 3   | Class C |

查询1：如果学生有班级的话，查所有学生信息和班级信息

查询2：如果学生有班级的话，所有学生名称和所在的班级名称

* 正确做法：没有班级的学生挥没有学生的班级不会查出来。这是一个等值连接，非自连接，内连接
  
  ```
  SELECT * 
  FROM students, classes 
  WHERE students.class_id = classes.id;
  
  SELECT students.name, classes.name 
  FROM students, classes 
  WHERE students.class_id = classes.id;
  ```

* 错误做法：因为没有给关联条件或关联条件无效的话，这样是笛卡尔积，两张表的数据依次结合，最终生成 m*n 条数据
  
  ```
  /*
  SELECT * FROM students, classes;
  SELECT students.name, classes.name FROM students, classes;
  */
  ```

多表连接想避免笛卡尔积，有以下技巧：

* n个表的多表查询至少有n-1个条件

* 单个的条件可以不用涉及n个表，但是所有条件综合起来必须涉及n个表

* 使用or的时候需要特别小心，可以每个条件逐个分析，如：
  
  （students表中 John 的班级为NULL）
  
  ```
  SELECT students.name, classes.name 
  FROM students, classes 
  WHERE 
    students.class_id = classes.id 
    OR students.name = 'John';
  ```
  
  看起来没问题，预想的效果是查询所有学生的姓名和所在班级，同事把没有班级的John也查出来，但是结果却是每个学生的姓名和对应的班级和John的笛卡尔积。
  
  分析：
  
  这样得到所有学生的姓名和班级，但是没有班级的学生没有查出来：
  
  ```
  SELECT students.name, classes.name 
  FROM students, classes 
  WHERE 
    students.class_id = classes.id;
  ```
  
  这样查出来John的笛卡尔积：
  
  ```
  SELECT students.name, classes.name 
  FROM students, classes 
  WHERE 
    students.name = 'John';
  ```
  
  两个结果已合并就能看出来了。

规范：

在多表查询中，如果两个表的字段相同，在这种情况下select必须要 表名.字段名 进行区分，这就引出了一个规范：虽然所个表字段不同可以直接写字段名，但是为了统一，规范上是建议都是用 表名.字段名。这样做也能优化SQL查询的效率，因为SQL可以直接知道去哪个表而不需要遍历每个表。

表别名：

可以给表起别名，因为from是最先执行的，所以别名可以在其他SQL中使用。

注意：一旦表用了别名，别名就会覆盖表的原名，所以其他SQL也一定要用别名，这和之前字段别名不一样，字段别名不会覆盖原名。

```
SELECT t1.name, t2.name 
FROM students AS t1, classes AS t2 
WHERE t1.class_id = t2.id;
```

多表查询的场景：

- 角度1：
  
  * 等值连接：如a表bid = b表bid，上面的例子就是
  
  * 非等值连接：如a表成绩 between b表成绩下限 and 成绩上限，找出成绩等级
    
    ```
    SELECT t1.name, t2.lv 
    FROM students AS t1, scope AS t2 
    WHERE t1.result BETWEEN t2.low AND t2.high;
    ```

- 角度2：
  
  * 非自连接：a表与b表连接，上面的例子就是
  
  * 自连接：学生表和学生表连接，学生表某个字段指向她的组长在学生表的id
    
    ```
    SELECT t1.name, t2.name 
    FROM students AS t1, students AS t2 
    WHERE t1.heedman_id = t2.id;
    ```

- 角度3：
  
  * 内连接：只把左表和右表中满足条件的数据筛选出来，上面的例子就是
  
  * 外连接：在内连接查询学生名和对应的班级时，没有班级/班级不存在的学生，和没有学生的班级会被过滤掉，而外连接则是也会查出来：
    
    又分为左外连接、右外连接，满外连接（也叫全外连接），一般提到要查询'所有'就可能是外连接，再再根据情况选择哪种外连接。
    
    以下实现全外连接的SQL是错的，原因见避免笛卡尔积的技巧：
    
    ```
    /*
    SELECT students.name, classes.name 
    FROM students, classes 
    WHERE 
      students.class_id = classes.id 
      OR students.class_id IS NULL 
      OR classes.id IS NULL;
    */
    ```
    
    想要实现外连接，需要join on 和 union。还有一种使用(+)，但是MySQL不支持。

#### 1.4.2 join on 和 union

多表查询的另一种写法，SQL99标准推出。

多个如 join...on...join...on，也可以写成join...join...on...on，但不建议这么写因为可读性查。

等值连接，非自连接，内连接：

```
/*
SELECT students.name, classes.name 
FROM students, classes 
WHERE students.class_id = classes.id;
*/

SELECT students.name, classes.name 
FROM students 
JOIN classes ON students.class_id = classes.id;
```

非等值连接：

```
/*
SELECT t1.name, t2.lv 
FROM students AS t1, scope AS t2 
WHERE t1.result BETWEEN t2.low AND t2.high;
*/

SELECT t1.name, t2.lv 
FROM students AS t1 
JOIN scope AS t2 ON t1.result BETWEEN t2.low AND t2.high;
```

自连接：

```
/*
SELECT t1.name, t2.name 
FROM students AS t1, students AS t2 
WHERE t1.heedman_id = t2.id;
*/

SELECT t1.name, t2.name 
FROM students AS t1 
JOIN students AS t2 ON t1.heedman_id = t2.id;
```

外连接：

```
SELECT students.name, classes.name 
FROM students 
  /* 内连接，不加默认就是INNER 
  INNER JOIN classes ON students.class_id = classes.id; 
  */
  /* 左外连接，OUTER可以省略 */ 
  LEFT OUTER JOIN classes ON students.class_id = classes.id; 

  /* 右外连接，OUTER可以省略 
  RIGHT OUTER JOIN classes ON students.class_id = classes.id; 
  */
  /*全外连接，MySQL不支持，OUTER可以省略 */
  FULL OUTER JOIN classes ON students.class_id = classes.id;
  */
```

MySQL不支持full，可以用union代替：

union用来合并多条select的查询结果组成新的结果集（取并集），合并时两个表的列数和数据类型必须相同：

有 union 和 union all，比如说xxx表中又80条数据，25 < age < 30 的有10条数据：

* union：单纯像数学上的取并集，去掉重复数据，{1,2} 并 {2,3} = {1,2,3}
  
  ```
  SELECT * FROM xxx WHERE age > 25 
  UNION 
  SELECT * FROM xxx WHERE age < 30;
  
  # 等价于下面，这条SQL作用就是查出所有80条数据
  SELECT * FROM xxx WHERE age > 25 OR age < 30;
  ```

* union all：与数学上并集不同的是，不会删除重复数据  {1,2} 并 {2,3} = {1,2,2,3}
  
  ```
  SELECT * FROM xxx WHERE age > 25 
  UNION ALL 
  SELECT * FROM xxx WHERE age < 30;
  ```

如果业务使用union和union all的结果一样，则尽量使用union all，避免查出重复的数据又删除，以提高查询性能。

结合union后，MySQL终于能实现全外连接了：

左外连接 union 右外连接去掉自连接

```
SELECT students.name, classes.name 
FROM students 
LEFT JOIN classes ON students.class_id = classes.id 
UNION ALL 
SELECT students.name, classes.name 
FROM students 
RIGHT JOIN classes ON students.class_id = classes.id 
WHERE students.class_id IS NULL;
```

#### 1.4.3 其他

（1）自然连接

自动匹配各个表相同字段，如果各个表不止一个字段相同也会and匹配，由于情况比较局限，不常用：

```
/*
SELECT * 
FROM t1, t2 
WHERE t1.bid = t2.bid;
*/

SELECT * 
FROM t1 NATURAL JOIN t2;
```

（2）using

简化内连接，仅限于下面情况，不常用：

```
/*
SELECT * 
FROM t1 
JOIN t2 ON t1.bid = t2.bid;
*/

SELECT * 
FROM t1 
JOIN t2 USING (bid);
```

### 4.5 流程控制

IF()：

```
SELECT IF(age >= 35, '中年危机', '还年轻') FROM xxx;
```

IFNULL()：

```
SELECT IFNULL(age, '空') FROM xxx;
```

case when...than...when...than...else end，其实就是if...else if...else：

```
SELECT 
  name, 
  CASE 
    WHEN age >= 35 THEN 'A' 
    WHEN age >= 30 THEN 'B' 
    ELSE 'C' 
  END 
FROM xxx;
```

### 1.6 函数

#### 1.6.1 内置函数

SQL语法在不同数据库支持不同的情况很少，但是内置函数区别就很大了。这里只列举MySQL的，且常用的，其他看文档。

分类：

* 单行函数：只用一行数据（如四舍五入只需要这一行数据）

* 多行函数：要多行数据，也叫聚合函数或分组函数（如max需要所有行的数据）。

单行函数可以嵌套，但是多行函数不行（MySQL以后可能会支持，因为Oracle支持）。

使用函数时，列名会变为 函数(参数)，所以建议使用列别名：

```
 select SIGN(ABS(age)) as a from xxx;
```

##### 1.6.1.1 单行函数

（1）数值相关

| 函数                   | 功能                           |
| -------------------- | ---------------------------- |
| ABS(x)               | 求绝对值                         |
| SIGH(x)              | 返回正负号                        |
| CEIL(x) 或 CEILING(x) | >=x 的最小整数                    |
| FLOOR(x)             | <=x 的最大整数                    |
| LEAST(x1, x2...)     | 返回列表的最小值                     |
| GREATEST(x1, x2...)  | 返回列表的最大值                     |
| MOD(x, y)            | x % y                        |
| RAND()               | 0-1的随机数，其他随机数的计算规则和其他变成语言一样  |
| RAND(x)              | 0-1的随机数，x为种子值，x相同则随机数也相同     |
| ROUND(x)             | 四舍五入x，保留y位小数，y是负数就往整数那边走四舍五入 |
| TRUNCATE(x, y)       | x直接截断，保留y位小数，y是负数就往整数那边走变为0  |
| SORT(x)              | x的平方根，x为负数时返回NULL            |
| 三角函数                 | ...                          |
| 其他数学函数，进制转换函数        | ...                          |

（2）字符串相关

注意：字符串的索引从1开始，除了字符串其他地方还是0开始。

| 函数                        | 功能                                                                  |
| ------------------------- | ------------------------------------------------------------------- |
| ASCII(s)                  | 返回字符串第一个字符的ASCLL码                                                   |
| CHAR_LENGTH(s)            | 字符串的字符个数                                                            |
| LENGTH(s)                 | 字符串的总字节数                                                            |
| CONCAT(s1, s2...)         | 连接字符串                                                               |
| CONCAT_WS(str, s1, s2...) | concat基础上，用 str 连接                                                  |
| INSERT(s, idx, len, rs)   | 将字符串s，索引idx后len位替换为rs，如INSERT('hello', 2, 3, 'abcde') 结果为 'heabcde' |
| REPLACE(s, os, rs)        | 将字符串s中的os替换为rs                                                      |
| UPPER(s) 或 UCASE(s)       | 全部字符转大写                                                             |
| LOWER(s) 或 LCASE(s)       | 全部字符转小写                                                             |
| LEFT(s, n)                | s的前n个字符                                                             |
| RIGHT(s, n)               | s尾部n个字符                                                             |
| LPAD(s, len, pad)         | 左对齐，s最左边填充pad直到长度为len，如 LPAD('123', 5, '0') 结果为 '00123'             |
| RPAD(s, len, pad)         | 右对齐                                                                 |

（3）日期时间相关

太多了

（4）加密解密

| 函数                                    | 功能                |
| ------------------------------------- | ----------------- |
| PASSWORD(p)                           | 5.7可用，8.0已弃用      |
| MD5(p)                                | MD5加密，不可逆         |
| SHA(p)                                | SHA加密，比MD5还安全，不可逆 |
| ENCODE(p, p_seed)   DECODE(p, p_seed) | 5.7可用，8.0已弃用      |

（5）其他

| 函数                         | 功能                             |
| -------------------------- | ------------------------------ |
| FORMAT(x, n)               | 将 x 四舍五入，保留 n 位小数，若 x 为负数则视为0  |
| CONV(x, from, to)          | 将 x 从 from 进制转为 to 进制          |
| INET_ATON(ip)              | 将 IP 地址转为整数                    |
| INET_NTOA(ip)              | 将整数转为对应的 IP 地址                 |
| BENCHMARK(x, expr)         | 执行 expr（SQL语句） x 次，用来测试 SQL 性能 |
| CONVERY(x USING char_code) | 将 x 的字符集改成 char_code           |

##### 1.6.1.2 聚合函数与分组

常用的5个：max，min，avg，sum，count，其他看文档。

聚合函数都会忽略NULL，但是如果给聚合函数的数据全部是NULL的话，除了count会返回0，其他都返回NULL。

这里因为select中全是聚合函数没有其他字段，所以不需要group by。

```
SELECT 
  MAX(age), 
  MIN(age), 
  AVG(age), 
  SUM(age), 
  COUNT(age) 
FROM xxx;
```

如果count想要统计包括NULL：

```
SELECT 
  COUNT(*), 
  COUNT(NULL),   /* 可以是任意数据类型但非NULL的常熟 */
  COUNT(IFNULL(age, '空')) 
FROM xxx;
```

分组 group by：

虽然在select之前执行无法使用列别名，但是MySQL5.7之后做了扩展使得从group by开始可以使用列别名。

如city表为城市表，everyday表为年月日气温表

统计月均气温：

先按年分组，再按月分组，统计月均气温：

```
SELECT year, month, AVG(temperature) AS avg_temperature
FROM everyday
GROUP BY year, month;
```

统计深圳市的月均气温：

先按年分组，再按月分组，统计气温平均值：

```
SELECT 
  city.name, 
  everyday.year, 
  everyday.month, 
  AVG(everyday.temperature) AS avg_temperature 
FROM city 
JOIN everyday ON city.day_id = everyday.id AND city.name = 'Shenzhen' 
GROUP BY everyday.year, everyday.month;
```

注意：数据库中是不允许出现一行数据包含多条数据的，比如上面如果把分组条件everyday.month但还select everyday.month的话就会出现这种情况。

这里就顺便总结在group by还需不需要加某个字段：

* 看需求，要参与分组的字段如果where已经过滤使得字段只有一种值可以不加，否则加上。不如统计深圳市的年均气温，可以where过滤到只剩深圳再分组年，比分组城市和年再having过滤到只剩深圳这种性能高多了

* 再看看select，如果都是聚合函数，那肯定就没有其他字段了，就不加；如果有聚合函数外的字段，则必须加

with rollup：

在group by结果的基础上，增加n条对整个结果集的汇总行，n是分组的个数，如下会产生只有年分组和先年后月分组两个汇总行，汇总使用selqct中的聚合函数，如下是使用MAX：

```
SELECT year, month, MAX(temperature) 
FROM everyday 
GROUP BY year, month WITH ROLLUP;
```

注意：用了with rollup就不能用order by了，从语义上也不应该将圆数据和汇总数据一起排序。

having：

因为执行顺序 where-group by-having ，所以如果过滤的条件是使用聚合函数后的列，就只能使用having，也正是having执行比聚合函数晚所以才能使用聚合函数后的列。

注意因为列使用聚合函数后列名改变了，所以having的过滤条件就必须是 聚合函数(列) 或 列别名，

```
SELECT year, month, AVG(temperature) AS avg_temperature 
FROM everyday 
GROUP BY year, month HAVING AVG(temperature) < 10;  
/* 或者别名 HAVING avg_temperature < 10 */
```

having不一定要配合group by使用，没有group by 的having就和where一样了。

没有使用聚合函数的列，使用where和having都可以，在没使用group by时性能一样，但是建议使用where，因为where性能比having高，原因是如果where改用having的话在分组之前没有过滤，使得分组的性能大减，且分组之后还有过滤掉，得不偿失，。

#### 1.6.2 自定义函数

## 1.7 子查询

子查询也叫嵌套查询。

外层的叫外查询或主查询，内层的叫内查询或子查询，不过嵌套可能有很多层，所以内外是相对来说的。

子查询的性能比多表查询差，所以能不用子查询就能够实现的就不用子查询。

子查询不同情况：

* 角度1：结果集是单行还是多行
  
  * 单行子查询：子查询的结果集只有一行数据
  
  * 多行子查询：子查询的结果集只有多行数据

* 角度2：子查询是否被执行多次
  
  * 非相关查询：子查询执行局一次，返回一个常量或一个集合，主查询与这个常量/集合依次比较
  
  * 相关子查询：子查询使用主查询的字段，使得子查询的结果是动态的，每次主查询都与不同的子查询结果进行比较

规则：

* 子查询在主查询之前执行，因为子查询的结果是给主查询使用的

* 子查询用小括号包裹；子查询为了可读性，所以规范是放在条件的右边

* 子查询可以写在on/where/having，select，from，order by

* 单行子查询既可以用单行操作符（如比较操作符等），也可以用多行操作符（in，all，any，，some这四种）；而多行子查询必须用多行操作符，且in只能使用多行操作符，all，any/some在多行操作符基础上还要配合单行操作符

* 若单行子查询的结果集为空，返回NULL；若多行子查询结果为空，那么in，any/some结果也为空，而all返回主查询所有结果。

#### 1.7.1 单行 & 非相关

查询年龄比 ’Una‘ 大的人的信息：

```
SELECT name, age 
FROM xxx 
WHERE age > (SELECT age FROM xxx WHERE name = 'Una');
```

其实一些子查询也可以改写成其他实现，比如这个例子可以用自连接：

```
SELECT t2.name, t2.age  
FROM 
  xxx AS t1, 
  xxx AS t2 
WHERE t1.name = 'Una' and t2.age > t1.age;
```

但不是所有子查询都可以改写成其他实现。

如果想使用子查询返回的单行多条字段，如查找和 'Una' 年龄和性别相同的人的信息：

```
SELECT name, age 
FROM xxx 
WHERE age = (SELECT age FROM xxx  WHERE name = 'Una') 
  AND sex = (SELECT sex FROM xxx  WHERE name = 'Una');
```

这种多条字段都是相等的情况下也可以这么写，不过也仅限于这种情况了：

```
SELECT name, age, sex 
FROM xxx 
WHERE (age, sex) = (
  SELECT age, sex FROM xxx WHERE name = 'Una' 
);
```

### 1.7.2 多行子查询

也叫集合比较子查询。

使用in，all，any，some。

下面都是一些很没有意义的查询，只是为了展示多行子查询的用法而已。

（1）in

匹配多行子查询的多行数据，找出相等的：

```
SELECT * FROM xxx 
WHERE age IN (SELECT age FROM xxx WHERE age BETWEEN 21 AND 22);
```

in，all，any,some也可以给单行子查询用：

```
SELECT * FROM xxx 
WHERE age >= IN (SELECT age FROM xxx WHERE age = 22);
```



（2）all

与多行子查询的所有行进行比较，找到比所有行如更大更小的数据：

```
SELECT * FROM xxx 
WHERE age > ALL(SELECT age FROM xxx WHERE age BETWEEN 20 AND 30);
```

使用all时需要注意，因为涉及到和子串的所有结果比较，如果子查询结果集中有NULL，则不管怎么比较结果都是empty，any/some则不会：

```
/* 这里为了演示，故意给子查询多了一个NULL值得行，一执行结果为empty
SELECT * FROM xxx 
WHERE age < ALL (
  SELECT age FROM xxx WHERE name = 'Una' OR age IS NULL
);
*/

/* 正确做法 */
SELECT * FROM xxx 
WHERE age < ALL (
  SELECT age FROM xxx 
  WHERE (name = 'Una' OR age IS NULL) AND age IS NOT NULL
);
```



（3）any和some：

any和some一模一样。any更常用。

与多行子查询的所有行进行比较，找出只要比任一个行如更大更小的数据：

```
SELECT * FROM xxx 
WHERE age > ALL (SELECT age FROM xxx WHERE age BETWEEN 21 AND 22);
```

（4）找最值：

主查询中除了最大值，其他都有比子查询结果集某一个或一部分小的，在这个基础上加一个NOT就能得到最小值：

```
SELECT * FROM xxx 
WHERE age <= ALL (SELECT age FROM xxx WHERE age IS NOT NULL) order by age desc;
```

简单的查询用MIN()就行了，但是有一些最值问题是不能只用MIN()解决的。

以下是一个真实的场景：

找到深圳市年均气温最低的是哪一年。

由于目前MySQL不支持嵌套嵌套函数，不然就能直接用 MIN(AVG())了，所以现在处理起来比较麻烦。

方式一：最笨的办法，三重查询且代码非常冗余

```
SELECT 
  city.name, 
  everyday.year, 
  AVG(everyday.temperature) AS main_avg_temperature 
FROM city 
JOIN everyday ON city.day_id = everyday.id 
WHERE city.name = 'shenzhen' 
GROUP BY city.name, everyday.year 
HAVING main_avg_temperature = (
  SELECT MIN(avg_temperature) 
  FROM (
    SELECT AVG(everyday.temperature) as avg_temperature 
    FROM city 
    JOIN everyday ON city.day_id = everyday.id 
    WHERE city.name = 'shenzhen' 
    GROUP BY everyday.year
  ) AS avg_table
);
```

方式二：优化成二重查询

```
SELECT 
  city.name, 
  everyday.year, 
  AVG(everyday.temperature) AS main_avg_temperature 
FROM city 
JOIN everyday ON city.day_id = everyday.id 
WHERE city.name = 'shenzhen' 
GROUP BY city.name, everyday.year 
HAVING main_avg_temperature <= ALL (
  SELECT AVG(everyday.temperature) as avg_temperature 
  FROM city 
  JOIN everyday ON city.day_id = everyday.id 
  WHERE city.name = 'shenzhen' 
  GROUP BY everyday.year 
  HAVING avg_temperature IS NOT NULL
);
```

方式三：优化成二重查询，并较少代码冗余

```
SELECT name, year, MIN(avg_temperature) 
FROM (
  SELECT 
    city.name, 
    everyday.year, 
    AVG(everyday.temperature) as avg_temperature 
  FROM city 
  JOIN everyday ON city.day_id = everyday.id 
  WHERE city.name = 'shenzhen' 
  GROUP BY city.name, everyday.year 
) as avg_table 
GROUP BY name, year;
```



方式四：优化成不需要子查询

注意：虽然avg会忽略NULL，但如果avg的内容全是NULL的话就返回NULL，而排序时NULL有事最小值，所以需要过滤NULL：

```
SELECT 
  city.name, 
  everyday.year, 
  AVG(everyday.temperature) as avg_temperature 
FROM city 
JOIN everyday ON city.day_id = everyday.id 
WHERE city.name = 'shenzhen' 
GROUP BY city.name, everyday.year 
HAVING avg_temperature IS NOT NULL 
ORDER BY avg_temperature ASC 
limit 1;
```



#### 1.7.3 相关子查询

直接看例子：

有员工表和部门表，查询工资大于本部门平均工资的员工信息，分析得出主查询查员工信息，子查询查每个部门的平均工资且用主查询的部门id来找到本部门的平均工资：

```
SELECT * 
FROM employee 
WHERE salary > (
  SELECT AVG(department.salary) 
  FROM department 
  WHERE department.name = employee.department_name 
  GROUP BY department.name
)


```



其实也可以写成多表查询+非相关子查询：

```
SELECT e.* 
FROM employee e 
JOIN (
  SELECT d.name, AVG(d.salary) as avg_salary 
  FROM department d 
  GROUP BY d.name 
) dept_avg 
ON e.department_name = dept_avg.name 
WHERE e.salary > dept_avg.avg_salary; 


```

exists和not exists：

exists如果相关子查询有匹配结果返回true，否则返回false；not exists则反过来。

```
SELECT * 
FROM customers 
WHERE EXISTS (
  SELECT * 
  FROM orders 
  WHERE customers.customer_id = orders.customer_id
);


```



## 1.8 12种查询关键字的编写和执行顺序

编写顺序：

select-distinct-函数-from-join-on-where-group by-having-order by-limit-union

执行顺序：

from-on-join-where-group by-函数-having-select-distinct-order by-limit-union

注意：

* 没有列举出来的，如as，like等，是因为它们是在上述关键字各自内部执行的

* 虽然在select之前执行无法使用列别名，但是MySQL5.7之后做了扩展使得从group by开始可以使用列别名。

* on，where，having三者之间是and的关系。

* union，union all在所有的查询结束后才最后执行，合并所有结果集

## 2 创建

## 3 修改

## 4 删除

## 5 DDL和DCL

# 三、

缺：字符串部分函数，日期时间全部函数，聚合函数除了count的外连接，操作系统细微差异，mysql版本细微差异，不同数据库细微差异。
