/***************************************************************************\
|* Preguntas calculadas                                                    *|
|*-------------------------------------------------------------------------*|
|* Author: Juan Carlos Monreal Romero                                      *|
|*                                                                         *|
\***************************************************************************/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include "fparser/fparser.hh"
#include "fparser/fparser.cc"
#define endl "\n"
using namespace std;

//--Pregunta Calculada
struct Calculada
{
	string name;
	string text;
	string formula;
	float points;
	string comodin;
};
struct Comodin
{
	string name;
	float up;
	float low;
	float num;
	string link;
};
//--Pregunta Calculada
//---PREGUNTA CALCULADA SIMPLE---
struct CalculadaS
{
	string name;
	string text;
	string formula;
	float points=100;
	string comodin;
};
//---PREGUNTA CALCULADA SIMPLE---

//---PREGUNTA CALCULADA OPCION MULTIPLE---
struct CalculadaM
{
	string name;
	string text;
	string formula[4];
	float points[4];
	string comodin;
};
//---PREGUNTA CALCULADA OPCION MULTIPLE---

//--Pregunta Calculada
void menuCalculada();
void calculadaC();//Metodo principal de la calculada
string findComodin(string str);//buscar comodines
void genComodin(string str, string link);//generar datos al comodin
float randomNum(float up, float low);//Generar numero aleatorio
void modifyC();//Modificar pregunta Calculada
void delC();//Eliminar pregunta calculada
//--Pregunta Calculada

void show(int id);//Listar preguntas

void showV(int *v,int size);//imprimir vector
void preguntas();//Menu Preguntas

//---PREGUNTA CALCULADA SIMPLE---
void menuCalculadaS();
void calculadaCS();
void modifyCS();
void delCS();
//---PREGUNTA CALCULADA SIMPLE---

//---PREGUNTA CALCULADA OPCION MULTIPLE---
void menuCalculadaM();
void calculadaCM();
void modifyCM();
void delCM();
//---PREGUNTA CALCULADA OPCION MULTIPLE---

//---EXAMEN---
void menuTest();
void modifyTest();
void addTest();//añadir preguntas a Test
void delTest();//eliminar preguntas de Test
void evalTest();//evaluacion del examen
float evalFormula(string str, string formula, string comodines,string link);
float searchComodin(string name, string link);
//---EXAMEN---

//---Archivo---
void guardarExamen(double calif);

//---Archivo---

//--Almacen---
vector <Calculada> calculada;//Almacena pregunta calculadas
vector <CalculadaS> calculadaS;//Almacena pregunta calculadas simples
vector <CalculadaM> calculadaM;//Almacena pregunta calculadas multiples
vector <Comodin> comodin;//Almacena comodines
//--Almacen---

vector <string> test;//Almacena nombre preguntas examen
vector <int> valTest;//Almacena el tipo de pregunta
float point=0;//guarda puntos examen
int main(){
	int op;
	do{
		printf("Bienvenido!!\nIngrese el numero de opcion\n");
		printf("1. Menu Preguntas \n");
		printf("2. Menu examen\n");
		printf("3. Guarda examen\n");
		printf("4. Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				preguntas();
				break;
			case 2:
				menuTest();
				break;
			case 3:
				guardarExamen(point);
				break;
			case 4:
				return 0;
				break;
			default:
				printf("Ingrese una opcion valida y/o el examen aun no tiene preguntas.\n");
				break;
		}

	} while (op!=4);

    return 0;
}

void preguntas(){
	int op;
	do{
		printf("Bienvenido!!\nEscoga el numero de opcion\n");
		printf("1. Menu pregunta calculada\n");
		printf("2. Menu pregunta calculada simple\n");
		printf("3. Menu pregunta calculada de opcion multiple\n");
		printf("4. Salir\n");
		printf("Ingrese el numero de opcion.\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				menuCalculada();
				break;
			case 2:
				menuCalculadaS();
				break;
			case 3:
				menuCalculadaM();
				break;
			case 4:
				main();
				break;
			default:
				printf("Ingrese una opcion valida\n");
		}
	} while (op!=4);
}

