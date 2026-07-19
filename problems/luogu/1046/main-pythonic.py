heights = list(map(int, input().split()))
reach = int(input()) + 30
print(sum(h <= reach for h in heights))
