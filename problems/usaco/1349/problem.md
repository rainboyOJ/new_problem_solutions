# 1349 Farmer John Actually Farms

## 赛事信息

USACO 2023 December Contest, Bronze

## 题目描述

Farmer John is growing $N$ ($1 \leq N \leq 2\cdot 10^5$) plants of asparagus on
his farm! However some of his plants have genetic differences, so some plants
will grow faster than others. The initial height of the $i$th plant is $h_i$
inches, and after each day, the $i$th plant grows by $a_i$ inches.
FJ likes some of his plants more than others, and he wants some specific plants
to be taller than others. He gives you an array of distinct values
$t_1,\dots,t_N$ containing all integers from $0$ to $N-1$ and he wants the $i$th
plant to have exactly $t_i$ other plants that are taller than it. Find the
minimum number of days so that FJ's request is satisfied, or determine that it
is impossible.

## 输入格式

The first will consist of an integer $T$, denoting the number of independent
test cases $(1 \leq T \leq 10)$.
The first line of each test case consists of an integer $N$.
The second line consists of $N$ integers $h_i$ $(1 \leq h_i \leq 10^9)$ denoting
the initial height of the $i$th plant in inches.
The third line consists of $N$ integers $a_i$ $(1 \leq a_i \leq 10^9)$ denoting
the number of inches the $i$th plant grows each day.
The fourth line consists of $N$ distinct integers $t_i$ denoting the array that
FJ gives you.
It is guaranteed that the sum of $N$ over all test cases does not exceed
$2\cdot 10^5$.

## 输出格式

Output $T$ lines, the answer to each test case on a different line. If it is not
possible, output $-1$.

## 输入输出样例 #1

### 输入 #1

```
6
1
10
1
0
2
7 3
8 10
1 0
2
3 6
10 8
0 1
2
7 3
8 9
1 0
2
7 7
8 8
0 1
2
7 3
8 8
1 0
```

### 输出 #1

```
0
3
2
5
-1
-1
```

## 输入输出样例 #2

### 输入 #2

```
2
5
7 4 1 10 12
3 4 5 2 1
2 1 0 3 4
5
4 10 12 7 1
3 1 1 4 5
2 4 3 1 0
```

### 输出 #2

```
4
7
```

## 样例说明

In the second sample input, there are 2 test cases.
In the first test case, the final heights after day 4 are 19, 20, 21, 18, 16.
In the second test case, the final heights after day 7 are 25, 17, 19, 35, 36.

## 测试点性质

- Input 3: $N \le 2$
- Inputs 4-5: $N \le 50$ and $a_i, h_i \le 10^3$
- Inputs 6-8: $N \le 10^3$
- Inputs 9-13: No additional constraints.
