#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define DIMENSAO	10
#define INFINITO	999999999

// Calcula a matriz A * B

pair< vector< vector<int> >, vector< vector<double> > > multiplica_matrizes(vector< vector<int> > A, vector< vector<int> > B, vector< vector<double> > pesoA, vector< vector<double> > pesoB){
	vector< vector<int> > C;
	vector< vector<double> > pesoC;
	for(int i = 0; i < DIMENSAO; i++){
		vector<int> linha;
		vector<double> linha_peso;
		for(int j = 0; j < DIMENSAO; j++){
			linha.push_back(0);
			linha[j] = 0;
			linha_peso.push_back(INFINITO);
			for(int k = 0; k < DIMENSAO; k++){
				linha[j] += A[i][k] * B[k][j];
				if(A[i][k] > 0 && B[k][j] > 0){	
					linha_peso[j] = min(linha_peso[j], pesoA[i][k] + pesoB[k][j]);
				}
			}
			if(linha_peso[j] == INFINITO) linha_peso[j] = 0;
		}
		C.push_back(linha);		
		pesoC.push_back(linha_peso);		
	}
	return make_pair(C, pesoC);
}


// Calcula a matriz A^exp e a matriz peso correspondente

pair< vector< vector<int> >, vector< vector<double> > > multiplica(vector< vector<int> > A, vector< vector<double> > peso, int exp){
	if(exp == 1) return make_pair(A, peso);
	pair< vector< vector<int> >, vector< vector<double> > > res = multiplica(A, peso, exp/2);
	if(exp % 2 == 0){
		return multiplica_matrizes(res.first, res.first, res.second, res.second);
	}else{
		pair< vector< vector<int> >, vector< vector<double> > > _res = multiplica_matrizes(res.first, res.first, res.second, res.second);
		return multiplica_matrizes(_res.first, A, _res.second, peso);
	}
}

pair< vector< vector<int> >, vector< vector<double> > > lerMatrizesBase(){
	vector< vector<int> > A;
	vector< vector<double> > peso;
	
	FILE *arqAdjacencia;
	FILE * arqPeso;
	arqAdjacencia = fopen("A1.txt", "r");
	arqPeso = fopen("peso1.txt", "r");
	
	if(arqAdjacencia == NULL || arqPeso == NULL){
		cout << "Erro ao ler o arquivo!" << endl;
	}

	for(int i = 0; i < DIMENSAO; i++){
		vector<int> linha;
		for(int j = 0; j < DIMENSAO; j++){
			linha.push_back(0);
			fscanf(arqAdjacencia, "%d", &linha[j]);
		}
		A.push_back(linha);
	}

	for(int i = 0; i < DIMENSAO; i++){
		vector<double> linha;
		for(int j = 0; j < DIMENSAO; j++){
			linha.push_back(0);
			fscanf(arqPeso, "%lf", &linha[j]);
			if((linha[j] > 0 && A[i][j] == 0) || (linha[j] == 0 && A[i][j] > 0)){
				cout << "ERRO " << "(" << A[i][j] << ", " << linha[j] << ")" << endl;
			}
		}
		peso.push_back(linha);
	}

	fclose(arqAdjacencia);
	fclose(arqPeso);

	return make_pair(A, peso);
}

void gravarMatrizes(string nomeA, string nomePesoA, vector< vector<int> > A, vector< vector<double> > peso){
	FILE *arqAdjacencia;
	FILE * arqPeso;
	
	arqAdjacencia = fopen(nomeA.c_str(), "w");
	arqPeso = fopen(nomePesoA.c_str(), "w");
	
	for(int i = 0; i < DIMENSAO; i++){
		for(int j = 0; j < DIMENSAO; j++){
			fprintf(arqAdjacencia, "%d\n", A[i][j]);
		}
	}

	for(int i = 0; i < DIMENSAO; i++){
		for(int j = 0; j < DIMENSAO; j++){
			fprintf(arqPeso, "%lf\n", peso[i][j]);
		}
	}

	fclose(arqAdjacencia);
	fclose(arqPeso);

}

void gerarMatrizes(){
	pair< vector< vector<int> >, vector< vector<double> > > dadosEntrada = lerMatrizesBase();
	for(int i = 2; i < DIMENSAO; i *= 2){
		pair< vector< vector<int> >, vector< vector<double> > > dadosSaida = multiplica(dadosEntrada.first, dadosEntrada.second, i);
		gravarMatrizes("A"+to_string(i)+".txt", "peso"+to_string(i)+".txt", dadosSaida.first, dadosSaida.second);
	}
}

int main(){
	gerarMatrizes();
}