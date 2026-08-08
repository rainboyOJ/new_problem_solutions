# P1569 [USACO ?] Generic Cow Protests【来源请求】
## 题目描述

Farmer John’s $n$ cows gather and line up in a row to stage a protest. The $i$-th cow has a rationality value $a_i$.

He wants the cows to remain rational; to that end, he plans to partition all the cows into several groups such that within each group the sum of rationality values is at least zero.

Since the cows are arranged in a straight line, each group must be a contiguous segment. Please help John compute the maximum number of groups.

## 输入格式

The first line contains a positive integer $n$, the number of cows.

The next $n$ lines each contain one integer, the rationality value of each cow.

## 输出格式

If a valid partition exists, output one line with a single integer, the answer; otherwise output `Impossible`.

## 输入输出样例 #1

### 输入 #1

```
4
2
3
-3
1
```

### 输出 #1

```
3
```

## 说明/提示

Constraints

- For 30% of the testdata, $1 \le n \le 20$.
- For 100% of the testdata, $1 \le n \le 1000$, $|a_i| \le 10^5$.

Translated by ChatGPT 5
