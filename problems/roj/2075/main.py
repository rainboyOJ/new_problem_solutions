#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

from collections import defaultdict
import sys


def solve() -> None:
    tokens = sys.stdin.buffer.read().split()
    if not tokens:
        return
    data = iter(tokens)
    h = int(next(data))
    w = int(next(data))
    grid = [next(data).decode() for _ in range(h)]

    # 1. 提取所有出现的矩形字母及其边界 (min_r, max_r, min_c, max_c)
    letters = sorted(set("".join(grid)) - {"."})
    bounds = {
        ch: (
            min(r for r in range(h) for c in range(w) if grid[r][c] == ch),
            max(r for r in range(h) for c in range(w) if grid[r][c] == ch),
            min(c for r in range(h) for c in range(w) if grid[r][c] == ch),
            max(c for r in range(h) for c in range(w) if grid[r][c] == ch),
        )
        for ch in letters
    }

    # 2. 统计每个矩形边框上覆盖它的其它字母：ch 必须在 top 之前放置 (ch -> top)
    # 即 ch 在底层，top 覆盖在 ch 上面
    edges = defaultdict(set)
    in_degree = {ch: 0 for ch in letters}
    for ch, (r1, r2, c1, c2) in bounds.items():
        border_cells = (
            [(r1, c) for c in range(c1, c2 + 1)]
            + [(r2, c) for c in range(c1, c2 + 1)]
            + [(r, c1) for r in range(r1, r2 + 1)]
            + [(r, c2) for r in range(r1, r2 + 1)]
        )
        for r, c in border_cells:
            top = grid[r][c]
            if top != ch and top in bounds and top not in edges[ch]:
                edges[ch].add(top)
                in_degree[top] += 1

    # 3. 回溯搜索所有合法的自底向上拓扑序（按字典序输出）
    n = len(letters)
    path: list[str] = []

    def dfs() -> None:
        if len(path) == n:
            sys.stdout.write("".join(path) + "\n")
            return
        for ch in letters:
            if ch not in path and in_degree[ch] == 0:
                for nxt in edges[ch]:
                    in_degree[nxt] -= 1
                path.append(ch)

                dfs()

                path.pop()
                for nxt in edges[ch]:
                    in_degree[nxt] += 1

    dfs()


if __name__ == "__main__":
    solve()
