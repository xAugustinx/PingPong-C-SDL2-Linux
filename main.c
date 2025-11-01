#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>



int paletkaStrona = 0;

double kierunek[2] = { 0, 1 };

int wykrywanieCzyDziala = 0;




double predkosc = 1;

int iloscPowturzen[2] = {0,0};

int kierunekDocelowy = 0;



double pilka[2] = { 50, 75 };

int paletkaGracza[2] = {50,140};

int paletkaWroga[2] = {50,10};


int test = 1;

int odbicieBool = 0;
int odbicieWrogaBool = 0;


double przechowanaWartoscDlaKierunku = 0;
double przechowanaWartoscDlaKierunkuWroga = 0;



int resetGry() {
    paletkaGracza[0] = 50;
    paletkaGracza[1] = 140;

    paletkaWroga[0] = 50;
    paletkaWroga[1] = 10;

    pilka[0] = 50;
    pilka[1] = 75;

    paletkaStrona = 0;

    kierunek[0] = 0;
    kierunek[1] = 1;

    predkosc = 1;


    printf("donna mama \n");

}

int odbijaniePilki() {
    for (int i = -8; i < 9; i++) {
        for (int s = -4; s < 4; s++) {
            for (int w = -4; w < 4; w++)
            {
                for (int a = -4; a < 4; a++) {

                    if (s == -4) {
                        s = 0;
                    }
                    if (w == -4) {
                        w = 0;
                    }
                    if (a == -4) {
                        a = 0;
                    }

                    if (paletkaGracza[0]+i == (int)pilka[0]+w && paletkaGracza[1]+s <= (int)pilka[1]+a ) {

                        pilka[1] = paletkaGracza[1]-10;
                        odbicieBool = 1;

                        if (i == 0) {
                            i = 1;
                        }

                        if (i < 0 && s > 0 || i > 0 && s < 0) {
                            s = s * -1;
                        }

                        przechowanaWartoscDlaKierunku = (i + s) / 2;


                        if (przechowanaWartoscDlaKierunku < 1 && 0 < przechowanaWartoscDlaKierunku) {
                            przechowanaWartoscDlaKierunku = 1;
                        }

                        if (i == 0) {
                            przechowanaWartoscDlaKierunku = 1;
                        }
                    }

                }
            }
        }
    }


    for (int i = -8; i < 9; i++) {
        for (int s = -4; s < 4; s++) {
            for (int w = -4; w < 4; w++)
            {
                for (int a = -4; a < 4; a++) {

                    if (s == -4) {
                        s = 0;
                    }
                    if (w == -4) {
                        w = 0;
                    }
                    if (a == -4) {
                        a = 0;
                    }


                    if (paletkaWroga[0]+i == (int)pilka[0]+w && paletkaWroga[1]+s >= (int)pilka[1]+a ) {
                        pilka[1] = paletkaWroga[1]+10;
                        odbicieWrogaBool = 1;

                        if (i == 0) {
                            i = 1;
                        }

                        if (i < 0 && s > 0 || i >0 && s < 0) {
                            s = s * -1;
                        }

                        przechowanaWartoscDlaKierunkuWroga = (i + s) / 2;


                        printf("nyga\n");

                        if (i == 0) {
                            przechowanaWartoscDlaKierunkuWroga = 1;
                        }

                        printf("nyga \n");


                        if (przechowanaWartoscDlaKierunkuWroga == 0) {
                            przechowanaWartoscDlaKierunkuWroga = 1;
                        }

                    }


                }
            }
        }
    }

}



int odbijaniePrzeciwnika() {
      int wysokosc = paletkaWroga[0];
        int wysokoscPilki = pilka[0];

    int szybkiBool = 1;

        if (kierunek[1] < 0) {

            for (int i = -4; i < 5; i++) {
                if (wysokoscPilki +i == wysokosc) {
                    szybkiBool = 0;
                }
            }

            if (szybkiBool) {
                if (wysokosc > wysokoscPilki) {
                    paletkaWroga[0] = paletkaWroga[0] - 5;
                }
                else
                {
                    paletkaWroga[0] = paletkaWroga[0] + 5;
                }
            }
        }

}

