---
title: "2026 CSP-J 暑期一等奖训练题单"
description: "根据 2026 CSP-J 暑期一等奖训练计划整理的阶段训练题单。"
---

# 2026 CSP-J 暑期一等奖训练题单

本题单根据根目录下的 `2026-cspj-暑期一等奖训练计划.md` 整理，目标是服务 8 周暑期训练。

这不是普通刷题清单。每一道核心题都要完成下面的训练闭环：

```text
暴力解 -> 复杂度瓶颈 -> 优化方向 -> 正确性证明 -> 正解代码 -> 对拍/复盘
```

每题完成后必须写清楚四件事：

```text
暴力怎么写：
瓶颈在哪里：
正解消掉了哪一层复杂度：
下次看到什么特征要想到这个方法：
```

训练目标：

```text
T1：100 分，必须稳定
T2：90-100 分，基本零失误
T3：70-100 分，重点突破
T4：30-60 分，稳定拿部分分
总分目标：290-330+
```

## 第 1-2 周：DP 基础转化

目标：把“我只能写暴力”变成“我知道暴力哪里慢，并能尝试设计状态”。

- [ ] [[problem: luogu,P1002]]
- [ ] [[problem: luogu,P1216]]
- [ ] [[problem: luogu,P1115]]
- [ ] [[problem: luogu,P1057]]
- [ ] [[problem: luogu,P1970]]
- [ ] [[problem: luogu,P3399]]
- [ ] [[problem: luogu,P1103]]
- [ ] [[problem: luogu,P7074]]
- [ ] [[problem: luogu,P8816]]
- [ ] [[problem: luogu,P1507]]
- [ ] [[problem: luogu,P1048]]
- [ ] [[problem: luogu,P1049]]
- [ ] [[problem: luogu,P1164]]
- [ ] [[problem: luogu,P2347]]
- [ ] [[problem: luogu,P1877]]

过关标准：

```text
能先写出暴力搜索或枚举。
能指出暴力中的重复子问题。
能定义 dp 数组的含义。
能写出转移方程并解释每一项来自哪里。
```

## 第 3-4 周：数学、贪心与规律专项

目标：解决“能写暴力，但不知道怎么优化”和“想到贪心但不会证明”。

- [ ] [[problem: luogu,P9749]]
- [ ] [[problem: luogu,P9750]]
- [ ] [[problem: luogu,P8814]]
- [ ] [[problem: luogu,P7909]]
- [ ] [[problem: luogu,P9748]]
- [ ] [[problem: luogu,P8177]]
- [ ] [[problem: luogu,P6625]]
- [ ] [[problem: luogu,P1824]]
- [ ] [[problem: luogu,P2920]]
- [ ] [[problem: luogu,P2985]]
- [ ] [[problem: luogu,P2678]]
- [ ] [[problem: luogu,P1969]]
- [ ] [[problem: luogu,P3585]]
- [ ] [[problem: luogu,P9974]]
- [ ] [[problem: luogu,P3817]]
- [ ] [[problem: luogu,P3392]]
- [ ] [[problem: luogu,P1109]]
- [ ] [[problem: luogu,P2239]]
- [ ] [[problem: luogu,P1887]]
- [ ] [[problem: luogu,P9585]]

过关标准：

```text
能解释为什么排序有用。
能解释为什么局部选择不会影响全局最优。
能从 $O(n^2)$ 或 $O(n^3)$ 暴力中看出可以预处理、前缀、排序或二分。
能把证明写成 3-5 句话，而不是只说“感觉是这样”。
```

## 第 5-6 周：近三年 CSP-J 真题锚点

目标：对准近三年 CSP-J T3/T4 的真实风格，训练考试转化能力。

这些题必须做两遍：

```text
第一遍：限时完成，记录真实得分。
第二遍：复盘后重写，补齐暴力分、特殊性质分和正解。
```

### 2023 CSP-J

- [ ] [[problem: luogu,P9748]]
- [ ] [[problem: luogu,P9749]]
- [ ] [[problem: luogu,P9750]]
- [ ] [[problem: luogu,P9751]]

### 2024 CSP-J

- [ ] [[problem: luogu,P11227]]
- [ ] [[problem: luogu,P11228]]
- [ ] [[problem: luogu,P11229]]
- [ ] [[problem: luogu,P11230]]

