m, n = map(int, input().split())
distance = n - m

previous = 1
current = 1
for _ in range(distance):
    previous, current = current, previous + current

print(previous)
