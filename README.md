## ReadMe

1. Name : Daeun Jeong, Juhye Son
* project name : CS228 PROJECT
* course name : CS225
* term : 20-07-20 ~ 20-08-07

2. The lists below are incomplete about the project.
- None

3. The lists below are complete about the project.
- [X] [**core**] All source code, data files and project files need to build and run the project are in this repo
- [X] [**core**] Created a ReadMe markdown file with all of the needed information
- [X] [**core**] Created a CoreTopics markdown file with all of the needed information
- [X] [**core**] Make good use of pointers and arrays ()(Pointers:List.h, Line 96~99/Array:Input.h, 46~52)
- [X] [**core**] Use Bitwise operations to create a some kind of configuration variable where you extract values. _(Combine bit flags of varying powers of 2)_ ()(Level2.cpp:435~451)
- [X] [**core**] Use bitwise operations to replace Arithmetic Operations ()(Level2.cpp, 257)
- [X] [**core**] Makes good use of operator overloading ()(List.h: 54~59)
- [X] [**core**] Has examples of Return Value Optimization ()(Level2.cpp:162~198)
- [X] [**core**] Makes good use of Inheritance and Polymorphism (GameState.h line 19, Level1.h line 22)
- [X] [**core**] Makes good use of Rule of 5 (List.hpp, line 39)
- [X] [**core**] Makes good use of Rule of 0 (Level1.h, line 34)
- [X] [**core**] Makes good use of RAII (List.hpp, line 18)
- [X] [**core**] Makes good use of Templates (List.hpp, line 22)
- [X] [**core**] Makes good use of STL Containers (Level1.cpp, line 32)
- [X] [**core**] Makes good use of STL Iterators (Level1.cpp, line 32)
- [X] [**core**] Makes good use of STL Algorithms (Level1.cpp, line 32)
- [X] All source files have a proper header comment with your name, project name, course name, term.
- [X] All source files compile without warnings and without errors
- [X] Reasonably High Warning levels and treat warnings as errors are enabled.
- [X] Correct files submitted. No unnecessary files submitted.
- [X] Followed the appropriate Code Quality Guidelines and Code Style Guidelines.
- [X] Utilize `clang-format` to automate code formatting
- [X] No obvious memory leaks in the code. _(Like not deleting memory in a destructor or not correctly implementing rule of 5)_
- [X] Reused functions as much as possible.
- [X] Code is organized nicely across multiple files.
- [X] Submitted pre-built executable(s) of the project on the course site
- [X] Source code submitted has no redundant computations.
- [X] Reused functions/code as much as possible.
- [X] Keep global variables to a minimum _(Allocate long lived objects on the stack in `main()` and then pass around pointers to it)_
- [X] All requirements that are completed are checked off here by replacing the `[ ]` with `[x]`

4. This project is a mini-games project, that has playable classic games.

* To build the project, set the 'CS228 PROJECT' to be the start project. And build.

* To interact with the project, Press space bar to go to the next level.
In 'minesweeper', click the left mouse button to show the tile, click the right mouse button to make a flag on the tile.
In 'asteroid', change the ship's angle by pressing the left arrow and right arrow. And move to up arrow, shoot to the space bar.
Press R key to restart the game for both games.

5. The things that we are proud of about the project.

* 1. We are proud of implementing the List class in the project our own. We have made a Singly linked list, vector in CS280 class. 
But it was the first time to make a double linked list. At first, we were worried if we could do it well, but now we are happy to complete it.

* 2. We are proud of implementing Rule of 5, Rule of 0 ourselves. We already studied Rule of 5, Rule of 0 before, but we did not understand it well. 
However, as we implemented Rule of 5, and Rule of 0 our own this time, we got to understand this well.

* 3. We are proud that we used the BFS when we made minesweeper. We have learned about BFS in CS280, and we applied it to the game based on what we learned. 
And fortunately, it worked well. So we are glad that we implemented it well.

* 4. We are proud of the good use of the source tree. When we were doing a game project for the last semester, 
we were not using it very well, so we pushed most of the things on the master branch, but now, we can use it well. 
And we realized that changes on the stage also be switched at the same time when switching a branch.

