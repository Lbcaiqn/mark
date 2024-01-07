## 一、基本

## 1 初始化

安装nest脚手架：

```
npm install -g @nestjs/cli
```

```
nest -v
```

创建nest项目：

```
nest new xxx
```

运行：

```
npm run start
```

运行并开启实时类型检查：

```
npm run start:dev
```

## 2 常用命令

帮助信息：

```
nest --help
```

生成模块：

生成一个模块，并且自动完成各种引入。

co是模块名，控制器的模块名就是co，其他模块名在帮助信息中查看

demo是文件夹名，如果没有就创建并创建文件，有就在该文件夹内创建文件

```
nest g co demo
nest g s demo
nest g mo demo
```

快速生成crud模板：

```
# resource 或 res
nest g resource xxx   
```

生成到指定目录下；

```
# 会生成在 /src/modules/ , 注意路径必须是nest规定的文件夹名，如modules
nest g res xxx modules
```

## 3 RESTful风格设计

RESTful不是什么硬性规定，只是一种api设计的风格。

（1）接口url

* 接口参数用 '/' 分开，而不是传统queryString的?形式
  
  ```
  //传统queryString
  https://xxx?id=1
  //RESTful风格
  https://xxx/1
  ```

* 一个url完成crud的业务，原理是通过请求类型来做crud

（2）接口版本控制

先要在main.ts中开启接口版本控制选项

```
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import {VersioningType} from '@nestjs/common';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  app.enableVersioning({
    type: VersioningType.URI //type接收VersioningType的枚举，URI最常用
  });
  await app.listen(3000);
}
bootstrap();
```

再在控制器中使用：

全部开启：

开启后，接口url就从 https://xxx/user 变成了 [https://xxx/v1/user](https://xxx/v1/user)

```
//原本
@Controller('user')

//修改后
@Controller({
  path: 'user',
  version: '1'
})
```

单个开启：

给需要的请求单独加上装饰器 @Version，这样只有这个请求需要加上 'v1'

```
import ...
import { Version } from '@nestjs/common';

@Controller('user')
export class UserController {
  @Get()
  @Version('1')
  findAll() {
    return 服务;
  }
}
```

（3）状态码规范

* 200：正常

* 304：Not Modified，协商缓存了

* 400：Bad Request，参数错误

* 401：Unauthonzed，token错误

* 403：Forbidden referer origin，验证失败，主要是防止跨站脚本攻击

* 404：Not Found，接口不存在

* 500：Internet Server Error，服务器错误

* 502：Bad Gateway，上游接口有问题或上游服务器错误

## 4 资源访问

设置静态文件夹：

```
//express
const app = express();
app.use(express.static("./public"));

//nest
// main.ts
import ...
import { NestExpressApplication } from '@nestjs/platform-express/interfaces';
import { join } from 'path';

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);
  //指定 /dist/aaa为静态文件夹
  app.useStaticAssets(join(__dirname, './aaa'))
  //也可以加一个虚拟路径前缀
  /*
  app.useStaticAssets(join(__dirname, './aaa'),{
    prefix: '/xxx'
  })
  */
  await app.listen(3000);
}
bootstrap();
```

（1）数据

直接以JSON格式返回数据库的数据

（2）图片

图片保存在静态资源文件夹，返回网络URL，若多次请求传的数据不同，且后端由这些数据产生的图片命名相同覆盖，则浏览器会缓存第一次返回的托片而无法获得新图片，解决：返回图片url时， 给url加上时间戳或随机数，使得每次返回的url都不同，就不会缓存了

## 二、模块、控制器与服务

一个nest项目分为若干个module，每个module通过若干controller提供各种service。

nest项目有一个主模块app，app引入子模块，而在main.ts中用app创建项目。

- module：模块，以 xxx.module.ts 命名

- controller：控制器，就是后端路由，以 xxx.controll;er.ts 命名

- service：服务，是具体的业务逻辑，以 xxx.service.ts 命名

main.ts 内容：

```
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import * as cors from 'cors';
import { NestExpressApplication } from '@nestjs/platform-express/interfaces';


async function bootstrap() {
  //泛型NestExpressApplication传不传都行，传了可以使app有类型提示
  const app = await NestFactory.create<NestExpressApplication>(AppModule);
  await app.listen(3000);
}
bootstrap();
```

## 1 模块

（1）基本使用

```
// xxx.module.ts
import ...

@Module({
  //引入子模块
  imports: [],

  //本模块的控制器
  controllers: [],

  //本模块的服务
  providers: [],
})
export class xxxModule {}
```

（2）共享模块

默认情况下，控制器只能使用此模块的服务。如果想使用其他模块的服务，可以将那个模块定义为共享模块，比如a模块要使用b模块的服务：

```
// b.module.ts
import ...

@Module({
  exports: [bService],
  //...
})
export class bModule {}
```

```
// a.module.ts 不用把bService放到providers里
// a.controller.ts
import ...

@Controller()
export class aController {
  constructor(
    //...
    private readonly bS: bService
  ) {}

  @Get()
  getHello(){
    return this.bS.service1();
  }
}
```

（3）全局模块：

和共享模块差不多：

```
// b.module.ts
import ...

@Global()
@Module({
  exports: [bService],
  providers: [bService]
  //...
})
export class bModule {}
```

```
// a.module.ts
import ...

@Module({
  imports: [bModule],
  //...
})
export class aModule {}
```

```
import ...

@Controller()
export class aController {
  constructor(
    //...
    private readonly bS: bService
  ) {}

  @Get()
  getHello() {
    return this.bS.service1();
  }
}
```

（4）动态模块：

可以传递参数的模块：

有很多应用场景，以下是与全局模块，服务的自定义值为例：

```
// b.module.ts
import { Module, Global } from '@nestjs/common';

@Global()
@Module({})
export class bModule {
  static func(num: number){
    return {
      module: bModule,
      exports: ['asd'],
      providers: [{
        provide: 'asd',
        useValue: 987 + num
      }],
    }
  }
}
```

```
// a.module.ts
import ...

@Module({
  imports: [bModule.func(1000)],
  //...
})
export class aModule {}
```

```
// a.controller.ts
import ...

@Controller()
export class aController {
  constructor(
    //...
    @Inject('asd') private readonly bS: number
  ) {}

  @Get()
  getHello() {
    return this.bS
  }
}
```

## 2 控制器

浏览器输入url访问是发送get请求，页面会直接输出get请求返回的信息。

### 2.1 基本使用

```
// xxx.controller.ts
import {
  Controller,
  Get,
  Request,
  Query,
  Param,
  Headers,
  Post,
  Body,
  Patch
  Delete,
} from "@nestjs/common";

@Controller("user")
export class UserController {
  constructor() {}

  /*
  @Get(),@Post()等这些装饰器可以再定义路径，如 @Get('/profile/:id')
  这样这条路由的url就是：服务器地址/user/profile/:id
  */
  @Get()
  ggg1(@Request() req, @Query() query, @Query('age') age, @Headers() headers) {
    //三种获取参数的方式
    console.log(req.query.age);
    console.log(query.age);
    console.log(age);
    //headers
    console.log(req.headers);
    console.log(headers);
    return {
      code: 200,
      meeeage: 'ok'
    };
  }

  //动态路由
  @Get(":id")
  ggg2(@Request() req){
    console.log(req.params.id);
    return {
      code: 200,
      messgae: 'ok'
    }
  }

  //套路一样，只是参数从body取
  //不用像express处理options请求了，应该是nest内部做了
  @Post()
  ppp(@Request() req, @Body() body){
    console.log(req.body)
    return {
      code: 200,
      message: 'ok'
    }
  }

  //套路都是一样的
  @Patch(":id")
  ppp(){}

  @Delete(":id")
  ddd(){}
}
```

总结：req的每个属性都有自己的装饰器如@Query()，可以直接取出来这些属性，且这些装饰器还可以传入参数再结构出来内部的属性。

### 2.2 CORS跨域

可以自己写响应头（参考node笔记），也可以用第三方库：

```
npm install --save cors @types/cors
```

```
// main.ts
import ...
import * as cors from 'cors';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  app.enableVersioning({
    type: VersioningType.URI //type接收VersioningType的枚举，URI最常用
  })

  //注意，跨域一定要放在所有use的最前面
  app.use(cors());
  await app.listen(3000);
}
bootstrap();
```

cors()也可以传递参数，比如cors这个库默认是不支持cookie跨域的，此时就需要在参数中允许cookie跨域：

```
app.use(cors({
  origin: true,
  credentials: true,
}));
```

### 2.3 中间件、守卫、拦截器、管道

执行顺序：中间件->守卫->管道->拦截器

#### 2.3.1 中间件

在路由之前做一些逻辑，

（1）基本使用

定义中间件：

```
// nest g mi DemoMiddleware
import { Injectable, NestMiddleware } from '@nestjs/common';
import {Request, Response, NextFunction} from 'express';

@Injectable()
export class MidMiddleware implements NestMiddleware {
  use(req: Request, res: Response, next: NextFunction) {
    console.log('hahaha');
    next();
  }
}
```

```
// xxx.module.ts
import ...

@Module({
  //...
})
export class AppModule implements NestModule {
  configure(consumer: MiddlewareConsumer){
    //方式一，本模块控制器的路由 forRoutes('/xxx')
    // consumer.apply(MidMiddleware).forRoutes('/xxx');

    //方式二，传入controller
    // consumer.apply(MidMiddleware).forRoutes(xxxController);

    //方式三，指定某个请求才能适应中间件
    // consumer.apply(MidMiddleware).forRoutes({path: '/xxx', method: RequestMethod.GET});


  }

}
```

（2）全局中间件

main.ts中定义，通常用来做白名单，cors等。

以下是拦截某些请求的例子：

```
// main.ts
import ...
import {Request, Response,NextFunction} from 'express';

const list = ['/user'];
function midAll(req: Request, res: Response, next: NextFunction){
  if(list.includes(req.originalUrl)){
    next();
  }
  else res.send('该接口不允许访问');
}

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  app.enableVersioning({
    type: VersioningType.URI //type接收VersioningType的枚举，URI最常用
  })
  app.use(midAll);
  await app.listen(3000);
}
bootstrap();
```

#### 2.3.2 守卫

用来做权限控制，jwt验证，访问控制等

返回ture就是通过，返回false就是不通过，不通过也可以直接抛出HttpError，这样可以自定义错误信息和状态码，如果是 return false 那状态码为 403。

如果在守卫使用了实体，则在每一个用到该守卫的控制器对应的module中都要引入该实体并在imports中用typeorm引用它。

canActivate 不能用async修饰，如果要是用异步的代码，可以 return 一个 Promise

```
// nest g gu xxx
// xxx.guard.ts
import { CanActivate, ExecutionContext, Injectable } from "@nestjs/common";
import { Observable } from "rxjs";
import { Request, Response, NextFunction } from "express";
import { Reflector } from "@nestjs/core";

@Injectable()
export class GuardGuard implements CanActivate {
  constructor(private reflector: Reflector) {}

  canActivate(
    context: ExecutionContext
  ): boolean | Promise<boolean> | Observable<boolean> {
    console.log("来了");
    const authority = this.reflector.get<string[]>(
      "role",
      context.getHandler()
    );
    console.log(authority); //['admin']

    //如果没有设置守卫，就直接通过
    if(!authority)  return true;

    const ctx = context.switchToHttp();
    const req = ctx.getRequest<Request>(),
          res = ctx.getResponse<Response>(),
          next = ctx.getNext<NextFunction>();

    //...token检验...

    //权限检验
    if (authority.includes(req.body.authority as string)) return true;
    else return false;
  }
}
```

局部使用：

```
// xxx.controller.ts
import { Controller, UseGuards,SetMetadata, Post } from '@nestjs/common';
import { GuardGuard } from './guard/guard.guard';

@Controller()
@UseGuards(GuardGuard)
//...
```

全局使用：（目前有错）

```
// main.ts
import ...
import { GuardGuard } from "./guard/guard.guard";
import { Reflector } from "@nestjs/core";

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);
  app.useGlobalGuards(new GuardGuard(new Reflector()))
  await app.listen(3000);
}
bootstrap();
```

无论是局部还是全局，如果某个路由要是用守卫，都要：

```
// xxx.controller.ts
import { Controller, UseGuards,SetMetadata, Post } from '@nestjs/common';
import { GuardGuard } from './guard/guard.guard';

@Controller()
@UseGuards(GuardGuard)   //全局就不用这一行
export class AppController {

  @Post()
  @SetMetadata('role',['admin'])
  xxx() {
    return 'ok';
  }
}
```

#### 2.3.3 管道

（1）管道转换

将前端传过来的参数进行类型转换，转换成uuid等：

```
//原来
// user.controller.ts
// http://localhost:3000/user/123
@Get(":id")
findOne(@Params('id') id: string){
  console.log(typeof id);  //string
  return {
    code: 200,
    messgae: 'ok'
  }
}

//管道转换
// user.controller.ts
// http://localhost:3000/user/123
// import { ParseIntPipe } from "@nestjs/common";
@Get(":id")
findOne(@Param('id', ParseIntPipe) id: number){
  console.log(typeof id);  //number
  return {
    code: 200,
    messgae: 'ok'
  }
}
```

（2）管道验证dto（Data  Transform Object）

前端虽然做了表单验证，但是仍然会有非法的途径将非法数据传给后端，所以后端也需要做验证：

```
npm install --save class-validator class-transformer
```

```
// login/dto/create-login.dto.ts
import { IsNotEmpty, IsOptional, IsNumber， Matches } from "class-validator";

export class CreateLoginDto {
  //没有做任何验证
  name: string;

  //使用class-validator，这里演示非空和限定类型为number
  @IsNotEmpty()
  @IsNumber()
  @Matches(/^.{3,20}$/, { message: '3到20个字符' })
  age: number

  // 定义可选参数
  @IsOptional()
  @IsNumber()
  @ApiProperty({ type: Number, example: 1 })
  quantity?: number;
}
```

如果是数组，对象的复杂数据：

