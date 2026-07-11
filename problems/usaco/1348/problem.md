# 1348 Cowntact Tracing 2

## 赛事信息

USACO 2023 December Contest, Bronze

## 题目描述

Farmer John has $N$ cows in a line ($1 \leq N \leq 3\cdot 10^5$). Unfortunately,
there is a sickness spreading throughout.
Initially, some cows start off infected. Every night, an infected cow spreads
the sickness to the cows on their left and right (if they exist). Once a cow is
infected, she stays infected.
After some amount of nights, Farmer John realizes that the issue has gotten out
of control, so he tests his cows to determine who has the sickness. Find the
minimum number of cows that could have started with the sickness.

## 输入格式

The first line contains $N$, the number of cows that Farmer John has.
The next line contains an $N$ character bitstring of only $1$s and $0$s where a
$1$ represents an infected cow and a $0$ represents an uninfected cow after some
number of nights.

## 输出格式

Output a single integer: the minimum number of cows that could have started
with the sickness.

## 输入输出样例 #1

### 输入 #1

```
5
11111
```

### 输出 #1

```
1
```

## 输入输出样例 #2

### 输入 #2

```
6
011101
```

### 输出 #2

```
4
```

## 样例说明

The only initial state and number of nights that could have led to this final
state is if no nights have passed and each of the four infected cows in the
input started off with the sickness.

## 测试点性质

- Inputs 3-7: $N \le 1000$
- Inputs 8-12: No additional constraints.
