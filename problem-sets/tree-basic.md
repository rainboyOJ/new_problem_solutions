---
title: "树上基础题单"
description: "为树形 DP、LCA 和树链剖分准备的基础题单，覆盖树遍历、子树信息、倍增、树上差分和换根 DP。"
order: 60
---

# 树上基础题单

树链剖分之前，至少要能熟练处理父子关系、深度、子树大小、DFS 序和 LCA。树上问题先问“这是子树信息还是路径信息”，再决定使用哪种工具。

## 一、树的表示与遍历

先把边表、根、父亲、深度和遍历顺序写清楚。二叉树题是理解递归结构的好入口。

- [ ] [[problem: luogu,P1305]] · [P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)
- [ ] [[problem: luogu,P1030]] · [P1030 求先序排列](https://www.luogu.com.cn/problem/P1030)
- [ ] [[problem: luogu,P1229]] · [P1229 遍历问题](https://www.luogu.com.cn/problem/P1229)
- [ ] [[problem: codeforces,115A]] · [Codeforces 115A Party](https://codeforces.com/problemset/problem/115/A)
- [ ] [[problem: codeforces,580C]] · [Codeforces 580C Kefa and Park](https://codeforces.com/problemset/problem/580/C)

## 二、树形 DP 与子树信息

树形 DP 通常是“先递归处理孩子，再由孩子状态合并父亲状态”。要明确状态是否允许选择当前节点，以及父子之间的限制。

- [ ] [[problem: luogu,P1122]] · [P1122 最大子树和](https://www.luogu.com.cn/problem/P1122)
- [ ] [[problem: luogu,P1352]] · [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
- [ ] [[problem: luogu,P2015]] · [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)
- [ ] [[problem: luogu,P2986]] · [P2986 Great Cow Gathering G](https://www.luogu.com.cn/problem/P2986)
- [ ] [[problem: luogu,P3478]] · [P3478 STA-Station](https://www.luogu.com.cn/problem/P3478)

## 三、LCA 与倍增

LCA 是树上路径问题的共同前置。先理解朴素向上跳，再用倍增把跳跃过程压到对数复杂度。

- [ ] [[problem: luogu,P3379]] · [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
- [ ] [[problem: atcoder,ABC070D]] · [AtCoder ABC070 D Transit Tree Path](https://atcoder.jp/contests/abc070/tasks/abc070_d)
- [ ] [[problem: luogu,P4427]] · [P4427 求和](https://www.luogu.com.cn/problem/P4427)

## 四、树上差分与路径统计

路径加、路径计数不一定要马上上树链剖分。先用 LCA 和差分把所有路径贡献汇总到节点，再做一次自底向上的统计。

- [ ] [[problem: luogu,P3258]] · [P3258 松鼠的新家](https://www.luogu.com.cn/problem/P3258)
- [ ] [[problem: luogu,P3128]] · [P3128 Max Flow P](https://www.luogu.com.cn/problem/P3128)
- [ ] [[problem: luogu,P4211]] · [P4211 LCA](https://www.luogu.com.cn/problem/P4211)

## 过关标准

进入树链剖分前，应能独立解释：

```text
dfs 序为什么能把子树变成连续区间：
LCA 如何把路径拆成两条向上的链：
树上差分在路径端点处为什么这样加减：
树形 DP 为什么可以后序合并：
```
