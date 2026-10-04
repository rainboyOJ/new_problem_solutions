#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 07:05
# update_at: 2026-10-02 07:05

import sys
from math import comb


def count_rising(k: int, w: int) -> int:
    """数出二进制长度不超过 w 的、2^k 进制下位数严格递增且至少两位的数的个数。

    r 有 m 位（最高位为 a）时，二进制长度 = k*(m-1) + a 的位数，因为 r 的最高位
    就是最高位数字 a 所占的那 k 位里的最高有效位。

    固定 m 与最高位 a：其余 m-1 位必须从比 a 大的数字 {a+1..B-1} 里选，共
    C(B-1-a, m-1) 种。按 a 的位数 j 分段（a 落在 [2^(j-1), 2^j-1]），对
    C(B-1-a, m-1) 用 hockey-stick 公式求和即 C(B-2^(j-1), m) - C(B-2^j, m)。
    """
    B = 1 << k  # 2^k 进制的基数
    # 位数 m 的上界：k*(m-1) 位加上最高位至少 1 位不得超过 w；数字取自 1..B-1 故 m<=B-1
    m_max = min(B - 1, (w - 1) // k + 1)
    return sum(
        comb(B - (1 << (j - 1)), m) - comb(B - (1 << j), m)  # 最高位落在 [2^(j-1), 2^j-1]
        for m in range(2, m_max + 1)
        for j in range(1, min(k, w - k * (m - 1)) + 1)       # 长度约束：k*(m-1)+j <= w
    )


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    k, w = next(data), next(data)
    print(count_rising(k, w))


if __name__ == "__main__":
    solve()
