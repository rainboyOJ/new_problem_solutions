# b001 人工复核包（验证点 1/3：专题归属逐题确认）

> 用法：逐题判断「实际解法是否真的是二分答案（或其等价的单调性二分）」。
> 同意 → 在结论列打 ✅；不同意/存疑 → 打 ❌ 或 ⚠️ 并写一句原因，然后把文件发回给我即可。
> 只需要看每题的「解法一句话」和「思路开头」，不需要通读全文。
> **审核状态（2026-10-02，独立审核 AI 填写）**：44 题已逐题读原文核对，结论见各题「结论」行，机器可读版本为 `review-topic-verdicts.jsonl`；共 ✅ 42 题 / ⚠️ 1 题（luogu/CF912E）/ ❌ 1 题（luogu/P8814）。标 ⚠️/❌ 的两题及「摘录为空」的 8 题请重点终审。

## OpenJ_Bailian/4135　Monthly Expense　
- **解法一句话**：(无)
- **思路开头**：
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/OpenJ_Bailian__4135.md`；正文：`problems/OpenJ_Bailian/4135/index.md`
- 结论：✅ 二分答案 X + 贪心分段判定（最小化最大段和）；摘录为空但原文完整

## codeforces/912E　Prime Gift　
- **解法一句话**：把质数拆成两组生成所有乘积，二分答案并双指针统计不超过它的乘积对数。
- **思路开头**：给定至多 16 个质数，求所有质因子都来自该集合的第 `k` 小正整数，答案不超过 $10^{18}$。 ### 思路 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/codeforces__912E.md`；正文：`problems/codeforces/912E/index.md`
- 结论：✅ 二分答案 limit + 双指针计数乘积对数

## luogu/P1083　[NOIP 2012 提高组] 借教室　
- **解法一句话**：把前 k 份订单是否可满足做成差分检查函数，再二分第一份出问题的订单编号。
- **思路开头**：未来有 `n` 天教室资源，第 `i` 天有 `r_i` 个教室可借。 有 `m` 份订单，按顺序处理。 每份订单 `(d, s, t)` 表示从第 `s` 天到第 `t` 天，每天都要借 `d` 个教室。
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1083.md`；正文：`problems/luogu/P1083/index.md`
- 结论：✅ 二分第一份失败订单 + 差分检查函数

## luogu/P11364　[NOIP2024] 树上查询　
- **解法一句话**：把连续编号区间的 LCA 深度转成相邻 LCA 深度数组的区间最小值，再离线二分答案。
- **思路开头**：给定一棵以 `1` 为根的树，节点编号为 `1..n`。节点深度定义为从根到该节点路径上的节点数量。 `LCA*(l, r)` 表示编号在 `[l, r]` 内所有节点的最近公共祖先。每次询问给出 `l, r, k`，要在 `[l, r]` 的所有长度至少为 `k` 的连续编号子区间 `[l', r']` 中，求 `dep(LCA*(l', r'))` 的最大值。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P11364.md`；正文：`problems/luogu/P11364/index.md`
- 结论：✅ 二分答案 LCA 深度 + 并行二分/线段树判定

## luogu/P1163　银行贷款　
- **解法一句话**：二分月利率，逐月模拟计息与还款后的剩余本金，使最终余额逼近零。
- **思路开头**：已知贷款本金、每月还款额和还清所需月数，求按月累计的利率，以百分数输出并保留一位小数。 ### 思路 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1163.md`；正文：`problems/luogu/P1163/index.md`
- 结论：✅ 实数域二分利率 + 逐月模拟余额

## luogu/P1182　数列分段 Section II　
- **解法一句话**：二分最大段和，用从左到右尽量装满当前段的贪心检查最少段数。
- **思路开头**：给定一个正整数序列，要把它分成 `M` 段，每段连续。 要求最小化所有段中最大的段和。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1182.md`；正文：`problems/luogu/P1182/index.md`
- 结论：✅ 二分最大段和 + 贪心分段计数

## luogu/P1314　[NOIP 2011 提高组] 聪明的质监员　
- **解法一句话**：检验值 y(W) 随阈值 W 单调不增，用前缀和在 O(n+m) 内计算一次 y(W)，再二分找到最接近标准值 s 的位置。
- **思路开头**：给定 `n` 个矿石，每个矿石有： - 重量 `w_i` - 价值 `v_i`
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1314.md`；正文：`problems/luogu/P1314/index.md`
- 结论：✅ 二分阈值 W（y(W) 单调不增）+ 前缀和

