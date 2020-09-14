/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Stack implementation                                *
 *                                                                  *
 *******************************************************************/

#include <stdint.h>
#include <iostream>
#include <string>

#include "logger.h"
#include "stack.h"

BLOG_INITIALISE(eLogDebug)

class Person
{
public:
    Person(std::string _name, uint32_t _age)
        : name(_name),
          age(_age)
    {
    }

    ~Person()
    {
    }

    std::string Name()
    {
        return name;
    }

    uint32_t Age()
    {
        return age;
    }

    friend std::ostream& operator<<(std::ostream& out, const Person& person)
    {
        out << person.name << ", " << person.age;
        return out;
    }

private:
    std::string name;
    uint32_t age;
};

void AddPerson(std::string name, uint32_t age, Stack<Person>& stack)
{
    Person new_person(name, age);
    stack.Push(new_person);
}

int main(int argc, char* argv[])
{
    BLOG(eLogInfo) << "Stack implementation test program...";

    Stack<Person> person_stack;
    AddPerson("Phillip Haddad", 36, person_stack);
    AddPerson("Suzie Haddad", 35, person_stack);
    AddPerson("Isaac Haddad", 10, person_stack);
    AddPerson("Ava Haddad", 7, person_stack);
    person_stack.Print();

    Person next_person = person_stack.Pop();

    BLOG(eLogInfo) << "Popped off [" << next_person << "] from the stack.";

    person_stack.Print();

    return 0;
}
