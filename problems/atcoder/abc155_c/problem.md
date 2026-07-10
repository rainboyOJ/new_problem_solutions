# abc155_c C - Poll

## Problem Statement

We have N voting papers. The i-th vote (1 \leq i \leq N) has the string S_i written on it.
Print all strings that are written on the most number of votes, in lexicographical order.

## 约束

- 1 \leq N \leq 2 \times 10^5
- S_i (1 \leq i \leq N) are strings consisting of lowercase English letters.
- The length of S_i (1 \leq i \leq N) is between 1 and 10 (inclusive).

## 输入格式

Input is given from Standard Input in the following format:

```
N
S_1
:
S_N
```

## 输出格式

Print all strings in question in lexicographical order.

## 输入输出样例 #1

### 输入 #1

```
7
beat
vet
beet
bed
vet
bet
beet
```

### 输出 #1

```
beet
vet
```

## 输入输出样例 #2

### 输入 #2

```
8
buffalo
buffalo
buffalo
buffalo
buffalo
buffalo
buffalo
buffalo
```

### 输出 #2

```
buffalo
```

## 输入输出样例 #3

### 输入 #3

```
7
bass
bass
kick
kick
bass
kick
kick
```

### 输出 #3

```
kick
```

## 输入输出样例 #4

### 输入 #4

```
4
ushi
tapu
nichia
kun
```

### 输出 #4

```
kun
nichia
tapu
ushi
```
