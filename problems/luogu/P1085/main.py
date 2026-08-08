answer = 0
max_hours = 8

for day in range(1, 8):
    school, extra = map(int, input().split())
    total = school + extra
    if total > max_hours:
        max_hours = total
        answer = day

print(answer, end="")
