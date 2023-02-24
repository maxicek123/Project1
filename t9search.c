#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//funkcia ktora nam vracia "string" v ktorej si pomocou switchu zadefinujeme ciselnik podla zadania
char* GetNumber(char number)
{
    switch (number)
    {
        case '0':
            return "+";
        case '1': 
            return " ";
        case '2':
            return "abc\0";
        case '3':
            return "def\0";
        case '4':
            return "ghi\0";
        case '5':
            return "jkl\0";
        case '6':
            return "mno\0";
        case '7':
            return "pqrs";
        case '8':
            return "tuv\0";
        case '9':
            return "wxyz";
            
        default:
            break;
    }
}
// funkcia v ktorej prechazame a porovnavame cislo s pismenami
bool ProcessRecord(char buffer[], char* searchedNumber)
{
    for(int i = 0; i < 100; i++)
    {       
        if(searchedNumber[0] == buffer[i])
        {
            int j = 0;
            // prechadzame cez hladane cislo 
            for (j; j < strlen(searchedNumber);)
            {
                // ak sa cisla nebudu rovnat ukoncime cyklus
                if((int) searchedNumber[j] != (int) buffer[j+i])
                {
                    break;  
                }
                j++;
            }

            // ak sme presli celym cyklom tak vieme ze sme tam nasli postupnost
            if(j == strlen(searchedNumber))
            {
                return true;
            }
        }
            // prelozime si prve cislo zo searchedNumber na postupnost pismen, ktoru sme si vypisali vo funkcii GetNumber  pomocou switchu
            char* translatedNumber = GetNumber(searchedNumber[0]); 

            
            // snazime sa najist v buffri, ci najdeme zaciatok hladanej postupnosti
            if(translatedNumber[0] == buffer[i] || translatedNumber[1] == buffer[i] || translatedNumber[2] == buffer[i] || translatedNumber[3])
            {
                // prechadzame searchedNumber pri hladani prelozenych pismenok
                int k = 0;
                //  prechadzame jednotlive cislice v hladanom cisle 
                for(k; k < strlen(searchedNumber);)
                {
                    // pocitadlo dame na 0 ked je zhodne  
                    //  dalej aa pozerame  ci sedi aj dalsie cislo v searchedNubmer
                    int numberOfMatches = 0;
                    // prechadzame postupnostou znakov ktore zodpovedaju searchedNumber[i] a porovnamvame to  s buffrom
                    //  prejdeme cez switch a porovname s buffrom a ak najdeme pokracujeme na dalsi znak v searchedNumber
                    for (int l = 0; l < strlen(translatedNumber); l++)
                    {
                    // ak sa rovna nejaky znak  takl si to pripocitame k numberOfMatches            
                        if((int) translatedNumber[l] == (int) buffer[i+k])
                        {
                            numberOfMatches++;
                        }
                    }
                    // ak sme nasli aspon jedno pismeno ktore sedi tak pokracujeme dalej v prechadzani (a hladame ci su nejake dalsie) 
                    // ak sme nenasli ani jednu zhodu tak ukoncujeme cyklus
                    if(numberOfMatches < 1)
                        break;
                    k++;
                    // ak sme nasli zhodu  tak si cisla prekladame na pismena
                    translatedNumber = GetNumber(searchedNumber[k]);
                }
                // ked sa  postunost nenajde cela tak vyskocime von
                // ak  k == dlzke  hladaneho cisla tak is found nastavime na true
                 if(k == strlen(searchedNumber))
                {
                    return true;
                }
            }
    }
        
        return false;

}


//main funkcia , v ktorej vykonavame hlavnu funkcionalitu
int main(int argc, char *argv[])
{
    // overovanie argumentu
    if(argc < 1)
    {
        printf("ERROR: Wrong number of arguments. Expected: more than 1, Got: %d.", argc);
        return -1;
    }
    
    bool printAll = false;

    if(argc == 1)
    {
        printAll = true;
    }

    // premenne vuzite na pre porovnavanie
    char* searchedNumber = argv[1];
    char character;
    int bufferPosition = 0;
    char buffer[101];
    int lineNumber = 1;
    bool isFound = false;
    bool foundSomething = false;
    
    // vypiseme cely subor , stdin je vstup odkial citame
    while((character = (char) getc(stdin)) != EOF)
    { 
        // ked bude znak koniec riadka tak vynulujeme buffer a ulozime hodnotu 
        if(character == (int)'\r')
                continue;

        // ak je  znak koniec / novy riadok
        if (character == (int)'\n')
        {   
            // ak je riadok meno tak dame zan ciarku a medzeru
            if (lineNumber % 2 != 0)
            {
                buffer[bufferPosition++] = ',';
                buffer[bufferPosition++] = ' ';
            }
            
            //pokial sme na "druhom riadku"(t.j. cisle)
            if (lineNumber % 2 == 0) 
            {
                if(searchedNumber != NULL)
                {
                    isFound = ProcessRecord(buffer, searchedNumber);

                }
                //vypisanie vsetkych kontaktov pokial zadame prazdny argument
                if(isFound || printAll)
                {
                    printf("%s\n", buffer);
                    isFound = false;
                    foundSomething = true;

                }
                // dame buffer pozition na nulu ked prideme na dalsi riadok
                bufferPosition = 0;
            }
            // zistujeme na akom sme riadku a ci je to cislo ci meno (parne je cislo, neparne je meno)
            lineNumber++;
        }
        else
        {
            // zapisovanie do buffra
            buffer[bufferPosition++] = character;
        }
    }
    
    if (foundSomething == false)
    {
        printf("Not found.\n");
        return -1;
    }
}