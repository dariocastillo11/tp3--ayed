#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <cmath>
#include <limits.h>
#include <queue>
#include <windows.h>
using namespace std;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Posicion {
    int x;
    int y;
    Posicion(int x_, int y_) : x(x_), y(y_) {}
};
struct Node {
    int vertex;
    vector<bool> visited;
    int path_length;
    vector<int> path;

    Node(int n) : visited(n, false), path_length(0) {}
};

const int cantidad_parches = 10;
const int cantidad_barreras= 20;
const int ancho= 100;
const int alto= 100;
const string fileName = "input.txt";


bool detectarBarrera(Posicion p0,Posicion p1,char matriz[alto][ancho]) {
    int dx = p1.x-p0.x, dy = p1.y-p0.y;
    int nx = abs(dx), ny = abs(dy);
    int sign_x = dx > 0? 1 : -1, sign_y = dy > 0? 1 : -1;

    Posicion p(p0.x, p0.y);
    for (int ix = 0, iy = 0; ix < nx || iy < ny;) {
        int decision = (1 + 2*ix) * ny - (1 + 2*iy) * nx;
        if (decision == 0) {
            // paso diagonal
            p.x += sign_x;
            p.y += sign_y;
            ix++;
            iy++;
        } else if (decision < 0) {
            // paso horizontal
            p.x += sign_x;
            ix++;
        } else {
            // paso vertical
            p.y += sign_y;
            iy++;
        }
        if(matriz[p.y][p.x]=='x'){return false;}
    }
    return true;
}

void pintarRecorrido(Posicion p0,Posicion p1,char matriz[alto][ancho],char celda) {
    int dx = p1.x-p0.x, dy = p1.y-p0.y;
    int nx = abs(dx), ny = abs(dy);
    int sign_x = dx > 0? 1 : -1, sign_y = dy > 0? 1 : -1;

    Posicion p(p0.x, p0.y);
    for (int ix = 0, iy = 0; ix < nx || iy < ny;) {
        int decision = (1 + 2*ix) * ny - (1 + 2*iy) * nx;
        if (decision == 0) {
            // paso diagonal
            p.x += sign_x;
            p.y += sign_y;
            ix++;
            iy++;
        } else if (decision < 0) {
            // paso horizontal
            p.x += sign_x;
            ix++;
        } else {
            // paso vertical
            p.y += sign_y;
            iy++;
        }
        if(matriz[p.y][p.x]!='1'){matriz[p.y][p.x]=celda;}
    }
    
}

void generarBarrerasHorizontales(char mapa[alto][ancho], int cantidad){
        uniform_int_distribution<std::mt19937::result_type> posy(0,alto-1);
        uniform_int_distribution<std::mt19937::result_type> posx(0,ancho-1);
        uniform_int_distribution<std::mt19937::result_type> lnt(4,10);

        for(int i=0;i<cantidad;i++){
            int posicionx= posx(rng);
            int posiciony= posy(rng);
            int largo= lnt(rng);
            while(posicionx+largo>ancho-1){
                posicionx= posx(rng);
                posiciony= posy(rng);
                largo= lnt(rng);
            }
            for(int j=0;j<largo;j++){
                mapa[posiciony][posicionx+j]= 'x';
            }
        }
}

void generarBarrerasVerticales(char mapa[alto][ancho], int cantidad){
        uniform_int_distribution<std::mt19937::result_type> posy(0,alto-1);
        uniform_int_distribution<std::mt19937::result_type> posx(0,ancho-1);
        uniform_int_distribution<std::mt19937::result_type> lnt(4,10);

        for(int i=0;i<cantidad;i++){
            int posicionx= posx(rng);
            int posiciony= posy(rng);
            int largo= lnt(rng);
            while(posiciony+largo>alto-1){
                posicionx= posx(rng);
                posiciony= posy(rng);
                largo= lnt(rng);
            }
            for(int j=0;j<largo;j++){
                mapa[posiciony+j][posicionx]= 'x';
            }
        }
}