```
import { IsNotEmpty, ArrayNotEmpty, IsString, IsNumber, IsObject, IsArray, ValidateNested } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger/dist';

class SalesAttrsDto {
  @IsNotEmpty()
  @IsString()
  @ApiProperty({ type: String, example: '分类' })
  name: string;

  @IsNotEmpty()
  @ArrayNotEmpty()
  @IsArray()
  @IsString({ each: true })
  values: Array<string>;
}

export class CreateGoodsSpuDto {
  @IsNotEmpty()
  @IsString()
  @ApiProperty({ type: String, example: '商品名' })
  goodsSpuName: string;

  @IsNotEmpty()
  @IsString()
  @ApiProperty({ type: String, example: 'https://xxx' })
  goodsSpuMainImg: string;

  @IsNotEmpty()
  @IsArray()
  @IsObject({ each: true })
  @ValidateNested({ each: true })
  @ApiProperty({ type: Array<SalesAttrsDto>, example: [{ name: '颜色', values: ['黑色', '红色'] }] })
  spuSalesAttrs: Array<SalesAttrsDto>;

  @IsNotEmpty()
  @IsArray()
  @IsString({ each: true })
  @ApiProperty({ type: Array<string>, example: ['https:/xxx', 'https://yyy'] })
  bannerImgList: Array<string>;

  @IsNotEmpty()
  @IsArray()
  @IsString({ each: true })
  @ApiProperty({ type: Array<string>, example: ['https:/xxx', 'https://yyy'] })
  detailImgList: Array<string>;

  @IsNotEmpty()
  @IsNumber()
  @ApiProperty({ type: Number, example: 1 })
  c1id: number;

  @IsNotEmpty()
  @IsNumber()
  @ApiProperty({ type: Number, example: 1 })
  c2id: number;

  @IsNotEmpty()
  @IsNumber()
  @ApiProperty({ type: Number, example: 1 })
  c3id: number;
}
```

方式一：

```
// login.controller.ts
import ...

@Controller('login')
export class LoginController {

  @Post()
  create(@Body(LoginPipe) createLoginDto: CreateLoginDto) {
    return 'ok';
  }
}
```

```
// nest g pi login
// login.pipe.ts
import {
  ArgumentMetadata,
  HttpException,
  HttpStatus,
  Injectable,
  PipeTransform,
} from "@nestjs/common";
import { plainToInstance } from "class-transformer";
import { validate } from "class-validator";

@Injectable()
export class LoginPipe implements PipeTransform {
  async transform(value: any, metadata: ArgumentMetadata) {
    //value是前端传的参数，metadata是这些参数的元信息如类型
    const DTO = plainToInstance(metadata.metatype, value);

    //fail是一个收集验证失败的数组，全部验证通过就是一个空数组
    const fail = await validate(DTO);
    if (fail.length) {
      // 枚举HttpStatus.BAD_REQUEST对应的状态码是400，表示参数错误
      throw new HttpException('表单验证不通过', HttpStatus.BAD_REQUEST);
    }
    return value;
  }
}
```

方式二，不用自己写pipe文件：

```
// login.controller.ts
@Post()
create(@Body() createLoginDto: CreateLoginDto) {
  return 'ok';
}
```

```
// main.ts
import ...
import {ValidationPipe} from '@nestjs/common'

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);
  app.useGlobalPipes(new ValidationPipe());
  await app.listen(3000);
}
bootstrap();
```

#### 2.3.4 响应拦截器，异常过滤器

（1）响应拦截器

可以拦截响应，并可以对响应结果做一些操作，比如：

```
// 某个控制器  返回 "HelloWorld"
@Get()
getHello() {
  return “HelloWorld”
}
// 现在想返回 {"data":“HelloWorld”,"status":200,"messgae":"666","sucess":true}，就需要用到响应拦截器
```

定义响应拦截器：

```
// /src/common/ResponseInterceptor.ts
import {
  Injectable,
  NestInterceptor,
  ExecutionContext,
  CallHandler,
} from "@nestjs/common";
import { map } from "rxjs/operators";
import { Observable } from "rxjs";

interface Data<T> {
  data: T;
}

@Injectable()
export class ResponseInterceptor<T> implements NestInterceptor {
  intercept(
    context: ExecutionContext,
    next: CallHandler<any>
  ): Observable<Data<T>> | Promise<Observable<Data<T>>> {
    return next.handle().pipe(
      map((data) => {
        return {
          data,
          status: 200,
          messgae: "请求成功",
          sucess: true,
        };
      })
    );
  }
}
```

使用：

```
// main.ts
import ...
import { ResponseInterceptor } from "./common/Response";

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);
  app.useGlobalInterceptors(new ResponseInterceptor());
  await app.listen(3000);
}
bootstrap();
```

（2）异常过滤器

当路由异常时生效，可以自定义一些异常信息

当发生错误时（站好不存在，密码错误，严惩吗错误等），后端需要返回异常，前端请求时try...catch...处理，先看看如何返回异常：

```
// xxx.service.ts
//import...
import { HttpException, HttpStatus } from '@nestjs/common';

export class XxxService {
  func(){
    //...  HttpStatus 是一个枚举，内容为状态码，下面的 BAD_REQUEST 状态码就是400
    if(密码错误)  throw new HttpException('密码错误', HttpStatus.BAD_REQUEST);
    //...
  }
}
```

然后就可以定义异常拦截器：

```
// /src/common/HttpFilter.ts
import {
  ExceptionFilter,
  Catch,
  ArgumentsHost,
  HttpException,
} from "@nestjs/common";
import { Request, Response, NextFunction } from "express";

@Catch()
export class HttpFilter implements ExceptionFilter {
  catch(exception: HttpException, host: ArgumentsHost) {
    // 如果是服务器自己语法逻辑错误，则直接return
    if (!exception.getStatus) {
      console.log(exception);
      return;
    }

    const ctx = host.switchToHttp();

    const req = ctx.getRequest<Request>(),
          res = ctx.getResponse<Response>(),
          next = ctx.getNext<NextFunction>();

    res.status(exception.getStatus()).json({
      sucess: false,
      time: new Date(),
      path: req.url,
      status: exception.getStatus(),
      errorMessage: exception.message
    })
  }
}
```

使用：

```
// main.ts
import ...
import { HttpFilter } from "./common/HttpFilter";

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);
  app.useGlobalFilters(new HttpFilter())
  await app.listen(3000);
}
bootstrap();
```

前端：

```
async func(){
  try {
    await 请求();
  } catch(err){
    console.log(err.response?.data?.errorMessage);  // 密码错误
  }
}
```

## 3 服务

有两点需要注意：

* return什么都可以，包括Promise，return一个Promise的话nest会做处理取出res并返回。

* 服务里的return或者其他地方如控制器的return最终都是解析为express的res.send()，所以也可以直接用res.send()代替return

（1）基本使用：

```
// xxx.service.ts
import { Injectable } from '@nestjs/common';

@Injectable()
export class xxxService {
  //各种crud服务
  service1(){
    return ...; 
  }
  service2(){
    return ...;  
  }
}
```

定义完服务后，在本模块中引入：

```
// xxx.module.ts
@Module({
  controllers: [xxxController],
  providers: [xxxService]
})
export class UserModule {}
```

然后，就可以在本模块中的控制器中使用：

```
// xxx.controller.ts
@Controller("user")
export class UserController {
  constructor(private readonly xxxService: xxxService) {}

  create(@Body() createUserDto: CreateUserDto) {
    return this.xxxService.service1();
  }
}
```

原理：基于IoC控制反转，以模块作为容器，将控制器和服务弄到容器里面，控制器中就可以直接使用服务，控制中不用new服务是因为nest内部处理了，所以直接在构造器中不需要new。

（2）自定义名称

其实上面的写法是简写，原本是这样的：

```
// xxx.module.ts
@Module({
  controllers: [xxxController],
  providers: [{
    provide: 'asd',
    useClass: xxxService
  }]
})
export class UserModule {}
```

```
// xxx.controller.ts
@Controller("user")
export class UserController {
  constructor(@Inject('asd') private readonly xxxService: xxxService) {}

  create(@Body() createUserDto: CreateUserDto) {
    return this.xxxService.service1();
  }
}
```

因此也可以自定义名称，不过一般用简写就好了，自定义名称没什么卵用。

（3）自定义值：

提供值给控制器使用

```
// xxx.module.ts
import ...

@Module({
  controllers: [xxxController],
  providers: [
    xxxService,
    {
      provide: 'list',
      useValue: ['red','grenn','blue']
    }
  ]
})
export class UserModule {}
```

```
// xxx.controller.ts
import ...

@Controller("user")
export class UserController {
  constructor(
    private readonly userService: UserService,
    @Inject('list') private readonly list: string[]  //类型是自定义值的类型
  ) {}

  @Get()
  findAll() {
    return this.list;  //['red','green','blue']
  }
}
```

（4）工厂模式

在自定义值得基础上，也可以自定义逻辑

```
// xxx.module.ts
import ...

@Module({
  controllers: [xxxController],
  providers: [
    xxxService,
    {
      provide: 'func',
      useFactory(){
        return 123;
      },
      /*也可以调用其他服务，yS也是自动new的
      inject: [yyyService],
      useFactory(yS: yyyService){
        console.log(yS.service1());
        return 123;
      }
      */
    }
  ]
})
export class UserModule {}
```

```
// xxx.controller.ts
import ...

@Controller("user")
export class UserController {
  constructor(
    private readonly userService: UserService,
    @Inject('func') private readonly num: number  //类型是工厂函数返回值的类型
  ) {}

  @Get()
  findAll() {
    return this.num;  //123
  }
}
```

注意：如果工厂函数用async修饰，虽然返回的是Promise，但nest内部做了处理简化了，使得在controller接收的时候类型直接是number而不是Promise，获取的值页直接是123。

## 4 自定义装饰器

基本使用：

```
// nest g d xxx
// xxx.decorator.ts
import { SetMetadata } from '@nestjs/common';
//SetMetadata注入的值可以用Reflector取出，详见守卫笔记。
export const xxx = (...args: string[]) => SetMetadata('xxx', args);
```

```
// xxx.conftroller.ts
@Post()
// @SetMetadata('role',['admin'])  //其实就等同于这一行
@MyD('admin')
```

参数装饰器：

使用就是 @xxx('id')  其实这就是@Req  @Param 等的实现原理。

```
import { createParamDecorator, ExecutionContext} from '@nestjs/common';
import {Request, Response, NextFunction} from 'express';

export const xxx = createParamDecorator((data: string, context: ExecutionContext) => {
  const ctx = context.switchToHttp();
  const req = ctx.getRequest<Request>(),
          res = ctx.getResponse<Response>(),
          next = ctx.getNext<NextFunction>();

  return req;

  //聚合装饰器，可以合成多个装饰器
  //return applyDecorators(xxx,yyy,zzz);
})
```

## 5 定时任务

在项目启动的时候可以启动定时任务。

如果是在服务中，直接使用setTimeout和setInterval即可。

```
npm install --save @nestjs/schedule
```

使用：

```
// app.task.service.ts

import { Injectable } from '@nestjs/common';
import { Cron, Interval, Timeout } from '@nestjs/schedule';

@Injectable()
export class AppTaskService {
  @Interval(5000) // 每隔 5 秒执行一次
  handleIntervalFunc() {
    console.log('定时任务正在执行...');
  }

  @Timeout(3000) // 3 秒后执行一次
  handleTimeoutFunc() {
    console.log('定时任务已触发！');
  }

  @Cron('0 0 * * *') // 每天 0 点触发
  handleCronFunc() {
    console.log('每天 0 点触发的定时任务正在执行...');
  }
}
```

```
// app.module.ts
import { Module } from '@nestjs/common';
import { ScheduleModule } from '@nestjs/schedule';
import { AppTaskService } from './app.task.service';

@Module({
  imports: [ScheduleModule.forRoot()],
  providers: [AppTaskService],
})
export class AppModule {}
```

## 三、连接数据库

CRUD：

* C（create）：给数据库增加新数据，对应post请求

* R（read）：读取数据库数据，对应get‘请求

* U（update）：修改数据库数据，对应patch请求或put请求或

* D（delete）：删除数据库数据，对应delete请求

数据库可视化工具：vscode插件Database Client，安装会会出现在左侧菜单栏。

nest链接mysql的库：

```
npm install --save @nestjs/typeorm typeorm mysql2
```

这里typeorm要操作什么数据库，就装对应的数据库操作的库，这里操作mysql就装了mysql2，之所以不是mysql，是因为mysql这个库是因为mysql8.0以上版本默认无法在代码里操作数据库，配置比较麻烦，所以直接装musql2。

## 1 初始化与定义实体

初始化：

```
// App.module.ts
import ...
import { TypeOrmModule } from "@nestjs/typeorm";

@Module({
  imports: [
    TypeOrmModule.forRoot({
      type: "mysql",
      username: "root",
      password: "123456",
      host: "localhost",
      port: 3306,
      database: "db001",         //要连接的数据库
      //entities: [__dirname + "/**/*.entity{.ts,.js}"], //正则匹配引入实体文件
      synchronize: true, //自动将实体同步成mysql表，生产环境不要用，开发环境可以用
      retryDelay: 500,           //重连数据库的时间间隔
      retryAttempts: 10,         //重连次数
      autoLoadEntities: true,    //自动加载实体
    }),
    //...
  ],
  controllers: [/*...*/],
  providers: [/*...*/],
})
export class AppModule {}
```

实体：

实体就是映射某一个table的类，类里面可以定义table的字段，在每个res文件下的entites/xxx.entities.ts中定义：

以下只列举最常用的装饰器和装饰器里的常用选项，更多见文档。

