#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 12:10
# update_at: 2026-10-01 12:10

import sys

MOD = (1 << 61) - 1  # Mersenne 素数：竖向折叠在 2^b 进制下对它取模（数据随机，单哈希足够）


def row_hashes(s: str, w: int) -> list[int]:
    """一行里所有长度为 w 的窗口，各拼成 w 位二进制整数指纹（精确值）。"""
    bits = int(s, 2)  # 整行读成一个二进制大整数，左端在高位
    full = (1 << w) - 1
    n = len(s)
    # 第 c 列的窗口 = (整行 >> (n - c - w)) 的低 w 位
    return [(bits >> (n - c - w)) & full for c in range(n - w + 1)]


def solve() -> None:
    it = iter(sys.stdin.buffer.read().split())
    m, n, a, b = (int(next(it)) for _ in range(4))
    rows = [next(it).decode() for _ in range(m)]        # 原矩阵 M 行字符串
    q = int(next(it))

    # 每个询问读 A 行、每行 B 列，按行主序拼成一个位串；重复矩阵去重后共享一次判定
    queries: dict[str, list[int]] = {}
    for i in range(q):
        queries.setdefault(''.join(next(it).decode() for _ in range(a)), []).append(i)
    q_hashes = {int(s, 2) % MOD: s for s in queries}    # 指纹 → 询问矩阵原文

    ans = [0] * q
    if a <= m and b <= n:                               # 询问比原矩阵还大时必然找不到
        fold = [[h % MOD for h in row_hashes(s, b)] for s in rows]  # 每行窗口指纹（mod 后）
        B = (1 << b) % MOD                              # 竖向折叠的进制 2^b
        if a == 1:                                      # 单行没有竖向折叠，直接查行内窗口
            table = set()
            for s in rows:
                table.update(h % MOD for h in row_hashes(s, b))
            for h, s in q_hashes.items():
                if h in table:
                    for i in queries[s]:
                        ans[i] = 1
        else:
            ncol = n - b + 1
            # H[c] = 以当前行为底的 a 行窗口在列 c 的指纹：
            # sum(第 r-k 行窗口指纹 * B^k)，顶行权 B^(a-1)（与询问位串的高位对齐）
            H = [0] * ncol
            for i in range(a - 1, -1, -1):
                pw = pow(B, a - 1 - i, MOD)
                Hi = fold[i]
                H = [(h + r * pw) % MOD for h, r in zip(H, Hi)]
            top_pow = pow(B, a - 1, MOD)                # 滑出行指纹的权
            for r in range(a - 1, m):
                if r > a - 1:                           # 底行滑入第 r 行、顶行滑出第 r-a 行
                    out_row, in_row = fold[r - a], fold[r]
                    H = [((h - o * top_pow) * B + i_) % MOD
                         for h, o, i_ in zip(H, out_row, in_row)]
                for c, h in enumerate(H):               # 逐列查指纹集合
                    s = q_hashes.get(h)
                    if s is not None:
                        for i in queries[s]:
                            ans[i] = 1

    print('\n'.join(map(str, ans)))


if __name__ == "__main__":
    solve()
