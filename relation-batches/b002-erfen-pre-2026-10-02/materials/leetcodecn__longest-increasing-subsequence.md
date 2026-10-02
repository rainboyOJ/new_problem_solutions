# leetcodecn longest-increasing-subsequence 最长递增子序列

> 原文摘录，非模型摘要。来源：`problems/leetcodecn/longest-increasing-subsequence/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及+/提高；标签：['动态规划', '二分查找', '贪心']

## 题目解析（原文摘录）

### 题意
求数组的最长严格递增子序列长度。

### 思路
维护 `tails` 数组：`tails[k]` 表示长度为 `k+1` 的递增子序列的最小结尾元素。对每个 `x`，用 `lower_bound` 找到 `tails` 中第一个 $\geqslant x$ 的位置并替换；若 `x` 大于所有 `tails`，则追加。

严格递增用 `lower_bound`（$\geqslant$），非严格递增用 `upper_bound`（$>$）。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n \log n)$。
- 空间复杂度：$O(n)$。

### 总结
LIS 的 $O(n \log n)$ 解法：`tails` 数组维护的是"各长度最优结尾"，`lower_bound` 更新保证严格递增。`tails` 的长度即为答案，但 `tails` 本身不一定是合法的子序列。

## 代码位置
- `problems/leetcodecn/longest-increasing-subsequence/main.cpp`
- `problems/leetcodecn/longest-increasing-subsequence/main.py`
