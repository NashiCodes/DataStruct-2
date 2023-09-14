#ifndef SORT_H
#define SORT_H

#include "config.h"
#include "perf.h"
#include <vector>

using namespace Perf;

namespace Sort {

    template<typename T, class Compare>
    void InsertionSort(std::vector<T> &v, Compare cmp, Performance &perf) {
#ifdef ENABLE_PERF
        perf.get_timer().start();
#endif
        int i, j;
        T key;
        for (i = 1; i < v.size(); i++) {
            key = v[i];
            j = i - 1;
#ifdef ENABLE_PERF
            perf.get_counter().increment_comparisons();
#endif
            while (j >= 0 && cmp(key, v[j])) {
                v[j + 1] = v[j];
                j--;
#ifdef ENABLE_PERF
                perf.get_counter().increment_comparisons();
                perf.get_counter().increment_swaps();
#endif
            }
            v[j + 1] = key;
#ifdef ENABLE_PERF
            perf.get_counter().increment_swaps();
#endif
        }
#ifdef ENABLE_PERF
        perf.get_timer().stop();
#endif
    }

    // Implementação do algoritmos de ordenação basicos O(n^2)
    // Escolha uns dos métodos abaixo para implementar
    //  - BubbleSort
    //  - SelectionSort
    //  - InsertionSort
    template<typename T, class Compare>
    void BasicSort(std::vector<T> &v, Compare cmp) {
        Perf::Performance perf;
        InsertionSort(v, cmp, perf);
#ifdef ENABLE_PERF
        std::cout << "BasicSort (InsertionSort): " << std::endl;
        std::cout << "   Tamanho    : " << v.size() << std::endl;
        std::cout << "   Comparacoes: " << perf.get_counter().get_comparisons() << std::endl;
        std::cout << "   Trocas     : " << perf.get_counter().get_swaps() << std::endl;
        std::cout << "   Tempo de execução : " << perf.get_timer().elapsed_time() << " segundos" << std::endl;
#endif
    }

    template<typename T, class Compare>
    void Merge(std::vector<T> &v, int low, int mid, int hight, Compare cmp, Performance &perf) {
        int i, j, k;
        int n1 = mid - low + 1;
        int n2 = hight - mid;

        std::vector<T> L(n1), R(n2);

        for (i = 0; i < n1; i++) {
            L[i] = v[low + i];
        }
        for (j = 0; j < n2; j++) {
            R[j] = v[mid + 1 + j];
        }

        i = 0;
        j = 0;
        k = low;

        while (i < n1 && j < n2) {
#ifdef ENABLE_PERF
            perf.get_counter().increment_comparisons();
#endif
            if (cmp(L[i], R[j])) {
                v[k] = L[i];
                i++;
            } else {
                v[k] = R[j];
                j++;
            }
#ifdef ENABLE_PERF
            perf.get_counter().increment_swaps();
#endif
            k++;
        }

        while (i < n1) {
            v[k] = L[i];
            i++;
            k++;
#ifdef ENABLE_PERF
            perf.get_counter().increment_swaps();
#endif
        }

        while (j < n2) {
            v[k] = R[j];
            j++;
            k++;
#ifdef ENABLE_PERF
            perf.get_counter().increment_swaps();
#endif
        }
    }

    template<typename T, class Compare>
    void auxMergeSort(std::vector<T> &v, int low, int hight, Compare cmp, Performance &perf) {
        if (low < hight) {
            int mid = (low + hight) / 2;
            auxMergeSort(v, low, mid, cmp, perf);
            auxMergeSort(v, mid + 1, hight, cmp, perf);
            Merge(v, low, mid, hight, cmp, perf);
        }
    }


    // Implementação algoritmo de ordenação MergeSort
    template<typename T, class Compare>
    void MergeSort(std::vector<T> &v, Compare cmp) {
        Perf::Performance perf;
        auxMergeSort(v, 0, v.size() - 1, cmp, perf);
#ifdef ENABLE_PERF
        perf.get_timer().stop();
        std::cout << "MergeSort: " << std::endl;
        std::cout << "   Tamanho    : " << v.size() << std::endl;
        std::cout << "   Comparacoes: " << perf.get_counter().get_comparisons() << std::endl;
        std::cout << "   Trocas     : " << perf.get_counter().get_swaps() << std::endl;
        std::cout << "   Tempo de execução : " << perf.get_timer().elapsed_time() << " segundos" << std::endl;
#endif

    }

    template<typename T, class Compare>
    int Partition(std::vector<T> &v, Compare cmp, Performance &perf) {
        int i = -1;
        T pivot = v[v.size() - 1];
        for (int j = 0; j < v.size() - 1; j++) {
#ifdef ENABLE_PERF
            perf.get_counter().increment_comparisons();
#endif
            if (cmp(v[j], pivot)) {
                i++;
                std::swap(v[i], v[j]);
#ifdef ENABLE_PERF
                perf.get_counter().increment_swaps();
#endif
            }
        }
        std::swap(v[i + 1], v[v.size() - 1]);
#ifdef ENABLE_PERF
        perf.get_counter().increment_swaps();
#endif
        return i + 1;
    }

