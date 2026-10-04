import sys

def main() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    a = list(map(int, data[1:1 + n]))
    s = sum(a) // n                       # 目标：每人最终 s 颗
    from itertools import accumulate
    # c[i] = a[i]-s + c[i-1]：即 i-1 传给 i 的净糖果数（负表示反向传）
    c = list(accumulate(x - s for x in a))
    c.sort()                              # 代价 = Σ|c[i]-x|，x 取中位数最优
    m = c[n // 2]
    print(sum(abs(v - m) for v in c))

main()
