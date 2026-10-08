#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 14:12
# update_at: 2026-10-08 14:27

import sys

INF = 4 * 10**18  # 划分二分的哨兵：p±t 的绝对值都远小于它

type Positions = list[int]  # 某个方向（向右 / 向左）的全部初始位置，升序


def kth_after_time(right_pos: Positions, left_pos: Positions, rank: int, t: int) -> int:
    """求 {right_pos[i]+t} ∪ {left_pos[j]-t} 合并后的第 rank 小（rank 从 1 开始）。

    枚举「从 right_pos 里取 x 个」，二分找让两侧划分合法的 x，O(log n)。
    """
    right_cnt, left_cnt = len(right_pos), len(left_pos)
    lo, hi = max(0, rank - left_cnt), min(rank, right_cnt)
    while lo <= hi:
        x = (lo + hi) // 2
        y = rank - x
        # 划分点两侧的四个边界值，越界处用哨兵保证比较不会误判
        r_last = right_pos[x - 1] + t if x > 0 else -INF
        r_next = right_pos[x] + t if x < right_cnt else INF
        l_last = left_pos[y - 1] - t if y > 0 else -INF
        l_next = left_pos[y] - t if y < left_cnt else INF
        split_ok = r_last <= l_next and l_last <= r_next
        if split_ok:
            return max(r_last, l_last)  # 划分合法时第 rank 小就是左半部分的最大值
        if r_last > l_next:
            hi = x - 1  # right_pos 取多了
        else:
            lo = x + 1  # right_pos 取少了
    return 0


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    try:
        n = next(data)
    except StopIteration:
        return
    pos = [next(data) for _ in range(n)]
    d = [next(data) for _ in range(n)]
    q = next(data)

    # 相遇折返等价于互相穿过并交换身份：位置多重集不变，且按初始位置的
    # 名次在任何时刻都不变，所以按位置升序排一遍即可确定每个方向的升序数组。
    order = sorted(range(n), key=pos.__getitem__)
    rank_of = [0] * n                                   # rank_of[k]：孩子 k 的名次，从 1 开始
    for r, k in enumerate(order, 1):
        rank_of[k] = r
    right_pos: Positions = [pos[k] for k in order if d[k] == 1]
    left_pos: Positions = [pos[k] for k in order if d[k] == 0]

    out: list[str] = []
    for _ in range(q):
        k, t = next(data), next(data)
        out.append(str(kth_after_time(right_pos, left_pos, rank_of[k], t)))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