```
// xxx.entity.ts
import { timestamp } from "rxjs";
import {
  Entity,
  PrimaryGeneratedColumn,
  Column,
  Index,
  CreateDateColumn,
  Generated,
} from "typeorm";

enum sexEnum {
  unknown = 2,
  male = 1,
  female = 0,
}

@Entity()
// 多列唯一约束
// @Index('idx_unique_role_name_by_shop', ['shop_manager_role_name', 'shop_id'], { unique: true })
export class Db {
  @PrimaryGeneratedColumn()             //自动自增的主键
  // @PrimaryGeneratedColumn('uuid')    //自动自增的uuid主键
  id: number;

  @Column() //列
  username: string;

  @Column({
    select: false,            //select为false表示查询的时候忽略掉
    type: "varchar",         //数据类型
    length: 255,             //长度
    comment: "注释xxx",      //注释
    default: "123456",      //默认值，默认没有默认值
    nullable: false,        //不能为空，默认为false
  })
  password: string;

  @Column({
    unsigned: true       // 无符号，默认为false
  })
  age: number;

  @Column({
    unique: true       // 唯一约束，默认为false
  })
  email: string;

  @Column({                //枚举
    type: "enum",
    enum: sexEnum,
    default: 2,
  })
  sex: sexEnum;

  @Generated("uuid")
  uuid: string;

  @Column("json")             //存入取出时会自动JSON.stringify(),JSON.parse()
  j: { name: string; age: number }; 

  @CreateDateColumn({ type: "timestamp" })
  time: Date;

  @Column({
    type: 'timestamp',
    default: () => 'CURRENT_TIMESTAMP',
  })
  add_time: Date;

  @Column("simple-array")
  hobbits: string[];

  @Column("simple-json")             //存入取出时会自动JSON.stringify(),JSON.parse()
  jjj: { name: string; age: number };    
}
```

注意，数据库中的数据类型和ts中的类型对应关系：

* bigint，decimal在ts中定义为string（查询出来这两个其实也是string），其他的整数，小数在ts定义为number

* char，text等都是string

* 日期时间是Date，json是JSON，二进制类型是Buffer

引入实体：

引入实体后，数据库会创建对应的table；

typeorm初始化的配置synchronize设为true后，每次修改实体代码，也会修改对应的table内容，没有表则会根据实体来创建，所以在开发环境为了方便可以开启，但是成产环境一定要把它关了。

引入的方式有三种：

* App.module.ts中引入各个实体文件再塞进typeorm初始化里（不推荐）

* typeorm初始化里正则匹配找entities文件（不推荐）

* 如果不是nest项目而是普通的node项目，那只能用上面两种方法，但如果是nest项目就可以有更好的方式，即自动加载：
  
  ```
  /* 注意
  * 本模块的所有实体都需要引入
  * 若本模块需要关联查询时，关联的其他模块的实体不需要引入
  * 若本模块需要对其他模块的实体CRUD时，或不能通过关联查询查出来时，就需要引入其他模块的实体
  */
  // xxx.module.ts
  import ...
  import { TypeOrmModule } from '@nestjs/typeorm';
  import { xxx } from './entities/xxx.entity'
  
  @Module({
    imports: [TypeOrmModule.forFeature([xxx])],
    //...
  })
  export class xxxModule {}
  ```

## 2 关系

在进行多表查询时，除非是原生sql，否则表之间必须要有关联关系，如果没有关联关系的话多表查询不知道为什么查不出来。

关系：OneToOne，OneToMany，ManyToOne，ManyToMany

创建实体时如果不知道用什么关系，可以参考一下例子：

* 一对一：一个表的外键对应这个表的主键，如学生表中，学生的外键组长id对应组长的id，而组长也是学生，所以对应学生表的主键

* 一对多，多对一：一个表的外键对应另一个表的主键，如学生表-班级表中，学生表的外键对应班级表的主键。一个班级对应多个学生，且学生只能在一个班级

* 多对多：a表的外键对应b表的主键，且b表的外键也对应a表的主键，如学生表-课程表，学生表的外键课程id对应课程表的主键，课程表的外键学生id对应学生的主键，一个学生可以有多个课程，一个课程也可以有多个不同的学生

总之，判断关系就以它们的主键外键为依据就好了，而不要以对应关系去判断，这样容易误判，比如一对一关系的学生表是不是也可以理解为一个组长对应多个学生，然后就误判了。

或者也可以用归属关系来判断，比如a一对多b，b多对一a，那么一个a就可以有多个b，但一个b只属于一个a；又比如a多对多b，那么一个a有多个b，一个b也可以属于多个a的。

创建关系后，从表表明关系的字段会同步主表主键的数据类型和unsigned，但是约束不会，所以约束需要定义。

例：一个user表，有外键tag，对应tag表的多条数据（一对多关系）：

```
// user.entity.ts  主表
import { Entity, PrimaryGeneratedColumn, Column, OneToMany } from 'typeorm';
import { Tag } from './tag.entity';

@Entity()
export class User {

  @PrimaryGeneratedColumn()
  id: number;

  @Column()
  name: string;

  @Column()
  desc: string;

  //一个user对应多个tag，外键关联tag表的字段user
  @OneToMany(() => Tag, t => t.user)
  tag: Tag[]
}
```

```
// tag.entity.ts  从表
import { Entity, PrimaryGeneratedColumn, Column, ManyToOne, Index } from "typeorm";
import { User } from './user.entity'

@Entity()
export class Tag {

  @PrimaryGeneratedColumn()
  id: number;

  @Column()
  tagName: string;

  //创建外键，外键的字段没有指定，会根据typeorm默认的规则起字段名，这里字段名应该会是user_id
  @ManyToOne(() => User)
  user: User

  /* //创建外键，同时自定义外检字段名
  @ManyToOne(() => User)
  @JoinColumn({ name: 'user_id' })
  user: User
  */

  /* 不创建外键，同时自定义外检字段名
  @ManyToOne(() => User, { createForeignKeyConstraints: false })
  @JoinColumn({ name: 'user_id' })
  user: User
  */

  /* 不创建外键，同时自定义外检字段名,并创建索引
  @Index()
  @ManyToOne(() => User, { createForeignKeyConstraints: false })
  @JoinColumn({ name: 'user_id' })
  user: User
  */

  /* 不创建外键，同时自定义外检字段名,并创建索引，同时满足想在查询的时候有只要user_id，不要user表数据的需求
  @Index()  
  @Column()
  user_id: number;

  @ManyToOne(() => User, { createForeignKeyConstraints: false })
  @JoinColumn({ name: 'user_id' })
  user: User
  */
}
```

```
// user.module.ts
import { ...
import { User } from './entities/user.entity';
import { Tag } from './entities/tag.entity';
import { TypeOrmModule } from '@nestjs/typeorm';

@Module({
  imports: [TypeOrmModule.forFeature([User, Tag])],
  //...
})
export class UserModule {}
```

注意，若没有创建外键

* 从表插入数据，或修改关联字段时，就需要自行判断主表主键是否存在该id

* 主表删除数据时，要一并删除从表对应的数据

自连接也可以是一对多-多对一关系：

```
@ManyToOne(() => Category, { createForeignKeyConstraints: false })
@JoinColumn({ name: 'cat_pid' })
parent: Category;

@OneToMany(() => Category, cat => cat.parent)
children: Category[];
```

多对多关系，则在两个实体是：

JoinTable()会生成一个中间表，如果要用repository，则JoinTable是必须的。

a多对多b关系其实就是a一对多c和c多对一b的结合

```
@ManyToOne(() => Shopcart, { createForeignKeyConstraints: false })
@JoinTable({name: 'user_mtm_shopcart'})  
shopcart: Shopcart[]
```

```
@ManyToOne(() => User, { createForeignKeyConstraints: false })
@JoinTable({name: 'user_mtm_shopcart'})  
user: User[]
```

一对一关系，则在两个表中：

```
@OneToOne(() => User, { createForeignKeyConstraints: false })
@JoinColumn({ name: 'user_id' })
user: User;
```

```
@OneToOne(() => UserDetailInfo, udi => udi.user)
userDetailInfo: UserDetailInfo;
```

## 3 CRUD操作

find()需要注意，多表查询的各表之间的实体必须有关联关系。

where需要注意，字段数据类型必须和实体定义的数据类型的一样。

save()若数据库没有已存在的数据就会新添一条数据；如果已存在则是修改这条数据.

例：数据库有一个user表（字段有id、name、desc，tag）和一个tag表（字段有id，tagName，user），一个user对应多个tag。对其进行crud操作（typeorm的api返回的都是Promise）：

```
// user.service.ts
import { Injectable } from "@nestjs/common";
import { InjectRepository } from "@nestjs/typeorm";
import { Repository, Like } from "typeorm";
import { User } from "./entities/user.entity";
import { Tag } from "./entities/tag.entity";
import { CreateUserDto } from "./dto/create-user.dto";
import { UpdateUserDto } from "./dto/update-user.dto";

@Injectable()
export class UserService {

  constructor(
    @InjectRepository(User) private readonly userTable: Repository<User>,
    @InjectRepository(Tag) private readonly tagTable: Repository<Tag>
  ) {}

  create(createUserDto: CreateUserDto) {
    const data = new User();
    data.name = createUserDto.name;
    data.desc = createUserDto.desc;

  await this.userTable.save(data)

  /* save也会返回新数据，通常是获取自增的新id
  const newUser = await this.userTable.save(data)
  console.log(newUser.id)
  */
    return ‘ok’;
  }

  //tag也可以定义dto，这里为了方便就不弄了
  async addTag(id: number, tags: string[]) {
    const who = await this.userTable.findOne({ where: { id } });

    //无论是方式一还是方式二，由于表之间有关联关系，一个表插入数据会使得另一个表对应的也插入数据
    // 推荐用方式一，简单，同事修改，删除也只能用方式一
    // 方式一
    for (let i of tags) {
      const t = new Tag();
      t.tagName = i;
      t.user = who;
      await this.tagTable.save(t);
    }

   /* 方式二，不推荐
   const tagsArr: Tag[] = [];
   for (let i of tags) {
      const t = new Tag();
      t.tagName = i;
      tagsArr.push(t);
    }
    who.tag = tagsArr;
    this.userTable.save(who);
   */

  /* 注意，如果两张表大都是要插入新new的数据，则方式一和方式二都要用，save两张表
     而且必须先save主表，主表只需要先save一次即可，后续主表就不用save了，只需要tags
     把user关联上就好
   const user = new User();
   user.name = 'xxx';
   user.desc = 'yyy';
   await this.userTable.save(user);

   for (let i of tags) {
      const t = new Tag();
      t.tagName = i;
      t.user = user;     // 关联上user
      this.tagTable.save(t); 
    }
   */
    return 'ok';
  }

  async findAll(page, pageSize, keyword) {
    let data: any = [];

    // 查找该表信息 fin()不带任何参数就是查询全部信息
    if (!keyword) {
      //如果没有关键词就查找全部并分页、排序
      data = await this.userTable.findAndCount({
        // 一并查询外键tag，不加的话是不会查外键的
        /*
        如果关联的表内还关联这其他表，也可以查出来，如：
        relations: ["tag", "tag.xxx"],
        */
        relations: ["tag"],
        // skip 和 take 实现分页，order 实现排序
        skip: (page - 1) * pageSize,
        take: pageSize,
        order: {
          //按id降序排序
          id: "DESC",
        },
      });

    }
    else {
      //如果有关键词，就按关键词进行模糊匹配查询，并分页、排序
      data = await this.userTable.findAndCount({
        where: {
          name: Like(`%${keyword}%`),
        },
        skip: (page - 1) * pageSize,
        take: pageSize,
        order: {
          id: "DESC",
        },
      });

    }
    return {
      data: data[0],
      total: data[1],
    };
  }

  update(id: number, updateUserDto: UpdateUserDto) {
    /* 注意，update的第二个参数不能包含关系的数据，如果有先要delete掉
    比如下面的data瑞国包含了关系数据
    const newUser = await this.userTable.save(data)
    delete newUser.xxx

    尤其常见于更新多对多关系的数据时中，因为多对多关系没有字段来关联另一个表，只能通过
    关系数据进行更新，此时update就不能用了，不过可以用 save 代替，因为 save 如果是
    同一行数据它会进行update
    */
    return this.userTable.update(id, updateUserDto);
  }

  remove(id: number) {
    return this.userTable.delete(id);
  }
}
```

也可以直接写sql语句，但是不太方便，就不用了：

```
let res = await this.GoodsAttributeRepository.query(
      `
    SELECT *
    FROM goods_attribute
    INNER JOIN attribute ON attribute._id = goods_attribute.attr_id
    WHERE goods_attribute.goods_spu_id = ?
  `,
  [12345]
);
```

也可以写成类似sql形式的函数调用，不过缺陷是和 find() 一样无法进行没有关联关系的多表查询，必须有关联关系的才行：

getOne，getMany返回Promise，其他不是。

```
async getTags() {
  const data = await this.userRepository
    .createQueryBuilder('user')  // user表别名
    .innerJoinAndSelect('user.tag', 'tag表别名')
    .where('user._id = :id', { id: 12345 })
    /* 也可以用模板字符串，但是有问题，比如 '123' 会匹配出 '000123' 等结果，须慎用
    .where(`user._id = ${变量}`)
    */
    /* 如果有多个where条件，可以写在一个where里，也可以使用andWhere，
    但不管是那种，冒号后面的变量都不能重复
    .andWhere()
    */
    .offset(0)
    .limit(30)   // 相当于 limit 0 30
    .getMany();
  console.log(data);
  return data;
}
```

使用 IN 时需要注意，如果数组是空数组的话实惠报错的，所以需要判断数组是否为空，不为空才能继续查询：

```
const ids = [1,4,8];
if(dis.length !== 0){
  const data = 
  //...
  .where(`_id IN (${updateInfo.roleIds})`)
  //...
} else {
   const data = xxx  // 数组为空时，根据情况给结果，如null, []
}
```

注意事项：

* 自增列在save时如果没有给值，会自动自增，但是必须注意每一次save的对象的引用必须是不同的，比如一次需要save多次则需要特别注意每次都要new一次，不然的话每次引用都是同一个，列就不会自增，就使得自增列相同，进而使得插入变成修改

* 如果需要一次save大量的数据如成千上万条，那么一条一条save是非常慢的，此时可以将数据放到数组里，将数组save进去；不过要注意如果数组的数据量太大是会save失败报错的，所以如果报错的话，就将数组分为几个小数组，再一次save

# 四、接口文档

接口文档是自动生成的。

```
npm install --save @nestjs/swagger swagger-ui-express
```

如果安装失败，就删掉node_modules，然后用pnpm安装。

初始化：

