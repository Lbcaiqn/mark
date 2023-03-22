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
nest g resource xxx
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
import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { NestExpressApplication } from '@nestjs/platform-express/interfaces';
import {join} from 'path';

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
import { IsNotEmpty, IsNumber } from "class-validator";

export class CreateLoginDto {
  //没有做任何验证
  name: string;
  
  //使用class-validator，这里演示非空和限定类型为number
  @IsNotEmpty()
  @IsNumber()
  age: number
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
      throw new HttpException(fail, HttpStatus.BAD_REQUEST);
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



#### 2.3.4 拦截器

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
// /src/common/Response.ts
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
          messgae: "666",
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

（2）异常拦截器

当路由异常时生效，可以自定义一些异常信息

定义异常拦截器：

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
    const ctx = host.switchToHttp();

    const req = ctx.getRequest<Request>(),
          res = ctx.getResponse<Response>(),
          next = ctx.getNext<NextFunction>();

    res.status(exception.getStatus()).json({
      sucess: false,
      time: new Date(),
      path: req.url,
      status: exception.getStatus(),
      data: exception.message
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

## 3 服务

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



## 三、CRUD和连接数据库

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

  app.use(cors());
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
  @ApiQuery({name: 'username', description: '用户名'})
  @ApiQuery({name: 'password', description: '密码'})
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
  //没有做任何验证
  @ApiProperty({example: 'lgx'})
  name: string;
}


```

还有很多Apixxx，每个Apixxx也有很多参数，详见文档，这里只列举最常用的。



## 五、Web Socket

HTML5的新特性，之所以不记在HTML笔记或ajax笔记里，是因为它需要结合后端。

WebSocket是一种网络通信协议，可以实现全双工通信，常用于实现聊天室等。

http是单向的，通过客户端发请求，服务端响应回去；而WebSocket可以服务端主动推送给客户端。

前端：

这是原生js的写法，

后端：

##

# 六、常见功能实现

## 1 注册/登录/鉴权/权限管理

需要的第三方库

```
const bcryptjs = require('bcryptjs')
const jsonwebtoken = require('jsonwebtoken')
```

### 1.1 注册

后端需要定义用户的表，账号限制唯一u，密码需要bcrypt加密

```//
//用户表定义
const bcryptjs = require('bcryptjs')
const mongoose = require('mongoose')
mongoose.connect('mongodb://localhost:27017/vnpDB',{
  useNewUrlParser: true
})

const Users = mongoose.model('users',new mongoose.Schema({
  username: {
    type: String,
    unique: true  //限制账号唯一，若重复会报错
  },
  password: {
    type: String,
    set(val){
      return bcryptjs.hashSync(val,10)  //加密
    }
  }
}))

module.exports = {
  Users
}
```

注册的接口，当账号已存在时需捕获异常

```
const {Users} = require('./db/Users.js')
app.post('/logup',async (request,response,next) => {
  try {
    await Users.create({
      username: request.body.username,
      password: request.body.password
    })
    response.send('注册成功')
  }
  catch(err) {
    response.send('注册失败')
  }
})
```

前端代码略，就是一些表单的验证和发送请求而已

### 1.2 登录

有账号密码登录、手机验证码登录、微信登录等。

状态保持：用某种方法保持登录状态，不需要重复登录。目前有cookie，session，jsonwebtoken三种，jsonwebtoken最常用。

后端：

（1）账号密码登录

先判断账号是否存在，再匹配密码，匹配成功返回jwt（jsonwebtoken），用于鉴权

① 后端代码

```
//私钥为了安全一般是不可见的，保存在本地文件中，不存放于git，这里为了方便就直接定义为了变量
const SECRCT = 'asf34g35s1g56erssa'

app.post('/login',async (request,response) => {
  let user = await Users.findOne({
    "username": request.body.username
  })
  if(!user) return response.send('用户名不存在')
  let passwordValid = bcryptjs.compareSync(request.body.password,user.password)
  if(!passwordValid)  return response.send('密码错误')
  //jwt用users表的id和私钥签名
  let token = jsonwebtoken.sign({
    id: String(user._id)
  },SECRCT)
  response.send({
    user,
    token
  })
})
```

② 前端代码

```
//账号密码登录
请求.then(res => {
  console.log(res.data.token);
})
//微信登录
wx.login();
```

③ 拿到token后，将token存放到storage和vuex中

token作为登录凭证来保持持久登录，无需账号密码。

那既然都存到storage了，为什么还要存到vuex中？

- 相对来说vuex的存取比storage方便一些，且配合vuex的持久化存储插件可以更加方便

- vuex的数据是响应式的，而storage不是响应式，有时候可能会考虑这一点

- vuex存在内存中，而storage存在本地磁盘中，在内存中存取数据会快一点

④ 当给需要登录的接口发请求时，携带token

后端的接口总体分为需要token鉴权和不需要token鉴权两种。一般后端需要token鉴权的接口会统一命名，如果是统一命名就适用下面的方法，如果不是就另找方法。

```
//可以在请求拦截器上根据url判断是否需要token，给请求头加上token
//比如需要token的接口的url都包含一个'/v2/''
请求拦截器(config => {
  if(/\/v2\//.test(config.url)){
    let token: string = JSON.parse(localStorage.getItem('mainStore') as string) ? JSON.parse(localStorage.getItem('mainStore') as string)?.token : '';
    config.headers!.Authorization = token;

    //如果是ts，headers可能为空而报错，需要非空断言
    //config.headers!.Authorization = token;
  }
  return config;
})
```

⑤ 路由跳转注意事项

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
        params和query，切回保存在params对象和query对象中
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
      if (!this.$route.query.redirect) router.push("/Home");
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

- NotFound
  
  配置NotFound路由

（2）手机验证码登录

（3）微信登录

退出登录

发请求，成功后需要清空storage和vuex的token

### 1.3 鉴权

在进行数据的增删改查的时候，需要鉴权，将token发送给后端，鉴权成功才能进行增删改查，以查询数据为例：

前端代码：

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

后端代码：

响应头需要加上Authorization

为了简化代码，将鉴权逻辑定义为express中间件，每个需要鉴权的url调用这个中间件即可。

```
async function auth(req,res,next){
  let token = req.headers.authorization
  //解析jwt中的user的id
  let {id} = jsonwebtoken.verify(token,SECRCT)
  let user = await Users.findById(id)
  res.user = user
  next()
}

//在执行回调之前，会先执行auth中间件
app.get('/getProfile',auth,(req,res) => {
  res.send(res.user)
})
```

### 1.4 权限管理

权限管理分为前端权限管理和后端权限管理，前后端未分离的时代权限都是由后端管理的，但是在前后端分离的时代，前端也需要权限管理。

权限的本质就是对数据库中的数据的增删改查

后台管理系统一般admin需要有对用户、角色、权限、菜单的增删改查

#### 1.4.1 后端权限管理

后端权限通过token来鉴权增删改查的操作，是权限管理的最后一道关口

#### 1.4.2 前端权限管理

前端权限管理仅仅是针对于视图层展示和请求的发送，并不能管理数据库的增删改查。

RBAC（基于角色的权限控制）：权限并不是针对于某个用户，而是针对于某类角色，一个用户可能有多个角色，在数据库设计上可以设计成用户表、角色表、权限表。

前端登录成功时，会同时发送该用户具备的权限。

但是前端的权限管理也是非常有必要的，主要有以下几点：

- 减少用户非法操作的可能性，如隐藏需要权限的按钮。

- 尽可能排除非必要和不具备权限的请求，减少服务器压力，尽管这些请求也一定不会成功

- 提高用户使用体验，如用户在浏览器输入url，若此url需要登录就跳转登录页，若此url需要权限且用户不具备权限则跳转404页面等

前端权限管理分为四个方面：

- 菜单权限：主要指后台管理系统的侧边菜单栏，登录后根据后端返回的菜单权限，只展示该用户具备权限的菜单。菜单权限控制一般都要配合页面的权限控制。

- 页面/路由权限：用户只能访问自己具备权限的页面，若用户通过非法操作（如输入不具备权限的url，或控制台进行路由跳转），应当强制跳转到登录页或404页。

- 按钮/超链接权限：一些页面可能几类角色都有权限进入（或非法进入），而该页面的按钮则具备权限，如普通角色只有查看权，而管理员有编辑、删除等按钮，那么这些按钮就应该根据权限来显示隐藏/启用禁用。

- 请求权限：若通过以上操作还不能规避用户非法操作，如用户非法进入页面，通过控制台修改按钮为显示/启用，那么在发送请求时，应当根据权限在前端层面请求发起时就拒绝发送请求。

可以看出这四个方面是循序渐进的。由前端进行的一系列权限控制之后若用户还是能够非法的操作对数据进行增删改查，后端通过token鉴权也能规避。

#### 1.4.3 前端权限管理代码实现

（1）场景模拟

某系统具备七个页面，分别是登录页，404页、个人主页，订单信息页和管理页（用户管理、商品给管理），具有两种角色，分别是普通用户和管理员。

登录页和404页在未登录时就能访问，

个人主页需要登录但是所有角色都可访问。

订单信息页和管理页需要登录且只有管理员具备权限访问。其中用户管理页和商品管理页是管理页的嵌套路由

管理员能在用户管理页设置各个用户的各项权限

如管理员的菜单如下：

个人信息

订单信息

管理

---用户管理
---商品管理

（2）菜单权限控制

默认路由为f个人主页，未登录时跳转到登录页，登录同时后端会返回权限列表，普通用户的菜单只有个人主页，管理员的菜单有个人主页、订单信息和管理（用户管理、商品管理）。

路由配置共有一条默认路由，一条NotFound路由和六条页面路由。其中管理页路由又有两个嵌套路由

但是由于菜单控制一般都要配合页面控制，所以路由配置不能写死，初始只配置不需要权限的路由，需要权限的路由根据权限列表由动态路由addRoute()动态添加

后端返回的菜单权限有可能是只有需要权限的菜单（如管理），也有可能是连个人主页也返回，这里就以只返回需要权限的菜单。

路由配置：

```
const route = [
  {
     // 默认路由
     path: '/',
     redirect: '/profile'
  },
  {
     //NotFound路由
     path: '/:catchAll(.*)',
     component: () => import(...)  
  },
  {
     path: '/login',
     component: () => import(...)  
  },
  {
     path: '/profile',
     component: () => import(...)  
  }
]
```

登录拿到权限列表后，就可以实现菜单/路由权限，分两种：

（1）后端实现

后端把权限信息、菜单信息和路由信息都返回了，前端必须要有一个菜单/路由管理的页面。

适合体量大，菜单变动多的项目。

缺陷：前后端开发人员需要高度配合。此外，后端返回的路由信息不一定是规范的，需要前端自行转换。

```
/*
管理员登录，后端返回的数据模拟：
token: '...',
rights:[
  {
    ...
  },
  {
    name: 'manage',
    title: '管理',
    icon: 'xxx',
    path: '/manage',
    url: '/Manage/Manage.vue',
    children: [
      ...
    ]
  }
]
普通用户登录rights则是空数组
*/

axios({
  //登录
}).then(res => {
  /* 拿到token并保存到storage和vuex的操作... */
  //拿到菜单权限，并保存到本地和vuex
  for(let i of res.data.rights){
    //若有多级菜单，就多套一层循环，视情况是配置普通路由还是嵌套路由
    this.$router.addRoute({
      path: i.path,
      name: i.name,
      component: () => import('...' + i.componentURL)
    ))
  }
  localStorage.set('rights',res.data.rights)
  this.$store.commit('setRights',res.data.rights)
})
```

（1）前端实现

后端不返回路由信息或菜单信息，这两个信息存储在前端，拿到权限信息后，在丛中筛选出对应的路由、菜单。

适合体量小，菜单变动少的项目，实现起来比较简单。

缺陷：路由信息、菜单信息存储在前端，一旦要修改这些信息就要重新打包前端。

① 前端实现方案1，后台只返回了菜单信息和权限信息，没有路由信息

需要前端先定义全部路由的数组，根据后台返回的权限来筛选出相应的路由并动态添加到路由配置

返回的权限信息可能是标识字符串，也可能是是角色信息，若是角色信息，则meta的内容就是角色，根据角色筛选权限，若是标识，就是下面的代码

```
/*
管理员登录，后端返回的数据模拟：
token: '...',
rights:[
  {
    ...
  },
  {
    name: 'manage',
    title: '管理',
    icon: 'xxx',
    children: [
      ...
    ]
  }
]
普通用户登录rights则是空数组
*/
//先定义好全部路由,若后台返回的name能和路由的name对应，也可以不要meta
const allRoutes = [
  {
    ...
  },
  {
    path: '/manage',
    url: '/Manage/Manage.vue',
    meta: {
      name: 'manage'
    },
    children: [
      ...
    ]
  }
]
//筛选路由的方法
function filteRoutes(userRoutes, allRoutes){
    let routes = [], allRoutesCopy = 深拷贝(allRoutes)
    for(let userR of userRoutes){
        for(let allR of allRoutesCopy){
            if(userR.name == allR.meta.name){
                if(userR?.children?.length > 0){
                  allR.children = filteRoutes(userR.children,allR.children)
                }
                else delete allR.children
                routes.push(allR)
            }
        }
    }
    return routes
}

//登录拿到权限列表的代码略
```

② 前端实现方案2，后端只返回权限信息，菜单信息和路由信息都不返回

需要在①的基础上在meta加入菜单信息即可

③ 前端实现方案3，不太推荐，后端只返回权限信息和路由信息，不返回菜单

把①的先定义全部路由改为先定义全部菜单，筛选路由改为筛选菜单即可

其他：

权限菜单路由信息和token一样需要持久化存储。

动态路由保持持久化，在App.vue的create()中，若有token，则根据storage的rights来重新addRoute()

退出登录时，需要清除storage和vuex的token和权限信息，removeRoute()对应路由或代码刷新页面

缺陷就是用户可以通过控制台自己addRoute()再push()达到非法进入页面的目的

若有动态默认路由的需求，可使用addRouter添加默认路由，修改默认路由通过router.getRoutes()[0].redirect == '/xxx'

（3）页面/路由权限控制

上面的NotFound路由和动态路由其实已经涉及了大部分页面/路由控制，就差一个登录状态的判断了

组件内守卫或独享守卫配置，缺陷就是每一个需要登录的页面都要配置；

```
//以组件内守卫为例
beforeRouteEnter(to,from,next){
  if(sessionStorage.getItem('token') != null) next()
  else  next({path: '/login'})
}

/*
路由守卫中，next({path: '/login'})跳转到登录页时，可以正常跳转，但是报错 ...via a navigation...
解决：
路由文件中：
const originalPush = VueRouter.prototype.push
VueRouter.prototype.push = function push(location, onResolve, onReject){
  if (onResolve || onReject) return originalPush.call(this, location, onResolve, onReject)
  return originalPush.call(this, location).catch(err => err)
}
其本质是跳转报错时，catch捕获异常，所以还是没有解决根本的问题，只是没有报错了
*/
```

也可以全局前置守卫中配置，更方便：

```
//路由的js文件中
...
router.beforeEach((from,to,next) => {

  if(sessionStorage.getItem('token') != null) next()
  else  next({path: '/login'})
})
```

（4）按钮/超链接权限控制

后端返回的权限列表里，可能也会有按钮的权限，一种是返回增删改查的权限，按钮根据增删改考察的类型来设置权限，一种是返回特定按钮的布尔值。在筛选路由的同时可以把按钮权限存到对应路由配置的meta中。

根据权限信息来v-if，v-show来隐藏，但是比较麻烦。最方便的实现就是全局自定义指令，需要权限的按钮绑定自定义指令，自定义指令内部根据当前路由的meta取得权限信息，来隐藏/禁用/删除按钮。

【警告】在某些情况下，使用自定义指令v-permission将无效。例如：元素UI的选项卡组件或el表格列以及其他动态渲染dom的场景。您只能使用v-if来执行此操作

（5）请求权限控制

分为token鉴权和截断无权限请求

token鉴权不再赘述

截断无权限请求：在发送请求前，先根据当前路由的meta的权限信息判断是否有权发送。在筛选路由的同时可以把请求权限存到对应路由配置的meta中。

后端接口如果设计比较规范的，如restfulAPI，可能会返回增删改查的权限，前端根据请求类型的设置权限

## 2 文件上传

### 2.1 文件上传可能需要的自定义方法

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

### 2.2 自定义API封装成工具类

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

### 2.3 文件上传前需要知道的内容

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

### 2.4 文件上传的不同实现

#### 2.4.1 单文件上传（FormData）

post请求，请求体放FormData，设置请求头为：

```
headers: {"Content-Type": "multipart/form-data"}
```

但是这样设置有时候会报错，说找不到边界，可以换成：headers: false

前端代码：

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

后端代码（express版）：

```
const express = require("express");
const fs = require("fs");
const multer = require("multer");
const cors = require("cors");

const app = express();
app.use(cors());

//解析FormData并放到对应目录的中间件
const UploadMiddle = multer({
  dest: "./upload/",
});

//multer为了防止重名覆盖原有文件，会将文件名命名为随机序列并且没有后缀名，需要自己重新命名
app.post("/upload", UploadMiddle.any(), (req, res) => {
  const newName = "./upload/" + req.files[0].originalname;
  fs.rename(req.files[0].path, newName, (err) => {
    if (err) res.send("上传失败");
    else res.send("上传成功");
  });
});

app.listen(8000, () => {
  console.log("server");
});
```

后端代码（nest版）：

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

#### 2.4.2 单文件上传（base64）

适合图片，音频，视频，图片居多

post请求，请求体base64

请求头：

```
headers:{'Content-Type':'application/x-www-dorm-urlencoded'}
```

### 2.4.3 多文件上传

选择文件，一是file表单增加属性multiple，一次选多个，在change事件中将files数组的元素全append到FormData，二是不加multiple，一次选一个，每次change将files[0]的文件append到已声明的FormData，最终都是得到含有多个file对象的FormData

上传文件也有两种方式，一是一次性上传全部file（但无法获得进度），后端通过req.files得到各个file信息并改名。二是每个file单独上传（能获得每个file的进度），都断与单文件上传一样。

### 2.4.4 大文件上传（切片+断点续传）

前端代码：

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

后端代码（express版）：

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

## 3 文件下载

正常情况下，部署到静态文件夹的文件，浏览器输入或a标签的href是这个文件的url：

* 若文件是浏览器无法解析的，如exe，csv等，则会进行下载

* 若是浏览器可以解析的，如html，图片等，则不进行下载，而是预览。

H5的a标签增加了新属性download，加上之后，html、图片等等也会进行下载，但是只在同源下有效（即使前端、后端设置了允许跨域也不行），跨域需要另外的解决方案。

前端发送下载请求，后端一般会返回url或文件流。

### 3.1 返回下载url

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

前端代码：

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

后端代码（express版）：

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

### 3.2 返回文件流

url下载最大的问题就是跨域情况下无法下载浏览器可预览的html，图片等文件，文件流式一种解决方案，一般返回blob或base64。

流程是ajax获得文件流后，转化成本地url再用a标签进行下载，可以看出，虽然解决了跨域问题，但是它相当于先下载完成后再出现文件保存框，用户体验性不好，若果文件太大，等待时间更久。

以下是文件流为blob的代码：

前端代码：

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

后端代码（express版）：

```
const express = require("express");
const cors = require("cors");

const app = express();
app.use(cors());

//现在public文件夹下放要被下载的文件
app.use(express.static("./public"));

app.get("/download", (req, res) => {
  //根据req的参数得到要下载的文件url，这里就不管参数直接返回路
  /*
  可以访问 服务器地址/download 下载
  可以 <a href="服务器地址/download" /> 下载
  可以 window.open('服务器地址/download') 下载
  可以将文件流转为url后下载
  */
  res.download("./public/lgx.png");
});

app.listen(8000, () => {
  console.log("start");
});
```

后端代码（nest版）：

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

### 3.3 大文件下载

### 3.3 下载封装成工具类

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

## 
