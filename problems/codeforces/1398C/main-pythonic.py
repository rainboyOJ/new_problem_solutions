# Pythonic 版（与 main.py 同一解法），分三步写清楚：
#   1. 原数组的前缀和 pre_sum[i] = a[1] + ... + a[i]，pre_sum[0] = 0；
#   2. 把下标减掉，得到 diff[i] = pre_sum[i] - i，也就是 s[i] - i；
#   3. 区间 [i, j] 合法 <=> diff[i-1] == diff[j]，
#      所以对 diff 里相同值「两两配对」，同一值出现 c 次就贡献 C(c, 2)。
# 平均 O(n)；比 main.py 短，是因为三件事都交给库函数做。

import sys
from collections import Counter
from itertools import accumulate


def solve(it):
    out = []
    for _ in range(int(next(it))):
        n = int(next(it))               # 长度，读入只为对齐下标
        s = next(it)                    # 这一行是数字串，逐字节取出来就是 a[i]

        # 第一步：前缀和，长度 n+1，pre_sum[0] = 0
        pre_sum = list(accumulate((ch - 48 for ch in s), initial=0))
        # 第二步：每个前缀和减掉自己的下标
        diff = [v - i for i, v in enumerate(pre_sum)]
        # 第三步：相同差值两两配对，统计组合数
        out.append(sum(c * (c - 1) // 2 for c in Counter(diff).values()))

    sys.stdout.write("\n".join(map(str, out)) + "\n")


if __name__ == "__main__":
    solve(iter(sys.stdin.buffer.read().split()))
