#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <cmath>
#include "torneo.h"
#include "torneo.cpp"
#include <algorithm>
#include <cstdlib>
#include <math.h>
#include <cmath>
#define MAX_EQUIPOS 3
#define NO_EXISTE -1
using namespace std;

struct Equipo{

    Equipo() : PJ(0), PG(0), PP(0), PE(0), GF(0), GC(0), DF(0), puntos(0) {}
    char id[4];
    char nombre[32];
    int atk;
    int def;

    int puntos;

    int PJ; //partidos jugados
    int PG; //partidos ganados
    int PP; //partidos perdidos
    int PE; //partidos empatados
    int GF; //goles a favor
    int GC; //goles en contra
    int DF; //diferencia de goles
}bar;

struct Partido
{
	int numPartido;
	int eqL;
	int eqV;
	int eqLGoles;
	int eqVGoles;
	int fecha;
};
//1.AGREGUE LA STRUCT FECHA, POSEE DOS ARRAYS DE EQUIPOS, UNO PARA L Y OTRO PARA V, LOS EQUIPOS DEP
//POR CADA PARTIDO HAY UN ARRAY DE PUNTAJES DE CADA TIPO, SEGUN EL INDICE DE PARTIDO
struct Fecha{

    int fecha;
    Partido partidos[];
    Equipo locales[];
    Equipo visitantes[];

};
void  mostrar(Equipo eqHastaF[],int &cantEquip);
void OrdenarEquipos(Equipo eqHastaF[],int &cantPartidos);
void AgregarSiHayLugar(Equipo eqHastaF[],Equipo equipoAg, int &cantEquip);
void ModEquipo(Equipo eqHastaF[],int &indice,Equipo equipoAg);
void siEstaLoPisaSinoLoAgrega(Equipo eqHastaF[],Equipo equipoAg,int &cantEquip);
////////////////////////////////////////////////////////////////////////////////////
void CalcularCantFechas(int &cantEquip, int &cantFechas);
void MostrarOpcionesDeEdicion(Equipo listaDeEquipos[],int &cantEquip);
void MostrarPartidos(Partido listaPartidos[], Equipo listaDeEquipos[], int &cantPartidos, int &cantEquip, char filtro);
void MostrarPosiciones(Equipo listaDeEquipos[], int &cantEquip, Partido listaPartidos[], int &cantPartidos, Fecha listaFechas[], int &cantFechas);
void MostrarOpcionesDeSimulacion(Equipo listaDeEquipos[], int &cantEquip);
void JugarPartidos(Equipo equipos[], int &cantEquip,Partido listaPartidos[], int &cantTotalPartidos, Fecha listaFechas[]);
void AsignarPartido(Equipo equipos[], int &cantEquip, int &cantFechas, int &cantPartidosPorFecha, Partido listaPartidos[], Fecha listaFechas[]);
////////////////////////////////////////////////////////////////////////////
void CargarDatos(Equipo listaDeEquipos[],int &cantEquip);
void GuardarDatos(Equipo listaDeEquipos[]);
void MostrarDatos(Equipo listaDeEquipos[],int &cantEquip);
int BuscarMismaID(Equipo listaDeEquipos[],char id[]);
void ModificarEquipoExistente(Equipo listaDeEquipos[],int indice);
void AgregarEquipo(Equipo listaDeEquipos[],int &cantEquip);
void AgregarNuevoEquipo(Equipo listaDeEquipos[],char id[]);
void EliminarEquipo(Equipo listaDeEquipos[],int &cantEquip);
void BorrarYReordenar(Equipo listaDeEquipos[],int indice,int &cantEquip);
void Blanquear(Equipo listaDeEquipos[],int indice,int &cantEquip);

