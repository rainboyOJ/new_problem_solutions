#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 05:40
# update_at: 2026-10-02 05:40

import sys


def build(seg: str, out: list[str]) -> None:
    """递归构造 seg 这一段的 FBI 子树，把它的后序遍历字符追加到 out。"""
    # 串段类型只看 0/1 是否同时出现：缺 1 全 0 为 B，缺 0 全 1 为 I，否则 F
    node = 'B' if '1' not in seg else 'I' if '0' not in seg else 'F'
    if len(seg) > 1:  # 题目保证串长是 2 的幂，对半分后两段等长
        mid = len(seg) // 2
        build(seg[:mid], out)
        build(seg[mid:], out)
    out.append(node)  # 后序：先左右子树，最后才记根


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))       # 串长为 2**n；构造只依赖串本身，n 仅用于校对格式
    s = next(data).decode()   # 01 串按原样读入，不做数值转换
    out: list[str] = []
    build(s, out)
    print(''.join(out))


if __name__ == "__main__":
    solve()