    template<typename T, class Compare>
    void auxQuickSort(std::vector<T> &v, int low, int hight, Compare cmp, Performance &perf) {
        if (low < hight) {
            int pi = Partition(v, cmp, perf);
            auxQuickSort(v, low, pi - 1, cmp, perf);
            auxQuickSort(v, pi + 1, hight, cmp, perf);
        }
    }

    // TODO: Implementação algoritmo de ordenação QuickSort
    template<typename T, class Compare>
    void QuickSort(std::vector<T> &v, Compare cmp) {
        Perf::Performance perf;
        auxQuickSort(v, 0, v.size() - 1, cmp, perf);
#ifdef ENABLE_PERF
        perf.get_timer().stop();
        std::cout << "QuickSort: " << std::endl;
        std::cout << "   Tamanho    : " << v.size() << std::endl;
        std::cout << "   Comparacoes: " << perf.get_counter().get_comparisons() << std::endl;
        std::cout << "   Trocas     : " << perf.get_counter().get_swaps() << std::endl;
        std::cout << "   Tempo de execução : " << perf.get_timer().elapsed_time() << " segundos" << std::endl;
#endif
    }


    //  TODO: Implemente algoritmo de ordenação HeapSort
    template<typename T, class Compare>
    void HeapSort(std::vector<T> &v, Compare cmp) {
        int size = v.size();
        for (int i = size / 2 - 1; i >= 0; i--) {
            Heapify(v, size, i, cmp);
        }

        for (int i = size - 1; i >= 0; i--) {
            std::swap(v[0], v[i]);
            Heapify(v, i, 0, cmp);
#ifdef ENABLE_PERF
            perf.get_counter().increment_swaps();
#endif
        }
#ifdef ENABLE_PERF
        perf.get_timer().stop();
        std::cout << "HeapSort: " << std::endl;
        std::cout << "   Tamanho    : " << v.size() << std::endl;
        std::cout << "   Comparacoes: " << perf.get_counter().get_comparisons() << std::endl;
        std::cout << "   Trocas     : " << perf.get_counter().get_swaps() << std::endl;
        std::cout << "   Tempo de execução : " << perf.get_timer().elapsed_time() << " segundos" << std::endl;
#endif
    }

    template<typename T, class Compare>
    void Heapify(std::vector<T> &v, int size, int i, Compare cmp, Performance &perf) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && cmp(v[left], v[largest])) {
            largest = left;
#ifdef ENABLE_PERF
            perf.get_counter().increment_comparisons();
#endif
        }

        if (right < size && cmp(v[right], v[largest])) {
            largest = right;
#ifdef ENABLE_PERF
            perf.get_counter().increment_comparisons();
#endif
        }

        if (largest != i) {
            std::swap(v[i], v[largest]);
            Heapify(v, size, largest, cmp);
#ifdef ENABLE_PERF
            perf.get_counter().increment_swaps();
#endif
        }
    }

    // TODO: Pesquise por algoritmos de ordenação eficientes não vistos em sala de aula.
    //       Implemente um deles.
    template<typename T, class Compare>
    void TimSort(std::vector<T> &v, Compare cmp) {
        Perf::Performance perf;
        int n = v.size();
        const int RUN = 32;
        for (int i = 0; i < n; i += RUN) {
            TimInsertionSort(v, i, std::min((i + 31), (n - 1)), cmp, perf);
        }

        for (int size = RUN; size < n; size = 2 * size) {
            for (int left = 0; left < n; left += 2 * size) {
                int mid = left + size - 1;
                int right = std::min((left + 2 * size - 1), (n - 1));
                Merge(v, left, mid, right, cmp, perf);
            }
        }

#ifdef ENABLE_PERF
        perf.get_timer().stop();
        std::cout << "TimSort: " << std::endl;
        std::cout << "   Tamanho    : " << v.size() << std::endl;
        std::cout << "   Comparacoes: " << perf.get_counter().get_comparisons() << std::endl;
        std::cout << "   Trocas     : " << perf.get_counter().get_swaps() << std::endl;
        std::cout << "   Tempo de execução : " << perf.get_timer().elapsed_time() << " segundos" << std::endl;
#endif
    }

    template<typename T, class Compare>
    void TimInsertionSort(std::vector<T> &v, int left, int right, Compare cmp, Performance &perf) {
        for (int i = left + 1; i <= right; i++) {
            T temp = v[i];
            int j = i - 1;
            while (j >= left && cmp(v[j], temp)) {
                v[j + 1] = v[j];
                j--;
#ifdef ENABLE_PERF
                perf.get_counter().increment_comparisons();
                perf.get_counter().increment_swaps();
#endif
            }
            v[j + 1] = temp;
#ifdef ENABLE_PERF
            perf.get_counter().increment_swaps();
#endif
        }

    }

    //Observaçã0:
    // Compare cmp é uma função que recebe dois elementos do tipo T e retorna um bool.
    // Exemplo de como declarar uma função do tipo Compare:
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