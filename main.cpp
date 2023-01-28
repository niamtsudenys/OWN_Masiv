#include "masiv.h"

int main()
{
	masiv <int> arr{ 1,2,3,4,5 };

	arr.print();

	arr.delete_first();

	arr.print();

	return 0;
}