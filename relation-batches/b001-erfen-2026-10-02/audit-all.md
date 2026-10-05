# b001 全量审核清单（写入后审核：15 对全部审核）

- 随机种子：27212（本次为全量审核，不抽样）
- 相似标准：核心模型相同 + 判定过程/状态设计高度相近 + 关键观察可迁移，三条同时满足；只共享二分答案框架/标签的一律 fail。
- 本清单由撰写流程生成；审核方须独立读题解原文核对，不得只核对 reason 文本。

## w01　OpenJ_Bailian/4135 ~ luogu/P1182
- 写入的 reason：同为二分最大段和+贪心分段判定：4135 按月度上限分段计数，P1182 按段和上限分段计数，check 结构可互相套用。
- 判断依据（Jev noul）：shared_core=0.88 check_similar=0.87 only_label=0.19
- 材料：`materials/OpenJ_Bailian__4135.md`、`materials/luogu__P1182.md`
- 题解原文：`problems/OpenJ_Bailian/4135/index.md`、`problems/luogu/P1182/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w02　luogu/P1824 ~ luogu/P2440
- 写入的 reason：同为最大化最小值的二分答案，判定均为单遍线性贪心扫描：P1824 按最小间距放牛，P2440 按长度计段数。
- 判断依据（Jev noul）：shared_core=0.88 check_similar=0.72 only_label=0.1
- 材料：`materials/luogu__P1824.md`、`materials/luogu__P2440.md`
- 题解原文：`problems/luogu/P1824/index.md`、`problems/luogu/P2440/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w03　luogu/P1824 ~ luogu/P2678
- 写入的 reason：同为最大化最小值+贪心扫描判定：P1824 按最小间距尽早放牛，P2678 按最短跳跃距离统计最少移石数，判定过程可互相套用。
- 判断依据（Jev noul）：shared_core=0.94 check_similar=0.92 only_label=0.07
- 材料：`materials/luogu__P1824.md`、`materials/luogu__P2678.md`
- 题解原文：`problems/luogu/P1824/index.md`、`problems/luogu/P2678/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w04　luogu/P1824 ~ noi_openjudge/ch0111-10
- 写入的 reason：同为二分最小距离+从左到右贪心扫描判定：P1824 放置奶牛，ch0111-10 统计需移走的石头数，判定同型。
- 判断依据（Jev noul）：shared_core=0.88 check_similar=0.89 only_label=0.1
- 材料：`materials/luogu__P1824.md`、`materials/noi_openjudge__ch0111-10.md`
- 题解原文：`problems/luogu/P1824/index.md`、`problems/noi_openjudge/ch0111-10/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w05　luogu/P1824 ~ usaco/1038
- 写入的 reason：同型题：都是二分最小间距+从左到右尽量靠左放牛的贪心判定，唯一差别是牛舍为点还是区间。
- 判断依据（Jev noul）：shared_core=0.94 check_similar=0.9 only_label=0.07
- 材料：`materials/luogu__P1824.md`、`materials/usaco__1038.md`
- 题解原文：`problems/luogu/P1824/index.md`、`problems/usaco/1038/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w06　luogu/P1843 ~ luogu/P1873
- 写入的 reason：同为二分答案+单调判定：P1843 检查烘衣机总秒数是否不超过时间，P1873 检查木材总量是否达标，判定都是对数组的线性聚合比较。
- 判断依据（Jev noul）：shared_core=0.86 check_similar=0.71 only_label=0.14
- 材料：`materials/luogu__P1843.md`、`materials/luogu__P1873.md`
- 题解原文：`problems/luogu/P1843/index.md`、`problems/luogu/P1873/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w07　luogu/P1873 ~ luogu/P2440
- 写入的 reason：同为最大化最小值的二分答案+线性聚合判定：P1873 求和判断木材达标，P2440 计数判断段数达标，check 可互相套用。
- 判断依据（Jev noul）：shared_core=0.9 check_similar=0.93 only_label=0.11
- 材料：`materials/luogu__P1873.md`、`materials/luogu__P2440.md`
- 题解原文：`problems/luogu/P1873/index.md`、`problems/luogu/P2440/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w08　luogu/P1873 ~ noi_openjudge/ch0111-04
- 写入的 reason：同为二分答案+单调判定：网线主管计数可切段数，P1873 求和木材量，判定都是单遍线性聚合比较。
- 判断依据（Jev noul）：shared_core=0.88 check_similar=0.89 only_label=0.15
- 材料：`materials/luogu__P1873.md`、`materials/noi_openjudge__ch0111-04.md`
- 题解原文：`problems/luogu/P1873/index.md`、`problems/noi_openjudge/ch0111-04/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w09　luogu/P2440 ~ POJ/3122
- 写入的 reason：同为二分长度/体积+切分计数判定：P2440 数木材段数，3122 数派的块数，check 都是 floor 聚合计数。
- 判断依据（Jev noul）：shared_core=0.9 check_similar=0.93 only_label=0.1
- 材料：`materials/luogu__P2440.md`、`materials/POJ__3122.md`
- 题解原文：`problems/luogu/P2440/index.md`、`problems/POJ/3122/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w10　luogu/P2440 ~ noi_openjudge/ch0111-04
- 写入的 reason：同型题：都是二分长度+可切段数计数判定（最大化最小段长），判定函数一致。
- 判断依据（Jev noul）：shared_core=0.95 check_similar=0.96 only_label=0.11
- 材料：`materials/luogu__P2440.md`、`materials/noi_openjudge__ch0111-04.md`
- 题解原文：`problems/luogu/P2440/index.md`、`problems/noi_openjudge/ch0111-04/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w11　luogu/P2678 ~ noi_openjudge/ch0111-10
- 写入的 reason：同型题（跳石头）：二分最短跳跃距离+贪心统计最少移走石头数，判定与关键观察完全一致。
- 判断依据（Jev noul）：shared_core=0.97 check_similar=0.97 only_label=0.07
- 材料：`materials/luogu__P2678.md`、`materials/noi_openjudge__ch0111-10.md`
- 题解原文：`problems/luogu/P2678/index.md`、`problems/noi_openjudge/ch0111-10/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w12　luogu/P2678 ~ usaco/1038
- 写入的 reason：同为最大化最小值+贪心扫描判定：P2678 二分跳跃距离统计移石数，1038 二分间距放置奶牛，判定均为单遍贪心。
- 判断依据（Jev noul）：shared_core=0.88 check_similar=0.85 only_label=0.09
- 材料：`materials/luogu__P2678.md`、`materials/usaco__1038.md`
- 题解原文：`problems/luogu/P2678/index.md`、`problems/usaco/1038/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w13　luogu/P4951 ~ POJ/2976
- 写入的 reason：同为 01 分数规划：二分比值 x 并把分式判定转为 Σ(参数+x·参数) 的线性判定；差别只在验证结构（2976 取最大 n-k 项求和，P4951 求最小生成树）。
- 判断依据（Jev noul）：shared_core=0.88 check_similar=0.78 only_label=0.09
- 材料：`materials/luogu__P4951.md`、`materials/POJ__2976.md`
- 题解原文：`problems/luogu/P4951/index.md`、`problems/POJ/2976/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w14　noi_openjudge/ch0111-04 ~ POJ/3122
- 写入的 reason：同为二分长度/体积+floor 切分计数判定：网线主管数可切段数，3122 数可切块数，判定同型。
- 判断依据（Jev noul）：shared_core=0.89 check_similar=0.92 only_label=0.11
- 材料：`materials/noi_openjudge__ch0111-04.md`、`materials/POJ__3122.md`
- 题解原文：`problems/noi_openjudge/ch0111-04/index.md`、`problems/POJ/3122/index.md`
- 结论：__（pass / fail / uncertain + 原因）__

## w15　noi_openjudge/ch0111-10 ~ usaco/1038
- 写入的 reason：同为最大化最小值+贪心扫描判定：跳房子统计需移走的石头数，1038 放置奶牛，判定过程可互相套用。
- 判断依据（Jev noul）：shared_core=0.88 check_similar=0.86 only_label=0.09
- 材料：`materials/noi_openjudge__ch0111-10.md`、`materials/usaco__1038.md`
- 题解原文：`problems/noi_openjudge/ch0111-10/index.md`、`problems/usaco/1038/index.md`
- 结论：__（pass / fail / uncertain + 原因）__
