student_count, rank = map(int, input().split())
students = []

for _ in range(student_count):
    student_id, score = input().split()
    students.append((student_id, float(score)))

# 成绩互不相同，按成绩从高到低排列后第 rank 个即为答案。
student_id, score = sorted(students, key=lambda student: student[1], reverse=True)[rank - 1]
print(student_id, f"{score:g}")
