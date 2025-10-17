# Relógio/Timer em C e Assembly com Sinais (x86-64)

Este projeto demonstra a Intercomunicação de Processos (IPC) e o controle de tempo no Linux, combinando código Assembly x86-64 (NASM) e C. O objetivo é configurar um temporizador de tempo real que dispara o sinal SIGALRM a cada segundo.

O código C (sigaction.c) atua como o framework de sinais, configurando o tratador (sigaction) e o temporizador (setitimer), enquanto o código Assembly (start.asm) é usado para interagir diretamente com as system calls.

##  Tecnologias

* **Linguagens:** C e Assembly x86-64 (NASM)
* **Ferramentas:** GCC e Makefile
* **Conceitos:** Sinais (`SIGALRM`), Tratamento de Sinais (`sigaction`) e Temporizadores de Tempo Real (`setitimer`).

## Arquivos

* `sigaction.c`: Contém a função principal (`main`) para configurar o sinal e o timer, e a função *handler* (`tratador`) que executa o código do relógio a cada segundo.
* `start.asm`: Contém funções de baixo nível em Assembly que interagem diretamente com *system calls*.
* `Makefile`: Define as regras para compilar tanto o código C quanto o Assembly.

##  Compilação e Execução

Este projeto utiliza um `Makefile` para automatizar a compilação do Assembly e do C e a ligação do executável final, que é chamado de `program`.

**Requisitos:**
* NASM (Netwide Assembler)
* GCC (Compilador C)

### Comandos

1.  **Compilar (Cria o executável 'program'):**
    ```bash
    make all
    ```
2.  **Executar:**
    ```bash
    make run
    # ou diretamente:
    # ./program
    ```
3.  **Limpar Arquivos Gerados (`.o`, `.lst`, `program`):**
    ```bash
    make clean
    ```

##  Syscalls e Sinais

O projeto se baseia nas seguintes chamadas de sistema (syscalls) para a manipulação de sinais e temporizadores:

* `setitimer`
* `rt_sigaction` (usada pelo `sigaction` em C)

| Nome do Sinal | Ação Padrão | Comentário |
| :--- | :--- | :--- |
| `SIGALRM` (14) | Terminate | Relógio de temporizador real |
| `SIGINT` (2) | Terminate | Interrupção do teclado, Control-C |
| `SIGKILL` (9) | Terminate | Finalização forçada do processo |
