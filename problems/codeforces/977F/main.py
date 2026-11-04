# 直接对每个位置往前扫前驱就是 O(n^2)，会超时。
# 记 f[i] 为以 i 结尾的最长连续递增子序列长度。
# 前驱的值必然是 a[i] - 1，所以只需要记住「值 v 最后一次出现的下标」。

import sys
from collections import defaultdict


def solve(data):
    n = next(data)
    a = [next(data) for _ in range(n)]

    last = defaultdict(lambda: -1)  # last[v] = 值 v 最后一次出现的下标
    pre = [-1] * n                  # pre[i] = 以 i 结尾时的前一个位置
    f = [1] * n                     # f[i] = 以 i 结尾的最长连续递增子序列长度

    for i in range(n):
        j = last[a[i] - 1]          # 值 a[i] - 1 最后一次出现的位置
        if j != -1:
            f[i] = f[j] + 1
            pre[i] = j
        last[a[i]] = i

    ans = max(f)
    print(ans)

    pos = f.index(ans)              # 任取一个取到最大长度的结尾
    output = []
    while pos != -1:
        output.append(pos)
        pos = pre[pos]
    print(*[p + 1 for p in output[::-1]])


if __name__ == "__main__":
    data = iter(map(int, sys.stdin.buffer.read().split()))
    solve(data)
