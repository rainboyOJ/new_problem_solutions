#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 21:33
# update_at: 2026-10-01 21:52

import sys


def match_once(p: int, s1: bytes, s2: bytes) -> tuple[int, int]:
    """从 s1 的下标 p 出发贪心匹配一整份 s2，返回（跨过的完整 s1 份数, 下一份内的起点）。

    每读满一份 s1 至少吃掉 s2 的一个字符（否则该字符根本不在 s1 里，会死循环），
    所以最多扫过 len(s2) 份 s1；调用方必须先用字符集检查排除无解情况。
    """
    j = 0                    # s2 中下一个待匹配的字符
    blocks, pos = 0, p
    while j < len(s2):
        if s1[pos] == s2[j]:
            j += 1
        pos += 1
        if pos == len(s1):   # 走完一份 s1，落到下一份的开头
            pos, blocks = 0, blocks + 1
    return blocks, pos


def max_copies(s1: bytes, s2: bytes, n1: int) -> int:
    """返回 s2 作为子序列最多能在 conn(s1, n1) 中出现多少次（贪心 + 倍增）。"""
    if not set(s2) <= set(s1):
        return 0                                     # s2 有字符不在 s1 里，一份都放不下

    L1 = len(s1)
    L2 = len(s2)
    # base[p]：从一份 s1 的下标 p 出发匹配完一份 s2，消耗的完整 s1 份数与落点。
    # 匹配是确定性的，所以「走 c 份 s2 后的状态」唯一，可以对状态做倍增。
    base = [match_once(p, s1, s2) for p in range(L1)]
    LOG = (n1 * L1 // L2 + 1).bit_length()           # 份数上限的二进制位数，够倍增到它
    up = [base]
    for _ in range(1, LOG):
        prev = up[-1]
        nxt: list[tuple[int, int]] = []
        for p in range(L1):
            blocks, q = prev[p]                      # 先走 2^(k-1) 份 s2，落在偏移 q
            more, q2 = prev[q]                       # 再走 2^(k-1) 份 s2
            nxt.append((blocks + more, q2))
        up.append(nxt)

    used, p, copies = 0, 0, 0
    for k in reversed(range(LOG)):                   # 从大步到小步，能加就加
        blocks, q = up[k][p]
        need = used + blocks + (q > 0)               # 落点不在份首时，当前这一份 s1 也被占用
        if need <= n1:
            used, p, copies = used + blocks, q, copies + (1 << k)
    return copies


def solve() -> None:
    raw = sys.stdin.buffer.read().rstrip()  # 输入末尾可能粘着一个 '}'（不是字符串内容），先把空格换行退掉
    data = raw.removesuffix(b'}').split()
    out: list[str] = []
    for group in range(0, len(data), 4):                 # 每组固定 4 个 token
        s2, n2, s1, n1 = data[group: group + 4]          # 题面的顺序：先 s2 n2，再 s1 n1
        # conn(s2, n2) 重复 m 次就是 s2 重复 m * n2 次，故 m = 最多份数 // n2
        out.append(str(max_copies(s1, s2, int(n1)) // int(n2)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
