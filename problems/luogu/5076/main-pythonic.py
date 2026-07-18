import sys
from bisect import bisect_left, bisect_right, insort

input = sys.stdin.buffer.readline
numbers = []
answers = []

for _ in range(int(input())):
    operation, value = map(int, input().split())
    if operation == 1:
        answers.append(str(bisect_left(numbers, value) + 1))
    elif operation == 2:
        answers.append(str(numbers[value - 1]))
    elif operation == 3:
        index = bisect_left(numbers, value)
        answers.append(str(numbers[index - 1] if index else -2147483647))
    elif operation == 4:
        index = bisect_right(numbers, value)
        answers.append(str(numbers[index] if index < len(numbers) else 2147483647))
    else:
        insort(numbers, value)

print("\n".join(answers))
