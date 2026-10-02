# noi_openjudge ch0111-04 网线主管

> 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0111-04/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及-；标签：['二分', '贪心', 'python']

## 题目解析（原文摘录）

[[TOC]]

### 题意

将库存网线切成至少指定数量的等长段，求能得到的最大长度，结果精确到厘米。

### 思路

把米转换为厘米整数，避免浮点误差。若每段长度为 `length`，一条网线能贡献 `wire // length` 段；总段数不少于需求时该长度可行。长度越短越容易可行，满足二分答案的单调性。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n \log M)$，$M$ 是最长网线的厘米长度；空间复杂度为 $O(n)$。

### 总结

要求固定小数精度时，先转换为最小单位整数常能让二分更可靠。

## 代码位置
- `problems/noi_openjudge/ch0111-04/main.cpp`
- `problems/noi_openjudge/ch0111-04/main.py`
