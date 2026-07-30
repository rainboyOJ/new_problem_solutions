---
title: "搜索入门题单"
description: "从递归枚举、回溯剪枝到 DFS、BFS 和网格搜索，建立搜索建模与状态去重的基础。"
order: 35
---

# 搜索入门题单

搜索题的重点不是把递归写出来，而是明确三件事：状态是什么、下一步有哪些选择、什么时候可以剪枝或判重。

建议每道题都先写出最直接的搜索，再记录搜索树的规模和重复状态，最后说明优化消除了哪一部分重复。

## 一、递归与枚举

先练习把“选择一个对象”翻译成递归层，把“不能重复或必须满足条件”写成约束。

- [ ] [[problem: luogu,P1706]] · [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)
- [ ] [[problem: luogu,P1157]] · [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)
- [ ] [[problem: luogu,P1036]] · [P1036 选数](https://www.luogu.com.cn/problem/P1036)
- [ ] [[problem: luogu,P1219]] · [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
- [ ] [[problem: luogu,P1605]] · [P1605 迷宫](https://www.luogu.com.cn/problem/P1605)

## 二、网格 DFS 与连通块

网格题是图搜索最直观的入口。先把四联通、八联通和边界条件写清楚，再考虑是否需要标记数组。

- [ ] [[problem: luogu,P1451]] · [P1451 求细胞数量](https://www.luogu.com.cn/problem/P1451)
- [ ] [[problem: luogu,P1596]] · [P1596 Lake Counting S](https://www.luogu.com.cn/problem/P1596)
- [ ] [[problem: luogu,P1162]] · [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
- [ ] [[problem: luogu,P1141]] · [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
- [ ] [[problem: atcoder,ABC007C]] · [ABC007 C 幅優先探索](https://atcoder.jp/contests/abc007/tasks/abc007_3)
- [ ] [[problem: atcoder,ABC088D]] · [ABC088 D Grid Repainting](https://atcoder.jp/contests/abc088/tasks/abc088_d)

## 三、BFS 与最短步数

当每次移动代价相同时，BFS 的层数就是最短距离。要特别注意起点入队时机和第一次到达状态的含义。

- [ ] [[problem: luogu,P1443]] · [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
- [ ] [[problem: luogu,P1135]] · [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)
- [ ] [[problem: luogu,P1825]] · [P1825 Corn Maze S](https://www.luogu.com.cn/problem/P1825)
- [ ] [[problem: luogu,P3956]] · [P3956 棋盘](https://www.luogu.com.cn/problem/P3956)
- [ ] [[problem: luogu,P5318]] · [P5318 【深基18.例3】查找文献](https://www.luogu.com.cn/problem/P5318)

## 四、搜索建模与剪枝

这一组开始出现状态压缩、传送、带代价移动和搜索顺序。不要一开始就套模板，先画出状态图。

- [ ] [[problem: luogu,P1120]] · [P1120 小木棍](https://www.luogu.com.cn/problem/P1120)
- [ ] [[problem: luogu,P1433]] · [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)
- [ ] [[problem: luogu,P1126]] · [P1126 机器人搬重物](https://www.luogu.com.cn/problem/P1126)
- [ ] [[problem: luogu,P1379]] · [P1379 八数码难题](https://www.luogu.com.cn/problem/P1379)

## 复盘要求

每道题完成后补充：

```text
状态由什么组成：
每次搜索有哪些选择：
是否存在重复状态：
剪枝条件为什么正确：
```
