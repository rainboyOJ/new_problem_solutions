#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 12:08
# update_at: 2026-10-02 12:12

import sys


def solve() -> None:
    lines = iter(sys.stdin.buffer)
    n, m = map(int, next(lines).split())

    # 朝向与职业按输入顺序读入：下标增大方向就是逆时针方向
    facing = [0] * n
    name = [b""] * n
    for i in range(n):
        f, job = next(lines).split()
        facing[i] = int(f)  # 0 = 朝圈内，1 = 朝圈外
        name[i] = job       # 职业两两不同，按位置存即可

    pos = 0  # 当前所在小人，从第 1 个（下标 0）开始
    for _ in range(m):
        a, s = map(int, next(lines).split())
        # 四种组合合并成一句：朝内时"左"使序号 -1、朝外时 +1，"右"相反，
        # 于是方向只取决于 a（0 左 / 1 右）与朝向是否相同——相异 +1，相同 -1。
        step = 1 if a != facing[pos] else -1
        pos = (pos + step * s) % n  # 环上直走 s 步 = 下标加减后取模

    print(name[pos].decode())


if __name__ == "__main__":
    solve()
