"""环状均分纸牌 / 糖果传递：前缀和转化为数轴上一点到各点的曼哈顿距离最小（中位数）。"""
import sys

def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n = next(data)  # 题面的 n
    a = [next(data) for _ in range(n)]
    avg = sum(a) // n
    # c[i] = S[i] - i * avg, 其中 c[0] = 0
    # 代价为 sum(|x_1 - c[i]|)，取 x_1 为 c 的中位数
    c = [0] * n
    s = 0
    for i in range(1, n):
        s += a[i - 1] - avg
        c[i] = s
    c.sort()
    mid = c[n // 2]
    print(sum(abs(x - mid) for x in c))

if __name__ == "__main__":
    main()
