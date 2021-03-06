//Declara�ao de Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

//Declaracao de pre-processadores
#define quant_medicos 10
#define quant_pacientes 100
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ESC 27
#define KEY_ENTER 13

//Declaracao de estruturas
struct medicos_hospital { //Struct que guarda os dados de um medico
	char cod_medico[100];
	char nome[1000];
	char endereco[100];
	float salario;
};

struct medicos_hospital medicos[quant_medicos];

struct pacientes_hospital{  //Struct que guarda os dados de um paciente
	char cod_paciente[100];
	char nome[100];
	char endereco[100];
	int idade;
};

struct pacientes_hospital pacientes[quant_pacientes];

struct hospital_consultas { //Struct que guarda os dados de uma consulta
	int num_prontuario;
	int dia_Consulta;
	int mes_Consulta;
	int ano_Consulta;
	char diagnostico[10000];
	char cod_medico[100];
	char cod_paciente[100];
};

struct hospital_consultas consultas[quant_pacientes];

//Declara�ao de fun�oes 
int menu_principal();
int menu_cadastrar_alterar_paciente_medico();
void cadastrar_paciente(int i);
void alterar_paciente(int i);
void cadastrar_medico(int i);
void alterar_medico(int i);
void excluir_funcionario(int i);
void cadastrar_consulta(int i);
void mostrar_consultas(int dia, int mes, int ano);
int menu_repetir_acao(int i, int j);
int menu_repetir_cadastro_consulta();
int get_medico(char cod[]);
int get_paciente(char cod[]);
int menu_bool(char mens[]);

//Declara�ao de variaveis
int quant_medicos_registrados = 0; //Salvar essa variavel no arquivo .txt
int quant_pacientes_registrados = 0; //Salvar essa variavel no arquivo .txt
int quant_consultas_registradas = 0; //Salvar essa variavel no arquivo .txt

