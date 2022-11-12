#include <iostream>
#include <string.h>
using namespace std;
class province{
private:
	int contador_cba;
	int contador_stafe;
	int contador_mndza;
	float temperaturas_cba;
	float temperaturas_stafe;
	float temperaturas_mndza;
	float prom_cba; 
	float prom_mndza; 
	float prom_stafe; 
	float dif_cba;
	float dif_mndza;
	float dif_stafe;
public:
	province(int c_cba,int c_stafe,int c_mndza,float t_cba,float t_stafe,float t_mndza){
		cout<<"\nInstanciando constructor..."<<endl; 
		contador_cba=c_cba;
		contador_stafe=c_stafe;
		contador_mndza=c_mndza;
		temperaturas_cba=t_cba;
		temperaturas_stafe=t_stafe;
		temperaturas_mndza=t_mndza;
	};
	float getprom_cba (){
		return prom_cba;
	};
	float getprom_stafe (){
		return prom_stafe;
	};
	float getprom_mndza (){
		return prom_mndza;
	};
	void set_prom_cba (){
		prom_cba=temperaturas_cba/contador_cba;
	};
	void set_prom_stafe (){
		prom_stafe=temperaturas_stafe/contador_stafe;
	};
	void set_prom_mndza (){
		prom_mndza=temperaturas_mndza/contador_mndza;
	};
	void pimientos (){
		dif_cba=23-prom_cba; 
		if (dif_cba<0)
		{
			(dif_cba=dif_cba*-1);
		}
		dif_stafe=23-prom_stafe; 
		if (dif_stafe<0)
		{
			(dif_stafe=dif_stafe*-1);
		}
		dif_mndza=23-prom_mndza; 
		if (dif_mndza<0)
		{
			(dif_mndza=dif_mndza*-1);
		}
		if((dif_cba<dif_stafe)&&(dif_cba<dif_mndza))
		{
			cout<<"\nLa mejor provincia para cultivar pimientos es Cordoba con "<<prom_cba<<" grados"<<endl; 
		}
		if((dif_mndza<dif_stafe)&&(dif_mndza<dif_cba))
		{
			cout<<"\nLa mejor provincia para cultivar pimientos es Mendoza con "<<prom_mndza<<" grados"<<endl; 
		}
		if((dif_stafe<dif_cba)&&(dif_stafe<dif_mndza))
		{
			cout<<"\nLa mejor provincia para cultivar pimientos es Santa fe con "<<prom_stafe<<" grados"<<endl; 
		}
	};
};
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
	struct measurement m;
	int cityId;
	int provinceId;
	char city_name[50];
};
struct node
{
	struct node *next;
	struct city c; 
};
struct city_prom
{
	int id;
	char name[50];
	float temperature; 
	int ctr;
	struct city_prom *next;
};
struct cal{
	int Id;
	char name[50];
	float temperature;
	int day; 
	int month;
	struct cal *next;
};
void push (struct node**,struct city,float*);
void print (struct node*,struct node*,struct node*);
void temp_prom (struct city_prom**,struct node*);
void printprom(struct city_prom*,struct city_prom*,struct city_prom*);
void calido(struct city_prom *);
void frio(struct city_prom *);
void d_frio(struct node*);
void d_cal(struct node*, struct cal**);
void printd_cal(struct cal*);

