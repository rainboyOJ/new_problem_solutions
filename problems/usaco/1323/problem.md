# 1323 FEB

## 赛事信息

USACO 2023 US Open Contest, Bronze

## 题目描述

Bessie and Elsie are plotting to overthrow Farmer John at last! They plan it out
over $N$ ($1\le N\le 2\cdot 10^5$) text messages. Their conversation can be
represented by a string $S$ of length $N$ where $S_i$ is either $B$ or $E$,
meaning the $i$th message was sent by Bessie or Elsie, respectively.
However, Farmer John hears of the plan and attempts to intercept their
conversation. Thus, some letters of $S$ are $F$, meaning Farmer John obfuscated
the message and the sender is unknown.
The excitement level of a non-obfuscated conversation is the number of
times a cow double-sends - that is, the number of occurrences of substring $BB$
or $EE$ in $S$. You want to find the excitement level of the original message,
but you don’t know which of Farmer John’s messages were actually Bessie’s
/ Elsie’s. Over all possibilities, output all possible excitement levels of
$S$.

## 输入格式

The first line will consist of one integer $N$.
The next line contains $S$.

## 输出格式

First output $K$, the number of distinct excitement levels possible. On the next
$K$ lines, output the excitement levels, in increasing order.

## 输入输出样例 #1

### 输入 #1

```
4
BEEF
```

### 输出 #1

```
2
1
2
```

## 输入输出样例 #2

### 输入 #2

```
9
FEBFEBFEB
```

### 输出 #2

```
2
2
3
```

## 输入输出样例 #3

### 输入 #3

```
10
BFFFFFEBFE
```

### 输出 #3

```
3
2
4
6
```

## 测试点性质

- Inputs 4-8: $N\le 10$
- Inputs 9-20: No additional constraints.