int main(void) {
	system("color b");
	setlocale(LC_ALL, "Portuguese");
	int op, alt_cad, i, res, medico_selecionado, paciente_selecionado, dia, mes, ano;
	int pause = 1;
	
	while(pause){
		op = menu_principal();
		switch(op) {
			case 1: 	//Cadastro ou altera�ao de paciente ou medicos
				alt_cad = menu_cadastrar_alterar_paciente_medico();
				
				if(alt_cad == 1) {	//Cadastro de paciente
					res = 1;
					while(res == 1) {
						cadastrar_paciente(quant_pacientes_registrados);
						res = menu_repetir_acao(1, 1);
					}
				}else if(alt_cad == 2) {	//Altera�ao de paciente
					system("cls");
					res = 1;
					if(quant_pacientes_registrados){
						while(res == 1) {
							for(i = 0; i<quant_pacientes_registrados; i++) { //Lista todos os pacientes ja registrados
								printf("-> %i. [%s] \n", i, pacientes[i].nome);
							}
							printf("----------------------------------\n");
							printf("-> Qual paciente deseja alterar? ");
							scanf("%i", &paciente_selecionado);
							printf("----------------------------------\n");
							fflush(stdin);
							alterar_paciente(paciente_selecionado); //Chama a fun�ao que altera os dados de um paciente e passa como parametro o Indice do paciente desejado no vetor
							res = menu_repetir_acao(1, 2);
						}
					}else {
						printf("--------------------------------------------------\n");
						printf("\a-> N�o existe nenhum paciente registrado ainda!\n");
						printf("--------------------------------------------------\n");
						system("pause > 1");
					}
				}else if(alt_cad == 3) {	//Cadastro de medico
					res = 1;
					while(res == 1) {
						cadastrar_medico(quant_medicos_registrados);
						res = menu_repetir_acao(2, 1);
					}
				}else {		//Altera�ao de medico
					system("cls");
					res = 1;
					if(quant_medicos_registrados){
						while(res == 1) {
							for(i = 0; i<quant_medicos_registrados; i++) { //Lista todos os pacientes ja registrados
								printf("-> %i. [%s] \n", i, medicos[i].nome);
							}
							printf("----------------------------------\n");
							printf("-> Qual m�dico deseja alterar? ");
							scanf("%i", &medico_selecionado);
							printf("----------------------------------\n");
							fflush(stdin);
							alterar_medico(medico_selecionado); //Chama a fun�ao que altera os dados de um medico e passa como parametro o Indice do medico desejado no vetor
							res = menu_repetir_acao(2, 2);
						}
					}else {
						printf("--------------------------------------------------\n");
						printf("\a-> N�o existe nenhum m�dico registrado ainda!\n");
						printf("--------------------------------------------------\n");
						system("pause > 1");
					}
				}
			break;
			
			case 2: //Cadastrar uma consulta
			
				if(quant_medicos_registrados) {
					res = 1;
					system("cls");
					while(res == 1) {
						cadastrar_consulta(quant_consultas_registradas);
						res = menu_repetir_cadastro_consulta();
					}				
				}else {
					system("cls");
					res = menu_bool("\a-> N�o existe nenhum m�dico cadastrado...\n   *Deseja cadastrar um m�dico agora?* ");
					if(res == 1) {
						cadastrar_medico(quant_medicos_registrados);
						res = 1;
						if(quant_pacientes_registrados){
							system("cls");
							while(res == 1) {
								cadastrar_consulta(quant_consultas_registradas);
								res = menu_repetir_cadastro_consulta();
							}				
						}else {
							res = menu_bool("\a-> N�o existe nenhum paciente cadastrado...\n   *Deseja cadastrar um paciente agora?*");
							if(res == 1) {
								cadastrar_paciente(quant_pacientes_registrados);
								system("cls");
								while(res == 1) {
									cadastrar_consulta(quant_consultas_registradas);
									res = menu_repetir_cadastro_consulta();
								}			
							}
						}
					}
				}
			break;
						
			case 3: //Excluir um m�dico
				system("cls");
				if(quant_medicos_registrados) {
					for(i = 0; i < quant_medicos_registrados; i++) {
						printf("%i. [%s] \n", i, medicos[i].nome);
					}
					
					printf("----------------------------------\n");
					printf("-> Qual m�dico deseja excluir? ");
					scanf("%i", &medico_selecionado);
					fflush(stdin);
					excluir_funcionario(medico_selecionado);
					printf("----------------------------------\n");
				}else {
					printf("--------------------------------------------------\n");
					printf("\a-> N�o existe nenhum m�dico registrado ainda!\n");
					printf("--------------------------------------------------\n");
					system("pause > 1");
				}
			break;
			
			case 4:  //Listar todas as consultas realizadas em um dia
			
				if(quant_consultas_registradas) {
					printf("---------------------------------------------------------------------------\n");
					printf("Informe uma data pra ver todas consultas realizadas(dd/mm/aaaa): ");
					scanf("%d/%d/%d", &dia, &mes, &ano);
					printf("---------------------------------------------------------------------------\n");
					mostrar_consultas(dia, mes, ano);		
				}else {
					printf("-------------------------------------------------\n");
					printf("\a-> Nenhuma consulta realizada at� o momento...!\n");
					printf("-------------------------------------------------\n");
					system("pause > 1");
				}
			break;
			
			default:
				printf("Op��o inv�lida\n");
		}	
	}	
	return 0;
}

//Fun�oes que realizam as opera�oes
void cadastrar_paciente(int i) { //Fun�ao que cadastra paciente (Concluido)**
	//char olhar[1000];
	// criando o ponteiro
	FILE *ponteiro;
 	ponteiro = fopen("dadosPaciente.txt", "a"); // append
	/********************/
	system("cls");
	//  scanf("%s", pacientes[i].cod_paciente); //Remover essa linha quando o codigo for gerado automaticamente
	//	fflush(stdin);
	printf("------------------------------------------------ \n");
	printf("D� um c�digo ao paciente: ");
	scanf("%s", pacientes[i].cod_paciente);
	fflush(stdin);		
	printf("\nInforme o nome do paciente: ");
	scanf("%[^\n]s", pacientes[i].nome);
	fflush(stdin);
	printf("Entre com o endere�o do paciente: ");
	scanf("%[^\n]s", pacientes[i].endereco);
	fflush(stdin);
	printf("Informe a idade do paciente: ");
	scanf("%i", &pacientes[i].idade);
	fflush(stdin);
	printf("------------------------------------------------ \n");
 	
 	// ler dados
	/*	while(fgets(olhar, 1000, lerDados) != NULL){
		printf("%s", olhar);
	}*/
	// salvando os dados do paciente no arquivo
	fprintf(ponteiro, "------ Dados do Paciente ------\n");
	fprintf(ponteiro, "C�digo: 00%s\n", pacientes[i].cod_paciente);
	fprintf(ponteiro, "Nome: %s\n", pacientes[i].nome);
	fprintf(ponteiro, "Endere�o: %s\n", pacientes[i].endereco);
	fprintf(ponteiro, "Idade: %i anos\n", pacientes[i].idade);
	fprintf(ponteiro, "-------------------------------\n");
	fclose(ponteiro);
	/********************/
	quant_pacientes_registrados++;
}

