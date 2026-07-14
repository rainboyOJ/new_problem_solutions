---
title: "2026 NOIP 冲刺暑假题目单"
description: "面向 NOIP 一等奖目标的 2026 暑假提高训练题单。"
order: 70
---

# 2026 NOIP 冲刺暑假题目单

这份题单不是“从 100 分补基础”的训练表，而是面向 **NOIP 一等奖** 的暑假冲刺题单。根据 CSP-S 2024、NOIP 2024、CSP-S 2025、NOIP 2025 的出题风格，训练重点应从基础模板升级到：

> 贪心构造、二分答案、区间覆盖、图建模、树上询问、字符串哈希、计数 DP、树形 DP、离线询问。

近两年的主要趋势：

1. **T1 不再只是纯模拟**，经常是贪心、构造、排序、分类讨论的中等题。
2. **T2 常考建模 + 二分 / 贪心 / 图论 / 最小生成树 / 区间覆盖**。
3. **字符串、树、询问类题增多**，需要能把题面限制转成可维护的数据结构或状态。
4. **树和序列的高级查询是强趋势**，不能只会 LCA 模板和线段树模板。
5. **图论从模板题转向建模题**，重点是“图怎么建”，不是背 Kruskal 或 Dijkstra。
6. **计数 DP / 组合数学 / 字符串哈希会在提高组后两题出现**，需要提前补齐。

## 核心训练方向

| 方向 | 对应近年真题 | 应训练能力 |
| --- | --- | --- |
| 贪心 / 构造 / 分类讨论 | CSP-S 2024 决斗、CSP-S 2025 社团招新、NOIP 2025 糖果店 | 排序、差值、反悔、构造最优 |
| 二分答案 + check | CSP-S 2024 超速检测、NOIP 2025 糖果店 | 单调性、区间判定、代价函数 |
| 区间覆盖 / 区间打点 | CSP-S 2024 超速检测 | 把对象转成区间，再贪心选点 |
| 图建模 / MST 变形 | CSP-S 2025 道路修复 | 虚拟点、Kruskal、最小连通代价 |
| 字符串哈希 / Trie / KMP | NOIP 2024 编辑字符串、CSP-S 2025 谐音替换 | 字符串匹配、替换计数、哈希 |
| 树上基础 + LCA | NOIP 2024 树上查询 | LCA、DFS 序、RMQ、倍增 |
| 树形 DP / mex / 子树 | NOIP 2025 树的价值 | 子树信息合并、树上 DP |
| 序列询问 / 离线 | NOIP 2025 序列询问 | 前缀和、单调队列、线段树、分块 |
| 组合计数 DP | CSP-S 2025 员工招聘、NOIP 2024 遗失的赋值 | 排列计数、限制计数、模数 |
| 部分分策略 | 近两年所有 T3/T4 | 暴力、特殊性质、分层优化 |

## 第一阶段：近年 T1 / T2 风格专项

目标是让 CSP-S / NOIP 前两题稳定拿高分。

### 贪心、排序、构造、分类讨论

对应真题：CSP-S 2024《决斗》、CSP-S 2025《社团招新》、NOIP 2025《糖果店》。

#### 训练题目

- [ ] [[problem: luogu,P11231]]
- [ ] [[problem: luogu,P14361]]
- [ ] [[problem: luogu,P14635]]
- [ ] [[problem: luogu,P1080]]
- [ ] [[problem: luogu,P2123]]
- [ ] [[problem: luogu,P4053]]
- [ ] [[problem: luogu,P2949]]
- [ ] [[problem: usaco,convention_ii]]
- [ ] [[problem: usaco,paired_up]]
- [ ] [[problem: atcoder,abc308_f]]
- [ ] [[problem: atcoder,abc325_d]]
- [ ] [[problem: codeforces,1520E]]
- [ ] [[problem: codeforces,1665C]]

这一组学生至少做 10 题。真题三题必须做透：P11231、P14361、P14635。

### 二分答案 + check 函数

对应真题：CSP-S 2024《超速检测》、NOIP 2025《糖果店》。

#### 训练题目

