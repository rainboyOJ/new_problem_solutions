# P9724 [EC Final 2022] Chase Game
## 题目描述

Prof. Shou is being chased by Prof. Pang on an undirected unweighted simple graph. Initially, Prof. Shou is at vertex $1$. His destination is vertex $n$. Prof. Pang is at vertex $k$.

In each second, Prof. Shou may choose an adjacent vertex and walk to that vertex. Then Prof. Shou is attacked by Prof. Pang. The damage of this attack is equal to $d-dis$ where $d$ is Prof. Pang's attack range and $dis$ is the distance (number of edges in the shortest path) between Prof. Shou and Prof. Pang on the graph. However, when $dis$ is greater than or equal to $d$, Prof. Pang cannot deal any positive damage. In this case, instead of attacking with non-positive damage, he will teleport to the vertex where Prof. Shou is and then deal $d$ damage. (When $dis$ is less than $d$, Prof. Pang will stay at his current vertex.)

Please find the minimum sum of damage Prof. Shou will take to reach vertex $n$ from vertex $1$. Prof. Shou will take the last attack at vertex $n$.

## 输入格式

The first line contains $4$ integers $n, m, k, d$ ($2\le n\le 10^5, n-1\le m\le 2\times 10^5, 1\le k\le n, 1\le d\le 2\times 10^5$).

Each of the next $m$ lines contains two integers $a, b$ ($1\le a, b\le n, a \ne b$) representing an edge of the graph. The edges are distinct. ($a\ b$ and $b\ a$ represents the same edge. Thus, only one of these two lines may appear in the input.)

It is guaranteed that the graph is connected.

## 输出格式

Output one integer representing the answer in one line.

## 输入输出样例 #1

### 输入 #1

```
5 5 3 1
1 2
2 4
4 5
1 3
3 5
```

### 输出 #1

```
2
```

## 输入输出样例 #2

### 输入 #2

```
13 17 12 3
1 2
2 3
3 4
4 13
5 13
7 8
7 9
7 10
7 11
7 6
12 7
1 8
8 9
9 10
10 11
11 6
6 13
```

### 输出 #2

```
7
```
