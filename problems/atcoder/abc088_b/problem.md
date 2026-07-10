# abc088_b ABC088B - Card Game for Two

## Problem Statement

We have N cards. A number a_i is written on the i-th card.
Alice and Bob will play a game using these cards. In this game, Alice and Bob alternately take one card. Alice goes first.
The game ends when all the cards are taken by the two players, and the score of each player is the sum of the numbers written on the cards he/she has taken. When both players take the optimal strategy to maximize their scores, find Alice's score minus Bob's score.

## 约束

- N is an integer between 1 and 100 (inclusive).
- a_i \ (1 \leq i \leq N) is an integer between 1 and 100 (inclusive).

## 输入格式

Input is given from Standard Input in the following format:

```
N
a_1 a_2 a_3 ... a_N
```

## 输出格式

Print Alice's score minus Bob's score when both players take the optimal strategy to maximize their scores.

## 输入输出样例 #1

### 输入 #1

```
2
3 1
```

### 输出 #1

```
2
```

## 输入输出样例 #2

### 输入 #2

```
3
2 7 4
```

### 输出 #2

```
5
```

## 输入输出样例 #3

### 输入 #3

```
4
20 18 2 18
```

### 输出 #3

```
18
```
