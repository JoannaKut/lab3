// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos



#include <iostream>
#include <stdio.h>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);

void sortBySex(Slav*,int n);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	sortBySex(slavs,n);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	vectorOfSlavs.push_back(NULL);
	srand(time(NULL));
	for (int i=0; i<n; i++)
	{
		int position=rand()%vectorOfSlavs.size();
		vectorOfSlavs.insert(vectorOfSlavs.begin()+position,slavs+i);
	}
	vectorOfSlavs.pop_back();

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
	vector<Slav*>::iterator i_vec;
	for (i_vec=vectorOfSlavs.begin(); i_vec!=vectorOfSlavs.end(); i_vec++)
		 cout<<(*i_vec)->description()<<endl;


	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	for(int i=0; i<n; i++)
	{
		 setOfSlavs.insert(vectorOfSlavs[i]);
		 vectorOfSlavs.pop_back();
	}
	
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	map<Slav*,Slav*>::iterator i_map;
	set<Slav*>::iterator i_set=setOfSlavs.begin();
	set<Slav*>::iterator i_set_delete=setOfSlavs.begin();

	while(i_set!=setOfSlavs.end())
	{	
		 mapOfSlavs[*i_set++]=*i_set++;
		 setOfSlavs.erase(i_set_delete++);
		 setOfSlavs.erase(i_set_delete++);
	}
	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	for(i_map=mapOfSlavs.begin(); i_map!=mapOfSlavs.end(); i_map++)
		 cout<<(*i_map).first->description()<<" "<<(*i_map).second->description()<<endl;
	
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.

	for(int i=0; i<n; i++)
		 queueOfSlavs.push(slavs+i);
	
	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.

	for(int i=0;i<n;i++)
	{
		 stackOfSlavs.push(queueOfSlavs.front());
		 queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
	for(int i=0;i<n;i++)
	{
		 cout<<(*stackOfSlavs.top()).description()<<endl;;
		 stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

void sortBySex(Slav * slavs, int n)
{
	map <sex, vector<Slav *> > mapBySex;
	for(int i=0; i < n; i++)
	{
		if(slavs[i]._sex() == male)
			mapBySex[male].push_back(&slavs[i]);
		else
			mapBySex[female].push_back(&slavs[i]);
	}

	vector <Slav *>::iterator i_vec_slav;

	cout << endl <<"Mężczyźni: " << endl;	
	for(i_vec_slav = mapBySex[male].begin(); i_vec_slav != mapBySex[male].end(); ++i_vec_slav)	
		cout << (*i_vec_slav)->description() << endl;

	cout << endl << "Kobiety: " << endl;	
	for(i_vec_slav = mapBySex[female].begin(); i_vec_slav != mapBySex[female].end(); ++i_vec_slav)	
		cout << (*i_vec_slav)->description() << endl;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}