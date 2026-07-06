---
title: "CSP-S 历年真题题单"
description: "整理 CSP-S 提高级第二轮全国真题，按年份和题号顺序排列。"
---

# CSP-S 历年真题题单

本题单整理 CSP-S 提高级第二轮全国真题。目前收录 2019 到 2025 年，共 30 题。

说明：

- 只收录 CSP-S 全国统一题，不收录江西、山东等地方题。
- 2019 年按两日比赛顺序列出 `D1T1` 到 `D2T3`，之后年份按 `T1` 到 `T4` 列出。
- 建议训练时整年限时完成，再按题目复盘。

## 2019 CSP-S

- [x] D1T1 格雷码 [[problem: luogu,P5657]]
  - 前置训练：[P7071 优秀的拆分](/problems/luogu/P7071)
  - 训练目的：先理解二进制位权、按位拆分和从高位到低位构造，再接受 `k xor (k >> 1)` 的格雷码公式。
- [x] D1T2 括号树 [[problem: luogu,P5658]]
  - 前置训练：[P1739 表达式括号匹配](/problems/luogu/P1739)、[P8815 逻辑表达式](/problems/luogu/P8815)、[P1122 最大子树和](/problems/luogu/P1122)
  - 训练目的：先会用栈处理括号，再把“线性栈状态”搬到根到当前点的 DFS 路径上。
- [x] D1T3 树上的数 [[problem: luogu,P5659]]
  - 前置训练：[P3367 并查集模板](/problems/luogu/P3367)、[P1197 星球大战](/problems/luogu/P1197)、[P1122 最大子树和](/problems/luogu/P1122)
  - 训练目的：先掌握并查集维护连通块和树 DFS，再理解本题按数字贪心选择终点时如何维护局部可删边约束。
- [x] D2T1 Emiya 家今天的饭 [[problem: luogu,P5664]]
  - 前置训练：[P1164 小 A 点菜](/problems/luogu/P1164)、[P1077 摆花](/problems/luogu/P1077)、[P1450 硬币购物](/problems/luogu/P1450)
  - 训练目的：先练“方案数 DP”和“从总方案里扣坏方案”，再理解按食材枚举多数者的差值 DP。
- [x] D2T2 划分 [[problem: luogu,P5665]]
  - 前置训练：[P1182 数列分段](/problems/luogu/P1182)、[P1083 借教室](/problems/luogu/P1083)、[P1886 单调队列](/problems/luogu/P1886)
  - 训练目的：先理解分段和前缀和检查，再学习用单调结构维护最优上一段结尾。
- [x] D2T3 树的重心 [[problem: luogu,P5666]]
  - 前置训练：[P1122 最大子树和](/problems/luogu/P1122)、[P3379 LCA](/problems/luogu/P3379)、[P1395 会议](/problems/luogu/P1395)
  - 训练目的：先补树 DFS、倍增和“树上中心点”直觉，再单独讲重心定义、最大子树链和换根枚举每条边两侧连通块。

## 2020 CSP-S

- [x] T1 儒略日 [[problem: luogu,P7075]]
  - 前置训练：[P8831 儒略历](/problems/luogu/P8831)、本题内暴力版
  - 训练目的：先练日期分段模拟，再把逐日推进优化成按年份/月分段反推。
- [x] T2 动物园 [[problem: luogu,P7076]]
  - 前置训练：[P7071 优秀的拆分](/problems/luogu/P7071)、[P5657 格雷码](/problems/luogu/P5657)
  - 训练目的：先熟悉二进制位含义、按位或和自由位计数，再理解“危险位”和可选动物数量。
- [x] T3 函数调用 [[problem: luogu,P7077]]
  - 前置训练：[P1113 杂务](/problems/luogu/P1113)、[P1038 神经网络](/problems/luogu/P1038)、[P1807 最长路](/problems/luogu/P1807)
  - 训练目的：先掌握拓扑序上的 DP/模拟，再理解函数调用图里反向求乘法效果、正向推加法贡献。
- [x] T4 贪吃蛇 [[problem: luogu,P7078]]
  - 前置训练：[P1090 合并果子](/problems/luogu/P1090)、[P1199 三国游戏](/problems/luogu/P1199)、[P1190 接水问题](/problems/luogu/P1190)
  - 训练目的：先训练“每步最优选择”的证明和队列/堆模拟，再理解必吃局面与冒险吃的递归反推。

