---
title: "Rainboy 个人题单"
description: "Rainboy 自己维护的训练题单，按专题分章节记录正在攻的知识点与题目顺序。"
pinned: true
order: 0
---

# Rainboy 个人题单

[[toc]]

## 一、线段树

本章题目之间的 `pre` 关系（箭头由前置题指向后续题，只画这 6 题内部的边）：

```mermaid
flowchart TD
  P3372["P3372 线段树 1"]
  U420425["U420425 线段树二分 2"]
  U502676["U502676 线段树上二分模版"]
  aalc001c["AT aalc001_c"]
  CF19D["CF19D Points"]
  P4116["P4116 Qtree3"]

  P3372 --> U420425
  U502676 --> CF19D
  aalc001c --> CF19D
  U502676 --> P4116
```

- [ ] [[problem: luogu,P3372]]
  训练点：懒标记下传时机，左右区间边界，`long long` 防溢出。
- [ ] [[problem: luogu,U420425]]
  训练点：区间和够不够用「还差多少」表示；树上下降依赖元素非负带来的单调性。
- [ ] [[problem: luogu,U502676]]
  训练点：把聚合量从区间和换成区间最大值；判据从「够不够」换成「这段最大值是否大于 k」，`mx <= k` 就整段剪掉。
- [ ] [[problem: atcoder,aalc001_c]]
  训练点：带着余量 `rem` 下降；向右找最小 $r$、向左找最大 $l$ 两个方向的对称写法；无解用哨兵位置吸收。
- [ ] [[problem: codeforces,19D]]
  训练点：外层按 $x$ 维护区间最大 $y$；`mx <= limit` 剪枝定位最左 $x$；组内用 `std::set` 或压缩后的 Fenwick 找大于 $y$ 的最小值。
- [ ] [[problem: luogu,P4116]]
  训练点：双 dfs 序把祖先关系化成二维偏序；结点维护 min 后找第一个 `rdfn <= Y` 的位置；对照重链剖分 + 每条链 `set` 的 $O(\log^2 n)$ 写法，理解两种做法的取舍。
