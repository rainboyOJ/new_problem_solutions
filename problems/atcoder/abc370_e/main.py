import sys

MOD = 998244353


def main() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    n = int(data[0])
    k = int(data[1])
    a = map(int, data[2:2 + n])

    # f[i] = 前缀 A[1..i] 的合法划分数, f[0] = 1
    # f[i] = (Σ_{j<i} f[j]) - (Σ_{j<i, pre[j] = pre[i]-K} f[j])
    total = 1            # Σ_{j<i} f[j], 初始只有 f[0] = 1
    # 桶
    bad = {0: 1}         # 前缀和 -> Σf[j]
    pre = 0
    f = 0

    for x in a:
        pre += x # 前缀和
        f = (total - bad.get(pre - k, 0)) % MOD
        total = (total + f) % MOD
        bad[pre] = (bad.get(pre, 0) + f) % MOD

    print(f)


if __name__ == "__main__":
    main()
