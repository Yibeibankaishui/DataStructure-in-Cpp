#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <utility>
#include <exception>
#include <iostream>


// 抽象类 linearlist
template <typename Object>
class linearlist{
    public:
        virtual ~linearlist(){};
        virtual bool empty() const = 0;
        virtual int size() const = 0;
        virtual Object & get(int theIndex) const = 0;
        virtual int indexOf(const Object & theElement) const = 0;
        virtual void erase(int theIndex) = 0;
        virtual void insert(int theIndex, const Object & theElement) = 0;
        virtual void output(std::ostream & out) const = 0;

};


// 双链表 list
template <typename Object>
class List{
    private:
        struct Node{
            Object data;
            Node *prev;
            Node *next;

            Node(const Object & d = Object{ }, Node * p = nullptr, Node * n = nullptr): data{d}, prev{p}, next{n} { }
            Node(Object && d, Node * p = nullptr, Node * n = nullptr): data{std::move(d)}, prev{p}, next{n} { }
        };

    public:
        class const_iterator{
            public:
                const_iterator(): theList(nullptr), current(nullptr) { }

                const Object & operator*() const{
                    return retrieve();
                }

                const_iterator & operator++(){
                    current = current -> next;
                    return *this;
                }

                const_iterator operator++(int){
                    const_iterator old = *this;
                    ++(*this);
                    return old;     // 返回临时变量的引用？如果不返回引用，怎么做左值
                }

                const_iterator & operator--(){
                    current = current -> prev;
                    return *this;
                }

                const_iterator operator--(int){
                    const_iterator old = *this;
                    --(*this);
                    return old;
                }

                bool operator==(const const_iterator & rhs) const{
                    return current == rhs.current;
                }
                bool operator!=(const const_iterator & rhs) const{
                    return !(*this == rhs);
                }

            protected:
                const List<Object> *theList;

                Node * current;

                Object & retrieve() const{
                    return current -> data;
                }

                const_iterator(const List<Object> & lst, Node *p): theList(&lst), current(p) { }

                void assertIsValid() const{
                    if(theList == nullptr || current == nullptr || current == theList -> head)
                        throw IteratorOutOfBoundsException{ };
                }

                friend class List<Object>;
        };

        class iterator : public const_iterator{
            public:
                iterator() { }

                Object & operator*(){
                    return const_iterator::retrieve();
                }

                const Object & operator*() const{
                    return const_iterator::operator*();
                }

                iterator & operator++(){
                    this -> current = this -> current -> next;
                    return *this;
                }

                iterator operator++(int){
                    iterator old = *this;
                    ++(*this);
                    return old;
                }

                iterator & operator--(){
                    this -> current = this -> current -> prev;
                    return *this;
                }

                iterator operator--(int){
                    iterator old = *this;
                    --(*this);
                    return old;
                }

            protected:
                // iterator(Node *p): const_iterator{p} { }
                iterator(const List<Object> & lst, Node *p): const_iterator(lst, p) { }                

                friend class List<Object>;
        };

    public:
        List(){
            init();
        }

        List(const List & rhs){
            init();
            for(auto & x: rhs){
                push_back(x);
            }
        }

        ~List(){
            clear();
            delete head;
            delete tail;
        }

