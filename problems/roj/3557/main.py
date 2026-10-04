#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-02 07:19
# update_at: 2026-10-02 07:19
from typing import List

p1, p2, p3 = map(int, input().split())  # 展开方式 / 重复个数 / 是否逆序
s = input().strip()


def expand(left: str, right: str) -> str:
    """展开 left-right 中间的片段：按 p1 决定填充形式，p2 决定每个字符重复几次，p3 决定是否逆序。"""
    if p1 == 3:  # 星号填充：个数 = 中间字符数 × p2
        return '*' * (p2 * (ord(right) - ord(left) - 1))
    seg = ''.join(chr(c) for c in range(ord(left) + 1, ord(right)))
    if p1 == 2 and left.isalpha():  # 只有字母子串才转大写，数字保持原样
        seg = seg.upper()
    if p3 == 2:
        seg = seg[::-1]
    return ''.join(ch * p2 for ch in seg)


def solve() -> None:
    """扫描每个减号：能展开就替换成展开结果，否则原样保留。"""
    res: List[str] = []
    for i, ch in enumerate(s):
        can_expand = (
            ch == '-'
            and 0 < i < len(s) - 1
            and ((s[i - 1].islower() and s[i + 1].islower())
                 or (s[i - 1].isdigit() and s[i + 1].isdigit()))
            and s[i - 1] < s[i + 1]  # 右边必须严格大于左边，否则保留减号
        )
        res.append(expand(s[i - 1], s[i + 1]) if can_expand else ch)
    print(''.join(res))


if __name__ == "__main__":
    solve()
