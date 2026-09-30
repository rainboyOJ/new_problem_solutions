#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 23:20
# update_at: 2026-09-30 23:20

from math import isqrt
from sys import stdin

ORZ = "Orz, I cannot find x!"


def mul_inverse(y: int, z: int, p: int) -> int | None:
    """解 x*y ≡ z (mod p)：返回使 x*y≡z 的最小非负 x，无解返回 None。

    p 是质数，y%p≠0 时费马小定理给出逆元 y^(p-2)；y%p=0 时只有 z%p=0 才有解，
    且任何 x 都行，最小取 0。
    """
    z %= p
    y %= p
    if y == 0:
        return 0 if z == 0 else None
    return z * pow(y, p - 2, p) % p


def discrete_log(y: int, z: int, p: int) -> int | None:
    """解 y^x ≡ z (mod p) 的最小非负 x（BSGS），无解返回 None。

    p 是质数：先特判 z≡1（x=0）与 y≡0，否则 gcd(y,p)=1，
    写 x = i*m - j（i≥1, 0≤j<m），方程改写成 y^(i*m) = z*y^j 分表查找；
    每个 i 对应 x 的一个互不重叠区间，所以首个命中的 i 里取最大的 j 就是最小 x。
    """
    z %= p
    y %= p
    if z == 1:
        return 0  # x=0 时 y^0=1
    if y == 0:
        return 1 if z == 0 else None  # y≡0 时 x≥1 都得 0

    m = isqrt(p - 1) + 1  # 分表块长，覆盖指数范围 [1, p-1]
    baby = {z * pow(y, j, p) % p: j for j in range(m)}  # 同值保留最大的 j，x=i*m-j 才最小
    step = pow(y, m, p)
    cur = step
    for i in range(1, m + 1):
        j = baby.get(cur)
        if j is not None:
            return i * m - j
        cur = cur * step % p
    return None


def solve() -> None:
    it = iter(stdin.buffer.read().split())
    T, K = int(next(it)), int(next(it))
    out: list[str] = []
    for _ in range(T):
        y, z, p = int(next(it)), int(next(it)), int(next(it))
        if K == 1:
            out.append(str(pow(y, z, p)))
        elif K == 2:
            x = mul_inverse(y, z, p)
            out.append(ORZ if x is None else str(x))
        else:
            x = discrete_log(y, z, p)
            out.append(ORZ if x is None else str(x))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
