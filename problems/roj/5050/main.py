#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-09 00:06
# update_at: 2026-10-09 00:06

import sys


def solve() -> None:
    """读入 n 与国家名，按字典序（逐字符编码值，区分大小写）升序逐行输出。"""
    data = iter(sys.stdin.buffer.read().split())
    n = int(next(data))
    names = [next(data).decode() for _ in range(n)]  # 国名不含空格，按空白切分即可
    # Python 的 str < 按码点逐位比较，与 C++ std::string 在纯 ASCII 数据上完全一致
    print('\n'.join(sorted(names)))


if __name__ == "__main__":
    solve()
