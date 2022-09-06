#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

struct colum_table
{
    int column;
    string data;
};

struct employee
{
    string name = "";
    string email = "";
    string department = "";
    string positions = "";
    string project = "";
    string task = "";
    string year = "";
    string month = "";
    string day = "";
    int logged_hours{};
};

class Work_with_File
{
private: 
    string path;
    string path_file_for_write;
    string Text;
    vector<employee> list_work;
    vector<colum_table> table;

    vector<string> split(string symbol, string Text)
    {
        vector<string> arr;
        regex re_line(symbol);
        sregex_token_iterator p(Text.begin(), Text.end(), re_line, -1);
        sregex_token_iterator end;
        while (p != end)
            arr.push_back(*p++);
        return arr;
    }
    bool validation(vector<string> arr)
    {
        if (arr.size() < table.size())
        {
            return true;
        }

        for (auto s : arr)
        {
            if (s.empty())
            {
                return true;
            }
        }
        return false;

    }
    void Work_with_line(string Text)
    {
        /// <summary>
        /// Work only for "Name;email;department;position;project;task;date;logged hours" according to the condition task
        /// </summary>
        ///
        vector<string> arr, arr_with_data;
        bool Flag = false;

        arr = split(";", Text);
        arr_with_data = split("-", arr[6]);

        if (validation(arr) != true)
        {
            employee em{ arr[0], arr[1], arr[2], arr[3], arr[4], arr[5],
             arr_with_data[0], arr_with_data[1], arr_with_data[2], stoi(arr[7]) };

            for (int i = 0; i < list_work.size(); i++)
            {
                if (list_work[i].name == em.name && list_work[i].email == em.email && list_work[i].year == em.year && list_work[i].month == em.month)
                {
                    list_work[i].logged_hours += em.logged_hours;
                    Flag = true;
                }
            }
            if (Flag == false)
            {
                list_work.push_back(em);
            }
        }
    }
    string number_to_month(int number)
    {
        switch (number)
        {
            case 1:
                return "January";
                break;
            case 2:
                return "February";
                break;
            case 3:
                return "March";
                break;
            case 4:
                return "April";
                break;
            case 5:
                return "May";
                break;
            case 6:
                return "June";
                break;
            case 7:
                return "July";
                break;
            case 8:
                return "August";
                break;
            case 9:
                return "September";
                break;
            case 10:
                return "October";
                break;
            case 11:
                return "November";
                break;
            case 12:
                return "December";
                break;

        }
    }

public:

    Work_with_File(string path, string path_file_for_write)
    {
        this->path = path;
        this->path_file_for_write = path_file_for_write;
    }

    void MAIN_LOOP()
    {
        ifstream FileRead(path);
        
        bool Flag_first_line = false;
        if (FileRead.is_open())
        {
            while (getline(FileRead, Text))
            {
                if (Flag_first_line == false)
                {
                    Flag_first_line = true;

                    vector<string> column = split(";", Text);
                    for (int i = 0; i < column.size(); i++)
                    {
                        string column_name = "";
                        for (auto s : column[i])
                        {
                            column_name += tolower((char)s);
                        }
                        table.push_back(colum_table{ i, column_name });
                    }
                }
                else
                {
                    Work_with_line(Text);
                }
            }
            FileRead.close();
            ofstream MyFile(path_file_for_write);
            if (MyFile.is_open())
            {
                MyFile << "Name;Month;Total hours\n";
                for (auto s : list_work)
                {

                    MyFile << s.name + ";" + number_to_month(stoi(s.month)) + ";" + to_string(s.logged_hours) + "\n";
                }
            }
            else
            {
                cout << "Error don't found Path output file";
            }
            MyFile.close();
        }
        else
        {
            cout << "Error don't found Path input file";
        }
    }
    void draw_list()
    {
        for (auto s : list_work)
        {
            cout << s.name << endl << s.email << s.department << endl << s.positions << endl << s.project << endl << s.task << endl << s.year << endl;
            cout << s.month << endl << s.day << endl << s.logged_hours << endl;
        }
    } 
};

int main()
{
    string path, path_file_for_write;
    cout << "Please Write path imput file" << endl;
    cin >> path;
    cout << "Please Write path output file" << endl;
    cin >> path_file_for_write;
    //
   
    Work_with_File Work(path, path_file_for_write);
    Work.MAIN_LOOP();
    
}
