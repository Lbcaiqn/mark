# 一、基本

关系型数据库：MySQL，oracle等
非关系型数据库（nosql）mongodb
mongodb是文档型数据库

一般在bin目录下创建 data/projectdb 作为数据库
启动数据库服务器：默认端口27017 可用 –port=端口号 指定端口
mongod --dbpath=数据库路径如…../bin/data/projectdb
启动客户端：
mongo  
可设置开机自启

## 2 数据库结构

结构：bjon（二进制的jison）存储数据。

mongodb以库-集合-文档/域 存储，对应mysql的 库-表-行/字段

文档对应json文件注意：数据库和集合不用手动创建，若没有而使用，会自动创建，反之，若文档/集合为空，则自动删除集合/数据库。

### 3 文档之间的关系

一对一：{a:对象啊ing}
一对多：{a:对象数组}
多对一：{a:对象数组}，同时数组的每个对象里有个id指向a
多对多：{a:对象数组}  同时数组的每个对象的id为一个数组。

### 4 客户端的shell命令

可使用es语法，但无法使用DOM BOM

```
show databases 或 show dbs
use dbname 进入指定数据库
db 打印当前所在数据库
show collections 打印当前数据库所有集合
```

# 二、CRUD

CRUD（create，read，update，delete，增查改删）操作：
注意：db相当于this
CRUD每个都有类似 …One()  …Many()方法

CRUD之前需要 use xxx 进入某个数据库

## 1 增

插入时会自动生成_id，类似mysql主键。若自己插入时有了_id 则不再生成。_

```
# 给集合插入文档，文档即json，可传入对象会自动加上双引号成json,若插入多个，则传入对象数组。
db.集合名.insert(文档) 

# 下面两个效果也一样，只是语义不同
db.集合名.insertOne() 
db.集合名.insertMany()
```

## 2 查

find()的查询结果默认按_id升序排序_

```
#返回该集合的所有内容，不需要传入参数
db.集合名.fund()

#也可以查询指定内容，可以传入查询文档，如下查询name为lgx且age为23的文档
db.集合名.find({
  name: 'lgx',
  age: 23
})

#查询出的结果过滤，只显示_id和name
db.集合名.find({
  name: 'lgx',
  age: 23
},{name: 1})

#只显示name不显示_id
db.集合名.find({
  name: 'lgx',
  age: 23
},{name: 1, _id; 0})
 

```

查询操作符

```
# $gt  查询 age > 18 的内容
db.集合名.find({
  age: {$gt > 18}
})
```



findOne()，与find()的区别在于findOne只返回第一个查询的结果，也可以传入参数

```
db.集合名.findOne() 
```

查询该集合的长度

```
db.集合名.count()
db.集合名.length()
```

排序和分页

```
# 先按age升序再按name降序
db.集合名.find().sort({age:1,name:-1})   

# 跳过m条数据，并展示前n条数据
# limit和skip和sort先后顺序无所谓，会自动调整
db.集合名.find().limit(n).skip(m)   
find().skip(m).limit(n)  


```

## 3 改

```
# 查询出name为'lgx'的第一个内容，并用{name: 'lgx',age: 23}替换掉
db.集合名.update({name: 'lgx'},{name: 'lgx',age: 23})

# 给查询出的文档修改/增加对象里面属性
db.集合名.update(查询,{$set: 对象})  


# 与update()的区别在于下面可以修改多个
db.集合名.updateMany()
db.集合名.update(xxx,yyy,{multi: true})
```

其他操作符

```
$unset    # 删除对应的属性，值可以随意

```



## 4 删

因为数据值钱，一般数据库的数据是不会删的，所以很少用删除，客户端的用户的数据删除了也不是真删，而是在数据中增加一个字段表示隐藏。

删除集合里面的文档

```
# 默认查询出的全部删除
db.集合名.remove(查询)，第二个参数true则只删除第一个
db.集合名.deleteMany(查询)

# 只删除查询出的第一条内容
db.集合名.remove(查询,true)
db.集合名.deleteOne(查询)

```

删除集合

```
# 推荐，直接删除该集合
db.集合名.drop()

# 不推荐，因为是一个一个文档删除，性能差
db.remove(0)
```



删除数据库

```
# 删除当前数据库
db.dropDatabase()
```

# 三、mongoose

node操作mongodb的一个第三方库

```
npm install --save mongoose
```

连接与断开数据库

```
const mongoose = require(‘mongoose’)
mongoose.conect(‘mongodb://localhost:27017/数据库名’,{useMongoClient: true})//连接数据库

//数据库一旦连接，除非终止程序则不会断开，也可以手动断开
mongoose.disconect() //断开数据库

//
mongoose.conection.once(‘open’,() => {})  


```