## luogu/P1419　寻找段落　
- **解法一句话**：(无)
- **思路开头**：(无解析正文)
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1419.md`；正文：`problems/luogu/P1419/index.md`
- 结论：✅ 实数域二分平均值 + 前缀和/单调队列；摘录为空但原文完整

## luogu/P1462　通往奥格瑞玛的道路　
- **解法一句话**：二分允许的最高城市收费，用受限 Dijkstra 检查血量能否到达终点。
- **思路开头**：总伤害不能超过血量，最小化所经城市收费的最大值。 ### 思路 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1462.md`；正文：`problems/luogu/P1462/index.md`
- 结论：✅ 二分收费上限 + 受限 Dijkstra 判定

## luogu/P14635　[NOIP2025] 糖果店　
- **解法一句话**：把购买拆成最便宜的两颗组和若干个单颗项，预处理奇偶最优值后二分答案。
- **思路开头**：有 `n` 种糖果，每种糖果数量无限。第 `i` 种糖果的价格按购买次数交替： ```text x_i, y_i, x_i, y_i, ...
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P14635.md`；正文：`problems/luogu/P14635/index.md`
- 结论：✅ 二分可买颗数 + O(1) 花费判定

## luogu/P1542　包裹快递　
- **解法一句话**：二分最大速度，给定速度后顺着维护每个地点可行签收时间区间的下界，线性判断是否能按时送完。
- **思路开头**：有 `n` 个地点需要按顺序依次送达。 第 `i` 个地点给出： 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1542.md`；正文：`problems/luogu/P1542/index.md`
- 结论：✅ 二分最大速度 + 最早可行时间前缀判定

## luogu/P1642　规划　
- **解法一句话**：(无)
- **思路开头**：(无解析正文)
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1642.md`；正文：`problems/luogu/P1642/index.md`
- 结论：✅ 分数规划二分比值 + 树形背包；摘录为空但原文完整

## luogu/P1824　[USACO05FEB] 进击的奶牛 Aggressive Cows G　
- **解法一句话**：排序牛舍后二分最小距离，用从左到右尽早放牛的贪心检查当前距离是否可行。
- **思路开头**：有 `n` 间牛舍，每间牛舍在一条直线上的某个坐标位置。要从中选择 `m` 间牛舍放牛，每间牛舍最多放一头牛。 希望任意两头牛之间的最小距离尽可能大，输出这个最大值。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1824.md`；正文：`problems/luogu/P1824/index.md`
- 结论：✅ 二分最小距离 + 尽早放牛贪心

## luogu/P1843　奶牛晒衣服　
- **解法一句话**：二分最少时间，检查给定时间下自然风干后剩余湿度对应的烘衣机总秒数是否不超过时间。
- **思路开头**：有 `n` 件衣服，每件衣服初始湿度为 `w_i`。 每过 1 秒，所有衣服都会自然减少 `a` 点湿度。同时还可以再用 1 秒烘衣机，让某一件衣服额外减少 `b` 点湿度。烘衣机同一时间只能烘一件衣服。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1843.md`；正文：`problems/luogu/P1843/index.md`
- 结论：✅ 二分最短时间 + 烘衣机总秒数判定

