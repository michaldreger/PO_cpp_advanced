#include <iostream>
#include <fstream>

using namespace std;
const int N = 100;

class VektorNd {
	double* _liczby; //pole ze wskaünikiem liczb
	int _wymiar; //wymiar wektora
public:
	VektorNd() : _liczby(nullptr), _wymiar(0) {} //konstruktor bezparametrowy

	VektorNd(const double liczby[], int wymiar) { //konstruktor
		_liczby = new double[wymiar];
		_wymiar = wymiar;
		for (int i = 0; i < _wymiar; i++)
			_liczby[i] = liczby[i];
	}

	~VektorNd() { //destruktor
		//cout << "zwalniam pamiec pod adresem: " << this << endl;
		delete[] _liczby;
	}

	VektorNd(const VektorNd& oryginal) { //konstruktor kopiujπcy
		_liczby = new double[oryginal._wymiar];
		_wymiar = oryginal._wymiar;
		for (int i = 0; i < _wymiar; i++)
			_liczby[i] = oryginal._liczby[i];
	}

	VektorNd& operator=(const VektorNd& right) { //implementacja operatora przypisania
		if (_wymiar != right._wymiar) { //gdy zgodne wymiary nie potrzeba realokowaÊ pamiÍci

				delete[] _liczby;
			_liczby = new double[right._wymiar]; //alokacja pamiÍci dla nowego wymiaru

				_wymiar = right._wymiar;
		}
		for (int i = 0; i < _wymiar; i++)
			_liczby[i] = right._liczby[i];
		return *this;
	}
	void getCoefs(double liczby[]) {
		for (int i = 0; i < _wymiar; i++)
			liczby[i] = _liczby[i];
	}
	void setCoef(double wartosc, int index) {
		_liczby[index] = wartosc;
	}

	double getCoef(int index) {
		return _liczby[index];
	}
	int getDim() {
		return _wymiar;
	}
	void wypisz(ostream& out = cout) {
		out << "|-------------------------BEGIN------------------------------ | "<<endl;
			out << "Jestem wektorem pod adresem: " << this << endl;
		out << "MÛj wymiar to: " << _wymiar << endl;
		out << "A elementy:" << endl;
		for (int i = 0; i < _wymiar; i++)
			out << "[" << i << "] = \t" << _liczby[i] << endl;
		out << "|--------------------------END------------------------------- | "<<endl;
	}
	friend ostream& operator<<(ostream& left, VektorNd& right);
	friend istream& operator>>(istream& in, VektorNd& vec);
};

ostream& operator<<(ostream& left, VektorNd& right) {
	right.wypisz(left);
	return left;
}
istream& operator>>(istream& in, VektorNd& vec) {
	double value;
	for (int i = 0; i < vec._wymiar; i++) {
		in >> value;
		vec.setCoef(value, i);
	}
	return in;
}



class VectorOfVectors {
    VektorNd vektory[N];
    int size;

public:
    VectorOfVectors() : size(0) {} // konstruktor bezparametrowy

    VectorOfVectors(const VektorNd vecs[], int s) : size(s) {
        for (int i = 0; i < size; i++)
            vektory[i] = vecs[i];
    }

    ~VectorOfVectors() {
        //for (int i = 0; i < size; i++)
            //cout << "Zwalniam pamiec z vektora o adresie: " << &vektory[i] << endl;
    }

    VectorOfVectors(const VectorOfVectors& other) : size(other.size) {
        for (int i = 0; i < size; i++)
            vektory[i] = other.vektory[i];
    }

    VectorOfVectors& operator=(const VectorOfVectors& right) {
        if (this != &right) {
            size = right.size;
            for (int i = 0; i < size; i++)
                vektory[i] = right.vektory[i];
        }
        return *this;
    }

	void wypisz(ostream& out = cout) {
		out << "|-------------------------BEGIN------------------------------ | " << endl;
		out << "Jestem tablica wektorow pod adresem: " << this << endl;
		out << "Moja wielkosc to: " << size << endl;
		out << "A wektory:" << endl;
		for (int i = 0; i < size; i++)
			out << "Vektor[" << i << "]:\n" << vektory[i];
		out << "|--------------------------END------------------------------- | " << endl;
	}

    friend ostream& operator<<(ostream& left, VectorOfVectors& right);
	friend istream& operator>>(istream& in, VectorOfVectors& vecOfVecs);
};

ostream& operator<<(ostream& left, VectorOfVectors& right) {
	right.wypisz(left);
	return left;
}

istream& operator>>(istream& in, VectorOfVectors& vecOfVecs) {
	cout << "Podaj wielkosc tablicy wektorow: ";
	in >> vecOfVecs.size;

	cout << "Podaj wektory:" << endl;
	for (int i = 0; i < vecOfVecs.size; i++) {
		cout << "Wektor " << i << ": " << endl;

		int dim; // dimension of the vector
		cout << "Podaj wymiar wektora: ";
		in >> dim;

		double* values = new double[dim];
		cout << "Podaj wartosci wektora (oddzielone spacja): ";
		for (int j = 0; j < dim; j++) {
			in >> values[j];
		}

		vecOfVecs.vektory[i] = VektorNd(values, dim);

		delete[] values;
	}

	return in;
}

int main() {
	VectorOfVectors vof;

	cout << "Wczytywanie danych ze strumienia standardowego (cin):" << endl;
	cin >> vof;

	cout << "Wypisywanie danych na standardowy strumieÒ wyjúciowy (cout):" << endl;
	cout << vof;

	return 0;
}