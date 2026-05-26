#include <raylib.h>

// Lógica para verificar se alguém alinhou 3 símbolos
int VerificarVencedor(int tab[3][3]) {
    //Verifica Linhas
    for (int i = 0; i < 3; i++) {
        if (tab[i][0] != 0 && tab[i][0] == tab[i][1] && tab[i][0] == tab[i][2]) {
            return tab[i][0]; // Retorna 1 (X) ou 2 (O)
        }
    }

    //Verifica colunas
    for (int j = 0; j < 3; j++) {
        if (tab[0][j] != 0 && tab[0][j] == tab[1][j] && tab[0][j] == tab[2][j]) {
            return tab[0][j];
        }
    }

    // 3. Verifica diagonal principal
    if (tab[0][0] != 0 && tab[0][0] == tab[1][1] && tab[0][0] == tab[2][2]) {
        return tab[0][0];
    }

    //Verifica diagonal secundária
    if (tab[0][2] != 0 && tab[0][2] == tab[1][1] && tab[0][2] == tab[2][0]) {
        return tab[0][2];
    }

    return 0; // Ninguém ganhou ainda
}

int main(void) {
    int width = 800;
    int height = 600;

    InitWindow(width, height, "Jogo da Velha"); 
    SetTargetFPS(60);

    // matriz que define as colisoes
    Rectangle casas[3][3] = {
        {{250, 150, 100, 100}, {350, 150, 100, 100}, {450, 150, 100, 100}},
        {{250, 250, 100, 100}, {350, 250, 100, 100}, {450, 250, 100, 100}}, 
        {{250, 350, 100, 100}, {350, 350, 100, 100}, {450, 350, 100, 100}}  
    };

    // 0 = vazio, 1 = X, 2 = O
    int tabuleiro[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    bool turnoDoX = true;
    int vencedor = 0;        
    bool jogoAcabou = false; 
        
    while (!WindowShouldClose())
    {
        Vector2 posicaoMouse = GetMousePosition();

        // Só permite clicar se o jogo NÃO tiver acabado
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !jogoAcabou)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    // Se o mouse clicou dentro da caixinha E ela está vazia (0)
                    if (CheckCollisionPointRec(posicaoMouse, casas[i][j]) && tabuleiro[i][j] == 0)
                    {
                        if (turnoDoX) {
                            tabuleiro[i][j] = 1; // Coloca X
                        } else {
                            tabuleiro[i][j] = 2; // Coloca O
                        }
                        
                        // Após a jogada, verifica se temos um vencedor
                        vencedor = VerificarVencedor(tabuleiro);
                        if (vencedor != 0) {
                            jogoAcabou = true;
                        }
                        
                        turnoDoX = !turnoDoX; // Inverte o turno
                    }
                }
            }
        }

        // Se o jogo acabou, permite reiniciar ao apertar a tecla R
        if (jogoAcabou && IsKeyPressed(KEY_R)) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    tabuleiro[i][j] = 0; // Limpa o tabuleiro
                }
            }
            vencedor = 0;
            jogoAcabou = false;
            turnoDoX = true; // X começa de novo
        }

        
        // Aqui é a render do jogo
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(10, 10);
        
        // Na vertical
        DrawLine(350, 150, 350, 450, BLACK); 
        DrawLine(450, 150, 450, 450, BLACK); 
        // Na horizontal
        DrawLine(250, 250, 550, 250, BLACK); 
        DrawLine(250, 350, 550, 350, BLACK); 

        // Desenha os simbolos
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (tabuleiro[i][j] == 1) // Se for 1, desenha o X
                {
                    DrawText("X", casas[i][j].x + 30, casas[i][j].y + 15, 70, RED);
                }
                else if (tabuleiro[i][j] == 2) // Se for 2, desenha o O
                {
                    DrawCircleLines(casas[i][j].x + 50, casas[i][j].y + 50, 35, BLUE);
                }
            }
        }

        // infos do jogo no topo da tela
        if (!jogoAcabou) {
            if (turnoDoX) {
                DrawText("Turno: X", 340, 80, 30, RED);
            } else {
                DrawText("Turno: O", 340, 80, 30, BLUE);
            }
        } else {
            if (vencedor == 1) {
                DrawText("X GANHOU!", 310, 70, 36, RED);
            } else if (vencedor == 2) {
                DrawText("O GANHOU!", 310, 70, 36, BLUE);
            }
            
            // o printf para reiniciar o jogo
            DrawText("Pressione 'R' para reiniciar", 220, 500, 24, DARKGRAY);
        }

        EndDrawing(); 
    }
    
    CloseWindow(); 
    return 0;
}