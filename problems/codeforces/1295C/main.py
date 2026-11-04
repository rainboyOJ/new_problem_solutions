# 一次操作 = 取 s 的一个子序列拼到 z 末尾，等价于「沿着 t 往下走，同时在 s 里只向右跳」。
# 每换一趟就重新从 s 的开头开始，所以答案就是最少需要几趟。
#
# 关键是「找 s 里当前位置之后的下一个字符」不要线性扫描：
# 对每个字符维护它在 s 中的出现位置列表（天然有序），
# 用 bisect_right 找严格大于当前位置的第一个出现位置即可。整体 O(|t| log |s|)。

import sys
from bisect import bisect_right


def solve():
    data = sys.stdin.buffer.read().split()
    T = int(data[0])
    out = []
    for k in range(T):
        s = data[1 + 2 * k]
        t = data[2 + 2 * k]

        pos = [[] for _ in range(26)]
        for i, ch in enumerate(s):
            pos[ch - 97].append(i)

        ans = 1
        cur = -1                    # s 中已经用到的位置，从 -1 开始表示还没开始
        for ch in t:
            p = pos[ch - 97]
            if not p:               # t 里出现了 s 中没有的字符，永远做不到
                ans = -1
                break
            j = bisect_right(p, cur)
            if j == len(p):         # s 后面没有这个字符了，只能重开一趟
                ans += 1
                cur = p[0]
            else:
                cur = p[j]
        out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
