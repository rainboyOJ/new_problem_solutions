import sys


input = sys.stdin.buffer.readline
rows, columns = map(int, input().split())
heights = [0] * columns
answer = 0

for _ in range(rows):
    for j, cell in enumerate(input().strip()):
        heights[j] = heights[j] + 1 if cell == 46 else 0

    stack = []
    ending_here = 0
    for height in heights:
        width = 1
        while stack and stack[-1][0] >= height:
            previous_height, previous_width = stack.pop()
            ending_here -= previous_height * previous_width
            width += previous_width
        stack.append((height, width))
        ending_here += height * width
        answer += ending_here

print(answer)
