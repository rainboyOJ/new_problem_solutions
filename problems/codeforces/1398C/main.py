# 解法一：区间 [i, j] 合法 <=> s[j] - j == s[i-1] - (i-1)。
# 固定右端点 j，用 dict 数「之前有多少个 k 使 s[k] - k 等于 s[j] - j」。
# 时间平均 O(n)（dict 是哈希表），不需要知道值的范围；
# 解法二(main2.py)把它换成平移后的 list 桶，O(n)。

import sys
from collections import defaultdict


def solve(it):
    t = int(next(it))
    out = []
    for _ in range(t):
        n = int(next(it))           # 长度，读入只为对齐下标
        s = next(it)                # 这一行是数字串，逐字节取出来就是 a[i]

        cnt = defaultdict(int)
        cnt[0] = 1                  # k = 0，空前缀 s[0] - 0 = 0
        pre = 0
        ans = 0
        for j, ch in enumerate(s, 1):
            pre += ch - 48          # 原数组的前缀和 s[j]
            key = pre - j           # s[j] - j
            ans += cnt[key]         # 之前出现过多少次同样的差值，就多多少个合法区间
            cnt[key] += 1
        out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve(iter(sys.stdin.buffer.read().split()))
