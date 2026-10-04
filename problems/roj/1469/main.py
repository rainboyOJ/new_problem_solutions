#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 13:54
# update_at: 2026-09-30 13:54

import sys


def union_of_ends(seg: bytes, k: int) -> int:
    """以 seg[0] 为子串左端点时，能凑出多少个不同右端点的 A+B+A 子串。

    第二个 A 起点偏移 i 满足 lcp(0,i) >= k 且 i >= k+1（B 非空）时，右端点
    落在连续区间 [i+k-1, i+min(lcp,i-1)-1]；区间左端点随 i 递增，顺序扫一遍
    求区间并，同一右端点（同一子串）就只数一次。
    """
    m = len(seg)
    z = [0] * m          # z[i] = lcp(seg, seg[i:])，经典 Z 数组
    box_l = box_r = 0    # Z 盒：seg[box_l..box_r) 与开头同段
    covered = -1          # 区间并已覆盖到的最右偏移
    ans = 0

    for i in range(1, m):
        zi = 0
        if i < box_r:
            zi = box_r - i
            v = z[i - box_l]
            if v < zi:
                zi = v    # 没顶到盒边：z[i] 已精确，免去逐字符比较
            else:
                # 顶到盒边：从盒边界继续向后逐字符延伸
                while i + zi < m and seg[zi] == seg[i + zi]:
                    zi += 1
        else:
            while i + zi < m and seg[zi] == seg[i + zi]:  # 盒外从头求 lcp
                zi += 1
        if i + zi > box_r:
            box_l, box_r = i, i + zi

        # 偏移 i 贡献的右端点区间：i>k 即 B 至少 1 个字符，zi>=k 即 |A|>=k
        if i > k and zi >= k:
            u = i - 1 if i - 1 < zi else zi   # min(lcp, i-1)：B 不能盖住第二个 A
            b = i + k - 1                      # 区间左端
            e = i + u - 1                      # 区间右端
            if e > covered:
                if b > covered:
                    ans += e - b + 1           # 整段新区间
                else:
                    ans += e - covered         # 只有尾巴是新的
                covered = e
        z[i] = zi                              # 供更后面的 Z 盒取用

    return ans


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    text = next(data)
    k = int(next(data))
    print(sum(union_of_ends(text[start:], k) for start in range(len(text))))


if __name__ == "__main__":
    solve()
