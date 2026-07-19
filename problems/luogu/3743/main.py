import sys


data = list(map(int, sys.stdin.buffer.read().split()))
n, power = data[:2]
devices = list(zip(data[2::2], data[3::2]))
total_use = sum(use for use, _ in devices)

if total_use <= power:
    print(-1)
else:
    def possible(seconds):
        lacks = (use * seconds - stored for use, stored in devices)
        needed = sum(lack for lack in lacks if lack > 0.0)
        return needed <= power * seconds

    left = 0.0
    right = sum(stored for _, stored in devices) / (total_use - power)
    for _ in range(60):
        middle = (left + right) / 2
        if possible(middle):
            left = middle
        else:
            right = middle

    print(f"{left:.10f}")
