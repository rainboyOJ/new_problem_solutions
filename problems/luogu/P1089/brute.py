costs = [int(input()) for _ in range(12)]

hand = 0
saved = 0
for month, cost in enumerate(costs, start=1):
    hand += 300
    if hand < cost:
        print(-month)
        break
    hand -= cost
    while hand >= 100:
        saved += 100
        hand -= 100
else:
    print(hand + saved * 12 // 10)