- [ ] [[problem: luogu,P11232]]
- [ ] [[problem: luogu,P14635]]
- [ ] [[problem: luogu,P2678]]
- [ ] [[problem: luogu,P1182]]
- [ ] [[problem: luogu,P1083]]
- [ ] [[problem: luogu,P1314]]
- [ ] [[problem: luogu,P1462]]
- [ ] [[problem: luogu,P2440]]
- [ ] [[problem: atcoder,abc023_d]]
- [ ] [[problem: atcoder,abc144_e]]
- [ ] [[problem: atcoder,abc294_f]]
- [ ] [[problem: codeforces,1201C]]
- [ ] [[problem: codeforces,1613C]]

每题必须写清楚：

```text
1. 答案是什么？
2. 单调性在哪里？
3. check(x) 判断什么？
4. check 的复杂度是多少？
```

如果学生只能背模板，不会解释单调性，这组题没过关。

### 区间覆盖、区间选点、线段交集

CSP-S 2024《超速检测》非常典型：先把每辆超速车转成“能检测它的测速仪区间”，再求保留最少测速仪。

#### 训练题目

- [ ] [[problem: luogu,P11232]]
- [ ] [[problem: luogu,P1803]]
- [ ] [[problem: luogu,P2887]]
- [ ] [[problem: luogu,P3662]]
- [ ] [[problem: luogu,P1250]]
- [ ] [[problem: luogu,P1712]]
- [ ] [[problem: usaco,lifeguards]]
- [ ] [[problem: usaco,cow_steeplechase_ii]]
- [ ] [[problem: atcoder,abc103_d]]
- [ ] [[problem: atcoder,abc230_d]]
- [ ] [[problem: codeforces,863E]]
- [ ] [[problem: codeforces,1249D2]]

做完后必须能把题目对象翻译成：

```text
区间是什么？
点是什么？
要最少点覆盖区间，还是最多不相交区间？
按左端点排，还是按右端点排？
```

## 第二阶段：近年 T2 / T3 风格专项

目标是把 T2 稳定拿满，T3 能拿 40-70 分。

### 图论建模、最短路、MST 变形

CSP-S 2025《道路修复》是典型的建模题。题面要求用修复道路或改造乡镇 + 新建道路，让原有城市连通且费用最小，重点不是套 MST 模板，而是想清楚怎么建图。

#### 训练题目

- [ ] [[problem: luogu,P14362]]
- [ ] [[problem: luogu,P3366]]
- [ ] [[problem: luogu,P1197]]
- [ ] [[problem: luogu,P1525]]
- [ ] [[problem: luogu,P1967]]
- [ ] [[problem: luogu,P4047]]
- [ ] [[problem: luogu,P2872]]
- [ ] [[problem: luogu,P2916]]
- [ ] [[problem: luogu,P1991]]
- [ ] [[problem: usaco,moocast_gold]]
- [ ] [[problem: usaco,superbull]]
- [ ] [[problem: atcoder,abc270_f]]
- [ ] [[problem: atcoder,abc065_d]]
- [ ] [[problem: codeforces,1245D]]
- [ ] [[problem: codeforces,17B]]

学生做这一组时，不能只写 Kruskal。每题必须写清楚“图怎么建”：

```text
点是什么？
边是什么？
有没有虚拟点？
原题的选择对应图中的什么？
为什么最小生成树/最短路能表示原目标？
```

### 最短路 + 二分 / 状态建图

近年 CSP-S / NOIP T2、T3 喜欢把二分、限制、图连通混在一起。

#### 训练题目

- [ ] [[problem: luogu,P1462]]
- [ ] [[problem: luogu,P4568]]
- [ ] [[problem: luogu,P1948]]
- [ ] [[problem: luogu,P1073]]
- [ ] [[problem: luogu,P2296]]
- [ ] [[problem: luogu,P1144]]
- [ ] [[problem: luogu,P2939]]
- [ ] [[problem: usaco,roadblock]]
- [ ] [[problem: usaco,shortcut]]
- [ ] [[problem: atcoder,abc237_e]]
- [ ] [[problem: atcoder,abc035_d]]
- [ ] [[problem: codeforces,20C]]
- [ ] [[problem: codeforces,919D]]

## 第三阶段：字符串方向专项