## 2021 CSP-S

- [x] T1 廊桥分配 [[problem: luogu,P7913]]
  - 前置训练：[P1190 接水问题](/problems/luogu/P1190)、[P1093 奖学金](/problems/luogu/P1093)
  - 训练目的：先会用小根堆维护最早空闲资源，再枚举国内/国际廊桥数量分配。
- [x] T2 括号序列 [[problem: luogu,P7914]]
  - 前置训练：[P1044 栈](/problems/luogu/P1044)、[P1063 能量项链](/problems/luogu/P1063)、[P1880 石子合并](/problems/luogu/P1880)
  - 训练目的：先掌握括号计数和区间 DP 的“最后一次合并/最外层结构”，再处理超级括号序列的多类状态。
- [x] T3 回文 [[problem: luogu,P7915]]
  - 前置训练：[P1147 连续正整数和](/problems/luogu/P1147)、[P11229 小木棍](/problems/luogu/P11229)、[P1008 三连击](/problems/luogu/P1008)
  - 训练目的：先练双指针和构造可行性判断，再理解固定首步后用两端配对构造操作串。
- [x] T4 交通规划 [[problem: luogu,P7916]]
  - 前置训练：[P1345 奶牛的电信](/problems/luogu/P1345)、[P1339 Heat Wave](/problems/luogu/P1339)、[P1880 石子合并](/problems/luogu/P1880)
  - 训练目的：先分别掌握最小割、最短路和环形区间 DP，再理解平面图割线转对偶图路径。

## 2022 CSP-S

- [x] T1 假期计划 [[problem: luogu,P8817]]
  - 前置训练：[P1135 奇怪的电梯](/problems/luogu/P1135)、[P1144 最短路计数](/problems/luogu/P1144)、[P1126 机器人搬重物](/problems/luogu/P1126)
  - 训练目的：先会做 BFS/状态 BFS，再学习为每个中间点保留少量高分候选来压缩枚举。
- [x] T2 策略游戏 [[problem: luogu,P8818]]
  - 前置训练：[P1816 忠诚](/problems/luogu/P1816)、[P9750 一元二次方程](/problems/luogu/P9750)、[P14360 多边形](/problems/luogu/P14360)
  - 训练目的：先掌握区间最值查询和分类讨论，再把正数、负数、零对乘积极值的影响分开处理。
- [x] T3 星战 [[problem: luogu,P8819]]
  - 前置训练：[P3370 字符串哈希](/problems/luogu/P3370)、[P1197 星球大战](/problems/luogu/P1197)
  - 训练目的：先理解哈希把复杂状态压成可比较数值，再学习用增删边贡献维护全图是否满足条件。
- [x] T4 数据传输 [[problem: luogu,P8820]]
  - 前置训练：[P3379 LCA](/problems/luogu/P3379)、[P1339 Heat Wave](/problems/luogu/P1339)、[P2146 软件包管理器](/problems/luogu/P2146)、[P3390 矩阵快速幂](/problems/luogu/P3390)
  - 训练目的：先补树上路径拆分、最短路转移和矩阵乘法思想，再理解把路径 DP 压成矩阵并在线段树/重链上合并。

## 2023 CSP-S

- [x] T1 密码锁 [[problem: luogu,P9752]]
  - 前置训练：[P1008 三连击](/problems/luogu/P1008)、[P1039 侦探推理](/problems/luogu/P1039)
  - 训练目的：先练枚举候选并逐条检查限制，再枚举所有五位密码判断能否解释所有记录。
- [x] T2 消消乐 [[problem: luogu,P9753]]
  - 前置训练：[P1165 日志分析](/problems/luogu/P1165)、[P8306 Trie 模板](/problems/luogu/P8306)、[P3370 字符串哈希](/problems/luogu/P3370)
  - 训练目的：先会维护栈状态和 Trie，再理解“两个相同前缀消除状态之间的子串可完全消掉”。
- [x] T3 结构体 [[problem: luogu,P9754]]
  - 前置训练：[P7911 网络连接](/problems/luogu/P7911)、[P1022 计算器的改良](/problems/luogu/P1022)、[P1055 ISBN 号码](/problems/luogu/P1055)
  - 训练目的：先练字符串解析、格式校验和递归访问路径，再处理结构体大小、成员偏移和地址反查。
