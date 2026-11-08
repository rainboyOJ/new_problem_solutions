# E - Find Permutation

## 题目描述

There is a length-$N$ sequence $A=(A_1,\ldots,A_N)$ that is a permutation of $1,\ldots,N$.
While you do not know $A$, you know that $A_{X_i}Can $A$ be uniquely determined? If it is possible, find $A$.

## 说明/提示

- $2 \leq N \leq 2\times 10^5$
- $1 \leq M \leq 2\times 10^5$
- $1\leq X_i,Y_i \leq N$
- All values in the input are integers.
- There is an $A$ consistent with the input.

## 输入格式

The input is given from Standard Input in the following format:
$N$ $M$
$X_1$ $Y_1$
$\vdots$
$X_M$ $Y_M$

## 输出格式

If $A$ can be uniquely determined, print Yes in the first line. Then, print $A_1,\ldots,A_N$ in the second line, separated by spaces.
If $A$ cannot be uniquely determined, just print No.

## 输入输出样例 #1

### 输入 #1
```
3 2
3 1
2 3
```

### 输出 #1
```
Yes
3 1 2
```

## 输入输出样例 #2

### 输入 #2
```
3 2
3 1
3 2
```

### 输出 #2
```
No
```

## 输入输出样例 #3

### 输入 #3
```
4 6
1 2
1 2
2 3
2 3
3 4
3 4
```

### 输出 #3
```
Yes
1 2 3 4
```
