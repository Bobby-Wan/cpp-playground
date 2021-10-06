#ifndef _LIST_HEADER_INCLUDED_
#define _LIST_HEADER_INCLUDED_
#include <iostream>

namespace ds{
    template <class T>
    class list{

        struct node{
            node(const T& data):data(data),ptr_next(nullptr){}
            T data;
            node* ptr_next;
        };

    public:
        class list_iterator{
            public:
                list_iterator(node*const n){
                    ptr = n;
                }

                friend bool operator==(const list_iterator& lh, const list_iterator& rh){
                    //FIXME: no check for same container

                    return lh.ptr == rh.ptr;
                }

                friend bool operator!=(const list_iterator& lh, const list_iterator& rh){
                    //FIXME: no check for same container

                    return !(operator==(lh, rh));
                }

                list_iterator& operator++(){
                    std::cout<<"++\n";
                    if(ptr){
                        ptr = ptr->ptr_next;
                    }

                    return *this;
                }

                list_iterator operator++(int){
                    list_iterator temp(ptr);
                    if(ptr && ptr->ptr_next){
                        ptr = ptr->ptr_next;
                    }

                    return temp;
                }

                T& operator*(){
                    return ptr->data;
                }

            private:
                node* ptr;
        };


    public:
        list():ptr_end_node(nullptr), ptr_start_node(nullptr){}
        ~list(){
            node* ptr_current_node = ptr_start_node;
            
            //FIXME
            while(ptr_current_node){
                node* temp = ptr_current_node->ptr_next;
                delete ptr_current_node;
                ptr_current_node = temp;
            }
        }
        list& operator=(const list& other){
            for(auto it = other.begin(); it != other.end(); ++it){
                this->append(*it);
            }
        }
        //TEST
        bool contains(const T& data) const{
            node* ptr_current_node = ptr_start_node;

            while(ptr_current_node){
                if(ptr_current_node->data == data){
                    return true;
                }

                ptr_current_node = ptr_current_node->ptr_next;
            }

            return false;
        }
        //deletes a single occurence of a node with data
        void remove(const T& data){
            node* ptr_current_node = ptr_start_node;
            if(ptr_current_node && ptr_current_node->data == data){
                ptr_start_node = ptr_current_node->ptr_next;
                if(ptr_start_node == nullptr){
                    ptr_end_node = nullptr;
                }
            }

            //TEST this
            while(ptr_current_node && ptr_current_node->ptr_next){
                if(ptr_current_node->ptr_next->data == data){
                    node* temp = ptr_current_node->ptr_next;
                    ptr_current_node->ptr_next = ptr_current_node->ptr_next->ptr_next;

                    if(temp == ptr_end_node){
                        ptr_end_node = nullptr;
                    }
                    
                    delete temp;
                }
            }
        }
        void append(const T& data){
            if(is_empty()){
                //check allocation
                ptr_start_node = new node(data);
                ptr_end_node = ptr_start_node;

                return;
            }

            //FIXME: not sure about this check
            if(ptr_end_node->ptr_next != nullptr){
                throw;
            }

            ptr_end_node->ptr_next = new node(data);
            ptr_end_node = ptr_end_node->ptr_next;
        }

        list_iterator begin()const{
            return list_iterator(ptr_start_node);
        }

        list_iterator end()const{
            return list_iterator(nullptr);
            // return list_iterator(ptr_end_node);
        }

    public:
        bool is_empty()const{
            return ptr_start_node == nullptr && ptr_end_node == nullptr;
        }

    private:
        node* ptr_start_node;
        node* ptr_end_node;
    };
}


#endif //_LIST_HEADER_INCLUDED_