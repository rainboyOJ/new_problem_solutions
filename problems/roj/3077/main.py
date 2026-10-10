#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-10 09:00
# update_at: 2026-10-10 09:00

import sys

def solve() -> None:
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    s1, s2, s3 = input_data[1], input_data[2], input_data[3]

    val = [-1] * n
    used = [False] * n

    vis_order = [False] * 26
    order = []
    for i in range(n - 1, -1, -1):
        for s in (s1, s2, s3):
            idx = ord(s[i]) - ord('A')
            if not vis_order[idx]:
                vis_order[idx] = True
                order.append(idx)

    def check() -> bool:
        carry = 0
        for i in range(n - 1, -1, -1):
            v1 = val[ord(s1[i]) - ord('A')]
            v2 = val[ord(s2[i]) - ord('A')]
            v3 = val[ord(s3[i]) - ord('A')]
            if v1 != -1 and v2 != -1 and v3 != -1:
                if carry != -1:
                    sm = v1 + v2 + carry
                    if sm % n != v3:
                        return False
                    carry = sm // n
                else:
                    if (v1 + v2) % n != v3 and (v1 + v2 + 1) % n != v3:
                        return False
            else:
                carry = -1
                if v1 != -1 and v2 != -1:
                    t1 = (v1 + v2) % n
                    t2 = (v1 + v2 + 1) % n
                    if used[t1] and used[t2]:
                        return False
                elif v1 != -1 and v3 != -1:
                    t1 = (v3 - v1 + n) % n
                    t2 = (v3 - v1 - 1 + n) % n
                    if used[t1] and used[t2]:
                        return False
                elif v2 != -1 and v3 != -1:
                    t1 = (v3 - v2 + n) % n
                    t2 = (v3 - v2 - 1 + n) % n
                    if used[t1] and used[t2]:
                        return False
        return True

    def verify() -> bool:
        carry = 0
        for i in range(n - 1, -1, -1):
            v1 = val[ord(s1[i]) - ord('A')]
            v2 = val[ord(s2[i]) - ord('A')]
            v3 = val[ord(s3[i]) - ord('A')]
            sm = v1 + v2 + carry
            if sm % n != v3:
                return False
            carry = sm // n
        return carry == 0

    def dfs(u: int) -> bool:
        if u == n:
            return verify()
        if not check():
            return False
        
        c = order[u]
        for i in range(n - 1, -1, -1):
            if not used[i]:
                val[c] = i
                used[i] = True
                if dfs(u + 1):
                    return True
                used[i] = False
                val[c] = -1
        return False

    dfs(0)
    print(" ".join(str(val[i]) for i in range(n)))

if __name__ == '__main__':
    solve()
