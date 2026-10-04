#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47
# 题目: roj 1437 扩散
# 结论: 时刻 t 两菱形(切比雪夫转曼哈顿菱形)相交 <=> 曼哈顿距离 <= 2t
#       边权 w = ceil(dist/2), 答案 = 最小生成树的最大边权
# 复杂度: O(n^2) 建完全图, Prim 求最小生成树, n<=50
import sys

n = int(sys.stdin.readline())
P = [tuple(map(int, sys.stdin.readline().split())) for _ in range(n)]
if n == 1:
    print(0)  # 只有一个点, 时刻 0 即连通
    raise SystemExit

a, b = P[0]
d = [abs(a - c) + abs(b - e) for c, e in P]  # Prim 初始: 点 0 到各点的距离
used, ans = [False] * n, 0
for _ in range(n):  # 做 n 轮, 每轮选出离生成树最近的点
    k = min(range(n), key=lambda i: (used[i], d[i]))  # 未使用的里挑最近的
    used[k], ans = True, max(ans, d[k])  # 并入生成树, 更新树的最大边
    d = [min(d[i], abs(P[i][0] - P[k][0]) + abs(P[i][1] - P[k][1])) if not used[i] else d[i]
         for i in range(n)]  # 用新点 k 松弛其余点
print(-(-ans // 2))  # ceil(ans/2): 边权 d 的扩散时刻
