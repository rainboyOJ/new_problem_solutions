import re

sentence = input()
print(re.sub(r"\S+", lambda match: match.group()[::-1], sentence))
