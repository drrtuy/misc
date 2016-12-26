from util import manhattanDistance
from game import Directions,Actions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
      A reflex agent chooses an action at each choice point by examining
      its alternatives via a state evaluation function.

      The code below is provided as a guide.  You are welcome to change
      it in any way you see fit, so long as you don't touch our method
      headers.
    """
    def __init__(self):
        self.hash={}
        
    def registerInitialState(self, gameState):
        foodGrid=gameState.getFood()
        foodList=foodGrid.asList()
        if not foodList: return
        for posW in range(foodGrid.width):
            for posH in range(foodGrid.height):
                if not gameState.hasWall(posW,posH):
                    pos=(posW,posH)
                    posPointsDist=[(fPos,util.manhattanDistance(pos,fPos)) for fPos in foodList]
                    posPointsDist.sort(key=lambda v: v[1],reverse=True)
                    self.hash[pos]=posPointsDist

    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {North, South, West, East, Stop}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        #print "agent.getAction()",scores
        #raw_input()
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        #print "getAction() actions,scores",zip(legalMoves,scores)
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        #print "agent.evaluationFunction() actions",action
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
        addValue=0
        minFoodDist=0
        if len(self.hash[newPos]): minFoodPos,minFoodDist=self.hash[newPos].pop()
        ghostDist=[util.manhattanDistance(newPos,gp) for gp in successorGameState.getGhostPositions()]
        for i,gd in enumerate(ghostDist):
            if gd<2:
                if newScaredTimes[i]:
                    ghostDist[i]=gd*-50
                else:
                    ghostDist[i]=gd*50
            else:
                ghostDist[i]=0
        return successorGameState.getScore()-sum(ghostDist)-addValue-minFoodDist

def scoreEvaluationFunction(successorGameState):
    return successorGameState.getScore()

class MultiAgentSearchAgent(Agent):

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)
        self.currDepth=0
        self.hash={}


def isPacman(ind):
    return not ind

def isGhost(ind):
    return ind

class MinimaxAgent(MultiAgentSearchAgent):
    def getAction(self, gameState):
        v,action=self.dispMinMax(gameState,0,0)       
        return action

    def dispMinMax(self,gameState,currDepth,agentInd,action=None):
        if agentInd>=gameState.getNumAgents():
            currDepth+=1
            agentInd=0
        if currDepth>=self.depth or gameState.isWin() or gameState.isLose():
            if not action: action='Stop'
            return scoreEvaluationFunction(gameState),action
    
        nextAgentInd=agentInd

        if isPacman(nextAgentInd):
            v,action=self.maxAgentTurn(gameState,currDepth,nextAgentInd,action)
        if isGhost(nextAgentInd):
            v,action= self.minAgentTurn(gameState,currDepth,nextAgentInd,action)
        return v,action        
    
    def maxAgentTurn(self,gameState,currDepth,agentInd,action):
        v=-999999
        optimalAction=action
        for succAction in gameState.getLegalActions(agentInd):
            succState=gameState.generateSuccessor(agentInd, succAction)
            succValue,subAgentAction=self.dispMinMax(succState,currDepth,agentInd+1,action=succAction)
            if succValue>v: 
                v=succValue
                optimalAction=succAction
        if v==-999999: optimalAction='Stop'
        return v,optimalAction

    def minAgentTurn(self,gameState,currDepth,agentInd,action):
        v=999999
        optimalAction=action
        for succAction in gameState.getLegalActions(agentInd): 
            succState=gameState.generateSuccessor(agentInd, succAction)
            succValue,subAgentAction=self.dispMinMax(succState,currDepth,agentInd+1,action=succAction)
            if succValue<v:
                v=succValue
                optimalAction=succAction
        if v==999999: optimalAction='Stop'
        return v,optimalAction

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
      minimax agent with alpha-beta pruning
    """

    def getAction(self, gameState):
        startDepth,startAgent=(0,0)
        v,action=self.dispMinMax(gameState,startDepth,startAgent)
        print "getAction value",v,"action",action
        return action

    def dispMinMax(self,gameState,currDepth,agentInd,a=None,b=None,action=None):
        if agentInd>=gameState.getNumAgents():
            currDepth+=1
            agentInd=0
        if currDepth>=self.depth or gameState.isWin() or gameState.isLose():
            if not action: action='Stop'
            return scoreEvaluationFunction(gameState),action
    
        nextAgentInd=agentInd

        if isPacman(nextAgentInd):
            v,action=self.maxAgentTurn(gameState,currDepth,a,b,nextAgentInd,action)
        if isGhost(nextAgentInd):
            v,action= self.minAgentTurn(gameState,currDepth,a,b,nextAgentInd,action)
        return v,action        
    
    def maxAgentTurn(self,gameState,currDepth,a,b,agentInd,action):
        v=-999999
        optimalAction=action
        for succAction in gameState.getLegalActions(agentInd):
            succState=gameState.generateSuccessor(agentInd, succAction)
            succValue,subAgentAction=self.dispMinMax(succState,currDepth,agentInd+1,a,b,action=succAction)
            if succValue>v:
                v=succValue
                optimalAction=succAction
            #print "maxAgentTurn before prunning v",v,"b",b
            if b and v>b:
                #print "maxAgentTurn b prunning v,",v,"b",b
                return v,optimalAction
            if a==None: a=v
            else: a=max(v,a)
        if v==-999999: optimalAction='Stop'
        return v,optimalAction

    def minAgentTurn(self,gameState,currDepth,a,b,agentInd,action):
        v=999999
        optimalAction=action
        for succAction in gameState.getLegalActions(agentInd): 
            succState=gameState.generateSuccessor(agentInd, succAction)
            succValue,subAgentAction=self.dispMinMax(succState,currDepth,agentInd+1,a,b,action=succAction)
            if succValue<v:
                v=succValue
                optimalAction=succAction
            if a and v<a:
                return v,optimalAction
            #print "minAgentTurn before b comparision v",v,"b",b
            if b==None: b=v
            else: b=min(v,b)
            #print "minAgentTurn after b comparision v",v,"b",b
        if v==999999: optimalAction='Stop'
        return v,optimalAction


