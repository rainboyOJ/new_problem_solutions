"""跳石头：二分答案 + 贪心判定。O(N log L)"""
import sys

def main():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    l, n, m = next(data), next(data), next(data)   # 终点距离 / 岩石数 / 可移走数
    d = [next(data) for _ in range(n)]             # 岩石到起点距离，已升序
    pos = d + [l]                                 # 把终点也看作一块岩石

    def check(x: int) -> bool:
        cnt, prev = 0, 0                # prev = 上一块保留岩石的位置
        for p in pos:                   # 依次考虑每块岩石（含第一块与终点）
            if p - prev < x:            # 距离不足，移走当前岩石
                cnt += 1
            else:
                prev = p                # 保留它
        return cnt <= m                 # 终点不可移走，cnt 天然不含终点被移

    lo, hi = 1, l                       # 答案在 [1, L]
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if check(mid):
            lo = mid
        else:
            hi = mid - 1
    print(lo)

main()
