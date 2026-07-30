---
title: "背包入门题单"
description: "根据洛谷“疯狂的背包问题”题单整理，从 0/1、完全、多重背包模板逐步练习复合模型、方案恢复与综合应用。"
order: 65
source: "https://www.luogu.com.cn/training/964658#problems"
---

# 背包入门题单

[洛谷原题单](https://www.luogu.com.cn/training/964658#problems)

这份题单先用 19 道模板题对比不同背包模型，再按原题单顺序完成 31 道应用题。学习时重点记录状态含义、容量枚举方向、初值和答案落点，而不是只背转移式。

## 一、基础模型模板

先掌握三种基本物品限制，以及“求最优值、判断可行、统计方案”三类常见目标。

### 0/1 背包

- [ ] [[problem: luogu,U661986]] · [U661986 疯狂的背包问题(1) - 01背包问题](https://www.luogu.com.cn/problem/U661986)
- [ ] [[problem: luogu,U663295]] · [U663295 疯狂的背包问题(2) - 01背包问题（可行性问题）](https://www.luogu.com.cn/problem/U663295)
- [ ] [[problem: luogu,U663298]] · [U663298 疯狂的背包问题(3) - 01背包问题（计数组合问题）](https://www.luogu.com.cn/problem/U663298)

### 完全背包

- [ ] [[problem: luogu,U661988]] · [U661988 疯狂的背包问题(4) - 完全背包问题](https://www.luogu.com.cn/problem/U661988)
- [ ] [[problem: luogu,U663703]] · [U663703 疯狂的背包问题(5) - 完全背包问题（可行性问题）](https://www.luogu.com.cn/problem/U663703)
- [ ] [[problem: luogu,U663710]] · [U663710 疯狂的背包问题(6) - 完全背包问题（计数组合问题）](https://www.luogu.com.cn/problem/U663710)
- [ ] [[problem: luogu,U663733]] · [U663733 疯狂的背包问题(7) - 完全背包问题（计数排列问题）](https://www.luogu.com.cn/problem/U663733)

### 多重背包

- [ ] [[problem: luogu,U661992]] · [U661992 疯狂的背包问题(8) - 多重背包问题 I](https://www.luogu.com.cn/problem/U661992)
- [ ] [[problem: luogu,U663791]] · [U663791 疯狂的背包问题(9) - 多重背包问题 II](https://www.luogu.com.cn/problem/U663791)
- [ ] [[problem: luogu,U663797]] · [U663797 疯狂的背包问题(10) - 多重背包问题 III](https://www.luogu.com.cn/problem/U663797)

## 二、复合模型模板

在基本模型上增加物品类型、费用维度、分组或依赖关系，练习先辨认限制再选择转移方式。

- [ ] [[problem: luogu,U661993]] · [U661993 疯狂的背包问题(11) - 混合背包问题](https://www.luogu.com.cn/problem/U661993)
- [ ] [[problem: luogu,U661994]] · [U661994 疯狂的背包问题(12) - 二维费用问题](https://www.luogu.com.cn/problem/U661994)
- [ ] [[problem: luogu,U661995]] · [U661995 疯狂的背包问题(13) - 分组背包](https://www.luogu.com.cn/problem/U661995)
- [ ] [[problem: luogu,U661996]] · [U661996 疯狂的背包问题(14) - 有依赖的背包问题](https://www.luogu.com.cn/problem/U661996)
- [ ] [[problem: luogu,U662012]] · [U662012 疯狂的背包问题(15) - 泛化物品背包问题](https://www.luogu.com.cn/problem/U662012)

## 三、方案恢复与最优方案计数

这一组不再只求最优值，还要恢复方案或统计最优方案，注意区分不可达状态与值为零的合法状态。

- [ ] [[problem: luogu,U662015]] · [U662015 疯狂的背包问题(16) - 输出字典序最小的最优方案](https://www.luogu.com.cn/problem/U662015)
- [ ] [[problem: luogu,U662039]] · [U662039 疯狂的背包问题(17) - 求所有最优方案](https://www.luogu.com.cn/problem/U662039)
- [ ] [[problem: luogu,U662097]] · [U662097 疯狂的背包问题(18) - 求最优方案总数](https://www.luogu.com.cn/problem/U662097)
- [ ] [[problem: luogu,U662107]] · [U662107 疯狂的背包问题(19) - 求恰好装满的最优方案数](https://www.luogu.com.cn/problem/U662107)

## 四、经典模型练习

以下练习保持洛谷原题单顺序。先把 0/1、完全背包和“恰好装满”状态练熟。

- [ ] [[problem: luogu,P1048]] · [P1048 \[NOIP 2005 普及组\] 采药](https://www.luogu.com.cn/problem/P1048)
- [ ] [[problem: luogu,P1616]] · [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)
- [ ] [[problem: luogu,P1049]] · [P1049 \[NOIP 2001 普及组\] 装箱问题](https://www.luogu.com.cn/problem/P1049)
- [ ] [[problem: luogu,P2842]] · [P2842 纸币问题 1](https://www.luogu.com.cn/problem/P2842)
- [ ] [[problem: luogu,P2840]] · [P2840 纸币问题 2](https://www.luogu.com.cn/problem/P2840)
- [ ] [[problem: luogu,P2834]] · [P2834 纸币问题 3](https://www.luogu.com.cn/problem/P2834)
- [ ] [[problem: luogu,P1802]] · [P1802 5 倍经验日](https://www.luogu.com.cn/problem/P1802)
- [ ] [[problem: luogu,P1164]] · [P1164 小 A 点菜](https://www.luogu.com.cn/problem/P1164)

## 五、状态设计与模型变形

这一组把背包状态用于可行性、计数、二维费用、分组和数论对象，重点练习从题意识别“物品、容量、选择限制”。

- [ ] [[problem: luogu,P8742]] · [P8742 \[蓝桥杯 2021 省 AB\] 砝码称重](https://www.luogu.com.cn/problem/P8742)
- [ ] [[problem: luogu,P1734]] · [P1734 最大约数和](https://www.luogu.com.cn/problem/P1734)
- [ ] [[problem: luogu,P2925]] · [P2925 \[USACO08DEC\] Hay For Sale S](https://www.luogu.com.cn/problem/P2925)
- [ ] [[problem: luogu,P1507]] · [P1507 NASA的食物计划](https://www.luogu.com.cn/problem/P1507)
- [ ] [[problem: luogu,P1877]] · [P1877 \[HAOI2012\] 音量调节](https://www.luogu.com.cn/problem/P1877)
- [ ] [[problem: luogu,P2347]] · [P2347 \[NOIP 1996 提高组\] 砝码称重](https://www.luogu.com.cn/problem/P2347)
- [ ] [[problem: luogu,P1757]] · [P1757 通天之分组背包](https://www.luogu.com.cn/problem/P1757)
- [ ] [[problem: luogu,P1679]] · [P1679 神奇的四次方数](https://www.luogu.com.cn/problem/P1679)
- [ ] [[problem: luogu,P1832]] · [P1832 A+B Problem（再升级）](https://www.luogu.com.cn/problem/P1832)
- [ ] [[problem: luogu,P1855]] · [P1855 榨取kkksc03](https://www.luogu.com.cn/problem/P1855)

## 六、综合应用与优化

最后一组综合方案计数、状态反推、依赖关系和多重背包优化。遇到陌生题面时，先尝试把状态写成“处理前若干物品、容量为某值时的答案”。

- [ ] [[problem: luogu,B4141]] · [B4141 \[信息与未来 2016\] 素数分解](https://www.luogu.com.cn/problem/B4141)
- [ ] [[problem: luogu,P1060]] · [P1060 \[NOIP 2006 普及组\] 开心的金明](https://www.luogu.com.cn/problem/P1060)
- [ ] [[problem: luogu,P1510]] · [P1510 精卫填海](https://www.luogu.com.cn/problem/P1510)
- [ ] [[problem: luogu,P1466]] · [P1466 \[USACO2.2\] 集合 Subset Sums](https://www.luogu.com.cn/problem/P1466)
- [ ] [[problem: luogu,P2370]] · [P2370 yyy2015c01 的 U 盘](https://www.luogu.com.cn/problem/P2370)
- [ ] [[problem: luogu,P4141]] · [P4141 消失之物](https://www.luogu.com.cn/problem/P4141)
- [ ] [[problem: luogu,P1156]] · [P1156 \[USACO01OPEN\] 垃圾陷阱](https://www.luogu.com.cn/problem/P1156)
- [ ] [[problem: luogu,P1509]] · [P1509 找啊找啊找朋友](https://www.luogu.com.cn/problem/P1509)
- [ ] [[problem: luogu,P6771]] · [P6771 \[USACO05MAR\] Space Elevator 太空电梯](https://www.luogu.com.cn/problem/P6771)
- [ ] [[problem: luogu,P5365]] · [P5365 \[SNOI2017\] 英雄联盟](https://www.luogu.com.cn/problem/P5365)
- [ ] [[problem: luogu,P1833]] · [P1833 樱花](https://www.luogu.com.cn/problem/P1833)
- [ ] [[problem: luogu,P1064]] · [P1064 \[NOIP 2006 提高组\] 金明的预算方案](https://www.luogu.com.cn/problem/P1064)
- [ ] [[problem: luogu,P1776]] · [P1776 宝物筛选](https://www.luogu.com.cn/problem/P1776)

## 复盘要求

每完成一道题，至少记录下面四项：

```text
物品和容量分别是什么：
每件物品能选几次：
状态定义与初始化：
容量为什么正序或倒序枚举：
```

当题目要求可行性、方案数、恰好装满或输出方案时，再单独写清楚状态值的语义，避免沿用“最大价值”模板造成初始化错误。
