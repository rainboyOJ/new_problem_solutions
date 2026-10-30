---
title: "洛谷-试炼场：省选斗兽场/NOI 神殿"
description: "原题单作者 @CLCK 编排的省选及以上训练参考，覆盖优化、动态规划、网络流、图论与高级数据结构。虚树、2-SAT、后缀自动机、可并堆、回文自动机五个专题为后续补充。"
order: 170
---

# 洛谷-试炼场：省选斗兽场/NOI 神殿

原题单作者：@CLCK。转载或引用请注明作者。

[上一章：提高历练地](/problem-sets/luogu-trial-ground-advanced)

面向省选及以上选手的训练参考。省选水平的 OIer 通常已能自行组织训练，本章仅供参考。

[[toc]]

## 基础优化、动态规划与网络流

### 省选基础：读入/输出优化

读入与输出优化是省选刷题的必要技能。本组需要自行实现相应的处理。

- [ ] [[problem: luogu,P1580]]
- [ ] [[problem: luogu,P2393]]
- [ ] [[problem: luogu,P2394]]

### 省选基础：位运算

位运算常能优化常数、空间或时间，有时能多通过一些数据点。

- [ ] [[problem: luogu,P2114]]
- [ ] [[problem: luogu,P2396]]
- [ ] [[problem: luogu,P2397]]

### 省选基础：打表

打表通常不是正解，但能帮助取得会超时或超空间部分的数据点。

- [ ] [[problem: luogu,P1149]]
- [ ] [[problem: luogu,P1463]]
- [ ] [[problem: luogu,P1896]]

### 动态规划 1

- [ ] [[problem: luogu,P2051]]
- [ ] [[problem: luogu,P1879]]
- [ ] [[problem: luogu,P1850]]
- [ ] [[problem: luogu,P2831]]
- [ ] [[problem: luogu,P1131]]
- [ ] [[problem: luogu,P1169]]

### 动态规划 2

- [ ] [[problem: luogu,P1273]]
- [ ] [[problem: luogu,P3648]]
- [ ] [[problem: luogu,P2519]]
- [ ] [[problem: luogu,P2515]]
- [ ] [[problem: luogu,P3233]]
- [ ] [[problem: luogu,P2501]]

### 网络流：最大流

- [ ] [[problem: luogu,P2765]]
- [ ] [[problem: luogu,P2764]]
- [ ] [[problem: luogu,P2763]]
- [ ] [[problem: luogu,P2766]]
- [ ] [[problem: luogu,P2774]]
- [ ] [[problem: luogu,P2805]]

### 网络流：费用流

- [ ] [[problem: luogu,P2153]]
- [ ] [[problem: luogu,P2053]]
- [ ] [[problem: luogu,P3159]]
- [ ] [[problem: luogu,P2604]]
- [ ] [[problem: luogu,P2050]]
- [ ] [[problem: luogu,P3980]]

### 单调队列

- [ ] [[problem: luogu,P2698]]
- [ ] [[problem: luogu,P2216]]
- [ ] [[problem: luogu,P2219]]
- [ ] [[problem: luogu,P2564]]
- [ ] [[problem: luogu,P2569]]

### 概率期望

- [ ] [[problem: luogu,P2473]]
- [ ] [[problem: luogu,P2221]]
- [ ] [[problem: luogu,P3317]]
- [ ] [[problem: luogu,P3343]]
- [ ] [[problem: luogu,P3600]]
- [ ] [[problem: luogu,P3830]]

### 二分图

- [ ] [[problem: luogu,P3386]]
- [ ] [[problem: luogu,P1640]]
- [ ] [[problem: luogu,P1129]]
- [ ] [[problem: luogu,P1963]]
- [ ] [[problem: luogu,P3231]]
- [ ] [[problem: luogu,P2526]]

## 分治、字符串与树结构

### 点分治

- [ ] [[problem: luogu,P2634]]
- [ ] [[problem: luogu,P2664]]
- [ ] [[problem: luogu,P3806]]
- [ ] [[problem: luogu,P3676]]

### 虚树

虚树把一棵大树按「关键点 + 它们两两的 LCA」压缩成 O(k) 个节点的小树，让每次询问都能在 O(k log k) 而不是 O(n) 内完成。省选里凡是「每次询问给定一个点集，要求在树上做统计」的题，第一反应就该是虚树。

- [ ] [[problem: luogu,P2495]] · 【模板】虚树 / 消耗战
- [ ] [[problem: luogu,P3233]] · [HNOI2014] 世界树
- [ ] [[problem: luogu,P4103]] · [HEOI2014] 大工程
- [ ] [[problem: luogu,P4606]] · [SDOI2018] 战略游戏
- [ ] [[problem: luogu,P5327]] · [ZJOI2019] 语言

### 2-SAT

省选的高频送分题。识别信号是「每个对象只有两种选择，且选择之间有强制约束」，建图后跑 Tarjan 求 SCC 即可。近年省选几乎每年都有一道。

- [ ] [[problem: luogu,P4782]] · 【模板】2-SAT
- [ ] [[problem: luogu,P4171]] · [JSOI2010] 满汉全席
- [ ] [[problem: luogu,P3007]] · [USACO11JAN] The Continental Cowngress G
- [ ] [[problem: luogu,P3825]] · [NOI2017] 游戏（2-SAT + 小范围枚举）
- [ ] [[problem: luogu,P6378]] · [PA 2010] Riddle

### 后缀自动机

后缀数组的强对手。SAM 的优势在于能在线构造、能维护 endpos 集合、能配合线段树合并处理多串问题。省选字符串难题基本绕不开它。

