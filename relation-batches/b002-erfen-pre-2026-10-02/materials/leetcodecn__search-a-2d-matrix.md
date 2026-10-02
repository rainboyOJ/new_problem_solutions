# leetcodecn search-a-2d-matrix 搜索二维矩阵

> 原文摘录，非模型摘要。来源：`problems/leetcodecn/search-a-2d-matrix/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及-；标签：['二分查找', '矩阵']

## 题目解析（原文摘录）

### 题意

给定满足"每行递增、每行首元素大于上一行末元素"的 `m x n` 矩阵，判断 `target` 是否存在。要求 $O(\log(mn))$。

### 思路

矩阵的行间递增性质使得整行拼起来就是一个严格递增的一维数组。因此只需把一维下标 `k` 映射到二维：`matrix[k / n][k % n]`，然后对 `k` 做标准二分查找即可。

映射公式：`k ∈ [0, m*n)`，行号 `k / n`，列号 `k % n`。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(\log(mn))$。
- 空间复杂度：$O(1)$。

### 总结

二维矩阵的二分查找，核心是建立一维到二维的下标映射。前提是矩阵满足行间递增的严格条件，这样一维展开后仍有序。

## 代码位置
- `problems/leetcodecn/search-a-2d-matrix/main.cpp`
- `problems/leetcodecn/search-a-2d-matrix/main.py`
