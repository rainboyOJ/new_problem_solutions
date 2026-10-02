#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 18:44
# update_at: 2026-10-02 19:40

import sys
from array import array

MOD = 10**9 + 7  # 题面要求的模数


def range_add(b1: array, b2: array, l: int, r: int, delta: int) -> None:
    """区间 [l, r] 加 delta：差分树打两处标记，前缀和处再还原成区间和。

    b1 存差分量本身，b2 存差分量乘 (下标-1)，于是前 i 项和 = i·Σb1 − Σb2。
    """
    size = len(b1) - 1
    lo, hi = delta * (l - 1), delta * r  # b2 的两处增量：l 处 +delta*(l-1)，r+1 处 -delta*r
    i = l
    while i <= size:
        b1[i] += delta
        b2[i] += lo
        i += i & -i
    i = r + 1
    while i <= size:
        b1[i] -= delta
        b2[i] -= hi
        i += i & -i


def prefix_sum(b1: array, b2: array, i: int) -> int:
    """下标 1..i 的元素和（含全部区间加修正）：i·Σb1 − Σb2。"""
    s1 = s2 = 0
    j = i
    while j:
        s1 += b1[j]
        s2 += b2[j]
        j &= j - 1  # 清掉最低位 1，等价于 j -= j & -j
    return s1 * i - s2


def catalan_table(n: int) -> array:
    """方案数表 cnt[t] = C(2t, t)/(t+1)：递推 C_t = C_{t-1}·(4t-2)/(t+1)，顺带线性求逆元。"""
    inv = array("q", [0]) * (n + 2)
    inv[1] = 1
    for i in range(2, n + 2):
        inv[i] = MOD - MOD // i * inv[MOD % i] % MOD
    cnt = array("q", [0]) * (n + 1)
    cnt[1] = 1  # 区间长度最短为 2，t 最小为 1
    for t in range(2, n + 1):
        cnt[t] = cnt[t - 1] * (4 * t - 2) % MOD * inv[t + 1] % MOD
    return cnt


def solve() -> None:
    data = sys.stdin.buffer
    n, m = map(int, data.readline().split())
    size = n + n  # 序列长度 2n，下标 1..2n

    # 静态前缀和：s0 覆盖全序列；se0 把偶数位 i=2j 压成槽 j 后的前缀和。
    # 奇数位的和不必再建一棵树：奇数位 = 全序列 - 偶数位。
    s0 = array("q", [0])
    se0 = array("q", [0])
    total = even_total = 0
    for i, x in enumerate(map(int, data.readline().split()), 1):
        total += x
        s0.append(total)
        if i % 2 == 0:
            even_total += x  # 只累计偶数位，不能直接抄全序列前缀和
            se0.append(even_total)

    u = array("q", [0]) * (size + 1)  # 全序列区间加：差分量
    v = array("q", [0]) * (size + 1)  # 全序列区间加：差分量 * (下标-1)
    ue = array("q", [0]) * (n + 1)  # 偶数位（按槽压缩）区间加：差分量
    ve = array("q", [0]) * (n + 1)  # 偶数位（按槽压缩）区间加：差分量 * (槽-1)

    cnt = catalan_table(n)  # 方案数只取决于区间长度，与数值无关
    out: list[str] = []

    for _ in range(m):
        op = data.readline().split()
        l, r = int(op[1]), int(op[2])
        if op[0] == b"0":  # 0 l r val：区间加（保证不破坏有序性）
            val = int(op[3])
            range_add(u, v, l, r, val)
            even_first = l + (l & 1)  # [l, r] 内第一个偶数位
            even_last = r - (r & 1)  # [l, r] 内最后一个偶数位
            if even_first <= even_last:
                range_add(ue, ve, even_first // 2, even_last // 2, val)
        else:  # 1 l r：求区间分离后的最大差距、最小差距和方案数
            t = (r - l + 1) >> 1  # 区间长度的一半 = 每个子序列的长度
            mid = r - t  # 后 t 个的起点 - 1 = 前 t 个的终点，两端各取一半正好错开
            high = s0[r] + prefix_sum(u, v, r)
            near_mid = s0[mid] + prefix_sum(u, v, mid)
            low = s0[l - 1] + prefix_sum(u, v, l - 1)
            gap = high - 2 * near_mid + low  # 最大差距 = 后 t 个之和 - 前 t 个之和
            even = (
                se0[r >> 1] + prefix_sum(ue, ve, r >> 1)
                - se0[(l - 1) >> 1] - prefix_sum(ue, ve, (l - 1) >> 1)
            )
            full = high - low  # 区间总和 = 奇数位之和 + 偶数位之和
            # 最小差距 = 相邻配对之差和；l 为奇数时偶数位在每对后面，l 为偶数时相反
            near = even + even - full if l & 1 else full - even - even
            out.append(f"{gap % MOD} {near % MOD} {cnt[t]}")

    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()
