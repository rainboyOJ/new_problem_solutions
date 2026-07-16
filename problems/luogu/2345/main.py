import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
cows = sorted((next(data), next(data)) for _ in range(n))
limit = max(position for _, position in cows) + 1
count_tree = [0] * (limit + 1)
sum_tree = [0] * (limit + 1)
seen = position_sum = answer = 0


def prefix(tree, index):
    result = 0
    while index:
        result += tree[index]
        index -= index & -index
    return result


for volume, position in cows:
    left_count = prefix(count_tree, position)
    left_sum = prefix(sum_tree, position)
    distance_sum = (position * left_count - left_sum
                    + position_sum - left_sum - position * (seen - left_count))
    answer += volume * distance_sum
    index = position
    while index <= limit:
        count_tree[index] += 1
        sum_tree[index] += position
        index += index & -index
    seen += 1
    position_sum += position

print(answer)
