#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 20:30
# update_at: 2026-09-30 20:30

import sys
from functools import cache


def count_upto(x: int) -> int:
    """数位 DP：[0, x] 里不含数字 4、也不含子串 62 的数有多少个。"""
    if x < 0:
        return 0                                  # n 可能为 0，此时区间下界比 0 还小
    digits = list(map(int, str(x)))

    @cache
    def dfs(pos: int, tight: bool, prev6: bool) -> int:
        """从高位 pos 起往低位填：前一位是否为 6、当前是否被上界掐住时，合法后缀的个数。

        前导零无需单独记录：0 既不是 4 也不会和 6 拼出 62，而真正的 6 只会
        出现在首位之后，所以只记"前一位是不是 6"就足以排除 62。
        """
        if pos == len(digits):
            return 1                              # 整数构造完成（含 0 本身）
        up = digits[pos] if tight else 9
        return sum(
            dfs(pos + 1, tight and d == up, d == 6)   # 只有贴着上界走才继续保持 tight
            for d in range(up + 1)
            if d != 4 and not (prev6 and d == 2)      # 跳过 4 与 62 的第二个 2
        )

    return dfs(0, True, False)


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    for low in data:                              # 每次取一对 (n, m)，读到 0 0 结束
        high = next(data)
        if low == 0 and high == 0:
            break
        # [n, m] 的个数 = [0, m] 的个数 − [0, n-1] 的个数
        out.append(str(count_upto(high) - count_upto(low - 1)))
    print('\n'.join(out))


if __name__ == "__main__":
    solve()
