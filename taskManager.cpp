#include <iostream>
#include <cstring>
using namespace std;

void callMenuList();
void removeElementList();

struct SCHEDULE {
    char task[50];
    struct SCHEDULE* next;
};

//Creacion del nodo raiz de la lista llamado scheduleList
struct SCHEDULE* scheduleList = NULL;

//Abajo declaro mi matriz para que sea global
struct SCHEDULE*** calendar;
int month;
int day;


void scheduler() {
    calendar = new struct SCHEDULE** [12]; //dos punteros harían a una matriz con dos dimensiones, el tercer puntero es para indicar el puntero que hay dentro de cada casilla de las dos dimensiones porque ese tercer puntero es el inicio de una LISTA
    int numberOfDays;

    for (int i = 0; i < 12; i++) {
        switch (i) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            numberOfDays = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            numberOfDays = 30;
        default: numberOfDays = 28;
        }

        calendar[i] = new struct SCHEDULE* [numberOfDays];

        //Con el for de abajo cada elemento de cada día se establece en NULL ya que se trabajaran listas
        for (int j = 0; j < numberOfDays; j++) {
            calendar[i][j] = NULL;
        }
    }
}

void selectDate() {
    cout << "Select the month to manage the list of tasks: ";
    cin >> month;
    cout << "Select the day: ";
    cin >> day;

    scheduleList = calendar[month][day];
    callMenuList();
}

void insertElementList(char task[50], int position) {
    //Aqui creo (instancio) la task que me estan enviando para poderle asignar valores
    struct SCHEDULE* element = new SCHEDULE[1];
    strcpy_s(element->task, task);
    element->next = NULL; //En null para poner la task al final de la lista

    //Ahora empiezo a recorrer la lista
    struct SCHEDULE* aux = new SCHEDULE[1]; //variable auxiliar para recorrer la lista

    if (position == 1) {
        element->next = scheduleList; //para la task nueva, decimos que su next apuntará hacia donde el nodo raiz este apuntando
        scheduleList = element; // y ahora que el nodo raiz apunte a la task nueva
    }
    else { //si no es el primer elemento el que nos mandan, entramos a recorrer la lista de elementos que tenemos
        aux = scheduleList;
        for (int i = 1; aux; i++) { //este for es para localizar el elemento previo
            if (i == position - 1) { //o sea ya en el elemento previo
                break;
            }
            else { //que siga avanzando
                aux = aux->next;
            }
        }

        element->next = aux->next;//hacemos que el nuevo elemento apunte a donde esta apuntando el elemento previo
        aux->next = element;//y ahora que el elemento previo apunte al nuevo

    }
}

void addElementList() {
    char task[50];
    int position;
    cout << "What is the new task?";
    cin >> task;
    cout << "Type the position of the task: ";
    cin >> position;

    insertElementList(task, position);
    callMenuList();
}

void createDefaultList() {
    char task[50];

    strcpy_s(task, "Brush my teeth");
    insertElementList(task, 1);

    strcpy_s(task, "Running");
    insertElementList(task, 2);

    strcpy_s(task, "Wash the dishes");
    insertElementList(task, 3);

    cout << endl << "The default tasks were added" << endl;

    callMenuList();
}

void showList(bool optionalMenu) { //Bool porque si recibe un true, muestra el menu despues de ejecutarse, si es false solo muestra la lista
    struct SCHEDULE* aux = scheduleList;//variable auxiliar para recorrer lista
    cout << "Task for the day." << endl << endl;
    for (int i = 1; aux; i++) {
        cout << "Task " << i << " : " << aux->task << endl;
        aux = aux->next;
    }

    if (optionalMenu) callMenuList();
}

void callMenuList() {

    //Abajo es el codigo para que una vez que ya elegimos el mes y dia del que queremos la lista de tareas, se muestren las opciones que tenemos sobre ellas
    int option;
    do {
        cout << endl << endl << "List of options for the selected month and day." << endl;
        cout << "1 - Show tasks for the day" << endl;
        cout << "2 - Add task for the day" << endl;
        cout << "3 - Remove task for the day" << endl;
        cout << "4 - Create a default task list" << endl;
        cout << "5 - Go back to select a diferent date" <<endl;
        cout << "6 - Exit" << endl;

        cin >> option;
    } while (option < 1 || option>6);

    switch (option) {
    case 1:
        showList(true); break;
    case 2:
        addElementList(); break;
    case 3:
        removeElementList(); break;
    case 4:
        createDefaultList(); break;
    case 5:
        calendar[month][day] = scheduleList;
        selectDate();
    case 6:
        break;
    }
}

void removeElementList() {
    showList(false);
    int number;
    cout << "Select the task to delete: ";
    cin >> number;

    if (number == 1 && scheduleList != NULL) {
        scheduleList = scheduleList->next;
    }
    else {
        struct SCHEDULE* aux = new SCHEDULE[1];
        aux = scheduleList;
        for (int i = 1; aux; i++) {
            if (number == i - 1) {
                if (aux->next->next == NULL) {
                    aux->next = NULL;
                }
                else {
                    aux->next = aux->next->next;
                    aux = NULL;
                    delete[] aux;
                }
                if (aux) {
                    aux = aux->next;
                }
            }
        }
    }
    callMenuList();
}

int main() {
    scheduler();
    selectDate();
    return 0;
}
