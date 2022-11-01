float calida=0; 
char name[50];
int id; 
counter=0; 
//eso es una estructura 
while(temp_2->next!=NULL)
{
	if (counter==0)
	{
		calida=(temp_2->temperatura)/(temp_2->ctr);
		strcpy(name,temp_2->name); 
		id=temp_2->id; 
		
	}else{
		if (((temp_2->temperatura)/(temp_2->ctr))>calida)
		{
			calida=(temp_2->temperatura)/(temp_2->ctr);
			strcpy(name,temp_2->name); 
			id=temp_2->id; 
		}
	}
	temp_2=temp_2->next;
}
