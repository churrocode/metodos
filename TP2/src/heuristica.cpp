#include "heuristica.h"

double calcularCosto(Puente& puente) {
	num costo = 0;
	puente.resolverPuente();
	if(!puente.esSeguro()) {
		num fuerza_absoluta_max = puente.getMatriz().getFuerzaMax();
		// colocar pilar debajo de la junta con la fuerza max incidiendo sobre ella
		int junta_incidente_izq, junta_incidente_der;
		int secciones_a_derecha = (junta_incidente_izq / 2) + 1;
		if(secciones_a_derecha % 2 == 0) {
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
		}
		//costo = calcularCosto(puente_1) + calcularCosto(puent_2)
	}
	//calcular la sumatoria de links etc
	return costo;
}