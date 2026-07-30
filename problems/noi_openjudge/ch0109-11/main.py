required = int(input())
text = input().strip()
count = 1
answer = "No"
for index in range(1, len(text)):
    count = count + 1 if text[index] == text[index - 1] else 1
    if count >= required:
        answer = text[index]
        break
if required == 1:
    answer = text[0]
print(answer)
