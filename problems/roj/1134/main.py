#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:26
# update_at: 2026-10-04 14:42

import re
import sys

# 合法标识符：首字符必须是字母或下划线，其后每个字符都是字母、数字或下划线
IDENTIFIER = re.compile(r'[A-Za-z_]\w*\Z', re.ASCII)  # \w 加 re.ASCII 后只认 [A-Za-z0-9_]


def solve() -> None:
    data = iter(sys.stdin.buffer.read().split())
    s: str = next(data).decode()

    # 保留字由题面保证不出现，所以只剩“形状”一条判定：整串匹配一次正则即可
    print('yes' if IDENTIFIER.match(s) else 'no')


if __name__ == "__main__":
    solve()
