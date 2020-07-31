## Core Topics

1. Pointers + Arrays
- Pointers are variables that indicate the location of another variable. If you put the value in the pointer, you can have an address value for that variable. And Using pointer, reference to the memory address makes it easy to access and manipulate various data types variables.

```
//example here!
```

- Arrays are lists of data of the same type as one variable. You can decide how much you want to use, then initialize the array, and use it. Arrays are sized according to the data type when declaring, so the index access is fast. So arrays are useful when the indices are important.

```
//example here!
```

2. Bit operations
- A bit is the smallest unit that the computer can use, to save the binary digits like '1011'.
Bit operations are the operations that applied in bits for the binary digits.
Bit operations can improve the CPU performance because '4/2' is the same as '4>>1' but, using '>>' is less expensive behavior.
Below codes are the examples for the bit operations.

```
/*The NOT operation is an operation that reverses the value of each digit.
This operation can be used effectively to obtain remuneration for any value.*/
NOT(~) 0111
     = 1000

/*The OR operation compares the number of digits in each of the two values and calculates 1 if any of them have one, or 0.*/
      0101
OR(|) 0011
    = 0111

/*The XOR operation compares the number of digits in each of the two values and calculates 0 if the value is equal to 0, 0 if the value is equal to 1, and 1 if different.*/
       0101
XOR(^) 0011
     = 0110

/*The AND operation compares the digits of each of the two values, calculating 1 only when there is 1 in both values and 0 in the remaining cases.*/
       0101
AND(&) 0011
     = 0001

/*The SHIFT operation moves the values for some digits, and put 0 or 1 in the empty places.*/
 0000'1011 RIGHT SHIFT(>>) 2
              = 0000'0010

 1011'0000 LEFT SHIFT(<<) 2
             = 1100'0000
```

```c++
//We used '>>' instead using like Engine::GetWindow().GetSize().x / 2.
Engine::GetWindow().GetSize().x >> 1
```

3. Operator Overloading
- Operator overloading is to redefine existing =,-,*, etc. operators. In this way, you can use operators like class+class and class*class.
- It can be used by redefining the operator within the function. The code below is how I used 'Operator Overloading' for this project.
```c++
template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
    nodePtr = nodePtr->pNext;

    return *this;
}
```

4. Return Value Optimization
- The return value optimization is literally to store the return value in the caller's memory to optimize the return value. For example, if you give a constructor a copy constructor, the constructor will not be called twice. Only the constructor is called once and no temporary objects are created. The code below is how I used 'Return Value Optimization' for this project.
```c++
template<typename T>
List<T>::Iterator List<T>::end(void)
{
    return Iterator(&data[mSize], mSize);
}
```

5. Inheritance + Polymorphism

**Inheritance**

- Inheritance is one of the important concepts of OOP (Object Oriented Programming) along with polymorphism and encapsulation. Inheritance has a base class (superclass) and derived class (subclass). The advantage of inheritance is that you can reuse code. If you create a function or variable in the base class, you can use the same content as in the base class without declaring the same content in the derived class.

**Inheritance Example: GameState.h&Level1.h**
```c++
class GameState//base class
{
public:
    GameState() {};
    virtual void Load() = 0;
    virtual void Update(double dt) = 0;
    virtual void Unload() = 0;
    virtual void Draw() = 0;
    virtual std::string GetName() = 0;
    virtual ~GameState() {};
private:
};//pure virtual functions

class Level1 : public GameState//derived class
{
public:
    Level1();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Level1"; }

private:
    std::vector<std::vector<int>> mGrid;
    std::vector<std::vector<int>> mShowGrid;
    bool mShouldGameRun = true;
};

```

**Polymorphism**

- Polymorphism and inheritance are important concepts of OOP(Object Oriented Programming). If we use polymorphism well, it can provide a consistent usage method to users regardless of the contents of the function. Polymorphism with this advantage can be implemented using inheritance. If at least one function in the superclass is implemented as virtual, a virtual function table in charge of this class is created. This table is a collection of virtual function pointers. When we override the virtual function in the subclass, a virtual pointer of the subclass is created. If not overridden in a subclass, the virtual pointer of the base class is retained. We can implement polymorphism in inheritance through this method.

