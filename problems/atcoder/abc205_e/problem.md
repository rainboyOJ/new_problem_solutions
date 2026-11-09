# E - White and Black Balls

## 题目描述

How many ways are there to arrange $N$ white balls and $M$ black balls in a row from left to right to satisfy the following condition?
- For each $i$ $(1 \leq i \leq N + M)$, let $w_i$ and $b_i$ be the number of white balls and black balls among the leftmost $i$ balls, respectively. Then, $w_i \leq b_i + K$ holds for every $i$.
Since the count can be enormous, find it modulo $(10^9 + 7)$.

## 说明/提示

- $0 \leq N, M \leq 10^6$
- $1 \leq N + M$
- $0 \leq K \leq N$
- All values in input are integers.

## 输入格式

Input is given from Standard Input in the following format:
$N$ $M$ $K$

## 输出格式

Print the answer. Be sure to find the count modulo $(10^9 + 7)$.

## 输入输出样例 #1

### 输入 #1
```
2 3 1
```

### 输出 #1
```
9
```

## 输入输出样例 #2

### 输入 #2
```
1 0 0
```

### 输出 #2
```
0
```

## 输入输出样例 #3

### 输入 #3
```
1000000 1000000 1000000
```

### 输出 #3
```
192151600
```
