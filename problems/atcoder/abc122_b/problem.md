# abc122_b B - ATCoder

## Problem Statement

You are given a string S consisting of uppercase English letters. Find the length of the longest ACGT string that is a substring (see Notes) of S.
Here, a ACGT string is a string that contains no characters other than A, C, G and T.

## 说明

A substring of a string T is a string obtained by removing zero or more characters from the beginning and the end of T.
For example, the substrings of ATCODER include TCO, AT, CODER, ATCODER and (the empty string), but not AC.

## 约束

- S is a string of length between 1 and 10 (inclusive).
- Each character in S is an uppercase English letter.

## 输入格式

Input is given from Standard Input in the following format:

```
S
```

## 输出格式

Print the length of the longest ACGT string that is a substring of S.

## 输入输出样例 #1

### 输入 #1

```
ATCODER
```

### 输出 #1

```
3
```

## 输入输出样例 #2

### 输入 #2

```
HATAGAYA
```

### 输出 #2

```
5
```

## 输入输出样例 #3

### 输入 #3

```
SHINJUKU
```

### 输出 #3

```
0
```
