---
title: "2026 NOIP 冲刺 Luogu 题解完成计划"
description: "清空旧清单后，针对 problem-sets/2026-summer-practice.md 中所有 Luogu 题目制定题解完成计划。"
source: problem-sets/2026-summer-practice.md
---

# 2026 NOIP 冲刺 Luogu 题解完成计划

## 目标

完成 [`problem-sets/2026-summer-practice.md`](problem-sets/2026-summer-practice.md) 中所有 Luogu 题目的正式题解。

本计划只覆盖题单中的 Luogu 题目；USACO、AtCoder、Codeforces 题目不纳入本轮。

## 当前统计

- Luogu 引用次数：213
- 唯一 Luogu 题目：81
- 已完成：81
- 已有目录但只有骨架：0
- 已有部分内容但未达完成标准：0
- 尚未收录：0
- 本轮待实际完成：0

## 完成标准

每道题完成后至少满足：

- `problems/luogu/<数字编号>/problem.md` 存在；如果已经存在，不重新下载覆盖。
- `index.md` 符合本项目题解格式，frontmatter 字段完整，含 `difficulty`、`description`、`tags`、`source`。
- `main.cpp` 是可提交的 C++17 正解。
- `brute.cpp` 是教学/对拍用暴力或可验证解法；不适合暴力时在验证记录中说明。
- 有随机数据/样例/边界验证记录，优先使用 `gen.py` + `duipai-report.md`。
- `index.md` 能清楚解释建模、关键性质、状态/转移/check 函数、复杂度。
- 一图流只在题解、正解、暴力和验证都完成后再决定是否生成；最终是否插入由题解质量决定。

目录规则：

- 新建 Luogu 目录使用数字编号，例如 `problems/luogu/P11231`。
- frontmatter 中 `problem_id` 使用洛谷原题号，例如 `P11231`。

## 执行顺序

### P0：近两年真题优先

这些题是题单核心目标，优先完成。先补题面，再完成题解、代码、验证。

- [x] [[problem: luogu,P11231]] `普及/提高-` `CSP-S 2024` `贪心/排序` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P11232]] `普及+/提高` `CSP-S 2024` `二分/区间覆盖` `完成：index.md + main.cpp + brute.cpp + 对拍 500 组；是否采用一图流：否`
- [x] [[problem: luogu,P11233]] `提高+/省选-` `CSP-S 2024` `动态规划/状态压缩` `完成：index.md + main.cpp + brute.cpp + 对拍 500 组；是否采用一图流：否`
- [x] [[problem: luogu,P11234]] `省选/NOI-` `CSP-S 2024` `树形结构/动态规划` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：是`
- [x] [[problem: luogu,P11361]] `普及+/提高` `NOIP 2024` `字符串/贪心` `完成：index.md + main.cpp + brute.cpp + 对拍 500 组；是否采用一图流：否`
- [x] [[problem: luogu,P11362]] `普及+/提高` `NOIP 2024` `组合计数/快速幂` `完成：index.md + main.cpp + brute.cpp + 对拍 500 组；是否采用一图流：否`
- [x] [[problem: luogu,P11363]] `提高+/省选-` `NOIP 2024` `树形结构/组合计数` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P11364]] `省选/NOI-` `NOIP 2024` `树上查询/LCA/离线二分/线段树` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：是`
- [x] [[problem: luogu,P14361]] `普及+/提高` `CSP-S 2025` `贪心/排序/构造` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P14362]] `提高+/省选-` `CSP-S 2025` `图论建模/MST/枚举` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P14363]] `省选/NOI-` `CSP-S 2025` `字符串/AC自动机/离线` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：是`
- [x] [[problem: luogu,P14364]] `省选/NOI-` `CSP-S 2025` `动态规划/组合计数` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组 + 上限性能检查；是否采用一图流：是`
- [x] [[problem: luogu,P14635]] `普及+/提高` `NOIP 2025` `贪心/二分` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P14636]] `提高+/省选-` `NOIP 2025` `贪心/组合计数` `完成：index.md + main.cpp + brute.cpp + 对拍/穷举验证；是否采用一图流：否`
- [x] [[problem: luogu,P14637]] `省选/NOI-` `NOIP 2025` `树形DP/mex/长链剖分` `完成：index.md + main.cpp + brute.cpp + 对拍 200 组 + 上限性能检查；是否采用一图流：是`
- [x] [[problem: luogu,P14638]] `省选/NOI-` `NOIP 2025` `序列询问/ST表/单调队列` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组 + 上限性能检查；是否采用一图流：是`

### P1：第 1-2 周能力题，T1/T2 稳定拿分

重点是贪心、排序、构造、二分答案、区间覆盖。完成时必须写清楚“为什么贪心成立”或“单调性在哪里”。

- [x] [[problem: luogu,P1080]] `普及+/提高` `贪心/排序/高精度` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P2123]] `普及+/提高` `贪心/排序/调度` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P4053]] `普及+/提高` `反悔贪心/堆/排序` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P2949]] `普及+/提高` `反悔贪心/堆/排序` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1182]] `普及/提高-` `二分答案/贪心` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1462]] `普及+/提高` `二分答案/最短路/Dijkstra` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1803]] `普及-` `区间贪心/排序` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P2887]] `普及/提高-` `区间覆盖/贪心/堆` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1250]] `普及/提高-` `区间覆盖/贪心/树状数组` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`

