# D - Bouquet

## 题目描述

Akari has $n$ kinds of flowers, one of each kind.
She is going to choose one or more of these flowers to make a bouquet.
However, she hates two numbers $a$ and $b$, so the number of flowers in the bouquet cannot be $a$ or $b$.
How many different bouquets are there that Akari can make?
Find the count modulo $(10^9 + 7)$.
Here, two bouquets are considered different when there is a flower that is used in one of the bouquets but not in the other bouquet.

## 说明/提示

- All values in input are integers.
- $2 \leq n \leq 10^9$
- $1 \leq a

## 输入格式

Input is given from Standard Input in the following format:
$n$ $a$ $b$

## 输出格式

Print the number of bouquets that Akari can make, modulo $(10^9 + 7)$. (If there are no such bouquets, print 0.)

## 输入输出样例 #1

### 输入 #1
```
4 1 3
```

### 输出 #1
```
7
```

## 输入输出样例 #2

### 输入 #2
```
1000000000 141421 173205
```

### 输出 #2
```
34076506
```
