#include <iostream>
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "rev_iterator.hpp"
#include "utils.hpp"
#include <memory>
#include <exception>
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
        typedef size_t size_type;
        

    private:
        pointer _vector;
        allocator_type _alloc;
        size_type _size;
        size_type _capacity;
        iterator _begin;
        
    
    public:
        vector (const allocator_type& alloc = allocator_type()):_vector(0),_alloc(alloc),_size(0),_capacity(0){}
        vector (size_type n, const value_type& val = value_type(),const allocator_type& alloc = allocator_type()){
            _alloc = alloc;
            _vector = _alloc.allocate(n);
            _size = n;
            _capacity = n;
            for (size_t i = 0; i < n; i++)
                _alloc.construct(_vector + i, val);
        }
        vector(const vector& x)

        {
            _vector = x._vector;
            _alloc = x._alloc;
            _size = x._size;
            _capacity = x._capacity;
        }
        ~vector(){

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
        vector operator=(const vector& x) {
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
        void push_back(const T &value)
      {
         if (_size == 0)
         {
            _capacity++;
            _vector = _alloc.allocate(_capacity);
         }
         if (_size == _capacity)
         {
            reserve(_capacity*2);
         }
         construct(value);
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
        reference front() 
        {
            return (*(this->_vector));
        } 
        const_reference front() const
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
      reference back()
      {
         return (*(this->_vector + _size - 1));
      }
      const_reference back() const
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
     void reserve (size_type n)
     {
        if (n > this->max_size())
            throw(std::length_error("vector::reserve"));
         else if (n > _capacity)
         {
            pointer tmp = _alloc.allocate(n);
         
            if (_capacity > 0){
               for (size_type i = 0; i < _size; i++)
                  _alloc.construct(tmp + i, *(_vector + i));
               _alloc.deallocate(_vector, _capacity);
            }
            _vector = tmp;
            _capacity = n;
         }
     }
    void resize(size_type n, value_type val = value_type())
      {
         if (n < _size)
         {
            for (size_t i = n; i < _size; i++)
               this->pop_back();
         }
         else
         {
            if (n >= _capacity)
               this->reserve(n);
            for (size_t i = _size; i < n; i++)
               _alloc.construct(_vector + i, val);
         }
         _size = n;
      }
     void pop_back()
     {
        _alloc.destroy(_vector + _size);
        _size--;
     }
     iterator erase(iterator position)
      {
         for (size_type i = position - this->begin(); i < _size - 1; i++)
            _vector[i] = _vector[i + 1];
         _size--;
         _alloc.destroy(_vector + _size);
         return (position);
      }

      iterator erase(iterator first, iterator last)
      {
         size_type n = last - first;
         while (n-- > 0)
            this->erase(first);
         return (first);
      }


};
   template <class T, class Alloc>
   bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
   {
      if (lhs.size() != rhs.size())
         return false;
      typename ft::vector<T>::const_iterator first1 = lhs.begin();
      typename ft::vector<T>::const_iterator first2 = rhs.begin();
      while (first1 != lhs.end())
      {
         if (first2 == rhs.end() || *first1 != *first2)
            return false;
         ++first1;
         ++first2;
      }
      return true;
   }
    template <class T, class Alloc>
   bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs < rhs); }

   template <class T, class Alloc>
   bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs < rhs) || lhs == rhs; }

   template <class T, class Alloc>
   bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return (lhs < rhs) || lhs == rhs; }

   template <class T, class Alloc>
   bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs == rhs); }

    template <class T, class Alloc>
   bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
   {
      return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
      ;
   }
}