k = int(input())

answer = 0
value = 1

while k > 0:
    days = min(k, value)
    answer += days * value
    k -= days
    value += 1

print(answer)