        List & operator=(const List & rhs){
            List copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        List(List && rhs): theSize(rhs.theSize), head(rhs.head), tail(rhs.tail) {
            rhs.theSize = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }
        
        List & operator=(List && rhs){
            std::swap(theSize, rhs.theSize);
            std::swap(head, rhs.head);
            std::swap(tail, rhs.tail);
            return *this;
        }

        // iterator begin(){
        //     return {head->next};
        // };

        iterator begin(){
            iterator itr{*this, head};
            return ++itr;
        }

        // const_iterator begin() const{
        //     return {head->next};
        // }

        const_iterator begin() const{
            const_iterator itr{*this, head};
            return ++itr;
        }

        // iterator end(){
        //     return {tail};
        // }

        iterator end(){
            iterator itr{*this, tail};
            return itr;
        }

        // const_iterator end() const{
        //     return {tail};
        // }

        const_iterator end() const{
            const_iterator itr{*this, tail};
            return itr;
        }

        int size() const{
            return theSize;
        }

        bool empty() const{
            return size() == 0;
        }

        void clear(){
            while(!empty())
                pop_front();
        }

        // 返回第一个元素值
        Object & front(){
            return *begin();
        }

        const Object & front() const{
            return *begin();
        }

        // 返回最后一个元素值
        Object & back(){
            return *--end();
        }

        const Object & back() const{
            return *--end();
        }

        Object & operator[](int index){
            if(index >= theSize){
                std::cout << "index out of range! " << std::endl;
                throw(IteratorOutOfBoundsException{ });
            }
            else{
                int id = 0;
                iterator itr = begin();
                while(id < index){
                    ++itr;
                    ++id;
                }
                return *itr;
            }
        }

        // const Object & operator[](int index) const{

        //     return objects[index];
        // }

        void push_front(const Object & x){
            insert(begin(), x);
        }

        void push_front(Object && x){
            insert(begin(), std::move(x));
        }

        void push_back(const Object & x){
            insert(end(), x);
        }

        void push_back(Object && x){
            insert(end(), std::move(x));
        }

        void pop_front(){
            erase(begin());
        }

        void pop_back(){
            erase(--end());
        }

        // iterator insert(iterator itr, const Object & x){
        //     Node *p = itr.current;
        //     theSize++;
        //     return {p -> prev = p -> prev -> next = new Node{x, p -> prev, p}};
        // }

        // 在指向节点之前插入新节点
        iterator insert(iterator itr, const Object & x){
            itr.assertIsValid();
            if(itr.theList != this)
                throw IteratorMismatchException{ };

            Node *p = itr.current;
            theSize++;
            return {*this, p -> prev = p -> prev -> next = new Node{x, p -> prev, p}};
        }

        // iterator insert(iterator itr, Object && x){
        //     Node *p = itr.current;
        //     theSize++;
        //     return {p -> prev = p -> prev -> next = new Node{std::move(x), p -> prev, p}}
        // }

        iterator insert(iterator itr, Object && x){
            itr.assertIsValid();
            if(itr.theList != this)
                throw IteratorMismatchException{ };

            Node *p = itr.current;
            theSize++;
            return {*this, p -> prev = p -> prev -> next = new Node{std::move(x), p -> prev, p}};
        }

        // // 删除当前节点，返回后一个节点
        // iterator erase(iterator itr){
        //     Node *p = itr.current;
        //     iterator retVal{p -> next};
        //     p -> prev -> next = p -> next;
        //     p -> next -> prev = p -> prev;
        //     delete p;
        //     theSize--;

        //     return retVal;
        // }

        iterator erase(iterator itr){
            itr.assertIsValid();
            if(itr.theList != this)
                throw IteratorMismatchException{ };

            Node *p = itr.current;
            iterator retVal{*this, p -> next};
            p -> prev -> next = p -> next;
            p -> next -> prev = p -> prev;
            delete p;
            theSize--;

            return retVal;
        }

        iterator erase(iterator from, iterator to){
            for(iterator itr = from; itr != to; )
                itr = erase(itr);

            return to;
        }

    private:
        int theSize;
        Node *head;
        Node *tail;

        void init(){
            theSize = 0;
            head = new Node;
            tail = new Node;
            head -> next = tail;
            tail -> prev = head;
        }

        class IteratorMismatchException : public std::exception{
            virtual const char * what() const throw(){
                return "Iterator Mismatch ";
            }
        }; 

        class IteratorOutOfBoundsException : public std::exception{
            virtual const char * what() const throw(){
                return "Iterator Out of Bounds ";
            }
        };
};


// 单链表实现
template <typename Object>
class ListSingle{
    private:
        struct Node{
            Object data;
            Node *next;

            Node(const Object & d = Object{ }, Node * n = nullptr): data(d), next(n) { }
            Node(Object && d, Node * n = nullptr): data{std::move(d)}, next{n} { }
        };

    private:
        int theSize;
        Node *head;
        Node *tail;

        void init(){
            theSize = 0;
            head = new Node;
            tail = new Node;
            head -> next = tail;
        }
        
        class IteratorMismatchException : public std::exception{
            virtual const char * what() const throw(){
                return "Iterator Mismatch ";
            }
        }; 

        class IteratorOutOfBoundsException : public std::exception{
            virtual const char * what() const throw(){
                return "Iterator Out of Bounds ";
            }
        };

    public:
        class const_iterator{
            public:
                const_iterator(): current(nullptr) { }

                const Object & operator*() const{
                    return retrieve();
                }

                const_iterator & operator++(){
                    current = current -> next;
                    return *this;
                }

                const_iterator operator++(int){
                    const_iterator old = *this;
                    ++(*this);
                    return old;
                }

                bool operator==(const const_iterator & rhs) const{
                    return current == rhs.current;
                }

                bool operator!=(const const_iterator & rhs) const{
                    return !(*this == rhs);
                }
            
            protected:
                Node * current;
                    
                Object & retrieve() const{
                    return current -> data;
                }