int main()
{
    Equipo listaDeEquipos[MAX_EQUIPOS];

  	int cantEquip = 0;

  	CargarDatos(listaDeEquipos,cantEquip);
    char opcion;
    bool salir = true;
    while(salir)
    {
        cout<<"1. Editar Equipos"<<endl;
        cout<<"2. Simular"<<endl;
        cout<<"0. Salir"<<endl;
        cin>>opcion;
        switch(opcion)
        {
            case '1':
                MostrarOpcionesDeEdicion(listaDeEquipos,cantEquip);
                break;
            case '2':
                MostrarOpcionesDeSimulacion(listaDeEquipos,cantEquip);
                break;
            case '0':
                salir = false;
                break;
            default:
                cout<<"Ingresaste un valor incorrecto"<<endl;
                break;

        }
    }

	return 0;
}
/////////////////////////////////////////////////////////////////NO TOCAR, TERMINADO///////////////////////////////////////////////////////////////////////////////////////
void MostrarOpcionesDeEdicion(Equipo listaDeEquipos[],int &cantEquip){

    bool finished = true;
    int opcion;
    while (finished)
        {
        cout <<"1.Agregar equipo"<<endl;
        cout <<"2.Eliminar equipo"<<endl;
        cout <<"3.Ver equipos"<<endl;
        cout <<"0.Volver"<<endl;
        cin>>opcion;
        switch (opcion)
            {
            case 1:
                AgregarEquipo(listaDeEquipos, cantEquip);
                break;
            case 2:
                EliminarEquipo(listaDeEquipos, cantEquip);
                break;
            case 3:
                MostrarDatos(listaDeEquipos, cantEquip);
                break;
            case 0:

                GuardarDatos(listaDeEquipos);
                finished = false;
                break;
            default:
                cout << "Opción inválida\n";
                break;
            }
        }
}

void CargarDatos(Equipo listaDeEquipos[],int &cantEquip){

    FILE * archivo;
    archivo = fopen("EQUIPOS.bin","rb");

    Equipo equipoVacio;
    equipoVacio.id[0]='\0';
    equipoVacio.nombre[0]='\0';
    equipoVacio.atk = NO_EXISTE;
    equipoVacio.def = NO_EXISTE;
    if(archivo == NULL){

        for(int i=0 ;i<MAX_EQUIPOS ;i++){

			listaDeEquipos[i]= equipoVacio;
        }

    }else{

        Equipo equipo;
        fread(&equipo,sizeof(Equipo),1,archivo);
        for(int i= 0; i < MAX_EQUIPOS;i++ ){
            if(equipo.id[0] != '\0') {

                cantEquip++;
                listaDeEquipos[i].atk = equipo.atk;
                listaDeEquipos[i].def = equipo.def;
                for(int h=0; h<4; h++){

                    listaDeEquipos[i].id[h]=equipo.id[h];
                    }
                for(int j = 0; j < 32; j++){

                    listaDeEquipos[i].nombre[j] = equipo.nombre[j];
                    }


                fread(&equipo,sizeof(Equipo),1,archivo);
            }else{

                listaDeEquipos[i] = equipoVacio;
            }
        }

        fclose(archivo);
    }

}

void GuardarDatos(Equipo listaDeEquipos[]){

    FILE * archivo;
    archivo = fopen("EQUIPOS.bin","wb");
    for(int i = 0;i < MAX_EQUIPOS;i++){

        Equipo equipoG;
        for(int h=0; h<4; h++){

            equipoG.id[h]=listaDeEquipos[i].id[h];
        }
        for(int j = 0; j < 32; j++){

            equipoG.nombre[j]=listaDeEquipos[i].nombre[j];
        }
        equipoG.atk = listaDeEquipos[i].atk;
        equipoG.def = listaDeEquipos[i].def;
        fwrite(&equipoG,sizeof(struct Equipo),1,archivo);
    }
    fclose(archivo);
}

void MostrarDatos(Equipo listaDeEquipos[],int &cantEquip){

    if(cantEquip != 0)
    {
        cout<<"Total de equipos->"<<cantEquip<<endl;
        for(int j = 0; j < MAX_EQUIPOS; j++)
        {

           if((listaDeEquipos[j].id[0] != '\0')) //&&(listaDeEquipos[j].id[1] != '\0') &&(listaDeEquipos[j].id[2] != '\0'))
           {
             cout<<"\n";
             cout<<"ID->"<<listaDeEquipos[j].id<<endl;
             cout<<"Nombre->"<<listaDeEquipos[j].nombre<<endl;
             cout<<"Atk->"<<listaDeEquipos[j].atk<<endl;
             cout<<"Def->"<<listaDeEquipos[j].def<<endl;
             cout<<"\n";
         }
       }
    }else cout<<"No hay equipos guardados vieja\n";

    /*ESTO ES PARA PROBAR TODAS LAS ID INDEPENDIENTEMENTE DE SI ES O NO VALIDO
    for(int h = 0; h < MAX_EQUIPOS; h++){

        cout<<"ID->"<<listaDeEquipos[h].id[0]<<listaDeEquipos[h].id[1]<<listaDeEquipos[h].id[2]<<endl;
    }*/
}

