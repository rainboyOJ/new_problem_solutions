# P9717 [EC Final 2022] Binary String
## 题目描述

You are given a binary string $a_0a_1a_2\dots a_{n-1}$ arranged on a cycle. Each second, you will change every $01$ to $10$ simultaneously. In other words, if $a_i = 0$ and $a_{(i+1) \bmod n} = 1$, you swap $a_i$ and $a_{(i+1)\bmod n}$. For example, we will change $\texttt{100101110}$ to $\texttt{001010111}$.

You need to answer how many different strings will occur in infinite seconds, modulo $998244353$.

Note: Two strings $a_0a_1\dots a_{n-1}$ and $b_0b_1\dots b_{n-1}$ are different if there exists an integer $i\in \{0,1,\ldots, n-1\}$ such that $a_i\neq b_i$. Thus, the cyclic shifts of a string may be different from the original string.

## 输入格式

The first line contains an integer $T$ $(1\leq T\leq 10^6)$ $-$ the number of test cases.

For each test case, the first line contains a binary string $a_0 a_1 \dots a_{n-1}$ $(a_i \in \{0, 1\})$.

It is guaranteed that the sum of lengths of strings over all test cases does not exceed $10^7$.

## 输出格式

For each test case, output one integer representing the answer in one line.

## 输入输出样例 #1

### 输入 #1

```
3
1
001001
0001111
```

### 输出 #1

```
1
3
9
```
