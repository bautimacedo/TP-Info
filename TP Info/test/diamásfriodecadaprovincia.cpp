float frio=0; 
int dia=0;
int mes=0;
char name[50];
int id; 
counter=0; 
//eso es una estructura 
while(temp_2->next!=NULL)
{
	if (counter==0)
	{
		frio=(temp->m.temp);
		strcpy(name,temp->city_name); 
		id=temp->cityId; 
		dia=temp->m.time.day; 
		mes=temp->m.time.month; 
		
	}else{
		if (((temp->m.temp)/(temp_2->ctr))<frio))
		{
			frio=(temp->m.temp);
			strcpy(name,temp->city_name); 
			id=temp->cityId; 
			dia=temp->m.time.day; 
			mes=temp->m.time.month; 
		}
	}
	temp_2=temp_2->next;
}
