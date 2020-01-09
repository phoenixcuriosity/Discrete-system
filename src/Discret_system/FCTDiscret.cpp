/*

	Discrete_system
	Copyright SAUTER Robin 2017-2019 (robin.sauter@orange.fr)
	last modification on this file on version: 3.1
	file version 2.0

	You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "FCTDiscret.h"

FCTDiscret::FCTDiscret() 
: _jury(nullptr), _num(nullptr), _den(nullptr), _deltaT(1)
{
	allocate((Polynome)1.0, (Polynome)1.0);
}
FCTDiscret::FCTDiscret(double userValue)
:_jury(nullptr), _num(nullptr), _den(nullptr), _deltaT(1)
{
	allocate((Polynome)userValue, (Polynome)1.0);
}
FCTDiscret::FCTDiscret(Polynome& num, Polynome& den, double deltaT)
: _jury(nullptr), _num(nullptr), _den(nullptr),_deltaT(deltaT)
{
	allocate(num, den);
}
FCTDiscret::FCTDiscret(const FCTDiscret& F)
: _jury(nullptr), _num(nullptr), _den(nullptr), _deltaT(F.GETdeltaT())
{
	allocate(F.GETnum(), F.GETden());
}
FCTDiscret::~FCTDiscret()
{
	if (_num != nullptr)
	{
		delete _num;
		_num = nullptr;
	}
	if (_den != nullptr)
	{
		delete _den;
		_den = nullptr;
	}
}


void FCTDiscret::allocate(Polynome num, Polynome den)
{
	_jury = new Matrice;
	_num = new Polynome(num);
	_den = new Polynome(den);
}



/*
		si la fct n'est pas de la meme forme alors on prend les attributs de a
*/
FCTDiscret& FCTDiscret::operator=(const FCTDiscret& a)
{
	
	if (this != &a)
	{
		_num = a._num;
		_den = a._den;
		_deltaT = a._deltaT;
	}
	return *this;
}


bool operator==(const FCTDiscret& a, const FCTDiscret& b)
{
	if (a.GETnum() == b.GETnum() && a.GETden() == b.GETden())
		return true;
	return false;
}
FCTDiscret operator+(const FCTDiscret& a, const FCTDiscret& b)
{
	FCTDiscret resultat;
	resultat.SETnum(a.GETnum() * b.GETden());
	resultat.SETnum(resultat.GETnum() + b.GETnum() * a.GETden());
	resultat.SETden(a.GETden() * b.GETden());
	return resultat;
}
FCTDiscret operator-(const FCTDiscret& a, const FCTDiscret& b)
{
	FCTDiscret resultat;
	resultat.SETnum(a.GETnum() * b.GETden());
	resultat.SETnum(resultat.GETnum() - b.GETnum() * a.GETden());
	resultat.SETden(a.GETden() * b.GETden());
	return resultat;
}
FCTDiscret operator*(const FCTDiscret& a, const FCTDiscret& b)
{
	FCTDiscret resultat;
	resultat.SETnum(a.GETnum() * b.GETnum());
	resultat.SETden(a.GETden() * b.GETden());
	return resultat;
}



void FCTDiscret::SETjuryPtr(const Matrice* J)
{
	*_jury = *J;
}
void FCTDiscret::SETnumPtr(const Polynome* a)
{
	*_num = *a;
}
void FCTDiscret::SETdenPtr(const Polynome* a)
{
	*_den = *a;
}
void FCTDiscret::SETjury(const Matrice& J)
{
	*_jury = J;
}
void FCTDiscret::SETnum(const Polynome& a)
{
	*_num = a;
}
void FCTDiscret::SETden(const Polynome& a)
{
	*_den = a;
}
void FCTDiscret::SETdeltaT(double deltaT)
{
	_deltaT = deltaT;
}
void FCTDiscret::SETnumOrder(unsigned int order)
{
	_num->SETorder(order);
}
void FCTDiscret::SETdenOrder(unsigned int order)
{
	_den->SETorder(order);
}
void FCTDiscret::SETnumThisCoef(unsigned int index, double userValue)
{
	_num->SETcoefTab(index, userValue);
}
void FCTDiscret::SETdenThisCoef(unsigned int index, double userValue)
{
	_den->SETcoefTab(index, userValue);
}


