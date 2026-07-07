# P1216 [IOI 1994 / USACO1.5] 数字三角形 Number Triangles
## 题目描述

Consider the number triangle shown below. Write a program that calculates the highest sum of numbers that can be passed on a route that starts at the top and ends somewhere on the base. Each step can go either diagonally down to the left or diagonally down to the right.

![](https://cdn.luogu.com.cn/upload/image_hosting/95pzs0ne.png)

In the sample above, the route from $7$ to $3$ to $8$ to $7$ to $5$ produces the highest sum: $30$.

## 输入格式

The first line contains $R$ ($1 \le R \le 1000$), the number of rows. Each subsequent line contains the integers for that particular row of the triangle. All the supplied integers are non-negative and no larger than $100$.

## 输出格式

A single line containing the largest sum using the traversal specified.

## 输入输出样例 #1

### 输入 #1

```
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5
```

### 输出 #1

```
30
```

## 说明/提示

IOI 1994 Day 1 T1 / USACO Training Section 1.5.
