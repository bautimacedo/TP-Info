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
	char city_name[50];
};

int main(int argc, char *argv[]) 
{
	struct city cordoba;
	struct timestamp time_cba;
	struct measurement weather_cba;
	
	FILE *fp;
	fp=fopen("./personaa.txt", "rb");
	if(fp==NULL)
	{
		printf("Imposible abrir el archivo");
		exit(1);
	}
	printf("CityId \t CityName \t Temperature \t Humidity\tHour \t Min\tDay \tMonth\n");
	while(feof(fp)==0)
	{
		fscanf(fp,"%d %s %f %f %d %d %d %d", &cordoba.cityId, &cordoba.city_name, &weather_cba.temp, &weather_cba.hum, &time_cba.hh, &time_cba.mm, &time_cba.day,  &time_cba.month);
		printf("  %d \t %s \t %f \t %f \t %d \t %d \t %d \t %d\n", cordoba.cityId, cordoba.city_name, weather_cba.temp, weather_cba.hum, time_cba.hh, time_cba.mm, time_cba.day,  time_cba.month);
	}
	
	fclose(fp);
	return 0;
}

