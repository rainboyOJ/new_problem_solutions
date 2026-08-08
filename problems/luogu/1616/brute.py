import sys

data = list(map(int, sys.stdin.buffer.read().split()))
T, M = data[0], data[1]
herbs = list(zip(data[2::2], data[3::2]))

best = 0

def dfs(idx, used_time, total_value):
    global best
    if idx == M:
        if used_time <= T and total_value > best:
            best = total_value
        return
    t_i, v_i = herbs[idx]
    max_k = (T - used_time) // t_i
    for k in range(max_k + 1):
        dfs(idx + 1, used_time + k * t_i, total_value + k * v_i)

dfs(0, 0, 0)
print(best)
