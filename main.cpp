#include <iostream>
#include "arr.cpp"
#include "queue.cpp"
#include "disjoint_kraskal.cpp"
#include <locale>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Graph
{
    dynamic_arr<string> vertex_arr;
    dynamic_arr<int> visited_arr;

public:
    dynamic_arr<dynamic_arr<int>> aMatrix_arr;
    void add_Vertex_aMatrix(const string& str)
    {
        fstream reading(str);
        string s;
        if (!reading.is_open())
        {
            cout << "Error, file not open" << endl;
            return;
        }

        getline(reading, s);
        stringstream ss(s);
        string vertex;
        while (ss >> vertex) {
            vertex_arr.push_back(vertex);
        }

        while (getline(reading, s))
        {
            dynamic_arr<int> row;
            stringstream row_ss(s);
            int val;
            while (row_ss >> val)
            {
                row.push_back(val);
            }
            aMatrix_arr.push_back(row);
        }
        cout << "ГРАФ СЧИТАН ИЗ ФАЙЛА!" << endl;
        cout << "     ";
        for (int i = 0; i < vertex_arr.get_size(); i++) {
            cout << vertex_arr.get_pos(i) << "   ";
        }
        cout << endl;

        for (int i = 0; i < aMatrix_arr.get_size(); i++) {
            cout << vertex_arr.get_pos(i) << " ";
            for (int j = 0; j < aMatrix_arr.get_pos(i).get_size(); j++) {
                cout << "   " << aMatrix_arr.get_pos(i)[j];
            }
            cout << endl;
        }
    }

    void dfs(dynamic_arr<dynamic_arr<int>>& aMatrix_arr, int v, dynamic_arr<int>& visited_arr) 
    {
        visited_arr[v] = 1;
        cout << vertex_arr.get_pos(v) << ": ";
        for (int i = 0; i < aMatrix_arr.get_size(); i++) 
        {
            if (aMatrix_arr[v][i]) 
            {
                cout << vertex_arr.get_pos(i) << "(" << aMatrix_arr[v][i] << ") ";
            }
        }
        cout << endl;

        for (int i = 0; i < aMatrix_arr.get_size(); i++) 
        {
            if (aMatrix_arr[v][i] && !visited_arr[i]) 
            {
                dfs(aMatrix_arr, i, visited_arr);
            }
        }
    }

    void dfs_GO(dynamic_arr<dynamic_arr<int>>& aMatrix_arr) 
    {
        dynamic_arr<int> visited_arr(aMatrix_arr.get_size(), 0);
        cout << "DFS: " << endl;
        for (int i = 0; i < aMatrix_arr.get_size(); i++) 
        {
            if (!visited_arr[i])
            { 
                dfs(aMatrix_arr, i, visited_arr);
            }
        }
        cout << endl;
    }


    void bfs(dynamic_arr<dynamic_arr<int>>& aMatrix_arr, int start) 
    {
        dynamic_arr<int> dist(aMatrix_arr.get_size(), -1);
        Queue<int> q;
        dist[start] = 0;
        q.push(start);

        cout << "BFS: " << endl;

        while (!q.is_empty()) 
        {
            int v = q.front();
            q.pop();
            cout << vertex_arr.get_pos(v) << ": ";
            for (int i = 0; i < aMatrix_arr.get_size(); i++) 
            {
                if (aMatrix_arr[v][i]) 
                {
                    cout << vertex_arr.get_pos(i) << "(" << aMatrix_arr[v][i] << ") ";
                    if (dist[i] == -1) 
                    {
                        dist[i] = dist[v] + 1;
                        q.push(i);
                    }
                }
            }
            cout << endl;
        }
    }
};

