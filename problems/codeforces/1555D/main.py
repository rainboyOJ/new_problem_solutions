#!/usr/bin/env python3
import itertools
import sys


def solve() -> None:
    input_data = sys.stdin.buffer.read().split()
    if not input_data:
        return

    n = int(input_data[0])
    m = int(input_data[1])
    s = input_data[2].decode("ascii")

    # 3 个字母的所有 6 种全排列
    perms = list(itertools.permutations("abc"))

    # 预处理 6 种排列的前缀差异和，pref[p][i] 表示长度为 i 的前缀中与周期串不同的字符数
    prefs = []
    for perm in perms:
        pref = [0] * (n + 1)
        for i, ch in enumerate(s):
            pref[i + 1] = pref[i] + (ch != perm[i % 3])
        prefs.append(pref)

    # 快速回答每个询问：O(1) 查询 6 个前缀和取最小值
    out = []
    ptr = 3
    for _ in range(m):
        l = int(input_data[ptr])
        r = int(input_data[ptr + 1])
        ptr += 2
        min_cost = min(pref[r] - pref[l - 1] for pref in prefs)
        out.append(str(min_cost))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
