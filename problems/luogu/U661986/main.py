import sys

def ints():
    for x in sys.stdin.buffer.read().split():
        yield int(x)

it = ints()
n = next(it)
C = next(it)
f = [0] * (C + 1)

for _ in range(n):
    vol = next(it)
    val = next(it)
    if vol > C:
        continue
    for c in range(C, vol - 1, -1):
        f[c] = f[c] if f[c] >= f[c - vol] + val else f[c - vol] + val

print(f[C])
