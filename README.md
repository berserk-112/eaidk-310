# 第十六届研电赛ARM命题基于eaidk-310的无人驾驶小车参赛思路
## 交通标志及红绿灯识别
 [在此](https://github.com/OAID/Tengine/blob/tengine-lite/examples/tm_yolofastest.cpp)基础上修改了部分代码
- 图像分类算法使用的是[Yolofastest](https://github.com/dog-qiuqiu/Yolo-Fastest)，可根据需要训练自己的模型,此仓库提供了一个训练好的模型
- 使用[Tengine-Convert-Tools](https://github.com/OAID/Tengine-Convert-Tools)转化训练好的模型
- 在eaidk-310上编译最新的Tengine [编译过程](https://github.com/OAID/Tengine/blob/tengine-lite/doc/compile.md)
- 在eaidk-310上编译cpp文件(相应的路径根据实际情况修改)
```shell
$ g++  tm_yolofastest.cpp `pkg-config --libs --cflags opencv` -I /home/openailab/Tengine-Lite/build/install/include/tengine/ -L /home/openailab/Tengine-Lite/build/install/lib -l tengine-lite -o yolofastest
```
- 摄像头链接310后运行程序
```shell
$ ./yolofastest -m ./yolo-fastest-1.1.tmfile 
```
