k = int(input())

answer = 0
day = 0
coin = 1
while day < k:
    for _ in range(coin):
        if day == k:
            break
        answer += coin
        day += 1
    coin += 1

print(answer)