**Polymorphism Example: Level1::Draw().h&Level2::Draw()&GameStateManager::SetRunningState()**
```c++
void Level1::Draw() //override Game State's pure virtual function
{
    Engine::GetWindow().Clear(sf::Color(LIGHT_BLUE));
    text.setString("Minesweeper");
    ...
 }

 void Level2::Draw()
{
    Engine::GetWindow().Clear(sf::Color(BLACK));
    text.setString("Asteroid");
    ...
}

void GameStateManager::SetRunningState(double dt)
{
    mCurrentGameState->Draw();

    mCurrentGameState->Update(dt);
}
```

6. Rule of 5, RAII, r-value references/Move Semantics

 **RAII**
- C++ has a risk of memory leak because the programmer has to free it manually. So RAII (Resource Acquisition Is Initialization) is used to eliminate the possibility of memory leak. Simply put, This is a programming concept where the initialize (constructor) the thing is done, and then it releases automatically in its destructor.
So using RAII is useful because there will be no possible memory leak, so the code is more stable.
```c++
//RAII example here!
```

 **Rule of 5**
- Not like the rule of 0, that avoids defining default operations and does not allocate and deallocate. Rule of 5 has, along with Rule of 3 (copy constructor, assignment operator, assignment destructor), move constructor, and move assignment operator.
Using the rule of 5 is important because the programmer can safely and efficiently implement RAII to manage dynamically allocated resources.
```c++
    //We have to manually manage the allocated resources, so we need rule of 5 to handle resources more safely and efficiently.
    Node* MakeNode(T data)
    {
        Node* pNewNode = new Node();
        pNewNode->data = data;
        pNewNode->pNext = nullptr;
        pNewNode->pPrev = nullptr;

        return pNewNode;
    }

    ~List();
    List(const List<T>& rhs); // copy constructor
    List(List<T>&& rhs); // move constructor
    List<T>& operator=(const List<T>& rhs); // copy assignment
    List<T>& operator=(List<T>&& rhs); //move assignment
```

 **r-value references/Move Semantics**
- The r-value is what makes the move possible, to avoid unneeded copy. Here, the r-value is the value to the right of the expression. The r-value does not exist when the expression ends. For r-value reference, use '&&'.
```c++
//r-value example here!
```

7. Templates
- A template is a frame created so that a class or function once created can be used with multiple data types. The advantage of using a template is that the code is shortened and easy to modify because there is no need to rewrite the code multiple times for every possible types.

- Generics is the idea to allow type (Integer, String, and user-defined types) to be a parameter to methods, classes, and interfaces. 
As it is independent of data type, so it is very reusable and convenient. 
And generics can be implemented in C++ using Templates, like sort(), max(), min(), print().

```c++
// These are member functions of the List class. 
// All the different types will do the same behavior in the template functions.
template<typename T>
class List
{
    void push_front(T value);
    void push_back(T value);

    T pop_front(void);
    T pop_back(void);

    Iterator begin(void);
    Iterator end(void);

    Iterator erase(Iterator target);
    void clear();

    T back(void);
    T front(void);

    bool empty(void);
    int size(void);
}
```

8. STL Container + Iterators + Algorithms
- STL is a Standard template library.

- STL container is various types of a template class, like linked list, tree, stack, queue. 
STL container can manage a collection of objects.
STL Container is useful because the programmer can choose what to use for the purpose, 
as each container has its pros and cons.

- STL Iterator is a common interface for accessing data of the container. 
STL Iterator can traverse over the contents of a container or a subset of the container.
STL Iterator is useful because as it can access the container, 
Programmers can perform various complex tasks with algorithm functions using iterators.

- STL Algorithm is a function that is defined in the <algorithm> library.
There are search, sort, access, find, and so on.
It is useful because algorithm uses the iterator as an interface, so algorithm function can be used in all containers.

```c++
//example here!
```