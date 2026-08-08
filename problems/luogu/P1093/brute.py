n = int(input())
students = []
for student_id in range(1, n + 1):
    chinese, math, english = map(int, input().split())
    students.append((student_id, chinese + math + english, chinese))

top = sorted(students, key=lambda x: (-x[1], -x[2], x[0]))[:5]
print("\n".join(f"{student_id} {total}" for student_id, total, _ in top))
