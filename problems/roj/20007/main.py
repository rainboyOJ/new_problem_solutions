#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 19:36
# update_at: 2026-10-02 19:36

import sys


def solve() -> None:
    it = iter(sys.stdin.buffer.read().split())
    L, T, n = int(next(it)), int(next(it)), int(next(it))

    ants = [(int(next(it)), next(it) == b"R") for _ in range(n)]  # (位置, 是否向右)，输入顺序

    # 碰撞瞬间掉头等价于互换身份：终态（位置+方向）的多重集合就是各自直走 T 秒的结果，
    # 且按初始位置排第 r 的蚂蚁领走按终态位置排第 r 个状态。
    final = sorted((pos + (T if right else -T), right) for pos, right in ants)
    order = sorted(range(n), key=lambda i: ants[i][0])  # 初始位置排名 → 蚂蚁编号

    cnt: dict[int, int] = {}
    for pos, _ in final:  # 终点位置计数，出现两次以上 → Same
        cnt[pos] = cnt.get(pos, 0) + 1

    out: list[str] = [""] * n
    for r, i in enumerate(order):  # 排名 r 的蚂蚁拿走终态 r，汇报时按编号归位
        pos, right = final[r]
        out[i] = (
            "Down"
            if pos < 0 or pos > L
            else f"{pos} Same"
            if cnt[pos] > 1
            else f"{pos} {'R' if right else 'L'}"
        )
    print("\n".join(out))


if __name__ == "__main__":
    solve()
