import sys
from operator import mul

MOD = 1_000_000_007
MAX_LENGTH = 5000

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
sticks = data[1:1 + n]

count = [0] * (MAX_LENGTH + 1)
for length in sticks:
    count[length] += 1

answer = 0
max_length = max(sticks)

for side in range(2, max_length + 1):
    side_count = count[side]
    if side_count < 2:
        continue

    # 左端点只取到中点之前，因此每对不同长度的短棒只统计一次。
    middle = (side + 1) // 2
    left_counts = count[1:middle]
    right_counts = count[side - 1:side - middle:-1]
    pair_choices = sum(map(mul, left_counts, right_counts))

    # side 为偶数时，补上两根短棒长度都为 side // 2 的情况。
    if side % 2 == 0:
        middle_count = count[side // 2]
        pair_choices += middle_count * (middle_count - 1) // 2

    same_side_choices = side_count * (side_count - 1) // 2
    answer = (answer + same_side_choices * pair_choices) % MOD

print(answer)
