# abc128_b B - Guidebook

## Problem Statement

You have decided to write a book introducing good restaurants.
There are N restaurants that you want to introduce: Restaurant 1, Restaurant 2, ..., Restaurant N. Restaurant i is in city S_i, and your assessment score of that restaurant on a 100-point scale is P_i.
No two restaurants have the same score.
You want to introduce the restaurants in the following order:
- The restaurants are arranged in lexicographical order of the names of their cities.
- If there are multiple restaurants in the same city, they are arranged in descending order of score.
Print the identification numbers of the restaurants in the order they are introduced in the book.

## 约束

- 1 ≤ N ≤ 100
- S is a string of length between 1 and 10 (inclusive) consisting of lowercase English letters.
- 0 ≤ P_i ≤ 100
- P_i is an integer.
- P_i ≠ P_j (1 ≤ i

## 输入格式

Input is given from Standard Input in the following format:

```
N
S_1 P_1
:
S_N P_N
```

## 输出格式

Print N lines. The i-th line (1 ≤ i ≤ N) should contain the identification number of the restaurant that is introduced i-th in the book.

## 输入输出样例 #1

### 输入 #1

```
6
khabarovsk 20
moscow 10
kazan 50
kazan 35
moscow 60
khabarovsk 40
```

### 输出 #1

```
3
4
6
1
5
2
```

## 输入输出样例 #2

### 输入 #2

```
10
yakutsk 10
yakutsk 20
yakutsk 30
yakutsk 40
yakutsk 50
yakutsk 60
yakutsk 70
yakutsk 80
yakutsk 90
yakutsk 100
```

### 输出 #2

```
10
9
8
7
6
5
4
3
2
1
```
