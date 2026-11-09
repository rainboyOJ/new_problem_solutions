# D - Knight

## 题目描述

There is a knight - the chess piece - at the origin $(0, 0)$ of a two-dimensional grid.
When the knight is at the square $(i, j)$, it can be moved to either $(i+1,j+2)$ or $(i+2, j+1)$.
In how many ways can the knight reach the square $(X, Y)$?
Find the number of ways modulo $10^9 + 7$.

## 说明/提示

- $1 \leq X \leq 10^6$
- $1 \leq Y \leq 10^6$
- All values in input are integers.

## 输入格式

Input is given from Standard Input in the following format:
$X$ $Y$

## 输出格式

Print the number of ways for the knight to reach $(X, Y)$ from $(0, 0)$, modulo $10^9 + 7$.

## 输入输出样例 #1

### 输入 #1
```
3 3
```

### 输出 #1
```
2
```

## 输入输出样例 #2

### 输入 #2
```
2 2
```

### 输出 #2
```
0
```

## 输入输出样例 #3

### 输入 #3
```
999999 999999
```

### 输出 #3
```
151840682
```