```
// main.ts
import { NestFactory } from "@nestjs/core";
import { AppModule } from "./app.module";
import { NestExpressApplication } from "@nestjs/platform-express/interfaces";

import { SwaggerModule, DocumentBuilder } from "@nestjs/swagger";

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);

  // http://localhost:3000/api-docs#
  const options = new DocumentBuilder()
                  .addBearerAuth()
                  .setTitle("我的接口文档")
                  .setDescription("我的描述")
                  .setVersion("1")
                  .build();
  const docs = SwaggerModule.createDocument(app, options);
  SwaggerModule.setup("/api-docs", app, docs);

  await app.listen(3000);
}
bootstrap();
```

给接口文档添加各种描述：

```
// xxx.controller.ts
import { Controller, Get, Post, Body, Patch, Param, Delete } from '@nestjs/common';
import { LoginService } from './login.service';
import { CreateLoginDto } from './dto/create-login.dto';
import { UpdateLoginDto } from './dto/update-login.dto';
import { ApiTags, ApiOperation, ApiParam, ApiQuery, ApiResponse, ApiBearerAuth } from '@nestjs/swagger';

@Controller('login')
@ApiTags('登录接口')
@ApiBearerAuth()
export class LoginController {
  constructor(private readonly loginService: LoginService) {}

  @Post()
  @ApiOperation({summary: "某个post接口", description: '描述xxx'})
  @ApiResponse({status: 403, description: '参数错误'})
  create(@Body() createLoginDto: CreateLoginDto) {
    return 'ok';
  }

  @Get()
  @ApiOperation({summary: "某个get接口", description: '描述xxx'})
  @ApiQuery({name: 'username', type: String, description: '用户名'})
  @ApiQuery({name: 'password', type: String, description: '密码'})
  @ApiResponse({status: 403, description: '参数错误'})
  findAll() {
    return this.loginService.findAll();
  }

  @Get(':id')
  @ApiOperation({summary: "某个get接口", description: '描述xxx'})
  @ApiParam({name: 'id', description: '这是一个必传的动态参数id', required: true, type: 'string'})
  @ApiResponse({status: 403, description: '参数错误'})
  findOne(@Param('id') id: string) {
    return this.loginService.findOne(+id);
  }
}
```

```
// xxx.dto.ts
import { ApiProperty } from "@nestjs/swagger/dist";

export class CreateLoginDto {
  @ApiProperty({ type: String, example: 'lgx' })
  name: string;

  @ApiProperty({ type: Number, example: 24 })
  age: number;
}
```

还有很多Apixxx，每个Apixxx也有很多参数，详见文档，这里只列举最常用的。

# 五、注册登录/鉴权/权限控制

首先需要知道cookie，WebStorage，session，token的区别于联系。

（1）cookie与WebStorage

cookie和WebStorage都是浏览器用来存储数据的，但是目前存储数据一般都是用JTML5新出的WebStorage，比起大小只有4K的cookie空间大得多，而且更重要的一点是，cookie会放在网络请求的请求头中传输，显得臃肿。更多区别见HTML5笔记。

cookie之所以在请求时会被放在请求头中，是因为早期的Web的鉴权方式是通过session实现的，而session需要配合cookie使用。

（2）session与token

web应用是基于http协议的，而http协议是无状态的，前端与后端交互一次就建立一个连接，交互完就（如关掉网页或浏览器）就会断开连接。在下一次前后端交互的时候，后端就不知道这个请求是谁发过来的了，这样就使得鉴权难以实现。

session是官方标准中的一种解决方案，原理是在第一次前后端交互的时候，后端为这个客户端生成一个唯一的sessionid存储到后端服务器内存中，这个sessionid在响应的时候放在cookie中返回给前端，前端就保存这个存放sessionid的cookie，在以后的请求中就把携带sessionid的cookie传给后端，后端就能识别是哪个前端了。

但是session有很多缺点，如：

* sessionid存储在后端服务器的内存中，当有大量用户进行交互，就有可能内存达到上限；而且如果这个web应用是用多台服务器假设的，sessionid只存在于一台服务器的内存中又很难在多台服务器中使用，即使用一台专门的服务器存储sessionid也有这台服务器单点故障的风险；如果是假设集群服务器成本又很高

* session需要配合cookie，像小程序、app这些就无法使用了

于是，民间就诞生了token，token也是目前最常用的解决方案，原理是第一次交互的时候，后端用一些能标识用户的字段（如数据库中的用户id）加上私钥通过某种算法生成一个token，将这个token返回给前端，前端可以把token存到WebStorage或者其他平台的存储载体中，以后的请求中吧token放到请求头中，后端拿到token通过私钥解析出id就可以了，这样后端服务器只需要保存一份私钥即可。

jwt（jsonwebtoken）是token的一种最常用的实现。

session和token的用途主要是两种：

* 身份验证（登录）和鉴权

* 数据传输

下面的例子就以通过jwt实现注册登录鉴权，以session实现验证码的验证为例。

## 1 注册与登录

### 1.1 账号密码的注册登录

（1）后端

因为这里只是示例，所以省略了管道验证和拦截器。

后端需要定义用户的表，账号限制唯一username，密码需要bcrypt加密。

需要的第三方库：

```
npm install --save bcryptjs
npm install --save express-session @types/express-session
npm install --save svg-captcha
npm install --save jsonwebtoken @types/jsonwebtoken
```

用session实现验证码的验证前，需要use一下：

```
// main.ts
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import * as cors from 'cors';
import * as session from 'express-session';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);
  //跨域，cookie的跨域需要参数里单独设置
  app.use(
    cors({
      origin: true,
      credentials: true,
    }),
  );
  //use后，每次交互时若此前端没有sessionid则会生成sessionid
  app.use(
    session({
      secret: 'asjlfhuig4145646g5sr4g65', //私钥
      rolling: true, //true每次请求后设置session会重新计时session过期时间
      name: 'cookiename', //session的name
      cookie: {
        maxAge: 3 * 60 * 1000, //过期时间，单位毫秒，如果是负数或null则是一次性的
      },
    }),
  );
  await app.listen(3000);
}
bootstrap();
```

实体定义：

```
// user.entity.ts
import { Entity, Column, PrimaryGeneratedColumn } from 'typeorm';

@Entity()
export class User {
  @PrimaryGeneratedColumn()
  id: number;

  //用户名限制唯一且非空
  @Column({
    unique: true,
    nullable: false,
  })
  username: string;

  //密码要加密、限制非空，查询时禁止查出密码
  //bcryptjs加密的密文长度是60，所以varchar必须 >= 60
  @Column({
    type: 'varchar',
    length: 100,
    nullable: false,
    select: false
  })
  password: string;
}
```

注册登录路由以及验证码验证：

先判断账号是否存在，再匹配密码，匹配成功返回jwt（jsonwebtoken），用于鉴权。

登录不要用get请求，因为账号密码会暴露在url，所以用post请求.

```
// user.controller.ts
import {
  Controller,
  UseGuards,
  Get,
  Post,
  Body,
  Req,
  Res,
} from '@nestjs/common';
import { UserService } from './user.service';
import { RegisterDto } from './dto/register.dto';

@Controller('user')
export class UserController {

  constructor(private readonly userService: UserService) {}

  @Post('/register')
  create(@Req() req, @Body() registerDto: RegisterDto) {
    return this.userService.register(req.session.code,registerDto);
  }

  @Post('/login')
  login(@Req() req, @Body() userInfo) {
    return this.userService.login(req.session.code, userInfo);
  }

  @Get('/code')
  createCode(@Req() req, @Res() res) {
    return this.userService.createCode(req, res);
  }
}
```

```
// user.service.ts
import { Injectable } from '@nestjs/common';
import { Request, Response } from 'express';
import { RegisterDto } from './dto/register.dto';
import { User } from './entities/user.entity';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository, Like } from 'typeorm';
import { sign } from 'jsonwebtoken';
import * as svgCaptcha from 'svg-captcha';
import * as bcrypt from 'bcryptjs';

//私钥为了安全一般是不可见的，保存在本地文件中，不存放于git，这里为了方便就直接定义为了变量
const SECRCT = 'asf34g35s1g56erssa';

@Injectable()
export class UserService {

  constructor(
    @InjectRepository(User)
    private readonly userTable: Repository<User>,
  ) {}

  async register(code: string, registerInfo: RegisterDto) {
    if (code !== registerInfo.code) return '验证码错误';

    const user = new User();
    user.user_name = registerInfo.user_name;
    user.user_icon = '';
    user.user_account = registerInfo.user_account;
    user.user_password = await bcrypt.hash(registerInfo.user_password, 10);

    let newUser: User | null = null;
    try {
      newUser = await this.userRepository.save(user);
    } catch (err) {
      return '账号已存在';
    }

    const jwt = sign(
      {
        _id: newUser._id,
      },
      SECRCT,
      { expiresIn: 60 * 60 * 24 }    // 过期时间， 单位（秒）
    );

    delete newUser.user_password;

    return {
      message: '注册成功',
      jwt,
      newUser,
    };
  }

  async login(code: string, userInfo: any) {
    if (code !== userInfo.code) return '验证码错误';

    const user = await this.userRepository
      .createQueryBuilder('user')
      .addSelect('user.password')   // addSelect就算只查询一个表，也要加表名
      .where('username = :un', { un: loginInfo.username })
      .getOne();

    if (!user) return '用户名不存在';

    const valid = await bcrypt.compare(loginInfo.password, user.password);

    if (!valid) return '密码错误';

    const token = sign(
      {
        id: user.id,
      },
      SECRCT, 
      { expiresIn: 60 * 60 * 24 }    // 过期时间， 单位（秒）
    );

    delete user.password;

    return {
      message: '登录成功',
      token,
      user,
    };
  }

  //req的类型不能限定为Request，否则session注入不进去
  createCode(req: any, res: Response) {
    const code = svgCaptcha.create({
      size: 4,
      fontSize: 50,
      width: 100,
      height: 34,
      background: '#cc9966',
    });

    // 将这个code放到session中，下次请求就可以 req.session 解析出来
    req.session.code = code.text;

    /* 
    直接返回svg标签，前端可以v-html
    或直接直接 <img src="http://localhost:3000/user/code/" + '?time=' + new Date() 加上时间戳是为了防止浏览器缓存而不重新发请求 
    */
    // 也可以返回其他形式，如url等
    res.type('image/svg+xml');
    res.send(code.data);
  }
}
```

（2）前端

注册的表单验证和请求略。

拿验证码请求略。

登录拿token，因为后端用session实现了验证码的验证，所以这里就需要在请求头上戴上cookie：

```
//账号密码登录
axios({
  url: "http://localhost:3000/user/login",
  method: "post",
  data: {
    //账号，密码，验证码
  },
  //注册登录要验证码，就带上cookie
  withCredentials: true,
}).then(res => {
  console.log(res.data.token);
}).catch(//...);

//微信登录
wx.login();
```

拿到token后，将token存放到storage和vuex中

token作为登录凭证来保持持久登录，无需账号密码。

那既然都存到storage了，为什么还要存到vuex中？

- 相对来说vuex的存取比storage方便一些，且配合vuex的持久化存储插件可以更加方便

- vuex的数据是响应式的，而storage不是响应式，有时候可能会考虑这一点

- vuex存在内存中，而storage存在本地磁盘中，在内存中存取数据会快一点

前端路由跳转注意事项

跳转页面前，需要进行判断，有以下几种情况：

- 未登录也可以访问的路由，登录后才可以访问的路由。同时需要实现在a页面未登录而跳转到登录页的情况下，登录成功跳回a页面。
  
  ```
  // /router/index.js 配置全局前置守卫
  router.beforeEach((to,from,next) => {
    if(to.meta.needToken && !localStorage.getItem('token')){
      //如果跳转后的路由需要登录，且此时未登录  
      next({
        path: '/Login',
        //params: {...to.params},  //可不写，因为params参数会在to.path
        query: { redirect: to.path, ...to.query }  
        /*
        或者query: { redirect: to.fullPath}，因为fullPath包括了
        params和query，且会保存在params对象和query对象中
        */
      });
    }
    else  next();   
  })
  
  // Login.vue
  methods: {
    login(){
      ...发请求
      localStorage.setItem("token", "123");
      //如果不是从其他页面调过来登录，而是直接进入的登录页，那登录完就跳首页
      if (!this.$route.query.redirect) this.$router.push("/Home");
      else {
        this.$router.push({
          path: this.$route.query.redirect,
          //params: this.$route.params,  //可不写，因为params在path中
          query: this.$route.query,
          /*
          不管query.redirect是path还是fullPath，都要传query参数，虽然fullPath
          有params和query，但是只会保留params到跳转路径
          */
        });
      }
    }
  }
  ```

- 登录后不能访问的路由，如登录后不再允许进入登录注册
  
  组件内守卫或独享守卫判断，进入登录注册页时是否已登录，登录了就回到首页

- 特殊情况下才可以访问的路由
  
  比如a路由必须从b路由跳转而来，a配置组件内守卫或独享守卫，判断from是否来自b

- NotFound：配置NotFound路由

导航守卫示例如下：

```
/* 路由配置示例
{
    path: '/confirmOrder',
    name: 'confirmOrder',
    component: () => import('@/views/Order/ConfirmOrder.vue'),
    meta: {
      jwt: true,
      canFrom: ['login', 'goods', 'shopcart'],
    },
  },
*/

router.beforeEach((to, from, next) => {
  if (to.meta.jwt && !JSON.parse(localStorage.getItem('gxbuy_PC_user_store') || 'null')?.gxbuy_PC_jwt) {
    //如果跳转后的路由需要登录，且此时未登录
    next({
      path: '/login',
      query: { toPath: to.fullPath },
    });
  } else if (to.name === 'login' && JSON.parse(localStorage.getItem('gxbuy_PC_user_store') || 'null')?.gxbuy_PC_jwt) {
    // 如果已登录，就不允许再进入登录页
    next('/home');
  } else {
    // 跳转的目标还是当前路由时的处理，不处理的话页面自跳自己是不会刷新的
    if ((to.name === 'goods' && from.name === 'goods') || (to.name === 'search' && from.name === 'search')) {
      next({ name: 'empty', query: { toPath: to.path, ...to.query } });
    }

    // 如果某个页面只允许在限制的几个页面中跳转过来，且不是本页面自跳，就不允许跳转
    // 例如确认订单页面只允许商品页面和购物车页面跳转而来，在确认订单页面跳转到支付页面后，就不允许从支付页面返回确认订单页面
    else if (to.meta.canFrom && !(to.meta.canFrom as Array<string>)?.includes(from.name as string)) {
      /* 
        这里需要注意，因为刷新页面后，from.nmae 是 undefined，但是事实上我们刷新页面
        也是需要警进行跳转的，所以这里需要判断 from.name 是否为undedined，如果是则精选跳转
        所以路由配置中所有的路由都要给name，才能判断是否是刷新页面
        可能有其他方法解决，但没找到
        */
      if (from.name) next(false);
      else next();
    } else next();   // 正常跳转
  }
});
```

