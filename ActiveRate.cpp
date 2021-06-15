#include "ActiveRate.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void ActiveRate::showData() {
    cout << "id: " << id;
    cout << "Дата події: " << DateOfEvent;
    cout << "Cума ставки: " << RatePrice;
    cout << "Вид події: " << EventType;
    cout << "Назва команди/учасника змагань: " << teamOrParticipant;
}

void ActiveRate::create()
{
    cin.ignore(10, '\n');
    cout << "Дата події "; cin >> DateOfEvent;
    cout << "Cума ставки "; cin >> RatePrice;
    cout << "Вид події "; cin >> EventType;
    cout << "Назва команди/учасника змагань "; cin >> teamOrParticipant;
    id = setId();
}

int ActiveRate::valiidation()
{
    int input = -1;
    bool valid = false;
    do
    {
        cin >> input;
        if (cin.good())
        {
            valid = true;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Помилка вводу. Введіть ще раз" << endl;
        }
    } while (!valid);
    return input;
}

int ActiveRate::count()
{
    ifstream ifile;
    ifile.open("ActiveRates.dat ", ios::binary);
    ifile.seekg(0, ios::end);
    int v= (int)ifile.tellg() / sizeof(ActiveRate);
    return v;
    ifile.close();
}

int ActiveRate::setId()
{
    int tempId;
    string str;
    fstream idfile;
    idfile.open("activeRateId.txt", fstream::out | fstream::in);
    while (!idfile.eof())
    {
        getline(idfile, str);
        tempId = atoi(str.c_str());
    }
    ++tempId;
    idfile.close();
    idfile.open("activeRateId.txt", fstream::out | fstream::in);
    idfile << tempId;
    idfile.close();
    return tempId;
}
void ActiveRate::write()
{
    ofstream ofile;
    ofile.open("ActiveRates.dat", ios::app | ios::binary | ios::out | ios::in);
    ofile.write((char*)this, sizeof(*this));
    ofile.close();
}

void ActiveRate::read(int p)
{
    ifstream ifile;
    ifile.open("ActiveRates.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    ifile.seekg(p * sizeof(ActiveRate));
    ifile.read((char*)this, sizeof(*this));
    ifile.close();
}


int ActiveRate::search(int variant)
{
    if (variant == 0)
        return 0;
    ActiveRate activeRate;
    ifstream ifile;
    char str[40];
    ifile.open("ActiveRates.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    cout << "Введіть дані для пошуку: ";
    cin >> str;
    for (int i = 0; i < count(); i++)
    {
        ifile.seekg(i * sizeof(ActiveRate));
        ifile.read(reinterpret_cast<char*>(&activeRate), sizeof(ActiveRate));

        switch (variant)
        {
        case 1:
            if (0 == strcmp(str, activeRate.DateOfEvent))
            {
                activeRate.showData();
                cout << endl;
            }
            break;

        case 2:
            if (atoi(str) == activeRate.RatePrice)
            {
                activeRate.showData();
                cout << endl;
            }
            break;
        case 3:
            if (0 == strcmp(str, activeRate.EventType))
            {
                activeRate.showData();
                cout << endl;
            }
            break;
        case 4:
            if (0 == strcmp(str, activeRate.teamOrParticipant))
            {
                activeRate.showData();
                cout << endl;
            }
            break;
        default:
            break;
        }
    }
    ifile.close();
}

void ActiveRate::edit()
{
    ActiveRate activeRate;
    char str[40];
    cout << "Введіть id для редагування: ";
    cin >> str;
    ifstream file;
    file.open("ActiveRates.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temporary.dat", ios::app | ios::binary | ios::out | ios::in);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(&activeRate), sizeof(ActiveRate));
    while (!file.eof())
    {

        if (atoi(str) != activeRate.id)
        {
            temp.write(reinterpret_cast<char*>(&activeRate), sizeof(ActiveRate));
        }

        else
        {
            activeRate.create();
            temp.write(reinterpret_cast<char*>(&activeRate), sizeof(ActiveRate));
        }
        file.read(reinterpret_cast<char*>(&activeRate), sizeof(ActiveRate));
    }
    temp.close();
    file.close();
    if (remove("ActiveRates.dat") != 0)
    {
        cout << "file do not remove";
    }
    if (rename("temporary.dat", "ActiveRates.dat") != 0)
    {
        cout << "file do not rename";
    }
}

void ActiveRate::deleted()
{
    ActiveRate activeRate;
    int str;
    cout << "Введіть id для видалення: ";
    cin >> str;
    ifstream file;
    file.open("ActiveRates.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temporary.dat", ios::app | ios::binary | ios::out | ios::in);
    file.read(reinterpret_cast<char*>(&activeRate), sizeof(ActiveRate));
    while (!file.eof())
    {

        if (str != activeRate.id)
        {
            temp.write(reinterpret_cast<char*>(&activeRate), sizeof(ActiveRate));
        }

        else
        {
            cout << "\nЗапис видалено\n";
        }
        file.read(reinterpret_cast<char*>(&activeRate), sizeof(ActiveRate));
    }
    temp.close();
    file.close();
    if (remove("ActiveRates.dat") != 0)
    {
        cout << "file do not remove";
    }
    if (rename("temporary.dat", "ActiveRates.dat") != 0)
    {
        cout << "file do not rename";
    }
}