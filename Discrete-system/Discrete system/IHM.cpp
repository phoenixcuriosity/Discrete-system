/*
Discret_system
author : SAUTER Robin
2017 - 2018
last modification on this file on version:0.22

This library is free software; you can redistribute it and/or modify it
You can check for update on github.com -> https://github.com/phoenixcuriosity/Discret_system

*/

#include "IHM.h"

using namespace std;

IHM::IHM() : _fct(0), _sys(0)
{
	_fct = new FCTDiscret;
	_sys = new SYSETATDiscret;
}
IHM::~IHM()
{
	delete _fct;
	delete _sys;
}


void mainLoop(IHM& ihm){
	bool continuer = true;
	unsigned int request = 0;
	logfileconsole("_________Init Success_________");

	//testPolynome();
	//testFCTDiscret();
	//testMatrice();
	//testComplexe();
	//testSYSETATDiscret();
	//testIHM();

	logfileconsole("_________START PROGRAM_________");
	logfileconsole("version: 22");
	logfileconsole("This is a free software, you can redistribute it and/or modify it\n");

	while (continuer){
		logfileconsole("type 1 (Fct Discret)\n or type 2 SYSETATDiscret\n or type 3 to exit the program\n");
		cin >> request;
		switch (request){
		case selectFCT:
			FCTLoop(ihm);
			break;
		case selectSYSETAT:
			logfileconsole("You have select SYSETATDiscret");
			break;
		case exitProgram:
			continuer = false;
			break;
		}
	}
}
void FCTLoop(IHM& ihm){
	unsigned int request = 0;
	double deltaT = 0;
	bool continuer = true;

	while (continuer){
		logfileconsole("You have selected Fct Discret");
		logfileconsole("type 1 to create the num and the den");
		logfileconsole("or type 2 to edit the FCT or type 3 to display the FCT");
		logfileconsole("or type 4 to return to previous menu : ");
		cin >> request;
		switch (request){
		case createNumDen:

			cout << "Init deltaT = " << ihm.GETfct()->GETdeltaT() << "s";
			logfileconsole("deltaT of FCT? : ");
			cin >> deltaT;
			ihm.GETfct()->SETdeltaT(deltaT);
			cout << "New deltaT = " << ihm.GETfct()->GETdeltaT() << "s";
			createNum(ihm);
			createDen(ihm);
			logfileconsole("You have created with SUCCESS the FCT, Yeah!!! You did it!!!");
			logfileconsole("Now try to diplay it");
			cout << endl << endl;
			break;
		case editFCT:
			break;
		case displayFCT:
			logfileconsole("FCT\n");
			ihm.GETfct()->printOn();
			break;
		case previousMenuFCT:
			continuer = false;
			break;
		}
	}
}

void createNum(IHM& ihm){
	unsigned int order = 0;
	double coef = 0;

	logfileconsole("You have selected to create Num");
	logfileconsole("order of FCT? : ");
	cin >> order;
	ihm.GETfct()->SETnum(order);
	for (unsigned int i = 0; i <= order; i++){
		logfileconsole("coef n:" + to_string(i) + " = ");
		cin >> coef;
		ihm.GETfct()->SETnumThisCoef(i, coef);
	}
	logfileconsole("You create the Num");
}
void createDen(IHM& ihm){
	unsigned int order = 0;
	double coef = 0;

	logfileconsole("You have selected to create Den");
	logfileconsole("order of FCT? : ");
	cin >> order;
	ihm.GETfct()->SETden(order);
	for (unsigned int i = 0; i <= order; i++){
		logfileconsole("coef n:" + to_string(i) + " = ");
		cin >> coef;
		ihm.GETfct()->SETdenThisCoef(i, coef);
	}
	logfileconsole("You create the Den");
}




void IHM::SETfct(FCTDiscret* fct){
	_fct = fct;
}
void IHM::SETsys(SYSETATDiscret* sys){
	_sys = sys;
}
FCTDiscret* IHM::GETfct()const{
	return _fct;
}
SYSETATDiscret* IHM::GETsys()const{
	return _sys;
}


void testIHM(){
	cout << endl << endl << "___TEST IHM___" << endl << endl;

	IHM ihm;
	ihm.GETfct()->SETnumOrder(1);
	ihm.GETfct()->SETnumThisCoef(0, 0);
	ihm.GETfct()->SETnumThisCoef(1, 1);
	ihm.GETfct()->SETdenOrder(2);
	ihm.GETfct()->SETdenThisCoef(0, 0);
	ihm.GETfct()->SETdenThisCoef(1, 0.1);
	ihm.GETfct()->SETdenThisCoef(2, 1.1);
	ihm.GETfct()->printOn();

	ihm.GETsys()->calculABCD(*ihm.GETfct());
	ihm.GETsys()->SETTe(100);
	ihm.GETsys()->printOn();
	ihm.GETfct()->tabJury();
	cout << endl << "BODE" << endl;
	ihm.GETfct()->Bode(0.1, 10, 100);

	Echelon E(50, 10.0);
	Matrice x0(ihm.GETsys()->GETA().GETlength(), 1);
	x0.SETthiscoef(0, 0, 0.1);

	cout << endl << endl << endl << "Reponse temporelle avec E = 10.0" << endl;
	ihm.GETsys()->simulation("bin/SaveAndLoad/ReponseTemporelle.txt", E, x0);

	cout << endl << endl;
}
void logfileconsole(const std::string &msg) {
	const string logtxt = "bin/log/log.txt";
	ofstream log(logtxt, ios::app);
	if (log) {
		cout << endl << msg;
		log << endl << msg;
	}
	else
		cout << endl << "ERREUR: Impossible d'ouvrir le fichier : " << logtxt;
}