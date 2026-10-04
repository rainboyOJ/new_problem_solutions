#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-01 03:45
# update_at: 2026-10-01 03:45

import sys


def find_max_prefix(primitives: list[str], s: str) -> int:
    """计算字符串 s 能由基本元素集合拼出的最长前缀长度。"""
    n = len(s)
    dp = [False] * (n + 1)
    dp[0] = True
    ans = 0

    # 按元素长度分组，便于快速向前匹配
    by_len: dict[int, set[str]] = {}
    for p in primitives:
        by_len.setdefault(len(p), set()).add(p)

    lens = sorted(by_len.keys())

    for i in range(1, n + 1):
        for l in lens:
            if l > i:
                break
            if dp[i - l] and s[i - l:i] in by_len[l]:
                dp[i] = True
                ans = i
                break

    return ans


def solve() -> None:
    # 元素集合与长字符串 S 都可能跨多行，所以只按空白切 token，靠「单独一个 '.' token」分界
    data = iter(sys.stdin.buffer.read().split())

    first = next(data, None)                     # 空输入：沿用原来的 if not tokens 守卫
    if first is None:
        return

    # 不靠下标：'.' 之前的 token 依次是集合元素，之后剩下的 token 拼成长字符串 S
    primitives: list[str] = []
    token = first
    while token != b".":
        primitives.append(token.decode())
        token = next(data)                       # 题面保证有 '.'，缺分界符属非法输入
    s = "".join(token.decode() for token in data)

    ans = find_max_prefix(primitives, s)
    print(ans)


if __name__ == "__main__":
    solve()