对应真题：NOIP 2024《编辑字符串》考带限制的二进制串相邻交换；CSP-S 2025《谐音替换》考字符串替换计数，要求统计从一个串替换成另一个串的方案数。

### 字符串哈希、Trie、KMP、字符串 DP

#### 训练题目

- [ ] [[problem: luogu,P11361]]
- [ ] [[problem: luogu,P14363]]
- [ ] [[problem: luogu,P3370]]
- [ ] [[problem: luogu,P3375]]
- [ ] [[problem: luogu,P2580]]
- [ ] [[problem: luogu,P4551]]
- [ ] [[problem: luogu,P2852]]
- [ ] [[problem: luogu,P3121]]
- [ ] [[problem: usaco,censoring]]
- [ ] [[problem: usaco,censoring_gold]]
- [ ] [[problem: usaco,standing_out_from_the_herd]]
- [ ] [[problem: atcoder,abc284_f]]
- [ ] [[problem: atcoder,abc141_e]]
- [ ] [[problem: atcoder,abc287_e]]
- [ ] [[problem: codeforces,271D]]
- [ ] [[problem: codeforces,126B]]
- [ ] [[problem: codeforces,432D]]
- [ ] [[problem: codeforces,514C]]

这组不要求一开始上后缀数组，但必须掌握：

- 双哈希
- 前缀哈希取子串
- Trie 插入与查询
- KMP 或 Z 函数至少会一种
- 字符串题先判断是否可以转化为“比较若干子串是否相等”

## 第四阶段：树上问题专项

对应真题：NOIP 2024《树的遍历》《树上查询》、NOIP 2025《树的价值》。其中《树上查询》涉及区间 $[l,r]$ 中结点的 LCA 深度最大值，数据范围到 $5 \times 10^5$，不是简单 LCA 模板。

### LCA、DFS 序、树上差分、树上查询

#### 训练题目

- [ ] [[problem: luogu,P11364]]
- [ ] [[problem: luogu,P3379]]
- [ ] [[problem: luogu,P5903]]
- [ ] [[problem: luogu,P3258]]
- [ ] [[problem: luogu,P3128]]
- [ ] [[problem: luogu,P2680]]
- [ ] [[problem: luogu,P1967]]
- [ ] [[problem: luogu,P2495]]
- [ ] [[problem: usaco,cow_land]]
- [ ] [[problem: usaco,directory_traversal]]
- [ ] [[problem: usaco,promotion_counting]]
- [ ] [[problem: atcoder,abc294_g]]
- [ ] [[problem: atcoder,abc267_f]]
- [ ] [[problem: codeforces,208E]]
- [ ] [[problem: codeforces,343D]]

学生必须完成以下基础能力：

```text
1. 会预处理 dep、fa[u][j]
2. 会求 lca(u,v)
3. 会把路径修改转成树上差分
4. 会用 DFS 序把子树变成连续区间
5. 会判断一道树题是“路径问题”还是“子树问题”
```

### 树形 DP、换根 DP、mex / 子树信息合并

对应真题：NOIP 2025《树的价值》要求给树上每个结点设置权值，最大化所有子树 mex 之和，明显是树结构 + mex / DP / 子树信息。

#### 训练题目

- [ ] [[problem: luogu,P14637]]
- [ ] [[problem: luogu,P1352]]
- [ ] [[problem: luogu,P2015]]
- [ ] [[problem: luogu,P2014]]
- [ ] [[problem: luogu,P1122]]
- [ ] [[problem: luogu,P3478]]
- [ ] [[problem: luogu,P2986]]
- [ ] [[problem: luogu,P3047]]
- [ ] [[problem: usaco,barn_painting]]
- [ ] [[problem: usaco,delegation]]
- [ ] [[problem: usaco,cow_at_large]]
- [ ] [[problem: atcoder,dp_v]]
- [ ] [[problem: atcoder,dp_p]]
- [ ] [[problem: atcoder,abc220_f]]
- [ ] [[problem: codeforces,600E]]
- [ ] [[problem: codeforces,219D]]
- [ ] [[problem: codeforces,161D]]

这组做完后，学生要能区分：

- 子树选点：树形 DP
- 路径统计：LCA / 树上差分
- 每个点作为根：换根 DP
- 子树颜色 / 出现次数：DSU on tree 或启发式合并

