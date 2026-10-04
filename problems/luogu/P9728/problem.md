# P9728 [EC Final 2022] Dining Professors
## 题目描述

Prof. Pang invited $n$ professors to his banquet. The professors sit at a round table. For all $i$ from $1$ to $n$, professor $i$ sits adjacent to professor $(i \bmod n) + 1$ and $((i + n - 2)\bmod n) + 1$.

Prof. Pang prepared $n$ dishes. There are $n$ positions on the table. Position $i$ is in front of professor $i$. Professor $i$ can access only the dishes placed at positions $i$, $(i \bmod n) + 1$, and $((i + n - 2)\bmod n) + 1$. Prof. Pang will place exactly one dish at each position.

Among the dishes, $a$ of them are spicy and $n-a$ of them are not spicy. Some (possibly $0$) professors are unable to have spicy food. If a professor can have spicy food, his/her **satisfaction level** is the number of dishes (no matter spicy or not) he/she can access. If a professor cannot have spicy food, his/her satisfaction level is the number of not spicy dishes he/she can access.

Prof. Pang knows whether each professor can have spicy food or not. Please help him to arrange the dishes on the table so that the sum of satisfaction levels over all the professors is maximized. Output the maximum sum.

## 输入格式

The first line contains two integers $n, a$ ($3\le n\le 10^5, 0\le a\le n$). 

The second line contains $n$ integers $b_1, \ldots, b_n$. $b_i$ is $0$ or $1$. $b_i=1$ means professor $i$ can have spicy food. $b_i=0$ means professor $i$ cannot have spicy food.

## 输出格式

Output one integer representing the answer in one line.

## 输入输出样例 #1

### 输入 #1

```
5 2
1 0 1 0 1
```

### 输出 #1

```
13
```
