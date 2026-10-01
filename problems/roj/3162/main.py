#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 22:00
# update_at: 2026-10-01 22:00

import sys
from functools import cache


@cache
def suffixes(k: int, rank: int, high: bool) -> int:
    """k 块待排的板里，本块排第 rank 小、它是 high 位时，后面还有多少种排法。

    板长互不相同，"谁挨着谁"只由相对大小决定，所以剩下的 k 块板可以把长度重新
    编号成 1..k，rank 就是本块的编号——这是唯一需要的状态。角色只约束"下一块往
    哪跳"：高位板两侧都更低，下一块必须更矮；低位板两侧都更高，下一块必须更高。
    """
    if k == 1:
        return 1  # 只剩本块，后面没有板，跳不跳都合法
    if high:  # 下一块取第 1..rank-1 小，它在剥掉本块后仍是第 r 小
        return sum(suffixes(k - 1, r, False) for r in range(1, rank))
    return sum(suffixes(k - 1, r - 1, True) for r in range(rank + 1, k + 1))  # 本来更高的板，编号前移 1


def kth_fence(n: int, c: int) -> list[int]:
    """字典序第 c 个围栏：从左往右逐位试填，用"这一位取它时后面还有多少排法"整块跳过。"""
    avail = list(range(1, n + 1))  # 还没用上的板，长度升序；下标 i 就是第 i+1 小
    ans: list[int] = []
    high: bool | None = None  # None 表示本块是第一块，没有前一块来限制它
    lo, hi = 0, n - 1  # 本块的候选板在 avail 中的下标闭区间，由前一块的高低决定
    for _ in range(n):
        k = len(avail)
        roles = (True, False) if high is None else (not high,)  # 高低交错：角色与上一块相反
        # 试填顺序即字典序：候选板按长度升序，同一块板先数"它是高位"的方案（下一块更矮，更小）。
        for idx, role in ((idx, role) for idx in range(lo, hi + 1) for role in roles):
            ways = suffixes(k, idx + 1, role)
            if c > ways:  # 第 c 个落在这一块之后，整块跳过
                c -= ways
                continue
            ans.append(avail[idx])
            del avail[idx]
            high = role
            lo, hi = (0, idx - 1) if role else (idx, k - 2)  # 高位块只配更矮的板，低位块只配更高的板
            break
    return ans


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    cases = next(data)  # 询问组数
    out: list[str] = []
    for _ in range(cases):
        n, c = next(data), next(data)  # 木板数、要求的排名
        out.append(' '.join(map(str, kth_fence(n, c))))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
