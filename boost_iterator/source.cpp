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

	return 0;
}