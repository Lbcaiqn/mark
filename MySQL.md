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



# 三、
