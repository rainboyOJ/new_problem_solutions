import sys

MOD = 1_000_000_007
MAX_LENGTH = 5000

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
sticks = data[1:1 + n]

count = [0] * (MAX_LENGTH + 1)
for length in sticks:
    count[length] += 1

pair_sum = [0] * (MAX_LENGTH + 1)
for left in range(1, MAX_LENGTH + 1):
    if count[left] == 0:
        continue
    for right in range(left, MAX_LENGTH - left + 1):
        if count[right] == 0:
            continue
        total = left + right
        if left == right:
            pair_sum[total] += count[left] * (count[left] - 1) // 2
        else:
            pair_sum[total] += count[left] * count[right]

answer = 0
for side in range(1, MAX_LENGTH + 1):
    if count[side] >= 2:
        same_side_choices = count[side] * (count[side] - 1) // 2
        answer = (answer + same_side_choices * pair_sum[side]) % MOD

print(answer)
