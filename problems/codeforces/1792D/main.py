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
        prefixes = set()

        # 第一步：读入排列，将逆置换 q 的所有前缀存入哈希集合
        for _ in range(n):
            perm = [int(next(it)) for _ in range(m)]
            a.append(perm)

            q = [0] * (m + 1)
            for pos, val in enumerate(perm, 1):
                q[val] = pos

            mask = 0
            for val in q[1:]:
                mask = (mask << 4) | val
                prefixes.add(mask)

        # 第二步：每个 a[i] 主动检索自身最大前缀，查完当场收集，无需第三步
        ans_list = []
        for perm in a:
            mask = 0
            res = 0
            for k, val in enumerate(perm, 1):
                mask = (mask << 4) | val
                if mask in prefixes:
                    res = k
                else:
                    break
            ans_list.append(str(res))

        out.append(" ".join(ans_list))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