void alterar_paciente(int i) { //Fun�ao que altera dados do paciente* (Concluido)**
	
//	FILE *lerDados;
//	lerDados = fopen("dadosPaciente.txt", "r"); //read
//	fscanf(lerDados, "%s %[^\n]s %[^\n]s %i", &pacientes[i].cod_paciente, &pacientes[i].nome, &pacientes[i].endereco, &pacientes[i].idade);
	
	system("cls");
	printf("C�digo do paciente: 00%s", pacientes[i].cod_paciente);
	printf("Informe o nome do paciente: ");
	scanf("%s", pacientes[i].nome);
	fflush(stdin);
	printf("Entre com o endere�o do paciente: ");
	scanf("%s", pacientes[i].endereco);
	fflush(stdin);
	printf("Informe a idade do paciente: ");
	scanf("%i", &pacientes[i].idade);
	fflush(stdin);
}

void cadastrar_medico(int i) { //Fun�ao que cadastra um funcionario(Medico) (Concluido)**
	// criando o ponteiro
	FILE *ponteiroMed;
 	ponteiroMed = fopen("dadosM�dico.txt", "a"); // append
	/********************/
	system("cls");
	printf("------------------------------------------------ \n");
	//	printf("Informe o codigo do medico: "); //Fazer uma fun�ao pra gerar esse codigo de forma automatica
	//	scanf("%s", medicos[i].cod_medico); //Quando o codigo for gerado de forma automatica excluir essa linha
	//	fflush(stdin);
	printf("D� um c�digo ao m�dico: ");
	scanf("%s", medicos[i].cod_medico);
	fflush(stdin);		
	printf("\nInforme o nome do medico: ");
	scanf("%s", medicos[i].nome);
	fflush(stdin);
	printf("Informe o endere�o do medico: ");
	scanf("%[^\n]s", medicos[i].endereco);
	fflush(stdin);
	printf("Informe o salario do medico: ");
	scanf("%f", &medicos[i].salario);
	fflush(stdin);
	printf("------------------------------------------------ \n");
	// salvando os dados do m�dico no arquivo
	fprintf(ponteiroMed, "------ Dados do M�dico ------\n");
	fprintf(ponteiroMed, "C�digo: 00%s\n", medicos[i].cod_medico);
	fprintf(ponteiroMed, "Nome: %s\n", medicos[i].nome);
	fprintf(ponteiroMed, "Endere�o: %s\n", medicos[i].endereco);
	fprintf(ponteiroMed, "Sal�rio: R$%.2f reais\n", medicos[i].salario);
	fprintf(ponteiroMed, "-------------------------------\n");
	fclose(ponteiroMed);
	/********************/
	quant_medicos_registrados++;
}

void alterar_medico(int i) { //Fun�ao que altera dados de um M�dico (Concluido)**
	system("cls");
	printf("-------------------------------------\n");
	printf("C�digo do m�dico: 00%s", medicos[i].cod_medico);
	printf("Informe o nome do medico: ");
	scanf("%[^\n]s", medicos[i].nome);
	fflush(stdin);
	printf("Informe o endere�o do medico: ");
	scanf("%[^\n]s", medicos[i].endereco);
	fflush(stdin);
	printf("Informe o salario do medico: ");
	scanf("%f", &medicos[i].salario);
	fflush(stdin);
	printf("-------------------------------------\n");
}

