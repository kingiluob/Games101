
# kingil_homework7 email: kingilustc@163.com

## 实现[5points]格式正确；可以正确编译运行
结果见/images
## 实现[45points]正确实现PathTracing算法
基本上还是按照老师PPT里的算法思路。需要注意的几个要点是：
1 ws和-ws的方向一定要注意写对符号；
2 要对光源注意进行判断，否则会出现光源全黑的情况；
3 wo是负的ray的方向
未使用多线程的时候，时间大致是68min。（具体就没贴了，不小心clear了结果，再跑一次实在太慢）
提交的结果图片是

784*784，16个点的采样效果；

512*512,8个点的采样效果。

还有其他一些测试结果。为快速验证算法。



## 实现[10points]多线程
对cpp多线程不是特别熟悉，所以根据大家论坛上的讨论，网上google了omp的方法，具体参考：
https://blog.csdn.net/fengtian12345/article/details/80566491
由于在家编码，个人电脑配置一般，macbookpro2015early版本，双核CPU，所以使用多线程的提升比较有限，最后时间大致在60min，也没有尝试更高采样点。
注意的是用多线程以后，原程序中progress进度条加载是只需要执行一次的，所以这块代码应该独立出来。

其他结果：

84*84 2sample 分别是6s和5s。

## 未实现Microfacet模块

