student_count = int(input())
best_name = ""
best_amount = -1
total_amount = 0

for _ in range(student_count):
    name, final_score_text, class_score_text, leader, west, paper_count_text = input().split()
    final_score = int(final_score_text)
    class_score = int(class_score_text)
    paper_count = int(paper_count_text)
    amount = 0
    amount += 8000 if final_score > 80 and paper_count >= 1 else 0
    amount += 4000 if final_score > 85 and class_score > 80 else 0
    amount += 2000 if final_score > 90 else 0
    amount += 1000 if final_score > 85 and west == "Y" else 0
    amount += 850 if class_score > 80 and leader == "Y" else 0
    total_amount += amount
    if amount > best_amount:
        best_name, best_amount = name, amount

print(best_name)
print(best_amount)
print(total_amount)
