struct city* general_head=NULL; //esto meterlo con la inicializada de todas las variables
//este general head tiene que estar arriba del todo de la lista, es decir tiene que ser como el "headcba" porque este head es el primero de todos porque es la primera provincia 



//METER ESTO EN EL WHILE ENORME PERO AFUERA DE LOS IF(PROVINCEID==1) Y TODOS ESOS
struct city* prev=NULL;//NUEVO 
struct city* current=NULL;//NUEVO
prev=general_head;
current=general_head->next;
if((general_head->cityId<0) ||(general_head->cityId>99))
{
	temp=general_head;
	general_head=general_head->next;
	freee(temp);
}
while((current!NULL)&&(current->cityId>=0)&&(current->cityId<=99))
{
	prev=current;
	current=current->next;
}
if(current!=NULL)
{
	temp=current;
	prev->next=current->next;
	free(temp);
}
//BORRAR POR PROVINCE ID
prev=general_head;
current=general_head->next;
if((general_head->prvinceId<0) ||(general_head->provinceId>3))
{
	temp=general_head;
	general_head=general_head->next;
	freee(temp);
}
while((current!NULL)&&(current->provinceId>=0)&&(current->provinceId<=3))
{
	prev=current;
	current=current->next;
}
if(current!=NULL)
{
	temp=current;
	prev->next=current->next;
	free(temp);
}
