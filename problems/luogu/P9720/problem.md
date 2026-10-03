# P9720 [EC Final 2022] Map
## 题目描述

It is a famous math fact that if you drop a map of a park completely inside the park, then there exists a point on the map which overlays with the point it represents.

Mio likes this fact a lot so she drops a map of her favorite park completely inside the park. The park $P$ can be represented by a rectangle. A map of the park is just a smaller (or equal) version of the park printed on paper. The map is similar to the original rectangle. Each point on the map corresponds to a point in the park by the similarity transformation.

We can define a map formally: A map is a rectangle $M$ (of smaller or equal size) together with a positive real number $r$ and a bijective function $f:M \rightarrow P$ satisfying 

- For every pair of different points $a, b\in M$, $|f(a)-f(b)|/|a-b|=r$.

$|x-y|$ represents the Euclidean distance between points $x$ and $y$. 

Like in many games, Mio can teleport using the map. Precisely, when Mio is at some point $x$ on the map (including the boundary), she may teleport to the corresponding point $f(x)$ in the park. She may also choose not to teleport. The reverse is also true. When she is at point $y$ in the park (including the boundary), she may teleport to the point $f^{-1}(y)$ on the map representing her current location. And she may also choose not to teleport.

Mio can teleport at most $n$ (and at least $0$) times. Each teleport takes $k$ seconds. Mio can also walk on her foot at a speed of $1$ unit per second. 

Given two points $s$ and $t$, find the minimum time Mio needs to reach $t$ from $s$.

Each teleport can be in any direction (from the map to the park, or from the park to the map). The map may be placed upside down. Since the map is inside the park, it is possible that Mio is on the map and in the park simultaneously. In this case, she may teleport in either direction. 

For example, in the following figure, the park is $ABCD$, and the map is $A'B'C'D'$. When Mio is inside the map, she is on the map and in the park simultaneously. When she is at point $D'$, she can teleport from the map to the park (reaching $D$), and from the park to the map (reaching $D^{\prime\prime}$).

![](https://cdn.luogu.com.cn/upload/image_hosting/hz6nq09e.png)

## 输入格式

The first line contains a single integer $T$ ($1\le T\le 100$) denoting the number of test cases.

For each test case, the first line contains the $4$ corners of the rectangle representing the park. The corners are given in clockwise or counterclockwise order. It is guaranteed that the $4$ corners are distinct.

The second line contains the $4$ corners of the rectangle representing the map. The $i$-th corner of the map corresponds to the $i$-th corner of the park for all $1\le i\le 4$. Note that you can figure out whether the map is placed upside down or not by the order of the corners. The corners are given in clockwise or counterclockwise order. It is guaranteed that the map is inside the park. (The boundary of the map may intersect with the boundary of the park at $1$ or more points.) It is guaranteed that the map is valid, i.e., there is a positive real number and a bijective function from the map to the park satisfying the definition above.

The third line contains two points $s$ and $t$. It is guaranteed that $s$ and $t$ are inside (or on the boundary of) the park.

The fourth line contains two integers $k, n$ ($0\le k\le 2\times 10^6, 0\le n\le 100$), the time each teleport needs, and the maximum number of teleports. 

Each point in the input is represented by a pair of integers whose absolute values are no more than $2\times 10^6$. Integers are separated by single spaces.

## 输出格式

For each test case, output one number representing the answer in one line. Your answer is considered correct if its absolute or relative error does not exceed $10^{-9}$.

## 输入输出样例 #1

### 输入 #1

```
2
0 0 0 2 4 2 4 0
0 0 0 1 2 1 2 0
2 1 4 2
1 1
0 0 0 3 6 3 6 0
0 1 1 0 3 2 2 3
0 0 4 2
0 3
```

### 输出 #1

```
1.0000000000
1.2272623352
```
