#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:15
# update_at: 2026-10-01 04:15

import sys

MAXV = 100     # 公司编号上限：题面保证 i, j, p 都在 1..100
MAJORITY = 50  # 控股线：汇总持股要「大于 50%」才算控制


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    lines: list[tuple[int, int, int]] = []
    for _ in range(next(data)):
        i, j, p = next(data), next(data), next(data)
        lines.append((i, j, p))

    max_id = max((max(i, j) for i, j, _ in lines), default=0)
    v = max(max_id, 1)  # 公司实际编号范围：控制关系与自身控制都在这个范围内

    # own[a][b] = 公司 a 直接持有 b 的股份百分比；没有股份的边留 0，对不等式无影响
    own = [[0] * (v + 1) for _ in range(v + 1)]
    for i, j, p in lines:
        own[i][j] += p  # 题面允许多组 (i, j, p) 描述同一条持股边，必须累加

    ctrl = [[False] * (v + 1) for _ in range(v + 1)]
    for h in range(1, v + 1):
        ctrl[h][h] = True  # 条件一：控制自己

        # 关系会连锁：本轮新控制到的公司，它的股份本轮立刻能纳进来。
        # 所以反复扫描，直到某一轮没有新增，才说明这条链闭包已经取完。
        while True:
            added = False
            for b in range(1, v + 1):
                if ctrl[h][b]:
                    continue
                # 汇总所有受 h 控制的公司所持有的 b 股份（含 h 自己）
                stake = sum(own[c][b] for c in range(1, v + 1) if ctrl[h][c])
                if stake > MAJORITY:
                    ctrl[h][b] = True
                    added = True
            if not added:
                break

    out = [f"{h} {s}" for h in range(1, v + 1) for s in range(1, v + 1) if ctrl[h][s] and h != s]
    sys.stdout.write("\n".join(out) + ("\n" if out else ""))


if __name__ == "__main__":
    solve()
