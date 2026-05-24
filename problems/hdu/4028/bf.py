import math
from itertools import combinations

def solve_brute_force(N, M):
    count = 0
    print(f"正在寻找 N={N} 中 LCM >= {M} 的方案...\n")
    print(f"{'方案':<10} {'子集':<20} {'LCM值'}")
    print("-" * 40)

    # 1. 枚举子集长度 (从选1个 到 选N个)
    for length in range(1, N + 1):
        # 2. 生成该长度的所有组合
        for subset in combinations(range(1, N + 1), length):
            # 3. 计算该子集的 LCM (Python 3.9+ 支持 *解包传参)
            lcm_val = math.lcm(*subset)
            
            # 4. 判断是否满足条件
            if lcm_val >= M:
                count += 1
                print(f"#{count:<9} {str(subset):<20} {lcm_val}")

    print("-" * 40)
    print(f"最终结果: 共 {count} 种方案")

# 运行题目样例 N=5, M=5
solve_brute_force(5, 5)
