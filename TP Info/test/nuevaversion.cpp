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
		dif_stafe=23-prom_stafe; 
		dif_mndza=23-prom_mndza; 
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
struct calidofrio{
	int id;
	char name[50];
	float temperature; 
};
void push (struct node**,struct city,float*);
void print (struct node*,struct node*,struct node*);
void temp_prom (struct city_prom**,struct node*);
void printprom(struct city_prom*,struct city_prom*,struct city_prom*);
void calido_frio(struct city_prom *, int);


int main(int argc, char *argv[]) 
{
	struct city c;
	struct node *head_cba=NULL;//Lista enlazada para cordoba
	struct node *head_stafe=NULL;//Lista enlazada para santa fe
	struct node *head_mndza=NULL;//Lista enlazada para mendoza
	
	struct city_prom *head_ctyprm_cba=NULL; 
	struct city_prom *head_ctyprm_stafe=NULL; 
	struct city_prom *head_ctyprm_mndza=NULL; 
	
	int ctr_cba=0,ctr_mndza=0,ctr_stafe=0;
	float temp_cba=0,temp_mndza=0,temp_stafe=0;
	int opt;
	char cont;
	int option=0; 
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
		case 1:
			printf("\n\n\n\nContador Cba: %d - Contador Stafe: %d - Contador Mndza: %d", ctr_cba,ctr_stafe,ctr_mndza);
			break; 
		case 2:
			cout<<"\nPromedio Cordoba "; 
			cout<<p.getprom_cba()<<endl;
			cout<<"\nPromedio Santa Fe "; 
			cout<<p.getprom_stafe()<<endl;
			cout<<"\nPromedio Santa Mendoza "; 
			cout<<p.getprom_mndza()<<endl;
			break; 
		case 3:
			printf("\n***TEMPERATURAS PROMEDIO***\n");
			printprom(head_ctyprm_cba,head_ctyprm_mndza,head_ctyprm_stafe);
			break; 
		case 4://ciudad más calida de cada provincia
			option=0;
			cout<<"\nCiudades con temperaturas más calidas"<<endl; 
			cout<<"\nCiudad más calida de Cordoba"<<endl;
			calido_frio(head_ctyprm_cba,option);
			cout<<"\nCiudad más calida de Mendoza"<<endl;
			calido_frio(head_ctyprm_mndza,option);
			cout<<"\nCiudad más calida de Santa fe"<<endl;
			calido_frio(head_ctyprm_stafe,option);
			break; 
		case 5://ciudad mas fria de cada provincia
			option=1;
			cout<<"\nCiudades con temperaturas más frias"<<endl; 
			cout<<"\nCiudad más fria de Cordoba"<<endl;
			calido_frio(head_ctyprm_cba,option);
			cout<<"\nCiudad más fria de Mendoza"<<endl;
			calido_frio(head_ctyprm_mndza,option);
			cout<<"\nCiudad más fria de Santa fe"<<endl;
			calido_frio(head_ctyprm_stafe,option);
			break; 
		case 6://dia más frio de cada provincia
			break; 
		case 7://dia más calido de cada ciudad
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
	
	cout<<"\ndesea imprimir??[s/n]"<<endl;
	cin>>cont; 
	if ((cont=='s')||(cont=='S'))
	{
		print(head_cba,head_stafe,head_mndza);
	}
	return 0;
}
void push (struct node** head, struct city c, float *temperature)
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
void print (struct node *head_cba,struct node *head_stafe,struct node *head_mndza)
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
void temp_prom(struct city_prom **head, struct node *node)
{
	struct city_prom *newnode=NULL; 
	struct city_prom *temp=NULL;
	struct node *temp_node=NULL;
	int ret;
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
			strcpy(newnode->name,temp_node->c.city_name);
			newnode->id=temp_node->c.cityId;
			newnode->temperature+=temp_node->c.m.temp;
			newnode->ctr++;
			*head=newnode;
			temp_node=temp_node->next;
			counter++;
			}
		}else{
			ret=strcmp(newnode->name,temp_node->c.city_name);
			if (ret==0)
			{
				newnode->temperature+=temp_node->c.m.temp;
				newnode->ctr++;
				temp_node=temp_node->next;
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
					temp_node=temp_node->next;
				}
			}
		}
	}	
}
void printprom(struct city_prom *head_ctyprm_cba, struct city_prom *head_ctyprm_mndza, struct city_prom *head_ctyprm_stafe)
{
	struct city_prom *temp=NULL;
	printf("\n***Ciudades de cordoba***\n\nCityId \t CityName \t Temperature");
	temp=head_ctyprm_cba;
	while(temp!=NULL)
	{
		printf(" \n%d \t %s \t %f \n", temp->id, temp->name, (temp->temperature)/temp->ctr);
		temp=temp->next;
	}
	printf("\n***Ciudades de santa fe***\n\nCityId \t CityName \t Temperature");
	temp=head_ctyprm_stafe;
	while(temp!=NULL)
	{
		printf(" \n%d \t %s \t %f \n", temp->id, temp->name, (temp->temperature)/temp->ctr);
		temp=temp->next;
	}
	printf("\n***Ciudades de mendoza***\n\nCityId \t CityName \t Temperature");
	temp=head_ctyprm_mndza;
	while(temp!=NULL)
	{
		printf(" \n%d \t %s \t %f \n", temp->id, temp->name, (temp->temperature)/temp->ctr);
		temp=temp->next;
	}
}
void calido_frio(struct city_prom *head, int option)
{
	struct calidofrio q;
	struct city_prom *temp=NULL; 
	int ctr=0;
	temp=head; 
	if (option == 1)//para más frio; 
	{
		while(temp!=NULL)
		{
			if (ctr==0)
			{
				q.id=temp->id; 
				strcpy(q.name,temp->name);
				q.temperature=temp->temperature/temp->ctr; 
				temp=temp->next;
				ctr++;
			}else{
				if((temp->temperature)<(q.temperature))
				{
					q.id=temp->id; 
					strcpy(q.name,temp->name);
					q.temperature=temp->temperature/temp->ctr; 
					temp=temp->next;
				}
			}
		}
		cout<<"Id ciudad "<<q.id<<endl; 
		cout<<"Nombre ciudad "<<q.name<<endl; 
		cout<<"Temperatura ciudad "<<q.temperature<<endl; 
	}
	if (option == 0)//para más calido; 
	{
		while(temp!=NULL)
		{
			if (ctr==0)
			{
				q.id=temp->id; 
				strcpy(q.name,temp->name);
				q.temperature=temp->temperature/temp->ctr; 
				temp=temp->next;
				ctr++;
			}else{
				if((temp->temperature)>(q.temperature))//temperatura mas alta
				{
					q.id=temp->id; 
					strcpy(q.name,temp->name);
					q.temperature=temp->temperature/temp->ctr; 
					temp=temp->next;
				}
			}
		}
		cout<<"Id ciudad, "<<q.id<<endl; 
		cout<<"Nombre ciudad "<<q.name<<endl; 
		cout<<"Temperatura ciudad "<<q.temperature<<endl; 
	}
	
}
