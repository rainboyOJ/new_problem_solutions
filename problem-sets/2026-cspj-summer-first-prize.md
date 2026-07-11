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
能从 O(n^2) 或 O(n^3) 暴力中看出可以预处理、前缀、排序或二分。
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

- [x] [[problem: usaco,1515]]
  训练点：简单枚举，规则映射，稳定处理输入输出。
- [x] [[problem: usaco,1491]]
  训练点：坐标变换，分类讨论，避免把公式写反。
- [x] [[problem: usaco,1467]]
  训练点：网格模拟，状态覆盖，逐格判断合法性。
- [x] [[problem: usaco,1443]]
  训练点：十进制规律，模拟进位，注意临界值。
- [x] [[problem: usaco,1419]]
  训练点：布尔表达式，局部替换，预处理前后缀结果。
- [x] [[problem: usaco,1395]]
  训练点：回文性质，简单博弈结论，快速判定。
- [x] [[problem: usaco,1371]]
  训练点：局部窗口统计，去重输出，边界长度处理。
- [x] [[problem: usaco,1347]]
  训练点：过程模拟，区间增长，long long 习惯。
- [ ] [USACO Bronze 2023 February P1 - Hungry Cow](https://usaco.org/index.php?page=viewproblem2&cpid=1299&lang=zh)
  训练点：时间轴模拟，累计贡献，排序后扫描。
- [ ] [USACO Bronze 2022 December P1 - Cow College](https://usaco.org/index.php?page=viewproblem2&cpid=1251&lang=zh)
  训练点：排序枚举，最大收益，平局规则。
- [ ] [USACO Bronze 2022 US Open P1 - Photoshoot](https://usaco.org/index.php?page=viewproblem2&cpid=1227&lang=zh)
  训练点：字符串构造，成对比较，忽略无效信息。
- [ ] [USACO Bronze 2022 January P1 - Herdle](https://usaco.org/index.php?page=viewproblem2&cpid=1179&lang=zh)
  训练点：字符计数，精确匹配与颜色匹配分离。
- [ ] [USACO Bronze 2021 US Open P1 - Acowdemia I](https://usaco.org/index.php?page=viewproblem2&cpid=1131&lang=zh)
  训练点：排序，答案枚举，理解 H-index 条件。
- [ ] [USACO Bronze 2021 February P1 - Year of the Cow](https://usaco.org/index.php?page=viewproblem2&cpid=1107&lang=zh)
  训练点：字典映射，关系链推导，模拟年份偏移。
- [ ] [USACO Bronze 2021 February P3 - Clockwise Fence](https://usaco.org/index.php?page=viewproblem2&cpid=1109&lang=zh)
  训练点：几何方向，路径转向，字符串扫描。
- [ ] [USACO Bronze 2021 January P1 - Uddered but not Herd](https://usaco.org/index.php?page=viewproblem2&cpid=1083&lang=zh)
  训练点：自定义顺序，子序列扫描，计数轮次。
- [ ] [USACO Bronze 2021 January P2 - Even More Odd Photos](https://usaco.org/index.php?page=viewproblem2&cpid=1084&lang=zh)
  训练点：奇偶计数，贪心配组，处理剩余情况。
- [ ] [USACO Bronze 2020 December P1 - Do You Know Your ABCs?](https://usaco.org/index.php?page=viewproblem2&cpid=1059&lang=zh)
  训练点：排序还原，基础等式，读题找最小信息。
- [ ] [USACO Bronze 2020 December P2 - Daisy Chains](https://usaco.org/index.php?page=viewproblem2&cpid=1060&lang=zh)
  训练点：区间枚举，平均数判断，O(n^3) 可接受分析。
- [ ] [USACO Bronze 2020 US Open P1 - Social Distancing I](https://usaco.org/index.php?page=viewproblem2&cpid=1035&lang=zh)
  训练点：连续段统计，放置策略，首尾空段处理。
- [ ] [USACO Bronze 2020 February P1 - Triangles](https://usaco.org/index.php?page=viewproblem2&cpid=1011&lang=zh)
  训练点：三点枚举，坐标轴对齐，面积公式。
- [ ] [USACO Bronze 2020 February P2 - Mad Scientist](https://usaco.org/index.php?page=viewproblem2&cpid=1012&lang=zh)
  训练点：连续段统计，差异段计数，简化模拟。
- [ ] [USACO Bronze 2020 January P1 - Word Processor](https://usaco.org/index.php?page=viewproblem2&cpid=987&lang=zh)
  训练点：格式化输出，当前行长度维护。
- [ ] [USACO Bronze 2020 January P2 - Photoshoot](https://usaco.org/index.php?page=viewproblem2&cpid=988&lang=zh)
  训练点：排列构造，枚举首项，合法性检查。
- [ ] [USACO Bronze 2019 December P1 - Cow Gymnastics](https://usaco.org/index.php?page=viewproblem2&cpid=963&lang=zh)
  训练点：二元关系统计，全局一致性判断。
- [ ] [USACO Bronze 2019 December P2 - Where Am I?](https://usaco.org/index.php?page=viewproblem2&cpid=964&lang=zh)
  训练点：子串枚举，去重判断，答案最小化。
- [ ] [USACO Bronze 2019 December P3 - Livestock Lineup](https://usaco.org/index.php?page=viewproblem2&cpid=965&lang=zh)
  训练点：全排列枚举，约束检查，字典序输出。

### T2：边界模拟、排序贪心与简单构造

- [ ] [USACO Bronze 2025 US Open P2 - More Cow Photos](https://usaco.org/index.php?page=viewproblem2&cpid=1516&lang=zh)
  训练点：数量关系，分类讨论，把结论落成代码。
- [ ] [USACO Bronze 2025 US Open P3 - It's Mooin' Time III](https://usaco.org/index.php?page=viewproblem2&cpid=1517&lang=zh)
  训练点：字符串模式，频次统计，修改一位后的影响。
- [ ] [USACO Bronze 2025 February P2 - Making Mexes](https://usaco.org/index.php?page=viewproblem2&cpid=1492&lang=zh)
  训练点：mex 定义，频率数组，答案区间。
- [ ] [USACO Bronze 2025 February P3 - Printing Sequences](https://usaco.org/index.php?page=viewproblem2&cpid=1493&lang=zh)
  训练点：序列构造，单调限制，样例反推规律。
- [ ] [USACO Bronze 2025 January P2 - It's Mooin' Time II](https://usaco.org/index.php?page=viewproblem2&cpid=1468&lang=zh)
  训练点：字符串枚举，出现次数，候选集合维护。
- [ ] [USACO Bronze 2025 January P3 - Cow Checkups](https://usaco.org/index.php?page=viewproblem2&cpid=1469&lang=zh)
  训练点：区间反转影响，暴力优化前的计数思路。
- [ ] [USACO Bronze 2024 December P2 - Farmer John's Cheese Block](https://usaco.org/index.php?page=viewproblem2&cpid=1444&lang=zh)
  训练点：三维坐标，完整线段计数，增量更新。
- [ ] [USACO Bronze 2024 December P3 - It's Mooin' Time](https://usaco.org/index.php?page=viewproblem2&cpid=1445&lang=zh)
  训练点：模式统计，去重候选，修改影响范围。
- [ ] [USACO Bronze 2024 US Open P2 - Walking Along a Fence](https://usaco.org/index.php?page=viewproblem2&cpid=1420&lang=zh)
  训练点：路径展开，前缀距离，环上两路取最小。
- [ ] [USACO Bronze 2024 US Open P3 - Farmer John's Favorite Permutation](https://usaco.org/index.php?page=viewproblem2&cpid=1421&lang=zh)
  训练点：排列还原，唯一性判断，构造失败处理。
- [ ] [USACO Bronze 2024 February P2 - Milk Exchange](https://usaco.org/index.php?page=viewproblem2&cpid=1396&lang=zh)
  训练点：循环结构，贡献合并，避免逐步模拟超时。
- [ ] [USACO Bronze 2024 February P3 - Maximizing Productivity](https://usaco.org/index.php?page=viewproblem2&cpid=1397&lang=zh)
  训练点：线性函数比较，排序查询，二分位置。
- [ ] [USACO Bronze 2024 January P2 - Cannonball](https://usaco.org/index.php?page=viewproblem2&cpid=1372&lang=zh)
  训练点：状态模拟，跳跃终止，访问标记。
- [ ] [USACO Bronze 2024 January P3 - Balancing Bacteria](https://usaco.org/index.php?page=viewproblem2&cpid=1373&lang=zh)
  训练点：差分思想，线性修正，累计影响。
- [ ] [USACO Bronze 2023 December P2 - Cowntact Tracing 2](https://usaco.org/index.php?page=viewproblem2&cpid=1348&lang=zh)
  训练点：连续段统计，最小传播半径，边界段特殊处理。
- [ ] [USACO Bronze 2023 December P3 - Farmer John Actually Farms](https://usaco.org/index.php?page=viewproblem2&cpid=1349&lang=zh)
  训练点：不等式约束，取交集，非法情况判断。
- [ ] [USACO Bronze 2023 US Open P1 - FEB](https://usaco.org/index.php?page=viewproblem2&cpid=1323&lang=zh)
  训练点：不确定字符，答案集合，奇偶规律。
- [ ] [USACO Bronze 2023 US Open P2 - Moo Language](https://usaco.org/index.php?page=viewproblem2&cpid=1324&lang=zh)
  训练点：语法构造，按规则输出，分支组织。
- [ ] [USACO Bronze 2023 US Open P3 - Rotate and Shift](https://usaco.org/index.php?page=viewproblem2&cpid=1325&lang=zh)
  训练点：循环移位，模运算，位置映射。
- [ ] [USACO Bronze 2023 February P2 - Stamp Grid](https://usaco.org/index.php?page=viewproblem2&cpid=1300&lang=zh)
  训练点：二维匹配，旋转枚举，覆盖合法性。
- [ ] [USACO Bronze 2023 February P3 - Watching Mooloo](https://usaco.org/index.php?page=viewproblem2&cpid=1301&lang=zh)
  训练点：连续段合并，费用比较，贪心断点。
- [ ] [USACO Bronze 2023 January P1 - Leaders](https://usaco.org/index.php?page=viewproblem2&cpid=1275&lang=zh)
  训练点：区间覆盖，候选领袖，分类计数。
- [ ] [USACO Bronze 2023 January P2 - Air Cownditioning II](https://usaco.org/index.php?page=viewproblem2&cpid=1276&lang=zh)
  训练点：子集枚举，覆盖验证，位运算暴力。
- [ ] [USACO Bronze 2023 January P3 - Moo Operations](https://usaco.org/index.php?page=viewproblem2&cpid=1277&lang=zh)
  训练点：子串位置，最小代价，分类讨论。
- [ ] [USACO Bronze 2022 December P2 - Feeding the Cows](https://usaco.org/index.php?page=viewproblem2&cpid=1252&lang=zh)
  训练点：贪心放置，覆盖范围，构造输出。
- [ ] [USACO Bronze 2022 December P3 - Reverse Engineering](https://usaco.org/index.php?page=viewproblem2&cpid=1253&lang=zh)
  训练点：条件筛选，递归消元，模拟推理过程。
- [ ] [USACO Bronze 2022 US Open P2 - Counting Liars](https://usaco.org/index.php?page=viewproblem2&cpid=1228&lang=zh)
  训练点：枚举答案点，区间约束，最少矛盾数。
- [ ] [USACO Bronze 2022 US Open P3 - Alchemy](https://usaco.org/index.php?page=viewproblem2&cpid=1229&lang=zh)
  训练点：资源递推，配方消耗，递归模拟。
- [ ] [USACO Bronze 2022 February P1 - Sleeping in Class](https://usaco.org/index.php?page=viewproblem2&cpid=1203&lang=zh)
  训练点：目标和枚举，分段验证，因子思维。
- [ ] [USACO Bronze 2022 February P2 - Photoshoot 2](https://usaco.org/index.php?page=viewproblem2&cpid=1204&lang=zh)
  训练点：相对顺序，贪心交换，位置数组。
- [ ] [USACO Bronze 2022 February P3 - Blocks](https://usaco.org/index.php?page=viewproblem2&cpid=1205&lang=zh)
  训练点：移动模拟，目标位置，构造操作。
- [ ] [USACO Bronze 2022 January P2 - Non-Transitive Dice](https://usaco.org/index.php?page=viewproblem2&cpid=1180&lang=zh)
  训练点：小范围枚举，比较计数，搜索候选。
- [ ] [USACO Bronze 2022 January P3 - Drought](https://usaco.org/index.php?page=viewproblem2&cpid=1181&lang=zh)
  训练点：贪心削减，奇偶约束，前后影响。
- [ ] [USACO Bronze 2021 December P1 - Lonely Photo](https://usaco.org/index.php?page=viewproblem2&cpid=1155&lang=zh)
  训练点：连续段贡献，组合计数，避免重复统计。
- [ ] [USACO Bronze 2021 December P2 - Air Cownditioning](https://usaco.org/index.php?page=viewproblem2&cpid=1156&lang=zh)
  训练点：差值数组，连续同号段，最少操作。

### T3：Silver 入门与 CSP-J 第三题转化

- [ ] [USACO Silver 2025 US Open P1 - Sequence Construction](https://usaco.org/index.php?page=viewproblem2&cpid=1518&lang=zh)
  训练点：构造验证，序列性质，先猜结论再证明。
- [ ] [USACO Silver 2025 February P1 - The Best Lineup](https://usaco.org/index.php?page=viewproblem2&cpid=1494&lang=zh)
  训练点：排序与选择，字典序目标，贪心正确性。
- [ ] [USACO Silver 2025 January P1 - Cow Checkups](https://usaco.org/index.php?page=viewproblem2&cpid=1470&lang=zh)
  训练点：区间贡献，分类计数，从 Bronze 思路升级。
- [ ] [USACO Silver 2024 December P1 - Cake Game](https://usaco.org/index.php?page=viewproblem2&cpid=1446&lang=zh)
  训练点：博弈规律，前后缀贡献，奇偶讨论。
- [ ] [USACO Silver 2024 US Open P1 - Bessie's Interview](https://usaco.org/index.php?page=viewproblem2&cpid=1422&lang=zh)
  训练点：优先队列，事件模拟，最后一层状态。
- [ ] [USACO Silver 2024 January P1 - Cowmpetency](https://usaco.org/index.php?page=viewproblem2&cpid=1374&lang=zh)
  训练点：约束填数，贪心构造，非法判定。
- [ ] [USACO Silver 2023 December P1 - Bovine Acrobatics](https://usaco.org/index.php?page=viewproblem2&cpid=1350&lang=zh)
  训练点：排序贪心，双指针匹配，批量处理。
- [ ] [USACO Silver 2023 US Open P1 - Milk Sum](https://usaco.org/index.php?page=viewproblem2&cpid=1326&lang=zh)
  训练点：排序贡献，单点修改查询，前缀和。
- [ ] [USACO Silver 2023 January P1 - Find and Replace](https://usaco.org/index.php?page=viewproblem2&cpid=1278&lang=zh)
  训练点：字符映射，图上环，操作次数分析。
- [ ] [USACO Silver 2023 January P2 - Following Directions](https://usaco.org/index.php?page=viewproblem2&cpid=1279&lang=zh)
  训练点：网格路径，影响传播，修改后的增量更新。
- [ ] [USACO Silver 2022 December P1 - Barn Tree](https://usaco.org/index.php?page=viewproblem2&cpid=1254&lang=zh)
  训练点：树上 DFS，平均值转移，操作顺序。
- [ ] [USACO Silver 2022 February P1 - Redistributing Gifts](https://usaco.org/index.php?page=viewproblem2&cpid=1206&lang=zh)
  训练点：偏好关系，可达性闭包，选择最优礼物。
- [ ] [USACO Silver 2022 January P1 - Searching for Soulmates](https://usaco.org/index.php?page=viewproblem2&cpid=1182&lang=zh)
  训练点：反向贪心，状态缩小，奇偶处理。
- [ ] [USACO Silver 2021 December P1 - Closest Cow Wins](https://usaco.org/index.php?page=viewproblem2&cpid=1158&lang=zh)
  训练点：区间拆分，候选收益，排序取最大。
- [ ] [USACO Silver 2021 February P1 - Comfortable Cows](https://usaco.org/index.php?page=viewproblem2&cpid=1110&lang=zh)
  训练点：网格增量维护，队列传播，局部更新。
- [ ] [USACO Silver 2021 January P2 - No Time to Paint](https://usaco.org/index.php?page=viewproblem2&cpid=1087&lang=zh)
  训练点：前后缀预处理，区间删除查询，栈思想。
- [ ] [USACO Silver 2020 December P1 - Cowntagion](https://usaco.org/index.php?page=viewproblem2&cpid=1062&lang=zh)
  训练点：树上扩散，倍增增长，DFS 统计。
- [ ] [USACO Silver 2020 US Open P1 - Social Distancing](https://usaco.org/index.php?page=viewproblem2&cpid=1038&lang=zh)
  训练点：二分答案，区间贪心检查，最大最小距离。

### T4：Silver 综合题与部分分训练

- [ ] [USACO Silver 2025 US Open P3 - Ski Slope](https://usaco.org/index.php?page=viewproblem2&cpid=1520&lang=zh)
  训练点：复杂状态建模，先写暴力，再拆特殊性质。
- [ ] [USACO Silver 2025 January P3 - Table Recovery](https://usaco.org/index.php?page=viewproblem2&cpid=1472&lang=zh)
  训练点：结构还原，约束推导，构造正确性。
- [ ] [USACO Silver 2024 December P3 - 2D Conveyor Belt](https://usaco.org/index.php?page=viewproblem2&cpid=1448&lang=zh)
  训练点：网格图，反向搜索，动态状态维护。
- [ ] [USACO Silver 2024 US Open P3 - The 'Winning' Gene](https://usaco.org/index.php?page=viewproblem2&cpid=1424&lang=zh)
  训练点：字符串统计，区间贡献，复杂度压缩。
- [ ] [USACO Silver 2024 February P3 - Moorbles](https://usaco.org/index.php?page=viewproblem2&cpid=1400&lang=zh)
  训练点：贪心策略，倒推安全线，多轮决策。
- [ ] [USACO Silver 2023 December P3 - Target Practice](https://usaco.org/index.php?page=viewproblem2&cpid=1352&lang=zh)
  训练点：模拟优化，事件影响，修改一次后的收益。
- [ ] [USACO Silver 2023 US Open P3 - Pareidolia](https://usaco.org/index.php?page=viewproblem2&cpid=1328&lang=zh)
  训练点：自动机思想，动态规划，字符串匹配计数。
- [ ] [USACO Silver 2022 December P3 - Range Reconstruction](https://usaco.org/index.php?page=viewproblem2&cpid=1256&lang=zh)
  训练点：区间信息还原，增量构造，合法性维护。
- [ ] [USACO Silver 2021 February P3 - Just Green Enough](https://usaco.org/index.php?page=viewproblem2&cpid=1112&lang=zh)
  训练点：二维计数，降维枚举，前缀思想。
- [ ] [USACO Silver 2020 February P3 - Clock Tree](https://usaco.org/index.php?page=viewproblem2&cpid=1016&lang=zh)
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
