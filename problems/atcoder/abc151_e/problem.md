# E - Max-Min Sums

## 题目描述

For a finite set of integers $X$, let $f(X)=\max X - \min X$.
Given are $N$ integers $A_1,...,A_N$.
We will choose $K$ of them and let $S$ be the set of the integers chosen. If we distinguish elements with different indices even when their values are the same, there are ${}_N C_K$ ways to make this choice. Find the sum of $f(S)$ over all those ways.
Since the answer can be enormous, print it $\bmod (10^9+7)$.

## 说明/提示

- $1 \leq N \leq 10^5$
- $1 \leq K \leq N$
- $|A_i| \leq 10^9$

## 输入格式

Input is given from Standard Input in the following format:
$N$ $K$
$A_1$ $...$ $A_N$

## 输出格式

Print the answer $\bmod (10^9+7)$.

## 输入输出样例 #1

### 输入 #1
```
4 2
1 1 3 4
```

### 输出 #1
```
11
```

## 输入输出样例 #2

### 输入 #2
```
6 3
10 10 10 -10 -10 -10
```

### 输出 #2
```
360
```

## 输入输出样例 #3

### 输入 #3
```
3 1
1 1 1
```

### 输出 #3
```
0
```

## 输入输出样例 #4

### 输入 #4
```
10 6
1000000000 1000000000 1000000000 1000000000 1000000000 0 0 0 0 0
```

### 输出 #4
```
999998537
```
