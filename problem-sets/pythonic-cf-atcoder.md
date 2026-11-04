---
title: "Python 迁移训练题单（C++ 选手转 Python）"
description: "面向已掌握算法的 C++ 竞赛选手：主线 CF 1600-2000 与 AtCoder Difficulty 1600-2000，训练用 Counter / defaultdict / bisect / heapq / itertools / 大整数位集把算法思想直接写成 Python，而不是翻译 C++。"
pinned: true
order: 0
---

# Python 迁移训练题单（C++ 选手转 Python）

这份题单面向**已经有算法基础的 C++ 竞赛选手**。它不重新教 BFS、DP、二分，而是专门训练四件事：

- **表达能力**：用 `Counter`、`defaultdict`、`bisect`、`heapq`、`itertools`、`functools` 把样板代码消掉。
- **实现速度**：C++ 要写 60 行的题，用清晰的 Python 表达出来。
- **思维转换**：拿到题先想「Python 的内置容器和标准库能直接表达这个对象吗」，而不是先想「C++ 怎么写，然后翻译」。
- **正确性与效率**：保留复杂度意识，但不为几毫秒的运行时间牺牲可读性。

主线难度锁定 **Codeforces 1600–2000**；AtCoder 用 **AtCoder Problems 的 Difficulty 估算值**对齐同一档。两个平台的数字**不能直接等同**，所以每道 AtCoder 题都单独标注估算难度，不靠题号（E/F）猜。

[[toc]]

## 零、路线与用法

两层结构：

1. **主线**：严格落在 1600–2000，覆盖第一节（CF 第一阶段 8 题）、第三节（CF 扩展 25 题）、第四节（AtCoder 25 题）。
2. **热身层**：少量难度低于 1600、但**语言迁移价值极高**的题，单独放在第二节说明，不混进主线凑数。

每题固定走两遍，这是本训练的核心动作：

1. **第一遍**：独立完成并 AC，优先「写得清楚」。
2. **第二遍**：不看原代码，重新写一个你认为**更自然**的 Python 版本。
3. **验收**：两版必须对拍通过（随机小数据 + 边界），不能只看样例。
4. **自检**：第二遍是否减少了临时变量、简化了状态、用上了标准库？核心实现能否 10 分钟内重写出来？

统一输入底座，先背下来：

```python
import sys

it = iter(sys.stdin.read().split())
nxt = lambda: next(it)
ni = lambda: int(next(it))
```

`sys.stdin.read().split()` 一次读完按空白切分，天然免疫行末空格 / CRLF / 空行，也避开逐行 `input()` 的调用开销；多测数据用 `for _ in range(ni())` 驱动。

## 一、Codeforces 第一阶段：建立 Pythonic 思维（8 题）

先做这 8 题，重点是字典、计数、序列处理和标准库。

