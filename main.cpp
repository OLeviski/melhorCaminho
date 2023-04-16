#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cstring>

using namespace std;

#define MAX_VERTICES	100
#define NUM_VERTICES	10
#define INFINITO 		999999999

// Estrutura de dados grafo

class Grafo{

private:
	map<string, int> mapeamento; // Mapeia nome das cidades para vertices do grafo
	int numVertices; // Numero de vertices
	float matriz_adjacencia[MAX_VERTICES][MAX_VERTICES]; // Matriz de adjacencia

public:

	Grafo(vector<string> nomeCidades){
		this->numVertices = (int) nomeCidades.size();
		
		for(int i = 0; i < this->numVertices; i++){
			for (int j = 0; j < this->numVertices; j++){
				this->matriz_adjacencia[i][j] = 0;
			}
		}

		for(int i = 0; i < this->numVertices; i++){
			this->mapeamento[nomeCidades[i]] = i;			
		}
	}

	void adicionarAresta(int i, int j, float distancia){
		this->matriz_adjacencia[i][j] = distancia;
	}

	int getVertice(string cidade){
		return this->mapeamento[cidade];
	}

	int getNumVertices(){
		return this->numVertices;
	}

	float verificaAdjacencia(int i, int j){
		return this->matriz_adjacencia[i][j];
	}

};

// Algoritmo Dijkstra

double Dijkstra(Grafo grafo, string cidadePartida, string cidadeChegada){
	
	double distancia[grafo.getNumVertices()];
	bool visitado[grafo.getNumVertices()];

	for(int i = 0; i < grafo.getNumVertices(); i++){
		distancia[i] = INFINITO;
		visitado[i] = false;
	}

	distancia[grafo.getVertice(cidadePartida)] = 0; 

	priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > fila_prioridades; 
	
	fila_prioridades.push(make_pair(distancia[grafo.getVertice(cidadePartida)], grafo.getVertice(cidadePartida)));

	while(true){ 

		int explorado = -1;
		int menor = INFINITO;
		
		while(!fila_prioridades.empty()){
			
			explorado = fila_prioridades.top().second;
			fila_prioridades.pop();
			
			if(visitado[explorado] == false){
				break;
			}
		}
		
		if(explorado == -1){
			break;
		}

		visitado[explorado] = true;

		for(int i = 0; i < grafo.getNumVertices(); i++){
			if(grafo.verificaAdjacencia(explorado, i) > 0){
				if(distancia[i] > distancia[explorado] + grafo.verificaAdjacencia(explorado, i)){  
					distancia[i] = distancia[explorado] + grafo.verificaAdjacencia(explorado, i);
					fila_prioridades.push(make_pair(distancia[i], i));
				}
			}
		}
	}

	return distancia[grafo.getVertice(cidadeChegada)];
}

void executaBuscas(){
	
	int n, numConsultas;
	float peso;

	char cidade[100], cidade1[100], cidade2[100];

	for(int i = 1; i < NUM_VERTICES; i *= 2){
		FILE *arqEntrada;
		vector<string> cidades;
		
		string caminhoArqEntrada = "Instancias/instancia"+to_string(i)+".txt";

		cout << "Resultados instancia" + to_string(i) + ".txt" << endl;

		arqEntrada = fopen(caminhoArqEntrada.c_str(), "r");

		if(arqEntrada == NULL){
			cout << "Erro ao ler o arquivo!" << endl;
		}

		fscanf(arqEntrada, "%d", &n);

		fgets(cidade, 100, arqEntrada);
		for(int i = 0; i < n; i++){
			fgets(cidade, 100, arqEntrada);
			cidade[strlen(cidade) - 1] = '\0';
			cidades.push_back(cidade);
		}

		Grafo g(cidades);

		for(int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				fscanf(arqEntrada, "%f", &peso);
				g.adicionarAresta(i, j, peso);
			}
		}

		fscanf(arqEntrada, "%d", &numConsultas);

		fgets(cidade1, 100, arqEntrada);
		for(int i = 0; i < numConsultas; i++){
			fgets(cidade1, 100, arqEntrada);
			cidade1[strlen(cidade1) - 1] = '\0';
			fgets(cidade2, 100, arqEntrada);
			cidade2[strlen(cidade2) - 1] = '\0';
			printf("Distancia entre %s e %s = %.1f\n", cidade1, cidade2, Dijkstra(g, cidade1, cidade2));
		}

	}	
}

int main(){

	executaBuscas();

	return 0;
}