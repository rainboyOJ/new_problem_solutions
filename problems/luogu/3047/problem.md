# P3047 [USACO12FEB] Nearby Cows G
## 题目描述

Farmer John has noticed that his cows often move between nearby fields. Taking this into account, he wants to plant enough grass in each of his fields not only for the cows situated initially in that field, but also for cows visiting from nearby fields.

Specifically, FJ's farm consists of $N$ fields $(1 \leq N \leq 100,000)$, where some pairs of fields are connected with bi-directional trails ($N-1$ of them in total). FJ has designed the farm so that between any two fields $i$ and $j$, there is a unique path made up of trails connecting between $i$ and $j$. Field $i$ is home to $C_i$ cows, although cows sometimes move to a different field by crossing up to $K$ trails $(1 \leq K \leq 20)$.

FJ wants to plant enough grass in each field $i$ to feed the maximum number of cows $M_i$ that could possibly end up in that field -- that is, the number of cows that can potentially reach field $i$ by following at most $K$ trails. Given the structure of FJ's farm and the value of $C_i$ for each field $i$, please help FJ compute $M_i$ for every field $i$.

## 输入格式

* Line $1$: Two space-separated integers, $N$ and $K$.

* Lines $2$ to $N$: Each line contains two space-separated integers, $i$ and $j$ $(1 \leq i,j \leq N)$ indicating that fields $i$ and $j$ are directly connected by a trail.

* Lines $N+1$ to $2N$: Line $N+i$ contains the integer $C_i$. $(0 \leq C_i \leq 1000)$

## 输出格式

* Lines $1$ to $N$: Line $i$ should contain the value of $M_i$.

## 输入输出样例 #1

### 输入 #1

```
6 2 
5 1 
3 6 
2 4 
2 1 
3 2 
1 
2 
3 
4 
5 
6
```

### 输出 #1

```
15 
21 
16 
10 
8 
11
```

## 说明/提示

There are $6$ fields, with trails connecting $(5,1)$, $(3,6)$, $(2,4)$, $(2,1)$, and $(3,2)$. Field $i$ has $C_i = i$ cows.

Field $1$ has $M_1 = 15$ cows within a distance of $2$ trails, etc.
