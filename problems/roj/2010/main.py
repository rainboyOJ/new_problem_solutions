import sys

def main() -> None:
    data = sys.stdin.read().split()
    m, s, c = int(data[0]), int(data[1]), int(data[2])
    a = sorted(map(int, data[3:3 + c]))
    # 从“一整块板 [a[0], a[-1]]”开始，允许再切 m-1 刀
    gaps = [y - x - 1 for x, y in zip(a, a[1:])]
    print(a[-1] - a[0] + 1 - sum(sorted(gaps, reverse=True)[:m - 1]))

main()
