# D - Restricted Permutation

## 题目描述

Among the sequences $P$ that are permutations of $(1, 2, \dots, N)$ and satisfy the condition below, find the lexicographically smallest sequence.
- For each $i = 1, \dots, M$, $A_i$ appears earlier than $B_i$ in $P$.
If there is no such $P$, print -1.

## 说明/提示

- $2 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq 2 \times 10^5$
- $1 \leq A_i, B_i \leq N$
- $A_i \neq B_i$
- All values in input are integers.

## 输入格式

Input is given from Standard Input in the following format:
$N$ $M$
$A_1$ $B_1$
$\vdots$
$A_M$ $B_M$

## 输出格式

Print the answer.

## 输入输出样例 #1

### 输入 #1
```
4 3
2 1
3 4
2 4
```

### 输出 #1
```
2 1 3 4
```

## 输入输出样例 #2

### 输入 #2
```
2 3
1 2
1 2
2 1
```

### 输出 #2
```
-1
```
