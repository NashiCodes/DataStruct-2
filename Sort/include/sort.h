#ifndef SORT_H
#define SORT_H

#include <vector>
#include "../include/perf.h"
using namespace std;

namespace Sort
{

    // TODO: Implemente do algoritmos de ordenação basicos O(n^2)
    // Escolha uns dos métodos abaixo para implementar
    //   - BubbleSort
    //  - SelectionSort
    //  - InsertionSort
    template <typename T, class Compare>
    void BasicSort(std::vector<T> &v, Compare cmp)
    {
        auto *timer = new Perf::PerformanceTimer();
        auto *counter = new Perf::PerformanceCounter();
        timer->start();
        for (int j = 1; j < v.size(); j++)
        {
            T v2 = v[j]; // v2 será o Pivo
            int i = j - 1;
            while (i >= 0 && cmp(v2, v[i], counter)) // compara com os anteriores
            {
                v[i + 1] = v[i];
                i = i - 1;
                counter->increment_swaps();
            }
            v[i + 1] = v2; // Pivô é colocado na posição certa
            counter->increment_swaps();
        }
        timer->stop();
        cout << "Basic Sort:" << endl
             << "Tempo: " << timer->elapsed_time() << endl
             << "Comparacoes: " << counter->get_comparisons() << endl
             << "Trocas: " << counter->get_swaps() << endl
             << endl;
        delete timer, counter;
    }

    // TODO: Implemente algoritmo de ordenação MergeSort
    template <typename T, class Compare>
    void Merge(vector<T> &v, int l, int m, int r, Compare cmp, Perf::PerformanceTimer *timer, Perf::PerformanceCounter *counter)
    {
        int i = l;
        int j = m + 1;
        int k = 0;

        vector<T> aux(r - l + 1);

        while (i <= m && j <= r)
        {
            if (cmp(v[i], v[j], counter))
            {
                aux[k] = v[i];
                i++;
                counter->increment_swaps();
            }
            else
            {
                aux[k] = v[j];
                j++;
                counter->increment_swaps();
            }
            k++;
        }
        while (i <= m)
        {
            aux[k] = v[i];
            i++;
            k++;
            counter->increment_swaps();
        }
        while (j <= r)
        {
            aux[k] = v[j];
            j++;
            k++;
            counter->increment_swaps();
        }
        for (i = l, k = 0; i <= r; i++, k++)
        {
            v[i] = aux[k];
            counter->increment_swaps();
        }
    }

    template <typename T, class Compare>
    void auxMerge(std::vector<T> &v, int l, int r, Compare cmp, Perf::PerformanceTimer *timer, Perf::PerformanceCounter *counter)
    {
        if (l < r)
        {
            int m = l + (r - l) / 2;
            auxMerge(v, l, m, cmp, timer, counter);
            auxMerge(v, m + 1, r, cmp, timer, counter);
            Merge(v, l, m, r, cmp, timer, counter);
        }
    }

    template <typename T, class Compare>
    void MergeSort(std::vector<T> &v, Compare cmp)
    {
        auto *timer = new Perf::PerformanceTimer();
        auto *counter = new Perf::PerformanceCounter();
        timer->start();
        auxMerge(v, 0, (v.size() - 1), cmp, timer, counter);
        timer->stop();
        cout << "Merge Sort:" << endl
             << "Tempo: " << timer->elapsed_time() << endl
             << "Comparacoes: " << counter->get_comparisons() << endl
             << "Trocas: " << counter->get_swaps() << endl
             << endl;
        delete timer, counter;
    }

