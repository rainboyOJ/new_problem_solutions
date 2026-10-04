#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-04-18 10:00
# update_at: 2026-04-18 10:00

import sys

# 大素数模数与进制基数，避免哈希冲突
MOD: int = (1 << 61) - 1
BASE: int = 2003


def solve() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return
    n = data[0]
    notes = data[1 : n + 1]

    # 音符差分数组：转调等价于相邻差分值完全一致
    # 长度为 L 的原主题对应长度为 L - 1 的差分序列
    diff = [notes[i] - notes[i - 1] + 100 for i in range(1, n)]
    m = len(diff)

    def check(k: int) -> bool:
        """判定差分数组中是否存在两个不重叠（原序列中间隔 >= k + 1）且长度为 k 的相同子串。"""
        power = pow(BASE, k, MOD)
        cur_hash = 0
        for i in range(k):
            cur_hash = (cur_hash * BASE + diff[i]) % MOD

        first_pos: dict[int, int] = {cur_hash: 0}
        for i in range(1, m - k + 1):
            cur_hash = (cur_hash * BASE + diff[i + k - 1] - diff[i - 1] * power) % MOD
            prev = first_pos.get(cur_hash)
            if prev is not None:
                # 差分串起点相差 >= k + 1，保证原音符子串互不重叠
                if i - prev >= k + 1:
                    return True
            else:
                first_pos[cur_hash] = i
        return False

    # 二分原音符主题长度 L（要求 L >= 5，对应差分串长度 k = L - 1 >= 4）
    low, high, ans = 4, n // 2, 0
    while low <= high:
        mid = (low + high) // 2
        if check(mid):
            ans = mid + 1
            low = mid + 1
        else:
            high = mid - 1

    print(ans if ans >= 5 else 0)


if __name__ == "__main__":
    solve()