                const_iterator(Node * p): current(p) { }

                void assertIsValid() const{
                    if(current == nullptr)
                        throw IteratorOutOfBoundsException{ };
                }
                friend class ListSingle<Object>;

        };
        
        class iterator : public const_iterator{
            public:
                iterator() { }

                Object & operator*(){
                    return const_iterator::retrieve();
                }

                const Object & operator*() const{
                    return const_iterator::operator*();
                }

                iterator & operator++(){
                    this -> current = this -> current -> next;
                    return *this;
                }

                iterator operator++(int){
                    iterator old = *this;
                    ++(*this);
                    return old;
                }

            protected:
                iterator(Node *p): const_iterator(p) { }
                friend class ListSingle<Object>;
        };

    public:
        ListSingle(){
            init();
        }

        ListSingle(const ListSingle & rhs){
            init();
            for(auto & x: rhs){
                push_back(x);
            }
        }
        
        ~ListSingle(){
            clear();
            delete head;
            delete tail;
        }

        ListSingle & operator=(const ListSingle & rhs){
            ListSingle copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        ListSingle(ListSingle && rhs): theSize(rhs.theSize), head(rhs.head){
            rhs.theSize = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }

        ListSingle & operator=(ListSingle && rhs){
            std::swap(theSize, rhs.theSize);
            std::swap(head, rhs.head);
            std::swap(tail, rhs.tail);
            return *this;
        }

        iterator begin(){
            return {head -> next};
        }

        const_iterator begin() const{
            return {head -> next};
        }

        iterator end(){
            return {tail};
        }

        const_iterator end() const{
            return {tail};
        }  

        int size() const{
            return theSize;
        }  

        bool empty() const{
            return size() == 0;
        }

        void clear(){
            while(!empty())
                pop_front();       
        }

        Object & front(){
            return *begin();
        }

        const Object & front() const{
            return *begin();
        }

        // Object & back(){ }

        // const Object & back() const{ }

        // 在head节点之后插入
        void push_front(const Object & x){
            iterator itr{head};
            insert(itr, x);
        }

        void push_front(Object && x){
            iterator itr{head};
            insert(itr, std::move(x));
        }

        // 在tail节点之前一个节点插入
        void push_back(const Object & x){
            insert(theSize - 1, x);
        }

        void push_back(Object && x){
            insert(theSize - 1, std::move(x));
        }

        void pop_front(){
            erase(0);
        }

        void pop_back(){
            erase(theSize - 1);
        }

        // 根据索引获得位置指针（迭代器）
        const_iterator get(int theIndex) const{
            if(theIndex >= theSize){
                std::cout << "index out of range! " << std::endl;
                throw(IteratorOutOfBoundsException{ });
            }
            else if(theIndex == -1){
                iterator itr{head};
                return itr;
            }
            else{
                int id = 0;
                const_iterator itr = begin();
                while(id < theIndex){
                    ++itr;
                    ++id;
                }
                return itr;
            }
        }

        iterator get(int theIndex){
            if(theIndex >= theSize){
                std::cout << "index out of range! " << std::endl;
                throw(IteratorOutOfBoundsException{ });
            }
            else if(theIndex == -1){
                iterator itr{head};
                return itr;
            }
            else{
                int id = 0;
                iterator itr = begin();
                while(id < theIndex){
                    ++itr;
                    ++id;
                }
                return itr;
            }
        }

        // List[index]
        Object & operator[](int theIndex){
            iterator itr = get(theIndex);
            return *itr;
        }

        // TODO: 根据索引，在后插入
        void insert(int theIndex, const Object & element){
            iterator itr = get(theIndex);
            insert(itr, element);
        }

        void insert(int theIndex, Object && element){
            iterator itr = get(theIndex);
            insert(itr, element);
        }

        // 根据索引，删除
        void erase(int theIndex){
            iterator itr_prev = get(theIndex - 1);
            iterator itr_cur = get(theIndex); 
            Node *prev = itr_prev.current;
            Node *cur = itr_cur.current;
            prev -> next = cur -> next;
            delete cur;
            theSize--;
        }

        // void erase(int theIndex_from, int theIndex_to){
        // }

        // 在节点之后插入
        iterator insert(iterator itr, const Object & x){
            itr.assertIsValid();
            Node *p = itr.current;
            theSize++;
            return {p -> next = new Node(x, p -> next)};
        }

        iterator insert(iterator itr, Object && x){
            itr.assertIsValid();
            Node *p = itr.current;
            theSize++;
            return {p -> next = new Node(std::move(x), p -> next)};
        }

};


#endif