#include "undecline.h"

int main()
{
	Undecliner u;
	u.loadEndings();
	cout << u.undecline("arboribus") << "\n";
	return 0;
}
