#include "iterator_traits.hpp"

namespace ft{
    template <class Iter>
    class reverse_iterator{
        // typedef typename iterator_traits<T*>::value_type value_type;
        // typedef ptrdiff_t difference_type;
        // typedef T*        pointer;
        // typedef T&        reference;
        // typedef std::random_access_iterator_tag iterator_category;
        // typedef value_type iterator_type;
        public:
            typedef Iter iterator_type;
            typedef typename iterator_type::value_type value_type;
            typedef typename iterator_type::pointer pointer;
            typedef typename iterator_type::reference reference;
            typedef typename iterator_type::difference_type difference_type;

        private:
            iterator_type p;
        public:
            reverse_iterator() : p() {}
            reverse_iterator(iterator_type _p) : p(_p) {}
            reverse_iterator( reverse_iterator const &it)
            {
                p = it.base();
            }
            reverse_iterator& operator=(const reverse_iterator& it) {
              p = it.p;
              return *this;
            }
            iterator_type base() const
            {
                return this->p;
            }
            template <class Iter1>
            reverse_iterator (const reverse_iterator<Iter1>& rev_it)
            {
                p = rev_it.base();
            }
            reference operator*() const
            {
                iterator_type a = this->base();
                return *(--a);
            }
            reverse_iterator& operator++() {
                --p;
                return *this;
            }
            reverse_iterator operator++(int) {
                reverse_iterator tmp(*this);
                --p;
                return tmp;
            }
            reverse_iterator& operator--() {
                ++p;
                return *this;
            }
            reverse_iterator operator--(int) {
                reverse_iterator tmp(*this);
                ++p;
                return tmp;
            }
            reverse_iterator& operator+=( difference_type n )
            {
                p -= n;
                return *this;
            }
            reverse_iterator& operator-=( difference_type n )
            {
                p += n;
                return *this;
            }
            reverse_iterator operator-( difference_type n ) const
            {
                return (this->base() + n);
            }
            reverse_iterator operator+( difference_type n ) const
            {
                return (this->base() - n);
            }
            pointer operator->() const
            {
                return &operator*();
            }
            reference operator[]( difference_type n )
            {
                return (this->base()[-n-1]);
            }

    };
    template< class Iterator1, class Iterator2 >
    bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,const ft::reverse_iterator<Iterator2>& rhs )
        {
            return (lhs.base() != rhs.base());
        }
    template< class Iterator1, class Iterator2 >
    bool operator==( const ft::reverse_iterator<Iterator1>& lhs,const ft::reverse_iterator<Iterator2>& rhs )
        {
            return (lhs.base() == rhs.base());
        }
    template< class Iterator1, class Iterator2 >
    bool operator>( const ft::reverse_iterator<Iterator1>& lhs,const ft::reverse_iterator<Iterator2>& rhs )
        {
            return (lhs.base() < rhs.base());
        }
    template< class Iterator1, class Iterator2 >
    bool operator<( const ft::reverse_iterator<Iterator1>& lhs,const ft::reverse_iterator<Iterator2>& rhs )
        {
            return (lhs.base() > rhs.base());
        }
    template< class Iterator1, class Iterator2 >
    bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,const ft::reverse_iterator<Iterator2>& rhs )
        {
            return (lhs.base() <= rhs.base());
        }
        template< class Iterator1, class Iterator2 >
    bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,const ft::reverse_iterator<Iterator2>& rhs )
        {
            return (lhs.base() >= rhs.base());
        }

        template< class Iterator1 >
        typename ft::reverse_iterator<Iterator1>::difference_type operator-( const ft::reverse_iterator<Iterator1>& lhs,const ft::reverse_iterator<Iterator1>& rhs )
        {
            return (rhs.base() - lhs.base());
        }
       template< class Iter >
       reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n,const reverse_iterator<Iter>& it )
        {
            return (it.base() -n);
        }


}