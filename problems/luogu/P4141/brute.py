import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n, m = data[0], data[1]
w = data[2:2 + n]

f = [0] * (m + 1)
f[0] = 1
for wi in w:
    for j in range(m, wi - 1, -1):
        f[j] = (f[j] + f[j - wi]) % 10

out_lines = []
for i in range(n):
    g = [0] * (m + 1)
    for j in range(m + 1):
        if j < w[i]:
            g[j] = f[j]
        else:
            g[j] = (f[j] - g[j - w[i]]) % 10
    out_lines.append(''.join(str(g[j]) for j in range(1, m + 1)))

sys.stdout.write('\n'.join(out_lines))
