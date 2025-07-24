#include <iostream>
#include <vector>

using namespace std;

struct Row {
    string label;
    int value;
};

struct Table2{

string category;
int value;

};

int main() {

    int values[21] = {41, 18, 21, 63, 2, 53, 5, 57, 60, 93, 28, 3,90, 39, 80, 88, 49, 60, 26, 28};

    vector<Row> table;

    cout<<"Table 1\n";

    cout<<"Index#\tValue"<<endl;

    for (int i = 0; i < 20; ++i) {
        table.push_back({ "A" + to_string(i+1), values[i] });
    }

    for (const auto& row : table) {
        cout << row.label << "\t" << row.value << endl;
    }


        vector<Table2> table2 = {

        {"Alpha", 30},
        {"Beta", 16},
        {"Charlie", 270}

        };

    cout<<"\n\nTable 2\n";

    cout<<"Category\tValue"<<endl;

     for (const auto& row : table2) {
        cout << row.category << "\t\t" << row.value << endl;
    }

    return 0;
}
