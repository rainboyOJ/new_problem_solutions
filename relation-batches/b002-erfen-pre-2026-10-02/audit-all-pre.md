# b002 全量审核清单（pre：14 对全部审核）

- 关系类型：pre（有向：前置 A → 当前题 B，单侧写入 B 的 frontmatter）
- 判断分值：step=A_is_step_to_B（A 是否为 B 的入门模板/台阶）、harder=B_harder_than_A、same_core=核心模型同族
- 写入规则：step≥0.8 且 harder≥0.6 且 same_core≥0.5（严格档，用户选定）
- 已被父会话复核排除：4135→P2680、P1163→P2680、P1182→P2680（核心模型不同族：线性聚合 vs 树上差分/LCA）
- 审核方须独立读题解原文核对，不得只核对 reason 文本；无原文依据判 uncertain。

## p01　noi_openjudge/ch0111-02 → luogu/P1024
- 写入的 reason：先用「变号区间内二分」求单个零点的入门模板，再把同一手法用到三次方程：扫描整数端点与开单位区间、对每个变号区间分别二分逼近三个实根。
- 判断分值：step=0.88 harder=0.96 same_core=0.88
- 材料：`materials/noi_openjudge__ch0111-02.md`、`materials/luogu__P1024.md`
- 题解原文：`problems/noi_openjudge/ch0111-02/index.md`、`problems/luogu/P1024/index.md`

## p02　luogu/P2440 → luogu/P2985
- 写入的 reason：先掌握「二分答案 + 一遍线性 check」模板（P2440 用 floor 计数判定），再把 check 换成每天贪心吃到刚达标的模拟判定。
- 判断分值：step=0.83 harder=0.88 same_core=0.9
- 材料：`materials/luogu__P2440.md`、`materials/luogu__P2985.md`
- 题解原文：`problems/luogu/P2440/index.md`、`problems/luogu/P2985/index.md`

## p03　luogu/P2440 → roj/19999
- 写入的 reason：先掌握二分答案与计数判定的写法，再处理把判定式变形为两个序列比较、排序后双指针计数求第 k 大的问题。
- 判断分值：step=0.82 harder=0.96 same_core=0.78
- 材料：`materials/luogu__P2440.md`、`materials/roj__19999.md`
- 题解原文：`problems/luogu/P2440/index.md`、`problems/roj/19999/index.md`

## p04　luogu/P2440 → luogu/P1462
- 写入的 reason：先掌握二分答案 + 单调 check 模板，再把 check 换成受限最短路（Dijkstra 判断可达性）。
- 判断分值：step=0.86 harder=0.94 same_core=0.9
- 材料：`materials/luogu__P2440.md`、`materials/luogu__P1462.md`
- 题解原文：`problems/luogu/P2440/index.md`、`problems/luogu/P1462/index.md`

## p05　luogu/P2440 → luogu/P2370
- 写入的 reason：先掌握二分答案 + 计数 check，再把 check 换成 0/1 背包可行性判定。
- 判断分值：step=0.89 harder=0.94 same_core=0.89
- 材料：`materials/luogu__P2440.md`、`materials/luogu__P2370.md`
- 题解原文：`problems/luogu/P2440/index.md`、`problems/luogu/P2370/index.md`

## p06　OpenJ_Bailian/4135 → luogu/P2370
- 写入的 reason：先掌握划分型二分（不超上限的分段判定），再处理判定函数换成 0/1 背包的可行性检验。
- 判断分值：step=0.86 harder=0.87 same_core=0.93
- 材料：`materials/OpenJ_Bailian__4135.md`、`materials/luogu__P2370.md`
- 题解原文：`problems/OpenJ_Bailian/4135/index.md`、`problems/luogu/P2370/index.md`

## p07　OpenJ_Bailian/4135 → luogu/P1083
- 写入的 reason：先掌握二分答案 + 线性 check（4135 用贪心分段），再把 check 换成差分数组判断前 k 份订单是否可满足。
- 判断分值：step=0.82 harder=0.82 same_core=0.84
- 材料：`materials/OpenJ_Bailian__4135.md`、`materials/luogu__P1083.md`
- 题解原文：`problems/OpenJ_Bailian/4135/index.md`、`problems/luogu/P1083/index.md`

## p08　OpenJ_Bailian/4135 → luogu/P1314
- 写入的 reason：先掌握二分答案 + O(n) check，再把 check 换成前缀和计算检验值 y(W)。
- 判断分值：step=0.83 harder=0.85 same_core=0.9
- 材料：`materials/OpenJ_Bailian__4135.md`、`materials/luogu__P1314.md`
- 题解原文：`problems/OpenJ_Bailian/4135/index.md`、`problems/luogu/P1314/index.md`

## p09　OpenJ_Bailian/4135 → luogu/P1948
- 写入的 reason：先掌握二分答案 + 线性判定，再把 check 换成 0-1 BFS 求最短路。
- 判断分值：step=0.84 harder=0.91 same_core=0.85
- 材料：`materials/OpenJ_Bailian__4135.md`、`materials/luogu__P1948.md`
- 题解原文：`problems/OpenJ_Bailian/4135/index.md`、`problems/luogu/P1948/index.md`

## p10　POJ/3122 → luogu/P1083
- 写入的 reason：先掌握二分的单调性判定模板（Pie 用切块计数验证），再把 check 换成差分数组的订单可行性判定。
- 判断分值：step=0.84 harder=0.87 same_core=0.85
- 材料：`materials/POJ__3122.md`、`materials/luogu__P1083.md`
- 题解原文：`problems/POJ/3122/index.md`、`problems/luogu/P1083/index.md`

## p11　POJ/3122 → luogu/P1419
- 写入的 reason：先掌握二分答案的单调性判定模板，再处理实数域二分平均值 + 前缀和/单调队列判定。
- 判断分值：step=0.86 harder=0.94 same_core=0.88
- 材料：`materials/POJ__3122.md`、`materials/luogu__P1419.md`
- 题解原文：`problems/POJ/3122/index.md`、`problems/luogu/P1419/index.md`

## p12　luogu/P1163 → luogu/P1314
- 写入的 reason：先掌握实数二分 + 逐月模拟的判定写法，再处理用前缀和计算 y(W) 的整数域二分。
- 判断分值：step=0.84 harder=0.93 same_core=0.91
- 材料：`materials/luogu__P1163.md`、`materials/luogu__P1314.md`
- 题解原文：`problems/luogu/P1163/index.md`、`problems/luogu/P1314/index.md`

## p13　luogu/P1163 → luogu/P1948
- 写入的 reason：先掌握二分答案 + 模拟判定，再把 check 换成 0-1 BFS 最短路判定。
- 判断分值：step=0.8 harder=0.93 same_core=0.72
- 材料：`materials/luogu__P1163.md`、`materials/luogu__P1948.md`
- 题解原文：`problems/luogu/P1163/index.md`、`problems/luogu/P1948/index.md`

## p14　luogu/P1182 → luogu/P1948
- 写入的 reason：先掌握二分答案 + 贪心分段判定，再把 check 换成 0-1 BFS 最短路判定。
- 判断分值：step=0.85 harder=0.9 same_core=0.85
- 材料：`materials/luogu__P1182.md`、`materials/luogu__P1948.md`
- 题解原文：`problems/luogu/P1182/index.md`、`problems/luogu/P1948/index.md`
