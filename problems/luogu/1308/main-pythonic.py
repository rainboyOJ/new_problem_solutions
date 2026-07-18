import re

word = input().strip()
article = input().rstrip("\n")
matches = list(re.finditer(rf"(?i)\b{re.escape(word)}\b", article))
print(-1 if not matches else f"{len(matches)} {matches[0].start()}")
