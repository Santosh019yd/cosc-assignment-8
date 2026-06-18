//
// Name: Santu Yadav
// Date: 06/18/2026
// Course: COSC 1437 C++ Programming Fundamentals II
// Desc: Chapter 8 Lab - Roster Report
//

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX_STUDENTS = 10;
const int NUM_TESTS = 4;

// Function Prototypes
void readRoster(char names[][31], int scores[][NUM_TESTS], int& count);

void calcAverages(const int scores[][NUM_TESTS],
                  double averages[],
                  char grades[],
                  int count);

void sortRoster(char names[][31],
                int scores[][NUM_TESTS],
                double averages[],
                char grades[],
                int count);

int searchRoster(const char names[][31],
                 int count,
                 const char target[]);

void printRoster(const char names[][31],
                 const int scores[][NUM_TESTS],
                 const double averages[],
                 const char grades[],
                 int count);

void printStats(const double averages[],
                int count);

int main()
{
    char names[MAX_STUDENTS][31] = {};
    int scores[MAX_STUDENTS][NUM_TESTS] = {};
    double averages[MAX_STUDENTS] = {};
    char grades[MAX_STUDENTS] = {};

    int count = 0;
    int choice;

    do
    {
        cout << "\n===== Roster Report Menu =====\n";
        cout << "1. Load roster (enter data)\n";
        cout << "2. Calculate averages and grades\n";
        cout << "3. Sort roster alphabetically\n";
        cout << "4. Search for a student\n";
        cout << "5. Print roster\n";
        cout << "6. Print class statistics\n";
        cout << "7. Quit\n";
        cout << "Enter choice: ";

        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice)
        {
            case 1:
                readRoster(names, scores, count);
                break;

            case 2:
                calcAverages(scores, averages, grades, count);
                cout << "Averages and grades calculated.\n";
                break;

            case 3:
                sortRoster(names, scores, averages, grades, count);
                cout << "Roster sorted alphabetically.\n";
                break;

            case 4:
            {
                char target[31];

                cout << "Enter student name to search: ";
                cin.getline(target, 31);

                int index = searchRoster(names, count, target);

                if (index == -1)
                    cout << "Student not found.\n";
                else
                    cout << "Student found at index "
                         << index << endl;

                break;
            }

            case 5:
                printRoster(names,
                            scores,
                            averages,
                            grades,
                            count);
                break;

            case 6:
                printStats(averages, count);
                break;

            case 7:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}

void readRoster(char names[][31],
                int scores[][NUM_TESTS],
                int& count)
{
    cout << "Enter number of students (1-10): ";
    cin >> count;
    cin.ignore(1000, '\n');

    if (count < 1)
        count = 1;

    if (count > MAX_STUDENTS)
        count = MAX_STUDENTS;

    for (int i = 0; i < count; i++)
    {
        cout << "\nEnter student name: ";
        cin.getline(names[i], 31);

        for (int j = 0; j < NUM_TESTS; j++)
        {
            cout << "Enter test score "
                 << (j + 1)
                 << ": ";

            cin >> scores[i][j];
        }

        cin.ignore(1000, '\n');
    }
}

void calcAverages(const int scores[][NUM_TESTS],
                  double averages[],
                  char grades[],
                  int count)
{
    for (int i = 0; i < count; i++)
    {
        int total = 0;

        for (int j = 0; j < NUM_TESTS; j++)
        {
            total += scores[i][j];
        }

        averages[i] = total / 4.0;

        if (averages[i] >= 90)
            grades[i] = 'A';
        else if (averages[i] >= 80)
            grades[i] = 'B';
        else if (averages[i] >= 70)
            grades[i] = 'C';
        else if (averages[i] >= 60)
            grades[i] = 'D';
        else
            grades[i] = 'F';
    }
}

void sortRoster(char names[][31],
                int scores[][NUM_TESTS],
                double averages[],
                char grades[],
                int count)
{
    for (int start = 0; start < count - 1; start++)
    {
        int minIndex = start;

        for (int i = start + 1; i < count; i++)
        {
            if (strcmp(names[i], names[minIndex]) < 0)
            {
                minIndex = i;
            }
        }

        if (minIndex != start)
        {
            char tempName[31];

            strcpy(tempName, names[start]);
            strcpy(names[start], names[minIndex]);
            strcpy(names[minIndex], tempName);

            for (int j = 0; j < NUM_TESTS; j++)
            {
                int tempScore = scores[start][j];
                scores[start][j] = scores[minIndex][j];
                scores[minIndex][j] = tempScore;
            }

            double tempAverage = averages[start];
            averages[start] = averages[minIndex];
            averages[minIndex] = tempAverage;

            char tempGrade = grades[start];
            grades[start] = grades[minIndex];
            grades[minIndex] = tempGrade;
        }
    }
}

int searchRoster(const char names[][31],
                 int count,
                 const char target[])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(names[i], target) == 0)
        {
            return i;
        }
    }

    return -1;
}

void printRoster(const char names[][31],
                 const int scores[][NUM_TESTS],
                 const double averages[],
                 const char grades[],
                 int count)
{
    if (count == 0)
    {
        cout << "No roster data available.\n";
        return;
    }

    cout << "\n";

    cout << left
         << setw(25) << "Name"
         << setw(8) << "T1"
         << setw(8) << "T2"
         << setw(8) << "T3"
         << setw(8) << "T4"
         << setw(12) << "Average"
         << setw(8) << "Grade"
         << endl;

    cout << "-----------------------------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        cout << left << setw(25) << names[i];

        for (int j = 0; j < NUM_TESTS; j++)
        {
            cout << setw(8) << scores[i][j];
        }

        cout << fixed
             << setprecision(2)
             << setw(12) << averages[i]
             << setw(8) << grades[i]
             << endl;
    }
}

void printStats(const double averages[],
                int count)
{
    if (count == 0)
    {
        cout << "No data available.\n";
        return;
    }

    double local[MAX_STUDENTS] = {};

    for (int i = 0; i < count; i++)
    {
        local[i] = averages[i];
    }

    double high = local[0];
    double low = local[0];
    double total = 0.0;

    for (auto value : local)
    {
        if (value == 0)
            continue;

        if (value > high)
            high = value;

        if (value < low)
            low = value;

        total += value;
    }

    cout << fixed << setprecision(2);

    cout << "\nClass High Average: "
         << high << endl;

    cout << "Class Low Average: "
         << low << endl;

    cout << "Class Average: "
         << total / count << endl;
}