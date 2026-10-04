#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-30 22:10
# update_at: 2026-09-30 22:10

import sys

# 凸包点 j 的纵坐标：dp[j] + S[j]^2（横坐标是 S[j]，斜率优化推式子里移项得到）
def y_of(dp: list[int], S: list[int], j: int) -> int:
    """直线截距式 y(j) = dp[j] + S[j]²，凸包上点 j 的 y 值。"""
    return dp[j] + S[j] * S[j]


def solve() -> None:
    data = sys.stdin.buffer.read().split()
    pos = 0
    out: list[str] = []

    while pos < len(data):  # 多组数据，读到 EOF
        n, m = int(data[pos]), int(data[pos + 1])
        pos += 2

        if n == 0:  # 没有单词，不用打印，费用为 0
            out.append('0')
            continue

        S = [0] * (n + 1)  # S[i] = 前 i 个单词的权值和
        s = 0
        for i in range(1, n + 1):
            s += int(data[pos])
            pos += 1
            S[i] = s

        dp = [0] * (n + 1)  # dp[i]：前 i 个单词分段的最小费用
        q = [0] * (n + 1)   # 凸包队列，存下标，X 坐标 S[j] 严格递增
        head, tail = 0, 1   # 队列有效区间 [head, tail)

        for i in range(1, n + 1):
            k = 2 * S[i]  # 当前决策直线的斜率，随 i 单调不减 → 可从队头淘汰

            # 队头两点斜率 <= k 时，队头不可能再成为最优决策
            while tail - head >= 2 and \
                    (y_of(dp, S, q[head + 1]) - y_of(dp, S, q[head])) <= \
                    k * (S[q[head + 1]] - S[q[head]]):
                head += 1

            j = q[head]
            d = S[i] - S[j]
            dp[i] = dp[j] + d * d + m

            # 新点加入队尾前，先弹出使凸包失去"斜率严格递增"的点
            while tail - head >= 2 and \
                    (y_of(dp, S, q[tail - 1]) - y_of(dp, S, q[tail - 2])) * (S[i] - S[q[tail - 2]]) >= \
                    (y_of(dp, S, i) - y_of(dp, S, q[tail - 2])) * (S[q[tail - 1]] - S[q[tail - 2]]):
                tail -= 1

            if S[i] > S[q[tail - 1]]:
                q[tail] = i
                tail += 1
            # S[i] == S[q[-1]] 时 dp 非降 ⇒ 新点 y 更大，被旧点完全覆盖，不入队

        out.append(str(dp[n]))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
