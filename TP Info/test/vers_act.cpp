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
struct city_prom
{
	int id;
	char name[50];
	float temperature; 
	int ctr;
	struct city_prom *next;
};

struct dia_cal_city
{
	int id;
	char name[50];
	float temp; 
	int day;
	int month;
	struct dia_cal_city *next;
};
void printlist(struct city*,struct city*,struct city*);
void printprom(struct city_prom*,struct city_prom*,struct city_prom*);
main(int argc, char *argv[]) 
{
	struct city *head_cba=NULL;//Lista enlazada para cordoba
	struct city *head_stafe=NULL;//Lista enlazada para santa fe
	struct city *head_mndza=NULL;//Lista enlazada para mendoza
	struct city_prom *head_ctyprm_cba=NULL; 
	struct city_prom *head_ctyprm_stafe=NULL; 
	struct city_prom *head_ctyprm_mndza=NULL; 
	struct city *temp=NULL;
	struct city *newnode=NULL;
	struct city_prom *newnode_2=NULL;
	struct city_prom *temp_2=NULL;
	struct dia_cal_city *newnode_cal=NULL;
	struct dia_cal_city *temp_cal=NULL;
	struct min_city cbamin,mndzamin,stafemin; //estructura para temp min por provincia
	int ctr_cba=0,ctr_mndza=0,ctr_stafe=0; //contador muestras por provincia
	float sum_cba=0,sum_stafe=0,sum_mndza=0; //suma de muestas por provincia
	float prom_cba=0,prom_stafe=0,prom_mndza=0; //promedio de temp por provincia
	int ret=0;
	int opt; 
	char cont;
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
					newnode_2=(struct city_prom*)malloc(sizeof(struct city_prom));
					if (newnode_2==NULL)
					{
						printf("\nno hay memoria suficiente"); 
						exit (1);
					}else{
						newnode_2->ctr=1; 
						strcpy(newnode_2->name,newnode->city_name);
						newnode_2->id=newnode->cityId;
						newnode_2->temperature+=newnode->m.temp;
						newnode_2->next=NULL;
						head_ctyprm_cba=newnode_2;
					}
				}else{
					ret=strcmp(newnode_2->name,newnode->city_name);
					if (ret==0)	//si string es = q anterior
					{
						newnode_cal=(struct dia_cal_city*)malloc(sizeof(struct dia_cal_city)); //lista para dia mas calida x ciudad
						if (newnode_cal==NULL)	//lista para dia mas calida x ciudad
						{
							printf("\nno hay memoria suficiente"); 
							exit (1);
						}
						else
						{
//							if(newnode_2->ctr==0) hacer counter nuevo
							{	
								strcpy(newnode_cal->name,newnode->city_name);
								newnode_cal->id=newnode->cityId;
								newnode_cal->temperature=newnode->m.temp;
								newnode_cal->next=NULL;
								temp_cal=head_ctyprm_cba;
							}
							else
							{
								if(newnode->m.temp > newnode_cal->temperature)
								{
									strcpy(newnode_cal->name,newnode->city_name);
									newnode_cal->id=newnode->cityId;
									newnode_cal->temperature=newnode->m.temp;
									newnode_cal->next=NULL;
									temp_cal=head_ctyprm_cba;
								}
								while(temp_cal->next!=NULL)
								{
									temp_cal=temp_cal->next;
								}
								temp_cal->next=newnode_cal;
								
							}
						}
						newnode_2->temperature+=newnode->m.temp; //sumatoria de temp por ciudad
						newnode_2->ctr++;
					}else{
						newnode_2=(struct city_prom*)malloc(sizeof(struct city_prom));
						if (newnode_2==NULL)
						{
							printf("\nno hay memoria suficiente"); 
							exit (1);
						}else{
							strcpy(newnode_2->name,newnode->city_name);
							newnode_2->id=newnode->cityId;
							newnode_2->temperature+=newnode->m.temp;
							newnode_2->next=NULL;
							temp_2=head_ctyprm_cba;
							while(temp_2->next!=NULL)
							{
								temp_2=temp_2->next;
							}
							temp_2->next=newnode_2;
							newnode_2->ctr++;
						}
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
				
				
				if (ctr_stafe==0)
				{
					newnode_2=(struct city_prom*)malloc(sizeof(struct city_prom));
					if (newnode_2==NULL)
					{
						printf("\nno hay memoria suficiente"); 
						exit (1);
					}else{
						newnode_2->ctr=1; 
						strcpy(newnode_2->name,newnode->city_name);
						newnode_2->id=newnode->cityId;
						newnode_2->temperature+=newnode->m.temp;
						newnode_2->next=NULL;
						head_ctyprm_stafe=newnode_2;
					}
				}else{
					ret=strcmp(newnode_2->name,newnode->city_name);
					if (ret==0)
					{
						newnode_2->temperature+=newnode->m.temp;
						newnode_2->ctr++;
					}else{
						newnode_2=(struct city_prom*)malloc(sizeof(struct city_prom));
						if (newnode_2==NULL)
						{
							printf("\nno hay memoria suficiente"); 
							exit (1);
						}else{
							strcpy(newnode_2->name,newnode->city_name);
							newnode_2->id=newnode->cityId;
							newnode_2->temperature+=newnode->m.temp;
							newnode->next=NULL;
							temp_2=head_ctyprm_stafe;
							while(temp_2->next!=NULL)
							{
								temp_2=temp_2->next;
							}
							temp_2->next=newnode_2;
							newnode_2->ctr++;
						}
					}
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
				
				if (ctr_mndza==0)
				{
					newnode_2=(struct city_prom*)malloc(sizeof(struct city_prom));
					if (newnode_2==NULL)
					{
						printf("\nno hay memoria suficiente"); 
						exit (1);
					}else{
						newnode_2->ctr=1; 
						strcpy(newnode_2->name,newnode->city_name);
						newnode_2->id=newnode->cityId;
						newnode_2->temperature+=newnode->m.temp;
						newnode_2->next=NULL;
						head_ctyprm_mndza=newnode_2;
					}
				}else{
					ret=strcmp(newnode_2->name,newnode->city_name);
					if (ret==0)
					{
						newnode_2->temperature+=newnode->m.temp;
						newnode_2->ctr++;
					}else{
						newnode_2=(struct city_prom*)malloc(sizeof(struct city_prom));
						if (newnode_2==NULL)
						{
							printf("\nno hay memoria suficiente"); 
							exit (1);
						}else{
							strcpy(newnode_2->name,newnode->city_name);
							newnode_2->id=newnode->cityId;
							newnode_2->temperature+=newnode->m.temp;
							newnode->next=NULL;
							temp_2=head_ctyprm_mndza;
							while(temp_2->next!=NULL)
							{
								temp_2=temp_2->next;
							}
							temp_2->next=newnode_2;
							newnode_2->ctr++;
						}
					}
				}
				
				ctr_mndza++;
				sum_mndza+=newnode->m.temp;
			}
		}//if()//aca hay que poner una condicion para ver el valor mas aproximado a 23 que es la temperatura para cosechar pimientos
	}
	prom_cba=sum_cba/ctr_cba;
	prom_stafe=sum_stafe/ctr_stafe;
	prom_mndza=sum_mndza/ctr_mndza;
	do{
		cout<<"\n***Men? de opciones***\n"<<endl;
		cout<<"\nIngrese:\n1:Total de las muestras de cada provincia\n2:Temperatura promedio de cada provincia\n3:Temperatura promedio de cada ciudad";
		cout<<"\n4:Ciudad mas calida de cada provincia\n5:Ciudad mas fria de cada provincia\n6:Dia mas frio de cada provincia\n7:Dia mas calido de cada ciudad\n8:Mejor provincia para el cultivo de pimientos\n";
		cin>>opt; 
		switch (opt)
		{
		case 1:
			printf("\n\n\n\nContador Cba: %d - Contador Stafe: %d - Contador Mndza: %d", ctr_cba,ctr_stafe,ctr_mndza);
			break; 
		case 2:
			printf("\n\n\n\nTemp Prom Cba: %f - Temp Prom Stafe: %f - Temp Prom Mndza: %f", (prom_cba),(prom_stafe),(prom_mndza));
			break; 
		case 3: //funcion printlist
			printf("\n***TEMPERATURAS PROMEDIO***\n");
			printprom(head_ctyprm_cba,head_ctyprm_mndza,head_ctyprm_stafe);
			break; 
		case 4://ciudad mas calida
			break; 
		case 5:
			printf("\n\n**Ciudad de Cordoba Con dia Mas Frio**\nNombre: %s\nId: %d\nFecha: %d/%d\nTemp: %f?C", cbamin.name,cbamin.id,cbamin.day,cbamin.month,cbamin.temp);
			printf("\n\n**Ciudad de Santa Fe Con dia Mas Frio**\nNombre: %s\nId: %d\nFecha: %d/%d\nTemp: %f?C", stafemin.name,stafemin.id,stafemin.day,stafemin.month,stafemin.temp);
			printf("\n\n**Ciudad de Mendoza Con dia Mas Frio**\nNombre: %s\nId: %d\nFecha: %d/%d\nTemp: %f?C", mndzamin.name,mndzamin.id,mndzamin.day,mndzamin.month,mndzamin.temp);
			break; 
		case 6://dia m?s frio de cada provincia
			break; 
		case 7://dia m?s calido de cada ciudad
			break; 
		case 8://Mejor provincia para el cultivo de pimientos
			break; 
		default: 
			cout<<"\nse ha ingresado mal la opci?n"<<endl; 
			break; 
		}
		cout<<"\ncontinuar en el menu? [s/n]"<<endl; 
		cin>>cont;
	} while((cont=='s')||(cont=='S'));
	
	cout<<"\ndesea imprimir??[s/n]"<<endl;
	cin>>cont; 
	if ((cont=='s')||(cont=='S'))
	{
		printlist(head_cba ,head_mndza ,head_stafe); ///////NUEVO
	}
	return 0;
}

