# P9719 [EC Final 2022] Minimum Suffix
## 题目描述

For a string $s$ of length $n$, we define $p_j = x$ if $s[x\ldots j]$ is the minimum suffix of $s[1\ldots j]$, for all $j=1,\ldots, n$. (A suffix is the minimum suffix of a string if it is lexicographically smaller than any other suffix of that string.)

You are to recover $s$ from $p_1,\ldots, p_n$. If there are multiple answers, find the lexicographically smallest one.

## 输入格式

The first line contains a single integer $T$ ($1\le T\le 10^5$) representing the number of test cases.

For each test case, the first line contains a single integer $n$ ($1\le n\le 3\times 10^6$) representing the length of $s$. The next line contains $n$ integers $p_1,\ldots, p_n$ ($1\le p_i\le i$ for all $1\le i\le n$).

It is guaranteed that the sum of $n$ over all test cases does not exceed $3\times 10^6$.

## 输出格式

For each test case, output one line. If there is no solution, output $-1$. Otherwise, output the lexicographically smallest $s$. Characters of $s$ are represented by positive integers. Smaller integers represent smaller characters in the lexicographical order.

## 输入输出样例 #1

### 输入 #1

```
6
3
1 1 1
3
1 1 2
3
1 1 3
3
1 2 1
3
1 2 2
3
1 2 3
```

### 输出 #1

```
1 2 2
-1
1 2 1
1 1 2
2 1 2
1 1 1
```

## 说明/提示

As the input/output can be huge, it is recommended to use fast input/output methods.