### 2025 CSP-J

- [ ] [[problem: luogu,P14357]]
- [ ] [[problem: luogu,P14358]]
- [ ] [[problem: luogu,P14359]]
- [ ] [[problem: luogu,P14360]]

过关标准：

```text
T3 能稳定写出暴力和部分优化。
T3 能在复盘后独立写出正解。
T4 能先拿暴力分，不空题。
T4 能识别特殊性质，并写出对应部分分代码。
```

## 第 5-6 周：综合实现与考试转化

目标：解决“思路知道，但代码写不稳、调不出、考场拿不到分”的问题。

- [ ] [[problem: luogu,P7910]]
- [ ] [[problem: luogu,P7911]]
- [ ] [[problem: luogu,P8815]]
- [ ] [[problem: luogu,P7073]]
- [ ] [[problem: luogu,P7912]]
- [ ] [[problem: luogu,P1175]]
- [ ] [[problem: luogu,P2058]]
- [ ] [[problem: luogu,P1886]]
- [ ] [[problem: luogu,P3662]]
- [ ] [[problem: luogu,P5542]]
- [ ] [[problem: luogu,P1147]]
- [ ] [[problem: luogu,P2895]]
- [ ] [[problem: luogu,P5663]]
- [ ] [[problem: luogu,P9751]]
- [ ] [[problem: luogu,P1330]]

过关标准：

```text
能在限时内写出可运行代码。
能处理边界和特殊数据。
能通过样例、自造数据和必要的对拍。
不会因为一个实现细节卡死整道题。
```

## 第 7-8 周：模拟赛与稳分策略

最后两周不再大规模扩题，重点训练考试分数转化。

每周安排：

```text
2 次完整模拟赛
2 次错题重写
1 次 T3/T4 专项
1 次 T1/T2 零失误训练
1 天轻量复盘
```

每次模拟赛后必须完成：

```text
1. 统计每题实际得分。
2. 标记失分原因：不会想、想到了但不会证、会想但写错、时间不够、低级错误。
3. T1/T2 的错误必须当天重写。
4. T3/T4 至少补出暴力和正解思路。
5. 第二天重写最关键的 1-2 道题。
```

考试时间分配建议：

```text
0-40 分钟：T1 完成并检查
40-100 分钟：T2 完成并检查
100-190 分钟：主攻 T3
190-240 分钟：T4 暴力分 + 特殊性质
最后 30 分钟：回查 T1/T2/T3
```

## USACO 对标训练

题源以 USACO 2019-2025 赛季 Bronze / Silver 官方题为主，用来补充 CSP-J 的英文题面阅读、模拟实现、贪心证明和 Silver 难度转化训练。

使用方式：

```text
T1：限时 20-35 分钟，追求一次 AC。
T2：限时 35-60 分钟，写清楚边界和复杂度。
T3：先写暴力，再找排序、前缀、二分、图论或 DP 优化。
T4：不要求每题正解，先训练暴力分、特殊性质分和复盘能力。
```

### T1：稳分实现与基础模拟

