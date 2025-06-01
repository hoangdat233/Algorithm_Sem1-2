#include <iostream>
#include <vector>
using namespace std;

class StudentGroup
{
    struct Student
    {
        int isu;
        int points;
    };

    vector<Student> data;
    int totalPoints = 0;
    int maxPoints = 0;

public:
    void insert(int isu, int points)
    {
        data.push_back({isu, points});
        totalPoints += points;
        if (points > maxPoints)
        {
            maxPoints = points;
        }
    }

    void remove(int isu)
    {
        for (int i = 0; i < (int)data.size(); ++i)
        {
            if (data[i].isu == isu)
            {
                totalPoints -= data[i].points;
                if (data[i].points == maxPoints)
                {
                    maxPoints = 0;
                    for (int j = 0; j < (int)data.size(); ++j)
                    {
                        if (j != i)
                        {
                            if (data[j].points > maxPoints)
                            {
                                maxPoints = data[j].points;
                            }
                        }
                    }
                }
                data[i] = data.back();
                data.pop_back();
                break;
            }
        }
    }

    int getAverage() const
    {
        return data.empty() ? 0 : totalPoints / (int)data.size();
    }

    int getMax() const
    {
        return data.empty() ? 0 : maxPoints;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, Q;
    cin >> M >> Q;

    vector<StudentGroup> allGroups(M + 1);

    while (Q--)
    {
        char type;
        cin >> type;

        if (type == '+')
        {
            int group, isu, points;
            cin >> group >> isu >> points;
            allGroups[group].insert(isu, points);
        }
        else if (type == '-')
        {
            int group, isu;
            cin >> group >> isu;
            allGroups[group].remove(isu);
        }
        else if (type == 'a')
        {
            int group;
            cin >> group;
            cout << allGroups[group].getAverage() << '\n';
        }
        else if (type == 'm')
        {
            int group;
            cin >> group;
            cout << allGroups[group].getMax() << '\n';
        }
    }

    return 0;
}
