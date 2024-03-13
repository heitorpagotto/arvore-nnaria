#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct knot {
    int key;
    struct knot *nextChild;
    struct knot *nextSibling;
}
KNOT;
typedef KNOT *POINTER;

POINTER createKnot(int key) {
    // Aloca memória do tamanho da struct KNOT
    // PODE CAUSAR UM LEAK DE MEMÓRIA
    auto newKnot = (POINTER)malloc(sizeof(KNOT));

    // Atribuí o valores da chave e do filho e irmão
    newKnot->key = key;
    newKnot->nextChild = nullptr;
    newKnot->nextSibling = nullptr;

    return (newKnot);
}

POINTER initTree(int key) {
    return createKnot(key);
}

POINTER searchKey(int key, POINTER root) {
    // Caso o ponteiro root seja null, é retornado null
    if (root == nullptr) return nullptr;

    // Se a chave do ponteiro root for igual a chave que é usada para busca
    // é retornado o próprio root
    if (root->key == key) return root;

    // É criado um ponteiro temporário olhando o filho do root
    POINTER temp = root->nextChild;
    while (temp) {
        // Iteração que roda recursivamente a mesma função até achar o ponteiro necessário
        POINTER search = searchKey(key, temp);
        // Quando o ponteiro é encontrado, ele é retornado
        if (search) return search;
        temp = temp->nextSibling;
    }

    return nullptr;
}

bool insertInTree(POINTER root, int newKey, int parentKey) {
    // Busca o ponteiro pai
    POINTER parent = searchKey(parentKey, root);

    // Se não achar o ponteiro pai, é retornado false
    if (!parent) return false;

    // Cria um novo nó
    POINTER child = createKnot(newKey);
    // Pega o primeiro filho do ponteiro pai
    POINTER temp = parent->nextChild;

    // Se o primeiro filho é null é substituído com o novo nó criado
    if (!temp)
        parent->nextChild = child;
    else {
        // Caso o primeiro filho não seja null é feito uma iteração
        // até o próximo irmão ser null
        while(temp->nextSibling){
            temp = temp->nextSibling;
        }
        // Quando o próximo irmão for null, ele será sobrescrito pelo novo nó criado
        temp->nextSibling = child;
    }

    return true;
}

void printTree(POINTER root) {
    // Caso o ponteiro root for null, a função não prossegue
    if (root == nullptr) return;

    // É printado o valor da chave de root e uma parentese
    cout << root->key << "(";

    // Olhamos o filho do ponteiro root, e caso ele não seja null, a função é chamada recursivamente até que os ponteiros acabem
    POINTER child = root->nextChild;
    while(child) {
        printTree(child);
        child = child->nextSibling;
    }

    cout << ")";
}

int main() {
    POINTER pointer = initTree(8);

    for (int i = 0; i < 5; i++) {
        insertInTree(pointer, i + 7, 8);
        int j = 0;
        for (; j < 2; j++){
            insertInTree(pointer->nextChild, j + 5, i+7);
        }
    }

    printTree(pointer);

    return 1;
}