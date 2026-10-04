#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data, None)
    if n is None:  # 空输入防御：没有位置量就直接结束
        return
    out: list[str] = []

    def dfs(rest: int, start: int, path: list[int]) -> None:
        """按非递减顺序搜索 rest 的拆分，path 记录已选加数。"""
        if rest == 0:
            out.append(f"{n}={'+'.join(map(str, path))}")
            return
        # 下一个加数不小于上一个（保证不重复），且必须小于 n
        for x in range(start, rest + 1):
            if x < n:
                path.append(x)
                dfs(rest - x, x, path)
                path.pop()

    dfs(n, 1, [])
    sys.stdout.write('\n'.join(out))


if __name__ == "__main__":
    solve()
