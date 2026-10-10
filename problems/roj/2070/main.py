#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 07:07
# update_at: 2026-10-08 07:07

import sys
from collections import defaultdict

LIMIT = 100000   # 五位素数都小于十万，筛表大小取到这里

type Layouts = list[str]        # 每个解按行拼成的 25 位数字串
type Digits = dict[int, tuple[int, ...]]  # 候选素数 -> 它的五位数字
type Grouped = dict[tuple[int, int], list[int]]  # (首位, 末位) -> 候选素数


def sieve(n: int) -> bytearray:
    """返回长度为 n 的标记表，第 p 位为 1 表示 p 是素数。"""
    flag = bytearray([1]) * n
    flag[0] = flag[1] = 0
    for i in range(2, int(n**0.5) + 1):
        if flag[i]:
            flag[i * i :: i] = bytearray(len(range(i * i, n, i)))
    return flag


def mk(a: int, b: int, c: int, d: int, e: int) -> int:
    """把五个数位按从左到右拼成五位数，用来直接查合法线集合。"""
    return ((((a * 10 + b) * 10 + c) * 10 + d) * 10 + e)


def layouts(S: int, D: int) -> Layouts:
    """枚举全部解：每条线都是数位和恰为 S 的五位素数，左上角固定为 D。

    先定两条共享中心点的对角线（锁死四角与中心），再定四条边框线；
    内部四格由行 1/行 3/列 1/列 3 的数位和反推，最后校验第 2 行、第 2 列。
    """
    prime = sieve(LIMIT)
    cand = [p for p in range(10000, LIMIT) if prime[p] and sum(map(int, str(p))) == S]
    if not cand:
        return []
    valid = set(cand)  # 一条线合法 ⇔ 它本身是候选素数（首位非零、数位和 = S 一并满足）
    dig: Digits = {p: tuple(int(ch) for ch in str(p)) for p in cand}
    head_tail: Grouped = defaultdict(list)
    for p in cand:
        head_tail[p // 10000, p % 10].append(p)

    res: Layouts = []
    for d1 in cand:
        if dig[d1][0] != D:
            continue                          # 主对角线首位就是左上角
        e2, mid, e4 = dig[d1][1], dig[d1][2], dig[d1][3]
        for d2 in cand:
            if dig[d2][2] != mid:
                continue                      # 副对角线必须穿过同一个中心点
            # 副对角线也按从左到右读：第 1 位是左下角，第 5 位是右上角
            x40, f4, f2, x04 = dig[d2][0], dig[d2][1], dig[d2][3], dig[d2][4]
            x44 = dig[d1][4]                  # 右下角
            for r0 in head_tail[D, x04]:      # 第 0 行：首尾为左上角、右上角
                b, c, d = dig[r0][1], dig[r0][2], dig[r0][3]
                for r4 in head_tail[x40, x44]:  # 第 4 行：首尾为左下角、右下角
                    v, w, x = dig[r4][1], dig[r4][2], dig[r4][3]
                    m = S - b - e2 - f4 - v   # 列 1 的数位和定出 g[2][1]
                    o = S - d - f2 - e4 - x   # 列 3 的数位和定出 g[2][3]
                    # 这两格由和推出，必须在 0~9 内，且填好后列 1、列 3 都是合法线
                    mid_ok = (
                        0 <= m <= 9
                        and 0 <= o <= 9
                        and mk(b, e2, m, f4, v) in valid
                        and mk(d, f2, o, e4, x) in valid
                    )
                    if not mid_ok:
                        continue
                    for c0 in head_tail[D, x40]:  # 第 0 列：首尾为左上角、左下角
                        g11, l, q = dig[c0][1], dig[c0][2], dig[c0][3]
                        for c4 in head_tail[x04, x44]:  # 第 4 列：首尾为右上角、右下角
                            i, n, s = dig[c4][1], dig[c4][2], dig[c4][3]
                            h = S - g11 - e2 - f2 - i  # 行 1 的数位和定出 g[1][2]
                            r = S - q - f4 - e4 - s    # 行 3 的数位和定出 g[3][2]
                            # 同理：这两格必须落在 0~9，填好后行 1、行 3 都要是合法线
                            edge_ok = (
                                0 <= h <= 9
                                and 0 <= r <= 9
                                and mk(g11, e2, h, f2, i) in valid
                                and mk(q, f4, r, e4, s) in valid
                            )
                            if not edge_ok:
                                continue
                            # 最后两个和约束：第 2 行、第 2 列也必须是合法线
                            row2_ok = mk(l, m, mid, o, n) in valid
                            col2_ok = row2_ok and mk(c, h, mid, r, w) in valid
                            if not col2_ok:
                                continue
                            res.append(
                                f"{D}{b}{c}{d}{x04}"
                                f"{g11}{e2}{h}{f2}{i}"
                                f"{l}{m}{mid}{o}{n}"
                                f"{q}{f4}{r}{e4}{s}"
                                f"{x40}{v}{w}{x}{x44}"
                            )
    return res


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    S, D = next(data), next(data)  # 数位和、左上角固定数字

    ans = layouts(S, D)
    if not ans:
        print("NONE")
        return
    ans.sort()  # 与 25 位数升序一致
    out: list[str] = []
    for k, layout in enumerate(ans):
        if k:
            out.append("")  # 两组方案之间空一行
        out += [layout[r * 5 : r * 5 + 5] for r in range(5)]
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