## luogu/P1873　[COCI 2011/2012 #5] EKO / 砍树　
- **解法一句话**：二分锯片高度，扫描树高判断当前高度能否得到至少 M 米木材，寻找最大可行高度。
- **思路开头**：有 `N` 棵树，每棵树有一个高度。锯片高度设为 `H` 后，只有高于 `H` 的部分会被锯掉。 要求找到最大的整数高度 `H`，使得锯下来的木材总长度至少为 `M`。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1873.md`；正文：`problems/luogu/P1873/index.md`
- 结论：✅ 二分锯片高度 + 求和判定（模板题）

## luogu/P1948　[USACO08JAN] Telephone Lines S　
- **解法一句话**：二分最大付费边长度，把超过阈值的边计为 1，用 0-1 BFS 判断免费额度是否足够。
- **思路开头**：要从 `1` 号电话杆连到 `n` 号电话杆。电信公司可以免费提供最多 `k` 条电话线。 剩余需要付费的电话线，其费用由其中最长的一条决定。要求最小化这条最长付费电话线的长度；如果无法连通，输出 `-1`。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P1948.md`；正文：`problems/luogu/P1948/index.md`
- 结论：✅ 二分最大付费边 + 0-1 BFS 判定

## luogu/P2323　[HNOI2006] 公路修建问题　
- **解法一句话**：二分最大允许造价 T。对每个 T，只看二级造价不超过 T 的边是否能连通全图，再看一级造价不超过 T 的边最多能提供多少条一级公路，从而判断可行性。
- **思路开头**：有 $n$ 个景点，候选公路一共若干条。 每条候选公路有两种修法： 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P2323.md`；正文：`problems/luogu/P2323/index.md`
- 结论：✅ 二分最大花费 + 并查集判定连通与一级路条数

## luogu/P2370　yyy2015c01 的 U 盘　
- **解法一句话**：二分最小文件大小限制L，每次check用0/1背包判断在容量S限制下能否装下价值≥p的文件。
- **思路开头**：有 $n$ 个文件，每个文件有大小 $W_i$ 和价值 $V_i$。U盘容量为 $S$，传输接口只能传输大小不超过 $L$ 的文件。文件不能被分割，要求选出总大小不超过 $S$ 的文件，使总价值至少为 $p$。 问在满足条件的前提下，最小的接口大小 $L$ 是多少？无解输出 `No Solution!`。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P2370.md`；正文：`problems/luogu/P2370/index.md`
- 结论：✅ 二分接口大小 + 0/1 背包判定

## luogu/P2440　木材加工　
- **解法一句话**：二分木材长度，统计总共能切出的段数是否至少达到 k。
- **思路开头**：给出 $n$ 根原木和目标段数 $k$。 要求把每根原木切成若干段长度相同的整数木段，并且总段数不少于 $k$。 输出能切出的最大长度。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P2440.md`；正文：`problems/luogu/P2440/index.md`
- 结论：✅ 二分段长 + 可切段数计数

## luogu/P2511　[HAOI2008] 木棍分割　
- **解法一句话**：先二分最长段长度的最小可行值，再在该上界下用滑动窗口优化的计数 DP 统计所有合法连续划分方案。
- **思路开头**：有 `n` 根木棍按顺序连在一起，允许最多切断 `m` 个连接处。 这样会把整列木棍分成若干段连续区间。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P2511.md`；正文：`problems/luogu/P2511/index.md`
- 结论：✅ 二分最长段上界 + 滑动窗口计数 DP

## luogu/P2678　[NOIP 2015 提高组] 跳石头　
- **解法一句话**：二分最短跳跃距离，贪心统计给定距离下最少需要移走的石头数。
- **思路开头**：有一条长为 `L` 的河道，起点和终点固定，中间有 `N` 块岩石。 你最多可以移走 `M` 块中间岩石，要求剩余相邻点之间的最短跳跃距离尽可能大。 ### 思路
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P2678.md`；正文：`problems/luogu/P2678/index.md`
- 结论：✅ 二分最短跳跃距离 + 贪心移石计数

## luogu/P2680　[NOIP 2015 提高组] 运输计划　
- **解法一句话**：二分答案，倍增 LCA 求路径长度，树上差分找所有超标路径的公共边并比较最大公共边权。
- **思路开头**：先看一个可以直接验证想法的朴素解： @include-code(./brute.cpp, cpp) 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P2680.md`；正文：`problems/luogu/P2680/index.md`
- 结论：✅ 二分时间上限 + 树上差分求公共边

