import heapq
import sys


data = iter(map(int, sys.stdin.buffer.read().split()))
value_count, query_count = next(data), next(data)
values = [next(data) for _ in range(value_count)]
queries = [next(data) for _ in range(query_count)]
lower = []
upper = []
inserted = 0
answers = []

for amount in queries:
    for value in values[inserted:amount]:
        if lower and value < -lower[0]:
            heapq.heappush(upper, -heapq.heappushpop(lower, -value))
        else:
            heapq.heappush(upper, value)
    inserted = amount
    answers.append(str(upper[0]))
    heapq.heappush(lower, -heapq.heappop(upper))

print("\n".join(answers))
