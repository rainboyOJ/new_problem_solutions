---
title: "图论入门题单"
description: "从图的存储、DFS/BFS 和连通性开始，逐步练习并查集、最短路、拓扑排序、最小生成树与强连通分量。"
order: 54
---

# 图论入门题单

图论入门的难点通常是建图，而不是背某个模板。每道题先明确顶点、边、方向和边权，再判断题目问的是连通性、最短路、依赖关系还是连通代价。

## 一、图的存储与遍历

先掌握邻接表、访问标记和 DFS/BFS 顺序。网格图可以看成特殊的隐式图。

- [ ] [[problem: luogu,P5318]] · [P5318 【深基18.例3】查找文献](https://www.luogu.com.cn/problem/P5318)
- [ ] [[problem: luogu,P3916]] · [P3916 图的遍历](https://www.luogu.com.cn/problem/P3916)
- [ ] [[problem: luogu,P1451]] · [P1451 求细胞数量](https://www.luogu.com.cn/problem/P1451)
- [ ] [[problem: luogu,P1141]] · [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
- [ ] [[problem: codeforces,20C]] · [Codeforces 20C Dijkstra?](https://codeforces.com/problemset/problem/20/C)

## 二、连通性与并查集

静态连通块可以 DFS/BFS，边不断加入的连通性则适合并查集。P2024 作为带权并查集挑战题，放在这一节最后。

- [ ] [[problem: hdu,1213]] · [HDU 1213 How Many Tables](https://acm.hdu.edu.cn/showproblem.php?pid=1213)
- [ ] [[problem: luogu,P3367]] · [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
- [ ] [[problem: luogu,P1551]] · [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)
- [ ] [[problem: luogu,P1955]] · [P1955 程序自动分析](https://www.luogu.com.cn/problem/P1955)
- [ ] [[problem: luogu,P2024]] · [P2024 食物链](https://www.luogu.com.cn/problem/P2024)

## 三、最短路

无权图先用 BFS；非负边权使用 Dijkstra。重点是理解“松弛”在维护什么不变量。

- [ ] [[problem: hdu,2544]] · [HDU 2544 最短路](https://acm.hdu.edu.cn/showproblem.php?pid=2544)
- [ ] [[problem: luogu,P3371]] · [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
- [ ] [[problem: luogu,P4779]] · [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
- [ ] [[problem: luogu,P1144]] · [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
- [ ] [[problem: luogu,P1462]] · [P1462 通往奥格瑞玛的道路](https://www.luogu.com.cn/problem/P1462)

## 四、拓扑排序与 DAG

入度为零的点代表当前没有未完成的前置依赖。除了排序，还要练习在 DAG 上做最长路或计数 DP。

- [ ] [[problem: luogu,P1347]] · [P1347 排序](https://www.luogu.com.cn/problem/P1347)
- [ ] [[problem: luogu,P4017]] · [P4017 最大食物链计数](https://www.luogu.com.cn/problem/P4017)
- [ ] [[problem: luogu,P1113]] · [P1113 杂务](https://www.luogu.com.cn/problem/P1113)
- [ ] [[problem: luogu,P1807]] · [P1807 最长路](https://www.luogu.com.cn/problem/P1807)

## 五、最小生成树与二分图

Kruskal 的核心是按边权从小到大尝试合并；二分图染色的核心是判断相邻点能否使用不同颜色。

- [ ] [[problem: luogu,P3366]] · [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
- [ ] [[problem: luogu,P2872]] · [P2872 Building Roads S](https://www.luogu.com.cn/problem/P2872)
- [ ] [[problem: luogu,P1991]] · [P1991 无线通讯网](https://www.luogu.com.cn/problem/P1991)
- [ ] [[problem: luogu,P1330]] · [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)
- [ ] [[problem: luogu,P1525]] · [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525)

## 六、强连通分量挑战

强连通分量是图论入门的收尾内容。先理解 DFS 时间戳和反图，再学习 Tarjan 或 Kosaraju。

- [ ] [[problem: hdu,1269]] · [HDU 1269 迷宫城堡](https://acm.hdu.edu.cn/showproblem.php?pid=1269)
- [ ] [[problem: luogu,P3387]] · [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
- [ ] [[problem: luogu,P2341]] · [P2341 奶牛的仰慕 G](https://www.luogu.com.cn/problem/P2341)

## 过关标准

```text
能根据题意写出顶点、边、方向和边权：
能判断 BFS、Dijkstra、并查集、拓扑排序和 Kruskal 的适用条件：
能说明最短路松弛或并查集合并为什么不会破坏已有结论：
```
