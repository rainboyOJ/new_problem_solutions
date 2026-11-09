#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-11-09 17:35
# update_at: 2026-11-09 17:35

import sys

# 每个区间 [l, r] 用 (左端点 l, 右端点 r, 字符串编号 w, 起始位置 p) 表示，下标 0 起
type Seg = tuple[int, int, int, int]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    out: list[str] = []
    q = int(next(data))

    for _ in range(q):
        t = next(data).decode()
        n = int(next(data))
        strs = [next(data).decode() for _ in range(n)]
        length = len(t)

        # 把每个 s_i 在 t 中的每次出现都看成一个能「一步涂红」的区间
        segs: list[Seg] = sorted(
            (p, p + len(s) - 1, w, p)
            for w, s in enumerate(strs, 1)
            for p in range(length - len(s) + 1)
            if t.startswith(s, p)
        )

        # 已涂红 t[0..covered-1]；每步在左端点 <= covered 的区间里取右端点最远的
        covered = 0
        plan: list[tuple[int, int]] = []
        impossible = False
        while covered < length:
            reachable = [seg for seg in segs if seg[0] <= covered and seg[1] >= covered]
            if not reachable:                         # 没有区间能越过 covered：有位置涂不到
                impossible = True
                break
            best = max(reachable, key=lambda seg: seg[1])
            plan.append((best[2], best[3] + 1))       # 记录 (字符串编号, 1 起起始位置)
            covered = best[1] + 1

        if impossible:
            out.append("-1")
        else:
            out.append(str(len(plan)))
            out += [f"{w} {p}" for w, p in plan]

    print("\n".join(out))


if __name__ == "__main__":
    solve()