//---Pregunta Calculada---
void menuCalculada(){
	int op;
	do
	{
		printf("Bienvenido al menu preguntas calculadas\n");
		printf("1. Agregar preguntas\n");
		printf("2. Modificar preguntas \n");
		printf("3. Eliminar preguntas\n");
		printf("4. Listar preguntas\n");
		printf("5. Salir\n");
		printf("Ingrese el numero de opcion deseada\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				calculadaC();
				break;
			case 2:
				modifyC();
				break;
			case 3:
				delC();
				break;
			case 4:
				show(1);
				break;
			case 5:
				preguntas();
			default:
				printf("Ingrese un numero de opcion valida\n");
				break;
		}

	} while (op!=5);
}
void calculadaC(){
	string str;
	float f;
	Calculada temp;
	printf("Ingrese el nombre de la pregunta\n");
	fflush(stdin);
	getline(cin,str);
	temp.name=str;
	printf("Ingrese el texto de la pregunta\n");
	getline(cin,str);
	temp.text=str;
	printf("Ingrese la formula de la respuesta\n");
	getline(cin,str);
	temp.formula=str;
	printf("Ingrese la puntuacion de la respuesta en un valor porcentual del 0 al 100 \n");
	printf("Siendo 100 como respuesta correcta.\n");
	scanf("%f",&f);
	temp.points=f;
	str=findComodin(temp.text);
	temp.comodin=str;
	genComodin(str,temp.name);
	calculada.push_back(temp);
}

string findComodin(string str){
	string temp="";
	while(str.find("{")!=string::npos){
		int found=str.find("{");
		int found2=str.find("}");
		if(temp.find(str.substr(found+1,(found2-found)-1))==string::npos){
			temp+=str.substr(found+1,(found2-found)-1)+",";
			while(found<=found2) {
			    str[found]='0';
			    found++;
			}
		}else{
			while(found<=found2) {
			    str[found]='0';
			    found++;
			}
		}
	}
	return temp;
}

float randomNum(float up, float low){
	srand(time(0));
	return low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(up-low)));
}
void genComodin(string str, string link){
	float f;
	int j=0;
	string aux;
	for (int i = 0; i < str.length(); ++i){
		Comodin temp;
		if (str[i] == ','){
			aux=str.substr(j,(i-j));
			temp.name=aux;
			j=i+1;
			cout<<"Ingrese el limite inferior para el comodin "<<aux<<endl;
			scanf("%f",&f);
			temp.low=f;
			cout<<"Ingrese el limite superior para el comodin "<<aux<<endl;
			scanf("%f",&f);
			temp.up=f;
			temp.num=randomNum(temp.up,temp.low);
			temp.link=link;
			comodin.push_back(temp);
		}

	}
}

void modifyC(){
	int op;
	do{
		string str;
		int id;
		printf("Modificaciones\nEscoga el numero de opcion\n");
		printf("1. Cambiar nombre pregunta\n");
		printf("2. Cambiar texto de pregunta\n");
		printf("3. Cambiar formula de pregunta\n");
		printf("4. Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				show(1);
				printf("Ingrese el numero de pregunta a ser modificado\n");
				scanf("%d",&id);
				printf("Ingrese el nuevo nombre de la pregunta\n");
				cin>>str;
				for (int i = 0; i < comodin.size(); ++i){
					if(comodin[i].link==calculada[id-1].name){
						calculada[id-1].name=str;
						comodin[i].link=str;
						printf("Cambio realizado\n");
					}
				}
				break;
			case 2:
				show(1);
				printf("Ingrese el numero de pregunta a ser modificado\n");
				scanf("%d",&id);
				printf("La pregunta %d tiene el texto: ",id);
				cout<<calculada[id-1].text<<endl;
				printf("Ingrese el nuevo texto de la pregunta\n");
				cin>>str;
				calculada[id-1].text=str;
				genComodin(findComodin(str),calculada[id-1].name);
				break;
			case 3:
				show(1);
				printf("Ingrese el numero de pregunta a ser modificado\n");
				scanf("%d",&id);
				printf("Ingrese la nueva formula\n");
				cin>>str;
				calculada[id-1].formula=str;
				break;
			case 4:
				menuCalculadaS();
				break;
			default:
				printf("Ingrese una opcion valida\n");
		}
	} while (op!=4);
}
void delC(){
	int id;
	show(1);
	printf("Ingrese el numero de la pregunta que eliminara\n");
	scanf("%d",&id);
	id-=1;
	calculada.erase(calculada.begin()+id);
}
//---Pregunta Calculada---

void show(int id){
	switch(id){
		case 1:
			printf("Se mostrara el listado de preguntas calculadas acorde a su nombre\n");
			for (int i = 0; i < calculada.size(); ++i){
				cout<<i+1<<". "<<calculada[i].name<<endl;
			}
			break;
		case 2:
			printf("Se mostrara el listado de preguntas calculadas simples acorde a su nombre\n");
			for (int i = 0; i < calculadaS.size(); ++i){
				cout<<i+1<<". "<<calculadaS[i].name<<endl;
			}
			break;
		case 3:
			printf("Se mostrara el listado de preguntas calculadas de opcion multiple acorde a su nombre\n");
			for (int i = 0; i < calculadaM.size(); ++i){
				cout<<i+1<<". "<<calculadaM[i].name<<endl;
			}
			break;
	}
}

