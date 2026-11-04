# 解法二：把每个元素减 1，条件变成「子段和为 0」，也就是「两个前缀和相等」。
# 前缀和的值域是 [-n, 8n]，加偏移量 n 后用 list 当桶（下标访问），O(n)，常数最小。
# 解法一(main.py)里 s[k] - k 正好等于这里减 1 后的前缀和，只是那边用 dict 存、不需要知道值域。

import sys


def solve():
    data = sys.stdin.buffer.read().split()
    t = int(data[0])
    idx = 1
    out = []
    for _ in range(t):
        n = int(data[idx])              # 长度，读入只为对齐下标
        s = data[idx + 1]               # 这一行是数字串，逐字节取出来就是 a[i]
        idx += 2

        base = n                        # 前缀和最小能到 -n，平移成非负下标
        cnt = [0] * (9 * n + 5)         # 桶：cnt[pre + base] = 前缀和 pre 出现次数
        cnt[base] = 1                   # 空前缀，前缀和 0 出现过一次
        pre = 0
        ans = 0
        for ch in s:
            pre += ch - 49              # a[i] - 1，ch 是 ASCII 码，'0' 是 48
            ans += cnt[pre + base]      # 相同前缀和的历史次数就是合法子段个数
            cnt[pre + base] += 1
        out.append(str(ans))

    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    solve()