void EliminarEquipo(Equipo listaDeEquipos[], int &cantEquip){

	char id[4];
    char v[4] = "v";

	if(cantEquip != 0){
        cout << "Ingrese la ID del Equipo, Si no lo recuerda presione v" << endl;
        std::cin >> id;

        if( v[0] != id[0]){

            int indice = BuscarMismaID(listaDeEquipos, id);
            if (0 <= indice) BorrarYReordenar(listaDeEquipos, indice, cantEquip);
            else cout<<"No existe ese equipo"<<endl;
        }
    }else cout<<"No hay equipos para eliminar"<<endl;
}

void BorrarYReordenar(Equipo listaDeEquipos[],int indice,int &cantEquip){


        if(cantEquip-1 == indice) Blanquear(listaDeEquipos,indice,cantEquip);
        else {
              listaDeEquipos[indice] = listaDeEquipos[cantEquip - 1];
              Blanquear(listaDeEquipos,cantEquip-1,cantEquip);
            }
}

void Blanquear(Equipo listaDeEquipos[],int indice,int &cantEquip){

        for(int h=0; h<4; h++){

            listaDeEquipos[indice].id[h]='\0';
        }
        for(int j = 0; j < 32; j++){

            listaDeEquipos[indice].nombre[j]=' ';
        }
        listaDeEquipos[indice].atk = NO_EXISTE;
        listaDeEquipos[indice].def = NO_EXISTE;
        cantEquip--;
}

void AgregarEquipo(Equipo listaDeEquipos[], int &cantEquip){
    //Funcion que chequea si existe el equipo, si hay espacio y lo agrega....
	char id[4];
	char respuesta;


        cout << "Ingrese la ID del Equipo" << endl;
        std::cin >> id;
        int indice = BuscarMismaID(listaDeEquipos, id);
        if (0 <= indice)
        {

            cout << "Este equipo ya existe. Si desea modificarlo preisone 's' de lo contrario presione 'n'" << endl;
            std::cin >> respuesta;
            if (respuesta == 's') ModificarEquipoExistente(listaDeEquipos, indice);
        }
        else{
            if(!(cantEquip < MAX_EQUIPOS))cout << "no hay espacio, intente eliminar alguno de los equipos ya cargados" << endl;
            else{
                 AgregarNuevoEquipo(listaDeEquipos, id);
                 cantEquip++;
                }

            }

}

int BuscarMismaID(Equipo listaDeEquipos[],char id[]){

    int estaElEquip = NO_EXISTE;
    for(int i = 0;i < MAX_EQUIPOS;i++){

        if((listaDeEquipos[i].id[0] == id[0]) &&(listaDeEquipos[i].id[1] == id[1]) &&(listaDeEquipos[i].id[2] == id[2])) estaElEquip = i;
     }
    return estaElEquip;
}

void AgregarNuevoEquipo(Equipo listaDeEquipos[],char id[]){

   for(int i = 0;i < MAX_EQUIPOS; i++){
        int unoSoloAgrego = MAX_EQUIPOS;
        if((listaDeEquipos[i].id[0] == '\0')){// &&(listaDeEquipos[i].id[1] == '@') &&(listaDeEquipos[i].id[2] &&(listaDeEquipos[i].id[2] == '@'))){

            strncpy(listaDeEquipos[i].id, id, 4);

            cout<<"ingrese nombre nuevo"<<endl;
            cin>>listaDeEquipos[i].nombre;

            cout<<"ingrese Ataque nuevo"<<endl;
            cin>>listaDeEquipos[i].atk;

            cout<<"ingrese Defensa nuevo"<<endl;
            cin>>listaDeEquipos[i].def;
            i = unoSoloAgrego;
        }
    }
 }