void excluir_funcionario(int i) { //Fun�ao que exclui um M�dico (Concluido)**
	int j, permss = 0;
	for(j=0; j < quant_consultas_registradas; j++) {
		if(strcmp(consultas[j].cod_medico, medicos[i].cod_medico) == 0){
			permss = 1;
		}
	}
	system("cls");
	if(permss){
		printf("---------------------------------------------\n");
		printf("\a-> Permiss�o para excluir m�dico negada...\n");
		printf("---------------------------------------------\n");
		system("pause");
		system("cls");
	}else {
		while(i < quant_medicos_registrados) {
			j = i + 1;
			strcpy(medicos[i].cod_medico, medicos[j].cod_medico);
			strcpy(medicos[i].endereco, medicos[j].endereco);
			strcpy(medicos[i].nome, medicos[j].nome);
			medicos[i].salario = medicos[j].salario;
			i++;
		}
		quant_medicos_registrados--;
		printf("---------------------------------\n");
		printf("\a-> M�dico exclu�do com sucesso!\n");
		printf("---------------------------------\n");
		system("pause");
		system("cls");
	}
	
	// Excluindo arquivo.txt
	int deletar;
	
	if(quant_consultas_registradas == 0){ 
		deletar = remove("dadosM�dico.txt");
		printf("------------------------------------------\n");
		printf("\a-> dadosM�dico.txt exclu�do com sucesso!\n");
		printf("------------------------------------------\n");
		system("pause");
		system("cls");
	}
	else{
		printf("-----------------------------------------------------\n");
		printf("\a-> Permiss�o para excluir dadosM�dico.txt negada...\n");
		printf("-----------------------------------------------------\n"); 
		system("pause");
		system("cls");
	}
}
//TESTEEEEEEEEEEEEEEEEEEEEE
void cadastrar_consulta(int i) { //Fun�ao para cadastrar consultas (Concluido)**
	
	int j, medico_selecionado, paciente_selecionado;
	//criar Ponteiro
	FILE *ponteiroConsultas;
	ponteiroConsultas = fopen("dadosConsulta.txt", "a");
	/**********************/
	
	printf("--------------------------------------------\n");
	printf("Informe o n�mero do prontu�rio: ");
	scanf("%d", &consultas[i].num_prontuario);
	fflush(stdin);
	printf("Informe a data da consulta (dd/mm/aaaa): ");
	scanf("%d/%d/%d", &consultas[i].dia_Consulta, &consultas[i].mes_Consulta, &consultas[i].ano_Consulta);
	fflush(stdin);
	printf("Qual foi o diagn�stico da consulta? ");
	scanf("%s", consultas[i].diagnostico);
	fflush(stdin);
	printf("--------------------------------------------\n");
	system("cls");
	for(j = 0; j < quant_medicos_registrados; j++){ //Lista todos os medicos registrados
		printf("-> %i. %s \n", j, medicos[i].nome);
	}
	printf("Qual m�dico realizou a consulta? ");
	scanf("%i", &medico_selecionado);
	strcpy(consultas[i].cod_medico, medicos[medico_selecionado].cod_medico);
	system("cls");
	for(j=0; j<quant_pacientes_registrados; j++) { //Lista todos pacientes registrados
		printf("-> %i. %s \n", j, pacientes[i].nome);
	}
	printf("Qual paciente foi consultado? ");
	scanf("%i", &paciente_selecionado);
	strcpy(consultas[i].cod_paciente, pacientes[paciente_selecionado].cod_paciente);
	//salvando dados em dadosConsultas.txt
	fprintf(ponteiroConsultas, "------------------------------Dados de Consulta---------------------------------\n");
	fprintf(ponteiroConsultas, "Data da consulta: %d/%d/%d\n", consultas[i].dia_Consulta, consultas[i].mes_Consulta, consultas[i].ano_Consulta);
	fprintf(ponteiroConsultas, "Diagn�stico da consulta: %s\n", consultas[i].diagnostico);
	fprintf(ponteiroConsultas, "M�dico que realizou a consulta: %s\n", medicos[i].nome);
	fprintf(ponteiroConsultas, "Paciente que realizou a consulta: %s\n", pacientes[i].nome);
	fprintf(ponteiroConsultas, "-------------------------------------------------------------------------------\n");
	fclose(ponteiroConsultas);
	/***********************************/
	quant_consultas_registradas++;
}

void mostrar_consultas(int dia, int mes, int ano) { //Fun�ao que mostrar todas as consultas de acordo com uma certa data (Concluido)**
	int i, find = 0;
	system("cls");
	for(i=0; i<quant_consultas_registradas; i++) {
		if((consultas[i].dia_Consulta == dia) && (consultas[i].mes_Consulta == mes) && (consultas[i].ano_Consulta == ano)) {
			find = 1;
			printf("----------------------------------------------\n");
			printf("N�mero prontu�rio: %i\n", consultas[i].num_prontuario);
			printf("Nome do m�dico que realizou a consulta: %s\n", medicos[get_medico(consultas[i].cod_medico)].nome);
			printf("Nome do paciente que foi consultado: %s\n", pacientes[get_paciente(consultas[i].cod_paciente)].nome);
			printf("----------------------------------------------\n");
			system("pause > 1");
		}
	}
	if(!find) {
		printf("\a-> Nenhuma consulta realizada no dia %d/%0d/%d\n", dia, mes, ano);
		system("pause > 1");
	}
}

