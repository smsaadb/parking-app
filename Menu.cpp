#include <iostream>
#include <cstring>
#include <iomanip>
#include "Menu.h"

using namespace std;

namespace sdds
{
    MenuItem::MenuItem(const char *n)
    {
        if (n == nullptr || n[0] == '\0')
        {
            name = nullptr;
        }
        else
        {
            name = new char[strlen(n) + 1];
            strcpy(name, n);
        }
    }

    void MenuItem::display() const
    {
        if (name != nullptr)
        {
            cout << name << endl;
        }
    }

    MenuItem::~MenuItem()
    {
        if (name != nullptr)
        {
            delete[] name;
            name = nullptr;
        }
    }

    Menu::Menu()
    {
        setEmptyMenu();
    }
    Menu::Menu(const char *t, int ilvl)
    {
        setEmptyMenu();
        setTitle(t);
        indLevel = ilvl;
    }
    Menu::Menu(const Menu &m)
    {
        setEmptyMenu();

        if (m)
        {
            if (m.numOfItems != 0)
            {
                numOfItems = m.numOfItems;
                for (int i = 0; i < numOfItems; i++)
                {
                    items[i] = new MenuItem(m.items[i]->name);
                }
            }
            indLevel = m.indLevel;
            setTitle(m.title);
        }
    }
    Menu &Menu::operator=(const Menu &m)
    {
        if (title != nullptr)
        {
            deleteTitle();
        }

        if (numOfItems != 0)
        {
            deleteItems();
        }

        setEmptyMenu();

        if (m)
        {
            setTitle(m.title);
            if (m.numOfItems != 0)
            {
                numOfItems = m.numOfItems;
                for (int i = 0; i < numOfItems; i++)
                {
                    items[i] = new MenuItem(m.items[i]->name);
                }
            }
            indLevel = m.indLevel;
        }

        return *this;
    }
    Menu &Menu::operator=(const char *t)
    {

        if (title != nullptr)
        {
            deleteTitle();
        }
        if (numOfItems != 0)
        {
            deleteItems();
        }
        if (t != nullptr)
        {
            setTitle(t);
        }

        return *this;
    }
    void Menu::deleteTitle()
    {
        delete[] title;
        title = nullptr;
    }
    void Menu::deleteItems()
    {
        if (numOfItems != 0)
        {
            for (int i = 0; i < numOfItems; i++)
            {
                if (items[i]->name != nullptr)
                {
                    delete items[i];
                    items[i] = nullptr;
                }
            }
            numOfItems = 0;
        }
    }
    void Menu::addItem(int &pos, const char *iName)
    {
        if (iName != nullptr && iName[0] != '\0')
        {
            items[pos] = new MenuItem(iName);
            pos++;
        }
        else
        {
            deleteTitle();
            deleteItems();
        }
    }
    void Menu::setTitle(const char *t)
    {
        if (t != nullptr && t[0] != '\0')
        {
            title = new char[strlen(t) + 1];
            strcpy(title, t);
        }
    }
    void Menu::setEmptyMenu()
    {
        indLevel = 0;
        numOfItems = 0;
        title = nullptr;
        for (int i = 0; i < MAX_NO_OF_ITEMS; i++)
        {
            items[i] = nullptr;
        }
    }
    Menu::operator bool() const
    {
        if (title != nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    Menu::operator int() const
    {
        return run();
    }
    bool Menu::isEmpty() const
    {
        if (!*this)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void Menu::display() const
    {
        if (!*this)
        {
            cout << "Invalid Menu!" << endl;
            return;
        }

        printIndentation(indLevel);
        cout << title << endl;
        if (numOfItems == 0)
        {
            cout << "No Items to display!" << endl;
        }
        else
        {
            for (int i = 0; i < numOfItems; i++)
            {
                printIndentation(indLevel);
                cout << i + 1 << "- ";
                items[i]->display();
            }
            printIndentation(indLevel);
            cout << "> ";
        }
    }
    int Menu::run() const
    {
        char opt[7];
        bool checkDigit = false;
        int option;

        display();

        if (numOfItems == 0)
        {
            return 0;
        }

        while (true)
        {
            cin >> opt;
            clearBuffer();

            for (int i = 0; i < int(strlen(opt)); i++)
            {
                if (isdigit(opt[i]))
                {
                    checkDigit = true;
                }
                else
                {
                    checkDigit = false;
                    break;
                }
            }

            if (!checkDigit)
            {
                cout << "Invalid Integer, try again: ";
            }
            else
            {
                option = atoi(opt);
                if (option < 1 || option > numOfItems)
                {
                    cout << "Invalid selection, try again: ";
                }
                else
                {
                    return option;
                }
            }
        }
    }
    void Menu::add(const char *t)
    {
        if (!*this)
        {
            return;
        }

        addItem(numOfItems, t);
    }
    Menu &Menu::operator<<(const char *t)
    {
        add(t);
        return *this;
    }
    Menu::~Menu()
    {

        deleteItems();
        deleteTitle();
    }
} // namespace sdds
