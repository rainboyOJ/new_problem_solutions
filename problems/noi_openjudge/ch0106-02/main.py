apple_heights = map(int, input().split())
reachable_height = int(input()) + 30
print(sum(height <= reachable_height for height in apple_heights))
