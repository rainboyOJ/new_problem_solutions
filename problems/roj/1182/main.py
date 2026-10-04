#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-10-04 12:54

import sys


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))  # 人数，2 ≤ n ≤ 40

    # 按 (性别, 身高) 分桶：male 升序、female 降序，身高互不相同保证次序唯一
    male: list[float] = []
    female: list[float] = []
    for _ in range(n):
        sex = next(data).decode()
        height = float(next(data))
        (male if sex == "male" else female).append(height)

    male.sort()
    female.sort(reverse=True)

    print(" ".join(f"{h:.2f}" for h in male + female))


if __name__ == "__main__":
    solve()
