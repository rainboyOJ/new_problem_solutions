#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 23:27
# update_at: 2026-09-29 23:27

import sys


def hanoi(n: int, src: str, aux: str, dst: str) -> None:
    """把第 1~n 号盘从 src 柱借助 aux 柱移到 dst 柱，按移动顺序输出。"""
    if n == 1:
        sys.stdout.write(f"{src}->{n}->{dst}\n")
        return
    hanoi(n - 1, src, dst, aux)          # 先移走上面的 n-1 个盘
    sys.stdout.write(f"{src}->{n}->{dst}\n")
    hanoi(n - 1, aux, src, dst)          # 再把 n-1 个盘从辅助柱移过来


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    # 输入三根柱子依次：源、目的、辅助
    src, dst, aux = next(data).decode(), next(data).decode(), next(data).decode()
    hanoi(n, src, aux, dst)


if __name__ == "__main__":
    solve()
