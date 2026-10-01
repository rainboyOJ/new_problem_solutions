#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 09:32
# update_at: 2026-10-01 09:32

import sys
from collections.abc import Iterator


def generate_permutations(n: int) -> Iterator[str]:
    """生成 1 到 n 的所有全排列，每项格式化为行末带空格的字符串。"""
    chosen = [False] * (n + 1)
    path = [0] * n

    def dfs(pos: int) -> Iterator[str]:
        if pos == n:
            yield " ".join(map(str, path)) + " "
            return
        for num in range(1, n + 1):
            if not chosen[num]:
                chosen[num] = True
                path[pos] = num
                yield from dfs(pos + 1)
                chosen[num] = False

    yield from dfs(0)


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    lines = list(generate_permutations(n))
    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    solve()
