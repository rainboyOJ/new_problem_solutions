import sys
# 1. 初始化 DP 表，长度设为 251 (下标 0-250)
dp = [0] * 251

# 2. 设置 Base Case (边界条件)
dp[0] = 1
dp[1] = 1

# 3. 递推填表
# 从 2 开始一直算到 250
for i in range(2, 251):
    dp[i] = dp[i-1] + 2 * dp[i-2]  # Python 会自动处理大整数，无需操心

# 此时，dp[n] 里存的就是答案


# sys.stdin 是一个迭代器，会自动读取每一行直到输入结束
for line in sys.stdin:
    line = line.strip() # 去除末尾换行符
    if not line:        # 防止读取空行
        continue
    n = int(line)
    print(dp[n])

