#include "heuristica.h"

double calcularCosto(Puente& puente) {
	num costo = 0;
	puente.resolverPuente();
	if(!puente.esSeguro()) {
		num fuerza_absoluta_max = puente.getMatriz().getFuerzaMax();

		// colocar pilar debajo de la junta con la fuerza max incidiendo sobre ella
		//costo = calcularCosto(puente_1) + calcularCosto(puent_2)
	}
	//calcular la sumatoria de links etc
	return costo;
}