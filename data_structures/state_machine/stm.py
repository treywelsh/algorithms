#!/usr/bin/env python

#class fsm():
#    def __init__(self):
#        self.edges = {}
#        self.accepting = []

#a+1+
edges = {(1, 'a') : 2,
        (2, 'a') : 2,
        (2, '1') : 3,
        (3, '1') : 3}
accepting = [3]


def build_fsm(string):
    pass        


def fsmsim_reccursive(string, current, edges, accepting):
    if string == "":
        if current in accepting:
            return True
    else:
        letter = string[0]
        if (current, letter) in edges:
            destination = edges[(current, letter)]
            remaining_string = string[1:]
            return fsmsim(remaining_string, destination, edges, accepting)
        else:
            return False

def fsmsim_iterative(string, state, edges, accepting):
    rest = list(string)
    while rest:
        #TODO exceptions : if rest is empty ...
        letter = rest.pop(0)
        if (state, letter) in edges:
            state = edges[(state, letter)]
        else:
            return False
    if state in accepting:
        return True
    return False


print fsmsim_iterative("aaa111",1,edges,accepting) # >>> True
print fsmsim_iterative("",1,edges,accepting)    #False
print fsmsim_iterative("ab1",1,edges,accepting) #False
print fsmsim_iterative("a1",1,edges,accepting)  #True
print fsmsim_iterative("a",1,edges,accepting)   #False
print fsmsim_iterative("1",1,edges,accepting)   #False
