n = int(input())
on_lights = set()
for _ in range(n):
    a, t = input().split()
    a, t = float(a), int(t)
    for k in range(1, t + 1):
        on_lights ^= {int(a * k)}
print(next(iter(on_lights)))
