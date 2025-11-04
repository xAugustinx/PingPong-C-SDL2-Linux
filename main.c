#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


//Bolls

int test = 1;

int odbicieBool = 0;
int odbicieWrogaBool = 0;

int wykrywanieCzyDziala = 0;

int playMode = 0;

//ints and doubles
int paletkaStrona = 0;
int paletkaStronaWroga = 0;


double kierunek[2] = { 0, 1 };

int wybranyElementMenu = 0;

double predkosc = 1;

int iloscPowturzen[2] = {0,0};

int punktacja[2] = {0, 0};

int kierunekDocelowy = 0;

int iloscPowtorzenWroga[2] = {0,0};

double pilka[2] = { 50, 75 };

int paletkaGracza[4] = {50,140};

int paletkaWroga[2] = {50,10};



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
        for (int sx = -4; sx < 4; sx++) {
            for (int wx = -4; wx < 4; wx++)
            {
                for (int ax = -4; ax < 4; ax++) {

                    int w = wx;
                    int s = sx;
                    int a = ax;
                    
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

                    iloscPowtorzenWroga[0]++;

                    if (iloscPowtorzenWroga[0] > 4) {
                        iloscPowtorzenWroga[0] = 0;
                    }

                    paletkaWroga[0] = paletkaWroga[0] - iloscPowtorzenWroga[0];
                }
                else
                {
                    iloscPowtorzenWroga[1]++;
                    if (iloscPowtorzenWroga[1] > 4) {
                        iloscPowtorzenWroga[1] = 0;
                    }


                    paletkaWroga[0] = paletkaWroga[0] + iloscPowtorzenWroga[1];
                }
            }
            else {
                iloscPowtorzenWroga[0] = 0;
                iloscPowtorzenWroga[1] = 0;
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
            //kierunek[1] = kierunek[1] * -1;
            kierunek[0] = kierunek[0] * -1;
        }


        if (przechowanaWartoscDlaKierunkuWroga >= 2 || przechowanaWartoscDlaKierunkuWroga <= -2 ) {


            int superZmienna = 1;

            if (przechowanaWartoscDlaKierunkuWroga < 0) {
                superZmienna = superZmienna * -1;
            }
            predkosc = predkosc * (przechowanaWartoscDlaKierunkuWroga / 2) * superZmienna;
        }

        odbicieWrogaBool = 0;


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


    if (playMode) {
        if (paletkaStronaWroga == 1) {

            if (iloscPowtorzenWroga[0] < 5) {
                iloscPowtorzenWroga[0]++;
            }


            paletkaWroga[0] = paletkaWroga[0] - 1 * iloscPowtorzenWroga[0];

            if (paletkaWroga[0] < 8) {
                paletkaWroga[0] = 8;
            }

        }
        else if (paletkaStronaWroga == 2)
        {

            if (iloscPowtorzenWroga[1] < 5) {
                iloscPowtorzenWroga[1]++;
            }

            paletkaWroga[0] = paletkaWroga[0] + 1 * iloscPowtorzenWroga[1];

            if (paletkaWroga[0] > 91) {
                paletkaWroga[0] = 91;
            }

        }
        else
        {
            iloscPowtorzenWroga[0] = 0;
            iloscPowtorzenWroga[1] = 0;
        }

        paletkaStronaWroga = 0;
    }

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


    int czyGraOdpalona = 0;

    while (dzialaMeow) {


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        for (int i = 0; i < 150; i++) {
            for (int j = 0; j < 100; j++) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }


        if (!czyGraOdpalona) {

            //kropki

            SDL_SetRenderDrawColor(renderer, 59, 77, 255, 255);
            for (int i = 1; i < playMode + 2; i++)
            {
             SDL_RenderDrawPoint(renderer, i+75, 71  );
            }


        //Buttons

        for (int i = 0; i < 21; i = i + 20) {


            SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255);

            if (i / 20 == wybranyElementMenu) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255);
            }


            for (int j = 49; j < 100; j++) {
                SDL_RenderDrawPoint(renderer, j, 45 +i);
                SDL_RenderDrawPoint(renderer, j, 60+i);
            }
            for (int j = 45; j < 61; j++) {
                SDL_RenderDrawPoint(renderer, 49, j+i);
                SDL_RenderDrawPoint(renderer, 100, j+i);
            }
        }

            //Napisy


            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            int szerokosc = 57;
            int licznikFajny = 0;
            double licznikFajnyDwa = 0;
            double licznikFajnyTrzy = 0;

            for (int i = 48; i < 58; i++) {

                SDL_RenderDrawPoint(renderer, szerokosc, i);
                if (i < 54) {
                    SDL_RenderDrawPoint(renderer, szerokosc +5, i);

                    SDL_RenderDrawPoint(renderer, szerokosc +27+(int)licznikFajnyTrzy, i);
                    SDL_RenderDrawPoint(renderer, szerokosc +28+(int)licznikFajnyTrzy, i);
                    licznikFajnyTrzy = licznikFajnyTrzy + 0.50;
                }

                if (i == 53 || i == 48) {
                    for (int j = szerokosc ; j < szerokosc +5; j++)
                    {
                        SDL_RenderDrawPoint(renderer, j+1, i);
                    }
                }
                SDL_RenderDrawPoint(renderer, szerokosc +15, i);
                SDL_RenderDrawPoint(renderer, szerokosc +8, i);

                if (i == 57) {
                    for (int j = szerokosc + 9; j < szerokosc +13; j++) {
                        SDL_RenderDrawPoint(renderer, j, i);
                    }

                }

                SDL_RenderDrawPoint(renderer, szerokosc +15+licznikFajny, i);
                SDL_RenderDrawPoint(renderer, szerokosc +16+licznikFajny, i);
                licznikFajny = licznikFajny + 1;

                SDL_RenderDrawPoint(renderer, szerokosc +33+(int)licznikFajnyDwa, i);
                SDL_RenderDrawPoint(renderer, szerokosc +34+(int)licznikFajnyDwa, i);
                licznikFajnyDwa = licznikFajnyDwa - 0.50;


                if ( i == 53) {
                    for (int b = szerokosc + 15; b < szerokosc +22; b++) {
                        SDL_RenderDrawPoint(renderer, b , i);
                    }
                }


            }

        }
        else  {

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

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
                if (pilka[1] < 0 ) {
                    punktacja[1]++;
                    resetGry();
                }
                else if (pilka[1] > 149) {
                    punktacja[0]++;
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
            if (!playMode) {
                odbijaniePrzeciwnika();
            }

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

            //wyniki
            SDL_SetRenderDrawColor(renderer, 240, 146, 193, 255);

            for (int i = 0; i < punktacja[0]*2; i = i + 2) {
                SDL_RenderDrawPoint(renderer, i + 5, 5);
            }

            for (int i = 149; i > 149 - punktacja[1]*2; i = i - 2) {
                SDL_RenderDrawPoint(renderer, i - 5, 5);
            }


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
                    wybranyElementMenu--;
                    if (wybranyElementMenu < 0 && !czyGraOdpalona) {
                        wybranyElementMenu = 1;
                    }
                }
                else if (zdarzenie.key.keysym.sym == SDLK_s)
                {
                    paletkaStrona = 2;
                    wybranyElementMenu++;
                    if (wybranyElementMenu > 1 && !czyGraOdpalona) {
                        wybranyElementMenu = 0;
                    }
                }
                else if (zdarzenie.key.keysym.sym == SDLK_UP) {
                    paletkaStronaWroga = 1;
                }
                else if (zdarzenie.key.keysym.sym == SDLK_DOWN) {
                    paletkaStronaWroga = 2;
                }
                else if (zdarzenie.key.keysym.sym == SDLK_a) {
                    paletkaGracza[1]--;
                }
                else if (zdarzenie.key.keysym.sym == SDLK_d) {
                    paletkaGracza[1]++;
                }
                else if (zdarzenie.key.keysym.sym == SDLK_r) {
                    resetGry();
                }
                else if (zdarzenie.key.keysym.sym == SDLK_p) {
                    predkosc++;
                }
                else if (zdarzenie.key.keysym.sym == SDLK_SPACE) {
                    if (wybranyElementMenu == 0) {
                        resetGry();
                        czyGraOdpalona = 1;
                    }

                    else  {
                        if (playMode == 0) {
                            playMode = 1;
                            printf("dgdfg");
                        }
                        else if (playMode == 1) {
                            playMode = 0;
                            printf("dgdfggdfg");
                        }
                    }

                }

            }
        }

        for (int i = 0; i < 2; i++) {
            if (punktacja[i] > 4) {

                czyGraOdpalona = 0;

                wybranyElementMenu = 0;

                punktacja[0] = 0;
                punktacja[1] = 0;
                resetGry();
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