- [ ] [[problem: luogu,P3804]] · 【模板】后缀自动机（SAM）
- [ ] [[problem: luogu,P2408]] · 不同子串个数
- [ ] [[problem: luogu,P3975]] · [TJOI2015] 弦论
- [ ] [[problem: luogu,P4070]] · [SDOI2016] 生成魔咒
- [ ] [[problem: luogu,P4248]] · [AHOI2013] 差异
- [ ] [[problem: luogu,P2178]] · [NOI2015] 品酒大会

### 后缀数组

- [ ] [[problem: luogu,P3809]]
- [ ] [[problem: luogu,P1117]]
- [ ] [[problem: luogu,P2178]]
- [ ] [[problem: luogu,P2463]]
- [ ] [[problem: luogu,P2336]]

### 主席树

- [ ] [[problem: luogu,P2468]]
- [ ] [[problem: luogu,P3157]]
- [ ] [[problem: luogu,P3302]]
- [ ] [[problem: luogu,P3168]]
- [ ] [[problem: luogu,P3313]]

### 数位 DP

- [ ] [[problem: luogu,P2602]]
- [ ] [[problem: luogu,P3281]]
- [ ] [[problem: luogu,P2518]]
- [ ] [[problem: luogu,P2606]]

### AC 自动机

- [ ] [[problem: luogu,P3808]]
- [ ] [[problem: luogu,P3796]]
- [ ] [[problem: luogu,P2444]]
- [ ] [[problem: luogu,P2414]]

### 平衡树

- [ ] [[problem: luogu,P2042]]
- [ ] [[problem: luogu,P2596]]
- [ ] [[problem: luogu,P1110]]
- [ ] [[problem: luogu,P3285]]
- [ ] [[problem: luogu,P3644]]
- [ ] [[problem: luogu,P3765]]
- [ ] [[problem: luogu,P3369]]

### 树链剖分

- [ ] [[problem: luogu,P2590]]
- [ ] [[problem: luogu,P2486]]
- [ ] [[problem: luogu,P2146]]
- [ ] [[problem: luogu,P3258]]
- [ ] [[problem: luogu,P3178]]

### 动态树

- [ ] [[problem: luogu,P3690]]
- [ ] [[problem: luogu,P2387]]
- [ ] [[problem: luogu,P3203]]
- [ ] [[problem: luogu,P3348]]

### 可并堆 / 左偏树

树上合并问题的主力工具。凡是「每个节点维护一个堆，需要把儿子的堆合并到父节点」的题（树上贪心、树上第 k 大），可并堆都是标准解法。

- [ ] [[problem: luogu,P3377]] · 【模板】可并堆 1
- [ ] [[problem: luogu,P2713]] · 罗马游戏
- [ ] [[problem: luogu,P1552]] · [APIO2012] 派遣
- [ ] [[problem: luogu,P3261]] · [JLOI2015] 城池攻占
- [ ] [[problem: luogu,P4331]] · [BalticOI 2004] Sequence (Day1)

### 回文自动机 / Manacher

Manacher 求最长回文子串是 O(n)，回文自动机（PAM）则能在 O(n) 内建出所有本质不同回文子串的结构。省选里出现「回文」二字的题，基本就是这两个工具之一。

- [ ] [[problem: luogu,P3805]] · 【模板】Manacher
- [ ] [[problem: luogu,P4555]] · [国家集训队] 最长双回文串
- [ ] [[problem: luogu,P1659]] · [国家集训队] 拉拉队排练
- [ ] [[problem: luogu,P4287]] · [SHOI2011] 双倍回文
- [ ] [[problem: luogu,P5496]] · 【模板】回文树 / 回文自动机（PAM）

### 树套树

- [ ] [[problem: luogu,P1903]]
- [ ] [[problem: luogu,P3157]]
- [ ] [[problem: luogu,P3332]]
- [ ] [[problem: luogu,P2166]]
- [ ] [[problem: luogu,P3380]]
- [ ] [[problem: luogu,P2137]]
- [ ] [[problem: luogu,P3759]]

## 高级数据结构与数论

### 可持久化 Trie 树

- [ ] [[problem: luogu,P2048]]
- [ ] [[problem: luogu,P3527]]
- [ ] [[problem: luogu,P3302]]
- [ ] [[problem: luogu,P3168]]
- [ ] [[problem: luogu,P3242]]
- [ ] [[problem: luogu,P3241]]
- [ ] [[problem: luogu,P3293]]

### 莫队算法

- [ ] [[problem: luogu,P1972]]
- [ ] [[problem: luogu,P2336]]
- [ ] [[problem: luogu,P3709]]
- [ ] [[problem: luogu,P2709]]
- [ ] [[problem: luogu,P3674]]

### 分块

- [ ] [[problem: luogu,P1972]]
- [ ] [[problem: luogu,P3396]]
- [ ] [[problem: luogu,P1822]]
- [ ] [[problem: luogu,P2801]]
- [ ] [[problem: luogu,P3203]]

### 莫比乌斯反演

- [ ] [[problem: luogu,P3768]]
- [ ] [[problem: luogu,P3172]]
- [ ] [[problem: luogu,P3455]]
- [ ] [[problem: luogu,P2522]]
- [ ] [[problem: luogu,P3327]]

### 其他

- [ ] [[problem: luogu,P3377]]
- [ ] [[problem: luogu,P3261]]
- [ ] [[problem: luogu,P3382]]
- [ ] [[problem: luogu,P2571]]
- [ ] [[problem: luogu,P3222]]
- [ ] [[problem: luogu,P3187]]
- [ ] [[problem: luogu,P3199]]
- [ ] [[problem: luogu,P3292]]
- [ ] [[problem: luogu,P2824]]
- [ ] [[problem: luogu,P3285]]
- [ ] [[problem: luogu,P1552]]
