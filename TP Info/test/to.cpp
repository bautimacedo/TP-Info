#include <iostream>
#include <string.h>
using namespace std;
struct timestamp
{
	int day;
	int month;
	int hh;
	int mm;
};

struct measurement
{
	float temp;
	float hum;
	struct timestamp time;
};

struct city
{
	struct city *next;
	struct measurement m;
	int cityId;
	int provinceId;
	char city_name[50];
};

struct min_city //estructura nueva
{
	int id;
	char name[50];
	float temp; 
	int day;
	int month;
};
struct prom
{
	int id;
	char name[50];
	float temperature; 
	struct city_prom *next;
};
main(int argc, char *argv[]) 
{
	struct city *head_cba=NULL;//Lista enlazada para cordoba
	struct city *head_stafe=NULL;//Lista enlazada para santa fe
	struct city *head_mndza=NULL;//Lista enlazada para mendoza
	struct city_prom *head_ctyprm=NULL; 
	struct city *temp=NULL;
	struct city *newnode=NULL;
	struct city *newnode_2=NULL;
	struct min_city cbamin,mndzamin,stafemin; //estructura para temp min por provincia
	int ctr_cba=0,ctr_mndza=0,ctr_stafe=0; //contador muestras por provincia
	float sum_cba=0,sum_stafe=0,sum_mndza=0; //suma de muestas por provincia
	float prom_cba=0,prom_stafe=0,prom_mndza=0; //promedio de temp por provincia
	FILE *fp;
	fp=fopen("./data_set.txt", "rb");
	if(fp==NULL)
	{
		printf("Imposible abrir el archivo");
		exit(1);//exit 1 es para algun problema en los archivos 
	}
	
	while(feof(fp)==0)
	{
		newnode=(struct city*)malloc(sizeof(struct city));
		if (newnode==NULL)
		{
			printf("error para crear otro nodo ");
			exit(2);//exit 2 es para problemas con las estucturas
		}else{
			fscanf(fp,"%d",&newnode->cityId);//City id
			fscanf(fp,"%d",&newnode->provinceId);//Province	id		
			fscanf(fp,"%s",&newnode->city_name);//City name
			fscanf(fp,"%f",&newnode->m.temp);//Temperature 
			fscanf(fp,"%f",&newnode->m.hum);//Humidity 
			fscanf(fp,"%d",&newnode->m.time.hh);//Hour
			fscanf(fp,"%d",&newnode->m.time.mm);//Minute
			fscanf(fp,"%d",&newnode->m.time.day);//Day
			fscanf(fp,"%d",&newnode->m.time.month);//Month
			newnode->next=NULL;
			if (newnode->provinceId==1)
			{
				if(head_cba==NULL)
				{
					head_cba=newnode;
				}else{
					temp=head_cba;
					while(temp->next!=NULL)
					{
						temp=temp->next;
					}
					temp->next=newnode;
				}
				if(ctr_cba==0)
				   cbamin.temp=newnode->m.temp; //el ctrcba == 0 para que solo en el primero se iguale la temperatura 
				if((newnode->m.temp) < (cbamin.temp))
				{
					cbamin.temp=newnode->m.temp;
					strcpy(cbamin.name,newnode->city_name);
					cbamin.id=newnode->cityId;
					cbamin.day=newnode->m.time.day;
					cbamin.month=newnode->m.time.month;
				}
// nuevo
				if (ctr_cba==0)
				{
					newnode_2=(struct prom*)malloc(sizeof(struct prom));
					if (newnode_2==NULL)
					{
						printf("\nno hay memoria suficiente"); 
						exit (1);
					}else{
						strcpy(newnode_2->name,newnode->city_name);
						newnode_2->id=newnode->cityId;
						newnode_2->temperature+=newnode->m.temp;
						newnode->next=NULL;
						head_ctyprm=newnode;
					}
				}else{
					temp=(struct city_prom*)malloc(sizeof(struct city_prom));
					if (newnode_2==NULL)
					{
						printf("\nno hay memoria suficiente"); 
						exit (1);
					}else{
						strcpy(newnode_2->name,newnode->city_name);
						newnode_2->id=newnode->cityId;
						newnode_2->temperature+=newnode->m.temp;
						newnode->next=NULL;
						head_ctyprm=newnode;
						temp=head_ctyprm;
						while(temp->next!=NULL)
						{
							temp=temp->next;
						}
						temp->next=newnode;
					}
				}
//
				ctr_cba++;//contador de muestas 
				sum_cba+=newnode->m.temp;//sumador de temperaturas para cada provincia
			}
			
			
			
			if (newnode->provinceId==2)
			{
				if(head_stafe==NULL)
				{
					head_stafe=newnode;
				}else{
					temp=head_stafe;
					while(temp->next!=NULL)
					{
						temp=temp->next;
					}
					temp->next=newnode;
				}
				if(ctr_stafe==0)
				   stafemin.temp=newnode->m.temp; //el ctrcba == 0 para que solo en el primero se iguale al temp 
				if((newnode->m.temp) < (stafemin.temp))
				{
					stafemin.temp=newnode->m.temp;
					strcpy(stafemin.name,newnode->city_name);
					stafemin.id=newnode->cityId;
					stafemin.day=newnode->m.time.day;
					stafemin.month=newnode->m.time.month;
				}
				ctr_stafe++;
				sum_stafe+=newnode->m.temp;
			}
			if (newnode->provinceId==3)
			{
				if(head_mndza==NULL)
				{
					head_mndza=newnode;
				}else{
					temp=head_mndza;
					while(temp->next!=NULL)
					{
						temp=temp->next;
					}
					temp->next=newnode;
				}
				if(ctr_mndza==0)
				   mndzamin.temp=newnode->m.temp; //el ctrcba == 0 para que solo en el primero se iguale al temp 
				if((newnode->m.temp) < (mndzamin.temp))
				{
					mndzamin.temp=newnode->m.temp;
					strcpy(mndzamin.name,newnode->city_name);
					mndzamin.id=newnode->cityId;
					mndzamin.day=newnode->m.time.day;
					mndzamin.month=newnode->m.time.month;
				}
				ctr_mndza++;
				sum_mndza+=newnode->m.temp;
			}
		}
		prom_cba=sum_cba/ctr_cba;
		prom_stafe=sum_stafe/ctr_stafe;
		prom_mndza=sum_mndza/ctr_mndza;
		//if()//aca hay que poner una condicion para ver el valor mas aproximado a 23 que es la temperatura para cosechar pimientos
		
	}
	temp=head_cba;
	printf("CityId \tProvinceId\t CityName \t Temperature \t Humidity\tHour \t Min\tDay \tMonth\n");
	while(temp!=NULL)
	{
		printf(" %d\t %d \t %s \t %f \t %f \t %d \t %d \t %d \t %d\n", temp->cityId, temp->provinceId, temp->city_name, temp->m.temp, temp->m.hum, temp->m.time.hh, temp->m.time.mm,  temp->m.time.day,temp->m.time.month);
		temp=temp->next;
	}
	temp=head_stafe;
	while(temp!=NULL)
	{
		printf(" %d\t %d \t %s \t %f \t %f \t %d \t %d \t %d \t %d\n", temp->cityId, temp->provinceId, temp->city_name, temp->m.temp, temp->m.hum, temp->m.time.hh, temp->m.time.mm,  temp->m.time.day,temp->m.time.month);
		temp=temp->next;
	}
	temp=head_mndza;
	while(temp!=NULL)
	{
		printf(" %d\t %d \t %s \t %f \t %f \t %d \t %d \t %d \t %d\n", temp->cityId, temp->provinceId, temp->city_name, temp->m.temp, temp->m.hum, temp->m.time.hh, temp->m.time.mm,  temp->m.time.day,temp->m.time.month);
		temp=temp->next;
	}
	
	printf("\n\n\n\nContador Cba: %d - Contador Stafe: %d - Contador Mndza: %d", ctr_cba,ctr_stafe,ctr_mndza);
	printf("\n\n\n\nTemp Prom Cba: %f - Temp Prom Stafe: %f - Temp Prom Mndza: %f", (prom_cba),(prom_stafe),(prom_mndza));
	printf("\n\n**Ciudad de Cordoba Con dia Mas Frio**\nNombre: %s\nId: %d\nFecha: %d/%d\nTemp: %f°C", cbamin.name,cbamin.id,cbamin.day,cbamin.month,cbamin.temp);
	printf("\n\n**Ciudad de Santa Fe Con dia Mas Frio**\nNombre: %s\nId: %d\nFecha: %d/%d\nTemp: %f°C", stafemin.name,stafemin.id,stafemin.day,stafemin.month,stafemin.temp);
	printf("\n\n**Ciudad de Mendoza Con dia Mas Frio**\nNombre: %s\nId: %d\nFecha: %d/%d\nTemp: %f°C", mndzamin.name,mndzamin.id,mndzamin.day,mndzamin.month,mndzamin.temp);
	return 0;
}
