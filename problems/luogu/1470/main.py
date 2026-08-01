import sys
from collections import defaultdict


# 读入全部输入并按空白切分，得到字节 token 列表
tokens = sys.stdin.buffer.read().split()

# 分隔符 b"." 之前是原串，之后是目标序列
separator = tokens.index(b".")
primitives_by_length = defaultdict(set)
for primitive in tokens[:separator]:
    primitives_by_length[len(primitive)].add(primitive)
sequence = b"".join(tokens[separator + 1:])

n = len(sequence)

# dp[i] 表示前缀 sequence[0..i) 能否由原串完整拼出
dp = bytearray(n + 1)
dp[0] = 1  # 空前缀一定能拼出

answer = 0
# 与 C++ 的写法一致：站在位置 i，往回找最后一个词
for i in range(1, n + 1):
    # 枚举最后一个词的长度 length（原串最长 10 个字符）
    for length in range(1, 11):
        start = i - length
        if start < 0:
            continue
        if length not in primitives_by_length:
            continue
        # 两个条件同时满足：前缀 sequence[0..start) 能拼出，
        # 且后缀 sequence[start..i) 是一个原串
        if dp[start] and sequence[start:i] in primitives_by_length[length]:
            dp[i] = 1
            break  # 找到一个拆法即可，不需要继续尝试更长或更短的词
    if dp[i]:
        answer = max(answer, i)  # dp 不单调，取所有可达位置的最大值

print(answer)
