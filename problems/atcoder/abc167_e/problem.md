# E - Colorful Blocks

## 题目描述

There are $N$ blocks arranged in a row. Let us paint these blocks.
We will consider two ways to paint the blocks different if and only if there is a block painted in different colors in those two ways.
Find the number of ways to paint the blocks under the following conditions:
- For each block, use one of the $M$ colors, Color $1$ through Color $M$, to paint it. It is not mandatory to use all the colors.
- There may be at most $K$ pairs of adjacent blocks that are painted in the same color.
Since the count may be enormous, print it modulo $998244353$.

## 说明/提示

- All values in input are integers.
- $1 \leq N, M \leq 2 \times 10^5$
- $0 \leq K \leq N - 1$

## 输入格式

Input is given from Standard Input in the following format:
$N$ $M$ $K$

## 输出格式

Print the answer.

## 输入输出样例 #1

### 输入 #1
```
3 2 1
```

### 输出 #1
```
6
```

## 输入输出样例 #2

### 输入 #2
```
100 100 0
```

### 输出 #2
```
73074801
```

## 输入输出样例 #3

### 输入 #3
```
60522 114575 7559
```

### 输出 #3
```
479519525
```
