#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 18:05
# update_at: 2026-09-30 18:05

import sys

INF_STEPS = 10**18  # "不限步"的上界：收缩到根的真实步数远小于它


def climb(state: tuple[int, int, int], limit: int) -> tuple[tuple[int, int, int], int]:
    """从 state 沿唯一父边向根收缩，最多走 limit 步；返回 (落点, 实际步数)。

    收缩一步 = 外侧棋子跳过相邻中轴棋子，等价于把较大间隙减去较小间隙；
    同方向的连续收缩整批执行（一次整除算清批长），否则 (1, 1e9) 这种间隙
    要单步走 1e9 次。两间隙相等即到达根，收缩方向不再存在。
    """
    a, b, c = state
    d1, d2 = b - a, c - b  # 左右两段间隙
    done = 0
    while d1 != d2 and done < limit:
        if d1 < d2:  # 右间隙大：批量"右间隙 -= 左间隙"，直到右间隙不超左间隙
            t = min((d2 - 1) // d1, limit - done)
            a += t * d1  # 每步最左与中轴两子同步右移一个左间隙，间隙差逐批递减
            b += t * d1
            d2 -= t * d1
        else:  # 左间隙大：批量"左间隙 -= 右间隙"，中轴与最右两子同步左移
            t = min((d1 - 1) // d2, limit - done)
            b -= t * d2
            c -= t * d2
            d1 -= t * d2
        done += t
    return (a, b, c), done


def distance(start: tuple[int, int, int], goal: tuple[int, int, int]) -> int | None:
    """跳动树上两状态的距离（最少跳动次数）；根不同说明无解，返回 None。"""
    root_s, depth_s = climb(start, INF_STEPS)
    root_g, depth_g = climb(goal, INF_STEPS)
    if root_s != root_g:
        return None

    # 深的一方先缩到同一深度；再同步收缩，"缩 k 步后相遇"对 k 单调，二分求最小 k
    if depth_s > depth_g:
        start, _ = climb(start, depth_s - depth_g)
    elif depth_g > depth_s:
        goal, _ = climb(goal, depth_g - depth_s)
    lo, hi = 0, min(depth_s, depth_g)  # k 的上界 = 同深后的深度（最迟在根相遇）
    while lo < hi:
        mid = (lo + hi) // 2
        if climb(start, mid)[0] == climb(goal, mid)[0]:
            hi = mid
        else:
            lo = mid + 1

    lca_depth = min(depth_s, depth_g) - lo  # 最近公共祖先距根的深度
    return depth_s + depth_g - 2 * lca_depth


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    start = tuple(sorted(data[:3]))
    goal = tuple(sorted(data[3:6]))

    steps = distance(start, goal)
    if steps is None:
        print("NO")
    else:
        print("YES")
        print(steps)


if __name__ == "__main__":
    solve()