int get_medico(char cod[]) { //Pegar o indice de acordo com o codigo do medico informado
	int i = 0;
	while(strcmp(cod, medicos[i].cod_medico) != 0) {
		i++;
	}
	return i;
}

int get_paciente(char cod[]) { //Pegar o indice de acordo com o codigo do paciente informado
	int i = 0;
	while(strcmp(cod, pacientes[i].cod_paciente) != 0) {
		i++;
	}
	return i;	
}

// Fun�oes que mostram algum tipo de menu
int menu_principal() {
	int op = 0;
	system("cls");
	while(op > 4 || op < 1) {	
		printf("------------------------ HospiTOP -------------------------\n");
		printf("-----------------------------------------------------------\n");
		printf("|1. CADASTRAR ou ALTERAR dados de Paciente ou M�dico      |\n");
		printf("|2. CADASTRAR consulta                                    |\n");
		printf("|3. EXCLUIR um m�dico                                     |\n");
		printf("|4. MOSTRAR todas consultas de uma certa data        	  |\n");
		printf("-----------------------------------------------------------\n");
		printf("\nInforme a op��o desejada: ");
		scanf("%i", &op);
		fflush(stdin);
	}
	return op;
}

int menu_cadastrar_alterar_paciente_medico() {
	int key = 0;
	int op = 1;
	while(1) {
		system("cls");
		printf("-------------------------------\n");
		printf("Alterar ou Cadastrar usu�rio: \n");
		printf("-------------------------------\n");
		printf("%s Cadastrar Paciente\n", (op == 1) ? "->" : " ");
		printf("%s Alterar Paciente\n", (op == 2) ? "->" : " ");
		printf("%s Cadastrar M�dico\n", (op == 3) ? "->" : " ");
		printf("%s Alterar M�dico\n", (op == 4) ? "->" : " ");
		printf("-------------------------------\n");
		key = getch();
		if(key == KEY_UP && op > 1){
			op--;
		}else if(key == KEY_DOWN && op < 4) {
			op++;
		}
		if(key == KEY_ESC) {
			return 0;
		}else if(key == KEY_ENTER) {
			return op;
		}
	}
//	tttttt
}

int menu_repetir_acao(int i, int j) {
	int op = 1;
	int key;
	while(1){
		system("cls");
		printf("------------------------------------- \n");
		printf("-> %s %s com Sucesso...\n",(i == 1) ? "Paciente" : "Medico", (j == 1) ? "cadastrado" : "alterado");
		printf("------------------------------------- \n");
		printf("\nDeseja %s outro %s: \n", (j == 1) ? "cadastrar" : "alterar", (i == 1) ? "paciente" : "m�dico");
		printf("\n%s SIM\n", (op == 1) ? "->" : " ");
		printf("%s N�O\n", (op == 2) ? "->" : " ");
		key = getch();
		if(key == KEY_UP && op > 1) {
			op--;
		}else if(key == KEY_DOWN && op < 2) {
			op++;
		}else if(key == KEY_ESC) {
			return 2;
		}else if(key == KEY_ENTER) {
			return op;
		}
	}
	system("cls");
}

int menu_repetir_cadastro_consulta() {
	int op = 1;
	int key;
	while(1){
		system("cls");
		printf("------------------------------------- \n");
		printf("-> Consulta cadastrada com Sucesso...\n");
		printf("------------------------------------- \n");
		printf("\n-> Deseja cadastrar outra consulta? \n");
		printf("\n%s SIM\n", (op == 1) ? "->" : " ");
		printf("%s N�O\n", (op == 2) ? "->" : " ");
		key = getch();
		if(key == KEY_UP && op > 1) {
			op--;
		}else if(key == KEY_DOWN && op < 2) {
			op++;
		}else if(key == KEY_ESC) {
			return 2;
		}else if(key == KEY_ENTER) {
			return op;
		}
	}
	system("cls");
	
}

int menu_bool(char mens[]) {
	int op = 1;
	int key;
	while(1){
		system("cls");
		printf("%s\n", mens);
		printf("\n%s SIM\n", (op == 1) ? "->" : " ");
		printf("%s N�O\n", (op == 2) ? "->" : " ");
		key = getch();
		if(key == KEY_UP && op > 1) {
			op--;
		}else if(key == KEY_DOWN && op < 2) {
			op++;
		}else if(key == KEY_ESC) {
			return 2;
		}else if(key == KEY_ENTER) {
			return op;
		}
	}
	system("cls");
}
