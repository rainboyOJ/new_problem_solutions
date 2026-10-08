#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 16:12
# update_at: 2026-10-08 16:12

from itertools import count


def solve() -> None:
    """本题无输入：从 7 的倍数起枚举，首个满足「每行 2..6 人都多出 1 人」的人数即最少人数。"""
    answer = next(n for n in count(7, 7) if all(n % k == 1 for k in range(2, 7)))
    print(answer)


if __name__ == "__main__":
    solve()
