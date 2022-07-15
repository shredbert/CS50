#!/usr/bin/env python3
class Student():
    def __init__(self, name, id):
        self.name = name
        self.id = id

    def changeID(self, id):
        self.id = id

    def print(self):
        print(f"{self.name} - {self.id}")


student = Student("Jane", 10)
student.print()
student.changeID(11)
student.print()
