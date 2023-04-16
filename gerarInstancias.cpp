#include <iostream>
#include <vector>

using namespace std;

#define NUM_VERTICES	10
#define NUM_CONSULTAS	5
#define INFINITO 		999999999

void gerarIntancias(){

	string cidades[] = {"Campo Grande", "Dourados", "Tres Lagoas", "Corumba", "Ponta Pora", "Navirai", "Aquidauana", "Paranaiba", "Coxim", "Nova Andradina"};
	pair<string, string> consultas[] = {{"Campo Grande", "Nova Andradina"}, {"Dourados", "Coxim"}, {"Tres Lagoas", "Paranaiba"}, {"Corumba", "Aquidauana"}, {"Ponta Pora", "Navirai"}};	
	float peso;

	for(int i = 1; i < NUM_VERTICES; i *= 2){
		FILE *arqEntrada;
		FILE * arqSaida;

		string caminhoArqEntrada = "Matrizes/peso"+to_string(i)+".txt";
		string caminhoArqSaida = "Instancias/instancia"+to_string(i)+".txt";

		arqEntrada = fopen(caminhoArqEntrada.c_str(), "r");
		arqSaida = fopen(caminhoArqSaida.c_str(), "w");
		
		if(arqEntrada == NULL){
			cout << "Erro ao ler o arquivo!" << endl;
		}

		fprintf(arqSaida, "%d\n", NUM_VERTICES);

		for(int i = 0; i < NUM_VERTICES; i++){
			fprintf(arqSaida, "%s\n", cidades[i].c_str());
		}

		for(int i = 0; i < NUM_VERTICES; i++){
			for (int j = 0; j < NUM_VERTICES; j++){
				fscanf(arqEntrada, "%f", &peso);
				fprintf(arqSaida, "%.1f\n", peso);
			}
		}

		fprintf(arqSaida, "%d\n", NUM_CONSULTAS);

		for(int i = 0; i < NUM_CONSULTAS; i++){
			fprintf(arqSaida, "%s\n%s\n", consultas[i].first.c_str(), consultas[i].second.c_str());
		}

	}

}

int main(){

	gerarIntancias();

	return 0;
}