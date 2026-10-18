#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-18 16:43
# update_at: 2026-10-18 16:43
#
# 在线倍增（binary jump）：
#   sum[i] = A[1] + ... + A[i] 严格递增，"sum[i] <= T" 具有二分性，
#   所以从位置 0 出发，从大到小试跳 2^i，跳过去仍然可行就跳，最后停下处即答案。
#   每读到一个 T 就立刻回答，符合题面的"在线"要求。

import sys


def jump(sum_: list[int], n: int, top: int, t: int) -> int:
    """返回最大的 k，满足 sum_[k] <= t。"""
    pos = 0  # 当前停留位置；sum_[0] = 0 一定可行
    for i in range(top, -1, -1):
        nxt = pos + (1 << i)  # 本轮尝试跳 2^i 个位置
        if nxt <= n and sum_[nxt] <= t:
            pos = nxt  # 不越界且不超过 T 才真的跳
    return pos


def solve() -> None:
    read = sys.stdin.buffer.readline
    n, q = map(int, read().split())

    sum_ = [0] * (n + 1)  # sum_[i] = A[1] + ... + A[i]
    a = list(map(int, read().split()))
    for i in range(1, n + 1):
        sum_[i] = sum_[i - 1] + a[i - 1]

    top = n.bit_length() - 1  # 最大的 i，使得 2^i <= n

    out = []
    for _ in range(q):
        t = int(read())          # 一次只处理一个询问
        out.append(str(jump(sum_, n, top, t)))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
