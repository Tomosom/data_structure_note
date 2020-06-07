#ifndef SORT_H
#define SORT_H

#include <iostream>
#include "object.h"
#include "array.h" /* 为了将该排序类应用于数组类(Array) */

namespace DTLib {

class Sort : public Object {
private: // 构造函数被定义为私有的，表明Sort这个类不可能有对象的
    Sort();
    Sort(const Sort&);
    Sort &operator = (const Sort &);

    template <typename T>
    static void Swap(T &a, T &b)
    {
        T c(a);
        a = b;
        b = c;
    }

    // 归并排序 辅助函数
    template <typename T>
    static void Merge(T src[], T helper[], int begin, int mid, int end, bool min2max) // 
    {
        int i = begin;
        int j = mid + 1;
        int k = begin;

        while ((i <= mid) && (j <= end))
        {
            if (min2max ? (src[i] < src[j]) : (src[i] > src[j])) {
                helper[k++] = src[i++];
            } else {
                helper[k++] = src[j++];
            }
        }

        while (i <= mid) {
            helper[k++] = src[i++];
        }
        
        while (j <= end) {
            helper[k++] = src[j++];
        }

        for (i = begin; i <= end; i++) {
            src[i] = helper[i];
        }
    }

    template <typename T>
    static void Merge(T src[], T helper[], int begin, int end, bool min2max) // 
    {
        if (begin < end) {
            int mid = (begin + end) / 2;
            Merge(src, helper, begin, mid, min2max);
            Merge(src, helper, mid + 1, end, min2max);
            Merge(src, helper, begin, mid, end, min2max);
        }
    }

    // 快速排序 辅助函数
    template <typename T>
    static int Partition(T array[], int begin, int end, bool min2max) // 
    {
        T pv = array[begin];

        while(begin < end) {
            while ((begin < end) && (min2max ? (array[end] > pv) :(array[end] < pv))) {
                end--;
            }
            Swap(array[begin], array[end]);
            while ((begin < end) && (min2max ? (array[begin] <= pv) : (array[begin] >= pv))) {
                begin++;
            }
            Swap(array[begin], array[end]);
        }

        array[begin] = pv;
        return begin;
    }

    template <typename T>
    static void Quick(T array[], int begin, int end, bool min2max) // 
    {
        if (begin < end) {
            int pivot = Partition(array, begin, end, min2max);
            Quick(array, begin, pivot - 1, min2max);
            Quick(array, pivot + 1, end, min2max);
        }
    }
public:
    // 选择排序, 该排序是不稳定的，会打破原先相同数据元素的先后关系
    template <typename T>
    static void Select(T array[], int len, bool min2max = true) // O(n2)
    {
        for(int i = 0; i < len; i++) {
            int min = i;
            for (int j = i + 1; j < len; j++) {
                if (min2max ? (array[min] > array[j]) : (array[min] < array[j])) {
                    min = j;
                }
            }
            if (min != i) {
                Swap(array[i], array[min]);
            }
        }
    }

    // 插入排序，该排序是稳定的
    template <typename T>
    static void Insert(T array[], int len, bool min2max = true) // O(n2)
    {
        for (int i = 1; i < len; i++) {
            int k = i;
            T e = array[i];

            for (int j = i - 1; (j >= 0) && (min2max ? (array[j] > e) : (array[j] < e)); j--) {
                array[j + 1] = array[j];
                k = j;
            }

            if (k != i) {
                array[k] = e;
            }
        }
    }

    // 冒泡排序，该排序是稳定的
    template <typename T>
    static void Bubble(T array[], int len, bool min2max = true) // O(n2)
    {
        bool exchange = true;

        for (int i = 0; (i < len) && exchange; i++) {
            exchange = false;
            for (int j = len - 1; j > i; j--) {
                if (min2max ? (array[j] < array [j - 1]) : (array[j] > array [j - 1])) {
                    Swap(array[j], array[j - 1]);
                    exchange = true;
                }
            }
        }
    }

