import sys


MOD = 10007
input = sys.stdin.buffer.readline
n, m = map(int, input().split())
numbers = list(map(int, input().split()))
colors = map(int, input().split())
size = 2 * (m + 1)
count = [0] * size
sum_position = [0] * size
sum_number = [0] * size
sum_product = [0] * size
answer = 0

for position, (number, color) in enumerate(zip(numbers, colors), 1):
    key = 2 * color + position % 2
    answer += (sum_product[key] + position * sum_number[key]
               + number * sum_position[key]
               + count[key] * position * number)
    count[key] += 1
    sum_position[key] = (sum_position[key] + position) % MOD
    sum_number[key] = (sum_number[key] + number) % MOD
    sum_product[key] = (sum_product[key] + position * number) % MOD

print(answer % MOD)
