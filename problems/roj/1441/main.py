#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 10:48
# update_at: 2026-09-30 11:15

import math
import sys

INF = 10**9


def search_cake(n: int, m: int) -> int:
    """搜索满足体积限制与单调递减约束的 M 层蛋糕最小表面积。"""
    # 预处理从顶层往下数前 i 层的最小累计体积与最小累计侧面积
    min_v = [0] + [sum(k * k * k for k in range(1, i + 1)) for i in range(1, m + 1)]
    min_s = [0] + [sum(2 * k * k for k in range(1, i + 1)) for i in range(1, m + 1)]

    best_s = INF

    def dfs(layer: int, v: int, s: int, r_prev: int, h_prev: int) -> None:
        """从下往上递归搜索第 layer 层，v 为剩余体积，s 为当前累计面积。"""
        nonlocal best_s
        if layer == 0:
            if v == 0 and s < best_s:
                best_s = s
            return

        # 剪枝 1：剩余体积不足以搭建剩余层
        # 剪枝 2：当前面积加上剩余最小侧面积仍劣于最优解
        # 剪枝 3：剩余体积换算侧面积下界 2 * v / r_prev 加上当前面积仍劣于最优解
        if v < min_v[layer] or s + min_s[layer] >= best_s or s + 2 * v // r_prev >= best_s:
            return

        # 半径上下界：必须严格小于上一层，且为剩余层预留最小高度 1
        max_r = min(r_prev - 1, int(math.isqrt((v - min_v[layer - 1]) // layer)))
        for r in range(max_r, layer - 1, -1):
            max_h = min(h_prev - 1, (v - min_v[layer - 1]) // (r * r))
            for h in range(max_h, layer - 1, -1):
                cur_v = r * r * h
                cur_s = 2 * r * h
                dfs(layer - 1, v - cur_v, s + cur_s, r, h)

    # 第 M 层（最底层）确定底面积 r^2 并启动搜索
    max_r_m = int(math.isqrt(n))
    for r in range(max_r_m, m - 1, -1):
        if r * r + min_s[m] >= best_s:
            continue
        max_h = (n - min_v[m - 1]) // (r * r)
        for h in range(max_h, m - 1, -1):
            cur_v = r * r * h
            cur_s = r * r + 2 * r * h
            if cur_s + min_s[m - 1] >= best_s or cur_s + 2 * (n - cur_v) // r >= best_s:
                continue
            dfs(m - 1, n - cur_v, cur_s, r, h)

    return best_s if best_s != INF else 0


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    m = next(data)
    ans = search_cake(n, m)
    print(ans)


if __name__ == "__main__":
    solve()
