#!/usr/bin/python
# -*- coding: utf-8 -*-

from sys import stdin, stdout

while True:
        # 입력이 끝날 때 까지 stdin 입력받기
        line = stdin.readline().strip()
        # 만약 받은 문장이 ""면 끝
        if line == "":
            break
        # 입력된 문장을 공백으로 split
        words = line.split()
        # 각 단어를 한번씩 stdout으로 모두 출력시킴
        for i in range(len(words)-1):
            stdout.write(words[i] + " " + words[i+1] + "\t1\n")
