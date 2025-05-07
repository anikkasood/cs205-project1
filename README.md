# CS 170 Project #1

## Group Members:

### Jyro Jimenez, Nhan Nguyen, Anika Sood

## Discussion Time: 2pm

### Summary:

In this project, we have to develop a program to solve the classic eight-puzzle using the A* search algorithm. Using the A* search algorithm, we will solve the puzzle using:
1. Uniform Cost Search
2. A* with the Misplaced Tile heuristic
3. A* search with the Euclidean Distance heuristic

### Design Summary:

For our design, we opted in using a Graph Search Algorithm, where we used a node class to keep track of its parent node and branching nodes. Using this algorithm, we only expand to states we think are valid, while keeping a closed list of explored states. Because of the way we expand and visit nodes, our search algorithm falls under the category of a Graph Search Algorithm. 

In our Graph Search Algorithm, we traverse through our graph using four different transitions: “up,” “down,” “left,” and “right.” With these transition states, we check if a square is able to move in these directions and expand from this. To keep track of already explored nodes through a vector called “explored,” where we keep the states of found nodes. Because of this design method, if a is valid through our transitions and if a node has not been visited by an earlier state, we expand to that state and search from there. After exploring a node, we then push this state into a priority queue to prioritize the first node expanded in order to see where it leads. Using this queue, we follow the earlier algorithm and keep expanding nodes until we reach the goal state, where we then return the solution path by going up to each node’s parent node. By returning the solution path, we can find the exact path the search algorithm took in order to find the goal state.

Other than the search algorithm, we utilize different heuristic functions to calculate the cost of each node, which is then used in our priority queue. Each heuristic function calculates the distance differently. For Uniform Cost Search, the heuristic function is set to h(n) = 0, as we do not care about how far we are from the goal state. As for the A* with the Misplaced Tile heuristic, we calculate h(n) by looking at each tile and seeing how many are not in correct positions. Using this information, we add transition cost g(n) and heuristic h(n) to find the total cost. Lastly, in A* search with the Euclidean Distance heuristic, we found the distance a tile to the goal state similar to using the distance formula in a graph. Using these functions, we pass them into our search function through referencing them by a pointer to the function itself. This makes it so our main function to solve the problem can be reused with different heuristic functions.

### Objects and Methods:
- Problem Class:
    - Stores initial state, goal state, transitions/actions.
    - Used to expand state and contain the overall model of the program.
- Node Class:
    - A node class containing information about the parent node, actions used, and total cost to reach a node.
- Heuristic Methods:
    - Header file used to contain functions to calculate h(n) or heuristics used within the search algorithm.
- graph_search function:
    - Main function used to find the goal state from an initial state (hardcoded or user input).

### Difficulties and Challenges:
Some difficulties and challenges we had with solving the problem consisted of team management, problem approach, and project implementation. Our team initially had problems with time management with the project, as we all had different schedules to work with. While not pertaining to the code written, it was the initial problem we had to solve in order to work together and finish our work.

Additionally, our approach to the problem was also a part of the difficulties we faced. Each member of the group had a different understanding of the problem, which made deciding on a solution to be confusing. Our understanding differed, where each of us thought of a different way to implement the solution. One such example would be the misunderstanding of the problem space, and how each heuristic was a different search algorithm. However, this was corrected by another team member to make sure we were headed in the right direction. Other difficulties in our planning and discussion surfaced, but using the first week to discuss the problem, we came to an agreement and common understanding to solve the project.

Finally, for the final steps in the project, the implementation. In this phase, we as a team saw some difficulty in implementing what we discussed, researched, and studied. One such source would be the lecture slides and online sources such as geeksforgeeks, where we tried to understand its implementation in code. Before fully implementing the search function, we had to decide on what type of structure we would have. By narrowing it down to a graph with a closed list, we modeled our search with this in mind and didn't have much difficulty until we needed to figure out how to implement our heuristic functions. We solved this problem by implementing different functions for each heuristic and referencing them through our search function. This helped us lessen our code and made it more concise and reusable.

### Analysis/Findings:
- Test Cases
    - Trivial:
        1 2 3
        4 5 6
        7 8 0
    - Easy:
        1 2 0
        4 5 3
        7 8 6
    - Oh Boy:
        8 7 1
        6 0 2 
        5 4 3
    - Very Easy:
        1 2 3
        4 5 6 
        7 0 8
    - Doable:
        0 1 2 
        4 5 3 
        7 8 6
    - Impossible:
        1 2 3 
        4 5 6 
        8 7 0

- Graph and Table:

    - Empty for now