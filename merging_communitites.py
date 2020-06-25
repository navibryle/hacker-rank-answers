# Enter your code here. Read input from STDIN. Print output to STDOUT
#issue output is incorrect
#possible cause the old member of the list is outdated so we should have it only point to one root
import fileinput
class Community:
    def __init__(self,representative):
        self.representative = representative
        self.size = 1
    def addMember(self,index):
        self.size += 1
        self.members.append(index)
    def get_size(self):
        return self.size
def findRoot(member,parent):
    #member will be an index
    root = member
    while parent[root-1].representative != root:
        root = parent[root-1].representative
    return root
def mergingQuery(member1,member2,parent):
    '''
    find the root of the community with smaller members and have it point to the root of the community with more members
    the root will be the single source of truth for the sizes of the communities.
    '''
    member1Root = parent[findRoot(member1.representative,parent)-1]
    member2Root = parent[findRoot(member2.representative,parent)-1]
    if member1Root.representative != member2Root.representative:
        if (member1Root.size > member2Root.size):
            member1Root.size += member2Root.size
            member2Root.representative = member1Root.representative
        else:
            member2Root.size += member1Root.size
            member1Root.representative = member2Root.representative
def make_to_community(anInt):
    return Community(anInt)
def main():
    query = []
    parent = []
    for line in fileinput.input():
        
        if line[0].isdigit():
            lineSplit = line.split()
            #item+1 so that the representative when we turn these integers into communities are correct
            parent2 = list(map(make_to_community,[item+1 for item in range(int(lineSplit[0]))]))
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
            memberRoot = parent[findRoot(member.representative,parent)-1]
            print(memberRoot.size)
main()