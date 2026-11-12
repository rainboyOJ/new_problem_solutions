#!/usr/bin/env python3
from itertools import accumulate, takewhile
import sys


def solve() -> None:
    it = iter(sys.stdin.read().split())
    if not (t := next(it, None)):
        return

    out = []
    # 状态压缩编码规则：4-bit 移位将每个数字追加至前缀整数中（绝对无冲突单射）
    encode = lambda mask, val: (mask << 4) | val

    for _ in range(int(t)):
        n, m = int(next(it)), int(next(it))
        a = [[int(next(it)) for _ in range(m)] for _ in range(n)]

        # 1. 计算每个排列的逆置换，并将其各阶前缀 hash 存入 set
        prefixes = set()
        for p in a:
            q = [0] * m
            for idx, val in enumerate(p, 1):
                q[val - 1] = idx
            prefixes.update(accumulate(q, encode))

        # 2. 查询每个 a[i] 的前缀在 set 中最长连续命中长度
        ans = [
            sum(1 for _ in takewhile(lambda h: h in prefixes, accumulate(p, encode)))
            for p in a
        ]
        out.append(" ".join(map(str, ans)))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