## 第五阶段：序列、区间询问、离线与数据结构

对应真题：NOIP 2025《序列询问》要求对每次 $[L,R]$ 长度限制，求每个位置被包含的极好区间最大权值，输出异或聚合；这是“前缀和 + 长度限制 + 每点贡献 + 批量询问”的复杂序列询问题。

### 单调队列、线段树、离线询问、分块

#### 训练题目

- [ ] [[problem: luogu,P14638]]
- [ ] [[problem: luogu,P1886]]
- [ ] [[problem: luogu,P1440]]
- [ ] [[problem: luogu,P2627]]
- [ ] [[problem: luogu,P1725]]
- [ ] [[problem: luogu,P3372]]
- [ ] [[problem: luogu,P3373]]
- [ ] [[problem: luogu,P1972]]
- [ ] [[problem: luogu,P1494]]
- [ ] [[problem: luogu,P1903]]
- [ ] [[problem: luogu,P3834]]
- [ ] [[problem: usaco,haybales]]
- [ ] [[problem: usaco,sleepy_cow_sorting]]
- [ ] [[problem: usaco,cow_hopscotch]]
- [ ] [[problem: atcoder,dp_q]]
- [ ] [[problem: atcoder,abc185_f]]
- [ ] [[problem: atcoder,abc339_g]]
- [ ] [[problem: codeforces,86D]]
- [ ] [[problem: codeforces,652D]]
- [ ] [[problem: codeforces,220B]]

学生必须建立这几个判断：

```text
固定长度窗口最大/最小：单调队列
区间修改查询：线段树
静态区间第 k 小：主席树
大量离线区间查询：莫队 / BIT
前缀贡献变化：扫描线 + BIT
```

## 第六阶段：计数 DP、组合数学、排列计数

对应真题：NOIP 2024《遗失的赋值》是变量限制计数；CSP-S 2025《员工招聘》是排列顺序计数，并对 998244353 取模。

### 组合计数、排列计数、DP 计数

#### 训练题目

- [ ] [[problem: luogu,P11362]]
- [ ] [[problem: luogu,P14364]]
- [ ] [[problem: luogu,P2822]]
- [ ] [[problem: luogu,P3197]]
- [ ] [[problem: luogu,P3214]]
- [ ] [[problem: luogu,P4931]]
- [ ] [[problem: luogu,P5664]]
- [ ] [[problem: luogu,P2679]]
- [ ] [[problem: luogu,P2513]]
- [ ] [[problem: atcoder,dp_m]]
- [ ] [[problem: atcoder,dp_o]]
- [ ] [[problem: atcoder,dp_r]]
- [ ] [[problem: atcoder,abc242_e]]
- [ ] [[problem: codeforces,401D]]
- [ ] [[problem: codeforces,478D]]
- [ ] [[problem: codeforces,559C]]
- [ ] [[problem: codeforces,895C]]

做这一组必须整理模数技巧：

```text
1. 快速幂
2. 逆元
3. 阶乘和逆阶乘
4. 组合数 C(n,k)
5. 前缀和优化 DP
6. 容斥的基本形式
```

## 近两年真题必须做清单

这部分建议放在第 6-8 周做，前面先补专项能力。

### CSP-S 2024

- [ ] [[problem: luogu,P11231]]
- [ ] [[problem: luogu,P11232]]
- [ ] [[problem: luogu,P11233]]
- [ ] [[problem: luogu,P11234]]

目标：P11231 必须 AC；P11232 必须 AC 或至少 80+；P11233 至少理解正解，能写 40-70 分；P11234 至少完成暴力与特殊性质。

### NOIP 2024

- [ ] [[problem: luogu,P11361]]
- [ ] [[problem: luogu,P11362]]
- [ ] [[problem: luogu,P11363]]
- [ ] [[problem: luogu,P11364]]

目标：P11361 必须 AC；P11362 争取 AC；P11363 争取 40-70 分；P11364 会写暴力、链、$k=r-l+1$ 特殊性质。

### CSP-S 2025

- [ ] [[problem: luogu,P14361]]
- [ ] [[problem: luogu,P14362]]
- [ ] [[problem: luogu,P14363]]
- [ ] [[problem: luogu,P14364]]

