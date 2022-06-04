# 一、水平与垂直居中

- 文本居中
  
  text-align: center;        文本水平居中
  
  line-height: 盒子高度;  文本垂直居中

- 盒子居中
  
  1. margin实现
     
     margin: 0 auto;    只能实现水平居中
  
  2. 定位与margin，translate配合实现
     
     ```
         /*父盒子*/
         .father {
           position: relative;
           width: 200px;
           height: 200px;
           border: 1px solid #000;
         }
         /*子盒子方法一，绝对定位上左偏移50%后，再margin偏移一半子盒子宽高*/
         .son {
           position: absolute;
           top: 50%;
           left: 50%;
           margin-top: 50px;
           margin-left: 50px;
           width: 100px;
           height: 100px;
           border: 1px solid #000;
         }
         /*子盒子方法二，绝对定位偏移都为0，margin自动就能水平垂直居中*/
         .son {
           position: absolute;
           top: 0;
           right: 0;
           bottom: 0;
           left: 0;
           margin: auto;
           width: 100px;
           height: 100px;
           border: 1px solid #000;
         }
         /*子盒子方法三，translate实现*/
         .son {
           position: absolute;
           top: 50%;
           left: 50%;
           transform: translate(-50%,-50%);
           width: 100px;
           height: 100px;
           border: 1px solid #000;
         }
     ```
  
  3. flex实现
     
     display: flex;   justify-content: center;     align-items: center;

# 二、清除浮动

# 三、BFC（块级格式化上下文）

形成独立的渲染区域，形成一个隔离的独立的容器，使得容器内每个子元素的布局都不会影响外界的布局（也不会影响父元素本身）。

形成BFC的条件（符合任一条件就形成BFC）：

1. <html>根元素以及<body>

2. float值不为默认的none

3. position值不为relative

4. display值不为block 如：flex，inline-flex，inline-block，grid，inline-grid，table-xxx等等

5. overflow值不为默认的visible的块级元素

6. contain值为如下：layout，content，paint

7. 多列元素，即column-count或column-width值不为默认的auto碎

常见用法：

1. 清除浮动：子元素设置了浮动，父元素没有设置高度，此时父元素的高度就会塌陷。此时给父元素overflow: hidden;  使得整个父元素变成BFC元素，使得它的子元素浮动后不会影响到外界，高度不变，达到清除浮动的效果。

2. 浮动元素会覆盖未浮动元素：只需要将被覆盖的元素设置为BFC，如overflow:hidden，就不会覆盖了。

3. 解决外边距合并问题：若两个上下/左右排列的div分别设置了margin-top，margin-bottom，则他们之间的间距会变成top，bottom t中值较大的那一个。解决：将两个div分别放入两个BFC父元素中（注意左右排列的margin-left和margin-right不胡已出现这种情况）

4. margin塌陷问题：子元素设置margin-top后，子元素不生效，反而是父元素生效了，此时父元素的margin-top=父+子。解决：给父元素设置BFC就能解决。此外，给父元素一个参照，给父元素设置上边框或上内边距也能解决。

# 四、HTML相关

1. div与p区别
   
   就一个区别，p有自带的margin-top和margin-bottom值，而div都为0
