#include <iostream>
#include <windows.h>
#define SIZE 300000

void sayHeap(HANDLE pheap) {
    PROCESS_HEAP_ENTRY proc_heap_entry;
    proc_heap_entry.lpData = nullptr;

    int sizeheap = 0;
    int uncommitted = 0;
    int busy = 0;
    int others = 0;

    while (HeapWalk(pheap, &proc_heap_entry)) {

        if ((proc_heap_entry.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE))
            uncommitted += proc_heap_entry.cbData;
        else if (proc_heap_entry.wFlags & PROCESS_HEAP_ENTRY_BUSY)
            busy += proc_heap_entry.cbData;
        else
            others += proc_heap_entry.cbData;
        
        sizeheap += proc_heap_entry.cbData;
    }

    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "heap size: " << sizeheap << std::endl;
    std::cout << "uncommited size: " << uncommitted << std::endl;
    std::cout << "busy size: " << busy << std::endl;
    std::cout << "others size: " << others << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

}

int main()
{
    HANDLE pheap = GetProcessHeap();

    sayHeap(pheap);
    int* array = new int[SIZE];
    sayHeap(pheap);
}
