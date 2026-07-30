carpet_count = int(input())
carpets = [tuple(map(int, input().split())) for _ in range(carpet_count)]
x, y = map(int, input().split())
for index in range(carpet_count - 1, -1, -1):
    left, bottom, width, height = carpets[index]
    if left <= x <= left + width and bottom <= y <= bottom + height:
        print(index + 1)
        break
else:
    print(-1)
