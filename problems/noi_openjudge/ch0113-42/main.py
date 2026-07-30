from collections import defaultdict

book_count = int(input())
books_by_author = defaultdict(list)

for _ in range(book_count):
    book_id, authors = input().split()
    for author in authors:
        books_by_author[author].append(book_id)

author = max(books_by_author, key=lambda name: len(books_by_author[name]))
print(author)
print(len(books_by_author[author]))
print(*books_by_author[author], sep="\n")
