## Core Topics

**1. Pointers + Arrays**

- Pointers

Pointers are variables that indicate the location of another variable. 

If you put the value in the pointer, you can have an address value for that variable. 

And Using pointer, reference to the memory address makes it easy to access and manipulate various data types variables.

```c++
// We are using Player* mPlayer in Level 2.
mPlayer->SetValues(playerAnimation, static_cast<float>(Engine::GetWindow().GetSize().x >> 1), static_cast<float>(Engine::GetWindow().GetSize().y >> 1), 0, 20);
mPlayer->dx = 0;
mPlayer->dy = 0;

if (mPlayer->GetIsMoving() == true)
{
    mPlayer->animation = playerMoveAnimation;
}
else
{
    mPlayer->animation = playerAnimation;
}

if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Right))
{
    mPlayer->angle += MOVING_ANGLE;
}
if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Left))
{
    mPlayer->angle -= MOVING_ANGLE;
}

if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Up))
{
    mPlayer->SetIsMoving(true);
}
else
{
    mPlayer->SetIsMoving(false);
}
```

- Arrays

Arrays are lists of data of the same type as one variable. 

You can decide how much you want to use, then initialize the array, and use it. 

Arrays are sized according to the data type when declaring, so the index access is fast. 

So arrays are useful when the indices are important.

```c++
bool mKeyPressed[sf::Keyboard::KeyCount];
bool mKeyReleased[sf::Keyboard::KeyCount];
bool mKeyTriggered[sf::Keyboard::KeyCount];

bool mMousePressed[sf::Mouse::ButtonCount];
bool mMouseReleased[sf::Mouse::ButtonCount];
bool mMouseTriggered[sf::Mouse::ButtonCount];

void Input::Reset()
{
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        mKeyPressed[i] = 0;
        mKeyReleased[i] = 0;
        mKeyTriggered[i] = 0;
    }

    for (int i = 0; i < sf::Mouse::ButtonCount; ++i)
    {
        mMousePressed[i] = 0;
        mMouseReleased[i] = 0;
        mMouseTriggered[i] = 0;
    }
}
```

**2. Bit operations**

A bit is the smallest unit that the computer can use, to save the binary digits like '1011'.

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
Engine::GetWindow().GetSize().x >> 1;

//And we used bit flags like this.
//New flag here!
```

**3. Operator Overloading**

Operator overloading is to redefine existing '=', '-', '/', etc. operators. In this way, you can use operators like 'class + class' and 'class - class'.

It can be used by redefining the operator within the function. The code below is how I used 'Operator Overloading' for this project.

```c++
template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
    nodePtr = nodePtr->pNext;

    return *this;
}
```

**4. Return Value Optimization**

The return value optimization is literally to store the return value in the caller's memory to optimize the return value. 

RVO is useful because it speeds up the runtime.

Suppose we return a really big resource from a function.

If we do not use RVO, we will make the resource locally, and return it. 

Then, we have to pay for that cost to deep copy and deallocate that big temporary object.

The code below is how I used 'Return Value Optimization' for this project.

```c++
//RVO here
```

**5. Inheritance + Polymorphism**

- Inheritance

Inheritance is one of the important concepts of OOP (Object Oriented Programming) along with polymorphism and encapsulation. 

Inheritance has a base class (superclass) and derived class (subclass). The advantage of inheritance is that you can reuse code. 

If you create a function or variable in the base class, you can use the same content as in the base class without declaring the same content in the derived class.

- Inheritance Example: GameObject.h & Level2.h & Level2.cpp
```c++
class GameObject
{
public:
    GameObject() {};
    void SetValues(Animation& newAnimation, float newX, float newY, float newAngle = 0, float newRadius = 1);
    virtual void Update() {};
    void Draw(sf::RenderWindow& window);
    bool IsCollideWith(GameObject* object);
    bool IsAlive(){ return isAlive;};
    virtual ~GameObject() {};
private:
    float x, y, dx, dy, radius, angle;
    bool isAlive = true;
    std::string name;
    Animation animation;
};

class Player : public GameObject
{
public:
    Player();
    void Update() override;
    bool GetIsMoving();
    void SetIsMoving(bool newIsMoving);
private:
    bool isMoving;
};
//there is no declare, but we can use baseclass' functions and variables

