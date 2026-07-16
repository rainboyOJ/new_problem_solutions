import sys


input = sys.stdin.buffer.readline
n, query_count = map(int, input().split())
lockers = [dict() for _ in range(n + 1)]
answers = []

for _ in range(query_count):
    operation = list(map(int, input().split()))
    if operation[0] == 1:
        _, locker, cell, item = operation
        lockers[locker][cell] = item
    else:
        _, locker, cell = operation
        answers.append(str(lockers[locker][cell]))

print("\n".join(answers))