int minrun(int n)
{
    int flag = 0;
    while (n >= 64)
    {
        flag |= n & 1;
        n >>= 1;
    }
    return n + flag;

}
int min_digit(int a, int b)
{
    int res;
    if (a > b)
    {
        res = b;
    }
    else
    {
        res = a;
    }

    return res;
}
void gallop(dynamic_arr<int>& arr, dynamic_arr<int>& left_arr, dynamic_arr<int>& right_arr, int& i, int& j, int& k, bool check)
{
    if (check)
    {
        int left = i;
        int right = left_arr.get_size();

        while (left < right)
        {
            int mid = (left + right) / 2;
            if (left_arr[mid] < right_arr[j])
            {
                for (int m = left; m <= mid; m++)
                {
                    arr[k++] = left_arr[m];
                }
                left = mid;
                i = left;
            }
            else
            {
                right = mid;
            }
        }

    }
    else
    {
        int left = j;
        int right = right_arr.get_size();

        while (left < right)
        {
            int mid = (left + right) / 2;
            if (right_arr[mid] < left_arr[i])
            {
                for (int m = left; m <= mid; m++)
                {
                    arr[k++] = right_arr[m];
                }
                left = mid;
                j = left;
            }
            else
            {
                right = mid;
            }
        }
    }
}
void insert_sort(dynamic_arr<int>& run, int left, int right)
{
    {
        for (int i = left + 1; i < right; i++) {
            int temp = run[i];
            int j = i - 1;
            while (j >= left && run[j] > temp) {
                run[j + 1] = run[j];
                j--;
            }
            run[j + 1] = temp;
        }
    }
}
void merge(dynamic_arr<int>& arr, int left, int mid, int right)
{
    int cnt_l = 0;
    int cnt_r = 0;

    int left_arr_length = mid - left;
    int rigth_arr_length = right - mid;

    dynamic_arr<int> left_arr(left_arr_length);
    dynamic_arr<int> right_arr(rigth_arr_length);
    for (int i = 0; i < left_arr_length; i++)
        left_arr[i] = arr[left + i];
    for (int j = 0; j < rigth_arr_length; j++)
        right_arr[j] = arr[mid + j];

    int i = 0, j = 0, k = left;

    while (i < left_arr_length && j < rigth_arr_length) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k++] = left_arr[i++];
            cnt_l++;
            cnt_r = 0;
        }
        else {
            arr[k++] = right_arr[j++];
            cnt_r++;
            cnt_l = 0;
        }
        if (cnt_l == 5)
        {
            gallop(arr, left_arr, right_arr, i, j, k, true);
            cnt_l = 0;
        }
        if (cnt_r == 5)
        {
            gallop(arr, left_arr, right_arr, i, j, k, false);
            cnt_r = 0;
        }
    }

    while (i < left_arr_length) arr[k++] = left_arr[i++];
    while (j < rigth_arr_length) arr[k++] = right_arr[j++];
}
void timsort(dynamic_arr<int>& arr, int mn)
{
    for (int i = 0, counter = 1; i < arr.get_size(); i += mn, counter++)
    {
        if (i + mn < arr.get_size())
            insert_sort(arr, i, i + mn);
        else
            insert_sort(arr, i, arr.get_size());
    }
    for (int size = mn; size < arr.get_size(); size = 2 * size)
    {
        for (int left = 0; left < arr.get_size(); left += 2 * size)
        {
            int mid = left + size;
            int right;
            if ((left + 2 * size) < (arr.get_size()))
                right = (left + 2 * size);
            else
                right = arr.get_size();
            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}



void menu() {
    char choice;
    bool running = true;
    Graph graph;
    string s = "algokusr.txt";

    while (running) {
        std::cout << "\n1 - Считать граф из файла\n";
        std::cout << "2 - Обойти граф\n";
        std::cout << "3 - Построение СНМ(алгоритм Краскала)\n";
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
        case '1': {
            graph.add_Vertex_aMatrix(s);
            break;
        }
        case '2': {
            graph.dfs_GO(graph.aMatrix_arr);
            graph.bfs(graph.aMatrix_arr, 0);
            break;
        }
        case '3': {
            
            break;
        }
        default:
            std::cout << "Некорректный выбор!\n";
            break;
        }
    }
}


int main()
{
    setlocale(LC_ALL, "ru");
    menu();
    return 0;
}