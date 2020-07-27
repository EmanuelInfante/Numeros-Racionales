/* Hola, una breve explicacion acerca de la funcionalidad de esta programacion con respecto al calculo de numeros racionales: Este programa es capaz
de pedir al usuario acerca de que tipo de operacion desea realizar con respecto a los dos terminos en la ecuacion (dos fracciones) y despues de selec
-ccionar el tipo de operacion le pide al usuario valores para esas fracciones, y procede a hacer los calculos. Ademas cuenta con un metodo de simpli
-ficacion para dichas fracciones. Sin nada mas que acotar se da inicio al programa */
#include <iostream>
#include <cmath>

//Definimos si estamos en windows o linux para definir funcion d limpiar pantalla
#ifdef WIN32
    #define cls() system("cls");
#else
   #define cls() system("clear");
#endif // WIN32

using namespace std;

struct numeroRacional
{
    /*Estructura que contiene lso valores de un número racional*/
    int numerador;
    int denominador;
};

//Declaramos funciones
void tomarValoresNumeros(struct numeroRacional *, struct numeroRacional *);
void tomarValoresNumeros(struct numeroRacional *numero1);
bool operacionRealizar();
void imprimirResultados(struct numeroRacional);
struct numeroRacional sumarRestarNumeros(struct numeroRacional, struct numeroRacional, char);
struct numeroRacional multiplicarNumeros(struct numeroRacional, struct numeroRacional);
struct numeroRacional dividirNumeros(struct numeroRacional, struct numeroRacional);
void simplificarResultado(struct numeroRacional *);
bool verificarEquipolenciaNumeros(struct numeroRacional, struct numeroRacional);
int verificarNumeroMasPequeno(struct numeroRacional);



int main()
{

    cout << "Bienvenido al programa para calcular operaciones con números racionales" << endl;


    while(true)
    {
        //Ciclo infinito en el que se realizan las operaciones

        //Realizamos la operación
        if(operacionRealizar() == false)
            break;

    }
    return 0;
}


void tomarValoresNumeros(struct numeroRacional *numero1, struct numeroRacional *numero2)
{
    /*Se encarga de llenar con los valores obtenidos los números*/

    cout << "Ingresa el valor del primer numerador: ";
    cin >> numero1 -> numerador;

    cout << "Ingresa el valor del segundo denominador: ";
    cin >> numero1 -> denominador;

    cout << "Ingresa el valor del primer numerador: ";
    cin >> numero2 -> numerador;

    cout << "Ingresa el valor del segundo denominador: ";
    cin >> numero2 -> denominador;

    cls();
}


void tomarValoresNumeros(struct numeroRacional *numero1)
{
    /*Se encarga de llenar con los valores obtenidos el número pasado por parámetro*/

    cout << "Ingresa el valor del numerador: ";
    cin >> numero1 -> numerador;

    cout << "Ingresa el valor del denominador: ";
    cin >> numero1 -> denominador;

    cls();
}


bool operacionRealizar()
{
    /*Inspecciona que operación quiere realizar el usuario y la ejecuta, retorna false si el programa ya no
    debe de ejecutarse*/
    struct numeroRacional numero1, numero2;

    cout << "1) Suma" << endl << "2) Resta" << endl;
    cout << "3) Multiplicación" << endl << "4) Divición" << endl;
    cout << "5) Simplificar Valor" << endl << "6) Revisar Equipolencía de fracciones" << endl;
    cout << "7) Salir del programa" << endl;

    cout << "Ingrese el número de la operación correspondiente: ";

    int opcionSeleccionada;
    cin >> opcionSeleccionada;

    cls();

    //Verifica que la opción sea valida y necesite dos valores, para llamar a la función tomarValores
    if((opcionSeleccionada >=1 && opcionSeleccionada <= 4) || opcionSeleccionada == 6)
    {
        //Simplificamos el segundo número
        simplificarResultado(&numero2);
        tomarValoresNumeros(&numero1, &numero2);
    }


    //Si la opción es igual a 4, no es necesario obtener dos valores, ya que solo se debe simplificar
    else if(opcionSeleccionada == 5)
        tomarValoresNumeros(&numero1);

    //Simplificamos los números antes de realizar una operación
    simplificarResultado(&numero1);

    //Llamamos a la operación correspondiente
    switch(opcionSeleccionada)
    {
    case 1:
         imprimirResultados(sumarRestarNumeros(numero1, numero2, '+'));
        break;
    case 2:
        imprimirResultados(sumarRestarNumeros(numero1, numero2, '-'));
        break;
    case 3:
        imprimirResultados(multiplicarNumeros(numero1, numero2));
        break;
    case 4:
        imprimirResultados(dividirNumeros(numero1, numero2));
        break;
    case 5:
        simplificarResultado(&numero1);
        imprimirResultados(numero1);
        break;
    case 6:
        if(verificarEquipolenciaNumeros(numero1, numero2))
            cout << "Son Equipolentes" << endl;
        else
            cout << "No son Equipolentes" << endl;
        break;
    case 7:
        return false;
    default:
        system("clear");
        cout << "Operación invalida" << endl << endl;
        break;

    }

    return true;
}