### 1.2 手机验证码登录

### 1.3 第三方登录

## 2 鉴权

在进行数据的增删改查的时候，需要鉴权，将token发送给后端，鉴权成功才能进行增删改查。

不过需要注意的是，像公共数据的查询如商品可以用商品id查询，但是隐私的数据如用户数据，即使鉴权了也不能直接前端传递用户id精选crud，否则的话任何一个已登录的用户都可以修改其他用户的信息。正确的方式是从jwt中取出用户id再crud，前端不需要传输用户id。

```
 const { id } = verify(req.headers.authorization, SECRCT) as any;
```

以查询数据为例：

（1）后端

在守卫中鉴权：

```
// jwt.guard.ts
import { CanActivate, ExecutionContext, Injectable } from '@nestjs/common';
import { Observable } from 'rxjs';
import { Request } from 'express';
import { Reflector } from '@nestjs/core';
import { verify } from 'jsonwebtoken';
import { SECRCT } from '../secrct';

@Injectable()
export class JwtGuard implements CanActivate {
  constructor(private reflector: Reflector) {}

  canActivate(context: ExecutionContext): boolean | Promise<boolean> | Observable<boolean> {
    const authority = this.reflector.get<string[]>('jwt', context.getHandler());

    if (!authority) return true;

    const req = context.switchToHttp().getRequest<Request>();
    const jwt = req.headers.authorization;
    if (!jwt) return false;

    try {
      verify(jwt, SECRCT);
    } catch (err) {
      return false;
    }

    return true;
  }
}
```

```
// xxx.controller.ts
import ...

@Controller('xxx')
@UseGuards(TokenGuard)
export class UserController {

  @Get()
  @SetMetadata('token', true)  //不加这一行或为false就是不需要鉴权
  findAll() {
    return 123;
  }

}
```

（3）前端

鉴权时，请求头需携带token：

```
//拿数据
axios({
  url: '/getProfile',
  method: 'get',
  headers: {
    Authorization: sessionStorage.getItem('token'),
  }
}).then(res => {
  console.log(res.data)  
})
```

当然，也可以在请求拦截器中，统一加上token请求头：

后端的接口总体分为需要token鉴权和不需要token鉴权两种。一般后端需要token鉴权的接口会统一命名，如果是统一命名就适用下面的方法，如果不是就另找方法。

此外，路由守卫中只能处理页面级别的登录判断，而按钮级别的登录判断则也可以在请求拦截器中实现：

```
import axios, { AxiosInstance, InternalAxiosRequestConfig, AxiosResponse, AxiosError } from 'axios';
import router from '@/router';

const cancelTokenSource = axios.CancelToken.source();

let instance: AxiosInstance = axios.create({
  baseURL:
    (import.meta.env.MODE === 'development' ? import.meta.env.VITE_DEV_BASEURL : import.meta.env.VITE_PROD_BASEURL) +
    '/v1/',
  timeout: 1000 *
 10,
});
// 请求拦截器
instance.interceptors.request.use(async (config: InternalAxiosRequestConfig) => {
  const userInfo = JSON.parse((localStorage.getItem('gxbuy_PC_user_store') as string) || 'null');
  const jwt = userInfo?.gxbuy_PC_jwt;

  // 后端需要jwt鉴权的接口，url都会有'/jwt/'，所以遇到有 '/jwt/' 的借口就加上请求头
  if (/\/jwt\//.test(config.url as string)) {
    // 如果未登录，就取消此次请求，并跳转登录页
    if (!jwt) {
      // 这里兜底一下，确保此时router却是已经挂在完毕
      await router.isReady();
      cancelTokenSource.cancel();
      router.push({
        path: '/login',
        query: { toPath: router.currentRoute.value.fullPath },
      });

      // 拦截器必须returen，所以这里return一个异常，请求时catch就好
      return Promise.reject(new Error('未登录'));
    } else {
      config.headers!.authorization = jwt;
    }
  }
  // 如果是登录状态，那么搜索和浏览商品时也携带token，让后端记录搜索记录和浏览记录
  else if (jwt && (/\/goods\/search/.test(config.url as string) || /\/goods\/detail/.test(config.url as string))) {
    config.headers!.authorization = jwt;
  }

  return config;
});

// 响应拦截器
instance.interceptors.response.use(
  (res: AxiosResponse) => {
    return res.data;
  },
  async (err: AxiosError) => {
    /* 无感刷新 token
       当 token 失效时会跳转登录，为了提高用户体验，可以在此处 refreshToken，
       在登录时后端返回 token 和 refresh token，当 token 失效时用 refresh token
       请求 refreshToken 接口，返回新的 token 和 refresh token
       这个 refresh token 看需求可以设置是否会过期，如果会过期，那么 refreshToken
       就不返回新的 refresh token ，当 refresh token 过期就真正过期。
       如果 refresh token 不设置过期，那么 refreshToken 就要返回新的 refresh token，
       这种方式可以保持永久登录。
       另一种方法是登录时返回 token 和 过期时间，前端计算过期时间或设置定时器，但是
       前端的系统时间可以随意被篡改，不安全，且 token 是否过期由前端控制是不合理的。
       另一种方式是在每次请求都再发一个 refreshToken ，这样虽然能频繁刷新 token ，但是
       请求总数翻倍，不合理
    */

    // 如果jwt验证失败或者jwt过期，后端一般是返回403
    if ((err.response?.data as any)?.status === 403) {
      console.log(localStorage.setItem('gxbuy_PC_user_store', ''));

      await router.isReady();
      cancelTokenSource.cancel();

      // 如果首页会发送需要鉴权的请求，嘛呢过期了就不及自动今日登录界面，不认用户体验性不好，用户自己重新点击登录
      if (router.currentRoute.value.name !== 'home') {
        router.push({
          path: '/login',
          query: { toPath: router.currentRoute.value.fullPath },
        });
      }

      return Promise.reject(new Error('未登录'));
    }

    return Promise.reject(err);
  }
);

export default instance;
```

发请求：

```
async function getUserInfo() {
  try {
    const res = (await getUserInfoRequest()).data;
    userStore.userInfo = res;
  } catch (err: any) {
    /*
    如果这个错误时后端返回的异常，那么就会有err.response?.data，errorMessage是后端自己定义的
    异常属性名；如果是前端请求拦截器返回的异常则没有err.response?.data，由此可以判断是前端异常
    还是后端异常
    */
    console.log(err.response?.data?.errorMessage || '请重新登录');
  }
}
```

请求失败可弹出信息：

```
// /src/tools/myMessage.ts


import { ElMessage } from "element-plus";
import "element-plus/dist/index.css";

export function myMessage(message: string | any, type: any, messageIsErrorType: boolean = false) {
  if (type === "error" && messageIsErrorType) {
    message = message?.response ? message?.response?.data?.errorMessage || "网络异常" : "请重新登录";
  }

  ElMessage({
    customClass: "my-el-message",
    showClose: true,
    message,
    type
  });
}
```

## 3 权限控制

权限管理分为前端权限管理和后端权限管理，前后端未分离的时代权限都是由后端管理的，但是在前后端分离的时代，前端也需要权限管理。

权限的本质就是对数据库中的数据的CRUD。

后台管理系统必须要有一个超级管理员admin，具备所有权限，必须要有对用户、角色、权限、菜单的增删改查，因为用户不是注册而来，而是管理员分配而来。

### 3.1 后端

后端权限通过token来鉴权增删改查的操作，是权限管理的最后一道关口。

通过守卫实现：

```
// auth-guard.ts
import { CanActivate, ExecutionContext, Injectable } from '@nestjs/common';
import { Observable } from 'rxjs';
import { HttpException, HttpStatus } from '@nestjs/common';
import { Request } from 'express';
import { Reflector } from '@nestjs/core';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { ShopManager } from '@/modules/user/entities/shop_manager.entity';
import { verify } from 'jsonwebtoken';
import { SECRCT } from '../secrct';

@Injectable()
export class AuthGuard implements CanActivate {
  constructor(
    private reflector: Reflector,
    @InjectRepository(ShopManager) private readonly shopManagerRepository: Repository<ShopManager>
  ) {}

  getAuth(
    data: any,
    auth: any = {
      menu: [],
      button: [],
    }
  ): any {
    let authority = auth;

    for (const i of data) {
      if (i.name) authority.menu.push(i.name);
      if (i?.button?.length > 0)
        authority.button = [...authority.button, ...(i?.button?.map((v: any) => v.value) || [])];

      if (i?.children?.length > 0) authority = this.getAuth(i.children, authority);
    }

    return authority;
  }

  async auth(userId: string, shopId: string, authorityInfo: any): Promise<boolean> {
    const user = await this.shopManagerRepository.findOne({
      relations: ['shop_manager_role'],
      where: { _id: userId, shop_id: shopId },
    });

    if (!user) throw new HttpException('您没有该权限', HttpStatus.UNAUTHORIZED);
    if (user.shop_manager_role.length === 0) throw new HttpException('您没有该权限', HttpStatus.UNAUTHORIZED);

    if (user.shop_manager_role.map((role: any) => role.shop_manager_role_name).includes('admin')) return true;

    for (const role of user.shop_manager_role) {
      if (!role.shop_manager_role_authority) continue;

      const { menu, button } = this.getAuth(role.shop_manager_role_authority);

      if (authorityInfo.isBtn) {
        if (button.includes(authorityInfo.value)) return true;
      } else {
        if (menu.includes(authorityInfo.value)) return true;
      }
    }

    throw new HttpException('您没有该权限', HttpStatus.UNAUTHORIZED);
  }

  canActivate(context: ExecutionContext): boolean | Promise<boolean> | Observable<boolean> {
    const authority = this.reflector.get<string[]>('auth', context.getHandler());

    if (!authority) return true;

    const req = context.switchToHttp().getRequest<Request>();
    const jwt = req.headers.authorization;
    if (!jwt) throw new HttpException('您未登录，或登录过期', HttpStatus.FORBIDDEN);

    let id: any = null;
    try {
      id = verify(jwt, SECRCT);
    } catch (err) {
      throw new HttpException('您未登录，或登录过期', HttpStatus.FORBIDDEN);
    }

    const { shopId, userId } = id;

    return this.auth(userId, shopId, authority);
  }
}
```

需要权限的控制器中（参考鉴权笔记，先导入guard并use）；

```
// 菜单权限，如获取角色列表的接口
@SetMetadata('auth', {
  value: 'roleManage',
  isBtn: false,
})

// 按钮权限，如修改角色的接口
@SetMetadata('auth', {
  value: 'role-update-role',
  isBtn: true,
})
```

### 3.2 前端

RBAC（基于角色的权限控制）：权限并不是针对于某个用户，而是针对于某类角色，一个用户可能有多个角色，在数据库设计上可以设计成用户表、角色表、权限表。

前端权限管理仅仅是针对于视图层展示和请求的发送这些用户体验方面的控制。前端就算做了再多的控制，用户也可以在控制台中绕过，所以真正的权限控制还在后端。

，但是前端的权限管理也是非常有必要的，主要有以下几点：

- 减少用户非法操作的可能性，如隐藏需要权限的按钮。

- 尽可能排除非必要和不具备权限的请求，减少服务器压力，尽管这些请求也一定不会成功

- 提高用户使用体验，如用户在浏览器输入url，若此url需要登录就跳转登录页，若此url需要权限且用户不具备权限则跳转404页面等

前端权限管理分为四个方面：

- 菜单权限：主要指后台管理系统的侧边菜单栏，每个用户只会拥有自己权限范围的菜单

- 路由权限：用户只能访问自己具备权限的页面，需与菜单权限配合

- 按钮权限：一些页面可能几类角色都有权限进入（或非法进入），而该页面的按钮则具备权限，如普通角色只有查看权，而管理员有编辑、删除等按钮，那么这些按钮就应该根据权限来显示隐藏/启用禁用。

- 请求权限：若通过以上操作还不能规避用户非法操作，如用户非法进入页面，通过控制台修改按钮为显示/启用，那么在发送请求时，应当根据权限在前端层面请求发起时就拒绝发送请求。

可以看出这四个方面是循序渐进的。由前端进行的一系列权限控制之后若用户还是能够非法的操作对数据进行增删改查，后端通过token鉴权也能规避。

#### 3.2.1 菜单权限与路由权限

这两个其实是配合在一起的。

根据用户的权限所能查看的菜单，动态添加菜单对应的路由。

初始路由及配置：

```
// /src/router/indexts

import { createRouter, createWebHashHistory, RouteRecordRaw } from "vue-router";

const routes: Array<RouteRecordRaw> = [
  {
    path: "/",
    name: "homeDefaultRoute",
    redirect: "/home"
  },
  {
    path: "/home",
    name: "home",
    component: () => import("@/views/Home/Home.vue"),
    meta: {
      useLayout: true,
      jwt: true,
      menuData: {
        title: "首页",
        icon: "home-filled"
      }
    }
  },
  {
    path: "/login",
    name: "login",
    component: () => import("@/views/Login/Login.vue"),
    meta: {
      useLayout: false,
      jwt: false
    }
  },
  {
    path: "/:catchAll(.*)",
    component: () => import("@/views/404/404.vue"),
    meta: {
      useLayout: false,
      jwt: false
    }
  }
];

const router = createRouter({
  history: createWebHashHistory(),
  routes
});

router.beforeEach((to, from, next) => {
  if (!from) return;

  if (to.meta.jwt && !JSON.parse(localStorage.getItem("gxbuy_manager_user_store") || "null")?.gxbuy_manager_jwt) {
    next({
      path: "/login",
      query: { toPath: to.fullPath }
    });
  } else if (
    to.name === "login" &&
    JSON.parse(localStorage.getItem("gxbuy_manager_user_store") || "null")?.gxbuy_manager_jwt
  ) {
    next("/home");
  } else next();
});

export default router;
```

