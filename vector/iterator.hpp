#include <iostream>
#include "iterator_traits.hpp"



namespace ft{
template <class iter>
class access_random_iterator{
    public:
        typedef std::ptrdiff_t difference_type;
        typedef typename iterator_traits<iter *>::value_type value_type;
        typedef iter* pointer;
        // typedef iter value_type;
        typedef iter& reference;
    private:
        pointer _ptr;

    public:
        access_random_iterator() :_ptr(0){ }
        access_random_iterator(pointer ptr):_ptr(ptr){
            // std::cout << " PTR" << std::endl;
        }
        pointer base() const
        {
            return _ptr;
        }
        template<class it>
        access_random_iterator( access_random_iterator<it> const &x)
        {
            _ptr = x.base();
        }
        // template<class it>
        // access_random_iterator& operator=( access_random_iterator<it> const &x)
        access_random_iterator& operator=( access_random_iterator const &x)
        {
            // std::cout << " ASSIGN" << std::endl;
            _ptr = x.base();
            return (*this);
        }
        reference operator*() {
            return *_ptr;
        }
        access_random_iterator operator-(difference_type n){
            return access_random_iterator(_ptr -n);
        }
        access_random_iterator operator+(difference_type n){
            return access_random_iterator(_ptr + n);
        }
        // access_random_iterator operator+(int)
        // {
        //     return access_random_iterator(_ptr +1);
        // }
         access_random_iterator& operator++() {
        ++_ptr;
        return *this;
        }
        access_random_iterator operator++(int) {
            access_random_iterator tmp(*this);
            ++_ptr;
            return tmp;
        }
        access_random_iterator operator--(){         
            return  (--_ptr);
        }
        access_random_iterator operator--(int) {
            access_random_iterator tmp(*this);
            --_ptr;
            return tmp;
        }
        bool operator!=(const access_random_iterator& it) const {
            return _ptr != it._ptr;
        }
        bool operator==(const access_random_iterator& it) const {
            return _ptr == it._ptr;
        }
        bool operator>(const access_random_iterator& it) const {
            return _ptr > it._ptr;
        }
        bool operator>=(const access_random_iterator& it) const {
            return _ptr >= it._ptr;
        }
        bool operator<(const access_random_iterator& it) const {
            return _ptr < it._ptr;
        }
        bool operator<=(const access_random_iterator& it) const {
            return _ptr <= it._ptr;
        }
        access_random_iterator operator+=(int)
        {
            _ptr += 1;
            return access_random_iterator(_ptr);
        }
        access_random_iterator operator-=(int)
        {
            _ptr -= 1;
            return access_random_iterator(_ptr);
        }
        pointer operator->() {
            return _ptr;
        }
        reference& operator[](size_t const & n) {
            return *(this->_ptr + n);
        }
        //
        friend access_random_iterator operator+(difference_type i, access_random_iterator it)
        {
            return (it._ptr + i);
        }
        friend access_random_iterator operator-(difference_type i, access_random_iterator it)
        {
            return (it._ptr - i);
        }
        difference_type operator-(access_random_iterator const &other) const
        {
            return (_ptr - other._ptr);
        }
};
struct random_access_iterator_tag {};


        

}