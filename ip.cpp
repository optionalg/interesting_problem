#include <vector>
#include <stdlib.h>
#include <string>
#include <climits>
#include <stdio.h>

using namespace std;

void insert(vector<int> &heap, int loc) {
    if(heap[loc] < heap[ (loc - 1) / 2 ]) {
        int temp = heap[ (loc - 1) / 2 ];
        heap[ (loc - 1) / 2 ] = heap[loc];
        heap[loc] = temp;
        insert(heap, (loc - 1) / 2);
    }
}

void reheap(vector<int> &heap, int loc) {
    unsigned int left_child = 2 * loc + 1;
    unsigned int right_child = 2 * loc + 2;
    if(left_child >= heap.size()) {
        return;
    }
    if(left_child >= heap.size() || right_child >= heap.size()) {
        if(left_child < heap.size()) {
            if(heap[loc] > heap[left_child]) {
                int temp = heap[left_child];
                heap[left_child] = heap[loc];
                heap[loc] = temp;
                loc = left_child;
            } else {
                return;
            }
        } else if(right_child < heap.size()) {
            if(heap[loc] > heap[right_child]) {
                int temp = heap[right_child];
                heap[right_child] = heap[loc];
                heap[loc] = temp;
                loc = right_child;
            } else {
                return;
            }
        }
        return;
    } else {
        if(heap[loc] > heap[left_child] || heap[loc] > heap[right_child]) {
            if(heap[left_child] <= heap[right_child]) {
                int temp = heap[left_child];
                heap[left_child] = heap[loc];
                heap[loc] = temp;
                loc = left_child;
            } else {
                int temp = heap[right_child];
                heap[right_child] = heap[loc];
                heap[loc] = temp;
                loc = right_child;
            }
        } else {
            return;
        }
    }
    reheap(heap, loc);
}


int remove(vector<int> &heap) {
    int ret = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.resize(heap.size()-1);
    reheap(heap, 0);
    return ret;
}

int minimum_len(int arr[], int length)
{
    vector<int> heap;
    heap.push_back(arr[0]);
    for(int i = 1; i < length; i++) {
        heap.push_back(arr[i]);
        insert(heap, heap.size() - 1);
    }
    int i = 0;
    int temp = LONG_MIN;
    int ans = LONG_MIN;
    ans = remove(heap);
    while(i < length - 1) {
        temp = remove(heap);
        if(temp > ans + 1) {
            ans = ans;
            break;
        }
        ans = temp;
        i++;
    }
    
    return ans + 1;
}

int main() {
    int arr[] = { -1,4,5,-23,24, -22 };
    int min = minimum_len(arr, 6);
    printf("%d\n", min);
}
