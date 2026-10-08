#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-07 11:40
# update_at: 2026-10-07 11:40

import sys
from functools import cache

MOD = 17    # 整除模数
INV10 = 12  # 10 在模 17 下的逆元：10 * 12 = 120 ≡ 1 (mod 17)

type Multiset = tuple[int, ...]  # 数字 0..9 各自剩余的重数，长度为 10
type RemDist = tuple[int, ...]   # 余数分布，下标 t 对应「数值 ≡ t (mod 17)」的个数


@cache
def rem_dist(ms: Multiset) -> RemDist:
    """用 ms 里的数字拼出的所有不同字符串的余数分布。

    按最低位 d 递推：X = 10 * X' + d，X ≡ t 等价于 X' ≡ (t - d) * 10^{-1} (mod 17)。
    分支只按数字取值枚举（不按字符下标），同一数字的多份拷贝不会重复计入，
    因此统计到的天然是「不同字符串」的个数，不需要再除以重数阶乘。
    """
    if not any(ms):                                  # 空多重集：空串的值为 0
        return (1,) + (0,) * (MOD - 1)
    out = [0] * MOD
    for d, c in enumerate(ms):
        if not c:
            continue
        sub = rem_dist(ms[:d] + (c - 1,) + ms[d + 1:])          # 去掉一个 d
        for t in range(MOD):
            out[t] += sub[(t - d) * INV10 % MOD]                # 反推低位之前的余数
    return tuple(out)


def nth_number(ms: Multiset, k: int, n: int, pow10: list[int]) -> str:
    """逐位试填，求满足条件的第 k 小数（前缀 mod 17 记作 p，剩余位数记作 m）。"""
    p, ans = 0, []
    for i in range(n):
        m = n - i                                            # 含当前位在内还剩多少位
        for d in range(10):
            if not ms[d] or (i == 0 and d == 0):             # 没有该数字 / 前导零
                continue
            np = (p * 10 + d) % MOD
            nxt = ms[:d] + (ms[d] - 1,) + ms[d + 1:]
            # 整个数 ≡ np * 10^{m-1} + X，要求 ≡ 0，故后缀 X 必须 ≡ (-np) * 10^{m-1}
            cnt = rem_dist(nxt)[(MOD - np) * pow10[m - 1] % MOD]
            if k > cnt:
                k -= cnt                                     # 这一支的方案全部更小，跳过
                continue
            ans.append(chr(48 + d))
            p, ms = np, nxt
            break                                                # 当前位定下，进入下一位
    return "".join(ans)


def solve() -> None:
    s, K = sys.stdin.buffer.read().split()
    n = len(s)
    digits = [b - 48 for b in s]
    ms = tuple(digits.count(d) for d in range(10))            # 数字多重集

    pow10 = [1] * (n + 1)                                     # 10 的幂（模 17）
    for i in range(1, n + 1):
        pow10[i] = pow10[i - 1] * 10 % MOD

    print(nth_number(ms, int(K), n, pow10))


if __name__ == "__main__":
    solve()