## luogu/P2852　[USACO06DEC] Milk Patterns G　
- **解法一句话**：二分模式长度，用序列双哈希统计固定长度子数组是否有出现至少 K 次的模式。
- **思路开头**：给定一个长度为 `N` 的整数序列，求最长的连续子序列长度，使得某个相同模式至少出现 `K` 次。 出现位置可以重叠。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P2852.md`；正文：`problems/luogu/P2852/index.md`
- 结论：✅ 二分模式长度 + 哈希滑窗计数

## luogu/P2985　[USACO10FEB] Chocolate Eating S　
- **解法一句话**：二分最低睡前幸福值，用每天吃到刚达标就停止的贪心检查可行性并构造吃巧克力日期。
- **思路开头**：有 `N` 块巧克力，要在 `D` 天内按顺序吃完。第 `i` 块巧克力会让幸福值增加 `H_i`。 每天睡前记录当天幸福值，然后睡觉时幸福值会变成 $floor(happy / 2)$。一天可以吃多块巧克力，也可以不吃，但巧克力必须按编号顺序吃。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P2985.md`；正文：`problems/luogu/P2985/index.md`
- 结论：✅ 二分最低睡前幸福值 + 贪心模拟

## luogu/P3017　[USACO11MAR] Brownie Slicing G　
- **解法一句话**：二分最小块权值，用非负矩阵上的横向与纵向贪心判定目标是否可行。
- **思路开头**：给定一个 $R\times C$ 的非负矩阵。先横切成 $A$ 条连续横带，每条横带再各自竖切成 $B$ 个连续块。其它牛会拿走较大的块，Bessie 最后只能得到权值最小的那一块。 要求最大化所有 $A\times B$ 个块中的最小权值。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P3017.md`；正文：`problems/luogu/P3017/index.md`
- 结论：✅ 二分最小块权值 + 矩阵贪心判定

## luogu/P3199　[HNOI2009] 最小圈　
- **解法一句话**：(无)
- **思路开头**：(无解析正文)
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P3199.md`；正文：`problems/luogu/P3199/index.md`
- 结论：✅ 分数规划二分比值 + SPFA 判负环；摘录为空但原文完整

## luogu/P3517　[POI 2011] WYK-Plot　
- **解法一句话**：二分最大误差，使用随机增量最小覆盖圆与最长可行前缀贪心构造连续分组。
- **思路开头**：把点序列切成不超过 `m` 个连续非空段，每段用一个新点代替。最小化所有原点到所属新点的最大距离，并输出误差、段数和各段代表点。 ### 思路 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P3517.md`；正文：`problems/luogu/P3517/index.md`
- 结论：✅ 实数域二分误差 + 最小覆盖圆/最长前缀贪心

## luogu/P3743　小鸟的设备　
- **解法一句话**：二分最长运行时间，用各设备累计能量缺口与充电宝总供能构造单调可行性判定。
- **思路开头**：有 $n$ 台设备同时运行。第 $i$ 台设备每秒消耗 $a_i$ 单位能量，初始存有 $b_i$ 单位能量。一个功率为 $p$ 的充电宝可以随时在设备之间切换，切换不耗时。 求所有设备能够共同运行的最长时间；如果可以永远运行，输出 `-1`。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P3743.md`；正文：`problems/luogu/P3743/index.md`
- 结论：✅ 实数域二分运行时间 + 能量缺口判定

## luogu/P3853　[TJOI2007] 路标设置　
- **解法一句话**：二分允许的最大间距，用 (gap-1)//limit 统计每段必须新增的路标数。
- **思路开头**：公路起点、终点和若干位置已有路标。最多新增 `K` 个整数位置路标，求相邻路标最大距离的最小值。 ### 思路 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P3853.md`；正文：`problems/luogu/P3853/index.md`
- 结论：✅ 二分最大间距 + (gap-1)//limit 计数

## luogu/P4322　[JSOI2016] 最佳团体　
- **解法一句话**：(无)
- **思路开头**：(无解析正文)
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P4322.md`；正文：`problems/luogu/P4322/index.md`
- 结论：✅ 分数规划二分比值 + 树形背包；摘录为空但原文完整

## luogu/P4377　[USACO18OPEN] Talent Show G　
- **解法一句话**：(无)
- **思路开头**：这道题是 “01分数规划” 的另一个经典应用场景：背包模型。 它和 P1642 的核心区别在于：P1642 是在树上做选择（树形DP），而这道题是在集合里做选择（背包DP）。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P4377.md`；正文：`problems/luogu/P4377/index.md`
- 结论：✅ 01 分数规划 + 截断式 0/1 背包判定