int odbijanieIPchanie() {


    int czyZmienicKierunek = 0;
    int zblizacjaceSieOdbicie = 0;
    int trueMeow = 1;


    pilka[0] = pilka[0] + kierunek[0] *predkosc;
    pilka[1] = pilka[1] + kierunek[1] *predkosc;


    if (pilka[0]+3+kierunek[0]*predkosc > 99) {
        pilka[0] = 96;

        kierunek[0] = kierunek[0]*-1;

    }
    if (pilka[0]-3+kierunek[0]*predkosc < 0) {
        pilka[0] = 3;
        kierunek[0] = kierunek[0]*-1;

    }

    int szypkiBool = 1;

    int boolFajnyMeow = 0;


    if (odbicieBool) {

        int dodatek = -1;

        if (przechowanaWartoscDlaKierunku > 0) {
            dodatek = 1;
        }


        przechowanaWartoscDlaKierunku = przechowanaWartoscDlaKierunku / 2;

        kierunek[0] = ((1 - 1 / przechowanaWartoscDlaKierunku ) * dodatek); /// 1.5;
        kierunek[1] = ((1 / przechowanaWartoscDlaKierunku  ) * dodatek * -1); /// 1.5;  //

        if (przechowanaWartoscDlaKierunku <= 1 && przechowanaWartoscDlaKierunku >= 0) {
            kierunek[1] = -1;
            kierunek[0] = 0;
        }

        if (przechowanaWartoscDlaKierunku >= 2 || przechowanaWartoscDlaKierunku <= -2 ) {


            int superZmienna = 1;

            if (przechowanaWartoscDlaKierunku < 0) {
                superZmienna = superZmienna * -1;
            }
            predkosc = predkosc * (przechowanaWartoscDlaKierunku / 2) * superZmienna;
        }

        odbicieBool = 0;
    }

    if (odbicieWrogaBool) {

        int dodatek = -1;

        if (przechowanaWartoscDlaKierunkuWroga > 0) {
            dodatek = 1;
        }


        przechowanaWartoscDlaKierunkuWroga = przechowanaWartoscDlaKierunkuWroga / 2;

        kierunek[0] = ((1 - 1 / przechowanaWartoscDlaKierunkuWroga ) * dodatek); /// 1.5;
        kierunek[1] = ((1 / przechowanaWartoscDlaKierunkuWroga  ) * dodatek * -1); /// 1.5;  //

        if (przechowanaWartoscDlaKierunkuWroga <= 1 && przechowanaWartoscDlaKierunkuWroga >= 0) {
            kierunek[1] = -1;
            kierunek[0] = 0;
        }

        if (przechowanaWartoscDlaKierunkuWroga >= 2 || przechowanaWartoscDlaKierunkuWroga <= -2 ) {


            int superZmienna = 1;

            if (przechowanaWartoscDlaKierunkuWroga < 0) {
                superZmienna = superZmienna * -1;
            }
            predkosc = predkosc * (przechowanaWartoscDlaKierunkuWroga / 2) * superZmienna;
        }

        odbicieWrogaBool = 0;

        kierunek[0] = kierunek[0];
        kierunek[1] = kierunek[1] * -1;

    }



    predkosc = predkosc - (predkosc/1000) /2;



}

int paletkiMeow() {

    if (paletkaStrona == 1) {

        if (iloscPowturzen[0] < 5) {
            iloscPowturzen[0]++;
        }


        paletkaGracza[0] = paletkaGracza[0] - 1 * iloscPowturzen[0];

        if (paletkaGracza[0] < 8) {
            paletkaGracza[0] = 8;
        }

    }
    else if (paletkaStrona == 2)
    {

        if (iloscPowturzen[1] < 5) {
            iloscPowturzen[1]++;
        }

        paletkaGracza[0] = paletkaGracza[0] + 1 * iloscPowturzen[1];

        if (paletkaGracza[0] > 91) {
            paletkaGracza[0] = 91;
        }

    }
    else
    {
        iloscPowturzen[0] = 0;
        iloscPowturzen[1] = 0;
    }

    paletkaStrona = 0;

}


