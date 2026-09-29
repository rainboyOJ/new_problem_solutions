#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:26
# update_at: 2026-09-29 20:26

import sys

# 环移规则表：26 个小写 + 26 个大写字母各自映到字母表上的后继，
# z→a、Z→A 由同一张表覆盖；未列出的字符（空格、标点、换行）查表失败即原样保留。
SUCCESSOR = str.maketrans(
    "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ",  # 源：26 小写 + 26 大写
    "bcdefghijklmnopqrstuvwxyza" "BCDEFGHIJKLMNOPQRSTUVWXYZA",  # 目标：各右移一位（尾回环）
)


def solve() -> None:
    text = sys.stdin.buffer.read().decode()
    # 换行不属于要加密的内容：先摘掉行尾换行，再由 print 补回恰好一个。
    print(text.translate(SUCCESSOR).rstrip("\n"))


if __name__ == "__main__":
    solve()
