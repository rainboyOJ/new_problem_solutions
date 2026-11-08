# D - Shortest Path Queries 2

## 题目描述

There are $N$ cities and $M$ roads in the Kingdom of Takahashi.
The cities are numbered $1$ through $N$, and the roads are numbered $1$ through $M$. Road $i$ is a **one-way** road that leads from City $A_i$ to City $B_i$, and it takes $C_i$ minutes to go through it.
Let us define $f(s, t, k)$ as the answer to the following query.
- Compute the minimum time needed to get from City $s$ to City $t$. Here, other than the Cities $s$ and $t$, it is only allowed to pass through Cities $1$ through $k$. If City $t$ is unreachable or $s = t$, the answer should be $0$.
Compute $f(s,t,k)$ for all triples $s,t,k$ and print the sum of them. More formally, print $\displaystyle \sum_{s = 1}^N \sum_{t = 1}^N \sum_{k = 1}^N f(s, t, k)$.

## 说明/提示

- $1 \leq N \leq 400$
- $0 \leq M \leq N(N-1)$
- $1 \leq A_i \leq N$ $(1 \leq i \leq M)$
- $1 \leq B_i \leq N$ $(1 \leq i \leq M)$
- $A_i \neq B_i$ $(1 \leq i \leq M)$
- $1 \leq C_i \leq 10^6$ $(1 \leq i \leq M)$
- $A_i \neq A_j$ or $B_i \neq B_j$, if $i \neq j$.
- All values in input are integers.

## 输入格式

Input is given from Standard Input in the following format:
$N$ $M$
$A_1$ $B_1$ $C_1$
$\vdots$
$A_M$ $B_M$ $C_M$

## 输出格式

Print $\displaystyle \sum_{s = 1}^N \sum_{t = 1}^N \sum_{k = 1}^N f(s, t, k)$.

## 输入输出样例 #1

### 输入 #1
```
3 2
1 2 3
2 3 2
```

### 输出 #1
```
25
```

## 输入输出样例 #2

### 输入 #2
```
3 0
```

### 输出 #2
```
0
```

## 输入输出样例 #3

### 输入 #3
```
5 20
1 2 6
1 3 10
1 4 4
1 5 1
2 1 5
2 3 9
2 4 8
2 5 6
3 1 5
3 2 1
3 4 7
3 5 9
4 1 4
4 2 6
4 3 4
4 5 8
5 1 2
5 2 5
5 3 6
5 4 5
```

### 输出 #3
```
517
```
