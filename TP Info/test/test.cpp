#include <iostream>
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

int main(int argc, char *argv[]) 
{
	struct city *head_cba=NULL;//Lista enlazada para cordoba
	struct city *head_stafe=NULL;//Lista enlazada para santa fe
	struct city *head_mndza=NULL;//Lista enlazada para mendoza
	struct city *temp=NULL;
	struct city *newnode=NULL;
	int ctr_cba=0;
	int ctr_mndza=0;
	int ctr_stafe=0;
	float sum_cba=0,sum_stafe=0,sum_mndza=0;
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
				ctr_mndza++;
				sum_mndza+=newnode->m.temp;
			}
		}
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
	printf("\n\n\n\nTemp Prom Cba: %f - Temp Prom Stafe: %f - Temp Prom Mndza: %f", (sum_cba/ctr_cba),(sum_stafe/ctr_stafe),(sum_mndza/ctr_mndza));
	return 0;
}