    /* 希尔排序 - 插入排序, 该排序是不稳定的
     * 基本思想：将待排序列划分为若干组，在每一组内进行插入排序，以使整个序列基本有序，然后再对整个序列进行插入排序
     */
    template <typename T>
    static void Shell_from_insert(T array[], int len, bool min2max = true) // O(n3/2)
    {
        int d = len;
        do {
            d = d / 3 + 1; // 实践证明这样减小d比较好，也可以d--, 但效率不会好
            for (int i = d; i < len; i += d) {
                int k = i;
                T e = array[i];

                for (int j = i - d; (j >= 0) && (min2max ? (array[j] > e) : (array[j] < e)); j -= d) {
                    array[j + d] = array[j];
                    k = j;
                }

                if (k != i) {
                    array[k] = e;
                }
            }
        } while(d > 1);
    }
#if 1
    /* 希尔排序 - 冒泡排序
     * 基本思想：将待排序列划分为若干组，在每一组内进行冒泡排序，以使整个序列基本有序，然后再对整个序列进行冒泡排序
     */
    template <typename T>
    static void Shell_from_bubble(T array[], int len, bool min2max = true) // test
    {
        int d = len;
        do {
            d = d / 3 + 1; // 实践证明这样减小d比较好，也可以d--, 但效率不会好
            bool exchange = true;
            for (int i = d - 1; (i < len - 1) && exchange; i += d) {
                exchange = false;
                // 定位到分组的最后一个
                int j = i;
                while (j < len - d) {
                    j += d;
                }
                for (; j > i; j -= d) {
                    if (min2max ? (array[j] < array [j - d]) : (array[j] > array [j - d])) {
                        Swap(array[j], array[j - d]);
                        exchange = true;
                    }
                }
            }
        } while(d > 1);
    }
#endif

    // 归并排序 - 运用到递归 - 是一种稳定的排序法 - 需要额外的辅助空间(空间复杂度O(n))
    // 基本思想：将两个或两个以上的有序序列合并成一个新的有序序列
    template <typename T>
    static void Merge(T array[], int len, bool min2max = true) // O(n*logn) 
    {
        T *helper = new T[len];

        if (helper != NULL) {
            Merge(array, helper, 0, len - 1, min2max);
        }

        delete[] helper;
    }

    // 快速排序 - 运用到递归 - 是一种不稳定的排序法
    // 基本思想：任取序列中的某个数据元素作为基准将整个序列划分为左右两个子序列
    //          左侧子序列中所有元素都小于或等于基准元素
    //          右侧序列中所有元素都大于基准元素
    //          基准元素排在这两个子序列中间
    //          分别对着两个子序列重复进行划分，直到所有的数据元素都排在相应位置上为止
    template <typename T>
    static void Quick(T array[], int len, bool min2max = true) // O(n*logn)
    {
        Quick(array, 0, len - 1, min2max);
    }

    /***************************************************/
    /* 为了将该排序类应用于数组类(Array)，固需新增重载函数 */
    template <typename T>
    static void Select(Array<T> &array, bool min2max = true)
    {
        Select(array.array(), array.length(), min2max);
    }
    
    template <typename T>
    static void Insert(Array<T> &array, bool min2max = true)
    {
        Insert(array.array(), array.length(), min2max);
    }
    
    template <typename T>
    static void Bubble(Array<T> &array, bool min2max = true)
    {
        Bubble(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void Shell_from_insert(Array<T> &array, bool min2max = true)
    {
        Shell_from_insert(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void Merge(Array<T> &array, bool min2max = true)
    {
        Merge(array.array(), array.length(), min2max);
    }

    template <typename T>
    static void Quick(Array<T> &array, bool min2max = true)
    {
        Quick(array.array(), array.length(), min2max);
    }

};



}


#endif