void generarParches(char mapa[alto][ancho], int cantidad){
        uniform_int_distribution<std::mt19937::result_type> posx(0,ancho-3);
        uniform_int_distribution<std::mt19937::result_type> posy(0,alto-3);

        for(int i=0;i<cantidad;i++){
            int posicionx= posx(rng);
            int posiciony= posy(rng);

            while(posiciony+3>99&&posicionx+3>99){
                posicionx= posx(rng);
                posiciony= posy(rng);
            }
            for(int y=0;y<3;y++){
                for (int x = 0; x < 3; x++)
                {
                    mapa[posiciony+y][posicionx+x]= '1';
                }
            }
        }
}

void generarPequenos(char mapa[alto][ancho], int cantidad){
        uniform_int_distribution<std::mt19937::result_type> posx(0,ancho-1);
        uniform_int_distribution<std::mt19937::result_type> posy(0,alto-1);

        for(int i=0;i<cantidad;i++){
            int posicionx= posx(rng);
            int posiciony= posy(rng);
                    mapa[posiciony][posicionx]= '1';
                }

}

float calGuarDistancia(float matrizAdyacencia[cantidad_parches+1][cantidad_parches+1], vector<Posicion> &parches, char mapa[alto][ancho]){
    for(int i = 0; i < parches.size(); ++i){
        for(int j = i; j < parches.size(); ++j){
            if(detectarBarrera(parches[i],parches[j],mapa)){
                Posicion p0 = parches[i];
                Posicion p1 = parches[j];
                matrizAdyacencia[i][j]= sqrt( pow( p1.x-p0.x, 2) + pow( p1.y-p0.y, 2) );
                matrizAdyacencia[j][i]= sqrt( pow( p1.x-p0.x, 2) + pow( p1.y-p0.y, 2) );
            }else{
                matrizAdyacencia[i][j]= 0;
                matrizAdyacencia[j][i]= 0;
            }
        }
    }
}

vector<Posicion>  detectarParches(char mapa[alto][ancho], vector<Posicion> &parches) {
    vector<Posicion> posicionesParches;
    Posicion inicio(0, 0);
    parches.push_back(inicio);
    cout << "Parches detectados:" << endl;
    for (int i = 0; i < alto - 2; i++) {
        for (int j = 0; j < ancho - 2; j++) {
            bool esParche = true;

            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (mapa[i + k][j + l] != '1') {
                        esParche = false;
                        break;
                    }
                }
                if (!esParche) break;
            }

            if (esParche) {
                Posicion parche(j + 1, i + 1);
                parches.push_back(parche);
            }
        }
    }
    return parches;
}

pair<int, vector<int>> findShortestHamiltonianCycle(float graph[][cantidad_parches+1], int start, int size) {
    int n = size;
    queue<Node*> q;
    Node* startNode = new Node(n);
    startNode->vertex = start;
    startNode->path.push_back(start);
    startNode->visited[start] = true;
    q.push(startNode);

    int minCycleLength = numeric_limits<int>::max();
    vector<int> minCyclePath;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        // If all nodes are visited, check for Hamiltonian cycle
        if (current->path.size() == n) { //si se han visitado todos los nodos
            if (graph[current->vertex][start] > 0) { // Si hay un arista que conecte el vertice actual al vertice start
                int cycleLength = current->path_length + graph[current->vertex][start]; //se calcula la long del ciclo
                if (cycleLength < minCycleLength) { //si el largo del ciclo es menor que el que había
                    minCycleLength = cycleLength;// se actualiza el largo mínimo para la nueva arista
                    minCyclePath = current->path;// se actualiza la arista
                    minCyclePath.push_back(start); // Complete the cycle
                }
            }
            delete current;
            continue;
        }

        // Explore neighbors
        for (int neighbor = 0; neighbor < n; ++neighbor) { //para cada vecino
            if (!current->visited[neighbor] && graph[current->vertex][neighbor] > 0) { //si no fue visitado y existe un camino
                Node* nextNode = new Node(*current); //se crea un nuevo nodo copiando el actual
                nextNode->vertex = neighbor; //actualiza el vértice
                nextNode->visited[neighbor] = true; //se actualiza visited
                nextNode->path_length += graph[current->vertex][neighbor]; ////se actualiza el largo de la arista
                nextNode->path.push_back(neighbor); //se actualiza la arista
                q.push(nextNode); //se añade el next Node a la cola
            }
        }
        delete current;
    }

    return {minCycleLength == numeric_limits<int>::max() ? -1 : minCycleLength, minCyclePath};
}

