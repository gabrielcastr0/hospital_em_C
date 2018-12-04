//Declaraçao de Bibliotecas
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

//Declaraçao de funçoes 
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

//Declaraçao de variaveis
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
			case 1: 	//Cadastro ou alteraçao de paciente ou medicos
				alt_cad = menu_cadastrar_alterar_paciente_medico();
				
				if(alt_cad == 1) {	//Cadastro de paciente
					res = 1;
					while(res == 1) {
						cadastrar_paciente(quant_pacientes_registrados);
						res = menu_repetir_acao(1, 1);
					}
				}else if(alt_cad == 2) {	//Alteraçao de paciente
					system("cls");
					res = 1;
					if(quant_pacientes_registrados){
						while(res == 1) {
							for(i = 0; i<quant_pacientes_registrados; i++) { //Lista todos os pacientes ja registrados
								printf("-> %i. [%s] \n", i, pacientes[i].nome);
							}
							printf("----------------------------------\n");
							printf("Qual paciente deseja alterar?: ");
							scanf("%i", &paciente_selecionado);
							printf("----------------------------------\n");
							fflush(stdin);
							alterar_paciente(paciente_selecionado); //Chama a funçao que altera os dados de um paciente e passa como parametro o Indice do paciente desejado no vetor
							res = menu_repetir_acao(1, 2);
						}
					}else {
						printf("--------------------------------------------------\n");
						printf("\a-> Não existe nenhum paciente registrado ainda!\n");
						printf("--------------------------------------------------\n");
						system("pause > 1");
					}
				}else if(alt_cad == 3) {	//Cadastro de medico
					res = 1;
					while(res == 1) {
						cadastrar_medico(quant_medicos_registrados);
						res = menu_repetir_acao(2, 1);
					}
				}else {		//Alteraçao de medico
					system("cls");
					res = 1;
					if(quant_medicos_registrados){
						while(res == 1) {
							for(i = 0; i<quant_medicos_registrados; i++) { //Lista todos os pacientes ja registrados
								printf("-> %i. [%s] \n", i, medicos[i].nome);
							}
							printf("----------------------------------\n");
							printf("Qual medico deseja alterar?: ");
							scanf("%i", &medico_selecionado);
							printf("----------------------------------\n");
							fflush(stdin);
							alterar_medico(medico_selecionado); //Chama a funçao que altera os dados de um medico e passa como parametro o Indice do medico desejado no vetor
							res = menu_repetir_acao(2, 2);
						}
					}else {
						printf("--------------------------------------------------\n");
						printf("\a-> Não existe nenhum médico registrado ainda!\n");
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
					res = menu_bool("\aNao existe nenhum médico cadastrado...\n\tDeseja cadastrar um médico agora: ");
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
							res = menu_bool("\aNao existe nenhum paciente cadastrado...\n\tDeseja cadastrar um paciente agora: ");
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
						
			case 3: //Excluir um medico
				system("cls");
				if(quant_medicos_registrados) {
					for(i = 0; i < quant_medicos_registrados; i++) {
						printf("%i. [%s] \n", i, medicos[i].nome);
					}
					
					printf("----------------------------------\n");
					printf("\nQual médico deseja excluir?: ");
					scanf("%i", &medico_selecionado);
					fflush(stdin);
					excluir_funcionario(medico_selecionado);
					printf("----------------------------------\n");
				}else {
					printf("--------------------------------------------------\n");
					printf("\n-> Não existe nenhum médico registrado ainda!\n");
					printf("--------------------------------------------------\n");
					system("pause > 1");
				}
			break;
			
			case 4:  //Listar todas as consulta realizadas em um dia
				printf("---------------------------------------------------------------------------\n");
				printf("Informe uma data pra ver todas consultas realizadas(dd/mm/aaaa): ");
				scanf("%d/%d/%d", &dia, &mes, &ano);
				printf("---------------------------------------------------------------------------\n");
				mostrar_consultas(dia, mes, ano);
			break;
			
			default:
				printf("Opção inválida\n");
		}	
	}	
	return 0;
}