    // TODO: Implemente algoritmo de ordenação QuickSort
    template <typename T, class Compare>
    void QuickSortHelper(std::vector<T> &v, Compare cmp, int left, int right, Perf::PerformanceTimer *timer, Perf::PerformanceCounter *counter)
    {
        if (left < right)
        {
            int pivotIndex = left + (right - left) / 2;
            T pivotValue = v[pivotIndex];
            int i = left;
            int j = right;
            while (i <= j)
            {
                while (cmp(v[i], pivotValue, counter))
                {
                    i++;
                }
                while (cmp(pivotValue, v[j], counter))
                {
                    j--;
                }
                if (i <= j)
                {
                    std::swap(v[i], v[j]);
                    i++;
                    j--;
                    counter->increment_swaps();
                }
            }
            QuickSortHelper(v, cmp, left, j, timer, counter);
            QuickSortHelper(v, cmp, i, right, timer, counter);
        }
    }
    template <typename T, class Compare>
    void QuickSort(std::vector<T> &v, Compare cmp)
    {
        auto *timer = new Perf::PerformanceTimer();
        auto *counter = new Perf::PerformanceCounter();
        timer->start();
        QuickSortHelper(v, cmp, 0, v.size() - 1, timer, counter);
        timer->stop();
        cout << "Quick Sort:" << endl
             << "Tempo: " << timer->elapsed_time() << endl
             << "Comparacoes: " << counter->get_comparisons() << endl
             << "Trocas: " << counter->get_swaps() << endl
             << endl;
        delete timer, counter;
    }
    template <typename T, class Compare>
    void Heapify(std::vector<T> &v, Compare cmp, int i, int size, Perf::PerformanceTimer *timer, Perf::PerformanceCounter *counter)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && cmp(v[left], v[largest], counter))
        {
            largest = left;
        }

        if (right < size && cmp(v[right], v[largest], counter))
        {
            largest = right;
        }

        if (largest != i)
        {
            std::swap(v[i], v[largest]);
            counter->increment_swaps();
            Heapify(v, cmp, largest, size, timer, counter);
        }
    }

    //  TODO: Implemente algoritmo de ordenação HeapSort
    template <typename T, class Compare>
    void HeapSort(std::vector<T> &v, Compare cmp)
    {
        int size = v.size();
        auto *timer = new Perf::PerformanceTimer();
        auto *counter = new Perf::PerformanceCounter();
        timer->start();

        for (int i = size / 2 - 1; i >= 0; i--)
        {
            Heapify(v, cmp, i, size, timer, counter);
        }

        for (int i = size - 1; i >= 1; i--)
        {
            std::swap(v[0], v[i]);
            counter->increment_swaps();
            Heapify(v, cmp, 0, i, timer, counter);
        }
        timer->stop();
        cout << "Heap Sort:" << endl
             << "Tempo: " << timer->elapsed_time() << endl
             << "Comparacoes: " << counter->get_comparisons() << endl
             << "Trocas: " << counter->get_swaps() << endl
             << endl;
        delete timer, counter;
    }

    // TODO: Pesquise por algoritmos de ordenação eficientes não vistos em sala de aula.
    //       Implemente um deles.

    template <typename T, class Compare>
    void insertionSort(std::vector<T> &v, int left, int right, Compare cmp, Perf::PerformanceTimer *timer, Perf::PerformanceCounter *counter)
    {
        for (int j = left; j <= right; j++)
        {
            T v2 = v[j];
            int i = j - 1;
            while (i >= left && cmp(v2, v[i], counter))
            {
                v[i + 1] = v[i];
                i = i - 1;
                counter->increment_swaps();
            }
            v[i + 1] = v2;
            counter->increment_swaps();
        }
    }

    template <typename T, class Compare>
    void TimSort(std::vector<T> &v, Compare cmp)
    {
        auto *timer = new Perf::PerformanceTimer();
        auto *counter = new Perf::PerformanceCounter();

        int n = v.size();
        const int RUN = 32;

        for (int i = 0; i < n; i += RUN)
        {
            insertionSort(v, i, std::min(i + RUN - 1, n - 1), cmp, timer, counter);
        }

        for (int size = RUN; size < n; size = 2 * size)
        {
            for (int left = 0; left < n; left += 2 * size)
            {
                int mid = left + size - 1;
                int right = std::min((left + 2 * size - 1), (n - 1));
                // Verifica se left, mid e right estão dentro dos limites do vetor
                if (mid >= n || left >= n || right >= n)
                    continue;
                Merge(v, left, mid, right, cmp, timer, counter);
            }
        }
        timer->stop();
        cout << "Tim Sort:" << endl
             << "Tempo: " << timer->elapsed_time() << endl
             << "Comparacoes: " << counter->get_comparisons() << endl
             << "Trocas: " << counter->get_swaps() << endl
             << endl;
        delete timer, counter;
    }

    // Observaçã0:
    //  Compare cmp é uma função que recebe dois elementos do tipo T e retorna um bool.
    //  Exemplo de como declarar uma função do tipo Compare:
    /*
      struct {
        bool operator() (T &a, T &b) const
           {
               return a < b;
           }
       } cmp;
   */
    // Se cmp(a, b) retorna true, então a é menor que b.
    // veja nos arquivos de teste como usar essa função.

    // Funçoes auxiliares deve ser implementadas neste arquivo.
}

#endif /* SORT_H */