void imprimirResultados(struct numeroRacional resultado)
{
    /*Función que se encarga de mostrar los resultados de las opciones 1 a 5*/

    simplificarResultado(&resultado);
    //Imprimimos el resiltado dependiendo del caso
    if(resultado.numerador != 0 && resultado.denominador == 1)
        cout << "El resultado es: " << resultado.numerador << endl;
    else if(resultado.numerador != 0 && resultado.denominador != 0)
        cout << "El resultado es: " << resultado.numerador << "/" << resultado.denominador << endl;
    else if(resultado.numerador == 0 && resultado.denominador != 0)
        cout << "El resultado es: 0" << endl;
    else
        cout << "El resultado es INFINITO" << endl;
}


struct numeroRacional sumarRestarNumeros(struct numeroRacional numero1, struct numeroRacional numero2, char operacion)
{
    /*Función que se encarga de sumar/restar los valores de un número racional, recibe la operación por parámetro*/
    int aux1Numerador, aux2Numerador;
    struct numeroRacional resultado;

    //Realizamos la operación en X
    aux1Numerador = numero1.numerador * numero2.denominador;
    aux2Numerador = numero1.denominador * numero2.numerador;

    //Completamos smando o restando los resultados
    resultado.numerador = (operacion == '+')? aux1Numerador + aux2Numerador : aux1Numerador - aux2Numerador;
    resultado.denominador = numero1.denominador * numero2.denominador;

    return resultado;
}


struct numeroRacional multiplicarNumeros(struct numeroRacional numero1, struct numeroRacional numero2)
{
    /*Función que realiza la multiplicación de dos numeros racionales*/
    struct numeroRacional resultado;

    resultado.numerador = numero1.numerador * numero2.numerador;
    resultado.denominador = numero1.denominador * numero2.denominador;

    return resultado;
}


struct numeroRacional dividirNumeros(struct numeroRacional numero1, struct numeroRacional numero2)
{
    /*Función que divide dos números racionales*/
    struct numeroRacional resultado;

    //Realizamos la operación en X
    resultado.numerador = numero1.numerador * numero2.denominador;
    resultado.denominador = numero1.denominador * numero2.numerador;

    return resultado;
}


void simplificarResultado(struct numeroRacional *numeroSimplificar)
{
    /*Función que simplifica el numero que se le pase*/

    //Determinamos la cantidad de negativos en el número
    int numeroMasPequeno, cantidadNegativos = 0;

    if(numeroSimplificar ->numerador < 0)
        cantidadNegativos++;
    if(numeroSimplificar ->denominador < 0)
        cantidadNegativos++;

    /*Le aplicamos valor absoluto a todo el número racional, esto con el fin de evitar problemas en los cálculos de
    Simplificación, al final de la función se agregan los negativos*/
    numeroSimplificar ->numerador = abs(numeroSimplificar ->numerador);
    numeroSimplificar ->denominador = abs(numeroSimplificar ->denominador);

    //Verificamos cual es el número de la fracción msa pequeño para realizar la simplificación
    numeroMasPequeno = verificarNumeroMasPequeno(*numeroSimplificar);

    //Creamos controlador del ciclo while, que se repite siempre que un número sea simplificable
    bool seguirSimplificando = true;

    while(seguirSimplificando)
    {
        for(int i = 2; i <= numeroMasPequeno; i++)
        {

            //Verificamos si el numero es divisible, en caso que si, divide el número y sigue simplificando
            if(int(numeroSimplificar ->numerador / i) == float(numeroSimplificar ->numerador) / i && int(numeroSimplificar ->denominador / i) == float(numeroSimplificar ->denominador) / i)
            {

                //SI el número es simplificable, entonces dividimos y volvemos a iniciar el ciclo
                numeroSimplificar ->numerador /= i;
                numeroSimplificar ->denominador /= i;
                numeroMasPequeno = verificarNumeroMasPequeno(*numeroSimplificar);
                seguirSimplificando = true;
                break;
            }else
                seguirSimplificando = false;
        }

        if(numeroSimplificar ->numerador == 1 || numeroSimplificar ->denominador == 1 || numeroSimplificar ->numerador == 0 || numeroSimplificar ->denominador == 0)
            break;
    }

    //Se agregan los negativos si son necesarios
    if(cantidadNegativos == 1)
        numeroSimplificar ->numerador *= -1;
}


bool verificarEquipolenciaNumeros(struct numeroRacional numero1, struct numeroRacional numero2)
{
    /*Revisa si dos fracciones son equipolentes, para ello multiplica el numerador del primer numero con el
    denominador del segundo número, luego hace el proceso contrario, si son iguales entonce sel número es
    Igual/Equipolente*/

    if(numero1.numerador * numero2.denominador == numero1.denominador * numero2.numerador)
        return true;

    return false;
}


int verificarNumeroMasPequeno(struct numeroRacional numero)
{
    /*Función que recibe un número racional, y que dvielve el valor mas pequeño entre el numerador y denominador*/
    if(numero.numerador < numero.denominador)
        return numero.numerador;
    //retorna el denomidaor, ya que o el denominador es mas pequeño que el numerador, o son iguales
    return numero.denominador;

}
