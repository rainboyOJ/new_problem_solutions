#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 19:38
# update_at: 2026-09-29 19:38

import sys


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)

    carpets = [(next(data), next(data), next(data), next(data)) for _ in range(n)]

    x, y = next(data), next(data)

    # 编号大的是后铺的，覆盖在上面：从后往前找到第一张盖住 (x, y) 的地毯即答案。
    # 盖住 = a <= x <= a+g 且 b <= y <= b+k（边界上的点也算被覆盖）。
    ans = next(
        (i for i in range(n, 0, -1) if (a := carpets[i - 1][0]) <= x <= a + carpets[i - 1][2]
            and (b := carpets[i - 1][1]) <= y <= b + carpets[i - 1][3]),
        -1,  # 一张都没盖住
    )

    print(ans)


if __name__ == "__main__":
    solve()
