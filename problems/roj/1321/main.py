#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 05:05
# update_at: 2026-09-30 05:08

import sys


def smallest_after_deletions(digits: str, s: int) -> str:
    """在 digits 中删去 s 位，返回剩下数字串能组成的正整数（去掉前导零）。

    维护一个单调不减的栈：新来的一位如果比栈顶小，就说明"栈顶那位靠左却更大"，
    删掉它一定比删掉当前位更划算，于是反复弹栈；扫完还有删除余量时，
    栈已经不减，剩下的名额只能从末尾花掉。
    """
    kept: list[str] = []
    budget = s  # 还剩几个删除名额
    for digit in digits:
        while budget and kept and kept[-1] > digit:  # 左侧更大且更靠前，删它
            kept.pop()
            budget -= 1
        kept.append(digit)
    if budget:  # kept 此时单调不减，末尾几位最大，删它们最划算
        del kept[len(kept) - budget:]
    return ''.join(kept).lstrip('0') or '0'  # 全 0（或精光）时题面要求输出 0


def solve() -> None:
    data = sys.stdin.read().split()
    n = data[0]
    s = int(data[1])
    print(smallest_after_deletions(n, s))


if __name__ == "__main__":
    solve()
