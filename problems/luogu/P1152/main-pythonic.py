import sys
data = list(map(int, sys.stdin.buffer.read().split()))
n, a = data[0], data[1:1 + data[0]]
diffs = []
ok = True
seen = set()
for i in range(n - 1):
    d = abs(a[i + 1] - a[i])
    if d < 1 or d >= n or d in seen:
        ok = False
        break
    seen.add(d)
print('Jolly' if ok and len(seen) == n - 1 else 'Not jolly')
