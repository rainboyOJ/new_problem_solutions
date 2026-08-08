n = int(input())
students = []

for student_id in range(1, n + 1):
    chinese, math, english = map(int, input().split())
    total = chinese + math + english
    students.append((student_id, total, chinese))

students.sort(key=lambda student: (-student[1], -student[2], student[0]))

for student in students[:5]:
    print(student[0], student[1])
