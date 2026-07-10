# arc065_a ABC049C - Daydream

## Problem Statement

You are given a string S consisting of lowercase English letters.
Another string T is initially empty.
Determine whether it is possible to obtain S = T by performing the following operation an arbitrary number of times:
- Append one of the following at the end of T: dream, dreamer, erase and eraser.

## 约束

- 1≦|S|≦10^5
- S consists of lowercase English letters.

## 输入格式

The input is given from Standard Input in the following format:

```
S
```

## 输出格式

If it is possible to obtain S = T, print YES. Otherwise, print NO.

## 输入输出样例 #1

### 输入 #1

```
erasedream
```

### 输出 #1

```
YES
```

## 输入输出样例 #2

### 输入 #2

```
dreameraser
```

### 输出 #2

```
YES
```

## 输入输出样例 #3

### 输入 #3

```
dreamerer
```

### 输出 #3

```
NO
```
