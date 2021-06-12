#ifndef MENU
#define MENU

#include "Utils.h"

using namespace std;

namespace sdds
{
    const int MAX_NO_OF_ITEMS = 10;

    class Menu;

    class MenuItem
    {
        friend class Menu;

    private:
        char *name;
        MenuItem(const char *n);
        void display() const;
        ~MenuItem();

        MenuItem(const MenuItem &) = delete;
        MenuItem &operator=(const MenuItem &) = delete;
    };

    class Menu
    {
    private:
        char *title;
        MenuItem *items[MAX_NO_OF_ITEMS];
        int numOfItems;
        int indLevel;

    public:
        Menu();
        Menu(const char *t, int ilvl = 0);
        Menu(const Menu &m);            //copy constructor
        Menu &operator=(const Menu &m); //copy assignment
        Menu &operator=(const char *t); //copy the title
        void deleteTitle();
        void deleteItems();
        void addItem(int &pos, const char *iName);
        void setTitle(const char *t);
        void setEmptyMenu();
        operator bool() const;
        operator int() const;
        bool isEmpty() const;
        void display() const;
        int run() const;
        void add(const char *t);         //add a new item to the array
        Menu &operator<<(const char *t); //add a new item to the array
        ~Menu();                         //destructor
    };

} // namespace sdds

#endif