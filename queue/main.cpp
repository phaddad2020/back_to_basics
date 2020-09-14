/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Queue implementation                                *
 *                                                                  *
 *******************************************************************/

#include <stdint.h>
#include <iostream>
#include <string>

#include "logger.h"
#include "queue.h"

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

void AddPerson(std::string name, uint32_t age, Queue<Person>& queue)
{
    Person new_person(name, age);
    queue.Enqueue(new_person);
}

int main(int argc, char* argv[])
{
    BLOG(eLogInfo) << "Queue implementation test program...";

    Queue<Person> person_queue;
    AddPerson("Phillip Haddad", 36, person_queue);
    AddPerson("Suzie Haddad", 35, person_queue);
    AddPerson("Isaac Haddad", 10, person_queue);
    AddPerson("Ava Haddad", 7, person_queue);
    person_queue.Print();

    Person next_person = person_queue.Dequeue();

    BLOG(eLogInfo) << "Dequeued [" << next_person << "] from the queue.";

    person_queue.Print();

    return 0;
}



