from math import hypot, inf


n = int(input())
points = [tuple(map(float, input().split())) for _ in range(n)]
distance = [
    [hypot(x1 - x2, y1 - y2) for x2, y2 in points]
    for x1, y1 in points
]

full = 1 << n
dp = [[inf] * n for _ in range(full)]
for index, (x, y) in enumerate(points):
    dp[1 << index][index] = hypot(x, y)

for mask in range(full):
    for last in range(n):
        current = dp[mask][last]
        if current == inf:
            continue
        remaining = (full - 1) ^ mask
        while remaining:
            bit = remaining & -remaining
            remaining -= bit
            nxt = bit.bit_length() - 1
            next_mask = mask | bit
            dp[next_mask][nxt] = min(
                dp[next_mask][nxt],
                current + distance[last][nxt],
            )

print(f"{min(dp[-1]):.2f}")
