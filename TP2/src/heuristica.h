#include "Puente.h"

double calcularCosto(Puente& puente);
pair<double,int> calcularCostoEstructura(Puente& puente, vector<double>& posiciones_pilares, vector<double>& costo_subestructuras, int n_del_principio);
double calcularCostoTotal(Puente& puente);
pair<double, pair< vector<double>, vector<double> > > costoTotal(Puente& puente);
