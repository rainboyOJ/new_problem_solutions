---
oj: "luogu"
problem_id: "P1621"
title: "集合"
description: "筛出不小于 p 的质数，并查集合并区间内每个质数的所有倍数。"
difficulty: "普及+/提高"
date: 2026-07-16 18:26
toc: true
tags: ["并查集", "筛法", "质因数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1621
---

[[TOC]]

### 题意

区间 `[a,b]` 中每个整数最初各自成集。若两个数拥有不小于 `p` 的公共质因数，就能合并它们所在的集合。求所有合并结束后的集合数。

### 思路

不要枚举两个数再分解最大公约数。反过来枚举允许使用的质因数 `prime>=p`：区间中 `prime` 的所有倍数都含有这个公共质因数，因此应该属于同一个集合。

具体做法：

1. 用埃氏筛得到 `2..b` 的所有质数；
2. 对每个不小于 `p` 的质数，求 `[a,b]` 中第一个倍数 `first`；
3. 把其余倍数依次与 `first` 合并；
4. 初始集合数为 `b-a+1`，每次真正合并两个不同集合就减一。

若两个集合能通过多步规则连起来，并查集会自动处理这种传递性。

### Python 知识

- 用下标 `number-a` 保存区间 `[a,b]`，无需为 `0..a-1` 浪费并查集空间。
- `bytearray` 每个筛标记只占一个字节，比 Python 布尔对象列表紧凑。
- 切片赋值 `is_prime[start:b+1:prime]=...` 一次标记整段倍数，循环工作在底层完成。
- `nonlocal groups` 允许内层 `union` 修改外层的集合计数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：Python 容器内存和循环性能注意点。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：按需遍历数值序列的思路。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

筛法约为 $O(b\log\log b)$。合并倍数的总次数不超过调和级数规模，结合并查集可写为 $O(b\log\log b+b\alpha(b))$，空间复杂度 $O(b)$。

### 总结

从“哪些数对能合并”转成“一个合法质因数能连接哪些倍数”，避免了平方级数对枚举；并查集负责把不同质因数产生的连接继续传递。
