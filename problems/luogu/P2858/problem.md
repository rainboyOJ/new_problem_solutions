# P2858 [USACO06FEB] Treats for the Cows G/S
## 题目描述

FJ has purchased $N (1 \le N \le 2000)$ yummy treats for the cows who get money for giving vast amounts of milk. FJ sells one treat per day and wants to maximize the money he receives over a given period time.

The treats are interesting for many reasons:The treats are numbered $1 \sim N$ and stored sequentially in single file in a long box that is open at both ends. On any day, FJ can retrieve one treat from either end of his stash of treats.Like fine wines and delicious cheeses, the treats improve with age and command greater prices.The treats are not uniform: some are better and have higher intrinsic value. Treat $i$ has value $v_i (1 \le v_i \le 1000)$. Cows pay more for treats that have aged longer: a cow will pay $v_i \times a$ for a treat of age $a$. Given the values $v_i$ of each of the treats lined up in order of the index $i$ in their box, what is the greatest value FJ can receive for them if he orders their sale optimally?

The first treat is sold on day $1$ and has age $a=1$. Each subsequent day increases the age by $1$.

## 输入格式

Line $1$: A single integer, $N$.

Lines $2 \sim N+1$: Line $i+1$ contains the value of treat $v_i$.

## 输出格式

Line $1$: The maximum revenue FJ can achieve by selling the treats.

## 输入输出样例 #1

### 输入 #1

```
5
1
3
1
5
2
```

### 输出 #1

```
43
```

## 说明/提示

Explanation of the sample:

Five treats. On the first day FJ can sell either treat $\#1$ (value $1$) or treat $\#5$ (value $2$).

FJ sells the treats (values $1, 3, 1, 5, 2$) in the following order of indices: $1, 5, 2, 3, 4$, making $1 \times 1 + 2 \times 2 + 3 \times 3 + 4 \times 1 + 5 \times 5 = 43$.
