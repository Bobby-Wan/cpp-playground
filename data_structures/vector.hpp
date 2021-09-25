#ifndef _VECTOR_HEADER_
#define _VECTOR_HEADER_

#include <initializer_list>

namespace ds{
    typedef std::size_t size_type;

    template <class T>
    class vector{
    public:
        class vector_iterator{
            // using value_type = T;
            // using pointer    = T*;      
            // using reference  = T&;      
            // using difference_type = std::ptrdiff_t;     
            // using iterator_category = std::random_access_iterator_tag;      
            
        public:
            vector_iterator():ptr(nullptr),position(0){};
            vector_iterator(vector<T>& v, size_type pos=-1){
                this->ptr = &v;

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

            const T& operator*(){
                return (*ptr)[position];
            }

            //FIXME
            vector_iterator& operator++(){
                ++position;
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

            friend bool operator==(const vector_iterator& lh, const vector_iterator& rh){
                //FIXME not checking pointers here, assuming same container..

                return lh.position == rh.position;
            }

            friend bool operator!=(const vector_iterator& lh, const vector_iterator& rh){
                return !operator==(lh, rh);
            }

            //operator=

        private:
            vector<T>* ptr;
            size_type position;
        };
            
    public:
        vector(){
            size_type size = 16;
            //FIXME
            this->start = new T[size];
            this->capacity = size;
            this->size = 0;
        }
        vector(std::initializer_list<T> values){
            auto size = values.size();
            this->capacity = size;
            this->start = new T[size];
            this->size = 0;

            for(auto it = values.begin();it!= values.end();++it){
                this->start[this->size] = *it;
                ++this->size;
            }
        }
        ~vector(){
            delete[] this->start;
        }
        vector(const vector<T>& other){
            //FIXME
            this->start = new T[other.capacity];
            this->size = 0;
            this->capacity = other.capacity;

            for(size_type i=0;i<this->size;++i){
                (*this)[i] = other[i];
                ++this->size;
            }
        }
        vector(int size){
           this->start = new T[size];
           this->capacity = size;
           this->size = 0;
        }   
        
    public:
        const size_type get_size()const{
            return this->size;
        }
        void append(const T& elem);

        const T& operator[](std::size_t i)const{
            if(i < 0 || i >= this->size){
                throw std::out_of_range("index out of range");
            }

            return this->start[i];
        }
        T& operator[](std::size_t i){
            if(i < 0 || i >= this->size){
                throw std::out_of_range("index out of range");
            }

            return this->start[i];
        }

    public:
        //FIXME should prob be const, but this becomes const and 
        //I cant use in iterator constructor
        vector_iterator begin(){
            vector_iterator temp(*this, 0);
            return temp;
        }
        vector_iterator end(){
            vector_iterator temp(*this, size-1);
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