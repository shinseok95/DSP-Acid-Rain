import sys
import sysv_ipc
import time

database = open(file="database", mode="rt", encoding="utf-8")
while True:
    try:
        q = sysv_ipc.MessageQueue(2017610015)
    except:
        time.sleep(1)
    else:
        break

if sys.argv[1] == "ALL":
    text = database.read()
    lines = text.split("\n")
    for line in lines:
        q.send(line.split(" ")[0], type=1, block=True)
else:
    text = database.read()
    lines = text.split("\n")
    for line in lines:
        tags = line.split(" ")
        word = tags[0]
        tags.pop(0)
        for tag in tags:
            if tag == sys.argv[1]:
                q.send(word, type=1, block=True)
q.send("END", type=1, block=True)
database.close()
