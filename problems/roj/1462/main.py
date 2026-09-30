#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 12:40
# update_at: 2026-09-30 12:40

import sys


def anti_manacher(s: bytes) -> int:
    """统计 01 串中反对称子串的个数。

    对每个缝隙 g 求 f[g]：以 g 为中心、左右两侧字符必须"不等"的最大配对数
    （半径）。半径从 1 到 f[g] 的每一段都是反对称子串，所以答案为 sum(f)。
    把 Manacher 的"相等"比较换成"不等"：若区间 [l, r] 关于缝隙 cg 反对称，
    则右半边的缝隙 i 能从镜像缝隙 l+r-1-i 继承半径 min(f[mirror], r-i)，
    剩下的比较都发生在旧区间右端之外，总比较次数均摊 O(len)。
    """
    n = len(s)
    f = [0] * (n - 1)  # f[g]：缝隙 g 两侧最多配出多少对"不等"
    ans = 0
    l, r = 0, -1       # 已知最靠右的反对称区间 [l, r]，初始为空
    for i in range(n - 1):
        if i < r:
            k = min(f[l + r - 1 - i], r - i)  # 镜像缝隙必在左半边且已计算
        else:
            k = 0
        while i - k >= 0 and i + 1 + k < n and s[i - k] != s[i + 1 + k]:
            k += 1
        f[i] = k
        ans += k
        if k and i + k > r:  # 摸到更靠右的反对称区间才更新
            l, r = i - k + 1, i + k
    return ans


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])  # 题面的 N，与 len(s) 相同，仅作输入格式注解
    s = data[1]
    print(anti_manacher(s))


if __name__ == "__main__":
    solve()