### P2：第 3 周图论建模与最短路

重点不是套模板，而是写清楚点、边、虚拟点、选择与图目标的对应关系。

- [x] [[problem: luogu,P3366]] `普及/提高-` `MST模板/Kruskal/并查集` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1197]] `普及+/提高` `并查集/逆序处理/连通块` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1525]] `普及+/提高` `并查集/二分图/排序` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1967]] `提高+/省选-` `最大生成树/Kruskal/LCA/倍增` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P4047]] `普及+/提高` `最小生成树/Kruskal/聚类/几何` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P2872]] `普及/提高-` `最小生成树/Kruskal/几何建图` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1991]] `普及/提高-` `最小生成树/Kruskal/聚类/几何` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1948]] `普及+/提高` `二分答案/最短路/0-1 BFS` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1073]] `普及+/提高` `图论/反图/最短路DP` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1144]] `普及/提高-` `BFS/最短路计数` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`

### P3：第 4 周字符串

重点是哈希、Trie、KMP/Z 函数。题解中要说明子串比较、失败指针或 Trie 查询的含义。

- [x] [[problem: luogu,P3370]] `普及/提高-` `字符串哈希/排序` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P4551]] `普及+/提高` `Trie/异或/树上路径` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P2852]] `普及+/提高` `字符串哈希/二分答案/排序` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P3121]] `提高+/省选-` `AC自动机/栈式删除/字符串` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`

### P4：第 5-6 周树上问题

先完成 LCA、树上差分、树形 DP，再做换根 DP 和子树信息合并。题解必须区分“路径问题”和“子树问题”。