根据后端返回信息的完整度，动态添加路由，后端最少都需要返回能标识该用户菜单权限的信息，比如路由name，角色等。

下面是后端只返回了路由name的情况，这种最复杂：

```
// /src/types/types/authority.ts

export interface RoutesNameInterface {
  name: string;
  children?: Array<RoutesNameInterface>;
}

export interface MenuDataInterface {
  path: string;
  title: string;
  icon: string;
  children?: Array<MenuDataInterface>;
}
```

```
import router from "./index.ts";
import { RouteRecordRaw } from "vue-router";
import store from "@/store";
import { RoutesNameInterface, MenuDataInterface } from "@/types";
import { deepCopy } from "@/tools/deepCopy";

/* 示例路由
 * 若下面有路由已存在的路由也没关系，动态添加时不影响，放在这里可以方便取出菜单信息
 * 默认路由不能先定义，因为胡无法确定定义的默认路由筛选后还是否存在
 */
const authRoutes: Array<RouteRecordRaw> = [
  {
    path: "/authorityManage",
    name: "authorityManage",
    component: () => import("@/views/AuthorityManage/AuthorityManage.vue"),
    meta: {
      useLayout: true,
      jwt: true,
      menuData: {
        title: "权限管理",
        icon: "lock"
      }
    },
    children: [
      {
        path: "roleManage",
        name: "roleManage",
        component: () => import("@/views/AuthorityManage/children/RoleManage.vue"),
        meta: {
          useLayout: true,
          jwt: true,
          menuData: {
            title: "角色管理",
            icon: "CreditCard"
          }
        }
      },
      {
        path: "userManage",
        name: "userManage",
        component: () => import("@/views/AuthorityManage/children/UserManage.vue"),
        meta: {
          useLayout: true,
          jwt: true,
          menuData: {
            title: "用户管理",
            icon: "user-filled"
          }
        }
      }
    ]
  },
  {
    path: "/goodsManage",
    name: "goodsManage",
    component: () => import("@/views/GoodsManage/GoodsManage.vue"),
    meta: {
      useLayout: true,
      jwt: true,
      menuData: {
        title: "商品管理",
        icon: "DocumentCopy"
      }
    }
  },
  {
    path: "/orderManage",
    name: "orderManage",
    component: () => import("@/views/OrderManage/OrderManage.vue"),
    meta: {
      useLayout: true,
      jwt: true,
      menuData: {
        title: "订单管理",
        icon: "user-filled"
      }
    },
    children: [
      {
        path: "logisticsManage",
        name: "logisticsManage",
        component: () => import("@/views/OrderManage/children/LogisticsManage.vue"),
        meta: {
          useLayout: true,
          jwt: true,
          menuData: {
            title: "物流管理",
            icon: "user-filled"
          }
        }
      },
      {
        path: "commentManage",
        name: "commentManage",
        component: () => import("@/views/OrderManage/children/CommentManage.vue"),
        meta: {
          useLayout: true,
          jwt: true,
          menuData: {
            title: "评论管理",
            icon: "user-filled"
          }
        }
      }
    ]
  }
];

// 根据后端返回的该用户具有的菜单name，筛选出对应的路由
function filterAuthRoutes(
  routesName: Array<RoutesNameInterface>,
  authRoutesData: Array<RouteRecordRaw> = authRoutes
): Array<RouteRecordRaw> {
  const result: Array<RouteRecordRaw> = [];
  const authRoutesDataCopy = deepCopy(authRoutesData);

  for (const item of routesName) {
    for (let route of authRoutesDataCopy) {
      if (item.name === route.name) {
        if (item?.children?.length! > 0) {
          route.children = filterAuthRoutes(item.children!, route.children);
        } else delete route.children;

        result.push(route);
      }
    }
  }
  return result;
}

// 获取路由meta中的菜单信息，若后端已返回菜单信息可忽略此函数
function getMenuData(routes: Array<RouteRecordRaw>, parentPath: string = ""): Array<MenuDataInterface> {
  const menuData: Array<MenuDataInterface> = [];

  for (let i of routes) {
    if (["", "/"].includes(i.path)) continue;
    if (!i?.meta?.menuData) continue;

    if (i?.children?.length! > 0) {
      menuData.push({
        path: i.path,
        title: (i?.meta?.menuData as any).title,
        icon: (i?.meta?.menuData as any).icon,
        children: getMenuData(i.children!, parentPath + i.path + "/")
      });
    } else menuData.push({ path: parentPath + i.path, ...(i?.meta?.menuData as object) } as MenuDataInterface);
  }

  return menuData;
}

// 如果想给每个子路由都增加默认路由，可使用此函数

function addDefaultRoute(routes: Array<RouteRecordRaw>, parentPath: string = ""): Array<RouteRecordRaw> {
  for (let index in routes) {
    if (index === "0") {
      routes.push({
        path: "",
        name: String(routes[index].name) + "DefaultRoute",
        redirect: parentPath + routes[index].path
      });
    }
    if (routes[index]?.children?.length! > 0) {
      addDefaultRoute(routes[index].children!, parentPath + routes[index].path + "/");
    }
  }
  return routes;
}

export async function addAuthRoutes(routesName: Array<RoutesNameInterface>) {
  // 筛选路由并增加默认路由
  const routes = addDefaultRoute(filterAuthRoutes(routesName));

  // 保证此时router已挂在完毕，再动态添加路由
  await router.isReady();
  for (let i of routes) router.addRoute(i);

  // 菜单信息存储到pinia中
  const menuStore = store.state.value.Menu;
  menuStore.menuData = getMenuData([...router.options.routes, ...routes, routes] as Array<RouteRecordRaw>);
}
```

jwt鉴权，路由守卫和axios拦截器配置参考之前的配置。

这里的pinia已做持久化存储，参考之前的配置。

登录拿到权限，并开始动态添加路由：

```
async function login(){
  try {
      const res = (await userLoginRequest(loginInfo)).data;

      userStore.gxbuy_manager_jwt = res.jwt;
      userStore.userInfo = res.userInfo;
      userStore.routesName = res.routesName;

      addAuthRoutes(userStore.routesName);
      router.push("/home");
    } catch (err) {
      // ...
    }
}
```

App.vue中判断，若storage有jwt则发请求获取权限信息，如果storage中有权限信息也最好重新请求一下，获取最新的权限信息：

```
<script setup lang="ts">
// ...

async function init() {
  if (userStore.gxbuy_manager_jwt) {
    try {
      const res = (await getUserInfoRequest()).data;

      userStore.userInfo = res.userInfo;
      userStore.routesName = res.routesName;

      await addAuthRoutes(userStore.routesName);

      // 没有添加路由前会跳转到404，所以添加完路由后要跳转一下
      router.push(route.fullPath);
    } catch (err: any) {
      myMessage(err, "error", true);
    }
  }
}

init();
</script>
```

退出登录：

```
async function logout() {
  // 清空pinia数据，因为已经做了持久化，所以storage和pinia会同时清空
  localStorage.setItem("gxbuy_manager_user_store", "");
  localStorage.setItem("gxbuy_manager_menu_store", "");

  // ... 退出登录请求

  // 跳转登录页
  await router.push("/login");

  // 也要 removeRoute() 路由，但是比较麻烦，直接刷新页面就行了,注意要在跳转到登录页后再刷新
  router.go(0);
}
```

这种适合体量小，菜单变动少的项目，缺陷是路由信息、菜单信息存储在前端，一旦要修改这些信息就要重新打包前端。

后端可能返回的信息还有以下几种情况，根据情况修改上面代码即可：

* 在上面情况基础上多返回了菜单信息，那么路由meta就不需要存储菜单信息了，也不需要从meta中取出菜单信息。菜单的信息存到数据库中也可以进行修改，适合体量大，菜单变动多的项目

* 在上面的基础上，又把路由的路径和组件路径都返回了，优点是灵活，缺点是后端需要高度配合前端。此外，后端返回的路由信息不一定是规范的，需要前端自行转换。

#### 3.3.2 按钮权限控制

不同用户拥有不同的按钮权限，每个用户只能看到自己有权限的权限。

根据权限信息来v-if，v-show来隐藏，但是比较麻烦。最方便的实现就是全局自定义指令，需要权限的按钮绑定自定义指令，自定义指令内部根据当前路由的meta取得权限信息，来隐藏/禁用/删除按钮。

【警告】在某些情况下，使用自定义指令v-permission将无效。例如：元素UI的选项卡组件或el表格列以及其他动态渲染dom的场景。您只能使用v-if来执行此操作。

全局自定义指令：

```
// 根据后端返回的按钮权限的数据形式来做，比如登录后就返回：
// {  buttons: ['goods-add','goods-update'] }

// /src/directs/authBtn.ts
import { DirectiveBinding } from "vue";
import { UserStore } from "@/store";

export function authBtn(app: any) {
  app.directive("authBtn", {
    mounted(el: HTMLElement, dir: DirectiveBinding) {
      const userStore = UserStore();
      if (!userStore.button.includes(dir.value)) el.parentNode?.removeChild(el);
    }


  });
}
// main.js 
import ...
authBtn(app);

// 按钮 中
<button v-auth-btn="'goods-add-spu'"></button>
```

#### 3.3.3 请求权限控制

不太好实现，也没有太大的必要弄，有些多余，一般按钮权限就够了。

要弄得话，可以再筛选路由的时候根据权限添加请求权限的路由元信息，组件中发请求是判断是否有权限。

也可以在请求拦截器中，根据url判断（如果url包含请求权限信息的话），或者判断请求类型来做。

# 六、文件上传与下载

## 1 文件上传

### 1.1 文件上传在前端需要的自定义方法

（1）分离文件名的后缀

```
function getName(file: any) {
  //文件名和后缀
  const fileFullNameList = file.name.split(".");
  const suffix = fileFullNameList[fileFullNameList.length - 1];
  const name = file.name.replace(new RegExp(`.${suffix}$`), "");
  return {
    name,
    suffix,
  };
}
```

（2）读取文件内容

在文件上传时，有可能会在前端读取文件，但不是必须的：

```
<script setup lang="ts">
import { ref } from "vue";

let fileContext = ref<string | ArrayBuffer | null>("");

function readFileContext(file: any) {
  return new Promise<string | ArrayBuffer | null>((resolve) => {
    const fileReader = new FileReader();

    //编码要选择的文件的编码一致，否则中文乱码
    fileReader.readAsText(file, "utf8");
    fileReader.onload = () => {
      //读取完成时回调, 取结果保存在result
      resolve(fileReader.result);
    };
  });
}

async function upload(e: any) {
  if (e.target.files.length === 0) return;
  let file = e.target.files[0];
  fileContext.value = "";
  fileContext.value = await readFileContext(file);
}
</script>

<template>
  <input type="file" @change="upload" />
  <p>{{ fileContext }}</p>
</template>

<style lang="less" scoped></style>
```

（3）文件内容转为base64编码

图片上传可能会用到：

```
function fileToBase64(file: any) {
  return new Promise<string>((resolve) => {
    let fileReader = new FileReader();

    //这是异步的，需要下面事件监听处理完成
    fileReader.readAsDataURL(file);
    fileReader.onload = (e) => {
      resolve(e.target.result);
    };
  });
}
```

（4）HASH命名文件

后端为了避免上传的文件与服务器中原有文件重名，会根据上传的文件弄出一个HASH值来对文件命名，但有的后端不处理，则需要前端前端自己处理成HASH。

使用SparkMD5：

* 根据buffer格式的文件生成HASH值

* HASH的值只跟文件内容有关(与文件名无关)，文件内容完全一样HASH就一样

* 根据需要可以将文件命名为 HASH.后缀名，有时也直接命名为HASH

```
import SparkMD5 from "spark-md5";

//先将文件对象转为buffer
function fileToBuffer(file: any) {
  return new Promise<ArrayBuffer>((resolve) => {
    let fileReader = new FileReader();

    fileReader.readAsArrayBuffer(file as Blob);
    fileReader.onload = (e) => {
      resolve(e.target.result);
    };
  });
}

//生成HASH
async function toHASH(file: any) {
  let buffer = await fileToBuffer(file);
  let sparkmd5 = new SparkMD5.ArrayBuffer().append(buffer);
  let HASH = await sparkmd5.end();
  return HASH;
}
```

（6）文件切片

```
interface CutChunkOption {
  file: any;
  chunkSize?: number;     //单位字节
  maxQuantity?: number;
  finishIndex?: number[]; //已上传过的切片index
}

function cutChunk(option: CutChunkOption): any {
  let { file, chunkSize, maxQuantity, finishIndex } = option;
  chunkSize = chunkSize || file.size;
  maxQuantity = maxQuantity || 1;
  finishIndex = finishIndex || [];

  /*
  可以固定数量或固定大小，但切片不要太多，建议设置最大切片数量
  推荐先固定大小，看有多少切片，若切片数量多于最大数量，则就切最大数量的切片
  */
  let chunkQuantity = Math.ceil(file.size / chunkSize!);
  if (chunkQuantity > maxQuantity) {
    chunkSize = Math.ceil(file.size / maxQuantity);
    chunkQuantity = Math.ceil(file.size / chunkSize);
  }

  //先确定哪些切片没有上传，已上传的就不再上传了
  let chunkIndex = [], finishIndexSet = new Set(finishIndex);
  for (let i = 0; i < chunkQuantity; i++) chunkIndex.push(i);
  chunkIndex = chunkIndex.filter((i: number) => {
    return !finishIndexSet.has(i);
  });

  //开始切片
  let chunks = [];
  for (let i of chunkIndex) {
    let chunk = null;
    if (i === chunkQuantity - 1) chunk = file.slice(i * chunkSize!, file.size);
    else chunk = file.slice(i * chunkSize!, i * chunkSize! + chunkSize!);
    chunks.push({
      chunk,
    });
  }

  return {
    chunkQuantity,
    chunks,
  };
}
```

### 1.2 自定义API封装成工具类

方便使用：

