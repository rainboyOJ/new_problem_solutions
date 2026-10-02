#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 08:02
# update_at: 2026-10-02 08:02

import sys


def render(coeffs: list[int]) -> str:
    """把降幂排列的系数序列按题目格式渲染成多项式字符串。

    首项（最高次非零项）正号省略、负号直接作开头；其余非零项用 +/- 连接。
    高于 0 次且系数绝对值为 1 时省略系数 1；0 次项只输出系数。
    """
    out: list[str] = []
    for i, coeff in enumerate(coeffs):
        if not coeff:
            continue                                      # 只输出系数不为 0 的项
        deg = len(coeffs) - 1 - i                          # 本项次数：序列首项即最高次
        sign = "-" if coeff < 0 else "+" if out else ""    # 首项正号不输出
        head = "" if abs(coeff) == 1 and deg else str(abs(coeff))  # 省略的只是系数 1
        power = f"x^{deg}" if deg > 1 else "x" if deg else ""      # 指数部分三种形式
        out.append(sign + head + power)
    return "".join(out)


def solve() -> None:
    data = iter(map(int, sys.stdin.read().split()))
    n = next(data)                                     # 多项式次数
    coeffs = [next(data) for _ in range(n + 1)]        # 降幂排列的 n+1 个系数
    print(render(coeffs))


if __name__ == "__main__":
    solve()
