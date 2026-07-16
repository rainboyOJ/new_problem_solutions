# CF25E Test
## 题目描述

Sometimes it is hard to prepare tests for programming problems. Now Bob is preparing tests to new problem about strings — input data to his problem is one string. Bob has 3 wrong solutions to this problem. The first gives the wrong answer if the input data contains the substring $ s_{1} $ , the second enters an infinite loop if the input data contains the substring $ s_{2} $ , and the third requires too much memory if the input data contains the substring $ s_{3} $ . Bob wants these solutions to fail single test. What is the minimal length of test, which couldn't be passed by all three Bob's solutions?

## 输入格式

There are exactly 3 lines in the input data. The $ i $ -th line contains string $ s_{i} $ . All the strings are non-empty, consists of lowercase Latin letters, the length of each string doesn't exceed $ 10^{5} $ .

## 输出格式

Output one number — what is minimal length of the string, containing $ s_{1} $ , $ s_{2} $ and $ s_{3} $ as substrings.

## 输入输出样例 #1

### 输入 #1

```
ab
bc
cd
```

### 输出 #1

```
4
```

## 输入输出样例 #2

### 输入 #2

```
abacaba
abaaba
x
```

### 输出 #2

```
11
```
