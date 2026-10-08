#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 22:35
# update_at: 2026-10-08 22:37

def solve() -> None:
    """本题无输入：由小到大输出所有形如 aabb 的四位完全平方数，每行一个。"""
    # 底数范围：31^2 = 961 < 1000、100^2 = 10000，故四位完全平方数的底数 k ∈ [32, 99]
    squares = (k * k for k in range(32, 100))
    # 前两位相同 ⇔ 千位 == 百位；后两位相同 ⇔ 十位 == 个位
    aabb_squares = (n for n in squares
                    if n // 1000 == n // 100 % 10 and n // 10 % 10 == n % 10)
    print('\n'.join(map(str, aabb_squares)))


if __name__ == "__main__":
    solve()
