# 1312D Count the Arrays

- Time limit: 2 seconds
- Memory limit: 512 megabytes

## 题目描述

Your task is to calculate the number of arrays such that:

- each array contains $n$ elements;
- each element is an integer from $1$ to $m$;
- for each array, there is exactly one pair of equal elements;
- for each array $a$, there exists an index $i$ such that the array is strictly ascending before the $i$-th element and strictly descending after it (formally, it means that $a_j \lt a_{j + 1}$, if $j \lt i$, and $a_j \gt a_{j + 1}$, if $j \ge i$).

## 输入格式

The first line contains two integers $n$ and $m$ ($2 \le n \le m \le 2 \cdot 10^5$).

## 输出格式

Print one integer — the number of arrays that meet all of the aforementioned conditions, taken modulo $998244353$.

## 输入输出样例 #1

### 输入 #1

```
3 4
```

### 输出 #1

```
6
```

## 说明

The arrays in the first example are:

- $[1, 2, 1]$;
- $[1, 3, 1]$;
- $[1, 4, 1]$;
- $[2, 3, 2]$;
- $[2, 4, 2]$;
- $[3, 4, 3]$.