Matrice* FCTDiscret::GETjuryPtr()const
{
	return _jury;
}
Polynome* FCTDiscret::GETnumPtr() const
{
	return _num;
}
Polynome* FCTDiscret::GETdenPtr() const
{
	return _den;
}
Matrice& FCTDiscret::GETjury()const
{
	return *_jury;
}
Polynome& FCTDiscret::GETnum() const
{
	return *_num;
}
Polynome& FCTDiscret::GETden() const
{
	return *_den;
}
double FCTDiscret::GETdeltaT()const
{
	return _deltaT;
}



std::ostream& operator<<(std::ostream& os, const FCTDiscret& s)
{
	return os << s.printOn(false);
}


/*
		affiche sur la console : en haut le num, puis la barre de fraction et enfin le den
		affichage selon la taille de la chaine de caratere la plus longue
*/
const std::string FCTDiscret::printOn(bool on) const
{
	unsigned int stringSize = 0;
	std::string equation;
	std::stringstream stream;

	if (_num->GETstringSize() > _den->GETstringSize())
	{
		stringSize = _num->GETstringSize();
		stream << _num->printOn(false) << std::endl;
		for (unsigned int i = 0; i < stringSize; i++)
			stream << "-";
		stream << std::endl;
		for (unsigned int i = 0; i < ((_num->GETstringSize() / 2) - (_den->GETstringSize() / 2)); i++)
			stream << " ";
		stream << _den->printOn(false);
		equation = stream.str();
	}
	else if (_num->GETstringSize() < _den->GETstringSize())
	{
		stringSize = _den->GETstringSize();
		for (unsigned int i = 0; i < ((_den->GETstringSize() / 2) - (_num->GETstringSize() / 2)); i++)
			stream << " ";
		stream << _num->printOn(false) << std::endl;
		for (unsigned int i = 0; i < stringSize; i++)
			stream << "-";
		stream << std::endl << _den->printOn(false);
		equation = stream.str();
	}
	else
	{
		stringSize = _num->GETstringSize();
		stream << _num->printOn(false) << std::endl;
		for (unsigned int i = 0; i < stringSize; i++)
			stream << "-";
		stream << std::endl << _den->printOn(false);
		equation = stream.str();
	}
	if (on)
		std::cout << equation;
	return equation;
}
void FCTDiscret::interg()
{
	_num->SETorder(1);
	_den->SETorder(1);
	_num->SETcoefTab(0, 0);
	_num->SETcoefTab(1, 1);
	_den->SETcoefTab(0, -1);
	_den->SETcoefTab(1, 1);
}
void FCTDiscret::secondOrdre()
{
	_num->SETorder(0);
	_den->SETorder(1);
	_num->SETcoefTab(0, 1);
	_den->SETcoefTab(0, -0.1);
	_den->SETcoefTab(1, 0.5);
	_den->SETcoefTab(2, 1);
}
/*
		calcul du crit�re de Jury permettant de statuer sur la stabilit� du syst�me
		tableau de Jury -> Matrice pouvant changer de taille en fonction de l'ordre du den
*/
bool FCTDiscret::tabJury()
{
	std::string tableauJury;
	std::ostringstream stream;

	Polynome den(_den->GETorder());
	for (unsigned int i = 0, j = _den->GETorder(); i <= _den->GETorder(), j >= 0; i++, j--)
	{
		den.SETcoefTab(i, _den->GETcoefTab(j));
		if (j == 0) break; // compatibilit� unsigned int, j ne peut etre �gale � -1
	}
		
	if (den.GETcoefTab(den.GETorder()) < 0)
		den = - 1.0 * den;

	Polynome ligne1(*_den);
	Polynome ligne2(*_den);

	if (_den->GETorder() > 2)
	{
		_jury->editsize(2, _den->GETorder() + 1);
		for (unsigned int i = 0; i <= _den->GETorder(); i++) // premi�re ligne
			_jury->SETthiscoef(0, i, _den->GETcoefTab(i));
		for (unsigned int i = 0; i <= _den->GETorder(); i++) // deuxi�me ligne
			_jury->SETthiscoef(1, i, den.GETcoefTab(i));
	}
	else
	{
		_jury->editsize(1, _den->GETorder() + 1);
		for (unsigned int i = 0; i <= _den->GETorder(); i++)
			_jury->SETthiscoef(0, i, _den->GETcoefTab(i));
	}
	
	
	while (ligne2.GETorder() > 2)
	{
		ligne2.SETorder(ligne2.GETorder() - 1);
		for (unsigned int i = 0, j = ligne2.GETorder(); i <= ligne2.GETorder(), j >= 0; i++, j--)
		{
			ligne2.SETcoefTab(i, ((ligne1.GETcoefTab(0) * ligne1.GETcoefTab(i)) - (ligne1.GETcoefTab(ligne1.GETorder()) * ligne1.GETcoefTab(ligne1.GETorder() - i))));
			if (j == 0) break;
		}
		if (ligne2.GETorder() > 2) 
		{
			_jury->editsize(_jury->GETlength() + 2, _den->GETorder() + 1);
			for (unsigned int i = 0; i <= ligne2.GETorder(); i++)


				_jury->SETthiscoef(_jury->GETlength() - 2, i, ligne2.GETcoefTab(i));
			for (unsigned int i = 0, j = ligne2.GETorder(); i <= ligne2.GETorder(), j >= 0; i++, j--)
			{
				_jury->SETthiscoef(_jury->GETlength() - 1, i, ligne2.GETcoefTab(j));
				if (j == 0) break;
			}
		}
		else
		{
			_jury->editsize(_jury->GETlength() + 1, _den->GETorder() + 1);
			for (unsigned int i = 0; i <= ligne2.GETorder(); i++)
				_jury->SETthiscoef(_jury->GETlength() - 1, i, ligne2.GETcoefTab(i));
		}
		ligne1 = ligne2;
	}
	
	 
	stream << std::endl << std::endl << "table of Jury = " << _jury;

	unsigned int condition = 0;

	/*
		condition abs(a0) < an
	*/
	stream << std::endl << std::endl << "abs(a0) = " << abs(_den->GETcoefTab(0));
	if (abs(_den->GETcoefTab(0)) < _den->GETcoefTab(_den->GETorder()))
	{
		stream << " < a" << _den->GETorder() << " = " << _den->GETcoefTab(_den->GETorder()) << "	Ok";
		condition++;
	}
	else
		stream << " > a" << _den->GETorder() << " = " << _den->GETcoefTab(_den->GETorder()) << "	Not Ok";


	/*
	condition D(1) > 0
	*/
	double somme = 0;
	for (unsigned int i = 0; i <= _den->GETorder(); i++)
		somme += _den->GETcoefTab(i);
	
	stream << std::endl << "D(1) = " << somme;
	if (somme > 0)
	{
		stream << " > 0	Ok";
		condition++;
	}
	else
		stream << " <= 0 Not Ok";

	/*
	condition D(-1) > 0 si n pair et ondition D(-1) < 0 si n impair
	*/
	somme = 0;
	for (unsigned int i = 0; i <= _den->GETorder(); i++)
		somme += _den->GETcoefTab(i) * pow(-1, i);
	stream << std::endl << "D(-1) = " << somme;
	if ((somme > 0 && (_den->GETorder() % 2) == 0) || (somme < 0 && (_den->GETorder() % 2) == 1))
	{
		stream << "	Ok";
		condition++;
	}
	else
		stream << "	Not Ok";
		
	if (_den->GETorder() > 2)
	{
		/*
		condition Q0 > Q2
		*/
		stream << std::endl << "Q0 = " << abs(ligne2.GETcoefTab(0));
		if (abs(ligne2.GETcoefTab(0)) > abs(ligne2.GETcoefTab(2)))
		{
			stream << " > Q2 = " << abs(ligne2.GETcoefTab(2)) << "	Ok";
			condition++;
		}
		else
			stream << " < Q2 = " << abs(ligne2.GETcoefTab(2)) << "	Not Ok";
	}
	else
	{
		condition++;
	}
	

	if (condition == 4)
	{
		stream << std::endl;
		tableauJury = stream.str();
		std::cout << tableauJury;
		return true;
	}
	else
	{
		stream << std::endl;
		tableauJury = stream.str();
		std::cout << tableauJury;
		return false;
	}
}
/*
		Diagramme de Bode en gain et phase
*/
bool FCTDiscret::Bode(double wMin, double wMax, unsigned int nbpoint, double** gainPhase)
{
	std::ofstream reponse("bin/files/Bode.txt");
	std::string texte;
	std::ostringstream stream;

	double amplitude = wMax - wMin;
	double increment = amplitude / nbpoint;
	double gain = 0, phase = 0;
	Complexe Z, c, cnum, cden;

	/*
		dans le diagramme de Bode wMin n'atteint jamais 0
	*/
	if (wMin == 0)
		wMin = 0.001;


	unsigned int o = 0;
	if (reponse){
		for (double i = wMin; i <= wMax; i += increment)
		{
			Z = Complexe::tfReIm(1, i * _deltaT);
			cnum = Complexe::tfPolynomeComplexe(*_num, Z);
			cden = Complexe::tfPolynomeComplexe(*_den, Z);
			c = cnum / cden;
			gainPhase[0][o] = i;
			gainPhase[1][o] = gain = 20 * log10(Complexe::module(c));
			gainPhase[2][o] = phase = -Complexe::arg(c);
			stream << std::endl << i << " , " << gain << " , " << phase;
			o++;
		}
		texte = stream.str();
		reponse << texte;
		std::cout << texte;
		return true;
	}
	else
		return false;
}



