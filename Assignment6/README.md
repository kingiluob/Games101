# HomeWork6 Kingil kingilustc@163.com

# 准备工作

### renderer.cpp

将ass5中的函数搬过来即可。注意，由于我们要求的是ray的方向，所以并不用对dir做特殊处理。向量平移不变。

在调用的时候，注意构造正确的ray对象。同时传入初始depth。

### Triangle::getIntersection in Triangle.hpp

填充进关于相交相关的信息。

# [5 points] 

提交格式正确，包含所有需要的文件;代码可以在虚拟机下正确 编译运行。 

完成。全部代码已运行成功，结果见images/binary.ppm和相关代码

# [20 points] 

包围盒求交:正确实现光线与包围盒求交函数。 

完成。

求光线与aabb包围盒是否相交。我们所定义的包围盒的面都是平行于坐标轴的，所以光线跟每一对长方体外表面求交的时候，只需要计算一个特定的坐标轴即可。

t = (px -ox) / dx.

r然后tEnter就是最近的交点，也就是tx/y/zmin中的最大值。同理，出射点texit应该是minof(tx/y/zmax).满足

tEnter<tExit&& tExit>=0

注意用三目运算符简化代码。

在这里，dirIsNeg的作用其实特别好用。相当于给你标注了哪个坐标应该是怎么和光线的照射方向相关联的。

显然，如果ray的x为正，那么光线肯定首先相交到包围盒x值较小的点。也就对应到了txmin和txmax。

# [15 points]

 BVH 查找:正确实现 BVH 加速的光线与场景求交。 

完成。

Intersection BVHAccel::getIntersection(BVHBuildNode* node, const Ray& ray) const

这个代码写起来比较简单，思路比较清晰。参照老师课件的算法，如果是叶子结点，直接计算返回。如果不是，遍历左右孩子，返回距离较近的节点值。

注意的有两点：

1 构造正确的dirisNeg供相交函数调用

2 比较两次相交的distance来决定返回值



# [加分项 20 points]

 SAH 查找:自学 SAH(Surface Area Heuristic) , 正 确实现 SAH 加速，并且提交结果图片，并在 README.md 中说明 SVH 的实现 方法，并对比 BVH、SVH 的时间开销。(可参考 http://15462.courses.cs .cmu.edu/fall2015/lecture/acceleration/slide_024，也可以查找其他资 料) 

完成。

参考材料：

https://www.cnblogs.com/lookof/p/3546320.html

思路就是在每一次选取划分包围盒的那条线的时候，找一种当下花费代价最小的方案。

这个cost = na * pa + nb*pb

分别是，划分完成后两边的物体数量和包围盒的表面积。

便利各种分法，找到一个cost最优的方案。

算法思想还在研究中，初步的理解是跟光线射中的概率相关。物体表面积大了，概率也会大一些。cost相当于是一个期望，值越小，期望越低越好。

下面是我的结果：（由于cpp不是特别熟悉，所以取巧替代了recursive函数，实现了SAH方法。）撒谎给你面试BVH的结果，下面是SAH的结果。

test001:
BVH:
BVH Generation complete: 
Time Taken: 0 hrs, 0 mins, 0 secs

 - Generating BVH...

BVH Generation complete: 
Time Taken: 0 hrs, 0 mins, 0 secs

Render complete: ======================================================] 100 %
Time taken: 0 hours
          : 0 minutes
          : 16 seconds

SAH:
SVH Generation complete: 
Time Taken: 0 hrs, 0 mins, 11 secs

 - Generating SVH...

SVH Generation complete: 
Time Taken: 0 hrs, 0 mins, 0 secs

Render complete: ======================================================] 100 %
Time taken: 0 hours
          : 0 minutes
          : 15 seconds


