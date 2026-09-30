#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

from functools import cache
import sys

MOD = 10**9 + 7
POW10 = [pow(10, i, MOD) for i in range(21)]  # 10 的次幂模表


@cache
def dfs(pos: int, num_mod: int, sum_mod: int, is_limit: bool, digits: tuple[int, ...]) -> tuple[int, int, int]:
    """返回 (合法国数个数, 一次方和, 平方和) 模 MOD。"""
    if pos < 0:
        return (1, 0, 0) if num_mod != 0 and sum_mod != 0 else (0, 0, 0)

    limit = digits[pos] if is_limit else 9
    ans_cnt, ans_sum, ans_sq = 0, 0, 0

    for d in range(limit + 1):
        if d == 7:
            continue
        nxt_cnt, nxt_sum, nxt_sq = dfs(
            pos - 1,
            (num_mod * 10 + d) % 7,
            (sum_mod + d) % 7,
            is_limit and (d == limit),
            digits if is_limit and (d == limit) else (),
        )
        base = (d * POW10[pos]) % MOD
        base_sq = (base * base) % MOD

        ans_cnt = (ans_cnt + nxt_cnt) % MOD
        ans_sum = (ans_sum + nxt_sum + base * nxt_cnt) % MOD
        ans_sq = (ans_sq + nxt_sq + 2 * base * nxt_sum + base_sq * nxt_cnt) % MOD

    return (ans_cnt, ans_sum, ans_sq)


def count(n: int) -> int:
    """计算 [1, n] 内与 7 无关的数平方和。"""
    if n <= 0:
        return 0
    digits = tuple(int(c) for c in reversed(str(n)))
    return dfs(len(digits) - 1, 0, 0, True, digits)[2]


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return
    it = iter(tokens)
    t = int(next(it))
    out = [(count(int(r)) - count(int(l) - 1)) % MOD for l, r in ((next(it), next(it)) for _ in range(t))]
    sys.stdout.write("\n".join(map(str, out)) + "\n")


if __name__ == "__main__":
    solve()
