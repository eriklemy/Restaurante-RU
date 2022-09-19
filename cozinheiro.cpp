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
#include <time.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

void cozinhando(int num_prat);
constexpr int MAX_PRAT = 3;
constexpr int MAX_RAND = 2;
constexpr time_t MICRO_SEC = 0.5e6;     // 0.5 segundos

int main(int argc, char *argv[])
{
    srand(time(NULL));
    if (argc < 2)
    {
        std::cerr << "ERRO: É NECESSARIO PASSAGEM DE __PARAMETRO__!!\n"
                  << "USO: " << argv[0] << " N\n"
                  << "N: int -> Numero de porções a ser feita pelo cozinheiro\n";
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

    sem_t *mutex = sem_open("mutex", O_CREAT | O_RDWR, 0666, 1);    // cria o semaforo
    if (mutex == SEM_FAILED)
    {
        std::cerr << "OCORREU ALGUM ERRO AO UTILIZAR __SEM_OPEN__!!\n";
        return 1;
    }
    
    if (*pmc != 0) *pmc = -1;
    int max_porcoes = atoi(argv[1]);

    std::cout << "┬─ Cozinheiro \n"
              << "├─┬─ Cozinheiro Dormindo\n";
   
    int num_prat = 1;
    while (true)
    {
        if (*pmc == -1 && num_prat <= MAX_PRAT) {
            std::cout << "│ ├─ Cozinheiro Acordou\n";
            std::cout << "│ └──── Cozinheiro cozinhando " << max_porcoes << " porções";
            cozinhando(num_prat);
     
            sem_wait(mutex);
            *pmc = max_porcoes;               // incrementa o valor na memoria apontada 
            sem_post(mutex);

            if (num_prat < 3) 
                std::cout << "├─┬─ Cozinheiro Dormindo\n";
            num_prat++;
        }
        if (num_prat > MAX_PRAT && *pmc <= 0) break;
    }
     
    std::cout << "├─ Cozinheiro Dormindo\n"
              << "└─ Cozinheiro Desistiu...\n";
    
    *pmc = -2;
    shm_unlink("porcoes_mc");               // destroi a memoria
    sem_unlink("mutex");                    // destroi o mutex
    return 0;
}

void cozinhando(int num_prat)
{
    int r = rand() % MAX_RAND + 1;
    for (size_t i = 0; i < r; ++i)
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
    std::cout << " OK!! (" << num_prat << "x)\n";
    std::cout << "├─ Liberando estudantes\n";
}
