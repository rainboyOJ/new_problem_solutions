n = int(input())

students = []
for order in range(n):
    name, year, month, day = input().split()
    students.append((int(year), int(month), int(day), -order, name))

students.sort()

for student in students:
    print(student[4])
