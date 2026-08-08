# P2926 [USACO08DEC] Patting Heads S
## 题目描述

It's Bessie's birthday and time for party games! Bessie has instructed the $N$ ($1 \le N \le 10^5$) cows conveniently numbered $1\cdots N$ to sit in a circle (so that cow $i$ [except at the ends] sits next to cows $i-1$ and $i+1$; cow $N$ sits next to cow $1$). Meanwhile, Farmer John fills a barrel with one billion slips of paper, each containing some integer in the range $1 \sim 10^6$.

Each cow i then draws a number $A_i$ ($1 \le A_i \le 10^6$) (which is not necessarily unique, of course) from the giant barrel.  Taking turns, each cow $i$ then takes a walk around the circle and pats the heads of all other cows $j$ such that her number $A_i$ is exactly divisible by cow $j$'s number $A_j$; she then sits again back in her original position.

The cows would like you to help them determine, for each cow, the number of other cows she should pat.

## 输入格式

* Line 1: A single integer: $N$

* Lines $2\sim N+1$: Line $i+1$ contains a single integer: $A_i$

## 输出格式

* Lines $1\sim N$: On line $i$, print a single integer that is the number of other cows patted by cow $i$.

## 输入输出样例 #1

### 输入 #1

```
5 
2 
1 
2 
3 
4
```

### 输出 #1

```
2 
0 
2 
1 
3
```

## 说明/提示

The $5$ cows are given the numbers $2$, $1$, $2$, $3$, and $4$, respectively.


The first cow pats the second and third cows; the second cow pats no cows; etc.
