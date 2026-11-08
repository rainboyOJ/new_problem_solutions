# E - Edge Deletion

## 题目描述

You are given a simple connected undirected graph with $N$ vertices and $M$ edges.
Edge $i$ connects Vertex $A_i$ and Vertex $B_i$, and has a length of $C_i$.
Let us delete some number of edges while satisfying the conditions below. Find the maximum number of edges that can be deleted.
- The graph is still connected after the deletion.
- For every pair of vertices $(s, t)$, the distance between $s$ and $t$ remains the same before and after the deletion.

## 说明/提示

- $2 \leq N \leq 300$
- $N-1 \leq M \leq \frac{N(N-1)}{2}$
- $1 \leq A_i \lt B_i \leq N$
- $1 \leq C_i \leq 10^9$
- $(A_i, B_i) \neq (A_j, B_j)$ if $i \neq j$.
- The given graph is connected.
- All values in input are integers.

## 输入格式

Input is given from Standard Input in the following format:
$N$ $M$
$A_1$ $B_1$ $C_1$
$A_2$ $B_2$ $C_2$
$\vdots$
$A_M$ $B_M$ $C_M$

## 输出格式

Print the answer.

## 输入输出样例 #1

### 输入 #1
```
3 3
1 2 2
2 3 3
1 3 6
```

### 输出 #1
```
1
```

## 输入输出样例 #2

### 输入 #2
```
5 4
1 3 3
2 3 9
3 5 3
4 5 3
```

### 输出 #2
```
0
```

## 输入输出样例 #3

### 输入 #3
```
5 10
1 2 71
1 3 9
1 4 82
1 5 64
2 3 22
2 4 99
2 5 1
3 4 24
3 5 18
4 5 10
```

### 输出 #3
```
5
```
