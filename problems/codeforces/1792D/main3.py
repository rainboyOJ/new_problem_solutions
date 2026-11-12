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

        # 1. 建立原排列 a 的前缀树 (Trie)
        ch = [{}]
        has_q = [False]

        for p in perms:
            u = 0
            for x in p:
                if x not in ch[u]:
                    ch[u][x] = len(ch)
                    ch.append({})
                    has_q.append(False)
                u = ch[u][x]

        # 2. 让每个逆置换 q 去树上漫游匹配，沿途激活节点
        for p in perms:
            q = [0] * (m + 1)
            for idx, val in enumerate(p, 1):
                q[val] = idx

            u = 0
            for x in q[1:]:
                if x in ch[u]:
                    u = ch[u][x]
                    has_q[u] = True
                else:
                    break

        # 3. 每个 a[i] 顺着自身路径查询最深被激活的深度
        ans_list = []
        for p in perms:
            u = 0
            depth = 0
            for k, x in enumerate(p, 1):
                u = ch[u][x]
                if has_q[u]:
                    depth = k
                else:
                    break
            ans_list.append(str(depth))

        out.append(" ".join(ans_list))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
