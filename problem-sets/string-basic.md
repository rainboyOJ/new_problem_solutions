---
title: "字符串基础题单"
description: "从字符与单词处理、回文和自定义排序开始，逐步过渡到字符串哈希、Trie、KMP 和 Manacher。"
order: 56
---

# 字符串基础题单

字符串入门先解决“如何表示和扫描字符串”，再学习“如何快速判断两个字符串的关系”。不要在还没有掌握下标、切片和边界处理时直接背 KMP 模板。

## 一、字符与单词处理

重点是字符分类、大小写、空格、单词边界和字符串长度。先把输入处理写稳定。

- [ ] [[problem: luogu,P5015]] · [P5015 标题统计](https://www.luogu.com.cn/problem/P5015)
- [ ] [[problem: luogu,P1308]] · [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
- [ ] [[problem: luogu,P1125]] · [P1125 笨小猴](https://www.luogu.com.cn/problem/P1125)
- [ ] [[problem: luogu,P5734]] · [P5734 【深基6.例6】文字处理软件](https://www.luogu.com.cn/problem/P5734)
- [ ] [[problem: luogu,P1914]] · [P1914 小书童——密码](https://www.luogu.com.cn/problem/P1914)
- [ ] [[problem: luogu,P1055]] · [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [ ] [[problem: luogu,P1957]] · [P1957 口算练习题](https://www.luogu.com.cn/problem/P1957)

## 二、回文、括号与字符串构造

这一组练习双指针、栈和字符串比较。注意区分“修改字符串”和“只判断是否满足条件”。

- [ ] [[problem: luogu,P1241]] · [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)
- [ ] [[problem: luogu,P1071]] · [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)
- [ ] [[problem: luogu,P1012]] · [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
- [ ] [[problem: luogu,P3370]] · [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)

## 三、Trie 与字符串集合

当题目反复询问“某个前缀是否出现”或“某个单词是否存在”时，Trie 比逐个字符串比较更自然。先做应用题，再看模板。

- [ ] [[problem: hdu,1251]] · [HDU 1251 统计难题](https://acm.hdu.edu.cn/showproblem.php?pid=1251)
- [ ] [[problem: luogu,P2580]] · [P2580 于是他错误的点名开始了](https://www.luogu.com.cn/problem/P2580)
- [ ] [[problem: luogu,P8306]] · [P8306 【模板】字典树](https://www.luogu.com.cn/problem/P8306)

## 四、KMP 作为算法桥接

KMP 不必作为第一节，但它是从“暴力匹配”走向“利用已知匹配信息”的第一道字符串算法题。

- [ ] [[problem: hdu,2087]] · [HDU 2087 剪花布条](https://acm.hdu.edu.cn/showproblem.php?pid=2087)
- [ ] [[problem: hdu,1711]] · [HDU 1711 Number Sequence](https://acm.hdu.edu.cn/showproblem.php?pid=1711)
- [ ] [[problem: luogu,P3375]] · [P3375 【模板】KMP](https://www.luogu.com.cn/problem/P3375)

## 五、回文串与 Manacher

Manacher 把每个位置作为回文中心统一处理，在 `O(n)` 时间内求出所有奇回文和偶回文的半径。先掌握半径数组的含义，再做需要统计或拼接两个回文串的应用题。

- [ ] [[problem: luogu,P3805]] · [P3805 【模板】manacher](https://www.luogu.com.cn/problem/P3805)
- [ ] [[problem: hdu,3068]] · [HDU 3068 最长回文](https://acm.hdu.edu.cn/showproblem.php?pid=3068)
- [ ] [[problem: luogu,P4555]] · [P4555 最长双回文串](https://www.luogu.com.cn/problem/P4555)

## 暂不放入入门题单

AC 自动机、后缀数组、后缀自动机和复杂字符串哈希应另建进阶题单。它们需要更稳定的前缀函数、Trie、哈希和复杂度基础。
