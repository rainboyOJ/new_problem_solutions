#!/usr/bin/env python3
import sys


def solve() -> None:
    lines = sys.stdin.read().split()
    if not lines:
        return
    it = iter(lines)

    t = int(next(it))
    out = []

    for _ in range(t):
        n = int(next(it))
        m = int(next(it))

        a = []
        seen = set()

        for _ in range(n):
            perm = [int(next(it)) for _ in range(m)]
            a.append(perm)

            # 计算逆置换：q[val] = pos (1-based)
            q = [0] * (m + 1)
            for pos, val in enumerate(perm, 1):
                q[val] = pos

            # 将逆置换的前缀编码为整数放入集合
            mask = 0
            for val in q[1:]:
                mask = (mask << 4) | val
                seen.add(mask)

        # 匹配每个 a[i] 的最长前缀
        ans_list = []
        for perm in a:
            mask = 0
            res = 0
            for k, val in enumerate(perm, 1):
                mask = (mask << 4) | val
                if mask in seen:
                    res = k
                else:
                    break
            ans_list.append(str(res))

        out.append(" ".join(ans_list))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
