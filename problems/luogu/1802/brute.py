import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n, x = data[0], data[1]
friends = []
for i in range(n):
    lose, win, use = data[2 + i * 3:5 + i * 3]
    friends.append((lose, win, use))

best = 0
for mask in range(1 << n):
    total_cost = 0
    total_exp = 0
    for i in range(n):
        lose_i, win_i, use_i = friends[i]
        if mask >> i & 1:
            total_cost += use_i
            if total_cost <= x:
                total_exp += win_i
            else:
                break
        else:
            total_exp += lose_i
    else:
        if total_cost <= x and total_exp > best:
            best = total_exp
print(best * 5)
