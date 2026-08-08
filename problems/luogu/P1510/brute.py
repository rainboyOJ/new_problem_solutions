import sys

data = list(map(int, sys.stdin.buffer.read().split()))
v_target, n, c = data[0], data[1], data[2]
stones = []
idx = 3
for _ in range(n):
    k, m = data[idx], data[idx + 1]
    idx += 2
    stones.append((k, m))

best_vol = 0
best_stamina = 0
for mask in range(1 << n):
    vol = 0
    stamina = 0
    for i in range(n):
        if mask >> i & 1:
            k, m = stones[i]
            vol += k
            stamina += m
    if stamina <= c:
        if vol > best_vol or (vol == best_vol and stamina < best_stamina):
            best_vol = vol
            best_stamina = stamina

if best_vol >= v_target:
    print(c - best_stamina)
else:
    print('Impossible')
