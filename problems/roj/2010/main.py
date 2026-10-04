import sys

def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, s, c = next(data), next(data), next(data)
    a = sorted(next(data) for _ in range(c))
    # 从“一整块板 [a[0], a[-1]]”开始，允许再切 m-1 刀
    gaps = [y - x - 1 for x, y in zip(a, a[1:])]
    print(a[-1] - a[0] + 1 - sum(sorted(gaps, reverse=True)[:m - 1]))

main()
