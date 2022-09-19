/*  
 *      TRABALHO 1 - SC
 *      SISTEMAS DE COMPUTAÇÃO 
 *      T1 - Restaurante U 
 *      NOME: Erick Lemmy dos Santos Oliveira
*/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <time.h>

void comendo();
constexpr int MAX_RAND = 2;
constexpr time_t MICRO_SEC = 0.7e6;   // 0.7 segundos de delay

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "ERRO: É NECESSARIO PASSAGEM DE __PARAMETRO__!!\n"
                  << "USO: " << argv[0] << " S\n"
                  << "S: string -> Nome do estudante que ira comer a porcao\n";
        return 1;
    }

    int id_porcoes_mc = shm_open("porcoes_mc", O_RDWR | O_CREAT, 0666);
    if (id_porcoes_mc == -1) 
    {
        std::cerr << "OCORREU ALGUM ERRO AO UTILIZAR __SHM_OPEN__!!\n";
        return 1;
    }

    int err = ftruncate(id_porcoes_mc, sizeof(int));
    if (err == -1)
    {
        std::cerr << "OCORREU ALGUM ERRO AO UTILIZAR __FTRUNCATE__!!\n";
        return 1;
    }

    int *pmc = (int *) mmap(nullptr, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, id_porcoes_mc, 0);
    if (pmc == MAP_FAILED)
    {
        std::cerr << "OCORREU ALGUM ERRO AO UTILIZAR __MMAP__!!\n";
        return 1;
    }

    sem_t *mutex = sem_open("mutex", O_CREAT | O_RDWR, 0666, 1);    // cria o semaphoro
    if (mutex == SEM_FAILED)
    {
        std::cerr << "OCORREU ALGUM ERRO AO UTILIZAR __SEM_OPEN__!!\n";
        return 1;
    }
    
    std::cout << "┬─ Estudante " << argv[1] << '\n';
    if (*pmc <= 0) *pmc = 0;

    bool key = true;
    while(key)
    {
        if (*pmc > 0) {
            sem_wait(mutex);
            --(*pmc); 
            std::cout << "├─┬─  " << "Se servindo de 1 porção (na prateleira: " << *pmc << ")\n"
                      << "│ └── " << "Esta comendo batata frita"; 
            sem_post(mutex);
            comendo();
        }

        key = (*pmc == -2) ? false : true;

        if (*pmc == 0) {
            sem_wait(mutex);
            std::cout << "├── Esta com Fome. Acordando Cozinheiro\n";
            *pmc = -1;
            sem_post(mutex);
        } 
        // std::cout << "├─ DEBUG: aguardando cozinheiro - porção: " << *pmc << '\n'; 
        // sleep(5);
    }
    
    std::cout << "├── Esta com Fome. Acordando Cozinheiro\n";
    std::cout << "├─ " <<"Morreu de fome \n"
              << "└─ " << argv[1] << " Terminou...\n";
    return 0;
}

void comendo()
{
    int r = rand() % MAX_RAND + 1;
    for (size_t i = 0; i <= r; ++i)
    {   
        usleep(MICRO_SEC);
        std::cout << "." << std::flush;
        usleep(MICRO_SEC);
        std::cout << "." << std::flush;
        usleep(MICRO_SEC);
        std::cout << "." << std::flush;
        usleep(MICRO_SEC);
        std::cout << "\b\b\b   \b\b\b" << std::flush;
    }
    std::cout << '\n';
}
