cash = 0
savings = 0

for month in range(1, 13):
    budget = int(input())
    cash += 300 - budget
    if cash < 0:
        print(-month)
        break
    savings += cash // 100 * 100
    cash %= 100
else:
    print(cash + int(savings * 1.2))
