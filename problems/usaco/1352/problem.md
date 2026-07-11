# 1352 Target Practice

## 赛事信息

USACO 2023 December Contest, Silver

## 题目描述

Bessie is a robovine, also known as a cowborg. She is on a number line trying to
shoot a series of $T$ $(1 \leq T \leq 10^5)$ targets located at distinct
positions. Bessie starts at position $0$ and follows a string of $C$
$(1 \leq C \leq 10^5)$ commands, each one of L, F, or R:
- L: Bessie moves one unit to the left.
- R: Bessie moves one unit to the right.
- F: Bessie fires. If there is a target at Bessie's current position, it is hit and destroyed, and cannot be hit again.
If you are allowed to change up to one command in the string to a different
command before Bessie starts following it, what is the maximum number of targets
that Bessie can hit?

## 输入格式

The first line contains $T$ and $C$.
The next line contains the locations of the $T$ targets, distinct integers in the range
$[-C,C]$.
The next line contains the command string of length $C$, containing only the
characters F, L, and R.

## 输出格式

Print the maximum number of targets that Bessie can hit after changing up to one
command in the string.

## 输入输出样例 #1

### 输入 #1

```
3 7
0 -1 1
LFFRFRR
```

### 输出 #1

```
3
```

## 输入输出样例 #2

### 输入 #2

```
1 5
0
FFFFF
```

### 输出 #2

```
1
```

## 输入输出样例 #3

### 输入 #3

```
5 6
1 2 3 4 5
FFRFRF
```

### 输出 #3

```
3
```

## 测试点性质

- Inputs 4-6: $T,C \le 1000$
- Inputs 7-15: No additional constraints.
