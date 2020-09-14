/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Linked List implementation                          *
 *                                                                  *
 *******************************************************************/

#include <stdint.h>
#include <iostream>
#include <string>

#include "logger.h"
#include "linked_list.h"

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

void AddPerson(std::string name, uint32_t age, LinkedList<Person>& list)
{
    Person new_person(name, age);
    list.InsertTail(new_person);
}

int main(int argc, char* argv[])
{
    BLOG(eLogInfo) << "Linked List implementation test program...";

    BLOG(eLogInfo) << "Starting with integer linked list.";

    LinkedList<int> integer_list;

    // Insert some numbers in a list
    integer_list.InsertHead(10);
    integer_list.InsertHead(2);
    integer_list.InsertHead(5);
    integer_list.InsertHead(1);
    integer_list.InsertHead(8);
    integer_list.InsertHead(9);
    integer_list.InsertHead(9);
    integer_list.InsertHead(9);

    integer_list.Print();
    integer_list.Delete(9);
    integer_list.Print();
    integer_list.Delete(9, true);
    integer_list.Print();

    LinkedList<Person> person_list;
    AddPerson("Phillip Haddad", 36, person_list);
    AddPerson("Suzie Haddad", 35, person_list);
    AddPerson("Isaac Haddad", 10, person_list);
    AddPerson("Ava Haddad", 7, person_list);
    person_list.Print();

    return 0;
}

