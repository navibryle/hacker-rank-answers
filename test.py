# Enter your code here. Read input from STDIN. Print output to STDOUT
import sys
'''
this is the correct answer
'''

class Stack:
    def __init__(self):
        #front of the stack is the end of the list
        self.stack = []
    def push(self,new_elem):
        self.stack.append(new_elem)
    def pop(self):
        self.stack.pop()
    def peek(self):
        return self.stack[-1]
    def is_empty(self):
        if len(self.stack) == 0:
            return True
        return False
    def set_stack(self,a_list):
        self.stack = a_list
    def get_stack(self):
        return self.stack
    
def cut_stack(a_stack):
    #will return a tuple of 2 stacks the stack being cut in half
    #will only work with enqueue stack
    #first index is enqueue stack second index is dequeue stack
    stack = a_stack.get_stack()
    if len(stack) == 1:
        stack_mid = 1
    else:
        stack_mid = len(stack)//2
    enqueue_stack = Stack()
    dequeue_stack = Stack()
    enqueue_stack.set_stack(stack[stack_mid:])
    dequeue_stack.set_stack(stack[stack_mid-1::-1])
    return [enqueue_stack,dequeue_stack]
class Queue:
    def __init__(self):
        self.enqueue_stack = Stack()
        self.dequeue_stack = Stack()
    def is_empty(self):
        if (self.enqueue_stack.is_empty() and self.dequeue_stack.is_empty()):
            return True
        return False
    def enqueue(self,new_elem):
       self.enqueue_stack.push(new_elem)
    def dequeue(self):
        if (self.dequeue_stack.is_empty()):
            new_stacks = cut_stack(self.enqueue_stack)
            self.enqueue_stack = new_stacks[0]
            self.dequeue_stack = new_stacks[1]
            self.dequeue_stack.pop()
        else:
            self.dequeue_stack.pop()
    def __str__(self):
        #this will print the front of the queue
        if (self.dequeue_stack.is_empty()):
            new_stacks = cut_stack(self.enqueue_stack)
            self.enqueue_stack = new_stacks[0]
            self.dequeue_stack = new_stacks[1]
            return self.dequeue_stack.peek()
        else:
            return self.dequeue_stack.peek()

def main():
    queries = sys.stdin.readlines()
    queue = Queue()
    for item in queries:
        if item[0:2] == '1 ':
            new_elem = item[2:].replace('\n','')
            queue.enqueue(new_elem)
        elif item[0] == '2':
            queue.dequeue()
        elif item[0] == '3':
            print(queue)
main()
