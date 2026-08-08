import sys

n = int(sys.stdin.buffer.read().split()[0])
total = n * (n + 1) // 2
if total % 2 != 0:
    print(0)
else:
    target = total // 2
    ans = 0
    for mask in range(1 << n):
        s = 0
        for i in range(1, n + 1):
            if mask >> (i - 1) & 1:
                s += i
        if s == target:
            ans += 1
    print(ans // 2)
