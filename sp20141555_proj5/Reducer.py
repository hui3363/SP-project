#!/usr/bin/python
from sys import stdin, stdout
book = {}


while True:
    #입력이 끝날때까지 (map의 출력결과로부터)입력받기
    line = stdin.readline().strip()
    if not line:
        break
    #\t로 split
    word, cnt = line.split("\t")
    #만약 새로운 단어가 아니면 1 더해주고 합침
    if word in book:
        book[word] += int(cnt)
    else:
        #새로운 단어이면 추가
        book[word] = int(cnt)
#결과 출력
for word in book:
    stdout.write(word + "\t" + str(book[word]) + "\n")
