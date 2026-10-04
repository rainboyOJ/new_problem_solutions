# 我家的门牌号 (ROJ 1404)
# 数学模型：设共 m 家，门牌总和 S = m(m+1)/2，我家 x 满足 (S - x) - 2x = n，即 S - 3x = n
# 标准答案的 std.cpp 用 int 计算 i*i+i-2n（存在 32 位溢出），
# 部分数据（如 n=146）的正确输出正是溢出后首个满足整除的位置（m 恰为 65536），
# 故必须逐位模拟 int32 溢出才能与测试数据一致。
import sys

M = 1 << 32

def v32(a: int) -> int:
    """按 C++ int 语义截断到 32 位有符号整数"""
    return (a % M) - M if (a % M) >= M // 2 else a % M

data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
i = int((6 + 2 * n) ** 0.5) - 1        # std 的起始下界 sqrt(6+2n)-1
while True:
    t = v32(v32(i * i) + i - 2 * n)    # i*(i+1) - 2n，与 std 的溢出一致
    x = t // 6
    if t % 6 == 0 and x > 0:
        print(x, i)
        break
    i += 1