/*
*		Calcul de la FTBF
*/
void closeLoop(const FCTDiscret& openLoop, const FCTDiscret& returnLoop)
{
	
	FCTDiscret num;
	FCTDiscret den;


	num = openLoop;
	den = 1.0 + openLoop * returnLoop;

	FCTDiscret resultat;
	resultat.SETnum(num.GETnum() * num.GETden());
	resultat.SETden(den.GETnum() * num.GETden());

	std::cout << std::endl << std::endl << "CloseLoop" << std::endl << resultat << std::endl;
}


void testFCTDiscret()
{
	std::string fctdiscret;
	std::ostringstream stream;

	stream << std::endl << "___TEST FCTDiscret___";
	Polynome a((unsigned int)3);
	a.SETcoefTab(2, 1), a.SETcoefTab(1, 2);
	Polynome b(a);
	b.SETcoefTab(2, 2), b.SETcoefTab(0, 1);
	a.grow(2), a.SETcoefTab(0, 51), a.SETcoefTab(1, -512);

	FCTDiscret fct1(b, a, 10.3);
	b.SETcoefTab(0, 7.3);
	b.SETcoefTab(1, -91);
	FCTDiscret fct2(a, b, 10.3);
	stream << std::endl << std::endl << "Fct1 constructeur par valeur:" << std::endl << fct1 << std::endl;
	stream << std::endl << "Fct2 constructeur par recopie:" << std::endl << fct2 << std::endl;
	FCTDiscret fctmultiplication = fct1 * fct2;
	stream << std::endl << "multiplication de fct1 * fct2, Fonctions de transfert :" << std::endl << fctmultiplication << std::endl;
	FCTDiscret fctaddition = fct1 + fct2;
	stream << std::endl << "addition de fct1 + fct2,  Fonctions de transfert :" << std::endl << fctaddition << std::endl;
	FCTDiscret fctsoustraction = fct1 - fct2;
	stream << std::endl << "soustraction de fct1 - fct2,  Fonctions de transfert :" << std::endl << fctsoustraction << std::endl;
	
	stream << std::endl << "taille du num de fct1 = " << fct1.GETnum().GETorder();
	fct1.SETnumOrder(5);
	stream << std::endl << "taille du num de fct1 = " << fct1.GETnum().GETorder();
	fct1.SETnumThisCoef(4, 5.6), fct1.SETnumThisCoef(3, -5.6);
	stream << std::endl << "Fct1 :" << std::endl << fct1 << std::endl << std::endl;
	FCTDiscret integ;
	integ.SETnumOrder(0), integ.SETnumThisCoef(0, 1);
	integ.SETdenOrder(1), integ.SETdenThisCoef(1, 1);
	stream << std::endl << "integ = " << std::endl << integ << std::endl;
	stream << std::endl << "integ * fct1 = " << std::endl << (integ * fct1) << std::endl;

	FCTDiscret openLoop = fct1 * integ;
	FCTDiscret returnLoop = -1.0;

	closeLoop(openLoop, returnLoop);

	fctdiscret = stream.str();
	std::cout << fctdiscret;
}
