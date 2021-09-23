#ifndef _VECTOR_HEADER_
#define _VECTOR_HEADER_

typedef std::size_t size_type;


namespace ds{
    template <class T>
    class vector{
        class vector_iterator{
            // using value_type = T;
            // using pointer    = T*;      
            // using reference  = T&;      
            // using difference_type = std::ptrdiff_t;     
            // using iterator_category = std::random_access_iterator_tag;      
            
            public:
                vector_iterator():ptr(nullptr),position(0){};
                vector_iterator(vector<T> *const ptr=nullptr, size_type pos=-1){
                    this->ptr = ptr;

                    if(ptr == nullptr){
                        position = -1;
                    }
                    else{
                        if(0 <= pos && pos < ptr->size){
                            position = pos;
                        }
                        else{
                            position = -1;
                        }
                    }
                }

                T& operator*(){
                    return (*ptr)[position];
                }

                //FIXME
                vector_iterator& operator++(){
                    ++position;
                    ++ptr;
                    return *this;
                }

                vector_iterator operator++(int){
                    vector_iterator temp(ptr, position);
                    ++position;
                    return temp;
                }

                operator bool() const{
                    return ptr != nullptr;
                }

                bool operator<(const vector_iterator& other){
                    if(ptr != other.ptr){
                        throw;
                    }

                    return position < other.position;
                }

                bool operator<=(const vector_iterator& other){
                    if(ptr != other.ptr){
                        throw;
                    }

                    return position <= other.position;
                }

                //operator=

            private:
                vector<T>* ptr;
                size_type position;
            };
    public:
        vector();
        vector(std::initializer_list<T>);
        ~vector();
        vector(const vector<T>& other);
        vector(int size);
        
    public:
        const size_type get_size()const;
        void append(const T& elem);

        // const T& operator[](const unsigned index)const;
        T& operator[](const size_type index)const;

    //playing around
    public:
        //FIXME should prob be const, but this becomes const and 
        //I cant use in iterator constructor
        vector_iterator begin(){
            vector_iterator temp(this, 0);
            return temp;
        }
        vector_iterator end(){
            vector_iterator temp(this, size);
            return temp;
        }
        // //TODO how to force T to be comparable? C++17?
        // //Do i want this in a container?
        // const T& get_max()const;
        // const T& get_min()const;
        // //TODO being able to provide sorting implementation here? 
        // void sort()

    private:
        void add_to_end(const T& element);
        //FIXME better naming for this one, 
        //dont connect it to size member
        void resize(const size_type newSize);
        // void auto_resize();
        bool buffer_is_full() const;

        
    private:
        T* start;
        size_type size;
        size_type capacity;
    };
}

#endif  //_VECTOR_HEADER_