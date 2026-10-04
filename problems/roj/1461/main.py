#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 12:10
# update_at: 2026-09-30 12:10

import sys

MASK = (1 << 64) - 1  # 取模用位与代替 %：底数为奇数时 2^64 取模仍是合法滚动哈希
BASE = 1_000_003      # 奇数底数，保证块哈希能用前缀哈希 O(1) 还原


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)
    a = [next(data) for _ in range(n)]

    # 幂表、正向前缀哈希、反向（从右往左）前缀哈希，三张表都是 O(n) 预处理
    pw = [1] * (n + 1)
    pre = [0] * (n + 1)   # pre[i] = a[0..i-1] 的哈希
    suf = [0] * (n + 1)   # suf[i] = a[i..n-1] 的哈希（越靠左权重越高）
    for i in range(1, n + 1):
        pw[i] = (pw[i - 1] * BASE) & MASK
    for i, x in enumerate(a):
        pre[i + 1] = (pre[i] * BASE + x) & MASK
    for i in range(n - 1, -1, -1):
        suf[i] = (suf[i + 1] * BASE + a[i]) & MASK

    best, ks = 0, []
    for k in range(1, n + 1):
        wk = pw[k]
        # 每 k 个珠子的块取一次（末尾不足 k 的丢弃）；正读与倒读哈希取小者，
        # 于是 (1,2,3) 与 (3,2,1) 落到同一个编码，去重后即为不同子串数
        cnt = len({
            min((pre[p + k] - pre[p] * wk) & MASK, (suf[p] - suf[p + k] * wk) & MASK)
            for p in range(0, n - k + 1, k)
        })
        if cnt > best:
            best, ks = cnt, [k]
        elif cnt == best:
            ks.append(k)

    print(best, len(ks))
    print(' '.join(map(str, ks)))


if __name__ == "__main__":
    solve()