int main(int argc, char *argv[]) 
{
	struct city c;
	
	struct node *head_cba=NULL;//Lista enlazada para cordoba
	struct node *head_stafe=NULL;//Lista enlazada para santa fe
	struct node *head_mndza=NULL;//Lista enlazada para mendoza
	
	struct city_prom *head_ctyprm_cba=NULL; 
	struct city_prom *head_ctyprm_stafe=NULL; 
	struct city_prom *head_ctyprm_mndza=NULL; 
	
	struct cal *head_cal_cba=NULL;
	struct cal *head_cal_stafe=NULL;
	struct cal *head_cal_mndza=NULL;
	
	int ctr_cba=0,ctr_mndza=0,ctr_stafe=0;
	float temp_cba=0,temp_mndza=0,temp_stafe=0;
	int opt;
	char cont;

	FILE *fp; 
	fp=fopen("./data_set.txt", "rb");
	
	if(fp==NULL)
	{
		printf("Imposible abrir el archivo");
		exit(2);//exit 2 es para algun problema en los archivos 
	}
	while(feof(fp)==0)
	{
		fscanf(fp,"%d",&c.cityId);//City id
		fscanf(fp,"%d",&c.provinceId);//Province id		
		fscanf(fp,"%s",c.city_name);//City name
		fscanf(fp,"%f",&c.m.temp);//Temperatura
		fscanf(fp,"%f",&c.m.hum);//Humedad 
		fscanf(fp,"%d",&c.m.time.hh);//Hora
		fscanf(fp,"%d",&c.m.time.mm);//Minuto
		fscanf(fp,"%d",&c.m.time.day);//Dia
		fscanf(fp,"%d",&c.m.time.month);//Mes
		
		if (c.provinceId==1)//cordoba
		{
			push(&head_cba,c,&temp_cba);
			
			ctr_cba++;
		}
		if (c.provinceId==2)//santa fe
		{
			push(&head_stafe,c,&temp_stafe);
			
			ctr_stafe++;
		}
		if (c.provinceId==3)//mendoza
		{
			push(&head_mndza,c,&temp_mndza);
			
			ctr_mndza++;
		}
		if(c.provinceId>3||c.provinceId<1)
		{
			cout<<"El codigo de provincia "<<c.provinceId<<" no existe"<<endl;
		}
	}
	temp_prom(&head_ctyprm_cba,head_cba);
	temp_prom(&head_ctyprm_stafe,head_stafe);
	temp_prom(&head_ctyprm_mndza,head_mndza);
	province p(ctr_cba,ctr_stafe,ctr_mndza,temp_cba,temp_stafe,temp_mndza);
	p.set_prom_cba();
	p.set_prom_stafe();
	p.set_prom_mndza();
	do{
		cout<<"\n***Menú de opciones***\n"<<endl;
		cout<<"\nIngrese:\n1:Total de las muestras de cada provincia\n2:Temperatura promedio de cada provincia\n3:Temperatura promedio de cada ciudad";
		cout<<"\n4:Ciudad mas calida de cada provincia\n5:Ciudad mas fria de cada provincia\n6:Dia mas frio de cada provincia\n7:Dia mas calido de cada ciudad\n8:Mejor provincia para el cultivo de pimientos\n";
		cin>>opt; 
		switch (opt)
		{
		case 1://contadores de cada provincia
			printf("\n\n\n\nContador Cba: %d - Contador Stafe: %d - Contador Mndza: %d", ctr_cba,ctr_stafe,ctr_mndza);
			break; 
		case 2://promedios de provincias
			cout<<"\nPromedio Cordoba "; 
			cout<<p.getprom_cba()<<endl;
			cout<<"\nPromedio Santa Fe "; 
			cout<<p.getprom_stafe()<<endl;
			cout<<"\nPromedio Santa Mendoza "; 
			cout<<p.getprom_mndza()<<endl;
			break; 
		case 3://promedios de cada ciudad
			printf("\n***TEMPERATURAS PROMEDIO***\n");
			printprom(head_ctyprm_cba,head_ctyprm_mndza,head_ctyprm_stafe);
			break; 
		case 4://ciudad más calida de cada provincia
			cout<<"\nCiudades con temperaturas más calidas"<<endl; 
			cout<<"\nCiudad más calida de Cordoba"<<endl;
			calido(head_ctyprm_cba);
			cout<<"\nCiudad más calida de Santa fe"<<endl;
			calido(head_ctyprm_stafe);
			cout<<"\nCiudad más calida de Mendoza"<<endl;
			calido(head_ctyprm_mndza);
			break; 
		case 5://ciudad mas fria de cada provincia
			cout<<"\nCiudades con temperaturas más frias"<<endl; 
			cout<<"\nCiudad más fria de Cordoba"<<endl;
			frio(head_ctyprm_cba);
			cout<<"\nCiudad más fria de Santa fe"<<endl;
			frio(head_ctyprm_stafe);
			cout<<"\nCiudad más fria de Mendoza"<<endl;
			frio(head_ctyprm_mndza);
			break; 
		case 6://dia más frio de cada provincia
			cout<<"\nDias más frios de cada provincia"<<endl; 
			cout<<"Día más frio de córdoba"<<endl; 
			d_frio(head_cba);
			cout<<"Día más frio de santa fe"<<endl; 
			d_frio(head_stafe);
			cout<<"Día más frio de mendoza"<<endl; 
			d_frio(head_mndza);
			break; 
		case 7://dia más calido de cada ciudad
			d_cal(head_cba,&head_cal_cba);
			cout<<"\nDias más calidos de las ciudades de cordoba"<<endl; 
			printd_cal(head_cal_cba);
			d_cal(head_stafe,&head_cal_stafe);
			cout<<"\nDias más calidos de las ciudades de Santa Fe"<<endl;
			printd_cal(head_cal_stafe);
			d_cal(head_mndza,&head_cal_mndza);
			cout<<"\nDias más calidos de las ciudades de Mendoza"<<endl; 
			printd_cal(head_cal_mndza);
			break; 
		case 8://Mejor provincia para el cultivo de pimientos
			p.pimientos();
			break; 
		default: 
			cout<<"\nse ha ingresado mal la opción"<<endl; 
			break; 
		}
		cout<<"\ncontinuar en el menu? [s/n]"<<endl; 
		cin>>cont;
	}while((cont=='s')||(cont=='S'));
	
	cout<<"\nDesea imprimir todos los datos??[s/n]"<<endl;
	cin>>cont; 
	if ((cont=='s')||(cont=='S'))
	{
		print(head_cba,head_stafe,head_mndza);
	}
	return 0;
}
void push (struct node** head, struct city c, float *temperature)//push de lista para cada provincia
{
	struct node* temp=NULL; 
	struct node* newnode=NULL; 
	newnode=(struct node*)malloc(sizeof(struct node));
	if(newnode==NULL)
	{
		cout<<"\nNo hay memoria disponible"<<endl; 
		exit (1);//Exit 1 es para errores en la memoria
	}else{
		newnode->c=c;
		newnode->next=NULL; 
		*temperature+=newnode->c.m.temp;
		if (*head==NULL)
		{
			*head=newnode;
		}else{
			temp=*head; 
			while(temp->next!=NULL)
			{
				temp=temp->next;
			}
			temp->next=newnode;
		}
	}
}
void print (struct node *head_cba,struct node *head_stafe,struct node *head_mndza)//impresion total de datos
{
	struct node* temp=NULL;
	temp=head_cba;
	printf("CityId \tProvinceId\t CityName \t Temperature \t Humidity\tHour \t Min\tDay \tMonth\n");
	while(temp!=NULL)
	{
		printf(" %d\t %d \t %s \t %f \t %f \t %d \t %d \t %d \t %d\n", temp->c.cityId, temp->c.provinceId, temp->c.city_name, temp->c.m.temp, temp->c.m.hum, temp->c.m.time.hh, temp->c.m.time.mm,  temp->c.m.time.day,temp->c.m.time.month);
		temp=temp->next;
	}
	temp=head_stafe;
	while(temp!=NULL)
	{
		printf(" %d\t %d \t %s \t %f \t %f \t %d \t %d \t %d \t %d\n", temp->c.cityId, temp->c.provinceId, temp->c.city_name, temp->c.m.temp, temp->c.m.hum, temp->c.m.time.hh, temp->c.m.time.mm,  temp->c.m.time.day,temp->c.m.time.month);
		temp=temp->next;
	}
	temp=head_mndza;
	while(temp!=NULL)
	{
		printf(" %d\t %d \t %s \t %f \t %f \t %d \t %d \t %d \t %d\n", temp->c.cityId, temp->c.provinceId, temp->c.city_name, temp->c.m.temp, temp->c.m.hum, temp->c.m.time.hh, temp->c.m.time.mm,  temp->c.m.time.day,temp->c.m.time.month);
		temp=temp->next;
	}
}
void temp_prom(struct city_prom **head, struct node *node)//push de listas de promedios de cada ciudad
{
	struct city_prom *newnode=NULL; 
	struct city_prom *temp=NULL;
	struct node *temp_node=NULL;
	int ret=0;
	int counter=0;
	
	temp_node=node;
	while (temp_node!=NULL)
	{
		if((counter==0)&&(*head==NULL))
		{
			newnode=(struct city_prom*)malloc(sizeof(struct city_prom));
			if(newnode==NULL)
			{
				cout<<"\nNo hay memoria disponible"; 
				exit(1);
			}else{
			newnode->next=NULL; 
			newnode->ctr=1;
			strcpy(newnode->name,temp_node->c.city_name);
			newnode->id=temp_node->c.cityId;
			newnode->temperature=temp_node->c.m.temp;
			*head=newnode;
			counter++;
			}
		}else{
			ret=strcmp(newnode->name,temp_node->c.city_name);
			if (ret==0)
			{
				newnode->temperature+=temp_node->c.m.temp;
				newnode->ctr++;
			}else{
				newnode=(struct city_prom*)malloc(sizeof(struct city_prom));
				if (newnode==NULL)
				{
					printf("\nno hay memoria suficiente"); 
					exit (1);
				}else{
					strcpy(newnode->name,temp_node->c.city_name);
					newnode->id=temp_node->c.cityId;
					newnode->temperature+=temp_node->c.m.temp;
					newnode->ctr++;
					newnode->next=NULL;
					temp=*head;
					while(temp->next!=NULL)
					{
						temp=temp->next;
					}
					temp->next=newnode;
				}
			}
		}
		temp_node=temp_node->next;
	}	
}
void printprom(struct city_prom *head_ctyprm_cba, struct city_prom *head_ctyprm_mndza, struct city_prom *head_ctyprm_stafe)//impresion lista promedios de cada ciudad
{
	struct city_prom *temp=NULL;
	printf("\n***Ciudades de cordoba***\n\nCityId \t CityName \t\t Temperature\n");
	temp=head_ctyprm_cba;
	while(temp!=NULL)
	{
		printf("\t%d \t %s \t\t %f \n", temp->id, temp->name, (temp->temperature)/temp->ctr);
		temp=temp->next;
	}
	printf("\n***Ciudades de santa fe***\n\nCityId \t CityName \t\t Temperature\n");
	temp=head_ctyprm_stafe;
	while(temp!=NULL)
	{
		printf("\t%d \t %s \t\t %f \n", temp->id, temp->name, (temp->temperature)/temp->ctr);
		temp=temp->next;
	}
	printf("\n***Ciudades de mendoza***\n\nCityId \t CityName \t\t Temperature\n");
	temp=head_ctyprm_mndza;
	while(temp!=NULL)
	{
		printf("\t%d \t %s \t\t %f \n", temp->id, temp->name, (temp->temperature)/temp->ctr);
		temp=temp->next;
	}
}
void calido(struct city_prom *head)//ciudad mas calida de cada provincia
{
	struct city_prom *temp=NULL; 
	int id;
	char name[50];
	float temperature; 
	int ctr=0;
	temp=head; 
	while(temp!=NULL)
	{
		if(ctr==0)
		{
			id=temp->id;
			strcpy(name,temp->name);
			temperature=temp->temperature/temp->ctr;
			ctr=1;
		}
		if((ctr!=0)&&((temp->temperature/temp->ctr)>temperature))
		{	
			id=temp->id;
			strcpy(name,temp->name);
			temperature=temp->temperature/temp->ctr;
		}	
		temp=temp->next;
	}
	cout<<"ID "<<id; 
	cout<<"\tNOMBRE "<<name; 
	cout<<"\tTEMPERATURA "<<temperature<<endl; 
	
}
void frio (struct city_prom *head)//ciudad más fria de cada provincia
{
	struct city_prom *temp=NULL; 
	int id;
	char name[50];
	float temperature; 
	int ctr=0;
	temp=head; 
	while(temp!=NULL)
	{
		if(ctr==0)
		{
			id=temp->id;
			strcpy(name,temp->name);
			temperature=temp->temperature/temp->ctr;
			ctr=1;
		}
		if((ctr!=0)&&((temp->temperature/temp->ctr)<temperature))
		{	
			id=temp->id;
			strcpy(name,temp->name);
			temperature=temp->temperature/temp->ctr;
		}	
		temp=temp->next;
	}
	cout<<"ID "<<id; 
	cout<<"\tNOMBRE "<<name; 
	cout<<"\tTEMPERATURA "<<temperature<<endl; 
	
}
void d_frio (struct node* head)//dia más frio de cada provincia
{
	struct node *temp=NULL; 
	int id;
	int dia; 
	int mes; 
	char nombre[50];
	float temperatura; 
	int ctr=0;
	temp=head; 
	while(temp!=NULL)
	{
		if(ctr==0)
		{
			id=temp->c.cityId;
			strcpy(nombre,temp->c.city_name);
			temperatura=temp->c.m.temp;
			dia=temp->c.m.time.day;
			mes=temp->c.m.time.month;
			ctr=1;
		}
		if((ctr!=0)&&((temp->c.m.temp)<temperatura))
		{
			id=temp->c.cityId;
			strcpy(nombre,temp->c.city_name);
			temperatura=temp->c.m.temp;
			dia=temp->c.m.time.day;
			mes=temp->c.m.time.month;
		}
		temp=temp->next;
	}
	cout<<"ID "<<id<<endl; 
	cout<<"NOMBRE "<<nombre<<endl; 
	cout<<"DIA "<<dia<<endl; 
	cout<<"MES "<<mes<<endl;
	cout<<"TEMPERATURA "<<temperatura<<endl; 
}
void d_cal (struct node *node,struct cal **head)//dia mas calido de cada ciudad
{
	struct node *temp_node=NULL;
	struct cal *newnode=NULL;
	struct cal *temp=NULL; 
	int ret;
	int ctr=0;
	temp_node=node;
	while(temp_node!=NULL)
	{
		if((ctr==0)&&(*head==NULL))
		{
			newnode=(struct cal*)malloc(sizeof(struct cal));
			if(newnode==NULL)
			{
				cout<<"\nNo hay memoria disponible"; 
				exit(1);
			}else{
				ctr=1;
				newnode->next=NULL;
				newnode->Id=temp_node->c.cityId;
				strcpy(newnode->name,temp_node->c.city_name);
				newnode->temperature=temp_node->c.m.temp;
				newnode->day=temp_node->c.m.time.day;
				newnode->month=temp_node->c.m.time.month;
				*head=newnode;
			}
		}else{
			ret=strcmp(newnode->name,temp_node->c.city_name);
			if (ret==0)
			{
				if((temp_node->c.m.temp)>(newnode->temperature))
				{
					newnode->Id=temp_node->c.cityId;
					strcpy(newnode->name,temp_node->c.city_name);
					newnode->temperature=temp_node->c.m.temp;
					newnode->day=temp_node->c.m.time.day;
					newnode->month=temp_node->c.m.time.month;
				}
			}else{
				newnode=(struct cal*)malloc(sizeof(struct cal));
				if (newnode==NULL)
				{
					printf("\nno hay memoria suficiente"); 
					exit (1);
				}else{
					newnode->Id=temp_node->c.cityId;
					strcpy(newnode->name,temp_node->c.city_name);
					newnode->temperature=temp_node->c.m.temp;
					newnode->day=temp_node->c.m.time.day;
					newnode->month=temp_node->c.m.time.month;
					temp=*head;
					while(temp->next!=NULL)
					{
						temp=temp->next;
					}
					temp->next=newnode;
				}
			}
		}
		temp_node=temp_node->next;
	}
	
}
void printd_cal(struct cal*head)// imprimir dia mas calido de cada ciudad
{
	struct cal *temp=NULL; 
	temp=head;
	cout<<"\tID\tNOMBRE\tTEMPERATURA\tDIA\tMES"<<endl; 
	while(temp!=NULL)
	{
		cout<<"\t"<<temp->Id;
		cout<<"\t"<<temp->name;
		cout<<"\t"<<temp->temperature;
		cout<<"\t"<<temp->day;
		cout<<"\t"<<temp->month;
		cout<<endl; 
		temp=temp->next;
	}
}