```
import SparkMD5 from "spark-md5";

interface CutChunkOption {
  file: any;
  chunkSize?: number;     //单位字节
  maxQuantity?: number;
  finishIndex?: number[]; //已上传过的切片index
}

interface UploadInterface {
  getName: (file: any) => { name: string; suffix: string };
  readFileContext: (file: any) => Promise<string | ArrayBuffer | null>;
  fileToBase64: (file: any) => Promise<string>;
  fileToBuffer: (file: any) => Promise<ArrayBuffer>;
  createHASH: (file: any) => Promise<string>;
  cutChunk: (option: cutChunkOption) => any;
}

export default class Upload implements UploadInterface {
  public static getName(file: any) {
    //文件名和后缀
    const fileFullNameList = file.name.split(".");
    const suffix = fileFullNameList[fileFullNameList.length - 1];
    const name = file.name.replace(new RegExp(`.${suffix}$`), "");
    return {
      name,
      suffix,
    };
  }

  public static readFileContext(file: any) {
    return new Promise<string | ArrayBuffer | null>((resolve) => {
      const fileReader = new FileReader();
      //编码要选择的文件的编码一致，否则中文乱码
      fileReader.readAsText(file, "utf8");
      fileReader.onload = () => {
        //读取完成时回调, 取结果保存在result
        resolve(fileReader.result);
      };
    });
  }

  public static fileToBase64(file: any) {
    return new Promise<string>((resolve) => {
      let fileReader = new FileReader();

      //这是异步的，需要下面事件监听处理完成
      fileReader.readAsDataURL(file);
      fileReader.onload = (e: any) => {
        resolve(e.target.result);
      };
    });
  }

  public static fileToBuffer(file: any) {
    return new Promise<ArrayBuffer>((resolve) => {
      let fileReader = new FileReader();

      fileReader.readAsArrayBuffer(file);
      fileReader.onload = (e: any) => {
        resolve(e.target.result);
      };
    });
  }

  public static async createHASH(file: any) {
    let buffer = await this.fileToBuffer(file);
    let sparkmd5 = new SparkMD5.ArrayBuffer().append(buffer);
    let HASH = await sparkmd5.end();
    return HASH;
  }

  public static cutChunk(option: CutChunkOption): any {
    let { file, chunkSize, maxQuantity, finishIndex } = option;
    chunkSize = chunkSize || file.size;
    maxQuantity = maxQuantity || 1;
    finishIndex = finishIndex || [];

    /*
    可以固定数量或固定大小，但切片不要太多，建议设置最大切片数量
    推荐先固定大小，看有多少切片，若切片数量多于最大数量，则就切最大数量的切片
    */
    let chunkQuantity = Math.ceil(file.size / chunkSize!);
    if (chunkQuantity > maxQuantity) {
      chunkSize = Math.ceil(file.size / maxQuantity);
      chunkQuantity = Math.ceil(file.size / chunkSize);
    }

    //先确定哪些切片没有上传，已上传的就不再上传了
    let chunkIndex = [], finishIndexSet = new Set(finishIndex);
    for (let i = 0; i < chunkQuantity; i++) chunkIndex.push(i);
    chunkIndex = chunkIndex.filter((i: number) => {
      return !finishIndexSet.has(i);
    });

    //开始切片
    let chunks = [];
    for (let i of chunkIndex) {
      let chunk = null;
      if (i === chunkQuantity - 1) chunk = file.slice(i * chunkSize!, file.size);
      else chunk = file.slice(i * chunkSize!, i * chunkSize! + chunkSize!);
      chunks.push({
        chunk,
      });
    }

    return {
      chunkQuantity,
      chunks,
    };
  }
}
```

### 1.3 文件上传前需要知道的内容

（1）后端文件存储形式

- 将整个文件以二进制形式存入数据库（不推荐）

- 存在后端服务器某个目录，数据库存放文件的路径

- 存放到另一个服务器（文件服务器）或第三方服务器，数据库存放网络url

（2）文件上传模块样式方面的设计：

- file表单隐藏，通过自定义按钮来触发file表单的点击

- 文件选择和文件上传可以分开，也可以合并

- 选择文件的方式也可以是拖拽，事件有：
  
  * dragenter：拖拽移入事件
  
  * dragleave：拖拽移开事件
  
  * dragover：拖拽在框里移动事件
  
  * drop分别是，拖拽放入事件
  
  注意点：
  
  * 拖拽放入时，浏览器会触发默认行为（打开新页面并显示文件内容），自己需要关闭默认行为
  
  * drapenter，drapleave可以用来设置样式，drapover和drop需要e.preventDefault()关闭默认行为（根据需要也可以关闭整个浏览器的这个行为），drop里面用e.dataTransfer.files获得文件对象。

- 上传时，通过css修改样式，js修改按钮描述内容和禁用按钮

（3）文件上传需要实现一些限制条件

- 文件类型限制和文件大小限制：
  
  ```
  <script setup lang="ts">
  import Upload from "../tools/upload";
  
  function upload(e: any) {
    if (e.target.files.length === 0) return;
  
    const file = e.target.files[0];
  
    const { name, suffix } = Upload.getName(file);
  
    if (!/(jpg|png)/i.test(suffix)) {
      console.log("不支持的格式");
      return;
    }
  
    if (file.size > 2 * 1024 * 1024) {
      console.log("文件超过2M，无法上传");
      return;
    }
  }
  </script>
  
  <template>
    <!-- 方式一，有点文件选择框就不会显示不支持的文件，缺点自定义性差  -->
    <input type="file" accept=".jpg,.png" />
  
    <!-- 方式二，js实现，有点事自定义性好，缺点是文件选择框依然会显示不支持的文件 -->
    <input type="file" @change="upload" />
  
    <!-- 方式一方式二结合使用 -->
    <input type="file" accept=".jpg,.png" @change="upload" />
  </template>
  
  <style lang="less" scoped></style>
  ```

（4）上传成功后，显示已选文件列表：

- 单文件直接显示就行

- 多文件可以事件委派实现删除功能

（5）已选文件预览/缩略图：

- 图片，先将图片转化为base64码，再将base64码赋值给img的src即能实现缩略图
  
  ```
  <script setup lang="ts">
  import { ref } from "vue";
  import Upload from "../tools/upload";
  
  let base64 = ref<string>("");
  
  async function upload(e: any) {
    if (e.target.files.length === 0) return;
  
    const file = e.target.files[0];
    base64.value = await Upload.fileToBase64(file);
  }
  </script>
  
  <template>
    <input type="file" @change="upload" />
    <img :src="base64" alt="" />
  </template>
  
  <style lang="less" scoped></style>
  ```

- 文本，可以用FileReader实现预览

- 其他类型的文件，为了美观可以用图标表示缩略图

（6）上传进度：

有相应的库，使用详见文档：

```
npm install --save nprogress
```

```
import nprogress from 'nprogress';
import "nprogress/nprogress.css";
```

也可以手写：

axios的配置项onUploadProgress可以实时监听，至于上传速度可以用已上传大小和已花费时间计算，剩余时间可以用上传速度和剩余大小计算

```
onUploadProgress: (progress: any) => {
  console.log('当前已上传:',progress.loaded,'字节')
  console.log('文件总大小:',progress.total,'字节')
  console.log('当前百分比:',Math.round((progress.loaded*100)/progress.total) + '%')
}
```

此外，不仅是上传，在其他业务中也可能需要用到进度条。

### 1.4 文件上传的不同实现

#### 1.4.1 单文件上传（FormData）

post请求，请求体放FormData，设置请求头为：

```
headers: {"Content-Type": "multipart/form-data"}
```

但是这样设置有时候会报错，说找不到边界，可以换成：headers: false

（1）前端

```
<script setup lang="ts">
import { ref } from "vue";
import axios from "axios";

let uploadRef = ref<HTMLElement | null>(null);

function upload(e: any) {
  const file = e.target.files[0];
  const formData = new FormData();
  /*
  append的第一/二个参数分别是键和值，用来给FormData对象填充信息，键可以根据需要自定义名，方便后端处理
  如append('fileName',file.name) append('HASH',hash值)
  */
  formData.append("file", file);

  axios({
    url: "http://localhost:8000/upload",
    method: "post",
    data: formData,
    headers: { "Content-Type": "multipart/form-data" },
  }).then((res) => {
    console.log(res.data);
  });
}
</script>

<template>
  <div id="upload">
    <input ref="uploadRef" type="file" style="display: none" @change="upload" />
    <button @click="uploadRef?.click()">点击上传</button>
  </div>
</template>

<style scoped lang="less"></style>
```

（2）后端

```
npm install --save multer @types/multer
```

```
// upload.module.ts
import { Module } from "@nestjs/common";
import { UploadController } from "./upload.controller";
import { MulterModule } from "@nestjs/platform-express";
import { diskStorage } from "multer";
import { extname, join } from "path";

@Module({
  imports: [
    MulterModule.register({
      //定义上传文件的存放目录
      storage: diskStorage({
        // 目录在 /dist/aaa
        destination: join(__dirname, "../aaa"),
        //文件名
        filename: (_, file, callback) => {
          //命名为时间戳，extname()可以去除后缀名
          const fileName = `${new Date().getTime() + extname(file.originalname)}`;
          return callback(null, fileName);
        },
      }),
    }),
  ],
  controllers: [UploadController],
})
export class UploadModule { }
```

```
// upload.controller.ts
import { Controller, Post, UseInterceptors, UploadedFile} from '@nestjs/common';
import { FileInterceptor, FilesInterceptor } from '@nestjs/platform-express';

@Controller('upload')
export class UploadController {
  @Post()
  //fileInterceptor为单文件上传, filesInterceptor为多文件上传
  @UseInterceptors(FileInterceptor('file'))
  upload(@UploadedFile() file) {
    console.log(file);
    return {
      code: 200,
      message: '上传成功'
    };
  }
}
```

#### 1.4.2 单文件上传（base64）

适合图片，音频，视频，图片居多

post请求，请求体base64

请求头：

```
headers:{'Content-Type':'application/x-www-dorm-urlencoded'}
```

### 1.4.3 多文件上传

选择文件，一是file表单增加属性multiple，一次选多个，在change事件中将files数组的元素全append到FormData，二是不加multiple，一次选一个，每次change将files[0]的文件append到已声明的FormData，最终都是得到含有多个file对象的FormData

上传文件也有两种方式，一是一次性上传全部file（但无法获得进度），后端通过req.files得到各个file信息并改名。二是每个file单独上传（能获得每个file的进度），都断与单文件上传一样。

### 1.4.4 大文件上传（切片+断点续传）

（1）前端

```
<script setup lang="ts">
import { ref } from "vue";
import Upload from "../tools/upload";
import axios from "axios";

let uploadRef = ref<HTMLElement | null>(null);

async function alreadyReq(HASH: srting): Promise<any> {
  let res = await axios({
    url: "http://localhost:8000/already",
    method: "get",
    params: {
      HASH,
    },
  });
  return res;
}

async function uploadReq(chunks: any): Promise<any> {
  //进度可以用已上传的切片数来确定
  let res: any = null;
  try {
    res = await Promise.all(
      chunks.map((c: any) => {
        let formData = new FormData();
        formData.append("chunk", c.chunk);
        formData.append("name", c.name);
        return axios({
          url: "http://localhost:8000/upload",
          method: "post",
          data: formData,
          headers: { "Content-Type": "multipart/form-data" },
        });
      })
    );
  } catch (err) {
    return "参数错误";
  }
  return res;
}

async function mergeReq(
  HASH: string,
  fileName: string,
  chunkQuantity: number
): Promise<any> {
  const res = await axios({
    url: "http://localhost:8000/merge",
    method: "post",
    data: {
      HASH,
      fileName,
      chunkQuantity,
    },
  });
  return res;
}

async function upload(e: any) {
  const file = e.target.files[0];

  //为了标识切片，需要给每个切片命名为 HASH_数字.后缀
  const { name, suffix } = Upload.getName(file);
  const HASH = await Upload.createHASH(file);

  //先看后端是否有已上传的切片
  let finishIndex = (await alreadyReq(HASH)).data.map((i: string) =>
    parseInt(i)
  );

  //开始切片
  let { chunkQuantity, chunks } = Upload.cutChunk({
    file,
    chunkSize: 1024 * 100,
    maxQuantity: 100,
    finishIndex,
  });
  chunks.forEach((i: any, index: number) => {
    i.name = `${HASH}_${index}.${suffix}`;
  });

  //若此时切片都已上传，但未合并
  if (chunks.length === 0) {
    let mergeRes = await mergeReq(HASH, file.name, chunkQuantity);
    console.log(res);
  }

  //切片从未上传过，或上传了部分切片
  else {
    const uploadRes = await uploadReq(chunks);
    console.log(uploadRes);

    let mergeRes = await mergeReq(HASH, file.name, chunkQuantity);
    console.log(mergeRes);
  }
}
</script>

<template>
  <div id="upload">
    <input ref="uploadRef" type="file" style="display: none" @change="upload" />
    <button @click="uploadRef.click()">点击上传</button>
  </div>
</template>

<style scoped lang="less"></style>
```

（2）后端（express版）