void ModificarEquipoExistente(Equipo listaDeEquipos[],int indice){

        char res;
        cout<<"desea modificar el nombre acttual? nombre-> "<<listaDeEquipos[indice].nombre<<" "<<"preisone 's' de lo contrario presione 'n'"<<endl;
        cin>>res;
        if(res == 's'){

            cout<<"ingrese nombre nuevo"<<endl;
            cin>>listaDeEquipos[indice].nombre;
        }
        cout<<"desea modificar el Ataque? Ataque-> "<<listaDeEquipos[indice].atk<<" "<<"preisone 's' de lo contrario presione 'n'"<<endl;
        cin>>res;
        if(res == 's'){

            cout<<"ingrese Ataque nuevo"<<endl;
            cin>>listaDeEquipos[indice].atk;
        }
        cout<<"desea modificar la Defensa acttual? Defensa-> "<<listaDeEquipos[indice].def<<" "<<"preisone 's' de lo contrario presione 'n'"<<endl;
        cin>>res;
        if(res == 's'){

            cout<<"ingrese Defensa nuevA"<<endl;
            cin>>listaDeEquipos[indice].def;
        }
}

/////////////////////////////////////////////////////////////////SEGUNDA PARTE///////////////////////////////////////////////////////////////////////////////////////

void MostrarOpcionesDeSimulacion(Equipo listaDeEquipos[], int &cantEquip){

    int cantPartidos = 0;
    int cantFechas = 0;
    int cantPartidosPorFechas = 0;

    if(cantEquip > 1){

        CalcularCantFechas(cantEquip,cantFechas);

        cantPartidosPorFechas = (int)floor(cantEquip/2);
        //2.CREO EL ARRAY DE FECHAS, LE PASO +1 PORQUE DESPUES BUSCO POR INDICE Y NO HAY FECHA QUE TENGA ID 0
        Fecha listaFechas[cantFechas+1];
        Partido listaPartidos[cantPartidosPorFechas*cantFechas];
        //3.MANDO LAS FECHAS AL ASIGNAR PARTIDO(MODIFICAR ARRIBA Y ABAJO)
        AsignarPartido(listaDeEquipos, cantEquip, cantFechas, cantPartidosPorFechas, listaPartidos, listaFechas);

        cantPartidos = cantPartidosPorFechas*cantFechas;
        char op;
        bool sa = true;
        while(sa)
        {
            cout<<"1. Ver tabla de posiciones"<<endl;
            cout<<"2. Ver partidos por equipo"<<endl;
            cout<<"3. Ver partidos por fecha"<<endl;
            cout<<"0. Volver"<<endl;
            cin>>op;

            switch(op)
            {
                case '1':
                    //8.ENVIO A  LAS POSICIONES LA LISTA DE FECHAS CON SU CANTIDAD
                    MostrarPosiciones(listaDeEquipos, cantEquip, listaPartidos, cantPartidos, listaFechas, cantFechas);
                    break;
                case '2':
                    MostrarPartidos(listaPartidos, listaDeEquipos, cantPartidos, cantEquip, 'e');
                    break;
                case '3':
                    MostrarPartidos(listaPartidos, listaDeEquipos, cantPartidos, cantEquip, 'f');
                    break;
                case '0':
                    sa = false;
                    break;
                default:
                    cout<<"Ingresaste un valor incorrecto"<<endl;
                    break;
            }

        }
    }else {cout<<"No hay equipos suficientes"<<endl;}

}

void CalcularCantFechas(int &cantEquip,int &cantFechas){

       if(cantEquip%2 == 0){//EN EL CASO EN EL QUE LA CANTIDAD DE EQUIPOS SEA PAR

                cantFechas = cantEquip-1;
        }
        else{//EN EL CASO EN EL QUE LA CANTIDAD DE EQUIPOS SEA IMPAR

                cantFechas = cantEquip;
        }

}

