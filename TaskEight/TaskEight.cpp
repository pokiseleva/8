#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>


using namespace std;

class Multinomial
{
public:
	int Coeff(int power)
	{
		if (coeff.count(power) > 0)
		{
			return coeff[power];
		}
		return 0;
	}

	int MaxPower()
	{
		return max_power;
	}

	Multinomial(map<int, int> coeff, int max_power)
	{
		this->coeff = coeff;
		this->max_power = max_power;
	}

	Multinomial() {};
private:
	map<int, int> coeff;
	int max_power;
};

Multinomial operator * (Multinomial& lhs, Multinomial& rhs)
{
	int new_max = lhs.MaxPower() + rhs.MaxPower();
	int max_power = max(lhs.MaxPower(), rhs.MaxPower());
	map<int, int> temp_coef;
	for (int i = 0; i <= new_max; i++)
		temp_coef[i] = 0;

	if (lhs.MaxPower() > rhs.MaxPower())
	{
		for (int i = 0; i <= lhs.MaxPower(); ++i)
		{
			for (int j = 0; j <= rhs.MaxPower(); ++j)
				temp_coef[i + j] += lhs.Coeff(i) * rhs.Coeff(j);
		}
		Multinomial multi(temp_coef, new_max);
		return multi;
	}
	else
	{
		for (int i = 0; i <= rhs.MaxPower(); i++)
		{
			for (int j = 0; j <= lhs.MaxPower(); j++)
			{
				temp_coef[i + j] += lhs.Coeff(j) * rhs.Coeff(i);
			}
		}
		Multinomial multi(temp_coef, new_max);
		return multi;
	}
}

Multinomial operator + (Multinomial& lhs, Multinomial& rhs)
{
	int max_power = max(lhs.MaxPower(), rhs.MaxPower());
	map<int, int> temp_coef_by_power;
	for (int i = 0; i <= max_power; ++i)
		temp_coef_by_power[i] = lhs.Coeff(i) + rhs.Coeff(i);
	Multinomial multi(temp_coef_by_power, max_power);
	return multi;
}

Multinomial operator - (Multinomial& lhs, Multinomial& rhs)
{
	int max_power = max(lhs.MaxPower(), rhs.MaxPower());
	map<int, int> temp_coef_by_power;
	for (int i = 0; i <= max_power; ++i)
		temp_coef_by_power[i] = lhs.Coeff(i) - rhs.Coeff(i);
	bool f = false;
	for (int i = max_power; i >= 0; --i)
	{
		if (temp_coef_by_power[i] != 0) {
			f = true;
			max_power = i;
			break;
		}
	}
	if (!f)
	{
		max_power = 0;
	}
	Multinomial multi_to_return(temp_coef_by_power, max_power);
	return multi_to_return;
}

ostream& operator << (ostream& stream, Multinomial& multinominal)
{
	for (int i = multinominal.MaxPower(); i >= 0; --i)
	{
		if (multinominal.Coeff(i) != 0)
		{
			if (multinominal.Coeff(i) > 0)
			{
				stream << "+";
			}
			if (i == 0 )
				stream << multinominal.Coeff(i);
			else stream << multinominal.Coeff(i) << "x^" << i << " ";
		}
	}
	return stream;
}

vector<Multinomial> Fibonacci(int& n)
{
	vector<Multinomial> vector_multinomials(n);

	map<int, int> temp_map = { {0, 0} };
	Multinomial temp_multinomial(temp_map, 0);
	vector_multinomials[0] = temp_multinomial;

	map<int, int> temp_map1 = { {0, 1} };
	Multinomial temp_multinomial1(temp_map1, 0);
	vector_multinomials[1] = temp_multinomial1;

	map<int, int> temp_map2 = { {1, 1} };
	Multinomial x(temp_map2, 1);

	for (int i = 2; i < n; ++i)
	{
		vector_multinomials[i] = vector_multinomials[i - 1] * x;
		vector_multinomials[i] = vector_multinomials[i] + vector_multinomials[i - 2];
	}
	return vector_multinomials;
}

int main()
{
	int n = 10;
	vector<Multinomial> vector_multinomial = Fibonacci(n);
	int number;
	cin >> number;
	if (number!=0) cout << vector_multinomial[number];
	else cout << "0";

	return 0;
}