class ExpectimaxAgent(MultiAgentSearchAgent):
    def registerInitialState(self, gameState):
        foodGrid=gameState.getFood()
        foodList=foodGrid.asList()
        if not foodList: return
        for posW in range(foodGrid.width):
            for posH in range(foodGrid.height):
                if not gameState.hasWall(posW,posH):
                    pos=(posW,posH)
                    posPointsDist=[(fPos,util.manhattanDistance(pos,fPos)) for fPos in foodList]
                    posPointsDist.sort(key=lambda v: v[1],reverse=True)
                    self.hash[pos]=posPointsDist

    def getAction(self, gameState):
        startDepth,startAgent=(0,0)
        v,action=self.dispMinMax(gameState,startDepth,startAgent)
        return action

    def dispMinMax(self,gameState,currDepth,agentInd,action=None):
        if agentInd>=gameState.getNumAgents():
            currDepth+=1
            agentInd=0
        if currDepth>=self.depth or gameState.isWin() or gameState.isLose():
            #print "!!!!!!!!dispMinMax max depth reached value",self.evaluationFunction(gameState,self.hash,action),action
            if not action: action='Stop'
            if self.evaluationFunction==betterEvaluationFunction:
                return self.evaluationFunction(gameState,self.hash,action),action
            else:
                return self.evaluationFunction(gameState),action
        nextAgentInd=agentInd

        if isPacman(nextAgentInd):
            v,action=self.maxAgentTurn(gameState,currDepth,nextAgentInd,action)
        if isGhost(nextAgentInd):
            v,action= self.expectAgentTurn(gameState,currDepth,nextAgentInd,action)
        #print "dispMinMax action on return",action
        return v,action        
    
    def maxAgentTurn(self,gameState,currDepth,agentInd,action):
        v=-999999
        vaList=[]
        optimalAction=action
        for succAction in gameState.getLegalActions(agentInd):
            succState=gameState.generateSuccessor(agentInd, succAction)
            succValue,subAgentAction=self.dispMinMax(succState,currDepth,agentInd+1,action=succAction)
            if not currDepth:
                vaList.append((succValue,succAction))
            if succValue>v: 
                v=succValue
                optimalAction=succAction
        if v==-999999: optimalAction='Stop'
        if not currDepth:
            #print "maxAgentTurn options",vaList
            #print "maxAgentTurn choose v",v,"action",optimalAction
            if optimalAction=='Stop':
                for (value,action) in vaList:
                    if v==value and action!='Stop':
                        v,optimalAction=value,action    
                        #print "maxAgentTurn choosed new action",optimalAction
                        break
                #raw_input()
        return v,optimalAction

    def minAgentTurn(self,gameState,currDepth,agentInd,action):
        v=999999
        optimalAction=action
        for succAction in gameState.getLegalActions(agentInd): 
            succState=gameState.generateSuccessor(agentInd, succAction)
            succValue,subAgentAction=self.dispMinMax(succState,currDepth,agentInd+1,action=succAction)
            if succValue<v:
                v=succValue
                optimalAction=succAction
        if v==999999: optimalAction='Stop'
        return v,optimalAction

    def expectAgentTurn(self,gameState,currDepth,agentInd,action):
        v=0
        optimalAction=action
        succActions=gameState.getLegalActions(agentInd)
        for succAction in succActions:
            succState=gameState.generateSuccessor(agentInd, succAction)
            succValue,subAgentAction=self.dispMinMax(succState,currDepth,agentInd+1,action=succAction)
            v+=succValue
        return float(v)/len(succActions),action

