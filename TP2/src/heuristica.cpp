#include "heuristica.h"

/*double calcularCosto(Puente& puente) {
	num costo = 0;
	puente.resolverPuente();
	if(!puente.esSeguro()) {
		num fuerza_absoluta_max = puente.getMatriz().getFuerzaMax().second; // numeracion de la fuerza maxima en el puente
		// colocar pilar debajo de la junta con la fuerza max incidiendo sobre ella
		int junta_incidente_fmax = puente.junta(fuerza_absoluta_max);
		int secciones_a_derecha = (junta_incidente_fmax / 2) + 1;
		if(secciones_a_derecha % 2 != 0) {
			junta_incidente_fmax += (secciones_a_derecha > 2) ? 1 : -1;
			secciones_a_derecha = (junta_incidente_fmax / 2) + 1;
		}

		int n = puente.getN();
		num length = puente.getLength();
		num height = puente.getH();
		int n_1 = secciones_a_derecha;
		int n_2 = n-secciones_a_derecha;
		num span_1 = n_2*length;
		num span_2 = n_1*length;
		num costo_pilar = puente.getCostoPilar();
		num fMax = puente.getFmax();
		//int n, double span, double h, double costoPilar, double fMax, vector<double>& cargas
		vector<double> cargas_nuevas_1,cargas_nuevas_2;
		vector<double> cargas_puente = puente.getCargas(); // abstraer con una funcion lo de generar los nuevos valores

		for(int i = 0; i < cargas_puente.size(); ++i) {
			if(i < junta_incidente_izq)
				cargas_nuevas_2.push_back(cargas_puente[i]);
			else if(i > junta_incidente_izq) {
				cargas_nuevas_1.push_back(cargas_puente[i]);
			}
		}
		
		Puente puente_1 = Puente(n_1,span_1,height,costo_pilar,fMax,cargas_nuevas_1);
		Puente puente_2 = Puente(n_2,span_2,height,costo_pilar,fMax,cargas_nuevas_2);			
		costo = calcularCosto(puente_1) + calcularCosto(puente_2)
	}
	
	//calcular la sumatoria de links etc
	costo += puente.costo();

	return costo;
}*/

pair<double,int> calcularCostoEstructura(Puente& puente, vector<double>& posiciones_pilares, vector<double>& costo_subestructuras) {
	int cant_pilares = 0;
	double costo_estructura = 0.0;
        puente.generarMatriz();
	puente.resolverPuente();
	if(!puente.esSeguro()) {
		cant_pilares += 1;
		int fuerza_absoluta_max = puente.getMatriz().getFuerzaMax().second; // numeracion de la fuerza maxima en el puente
		// colocar pilar debajo de la junta con la fuerza max incidiendo sobre ella
		int junta_incidente_fmax = puente.junta(fuerza_absoluta_max);
		int secciones_a_derecha = (junta_incidente_fmax / 2) + 1;
		if(secciones_a_derecha % 2 != 0) {
			junta_incidente_fmax += (secciones_a_derecha > 2) ? 1 : -1;
			secciones_a_derecha = (junta_incidente_fmax / 2) + 1;
		}
                posiciones_pilares.push_back(junta_incidente_fmax);
		int n = puente.getN();
		num length = puente.getLength();
		num height = puente.getH();
		int n_1 = secciones_a_derecha;
		int n_2 = n-secciones_a_derecha;
		num span_1 = n_2*length;
		num span_2 = n_1*length;
		num costo_pilar = puente.getCostoPilar();
		num fMax = puente.getFMax();
		vector<double> cargas_nuevas_1,cargas_nuevas_2;
		vector<double> cargas_puente = puente.getCargas(); 

		for(int i = 0; i < cargas_puente.size(); ++i) {
			if(i < junta_incidente_fmax)
				cargas_nuevas_2.push_back(cargas_puente[i]);
			else if(i > junta_incidente_fmax) {
				cargas_nuevas_1.push_back(cargas_puente[i]);
			}
		}
		
		Puente puente_1 = Puente(n_1,span_1,height,costo_pilar,fMax,cargas_nuevas_1);
		Puente puente_2 = Puente(n_2,span_2,height,costo_pilar,fMax,cargas_nuevas_2);
		pair<double,int> costo_sub_estructura_1 = calcularCostoEstructura(puente_1, posiciones_pilares, costo_subestructuras);
		pair<double,int> costo_sub_estructura_2 = calcularCostoEstructura(puente_2, posiciones_pilares, costo_subestructuras);
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
	pair<double,int> costo_y_pilares = calcularCostoEstructura(puente, posiciones_pilares, costo_subestructuras);
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
