#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:12
# update_at: 2026-10-02 08:12

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    # 读入 (报名号, 成绩) 对
    people: list[tuple[int, int]] = [(next(data), next(data)) for _ in range(n)]

    # 成绩降序、成绩相同报名号升序：排序键直接取 (-成绩, 报名号)
    ranked: list[tuple[int, int]] = sorted(people, key=lambda p: (-p[1], p[0]))

    # 面试分数线 = 排名 floor(m*150%) 的选手分数（ranked 下标从 0 起）
    cutoff_rank = m * 3 // 2 - 1
    line = ranked[cutoff_rank][1]

    # 不低于分数线的全部进面试（含重分扩招）
    admitted: list[tuple[int, int]] = [p for p in ranked if p[1] >= line]

    out: list[str] = [f"{line} {len(admitted)}"]
    out += (f"{k} {s}" for k, s in admitted)
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()