void Level2::Update([[maybe_unused]] double dt)
{
  for (auto objectIterator = mGameObjectList.begin(); objectIterator != mGameObjectList.end();)
        {
            GameObject* object = *objectIterator;

            if (object->IsAlive() == false)
            {
                objectIterator = mGameObjectList.erase(objectIterator);
                delete object;
            }
            else
            {
                objectIterator++;
            }
        }
}
//mGameObjectList has player. 
//We can see that we can also use functions and variables declared in the game object class, not the player class.
```

- Polymorphism

Polymorphism and inheritance are important concepts of OOP(Object Oriented Programming). 

If we use polymorphism well, it can provide a consistent usage method to users regardless of the contents of the function. 

Polymorphism with this advantage can be implemented using inheritance. 

If at least one function in the superclass is implemented as virtual, a virtual function table in charge of this class is created.

This table is a collection of virtual function pointers. 

When we override the virtual function in the subclass, a virtual pointer of the subclass is created. 

The virtual pointers of the subclass have a unique location when overridden, but when not overridden, they point to the virtual pointer location of the base class. 

We can implement polymorphism in inheritance through this method.

- Virtual table & Pointer example

```c++
class shape
{
    public:
        virtual void draw() {std::cout<<"draw shape"<<std::endl;}
        virtual void print() {std::cout<< "print shape"<<std::endl;}

}

class rectangle{
    public:
        void draw() {std::cout<<"draw shape"<<std::endl;} override;

}
[shape virtual table]  
[shape::draw()]
[shape::print()]

[rectangle virtual table]
[rectangle::draw()]
[shape::print()]
```

- Polymorphism Example: Level1::Draw().h & Level2::Draw() & GameStateManager::SetRunningState()

```c++
class GameState
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
};

class Level1 : public GameState
{
public:
    Level1();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Level1"; }
};

class Level2 : public GameState
{
public:
    Level2();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Level2"; }
};

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

void GameStateManager::SetRunningState(double dt)
{
    mCurrentGameState->Draw();

    mCurrentGameState->Update(dt);

}//mCurrentGameState is a variable that stores subclasses that have GameState as the base class.
```

**6. Rule of 5, RAII, r-value references/Move Semantics**

 - RAII

C++ has a risk of memory leak because the programmer has to free it manually. 

So RAII (Resource Acquisition Is Initialization) is used to eliminate the possibility of memory leak. 

Simply put, we initialize and allocate resources in the constructor, and then it deallocates automatically in its destructor.

So using RAII is useful because there will be no possible memory leak, so the code become more stable.

```c++
//List count constructor
```

- Rule of 5

Not like the rule of 0, that avoids defining operations, uses default, does not allocate and deallocate. 

Rule of 5 has, along with Rule of 3 (copy constructor, copy assignment operator, destructor), move constructor, and move assignment operator.

For copy constructor and copy assignment operator, 

the default copy constructor is a shallow copy. So if we do not define a copy constructor for a deep copy, 

and we just use a default copy constructor to make an object,

a new object uses the same memory address with the object that is just copied. 

Then, 'delete' will be called twice on the same memory address, 

and there will be memory corruption and segmentation fault for 'double free'.

For these reasons, we need a copy constructor and copy assignment operator.

And for move constructor, and move assignment operator,

copying objects can be expensive as it involves creating, 

copying and then destroying temporary objects.

So it is useful to only have one resource at a time. 

This resource's ownership can be transferred from one manager to another. 

In such cases, we define and use move constructor and move assignment operator.

Thus, using the rule of 5 is important 

because the programmer can safely and efficiently implement RAII to manage dynamically allocated resources.

```c++
Node* MakeNode(T data)
{
    //We have to manually manage the allocated resources, 
    //so we need rule of 5 to handle resources more safely and efficiently.
    Node* pNewNode = new Node();
    pNewNode->data = data;
    pNewNode->pNext = nullptr;
    pNewNode->pPrev = nullptr;

    return pNewNode;
}

template<typename T>
List<T>::~List()
{
    clear();
}

template<typename T>
void List<T>::clear()
{
    Node* current = pHead;
    Node* next;

    while (current != nullptr)
    {
        next = current->pNext;
        delete current;
        --mSize;
        current = next;
    }

    pHead = nullptr;
    pTail = nullptr;
}

