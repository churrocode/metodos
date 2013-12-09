#include "heuristica.h"
#include <iostream>

pair<double,int> calcularCostoEstructura(Puente& puente, vector<double>& posiciones_pilares, vector<double>& costo_subestructuras, int n_del_principio) {
	int cant_pilares = 0;
	double costo_estructura = 0.0;
    puente.generarMatriz();
	puente.resolverPuente();
	int n = puente.getN();
	if(!puente.esSeguro()) {
		if (n == 2) {
			cout << "El puente no es seguro y ya no se puede subdividir. Lo lamento.\n";
			return pair<double, int>(1/0.0, -1);
		}
		cant_pilares += 1;
		int fuerza_absoluta_max = puente.getMatriz().getFuerzaMax().second; // numeracion de la fuerza maxima en el puente
		// colocar pilar debajo de la junta con la fuerza max incidiendo sobre ella, o casi, si el resultado es impar o estoy en la punta
		int junta_incidente_fmax = puente.junta(fuerza_absoluta_max);
		int posicion_del_pilar = (junta_incidente_fmax/2) +1;
		int secciones_a_izq = posicion_del_pilar+1;
		//cout << "la fuerza máxima se ejerce sobre la junta " << junta_incidente_fmax << "o sea en la carga " << posicion_del_pilar <<endl;
		if (secciones_a_izq % 2 != 0) {//el resultado es impar
			if (posicion_del_pilar <= n-3) { //lo puedo correr uno a la der y me quedan subestructuras pares
				posicion_del_pilar += 1;
				secciones_a_izq += 1;
			} else { //lo corro a la izq
				posicion_del_pilar -= 1;
				secciones_a_izq -= 1;
			}
		} 
		if (secciones_a_izq == 0) { //estoy en alguna de las dos puntas, me corro dos para adentro
			posicion_del_pilar = 1;
			secciones_a_izq = 2;
		} else if (secciones_a_izq == n) {
			posicion_del_pilar = n-3;
			secciones_a_izq = n-2;
		}
		//construimos los puentes
		num length = puente.getLength();
		num height = puente.getH();
		int n_1 = secciones_a_izq;
		int n_2 = n - n_1;
		//cout << "dividi así: " << n_1 << ' ' << n_2 << endl;
		num span_1 = n_1*length;
		num span_2 = n_2*length;
		int posicion_del_pilar_absoluta = n_del_principio + posicion_del_pilar +1;
		//cout << "estoy empezando en n = " << n_del_principio << " y voy a pushear " << posicion_del_pilar << " que en absoluta es " << posicion_del_pilar_absoluta <<endl;
		posiciones_pilares.push_back(posicion_del_pilar_absoluta);

		num costo_pilar = puente.getCostoPilar();
		num fMax = puente.getFMax();
		vector<double> cargas_nuevas_1,cargas_nuevas_2;
		vector<double> cargas_puente = puente.getCargas(); 
		for(int i = 0; i < cargas_puente.size(); ++i) {
			if(i < posicion_del_pilar)
				cargas_nuevas_1.push_back(cargas_puente[i]);
			else if(i > posicion_del_pilar) {
				cargas_nuevas_2.push_back(cargas_puente[i]);
			}
		}

		//cout << "puente 1 : n: " << n_1 << endl;
		//if (cargas_nuevas_1.size() == 0) cout << "!! EL PUENTE 1 NO TIENE CARGA\n";
		//cout << "|cargas_1|: " << cargas_nuevas_1.size() << endl;
		//subpuente izquierdo
		Puente puente_1 = Puente(n_1,span_1,height,costo_pilar,fMax,cargas_nuevas_1);
		pair<double,int> costo_sub_estructura_1 = calcularCostoEstructura(puente_1, posiciones_pilares, costo_subestructuras, n_del_principio);
		if (costo_sub_estructura_1.second == -1) {
			return pair<double, int>(1/0.0, -1);
		}
		//cout << "puente 2 : n: " << n_2 << endl;
		//if (cargas_nuevas_2.size() == 0) cout << "!! El PUENTE 2 NO TIENE CARGA\n";
		//cout << "|cargas_2|: " << cargas_nuevas_2.size() << endl;
		//subpuente derecho
		Puente puente_2 = Puente(n_2,span_2,height,costo_pilar,fMax,cargas_nuevas_2);
		pair<double,int> costo_sub_estructura_2 = calcularCostoEstructura(puente_2, posiciones_pilares, costo_subestructuras, posicion_del_pilar_absoluta);
		if (costo_sub_estructura_2.second == -1) {
			return pair<double, int>(1/0.0, -1);
		}
		cant_pilares += costo_sub_estructura_1.second + costo_sub_estructura_2.second;
		costo_estructura += costo_sub_estructura_1.first + costo_sub_estructura_2.first;
	} else {
		costo_estructura += puente.costo();
        costo_subestructuras.push_back(costo_estructura);
    }
	
	pair<double,int> costo_y_pilares(costo_estructura,cant_pilares);

	return costo_y_pilares;
}

pair<double, pair< vector<double>, vector<double> > > costoTotal(Puente& puente) {
	double costo_pilar = puente.getCostoPilar();
    vector<double> posiciones_pilares;
    vector<double> costo_subestructuras;
	pair<double,int> costo_y_pilares = calcularCostoEstructura(puente, posiciones_pilares, costo_subestructuras, 0);

	double costo_estructuras = costo_y_pilares.first;
	int cant_pilares = costo_y_pilares.second;
    int cant_subestructuras = cant_pilares+1;
    double costo_total = costo_estructuras + cant_subestructuras * costo_pilar;
    pair<vector<double>, vector<double> > pilares_y_sub;
    pilares_y_sub.first = posiciones_pilares;

    pilares_y_sub.second = costo_subestructuras;
    pair<double, pair< vector<double>, vector<double> > > res;
    res.first = costo_total;
    res.second = pilares_y_sub;
	return res;
}
