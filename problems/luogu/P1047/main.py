length, interval_count = map(int, input().split())

diff = [0] * (length + 2)

for _ in range(interval_count):
    left, right = map(int, input().split())
    diff[left] += 1
    diff[right + 1] -= 1

covered = 0
answer = 0

for position in range(length + 1):
    covered += diff[position]
    if covered == 0:
        answer += 1

print(answer)
