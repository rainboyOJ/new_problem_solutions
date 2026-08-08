import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
mms = []
idx = 1
for _ in range(n):
    rmb, rp, time = data[idx], data[idx + 1], data[idx + 2]
    idx += 3
    mms.append((rmb, rp, time))
m, r = data[idx], data[idx + 1]

best_cnt = 0
best_time = 0
for mask in range(1 << n):
    cnt = 0
    tot_rmb = 0
    tot_rp = 0
    tot_time = 0
    for i in range(n):
        if mask >> i & 1:
            rmb, rp, time = mms[i]
            tot_rmb += rmb
            tot_rp += rp
            tot_time += time
            cnt += 1
    if tot_rmb <= m and tot_rp <= r:
        if cnt > best_cnt or (cnt == best_cnt and tot_time < best_time):
            best_cnt = cnt
            best_time = tot_time

print(best_time)
