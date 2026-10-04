#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:11
# update_at: 2026-09-30 23:11

import sys

MAX_S = 2 * 10**9
LIMIT = int(MAX_S**0.5) + 1   # 只筛到 sqrt(S)：指数 >= 2 的质因子必然落在这个范围内
BASES = (2, 3, 5, 7)          # n <= 2e9 时这 4 个底数的 Miller-Rabin 已能确定素性


def sieve(limit: int) -> tuple[list[int], bytearray]:
    """埃氏筛：返回 limit 以内的质数表，以及「是否合数」的标记表。"""
    composite = bytearray(limit + 1)
    for i in range(2, int(limit**0.5) + 1):
        if not composite[i]:
            composite[i * i :: i] = b"\x01" * ((limit - i * i) // i + 1)
    return [i for i in range(2, limit + 1) if not composite[i]], composite


PRIMES, COMPOSITE = sieve(LIMIT)


def is_prime(n: int) -> bool:
    """判断 n 是否为质数：小范围查筛表，大范围用 Miller-Rabin。

    n <= 2e9 远小于已知反例下界 3.2e9，底数 2、3、5、7 的强伪素数判定没有遗漏。
    """
    if n < 2:
        return False
    if n < LIMIT:
        return not COMPOSITE[n]
    d, s = n - 1, 0
    while not d & 1:
        d >>= 1
        s += 1
    for a in BASES:
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(s - 1):
            x = x * x % n
            if x == n - 1:
                break
        else:
            return False
    return True


def search(start: int, rest: int, cur: int, found: list[int]) -> None:
    """继续枚举：只能用第 start 个及之后的质数，编号段的乘积还差 rest，已确定部分为 cur。

    sigma(x) = (1+p1+...+p1^a1)*(1+p2+...+p2^a2)*... 是若干编号段之积，
    所以枚举 x 等价于把 rest 拆成若干个「1+p+...+p^a」再拼回去，质数只能从小到大用。
    """
    if rest == 1:                              # 编号段全部拆完，cur 就是一个答案
        found.append(cur)
        return
    if rest - 1 >= PRIMES[start] and is_prime(rest - 1):
        found.append(cur * (rest - 1))         # 编号段 (1+p) 一次收尾，对应指数取 1
    for j in range(start, len(PRIMES)):
        p = PRIMES[j]
        if p * p > rest:                       # p 的指数已只能取 1，交给上面那行收尾
            break
        pk, segment = p, 1 + p                 # pk = p^a，segment = 1+p+...+p^a
        while segment <= rest:
            if rest % segment == 0:
                search(j + 1, rest // segment, cur * pk, found)
            pk *= p
            segment += pk                      # 下一段是 1+p+...+p^(a+1)
    return


def divisor_sum_candidates(s: int) -> list[int]:
    """返回所有正约数之和等于 s 的正整数，升序。"""
    found: list[int] = []
    search(0, s, 1, found)
    found.sort()
    return found


def solve() -> None:
    out: list[str] = []
    for s in map(int, sys.stdin.buffer.read().split()):
        ans = divisor_sum_candidates(s)
        out.append(str(len(ans)))
        if ans:                                # m = 0 时第二行不输出
            out.append(" ".join(map(str, ans)))
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
