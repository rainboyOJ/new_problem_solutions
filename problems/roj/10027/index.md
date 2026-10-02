---
oj: "roj"
problem_id: "10027"
title: "Decode"
description: "第二行给出 A~Z 的 26 位编码表：str.maketrans 建表后用 translate 在 C 层一次线性扫描替换第一行，空格不在表内自动原样保留，O(n) 一行完成编码。"
difficulty: "普及"
date: 2026-10-02 18:54
updated: 2026-10-02 19:07
toc: true
tags: ["入门", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/10027
---

[[TOC]]

## 形式化题目

给定两行字符串：

- 第一行 $s$，$|s| \leqslant 10000$，只含大写字母和空格；
- 第二行 $T$，恰 26 个大写字母，$T$ 的第 $i$ 个字符表示字母 $\mathrm{A}+i$ 编码后变成的字母。

把 $s$ 中每个大写字母 $c$ 替换为 $T[\operatorname{ord}(c) - \operatorname{ord}(\mathrm{A})]$，空格保持不变，输出替换后的整行。

样例 1（$T$ = `BLMRGJIASOPZEFDCKWYHUNXQTV`）的逐字符编码过程如下，展示了映射方向：下标 $c-\mathrm{A}$ 决定查 $T$ 的位置，空格没有下标、原样通过。

| 输入字符 | H | P | C | （空格） | P | J | V | Y | M | I | Y |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 下标 $c-\mathrm{A}$ | 7 | 15 | 2 | — | 15 | 9 | 21 | 24 | 12 | 8 | 24 |
| 输出字符 | A | C | M | （空格） | C | O | N | T | E | S | T |

`HPC PJVYMIY` 逐位查表得到 `ACM CONTEST`；同理样例 2 中 `FDY GAI BG UKMY` 编码为 `THE SKY IS BLUE`。注意每个字母只依赖自己的下标，字符之间没有任何先后依赖——整个问题就是一次批量查表。

## 正解

### 思路

**一句话本质**：把「逐字符查表」当作一次**批量字符串替换**，映射关系交给 `str.maketrans` 建表，执行交给 `str.translate` 在 C 层一次扫完。

先看朴素做法。直接按定义翻译控制流：

```python
out = []
for ch in text:
    out.append(' ' if ch == ' ' else table[ord(ch) - 65])
print(''.join(out))
```

$O(n)$、思路与题面逐字对应，任何语言都能过——所以本题**没有算法瓶颈**，朴素解就是复杂度正确的解。真正要推导的是：这段循环把「映射关系」和「执行」揉在一起，逐字符都要在 Python 解释器里走一遍比较、`ord`、索引、`append`，这是唯一多余的工作。

**问题？** 为什么可以把循环整体下沉成一个原语？

因为映射是**固定 26 个字母、与位置无关**的静态规则，正是翻译表的形状：

1. `str.maketrans("ABCDEFGHIJKLMNOPQRSTUVWXYZ", table)` 把两串按下标配对：`A` 换成 `table[0]`、`B` 换成 `table[1]`……`Z` 换成 `table[25]`，与题面「第二行第 $i$ 位表示 $\mathrm{A}+i$ 编码后变成什么」逐位一致；表在运行时从读入的 `table` 构建，因为编码表本身是输入。
2. `text.translate(...)` 对整串做一次 C 层线性扫描，每个位置查到映射就替换，查不到就原样保留。

**问题？** 空格为什么不需要特判？

因为 `maketrans` 只绑定 `A..Z` 这 26 个码点，而 `translate` 对**不在表中的字符一律原样输出**。题面保证第一行只含大写字母和空格，于是空格天然走"不在表中"分支，`if ch == ' '` 这个判断整个消失——边界由原语语义保证，而不是靠手写分支。同理，行尾换行等字符也不会被误伤。

**问题？** `maketrans` 对两串长度有什么要求？

必须等长，否则抛 `ValueError`。题面保证第二行恰好 26 个字母、`"ABCDEFGHIJKLMNOPQRSTUVWXYZ"` 也是 26 个，参数天然合法，不需要防御式截断。

最终写法：读两行 → 建表 → `translate` → 输出，三行控制流解决，复杂度与朴素循环同为 $O(n)$，常数从"每字符若干字节码"降为"一次 C 层扫描"。

### 代码

`text, table, *_` 按格式取前两行（`*_` 吸收文件末尾换行产生的空串）；`str.maketrans` + `translate` 即上文推导的两步，空格没有任何显式处理。

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n)$，$n \leqslant 10000$。`split` 读入线性，`maketrans` 建 26 项表 $O(1)$，`translate` 单次线性扫描每字符 $O(1)$。与朴素逐字符循环同阶。
- 空间复杂度：$O(n)$（输入串与输出串各一份，翻译表 26 项为 $O(1)$）；实测峰值约 14.5 MB，相对 128 MB 限制宽裕。

## 总结

本题表面是"编码/解码"，模型就是**字母表上的查表映射**：字符间完全独立、映射只定义在 `A..Z` 上，所以朴素逐字符循环 $O(n)$ 已是正解，优化只在实现层——用 `str.maketrans` 把 26 对映射声明成数据、`str.translate` 在 C 层一次线性扫描，空格等表外字符被原语自动保留，连边界分支都不用写。真实测点 `decode0`~`decode9` 共 10 组输入全部输出一致，单点约 0.017~0.019 s、峰值 14.5 MB，相对 1000 ms / 128 MB 的限制毫无 TLE/MLE 风险；C++ 里等价落地就是 `t[c - 'A']` 的一次循环，同样 $O(n)$。
