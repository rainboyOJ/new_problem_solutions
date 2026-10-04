#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:39
# update_at: 2026-09-30 20:39

import sys


def count_digits(n: int) -> list[int]:
    """统计 1..n 中每个数码出现的次数（n<=0 时全为 0），0 只统计真实数位上的。"""
    cnt = [0] * 10
    factor = 1                      # 当前数位的位权：1 个位、10 十位、100 百位……
    while factor <= n:
        high, cur, low = n // (factor * 10), n // factor % 10, n % factor

        # 1~9：按"当前位的数码 d 与 cur 的大小关系"把 [1,n] 分成三段计数
        for d in range(1, 10):
            if d < cur:
                cnt[d] += (high + 1) * factor    # 前缀 0..high 都能取满
            elif d == cur:
                cnt[d] += high * factor + low + 1  # 等值前缀只取到 low
            else:
                cnt[d] += high * factor          # 前缀只能取 0..high-1

        # 0：前缀不能为 0，否则该位是前导零、不是真实数位
        if cur:
            cnt[0] += high * factor              # 当前位非 0，后缀可取满 factor 个
        else:
            cnt[0] += (high - 1) * factor + low + 1  # cur==0 时 high 至少为 1
        factor *= 10
    return cnt


def solve() -> None:
    a, b = map(int, sys.stdin.buffer.read().split())
    # 区间计数用前缀和相减：[a,b] = [1,b] - [1,a-1]
    hi, lo = count_digits(b), count_digits(a - 1)
    print(' '.join(str(x - y) for x, y in zip(hi, lo)))


if __name__ == "__main__":
    solve()
