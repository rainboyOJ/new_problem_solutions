---
oj: "codeforces"
problem_id: "1935D"
title: "Exam in MAC"
description: "正难则反二元容斥原理 + 二元一次方程消元同奇偶配对计数"
difficulty: "1800"
date: 2026-11-13 11:50
updated: 2026-11-13 12:05
toc: true
tags: ["数学", "组合数学", "容斥原理", "数论"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: ["rbook1:combinatorics", "rbook1:mind_theory","rbook1:inclusion-exclusion"]
rbookLinks:
  - id: "rbook1:combinatorics"
    reason: "掌握二元容斥原理与正难则反补集转化计数方法"
  - id: "rbook1:mind_theory"
    reason: "理解将方程组整数解约束转化为奇偶同余特性的代数降维思维模型"
pre: []
common: []
recommend: []
source: https://vjudge.net/problem/CodeForces-1935D#author=translator:1281311:zh
---

[[TOC]]

## 形式化题目

给定一个大小为 $n$ 的正整数集合 $S = \{s_1, s_2, \dots, s_n\}$（满足 $0 \leqslant s_1 < s_2 < \dots < s_n \leqslant c$），以及一个上界整数 $c$（$1 \leqslant c \leqslant 10^9$）。

求满足以下所有条件的非负整数对 $(x, y)$ 的数量：
1. $0 \leqslant x \leqslant y \leqslant c$；
2. 和不属于集合：$x + y \notin S$；
3. 差不属于集合：$y - x \notin S$。

---

## 解法总览

| 解法 | 核心机制 | 时间复杂度 | 空间复杂度 | 对应代码 |
| :--- | :--- | :--- | :--- | :--- |
| **暴力枚举与哈希判断（基线解法）** | $O(c^2)$ 枚举所有数对 $(x, y)$，哈希表检索和与差 | $O(t \cdot c^2)$ | $O(n)$ | `brute.cpp` |
| **正难则反与二元容斥（推荐正解）** | 全集减去不合法数对，利用消元转化为奇偶分类组合计数 | $O(t \cdot n)$ | $O(n)$ | `main.cpp` / `main.py` |

---

## 暴力枚举与集合判断（基线解法）

### 思路

::: info 暴力数对枚举（仅用于小数据对拍验证）
在 $c \leqslant 100$ 的极小规模下：
1. 将集合 $S$ 中的元素插入哈希表；
2. 双重循环枚举所有满足 $0 \leqslant x \leqslant y \leqslant c$ 的数对 $(x, y)$；
3. 检查 $x + y$ 和 $y - x$ 是否均不在哈希表中，满足则计数器累加。
:::

### 代码

C++17 版本：

@include-code(./brute.cpp, cpp)

### 复杂度分析

- **时间复杂度**：$O(t \cdot c^2)$，当 $c = 10^9$ 时总运算量高达 $10^{18}$，必然严重超时；
- **空间复杂度**：存储集合元素需 $O(n)$ 空间。

---

## 正难则反与二元容斥原理（推荐正解）

### 思路

::: info 正难则反与二元容斥模型
直接统计同时满足“和不在 $S$”且“差不在 $S$”的数对非常棘手。我们采用**正难则反**的思想：
1. **全集 $U$**：统计所有满足 $0 \leqslant x \leqslant y \leqslant c$ 的数对总数 $tot = \frac{(c + 1)(c + 2)}{2}$；
2. **不合法集合**：
   - 集合 $A$：满足 $x + y \in S$ 的数对；
   - 集合 $B$：满足 $y - x \in S$ 的数对；
3. 不合法数对的并集大小由**容斥原理**给出：
   $$|A \cup B| = |A| + |B| - |A \cap B|$$
4. 最终合法数对数量即为补集大小：
   $$ans = tot - |A \cup B| = tot - |A| - |B| + |A \cap B|$$
:::

### 核心思维推导

#### 1. 全集大小计算
满足 $0 \leqslant x \leqslant y \leqslant c$ 的整数对：
- 当 $y = 0$ 时，$x$ 可取 $0$（1 种）；
- 当 $y = 1$ 时，$x$ 可取 $0, 1$（2 种）；
- $\dots$
- 当 $y = c$ 时，$x$ 可取 $0, 1, \dots, c$（$c + 1$ 种）。
因此全集总数为等差数列求和：
$$tot = \sum_{y=0}^c (y + 1) = \frac{(c + 1)(c + 2)}{2}$$

#### 2. 单个不合法集合大小推导
- **求 $|A|$（和在集合中）**：
  若数对 $(x, y)$ 满足 $x + y = u \in S$：
  由于要求 $0 \leqslant x \leqslant y$，代入 $y = u - x$ 可得 $x \leqslant u - x \implies 2x \leqslant u \implies x \leqslant \lfloor u / 2 \rfloor$。
  因此对于固定的 $u \in S$，$x$ 可以任意取 $0, 1, \dots, \lfloor u / 2 \rfloor$，对应的方案数为 $\lfloor u / 2 \rfloor + 1$。
  累加集合 $S$ 中的所有元素：
  $$|A| = \sum_{u \in S} \left( \lfloor \frac{u}{2} \rfloor + 1 \right)$$

- **求 $|B|$（差在集合中）**：
  若数对 $(x, y)$ 满足 $y - x = v \in S$：
  即 $y = x + v$。由于受到上界约束 $y \leqslant c$，因此 $x + v \leqslant c \implies x \leqslant c - v$。
  同时天然满足 $x \leqslant x + v = y$。
  因此对于固定的 $v \in S$，$x$ 可以任意取 $0, 1, \dots, c - v$，对应的方案数为 $c - v + 1$。
  累加集合 $S$ 中的所有元素：
  $$|B| = \sum_{v \in S} (c - v + 1)$$

#### 3. 核心突破：交集 $|A \cap B|$ 的二元一次消元与同奇偶性
求交集大小是整道题最精妙的一步。
一个数对 $(x, y)$ 同时属于 $A$ 和 $B$，意味着存在 $u \in S$ 和 $v \in S$，使得：
$$\begin{cases}
x + y = u \\
y - x = v
\end{cases}$$

将两式相加与相减解此二元一次方程组：
$$y = \frac{u + v}{2}, \quad x = \frac{u - v}{2}$$

要求解出的 $(x, y)$ 必须是满足 $0 \leqslant x \leqslant y \leqslant c$ 的**非负整数**：
1. **整数约束**：$u + v$ 与 $u - v$ 必须均为偶数。这在数论上的充要条件是：**$u$ 与 $v$ 必须具有相同的奇偶性（同奇同偶）**！
2. **非负与偏序约束**：
   - $x \geqslant 0 \implies u - v \geqslant 0 \implies u \geqslant v$；
   - $x \leqslant y \implies \frac{u - v}{2} \leqslant \frac{u + v}{2} \implies v \geqslant 0$（条件给定的集合元素非负，天然成立）；
   - $y \leqslant c \implies \frac{u + v}{2} \leqslant c \implies u + v \leqslant 2c$（由于 $u \leqslant c, v \leqslant c$，天然严格成立）。

**结论**：每一个属于 $A \cap B$ 的合法数对 $(x, y)$，**严格一一对应**于在集合 $S$ 中选取两个同奇偶且满足 $u \geqslant v$ 的元素配对 $(u, v)$（允许 $u = v$）。

我们统计集合 $S$ 中：
- 奇数的个数为 $cnt_{odd}$；
- 偶数的个数为 $cnt_{even}$。

则在奇数中挑选两个数（允许相同）使得 $u \geqslant v$ 的方案数为 $\frac{cnt_{odd}(cnt_{odd} + 1)}{2}$；
在偶数中挑选两个数的方案数为 $\frac{cnt_{even}(cnt_{even} + 1)}{2}$。
交集大小即可在一瞬间闭式求得：
$$|A \cap B| = \frac{cnt_{odd}(cnt_{odd} + 1)}{2} + \frac{cnt_{even}(cnt_{even} + 1)}{2}$$

### 代码

C++17 版本：

@include-code(./main.cpp, cpp)

Python 3 版本：

@include-code(./main.py, python)

### 复杂度分析

- **时间复杂度**：
  - 单次遍历大小为 $n$ 的集合 $S$，分别统计奇偶数个数并累加 $|A|$ 与 $|B|$，每组测试用例耗时严格为 $O(n)$；
  - 总时间复杂度为 $O(\sum n)$，与 $c \leqslant 10^9$ 毫无关联。对于 $\sum n \leqslant 3 \cdot 10^5$，实际运行耗时仅约 2ms。
- **空间复杂度**：
  - 仅需存储输入数组，空间复杂度为 $O(n)$，内存占用不到 1 MB。

---

## 总结

### 1. 正难则反：利用补集转化打破全局复合否定约束

- **识别信号**：计数约束中出现多个并列的否定条件（例如“不能满足性质 A，且不能满足性质 B”），正面枚举需要避开所有禁区，状态交织极其繁琐。
- **思维动作**：果断应用德·摩根定律与正难则反策略，把原目标转化为“全集计数”减去“违反至少一个条件的补集并集”：$ans = |U| - |A \cup B|$。
- **有效原因**：在补集视角下，条件的复合“且”被转化为容斥的单条件“或”，使得原本纠缠的复合限制被拆解为独立的单项约束与交集约束，极大地降低了状态耦合度。
- **适用边界**：前提是全集容易闭式计算，且各不合法集合的交集具有简洁的解析形式；若交集维度过多（如 $k \geqslant 20$ 个集合），则高阶容斥本身会面临 $2^k$ 项展开爆炸。

### 2. 二元一次消元与同余约束提取

- **识别信号**：两个未知量受到和与差的联合约束（形如 $x + y = u$ 且 $y - x = v$）。
- **思维动作**：不要将 $(x, y)$ 与 $(u, v)$ 孤立看待，直接解方程组写出显式代数解 $y = \frac{u+v}{2}, x = \frac{u-v}{2}$，并将“未知数是整数”的形式要求，精准提炼为对已知参数的同余充要条件（$u \equiv v \pmod 2$）。
- **有效原因**：通过消元法，两个原本在不同坐标系下的几何约束被彻底打通，问题从两维几何平面的区域点数搜索，转化为输入参数在代数同余类上的组合划分。
- **适用边界**：适用于线性系数方程组；若变量间存在高次项或非线性调制，则整点解的存在性无法简单用奇偶同余判定，需借助丢番图方程或格点论。

### 3. 同余等价类内的独立组合计数

- **识别信号**：有效配对的充要条件简化为“两数具有相同余数/同奇同偶”且满足偏序关系（$u \geqslant v$）。
- **思维动作**：将全集合按特征标签（如奇偶性）划分为若干个互不相交的等价类子集。在每个子集内部，任意选取两个元素均自动天然满足同余要求，方案数直接套用组合公式 $\binom{k+1}{2} = \frac{k(k+1)}{2}$。
- **有效原因**：等价类划分彻底消除了跨集合的关联性，使得各类别之间的贡献独立互斥，避免了任何昂贵的数据结构检索，将配对搜索的开销从 $O(n^2)$ 压缩到 $O(n)$ 的频次统计。
- **适用边界**：要求约束条件完全由单变量的同余性质决定，且两变量在所属类别内部无额外的非线性干涉。