- [x] T4 种树 [[problem: luogu,P9755]]
  - 前置训练：[P1182 数列分段](/problems/luogu/P1182)、[P1250 种树](/problems/luogu/P1250)、[P1090 合并果子](/problems/luogu/P1090)
  - 训练目的：先掌握二分答案和按截止时间贪心，再理解把每个点转成最晚种植日后的树上调度。

## 2024 CSP-S

- [x] T1 决斗 [[problem: luogu,P11231]]
  - 前置训练：[P1093 奖学金](/problems/luogu/P1093)、[P1803 线段覆盖](/problems/luogu/P1803)
  - 训练目的：先练排序后贪心选择，再理解强牌匹配弱牌时为什么双指针最优。
- [x] T2 超速检测 [[problem: luogu,P11232]]
  - 前置训练：[P1803 线段覆盖](/problems/luogu/P1803)、[P1182 数列分段](/problems/luogu/P1182)、[P1314 聪明的质监员](/problems/luogu/P1314)
  - 训练目的：先把条件转成区间，再用区间覆盖贪心选最少测速仪。
- [x] T3 染色 [[problem: luogu,P11233]]
  - 前置训练：[P1216 数字三角形](/problems/luogu/P1216)、[P11230 接龙](/problems/luogu/P11230)、[P1531 I Hate It](/problems/luogu/P1531)
  - 训练目的：先理解 DP 状态压缩和“只保留关键历史”，再学习用数据结构维护一批状态的最优值。
- [x] T4 擂台游戏 [[problem: luogu,P11234]]
  - 前置训练：[P1087 FBI 树](/problems/luogu/P1087)、[P8089 Color](/problems/luogu/P8089)、[P1047 校门外的树](/problems/luogu/P1047)
  - 训练目的：先熟悉二叉树递归和差分，再理解每个叶子可能夺冠的前缀区间如何统计。

## 2025 CSP-S

- [x] T1 社团招新 [[problem: luogu,P14361]]
  - 前置训练：[P1093 奖学金](/problems/luogu/P1093)、[P11231 决斗](/problems/luogu/P11231)
  - 训练目的：先练排序和匹配贪心，再理解先让每人去最满意部门、再按最小损失修正超员部门。
- [x] T2 道路修复 [[problem: luogu,P14362]]
  - 前置训练：[P3366 最小生成树](/problems/luogu/P3366)、[P1194 买礼物](/problems/luogu/P1194)、[P9235 网络稳定性](/problems/luogu/P9235)
  - 训练目的：先掌握 MST 和路径替换性质，再理解为什么每次 Kruskal 只需保留原图 MST 边。
- [x] T3 谐音替换 [[problem: luogu,P14363]]
  - 前置训练：[P8306 Trie 模板](/problems/luogu/P8306)、[P3374 树状数组 1](/problems/luogu/P3374)、[P1972 HH 的项链](/problems/luogu/P1972)、[P3808 AC 自动机模板](/problems/luogu/P3808)
  - 训练目的：先补 Trie、树状数组和离线计数，再学习 AC 自动机 fail 树上按长度阈值批量统计。
- [x] T4 员工招聘 [[problem: luogu,P14364]]
  - 前置训练：[P1025 数的划分](/problems/luogu/P1025)、[P1077 摆花](/problems/luogu/P1077)、[P11362 遗失的赋值](/problems/luogu/P11362)
  - 训练目的：先掌握组合计数型 DP，再理解按失败人数做状态、把大耐心人群 pending 延后结算。

## 使用建议

### 第一遍：整年模拟

按年份做整套题，目标是看真实得分：

```text
T1：必须稳定 AC
T2：尽量 AC，注意证明和边界
T3：先拿暴力分，再补正解
T4：先写可得分做法，不空题
```

2019 年有 6 题，建议拆成两天训练：

```text
D1：限时完成 D1T1 到 D1T3
D2：限时完成 D2T1 到 D2T3
```

### 第二遍：题型复盘

做完一套后，把每题按下面格式复盘：

```text
题号：
考点：
暴力分怎么拿：
正解关键观察：
本题最容易错在哪里：
```

### 第三遍：近三年重点重做

2023、2024、2025 三年的 `T2`、`T3`、`T4` 最适合用于冲刺训练。要求不是只看题解，而是补齐：

```text
暴力代码
正解代码
复杂度证明
容易出错的数据
```
