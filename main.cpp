#include "masiv.h"

int main()
{
	masiv<int> arr{ 1, 2, 3, 4, 5 };
	
	arr.print();

	arr.push_back(6);

	arr.print();
	
	return 0;
}