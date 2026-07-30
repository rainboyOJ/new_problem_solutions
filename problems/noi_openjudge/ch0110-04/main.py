student_count = int(input())
students = []

for student_id in range(1, student_count + 1):
    chinese, math, english = map(int, input().split())
    total = chinese + math + english
    students.append((student_id, chinese, total))

# 总分、语文分取相反数可得到降序；学号保持正数则为升序。
students.sort(key=lambda student: (-student[2], -student[1], student[0]))
for student_id, _, total in students[:5]:
    print(student_id, total)
