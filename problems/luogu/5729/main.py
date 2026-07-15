width, depth, height = map(int, input().split())
cut_count = int(input())

removed = [
    [[False for _ in range(height + 1)] for _ in range(depth + 1)]
    for _ in range(width + 1)
]

for _ in range(cut_count):
    x1, y1, z1, x2, y2, z2 = map(int, input().split())
    for x in range(x1, x2 + 1):
        for y in range(y1, y2 + 1):
            for z in range(z1, z2 + 1):
                removed[x][y][z] = True

answer = 0
for x in range(1, width + 1):
    for y in range(1, depth + 1):
        for z in range(1, height + 1):
            if not removed[x][y][z]:
                answer += 1

print(answer)