//Funçoes que realizam as operaçoes
void cadastrar_paciente(int i) { //Funçao que cadastra paciente (Concluido)**
	// criando o ponteiro
	FILE *ponteiro;
 	ponteiro = fopen("dadosPaciente.txt", "w"); // write
	/********************/
	system("cls");
	//  scanf("%s", pacientes[i].cod_paciente); //Remover essa linha quando o codigo for gerado automaticamente
	//	fflush(stdin);
	srand(time(NULL));
	printf("------------------------------------------------ \n");
	printf("O código do paciente é: [%d]" , rand() % 1000);		
	printf("\nInforme o nome do paciente: ");
	scanf("%[^\n]s", pacientes[i].nome);
	fflush(stdin);
	printf("Entre com o endereço do paciente: ");
	scanf("%[^\n]s", pacientes[i].endereco);
	fflush(stdin);
	printf("Informe a idade do paciente: ");
	scanf("%i", &pacientes[i].idade);
	fflush(stdin);
	printf("------------------------------------------------ \n");
	// salvando os dados do paciente no arquivo
	fprintf(ponteiro, "------ Dados do Paciente ------\n");
	fprintf(ponteiro, "Código: %s\n", pacientes[i].cod_paciente);
	fprintf(ponteiro, "Nome: %s\n", pacientes[i].nome);
	fprintf(ponteiro, "Endereço: %s\n", pacientes[i].endereco);
	fprintf(ponteiro, "Idade: %i anos\n", pacientes[i].idade);
	fprintf(ponteiro, "-------------------------------\n");
	fclose(ponteiro);
	/********************/
	quant_pacientes_registrados++;
}

void alterar_paciente(int i) { //Funçao que altera dados do paciente* (Concluido)**
	system("cls");
	printf("Código do paciente: %s\n\n", pacientes[i].cod_paciente);
	printf("Informe o nome do paciente: ");
	scanf("%s", pacientes[i].nome);
	fflush(stdin);
	printf("Entre com o endereço do paciente: ");
	scanf("%s", pacientes[i].endereco);
	fflush(stdin);
	printf("Informe a idade do paciente: ");
	scanf("%i", &pacientes[i].idade);
	fflush(stdin);
}

void cadastrar_medico(int i) { //Funçao que cadastra um funcionario(Medico) (Concluido)**
	// criando o ponteiro
	FILE *ponteiroMed;
 	ponteiroMed = fopen("dadosMédico.txt", "w"); // write
	/********************/
	system("cls");
	printf("------------------------------------------------ \n");
	//	printf("Informe o codigo do medico: "); //Fazer uma funçao pra gerar esse codigo de forma automatica
	//	scanf("%s", medicos[i].cod_medico); //Quando o codigo for gerado de forma automatica excluir essa linha
	//	fflush(stdin);
	printf("O código do médico é: [%d]" , rand() % 1000);	
	printf("\nInforme o nome do medico: ");
	scanf("%s", medicos[i].nome);
	fflush(stdin);
	printf("Informe o endereço do medico: ");
	scanf("%[^\n]s", medicos[i].endereco);
	fflush(stdin);
	printf("Informe o salario do medico: ");
	scanf("%f", &medicos[i].salario);
	fflush(stdin);
	printf("------------------------------------------------ \n");
	// salvando os dados do médico no arquivo
	fprintf(ponteiroMed, "------ Dados do Médico ------\n");
	fprintf(ponteiroMed, "Código: %s\n", medicos[i].cod_medico);
	fprintf(ponteiroMed, "Nome: %s\n", medicos[i].nome);
	fprintf(ponteiroMed, "Endereço: %s\n", medicos[i].endereco);
	fprintf(ponteiroMed, "Salário: R$%.2f reais\n", medicos[i].salario);
	fprintf(ponteiroMed, "-------------------------------\n");
	fclose(ponteiroMed);
	/********************/
	quant_medicos_registrados++;
}

void alterar_medico(int i) { //Funçao que altera dados de um funcionario(Medico) (Concluido)**
	system("cls");
	printf("-------------------------------------\n");
	printf("Codigo do medico: %s\n\n", medicos[i].cod_medico);
	printf("Informe o nome do medico: ");
	scanf("%[^\n]s", medicos[i].nome);
	fflush(stdin);
	printf("Informe o endereço do medico: ");
	scanf("%[^\n]s", medicos[i].endereco);
	fflush(stdin);
	printf("Informe o salario do medico: ");
	scanf("%f", &medicos[i].salario);
	fflush(stdin);
	printf("-------------------------------------\n");
}

void excluir_funcionario(int i) { //Funçao que exclui um funcionario(Medico) (Concluido)**
	int j, permss = 0;
	for(j=0; j < quant_consultas_registradas; j++) {
		if(strcmp(consultas[j].cod_medico, medicos[i].cod_medico) == 0){
			permss = 1;
		}
	}
	system("cls");
	if(permss){
		while(i < quant_medicos_registrados) {
			j = i + 1;
			strcpy(medicos[i].cod_medico, medicos[j].cod_medico);
			strcpy(medicos[i].endereco, medicos[j].endereco);
			strcpy(medicos[i].nome, medicos[j].nome);
			medicos[i].salario = medicos[j].salario;
			i++;
		}
		quant_medicos_registrados--;
		printf("--------------------------------\n");
		printf("\n->Médico excluído com sucesso!\n");
		printf("--------------------------------\n");
	}else {
		printf("-------------------------------------------\n");
		printf("\n->Permissão para excluir medico negada...");
		printf("-------------------------------------------\n");
	}
}

