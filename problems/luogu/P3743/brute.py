import sys
from fractions import Fraction


data = list(map(int, sys.stdin.buffer.read().split()))
n, charger_power = data[:2]
devices = list(zip(data[2::2], data[3::2]))

if sum(use for use, _ in devices) <= charger_power:
    print(-1)
    raise SystemExit

ordered = sorted((Fraction(stored, use), use, stored) for use, stored in devices)
active_use = 0
active_stored = 0
index = 0

while index < n:
    threshold = ordered[index][0]
    while index < n and ordered[index][0] == threshold:
        _, use, stored = ordered[index]
        active_use += use
        active_stored += stored
        index += 1

    next_threshold = ordered[index][0] if index < n else None
    if active_use > charger_power:
        answer = Fraction(active_stored, active_use - charger_power)
        if next_threshold is None or answer <= next_threshold:
            print(f"{float(answer):.10f}")
            break
