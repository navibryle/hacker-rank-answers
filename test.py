def addOne(item):
    return item+1
def main ():
    aList = [1,2,3]
    return map(addOne,aList)
print(list(main()))