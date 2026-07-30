days = int(input())
total = 0
salary = 1

while days > 0:
    paid_days = min(days, salary)
    total += salary * paid_days
    days -= paid_days
    salary += 1

print(total)
