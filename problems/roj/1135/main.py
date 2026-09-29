#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 20:26
# update_at: 2026-09-29 20:26

import sys

# 互补关系只有两对：A↔T、G↔C；对照着写 "ATGC"/"TACG" 就是一张双向翻译表
COMPLEMENT = str.maketrans("ATGC", "TACG")


def solve() -> None:
    chain: str = sys.stdin.readline().strip()

    # 每位碱基的互补碱基只由自己决定，整条链可以交给 translate 一次替换完
    print(chain.translate(COMPLEMENT))


if __name__ == "__main__":
    solve()
