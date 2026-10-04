#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47


def is_type_a(x: int) -> bool:
    """判断正整数 x 化为二进制后 1 的个数是否严格多于 0 的个数。"""
    c1 = x.bit_count()
    c0 = x.bit_length() - c1
    return c1 > c0


def solve() -> None:
    # 统计 1~1000 中 A 类数数量，其余为 B 类数
    total = 1000
    cnt_a = sum(1 for i in range(1, total + 1) if is_type_a(i))
    print(f"{cnt_a} {total - cnt_a}")


if __name__ == "__main__":
    solve()
