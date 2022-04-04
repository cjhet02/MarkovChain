file = open("testIn.txt", "r", encoding="UTF-8", errors='replace')
data = file.read()

data = data.lower()
punc = [".", ", ", "? ", "! ", "; ", ": ", "~"]
for char in punc:
    data = data.replace(char, " " + char + " ")

bad = ["™", "@"]
for char in bad:
    data = data.replace(char, "")

print(data)
out = open("cleaned.txt", "w", errors='replace')
out.write(data)
out.close()
file.close()