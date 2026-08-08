n = int(input())
best_student = None
best_total = -1

for _ in range(n):
    name, chinese, math, english = input().split()
    chinese = int(chinese)
    math = int(math)
    english = int(english)
    total = chinese + math + english

    if total > best_total:
        best_total = total
        best_student = (name, chinese, math, english)

print(best_student[0], best_student[1], best_student[2], best_student[3])
