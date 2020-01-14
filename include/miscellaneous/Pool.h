#ifndef POOL_H
#define POOL_H

template<int size>
class Pool
{  
    private:
        int firstFreeEntry = -1;
        int lastEntry = 0;
        int data[size];

    public:
        Pool() = default;
        ~Pool() = default;

        int allocate()
        {
            if (firstFreeEntry >= 0)
            {
                int entry = firstFreeEntry;
                firstFreeEntry = data[entry];
                return entry;
            }
            return lastEntry++;
        }

        void deallocate(int entry)
        {
            data[entry] = firstFreeEntry;
            firstFreeEntry = entry;
        }
};

#endif