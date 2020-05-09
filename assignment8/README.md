
# kingil_homework8 email: kingilustc@163.com

## 实现[5points]格式正确；可以正确编译运行
结果见/images gif
## 实现[5points]连接绳子约束，正确的构造绳子
1 注意绳子长度为0或者1的时候，直接返回，没啥意义
2 处理好开头和结尾就可以，注意是push_back不是pushback。。。

## 实现[5points]半隐式欧拉法
//semi-implicit method
m->velocity += a * delta_t;
m->position += m->velocity * delta_t;

## 实现[5points]显式欧拉法 
//Explicit method
m->position += m->velocity * delta_t;
m->velocity += a * delta_t;

+ 以上显式和半隐式欧拉方法，编码上只是调换了计算x和v的顺序。
只要能理解，我们拿到的value就是t时刻的value，我们要计算的value就是t+1时刻的value，就可以正确进行过程计算了。
+ 两个方法放在同一个方法里，控制true段落调用，比较无脑。。
+ 对于欧拉方法调试，由于算法本身不稳定，所以需要加长步长来进行显示，否则会有跳变和发散的结果。最终录屏是256的步长。

## 实现[10points]显式 Verlet

先实现力，然后按照pdf里面的公式实现即可。注意每次循环后将质点的力归位零。
下面一起说。
## 实现[5points]阻尼
这里要注意的是，t-1，t以及t+1作正确的对应。
// TODO (Part 3.1): Set the new position of the rope mass
Vector2D lastposition = m->position;
// TODO (Part 4): Add global Verlet damping
float dampfactor = 0.00005;
m->position = m->position +  (1 - dampfactor) * (m->position - m->last_position) + a * delta_t *delta_t;
m->last_position = lastposition;
