# 295B Greg and Graph

- Time limit: 3 seconds
- Memory limit: 256 megabytes

## 题目描述

Greg has a weighed directed graph, consisting of *n* vertices. In this graph any pair of distinct vertices has an edge between them in both directions. Greg loves playing with the graph and now he has invented a new game:

- The game consists of *n* steps.
- On the *i*-th step Greg removes vertex number *x*<sub>*i*</sub> from the graph. As Greg removes a vertex, he also removes all the edges that go in and out of this vertex.
- Before executing each step, Greg wants to know the sum of lengths of the shortest paths between all pairs of the remaining vertices. The shortest path can go through any remaining vertex. In other words, if we assume that *d*(*i*, *v*, *u*) is the shortest path between vertices *v* and *u* in the graph that formed before deleting vertex *x*<sub>*i*</sub>, then Greg wants to know the value of the following sum: ![](https://espresso.codeforces.com/90b01d654bf6bf2750396d13f2082c090a85368a.png).

Help Greg, print the value of the required sum before each step.

## 输入格式

The first line contains integer *n* (1 ≤ *n* ≤ 500) — the number of vertices in the graph.

Next *n* lines contain *n* integers each — the graph adjacency matrix: the *j*-th number in the *i*-th line *a*<sub>*ij*</sub> (1 ≤ *a*<sub>*ij*</sub> ≤ 10<sup>5</sup>, *a*<sub>*ii*</sub> = 0) represents the weight of the edge that goes from vertex *i* to vertex *j*.

The next line contains *n* distinct integers: *x*<sub>1</sub>, *x*<sub>2</sub>, ..., *x*<sub>*n*</sub> (1 ≤ *x*<sub>*i*</sub> ≤ *n*) — the vertices that Greg deletes.

## 输出格式

Print *n* integers — the *i*-th number equals the required sum before the *i*-th step.

Please, do not use the `%lld` specifier to read or write 64-bit integers in C++. It is preferred to use the `cin`, `cout` streams of the `%I64d` specifier.

## 输入输出样例 #1

### 输入 #1

```
1
0
1
```

### 输出 #1

```
0
```
