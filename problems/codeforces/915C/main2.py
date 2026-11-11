#!/usr/bin/env python3
import sys


def solve() -> None:
    lines = sys.stdin.read().split()
    if not lines:
        return
    a, b = lines[0], lines[1]

    # 1. 长度较小：无上界约束，直接降序最大化
    if len(a) < len(b):
        sys.stdout.write("".join(sorted(a, reverse=True)) + "\n")
        return

    # 2. 长度相同：确定性数位贪心（通过剩余最小值预判剪枝，无需回溯）
    ans, rem = [], sorted(a, reverse=True)
    for i, ch in enumerate(b):
        # 尝试紧贴 b[i]：剩余数字的理论最小值必须 <= b 的后续后缀
        if ch in rem:
            nxt = rem.copy()
            nxt.remove(ch)
            if "".join(sorted(nxt)) <= b[i + 1 :]:
                ans.append(ch)
                rem = nxt
                continue

        # 无法紧贴：当前位选严格小于 b[i] 的最大数，剩余数字直接降序拼接完成
        for d in rem:
            if d < ch:
                ans.append(d)
                rem.remove(d)
                ans.extend(rem)  # rem 本身即为降序
                break
        break

    sys.stdout.write("".join(ans) + "\n")


if __name__ == "__main__":
    solve()
