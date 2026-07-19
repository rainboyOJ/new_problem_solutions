start, end = map(int, input().split())
years = [y for y in range(start, end + 1) if y % 400 == 0 or (y % 4 == 0 and y % 100 != 0)]
print(len(years))
print(*years)
