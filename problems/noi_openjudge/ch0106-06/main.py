road_length, interval_count = map(int, input().split())
removed = [False] * (road_length + 1)

for _ in range(interval_count):
    left, right = map(int, input().split())
    for position in range(left, right + 1):
        removed[position] = True

print(removed.count(False))
