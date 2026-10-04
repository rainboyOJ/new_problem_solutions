import sys

data = iter(map(int, sys.stdin.buffer.read().split()))
n, m, k, x = next(data), next(data), next(data), next(data)
# 每轮所有人整体顺时针移动 m 格 => k 轮共移动 m*10^k 格（mod n）
# pow(10, k, n) 用快速幂求 10^k mod n，O(log k)
print((x + m * pow(10, k, n)) % n)
