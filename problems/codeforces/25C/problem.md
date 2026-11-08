# 25C Roads in Berland

- Time limit: 2 seconds
- Memory limit: 256 megabytes

## 题目描述

There are *n* cities numbered from 1 to *n* in Berland. Some of them are connected by two-way roads. Each road has its own length — an integer number from 1 to 1000. It is known that from each city it is possible to get to any other city by existing roads. Also for each pair of cities it is known the shortest distance between them. Berland Government plans to build *k* new roads. For each of the planned road it is known its length, and what cities it will connect. To control the correctness of the construction of new roads, after the opening of another road Berland government wants to check the sum of the shortest distances between all pairs of cities. Help them — for a given matrix of shortest distances on the old roads and plans of all new roads, find out how the sum of the shortest distances between all pairs of cities changes after construction of each road.

## 输入格式

The first line contains integer *n* (2 ≤ *n* ≤ 300) — amount of cities in Berland. Then there follow *n* lines with *n* integer numbers each — the matrix of shortest distances. *j*-th integer in the *i*-th row — *d*<sub>*i*, *j*</sub>, the shortest distance between cities *i* and *j*. It is guaranteed that *d*<sub>*i*, *i*</sub> = 0, *d*<sub>*i*, *j*</sub> = *d*<sub>*j*, *i*</sub>, and a given matrix is a matrix of shortest distances for some set of two-way roads with integer lengths from 1 to 1000, such that from each city it is possible to get to any other city using these roads.

Next line contains integer *k* (1 ≤ *k* ≤ 300) — amount of planned roads. Following *k* lines contain the description of the planned roads. Each road is described by three space-separated integers *a*<sub>*i*</sub>, *b*<sub>*i*</sub>, *c*<sub>*i*</sub> (1 ≤ *a*<sub>*i*</sub>, *b*<sub>*i*</sub> ≤ *n*, *a*<sub>*i*</sub> ≠ *b*<sub>*i*</sub>, 1 ≤ *c*<sub>*i*</sub> ≤ 1000) — *a*<sub>*i*</sub> and *b*<sub>*i*</sub> — pair of cities, which the road connects, *c*<sub>*i*</sub> — the length of the road. It can be several roads between a pair of cities, but no road connects the city with itself.

## 输出格式

Output *k* space-separated integers *q*<sub>*i*</sub> (1 ≤ *i* ≤ *k*). *q*<sub>*i*</sub> should be equal to the sum of shortest distances between all pairs of cities after the construction of roads with indexes from 1 to *i*. Roads are numbered from 1 in the input order. Each pair of cities should be taken into account in the sum exactly once, i. e. we count unordered pairs.

## 输入输出样例 #1

### 输入 #1

```
2
0 5
5 0
1
1 2 3
```

### 输出 #1

```
3
```
