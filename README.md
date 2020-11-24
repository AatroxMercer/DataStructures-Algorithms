# 算法分析与设计

## 导论

- 算法复杂性计算
  - T_max
  - T_min
  - T_avg

## 子问题策略

#### 递归与分治

- 递归
  - 递归
  - 参照上一条
- 分治
  - 原问题的较小型式

- 二分搜索技术
- 棋盘覆盖
- 合并排序
- 快速排序
- 线性时间选择

> 1. 够短，**直接排序**
> 2. 按group_length为单位进行分组，把每一组的中位数置于数组当前最前
> 3. **线性时间选择**寻找分组中位数中的中位数
> 4. 使用找到的中位数的中位数，为基准，进行**大小比较划分**
> 5. 二分**线性时间选择**

- 最接近点对问题

  - 一维情况

  > 设当前最短间隔为d，点按x升序排列存储
  >
  > 1. 选定中间点为二分位置
  >
  > 2. 在当前二分位置，距离d的邻域内，至多有两个点

  - 二维情况

  > 设当前最短间隔为d，点按x升序排列存储
  >
  > 1. 选定x中间点二分
  > 2. 取当前二分位置，左右d的邻域
  > 3. 对于邻域中的点，只有一阶数量个点需要考虑

#### 动态规划

- 最优子结构
- 重叠子问题
- 备忘录方法
- 矩阵连乘问题
- 最长公共子序列
- 凸多边形最优三角划分
- 多边形游戏
- 电路布线
- 流水作业调度
- 0-1背包问题

#### 贪心

- 最优子结构
- 贪心选择性质
- 活动安排问题
- 哈夫曼编码
- Dijkstra 单源最短路算法
- 最小生成树
  - Prim算法
  - Kruskal算法（并查集）
- 多机调度问题的较好近似算法

## 解空间搜索

#### 解向量

- 子集树
- 排列树

#### 回溯法

> 一种穷举式搜索

- constraint 约束函数
- bound 限界函数
- 装载问题
- 批处理作业调度
- n后问题
- 0-1背包问题
- 旅行售货员问题
- 圆排列问题

#### 分支限界法

> 一种启发式搜索

- 约束函数+限界函数
- 优先队列
- Dijkstra 单源最短路径算法
- 装载问题
- 布线问题
- 0-1 背包问题

## NP问题

- 定义
  - P 确定性图灵机
  - NP 非确定性图灵机
- NP完全问题
  - Hamilton回路
  - 旅行售货员问题

