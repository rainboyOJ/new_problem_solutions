#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 04:15
# update_at: 2026-10-01 04:15

# 方向编码：0 北 1 东 2 南 3 西，顺时针转 90 度就是 (d + 1) % 4
DIRS = ((-1, 0), (0, 1), (1, 0), (0, -1))


def step(r: int, c: int, d: int, grid: list[str]) -> tuple[int, int, int]:
    """按牛/John 的固定走法推进一步，返回新的 (行, 列, 方向)。

    前方无障碍且不出界就前进一步，否则原地顺时针转 90 度。
    """
    nr, nc = r + DIRS[d][0], c + DIRS[d][1]
    in_path = 0 <= nr < 10 and 0 <= nc < 10 and grid[nr][nc] != '*'
    return (nr, nc, d) if in_path else (r, c, (d + 1) % 4)


def solve() -> None:
    grid = [input() for _ in range(10)]
    # John、牛的初始 (行, 列)；两者初始都朝北
    f = next((r, c) for r in range(10) for c in range(10) if grid[r][c] == 'F') + (0,)
    c = next((r, c) for r in range(10) for c in range(10) if grid[r][c] == 'C') + (0,)

    seen: set = set()                   # (John 行,列,方向, 牛 行,列,方向)，共 16000 种
    while f[:2] != c[:2]:               # 分钟末同格才算抓住
        if (f, c) in seen:              # 状态重现仍未相遇 → 以后永远原样循环
            print(0)
            return
        seen.add((f, c))
        f = step(*f, grid)
        c = step(*c, grid)
    print(len(seen))                    # 每分钟登记一个状态，登记数就是经过的分钟数


if __name__ == "__main__":
    solve()
