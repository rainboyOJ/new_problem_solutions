#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys


def kmp_count(pat: str, text: str) -> int:
    """统计模式串 pat 在 text 中出现的次数（允许重叠），KMP 扫一遍。"""
    # 失配指针：fail[i] = pat[:i] 的最长相等真前后缀长度
    fail = [0] * len(pat)
    k = 0
    for i in range(1, len(pat)):
        while k and pat[i] != pat[k]:
            k = fail[k - 1]            # 沿失配链回退
        k += pat[i] == pat[k]          # 匹配上则延长一位
        fail[i] = k

    count = 0
    k = 0                              # 已匹配的 pat 前缀长度
    for ch in text:
        while k and ch != pat[k]:
            k = fail[k - 1]
        k += ch == pat[k]
        count += k == len(pat)         # 完整出现一次（重叠出现不被回退，天然支持）
        if k == len(pat):
            k = fail[k - 1]            # 继续找下一个可重叠出现
    return count


def solve() -> None:
    tokens = sys.stdin.read().split()
    out: list[str] = []

    if tokens[0].isdigit():                     # 样例格式：首行 T，后跟 T 组
        T = int(tokens[0])                      # 测试组数
        for pos in range(1, 2 * T + 1, 2):
            out.append(str(kmp_count(tokens[pos], tokens[pos + 1])))
    else:                                       # 数据文件格式：第 1 行 s2，第 2 行 s1
        out.append(str(kmp_count(tokens[1], tokens[0])))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
