#include <iostream>
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "rev_iterator.hpp"
#include "utils.hpp"
namespace ft {
template < class T, class Alloc = std::allocator<T> > class vector{
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename ft::access_random_iterator<value_type> iterator;
        typedef typename ft::access_random_iterator<const value_type> const_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef  difference_type size_type;

    private:
        pointer _vector;
        allocator_type _alloc;
        size_type _size;
        size_type _capacity;
        iterator _begin;
        
    
    public:
        vector (const allocator_type& alloc = allocator_type()):_vector(0),_alloc(alloc),_size(0),_capacity(0){}
        vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type()){
            _vector = _alloc.allocate(n);
            _size = n;
            _capacity = n;
            for (size_t i = 0; i < n; i++)
                _vector[i] = val;
        }
        vector(const vector& x)

        {
            _vector = x._vector;
            _alloc = x._alloc;
            _size = x._size;
            _capacity = x._capacity;
        }
        void construct(const T &value)
      {
         _alloc.construct(_vector + _size, value);
         _size++;
      }
        template <class InputIterator>
      // dont use is_same
      vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
             typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type * = 0)
          : _alloc(alloc), _size(last - first), _capacity(last - first)
      {
         _vector = _alloc.allocate(last - first);
         for (size_t i = 0; i < _size; i++)
            _alloc.construct(_vector + i, *(first + i));
      }
        reference operator[](size_type n)
        {
            return (*(_vector + n));
        }
        const_reference operator[](size_type n) const
        {
            return (*(_vector + n));
        }
        vector operator=(const vector& x){
            _vector = x._vector;
            _size = x._size;
            _capacity = x._capacity;
            this->_begin = x._begin;
            // this->_end = x._end;
            return (*this);
        }
        iterator begin()
        {
            return iterator(_vector);
        }
        const_iterator begin() const
        {
            return const_iterator(_vector);
        }
        iterator end()
        {
            return iterator(_vector + _size);
        }
        const_iterator end() const
        {
            return const_iterator(_vector + _size);
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(this->end());
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(this->end());
        } 
        reverse_iterator rend()
        {
            return reverse_iterator(this->begin());
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(this->begin());
        }

        size_type size() const{
            return _size;
        }
        size_type max_size() const{
            return _alloc.max_size();
        }
        void push_back (const value_type& val){
            if(_size == 0)
            {
                _vector = _alloc.allocate(1);
                _capacity++;
            }
            if (_size == _capacity)
            {
                _capacity *= 2;
                _alloc.allocate(_capacity);
            }
            // _alloc.allocate(_size +1);
            _vector[_size] = val;
            _size++;
        }
        size_type capacity() const{
            return this->_capacity;
        }
        bool empty() const{
            return _size == 0;
        }
        void clear(){
            for(size_type i= 0;i< _size;i++)
                _alloc.destroy(_vector + i);
            _size = 0;
        }
        reference front() const
        {
            return (*(this->_vector));
        }
        const_reference front()
        {
            return (*(this->_vector));
        }
        reference at(size_type n)
      {
         if (n > size())
            throw std::out_of_range("vector");
         return (*(this->_vector + n));
      }
      const_reference at(size_type n) const
      {
         if (n > size())
            throw std::out_of_range("vector");
         return (*(this->_vector + n));
      }
      reference back() const
      {
         return (*(this->_vector + _size - 1));
      }
      const_reference back()
      {
         return (*(this->_vector + _size - 1));
      }
      void swap(vector &x)
      {
         vector c(*this);
         *this = x;
         x = c;
      }
      allocator_type get_allocator() const
      {
         return _alloc;
      }
      template <class InputIterator>
      typename ft::enable_if<!        ft::is_integral<InputIterator>::value               , void>::type assign(InputIterator first, InputIterator last)
      {
         if (_capacity != 0)
         {
            _alloc.deallocate(_vector, _capacity);
            _size = 0;
         }
         size_t new_vector_size = last - first;
         if (new_vector_size >= _capacity)
            _capacity = new_vector_size;
         _vector = _alloc.allocate(_capacity);
         for (size_t i = 0; i < new_vector_size; i++)
         {
            _alloc.construct(_vector + _size, *(first + i));
            _size++;
         }
      }

      void assign(size_type n, const value_type &val)
      {
         if (_capacity != 0)
         {
            _alloc.deallocate(_vector, _capacity);
            _size = 0;
         }
         if (n >= _capacity)
            _capacity = n;
         _vector = _alloc.allocate(_capacity);
         for (size_t i = 0; i < n; i++)
            construct(val);
      }

};
template <class T, class Alloc>
   bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
   {
      typename vector<T, Alloc>::const_iterator first1 = lhs.begin();
      typename vector<T, Alloc>::const_iterator last1 = lhs.end();
      typename vector<T, Alloc>::const_iterator first2 = rhs.begin();
      typename vector<T, Alloc>::const_iterator last2 = rhs.end();

      while (first1 != last1)
      {
         if (!(*first1 == *first2))
            return true;
         ++first1;
         ++first2;
      }
      return false;
   }
    // template <class T, class Alloc>
    // bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs == rhs); }
}