```
const express = require("express");
const fs = require("fs");
const bodyParser = require("body-parser");
const multiparty = require("multiparty");

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

app.all("*", (request, response, next) => {
  response.header("Access-Control-Allow-Origin", "*");
  response.setHeader(
    "Access-Control-Allow-Headers",
    "content-type,Authorization"
  );
  if (request.method == "OPTIONS") response.send(200);
  else next();
});

//获取已上传的切片
app.get("/already", (req, res) => {
  const { HASH } = req.query;
  let nameList = [];
  if (fs.existsSync("./upload/" + HASH))
    nameList = fs.readdirSync("./upload/" + HASH).sort((a, b) => a - b);
  res.send(nameList);
});

//上传切片
app.post("/upload", async (req, res) => {
  //注意，upload文件夹必须存在，否则会创建失败
  let form = new multiparty.Form({ uploadDir: "./upload" });

  //form.parse()会将文件保存到设置的路径
  form.parse(req, async (err, fields, files) => {
    try {
      //fields是前端formData.append()的非FormData类型数据
      //files是文件的路径等信息,
      const index = fields.name[0].match(/(?<=_)\d+(?=.)/)["0"];
      const dir = fields.name[0].match(/.+(?=_\d+)/)["0"];

      //创建存放切片的目录
      if (!fs.existsSync("./upload/" + dir))
        fs.mkdirSync("./upload/" + dir, (err) => {});

      //将切片移动到创建的目录
      //用常规的移动文件也可以，但有大小限制，推荐用流写入
      const buffer = fs.readFileSync(files.chunk[0].path);
      let ws = fs.createWriteStream(`./upload/${dir}/${index}`);
      ws.write(buffer);
      ws.close();

      //删除留在外面的切片文件
      fs.unlinkSync(files.chunk[0].path, (err) => {});
      res.send(index);
    } catch (err) {
      res.status(403).send("参数错误");
    }
  });
});

//合并切片
const Buffer = require("buffer").Buffer;
app.post("/merge", (req, res) => {
  const { HASH, fileName, chunkQuantity } = req.body;

  //得到所有切片的名字
  const nameList = fs.readdirSync("./upload/" + HASH);
  if (nameList.length < chunkQuantity) {
    res.send("上传失败");
    return;
  }

  //排序切片名
  nameList.sort((a, b) => a - b);

  //合并切片需要buffer格式的切片的数组，和所有切片的总字节
  let Byte = 0,
    bufferList = [];
  for (let name of nameList) {
    let buffer = fs.readFileSync(`./upload/${HASH}/${name}`);
    bufferList.push(buffer);
    Byte += buffer.length;
  }
  let mergeBuffer = Buffer.concat(bufferList, Byte);

  //以流的形式写入文件，没有大小限制
  let ws = fs.createWriteStream("./upload/" + fileName);
  ws.write(mergeBuffer);
  ws.close();

  //合并完成，删除存放切片的临时文件夹
  fs.readdirSync(`./upload/${HASH}`).forEach((name) => {
    fs.unlinkSync(`./upload/${HASH}/${name}`);
  });
  fs.rmdirSync(`./upload/${HASH}`);
  res.send("上传成功");
});

app.listen(8000, () => [console.log("服务已启动")]);
```

## 2 文件下载

正常情况下，部署到静态文件夹的文件，浏览器输入或a标签的href是这个文件的url：

* 若文件是浏览器无法解析的，如exe，csv等，则会进行下载

* 若是浏览器可以解析的，如html，图片等，则不进行下载，而是预览。

H5的a标签增加了新属性download，加上之后，html、图片等等也会进行下载，但是只在同源下有效（即使前端、后端设置了允许跨域也不行），跨域需要另外的解决方案。

前端发送下载请求，后端一般会返回url或文件流。

### 2.1 返回下载url

几种解决方案；

- 直接把url放a标签里，a标签默认且只能get请求，所以url有长度限制，且download是H5特性IE有兼容问题。

- form表单下载，最传统无兼容性问题，form可以get或post请求，但无法下载浏览器可解析的文件，如html，图片等等。

- window.open() 或 location.href = url， 简单一行代码，缺点是url长度限制和编码限制，无法下载html，图片等。

- iframe，优缺点基本与直接用a标签一样，但兼容性和性能差。

- ajax请求获取下载url，再生成a标签下载。

除了ajax的方案都有无法监听返回是否成功和进度，无法携带token的问题。

以下是ajax请求uri生成a标签的方案：

注意，虽然a加了download，但：

* 要跨域的可解析文件不下载而是打开，无法解析的才能下载，就和没加download一样

* 同源的所有文件都能下载，其实这就是download的功能

（1）前端

```
<script setup lang="ts">
import { ref } from "vue";
import axios from "axios";

async function download() {
  const res = await axios({
    url: "http://localhost:8000/download",
    method: "get",
    params: {
      //...
    },
  });
  let url = res.data.url, fileName = res.data.fileNmae;
  let ele = document.createElement("a");
  ele.style.display = "none";
  ele.href = url;
  ele.download = fileName;
  document.querySelectorAll("body")[0].appendChild(ele);
  ele.click();
  ele.remove();
}
</script>

<template>
  <button @click="download">下载</button>
</template>

<style lang="less" scoped></style>
```

（2）后端（express版）：

```
const express = require("express");
const cors = require("cors");

const app = express();
app.use(cors());

//现在public文件夹下放要被下载的文件
app.use(express.static("./public"));

app.get("/download", (req, res) => {
  console.log(123);
  //根据req的参数得到要下载的文件url，这里就不管参数直接返回路径了
  res.send({
    url: "http://localhost:8000/lgx.html",
    fileName: "lgx.html",
  });
});

app.listen(8000, () => {
  console.log("start");
});
```

### 2.2 返回文件流

url下载最大的问题就是跨域情况下无法下载浏览器可预览的html，图片等文件，文件流式一种解决方案，一般返回blob或base64。

流程是ajax获得文件流后，转化成本地url再用a标签进行下载，可以看出，虽然解决了跨域问题，但是它相当于先下载完成后再出现文件保存框，用户体验性不好，若果文件太大，等待时间更久。

以下是文件流为blob的代码：

（1）前端

```
<script setup lang="ts">
import { ref } from "vue";
import axios from "axios";

async function download() {
  let res = await axios({
    url: "http://localhost:8000/download",
    method: "get",
    responseType: "arraybuffer",  //或者blob
    params: {
      //...
    },
  });

  //将文件流转为url后下载
  if (!res) {
    console.log("下载失败");
    return;
  }
  let blob = new Blob([res.data], {
    type: "image/png", //可以网上查阅blob.type
  });
  let url = window.URL.createObjectURL(blob);
  let ele = document.createElement("a");
  ele.style.display = "none";
  ele.href = url;
  ele.download = "123"; //有了blob的type，如果fileName没有后缀，后缀也会会自己加上
  document.querySelectorAll("body")[0].appendChild(ele);
  ele.click();
  ele.remove();
}
</script>

<template>
  <button @click="download">下载</button>
</template>

<style lang="less" scoped></style>
```

（2）后端

如果有压缩后再给前端下载的话可以使用compressing

```
npm install --save compression
```

```
// download/controller.ts
import { Controller, Get, Res } from "@nestjs/common";
import { Response } from "express";
import { join } from "path";

@Controller("download")
export class DownloadController {
  @Get()
  download(@Res() res: Response) {
    //下载 /dist/aaa 目录下的文件
    /*
    可以访问 服务器地址/download 下载
    可以 <a href="服务器地址/download" /> 下载
    可以 window.open('服务器地址/download') 下载
    可以将文件流转为url后下载
    */

    /* 方式一
    res.download(join(__dirname, "../aaa/1679373780635.png"));
    */

    /* 方式二，fs将文件转为文件流

    */

    /*方式三  compressing压缩并转为文件流
    // 下载 /dist/aaa 目录下的文件
    const tarStream = new zip.Stream();
    await tarStream.addEntry(join(__dirname, "../aaa/lgx.png"));
    // 设置相应头
    res.setHeader('Content-Type', 'application/octet-stream');
    res.setHeader('Content-Disposition', 'attachment; filename=lgx.zip');
    // 返回流
    tarStream.pipe(res);
    */
  }
}
```

### 2.3 大文件下载

### 2.4 下载封装成工具类

方便使用：

```
interface DownloadInterface {
  aDownload: (url: string, fileName: string) => void;
  streamDownload: (stream: Blob, fileType: string, fileName: string) => void;
  bigDownload: () => void;
}

export default class Download implements DownloadInterface {
  public static async aDownload(url: string, fileName: string): void {
    let ele = document.createElement("a");
    ele.style.display = "none";
    ele.href = url;
    ele.download = fileName;
    document.querySelectorAll("body")[0].appendChild(ele);
    ele.click();
    ele.remove();
  }

  public static async streamDownload(stream: Blob, fileType: string, fileName: string): void {
    let blob = new Blob([stream], {
      type: fileType, //可以网上查阅blob.type
    });
    let url = window.URL.createObjectURL(blob);
    let ele = document.createElement("a");
    ele.style.display = "none";
    ele.href = url;
    ele.download = fileName; //有了blob的type，如果fileName没有后缀，后缀也会会自己加上
    document.querySelectorAll("body")[0].appendChild(ele);
    ele.click();
    ele.remove();
  }

  public static bigDownload(): void {

  }
}
```

# 七、Web Socket

HTML5的新特性，之所以不记在HTML笔记或ajax笔记里，是因为它需要结合后端。

WebSocket是一种网络通信协议，可以实现全双工通信，常用于实现聊天室等。

http是单向的，通过客户端发请求，服务端响应回去；而WebSocket可以服务端主动推送给客户端。

（1）后端

安装依赖：

```
npm install --save @nestjs/websockets @nestjs/platform-socket.io
```

创建res，选择WebSockets：

```
nest g res xxx
```

```
// xxx.gateway.ts
import {
  WebSocketGateway,
  SubscribeMessage,
  MessageBody,
  ConnectedSocket,
} from '@nestjs/websockets';
import { WebSocketServer } from '@nestjs/websockets/decorators';
import { Server, Socket } from 'socket.io';
import { SocketService } from './socket.service';

@WebSocketGateway({
  cors: true, //允许跨域
})
export class SocketGateway {
  @WebSocketServer()
  private server: Server;

  private count: number = 0;

  constructor(private readonly socketService: SocketService) {}

  //监听连接
  async handleConnection(client: Socket): Promise<string> {
    console.log(`用户${client.handshake.query.userId}已连接`);
    /*client.join()
     * 类似于哈希表
     * 用户连接后，将此用户加入到自己独立的房间（Room）中；this.server.to('RoomName').emit()可以给该房间中的用户发送消息
     * client可以加入多个房间；给单独一人的房间emit就是私聊，多人房间emit就是群聊
     * 广播可以设置一个所有用户的房间emit实现，也可以client.broadcast()实现；下面两种方式都有演示
     * 虽然join的信息是存于内存中，但socket.io内部做了优化，即使是大型应用页很难出现内存不够的情况
     */
    client.join(client.handshake.query.userId);

    const clients = await this.server.fetchSockets();
    this.count = clients.length;

    //public为所有人的公告房间，用来广播
    //群聊也是一样的，就不演示了
    client.join('public');
    this.server.to('public').emit('broadcastRes', {
      message: `用户${client.handshake.query.userId}已连接`,
      count: `总人数：${this.count}人`,
    });
    return '连接成功';
  }

  //监听断开
  async handleDisconnect() {
    this.count--;
    this.server.to('public').emit('broadcastRes', {
      count: `总人数：${this.count}人`,
    });
  }

  @SubscribeMessage('socketTest1')
  socketTest1(@MessageBody() data: any) {
    return this.socketService.socketTest1(data);
  }

  @SubscribeMessage('socketTest2')
  socketTest2(@MessageBody() data: any) {
    return this.socketService.socketTest2(data);
  }

  @SubscribeMessage('broadcast')
  broadcast(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
    return this.socketService.broadcast(client, data);
  }

  @SubscribeMessage('privatechat')
  privatechat(@MessageBody() data: any) {
    return this.socketService.privatechat(this.server, data);
  }
}
```

```
// xxx.service.ts
import { Injectable } from '@nestjs/common';
import { Server, Socket } from 'socket.io';

@Injectable()
export class SocketService {

  //前后端交互测试1, 接收与返回数据
  socketTest1(data: any) {
    console.log('前端发来的数据', data);
    return {
      msg1: '测试1',
      msg2: '测试2',
    };
  }

  //前后端交互测试2, 接收与返回数据，不同的是返回的数据前端需要另外监听
  socketTest2(data: any) {
    console.log('前端发来的数据', data);
    return {
      event: 'socketTest2Res',
      data,
    };
  }

  //广播
  broadcast(client: Socket, data: any) {
    //给除了发送者的所有人广播
    client.broadcast.emit('broadcastRes', data);
    //给发送者自己返回消息
    return data;
  }

  //私聊
  privatechat(server: Server, data: any) {
    server.to(data.userId).emit('privatechatRes', data.text);
    //也给发送者返回
    return data.text;
  }
}
```

（2）前端

安装依赖，版本要与后端的一样，防止出错：

```
npm install --save socket.io-client
```

```
// xxx.vue
<script setup lang="ts">
import { ref, reactive, onMounted, inject } from "vue";
import { io, Socket } from "socket.io-client";

//这里就用时间戳暂时代替数据库的userId
const userId = ref(new Date().getTime());
const usersId = ref<string[]>([]);

//socket配置
const socket: Socket = io("http://localhost:3000", {
  autoConnect: false, //关闭自动连接
  // 后端通过 client.handshake.query 获取
  query: {
    userId: userId.value,
  },
});

//基本的数据交互---------------------------------------------------------------------
socket.emit("socketTest1", { test: "前端发来的测试数据" }, (data: any) => {
  console.log("后端返回的测试数据", data);
});

socket.emit("socketTest2", { msg1: "前端发来的测试数据" });
socket.on("socketTest2Res", (data: any) => {
  console.log(data);
});
//------------------------------------------------------------------------------------

//广播--------------------------------------------------------------------------------
function sendBroadcast() {
  socket.emit("broadcast", { msg1: "这是一条广播信息" }, (data: any) => {
    console.log(data);
  });
}
socket.on("broadcastRes", (data: any) => {
  console.log(data);
});
//------------------------------------------------------------------------------------

//私聊---------------------------------------------------------------------------------
const privatechat = reactive({
  userId: "",
  text: "",
});
function sendPrivatechat() {
  if (!privatechat.userId || !privatechat.text) return;
  socket.emit("privatechat", privatechat, (data: any) => {
    console.log(data);
  });
}
socket.on("privatechatRes", (data: any) => {
  console.log(data);
});
//-------------------------------------------------------------------------------------

//连接服务器
onMounted(() => {
  socket.connect({}); //连接socket服务器
});
</script>

<template>
  <div>
    <button @click="sendBroadcast">发送广播</button>
  </div>
  <table>
    <tr>
      <td>私发给：</td>
      <td><input type="text" v-model="privatechat.userId" /></td>
    </tr>
    <tr>
      <td>内容：</td>
      <td><input type="text" v-model="privatechat.text" /></td>
    </tr>
    <tr>
      <td></td>
      <td><button @click="sendPrivatechat">发送</button></td>
    </tr>
  </table>
</template>

<style lang="less" scoped></style>
```

以上，只是演示了websocket最核心用法，像一些基本的空值判断都没弄。

知道了这些websocket核心用法，可以在此基础上，配合数据库增加注册登录、好友，群组等等功能。