目标：P14361 必须 AC；P14362 争取 AC；P14363 争取 40-70 分；P14364 会写暴力 + 部分特殊性质。

### NOIP 2025

- [ ] [[problem: luogu,P14635]]
- [ ] [[problem: luogu,P14636]]
- [ ] [[problem: luogu,P14637]]
- [ ] [[problem: luogu,P14638]]

目标：P14635 必须 AC；P14636、P14637 争取 40-70 分；P14638 会写暴力、短区间、固定长度等特殊性质。

## 8 周新版训练安排

### 第 1 周：贪心构造 + 二分答案

重点对应：决斗、社团招新、糖果店。

#### 必做

- [ ] [[problem: luogu,P11231]]
- [ ] [[problem: luogu,P14361]]
- [ ] [[problem: luogu,P14635]]
- [ ] [[problem: luogu,P2678]]
- [ ] [[problem: luogu,P1182]]
- [ ] [[problem: luogu,P1083]]
- [ ] [[problem: luogu,P4053]]
- [ ] [[problem: luogu,P2949]]
- [ ] [[problem: atcoder,abc023_d]]
- [ ] [[problem: atcoder,abc325_d]]
- [ ] [[problem: codeforces,1201C]]
- [ ] [[problem: codeforces,1665C]]

#### 周末模拟

- [ ] [[problem: luogu,P11231]]
- [ ] [[problem: luogu,P14635]]
- [ ] [[problem: luogu,P4053]]
- [ ] [[problem: codeforces,1665C]]

### 第 2 周：区间覆盖 + 区间贪心 + 复杂 check

重点对应：超速检测。

#### 必做

- [ ] [[problem: luogu,P11232]]
- [ ] [[problem: luogu,P1803]]
- [ ] [[problem: luogu,P2887]]
- [ ] [[problem: luogu,P1250]]
- [ ] [[problem: luogu,P1712]]
- [ ] [[problem: atcoder,abc103_d]]
- [ ] [[problem: atcoder,abc230_d]]
- [ ] [[problem: codeforces,1249D2]]
- [ ] [[problem: codeforces,863E]]
- [ ] [[problem: usaco,lifeguards]]

#### 周末模拟

- [ ] [[problem: atcoder,abc103_d]]
- [ ] [[problem: luogu,P11232]]
- [ ] [[problem: codeforces,1249D2]]
- [ ] [[problem: luogu,P1712]]

### 第 3 周：图论建模 + MST 变形

重点对应：道路修复。

#### 必做

- [ ] [[problem: luogu,P14362]]
- [ ] [[problem: luogu,P3366]]
- [ ] [[problem: luogu,P1197]]
- [ ] [[problem: luogu,P1525]]
- [ ] [[problem: luogu,P1967]]
- [ ] [[problem: luogu,P2916]]
- [ ] [[problem: luogu,P2872]]
- [ ] [[problem: atcoder,abc270_f]]
- [ ] [[problem: atcoder,abc065_d]]
- [ ] [[problem: codeforces,1245D]]
- [ ] [[problem: usaco,moocast_gold]]
- [ ] [[problem: usaco,superbull]]

#### 周末模拟

- [ ] [[problem: luogu,P3366]]
- [ ] [[problem: luogu,P14362]]
- [ ] [[problem: codeforces,1245D]]
- [ ] [[problem: luogu,P1967]]

### 第 4 周：字符串哈希 / Trie / 替换计数

重点对应：编辑字符串、谐音替换。

#### 必做

- [ ] [[problem: luogu,P11361]]
- [ ] [[problem: luogu,P14363]]
- [ ] [[problem: luogu,P3370]]
- [ ] [[problem: luogu,P3375]]
- [ ] [[problem: luogu,P2580]]
- [ ] [[problem: luogu,P3121]]
- [ ] [[problem: luogu,P2852]]
- [ ] [[problem: atcoder,abc284_f]]
- [ ] [[problem: atcoder,abc141_e]]
- [ ] [[problem: atcoder,abc287_e]]
- [ ] [[problem: codeforces,126B]]
- [ ] [[problem: codeforces,432D]]
- [ ] [[problem: codeforces,514C]]

