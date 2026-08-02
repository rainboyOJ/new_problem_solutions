# 25E Test

- Time limit: 2 seconds
- Memory limit: 256 megabytes

## 题目描述

Sometimes it is hard to prepare tests for programming problems. Now Bob is preparing tests to new problem about strings — input data to his problem is one string. Bob has 3 wrong solutions to this problem. The first gives the wrong answer if the input data contains the substring *s*<sub>1</sub>, the second enters an infinite loop if the input data contains the substring *s*<sub>2</sub>, and the third requires too much memory if the input data contains the substring *s*<sub>3</sub>. Bob wants these solutions to fail single test. What is the minimal length of test, which couldn't be passed by all three Bob's solutions?

## 输入格式

There are exactly 3 lines in the input data. The *i*-th line contains string *s*<sub>*i*</sub>. All the strings are non-empty, consists of lowercase Latin letters, the length of each string doesn't exceed 10<sup>5</sup>.

## 输出格式

Output one number — what is minimal length of the string, containing *s*<sub>1</sub>, *s*<sub>2</sub> and *s*<sub>3</sub> as substrings.

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
