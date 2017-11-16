// An Almost Perfect Program
// Bradley Marques
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
// Other include files?
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::sort;
using std::vector;

bool IsSemiPerfect(int, int&, vector<int>&);
int FindProperFactors(int, int&, vector<int>&);

void main() {
	ifstream fin("semiperfect.in");
	if (fin.is_open()) {
		ofstream fout("semiperfect.out");
		int number_to_read = 0;
		fin >> number_to_read;
		while (number_to_read > 0) {
			int sum;
			vector<int> proper_factors;
			int number_of_factors = FindProperFactors(number_to_read, sum, proper_factors);
			if (sum < number_to_read) {
				cout << number_to_read << ":" << "NO" << endl;
				fout << number_to_read << ":" << "NO" << endl;
			}
			else if (sum == number_to_read) {
				cout << number_to_read << ":" << "YES" << endl;
				fout << number_to_read << ":" << "YES" << endl;
			}
			else if (number_to_read % (sum - number_to_read) == 0) {
				cout << number_to_read << ":" << "YES" << endl;
				fout << number_to_read << ":" << "YES" << endl;
			}
			else if ((number_to_read / 6) + 2 * (number_to_read / 6) + 3 * (number_to_read / 6) == number_to_read) {
				cout << number_to_read << ":" << "YES" << endl;
				fout << number_to_read << ":" << "YES" << endl;
			}
			else if (IsSemiPerfect(number_to_read, sum, proper_factors)) {
				cout << number_to_read << ":" << "YES" << endl;
				fout << number_to_read << ":" << "YES" << endl;
			}
			else {
				cout << number_to_read << ":" << "NO" << endl;
				fout << number_to_read << ":" << "NO" << endl;
			}

			fin >> number_to_read;
		}

		fout.close();
		fin.close();
	}
	else {
		cout << "Input file not found." << endl;
	}
}

bool IsSemiPerfect(int n, int &sum, vector<int>&proper_factors)
{
	// 1. Sort the properFactors in ascending order
	sort(proper_factors.begin(), proper_factors.end());
	// 2. We'll need to know the number of proper factors
	int number_of_proper_factors = proper_factors.size();

	int columns = 0;
	// 3. Build a 2D "array" of bool  (Actually easier to use 2D vector)
	vector < vector<bool> > A(number_of_proper_factors + 1, vector<bool>(n + 1, false));
	// The rows correspond to the different factors in properFactors
	// The columns correspond to particular sum  (0, 1, 2, 3, ..., n)

	// In this function we set an entry: A[row][col] to true if there
	// is a subset of the first 'row' properFactors that will sum to 
	// the number, n.  The objective is to find the boolean that should
	// be stored at A[numProperFactors][n].

	// 4. Build the array top-to-bottom and then left-to-right.
	// Since the empty set adds up to 0, the first column should be all true.
	// For all of the remaining columns, if an entry is ever determined
	// to be true, then ALL entries under that one are also true.
	for (int index = 0; index < A.size(); index++) {
		A[index][columns] = true;
	}
	for (int j = 1; j <= n; j++) {
		for (int i = 0; i <= number_of_proper_factors; i++) {
			if (i > 0) {
				int columns_minus_proper_factors_at_index = j - proper_factors[i - 1];
				if (A[i - 1][j] == true) {
					A[i][j] = true;
				}
				else if (columns_minus_proper_factors_at_index >= 0) {
					A[i][j] = A[i - 1][columns_minus_proper_factors_at_index];
				}
			}
		}
	}



	// That leaves the problem of determining whether or not A[row][col]
	// should be true or false, if all of the entries above it in the 
	// same column are false.

	return A[number_of_proper_factors][n];
}

int FindProperFactors(int n, int &sum, vector<int>&proper_factors)
{
	int number_of_proper_factors = 0;
	sum = 0;
	proper_factors.clear();

	if (n >= 2) {
		// The integer 1 is always a proper factor if n >= 2
		proper_factors.push_back(1);
		sum = 1;
		number_of_proper_factors = 1;

		for (int i = 2; i*i <= n; i++) {
			if (n % i == 0) {
				sum += i;
				number_of_proper_factors++;
				proper_factors.push_back(i);

				int factor2 = n / i;
				if (factor2 != i) {
					sum += factor2;
					number_of_proper_factors++;
					proper_factors.push_back(factor2);
				}
			}
		}
	}
	return number_of_proper_factors;
}
