#include "DoneRate.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void DoneRate::showData() {
    cout << "id: " << id;
    cout << "Дата події: " << DateOfEvent;
    cout << "Cума ставки: " << RatePrice;
    cout << "Вид події: " << EventType;
    cout << "Назва команди/учасника змагань: " << teamOrParticipant;
}

void DoneRate::create()
{
    char number[12];
    cin.ignore(10, '\n');
    cout << "Дата події"; cin >> DateOfEvent;
    cout << "Cума ставки"; cin >> RatePrice;
    cout << "Вид події"; cin >> EventType;
    cout << "Назва команди/учасника змагань"; cin >> teamOrParticipant;
    id = setId();
}

int DoneRate::valiidation()
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

int DoneRate::count()
{
    ifstream ifile;
    ifile.open("DoneRates.dat ", ios::binary);
    ifile.seekg(0, ios::end);
    int v = (int)ifile.tellg() / sizeof(DoneRate);
    return v;
    ifile.close();
}

int DoneRate::setId()
{
    int tempId;
    string str;
    fstream idfile;
    idfile.open("doneRateId.txt", fstream::out | fstream::in);
    while (!idfile.eof())
    {
        getline(idfile, str);
        tempId = atoi(str.c_str());
    }
    ++tempId;
    idfile.close();
    idfile.open("doneRateId.txt", fstream::out | fstream::in);
    idfile << tempId;
    idfile.close();
    return tempId;
}
void DoneRate::write()
{
    ofstream ofile;
    ofile.open("DoneRates.dat", ios::app | ios::binary | ios::out | ios::in);
    ofile.write((char*)this, sizeof(*this));
    ofile.close();
}

void DoneRate::read(int p)
{
    ifstream ifile;
    ifile.open("DoneRates.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    ifile.seekg(p * sizeof(DoneRate));
    ifile.read((char*)this, sizeof(*this));
    ifile.close();
}


int DoneRate::search(int variant)
{
    if (variant == 0)
        return 0;
    DoneRate doneRate;
    ifstream ifile;
    char str[40];
    ifile.open("DoneRates.dat", ios::binary | ios::out | ios::in);
    ifile.seekg(0);
    cout << "Введіть дані для пошуку: ";
    cin >> str;
    for (int i = 0; i < count(); i++)
    {
        ifile.seekg(i * sizeof(DoneRate));
        ifile.read(reinterpret_cast<char*>(&doneRate), sizeof(DoneRate));

        switch (variant)
        {
        case 1:
            if (0 == strcmp(str, doneRate.DateOfEvent))
            {
                doneRate.showData();
                cout << endl;
            }
            break;

        case 2:
            if (atoi(str) == doneRate.RatePrice)
            {
                doneRate.showData();
                cout << endl;
            }
            break;
        case 3:
            if (0 == strcmp(str, doneRate.EventType))
            {
                doneRate.showData();
                cout << endl;
            }
            break;
        case 4:
            if (0 == strcmp(str, doneRate.teamOrParticipant))
            {
                doneRate.showData();
                cout << endl;
            }
            break;
        default:
            break;
        }
    }
    ifile.close();
}

void DoneRate::edit()
{
    DoneRate doneRate;
    char str[40];
    cout << "Введіть id для редагування: ";
    cin >> str;
    ifstream file;
    file.open("DoneRates.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temporary.dat", ios::app | ios::binary | ios::out | ios::in);
    file.seekg(0);
    file.read(reinterpret_cast<char*>(&doneRate), sizeof(DoneRate));
    while (!file.eof())
    {

        if (atoi(str) != doneRate.id)
        {
            temp.write(reinterpret_cast<char*>(&doneRate), sizeof(DoneRate));
        }

        else
        {
            doneRate.create();
            temp.write(reinterpret_cast<char*>(&doneRate), sizeof(DoneRate));
        }
        file.read(reinterpret_cast<char*>(&doneRate), sizeof(DoneRate));
    }
    temp.close();
    file.close();
    if (remove("DoneRates.dat") != 0)
    {
        cout << "file do not remove";
    }
    if (rename("temporary.dat", "DoneRates.dat") != 0)
    {
        cout << "file do not rename";
    }
}

void DoneRate::deleted()
{
    DoneRate doneRate;
    int str;
    cout << "Введіть id для видалення: ";
    cin >> str;
    ifstream file;
    file.open("DoneRates.dat", ios::binary | ios::out | ios::in);
    ofstream temp;
    temp.open("temporary.dat", ios::app | ios::binary | ios::out | ios::in);
    file.read(reinterpret_cast<char*>(&doneRate), sizeof(DoneRate));
    while (!file.eof())
    {

        if (str != doneRate.id)
        {
            temp.write(reinterpret_cast<char*>(&doneRate), sizeof(DoneRate));
        }

        else
        {
            cout << "\nЗапис видалено\n";
        }
        file.read(reinterpret_cast<char*>(&doneRate), sizeof(DoneRate));
    }
    temp.close();
    file.close();
    if (remove("DoneRates.dat") != 0)
    {
        cout << "file do not remove";
    }
    if (rename("temporary.dat", "DoneRates.dat") != 0)
    {
        cout << "file do not rename";
    }
}