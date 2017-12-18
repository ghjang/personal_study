def makeInverseIndex(strlist):
    inverseIndex = {}
    for i, s in enumerate(strlist):
        for w in s.split():
            if w in inverseIndex:
                inverseIndex[w].add(i)
            else:
                inverseIndex[w] = set({ i })
    return inverseIndex

def orSearch(inverseIndex, query):
    result = set()
    for q in query:
        if q in inverseIndex:
            result.update(inverseIndex[q])
    return result

def andSearch(inverseIndex, query):
    result = set()
    for q in query:
        if q in inverseIndex:
            result.intersection_update(inverseIndex[q])
    return result