## luogu/P4951　[USACO01OPEN] Earthquake　
- **解法一句话**：(无)
- **思路开头**：这道题目是一个非常经典的**0/1分数规划（0/1 Fractional Programming）**问题，结合了**最小生成树（MST）**的知识。 ### 1. 题目分析 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P4951.md`；正文：`problems/luogu/P4951/index.md`
- 结论：✅ 01 分数规划 + Kruskal 最小生成树判定

## luogu/P8660　[蓝桥杯 2017 国 A] 区间移位　
- **解法一句话**：二分最大位移后，把每个区间转成带最早可接点和最晚失效点的任务，按失效点最小优先贪心推进覆盖前缀。
- **思路开头**：给出 `n` 个区间 `[a_i,b_i]`。 现在可以把每个区间整体平移成 `[a_i+c_i,b_i+c_i]`，要求所有平移后的区间并起来以后，完整覆盖 `[0,10000]`。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P8660.md`；正文：`problems/luogu/P8660/index.md`
- 结论：✅ 整数二分最大位移 + 失效点优先贪心

## luogu/P8814　[CSP-J 2022] 解密　（已人工否决：人工审查否决入选：题解自述「它在这里不是二分答案」，关键词为提及性出现，实际解法…）
- **解法一句话**：由两个条件推出 p+q，再用二次方程判别式判断是否存在正整数根。
- **思路开头**：给出 `k` 组询问，每组有三个正整数 `n,e,d`。 要求寻找正整数 $p,q$，满足： 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P8814.md`；正文：`problems/luogu/P8814/index.md`
- 结论：❌ 原文自述「它在这里不是二分答案」；二分仅求整数平方根，主体是代数推导 + 判别式

## luogu/P9755　[CSP-S 2023] 种树　
- **解法一句话**：二分完成天数，把每个点转成最晚种植日，再用最早截止时间优先判断树上调度。
- **思路开头**：二分 $T$，然后递归枚举所有合法的连通种植顺序：第 `day` 天在"未种、且与某种下的地块相邻"的地块里任选一个种下，检查每个点种下时是否不晚于自己的最晚种植日。
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__P9755.md`；正文：`problems/luogu/P9755/index.md`
- 结论：✅ 二分完成天数 + 最早截止优先调度（摘录误取了「暴力解法」段，正解段明写二分答案）

## luogu/CF912E　Prime Gift　（已人工否决：入口页：题解已迁移至 codeforces/912E，本页仅保留跳转说明，不是独…）
- **解法一句话**：Luogu 无法提交 Codeforces 原题，解析已迁移至 codeforces/912E，本页仅保留入口。
- **思路开头**：给定至多 16 个质数，求所有质因子都来自该集合的第 `k` 小正整数，答案不超过 $10^{18}$。完整教学解析（含 Python 版本与思考过程）已迁移至： - [[problem: codeforces,912E]] · [CF912E Prime Gift 题解](https://codeforces.com/problemset/problem/912/E) 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/luogu__CF912E.md`；正文：`problems/luogu/cf912e/index.md`
- 结论：⚠️ 解法确为二分答案，但本页自述解析已迁移、与 codeforces/912E 同一题；是否作为独立节点写入需人工终审

## noi_openjudge/ch0111-04　网线主管　
- **解法一句话**：以厘米为整数单位二分长度，用可切出的段数判断可行性。
- **思路开头**：将库存网线切成至少指定数量的等长段，求能得到的最大长度，结果精确到厘米。 ### 思路 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/noi_openjudge__ch0111-04.md`；正文：`problems/noi_openjudge/ch0111-04/index.md`
- 结论：✅ 二分网线段长 + 可切段数计数

