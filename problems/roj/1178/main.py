#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-05-22 19:17
# update_at: 2026-05-22 19:17

import sys


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    students: list[tuple[str, int]] = [
        (data[i].decode(), int(data[i + 1])) for i in range(1, 2 * n, 2)
    ]
    # 成绩降序，同分名字字典序升序
    students.sort(key=lambda x: (-x[1], x[0]))
    print('\n'.join(f"{name} {score}" for name, score in students))


if __name__ == "__main__":
    solve()
