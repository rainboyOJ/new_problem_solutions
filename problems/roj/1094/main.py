#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

n = int(input())

# 与 7 无关：不是 7 的倍数，且十进制各位都没有数字 7
print(sum(i * i for i in range(1, n + 1) if i % 7 and '7' not in str(i)))
