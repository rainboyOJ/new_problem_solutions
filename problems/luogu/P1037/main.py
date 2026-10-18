import sys


input = sys.stdin.buffer.readline
number, rule_count = input().split()

# 二进制数表示各个数字之间的转换的状态
reachable = [1 << digit for digit in range(10)]

for _ in range(int(rule_count)):
    source, target = map(int, input().split())
    reachable[source] |= 1 << target # 走一步

# 传递闭包 ,中点
for middle in range(10):

    # 把点转成 状态
    bit = 1 << middle
    # 枚举起点
    for start in range(10):
        # 查看起点是否可以到达中点
        if reachable[start] & bit:
            # 如果中点到终点可达，那么起点到终点可达
            reachable[start] |= reachable[middle]
answer = 1
for digit in number:
    # bit_count() 求该位数字可达的种数
    answer *= reachable[digit - 48].bit_count()

print(answer)
