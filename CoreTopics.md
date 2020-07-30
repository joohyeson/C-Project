## Core Topics

1. Pointers + Arrays
- A pointers are variables that indicate the location of another variable. If you put the value in the pointer, you can have an address value for that variable. And Using pointer, reference to the memory address makes it easy to access and manipulate various data types variables.

- Arrays are lists of data of the same type as one variable. You can decide how much you want to use, then initialize the array, and use it. Arrays are sized according to the data type when declaring, so the index access is fast. So arrays are useful when the indices are important.

2. Bit operations
- Bit is the smallest unit that computer can use, to save the binary digits like '1011'.
Bit operations are the operations that applied in bits for the binary digits.
Bit operations can improve the CPU performance, because '4/2' is the same as '4>>1' but, using '>>' is less expensive behavior.
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

3. Operator Overloading
- Operator overloading is to redefine existing =,-,*, etc. operators. In this way, you can use operators like class+class and class*class.
- It can be used by redefining the operator within the function. The code below is how I used 'Operator Overloading' for this project.
```
template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
    nodePtr = nodePtr->pNext;

    return *this;
}
```

4. Return Value Optimization
- The return value optimization is literally to store the return value in caller's memory to optimize the return value. For example, if you give a constructor a copy constructor, the constructor will not be called twice. Only the constructor is called once and no temporary objects are created. The code below is how I used 'Return Value Optimization' for this project.
```
template<typename T>
List<T>::Iterator List<T>::end(void)
{
    return Iterator(&data[mSize], mSize);
}
```

5. Inheritance + Polymorphism
- Polymorphism and inheritance are important concepts of OOP(Object Oriented Programming). If we use polymorphism well, it can provide a consistent usage method to users regardless of the contents of the function. Polymorphism with this advantage can be implemented using inheritance. First of all, inheritance has base class (superclass) and derived class (subclass). If you create at least one function declared as pure virtual in a super class, all subclasses must override that function. We can implement polymorphism in inheritance through this method.
//More explanatation about Inheritance(duplicating in a new class?) and then Polymorphism(virtual table).

```
**Inheritance Example: GameState.h&Level1.h**

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

**Polymorphism Example: Level1::Draw().h&Level2::Draw()**

void Level1::Draw()//override Game State's pure virtual function
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

//Another Draw function that use reference base class?
//Calling draw function?
```

6. Rule of 5, RAII, r-value references/Move Semantics

 **Rule of 5**
- Along with Rule of 3 (copy constructor, assignment operator, assignment destructor), move constructor and move assignment operator are also rules that must be defined in the class. This rule is important because it has a lot to do with optimization.

 **RAII**
- C++ has a risk of memory leak because the programmer has to free it manually. RAII (Resource Acquisition is Initialization) is used to eliminate the possibility of memory leak. Simply put, This is a programming concept where the initialize (constructor) the thing is done, and then it releases automatically in it's destructor. If you use std::lock_guard, std::scoped_lock, std::unique_lock, etc, you can easily lock and unlock the memory. 

 **r-value references/Move Semantics**
- The r-value is what makes the move possible, not a copy of the memory. Here, r-value is the value to the right of the expression. The r-value does not exist when the expression ends. For r-value reference, use operator &&.

7. Templates
- A template is a frame created so that a class or function once created can be used in multiple data types. The advantage of using a template is that the code is shortened and easy to modify because there is no need to rewrite the code multiple times.

8. STL Container + Iterators + Algorithms
//refer to cs22519kr moodle page.
- STL containers provide various types of template classes. STL Container is useful because programmer can choose what to use for the purpose, as each container has its own pros and cons.

- STL Iterator is a repeater who can read and move the data memory address stored in the previous container. 
And iterator is an interface, that make the container and algorithm work as one.
When using STL algorithms and other functions are also useful because iterators are easy to access the elements of the container.

- STL Algorithm is a function that is defined in the <algorithm> library.
There are lots of different functions like 'find', 'erase' and so on.
It is useful because programmer can perform various complex tasks, using iterators and containers with algorithm functions.
//one algorithm function to all containers.