| 题目 | CF 难度 | Python 训练重点 |
| --- | --- | --- |
| [1398C — Good Subarrays](https://vjudge.net/problem/CodeForces-1398C) | 1600 | `defaultdict`、前缀和、计数 |
| [1295C — Obtain The String](https://vjudge.net/problem/CodeForces-1295C) | 1600 | `bisect_right`、字符位置索引 |
| [1395C — Boboniu and Bit Operations](https://vjudge.net/problem/CodeForces-1395C) | 1600 | `all()`、`any()`、生成器表达式 |
| [1373D — Maximum Sum on Even Positions](https://vjudge.net/problem/CodeForces-1373D) | 1600 | 切片、`zip()`、Kadane |
| [466C — Number of Ways](https://vjudge.net/problem/CodeForces-466C) | 1700 | 前缀和、计数状态 |
| [977F — Consecutive Subsequence](https://vjudge.net/problem/CodeForces-977F) | 1700 | 字典 DP、路径恢复 |
| [1681D — Required Length](https://vjudge.net/problem/CodeForces-1681D) | 1700 | `deque`、集合去重、BFS |
| [1948D — Tandem Repeats?](https://vjudge.net/problem/CodeForces-1948D) | 1700 | 字符串操作、`zip()`、区间枚举 |

其中 **1398C、1295C、977F** 最值得反复做：它们最能暴露「还在用 C++ 的下标思维写 Python」这个毛病，同时算法思考量足够。

- **1398C** 的转折点是：把 `sum == 长度` 改写成「把每个元素减 1 后的子段和为 0」，于是答案变成「前缀和相等的对数」——一次 `Counter` 归约，不需要任何双指针。
- **1295C** 的转折点是：把「扫一遍 s 能匹配到 t 的哪里」换成「对每个字符维护出现位置列表，用 `bisect_right` 找下一个位置」，把线性扫描变成 `O(log n)` 跳转。
- **977F** 的转折点是：`dp[x] = dp.get(x-1, 0) + 1`，一个字典就表达了「以 x 结尾的最长连续上升链」，不需要排序、不需要二分、不需要离散化。

## 二、热身层：难度低于 1600 但迁移价值极高

这些题**不进主线**，只在你想快速熟悉语法时做。它们的算法量很小，但每题都能让你第一次用上某个 Python 原语。

| 题目 | AtCoder Difficulty | 用途 |
| --- | --- | --- |
| [ABC350 E — Toward 0](https://vjudge.net/problem/AtCoder-abc350_e) | 1385 | `@cache` 递归 + 记忆化写法入门 |
| [ABC370 E — Avoid K Partition](https://vjudge.net/problem/AtCoder-abc370_e) | 1453 | 前缀和 + `defaultdict` 计数 DP |
| [ABC327 E — Maximize Rating](https://vjudge.net/problem/AtCoder-abc327_e) | 1227 | 浮点 DP、`max()` 归约 |

注意：**ABC350 E、ABC370 E 虽然题号是 E，难度只有 1385 / 1453**，ABC327 E 只有 1227。不要用题号 E/F 反推难度——这就是下面要专门说的一件事。

## 三、难度口径：AtCoder 不能只看 E、F 题号

AtCoder 的题号只表示「这场比赛的第五题 / 第六题」，同一题号在不同年代的难度差异很大。核对 AtCoder Problems 的估算难度后，会看到明显的偏差：

| 题目 | Difficulty | 处理方式 |
| --- | --- | --- |
| ABC350 E — Toward 0 | 1385 | 降为热身题 |
| ABC370 E — Avoid K Partition | 1453 | 降为热身题 |
| ABC327 E — Maximize Rating | 1227 | 不进主线 |
| ABC351 E — Jump Distance Sum | 1627 | 保留 |
| ABC335 F — Hop Sugoroku | 1690 | 保留 |
| ABC332 E — Lucky bag | 1883 | 保留 |

这些数字是第三方估算，会随统计更新变化，但足以避免把明显偏简单的题混进主线。所以本单每一道 AtCoder 题都标注 Difficulty，而不是「E 题 / F 题」。

## 四、Codeforces 扩展题单（25 题）

优先级：★★★ 语言迁移价值很高，建议必做；★★ 既练算法也练 Python 常见实现；★ 写得熟练后再挑战。

### 1600–1700：快速实现与常用容器

| 题目 | 难度 | 重点技巧 | 推荐 |
| --- | --- | --- | --- |
| [1714D — Color with Occurrences](https://vjudge.net/problem/CodeForces-1714D) | 1600 | `str.find()`、字符串覆盖贪心 | ★★★ |
| [660C — Hard Process](https://vjudge.net/problem/CodeForces-660C) | 1600 | 双指针、切片、`sum()` | ★★★ |
| [1555D — Say No to Palindromes](https://vjudge.net/problem/CodeForces-1555D) | 1600 | `itertools.permutations`、模式匹配前缀和 | ★★★ |
| [1519D — Maximum Sum of Products](https://vjudge.net/problem/CodeForces-1519D) | 1600 | `zip()`、中心扩展、增量计算 | ★★ |
| [1753B — Factorial Divisibility](https://vjudge.net/problem/CodeForces-1753B) | 1600 | `Counter`、频次进位 | ★★★ |
| [1288C — Two Arrays](https://vjudge.net/problem/CodeForces-1288C) | 1600 | `math.comb()`、组合计数 | ★★ |
| [915C — Permute Digits](https://vjudge.net/problem/CodeForces-915C) | 1700 | `Counter`、贪心、字符串拼接 | ★★★ |
| [1792D — Fixed Prefix Permutations](https://vjudge.net/problem/CodeForces-1792D) | 1700 | `tuple`、`set`、排列逆映射 | ★★★ |
| [1061C — Multiplicity](https://vjudge.net/problem/CodeForces-1061C) | 1700 | 因数枚举、倒序 DP | ★★ |
| [1829H — Don't Blame Me](https://vjudge.net/problem/CodeForces-1829H) | 1700 | `bit_count()`、小状态 DP | ★★★ |
| [919D — Substring](https://vjudge.net/problem/CodeForces-919D) | 1700 | `deque`、拓扑排序、图上 DP | ★★ |

### 1800：进阶 Pythonic 解法

| 题目 | 难度 | 重点技巧 | 推荐 |
| --- | --- | --- | --- |
| [33B — String Problem](https://vjudge.net/problem/CodeForces-33B) | 1800 | 字符映射、Floyd、字符串构造 | ★★ |
| [1475D — Cleaning the Phone](https://vjudge.net/problem/CodeForces-1475D) | 1800 | 分类排序、前缀和、`bisect` | ★★★ |
| [1063B — Labyrinth](https://vjudge.net/problem/CodeForces-1063B) | 1800 | `deque`、0-1 BFS、网格 | ★★★ |
| [888E — Maximum Subsequence](https://vjudge.net/problem/CodeForces-888E) | 1800 | 折半搜索、`bisect` | ★★★ |
| [1935D — Exam in MAC](https://vjudge.net/problem/CodeForces-1935D) | 1800 | `set`、数学计数、容斥去重 | ★★★ |
| [1915G — Bicycles](https://vjudge.net/problem/CodeForces-1915G) | 1800 | `heapq`、带状态最短路 | ★★ |
| [1930D1 — Sum over all Substrings](https://vjudge.net/problem/CodeForces-1930D1) | 1800 | 字符串状态、DP、贪心 | ★★ |

### 1900–2000：简洁状态表达与提高题

| 题目 | 难度 | 重点技巧 | 推荐 |
| --- | --- | --- | --- |
| [1155D — Beautiful Array](https://vjudge.net/problem/CodeForces-1155D) | 1900 | 多状态线性 DP | ★★★ |
| [1114D — Flood Fill](https://vjudge.net/problem/CodeForces-1114D) | 1900 | `itertools.groupby`、区间 DP | ★★★ |
| [1898D — Absolute Beauty](https://vjudge.net/problem/CodeForces-1898D) | 1900 | 区间关系、`min()`、`max()` | ★★ |
| [1891D — Suspicious logarithms](https://vjudge.net/problem/CodeForces-1891D) | 1900 | 整数数学、分段计数 | ★★ |
| [1891F — A Growing Tree](https://vjudge.net/problem/CodeForces-1891F) | 2000 | 离线逆序、树遍历、状态记录 | ★★ |
| [1893C — Freedom of Choice](https://vjudge.net/problem/CodeForces-1893C) | 2000 | `Counter`、频次统计、构造 | ★★ |
| [2052E — Expression Correction](https://vjudge.net/problem/CodeForces-2052E) | 1900 | 字符串解析与合法性处理 | ★★★ |

这一批里 **CF 1714D、1792D、1829H、1475D、1063B、888E、1114D** 是重点，覆盖 Python 最有价值的几个方向：标准库、哈希容器、二分、队列、枚举、简洁状态表示。

## 五、AtCoder 精选（25 题）

AtCoder 部分更值得投入，因为很多题能充分利用 Python 的表达能力，尤其是 `bisect`、`heapq`、`itertools`、`functools`，以及 Python 整数自带的任意精度位集运算。

### A 组：Difficulty 1600–1749

| 题目 | Difficulty | Pythonic 训练重点 | 推荐 |
| --- | --- | --- | --- |
| [ABC350 F — Transpose](https://vjudge.net/problem/AtCoder-abc350_f) | 1601 | 栈、字符串转换、括号匹配 | ★★★ |
| [ABC195 E — Lucky 7 Battle](https://vjudge.net/problem/AtCoder-abc195_e) | 1609 | 小状态 DP、字符串数字处理 | ★★ |
| [ABC369 F — Gather Coins](https://vjudge.net/problem/AtCoder-abc369_f) | 1618 | `bisect`、LIS、路径恢复 | ★★★ |
| [ABC351 E — Jump Distance Sum](https://vjudge.net/problem/AtCoder-abc351_e) | 1627 | 排序、坐标变换、前缀和 | ★★★ |
| [ABC354 F — Useless for LIS](https://vjudge.net/problem/AtCoder-abc354_f) | 1639 | `bisect_left`、双向 LIS | ★★★ |
| [ABC190 E — Magical Ornament](https://vjudge.net/problem/AtCoder-abc190_e) | 1645 | `deque`、BFS、状压 DP | ★★★ |
| [ABC335 F — Hop Sugoroku](https://vjudge.net/problem/AtCoder-abc335_f) | 1690 | 数组 DP、按步长分类 | ★★ |
| [ABC341 F — Breakdown](https://vjudge.net/problem/AtCoder-abc341_f) | 1604 | 图上状态处理、背包 DP | ★ |
| [ABC372 F — Teleporting Takahashi 2](https://vjudge.net/problem/AtCoder-abc372_f) | 1722 | 压缩状态、计数 DP | ★★ |

**ABC351 E** 和 **ABC354 F** 特别值得做：这两题能让你直接体会到「用几个清晰的数组操作表达算法」比 C++ 里手写循环舒服多少。

### B 组：Difficulty 1750–1899

| 题目 | Difficulty | Pythonic 训练重点 | 推荐 |
| --- | --- | --- | --- |
| [ABC359 F — Tree Degree Optimization](https://vjudge.net/problem/AtCoder-abc359_f) | 1792 | `heapq`、堆贪心 | ★★★ |
| [ABC366 F — Maximum Composition](https://vjudge.net/problem/AtCoder-abc366_f) | 1819 | `cmp_to_key`、排序、DP | ★★★ |
| [ABC346 F — SSttrriinngg in StringString](https://vjudge.net/problem/AtCoder-abc346_f) | 1840 | 字符位置索引、二分答案 | ★★★ |
| [ABC377 G — Edit to Match](https://vjudge.net/problem/AtCoder-abc377_g) | 1782 | Trie、字典、前缀状态 | ★★ |
| [ABC192 F — Potion](https://vjudge.net/problem/AtCoder-abc192_f) | 1783 | 模数状态、分组 DP | ★★ |
| [ABC199 E — Permutation](https://vjudge.net/problem/AtCoder-abc199_e) | 1814 | 位掩码、子集 DP | ★★★ |
| [ABC324 F — Beautiful Path](https://vjudge.net/problem/AtCoder-abc324_f) | 1815 | 二分答案、拓扑 DP | ★★ |
| [ABC334 F — Christmas Present 2](https://vjudge.net/problem/AtCoder-abc334_f) | 1813 | DP、滑动窗口最小值维护 | ★★ |
| [ABC338 F — Negative Traveling Salesman](https://vjudge.net/problem/AtCoder-abc338_f) | 1835 | Floyd、位运算、状压 DP | ★★ |
| [ABC332 E — Lucky bag](https://vjudge.net/problem/AtCoder-abc332_e) | 1883 | 子集枚举、`bit_count()`、DP | ★★★ |
| [ABC187 F — Close Group](https://vjudge.net/problem/AtCoder-abc187_f) | 1895 | 位集、子集划分 DP | ★★ |
| [ABC333 F — Bomb Game 2](https://vjudge.net/problem/AtCoder-abc333_f) | 1770 | 数学递推、二维 DP | ★ |
| [ABC389 E — Square Price](https://vjudge.net/problem/AtCoder-abc389_e) | 1897 | 数学计数、二分答案、整数运算 | ★★★ |

### C 组：Difficulty 1900–2000

| 题目 | Difficulty | Pythonic 训练重点 | 推荐 |
| --- | --- | --- | --- |
| [ABC363 F — Palindromic Expression](https://vjudge.net/problem/AtCoder-abc363_f) | 1913 | `@cache`、因数枚举、记忆化搜索 | ★★★ |
| [ABC348 F — Oddly Similar](https://vjudge.net/problem/AtCoder-abc348_f) | 1955 | 大整数当位集、`bit_count()` | ★★★ |
| [ABC200 E — Patisserie ABC 2](https://vjudge.net/problem/AtCoder-abc200_e) | 1955 | 组合数学、分段计数、构造 | ★★★ |

**ABC348 F** 是典型的「Python 语言优势题」：某些位集计数场景里可以直接用任意精度整数 + `bit_count()`，不必自己实现一整套位集操作。这个思路值得 C++ 转 Python 的选手专门练。

## 六、建议先刷这 12 题

从上面挑出最贴合目标的一组，按这个顺序完成。比起按难度机械刷，这个顺序更利于建立 Python 的自然表达习惯。

- [ ] [[problem: codeforces,1714D]] · [1714D — Color with Occurrences](https://vjudge.net/problem/CodeForces-1714D) · 字符串查找
- [ ] [[problem: codeforces,915C]] · [915C — Permute Digits](https://vjudge.net/problem/CodeForces-915C) · `Counter` 与贪心
- [ ] [[problem: codeforces,1792D]] · [1792D — Fixed Prefix Permutations](https://vjudge.net/problem/CodeForces-1792D) · `tuple` 与 `set`
- [ ] [[problem: atcoder,abc350_f]] · [ABC350 F — Transpose](https://vjudge.net/problem/AtCoder-abc350_f) · 栈与字符串
- [ ] [[problem: atcoder,abc354_f]] · [ABC354 F — Useless for LIS](https://vjudge.net/problem/AtCoder-abc354_f) · `bisect`
- [ ] [[problem: atcoder,abc351_e]] · [ABC351 E — Jump Distance Sum](https://vjudge.net/problem/AtCoder-abc351_e) · 排序与前缀和
- [ ] [[problem: codeforces,1063B]] · [1063B — Labyrinth](https://vjudge.net/problem/CodeForces-1063B) · `deque` 与 0-1 BFS
- [ ] [[problem: atcoder,abc359_f]] · [ABC359 F — Tree Degree Optimization](https://vjudge.net/problem/AtCoder-abc359_f) · `heapq`
- [ ] [[problem: codeforces,888E]] · [888E — Maximum Subsequence](https://vjudge.net/problem/CodeForces-888E) · 折半枚举
- [ ] [[problem: atcoder,abc366_f]] · [ABC366 F — Maximum Composition](https://vjudge.net/problem/AtCoder-abc366_f) · 自定义排序
- [ ] [[problem: codeforces,1114D]] · [1114D — Flood Fill](https://vjudge.net/problem/CodeForces-1114D) · `groupby` 与区间 DP
- [ ] [[problem: atcoder,abc348_f]] · [ABC348 F — Oddly Similar](https://vjudge.net/problem/AtCoder-abc348_f) · 大整数位集

完成这 12 题后，再按区间挑题：**CF 1800–1900** 与 **AtCoder 1700–1900**。这两个区间的题思路有挑战，但 Python 能显著降低实现负担，正好对应「从追求执行速度转向追求思维表达速度」。

## 七、刷题时重点改变什么

固定规则：**第一次写代码优先清晰表达，AC 后再想 Python 有没有更自然的表达方式。**

| C++ 里熟悉的写法 | Python 优先考虑 |
| --- | --- |
| `map<int,int>` 频率统计 | `Counter` |
| `unordered_map<int, vector<int>>` | `defaultdict(list)` |
| `lower_bound` / `upper_bound` | `bisect_left` / `bisect_right` |
| `priority_queue` | `heapq` |
| `queue` / `deque` | `collections.deque` |
| `next_permutation` | `itertools.permutations`（规模允许时） |
| `__builtin_popcountll` | `int.bit_count()` |
| `std::accumulate` | `sum`、`itertools.accumulate` |
| 连续相同元素分组 | `itertools.groupby` |
| 带记忆化的递归 DP | `functools.cache` |
| `bitset<N>` | Python 任意精度 `int`（`dp \|= dp << w`） |
| 手写 `abs`/`min` 循环 | `min(map(...))`、生成器表达式 |

还有一条重要原则：**Pythonic 不等于代码越短越好。** 有些生成器表达式写得很漂亮，但放在百万次循环里可能比普通 `for` 慢。追求的是**减少思维负担和代码噪声**，不是为了压成一行而牺牲清晰性。

## 八、附录：四类核心武器与已验证样例

前面几节解决「练什么」，这一节解决「怎么表达」。四类武器的模式都在仓库里用暴力对拍验证过，可以直接当模板。

### 武器 1：流式归约与游程编码（`itertools`）

```python
from itertools import groupby, accumulate

blocks = [len(list(g)) for _, g in groupby(s)]   # 游程编码，RLE
pref = [0, *accumulate(a)]                       # 前缀和，替代手写循环
```

| 题目 | 武器 | 验收方式 |
| --- | --- | --- |
| CF 1430D String Deletion | `groupby` 压成块长，再在**块层面**贪心：`blocks[i] == 1` 时向后借一个 `>1` 的块，借不到就两两配对 | 枚举所有块长序列（块数 ≤ 6、块长 1–3），与块级记忆化暴力对拍 |
| CF 1748C Zero-Sum Prefixes | `accumulate` 出前缀和，两个 `0` 之间取**众数频次**（`Counter.most_common(1)`），第一个 `0` 之前直接数已有 `0` | 随机小数组 + 枚举每个 `0` 的取值，暴力求最大 `0` 前缀个数 |
| CF 1555D Say No to Palindromes | `permutations("abc")` × `cycle` × `accumulate` 一次生成 6 条代价前缀和，查询取 `min` | 随机串 + 随机区间，与「枚举 6 种模式逐字符比较」对拍 |
| CF 1795D Triangle Coloring | `sorted(w[i:i+3])` 切片 + `math.comb(n//3, n//6)` | $n=6,12$ 随机权重，枚举所有 $\binom{n}{n/2}$ 染色暴力计数 |

### 武器 2：多重集代数与一阶逻辑（`Counter` / `set` / `all` / `any`）

```python
from collections import Counter

same = Counter(s) == Counter(t)      # 多重集相等，不用排序也不用 26 位计数数组
```

| 题目 | 武器 | 验收方式 |
| --- | --- | --- |
| CF 1800E2 Unforgivable Curse | 切片在 `n-k >= k` 时自动返回空串，**不需要 C++ 那套 `if (n - k < k)` 分支**：`Counter(s) == Counter(t) and s[n-k:k] == t[n-k:k]` | 小规模 BFS 求交换可达集合，与切片公式对拍 |
| CF 1468K The Robot | `{"L":-1,"R":1,"D":-1j,"U":1j}` + `accumulate` 得到路径点集，`complex` 可直接进 `set`；撞墙写成 `p = p if p + step == ob else p + step` | 随机指令串，与全平面暴力枚举障碍点对拍 |
| CF 1833E Round Dance | 5 行并查集 + `defaultdict(list)` 分组 + `all(deg[v] == 2 ...)` 谓词判定「该分量本身是完整环」 | $n \le 7$ 随机数据，枚举所有圆舞划分求最小/最大环数 |
| ABC295 D Three Days Ago | 前缀奇偶状态压成 10 位整数 `pref ^= 1 << int(ch)`，`Counter` 数状态，答案 `sum(v*(v-1)//2)` | 随机短串，枚举所有子串直接检查「每数字出现偶数次」 |

### 武器 3：大整数 Bitset 压位（Python `int` 的隐藏福利）

`int` 是任意精度，`dp = 1` 表示「只可达和 0」，`dp |= dp << w` 就是一次完整的 0-1 背包转移；底层是 C 级字长块运算。

```python
dp = 1
for w in weights:
    dp |= dp << w              # 0-1 背包可达性
print((dp >> target) & 1)      # 目标和 target 是否可达
```

| 题目 | 武器 | 验收方式 |
| --- | --- | --- |
| CF 1862F Magic Will Save the World | 两行 `dp \|= dp << s` 做 $\sum s_i \le 10^6$ 子集和，二分时间 $t$，判定用一次掩码 `(dp >> lo) & ((1 << (hi - lo + 1)) - 1)` | $n \le 4$ 随机血量，枚举所有分配 × 时间暴力对拍 |
| CF 1695C Zero Path | `dp` 是长度 $m$ 的整数数组，每元素是位图：`dp[j] \|= dp[j-1]` 横向转移、`dp[j] <<= 1` 处理值为 1 的格子 | $5\times5$ 随机网格，与「逐格维护可达和集合」对拍 |
| ABC147 E Balanced Path | 「可达差值」压成位图，转移 `(x << d) \| (x >> d)`，用 `OFF = (H+W)*81` 统一处理负数，最后从 `OFF` 向两侧找最近置位 | $4\times4$ 以内随机矩阵，与 `@cache` 递归求差值集合对拍 |
| CF 1856E1 PermuTree | 树上背包退化成 `dp \|= dp << sz[child]`，再 `max(x*(tot-x) for x in range(tot+1) if (dp >> x) & 1)` | $n \le 6$ 随机树，枚举所有排列暴力统计 `a[u] < a[lca] < a[v]` |

### 武器 4：免拓扑序记忆化与高精度代数（`@cache` / `math`）

```python
from functools import cache

@cache
def f(state):
    ...        # 只写「状态如何转移」，不写「先算谁」
```

| 题目 | 武器 | 验收方式 |
| --- | --- | --- |
| CF 1458A Row GCD | `math.gcd(*(x - a[0] for x in a[1:]))` 直接解包任意多参数（3.9+），不用管 $a_i \le 10^{18}$ 溢出 | 小规模随机序列，与逐个 `gcd` 累加对拍 |
| CF 1907E Good Triplets | `math.prod(math.comb(int(d)+2, 2) for d in str(n))` 一行出答案 | $n \le 200$ 枚举 $a,b,c$ 暴力统计 |
| CF 1681D Required Length | `set(map(int, str(x)))` 取可选数位，`len(str(x))` 判位数，BFS/`@cache` 都只有几行 | $n \le 6, x \le 120$ 与朴素 BFS 对拍（样例 `2 1→-1`、`3 2→4`、`13 42→12`） |
| CF 1846E2 Rudolf and Snowflakes | `math.isqrt(4*n-3)` 精确开方判项数 3；项数 ≥ 4 时 $k \le 10^6$ 直接枚举，大整数幂无溢出 | $n < 5000$ 全量枚举 $k$ 对拍 |
| ABC300 E Dice Product 3 | `@cache` 写 $f(x) = \frac{1}{5}\sum_{d=2}^{6} f(xd)$（掷 1 原地不动，除以 5 不是 6），`pow(5, -1, 998244353)` 求逆元 | $N \le 40$ 用 `Fraction` 精确概率再转模数对拍 |
| CF 1624E Masha-forgetful | `{sub: (l, r, idx)}` 建长度 2/3 子串字典，DP 条件 `dp[i-L] and s[i-L:i] in seg` 一行，`pre` 数组回溯 | 随机小数据（$m \le 6$）与递归记忆化暴力比较可行性与段数 |

## 九、提交前的三个工程习惯

1. **流式 token 读取**：统一用开头的 `sys.stdin.read().split()` 迭代器，不要混用 `input()` 和 `sys.stdin.readline()`。
2. **整数 key 加随机异或**：CF 上存在专门卡 Python `dict` / `Counter` / `set` 哈希冲突的数据（$O(N)$ 退化到 $O(N^2)$）。对整数 key 异或一个全局随机数即可打散：

   ```python
   from random import getrandbits
   R = getrandbits(30)
   cnt = Counter(x ^ R for x in a)     # 仅用于计数，取值时记得异或回来
   ```

   这只对整数 key 有效；字符串 key 不受这种攻击影响。
3. **按负载选解释器**：
   - 纯循环 / 双指针 / 数组操作 → **PyPy 3-64**（JIT 通常快 5~10 倍）。
   - 大整数 Bitset（`dp |= dp << w`）或重度依赖内置 C 函数 → **CPython** 有时更快，且 `@cache` 递归的内存占用显著小于 PyPy。

另外记牢一条硬事实：**洛谷等平台的 Python 时限通常是 C++ 的 3 倍左右**，别拿 C++ 的常数经验直接套 Python。

## 十、复盘只回答一个问题

每道题做完，回到这一个问题：

> **我这一版代码里，还有哪一段是在「维护下标」而不是「描述对象」？**

能指出具体是哪一段，这道题才算练到。指不出来，说明只是把 C++ 逐行翻译成了 Python，那还不如继续用 C++。
