n = int(input())
students = []
for order in range(n):
    name, y, m, d = input().split()
    students.append((int(y), int(m), int(d), -order, name))
for *_, name in sorted(students):
    print(name)
