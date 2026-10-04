import sys

def main() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    # 按推销疲劳值 A 降序排序，A 相同则距离大者优先：
    # 这样「排序前 i 项」恰好是「A 前 i 大中距离尽量大的那组」
    sa = sorted(((int(s), int(a)) for s, a in zip(data[1:1 + n], data[1 + n:1 + 2 * n])), key=lambda p: (-p[1], -p[0]))
    s = [p[0] for p in sa]
    a = [p[1] for p in sa]
    # h[i] = max_{j>=i} (2*S_j + A_j)：最远点取到排序位置 >= i 时的最佳「路程+推销」贡献
    h = [0] * (n + 2)
    for i in range(n - 1, -1, -1):
        h[i] = max(h[i + 1], 2 * s[i] + a[i])
    ans: list[int] = []
    prev = 0   # 前 X-1 大的 A 之和
    pre = 0    # 前 X 大的 A 之和
    qmax = 0   # 前 X 名中的最远距离
    for i in range(n):
        pre += a[i]
        qmax = max(qmax, s[i])
        # 决策一：最远点在前 i 名内 → pre + 2*qmax
        # 决策二：舍弃第 i 名、改去更远的 j（>=i，按 A 序）→ prev + 2*S_j + A_j
        ans.append(max(pre + 2 * qmax, prev + h[i]))
        prev = pre
    sys.stdout.write('\n'.join(map(str, ans)))

if __name__ == '__main__':
    main()
