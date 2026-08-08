# P2882 [USACO07MAR] Face The Right Way G
# N 头牛排成一列（F=朝前,B=朝后），每次将连续 K 头转向。求最小 K 和最少操作数。

import sys

FORWARD = 0     # 朝前
BACKWARD = 1    # 朝后

# ---- 读入 ----
data = sys.stdin.read().split()
n = int(data[0])
cows = [BACKWARD if direction == "B" else FORWARD for direction in data[1:]]


def count_operations(k):
    """
    固定 K=k，贪心从左到右：
    碰到朝后的牛就翻从它开始的 k 头牛。
    返回操作数，不可行返回 None。
    """
    # started[i] = 1  表示"以 i 为起点发起过一次 k-翻转"
    started = [0] * n

    # flip_parity: 当前位置 i 上，有奇数个还是偶数个之前的翻转在生效？
    #   0 = 偶数（0个）= 朝向不变
    #   1 = 奇数      = 朝向反转
    # 每次开始/结束一次翻转就 XOR 1，在 0 和 1 之间来回切。
    # parity=奇偶性的意思：只关心"翻转次数是奇数还是偶数"。
    flip_parity = 0
    operations = 0

    for i in range(n):
        # 从 i-k 开始的翻转只覆盖 [i-k, i-1]，走到 i 已失效，关掉它
        if i >= k:
            flip_parity ^= started[i - k]

        # 真实朝向 = 原始朝向 XOR 是否处在翻转中
        current_direction = cows[i] ^ flip_parity
        if current_direction == FORWARD:
            continue        # 已经朝前，跳过

        # 仍然朝后 → 必须从 i 开始做一次 k-翻转
        if i + k > n:       # 窗口越界，此 K 不可行
            return None

        started[i] = 1      # 标记：从这里开始了一个翻转
        flip_parity ^= 1    # 立刻进入翻转状态
        operations += 1

    return operations


# ---- 枚举 K ----
best_k = 1
best_operations = n + 1

for k in range(1, n + 1):
    operations = count_operations(k)
    if operations is not None and operations < best_operations:
        best_k = k
        best_operations = operations

print(best_k, best_operations)