void cadastrar_consulta(int i) { //Funçao para cadastrar consultas (Concluido)**
	
	int j, medico_selecionado, paciente_selecionado;
	
	printf("Informe o numero do prontuario: ");
	scanf("%d", &consultas[i].num_prontuario);
	fflush(stdin);
	printf("Informe a data da consulta (dd/mm/aaaa): ");
	scanf("%d/%d/%d", &consultas[i].dia_Consulta, &consultas[i].mes_Consulta, &consultas[i].ano_Consulta);
	fflush(stdin);
	printf("Qual foi o diagnostico da consulta: \n");
	scanf("%s", consultas[i].diagnostico);
	fflush(stdin);
	system("cls");
	for(j = 0; j < quant_medicos_registrados; j++){ //Lista todos os medicos registrados
		printf("%i. %s \n", j, medicos[i].nome);
	}
	printf("Qual medico realizou a consulta: ");
	scanf("%i", &medico_selecionado);
	strcpy(consultas[i].cod_medico, medicos[medico_selecionado].cod_medico);
	system("cls");
	for(j=0; j<quant_pacientes_registrados; j++) { //Lista todos pacientes registrados
		printf("\t| %i |%s |\n", j, pacientes[i].nome);
	}
	printf("Qual paciente foi consultado: ");
	scanf("%i", &paciente_selecionado);
	strcpy(consultas[i].cod_paciente, pacientes[paciente_selecionado].cod_paciente);
	quant_consultas_registradas++;
}

void mostrar_consultas(int dia, int mes, int ano) { //Funçao que mostrar todas as consultas de acordo com uma certa data (Concluido)**
	int i;
	system("cls");
	for(i=0; i<quant_consultas_registradas; i++) {
		if((consultas[i].dia_Consulta == dia) && (consultas[i].mes_Consulta == mes) && (consultas[i].ano_Consulta == ano)) {
			printf("Número prontuario: ", consultas[i].num_prontuario);
			printf("Nome do medico que realizou a consulta: %s\n", medicos[get_medico(consultas[i].cod_medico)].nome);
			printf("Nome do paciente que foi consultado: %s\n", pacientes[get_paciente(consultas[i].cod_paciente)].nome);
		}
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

// Funçoes que mostram algum tipo de menu
int menu_principal() {
	int op = 0;
	system("cls");
	while(op > 3 || op < 1) {	
		printf("--------------------- Menu principal ----------------------\n");
		printf("-----------------------------------------------------------\n");
		printf("|1. CADASTRAR ou ALTERAR dados de Paciente ou Médico      |\n");
		printf("|2. CADASTRAR consulta                                    |\n");
		printf("|3. EXCLUIR um médico                                     |\n");
		printf("|4. MOSTRAR todas consultas de uma certa data        	  |\n");
		printf("-----------------------------------------------------------\n");
		printf("\nInforme a opção desejada: ");
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
		printf("Alterar ou Cadastrar usuário: \n");
		printf("-------------------------------\n");
		printf("%s Cadastrar Paciente\n", (op == 1) ? "->" : " ");
		printf("%s Alterar Paciente\n", (op == 2) ? "->" : " ");
		printf("%s Cadastrar Médico\n", (op == 3) ? "->" : " ");
		printf("%s Alterar Médico\n", (op == 4) ? "->" : " ");
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
}

int menu_repetir_acao(int i, int j) {
	int op = 1;
	int key;
	while(1){
		system("cls");
		printf("------------------------------------ \n");
		printf("->%s %s com Sucesso...\n",(i == 1) ? "Paciente" : "Medico", (j == 1) ? "cadastrado" : "alterado");
		printf("------------------------------------ \n");
		printf("\nDeseja %s outro %s: \n", (j == 1) ? "cadastrar" : "alterar", (i == 1) ? "paciente" : "medico");
		printf("\n%s SIM\n", (op == 1) ? "->" : " ");
		printf("%s NÃO\n", (op == 2) ? "->" : " ");
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
		printf("Consulta cadastrada com Sucesso...\n");
		printf("\nDeseja cadastrar outra consulta: \n");
		printf("\n%s SIM\n", (op == 1) ? "->" : " ");
		printf("%s NÃO\n", (op == 2) ? "->" : " ");
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
		printf("%s NÃO\n", (op == 2) ? "->" : " ");
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
