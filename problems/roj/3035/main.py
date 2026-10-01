#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 11:22
# update_at: 2026-10-01 11:22

import sys
from collections import deque

NEG = -1 << 62  # 空队哨兵：保证含哨兵的 max 一定落在非空队列上


def pop_max(queues: list[deque]) -> int:
    """从三个降序单调队列的队首中取出当前最长的蚯蚓长度。"""
    candidates = [q[0] if q else NEG for q in queues]
    pick = candidates.index(max(candidates))
    return queues[pick].popleft()


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n, m, q = int(next(data)), int(next(data)), int(next(data))
    u, v, t = int(next(data)), int(next(data)), int(next(data))

    # 三个队列分别装：未切过的蚯蚓、切出的 ⌊px⌋ 段、切出的 x-⌊px⌋ 段。
    # 队首存真实值（含此后累积的 q），单调递减；队尾存"没长过"的历史值。
    initial = sorted((int(next(data)) for _ in range(n)), reverse=True)
    queues = [deque(initial), deque(), deque()]
    cut_lengths: list[int] = []  # 每一秒被切断蚯蚓（切断前）的长度

    offset = 0  # 全局偏移：除最近切出的两只外，每只蚯蚓每秒都长 q
    for second in range(1, m + 1):
        x = pop_max(queues) + offset
        left = x * u // v    # ⌊px⌋，历史值（含累积的 q）
        right = x - left
        # 新蚯蚓从下一秒开始长：历史值要倒扣本秒之后的 q（含即将累加的这一次）
        queues[1].append(left - offset - q)
        queues[2].append(right - offset - q)
        offset += q
        cut_lengths.append(x)

    final = sorted(
        (w + offset for qu in queues for w in qu),
        reverse=True,
    )  # m 秒后所有蚯蚓的真实长度：三个降序队列拼接后归并，从大到小

    # 两行各占一行输出，没有数的行也要输出空行
    out = [cut_lengths[i] for i in range(t - 1, len(cut_lengths), t)]
    print(' '.join(map(str, out)))
    out = [final[i] for i in range(t - 1, len(final), t)]
    print(' '.join(map(str, out)))


if __name__ == "__main__":
    solve()
