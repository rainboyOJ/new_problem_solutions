"""ROJ 3167 减操作：给每次减操作输出一个合法位置序列。

核心观察：无论操作顺序如何，a[1] 的最终系数恒为 +1，且 a[2] 必为 -1，
故答案形如 t = a[1] - a[2] ± a[3] ± ... ± a[n]，只需 DP 求一组符号，
再按固定规则还原操作序列（先消 +1 项，最后从 1 号位消掉全部 -1 项）。
f[i][v] = 前缀 a[1..i] 凑出 v 时 a[i] 的符号（+1/-1/0 不可达），
回溯时优先取 +1，与题目约定保持一致；无解时 f 全 0，恰好什么都不输出。
"""
import sys

OFF = 10_000  # 值域 [-10000, 10000] 的下标平移常数


def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, t = next(data), next(data)
    a = [next(data) for _ in range(n)]
    if n == 1:
        return  # 长度 1 无操作，不输出

    # f[i][v]：凑出 v 时 a[i] 取的符号；0 表示该状态不可达
    f: list[list[int]] = [[0] * (2 * OFF + 1) for _ in range(n + 1)]
    f[1][OFF + a[0]] = 1
    f[2][OFF + a[0] - a[1]] = -1  # a[2] 只能作为减数
    for i in range(3, n + 1):
        fi, fp, ai = f[i], f[i - 1], a[i - 1]
        for j in range(2 * OFF + 1):
            if fp[j]:
                if j + ai <= 2 * OFF:
                    fi[j + ai] = 1  # a[i] 取 +：上一步和为 j - a[i]
                if j >= ai:
                    fi[j - ai] = -1  # a[i] 取 -：上一步和为 j + a[i]

    # 回溯符号（优先 +1）；无解时 ans 全 0，输出恰为空
    s = OFF + t
    ans = [0] * (n + 1)
    for i in range(n, 1, -1):
        ans[i] = f[i][s]
        if ans[i] == 1:
            s -= a[i - 1]
        elif ans[i] == -1:
            s += a[i - 1]

    # 还原操作序列：先依次消去每个 +1 项，末尾再从 1 号位消掉所有 -1 项
    ops: list[str] = []
    cnt = 0  # 已消去的 +1 个数，其后位置整体左移
    for i in range(2, n + 1):
        if ans[i] == 1:
            ops.append(str(i - cnt - 1))
            cnt += 1
    for i in range(2, n + 1):
        if ans[i] == -1:
            ops.append("1")
    if ops:
        sys.stdout.write("\n".join(ops) + "\n")


if __name__ == "__main__":
    main()
