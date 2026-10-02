# luogu P1462 通往奥格瑞玛的道路

> 原文摘录，非模型摘要。来源：`problems/luogu/P1462/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及+/提高-；标签：['二分答案', 'Dijkstra', '最短路', 'python']

## 题目解析（原文摘录）

[[TOC]]

### 题意

总伤害不能超过血量，最小化所经城市收费的最大值。

### 思路

固定收费上限后，只允许进入收费不超过上限的城市，运行 Dijkstra 求最小伤害；能否到达具有单调性，因此在去重后的收费列表上二分。最高收费仍不可达则输出 `AFK`。

### Python 知识

- `sorted(set(fee))` 同时得到离散二分候选。
- Dijkstra 中把 `health+1` 作为无穷大，并剪掉超过血量的状态。
- 提前弹出终点即可结束判定。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

时间 `O((n+m)log n log n)`，空间 `O(n+m)`。

### 总结

目标是最小化路径上的最大属性时，常用属性阈值二分加可达性检查。

## 代码位置
- `problems/luogu/P1462/1.cpp`
- `problems/luogu/P1462/brute.cpp`
- `problems/luogu/P1462/gen.py`
- `problems/luogu/P1462/main.cpp`
- `problems/luogu/P1462/main.py`
