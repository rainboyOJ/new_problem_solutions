sides = int(input())
known_angles = map(int, input().split())
print((sides - 2) * 180 - sum(known_angles))