//---PREGUNTA CALCULADA SIMPLE---
void menuCalculadaS(){
	int op;
	do
	{
		printf("Bienvenido al menu preguntas calculadas simples\n");
		printf("1. Agregar preguntas\n");
		printf("2. Modificar preguntas \n");
		printf("3. Eliminar preguntas\n");
		printf("4. Listar preguntas\n");
		printf("5. Salir\n");
		printf("Ingrese el numero de opcion deseada\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				calculadaCS();
				break;
			case 2:
				modifyCS();
				break;
			case 3:
				delCS();
				break;
			case 4:
				show(2);
				break;
			case 5:
				preguntas();
				break;
			default:
				printf("Ingrese un numero de opcion valida\n");
				break;
		}

	} while (op!=5);
}
void calculadaCS(){
	string str;
	float f;
	CalculadaS temp;
	printf("Ingrese el nombre de la pregunta\n");
	fflush(stdin);
	getline(cin,str);
	temp.name=str;
	printf("Ingrese el texto de la pregunta\n");
	getline(cin,str);
	temp.text=str;
	printf("Ingrese la formula de la respuesta\n");
	getline(cin,str);
	temp.formula=str;
	str=findComodin(temp.text);
	temp.comodin=str;
	genComodin(str,temp.name);
	calculadaS.push_back(temp);
}
void modifyCS(){
	int op;
	do{
		string str;
		int id;
		printf("Modificaciones\nEscoga el numero de opcion\n");
		printf("1. Cambiar nombre pregunta\n");
		printf("2. Cambiar texto de pregunta\n");
		printf("3. Cambiar formula de pregunta\n");
		printf("4. Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				show(2);
				printf("Ingrese el numero de pregunta a ser modificado\n");
				scanf("%d",&id);
				printf("Ingrese el nuevo nombre de la pregunta\n");
				cin>>str;
				for (int i = 0; i < comodin.size(); ++i){
					if(comodin[i].link==calculadaS[id-1].name){
						calculadaS[id-1].name=str;
						comodin[i].link=str;
					}
				}
				break;
			case 2:
				show(2);
				printf("Ingrese el numero de pregunta a ser modificado\n");
				scanf("%d",&id);
				printf("La pregunta %d tiene el texto: ",id);
				cout<<calculadaS[id-1].text<<endl;
				printf("Ingrese el nuevo texto de la pregunta\n");
				cin>>str;
				calculadaS[id-1].text=str;
				genComodin(findComodin(str),calculadaS[id-1].name);
				break;
			case 3:
				show(2);
				printf("Ingrese el numero de pregunta a ser modificado\n");
				scanf("%d",&id);
				printf("Ingrese la nueva formula\n");
				cin>>str;
				calculadaS[id-1].formula=str;
				break;
			case 4:
				menuCalculadaS();
				break;
			default:
				printf("Ingrese una opcion valida\n");
		}
	} while (op!=4);
}
void delCS(){
	int id;
	show(2);
	printf("Ingrese el numero de la pregunta que eliminara\n");
	scanf("%d",&id);
	id-=1;
	calculadaS.erase(calculadaS.begin()+id);
}
//---PREGUNTA CALCULADA SIMPLE---

