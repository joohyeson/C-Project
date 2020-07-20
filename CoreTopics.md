## Core Topics

1. Pointers + Arrays
- A pointers are variables that indicate the location of another variable. If you put the value in the pointer, you can have an address value for that variable. And Using pointer, reference to the memory address makes it easy to access and manipulate various data types variables.
- Arrays are lists of data of the same type as one variable. You can decide how much you want to use, then initialize the array, and use it. Arrays are sized according to the data type when declaring, so the index access is fast. So arrays are useful when the indices are important.

2. Bit operations
- Bit operations are calculating the bits using bit operators. It is using bit operations like '<<' to left shift. The bit operations are useful because the 8 bits to be written to one byte bool variable, which can save memory.

3. Operator Overloading
- Operator overloading is to redefine existing =,-,*, etc. operators. In this way, you can use operators like class+class and class*class.
- It can be used by redefining the operator within the function.
'''
Point& operator+(const Point& Ref){};
'''

4. Return Value Optimization
- The return value optimization is literally to store the return value in one memory to optimize the return value. For example, if you give a constructor a copy constructor, the constructor will not be called twice. Only the constructor is called once and no temporary objects are created. The return optimization can be useful, such as operator overloading by using memory efficiently.

5. Inheritance + Polymorphism
- **Inheritance**
- What is Inheritance? 

- Inheritance has base class (superclass) and derived class (subclass). As the name suggests, it is inheriting another class or struct. 
- Why is it important?

- The first advantage of using Inheritance is that it reduces the amount of code. The second advantage is that if classes with similar roles exist as independent classes rather than inheritance, it takes a lot of time to modify the code, but using Inheritance only requires modification of the base class.

- How does it work?
- After creating the base class, when creating the class to inherit, specify the base class next to the class name.

'''
class base{};
class derived:public base{};
'''
- **Polymorphism**
- What is Polymorphism? 

- It is one of the important concepts in OOP (Object Oriented Programming). Simply put, different objects respond to the same message in their own way. For example, if you have a shape class and a circle, square, and triangle that inherits the shape class, you can think of each class' Draw() function causing different results.

- Why is it important?

- It's easy to reuse code, and you only need to modify the class.

- How does it work?

'''
class base{
   Draw(){};
};
class derived:public base{
   Draw(){};
};
'''

6. Rule of 5, RAII, r-value references/Move Semantics
- **Rule of 5**

- Along with Rule of 3 (copy constructor, assignment operator, assignment destructor), move constructor and move assignment operator are also rules that must be defined in the class. This rule is important because it has a lot to do with optimization.

- **RAII**
- C++ has a risk of memory leak because the programmer has to free it manually. RAII (Resource Acquisition is Initialization) is used to eliminate the possibility of memory leak. Simply put, This is a programming concept where the initialize (constructor) the thing is done, and then it releases automatically in it's destructor. If you use std::lock_guard, std::scoped_lock, std::unique_lock, etc, you can easily lock and unlock the memory. 

- **r-value references/Move Semantics**

- The r-value is what makes the move possible, not a copy of the memory. Here, r-value is the value to the right of the expression. The r-value does not exist when the expression ends. For r-value reference, use operator &&.


7. Templates
- A template is a frame created so that a class or function once created can be used in multiple data types. The advantage of using a template is that the code is shortened and easy to modify because there is no need to rewrite the code multiple times.

8. STL Container + Iterators + Algorithms
- STL containers provide classes of data storage objects provided by STL.
As STL container is a template, you must set the type of variable when declare the STL container.
STL containers have various types and each has its pros and cons. So datas can be managed in a useful way if needed.

- STL Iterator is a repeater who can read and move the data memory address stored in the previous container.
Similarly, since it is a template, you must set the type of variable and use it after receiving the container value that you want to access.
When using STL algorithms and other functions are also useful because iterators are easy to access the elements of the container.

- STL Algorithm is a function that can be used using the container and repeater in front.
You can include the <algorithm> library and use the functions in it.
It is useful to have iterators in containers and to perform various tasks easily.