#### 周末模拟

- [ ] [[problem: luogu,P11361]]
- [ ] [[problem: atcoder,abc287_e]]
- [ ] [[problem: codeforces,126B]]
- [ ] [[problem: luogu,P14363]]

### 第 5 周：树上基础 + LCA + 树上差分

重点对应：树上查询。

#### 必做

- [ ] [[problem: luogu,P3379]]
- [ ] [[problem: luogu,P3258]]
- [ ] [[problem: luogu,P3128]]
- [ ] [[problem: luogu,P2680]]
- [ ] [[problem: luogu,P1967]]
- [ ] [[problem: luogu,P11364]]
- [ ] [[problem: atcoder,abc294_g]]
- [ ] [[problem: atcoder,abc267_f]]
- [ ] [[problem: codeforces,208E]]
- [ ] [[problem: usaco,cow_land]]

#### 周末模拟

- [ ] [[problem: luogu,P3379]]
- [ ] [[problem: luogu,P3258]]
- [ ] [[problem: luogu,P2680]]
- [ ] [[problem: luogu,P11364]]

### 第 6 周：树形 DP + 换根 DP + mex 思维

重点对应：树的价值。

#### 必做

- [ ] [[problem: luogu,P14637]]
- [ ] [[problem: luogu,P1352]]
- [ ] [[problem: luogu,P2015]]
- [ ] [[problem: luogu,P2014]]
- [ ] [[problem: luogu,P1122]]
- [ ] [[problem: luogu,P3478]]
- [ ] [[problem: luogu,P2986]]
- [ ] [[problem: luogu,P3047]]
- [ ] [[problem: atcoder,dp_p]]
- [ ] [[problem: atcoder,dp_v]]
- [ ] [[problem: atcoder,abc220_f]]
- [ ] [[problem: codeforces,219D]]
- [ ] [[problem: codeforces,600E]]

#### 周末模拟

- [ ] [[problem: luogu,P1352]]
- [ ] [[problem: atcoder,abc220_f]]
- [ ] [[problem: luogu,P2014]]
- [ ] [[problem: luogu,P14637]]

### 第 7 周：序列询问 + 数据结构 + 离线

重点对应：序列询问。

#### 必做

- [ ] [[problem: luogu,P14638]]
- [ ] [[problem: luogu,P1886]]
- [ ] [[problem: luogu,P2627]]
- [ ] [[problem: luogu,P1725]]
- [ ] [[problem: luogu,P3372]]
- [ ] [[problem: luogu,P3373]]
- [ ] [[problem: luogu,P1972]]
- [ ] [[problem: luogu,P1494]]
- [ ] [[problem: atcoder,dp_q]]
- [ ] [[problem: atcoder,abc185_f]]
- [ ] [[problem: atcoder,abc339_g]]
- [ ] [[problem: codeforces,86D]]
- [ ] [[problem: codeforces,652D]]

#### 周末模拟

- [ ] [[problem: luogu,P1886]]
- [ ] [[problem: luogu,P2627]]
- [ ] [[problem: luogu,P1972]]
- [ ] [[problem: luogu,P14638]]

### 第 8 周：组合计数 + 近两年真题模拟

重点对应：遗失的赋值、员工招聘、清仓甩卖。

#### 必做

- [ ] [[problem: luogu,P11362]]
- [ ] [[problem: luogu,P14364]]
- [ ] [[problem: luogu,P14636]]
- [ ] [[problem: luogu,P2822]]
- [ ] [[problem: luogu,P5664]]
- [ ] [[problem: luogu,P2679]]
- [ ] [[problem: atcoder,dp_m]]
- [ ] [[problem: atcoder,dp_o]]
- [ ] [[problem: atcoder,dp_r]]
- [ ] [[problem: codeforces,401D]]
- [ ] [[problem: codeforces,478D]]
- [ ] [[problem: codeforces,559C]]

#### 真题模拟 1

- [ ] [[problem: luogu,P11231]]
- [ ] [[problem: luogu,P11232]]
- [ ] [[problem: luogu,P11233]]
- [ ] [[problem: luogu,P11234]]

#### 真题模拟 2

