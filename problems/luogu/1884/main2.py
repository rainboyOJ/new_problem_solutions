import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
rects = []
xs_set, ys_set = set(), set()
p = 1
for _ in range(n):
    x1, y1, x2, y2 = data[p:p+4]
    p += 4
    x_low, x_high = (x1, x2) if x1 < x2 else (x2, x1)
    y_low, y_high = (y1, y2) if y1 < y2 else (y2, y1)
    rects.append((x_low, y_low, x_high, y_high))
    xs_set.add(x_low); xs_set.add(x_high)
    ys_set.add(y_low); ys_set.add(y_high)

xs = sorted(xs_set)
ys = sorted(ys_set)

xid = {v: i for i, v in enumerate(xs)}
yid = {v: i for i, v in enumerate(ys)}

diff = [[0] * (len(xs) + 1) for _ in range(len(ys) + 1)]

for x1, y1, x2, y2 in rects:
    ix1, ix2 = xid[x1], xid[x2]
    iy1, iy2 = yid[y1], yid[y2]
    diff[iy1][ix1] += 1
    diff[iy1][ix2] -= 1
    diff[iy2][ix1] -= 1
    diff[iy2][ix2] += 1

pref = [[0] * (len(xs) + 1) for _ in range(len(ys) + 1)]
ans = 0
for i in range(len(ys)):
    si = i + 1
    for j in range(len(xs)):
        sj = j + 1
        pref[si][sj] = pref[i][sj] + pref[si][j] - pref[i][j] + diff[i][j]
        if pref[si][sj]:
            ans += (xs[j + 1] - xs[j]) * (ys[i + 1] - ys[i])

print(ans)
