#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:26
# update_at: 2026-09-30 20:26

from functools import cache
import sys


def count_windy(n: int) -> int:
    """统计 [1, n] 内相邻数位差绝对值 >= 2 的正整数个数。"""
    if n <= 0:
        return 0
    digits = [int(c) for c in str(n)]

    @cache
    def dfs(pos: int, prev: int | None, is_limit: bool, is_num: bool) -> int:
        if pos == len(digits):
            return int(is_num)

        up = digits[pos] if is_limit else 9
        ans = 0
        if not is_num:
            # 这一位不选数字，继续跳过前导零
            ans += dfs(pos + 1, None, False, False)
            # 这一位选择作为最高位（不能填 0）
            for d in range(1, up + 1):
                ans += dfs(pos + 1, d, is_limit and d == up, True)
        else:
            # 已经有前缀数字，下一位必须与 prev 差绝对值 >= 2
            for d in range(up + 1):
                if abs(d - prev) >= 2:
                    ans += dfs(pos + 1, d, is_limit and d == up, True)
        return ans

    return dfs(0, None, True, False)


def solve() -> None:
    data = sys.stdin.read().split()
    if not data:
        return
    a, b = int(data[0]), int(data[1])
    print(count_windy(b) - count_windy(a - 1))


if __name__ == "__main__":
    solve()
