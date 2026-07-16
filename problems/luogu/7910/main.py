import sys
from bisect import bisect_left, insort


data = iter(map(int, sys.stdin.buffer.read().split()))
n, queries = next(data), next(data)
values = [next(data) for _ in range(n)]
ordered = sorted((value, index) for index, value in enumerate(values))
answers = []

for _ in range(queries):
    operation, index = next(data), next(data) - 1
    if operation == 1:
        new_value = next(data)
        ordered.pop(bisect_left(ordered, (values[index], index)))
        values[index] = new_value
        insort(ordered, (new_value, index))
    else:
        answers.append(str(bisect_left(ordered, (values[index], index)) + 1))

print("\n".join(answers))
