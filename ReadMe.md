
##### 说明

C++ 实现的图片轮播

![Gif](./gif1.gif)


##### 消息处理

```c++
WM_CRAETE： 加载图片

WM_MOUSEMOVE：更新左右导航箭头显示

WM_LBUTTONUP： 响应自绘按钮事件

WM_PAINT： 按顺序绘制背景，图片，按钮

WM_TIMER: 实现自动轮播
```


##### V2版本 添加动画阻尼效果

实现逻辑，定时器刷新，频率为1秒24帧。

使用了硬编码，事先计算好图片每次移动的距离和显示的大小。

这个效果根据需求，自己填写修改，见 [Mapinter.cpp](CarouselMap/MyPainter.cpp)












