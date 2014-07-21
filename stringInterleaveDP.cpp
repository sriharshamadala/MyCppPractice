// Perfectly working isInterleave program. Used recursion. There seems to be overlapping subproblems. Use of DP is recommended. store the result of isInterleave(a(i), b(j), c) so that we dont solve the same problem again using recursion.
#include <iostream>

using namespace std;

bool isInterleave(const char* a, const char*b, const char* c)
{
	if ((*a == 0) && (*b==0) && (*c==0))
		return true;
	else if ( *c==0 )
		return false;
	else if ((*c==*a) && (*c != *b))
			return isInterleave(a+1, b, c+1);
	else if ((*c!=*a) && (*c == *b))
			return isInterleave(a, b+1, c+1);
	else if ((*c==*a) && (*c == *b))
			return (isInterleave(a+1, b, c+1) || isInterleave(a,b+1,c+1)) ;
	else
			return isInterleave(a,b,c+1);
}

int main()
{
	string a="pqrs";
	string b="tuvw";
	string c="ptqurvswx";
	if (isInterleave(a.c_str(), b.c_str(), c.c_str()))
		cout << c << " is an interleave of " << a << ", " << b << endl;
	else
		cout <<  c << " is an not interleave of " << a << ", " << b << endl;
	return 0;
}
