#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def solve() -> None:
    tokens = sys.stdin.read().split()
    n = int(tokens[0])  # 人数，2 ≤ n ≤ 40

    # 按 (性别, 输入序) 分桶：male 升序、female 降序，身高互不相同保证次序唯一
    male = sorted(float(h) for s, h in zip(tokens[1::2], tokens[2::2]) if s == "male")
    female = sorted((float(h) for s, h in zip(tokens[1::2], tokens[2::2]) if s == "female"), reverse=True)

    print(" ".join(f"{h:.2f}" for h in male + female))


if __name__ == "__main__":
    solve()