//---PREGUNTA CALCULADA OPCION MULTIPLE---
void menuCalculadaM(){
	int op;
	do{
		printf("Bienvenido al menu preguntas calculadas de opcion multiple\n");
		printf("1. Agregar preguntas\n");
		printf("2. Modificar preguntas \n");
		printf("3. Eliminar preguntas\n");
		printf("4. Listar preguntas\n");
		printf("5. Salir\n");
		printf("Ingrese el numero de opcion deseada\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				calculadaCM();
				break;
			case 2:
				modifyCM();
				break;
			case 3:
				delCM();
				break;
			case 4:
				show(3);
				break;
			case 5:
				preguntas();
				break;
			default:
				printf("Ingrese un numero de opcion valida\n");
				break;
		}

	} while (op!=5);
}
void calculadaCM(){
	string str;
	float f;
	CalculadaM temp;
	printf("Ingrese el nombre de la pregunta\n");
	fflush(stdin);
	getline(cin,str);
	temp.name=str;
	printf("Ingrese el texto de la pregunta\n");
	getline(cin,str);
	temp.text=str;
	for (int i = 0; i < 4; ++i){
		printf("Ingrese la formula %d de la respuesta\n",i+1);
		cin>>str;
		temp.formula[i]=str;
		printf("Ingrese la puntuacion de la respuesta en un valor porcentual del 0 al 100 \n");
		printf("Siendo 100 como respuesta correcta.\n");
		scanf("%f",&f);
		temp.points[i]=f;
	}
	str=findComodin(temp.text);
	temp.comodin=str;
	genComodin(str,temp.name);
	calculadaM.push_back(temp);
}
void modifyCM(){
	int op;
	do{
		string str;
		int id;
		printf("Modificaciones\nEscoga el numero de opcion\n");
		printf("1. Cambiar nombre pregunta\n");
		printf("2. Cambiar texto de pregunta\n");
		printf("3. Cambiar formulas de pregunta\n");
		printf("4. Salir\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				show(3);
				printf("Ingrese el numero de pregunta a ser modificado\n");
				scanf("%d",&id);
				printf("Ingrese el nuevo nombre de la pregunta\n");
				cin>>str;
				for (int i = 0; i < comodin.size(); ++i){
					if(comodin[i].link==calculadaM[id-1].name){
						calculadaM[id-1].name=str;
						comodin[i].link=str;
					}
				}
				break;
			case 2:
				show(3);
				printf("Ingrese el numero de pregunta a ser modificado\n");
				scanf("%d",&id);
				printf("La pregunta %d tiene el texto: ",id);
				cout<<calculadaM[id-1].text<<endl;
				printf("Ingrese el nuevo texto de la pregunta\n");
				cin>>str;
				calculadaM[id-1].text=str;
				genComodin(findComodin(str),calculadaM[id-1].name);
				break;
			case 3:
				show(3);
				printf("Ingrese el numero de pregunta a ser modificado\n");
				scanf("%d",&id);
				for (int i = 0; i < 4; ++i){
					printf("Ingrese la nueva formula %d\n",i+1);
					cin>>str;
					calculadaM[id-1].formula[i]=str;
				}
				break;
			case 4:
				menuCalculadaM();
				break;
			default:
				printf("Ingrese una opcion valida\n");
		}
	} while (op!=4);
}
void delCM(){
	int id;
	show(3);
	printf("Ingrese el numero de la pregunta que eliminara\n");
	scanf("%d",&id);
	id-=1;
	calculadaM.erase(calculadaM.begin()+id);
}
//---PREGUNTA CALCULADA OPCION MULTIPLE---

//---EXAMEN---
void menuTest(){
	int op;
	do{
		printf("Bienvenido al menu Examen\n");
		printf("1. Agregar preguntas al examen\n");
		printf("2. Modificar preguntas al examen\n");
		printf("3. Eliminar preguntas al examen\n");
		printf("4. Probar/Realizar Examen\n");
		printf("5. Salir\n");
		printf("Ingrese el numero de opcion deseada\n");
		scanf("%d",&op);
		switch(op){
			case 1:
				addTest();
				break;
			case 2:
				modifyTest();
				break;
			case 3:
				delTest();
				break;
			case 4:
				evalTest();
				break;
			case 5:
				main();
				break;
			default:
				printf("Ingrese un numero de opcion valida\n");
				break;
		}

	} while (op!=5);

}
void modifyTest(){
	string str;
	int id=0;
	printf("Listado de preguntas en el examen\n");
	for (int i = 0; i < test.size(); ++i)
	{
		cout<<i+1<<". "<<test[i]<<endl;
	}
	printf("Ingrese el numero de pregunta a ser modificado\n");
	scanf("%d",&id);
	printf("Ingrese el nuevo nombre de pregunta siendo del mismo tipo que el anterior\n");
	cin>>str;
	test[id]=str;
	printf("Cambio Realizado\n");

}
void addTest(){
	int id,id2;
	do{
		printf("Ingrese el numero del tipo de pregunta que añadira al examen\n");
		printf("1. Pregunta calculada\n");
		printf("2. Pregunta calculada simple\n");
		printf("3. Pregunta calculada de opcion multiple\n");
		printf("4. Salir\n");
		scanf("%d",&id);
		show(id);
		printf("Ingrese el numero de la pregunta que añadira al examen\n");
		scanf("%d",&id2);
		id2-=1;
		switch(id){
			case 1:
				test.push_back(calculada[id2].name);
				valTest.push_back(id);
				break;
			case 2:
				test.push_back(calculadaS[id2].name);
				valTest.push_back(id);
				break;
			case 3:
				test.push_back(calculadaM[id2].name);
				valTest.push_back(id);
				break;
			case 4:
				menuTest();
				break;
			default:
				printf("Ingrese una opcion valida\n");
				break;
		}
	}while(id!=4);
}

