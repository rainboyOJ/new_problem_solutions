---
oj: "roj"
problem_id: "3598"
title: "[NOIP2012-提高] Vigenère 密码"
description: "Vigenère 加密是逐位模 26 加法，解密即逐位做模 26 减法 m = (c − k) mod 26，密钥用 i % len(key) 循环复用，大小写沿用密文原字母。"
difficulty: "普及-"
date: 2026-10-02 09:52
updated: 2026-10-02 09:54
toc: true
tags: ["模拟", "字符串", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3598
---

[[TOC]]

## 形式化题目

给定一个仅含字母的密钥串 $k = k_0, k_1, \dots, k_{n-1}$ 和一个仅含字母的密文串 $C = c_0, c_1, \dots, c_{m-1}$。Vigenère 加密对每个位置 $i$ 做

$$c_i = m_i \circledR k_{i \bmod n}$$

其中 $\circledR$ 满足两条规则：

1. 运算把两侧字母都视为不区分大小写，但结果保持该字母在原串中的大小写；
2. 密钥比明文短时循环重复使用（即下标取 $i \bmod n$）。

按字母表数值化后，$\circledR$ 就是模 26 加法：$c_i \equiv m_i + k_{i \bmod n} \pmod{26}$。

现给定 $k$ 与 $C$，求明文 $M$。

**样例**：密钥 `CompleteVictory`，密文 `Yvqgpxaimmklongnzfwpvxmniytm`，对应明文 `Wherethereisawillthereisaway`。

## 正解

### 思路

**朴素做法：查表反查。** 拿到密文第 $i$ 位 $c_i$ 和密钥第 $i$ 位 $k_i$，去 Vigenère 表里找**第 $k_i$ 行、第 $c_i$ 列**的字母，它就是明文 $m_i$。逐位查完拼接即可。这是正确的，但需要建表或背表，写起来笨。

**观察：表本身就是加法。** Vigenère 表的第 $k$ 行恰好是字母表整体右移 $k$ 位，也就是 $\mathbb{Z}_{26}$ 上的加法表。既然加密是

$$c_i \equiv m_i + k_{i \bmod n} \pmod{26},$$

那么在模 26 里两边同时减去 $k_{i \bmod n}$，"反查表格"就退化成一次减法：

$$m_i \equiv c_i - k_{i \bmod n} \pmod{26}.$$

这就是全部核心。用样例的前 8 位验证这条公式（字母数值 $A=0,\dots,Z=25$）：

| 密文字符 $c_i$ | `Y` | `v` | `q` | `g` | `p` | `x` | `a` | `i` |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 密钥字符 $k_i$ | `C` | `o` | `m` | `p` | `l` | `e` | `t` | `e` |
| $c_i - k_i \pmod{26}$ | $24-2=22$ | $21-14=7$ | $16-12=4$ | $6-15=17$ | $15-11=4$ | $23-4=19$ | $0-19=7$ | $8-4=4$ |
| 明文字符 $m_i$ | `W` | `h` | `e` | `r` | `e` | `t` | `h` | `e` |

逐位拼出 `Wherethere…`，与样例输出一致。注意第 4、7 位 $c_i - k_i$ 为负数，取模后才是 $17$、$7$——Python 的 `%` 对负数直接返回 $[0, 26)$ 内的余数，天然等于"不够就加 26"。

剩下两条规则都是实现细节：

- **大小写**：加密保持了明文大小写，所以密文大小写与明文完全相同。解密时把 $c_i$、$k_i$ 都转小写做数值运算，最后按 $c_i$ 自身大小写输出即可。
- **密钥循环**：第 $i$ 位取 `key[i % len(key)]`，无需把密钥真的复制展开成与明文等长。

### 代码

逐位套用公式，一个推导式完成全部转换：

@include-code(./main.py, python)

`undo` 是单字符的逆 ® 运算；`solve` 只做读入、逐位调用、拼接输出。`i % len(key)` 落实密钥循环，`(ord(ch.lower()) - ord(kch.lower())) % 26` 落实模 26 减法，`ord('A' if ch.isupper() else 'a')` 落实大小写保持。

### 复杂度

- **时间**：每个密文字符做 $O(1)$ 运算，共 $O(m)$，$m \leqslant 1000$。
- **空间**：输出串 $O(m)$，其余 $O(n)$ 存密钥。

## 总结

Vigenère 加密的数学本质是 $\mathbb{Z}_{26}$ 上的逐位加法，所以解密就是逐位减法 $m_i = (c_i - k_{i \bmod n}) \bmod 26$，一次遍历 $O(m)$ 解决。三条容易踩的坑：负数取模用 Python 的 `%` 即可（等价 $+26$）；大小写只是字母的"外壳"，数值运算忽略它、输出时按密文还原；密钥循环用下标取模表达，不必展开。本题解法复杂度与标准 C++ 正解完全同阶。
