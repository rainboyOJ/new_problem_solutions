import sys

# 1. 一次性读取所有输入，split() 自动处理换行，[1:] 直接过滤掉第一行的数字 N
words = sys.stdin.read().split()[1:]

dp = {}
for w in words:
    # 2. 生成当前单词的所有前缀 w[:i]，去哈希表查表，取最大值 + 1
    dp[w] = max([dp.get(w[:i], 0) for i in range(1, len(w))], default=0) + 1

# 3. 输出最长词链长度
print(max(dp.values()) if dp else 0)