## noi_openjudge/ch0111-10　河中跳房子　
- **解法一句话**：二分最短跳跃距离，用贪心扫描统计必须移走的石头数。
- **思路开头**：最多移走 $M$ 块中间石头，使从起点到终点的最短一次跳跃距离尽量大。 ### 思路 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/noi_openjudge__ch0111-10.md`；正文：`problems/noi_openjudge/ch0111-10/index.md`
- 结论：✅ 二分最短跳跃距离 + 贪心删石（跳石头同型）

## POJ/2976　Dropping tests　
- **解法一句话**：(无)
- **思路开头**：- 二分性: 如果分数 x 可以达到, 那么$query_max_sum(x) >=0 $ 成立,则分数 $x_i < x$ 都可以成立,我们要使得x尽可能的大 - 答案范围: $[0,1]$
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/POJ__2976.md`；正文：`problems/poj/2976/index.md`
- 结论：✅ 01 分数规划；正文极短（151 字符），已据 1.cpp 的 100 次二分 + 贪心 check 确认，材料偏薄

## POJ/3122　Pie　
- **解法一句话**：(无)
- **思路开头**：二分答案题目。我们需要在连续的实数域上二分体积。 ### 1 题目解析：单调性证明（反证法） 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/POJ__3122.md`；正文：`problems/poj/3122/index.md`
- 结论：✅ 实数域二分体积 + 可切块数计数

## roj/19999　Function　
- **解法一句话**：f(i,j) 是 y_i、y_j 的加权平均，取值有界可二分；f(i,j)≥v 变形为两个序列的比较，排序后双指针 O(n) 计数求第 k 大。
- **思路开头**：一句话本质：$f(i,j)$ 是 $y_i, y_j$ 关于权重 $x_i, x_j$ 的加权平均，所以取值有界、可二分；"第 $k$ 大"用二分答案 $v$ 转化，而 $f(i,j) \geqslant v$ 可以变形为两个独立序列之间的比较 $x_i(y_i-v) \geqslant x_j(v-y_j)$，排序后双指针 $O(n)$ 计数。 **问题？**直接枚举所有 $f(i,j)$ 排序
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/roj__19999.md`；正文：`problems/roj/19999/index.md`
- 结论：✅ 二分第 k 大值 + 排序双指针计数

## roj/20027　聚会　
- **解法一句话**：二分答案：时间 T 可行等价于每个人的可达区间有公共交点，判定只需比较区间左端点最大值与右端点最小值。
- **思路开头**：**一句话本质**："最小化最晚到达时间"反过来变成"判定给定时间 $T$ 内能否全部赶到"——每人可达区间 $[x_i - v_iT,\ x_i + v_iT]$ 的交非空，判定 $O(n)$ 且关于 $T$ 单调，于是二分答案。 先看一个可以直接验证想法的小数据精确解： 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/roj__20027.md`；正文：`problems/roj/20027/index.md`
- 结论：✅ 二分最晚到达时间 + 可达区间交非空判定

## shumeng/CSP202605B　机器人宿管指南　
- **解法一句话**：模拟固定天数的苹果消耗过程，并对机器人数量二分答案。
- **思路开头**：### 固定机器人数量后直接模拟 若机器人数量为 $x$，每天的过程是确定的：先丢弃变质苹果，再检查剩余苹果是否够 $x$ 个机器人吃，不够就失败。用 `(t * k + 99) / 100` 整数计算向上取整即可，全程只用整数，避免浮点误差。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/shumeng__CSP202605B.md`；正文：`problems/shumeng/CSP202605B/index.md`
- 结论：✅ 二分机器人数量 + 逐日模拟判定

## usaco/1038　Social Distancing　
- **解法一句话**：二分最小间距，用区间贪心从左到右尽量靠左放牛来判断可行性。
- **思路开头**：数轴上有 $M$ 个互不相交的有草区间，要放置 $N$ 头牛。 所有牛都必须放在整数位置，并且位置上有草。定义 $D$ 为任意两头牛之间的最小距离，要求最大化 $D$。 
- 材料：`relation-batches/b001-erfen-2026-10-02/materials/usaco__1038.md`；正文：`problems/usaco/1038/index.md`
- 结论：✅ 二分最小间距 + 区间贪心放置
