# P9666 [ICPC 2021 Macao R] Link-Cut Tree
## 题目描述

BaoBao just learned how to use a data structure called link-cut tree to find cycles in a graph and decided to give it a try. BaoBao is given an undirected graph with $n$ vertices and $m$ edges, where the length of the $i$-th edge equals $2^i$. She needs to find a simple cycle with the smallest length.

A simple cycle is a subgraph of the original graph containing $k$ ($3 \le k \le n$) vertices $a_1, a_2, \cdots, a_k$ and $k$ edges such that for all $1 \le i \le k$ there is an edge connecting vertices $a_i$ and $a_{(i \mod k) + 1}$ in the subgraph. The length of a simple cycle is the total length of the edges in the cycle.

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($3 \le n \le 10^5$, $1 \le m \le 10^5$) indicating the number of vertices and edges in the original graph.

For the following $m$ lines, the $i$-th line contains two integers $u_i$ and $v_i$ ($1 \le u_i, v_i \le n$) indicating an edge connecting vertices $u_i$ and $v_i$ with length $2^i$. There are no self loops nor multiple edges. Note that the graph is not necessarily connected.

It's guaranteed that neither the sum of $n$ nor the sum of $m$ of all test cases will exceed $10^6$.

## 输出格式

For each test case output one line. If there are no simple cycles in the graph output ``-1`` (without quotes); Otherwise output $k$ integers separated by a space in increasing order indicating the indices of the edges in the simple cycle with the smallest length. It can be shown that there is at most one answer.

Please, DO NOT output extra spaces at the end of each line, or your solution may be considered incorrect!

## 输入输出样例 #1

### 输入 #1

```
2
6 8
1 2
2 3
5 6
3 4
2 5
5 4
5 1
4 2
4 2
1 2
4 3
```

### 输出 #1

```
2 4 5 6
-1
```

## 说明/提示

The first sample test case is shown below. The integers beside the edges are their indices (outside the parentheses) and lengths (inside the parentheses). The simple cycle with the smallest length consists of edges $2$, $4$, $5$ and $6$ with a length of $2^2 + 2^4 + 2^5 + 2^6 = 116$.
