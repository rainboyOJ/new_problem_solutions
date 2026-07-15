target = float(input())

distance = 0.0
step = 2.0
answer = 0

while distance < target:
    distance += step
    step *= 0.98
    answer += 1

print(answer)
