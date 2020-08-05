# CS225 Class Project

For this class you will be creating your own C++ project to practice the main topics of the course.

You can create almost any project you like as long as it is approved by the instructor. For example you could create a small Game, command line tool, useful library of some kind, or even a collection of these.

You may also form small teams of 2. Teams of 3 may be possible with instructor permission and if the project merits 3 people.

You must do the project in this GitHub repo. We will use this to do daily (Monday-Friday) code reviews via pull requests with the instructor.

The goal of this project is for you to make something you think is interesting, practice the core topics, and gain some insight from the instructor's experience.

## Core Topics

Create a CoreTopics markdown file.

You must create a document that explains the following:

**In your own words**, explain the following programming topics. 

Topics:

1. Pointers + Arrays
2. Bit operations
3. Operator Overloading
4. Return Value Optimization
5. Inheritance + Polymorphism
6. Rule of 5, RAII, r-value references/Move Semantics
7. Templates
8. STL Containers + Iterators + Algorithms

Tip: For each topic think about the What, Why and How. Like, What is it? Why is it important? How does it work?

All of these topics must be incorporated into the project. For each topic explanation provide a small code snippet from your project that shows you are using the topic.

## ReadMe

You must create a ReadMe markdown file that provides the following information:

1. your name, project name, course name, term
2. Section describing anything incomplete about the project
3. Section to Provide file name and line numbers for all code related requirements.
4. Section to Introduces your project
    - What is it
    - What does it do
    - How to build the project
    - How to interact with the project
5. Section describing something you're proud of about the project
6. Section that describes work that was done to earn an Excellent score

## Submission

This git repo will be your submission location for the source code and project files.

The course site is where you will submit your pre-built binaries of the project. For example, if you created a small game then you will submit the exe and the needed data files of the game there.

The instructor will use the repo for examining the code and building the project. The course site submission will be used to quickly run and try out your project.

## Rubric

- [X] [**core**] All source code, data files and project files need to build and run the project are in this repo
- [X] [**core**] Created a ReadMe markdown file with all of the needed information
- [X] [**core**] Created a CoreTopics markdown file with all of the needed information
- [X] [**core**] Make good use of pointers and arrays
- [X] [**core**] Use Bitwise operations to create a some kind of configuration variable where you extract values. _(Combine bit flags of varying powers of 2)_
- [X] [**core**] Use bitwise operations to replace Arithmetic Operations
- [X] [**core**] Makes good use of operator overloading
- [X] [**core**] Has examples of Return Value Optimization
- [X] [**core**] Makes good use of Inheritance and Polymorphism
- [X] [**core**] Makes good use of Rule of 5
- [X] [**core**] Makes good use of Rule of 0
- [X] [**core**] Makes good use of RAII
- [X] [**core**] Makes good use of Templates
- [X] [**core**] Makes good use of STL Containers
- [X] [**core**] Makes good use of STL Iterators
- [X] [**core**] Makes good use of STL Algorithms
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

Score for the project will be given as the following:

Score        | Assessment
------------ | ----------
Zero         | Nothing turned in at all
Failing      | Close to meeting core requirements
Rudimentary  | Meets all of the core requirements
Satisfactory | Close to meeting all requirements
Good         | Clearly meets all requirements 
Excellent    | High quality, well beyond the requirements
