# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem: SearchProblem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

def breadthFirstSearch(problem: SearchProblem):
    """Search the shallowest nodes in the search tree first."""
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    n = Directions.NORTH
    e = Directions.EAST
    now = problem.getStartState()
    tri = problem.getSuccessors(problem.getStartState())
    corners = 0
    gone_goal = []
    route = list()
    while corners < 4:
        queue = []
        queue.append(now)
        traversed = []
        traversed.append(now)
        dir = [[] for i in range(100000)]
        a = 0
        b = 0
        while (len(queue) > 0):
            vertex = queue.pop(0)
            nodes = problem.getSuccessors(vertex)
            if (problem.isGoalState(vertex)) and (vertex not in gone_goal):
                break
            for x in nodes:
                if x[0] not in traversed:
                    queue.append(x[0])
                    traversed.append(x[0])
                    b = b + 1
                    if x[1] == "South":
                        dir[b] = dir[a] + [s]
                    elif x[1] == "West":
                        dir[b] = dir[a] + [w]
                    elif x[1] == "North":
                        dir[b] = dir[a] + [n]
                    else:
                        dir[b] = dir[a] + [e]
            a = a + 1
        route.extend(dir[a])
        now = vertex
        gone_goal.append(now)
        corners = corners + 1
    return route
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

def uniformCostSearch(problem: SearchProblem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

class Node():
    """A node class for A* Pathfinding"""

    def __init__(self, parent=None, position=None):
        self.parent = parent
        self.position = position

        self.g = 0
        self.h = 0
        self.f = 0

    def __eq__(self, other):
        return self.position == other.position

def aStarSearch(problem: SearchProblem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    from  searchAgents import CornersProblem
    limit = 1
    if type(problem) == CornersProblem:
        limit = 4
    count = 0
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    n = Directions.NORTH
    e = Directions.EAST
    gone_goal = []
    start_node = Node(None, problem.getStartState())
    start_node.g = start_node.h = start_node.f = 0
    start_node.h = heuristic(start_node.position, problem, gone_goal)
    route = []
    while count < limit:
        open_list = []
        closed_list = []
        open_list.append(start_node)
        while len(open_list) and count < limit:
            current_node = open_list[0]
            current_index = 0
            for index, item in enumerate(open_list):
                if item.f < current_node.f:
                    current_node = item
                    current_index = index
            open_list.pop(current_index)
            closed_list.append(current_node)
            if problem.isGoalState(current_node.position) and current_node.position not in gone_goal:
                path = []
                current = current_node
                while current.parent is not None:
                    pre = current.parent
                    if current.position[0] > pre.position[0]:
                        path.append(e)
                    elif current.position[0] < pre.position[0]:
                        path.append(w)
                    elif current.position[1] > pre.position[1]:
                        path.append(n)
                    elif current.position[1] < pre.position[1]:
                        path.append(s)
                    current = pre
                "print(path[::-1])"
                route.extend(path[::-1])  # Return reversed path   #need to look carefully
                gone_goal.append(current_node.position)
                start_node = Node(None, current_node.position)
                start_node.g = start_node.f = 0
                start_node.h = heuristic(start_node.position, problem, gone_goal)
                count = count + 1
                if count == limit:
                    return route
                break
            children = []
            tri = problem.getSuccessors(current_node.position)
            for new_successor in tri:
                node_position = new_successor[0]
                new_node = Node(current_node, node_position)
                children.append(new_node)
            for child in children:
                conti = 0
                for closed_child in closed_list:
                    if child.position == closed_child.position:
                        conti = 1
                if conti:
                    continue
                child.g = current_node.g + 1
                child.h = heuristic(child.position, problem, gone_goal)
                child.f = child.g + child.h
                for open_node in open_list:
                    if child.position == open_node.position and child.g > open_node.g:
                        conti = 1
                if conti:
                    continue
                open_list.append(child)
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
