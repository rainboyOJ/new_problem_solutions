#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 19:44
# update_at: 2026-10-08 19:44


def is_narcissistic(x: int) -> bool:
    """判断 x 是否为水仙花数：各位数字的立方和是否等于 x 本身。"""
    return sum(int(d) ** 3 for d in str(x)) == x


def solve() -> None:
    """本题无输入，枚举 100~999 并按由小到大输出所有水仙花数。"""
    # 从小到大遍历，输出天然有序；str 拆数位比 / 和 % 更短且不易写错。
    print('\n'.join(str(x) for x in range(100, 1000) if is_narcissistic(x)))


if __name__ == "__main__":
    solve()
