# 1278 Find and Replace

## 赛事信息

USACO 2023 January Contest, Silver

## 题目描述

Bessie is using the latest and greatest innovation in text-editing software,
miV! She starts with an input string consisting solely of upper and lowercase
English letters and wishes to transform it into some output string. With just
one keystroke, miV allows her to replace all occurrences of one English letter
$c_1$ in the string with another English letter $c_2$. For example, given the
string $\texttt{aAbBa}$, if Bessie selects $c_1$ as 'a' and $c_2$ as 'B', the given string transforms into
$\texttt{BAbBB}$.
Bessie is a busy cow, so for each of $T$ ($1\le T\le 10$) independent test
cases, output the minimum number of keystrokes required to transform her input
string into her desired output string.

## 输入格式

The first line contains $T$, the number of independent test cases.
The following $T$ pairs of lines contain an input and output string of equal
length. All characters are upper or lowercase English letters (either A through
Z or a through z). The sum of the lengths of all strings does not exceed $10^5$.

## 输出格式

For each test case, output the minimum number of keystrokes required to change
the input string into the output string, or $-1$ if it is impossible to do so.

## 输入输出样例 #1

### 输入 #1

```
4
abc
abc
BBC
ABC
abc
bbc
ABCD
BACD
```

### 输出 #1

```
0
-1
1
3
```

## 样例说明

The first input string is the same as its output string, so no keystrokes are
required.
The second input string cannot be changed into its output string because Bessie
cannot change one '$\texttt{B}$' to '$\texttt{A}$' while keeping the other as
'$\texttt{B}$'.
The third input string can be changed into its output string by changing
'$\texttt{a}$' to '$\texttt{b}$'.
The last input string can be changed into its output string like so:
$\texttt{ABCD} \rightarrow \texttt{EBCD} \rightarrow \texttt{EACD} \rightarrow \texttt{BACD}$.

## 测试点性质

- Inputs 2-6: Every string has a length at most $50$.
- Inputs 7-9: All strings consist only of lowercase letters '$\texttt{a}$' through '$\texttt{e}$'
- Inputs 10-15: No additional constraints.
