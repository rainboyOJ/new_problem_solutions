#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-05-22 19:17
# update_at: 2026-10-04 10:19

import sys


def solve() -> None:
    data = iter(map(lambda b: b.decode(), sys.stdin.buffer.read().split()))
    n = int(next(data))  # 题面的 n：接下来有 n 行「姓名 成绩」
    students: list[tuple[str, int]] = [
        (next(data), int(next(data))) for _ in range(n)
    ]
    # 成绩降序，同分名字字典序升序
    students.sort(key=lambda x: (-x[1], x[0]))
    print('\n'.join(f"{name} {score}" for name, score in students))


if __name__ == "__main__":
    solve()
