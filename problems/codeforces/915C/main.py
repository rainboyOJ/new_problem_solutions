#!/usr/bin/env python3
from collections import Counter
import sys


def solve() -> None:
    lines = sys.stdin.read().split()
    if not lines:
        return
    a, b = lines[0], lines[1]

    cnt = Counter(a)

    # 1. 若 A 的长度小于 B 的长度，直接输出降序
    if len(a) < len(b):
        sys.stdout.write("".join(sorted(a, reverse=True)) + "\n")
        return

    # 2. 长度相等，DFS 数位贪心回溯
    ans = []
    n = len(a)

    def dfs(pos: int, is_less: bool) -> bool:
        if pos == n:
            return True

        if is_less:
            # 已经严格小于，剩余数字全部降序填充
            rem = []
            for d in map(str, range(9, -1, -1)):
                if cnt[d] > 0:
                    rem.append(d * cnt[d])
            ans.extend("".join(rem))
            return True

        limit = int(b[pos])
        # 从大到小尝试当前位数字
        for d_int in range(limit, -1, -1):
            d_str = str(d_int)
            if cnt[d_str] > 0:
                cnt[d_str] -= 1
                ans.append(d_str)
                if dfs(pos + 1, d_int < limit):
                    return True
                ans.pop()
                cnt[d_str] += 1  # 回溯
        return False

    dfs(0, False)
    sys.stdout.write("".join(ans) + "\n")


if __name__ == "__main__":
    solve()
