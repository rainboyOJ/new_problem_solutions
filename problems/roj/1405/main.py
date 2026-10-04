# 质数的和与积：两个质数和为 S，求最大乘积
# 埃氏筛预处理 <=S 的质数表，从 p=S//2 向下枚举：p 与 S-p 均为质数的首个 p 即最优
# 因为 p*(S-p) 关于 S/2 对称且随 p 靠近 S/2 增大

import sys

data = iter(map(int, sys.stdin.buffer.read().split()))
S: int = next(data)  # 两个质数的和
is_comp: list[bool] = [False] * (S + 1)  # 埃氏筛标记合数
for i in range(2, int(S**0.5) + 1):
    if not is_comp[i]:
        is_comp[i * i :: i] = [True] * len(is_comp[i * i :: i])

p = next(p for p in range(S // 2, 1, -1) if not is_comp[p] and not is_comp[S - p])
print(p * (S - p))
