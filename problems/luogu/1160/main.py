import sys


tokens = iter(map(int, sys.stdin.buffer.read().split()))
n = next(tokens)
left = [0] * (n + 1)
right = [0] * (n + 1)
removed = [False] * (n + 1)

for student in range(2, n + 1):
    neighbor, side = next(tokens), next(tokens)
    if side == 0:
        previous = left[neighbor]
        left[student], right[student] = previous, neighbor
        left[neighbor] = student
        if previous:
            right[previous] = student
    else:
        following = right[neighbor]
        left[student], right[student] = neighbor, following
        right[neighbor] = student
        if following:
            left[following] = student

for _ in range(next(tokens)):
    student = next(tokens)
    if removed[student]:
        continue
    removed[student] = True
    previous, following = left[student], right[student]
    if previous:
        right[previous] = following
    if following:
        left[following] = previous

head = next(
    (student for student in range(1, n + 1) if not removed[student] and left[student] == 0),
    0,
)
answer = []
while head:
    answer.append(head)
    head = right[head]

print(*answer)
