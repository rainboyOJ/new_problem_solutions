#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 18:40
# update_at: 2026-10-04 12:56

import sys


def rectangle(height: int, width: int, ch: bytes, solid: bool) -> bytes:
    """返回矩形画布：实心每一行都是 ch；空心只在四条边上画 ch，内部填空格。"""
    border = ch * width                                       # 上下两条边，也是实心的每一行
    middle = border if solid else ch + b" " * (width - 2) + ch  # 空心时中间行 = 左右边框 + 空白
    rows = [border] + [middle] * (height - 2) + [border]      # 高度 ≥ 3，首尾两行必为实边
    return b"\n".join(rows) + b"\n\n"                        # 末尾补一个空行，与标准程序一致


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    height, width = int(next(data)), int(next(data))  # 题面的 h、w
    ch = next(data)            # 填充字符
    fill = next(data) == b"1"  # d = 1 表示实心
    sys.stdout.buffer.write(rectangle(height, width, ch, fill))


if __name__ == "__main__":
    solve()