* 5. We devoted ourselves to the project every day for three weeks, including weekends. We are proud of our team's teamwork. 
It was the first time to do a project together, but we took care of each other, never be late, and we did our best. 
We have never shown a lazy attitude like doing nothing for the code review, or not making a pull request before the code review.
And also, rather than bringing what we did before, and getting points without effort, 
we thought about what we can do and what we will do to learn more and better.
We are proud that we have learned so much.

6. The work that was done to earn an Excellent score.

* 1. Our team didn't only care about core requirements but also put lots of attention into the game's details.
Especially when implementing minesweeper, we played the original minesweeper to make it as similar as possible.
And there was a bug that flags can be made on the number tiles, 
a bug that can't get rid of the flags that already made, 
a bug that has implemented BFS but is different from the original minesweeper's result.
And also, BFS proceeded one by one, which is actually should be done at once 
We fixed all these bugs, even though there is no one to play this.
The professor told us to pay more attention to the code than to complete the game.
But our team also put lots of effort into the game.

* 2. good use of STL Iterators and Algorithms -
We studied an algorithm functions that we have never used to create a 2D Vector at level1.cpp. Thanks to std::generate, 
we were able to make our code shorter and easier to understand than when we created it using the for statement.

```c++
std::vector<int> GetGridRow(void)
{
    std::vector<int> row(GRID_LENGTH, EMPTY);

    std::generate(row.begin() + 1, row.end() - 1,
        []()
    {
        if (rand() % LEVEL == 0)
        {
            return MINE;
        }
        return EMPTY;
    });

    return row;
}

void Level1::Load()
{
    //...
    std::generate(mGrid.begin() + 1, mGrid.end() - 1, GetGridRow);
    //...
}
```

In addition, the std::find function was used when implementing the BFS algorithm in the minesweeper.

```c++
bool Level1::TryToAdd(sf::Vector2i location)
{
    std::vector<sf::Vector2i>::iterator checkAlreadyExist = std::find(mEmptyPlace.begin(), mEmptyPlace.end(), location);

    if (checkAlreadyExist != mEmptyPlace.end())
    {
        return false;
    }
```

* 3. Makes good use of Inheritance and Polymorphism-In our game, GameState is an Inheritance structure, so we should get excellent in this part. Also, GameObject class was implemented using Inheritance and polymorphism.
Since these parts were the key to implementing our project, if we had written the code without using Inheritance and polymorphism, the code would have been much longer and harder to use.

* 4. We've made our own std::list.
First, we code using the STL container list, and then, implemented List class and iterator using template, and make a test driver and check it is working properly.
And in level2, the use of std::list was replaced with List container that we made.
It may be easy coding for someone, but we didn't even know that the std::list was the base of the linked list, and it was the first time making a double linked list like this.
So it took more time than we expected, and it was the most difficult part of the project.

* 5. We clean up the code as mush as possible that we can.
Below codes were very long in the previous version of the project.
There were lots of if checks and push backs. But now, we just have a least amount of it.

```c++
//This is a part of Level1::Load()
std::vector<sf::Vector2i> checkLocation = { sf::Vector2i(0,1), sf::Vector2i(1,0), sf::Vector2i(0,-1), sf::Vector2i(-1,0), sf::Vector2i(-1,1), sf::Vector2i(-1,-1), sf::Vector2i(1,-1), sf::Vector2i(1,1) };

for (int currCount = 0; currCount < checkLocation.size(); currCount++)
{
    if (mGrid[i + checkLocation.at(currCount).x][j + checkLocation.at(currCount).y] == MINE)
    {
        ++numberOfMines;
    }
}
```

```c++
//This is a part of Level1::CanVisit(void)
std::vector<sf::Vector2i> checkLocations = { sf::Vector2i(0,1), sf::Vector2i(1,0),sf::Vector2i(0,-1),sf::Vector2i(-1,0),sf::Vector2i(-1,1), sf::Vector2i(-1,-1),sf::Vector2i(1,-1),sf::Vector2i(1,1) };

for (int i = 0; i < checkLocations.size(); ++i)
{
    if (IsOutOfRange(currentLocation + checkLocations.at(i)) == false)
    {
        if (TryToAdd(currentLocation + checkLocations.at(i)) == true)
        {
            mToVisit.push_back(currentLocation + checkLocations.at(i));
        }
    }
}
```