# P1217 [USACO1.5] 回文质数 Prime Palindromes
## 题目描述

The number $151$ is a prime palindrome because it is both a prime number and a palindrome. It is the same number when read forward as backward. Write a program that finds all prime palindromes in the range of two supplied numbers $a$ and $b$ ($5 \le a < b \le 100000000$). Both $a$ and $b$ are considered to be within the range.

## 输入格式

- Line 1: Two integers, $a$ and $b$.

## 输出格式

The list of palindromic primes in numerical order, one per line.

## 输入输出样例 #1

### 输入 #1

```
5 500
```

### 输出 #1

```
5
7
11
101
131
151
181
191
313
353
373
383
```

## 说明/提示

### HINTS (use them carefully!)

:::info[Hint 1]
Generate the palindromes and see if they are prime. 
:::

:::info[Hint 2]
Generate palindromes by combining digits properly. You might need more than one of the loops like below.
```
/* generate five digit palindrome: */
for (d1 = 1; d1 <= 9; d1+=2) {	/* only odd; evens aren't so prime */
    for (d2 = 0; d2 <= 9; d2++) {
        for (d3 = 0; d3 <= 9; d3++) {
            palindrome = 10000*d1 + 1000*d2 + 100*d3 + 10*d2 + d1;
            /* ... deal with palindrome ... */
        }
    }
}
```
:::

USACO Training Section 1.5
