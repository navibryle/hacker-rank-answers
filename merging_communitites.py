
# Enter your code here. Read input from STDIN. Print output to STDOUT
#passes the sample test case but fails all the other ones
import fileinput
class Community:
    def __init__(self,representative):
        self.representative = representative
        self.size = 1
    def addMember(self):
        self.size += 1
    def get_size(self):
        return self.size
def mergingQuery(member1,member2,parent):
    if isinstance(member1,Community) and isinstance(member2,Community):
        newRepresentative = member1.representative
        member1.size += member2.size
        for index in member2.members:
            parent[index] = member1
    elif isinstance(member1,Community) and isinstance(member2,int):
        
        member1.size += 1
        parent[member2-1] = member1
    elif isinstance(member2,Community) and isinstance(member1,int):
        
        member2.size += 1
        parent[member1-1] = member2
    else:
        #they are both integers
        newCommunity = Community(member1)
        newCommunity.size += 1
        parent[member1-1] = newCommunity
        parent[member2-1] = newCommunity
def main():
    query = []
    parent = []
    for line in fileinput.input():
        
        if line[0].isdigit():
            parent2 = [item+1 for item in range(int(line[0]))]
            parent = parent2
        else:
            query.append(line.rstrip())
    for item in query:
        if item[0] == 'M':
            '''
            3 cases for each memeber:
            1.)need to create a community 
            2.)need to add memeber to an existing community and change the memebers representative in the parent. And increase the size of the community
            3.)both memebers are part of a community therefore the root of member 1 becomes the new root of the newly joined community and the size of member 1 is increased
            '''
            querySplit = item.split()
            member1 = parent[int(querySplit[1])-1]
            member2 = parent[int(querySplit[2])-1]
            mergingQuery(member1,member2,parent)#this will mutate parent
        else:

            querySplit = item.split()
            member = parent[int(querySplit[1])-1]
            if isinstance(member,int):
                print(1)
            else:
                print(member.size)
main()