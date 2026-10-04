#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 16:54
# update_at: 2026-09-30 16:54

import sys

A = b'A'  # 事件类型：A 询问 / B 上车 / C 下车
B = b'B'


def walk_sweep(events: list[tuple[bytes, int, int]], n: int) -> list[str]:
    """指针扫描所有事件：主任只向前走，返回每次 A 的前缀和答案。

    询问的 m 单调不减，所以主任的位置 pos 只增不减；把答案拆成两半维护——
    已走过的前缀和存 total，还没走到的车厢净人数存 cnt，两者互不重叠。
    """
    cnt = [0] * (n + 1)  # 各车厢净人数（仅对未走过的位置有意义）
    pos = 0              # 主任当前位置：前 pos 节车厢已被点过
    total = 0            # 前 pos 节车厢的人数和
    out: list[str] = []

    for op, m, p in events:
        if op == A:
            while pos < m:  # 一站一站往前走，累计新经过的车厢
                pos += 1
                total += cnt[pos]
            out.append(str(total))
        else:
            delta = p if op == B else -p
            if m <= pos:  # 车厢已被走过：直接修正前缀和
                total += delta
            else:         # 还没走到：先记在车厢上，等指针经过时再累加
                cnt[m] += delta
    return out


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    k = int(next(data))

    events: list[tuple[bytes, int, int]] = []
    for _ in range(k):
        op = next(data)
        m = int(next(data))
        p = int(next(data)) if op != A else 0  # A 只有一个 m
        events.append((op, m, p))

    print('\n'.join(walk_sweep(events, n)))


if __name__ == "__main__":
    solve()
