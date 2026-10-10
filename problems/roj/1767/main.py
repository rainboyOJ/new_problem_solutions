#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 00:09
# update_at: 2026-10-08 00:09

import sys

NEG = -10 ** 18  # 不可达状态的哨兵；合法得分一定 >= 0

# 类型别名（Python 3.12+ 的 type 语句），相当于 C++ 的 using / typedef
type States = list[int]           # 某区间残留串各形态（下标即 01 串的值）对应的最大得分
type Rules = list[tuple[int, int]]  # 2^k 条合并规则：二进制值 -> (新字符, 本次分数)


def join(pre: States, suf: States, rules: Rules | None) -> States:
    """把前缀残留串 S 与后缀单字符 b 拼成 S<<1|b；rules 非空表示这次恰好拼满 k 位，立即合并加分。"""
    if rules is None:
        out = [NEG] * (len(pre) * 2)
        for s, base in enumerate(pre):
            if base <= NEG // 2:
                continue                    # 前缀该形态不可达，整条拼法都不成立
            for b, tail in enumerate(suf):
                if tail <= NEG // 2:
                    continue                # 后缀该形态不可达，这条拼法也不成立
                val = base + tail
                if val > out[s << 1 | b]:
                    out[s << 1 | b] = val
        return out
    out = [NEG, NEG]
    for s, base in enumerate(pre):
        if base <= NEG // 2:
            continue
        for b, tail in enumerate(suf):
            if tail <= NEG // 2:
                continue
            ch, score = rules[s << 1 | b]
            if base + tail + score > out[ch]:
                out[ch] = base + tail + score
    return out


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    a = [0] + [next(data) for _ in range(n)]
    rules: Rules = [(next(data), next(data)) for _ in range(1 << k)]

    km1 = k - 1  # 每次合并净减少 k-1 个字符，这就是长度不变量
    # f[l, r]：把 a[l..r] 合并到不能再合并时，残留串各形态对应的最大得分。
    # 残留长度恒为 (r-l) % km1 + 1，所以表长正好是 2 ** 该长度。
    f: dict[tuple[int, int], States] = {}
    for i in range(1, n + 1):
        single = [NEG, NEG]  # 单字符区间只可能残留它自己
        single[a[i]] = 0
        f[i, i] = single

    for length in range(2, n + 1):
        rest = (length - 1) % km1     # 该区间残留长度 = rest + 1
        full = rest == 0              # 残留 1 个字符：这次拼接恰好凑满 k 位，要立即合并
        for l in range(1, n - length + 2):
            r = l + length - 1
            # 后缀 [mid+1, r] 必须以 1 个字符收尾，故 mid 以 k-1 为步长倒着取
            parts = [
                join(f[l, mid], f[mid + 1, r], rules if full else None)
                for mid in range(r - 1, l - 1, -km1)
            ]
            f[l, r] = [max(column) for column in zip(*parts)]

    print(max(f[1, n]))


if __name__ == "__main__":
    solve()
