#include <boost/lambda/lambda.hpp>
#include <list>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <iterator>

template <typename _base_iterator>
class sorted_view_iterator 
	: public std::iterator<typename std::iterator_traits<_base_iterator>::iterator_category,
						   typename std::iterator_traits<_base_iterator>::value_type,
						   typename std::iterator_traits<_base_iterator>::difference_type,
						   typename std::iterator_traits<_base_iterator>::pointer,
						   typename std::iterator_traits<_base_iterator>::reference>
{
protected:
	_base_iterator current;

public:
	typedef _base_iterator							iterator_type;

	sorted_view_iterator() : current() {}

	explicit
	sorted_view_iterator(iterator_type __x) : current(__x) {}

	template<typename _Iter>
	sorted_view_iterator(const sorted_view_iterator<_Iter>& __i)
		: current(__i.base()) {}

	iterator_type
	base() const
	{  return current;  }

	typename value_type::reference operator*() const
	{
		return **current;
	}

	sorted_view_iterator&
	operator+=(difference_type __n)
	{
		current += __n;
		return *this;
	}
};

template<typename _iterator>
  inline typename sorted_view_iterator<_iterator>
  operator+(typename sorted_view_iterator<_iterator>::difference_type __n,
			const sorted_view_iterator<_iterator>& __x)
  {  return sorted_view_iterator<_iterator>(__x.base() + __n); }

template<typename _iterator>
  inline typename sorted_view_iterator<_iterator>
  operator-(const sorted_view_iterator<_iterator>& __x, 
			typename sorted_view_iterator<_iterator>::difference_type __n)
  {  return sorted_view_iterator<_iterator>(__x.base() - __n); }

template<typename _iterator>
  inline typename sorted_view_iterator<_iterator>
  operator-(const sorted_view_iterator<_iterator>& __x, 
			const sorted_view_iterator<_iterator>& __y)
  {  return sorted_view_iterator<_iterator>(__x.base() - __y.base()); }

template <typename _Iterator>
class sorted_view
{
public:
	typedef typename std::vector<_Iterator> internal_storage_type;
	typedef typename sorted_view_iterator<typename internal_storage_type::iterator> iterator;
	typedef typename sorted_view_iterator<typename internal_storage_type::const_iterator> const_iterator;

	sorted_view(_Iterator begin, _Iterator end)
	{
		for_each(begin, end, [&]{ _storage.push_back(*_1)} );
	}

	const_iterator begin() const { return _storage.begin(); }
	const_iterator end() const { return _storage.end(); }

private:
	internal_storage_type _storage;
};

const std::list<int> get_const_list() {
	std::list<int> li;

	li.push_back(3);
	li.push_back(0);
	li.push_back(1);
	li.push_back(4);
	li.push_back(2);
}

int main()
{
	using namespace std;
	using namespace boost::lambda;

	const list<int> li(get_const_list());

	for_each(li.begin(), li.end(), cout << _1 << " ");
	cout << endl;

	typedef sorted_view<list<int>::const_iterator> sv_t; // (1)

	sv_t sv1(li.begin(), li.end());
	for_each(sv1.begin(), sv1.end(), cout << _1 << " "); // (2)
	cout << endl;

	sv_t sv2(li.begin(), li.end(), greater<int>()); // (3)
	for_each(sv2.begin(), sv2.end(), cout << _1 << " ");
	cout << endl;

	sv_t::const_iterator i = sv2.begin();
	i += 2; // (4)
	cout << *i << endl;
	cout << i - sv2.begin() << endl;

	// output
	// 3 0 1 4 2
	// 0 1 2 3 4
	// 4 3 2 1 0
	// 2 
	// 2

	return 0;
}