int main() {

    srand(time(NULL));

    SDL_Window* okno = SDL_CreateWindow(
        "Ping Pung",
        150,
        100,
        1250,
        800,
        SDL_WINDOW_SHOWN
    );



    SDL_Renderer* renderer = SDL_CreateRenderer(okno, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderSetLogicalSize(renderer, 150, 100);

    int dzialaMeow = 1;
    SDL_Event zdarzenie;



    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    while (dzialaMeow) {

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


        //Ustawienia Wszystkiego na Czarno
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            for (int i = 0; i < 150; i++) {
                for (int j = 0; j < 100; j++) {
                    SDL_RenderDrawPoint(renderer, i, j);
                }
            }


        //obramowki
        SDL_SetRenderDrawColor(renderer, 90, 90, 0, 255);
        for (int i = 0; i < 150; i++) {
            SDL_RenderDrawPoint(renderer, i, 0);
            SDL_RenderDrawPoint(renderer, i, 99);
        }
        for (int i = 0; i < 100; i++) {
            SDL_RenderDrawPoint(renderer, 0, i);
            SDL_RenderDrawPoint(renderer, 149, i);
        }


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);



        int rysunekLini = 0;
        int licznik = 0;
        while (1) {

            SDL_RenderDrawPoint(renderer, 75, rysunekLini);

            if (licznik == 3) {
                licznik = 0;
                rysunekLini = rysunekLini + 3;
            }
            else {
                rysunekLini++;
                licznik++;
            }

            if (rysunekLini > 99) {break;}
        }


        //pilka

        odbijaniePilki();


        odbijanieIPchanie();


        if (!(odbicieBool && odbicieWrogaBool))
        {
            if (pilka[1] < 0 || pilka[1] > 149) {
                resetGry();
            }
        }

        for (int i = -3; i < 4; i++) {
            for (int j = -3; j < 4; j++) {
                if (pilka[1] < 149 && pilka[1] > -1 && pilka[0] > -1 && pilka[0] < 99) {
                    SDL_RenderDrawPoint(renderer, pilka[1] + i, pilka[0]+j);
                }
            }
        }


        //paletki

        paletkiMeow();


            for (int i = -8; i < 9; i++) {
                SDL_RenderDrawPoint(renderer, paletkaGracza[1]+1, paletkaGracza[0]+i);
                SDL_RenderDrawPoint(renderer, paletkaGracza[1], paletkaGracza[0]+i);

                SDL_RenderDrawPoint(renderer, paletkaWroga[1]-1, paletkaWroga[0]+i);
                SDL_RenderDrawPoint(renderer, paletkaWroga[1], paletkaWroga[0]+i);
            }


        //odbijaniePrzeciwnika
        odbijaniePrzeciwnika();



        //nyga
        //for (int i = 0; i < 10; i++) {
        odbijaniePilki();



        //testowy migający piksel

        if (test) {

            if (wykrywanieCzyDziala) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            }


            SDL_RenderDrawPoint(renderer, 1, 1);

            test = 0;
        }
        else {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);




            SDL_RenderDrawPoint(renderer, 1, 1);

            test = 1;
        }


        if (predkosc < 0.05) {
            resetGry();
            printf("fsfs Meow meow \n");
        }



        //obsługa błędów
        while (SDL_PollEvent(&zdarzenie)) {

            if (zdarzenie.type == SDL_QUIT) {
                dzialaMeow = 0;
            }
            else if ( zdarzenie.type == SDL_KEYDOWN)
            {
                if (zdarzenie.key.keysym.sym == SDLK_w) {
                    paletkaStrona = 1;
                }
                else if (zdarzenie.key.keysym.sym == SDLK_s)
                {
                    paletkaStrona = 2;
                }
                else if (zdarzenie.key.keysym.sym == SDLK_r) {
                    resetGry();
                }
                else if (zdarzenie.key.keysym.sym == SDLK_p) {
                    predkosc++;
                }

            }
        }
        SDL_Delay(33);
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(okno);
    SDL_Quit();

    return 0;
}