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

        perms = [[int(next(it)) for _ in range(m)] for _ in range(n)]

        # 1. 建立 a_i 的前缀 hash 集合
        a_prefixes = set()
        a_prefs = []

        for p in perms:
            pref = []
            mask = 0
            for val in p:
                mask = (mask << 4) | val
                pref.append(mask)
                a_prefixes.add(mask)
            a_prefs.append(pref)

        # 2. 计算每个逆置换 q，让 q 去 a 的哈希表中寻找！
        matched = set()
        for p in perms:
            q = [0] * (m + 1)
            for pos, val in enumerate(p, 1):
                q[val] = pos

            mask = 0
            for val in q[1:]:
                mask = (mask << 4) | val
                if mask in a_prefixes:
                    matched.add(mask)  # q 找到了这个前缀
                else:
                    break

        # 3. 输出每个 a[i] 的最大匹配深度
        ans_list = []
        for pref in a_prefs:
            res = 0
            for k, mask in enumerate(pref, 1):
                if mask in matched:
                    res = k
                else:
                    break
            ans_list.append(str(res))

        out.append(" ".join(ans_list))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