void printMapa(char mapa[alto][ancho]){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    for (int i = 0; i < alto; i++)
        {
            for (int j = 0; j < ancho; j++){
                SetConsoleTextAttribute(hConsole, consoleInfo.wAttributes & ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE));
                if(mapa[i][j]=='T'){SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);}
                else if(mapa[i][j]=='x'){SetConsoleTextAttribute(hConsole, BACKGROUND_RED);}
                else if(mapa[i][j]=='1'){SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);}
                else if(mapa[i][j]=='&'){SetConsoleTextAttribute(hConsole, (hConsole, BACKGROUND_RED | BACKGROUND_GREEN));}
                cout<<"-";
            }
        SetConsoleTextAttribute(hConsole, consoleInfo.wAttributes & ~(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE));
        cout<<endl;
        }

}

void pintarPosibles( char mapa[alto][ancho],vector<Posicion> parches){
    for(int i = 0; i < parches.size(); ++i){
        for(int j = i; j < parches.size(); ++j){
            if(detectarBarrera(parches[i],parches[j],mapa)){pintarRecorrido(parches[i],parches[j],mapa,'T');}
            
        }
    }
}

void escribirMapa(const string &input, char mapa[alto][ancho]){
    std::ofstream file(input);

    for(int i=0; i<alto; i++){
        for(int j=0; j<ancho; j++){
            file << mapa[i][j];
        }
        file << endl;
    }
    
    cout << "Mapa escrito en " << input << endl;
}

void leerMapa(const string &input, char mapa[alto][ancho]){
    std::ifstream file("input.txt");
    if (file.is_open())
    {
    string linea ="";
    int i =0;
    while(getline(file,linea)){
        for(int j=0; j<ancho; j++){
            mapa[i][j]=linea[j];
        }
        i++;
    }
    cout << "Mapa leido en " << input << endl;
    }
}


int main (int argc, char *argv[])
{
char opcion;
while(opcion!='S'&&opcion!='N'&&opcion!='s'&&opcion!='n'){
cout<<"Generar mapa nuevo?(S/N) Si cambio parametros de ancho o alto genere uno nuevo"<<endl;
cin>>opcion;
}
char mapa[alto][ancho];
if(opcion=='s'||opcion=='y'){
    
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            mapa[i][j] = '0';
        }
    }
    generarParches(mapa,cantidad_parches);
    generarPequenos(mapa,50);
    generarBarrerasHorizontales(mapa,cantidad_barreras/2);
    generarBarrerasVerticales(mapa,cantidad_barreras/2);
    cout<<"se lleno la matriz"<<endl;



    std::ofstream file(fileName, ios::out | ios::trunc);

    if((!file.is_open())){
        std::cerr << "No se puede abrir el archivo" << std::endl;
        return EXIT_SUCCESS;
    }
    escribirMapa(fileName ,mapa);
}
    //leer .txt
    leerMapa(fileName,mapa);
    
    //encontrar parches
    vector<Posicion> parches;
    detectarParches(mapa, parches);
    cout<<"Se calcularon los parches"<<endl;

    //pintar caminos posibles   
    pintarPosibles(mapa,parches);
    cout<<"se pintaron los posibles"<<endl;

    //crear matriz  adyacencia
    float mAdyacencia[cantidad_parches+1][cantidad_parches+1];
    calGuarDistancia(mAdyacencia, parches, mapa);

    cout<<"cantidad parches: "<<parches.size()-1<<endl;



    pair<int,vector<int>> resultado = findShortestHamiltonianCycle(mAdyacencia, 0,parches.size());    

    if (resultado.first != -1) {
        cout << "El camino mas corto es de largo: " << resultado.first << endl;
        cout << "El camino es: ";
        for (int node : resultado.second) {
            cout << node << " ";
        }
        cout << endl;
    
    for (int i = 0; i < resultado.second.size()-1; i++)
    {   
        cout<<"pintando camino: "<<resultado.second[i]<<" "<<resultado.second[i+1]<<endl;
        pintarRecorrido(parches[resultado.second[i]],parches[resultado.second[i+1]],mapa,'&');
        
    }

    
    printMapa(mapa);
    
    }else {cout<<endl<<"NO SE ENCONTRO UN HAMILTONIANO VALIDO";}
    


}