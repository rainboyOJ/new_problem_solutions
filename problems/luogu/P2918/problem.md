# P2918 [USACO08NOV] Buying Hay S
## 题目描述

Farmer John is running out of supplies and needs to purchase H (1 <= H <= 50,000) pounds of hay for his cows.

He knows N (1 <= N <= 100) hay suppliers conveniently numbered 1..N. Supplier i sells packages that contain P\_i (1 <= P\_i <= 5,000) pounds of hay at a cost of C\_i (1 <= C\_i <= 5,000) dollars. Each supplier has an unlimited number of packages available, and the packages must be bought whole.

Help FJ by finding the minimum cost necessary to purchase at least H pounds of hay.

## 输入格式

\* Line 1: Two space-separated integers: N and H

\* Lines 2..N+1: Line i+1 contains two space-separated integers: P\_i and C\_i

## 输出格式

\* Line 1: A single integer representing the minimum cost FJ needs to pay to obtain at least H pounds of hay.

## 输入输出样例 #1

### 输入 #1

```
2 15 
3 2 
5 3
```

### 输出 #1

```
9
```

## 说明/提示

FJ can buy three packages from the second supplier for a total cost of 9.