- [x] [[problem: usaco,1515]]（洛谷：[P12022](https://www.luogu.com.cn/problem/P12022)）
  训练点：简单枚举，规则映射，稳定处理输入输出。
- [x] [[problem: usaco,1491]]（洛谷：[P11836](https://www.luogu.com.cn/problem/P11836)）
  训练点：坐标变换，分类讨论，避免把公式写反。
- [x] [[problem: usaco,1467]]（洛谷：[P11667](https://www.luogu.com.cn/problem/P11667)）
  训练点：网格模拟，状态覆盖，逐格判断合法性。
- [x] [[problem: usaco,1443]]（洛谷：[P11449](https://www.luogu.com.cn/problem/P11449)）
  训练点：十进制规律，模拟进位，注意临界值。
- [x] [[problem: usaco,1419]]（洛谷：[P10274](https://www.luogu.com.cn/problem/P10274)）
  训练点：布尔表达式，局部替换，预处理前后缀结果。
- [x] [[problem: usaco,1395]]（洛谷：[P10187](https://www.luogu.com.cn/problem/P10187)）
  训练点：回文性质，简单博弈结论，快速判定。
- [x] [[problem: usaco,1371]]（洛谷：[P10131](https://www.luogu.com.cn/problem/P10131)）
  训练点：局部窗口统计，去重输出，边界长度处理。
- [x] [[problem: usaco,1347]]（洛谷：[P9974](https://www.luogu.com.cn/problem/P9974)）
  训练点：过程模拟，区间增长，long long 习惯。
- [x] [[problem: usaco,1299]]（洛谷：[P9121](https://www.luogu.com.cn/problem/P9121)）
  训练点：时间轴模拟，累计贡献，排序后扫描。
- [x] [[problem: usaco,1251]]（洛谷：[P8897](https://www.luogu.com.cn/problem/P8897)）
  训练点：排序枚举，最大收益，平局规则。
- [x] [[problem: usaco,1227]]（洛谷：[P8266](https://www.luogu.com.cn/problem/P8266)）
  训练点：字符串构造，成对比较，忽略无效信息。
- [x] [[problem: usaco,1179]]（洛谷：[P8090](https://www.luogu.com.cn/problem/P8090)）
  训练点：字符计数，精确匹配与颜色匹配分离。
- [x] [[problem: usaco,1131]]（洛谷：[P9937](https://www.luogu.com.cn/problem/P9937)）
  训练点：排序，答案枚举，理解 H-index 条件。
- [x] [[problem: usaco,1107]]（洛谷：[P9943](https://www.luogu.com.cn/problem/P9943)）
  训练点：字典映射，关系链推导，模拟年份偏移。
- [x] [[problem: usaco,1109]]（洛谷：[P9945](https://www.luogu.com.cn/problem/P9945)）
  训练点：几何方向，路径转向，字符串扫描。
- [x] [[problem: usaco,1083]]（洛谷：[P9940](https://www.luogu.com.cn/problem/P9940)）
  训练点：自定义顺序，子序列扫描，计数轮次。
- [x] [[problem: usaco,1084]]（洛谷：[P9941](https://www.luogu.com.cn/problem/P9941)）
  训练点：奇偶计数，贪心配组，处理剩余情况。
- [x] [[problem: usaco,1059]]（洛谷：[P9955](https://www.luogu.com.cn/problem/P9955)）
  训练点：排序还原，基础等式，读题找最小信息。
- [x] [[problem: usaco,1060]]（洛谷：[P9956](https://www.luogu.com.cn/problem/P9956)）
  训练点：区间枚举，平均数判断，$O(n^3)$ 可接受分析。
- [x] [[problem: usaco,1035]]（洛谷：[P9952](https://www.luogu.com.cn/problem/P9952)）
  训练点：连续段统计，放置策略，首尾空段处理。
- [x] [[problem: usaco,1011]]（洛谷：[P9949](https://www.luogu.com.cn/problem/P9949)）
  训练点：三点枚举，坐标轴对齐，面积公式。
- [x] [[problem: usaco,1012]]（洛谷：[P9950](https://www.luogu.com.cn/problem/P9950)）
  训练点：连续段统计，差异段计数，简化模拟。
- [x] [[problem: usaco,987]]（洛谷：[P9946](https://www.luogu.com.cn/problem/P9946)）
  训练点：格式化输出，当前行长度维护。
- [x] [[problem: usaco,988]]（洛谷：[P9947](https://www.luogu.com.cn/problem/P9947)）
  训练点：排列构造，枚举首项，合法性检查。
- [x] [[problem: usaco,963]]（洛谷：[P5831](https://www.luogu.com.cn/problem/P5831)）
  训练点：二元关系统计，全局一致性判断。
- [x] [[problem: usaco,964]]（洛谷：[P5832](https://www.luogu.com.cn/problem/P5832)）
  训练点：子串枚举，去重判断，答案最小化。
- [x] [[problem: usaco,965]]（洛谷：[P5833](https://www.luogu.com.cn/problem/P5833)）
  训练点：全排列枚举，约束检查，字典序输出。

### T2：边界模拟、排序贪心与简单构造

- [x] [[problem: usaco,1516]]（洛谷：[P12023](https://www.luogu.com.cn/problem/P12023)）
  训练点：数量关系，分类讨论，把结论落成代码。
- [x] [[problem: usaco,1517]]（洛谷：[P12024](https://www.luogu.com.cn/problem/P12024)）
  训练点：字符串模式，频次统计，修改一位后的影响。
- [x] [[problem: usaco,1492]]（洛谷：[P11837](https://www.luogu.com.cn/problem/P11837)）
  训练点：mex 定义，频率数组，答案区间。
- [x] [[problem: usaco,1493]]（洛谷：[P11838](https://www.luogu.com.cn/problem/P11838)）
  训练点：序列构造，单调限制，样例反推规律。
- [x] [[problem: usaco,1468]]（洛谷：[P11668](https://www.luogu.com.cn/problem/P11668)）
  训练点：字符串枚举，出现次数，候选集合维护。
- [x] [[problem: usaco,1469]]（洛谷：[P11669](https://www.luogu.com.cn/problem/P11669)）
  训练点：区间反转影响，暴力优化前的计数思路。
- [x] [[problem: usaco,1444]]（洛谷：[P11450](https://www.luogu.com.cn/problem/P11450)）
  训练点：三维坐标，完整线段计数，增量更新。
- [x] [[problem: usaco,1445]]（洛谷：[P11451](https://www.luogu.com.cn/problem/P11451)）
  训练点：模式统计，去重候选，修改影响范围。
- [x] [[problem: usaco,1420]]（洛谷：[P10275](https://www.luogu.com.cn/problem/P10275)）
  训练点：路径展开，前缀距离，环上两路取最小。
- [x] [[problem: usaco,1421]]（洛谷：[P10276](https://www.luogu.com.cn/problem/P10276)）
  训练点：排列还原，唯一性判断，构造失败处理。
- [x] [[problem: usaco,1396]]（洛谷：[P10188](https://www.luogu.com.cn/problem/P10188)）
  训练点：循环结构，贡献合并，避免逐步模拟超时。
- [x] [[problem: usaco,1397]]（洛谷：[P10189](https://www.luogu.com.cn/problem/P10189)）
  训练点：线性函数比较，排序查询，二分位置。
- [x] [[problem: usaco,1372]]（洛谷：[P10132](https://www.luogu.com.cn/problem/P10132)）
  训练点：状态模拟，跳跃终止，访问标记。
- [x] [[problem: usaco,1373]]（洛谷：[P10133](https://www.luogu.com.cn/problem/P10133)）
  训练点：差分思想，线性修正，累计影响。
- [x] [[problem: usaco,1348]]（洛谷：[P9975](https://www.luogu.com.cn/problem/P9975)）
  训练点：连续段统计，最小传播半径，边界段特殊处理。
- [x] [[problem: usaco,1349]]（洛谷：[P9976](https://www.luogu.com.cn/problem/P9976)）
  训练点：不等式约束，取交集，非法情况判断。
- [x] [[problem: usaco,1323]]（洛谷：[P9183](https://www.luogu.com.cn/problem/P9183)）
  训练点：不确定字符，答案集合，奇偶规律。
- [x] [[problem: usaco,1324]]（洛谷：[P9184](https://www.luogu.com.cn/problem/P9184)）
  训练点：语法构造，按规则输出，分支组织。
- [x] [[problem: usaco,1325]]（洛谷：[P9185](https://www.luogu.com.cn/problem/P9185)）
  训练点：循环移位，模运算，位置映射。
- [x] [[problem: usaco,1300]]（洛谷：[P9122](https://www.luogu.com.cn/problem/P9122)）
  训练点：二维匹配，旋转枚举，覆盖合法性。
- [x] [[problem: usaco,1301]]（洛谷：[P9123](https://www.luogu.com.cn/problem/P9123)）
  训练点：连续段合并，费用比较，贪心断点。
- [x] [[problem: usaco,1275]]（洛谷：[P9010](https://www.luogu.com.cn/problem/P9010)）
  训练点：区间覆盖，候选领袖，分类计数。
- [x] [[problem: usaco,1276]]（洛谷：[P9011](https://www.luogu.com.cn/problem/P9011)）
  训练点：子集枚举，覆盖验证，位运算暴力。
- [x] [[problem: usaco,1277]]（洛谷：[P9012](https://www.luogu.com.cn/problem/P9012)）
  训练点：子串位置，最小代价，分类讨论。
- [x] [[problem: usaco,1252]]（洛谷：[P8898](https://www.luogu.com.cn/problem/P8898)）
  训练点：贪心放置，覆盖范围，构造输出。
- [x] [[problem: usaco,1253]]（洛谷：[P8899](https://www.luogu.com.cn/problem/P8899)）
  训练点：条件筛选，递归消元，模拟推理过程。
- [x] [[problem: usaco,1228]]（洛谷：[P8267](https://www.luogu.com.cn/problem/P8267)）
  训练点：枚举答案点，区间约束，最少矛盾数。
- [x] [[problem: usaco,1229]]（洛谷：[P8268](https://www.luogu.com.cn/problem/P8268)）
  训练点：资源递推，配方消耗，递归模拟。
- [x] [[problem: usaco,1203]]（洛谷：[P8183](https://www.luogu.com.cn/problem/P8183)）
  训练点：目标和枚举，分段验证，因子思维。
- [x] [[problem: usaco,1204]]（洛谷：[P8184](https://www.luogu.com.cn/problem/P8184)）
  训练点：相对顺序，贪心交换，位置数组。
- [x] [[problem: usaco,1205]]（洛谷：[P8185](https://www.luogu.com.cn/problem/P8185)）
  训练点：移动模拟，目标位置，构造操作。
- [x] [[problem: usaco,1180]]（洛谷：[P8091](https://www.luogu.com.cn/problem/P8091)）
  训练点：小范围枚举，比较计数，搜索候选。
- [x] [[problem: usaco,1181]]（洛谷：[P8092](https://www.luogu.com.cn/problem/P8092)）
  训练点：贪心削减，奇偶约束，前后影响。
- [x] [[problem: usaco,1155]]（洛谷：[P7993](https://www.luogu.com.cn/problem/P7993)）
  训练点：连续段贡献，组合计数，避免重复统计。
- [x] [[problem: usaco,1156]]（洛谷：[P7994](https://www.luogu.com.cn/problem/P7994)）
  训练点：差值数组，连续同号段，最少操作。

### T3：Silver 入门与 CSP-J 第三题转化

- [x] [[problem: usaco,1518]]（洛谷：[P12025](https://www.luogu.com.cn/problem/P12025)）
  训练点：构造验证，序列性质，先猜结论再证明。
- [x] [[problem: usaco,1494]]（洛谷：[P11839](https://www.luogu.com.cn/problem/P11839)）
  训练点：排序与选择，字典序目标，贪心正确性。
- [x] [[problem: usaco,1470]]（洛谷：[P11670](https://www.luogu.com.cn/problem/P11670)）
  训练点：区间贡献，分类计数，从 Bronze 思路升级。
- [x] [[problem: usaco,1446]]（洛谷：[P11452](https://www.luogu.com.cn/problem/P11452)）
  训练点：博弈规律，前后缀贡献，奇偶讨论。
- [x] [[problem: usaco,1422]]（洛谷：[P10277](https://www.luogu.com.cn/problem/P10277)）
  训练点：优先队列，事件模拟，最后一层状态。
- [x] [[problem: usaco,1374]]（洛谷：[P10134](https://www.luogu.com.cn/problem/P10134)）
  训练点：约束填数，贪心构造，非法判定。
- [x] [[problem: usaco,1350]]（洛谷：[P9977](https://www.luogu.com.cn/problem/P9977)）
  训练点：排序贪心，双端队列，批量处理。
- [x] [[problem: usaco,1326]]（洛谷：[P9186](https://www.luogu.com.cn/problem/P9186)）
  训练点：排序贡献，单点修改查询，前缀和。
- [x] [[problem: usaco,1278]]（洛谷：[P9013](https://www.luogu.com.cn/problem/P9013)）
  训练点：字符映射，图上环，操作次数分析。
- [x] [[problem: usaco,1279]]（洛谷：[P9014](https://www.luogu.com.cn/problem/P9014)）
  训练点：网格路径，影响传播，修改后的增量更新。
- [x] [[problem: usaco,1254]]（洛谷：[P8900](https://www.luogu.com.cn/problem/P8900)）
  训练点：树上 DFS，平均值转移，操作顺序。
- [x] [[problem: usaco,1206]]（洛谷：[P8186](https://www.luogu.com.cn/problem/P8186)）
  训练点：偏好关系，可达性闭包，选择最优礼物。
- [x] [[problem: usaco,1182]]（洛谷：[P8093](https://www.luogu.com.cn/problem/P8093)）
  训练点：反向贪心，状态缩小，奇偶处理。
- [x] [[problem: usaco,1158]]（洛谷：[P7990](https://www.luogu.com.cn/problem/P7990)）
  训练点：区间拆分，候选收益，排序取最大。
- [x] [[problem: usaco,1110]]（洛谷：[P7411](https://www.luogu.com.cn/problem/P7411)）
  训练点：网格增量维护，队列传播，局部更新。
- [x] [[problem: usaco,1087]]（洛谷：[P7300](https://www.luogu.com.cn/problem/P7300)）
  训练点：前后缀预处理，区间删除查询，栈思想。
- [x] [[problem: usaco,1062]]（洛谷：[P7148](https://www.luogu.com.cn/problem/P7148)）
  训练点：树上扩散，倍增增长，DFS 统计。
- [x] [[problem: usaco,1038]]（洛谷：[P6281](https://www.luogu.com.cn/problem/P6281)）
  训练点：二分答案，区间贪心检查，最大最小距离。

### T4：Silver 综合题与部分分训练

- [x] [[problem: usaco,1520]]（洛谷：[P12027](https://www.luogu.com.cn/problem/P12027)）
  训练点：复杂状态建模，先写暴力，再拆特殊性质。
- [x] [[problem: usaco,1472]]（洛谷：[P11672](https://www.luogu.com.cn/problem/P11672)）
  训练点：结构还原，约束推导，构造正确性。
- [x] [[problem: usaco,1448]]（洛谷：[P11454](https://www.luogu.com.cn/problem/P11454)）
  训练点：网格图，反向搜索，动态状态维护。
- [x] [[problem: usaco,1424]]（洛谷：[P10279](https://www.luogu.com.cn/problem/P10279)）
  训练点：字符串统计，区间贡献，复杂度压缩。
- [x] [[problem: usaco,1400]]（洛谷：[P10192](https://www.luogu.com.cn/problem/P10192)）
  训练点：贪心策略，倒推安全线，多轮决策。
- [x] [[problem: usaco,1352]]（洛谷：[P9979](https://www.luogu.com.cn/problem/P9979)）
  训练点：模拟优化，事件影响，修改一次后的收益。
- [x] [[problem: usaco,1328]]（洛谷：[P9188](https://www.luogu.com.cn/problem/P9188)）
  训练点：自动机思想，动态规划，字符串匹配计数。
- [x] [[problem: usaco,1256]]（洛谷：[P8902](https://www.luogu.com.cn/problem/P8902)）
  训练点：区间信息还原，增量构造，合法性维护。
- [x] [[problem: usaco,1112]]（洛谷：[P7410](https://www.luogu.com.cn/problem/P7410)）
  训练点：二维计数，降维枚举，前缀思想。
- [x] [[problem: usaco,1016]]（洛谷：[P6150](https://www.luogu.com.cn/problem/P6150)）
  训练点：树形结构，奇偶层分析，结论证明。

## 追加训练：DP 深化题

下面这些题来自原训练计划的 72 题核心清单。若前 6 周进度稳定，可以作为 DP 深化训练；若模拟赛暴露 DP 转化问题，也从这里回补。

- [ ] [[problem: luogu,P1388]]
- [ ] [[problem: luogu,P1977]]
- [ ] [[problem: luogu,P2800]]
- [ ] [[problem: luogu,P3009]]
- [ ] [[problem: luogu,P7158]]
- [ ] [[problem: luogu,P1855]]
- [ ] [[problem: luogu,P1616]]
- [ ] [[problem: luogu,P1832]]
- [ ] [[problem: luogu,P1077]]
- [ ] [[problem: luogu,P5662]]

## 最终执行原则

1. 每天宁可少做题，也要完成“暴力到正解”的完整链路。
2. T1/T2 错误必须当天清零，不能积压。
3. T3 是一等奖核心突破点，复盘质量比题量更重要。
4. T4 不追求每题正解，但必须训练稳定拿部分分。
5. 每周模拟赛的分数趋势比单题 AC 数更重要。
