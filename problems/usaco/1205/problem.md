# 1205 Blocks

## 赛事信息

USACO 2022 February Contest, Bronze

## 题目描述

为了提高她的词汇量，奶牛 Bessie 拿来了一套共四块积木，每块积木都是一个正方体，六面各写着一个字母。她正在将积木排成一排，使积木顶部的字母拼出单词，以此来学习拼写。
给定 Bessie 四块积木上的字母，以及她想要拼写的单词列表，请判断她可以使用积木成功拼写列表中的哪些单词。

## 输入格式

输入的第一行包含 $N$（$1\le N\le 10$），为 Bessie 想要拼写的单词数。以下四行，每行包含一个包含六个大写字母的字符串，表示 Bessie 的一块积木六面上的字母。以下 $N$ 行包含 Bessie 想要拼写的 $N$ 个单词。每一个均由 1 到 4 个大写字母组成。

## 输出格式

对于 Bessie 的列表中的每一个单词，如果她可以拼写这个单词则输出 YES，否则输出 NO。

## 输入输出样例 #1

### 输入 #1

```
6
MOOOOO
OOOOOO
ABCDEF
UVWXYZ
COW
MOO
ZOO
MOVE
CODE
FARM
```

### 输出 #1

```
YES
NO
YES
YES
NO
NO
```

## 样例说明

在这个例子中，Bessie 可以拼写 COW，ZOO 和 MOVE。令人难过地，她无法拼出 MOO，因为唯一包含 M 的积木不能同时用于 O。她无法拼出 FARM，因为没有包含字母 R 的积木。她无法拼出 CODE，因为 C，D 和 E 属于同一块积木。
供题：Brian Dean
