#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 11:39
# update_at: 2026-09-30 11:41

import sys
from collections.abc import Iterator


def execute_commands(commands: Iterator[str]) -> Iterator[str]:
    """处理图书馆操作序列，返回查询指令对应的结果流。"""
    library: set[str] = set()
    for line in commands:
        op, title = line.split(" ", 1)
        if op == "add":
            library.add(title)
        else:
            yield "yes" if title in library else "no"


def solve() -> None:
    lines = sys.stdin.read().splitlines()
    if not lines:
        return
    n = int(lines[0])
    command_lines = iter(lines[1 : n + 1])
    print("\n".join(execute_commands(command_lines)))


if __name__ == "__main__":
    solve()