void printlist(struct city* head_cba ,struct city* head_mndza ,struct city* head_stafe)
{
	struct city* temp=NULL;
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
}

void printprom(struct city_prom* head_ctyprm_cba, struct city_prom* head_ctyprm_mndza, struct city_prom* head_ctyprm_stafe)
{
	struct city_prom *temp_2=NULL;
	printf("\n***Ciudades de cordoba***\n\nCityId \t CityName \t Temperature");
	temp_2=head_ctyprm_cba;
	while(temp_2!=NULL)
	{
		printf(" \n%d \t %s \t %f \n", temp_2->id, temp_2->name, (temp_2->temperature)/temp_2->ctr);
		temp_2=temp_2->next;
	}
	printf("\n***Ciudades de santa fe***\n\nCityId \t CityName \t Temperature");
	temp_2=head_ctyprm_stafe;
	while(temp_2!=NULL)
	{
		printf(" \n%d \t %s \t %f \n", temp_2->id, temp_2->name, (temp_2->temperature)/temp_2->ctr);
		temp_2=temp_2->next;
	}
	printf("\n***Ciudades de mendoza***\n\nCityId \t CityName \t Temperature");
	temp_2=head_ctyprm_mndza;
	while(temp_2!=NULL)
	{
		printf(" \n%d \t %s \t %f \n", temp_2->id, temp_2->name, (temp_2->temperature)/temp_2->ctr);
		temp_2=temp_2->next;
	}
}
