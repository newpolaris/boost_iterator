#include <boost/lambda/lambda.hpp>
#include <list>
#include <iostream>

int main()
{
	using namespace std;
	using namespace boost::lambda;

	list<int> li;
	li.push_back(3);
	li.push_back(0);
	li.push_back(1);
	li.push_back(4);
	li.push_back(2);

	for_each(li.begin(), li.end(), cout << _1 << " ");
	cout << endl;

	typedef sorted_view<list<int>::iterator> sv_t; // (1)

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