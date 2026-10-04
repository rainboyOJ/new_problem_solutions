import sys
import heapq

def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    w = [next(data) for _ in range(n)]
    # 小根堆维护 m 个龙头的“当前占用截止时刻”；初始都为 0，即 m 个龙头在第 0 秒空闲
    taps = [0] * m
    for x in w:
        # 取最早空闲的龙头，该同学从下一秒开始接 x 秒
        t = heapq.heapreplace(taps, taps[0] + x)
    # 答案 = 最后一个龙头完成时刻
    print(max(taps))

main()