void delTest(){
	int id;
	printf("Listado de preguntas del examen\n");
	for (int i = 0; i < test.size(); ++i)
		printf("%d %s\n",i+1,test[i]);
	printf("Ingrese el numero de la pregunta que eliminara del examen\n");
	scanf("%d",&id);
	id-=1;
	test.erase(test.begin()+id);
}

void evalTest(){
	double answer[4];
	float aux;
	int id=0;
	for (int i = 0; i < test.size(); ++i){
		cout<<i+1<<". "<<test[i]<<endl;
		switch(valTest[i]){
			case 1:
				id=0;
				while(test[i]!=calculada[id].name)
				    id++;

				answer[0]=evalFormula(calculada[id].text, calculada[id].formula, calculada[id].comodin, test[i]);
				printf("Ingrese su respuesta:\n");
				cin>>aux;
				if( aux<answer[0]+1  && aux>answer[0]-1){
					point+= calculada[id].points/10;
				}else{
					cout<<"La respuesta correcta es: "<<answer[0]<<endl;
					point+=0;
				}
				break;
			case 2:
				id=0;
				while(test[i]!=calculadaS[id].name)
				    id++;
				answer[0]=evalFormula(calculadaS[id].text, calculadaS[id].formula, calculadaS[id].comodin, test[i]);
				printf("Ingrese su respuesta:\n");
				cin>>aux;
				if(aux<answer[0]+1  && aux>answer[0]-1){
					point+= calculadaS[id].points/10;
				}else{
					cout<<"La respuesta correcta es: "<<answer[0]<<endl;
					point+=0;
				}
				break;
			case 3:
				id=0;
				while(test[i]!=calculadaM[id].name)
				    id++;
				for (int i = 0; i < 4; ++i){
					answer[i]=evalFormula(calculadaM[id].text, calculadaM[id].formula[i], calculadaM[id].comodin, test[i]);
					printf("%d. %lf \n",i+1,answer[i]);
				}
				printf("Ingrese su numero de respuesta:\n");
				cin>>aux;
				point+= calculadaM[id].points[(int)aux-1] / 10;
				break;

		}
	}
	point/=test.size();
	printf("Su calificacion es %.2f\n", point);
}
float evalFormula(string str, string formula, string comodines,string link){
	string aux;
	vector <string> temp;
	int j=0,n=0;
	double a[50];
	float val;
	for (int i = 0; i < comodines.length(); ++i){
		if (comodines[i] == ','){
			aux=comodines.substr(j,(i-j));
			temp.push_back(aux);
			j=i+1;
			val=searchComodin(aux,link);
			a[n]=(double)val;
			n++;
		}
	}
	int k=0;
	for (int i = 0; i < str.length(); ++i){
		if (str[i]=='{'){
			j=0;
			k=i+1;
			while(str[i]!='}') {
			    i++;
			    j++;
			}
			aux=str.substr(k,j-1);
			for (int k = 0; k < temp.size(); ++k){
				if(aux==temp[k]){
					cout<<a[k];
				}
			}
		}else{
			cout<<str[i];
		}
	}
	double valtemp[n];
	for (int i = 0; i < n; ++i){valtemp[i]=a[i];}
	printf("\n");

	FunctionParser fparser;
	fparser.AddConstant("pi", 3.1415926535897932);
	fparser.AddConstant("e", 2.718281828459045235360);
	comodines.pop_back();
	while(formula.find('{')!=std::string::npos) {
	    formula.erase(formula.find('{'),1);
	}
	while(formula.find('}')!=std::string::npos) {
	    formula.erase(formula.find('}'),1);
	}
	fparser.Parse(formula,comodines);
	double eval= fparser.Eval(valtemp);
	return eval;
}
float searchComodin(string name, string link){
	for (int i = 0; i < comodin.size(); ++i){
		if (comodin[i].link == link && comodin[i].name == name){
			return comodin[i].num;
		}
	}
	return 0;
}
//---EXAMEN---

//archivo
void guardarExamen(double calif){
	fstream fs;
	fs.open("examenes.txt",std::fstream::in | std::fstream::out | std::fstream::app);
	for (int i = 0; i < test.size(); ++i){
		fs<<test[i]<<",";
	}
	fs<<calif<<"?";
	fs.close();
}

//archivo