def betterEvaluationFunction(successorGameState,hashA,action):
    newPos = successorGameState.getPacmanPosition()
    newFood = successorGameState.getFood()
    newGhostStates = successorGameState.getGhostStates()
    newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
    closeFoodDist=0
    nextFoodDist=0
    if len(hashA[newPos]):
        closeFoodPos,closeFoodDist=hashA[newPos][-1]
        foodX,foodY=closeFoodPos
        while not successorGameState.hasFood(foodX,foodY) and len(hashA[newPos]):
            hashA[newPos].pop()
            if len(hashA[newPos]): closeFoodPos,closeFoodDist=hashA[newPos][-1]
            else: break
            foodX,foodY=closeFoodPos
        if len(hashA[closeFoodPos]):
            nextFoodPos,nextFoodDist=hashA[closeFoodPos][-1]
            nextFoodX,nextFoodY=nextFoodPos
            while not successorGameState.hasFood(nextFoodX,nextFoodY) and len(hashA[closeFoodPos]):
                hashA[closeFoodPos].pop()
                if len(hashA[closeFoodPos]): nextFoodPos,nextFoodDist=hashA[closeFoodPos][-1]
                else: break
                nextFoodX,nextFoodY=nextFoodPos
        closeFoodDist+=nextFoodDist
    #if closeFoodDist<3: closeFoodDist=-closeFoodDist
    ghostDist=[util.manhattanDistance(newPos,gp) for gp in successorGameState.getGhostPositions()]
    for i,gd in enumerate(ghostDist):
        if gd<2:
            if newScaredTimes[i]:
                ghostDist[i]=gd*-50
            else:
                ghostDist[i]=gd*50
        else:
            ghostDist[i]=0
    return successorGameState.getScore()-sum(ghostDist)-newFood.count()-closeFoodDist*0.5+random.randint(0,5)#-actionCost

# Abbreviation
better = betterEvaluationFunction
