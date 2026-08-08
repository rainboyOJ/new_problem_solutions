n = int(input())
students = []
for order in range(n):
    name, year, month, day = input().split()
    students.append((int(year), int(month), int(day), -order, name))

print("\n".join(map(lambda item: item[4], sorted(students))))
