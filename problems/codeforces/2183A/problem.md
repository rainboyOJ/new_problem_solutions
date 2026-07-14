# 2183A Binary Array Game

- Time limit: 1 second
- Memory limit: 256 megabytes

## 题目描述

Alice and Bob are playing a game on an array $a$ of size $n$, containing only numbers `0` and `1`. Alice moves first, with each player alternating turns.

In a player's turn, he or she chooses two integers $l$ and $r$ such that $1 \leq l \color{red}{ \lt } r \leq |a|$ (here, $|a|$ denotes the current length of $a$). Then, the subarray $[a_l,a_{l+1},\ldots,a_r]$ is replaced with a single number $1-\operatorname{min}(a_l,a_{l+1},\ldots,a_r)$. That is, if all numbers in the subarray are $1$, then the subarray $[a_l,a_{l+1},\ldots,a_r]$ is removed, and the number $0$ is inserted where the subarray was. Otherwise, the subarray $[a_l,a_{l+1},\ldots,a_r]$ is removed, and the number $1$ is inserted where the subarray was.

The game ends when there is exactly one number left in the array (where the player to go cannot make legal moves). Alice wins if the final number is $0$. Otherwise, Bob wins. Please determine who wins this game with optimal play.

## 输入格式

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 100$). The description of the test cases follows.

The first line of each test case contains a positive integer $n$ ($3 \le n \le 100$), denoting the length of the array $a$.

The second line of each test case contains $n$ integers $a_1,a_2,\ldots,a_n$ ($0 \le a_i \le 1$).

## 输出格式

For each test case, output `Alice` if Alice wins, and `Bob` otherwise. You may output each character in any case. For example, the answers `Alice`, `alice`, `ALICE`, `AliCe` will all be interpreted the same.

## 输入输出样例 #1

### 输入 #1

```
7
3
1 1 0
3
1 1 1
3
0 1 0
4
0 0 0 0
5
1 0 1 0 1
6
0 1 0 1 0 1
6
0 1 0 1 0 0
```

### 输出 #1

```
Alice
Alice
Bob
Bob
Alice
Alice
Bob
```

## 说明

In the first test case, Alice can win by choosing $l=2$ and $r=3$. Since $1-\operatorname{min}(a_2,a_3)=1$, the subarray $[1,0]$ is replaced with a single integer $1$, and $a$ becomes $[1,1]$. At this point, it is Bob's turn, and the only move he has is to choose $l=1$ and $r=2$. Since $1-\operatorname{min}(a_1,a_2)=0$, the array $a$ becomes $[0]$. The game now ends, and Alice wins because the last number is $0$.

In the second test case, Alice can win by choosing $l=1$ and $r=3$ in her first move. The array becomes $[0]$, and the game ends as a win for Alice immediately.
