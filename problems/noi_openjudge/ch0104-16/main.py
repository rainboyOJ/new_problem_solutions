sides = sorted(map(int, input().split()))
print("yes" if sides[0] + sides[1] > sides[2] else "no")
