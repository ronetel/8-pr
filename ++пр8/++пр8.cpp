
#include <iostream>
#include <vector>
#include <thread>
using namespace std;

class MargeSort
{
public:
    void Sort( vector<int>& array) {
        if (array.size() <= 1) return;
        mergeSort(array, 0, array.size() - 1);
    }
private:
    void merge( vector<int>& array, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

         vector<int> L(n1);
         vector<int> R(n2);

        for (int i = 0; i < n1; ++i) {
            L[i] = array[left + i];
        }
        for (int j = 0; j < n2; ++j) {
            R[j] = array[mid + 1 + j];
        }

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                array[k] = L[i];
                ++i;
            }
            else {
                array[k] = R[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            array[k] = L[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            array[k] = R[j];
            ++j;
            ++k;
        }
    }

    void mergeSort( vector<int>& array, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

             thread t1(&MargeSort::mergeSort, this,  ref(array), left, mid);
             thread t2(&MargeSort::mergeSort, this,  ref(array), mid + 1, right);

            t1.join();
            t2.join();

            merge(array, left, mid, right);
        }
    }
};

int main()
{
    setlocale(LC_ALL, "RU");

    vector<int> start(10);
    vector<int> finish(10);
    MargeSort marg;

    cout << "Укажите массив из 10 чисел: ";
    for (int i = 0; i < 10; i++)
    {
        cin >> start[i];
    }
    thread thread1([&marg,&start]()
        {
           marg.Sort(start);
        }
    );
    thread1.join();

    cout << "Массив был отсортирован по возрастанию: ";
    for (const auto& i : start)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
