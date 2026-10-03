# P9718 [EC Final 2022] Best Carry Player 2
## 题目描述

Given a positive integer $x$, find the minimum positive integer $y$ such that the number of $\textbf{carries}^1$ of $x+y$ is exactly $k$.

We adds numbers $\textbf{by column addition in base-ten}$, just like what we normally do in primary school. For example, there are two carries in the following addition.

![](https://cdn.luogu.com.cn/upload/image_hosting/pfnper3r.png)

$^1$ which means ``进位`` in Chinese.

## 输入格式

The first line contains an integer $T$ $(1\leq T\leq 10^5)$ $-$ the number of test cases.

For each test case, the first line contains two integers $x, k$ $(1\leq x < 10^{18}, 0\leq k \leq 18)$.

## 输出格式

For each test case, output one integer representing the answer in one line. If there is no solution, output $-1$ instead.

## 输入输出样例 #1

### 输入 #1

```
4
12345678 0
12345678 5
12345678 18
990099 5
```

### 输出 #1

```
1
54322
999999999987654322
9910
```
