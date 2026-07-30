student_count = int(input())
students = [input().split() for _ in range(student_count)]

# 元组 key 先比较负分数，再比较姓名，因此正好符合题目的两级规则。
students.sort(key=lambda student: (-int(student[1]), student[0]))
for name, score in students:
    print(name, score)
