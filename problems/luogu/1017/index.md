---
oj: "luogu"
problem_id: "P1017"
title: "[NOIP 2000 提高组] 进制转换"
description: "每次选择非负余数并据此更新负进制商，逆序连接余数得到表示。"
difficulty: "普及/提高-"
date: 2026-07-16 19:20
toc: true
tags: ["负进制", "进制转换", "整除", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1017
---

[[TOC]]

### 题意

把十进制整数 `n` 转成基数 `R` 的负进制表示，其中 `-20<=R<=-2`，数码必须在 `0..|R|-1`。

### 思路

每一步需要满足 `value=quotient*base+remainder`，并让余数非负。取 `remainder=value%(-base)`，它一定落在 `0..|base|-1`，再计算：

```text
quotient=(value-remainder)//base
```

重复到商为零。余数仍按低位到高位产生，最后反转。原数为零时表示为 `0`。

### Python 知识

- Python 的 `%` 与 `//` 遵守整除恒等式，但负除数余数符号不适合本题，因此主动对 `-base` 取模。
- f-string 直接拼出题目要求的 `n=result(baseR)` 格式。
- 字符表扩展到 `J`，覆盖绝对值不超过 20 的基数。
- `reversed` 惰性反转数码列表。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：负数整除与取模语义。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串构造。

### 代码

@include-code(./main.py, python)


### 复杂度

设结果有 `d` 位，时间复杂度 $O(d)$，空间复杂度 $O(d)$。

### 总结

负进制转换的关键不是照搬 `divmod(value,base)`，而是先保证余数属于合法的非负数码范围。
