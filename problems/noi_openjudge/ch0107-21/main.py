sentence = input()
old_word = input().strip()
new_word = input().strip()

words = sentence.split(" ")
print(" ".join(new_word if word == old_word else word for word in words))
