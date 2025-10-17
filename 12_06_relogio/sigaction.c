/*
 * Relogio/Timer com Sinais (SIGALRM) em C e Assembly
 * Copyright (C) 2025 Ana Alicy Ribeiro
 *
 * Este programa é software livre: você pode redistribuí-lo e/ou modificá-lo
 * sob os termos da Licença Pública Geral GNU conforme publicada pela Free
 * Software Foundation, na versão 3 da Licença ou (a seu critério)
 * qualquer versão posterior.
 *
 * Você deve ter recebido uma cópia da Licença Pública Geral GNU
 * junto com este programa. Se não, consulte <https://www.gnu.org/licenses/>.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

// A função que trata o sinal
void tratador(int sinal) {
    time_t agora;
    struct tm *infoTempo;
    char buffer[128]; // Buffer para a string formatada

    // Obtém o tempo atual
    time(&agora);

    // Converte para o tempo UTC
    infoTempo = gmtime(&agora);

    // Formata a string com a hora e um indicativo de UTC
    strftime(buffer, sizeof(buffer), "%H:%M:%S (UTC)", infoTempo);

    // Imprime a hora formatada
    printf("Hora: %s\n", buffer);
}

int main() {
    struct sigaction sa;
    struct itimerval timer;

    // Configura o handler do sinal
    sa.sa_handler = tratador;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // Reinicia chamadas de sistema interrompidas pelo sinal

    // Associa o handler ao sinal SIGALRM
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("Erro ao configurar sigaction");
        exit(1);
    }

    // Configura o temporizador para disparar a cada 1 segundo
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;

    // Inicia o temporizador
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("Erro ao configurar setitimer");
        exit(1);
    }

    // Loop infinito para manter o programa em execução
    while (1) {
        pause();  // Espera por um sinal
    }

    return 0;
}