- [x] [[problem: luogu,P3379]] `普及/提高-` `LCA/倍增/树` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P5903]] `普及+/提高` `树上查询/倍增/K级祖先` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P3258]] `普及+/提高` `树上差分/LCA/倍增` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P3128]] `普及+/提高` `树上差分/LCA/倍增` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P2680]] `提高+/省选-` `树上差分/二分答案/LCA` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：是`
- [x] [[problem: luogu,P2495]] `省选/NOI-` `虚树/树形DP/LCA` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：是`
- [x] [[problem: luogu,P1352]] `普及/提高-` `树形DP/动态规划` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P2014]] `普及+/提高` `树上背包/树形DP` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1122]] `普及/提高-` `树形DP/最大连通子树和` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P3478]] `普及+/提高` `换根DP/树形DP` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`

### P5：第 7 周序列、区间询问与数据结构

重点是单调队列、线段树、莫队、主席树。题解中要写清楚查询是在线、离线，修改是否存在。

- [x] [[problem: luogu,P1440]] `普及/提高-` `单调队列/滑动窗口` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P2627]] `普及+/提高` `动态规划/单调队列/前缀和` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1725]] `普及+/提高` `动态规划/单调队列/滑动窗口` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P3372]] `普及/提高-` `线段树/懒标记` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1972]] `普及+/提高` `离线/树状数组` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1494]] `普及+/提高` `莫队/离线` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P1903]] `提高+/省选-` `带修莫队/离线` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：是`
- [x] [[problem: luogu,P3834]] `提高+/省选-` `主席树/可持久化线段树/离散化` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：是`

### P6：第 8 周组合计数与计数 DP

重点是组合数、前缀和优化、容斥、模数。题解中要明确状态定义和转移来源。

- [x] [[problem: luogu,P2822]] `普及/提高-` `组合计数/动态规划/前缀和` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：否`
- [x] [[problem: luogu,P3214]] `提高+/省选-` `组合计数/数学/递推` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：是`
- [x] [[problem: luogu,P4931]] `普及+/提高` `组合计数/递推/数学` `完成：index.md + main.cpp + brute.cpp + 对拍 150 组；是否采用一图流：是`
- [x] [[problem: luogu,P2679]] `提高+/省选-` `动态规划/字符串/计数DP` `完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：是`

## 已完成题目，后续只做抽查

这些题当前已有 `problem.md`、`index.md`、`main.cpp`、`brute.cpp`，不纳入第一轮写作工作量。后续只做质量抽查、渲染检查和必要的一图流补充。

- [x] [[problem: luogu,P2678]] `普及/提高-` `[NOIP 2015 提高组] 跳石头`
- [x] [[problem: luogu,P1083]] `普及+/提高` `[NOIP 2012 提高组] 借教室`
- [x] [[problem: luogu,P1314]] `普及+/提高` `[NOIP 2011 提高组] 聪明的质监员`
- [x] [[problem: luogu,P2440]] `普及-` `木材加工`
- [x] [[problem: luogu,P3662]] `普及-` `[USACO17FEB] Why Did the Cow Cross the Road II S`
- [x] [[problem: luogu,P1712]] `提高+/省选-` `[NOI2016] 区间`
- [x] [[problem: luogu,P2916]] `普及+/提高` `[USACO08NOV] Cheering up the Cow G`
- [x] [[problem: luogu,P4568]] `普及+/提高` `[JLOI2011] 飞行路线`
- [x] [[problem: luogu,P2296]] `普及+/提高` `[NOIP 2014 提高组] 寻找道路`
- [x] [[problem: luogu,P2939]] `普及+/提高` `[USACO09FEB] Revamping Trails G`
- [x] [[problem: luogu,P3375]] `普及/提高-` `【模板】KMP`
- [x] [[problem: luogu,P2580]] `普及-` `于是他错误的点名开始了`
- [x] [[problem: luogu,P2015]] `普及+/提高` `二叉苹果树`
- [x] [[problem: luogu,P2986]] `普及+/提高` `[USACO10MAR] Great Cow Gathering G`
- [x] [[problem: luogu,P3047]] `普及+/提高` `[USACO12FEB] Nearby Cows G`
- [x] [[problem: luogu,P1886]] `普及/提高-` `【模板】单调队列 / 滑动窗口`
- [x] [[problem: luogu,P3373]] `普及/提高-` `【模板】线段树 2`
- [x] [[problem: luogu,P3197]] `普及/提高-` `[HNOI2008] 越狱`
- [x] [[problem: luogu,P5664]] `提高+/省选-` `[CSP-S 2019] Emiya 家今天的饭`
- [x] [[problem: luogu,P2513]] `普及+/提高` `[HAOI2009] 逆序对数列`

## 批量推进规则

每批建议按这个顺序推进：

1. 先补 `missing-dir`：创建目录、补 `problem.md`、生成题解骨架。
2. 再补 `scaffold`：检查题面和 frontmatter，补正解、暴力和验证。
3. 再补 `partial`：重点补 `main.cpp`、`brute.cpp`、`gen.py`、`duipai-report.md`。
4. 每完成 3-5 题运行一次局部检查。
5. 每完成一个 P 阶段，运行 `npm run generate:problems` 和相关预览检查。

建议每题完成后在本文件中把对应条目改成 `[x]`，并追加一句完成摘要：

```text
完成：index.md + main.cpp + brute.cpp + 对拍 300 组；是否采用一图流：是/否。
```
