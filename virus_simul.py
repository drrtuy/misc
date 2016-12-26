#!/usr/bin/python
#Virus pop simul

import numpy
import random
import pylab


class NoChildException(Exception):

class SimpleVirus(object):

    """
    Representation of a simple virus (does not model drug effects/resistance).
    """
    def __init__(self, maxBirthProb, clearProb):

        """
        maxBirthProb: Maximum reproduction probability (a float between 0-1)        
        clearProb: Maximum clearance probability (a float between 0-1).
        """
        self.maxBirthProb=maxBirthProb
        self.clearProb=clearProb

    def doesClear(self):

        if (random.random()<=self.clearProb):
            return True
        
        return False

    
    def reproduce(self, popDensity):

        if(random.random()>=self.maxBirthProb * (1 - popDensity)):
            raise NoChildException
        newVirus=SimpleVirus(self.maxBirthProb,self.clearProb)
        return newVirus


class SimplePatient(object):

    """
    Patient model
    """    

    def __init__(self, viruses, maxPop):

        """
        viruses: list of virus instances
        maxPop: int
        """
        self.viruses=viruses
        self.maxPop=maxPop


    def getTotalPop(self):

        return len(self.viruses)


    def update(self):

    """
        returns viruses pop count
    """

        virusList=self.viruses[:]
        for virus in virusList:
            if(virus.doesClear()):
                self.viruses.remove(virus)

        if(not self.getTotalPop()):
            return 0
        popDensity=float(self.getTotalPop())/self.maxPop

        virusList=self.viruses[:]
        for virus in virusList:
            try:
                self.viruses.append(virus.reproduce(popDensity))
            except NoChildException:
                continue

        return self.getTotalPop()


def simulationWithoutDrug():

    initPop=100
    maxPop=1000
    maxBirthProb=0.1
    clearProb=0.05
    maxSteps=300
    yValues=[]
    xValues=[n for n in range(1,301,1)]
    virusList=[SimpleVirus(maxBirthProb,clearProb) for i in range(initPop)]
    patient=SimplePatient(virusList,maxPop)
    
    for i in range(maxSteps):
        patient.update()
        yValues.append(patient.getTotalPop())
    
    pylab.plot(xValues,yValues,'g^')
    pylab.title("Virus population dynamics")
    pylab.xlabel("Elapsed timeticks")
    pylab.ylabel("Virus population size")
    pylab.show()
    

def noTherapyMean():
    initPop=100
    maxPop=1000
    maxBirthProb=0.1
    clearProb=0.05
    maxSteps=300
    trials=100
    yValues=[[] for i in range(maxSteps)]
    xValues=[n for n in range(1,maxSteps+1,1)]

    for i in range(trials):                
        virusList=[SimpleVirus(maxBirthProb,clearProb) for i in range(initPop)]
        patient=SimplePatient(virusList,maxPop)
        
        for it in range(maxSteps):
            patient.update()
            yValues[it].append(patient.getTotalPop())
        
    
    yMeanValues=[ sum(yValues[it])/float( len(yValues[0]) ) for it in range(maxSteps) ]

    pylab.plot(xValues,yMeanValues)
    pylab.title("Virus population dynamics")
    pylab.xlabel("Elapsed timeticks")
    pylab.ylabel("Virus population size")
    pylab.show()














