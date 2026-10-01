#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 08:20
# update_at: 2026-10-01 08:20

import sys

# N <= 7，网格至多 49 格：每个格子用一个 bit 表示"已访问"，整张棋盘就是 49 位整数，
# 剪枝用位运算一次测四个邻居，避免逐格检查。

def bits(mask: int):
    """依次产出 mask 中每个 1 位的下标。"""
    while mask:
        b = mask & -mask
        yield b.bit_length() - 1
        mask ^= b


def solve() -> None:
    n = int(sys.stdin.buffer.read())
    cells = n * n
    full = (1 << cells) - 1
    target = (n - 1) * n  # 左下角 = 集市

    # NB[i]：i 的四个邻居合并成的位掩码；SIDE[i] = (左, 右, 上, 下) 各是单比特掩码，越界记 0
    inb = lambda r, c: 0 <= r < n and 0 <= c < n
    NB = tuple(
        sum(1 << (nr * n + nc) for nr, nc in ((r - 1, c), (r + 1, c), (r, c - 1), (r, c + 1)) if inb(nr, nc))
        for r in range(n) for c in range(n)
    )
    SIDE = tuple(
        tuple(1 << (nr * n + nc) if inb(nr, nc) else 0 for nr, nc in ((r, c - 1), (r, c + 1), (r - 1, c), (r + 1, c)))
        for r in range(n) for c in range(n)
    )
    PB = tuple(1 << i for i in range(cells))  # 单比特掩码表，避免反复 1 << i
    tbit = PB[target]

    # 增量维护每个未访问格的"度"（未访问邻居数），并登记度 0 / 度 1 的格子：
    # 度 0 的内部格永远到不了；度 1 的内部格只能紧贴当前格成为下一步，否则就是死胡同。
    deg = [NB[i].bit_count() for i in range(cells)]
    ones = sum(PB[i] for i in range(cells) if deg[i] == 1 and i != target)
    zeros = 0

    ans = 0

    def dfs(pos: int, vis: int, left: int) -> None:
        """从 pos 出发走遍剩余 left 格、终点为集市的路径计数（枚举所有哈密顿路径）。"""
        nonlocal ans, ones, zeros
        if pos == target:  # 走到集市：必须同时走完全部格子，否则剩下的格子永远到不了
            ans += left == 0
            return
        U = full ^ vis
        # 剪枝 1（孤立区域）：左右都已封死（访问过或越界）而上、下都未访问，或相反。
        # 步出当前格后未访问区域会被切成两半，永远走不完。
        l, r, u, d = SIDE[pos]
        l_vis = not l or (l & vis)
        r_vis = not r or (r & vis)
        u_vis = not u or (u & vis)
        d_vis = not d or (d & vis)
        if (l_vis and r_vis and not u_vis and not d_vis) or (u_vis and d_vis and not l_vis and not r_vis):
            return
        avail = NB[pos] & U
        if not avail:  # 无路可走
            return
        if not (avail & tbit) and deg[target] == 0:  # 集市已被未访问格隔离
            return
        if zeros:  # 存在度 0 的内部格
            return
        # 剪枝 2（死胡同）：度 1 的内部格必须与当前格相邻，否则它只有"一进"没有"一出"
        forced, only = 0, -1
        f = ones
        while f:
            b = f & -f
            w = b.bit_length() - 1
            if w != pos:
                if not (NB[pos] & b):
                    return
                forced += 1
                only = w
            f ^= b
        if forced > 1:  # 两个度 1 格不可能都成为下一步
            return
        if forced:  # 唯一度 1 邻居是唯一合法的下一步
            moves = (only,)
        else:
            moves = sorted((deg[x], x) for x in bits(avail))  # 度数小的先走，尽早撞墙
        for _, x in moves:
            if x == target and left > 1:
                continue
            # 访问 pos：邻居的度 -1，并同步维护 ones/zeros 两个登记表
            f = NB[pos] & U
            while f:
                b = f & -f
                w = b.bit_length() - 1
                deg[w] -= 1
                if w != target:
                    if deg[w] == 1:
                        zeros &= ~b
                        ones |= b
                    elif deg[w] == 0:
                        ones &= ~b
                        zeros |= b
                    else:
                        ones &= ~b
                        zeros &= ~b
                f ^= b
            ones &= ~PB[pos]
            zeros &= ~PB[pos]
            dfs(x, vis | PB[pos], left - 1)
            # 回溯：度 +1，恢复登记表（pos 本身按原度数归位）
            f = NB[pos] & U
            while f:
                b = f & -f
                w = b.bit_length() - 1
                deg[w] += 1
                if w != target:
                    if deg[w] == 1:
                        zeros &= ~b
                        ones |= b
                    elif deg[w] == 0:
                        ones &= ~b
                        zeros |= b
                    else:
                        ones &= ~b
                        zeros &= ~b
                f ^= b
            if deg[pos] == 1:
                ones |= PB[pos]
            elif deg[pos] == 0:
                zeros |= PB[pos]

    dfs(0, 1, cells - 1)
    print(ans)


if __name__ == "__main__":
    solve()