void AsignarPartido(Equipo equipos[], int &cantEquip, int &cantFechas, int &cantPartidosPorFecha, Partido listaPartidos[], Fecha listaFechas[]){

			int local = 0;
			int visitante = 0;
            int id = 0;
			for(int i = 0; i < cantFechas; i++)
			{
			    //4.AGREGO A LA LISTA DE FECHAS EL ID DE LA FECHA CORRESPONDIENTE
			    listaFechas[i].fecha = i+1;
				for(int partido = 0; partido < cantPartidosPorFecha; partido++)
				{

					generarPartido(cantEquip, i+1, partido+1, local, visitante);
					listaPartidos[id].eqL = local;
					listaPartidos[id].eqV = visitante;
					listaPartidos[id].fecha = i+1;
					listaPartidos[id].numPartido = partido+1;
					//5.AGREGO EL PARTIDO A LA LISTA DE FECHAS
                    listaFechas[i].partidos[partido] = listaPartidos[id];
					id++;
                }
			}
    //6.MANDO LA LISTA DE FECHAS A LA GENERACION DE PARTIDOS (MODIFICAR ARRIBA Y ABAJO)
	JugarPartidos(equipos, cantEquip ,listaPartidos, id, listaFechas);
}

void JugarPartidos(Equipo equipos[],int &cantEquip,Partido listaPartidos[], int &cantTotalPartidos, Fecha listaFechas[]){

        for(int i = 0; i < cantEquip; i++){

            equipos[i].PJ = bar.PJ;
            equipos[i].PG = bar.PG;
            equipos[i].PP = bar.PP;
            equipos[i].PE = bar.PE;
            equipos[i].GF = bar.GF;
            equipos[i].GC = bar.GC;
            equipos[i].DF = bar.DF;
            equipos[i].puntos = bar.puntos;
        }

        for(int i = 0; i < cantTotalPartidos; i++){

            int atkL = equipos[listaPartidos[i].eqL].atk;
            int defL = equipos[listaPartidos[i].eqL].def;
            int atkV = equipos[listaPartidos[i].eqV].atk;
            int defV = equipos[listaPartidos[i].eqV].def;

            simularPartido(atkL, defL,atkV, defV, listaPartidos[i].eqLGoles, listaPartidos[i].eqVGoles);

            equipos[listaPartidos[i].eqL].PJ++;
            equipos[listaPartidos[i].eqL].GF += listaPartidos[i].eqVGoles;
            equipos[listaPartidos[i].eqL].GC += listaPartidos[i].eqLGoles;
            equipos[listaPartidos[i].eqL].DF += listaPartidos[i].eqVGoles - listaPartidos[i].eqLGoles;

            equipos[listaPartidos[i].eqV].PJ++;
            equipos[listaPartidos[i].eqV].GF += listaPartidos[i].eqVGoles;
            equipos[listaPartidos[i].eqV].GC += listaPartidos[i].eqLGoles;
            equipos[listaPartidos[i].eqV].DF += listaPartidos[i].eqVGoles - listaPartidos[i].eqLGoles;

            //7. FECHA ACTUAL:
            //   listaFechas[listaPartidos[i].fecha]
            //   PARTIDO ACTUAL SEGUN LA FECHA:
            //   listaFechas[listaPartidos[i].fecha].partidos[listaPartidos[i].numPartido]
            //   EQUIPO LOCAL SEGUN LA FECHA Y EL PARTIDO:
            //   listaFechas[listaPartidos[i].fecha].locales[listaPartidos[i].numPartido]
            //   EQUIPO VISITANTE SEGUN LA FECHA Y EL PARTIDO:
            //   listaFechas[listaPartidos[i].fecha].visitantes[listaPartidos[i].numPartido]

            if(listaPartidos[i].eqLGoles > listaPartidos[i].eqVGoles){
                equipos[listaPartidos[i].eqL].puntos += 3;
                equipos[listaPartidos[i].eqL].PG++;
                equipos[listaPartidos[i].eqV].PP++;
                ///listaFechas[listaPartidos[i].fecha].eqFecha[listaPartidos[i].eqL].puntos = equipos[listaPartidos[i].eqL].puntos;
                listaFechas[listaPartidos[i].fecha].locales[listaPartidos[i].numPartido].puntos = equipos[listaPartidos[i].eqL].puntos;
                listaFechas[listaPartidos[i].fecha].locales[listaPartidos[i].numPartido].PG = equipos[listaPartidos[i].eqL].PG;
                listaFechas[listaPartidos[i].fecha].visitantes[listaPartidos[i].numPartido].PP = equipos[listaPartidos[i].eqV].PP;

            }
            if(listaPartidos[i].eqLGoles < listaPartidos[i].eqVGoles){
                equipos[listaPartidos[i].eqV].puntos += 3;
                equipos[listaPartidos[i].eqV].PG++;
                equipos[listaPartidos[i].eqL].PP++;

                listaFechas[listaPartidos[i].fecha].visitantes[listaPartidos[i].numPartido].puntos = equipos[listaPartidos[i].eqV].puntos;
                listaFechas[listaPartidos[i].fecha].visitantes[listaPartidos[i].numPartido].PG = equipos[listaPartidos[i].eqV].PG;
                listaFechas[listaPartidos[i].fecha].locales[listaPartidos[i].numPartido].PP = equipos[listaPartidos[i].eqL].PP;

            }
            if(listaPartidos[i].eqLGoles == listaPartidos[i].eqLGoles){
                equipos[listaPartidos[i].eqL].puntos += 1;
                equipos[listaPartidos[i].eqV].puntos += 1;
                equipos[listaPartidos[i].eqL].PE++;
                equipos[listaPartidos[i].eqV].PE++;

                listaFechas[listaPartidos[i].fecha].locales[listaPartidos[i].numPartido].puntos = equipos[listaPartidos[i].eqL].puntos;
                listaFechas[listaPartidos[i].fecha].visitantes[listaPartidos[i].numPartido].puntos = equipos[listaPartidos[i].eqV].puntos;
                listaFechas[listaPartidos[i].fecha].locales[listaPartidos[i].numPartido].PE = equipos[listaPartidos[i].eqL].PE;
                listaFechas[listaPartidos[i].fecha].visitantes[listaPartidos[i].numPartido].PE = equipos[listaPartidos[i].eqV].PE;
            }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MostrarPosiciones(Equipo listaDeEquipos[], int &cantEquip, Partido listaPartidos[], int &cantPartidos, Fecha listaFechas[], int &cantFechas)
{
        int opcion;
        Equipo eqHastaF[cantEquip];
        for(int k = 0; k <cantEquip; k++){

            eqHastaF[k].id[0] = '\0';
        }

		cout<<"Ingrese una fecha"<<endl;
		cout<<"Las fechas disponibles son: ";
		for(int i= 0; i <cantFechas-1;i++){

            cout<<i+1<<", ";
		}
		cout<<cantFechas<<endl;
		cin>>opcion;

        if(cin)
        {
            cout<<"Tabla de posiciones : "<<opcion<<endl;


           if(opcion <= cantFechas){

                for(int i=0; i<opcion; i++){

                    for(int j=0; j<sizeof(listaFechas[i].partidos); j++){
                            ///eqHastaF

                        siEstaLoPisaSinoLoAgrega(eqHastaF, listaDeEquipos[listaFechas[i].partidos[j].eqL],cantEquip);
                        siEstaLoPisaSinoLoAgrega(eqHastaF, listaDeEquipos[listaFechas[i].partidos[j].eqV],cantEquip);
                    }

                }
                OrdenarEquipos(eqHastaF,cantPartidos);
                mostrar(eqHastaF, cantEquip);

            }
            else{
                cout<<"Ingrese una fecha válida"<<endl;
            }

    }
}

void siEstaLoPisaSinoLoAgrega(Equipo eqHastaF[],Equipo equipoAg,int &cantEquip){

    int indice = BuscarMismaID(eqHastaF, equipoAg.id);
    if (0 <= indice){

        ModEquipo(eqHastaF, indice,equipoAg);
    }else{
        AgregarSiHayLugar(eqHastaF, equipoAg,cantEquip);
    }
}

void ModEquipo(Equipo eqHastaF[],int &indice,Equipo equipoAg){

    eqHastaF[indice].atk =equipoAg.atk;
    eqHastaF[indice].def =equipoAg.def;
    for(int i =0;i<4;i++){

        eqHastaF[indice].id[i] =equipoAg.id[i];
    }
    for(int j =0;j<32;j++){

        eqHastaF[indice].nombre[j] =equipoAg.nombre[j];
    }
}

void AgregarSiHayLugar(Equipo eqHastaF[],Equipo equipoAg, int &cantEquip){

    for(int k =0; k< cantEquip; k++){

        if(eqHastaF[k].id[0] == '\0'){

            eqHastaF[k].atk =equipoAg.atk;
            eqHastaF[k].def =equipoAg.def;
            for(int i =0;i<4;i++){

                eqHastaF[k].id[i] =equipoAg.id[i];
            }
            for(int j =0;j<32;j++){

                eqHastaF[k].nombre[j] =equipoAg.nombre[j];
            }
        }
    }
}

void OrdenarEquipos(Equipo eqHastaF[], int &cantPartidos){

    for(int i=1;i<cantPartidos;i++)
    {
        for(int j=0;j<cantPartidos-i;j++)
        {
            if(eqHastaF[j].GF < eqHastaF[j+1].GF)
            {
                Equipo temp = eqHastaF[j];
                eqHastaF[j] = eqHastaF[j+1];
                eqHastaF[j+1] = temp;
            }
        }
    }

    for(int i=1;i<cantPartidos;i++)
    {
        for(int j=0;j<cantPartidos-i;j++)
        {
            if(eqHastaF[j].DF < eqHastaF[j+1].DF)
            {
                Equipo temp = eqHastaF[j];
                eqHastaF[j] = eqHastaF[j+1];
                eqHastaF[j+1] = temp;
            }
        }
    }

    for(int i=1;i<cantPartidos;i++)
    {
        for(int j=0;j<cantPartidos-i;j++)
        {
            if(eqHastaF[j].puntos < eqHastaF[j+1].puntos)
            {
                Equipo temp = eqHastaF[j];
                eqHastaF[j] = eqHastaF[j+1];
                eqHastaF[j+1] = temp;
            }
        }
    }
}

void  mostrar(Equipo eqHastaF[],int &cantEquip){

       cout<<"Equipo"<<"\tNombre\tPuntos\tPJ\tPG\tPE\tPP\tGF\tGC\tDG"<<endl;
       for(int i =0; i< cantEquip; i++){

            cout<<eqHastaF[i].id<<"\t"<<eqHastaF[i].nombre<<"\t"<<eqHastaF[i].PJ <<"\t "<<eqHastaF[i].PG<<"\t "<<eqHastaF[i].PE <<"\t"<<eqHastaF[i].PP <<"\t"<<eqHastaF[i].GF <<"\t"<<eqHastaF[i].GC <<"\t"<<eqHastaF[i].DF <<endl;
            i++;
       }
}

void MostrarPartidos(Partido listaPartidos[], Equipo listaDeEquipos[], int &cantPartidos, int &cantEquip, char filtro){
	if(cantPartidos > 0)
    {
          char opcionId[4];
          int opcionFecha;

          if(filtro == 'e')
            {
               cout<<"Ingrese ID de un equipo"<<endl;
               cout<<"Los equipos disponibles son: "<<endl;
               for(int i = 0; i < cantEquip-1; i++){

                    cout<<listaDeEquipos[i].id<<", ";
               }
               cout<<listaDeEquipos[cantEquip-1].id<<endl;
               cin>>opcionId;
               cout<<"Partidos de: "<<opcionId<<endl;
            }
          if(filtro == 'f')
          {
               cout<<"Ingrese una fecha: "<<endl;
               cout<<"Las fechas disponibles son "<<endl;
               /*for(int i = 0; i < cantEquip-1; i++){

                    cout<<listaDeEquipos[i].id<<", ";
               }*/
               cout<<listaDeEquipos[cantEquip-1].id<<endl;
               cin>>opcionFecha;
               cout<<"Partidos de la fecha: "<<opcionFecha<<endl;
          }

          for(int i=0; i<cantPartidos; i++)
          {
               if( (filtro == 'e' && (strcmp(listaDeEquipos[listaPartidos[i].eqL].id, opcionId) == 0 || strcmp(listaDeEquipos[listaPartidos[i].eqV].id, opcionId) == 0 )) ||
                (filtro == 'f' && listaPartidos[i].fecha == opcionFecha ))
               {
                    cout<<""<<listaDeEquipos[listaPartidos[i].eqL].id<<" "<<listaDeEquipos[listaPartidos[i].eqL].nombre<<" "<<listaPartidos[i].eqLGoles<<" - "<<listaPartidos[i].eqVGoles<<listaDeEquipos[listaPartidos[i].eqV].id<<" "
                    <<listaDeEquipos[listaPartidos[i].eqV].nombre<<" "<<endl;
               }
          }
    }
}

