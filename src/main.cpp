#include "undecline.h"

int main()
{
	Undecliner u;
	u.loadEndings();
	cout << u.undecline("rerum") << "\n";
	return 0;
}
