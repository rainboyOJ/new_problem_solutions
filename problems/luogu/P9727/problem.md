# P9727 [EC Final 2022] Aqre
## 题目描述

Given an $n \times m$ matrix, you need to fill it with $0$ and $1$, such that:

- There cannot be **four** consecutive horizontal or vertical cells filled with the same number.
- The cells filled with $1$ form a connected area. (Two cells are adjacent if they share an edge. A group of cells is said to be connected if for every pair of cells it is possible to find a path connecting the two cells which lies completely within the group, and which only travels from one cell to an adjacent cell in each step.)

Please construct a matrix satisfying the conditions above and has as many $1$s as possible. Output the maximum number of $1$s, and the matrix.

## 输入格式

The first line contains an integer $T~(1\leq T\leq 10^3)$ -- the number of test cases.

For each test case, the first line contains two integers $n, m~(2\leq n, m\leq 10^3)$.

### It is guaranteed that the sum of $n\cdot m$ over all test cases does not exceed $10^6$.

## 输出格式

For each test case, output the maximum number of $1$s in the first line. Then output the matrix in the following $n$ lines. If there are multiple solution, output any.

## 输入输出样例 #1

### 输入 #1

```
3
2 2
3 4
3 8
```

### 输出 #1

```
4
11
11
9
1110
1110
1110
18
11101110
10111011
11011011
```