template<typename T>
void List<T>::deep_copy(const List<T>& rhs)
{
    if (rhs.pHead != nullptr)
    {
        pHead = MakeNode(rhs.pHead->data);

        Node* pTemp = pHead;
        Node* rhsTemp = rhs.pHead->pNext;

        while (rhsTemp != nullptr)
        {
            pTemp->pNext = MakeNode(rhsTemp->data, nullptr, pTemp);
            pTemp = pTemp->pNext;
            rhsTemp = rhsTemp->pNext;
        }

        pTail = pTemp;
    }

    mSize = rhs.mSize;
}

//copy constructor(deep copy)
template<typename T>
List<T>::List(const List<T>& rhs)
{
    deep_copy(rhs);
}

//move constructor 
template<typename T>
List<T>::List(List<T>&& rhs)
{
    pHead = rhs.pHead;
    pTail = rhs.pTail;
    mSize = rhs.mSize;

    rhs.pHead = nullptr;
    rhs.pTail = nullptr;
    rhs.mSize = 0;
}

//copy assignment operator(deep copy)
template<typename T>
List<T>& List<T>::operator=(const List<T>& rhs)
{
    clear();
    deep_copy(rhs);

    return *this;
}

//move assignmnet operator
template<typename T>
List<T>& List<T>::operator=(List<T>&& rhs)
{
    if (this != &rhs)
    {
        clear();

        pHead = rhs.pHead;
        pTail = rhs.pTail;
        mSize = rhs.mSize;

        rhs.pHead = nullptr;
        rhs.pTail = nullptr;
        rhs.mSize = 0;
    }

    return *this;
}
```

- r-value references/Move Semantics

The r-value's name comes from the reason that the value is to the right of the expression.

R-value is a special name for a temporary object that does not have a variable name.

So no variable name means that we cannot get the address and reference to it.

This is useful to copy more efficiently, because r-value object has very short life time,

so it will disappear very soon. So if we just move the object, we can save the cost of deep copy.

To express r-value in c++, we make a type declaration of a reference that has '&&'(This is not a logical and!).

```c++
//This is a move constructor of List class.
template<typename T>
List<T>::List(List<T>&& rhs)
{
    pHead = rhs.pHead;
    pTail = rhs.pTail;
    mSize = rhs.mSize;

    rhs.pHead = nullptr;
    rhs.pTail = nullptr;
    rhs.mSize = 0;
}
```

**7. Templates**

A template is a frame created so that a class or function once created can be used with multiple data types. 

The advantage of using a template is that the code is shortened and easy to modify because there is no need to rewrite the code multiple times for every possible types.

And Generics is the idea to allow type (Integer, String, and user-defined types) to be a parameter to methods, classes, and interfaces. 

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

**8. STL Container + Iterators + Algorithms**

- STL Container

STL container is various types of a template class, like linked list, tree, stack, queue. 

STL container can manage a collection of objects.

STL Container is useful because the programmer can choose what to use for the purpose, as each container has its pros and cons.

```c++
void Level1::Selected(sf::Vector2i location)
{
    mToVisit.clear();

    if (mGrid[location.x][location.y] != EMPTY)
    {
        return;
    }
    else
    {
        mToVisit.push_back(location);
    }
}
```

- STL Iterators

STL Iterator is a common interface for accessing data of the container. 

STL Iterator can traverse over the contents of a container or a subset of the container.

STL Iterator is useful because as it can access the container, Programmers can perform various complex tasks with algorithm functions using iterators.

```c++
std::vector<sf::Vector2i>::iterator checkAlreadyExist = std::find(mEmptyPlace.begin(), mEmptyPlace.end(), location);

if (checkAlreadyExist != mEmptyPlace.end())
{
    return false;
}
```

- STL Algorithms

STL Algorithm is a function that is defined in the <algorithm> library.

There are search, sort, access, find, and so on.

It is useful because algorithm uses the iterator as an interface, so algorithm function can be used in all containers.

```c++
//When initializing grid and show grid in Level 1.
mGrid.resize(GRID_LENGTH);
std::generate(mGrid.begin(), mGrid.end(), EmptyRow);

mShowGrid.resize(GRID_LENGTH);
std::generate(mShowGrid.begin(), mShowGrid.end(), TileRow);
```