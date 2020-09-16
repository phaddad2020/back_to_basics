/********************************************************************
 * Back to Basics                                                   *
 *                                                                  *
 * Author: Phillip Haddad                                           *
 *                                                                  *
 * Description: Binary Tree implementation                          *
 *                                                                  *
 *******************************************************************/

#include <stdint.h>
#include <iostream>
#include <string>

#include "logger.h"
#include "binary_tree.h"

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

    bool operator<(const Person &rhs) const
    {
        return age < rhs.age;
    }

    bool operator>(const Person &rhs) const
    {
        return age > rhs.age;
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

int main(int argc, char* argv[])
{
    BLOG(eLogInfo) << "Binary Tree implementation test program...";

    BinaryTree<Person> b_tree;
    Person phillip("Phillip Haddad", 36);
    b_tree.Insert(Person("Trevor McNigel", 25));
    b_tree.Insert(Person("Phillip Haddad", 36));
    b_tree.Insert(Person("Suzie Haddad", 35));
    b_tree.Insert(Person("Isaac Haddad", 10));
    b_tree.Insert(Person("Ava Haddad", 7));
    b_tree.Insert(Person("Bernadette O'Connor", 40));
    b_tree.Insert(Person("Michael O'Connor", 46));
    b_tree.Insert(Person("Mary O'Connor", 16));
    b_tree.Insert(Person("Sean O'Connor", 13));
    b_tree.Insert(Person("Grace O'Connor", 6));
    b_tree.Insert(Person("Kamelia Haddad", 60));
    b_tree.Insert(Person("Nabil Haddad", 69));

    b_tree.InOrderTraversal();

    BLOG(eLogInfo) << "Max Value: " << b_tree.GetMaxData();
    BLOG(eLogInfo) << "Min Value: " << b_tree.GetMinData();

    Person *temp_person = b_tree.Search(phillip);
    if (temp_person)
    {
        BLOG(eLogInfo) << "Person found: " << *temp_person;
    }

    b_tree.Remove(phillip);

    b_tree.InOrderTraversal();
    b_tree.PreOrderTraversal();
    b_tree.PostOrderTraversal();

    return 0;
}


