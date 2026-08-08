# P2851 [USACO06DEC] The Fewest Coins G
## 题目描述

Farmer John has gone to town to buy some farm supplies. Being a very efficient man, he always pays for his goods in such a way that the smallest number of coins changes hands, i.e., the number of coins he uses to pay plus the number of coins he receives in change is minimized. Help him to determine what this minimum number is.

FJ wants to buy $T (1 \le T \le 10,000)$ cents of supplies. The currency system has $N (1 \le N \le 100)$ different coins, with values $V_1, V_2, \dots, V_N (1 \le V_i \le 120)$. Farmer John is carrying $C_1$ coins of value $V_1$, $C_2$ coins of value $V_2$, ...., and $C_N$ coins of value $V_N\ (0 \le C_i \le 10,000)$. The shopkeeper has an unlimited supply of all the coins, and always makes change in the most efficient manner (although Farmer John must be sure to pay in a way that makes it possible to make the correct change).

## 输入格式

Line $1$: Two space-separated integers: $N$ and $T$.

Line $2$: $N$ space-separated integers, respectively $V_1, V_2, \dots, V_N$.

Line $3$: $N$ space-separated integers, respectively $C_1, C_2, \dots C_N$.

## 输出格式

Line $1$: A line containing a single integer, the minimum number of coins involved in a payment and change-making. If it is impossible for Farmer John to pay and receive exact change, output $-1$.

## 输入输出样例 #1

### 输入 #1

```
3 70
5 25 50
5 2 1
```

### 输出 #1

```
3
```

## 说明/提示

Farmer John pays $75$ cents using a $50$ cents and a $25$ cents coin, and receives a $5$ cents coin in change, for a total of $3$ coins used in the transaction.
