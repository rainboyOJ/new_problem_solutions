# abc087_b ABC087B - Coins

## Problem Statement

You have A 500-yen coins, B 100-yen coins and C 50-yen coins (yen is the currency of Japan).
In how many ways can we select some of these coins so that they are X yen in total?
Coins of the same kind cannot be distinguished. Two ways to select coins are distinguished when, for some kind of coin, the numbers of that coin are different.

## 约束

- 0 \leq A, B, C \leq 50
- A + B + C \geq 1
- 50 \leq X \leq 20 000
- A, B and C are integers.
- X is a multiple of 50.

## 输入格式

Input is given from Standard Input in the following format:

```
A
B
C
X
```

## 输出格式

Print the number of ways to select coins.

## 输入输出样例 #1

### 输入 #1

```
2
2
2
100
```

### 输出 #1

```
2
```

## 输入输出样例 #2

### 输入 #2

```
5
1
0
150
```

### 输出 #2

```
0
```

## 输入输出样例 #3

### 输入 #3

```
30
40
50
6000
```

### 输出 #3

```
213
```
