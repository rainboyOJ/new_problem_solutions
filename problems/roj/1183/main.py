#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 22:28
# update_at: 2026-09-29 22:28

import sys

ELDERLY_AGE = 60  # 老年人门槛：年龄 >= 60 者优先看病


def visit_key(person: tuple[bytes, int, int]) -> tuple[bool, int, int]:
    """看病顺序键：老年人优先，老年人按年龄从大到小，登记序号兜底保持先来后到。"""
    _pid, age, idx = person
    # 非老年人的年龄不参与排序，统一记 0；同键由登记序号按输入先后打破平局
    return (age < ELDERLY_AGE, -age if age >= ELDERLY_AGE else 0, idx)


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    count = next(data)  # 病人个数
    # (ID, 年龄, 登记序号)，登记序号即输入行的先后，也是同组内的平局裁决
    people: list[tuple[bytes, int, int]] = [
        (pid, int(age), i) for i, (pid, age) in enumerate(zip(data, data))
    ]
    people.sort(key=visit_key)
    print(b'\n'.join(pid for pid, _, _ in people).decode())


if __name__ == "__main__":
    solve()
