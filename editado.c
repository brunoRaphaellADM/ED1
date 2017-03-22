#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 14

//verificar se o app ja esta instalado na loja
typedef struct
{
	char name[150];
	float size;
	int id;
	int status;
} app;

app appInstalado[SIZE];
app appRun[SIZE];
app appStorie[SIZE];

int countApp = 0;
int countAppRun = 0;

int main()
{
	int menu (void);
	void menuStories ();
	void loadApp (void);
	void menuMyAppsED();
	void menuRun();
	int resp;
	
	loadApp();

	appInstalado[0].size = -1;
	appRun[0].size = -1;
	do
	{
		resp = menu();
		switch(resp)
		{
		case 1:
			menuStories();
			break;
		case 2:
			menuMyAppsED();
			break;
		case 3:
			menuRun();
			break;
		case 0:
			return 0;
			break;
		default:
			printf("OPTION INVALID, PLEASE CHOOSE ANOTHER OPTION!!\n");
			break;
		}
	}
	while (resp != 0);

	return EXIT_SUCCESS;
}

int menu (void)
{
	int choose;
	printf("\t\t-----------My Cel ------------\n");
	printf("\t\t|  1. Storie                 |\n");
	printf("\t\t|  2. MeusAppsED             |\n");
	printf("\t\t|  3. AppRun                 |\n\t\t|\t\t\t     |\n");
	printf("\t\t------------------------------");

	printf("\n\n\t\tChoose an option: ");
	scanf("%d", &choose);

	return choose;
}

int menuApps(void)
{
	int resp;
	printf("\t\t---------Menu MyAppsED-------------\n");
	printf("\t\t|  1. View My Apps                 |\n");
	printf("\t\t|  2. Run Application              |\n");
	printf("\t\t|  3. Uninstall the application    |\n");
	printf("\t\t|  0. Exit                         |\n\t\t|\t\t\t\t   |\n");
	printf("\t\t------------------------------------");

	printf("\n-------- > Your choose:  ");
	scanf("%d", &resp);
	return resp;
}

int menuAppsRun(void)
{
	int resp;
	printf("\t\t---------Menu MyAppsRun-------------\n");
	printf("\t\t|  1. View My Apps Run             |\n");
	printf("\t\t|  2. Stop App                     |\n");
	printf("\t\t|  0. Exit                         |\n\t\t|\t\t\t\t   |\n");
	printf("\t\t------------------------------------");

	printf("\n-------- > Your choose:  ");
	scanf("%d", &resp);
	return resp;
}

int indiceReturn (int idApp, int id)
{
	int i;

	for (i = 0; i < SIZE; i++)
	{
		if ((id == 1) && (idApp == appStorie[i].id)) return i;
		if ((id == 2) && (idApp == appInstalado[i].id)) return i;
		if ((id == 3) && (idApp == appRun[i].id)) return i;

	}
	return -1;
}

void sort (app App[], app seachApp)
{
	// printf(" - 1");
	app aux;
	int i, j;

	for (i = 0; i < SIZE; i++)
	{
		// printf("- f1");
		if (App[i].size == -1)
		{
			printf(" - if1");
			App[i] = seachApp;
			App[i + 1].size = -1;
			break;
		}
		if (seachApp.size > App[i].size) continue;
		else
		{
			// printf(" - else 1 \n i - %d\n", i);
			for (j = i; j < SIZE; j++)
			{
				// printf(" - f2");
				aux = App[j];
				App[j] = seachApp;
				seachApp = aux;
			}
			break;
		}
	}
}
void excluir (app App[], int indice, int id)
{
	int i, indiceRun;
	int aux = App[indice].id;
	
	for (i = indice; i < SIZE - 1; i++)
		App[i] = App[i +1];
	
	if (id == 1)
	{
		indiceRun = indiceReturn(aux, 3);
		if (indiceRun >= 0) 
		{
			excluir (appRun, indiceRun, 2);
			countAppRun--;
		}
	}

	App[i+1].size = -1;
}
void loadApp (void)
{
	FILE *loadAPP;
	int i;

	if ((loadAPP = fopen("MobileED.txt", "r")) == NULL)
	{
		printf("The apps Can´t be loading\n");
		exit(1);
	}

	for (i = 0; i < SIZE; i++)
	{
		fscanf(loadAPP, "%s %f", appStorie[i].name, &appStorie[i].size);
		sort (appStorie, appStorie[i]);
	}
	for (i = 0; i < SIZE; i++)
	{
		appStorie[i].id = i + 1;
		appStorie[i].status = 0;
	}

}

