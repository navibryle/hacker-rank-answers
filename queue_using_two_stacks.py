# Enter your code here. Read input from STDIN. Print output to STDOUT
import sys
'''
solution:
Have a enqueue stack and a dequeue stack. Type 1 transfer all data into the enqueue stack and push new data onto the enqueue stack.Type 2 transfer all data into the dequeue stack and pop the top of the stack. Type 3 transfer all data into the dequeue stack and peek the top of the stack.

new solution: new solution cut the queue in half and have an enqueue stack and a dequeue stACK. Put the front half in a stack with the front 
on top of the stack and take the end into another stack with the end facing up. when dequeue just pop from dequeue stack and when enqueueing 
add to enqueue stack. when dequeue stack is empty cut the stack in half.
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
    #the
    stack = a_stack.get_stack
    stack_mid = len(stack)//2
    enqueue_stack = Stack()
    dequeue_stack = Stack()
    enqueue_stack.set_stack(stack[:stack_mid])
    dequeue_stack.set_stack(stack[stack_mid:])
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
        if (self.is_empty()):
            self.enqueue_stack.push(new_elem)
        elif (self.enqueue_stack.is_empty()):
            #in this case the dequeue stack is not empty therefore we need to
            #transfer the contents of the dequeue stack onto the enqueue stack and
            #proceed to enqueue new_eleme onto the enqueue stack
            self.enqueue_stack.stack_transfer(self.dequeue_stack)
            self.enqueue_stack.push(new_elem)
        else:
            #in this case the all the data is in the enqueue stack therefore we just need
            #to push new_elem onto the stack
            self.enqueue_stack.push(new_elem)
    def dequeue(self):
        if (self.is_empty()):
            None
        elif (self.enqueue_stack.is_empty()):
            #in this case all the data is in the dequeue stack and we just need to pop 
            #that stack
            self.dequeue_stack.pop()
        else:
            #in this case all the data is in the enqueue stack so we need to transfer all
            #the data onto the dequeue stack and then pop the dequeue stack
            self.dequeue_stack.stack_transfer(self.enqueue_stack)
            self.dequeue_stack.pop()
    def __str__(self):
        #this will print the front of the queue
        if (self.enqueue_stack.is_empty()):
            #in this case all the data is in the dequeue stack and we just need to pop 
            #that stack

            return str(self.dequeue_stack.peek())
        else:
            #in this case all the data is in the enqueue stack so we need to transfer all
            #the data onto the dequeue stack and then pop the dequeue stack
            #print(self.dequeue_stack.stack)
            self.dequeue_stack.stack_transfer(self.enqueue_stack)
            #print(self.dequeue_stack.stack)
            return str(self.dequeue_stack.peek())

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
