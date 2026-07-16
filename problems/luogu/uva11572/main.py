import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
answers = []
for _ in range(next(data)):
    last = {}
    left = best = 0
    for right in range(next(data)):
        snowflake = next(data)
        left = max(left, last.get(snowflake, -1) + 1)
        last[snowflake] = right
        best = max(best, right - left + 1)
    answers.append(str(best))
print("\n".join(answers))
