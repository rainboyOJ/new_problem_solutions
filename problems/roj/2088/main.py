#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-07-05 21:47
# update_at: 2026-07-05 21:47

import sys

INF = 10**9
CHARS = " abcdefghijklmnopqrstuvwxyz"


def calc_diff19(dc: list[list[int]]) -> tuple[int, int]:
    """计算 19 行输入与标准字体匹配时的最小差异及最优字符编号。"""
    best_cost, best_c = INF, 0
    for c in range(27):
        d = dc[c]
        # 缺失第 k 行：前 k 行匹配标准第 0..k-1 行，后 19-k 行匹配标准第 k+1..19 行
        cost = sum(d[r][r + 1] for r in range(19))
        min_c = cost
        for k in range(19):
            cost += d[k][k] - d[k][k + 1]
            if cost < min_c:
                min_c = cost
        if min_c < best_cost:
            best_cost, best_c = min_c, c
    return best_cost, best_c


def calc_diff20(dc: list[list[int]]) -> tuple[int, int]:
    """计算 20 行输入与标准字体一对一匹配时的最小差异及最优字符编号。"""
    best_cost, best_c = INF, 0
    for c in range(27):
        cost = sum(dc[c][r][r] for r in range(20))
        if cost < best_cost:
            best_cost, best_c = cost, c
    return best_cost, best_c


def calc_diff21(dc: list[list[int]]) -> tuple[int, int]:
    """计算 21 行输入与标准字体匹配时的最小差异及最优字符编号。"""
    best_cost, best_c = INF, 0
    for c in range(27):
        d = dc[c]
        # 重复第 k 行：第 k 行与第 k+1 行均对应标准第 k 行，取两者中差异较小者
        pref = [0] * 22
        for r in range(20):
            pref[r + 1] = pref[r] + d[r][r]
        suff = [0] * 22
        for r in range(20, 0, -1):
            suff[r] = suff[r + 1] + d[r][r - 1]
        min_c = min(pref[k] + min(d[k][k], d[k + 1][k]) + suff[k + 2] for k in range(20))
        if min_c < best_cost:
            best_cost, best_c = min_c, c
    return best_cost, best_c


def solve() -> None:
    tokens = sys.stdin.read().split()
    if not tokens:
        return

    f_cnt = int(tokens[0])
    font_raw = tokens[1 : 1 + f_cnt]
    n = int(tokens[1 + f_cnt])
    char_raw = tokens[2 + f_cnt : 2 + f_cnt + n]

    # 将 20 位 01 串转换为整数，便于位运算计算汉明距离
    font = [[int(x, 2) for x in font_raw[c * 20 : (c + 1) * 20]] for c in range(27)]
    inp = [int(x, 2) for x in char_raw]

    # diff[i][c][r] 表示输入第 i 行与字符 c 的第 r 行的差异位变化数
    diff = [[[(inp[i] ^ font[c][r]).bit_count() for r in range(20)] for c in range(27)] for i in range(n)]

    # dp[i] 表示匹配完前 i 行的最小总修改代价
    dp = [INF] * (n + 1)
    prev = [(-1, '')] * (n + 1)
    dp[0] = 0

    for i in range(n):
        if dp[i] == INF:
            continue
        cur = dp[i]

        # 转移 1：当前字符占 19 行（缺失 1 行）
        if i + 19 <= n:
            dc = [[diff[i + r][c] for r in range(19)] for c in range(27)]
            cost, c = calc_diff19(dc)
            if cur + cost < dp[i + 19]:
                dp[i + 19] = cur + cost
                prev[i + 19] = (i, CHARS[c])

        # 转移 2：当前字符占 20 行（行数未变）
        if i + 20 <= n:
            dc = [[diff[i + r][c] for r in range(20)] for c in range(27)]
            cost, c = calc_diff20(dc)
            if cur + cost < dp[i + 20]:
                dp[i + 20] = cur + cost
                prev[i + 20] = (i, CHARS[c])

        # 转移 3：当前字符占 21 行（重复 1 行）
        if i + 21 <= n:
            dc = [[diff[i + r][c] for r in range(21)] for c in range(27)]
            cost, c = calc_diff21(dc)
            if cur + cost < dp[i + 21]:
                dp[i + 21] = cur + cost
                prev[i + 21] = (i, CHARS[c])

    # 回溯得到识别出的字符序列，首部多余的空白字符按数据规范剥离
    res = []
    curr = n
    while curr > 0:
        p, ch = prev[curr]
        res.append(ch)
        curr = p
    print("".join(reversed(res)).lstrip())


if __name__ == "__main__":
    solve()
