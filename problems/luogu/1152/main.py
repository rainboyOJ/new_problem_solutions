import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
numbers = data[1:1 + n]

seen = set()
ok = True

for i in range(n - 1):
    diff = abs(numbers[i + 1] - numbers[i])
    if diff < 1 or diff >= n or diff in seen:
        ok = False
        break
    seen.add(diff)

print("Jolly" if ok else "Not jolly")
