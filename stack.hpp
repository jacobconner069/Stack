#ifndef STACK_HPP
#define STACK_HPP

#include <deque>
#include <iostream>

template <typename T>
Stack<T>::Stack()
{
    container = std::deque<T>();
}

template <typename T>
Stack<T>::~Stack()
{
    clear();
}

template <typename T>
Stack<T>::Stack(const Stack<T> &other)
{
    container = other.container;
}

template <typename T>
Stack<T>::Stack(Stack<T> &&other)
{
    container = std::move(other.container);
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other)
{
    if (this != &other)
    {
        container = other.container;
    }
    return *this;
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&other)
{
    if (this != &other)
    {
        container = std::move(other.container);
    }
    return *this;
}

template <typename T>
bool Stack<T>::empty() const
{
    return container.empty();
}

template <typename T>
void Stack<T>::clear()
{
    container.clear();
}

template <typename T>
void Stack<T>::push(const T &x)
{
    container.push_back(x);
}

template <typename T>
void Stack<T>::push(T &&x)
{
    container.push_back(std::move(x));
}

template <typename T>
void Stack<T>::pop()
{
    if (!empty())
    {
        container.pop_back();
    }
}

template <typename T>
T &Stack<T>::top()
{
    if (!empty())
    {
        return container.back();
    }
    throw std::runtime_error("Stack is empty");
}

template <typename T>
const T &Stack<T>::top() const
{
    if (!empty())
    {
        return container.back();
    }
    throw std::runtime_error("Stack is empty");
}

template <typename T>
int Stack<T>::size() const
{
    return container.size();
}

template <typename T>
void Stack<T>::print(std::ostream &os, char ofc) const
{
    for (const auto &item : container)
    {
        os << item << ofc;
    }
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const Stack<T> &a)
{
    a.print(os);
    return os;
}

template <typename T>
bool operator==(const Stack<T> &a, const Stack<T> &b)
{
    Stack<T> tempA = a;
    Stack<T> tempB = b;

    if(tempA.size() != tempB.size()) {
        return false;
    }

    while(!tempA.empty() && !tempB.empty()) {
        if(tempA.top() != tempB.top()) {
            return false;
        }
        tempA.pop();
        tempB.pop();
    }
    
    return true;
}

template <typename T>
bool operator!=(const Stack<T> &a, const Stack<T> &b)
{
    return !(a == b);
}

template <typename T>
bool operator<=(const Stack<T> &a, const Stack<T> &b)
{
    return a.size() <= b.size();
}


#endif