---
title: "二分与双指针入门题单"
description: "围绕单调性、左右指针、滑动窗口、前缀和与差分，训练把线性枚举优化为线性或对数复杂度。"
order: 45
---

# 二分与双指针入门题单

二分的核心不是“写一个 while”，而是找到答案或判定条件的单调性；双指针的核心也不是两个变量，而是确认指针为什么不会回退。

## 一、二分查找基础

先区分“找任意满足位置”和“找第一个满足位置”，并统一处理不存在、重复值和边界答案。

- [ ] [[problem: luogu,P2249]] · [P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)
- [ ] [[problem: luogu,P1102]] · [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
- [ ] [[problem: luogu,P1678]] · [P1678 烦恼的高考志愿](https://www.luogu.com.cn/problem/P1678)
- [ ] [[problem: codeforces,279B]] · [Codeforces 279B Books](https://codeforces.com/problemset/problem/279/B)

## 二、二分答案

答案越大（或越小）越容易满足时，可以二分答案，并把所有复杂度集中到 `check` 函数中。

- [ ] [[problem: luogu,P1182]] · [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
- [ ] [[problem: luogu,P2678]] · [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
- [ ] [[problem: luogu,P2440]] · [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)
- [ ] [[problem: luogu,P1873]] · [P1873 砍树](https://www.luogu.com.cn/problem/P1873)
- [ ] [[problem: luogu,P1083]] · [P1083 借教室](https://www.luogu.com.cn/problem/P1083)
- [ ] [[problem: codeforces,1201C]] · [Codeforces 1201C Maximum Median](https://codeforces.com/problemset/problem/1201/C)

## 三、双指针与滑动窗口

排序后左右夹逼、或维护一个满足条件的连续窗口，是双指针最常见的两种形态。要写出窗口右端增加后左端为什么只需右移。

- [ ] [[problem: luogu,P1638]] · [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)
- [ ] [[problem: luogu,P3143]] · [P3143 Diamond Collector S](https://www.luogu.com.cn/problem/P3143)
- [ ] [[problem: luogu,P1094]] · [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [ ] [[problem: atcoder,ABC032C]] · [AtCoder ABC032 C 列](https://atcoder.jp/contests/abc032/tasks/abc032_c)

## 四、前缀和、差分与离散化配套

这些技巧经常和二分、双指针一起出现：先把区间信息压缩成前缀量，再用一次扫描或判定完成优化。

- [ ] [[problem: luogu,P1115]] · [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [ ] [[problem: luogu,P3397]] · [P3397 地毯](https://www.luogu.com.cn/problem/P3397)
- [ ] [[problem: luogu,P2367]] · [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)
- [ ] [[problem: luogu,P2004]] · [P2004 领地选择](https://www.luogu.com.cn/problem/P2004)
- [ ] [[problem: luogu,P2882]] · [P2882 Face The Right Way G](https://www.luogu.com.cn/problem/P2882)

## 复盘要求

```text
判定条件是什么：
它为什么具有单调性：
双指针移动后，哪些状态不可能再回到答案：
前缀量或差分量分别表示什么：
```
