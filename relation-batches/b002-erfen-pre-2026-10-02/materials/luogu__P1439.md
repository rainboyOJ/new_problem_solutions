# luogu P1439 两个排列的最长公共子序列

> 原文摘录，非模型摘要。来源：`problems/luogu/P1439/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及+/提高-；标签：['动态规划', '二分', '排列', '下标映射']

## 题目解析（原文摘录）

### 思路

把"枚举 $P_1$ 的所有子序列"写成选择树：$P_1$ 的每个数只有**选**和**不选**两种决定，$n$ 个数一共产生 $2^n$ 条完整的 01 选择序列。用 `choose[]` 记录每层的选择，`dfs(dep)` 只负责决定第 `dep` 个数选不选，选中的数按原顺序放进 `candidate`：

- `dep > n` 说明一条完整选择序列生成完毕，`candidate` 就是一个 $P_1$ 的子序列；
- 在叶子节点检查 `candidate` 是否是 $P_2$ 的子序列，是就更新答案。

检查同样用一个指针在 $P_2$ 上顺序扫描：扫完 $P_2$ 时指针走完了 `candidate`，就说明匹配成功。

先生成完整选择序列、再在叶子统一检查，逻辑最短，也最容易确认没有漏掉任何方案。

## 代码位置
- `problems/luogu/P1439/brute.cpp`
- `problems/luogu/P1439/gen.py`
- `problems/luogu/P1439/main.cpp`
- `problems/luogu/P1439/main2.cpp`
