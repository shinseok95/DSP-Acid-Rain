import sys
database = open(file="database", mode="rt", encoding="utf-8")
forserver = open(file=".db", mode="wt", encoding="utf-8")
if len(sys.argv) == 1:
    text = database.read()
    lines = text.split("\n")
    for line in lines:
        forserver.write(line.split(" ")[0])
        forserver.write("\n")
else:
    text = database.read()
    lines = text.split("\n")
    for line in lines:
        tags = line.split(" ")
        word = tags[0]
        tags.pop(0)
        for tag in tags:
            if tag == sys.argv[1]:
                forserver.write(word)
                forserver.write("\n")
database.close()
forserver.close()
