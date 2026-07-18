from collections import deque

n, step = map(int, input().split())
circle = deque(range(1, n + 1))
order = []

while circle:
    circle.rotate(-(step - 1))
    order.append(circle.popleft())

print(*order)
