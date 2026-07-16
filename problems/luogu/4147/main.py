import sys


input = sys.stdin.buffer.readline
rows, columns = map(int, input().split())
heights = [0] * columns
best = 0

for _ in range(rows):
    for j, cell in enumerate(input().split()):
        heights[j] = heights[j] + 1 if cell == b"F" else 0

    stack = []
    for j in range(columns + 1):
        height = heights[j] if j < columns else 0
        start = j
        while stack and stack[-1][1] > height:
            start, previous_height = stack.pop()
            best = max(best, previous_height * (j - start))
        if not stack or stack[-1][1] < height:
            stack.append((start, height))

print(3 * best)
