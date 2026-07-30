row_count, column_count, time_limit = map(int, input().split())
peanuts = []

for row in range(1, row_count + 1):
    for column, amount in enumerate(map(int, input().split()), start=1):
        if amount:
            peanuts.append((amount, row, column))

peanuts.sort(reverse=True)
elapsed = 0
answer = 0
previous = None
for amount, row, column in peanuts:
    move = row if previous is None else abs(row - previous[0]) + abs(column - previous[1])
    if elapsed + move + 1 + row > time_limit:
        break
    elapsed += move + 1
    answer += amount
    previous = (row, column)

print(answer)