- [ ] [[problem: luogu,P14361]]
- [ ] [[problem: luogu,P14362]]
- [ ] [[problem: luogu,P14363]]
- [ ] [[problem: luogu,P14364]]

#### NOIP 风格模拟

- [ ] [[problem: luogu,P14635]]
- [ ] [[problem: luogu,P14636]]
- [ ] [[problem: luogu,P14637]]
- [ ] [[problem: luogu,P14638]]

## 给 100 分学生的分层要求

这份题单偏提高，不建议一口气全部压给学生。建议分三层。

### A 层：必须完成，目标 200-240 分

- [ ] [[problem: luogu,P11231]]
- [ ] [[problem: luogu,P11232]]
- [ ] [[problem: luogu,P11361]]
- [ ] [[problem: luogu,P11362]]
- [ ] [[problem: luogu,P14361]]
- [ ] [[problem: luogu,P14362]]
- [ ] [[problem: luogu,P14635]]
- [ ] [[problem: luogu,P2678]]
- [ ] [[problem: luogu,P1083]]
- [ ] [[problem: luogu,P1525]]
- [ ] [[problem: luogu,P3379]]
- [ ] [[problem: luogu,P3372]]
- [ ] [[problem: luogu,P1886]]
- [ ] [[problem: atcoder,abc023_d]]
- [ ] [[problem: atcoder,abc103_d]]
- [ ] [[problem: atcoder,dp_p]]
- [ ] [[problem: codeforces,1201C]]
- [ ] [[problem: codeforces,1245D]]

### B 层：冲省一核心，目标 240-280 分

- [ ] [[problem: luogu,P11233]]
- [ ] [[problem: luogu,P11363]]
- [ ] [[problem: luogu,P11364]]
- [ ] [[problem: luogu,P14363]]
- [ ] [[problem: luogu,P14636]]
- [ ] [[problem: luogu,P14637]]
- [ ] [[problem: luogu,P14638]]
- [ ] [[problem: luogu,P1967]]
- [ ] [[problem: luogu,P2680]]
- [ ] [[problem: luogu,P1972]]
- [ ] [[problem: luogu,P2014]]
- [ ] [[problem: atcoder,abc270_f]]
- [ ] [[problem: atcoder,abc294_g]]
- [ ] [[problem: atcoder,dp_v]]
- [ ] [[problem: codeforces,600E]]
- [ ] [[problem: codeforces,86D]]

### C 层：冲高分 / 省队边缘题感

- [ ] [[problem: luogu,P11234]]
- [ ] [[problem: luogu,P14364]]
- [ ] [[problem: luogu,P3834]]
- [ ] [[problem: luogu,P2495]]
- [ ] [[problem: atcoder,abc339_g]]
- [ ] [[problem: codeforces,559C]]
- [ ] [[problem: codeforces,895C]]
- [ ] [[problem: usaco,promotion_counting]]
- [ ] [[problem: usaco,cow_land]]
- [ ] [[problem: usaco,delegation]]

## 实际布置建议

每周不要只按题号布置，建议每题附带“任务目标”。

例如 P11232《超速检测》的目标：

```text
1. 能把每辆车转成一个测速仪区间。
2. 能解释为什么保留最少测速仪等价于区间选点。
3. 能写出 O((n+m)logm) 或接近复杂度的做法。
4. 赛后重写一次，不看题解。
```

例如 P14362《道路修复》的目标：

```text
1. 写出原图 MST 暴力。
2. 思考乡镇改造如何转成额外边或虚拟结构。
3. 至少拿到特殊性质分。
4. 复盘为什么这是“建图题”，不是普通 MST 模板题。
```

## 这版题单的核心变化

相较基础模板题单，这版围绕近两年趋势强化：

```text
1. 贪心构造题更多
2. 二分 + 复杂 check 更多
3. 区间转化题更多
4. 图论更重建模，不重模板
5. 字符串题重新进入重点
6. 树上询问明显变难
7. T3/T4 更强调部分分和特殊性质
8. 计数 DP 与组合数学需要补
```

学生暑假的目标不是“刷完所有题”，而是：

> **A 层全做透，B 层至少完成 60%，近两年真题全部做一遍并复盘，最后 2 周严格模拟。**