void menuStories ()
{
	int i, indiceApp, idApp;
	char resposta;

	for (i = 0; i < SIZE; i++)
		printf("%d - %s %.2f\n", appStorie[i].id, appStorie[i].name, appStorie[i].size);

	do
	{
		printf("\n\n-----> Deseja instalar algum app? (y-yes / n - no): ");
		scanf(" %c", &resposta);
	}
	while(!isalpha(resposta));

	if (toupper(resposta) == 'Y')
	{
		do
		{
			printf("\n\n-----> Digite a identificação do app a ser instalado: ");
			scanf("%d", &idApp);
			indiceApp = indiceReturn(idApp, 1);
			if (appStorie[indiceApp].status == 1) 
			{
				printf("\nAPP JA INSTALADO\n");
				return;
			}
			printf("indice = %d", indiceApp);
			if (indiceApp >= 0)
			{
				sort(appInstalado, appStorie[indiceApp]);
				appStorie[indiceApp].status = 1;
				countApp++;
			}
			else printf("APP NAO ENCONTRADO");
		}
		while (indiceApp < 0);
	}
}

void menuMyAppsED()
{
	if (countApp == 0)
	{
		printf("Nenhum app instalado. por favor instale um primeiro.\n");
		return;
	}
	int i, indiceApp, idApp, indiceApp1;
	char resp;

	do
	{
		resp = menuApps();

		switch(resp)
		{
		case 1:
			for (i = 0; i < countApp; i++)
				printf("%s %.2f\n", appInstalado[i].name, appInstalado[i].size);
			break;
		case 2:
			for (i = 0; i < countApp; i++)
				printf("%d - %s %.2f\n", appInstalado[i].id, appInstalado[i].name, appInstalado[i].size);

			do
			{
				printf("\n\n-----> Deseja executar algum app? (y-yes / n-no): ");
				scanf(" %c", &resp);
			}
			while(!isalpha(resp));

			if (toupper(resp) == 'Y')
			{
				do
				{
					printf("\n\n-----> Digite o indice do app a ser executado: ");
					scanf("%d", &idApp);
					indiceApp = indiceReturn(idApp, 2);
					if (appInstalado[indiceApp].status == 1)
					{
						printf("\nAPP JÁ EM EXECUÇÃO\n");
						return;
					}
					if (indiceApp >= 0) 
					
					{
						sort(appRun, appInstalado[indiceApp]);
						appInstalado[indiceApp].status = 1;	
					}
					else printf("\nAPP NAO ENCONTRADO\n");
				}while(indiceApp < 0);
			
				countAppRun++;
			}
			break;
		case 3:
			for (i = 0; i < countApp; i++)
				printf("%d - %s %.2f\n", appInstalado[i].id, appInstalado[i].name, appInstalado[i].size);

			printf("\n\n-----> Digite o indice do app a ser excluido: ");
			scanf("%d", &idApp);

			indiceApp = indiceReturn(idApp, 2);
			indiceApp1 = indiceReturn(idApp, 1);
			excluir (appInstalado, indiceApp, 1);
			
			appStorie[indiceApp1].status = 0;
			appInstalado[indiceApp1].status = 0;
			
			countApp--;
			break;
		case 0:
			return;
		default:
			printf("Invalid Option\n");
			break;
		}
	}
	while ((resp != 1) || (resp != 2));
}

void menuRun()
{
	int i, resp, idApp, indice, indice1;
	do
	{
		resp = menuAppsRun();
		switch(resp)
		{
		case 1:
			printf("\ncase 1\n");
			for (i = 0; i < countAppRun; i++)
				printf("%s %.2f\n", appRun[i].name, appRun[i].size);
			break;
		case 2:
			printf("\ncase 2\n");
			for (i = 0; i < countAppRun; i++)
				printf("%d - %s %.2f\n", appRun[i].id, appRun[i].name, appRun[i].size);

			printf("\n\n-----> Digite o indice do app a para ser parada a execução: ");
			scanf("%d", &idApp);

			indice = indiceReturn(idApp, 3);
			indice1 = indiceReturn(idApp, 2);
			
			excluir (appRun, indice, 2);	
			
			appInstalado[indice1].status = 0;
			
			countAppRun--;
			break;
		case 0:
			return;
		default:
			printf("\nInvalid Option\n");
			break;
		}

	}
	while ((resp >	 0) && (resp < 2));
}
