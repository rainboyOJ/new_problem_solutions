# 510C Fox And Names

- Time limit: 2 seconds
- Memory limit: 256 megabytes

## 题目描述

Fox Ciel is going to publish a paper on FOCS (Foxes Operated Computer Systems, pronounce: "Fox"). She heard a rumor: the authors list on the paper is always sorted in the lexicographical order.

After checking some examples, she found out that sometimes it wasn't true. On some papers authors' names weren't sorted in lexicographical order in normal sense. But it was always true that after some modification of the order of letters in alphabet, the order of authors becomes lexicographical!

She wants to know, if there exists an order of letters in Latin alphabet such that the names on the paper she is submitting are following in the lexicographical order. If so, you should find out any such order.

Lexicographical order is defined in following way. When we compare *s* and *t*, first we find the leftmost position with differing characters: *s*<sub>*i*</sub> ≠ *t*<sub>*i*</sub>. If there is no such position (i. e. *s* is a prefix of *t* or vice versa) the shortest string is less. Otherwise, we compare characters *s*<sub>*i*</sub> and *t*<sub>*i*</sub> according to their order in alphabet.

## 输入格式

The first line contains an integer *n* (1 ≤ *n* ≤ 100): number of names.

Each of the following *n* lines contain one string *name*<sub>*i*</sub> (1 ≤ |*name*<sub>*i*</sub>| ≤ 100), the *i*-th name. Each name contains only lowercase Latin letters. All names are different.

## 输出格式

If there exists such order of letters that the given names are sorted lexicographically, output any such order as a permutation of characters 'a'–'z' (i. e. first output the first letter of the modified alphabet, then the second, and so on).

Otherwise output a single word "Impossible" (without quotes).

## 输入输出样例 #1

### 输入 #1

```
3
rivest
shamir
adleman
```

### 输出 #1

```
bcdefghijklmnopqrsatuvwxyz
```
