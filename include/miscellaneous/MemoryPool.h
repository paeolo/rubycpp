#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

using namespace std;

template <class T, size_t size>
class MemoryPool
{
    struct Entry
    {
        Entry* next;
    };
    
    private:
        Entry *firstFreeEntry = nullptr;
        size_t lastIndex = 0;

        static const size_t entrySize = sizeof(T) > sizeof(Entry) ? sizeof(T) : sizeof(Entry);
        char data[size * entrySize];

        T* getEntry(size_t index)
        {
            return reinterpret_cast<T* >(&data[index * entrySize]); 
        }

    public:
        MemoryPool() = default;
        ~MemoryPool() = default;

        T* allocate()
        {
            if (firstFreeEntry)
            {
                Entry* entry = firstFreeEntry;
                firstFreeEntry = entry->next;
                return reinterpret_cast<T *>(entry);
            }

            if(lastIndex < size)
                return this->getEntry(lastIndex++);

            return nullptr;
        }

        void deallocate(T *pointer)
        {
            Entry *entry = reinterpret_cast<Entry*>(pointer);
            entry->next = firstFreeEntry;
            firstFreeEntry = entry;
        }
};

#endif
