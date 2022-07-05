#!/usr/bin/python3

import cs50

scores = []
for i in range(3):
    score = cs50.get_int("Score: ")
    scores.append(score)

avg = sum(scores) / len(scores)
print(f"Avg: {avg}")
