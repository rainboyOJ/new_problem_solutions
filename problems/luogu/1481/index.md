---
oj: "luogu"
problem_id: "P1481"
title: "魔族密码"
description: "枚举前缀 / 字典树 / DP 三种方式求以每个单词结尾的最长词链长度。"
difficulty: "普及-"
date: 2026-07-16 19:57
toc: true
tags: ["字符串", "字典树", "dp", "python", "cpp", "模板题"]
favorite: true
favorite_reason: "trie 的入门题目,trie树建模" 
categories: []
pre:
  - oj: "luogu"
    problem_id: "P2580"
    reason: "集合查重作为 Trie 的简单铺垫"
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1481
---

[[TOC]]

### 题意

从单词表中选出尽量多的词，使前一个词始终是后一个词的前缀。

### 思路

固定链的最后一个单词 `word`。所有出现在词表中的 `word` 前缀天然按长度互相包含，所以把它们全部选上就是最优链。

因此只需把单词放入集合，对每个 `word` 枚举所有非空前缀并统计有多少个也在集合中，取最大值。

单词长度最多 75，切片产生的额外常数很小；相比手写 Trie，这种写法更能体现 Python 的字符串和哈希集合优势。

#### 字典树（Trie）视角

枚举前缀在集合中查找已经够用，但 Trie 能更直观地展现前缀嵌套的关系。以样例 `i → int → integer → intern → internet` 走一遍。

**初始**：`trie = {}`，根节点是空字典。每个节点存子节点和可能的 `#` 标记（单词结尾）。

**插入 `"i"`**：创建 `trie['i'] = {}`，标记 `#`。

```python
trie = { 'i': { '#': True } }
```

走到 `#` 的路上看到了 0 个已结束的单词，加上自己 → 链长 1。

**插入 `"int"`**：沿已有节点 `i` 往下，读到 `n`、`t` 时依次创建。

```python
trie = { 'i': {
    '#': True,          ← 路上看到 1 个
    'n': { 't': { '#': True } }
} }
```

路上看到 `i` 的 `#`（1 个），加上自己 → 链长 2。

**插入 `"integer"`**：走到 `int` 节点的 `#` 时又累加一次。

```python
trie = { 'i': {
    '#': True,
    'n': { 't': {
        '#': True,      ← 路上又看到 1 个
        'e': { 'g': { 'e': { 'r': { '#': True } } } }
    } }
} }
```

路上看到 `i` 和 `int` 两个 `#`，加上自己 → 链长 3。

**插入 `"intern"`**：在 `e` 处分叉，与 `integer` 走不同分支。

```python
trie = { 'i': {
    '#': True,
    'n': { 't': {
        '#': True,
        'e': {                     ← 分叉点
            'g': { 'e': { 'r': { '#': True } } },   ← "integer"
            'r': { 'n': { '#': True } }              ← "intern"
        }
    } }
} }
```

路上看到 `i` 和 `int` 两个 `#`，加上自己 → 链长 3。

**插入 `"internet"`**：沿 `intern` 路径继续往下。

```python
trie = { 'i': {
    '#': True,
    'n': { 't': {
        '#': True,
        'e': {
            'g': { 'e': { 'r': { '#': True } } },
            'r': { 'n': {
                '#': True,          ← 路上看到第 3 个
                'e': { 't': { '#': True } }
            } }
        }
    } }
} }
```

路上看到 `i`、`int`、`intern` 三个 `#`，加上自己 → 链长 4。`ans = 4`。

**本质**：每个单词沿着 Trie 往下走时经过的 `#` 数，就是它有多少个前缀已在词表中。加上自己，就是以它结尾的最长词链长度。

### Python 知识

- `set(data[1:])` 建立平均 $O(1)$ 查询的单词集合。
- `word[:length] in words` 同时使用字节串切片与集合成员测试。
- 内层 `sum(...)` 统计布尔值，外层 `max(...)` 取所有链的最大长度。
- 生成器表达式不保存所有中间计数。
- 字典树可借助嵌套 `dict` 实现，用特殊键 `'#'` 标记单词结尾，省去手写节点类。
- DP 的 `str.startswith` 直接判断前缀关系，配合字典序保证的先后顺序。

### 代码

三种做法：

- 集合 + 前缀枚举（main.py）：最短，Python 风格，$O(nL^2)$
- 字典树（main-trie.py / main.cpp）：路径上数 `#`，$O(nL)$，适合理解前缀嵌套
- DP（main-dp.py）：`startswith` 向前查找，$O(n^2L)$，N=2000 可过

@include-code(./main.py, python)

@include-code(./main-trie.py, python)

@include-code(./main-dp.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

| 做法 | 时间 | 空间 |
|------|------|------|
| 集合 + 前缀枚举 | $O(nL^2)$ | $O(nL)$ |
| 字典树（Python / C++） | $O(nL)$ | $O(\sum L \times 26)$ |
| DP | $O(n^2L)$ | $O(n)$ |

最大单词长度 $L\le75$，三种均能通过。

### 总结

当键本身就是完整短字符串时，Python 集合往往比节点级 Trie 更短、更清楚；Trie 的优势在于理解前缀嵌套结构和稳定的时间表现；DP 在 N 足够小（2000）时也是可选项。
