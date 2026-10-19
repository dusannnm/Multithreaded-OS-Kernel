//
// Created by os on 10/8/25.
//

#include "../h/Resource.hpp"
#include "../test/printing.hpp"

Resource::Resource(int N)
{
    this->instancesNum = N;
    this->freeInstances = N;
    this->busyInstances = 0;
    this->resourceSem = new Semaphore(0);
    this->waitingThreads = 0;
}

void Resource::take(int num_of_instances)
{
    if (num_of_instances > this->instancesNum)
    {
        printString("Nema dovoljno resursa!");
        return;
    }

    while (num_of_instances > this->freeInstances)
    {
        this->waitingThreads++;
        printString("Resource: Nit ceka na "); printInt(num_of_instances); printString(" resursa, trenutno nema dovoljno. \n");
        this->resourceSem->wait();
        printString("Resource: Nit se odblokirala i pokusava da uzme "); printInt(num_of_instances); printString(" resursa. \n");
    }

    printString("Resource: Nit uzima "); printInt(num_of_instances); printString(" resursa. \n");
    this->freeInstances-=num_of_instances;
    this->busyInstances+=num_of_instances;
    printString("Resource: Preostalo je "); printInt(this->freeInstances); printString(" resursa. \n");

}

int Resource::give_back(int num_of_instances)
{
    if (this->busyInstances < num_of_instances)
    {
        printString("Greska! Vraca se vise resursa nego sto je moguce. \n");
        return -1;
    }

    this->freeInstances+=num_of_instances;
    this->busyInstances-=num_of_instances;

    printString("Resource: Nit vraca "); printInt(num_of_instances); printString(" resursa i budi "); printInt(this->waitingThreads);
    printString(" nit/i.Sada ima dostupno "); printInt(this->freeInstances); printString(" resursa.\n");

    while (this->waitingThreads > 0)
    {
        this->waitingThreads--;
        this->resourceSem->signal();
    }
    return 0;
}




