#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 23:17
# update_at: 2026-10-08 23:17

import sys
from collections.abc import Iterator


def nonzero_triples(data: Iterator[int], n: int, m: int) -> Iterator[str]:
    """按行优先依次消费矩阵的 n×m 个数，只产出非 0 元素的「行号 列号 值」。"""
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            value = next(data, 0)  # 输入不完整时按 0 处理，不会继续吐元素
            if value != 0:
                yield f"{i} {j} {value}"


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data, 0), next(data, 0)  # 无输入时 n = 0，循环不执行，静默结束

    # 边读边写：全 0 矩阵时一次也不写，输出严格是 0 字节（而不是一个空行）。
    for triple in nonzero_triples(data, n, m):
        sys.stdout.write(triple + "\n")


if __name__ == "__main__":
    solve()
