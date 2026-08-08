# P1466 [USACO2.2] 集合 Subset Sums
## 题目描述

For many sets of consecutive integers from $1$ through $N$ ($1 \le N \le 39$), one can partition the set into two sets whose sums are identical.

For example, if $N=3$, one can partition the set $\{1,2,3\}$ in one way so that the sums of both subsets are identical:

- $\{3\}$ and $\{1,2\}$

This counts as a single partitioning. Reversing the order counts as the same partitioning and thus does not increase the count of partitions.

If $N=7$, there are four ways to partition the set $\{1,2,3,\ldots,7\}$ so that each partition has the same sum:

- $\{1,6,7\}$ and $\{2,3,4,5\}$
- $\{2,5,7\}$ and $\{1,3,4,6\}$
- $\{3,4,7\}$ and $\{1,2,5,6\}$
- $\{1,2,4,7\}$ and $\{3,5,6\}$

Given $N$, print the number of ways a set containing the integers from $1$ through $N$ can be partitioned into two sets whose sums are identical. Print $0$ if there are no such ways.

Your program must calculate the answer, not look it up from a table.

## 输入格式

A single line with a single integer $N$.

## 输出格式

A single line with a single integer that tells how many same-sum partitions can be made from the set $\{1,2,\ldots,N\}$. The output should be $0$ if there are no ways to make a same-sum partition.

## 输入输出样例 #1

### 输入 #1

```
7
```

### 输出 #1

```
4
```

## 说明/提示

USACO Training Section 2.2.
