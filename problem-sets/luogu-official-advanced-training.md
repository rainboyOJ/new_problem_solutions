---
title: "洛谷官方深入浅出进阶篇题单"
description: "按洛谷官方深入浅出进阶篇训练题单整理的完整练习路径。"
order: 130
source: "https://www.luogu.com.cn/training/list?type=srqc-jj"
---

# 洛谷官方深入浅出进阶篇题单

[洛谷官方题单列表](https://www.luogu.com.cn/training/list?type=srqc-jj)

本题单共收录 **22** 个官方子题单、**368** 个题目条目、**357** 道不同题目。

其中有 **9** 道题出现在多个学习阶段，形成 **11** 个重复条目。这些条目按洛谷官方分组原样保留，并共享完成进度。

[[toc]]

## 怎么看小节里的图

每个小节开头有几张 `flowchart TD` 有向图，画的是**本节题目之间的做题先后关系**。

- 节点写「题号 + 简短标题」，就是本节题单里列的那几道题。
- 箭头 `A → B` 表示**硬前置**：B 会用到 A 建立起来的套路，先把 A 做完再碰 B，能省掉大量原地打转。
- 题目多的小节按支线拆成几张图，每张图只画一条线。两张图之间还有依赖时，用图下面那句话说明，不跨图画箭头。
- **图里只画有前置关系的题。** 没有出现在任何图里的题，在每节末尾单独列出，它们不依赖本节任何题，可以随时插进来做。
- 图只画**节内**关系。跨小节的依赖（比如树状数组要先会前缀和）写在小节正文里。
- 同一道题出现在多个小节时，每节的图都把它完整画一次，因为它在不同小节的入边并不相同。
## 【算法2-1】前缀和、差分与离散化

[洛谷官方子题单](https://www.luogu.com.cn/training/200) · 18 题

**前缀和**

```mermaid
flowchart TD
  nP8218["P8218 求区间和"]
  nP2004["P2004 领地选择"]
  nP1719["P1719 最大加权矩形"]
  nP3017["P3017 Brownie Slicing"]
  nP1314["P1314 聪明的质监员"]

  nP8218 --> nP2004
  nP2004 --> nP1719
  nP2004 --> nP3017
  nP8218 --> nP1314
```

P8218 是模板，P2004 把它升到二维；P1719 是二维前缀和加枚举上下界，P3017 再多一步二分。P1314 也是前缀和加二分，但它还要先会下一张图的差分 P1083。

**差分**

```mermaid
flowchart TD
  nP2367["P2367 语文成绩"]
  nP3397["P3397 地毯"]
  nP3406["P3406 海底高铁"]
  nP4552["P4552 IncDec Sequence"]
  nP2882["P2882 Face The Right Way"]
  nP1083["P1083 借教室"]

  nP2367 --> nP3397
  nP2367 --> nP3406
  nP2367 --> nP4552
  nP2367 --> nP2882
  nP2367 --> nP1083
```

一维差分 P2367 之后分四路：二维差分 P3397、树上路径差分 P3406、构造题 P4552、翻转技巧 P2882。P1083 是「差分 + 二分」，它正是上一张图里 P1314 缺的那块前置。

**离散化**

```mermaid
flowchart TD
  nP1496["P1496 火烧赤壁"]
  nP3029["P3029 Cow Lineup"]
  nP1904["P1904 天际线"]
  nP1884["P1884 Overplanting"]
  nP1955["P1955 程序自动分析"]
  nP5937["P5937 Parity Game"]
  nP4375["P4375 Out of Sorts"]

  nP1496 --> nP3029
  nP1496 --> nP1904
  nP1904 --> nP1884
  nP1496 --> nP1955
  nP1955 --> nP5937
  nP1496 --> nP4375
```

P1496 是离散化与区间并的入门，之后分三路：扫描线（P1904 → P1884）、离散化加并查集（P1955 → P5937），以及只要排序离散的 P3029 与 P4375。

- [x] [[problem: luogu,P8218]] · [P8218 【深进1.例1】求区间和](https://www.luogu.com.cn/problem/P8218)
- [x] [[problem: luogu,P1719]] · [P1719 最大加权矩形](https://www.luogu.com.cn/problem/P1719)
- [x] [[problem: luogu,P1314]] · [P1314 \[NOIP 2011 提高组\] 聪明的质监员](https://www.luogu.com.cn/problem/P1314)
- [x] [[problem: luogu,P2367]] · [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)
- [x] [[problem: luogu,P3397]] · [P3397 地毯](https://www.luogu.com.cn/problem/P3397)
- [x] [[problem: luogu,P1496]] · [P1496 火烧赤壁](https://www.luogu.com.cn/problem/P1496)
- [x] [[problem: luogu,P1955]] · [P1955 \[NOI2015\] 程序自动分析](https://www.luogu.com.cn/problem/P1955)
- [x] [[problem: luogu,P1884]] · [P1884 \[USACO12FEB\] Overplanting S](https://www.luogu.com.cn/problem/P1884)
- [x] [[problem: luogu,P2004]] · [P2004 领地选择](https://www.luogu.com.cn/problem/P2004)
- [x] [[problem: luogu,P3017]] · [P3017 \[USACO11MAR\] Brownie Slicing G](https://www.luogu.com.cn/problem/P3017)
- [x] [[problem: luogu,P3406]] · [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)
- [x] [[problem: luogu,P1083]] · [P1083 \[NOIP 2012 提高组\] 借教室](https://www.luogu.com.cn/problem/P1083)
- [x] [[problem: luogu,P2882]] · [P2882 \[USACO07MAR\] Face The Right Way G](https://www.luogu.com.cn/problem/P2882)
- [x] [[problem: luogu,P4552]] · [P4552 \[Poetize6\] IncDec Sequence](https://www.luogu.com.cn/problem/P4552)
- [x] [[problem: luogu,P3029]] · [P3029 \[USACO11NOV\] Cow Lineup S](https://www.luogu.com.cn/problem/P3029)
- [x] [[problem: luogu,P1904]] · [P1904 天际线](https://www.luogu.com.cn/problem/P1904)
- [x] [[problem: luogu,P4375]] · [P4375 \[USACO18OPEN\] Out of Sorts G](https://www.luogu.com.cn/problem/P4375)
- [x] [[problem: luogu,P5937]] · [P5937 \[CEOI 1999\] Parity Game](https://www.luogu.com.cn/problem/P5937)

## 【算法2-2】常见优化技巧

[洛谷官方子题单](https://www.luogu.com.cn/training/201) · 20 题

**单调队列**

```mermaid
flowchart TD
  nP1886["P1886 滑动窗口"]
  nP2032["P2032 扫描"]
  nP2216["P2216 理想的正方形"]
  nP2880["P2880 Balanced Lineup"]
  nP1714["P1714 切蛋糕"]
  nP1725["P1725 琪露诺"]
  nP1115["P1115 最大子段和"]

  nP1886 --> nP2032
  nP1886 --> nP2216
  nP1886 --> nP2880
  nP1115 --> nP1714
  nP1886 --> nP1714
  nP1886 --> nP1725
```

P1886 是模板，之后分到滑动窗口 P2032、二维窗口 P2216、区间最值 P2880，以及两条「前缀和 / DP 加单调队列」的 P1714 和 P1725。

**单调栈与最大子矩形**

```mermaid
flowchart TD
  nP2866["P2866 Bad Hair Day"]
  nP3467["P3467 PLA-Postering"]
  nP4147["P4147 玉蟾宫"]
  nP1950["P1950 长方形"]
  nP1578["P1578 奶牛浴场"]

  nP2866 --> nP3467
  nP2866 --> nP4147
  nP4147 --> nP1950
  nP4147 --> nP1578
```

P2866 是单调栈入门，P4147 的悬线法把它变成「最大全 1 子矩形」，P1950 与 P1578 都是这条路的延伸。

**尺取与排序双指针**

```mermaid
flowchart TD
  nP1638["P1638 逛画展"]
  nUVA11572["UVA11572 唯一雪花"]
  nP4653["P4653 Sure Bet"]
  nP1102["P1102 A-B 数对"]
  nP3143["P3143 Diamond Collector"]

  nP1638 --> nUVA11572
  nP1638 --> nP4653
  nP1102 --> nP3143
```

P1638 是尺取模板，UVA11572 是同一个窗口但要求去重，P4653 要先排序再扫。P1102 用排序加双指针数对，P3143 是同类的两个维护窗口。

P7072（桶 / 堆）、P2671（数学计数）、P7910（插入排序性质）与上面三条支线都没有前置关系，可以随时插进来做。

- [x] [[problem: luogu,P1102]] · [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
- [x] [[problem: luogu,P1638]] · [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)
- [x] [[problem: luogu,P1115]] · [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [x] [[problem: luogu,P7072]] · [P7072 \[CSP-J 2020\] 直播获奖](https://www.luogu.com.cn/problem/P7072)
- [x] [[problem: luogu,P2671]] · [P2671 \[NOIP 2015 普及组\] 求和](https://www.luogu.com.cn/problem/P2671)
- [x] [[problem: luogu,P4147]] · [P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147)
- [x] [[problem: luogu,P2866]] · [P2866 \[USACO06NOV\] Bad Hair Day S](https://www.luogu.com.cn/problem/P2866)
- [x] [[problem: luogu,P1950]] · [P1950 长方形](https://www.luogu.com.cn/problem/P1950)
- [x] [[problem: luogu,P2032]] · [P2032 扫描](https://www.luogu.com.cn/problem/P2032)
- [x] [[problem: luogu,P2216]] · [P2216 \[HAOI2007\] 理想的正方形](https://www.luogu.com.cn/problem/P2216)
- [x] [[problem: luogu,UVA11572]] · [UVA11572 唯一的雪花 Unique Snowflakes](https://www.luogu.com.cn/problem/UVA11572)
- [x] [[problem: luogu,P4653]] · [P4653 \[CEOI 2017\] Sure Bet](https://www.luogu.com.cn/problem/P4653)
- [x] [[problem: luogu,P3143]] · [P3143 \[USACO16OPEN\] Diamond Collector S](https://www.luogu.com.cn/problem/P3143)
- [x] [[problem: luogu,P7910]] · [P7910 \[CSP-J 2021\] 插入排序](https://www.luogu.com.cn/problem/P7910)
- [x] [[problem: luogu,P1578]] · [P1578 \[WC2002\] 奶牛浴场](https://www.luogu.com.cn/problem/P1578)
- [x] [[problem: luogu,P3467]] · [P3467 \[POI 2008\] PLA-Postering](https://www.luogu.com.cn/problem/P3467)
- [x] [[problem: luogu,P1886]] · [P1886 【模板】单调队列 / 滑动窗口](https://www.luogu.com.cn/problem/P1886)
- [x] [[problem: luogu,P2880]] · [P2880 \[USACO07JAN\] Balanced Lineup G](https://www.luogu.com.cn/problem/P2880)
- [x] [[problem: luogu,P1714]] · [P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)
- [x] [[problem: luogu,P1725]] · [P1725 琪露诺](https://www.luogu.com.cn/problem/P1725)

## 【算法2-3】分治与倍增

[洛谷官方子题单](https://www.luogu.com.cn/training/202) · 18 题

**分治**

```mermaid
flowchart TD
  nP1177["P1177 排序"]
  nP1908["P1908 逆序对"]
  nP1966["P1966 火柴排队"]
  nP2345["P2345 MooFest"]
  nP1115["P1115 最大子段和"]
  nP1257["P1257 最近点对"]
  nP1228["P1228 地毯填补"]

  nP1177 --> nP1908
  nP1908 --> nP1966
  nP1908 --> nP2345
  nP1177 --> nP1115
  nP1177 --> nP1257
  nP1177 --> nP1228
```

P1177 的归并排序是总入口：P1908 用归并数逆序对，P1966 与 P2345 都在它之上；分治版最大子段 P1115、最近点对 P1257、棋盘覆盖 P1228 直接从 P1177 出发。

**倍增与快速幂**

```mermaid
flowchart TD
  nP2880["P2880 Balanced Lineup"]
  nP1816["P1816 忠诚"]
  nP7167["P7167 Fountain"]
  nP4155["P4155 国旗计划"]
  nP7562["P7562 Event Hopping"]
  nP6648["P6648 Triangle"]
  nP3509["P3509 ZAB-Frog"]
  nP3517["P3517 WYK-Plot"]
  nP1226["P1226 快速幂"]
  nP1045["P1045 麦森数"]

  nP2880 --> nP1816
  nP2880 --> nP7167
  nP2880 --> nP4155
  nP4155 --> nP7562
  nP2880 --> nP6648
  nP2880 --> nP3509
  nP2880 --> nP3517
  nP1226 --> nP1045
```

倍增一支统一从 ST 表 P2880 起步，其中 P4155 → P7562 是最硬的一段。P1226 的快速幂是同一思想的另一面，P1045 在它之上加高精度。

P2415 集合求和只用组合计数，与本节其他题没有前置关系。

- [x] [[problem: luogu,P1177]] · [P1177 【模板】排序](https://www.luogu.com.cn/problem/P1177)
- [x] [[problem: luogu,P1908]] · [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
- [x] [[problem: luogu,P1966]] · [P1966 \[NOIP 2013 提高组\] 火柴排队](https://www.luogu.com.cn/problem/P1966)
- [x] [[problem: luogu,P1226]] · [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)
- [x] [[problem: luogu,P1045]] · [P1045 \[NOIP 2003 普及组\] 麦森数](https://www.luogu.com.cn/problem/P1045)
- [x] [[problem: luogu,P1115]] · [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [x] [[problem: luogu,P2880]] · [P2880 \[USACO07JAN\] Balanced Lineup G](https://www.luogu.com.cn/problem/P2880)
- [x] [[problem: luogu,P7167]] · [P7167 \[eJOI 2020\] Fountain (Day1)](https://www.luogu.com.cn/problem/P7167)
- [x] [[problem: luogu,P2415]] · [P2415 集合求和](https://www.luogu.com.cn/problem/P2415)
- [x] [[problem: luogu,P1257]] · [P1257 平面上的最接近点对](https://www.luogu.com.cn/problem/P1257)
- [x] [[problem: luogu,P1228]] · [P1228 地毯填补问题](https://www.luogu.com.cn/problem/P1228)
- [x] [[problem: luogu,P2345]] · [P2345 \[USACO04OPEN\] MooFest G](https://www.luogu.com.cn/problem/P2345)
- [x] [[problem: luogu,P3509]] · [P3509 \[POI 2010\] ZAB-Frog](https://www.luogu.com.cn/problem/P3509)
- [x] [[problem: luogu,P3517]] · [P3517 \[POI 2011\] WYK-Plot](https://www.luogu.com.cn/problem/P3517)
- [x] [[problem: luogu,P4155]] · [P4155 \[SCOI2015\] 国旗计划](https://www.luogu.com.cn/problem/P4155)
- [x] [[problem: luogu,P1816]] · [P1816 忠诚](https://www.luogu.com.cn/problem/P1816)
- [x] [[problem: luogu,P6648]] · [P6648 \[CCC 2019\] Triangle: The Data Structure](https://www.luogu.com.cn/problem/P6648)
- [x] [[problem: luogu,P7562]] · [P7562 \[JOISC 2021\] イベント巡り 2 (Event Hopping 2) (Day4)](https://www.luogu.com.cn/problem/P7562)

## 【算法2-4】字符串

[洛谷官方子题单](https://www.luogu.com.cn/training/203) · 16 题

**KMP**

```mermaid
flowchart TD
  nP3375["P3375 KMP"]
  nP4391["P4391 Radio Transmission"]
  nP3435["P3435 OKR-Periods"]
  nP2375["P2375 动物园"]
  n25E["25E Test"]

  nP3375 --> nP4391
  nP3375 --> nP3435
  nP3435 --> nP2375
  nP3375 --> n25E
```

P3375 是唯一入口：P4391 直接用周期结论，P3435 要会失配树的遍历，P2375 再往上叠倍增，25E 用 KMP 判包含。

**Trie**

```mermaid
flowchart TD
  nP1481["P1481 魔族密码"]
  nP1470["P1470 最长前缀"]
  nP2580["P2580 点名"]
  nP2922["P2922 Secret Message"]
  nP3879["P3879 阅读理解"]

  nP1481 --> nP1470
  nP1481 --> nP2580
  nP2580 --> nP2922
  nP1481 --> nP3879
```

P1481 是 Trie 入门，之后分到「Trie 加 DP」的 P1470 和三个统计题：P2580 判存在、P2922 数前缀、P3879 数出现。

**01-Trie 与可持久化**

```mermaid
flowchart TD
  nP4551["P4551 最长异或路径"]
  nP6824["P6824 可乐"]
  nP4735["P4735 最大异或和"]
  nP5283["P5283 异或粽子"]
  nP4592["P4592 异或"]

  nP4551 --> nP6824
  nP4551 --> nP4735
  nP4735 --> nP5283
  nP4551 --> nP4592
  nP4735 --> nP4592
```

01-Trie 一支从 P4551 起（树上异或路径），P6824 是它的贪心应用；P4735 → P5283 是可持久化 01-Trie，P4592 要把它搬到树链剖分上。

P3369 普通平衡树与本节其他题没有前置关系，可以单独安排。

- [x] [[problem: luogu,P3375]] · [P3375 【模板】KMP](https://www.luogu.com.cn/problem/P3375)
- [x] [[problem: luogu,P4391]] · [P4391 \[BalticOI 2009\] Radio Transmission 无线传输](https://www.luogu.com.cn/problem/P4391)
- [x] [[problem: luogu,P1481]] · [P1481 魔族密码](https://www.luogu.com.cn/problem/P1481)
- [x] [[problem: luogu,P2580]] · [P2580 于是他错误的点名开始了](https://www.luogu.com.cn/problem/P2580)
- [x] [[problem: luogu,P4551]] · [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)
- [x] [[problem: luogu,P5283]] · [P5283 \[十二省联考 2019\] 异或粽子](https://www.luogu.com.cn/problem/P5283)
- [x] [[problem: luogu,P1470]] · [P1470 \[IOI 1996 / USACO2.3\] 最长前缀 Longest Prefix](https://www.luogu.com.cn/problem/P1470)
- [x] [[problem: codeforces,25E]] · [25E Test](https://codeforces.com/problemset/problem/25/E)
- [x] [[problem: luogu,P3435]] · [P3435 \[POI 2006\] OKR-Periods of Words](https://www.luogu.com.cn/problem/P3435)
- [x] [[problem: luogu,P2375]] · [P2375 \[NOI2014\] 动物园](https://www.luogu.com.cn/problem/P2375)
- [x] [[problem: luogu,P2922]] · [P2922 \[USACO08DEC\] Secret Message G](https://www.luogu.com.cn/problem/P2922)
- [x] [[problem: luogu,P3879]] · [P3879 \[TJOI2010\] 阅读理解](https://www.luogu.com.cn/problem/P3879)
- [x] [[problem: luogu,P4735]] · [P4735 最大异或和](https://www.luogu.com.cn/problem/P4735)
- [x] [[problem: luogu,P4592]] · [P4592 \[TJOI2018\] 异或](https://www.luogu.com.cn/problem/P4592)
- [x] [[problem: luogu,P3369]] · [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)
- [x] [[problem: luogu,P6824]] · [P6824 「EZEC-4」可乐](https://www.luogu.com.cn/problem/P6824)

## 【算法2-5】进阶搜索

[洛谷官方子题单](https://www.luogu.com.cn/training/204) · 15 题

**DFS 与剪枝**

```mermaid
flowchart TD
  nP1036["P1036 选数"]
  nP1433["P1433 吃奶酪"]
  nP1120["P1120 小木棍"]
  nP1074["P1074 靶形数独"]
  nP1312["P1312 Mayan 游戏"]
  nP3959["P3959 宝藏"]

  nP1036 --> nP1433
  nP1036 --> nP1120
  nP1120 --> nP1074
  nP1120 --> nP1312
  nP1433 --> nP3959
```

P1036 是 DFS 枚举入口：P1433 给它加状压、P1120 给它加剪枝，P3959 是状压加枚举；P1074 与 P1312 都走在 P1120 的剪枝思路上。

**BFS 与迭代加深**

```mermaid
flowchart TD
  nP1379["P1379 八数码"]
  nP2960["P2960 Milkweed"]
  nP1763["P1763 埃及分数"]
  nP2324["P2324 骑士精神"]
  nP5507["P5507 机关"]

  nP1379 --> nP2960
  nP1379 --> nP5507
  nP1763 --> nP2324
  nP1763 --> nP5507
```

两个入口都要先有上一张图里 DFS 的底子：P1379 是 BFS 与双向 BFS，P1763 是 IDDFS；P2324 与 P5507 是 IDA* 的两个典型。

**折半搜索**

```mermaid
flowchart TD
  n525E["525E Anya and Cubes"]
  nP4799["P4799 世界冰球锦标赛"]
  n912E["912E Prime Gift"]

  n525E --> nP4799
  n525E --> n912E
```

525E 是折半搜索入门，P4799 与 912E 是同一模板在不同规模上的应用，可以并列做。

P1078 文化之旅是 DFS 加最短路的错题，与本节其他题没有前置关系。

- [x] [[problem: luogu,P1036]] · [P1036 \[NOIP 2002 普及组\] 选数](https://www.luogu.com.cn/problem/P1036)
- [x] [[problem: luogu,P1433]] · [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)
- [x] [[problem: luogu,P1120]] · [P1120 \[CERC 1995\] 小木棍](https://www.luogu.com.cn/problem/P1120)
- [x] [[problem: luogu,P1763]] · [P1763 埃及分数](https://www.luogu.com.cn/problem/P1763)
- [x] [[problem: codeforces,525E]] · [525E Anya and Cubes](https://codeforces.com/problemset/problem/525/E)
- [x] [[problem: luogu,P1379]] · [P1379 八数码难题](https://www.luogu.com.cn/problem/P1379)
- [x] [[problem: luogu,P5507]] · [P5507 机关](https://www.luogu.com.cn/problem/P5507)
- [x] [[problem: luogu,P2324]] · [P2324 \[SCOI2005\] 骑士精神](https://www.luogu.com.cn/problem/P2324)
- [x] [[problem: luogu,P1074]] · [P1074 \[NOIP 2009 提高组\] 靶形数独](https://www.luogu.com.cn/problem/P1074)
- [x] [[problem: luogu,P1312]] · [P1312 \[NOIP 2011 提高组\] Mayan 游戏](https://www.luogu.com.cn/problem/P1312)
- [x] [[problem: luogu,P3959]] · [P3959 \[NOIP 2017 提高组\] 宝藏](https://www.luogu.com.cn/problem/P3959)
- [x] [[problem: luogu,P2960]] · [P2960 \[USACO09OCT\] Invasion of the Milkweed G](https://www.luogu.com.cn/problem/P2960)
- [x] [[problem: codeforces,912E]] · [912E Prime Gift](https://codeforces.com/problemset/problem/912/E)
- [x] [[problem: luogu,P4799]] · [P4799 \[CEOI 2015\] 世界冰球锦标赛 (Day2)](https://www.luogu.com.cn/problem/P4799)
- [x] [[problem: luogu,P1078]] · [P1078 \[NOIP 2012 普及组\] 文化之旅（疑似错题）](https://www.luogu.com.cn/problem/P1078)

## 【数据结构2-1】二叉堆与树状数组

[洛谷官方子题单](https://www.luogu.com.cn/training/205) · 17 题

**二叉堆**

```mermaid
flowchart TD
  nP3378["P3378 堆"]
  nP1090["P1090 合并果子"]
  nP4053["P4053 建筑抢修"]
  nP1801["P1801 黑匣子"]
  nP1168["P1168 中位数"]
  nP2085["P2085 最小函数值"]
  nP1631["P1631 序列合并"]
  nP2168["P2168 荷马史诗"]
  nP2827["P2827 蚯蚓"]
  nP1878["P1878 舞蹈课"]

  nP3378 --> nP1090
  nP1090 --> nP4053
  nP3378 --> nP1801
  nP1801 --> nP1168
  nP3378 --> nP2085
  nP2085 --> nP1631
  nP3378 --> nP2168
  nP3378 --> nP2827
  nP3378 --> nP1878
```

P3378 是模板，之后分到贪心（P1090 → P4053 的反悔贪心）、对顶堆（P1801 → P1168）、多路合并（P2085 → P1631）和三个单点应用（P2168 / P2827 / P1878）。

**树状数组**

```mermaid
flowchart TD
  nP3374["P3374 树状数组 1"]
  nP3368["P3368 树状数组 2"]
  nP2251["P2251 质量检测"]
  nP2161["P2161 会场预约"]
  nP1908["P1908 逆序对"]
  nP1966["P1966 火柴排队"]
  nP5677["P5677 配对统计"]

  nP3374 --> nP3368
  nP3374 --> nP2251
  nP3374 --> nP2161
  nP3374 --> nP1908
  nP1908 --> nP1966
  nP1908 --> nP5677
```

P3374 是模板：P3368 是它的差分版，P2251 和 P2161 要的是区间查询；P1908 用树状数组数逆序对，P1966 与 P5677 都在它之上。

- [x] [[problem: luogu,P3378]] · [P3378 【模板】堆](https://www.luogu.com.cn/problem/P3378)
- [x] [[problem: luogu,P1801]] · [P1801 黑匣子](https://www.luogu.com.cn/problem/P1801)
- [x] [[problem: luogu,P1090]] · [P1090 \[NOIP 2004 提高组\] 合并果子](https://www.luogu.com.cn/problem/P1090)
- [x] [[problem: luogu,P2168]] · [P2168 \[NOI2015\] 荷马史诗](https://www.luogu.com.cn/problem/P2168)
- [x] [[problem: luogu,P2827]] · [P2827 \[NOIP 2016 提高组\] 蚯蚓](https://www.luogu.com.cn/problem/P2827)
- [x] [[problem: luogu,P1168]] · [P1168 中位数](https://www.luogu.com.cn/problem/P1168)
- [x] [[problem: luogu,P2085]] · [P2085 最小函数值](https://www.luogu.com.cn/problem/P2085)
- [x] [[problem: luogu,P1631]] · [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
- [x] [[problem: luogu,P4053]] · [P4053 \[JSOI2007\] 建筑抢修](https://www.luogu.com.cn/problem/P4053)
- [x] [[problem: luogu,P1878]] · [P1878 舞蹈课](https://www.luogu.com.cn/problem/P1878)
- [x] [[problem: luogu,P2251]] · [P2251 质量检测](https://www.luogu.com.cn/problem/P2251)
- [x] [[problem: luogu,P3374]] · [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
- [x] [[problem: luogu,P3368]] · [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
- [x] [[problem: luogu,P1908]] · [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
- [x] [[problem: luogu,P5677]] · [P5677 \[GZOI2017\] 配对统计](https://www.luogu.com.cn/problem/P5677)
- [x] [[problem: luogu,P1966]] · [P1966 \[NOIP 2013 提高组\] 火柴排队](https://www.luogu.com.cn/problem/P1966)
- [x] [[problem: luogu,P2161]] · [P2161 \[SHOI2009\] 会场预约](https://www.luogu.com.cn/problem/P2161)

## 【数据结构2-2】线段树

[洛谷官方子题单](https://www.luogu.com.cn/training/206) · 16 题

**懒标记与标记叠加**

```mermaid
flowchart TD
  nP3372["P3372 线段树 1"]
  nP3870["P3870 开关"]
  nP5522["P5522 棠梨煎雪"]
  nP1558["P1558 色板游戏"]
  nP1253["P1253 扶苏的问题"]
  nP3373["P3373 线段树 2"]
  nP2572["P2572 序列操作"]
  nP4513["P4513 小白逛公园"]

  nP3372 --> nP3870
  nP3870 --> nP1558
  nP3372 --> nP5522
  nP5522 --> nP1558
  nP3372 --> nP1253
  nP1253 --> nP3373
  nP3373 --> nP2572
  nP4513 --> nP2572
```

P3372 是入口：区间异或走 P3870 → P1558（状压色板），区间赋值与加法走 P1253 → P3373，最后叠成 P2572 这种多标记题，而 P2572 还要上一张图的 P4513 做前置。

**区间信息与定位**

```mermaid
flowchart TD
  nP3372["P3372 线段树 1"]
  nP1438["P1438 无聊的数列"]
  nP1816["P1816 忠诚"]
  nP1471["P1471 方差"]
  nP4145["P4145 花神游历"]
  nP1637["P1637 三元上升子序列"]
  n19D["19D Points"]
  nP1908["P1908 逆序对"]
  nP4513["P4513 小白逛公园"]
  nP6492["P6492 STEP"]

  nP3372 --> nP1438
  nP3372 --> nP1816
  nP3372 --> nP1471
  nP3372 --> nP4145
  nP3372 --> nP1637
  nP3372 --> n19D
  nP1908 --> nP1637
  nP4513 --> nP6492
```

这一张都是「节点里存什么」的变体：差分映射 P1438、区间最值 P1816、方差 P1471、开方势能 P4145、单点定位 19D；P1908 → P1637 是逆序对的升级，P4513 → P6492 是区间合并。

- [x] [[problem: luogu,P3372]] · [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
- [x] [[problem: luogu,P3870]] · [P3870 \[TJOI2009\] 开关](https://www.luogu.com.cn/problem/P3870)
- [x] [[problem: luogu,P1438]] · [P1438 无聊的数列](https://www.luogu.com.cn/problem/P1438)
- [x] [[problem: luogu,P1253]] · [P1253 扶苏的问题](https://www.luogu.com.cn/problem/P1253)
- [x] [[problem: luogu,P3373]] · [P3373 【模板】线段树 2](https://www.luogu.com.cn/problem/P3373)
- [x] [[problem: luogu,P4513]] · [P4513 小白逛公园](https://www.luogu.com.cn/problem/P4513)
- [x] [[problem: luogu,P1908]] · [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
- [x] [[problem: luogu,P1816]] · [P1816 忠诚](https://www.luogu.com.cn/problem/P1816)
- [x] [[problem: luogu,P1471]] · [P1471 方差](https://www.luogu.com.cn/problem/P1471)
- [x] [[problem: luogu,P6492]] · [P6492 \[COCI 2010/2011 \#6\] STEP](https://www.luogu.com.cn/problem/P6492)
- [x] [[problem: luogu,P1637]] · [P1637 三元上升子序列](https://www.luogu.com.cn/problem/P1637)
- [x] [[problem: luogu,P1558]] · [P1558 色板游戏](https://www.luogu.com.cn/problem/P1558)
- [x] [[problem: luogu,P5522]] · [P5522 \[yLOI2019\] 棠梨煎雪](https://www.luogu.com.cn/problem/P5522)
- [x] [[problem: luogu,P4145]] · [P4145 上帝造题的七分钟 2 / 花神游历各国](https://www.luogu.com.cn/problem/P4145)
- [x] [[problem: luogu,P2572]] · [P2572 \[SCOI2010\] 序列操作](https://www.luogu.com.cn/problem/P2572)
- [x] [[problem: codeforces,19D]] · [19D Points](https://codeforces.com/problemset/problem/19/D)

## 【图论2-1】树

[洛谷官方子题单](https://www.luogu.com.cn/training/207) · 22 题

**DFS 与树的量**

```mermaid
flowchart TD
  nP5908["P5908 猫猫和企鹅"]
  nP1099["P1099 树网的核"]
  nP5536["P5536 核心城市"]
  nP4408["P4408 逃学的小孩"]
  nP2052["P2052 道路修建"]
  nP1395["P1395 会议"]
  nP5666["P5666 树的重心"]
  nP1351["P1351 联合权值"]

  nP5908 --> nP1099
  nP1099 --> nP5536
  nP1099 --> nP4408
  nP5908 --> nP2052
  nP2052 --> nP5666
  nP5908 --> nP1395
  nP1395 --> nP5666
  nP5908 --> nP1351
```

P5908 的 DFS 是本节总入口，之后拿三件基础武器：树的直径（P1099 → P5536 / P4408）、子树大小与重心（P2052 → P5666、P1395 → P5666）、两点距离计数 P1351。

**LCA 与树上差分**

```mermaid
flowchart TD
  nP3379["P3379 LCA"]
  nP5836["P5836 Milk Visits"]
  nP3398["P3398 仓鼠找 sugar"]
  nP5588["P5588 小猪佩奇爬树"]
  nP3128["P3128 Max Flow"]
  nP2680["P2680 运输计划"]
  nP1600["P1600 天天爱跑步"]

  nP3379 --> nP5836
  nP3379 --> nP3398
  nP3379 --> nP5588
  nP3379 --> nP3128
  nP3128 --> nP2680
  nP3379 --> nP2680
  nP3128 --> nP1600
  nP3379 --> nP1600
```

P3379 是 LCA 模板，之后分到「LCA 判定」（P5836、P3398、P5588）和「树上差分」（P3128 → P2680 / P1600，后两题还要再叠二分或计数）。

**树链剖分**

```mermaid
flowchart TD
  nP3384["P3384 树链剖分"]
  nP3038["P3038 Grass Planting"]
  nP3178["P3178 树上操作"]
  nP3976["P3976 旅游"]
  nP4092["P4092 树"]
  nP4116["P4116 Qtree3"]
  nP3313["P3313 旅行"]

  nP3384 --> nP3038
  nP3384 --> nP3178
  nP3384 --> nP3976
  nP3384 --> nP4092
  nP3384 --> nP4116
  nP3384 --> nP3313
```

P3384 是模板，进它之前要先会上一张图的 LCA；之后 P3178 / P3976 / P4092 / P4116 / P3313 都是「剖分加另一种数据结构」，P3038 是剖分加边差分。

- [x] [[problem: luogu,P5908]] · [P5908 猫猫和企鹅](https://www.luogu.com.cn/problem/P5908)
- [x] [[problem: luogu,P1099]] · [P1099 \[NOIP 2007 提高组\] 树网的核](https://www.luogu.com.cn/problem/P1099)
- [x] [[problem: luogu,P1395]] · [P1395 会议](https://www.luogu.com.cn/problem/P1395)
- [x] [[problem: luogu,P3379]] · [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
- [x] [[problem: luogu,P3128]] · [P3128 \[USACO15DEC\] Max Flow P](https://www.luogu.com.cn/problem/P3128)
- [x] [[problem: luogu,P3384]] · [P3384 【模板】重链剖分 / 树链剖分](https://www.luogu.com.cn/problem/P3384)
- [x] [[problem: luogu,P3038]] · [P3038 \[USACO11DEC\] Grass Planting G](https://www.luogu.com.cn/problem/P3038)
- [x] [[problem: luogu,P3976]] · [P3976 \[TJOI2015\] 旅游](https://www.luogu.com.cn/problem/P3976)
- [x] [[problem: luogu,P2052]] · [P2052 \[NOI2011\] 道路修建](https://www.luogu.com.cn/problem/P2052)
- [x] [[problem: luogu,P5666]] · [P5666 \[CSP-S 2019\] 树的重心](https://www.luogu.com.cn/problem/P5666)
- [x] [[problem: luogu,P5588]] · [P5588 小猪佩奇爬树](https://www.luogu.com.cn/problem/P5588)
- [x] [[problem: luogu,P5536]] · [P5536 【XR-3】核心城市](https://www.luogu.com.cn/problem/P5536)
- [x] [[problem: luogu,P5836]] · [P5836 \[USACO19DEC\] Milk Visits S](https://www.luogu.com.cn/problem/P5836)
- [x] [[problem: luogu,P1351]] · [P1351 \[NOIP 2014 提高组\] 联合权值](https://www.luogu.com.cn/problem/P1351)
- [x] [[problem: luogu,P4408]] · [P4408 \[NOI2003\] 逃学的小孩 / 数据生成器](https://www.luogu.com.cn/problem/P4408)
- [x] [[problem: luogu,P3398]] · [P3398 仓鼠找 sugar](https://www.luogu.com.cn/problem/P3398)
- [x] [[problem: luogu,P2680]] · [P2680 \[NOIP 2015 提高组\] 运输计划](https://www.luogu.com.cn/problem/P2680)
- [x] [[problem: luogu,P1600]] · [P1600 \[NOIP 2016 提高组\] 天天爱跑步](https://www.luogu.com.cn/problem/P1600)
- [x] [[problem: luogu,P3178]] · [P3178 \[HAOI2015\] 树上操作](https://www.luogu.com.cn/problem/P3178)
- [x] [[problem: luogu,P4092]] · [P4092 \[HEOI2016/TJOI2016\] 树](https://www.luogu.com.cn/problem/P4092)
- [x] [[problem: luogu,P4116]] · [P4116 Qtree3](https://www.luogu.com.cn/problem/P4116)
- [x] [[problem: luogu,P3313]] · [P3313 \[SDOI2014\] 旅行](https://www.luogu.com.cn/problem/P3313)

## 【图论2-2】最短路

[洛谷官方子题单](https://www.luogu.com.cn/training/208) · 19 题

**Dijkstra**

```mermaid
flowchart TD
  nP4779["P4779 单源最短路"]
  nP2865["P2865 Roadblocks"]
  nP1144["P1144 最短路计数"]
  nP1462["P1462 通往奥格瑞玛"]
  nP1875["P1875 魔法药水"]
  nP3403["P3403 跳楼机"]
  nP4568["P4568 飞行路线"]
  nP1073["P1073 最优贸易"]

  nP4779 --> nP2865
  nP4779 --> nP1144
  nP4779 --> nP1462
  nP4779 --> nP1875
  nP4779 --> nP3403
  nP4779 --> nP4568
  nP4568 --> nP1073
```

P4779 是模板，之后六个方向：次短路 P2865、计数 P1144、二分答案 P1462、Dijkstra 变体 P1875、同余最短路 P3403、分层图 P4568 → P1073。

**负环与差分约束**

```mermaid
flowchart TD
  nP3385["P3385 负环"]
  nP5960["P5960 差分约束"]
  nP1993["P1993 小 K 的农场"]
  nP3275["P3275 糖果"]

  nP3385 --> nP5960
  nP5960 --> nP1993
  nP5960 --> nP3275
```

P3385 判负环是入口，P5960 把差分约束化成最短路判负环，P1993 与 P3275 是方向相反的两个应用（最短与最长）。

**Floyd 与传递闭包**

```mermaid
flowchart TD
  nP2910["P2910 Clear And Present Danger"]
  nB3611["B3611 传递闭包"]
  nP2419["P2419 Cow Contest"]
  nP1119["P1119 灾后重建"]
  nP2047["P2047 社交网络"]
  nP6464["P6464 传送门"]
  nP1037["P1037 产生数"]

  nP2910 --> nB3611
  nB3611 --> nP2419
  nB3611 --> nP1119
  nB3611 --> nP2047
  nB3611 --> nP6464
  nB3611 --> nP1037
```

P2910 是 Floyd 模板，B3611 传递闭包之后分到 P2419（排名确定）、P1119（增量加点）、P2047（路径计数）、P6464（枚举加边）。

- [x] [[problem: luogu,P4779]] · [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
- [x] [[problem: luogu,P4568]] · [P4568 \[JLOI2011\] 飞行路线](https://www.luogu.com.cn/problem/P4568)
- [x] [[problem: luogu,P3385]] · [P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)
- [x] [[problem: luogu,P5960]] · [P5960 【模板】差分约束](https://www.luogu.com.cn/problem/P5960)
- [x] [[problem: luogu,P2865]] · [P2865 \[USACO06NOV\] Roadblocks G](https://www.luogu.com.cn/problem/P2865)
- [x] [[problem: luogu,P2910]] · [P2910 \[USACO08OPEN\] Clear And Present Danger S](https://www.luogu.com.cn/problem/P2910)
- [x] [[problem: luogu,B3611]] · [B3611 【模板】传递闭包](https://www.luogu.com.cn/problem/B3611)
- [x] [[problem: luogu,P1144]] · [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
- [x] [[problem: luogu,P1875]] · [P1875 佳佳的魔法药水【数据有误】](https://www.luogu.com.cn/problem/P1875)
- [x] [[problem: luogu,P1462]] · [P1462 通往奥格瑞玛的道路](https://www.luogu.com.cn/problem/P1462)
- [x] [[problem: luogu,P1073]] · [P1073 \[NOIP 2009 提高组\] 最优贸易](https://www.luogu.com.cn/problem/P1073)
- [x] [[problem: luogu,P1993]] · [P1993 小 K 的农场](https://www.luogu.com.cn/problem/P1993)
- [x] [[problem: luogu,P3275]] · [P3275 \[SCOI2011\] 糖果](https://www.luogu.com.cn/problem/P3275)
- [x] [[problem: luogu,P6464]] · [P6464 \[传智杯 \#2 决赛\] 传送门](https://www.luogu.com.cn/problem/P6464)
- [x] [[problem: luogu,P3403]] · [P3403 跳楼机](https://www.luogu.com.cn/problem/P3403)
- [x] [[problem: luogu,P1119]] · [P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)
- [x] [[problem: luogu,P1037]] · [P1037 \[NOIP 2002 普及组\] 产生数](https://www.luogu.com.cn/problem/P1037)
- [x] [[problem: luogu,P2419]] · [P2419 \[USACO08JAN\] Cow Contest S](https://www.luogu.com.cn/problem/P2419)
- [x] [[problem: luogu,P2047]] · [P2047 \[NOI2007\] 社交网络](https://www.luogu.com.cn/problem/P2047)

## 【图论2-3】最小生成树

[洛谷官方子题单](https://www.luogu.com.cn/training/209) · 11 题

**MST 与建模**

```mermaid
flowchart TD
  nP3366["P3366 最小生成树"]
  nP1194["P1194 买礼物"]
  nP1396["P1396 营救"]
  nP1195["P1195 口袋的天空"]
  nP2700["P2700 逐个击破"]
  nP1550["P1550 Watering Hole"]
  n1245D["1245D Power Grid"]
  nP3623["P3623 免费道路"]
  nP1967["P1967 货车运输"]
  nP4180["P4180 严格次小生成树"]

  nP3366 --> nP1194
  nP3366 --> nP1396
  nP3366 --> nP1195
  nP1195 --> nP2700
  nP3366 --> nP1550
  nP1550 --> n1245D
  nP3366 --> nP3623
  nP3366 --> nP1967
  nP1967 --> nP4180
```

P3366 是唯一入口，之后一分为二：一是「建模」（建图 P1194、虚点 P1550 → 1245D、森林 P1195 → P2700、构造 P3623），二是「MST 加 LCA」这条硬链 P1967 → P4180。

1120D 与本节其他题没有前置关系，可以最后再做。

- [ ] [[problem: luogu,P3366]] · [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
- [ ] [[problem: luogu,P1194]] · [P1194 买礼物](https://www.luogu.com.cn/problem/P1194)
- [ ] [[problem: luogu,P4180]] · [P4180 \[BJWC2010\] 严格次小生成树](https://www.luogu.com.cn/problem/P4180)
- [ ] [[problem: luogu,P1396]] · [P1396 营救](https://www.luogu.com.cn/problem/P1396)
- [ ] [[problem: luogu,P1195]] · [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)
- [ ] [[problem: luogu,P1550]] · [P1550 \[USACO08OCT\] Watering Hole G](https://www.luogu.com.cn/problem/P1550)
- [ ] [[problem: luogu,P1967]] · [P1967 \[NOIP 2013 提高组\] 货车运输](https://www.luogu.com.cn/problem/P1967)
- [ ] [[problem: luogu,P2700]] · [P2700 逐个击破](https://www.luogu.com.cn/problem/P2700)
- [ ] [[problem: codeforces,1245D]] · [1245D Shichikuji and Power Grid](https://codeforces.com/problemset/problem/1245/D)
- [ ] [[problem: luogu,P3623]] · [P3623 \[APIO2008\] 免费道路](https://www.luogu.com.cn/problem/P3623)
- [ ] [[problem: codeforces,1120D]] · [1120D Power Tree](https://codeforces.com/problemset/problem/1120/D)

## 【图论2-4】连通性问题

[洛谷官方子题单](https://www.luogu.com.cn/training/210) · 17 题

**边双**

```mermaid
flowchart TD
  nP1656["P1656 炸铁路"]
  nP2860["P2860 Redundant Paths"]
  nCF1000E["CF1000E We Need More Bosses"]

  nP1656 --> nP2860
  nP2860 --> nCF1000E
```

P1656 求桥是入口：缩掉边双之后，P2860 问「加多少边才能边双连通」，CF1000E 再叠一步求缩点树的直径。

**点双与圆方树**

```mermaid
flowchart TD
  nP3388["P3388 割点"]
  nP3469["P3469 BLO-Blockade"]
  nP4630["P4630 铁人两项"]
  nP4606["P4606 战略游戏"]
  nCF487E["CF487E Tourists"]

  nP3388 --> nP3469
  nP3388 --> nP4630
  nP4630 --> nP4606
  nP4606 --> nCF487E
```

P3388 割点是入口：P3469 数删点之后的连通块变化，P4630 把割点建成圆方树，P4606 与 CF487E 是圆方树上的进一步套用。

**SCC 与 2-SAT**

```mermaid
flowchart TD
  nP2863["P2863 The Cow Prom"]
  nP3387["P3387 缩点"]
  nP1262["P1262 间谍网络"]
  nP2341["P2341 受欢迎的牛"]
  nP4819["P4819 杀人游戏"]
  nP5025["P5025 炸弹"]
  nP7737["P7737 庆典"]
  nP4782["P4782 2-SAT"]
  nP3825["P3825 游戏"]

  nP2863 --> nP3387
  nP3387 --> nP1262
  nP3387 --> nP2341
  nP3387 --> nP4819
  nP3387 --> nP5025
  nP3387 --> nP7737
  nP2863 --> nP4782
  nP4782 --> nP3825
```

P2863 是 SCC 模板，P3387 缩点之后分出 P1262 / P2341 / P4819 / P5025 / P7737；2-SAT 要先会 SCC，也就是 P4782 → P3825。

- [ ] [[problem: luogu,P1656]] · [P1656 炸铁路](https://www.luogu.com.cn/problem/P1656)
- [ ] [[problem: luogu,P2860]] · [P2860 \[USACO06JAN\] Redundant Paths G](https://www.luogu.com.cn/problem/P2860)
- [ ] [[problem: luogu,P3388]] · [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)
- [ ] [[problem: luogu,P4630]] · [P4630 \[APIO2018\] 铁人两项](https://www.luogu.com.cn/problem/P4630)
- [ ] [[problem: luogu,P2863]] · [P2863 \[USACO06JAN\] The Cow Prom S](https://www.luogu.com.cn/problem/P2863)
- [ ] [[problem: luogu,P3387]] · [P3387 【模板】缩点 / 强连通分量](https://www.luogu.com.cn/problem/P3387)
- [ ] [[problem: luogu,P4782]] · [P4782 【模板】2-SAT](https://www.luogu.com.cn/problem/P4782)
- [ ] [[problem: luogu,CF1000E]] · [CF1000E We Need More Bosses](https://www.luogu.com.cn/problem/CF1000E)
- [ ] [[problem: luogu,P3469]] · [P3469 \[POI 2008\] BLO-Blockade](https://www.luogu.com.cn/problem/P3469)
- [ ] [[problem: luogu,P4606]] · [P4606 \[SDOI2018\] 战略游戏](https://www.luogu.com.cn/problem/P4606)
- [ ] [[problem: luogu,CF487E]] · [CF487E Tourists](https://www.luogu.com.cn/problem/CF487E)
- [ ] [[problem: luogu,P1262]] · [P1262 \[POI 1996 R3\] 间谍网络](https://www.luogu.com.cn/problem/P1262)
- [ ] [[problem: luogu,P2341]] · [P2341 \[USACO03FALL / HAOI2006\] 受欢迎的牛 G](https://www.luogu.com.cn/problem/P2341)
- [ ] [[problem: luogu,P5025]] · [P5025 \[SNOI2017\] 炸弹](https://www.luogu.com.cn/problem/P5025)
- [ ] [[problem: luogu,P3825]] · [P3825 \[NOI2017\] 游戏](https://www.luogu.com.cn/problem/P3825)
- [ ] [[problem: luogu,P4819]] · [P4819 \[中山市选\] 杀人游戏](https://www.luogu.com.cn/problem/P4819)
- [ ] [[problem: luogu,P7737]] · [P7737 \[NOI2021\] 庆典](https://www.luogu.com.cn/problem/P7737)

## 【动态规划1】动态规划的引入

[洛谷官方子题单](https://www.luogu.com.cn/training/211) · 18 题

**线性与网格 DP**

```mermaid
flowchart TD
  nP1216["P1216 数字三角形"]
  nP2196["P2196 挖地雷"]
  nP1434["P1434 滑雪"]
  nP4017["P4017 食物链计数"]
  nP1115["P1115 最大子段和"]
  nP1002["P1002 过河卒"]
  nP3842["P3842 线段"]

  nP1216 --> nP2196
  nP1216 --> nP1434
  nP1216 --> nP4017
  nP1216 --> nP1115
  nP1216 --> nP1002
  nP1216 --> nP3842
```

P1216 是本节所有「按顺序填表」的共同入口，之后分到 DAG 上的 DP（P2196、P4017）、记忆化（P1434）、线性（P1115、P3842）和网格（P1002）。

**01 背包**

```mermaid
flowchart TD
  nP1048["P1048 采药"]
  nP1802["P1802 5 倍经验日"]
  nP1049["P1049 装箱问题"]
  nP1164["P1164 小 A 点菜"]
  nP1064["P1064 金明的预算"]
  nP2392["P2392 考前抱佛脚"]

  nP1048 --> nP1802
  nP1048 --> nP1049
  nP1048 --> nP1164
  nP1048 --> nP1064
  nP1048 --> nP2392
```

P1048 是 01 背包模板，之后分到价值最大化（P1802）、体积装填（P1049）、方案计数（P1164）、分组背包（P1064）和搜索也能过的 P2392。

**完全背包**

```mermaid
flowchart TD
  nP2842["P2842 纸币问题 1"]
  nP2840["P2840 纸币问题 2"]
  nP2834["P2834 纸币问题 3"]
  nP1077["P1077 摆花"]
  nP1616["P1616 疯狂的采药"]

  nP2842 --> nP2840
  nP2840 --> nP2834
  nP2842 --> nP1616
  nP2840 --> nP1077
```

纸币问题 1 / 2 / 3 是同一条递进线；P1616 是 P1048 的完全背包版（要先看上一张图的 01 背包），P1077 是它的计数版。

- [ ] [[problem: luogu,P2842]] · [P2842 纸币问题 1](https://www.luogu.com.cn/problem/P2842)
- [ ] [[problem: luogu,P1216]] · [P1216 \[IOI 1994 / USACO1.5\] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)
- [ ] [[problem: luogu,P2840]] · [P2840 纸币问题 2](https://www.luogu.com.cn/problem/P2840)
- [ ] [[problem: luogu,P2834]] · [P2834 纸币问题 3](https://www.luogu.com.cn/problem/P2834)
- [ ] [[problem: luogu,P1048]] · [P1048 \[NOIP 2005 普及组\] 采药](https://www.luogu.com.cn/problem/P1048)
- [ ] [[problem: luogu,P2196]] · [P2196 \[NOIP 1996 提高组\] 挖地雷](https://www.luogu.com.cn/problem/P2196)
- [ ] [[problem: luogu,P1434]] · [P1434 \[SHOI2002\] 滑雪](https://www.luogu.com.cn/problem/P1434)
- [ ] [[problem: luogu,P4017]] · [P4017 最大食物链计数](https://www.luogu.com.cn/problem/P4017)
- [ ] [[problem: luogu,P1115]] · [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [ ] [[problem: luogu,P1802]] · [P1802 5 倍经验日](https://www.luogu.com.cn/problem/P1802)
- [ ] [[problem: luogu,P1002]] · [P1002 \[NOIP 2002 普及组\] 过河卒](https://www.luogu.com.cn/problem/P1002)
- [ ] [[problem: luogu,P1049]] · [P1049 \[NOIP 2001 普及组\] 装箱问题](https://www.luogu.com.cn/problem/P1049)
- [ ] [[problem: luogu,P1616]] · [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)
- [ ] [[problem: luogu,P1164]] · [P1164 小 A 点菜](https://www.luogu.com.cn/problem/P1164)
- [ ] [[problem: luogu,P1077]] · [P1077 \[NOIP 2012 普及组\] 摆花](https://www.luogu.com.cn/problem/P1077)
- [ ] [[problem: luogu,P3842]] · [P3842 \[TJOI2007\] 线段](https://www.luogu.com.cn/problem/P3842)
- [ ] [[problem: luogu,P1064]] · [P1064 \[NOIP 2006 提高组\] 金明的预算方案](https://www.luogu.com.cn/problem/P1064)
- [ ] [[problem: luogu,P2392]] · [P2392 kkksc03 考前临时抱佛脚](https://www.luogu.com.cn/problem/P2392)

## 【动态规划2】线性状态动态规划

[洛谷官方子题单](https://www.luogu.com.cn/training/212) · 17 题

**LIS、字符串与网格**

```mermaid
flowchart TD
  nP1020["P1020 导弹拦截"]
  nP2285["P2285 打鼹鼠"]
  nP1439["P1439 最长公共子序列"]
  nP1091["P1091 合唱队形"]
  nP1874["P1874 快速求和"]
  nP2758["P2758 编辑距离"]
  nP2679["P2679 子串"]
  nP1544["P1544 三倍经验"]
  nP1004["P1004 方格取数"]
  nP1541["P1541 乌龟棋"]
  nP1854["P1854 花店橱窗"]

  nP1020 --> nP2285
  nP1020 --> nP1439
  nP1020 --> nP1091
  nP1874 --> nP2758
  nP2758 --> nP2679
  nP1544 --> nP1004
  nP1004 --> nP1541
  nP1854 --> nP1541
```

三条线：LIS 从 P1020 起（P2285、P1439、P1091），字符串 DP 从 P1874 → P2758 → P2679，网格 DP 从 P1544 → P1004 → P1541。

P4933（等差序列）、P4310（位运算）、P3147（倍增 DP）、P1725（单调队列优化）、P1833（多重背包）、P2340（值域背包）与上面三条线都没有前置关系，按难度自选顺序即可。

- [ ] [[problem: luogu,P1020]] · [P1020 \[NOIP 1999 提高组\] 导弹拦截](https://www.luogu.com.cn/problem/P1020)
- [ ] [[problem: luogu,P2285]] · [P2285 \[HNOI2004\] 打鼹鼠](https://www.luogu.com.cn/problem/P2285)
- [ ] [[problem: luogu,P1725]] · [P1725 琪露诺](https://www.luogu.com.cn/problem/P1725)
- [ ] [[problem: luogu,P4933]] · [P4933 大师](https://www.luogu.com.cn/problem/P4933)
- [ ] [[problem: luogu,P1874]] · [P1874 快速求和](https://www.luogu.com.cn/problem/P1874)
- [ ] [[problem: luogu,P2758]] · [P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)
- [ ] [[problem: luogu,P1439]] · [P1439 两个排列的最长公共子序列](https://www.luogu.com.cn/problem/P1439)
- [ ] [[problem: luogu,P2679]] · [P2679 \[NOIP 2015 提高组\] 子串](https://www.luogu.com.cn/problem/P2679)
- [ ] [[problem: luogu,P1544]] · [P1544 三倍经验](https://www.luogu.com.cn/problem/P1544)
- [ ] [[problem: luogu,P1004]] · [P1004 \[NOIP 2000 提高组\] 方格取数](https://www.luogu.com.cn/problem/P1004)
- [ ] [[problem: luogu,P1091]] · [P1091 \[NOIP 2004 提高组\] 合唱队形](https://www.luogu.com.cn/problem/P1091)
- [ ] [[problem: luogu,P1854]] · [P1854 \[IOI 1999\] 花店橱窗布置](https://www.luogu.com.cn/problem/P1854)
- [ ] [[problem: luogu,P1833]] · [P1833 樱花](https://www.luogu.com.cn/problem/P1833)
- [ ] [[problem: luogu,P2340]] · [P2340 \[USACO03FALL\] Cow Exhibition G](https://www.luogu.com.cn/problem/P2340)
- [ ] [[problem: luogu,P1541]] · [P1541 \[NOIP 2010 提高组\] 乌龟棋](https://www.luogu.com.cn/problem/P1541)
- [ ] [[problem: luogu,P4310]] · [P4310 绝世好题](https://www.luogu.com.cn/problem/P4310)
- [ ] [[problem: luogu,P3147]] · [P3147 \[USACO16OPEN\] 262144 P](https://www.luogu.com.cn/problem/P3147)

## 【动态规划3】区间与环形动态规划

[洛谷官方子题单](https://www.luogu.com.cn/training/213) · 12 题

**区间与环形**

```mermaid
flowchart TD
  nP1435["P1435 回文字串"]
  nP1775["P1775 石子合并（弱化版）"]
  nCF607B["CF607B Zuma"]
  nP3205["P3205 合唱队"]
  nP1220["P1220 关路灯"]
  nP4170["P4170 涂色"]
  nP4290["P4290 玩具取名"]
  nP1880["P1880 石子合并"]
  nP1063["P1063 能量项链"]
  nP4342["P4342 Polygon"]

  nP1435 --> nP1775
  nP1775 --> nCF607B
  nP1775 --> nP3205
  nP3205 --> nP1220
  nP1775 --> nP4170
  nP1775 --> nP4290
  nP1775 --> nP1880
  nP1880 --> nP1063
  nP1880 --> nP4342
```

P1435 和 P1775 是两个入口，P1775 之后分到 P607B、P3205（→ P1220）、P4170、P4290。环形必须先会 P1880 的断环成链，它的两个后继 P1063 与 P4342 是本节的最高档。

P1140（相似基因）和 P1070（道路游戏）与这条主线没有前置关系。

- [ ] [[problem: luogu,P1435]] · [P1435 \[IOI 2000\] 回文字串](https://www.luogu.com.cn/problem/P1435)
- [ ] [[problem: luogu,P1775]] · [P1775 石子合并（弱化版）](https://www.luogu.com.cn/problem/P1775)
- [ ] [[problem: luogu,CF607B]] · [CF607B Zuma](https://www.luogu.com.cn/problem/CF607B)
- [ ] [[problem: luogu,P3205]] · [P3205 \[HNOI2010\] 合唱队](https://www.luogu.com.cn/problem/P3205)
- [ ] [[problem: luogu,P1880]] · [P1880 \[NOI1995\] 石子合并](https://www.luogu.com.cn/problem/P1880)
- [ ] [[problem: luogu,P1140]] · [P1140 \[ICPC 2001 Taejon R\] 相似基因](https://www.luogu.com.cn/problem/P1140)
- [ ] [[problem: luogu,P4170]] · [P4170 \[CQOI2007\] 涂色](https://www.luogu.com.cn/problem/P4170)
- [ ] [[problem: luogu,P4290]] · [P4290 \[HAOI2008\] 玩具取名](https://www.luogu.com.cn/problem/P4290)
- [ ] [[problem: luogu,P1063]] · [P1063 \[NOIP 2006 提高组\] 能量项链](https://www.luogu.com.cn/problem/P1063)
- [ ] [[problem: luogu,P1070]] · [P1070 \[NOIP 2009 普及组\] 道路游戏](https://www.luogu.com.cn/problem/P1070)
- [ ] [[problem: luogu,P4342]] · [P4342 \[IOI 1998\] Polygon](https://www.luogu.com.cn/problem/P4342)
- [ ] [[problem: luogu,P1220]] · [P1220 关路灯](https://www.luogu.com.cn/problem/P1220)

## 【动态规划4】树与图上的动态规划

[洛谷官方子题单](https://www.luogu.com.cn/training/214) · 17 题

**树形 DP**

```mermaid
flowchart TD
  nP1352["P1352 没有上司的舞会"]
  nP1122["P1122 最大子树和"]
  nP2016["P2016 战略游戏"]
  nP2585["P2585 三色二叉树"]
  nP2986["P2986 Great Cow Gathering"]
  nP2015["P2015 二叉苹果树"]
  nP2014["P2014 选课"]
  nP1273["P1273 有线电视网"]
  nP2515["P2515 软件安装"]

  nP1352 --> nP1122
  nP1352 --> nP2016
  nP1352 --> nP2585
  nP1352 --> nP2986
  nP1352 --> nP2015
  nP2015 --> nP2014
  nP2014 --> nP1273
  nP2014 --> nP2515
```

P1352 是树形 DP 入口：一支是树上背包（P2015 → P2014 → P1273，再叠 tarjan 缩点得到 P2515），一支是覆盖与计数（P2016、P2585），P2986 是换根。

**图上 DP**

```mermaid
flowchart TD
  nP4316["P4316 绿豆蛙的归宿"]
  nP7077["P7077 函数调用"]
  nP1613["P1613 跑路"]
  nP3953["P3953 逛公园"]

  nP4316 --> nP7077
  nP1613 --> nP3953
```

这条线跟前一张图没有关系：P4316 是 DAG 上的期望，P7077 是同类的「按拓扑序算贡献」；P1613 → P3953 是倍增加最短路计数。

P1040（树上区间 DP）、P2656（SCC 加 DP）、P6772（矩阵加 DP）、P7516（图函数）各自独立，可以随时穿插。

- [ ] [[problem: luogu,P1352]] · [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
- [ ] [[problem: luogu,P2015]] · [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)
- [ ] [[problem: luogu,P2014]] · [P2014 \[CTSC1997\] 选课](https://www.luogu.com.cn/problem/P2014)
- [ ] [[problem: luogu,P1613]] · [P1613 跑路](https://www.luogu.com.cn/problem/P1613)
- [ ] [[problem: luogu,P6772]] · [P6772 \[NOI2020\] 美食家](https://www.luogu.com.cn/problem/P6772)
- [ ] [[problem: luogu,P4316]] · [P4316 绿豆蛙的归宿](https://www.luogu.com.cn/problem/P4316)
- [ ] [[problem: luogu,P2656]] · [P2656 采蘑菇](https://www.luogu.com.cn/problem/P2656)
- [ ] [[problem: luogu,P1040]] · [P1040 \[NOIP 2003 提高组\] 加分二叉树](https://www.luogu.com.cn/problem/P1040)
- [ ] [[problem: luogu,P1122]] · [P1122 最大子树和](https://www.luogu.com.cn/problem/P1122)
- [ ] [[problem: luogu,P2016]] · [P2016 \[SEERC 2000\] 战略游戏](https://www.luogu.com.cn/problem/P2016)
- [ ] [[problem: luogu,P2585]] · [P2585 \[ZJOI2006\] 三色二叉树](https://www.luogu.com.cn/problem/P2585)
- [ ] [[problem: luogu,P1273]] · [P1273 \[CHCI 2002 Final Exam \#2\] 有线电视网](https://www.luogu.com.cn/problem/P1273)
- [ ] [[problem: luogu,P2515]] · [P2515 \[HAOI2010\] 软件安装](https://www.luogu.com.cn/problem/P2515)
- [ ] [[problem: luogu,P2986]] · [P2986 \[USACO10MAR\] Great Cow Gathering G](https://www.luogu.com.cn/problem/P2986)
- [ ] [[problem: luogu,P3953]] · [P3953 \[NOIP 2017 提高组\] 逛公园](https://www.luogu.com.cn/problem/P3953)
- [ ] [[problem: luogu,P7077]] · [P7077 \[CSP-S 2020\] 函数调用](https://www.luogu.com.cn/problem/P7077)
- [ ] [[problem: luogu,P7516]] · [P7516 \[省选联考 2021 A/B 卷\] 图函数](https://www.luogu.com.cn/problem/P7516)

## 【动态规划5】状态压缩动态规划

[洛谷官方子题单](https://www.luogu.com.cn/training/215) · 21 题

**网格状压**

```mermaid
flowchart TD
  nP1896["P1896 互不侵犯"]
  nP1879["P1879 Corn Fields"]
  nP2704["P2704 炮兵阵地"]

  nP1896 --> nP1879
  nP1879 --> nP2704
```

P1896 是状压起点，逐行转移的模板再加一格难度就是 P1879 和 P2704 这一对。

**集合状压与计数**

```mermaid
flowchart TD
  nP1896["P1896 互不侵犯"]
  nCF11D["CF11D A Simple Task"]
  nP3959["P3959 宝藏"]
  nP2831["P2831 愤怒的小鸟"]
  nP3694["P3694 邦邦的大合唱"]
  nP5369["P5369 最大前缀和"]

  nP1896 --> nCF11D
  nP1896 --> nP3959
  nP1896 --> nP2831
  nP1896 --> nP3694
  nP1896 --> nP5369
```

这一张都是「把集合当状态」：简单环计数 CF11D、生成树 P3959、覆盖 P2831、顺序 P3694、前缀和计数 P5369。

**状压再叠一个工具**

```mermaid
flowchart TD
  nP1896["P1896 互不侵犯"]
  nP1357["P1357 花园"]
  nP4045["P4045 密码"]
  nP2167["P2167 Bill 的挑战"]
  nP4484["P4484 最长上升子序列"]
  nP4363["P4363 一双木棋"]
  nP2473["P2473 奖励关"]

  nP1896 --> nP1357
  nP1896 --> nP4045
  nP1896 --> nP2167
  nP1896 --> nP4484
  nP1896 --> nP4363
  nP1896 --> nP2473
```

矩阵快速幂 P1357、AC 自动机 P4045、容斥 P2167、状态压缩 LIS P4484、博弈 P4363、期望倒推 P2473——状压只是入口，难点在叠加的那个工具。

**状态当点跑 BFS**

```mermaid
flowchart TD
  nP1896["P1896 互不侵犯"]
  nP2622["P2622 关灯问题"]
  nP2761["P2761 软件补丁"]

  nP1896 --> nP2622
  nP2622 --> nP2761
```

P2622 把每个状态当作图上一点跑 BFS 求最少步数，P2761 是同一个套路再叠一层最短路。

**状压综合**

```mermaid
flowchart TD
  nP1896["P1896 互不侵犯"]
  nCF1209E2["CF1209E2 Rotate Columns"]
  nAT_agc012_e["AT_agc012_e Camel and Oases"]
  nP10865["P10865 Genshin Impact"]

  nP1896 --> nCF1209E2
  nP1896 --> nAT_agc012_e
  nP1896 --> nP10865
```

这三题是比赛里的变形用法，没有额外的公共前置，做完前几张图再来。

P1450（容斥加背包）和 P1441（枚举子集）与状压主线没有前置关系。

- [ ] [[problem: luogu,P1896]] · [P1896 \[SCOI2005\] 互不侵犯](https://www.luogu.com.cn/problem/P1896)
- [ ] [[problem: luogu,P2622]] · [P2622 关灯问题 II](https://www.luogu.com.cn/problem/P2622)
- [ ] [[problem: luogu,CF11D]] · [CF11D A Simple Task](https://www.luogu.com.cn/problem/CF11D)
- [ ] [[problem: luogu,P3959]] · [P3959 \[NOIP 2017 提高组\] 宝藏](https://www.luogu.com.cn/problem/P3959)
- [ ] [[problem: luogu,P4484]] · [P4484 \[BJWC2018\] 最长上升子序列](https://www.luogu.com.cn/problem/P4484)
- [ ] [[problem: luogu,P4363]] · [P4363 \[九省联考 2018\] 一双木棋 chess](https://www.luogu.com.cn/problem/P4363)
- [ ] [[problem: luogu,P1357]] · [P1357 花园](https://www.luogu.com.cn/problem/P1357)
- [ ] [[problem: luogu,P1450]] · [P1450 \[HAOI2008\] 硬币购物](https://www.luogu.com.cn/problem/P1450)
- [ ] [[problem: luogu,P3694]] · [P3694 邦邦的大合唱站队](https://www.luogu.com.cn/problem/P3694)
- [ ] [[problem: luogu,P1441]] · [P1441 砝码称重](https://www.luogu.com.cn/problem/P1441)
- [ ] [[problem: luogu,P1879]] · [P1879 \[USACO06NOV\] Corn Fields G](https://www.luogu.com.cn/problem/P1879)
- [ ] [[problem: luogu,P2704]] · [P2704 \[NOI2001\] 炮兵阵地](https://www.luogu.com.cn/problem/P2704)
- [ ] [[problem: luogu,P2831]] · [P2831 \[NOIP 2016 提高组\] 愤怒的小鸟](https://www.luogu.com.cn/problem/P2831)
- [ ] [[problem: luogu,P4045]] · [P4045 \[JSOI2009\] 密码](https://www.luogu.com.cn/problem/P4045)
- [ ] [[problem: luogu,AT_agc012_e]] · [AT\_agc012\_e \[AGC012E\] Camel and Oases](https://www.luogu.com.cn/problem/AT_agc012_e)
- [ ] [[problem: luogu,CF1209E2]] · [CF1209E2 Rotate Columns (hard version)](https://www.luogu.com.cn/problem/CF1209E2)
- [ ] [[problem: luogu,P5369]] · [P5369 \[PKUSC2018\] 最大前缀和](https://www.luogu.com.cn/problem/P5369)
- [ ] [[problem: luogu,P2761]] · [P2761 软件补丁问题](https://www.luogu.com.cn/problem/P2761)
- [ ] [[problem: luogu,P2473]] · [P2473 \[SCOI2008\] 奖励关](https://www.luogu.com.cn/problem/P2473)
- [ ] [[problem: luogu,P2167]] · [P2167 \[SDOI2009\] Bill的挑战](https://www.luogu.com.cn/problem/P2167)
- [ ] [[problem: luogu,P10865]] · [P10865 \[HBCPC2024\] Genshin Impact Startup Forbidden III](https://www.luogu.com.cn/problem/P10865)

## 【数学2-1】进阶数论

[洛谷官方子题单](https://www.luogu.com.cn/training/216) · 22 题

**exgcd 与 CRT**

```mermaid
flowchart TD
  nP1082["P1082 同余方程"]
  nP4549["P4549 裴蜀定理"]
  nP1516["P1516 青蛙的约会"]
  nP2421["P2421 荒岛野人"]
  nP1495["P1495 中国剩余定理"]
  nCF687B["CF687B Remainders Game"]
  nP4942["P4942 小凯的数字"]

  nP1082 --> nP4549
  nP4549 --> nP1516
  nP1516 --> nP2421
  nP1082 --> nP1495
  nP1495 --> nCF687B
  nP1082 --> nP4942
```

P1082 同余方程是入口：P4549 裴蜀定理 → P1516 → P2421 是同一套 exgcd 的四步；CRT 一支 P1495 → CF687B；P4942 只用同余运算。

**逆元与扩展欧拉定理**

```mermaid
flowchart TD
  nP1082["P1082 同余方程"]
  nP3811["P3811 乘法逆元"]
  nP2613["P2613 有理数取余"]
  nP5091["P5091 扩展欧拉定理"]
  nP4139["P4139 上帝与集合"]

  nP1082 --> nP3811
  nP3811 --> nP2613
  nP3811 --> nP5091
  nP5091 --> nP4139
```

P3811 是逆元模板（它的前置就是上一张图的 P1082），P2613 直接用逆元；P5091 → P4139 是扩展欧拉定理这条线。

**欧拉函数与整除分块**

```mermaid
flowchart TD
  nP2568["P2568 GCD"]
  nP2303["P2303 Longge 的问题"]
  nP2158["P2158 仪仗队"]
  nP2261["P2261 余数求和"]
  nP6583["P6583 回首过去"]

  nP2568 --> nP2303
  nP2568 --> nP2158
  nP2261 --> nP6583
```

P2568 用线性筛求欧拉函数，P2303 与 P2158 是它的两个应用；P2261 是整除分块模板，P6583 在它之上。

**素数筛与 gcd 计数**

```mermaid
flowchart TD
  nCF776B["CF776B Sherlock"]
  nCF757B["CF757B Bash's Big Day"]
  nCF632D["CF632D Longest Subsequence"]
  nCF582A["CF582A GCD Table"]

  nCF776B --> nCF757B
  nCF757B --> nCF632D
  nCF632D --> nCF582A
```

这四题做的是同一件事的不同规模：筛素数、按 gcd 归类、按倍数枚举、从 GCD 表还原原数组。

P2152（高精度 gcd）和 P3861（拆分）与本节其他题没有前置关系。

- [ ] [[problem: luogu,P1516]] · [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)
- [ ] [[problem: luogu,P4942]] · [P4942 小凯的数字](https://www.luogu.com.cn/problem/P4942)
- [ ] [[problem: luogu,P3811]] · [P3811 【模板】模意义下的乘法逆元](https://www.luogu.com.cn/problem/P3811)
- [ ] [[problem: luogu,P1495]] · [P1495 【模板】中国剩余定理（CRT）/ 曹冲养猪](https://www.luogu.com.cn/problem/P1495)
- [ ] [[problem: luogu,P3861]] · [P3861 拆分](https://www.luogu.com.cn/problem/P3861)
- [ ] [[problem: luogu,P5091]] · [P5091 【模板】扩展欧拉定理](https://www.luogu.com.cn/problem/P5091)
- [ ] [[problem: luogu,P2568]] · [P2568 GCD](https://www.luogu.com.cn/problem/P2568)
- [ ] [[problem: luogu,P2303]] · [P2303 \[SDOI2012\] Longge 的问题](https://www.luogu.com.cn/problem/P2303)
- [ ] [[problem: luogu,P1082]] · [P1082 \[NOIP 2012 提高组\] 同余方程](https://www.luogu.com.cn/problem/P1082)
- [ ] [[problem: luogu,P4549]] · [P4549 【模板】裴蜀定理](https://www.luogu.com.cn/problem/P4549)
- [ ] [[problem: luogu,P2421]] · [P2421 \[NOI2002\] 荒岛野人](https://www.luogu.com.cn/problem/P2421)
- [ ] [[problem: luogu,P2613]] · [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)
- [ ] [[problem: luogu,CF757B]] · [CF757B Bash's Big Day](https://www.luogu.com.cn/problem/CF757B)
- [ ] [[problem: luogu,CF776B]] · [CF776B Sherlock and his girlfriend](https://www.luogu.com.cn/problem/CF776B)
- [ ] [[problem: luogu,P2152]] · [P2152 \[SDOI2009\] SuperGCD](https://www.luogu.com.cn/problem/P2152)
- [ ] [[problem: luogu,CF632D]] · [CF632D Longest Subsequence](https://www.luogu.com.cn/problem/CF632D)
- [ ] [[problem: luogu,CF582A]] · [CF582A GCD Table](https://www.luogu.com.cn/problem/CF582A)
- [ ] [[problem: luogu,CF687B]] · [CF687B Remainders Game](https://www.luogu.com.cn/problem/CF687B)
- [ ] [[problem: luogu,P2261]] · [P2261 \[CQOI2007\] 余数求和](https://www.luogu.com.cn/problem/P2261)
- [ ] [[problem: luogu,P2158]] · [P2158 \[SDOI2008\] 仪仗队](https://www.luogu.com.cn/problem/P2158)
- [ ] [[problem: luogu,P6583]] · [P6583 回首过去](https://www.luogu.com.cn/problem/P6583)
- [ ] [[problem: luogu,P4139]] · [P4139 上帝与集合的正确用法](https://www.luogu.com.cn/problem/P4139)

## 【数学2-2】组合数学与计数

[洛谷官方子题单](https://www.luogu.com.cn/training/217) · 19 题

**组合数与 Catalan**

```mermaid
flowchart TD
  nP2822["P2822 组合数问题"]
  nP1313["P1313 计算系数"]
  nP3214["P3214 卡农"]
  nP5664["P5664 Emiya"]
  nP1044["P1044 栈"]
  nP2532["P2532 树屋阶梯"]
  nP3200["P3200 有趣的数列"]

  nP2822 --> nP1313
  nP2822 --> nP3214
  nP2822 --> nP5664
  nP1044 --> nP2532
  nP2532 --> nP3200
```

P2822 递推组合数之后分出 P1313（二项式定理）、P3214 与 P5664（计数 DP）；P1044 是 Catalan 入门，P2532 与 P3200 是同一个数的两种包装。

**容斥**

```mermaid
flowchart TD
  nP3197["P3197 越狱"]
  nP5505["P5505 分特产"]
  nP2567["P2567 幸运数字"]
  nP1450["P1450 硬币购物"]

  nP3197 --> nP5505
  nP5505 --> nP2567
  nP5505 --> nP1450
```

P3197 是容斥入门，P5505 把它做成「至少」的形式，P2567 与 P1450 是两个不同场景的应用。

**错排、斯特林与排列**

```mermaid
flowchart TD
  nP4071["P4071 排列计数"]
  nP1287["P1287 盒子与球"]
  nCF961G["CF961G Partitions"]
  nCF1278F["CF1278F Cards"]
  nP5520["P5520 青原樱"]
  nP3223["P3223 排队"]

  nP4071 --> nP1287
  nP1287 --> nCF961G
  nP4071 --> nCF1278F
  nP5520 --> nP3223
```

P4071 错排是入口：P1287 盒子与球、CF961G 都用斯特林数，CF1278F 是它的期望版本；P5520 → P3223 是插板法与排列。

P3228（数列计数）和 CF1332E（奇偶性计数）与本节其他题没有前置关系。

- [ ] [[problem: luogu,P3197]] · [P3197 \[HNOI2008\] 越狱](https://www.luogu.com.cn/problem/P3197)
- [ ] [[problem: luogu,P5664]] · [P5664 \[CSP-S 2019\] Emiya 家今天的饭](https://www.luogu.com.cn/problem/P5664)
- [ ] [[problem: luogu,P1287]] · [P1287 盒子与球](https://www.luogu.com.cn/problem/P1287)
- [ ] [[problem: luogu,P1450]] · [P1450 \[HAOI2008\] 硬币购物](https://www.luogu.com.cn/problem/P1450)
- [ ] [[problem: luogu,P5520]] · [P5520 \[yLOI2019\] 青原樱](https://www.luogu.com.cn/problem/P5520)
- [ ] [[problem: luogu,P4071]] · [P4071 \[SDOI2016\] 排列计数](https://www.luogu.com.cn/problem/P4071)
- [ ] [[problem: luogu,P1313]] · [P1313 \[NOIP 2011 提高组\] 计算系数](https://www.luogu.com.cn/problem/P1313)
- [ ] [[problem: luogu,CF1332E]] · [CF1332E Height All the Same](https://www.luogu.com.cn/problem/CF1332E)
- [ ] [[problem: luogu,P1044]] · [P1044 \[NOIP 2003 普及组\] 栈](https://www.luogu.com.cn/problem/P1044)
- [ ] [[problem: luogu,P2567]] · [P2567 \[SCOI2010\] 幸运数字](https://www.luogu.com.cn/problem/P2567)
- [ ] [[problem: luogu,P5505]] · [P5505 \[JSOI2011\] 分特产](https://www.luogu.com.cn/problem/P5505)
- [ ] [[problem: luogu,P3223]] · [P3223 \[HNOI2012\] 排队](https://www.luogu.com.cn/problem/P3223)
- [ ] [[problem: luogu,P2822]] · [P2822 \[NOIP 2016 提高组\] 组合数问题](https://www.luogu.com.cn/problem/P2822)
- [ ] [[problem: luogu,P3214]] · [P3214 \[HNOI2011\] 卡农](https://www.luogu.com.cn/problem/P3214)
- [ ] [[problem: luogu,P2532]] · [P2532 \[AHOI2012\] 树屋阶梯](https://www.luogu.com.cn/problem/P2532)
- [ ] [[problem: luogu,P3200]] · [P3200 \[HNOI2009\] 有趣的数列](https://www.luogu.com.cn/problem/P3200)
- [ ] [[problem: luogu,CF1278F]] · [CF1278F Cards](https://www.luogu.com.cn/problem/CF1278F)
- [ ] [[problem: luogu,P3228]] · [P3228 \[HNOI2013\] 数列](https://www.luogu.com.cn/problem/P3228)
- [ ] [[problem: luogu,CF961G]] · [CF961G Partitions](https://www.luogu.com.cn/problem/CF961G)

## 【数学2-3】概率与统计

[洛谷官方子题单](https://www.luogu.com.cn/training/218) · 9 题

**概率与期望 DP**

```mermaid
flowchart TD
  nP2719["P2719 搞笑世界杯"]
  nP4316["P4316 绿豆蛙的归宿"]
  nP1850["P1850 换教室"]
  nP1365["P1365 WJMZBMR打osu!"]
  nP1654["P1654 OSU!"]

  nP2719 --> nP4316
  nP4316 --> nP1850
  nP1365 --> nP1654
```

本节只有两条短链：概率与期望 DP 的主线 P2719 → P4316 → P1850，以及 osu 系列的 P1365 → P1654。

P1297、CF280C、UVA11181、P2111 四题彼此独立，按难度自选顺序即可。

- [ ] [[problem: luogu,P2719]] · [P2719 搞笑世界杯](https://www.luogu.com.cn/problem/P2719)
- [ ] [[problem: luogu,P1654]] · [P1654 OSU!](https://www.luogu.com.cn/problem/P1654)
- [ ] [[problem: luogu,CF280C]] · [CF280C Game on Tree](https://www.luogu.com.cn/problem/CF280C)
- [ ] [[problem: luogu,UVA11181]] · [UVA11181 条件概率 Probability|Given](https://www.luogu.com.cn/problem/UVA11181)
- [ ] [[problem: luogu,P1365]] · [P1365 WJMZBMR打osu! / Easy](https://www.luogu.com.cn/problem/P1365)
- [ ] [[problem: luogu,P4316]] · [P4316 绿豆蛙的归宿](https://www.luogu.com.cn/problem/P4316)
- [ ] [[problem: luogu,P1297]] · [P1297 \[国家集训队\] 单选错位](https://www.luogu.com.cn/problem/P1297)
- [ ] [[problem: luogu,P2111]] · [P2111 考场奇遇](https://www.luogu.com.cn/problem/P2111)
- [ ] [[problem: luogu,P1850]] · [P1850 \[NOIP 2016 提高组\] 换教室](https://www.luogu.com.cn/problem/P1850)

## 【数学2-4】基础线性代数

[洛谷官方子题单](https://www.luogu.com.cn/training/219) · 12 题

**矩阵快速幂**

```mermaid
flowchart TD
  nP1962["P1962 斐波那契数列"]
  nP1349["P1349 广义斐波那契"]
  nP1939["P1939 矩阵加速"]
  nP4910["P4910 帕秋莉的手环"]
  nP3216["P3216 数学作业"]
  nP2151["P2151 HH 去散步"]

  nP1962 --> nP1349
  nP1349 --> nP1939
  nP1939 --> nP4910
  nP1962 --> nP3216
  nP1962 --> nP2151
```

P1962 是矩阵快速幂模板，之后分到广义递推（P1349 → P1939 → P4910）、按位分段（P3216）和图上矩阵（P2151）。

**高斯消元**

```mermaid
flowchart TD
  nP2455["P2455 线性方程组"]
  nP2447["P2447 外星千足虫"]
  nP4035["P4035 球形空间产生器"]
  nP2973["P2973 Piggies"]

  nP2455 --> nP2447
  nP2455 --> nP4035
  nP2455 --> nP2973
```

P2455 是高斯消元模板，之后分到 bitset 优化 P2447、几何建模 P4035、概率方程 P2973。

P7112（行列式求值）与 P2520（向量）和本节其他题没有前置关系。

- [ ] [[problem: luogu,P1962]] · [P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)
- [ ] [[problem: luogu,P2455]] · [P2455 \[SDOI2006\] 线性方程组](https://www.luogu.com.cn/problem/P2455)
- [ ] [[problem: luogu,P2520]] · [P2520 \[HAOI2011\] 向量](https://www.luogu.com.cn/problem/P2520)
- [ ] [[problem: luogu,P1349]] · [P1349 广义斐波那契数列](https://www.luogu.com.cn/problem/P1349)
- [ ] [[problem: luogu,P1939]] · [P1939 矩阵加速（数列）](https://www.luogu.com.cn/problem/P1939)
- [ ] [[problem: luogu,P2447]] · [P2447 \[SDOI2010\] 外星千足虫](https://www.luogu.com.cn/problem/P2447)
- [ ] [[problem: luogu,P7112]] · [P7112 【模板】行列式求值](https://www.luogu.com.cn/problem/P7112)
- [ ] [[problem: luogu,P3216]] · [P3216 \[HNOI2011\] 数学作业](https://www.luogu.com.cn/problem/P3216)
- [ ] [[problem: luogu,P4910]] · [P4910 帕秋莉的手环](https://www.luogu.com.cn/problem/P4910)
- [ ] [[problem: luogu,P2151]] · [P2151 \[SDOI2009\] HH 去散步](https://www.luogu.com.cn/problem/P2151)
- [ ] [[problem: luogu,P4035]] · [P4035 \[JSOI2008\] 球形空间产生器](https://www.luogu.com.cn/problem/P4035)
- [ ] [[problem: luogu,P2973]] · [P2973 \[USACO10HOL\] Driving Out the Piggies G](https://www.luogu.com.cn/problem/P2973)

## 【数据结构2-3】线段树的进阶用法

[洛谷官方子题单](https://www.luogu.com.cn/training/221) · 13 题

**主席树**

```mermaid
flowchart TD
  nP3834["P3834 主席树"]
  nP4587["P4587 神秘数"]
  nP3293["P3293 美味"]
  nP2839["P2839 middle"]
  nP3168["P3168 任务查询系统"]
  nP4602["P4602 混合果汁"]

  nP3834 --> nP4587
  nP3834 --> nP3293
  nP3834 --> nP2839
  nP3834 --> nP3168
  nP3834 --> nP4602
```

P3834 是主席树模板，之后分到五个方向：P4587 用区间值的单调性，P3293 与 P2839 是 01 位贪心，P3168 是差分版本，P4602 再多一步二分。

**树套树**

```mermaid
flowchart TD
  nP3834["P3834 主席树"]
  nP3380["P3380 树套树"]
  nP2617["P2617 Dynamic Rankings"]

  nP3834 --> nP3380
  nP3380 --> nP2617
```

入口同上一张图的 P3834：P3380 是树套树模板，P2617 是带修改的区间第 k 小。

**CDQ 分治**

```mermaid
flowchart TD
  nP3810["P3810 三维偏序"]
  nP3157["P3157 动态逆序对"]
  nP4093["P4093 序列"]

  nP3810 --> nP3157
  nP3157 --> nP4093
```

P3810 三维偏序是 CDQ 模板，P3157 把逆序对变成带删除，P4093 把 CDQ 用到 DP 上。

P5445（路灯）和 CF960F（Pathwalks）与上面三条主线没有硬前置。

- [ ] [[problem: luogu,P3834]] · [P3834 【模板】可持久化线段树 2](https://www.luogu.com.cn/problem/P3834)
- [ ] [[problem: luogu,P4587]] · [P4587 \[FJOI2016\] 神秘数](https://www.luogu.com.cn/problem/P4587)
- [ ] [[problem: luogu,P3380]] · [P3380 【模板】树套树](https://www.luogu.com.cn/problem/P3380)
- [ ] [[problem: luogu,P3810]] · [P3810 【模板】三维偏序 / 陌上花开](https://www.luogu.com.cn/problem/P3810)
- [ ] [[problem: luogu,P4093]] · [P4093 \[HEOI2016/TJOI2016\] 序列](https://www.luogu.com.cn/problem/P4093)
- [ ] [[problem: luogu,P3157]] · [P3157 \[CQOI2011\] 动态逆序对](https://www.luogu.com.cn/problem/P3157)
- [ ] [[problem: luogu,P3293]] · [P3293 \[SCOI2016\] 美味](https://www.luogu.com.cn/problem/P3293)
- [ ] [[problem: luogu,CF960F]] · [CF960F Pathwalks](https://www.luogu.com.cn/problem/CF960F)
- [ ] [[problem: luogu,P2617]] · [P2617 Dynamic Rankings](https://www.luogu.com.cn/problem/P2617)
- [ ] [[problem: luogu,P3168]] · [P3168 \[CQOI2015\] 任务查询系统](https://www.luogu.com.cn/problem/P3168)
- [ ] [[problem: luogu,P2839]] · [P2839 \[国家集训队\] middle](https://www.luogu.com.cn/problem/P2839)
- [ ] [[problem: luogu,P4602]] · [P4602 \[CTSC2018\] 混合果汁](https://www.luogu.com.cn/problem/P4602)
- [ ] [[problem: luogu,P5445]] · [P5445 \[APIO2019\] 路灯](https://www.luogu.com.cn/problem/P5445)

## 【动态规划6】动态规划的设计与优化

[洛谷官方子题单](https://www.luogu.com.cn/training/225) · 19 题

**前缀和与单调队列优化**

```mermaid
flowchart TD
  nP2513["P2513 逆序对数列"]
  nCF708E["CF708E Student's Camp"]
  nP3800["P3800 Power 收集"]
  nP3572["P3572 PTA-Little Bird"]
  nP2254["P2254 瑰丽华尔兹"]
  nP2569["P2569 股票交易"]
  nP5468["P5468 回家路线"]

  nP2513 --> nCF708E
  nP3800 --> nP3572
  nP3572 --> nP2254
  nP3572 --> nP2569
  nP3572 --> nP5468
```

P2513 用前缀和把三重循环压成两重，CF708E 是同一招的更大规模；P3800 是单调队列优化入口，P3572 → P2254 / P2569 / P5468 都是它的变体。

**斜率优化**

```mermaid
flowchart TD
  nP5785["P5785 任务安排"]
  nP3648["P3648 序列分割"]
  nP4027["P4027 货币兑换"]
  nP3195["P3195 玩具装箱"]
  nP5504["P5504 柠檬"]

  nP5785 --> nP3648
  nP3648 --> nP4027
  nP3648 --> nP3195
  nP3648 --> nP5504
```

P5785 任务安排是斜率优化入口，P3648 之后分到需要 CDQ 的 P4027、模板题 P3195 和带决策单调性的 P5504。

**决策单调性**

```mermaid
flowchart TD
  nP1912["P1912 诗人小G"]
  nP1973["P1973 NOI 嘉年华"]

  nP1912 --> nP1973
```

P1912 诗人小 G 是决策单调性（四边形不等式）的模板，P1973 是它在计数 DP 上的应用。

P4099（树形 DP 加计数）、P5464、CF833B（线段树优化）、AT_arc081_d 与 AT_arc066_d 与上面三块都没有硬前置。

- [ ] [[problem: luogu,P2513]] · [P2513 \[HAOI2009\] 逆序对数列](https://www.luogu.com.cn/problem/P2513)
- [ ] [[problem: luogu,CF708E]] · [CF708E Student's Camp](https://www.luogu.com.cn/problem/CF708E)
- [ ] [[problem: luogu,P3800]] · [P3800 Power 收集](https://www.luogu.com.cn/problem/P3800)
- [ ] [[problem: luogu,CF833B]] · [CF833B The Bakery](https://www.luogu.com.cn/problem/CF833B)
- [ ] [[problem: luogu,P5785]] · [P5785 \[SDOI2012\] 任务安排](https://www.luogu.com.cn/problem/P5785)
- [ ] [[problem: luogu,P3648]] · [P3648 \[APIO2014\] 序列分割](https://www.luogu.com.cn/problem/P3648)
- [ ] [[problem: luogu,P4027]] · [P4027 \[NOI2007\] 货币兑换](https://www.luogu.com.cn/problem/P4027)
- [ ] [[problem: luogu,AT_arc081_d]] · [AT\_arc081\_d \[ARC081F\] Flip and Rectangles](https://www.luogu.com.cn/problem/AT_arc081_d)
- [ ] [[problem: luogu,P5464]] · [P5464 缩小社交圈](https://www.luogu.com.cn/problem/P5464)
- [ ] [[problem: luogu,P4099]] · [P4099 \[HEOI2013\] SAO](https://www.luogu.com.cn/problem/P4099)
- [ ] [[problem: luogu,P3572]] · [P3572 \[POI 2014\] PTA-Little Bird](https://www.luogu.com.cn/problem/P3572)
- [ ] [[problem: luogu,P2254]] · [P2254 \[NOI2005\] 瑰丽华尔兹](https://www.luogu.com.cn/problem/P2254)
- [ ] [[problem: luogu,P2569]] · [P2569 \[SCOI2010\] 股票交易](https://www.luogu.com.cn/problem/P2569)
- [ ] [[problem: luogu,P1973]] · [P1973 \[NOI2011\] NOI 嘉年华](https://www.luogu.com.cn/problem/P1973)
- [ ] [[problem: luogu,P5504]] · [P5504 \[JSOI2011\] 柠檬](https://www.luogu.com.cn/problem/P5504)
- [ ] [[problem: luogu,P1912]] · [P1912 \[NOI2009\] 诗人小G](https://www.luogu.com.cn/problem/P1912)
- [ ] [[problem: luogu,P3195]] · [P3195 \[HNOI2008\] 玩具装箱](https://www.luogu.com.cn/problem/P3195)
- [ ] [[problem: luogu,P5468]] · [P5468 \[NOI2019\] 回家路线](https://www.luogu.com.cn/problem/P5468)
- [ ] [[problem: luogu,AT_arc066_d]] · [AT\_arc066\_d \[ARC066F\] Contest with Drinks Hard](https://www.luogu.com.cn/problem/AT_arc066_d)
