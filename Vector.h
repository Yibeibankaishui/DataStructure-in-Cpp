#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <utility>

template <typename Object>
class Vector{
    public:
        explicit Vector(int initSize = 0): theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY}{
            objects = new Object[theCapacity];
        }

        Vector(const Vector & rhs): theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{nullptr}{
            objects = new Object[theCapacity];
            for (int k = 0; k < theSize; ++k)
                objects[k] = rhs.objects[k];
        }

        Vector & operator=(const Vector & rhs){
            Vector copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        ~Vector(){
            delete [ ] objects;
        }

        Vector(Vector && rhs): theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects}{
            rhs.objects = nullptr;
            rhs.theSize = 0;
            rhs.theCapacity = 0;
        }

        Vector & operator=(Vector && rhs){
            std::swap(theSize, rhs.theSize);
            std::swap(theCapacity, rhs.theCapacity);
            std::swap(objects, rhs.objects);

            return *this;
        }

        void resize(int newSize){
            if(newSize > theCapacity)
                reserve(newSize * 2);
            theSize = newSize;
        }

        void reserve(int newCapacity){
            if(newCapacity < theSize)
                return;
            
            Object *newArray = new Object[newCapacity];
            for(int k = 0; k < theSize; ++k)
                newArray[k] = std::move(objects[k]);

            theCapacity = newCapacity;
            std::swap(objects, newArray);
            delete [ ] newArray;
        }

        Object & operator[](int index){
            return objects[index];
        }

        const Object & operator[](int index) const{
            return objects[index];
        }

        bool empty() const{
            return size() == 0;
        }

        int size() const{
            return theSize;
        }

        int capacity() const{
            return theCapacity;
        }

        void push_back(const Object & x){
            if(theSize == theCapacity)
                reserve(2 * theCapacity + 1);
            objects[theSize++] = x;
        }

        void push_back(Object && x){
            if(theSize == theCapacity)
                reserve(2 * theCapacity + 1);
            objects[theSize++] = std::move(x);
        }

        void pop_back()
        {
            --theSize;
        }

        // 末尾元素
        const Object & back () const{
            return objects[theSize - 1];
        }

        Object & back (){
            return objects[theSize - 1];
        }

        typedef Object * iterator;
        typedef const Object * const_iterator;

        // 获取首指针
        iterator begin(){
            return &objects[0];
        }

        const_iterator begin() const{
            return &objects[0];
        }

        // 获取末指针
        iterator end(){
            return &objects[size()];
        }

        const_iterator end() const{
            return &objects[size()];
        }

        static const int SPARE_CAPACITY = 16;

    private:
        int theSize;
        int theCapacity;
    
    protected:
        Object * objects;

};


#endif