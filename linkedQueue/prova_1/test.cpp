#include "pch.h"
#include "Prova.h"

class Unidade1Test : public ::testing::Test {
protected:
	void TearDownDLL() {
		struct noDuplo* aux;
		struct noDuplo* proxNo = listaDLL->cabeca;
		while (proxNo != NULL) {
			aux = proxNo;
			proxNo = proxNo->prox;
			free(aux);
		}
		free(listaDLL);
	}

	void TearDownLL() {
		struct no* aux;
		struct no* proxNo = listaLL->cabeca;
		while (proxNo != NULL) {
			aux = proxNo;
			proxNo = proxNo->prox;
			free(aux);
		}
		free(listaLL);
	}

	virtual void TearDown() {
		TearDownLL();
		TearDownDLL();
	}

	virtual void SetUp() {
		listaLL = inicializarLL();
		listaDLL = inicializarDLL();
	}

	struct linkedlist* listaLL = NULL;
	struct doublylinkedlist* listaDLL = NULL;
};

/******************************************/

/* Q1: Inverta uma lista duplamente ligada
 * com um algoritmo in-place (ou seja, sem
 * criar uma nova lista duplamente ligada)
 */

TEST_F(Unidade1Test, InverterDoublyLinkedListNumPar) {
	int qtdadeElementos = 10;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(listaDLL, i);
	}
	inverterDoublyLinkedList(listaDLL);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(listaDLL, i), qtdadeElementos - i);
	}
}

TEST_F(Unidade1Test, InverterDoublyLinkedListNumImpar) {
	int qtdadeElementos = 11;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(listaDLL, i);
	}
	inverterDoublyLinkedList(listaDLL);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(listaDLL, i), qtdadeElementos - i);
	}
}

/******************************************/

/* Q2: escreva um algoritmo que detecte se uma
 * certa combinacao de parenteses estah balanceada.
 * Dica: usar pilha, pode ser a impl "stack" CPP STL.
 * Olhe os casos de teste para entender o que eh uma
 * combinacao balanceada.
 */


TEST_F(Unidade1Test, CombinacaoParentesesBalanceados) {
	const char* parentesesTest = "()()";
	EXPECT_TRUE(balanceamentoParenteses(parentesesTest, 4));
	parentesesTest = "(())";
	EXPECT_TRUE(balanceamentoParenteses(parentesesTest, 4));
	parentesesTest = "(())()()";
	EXPECT_TRUE(balanceamentoParenteses(parentesesTest, 8));
	parentesesTest = "((())()())";
	EXPECT_TRUE(balanceamentoParenteses(parentesesTest, 10));
}

TEST_F(Unidade1Test, CombinacaoParentesesDesbalanceados) {
	const char* parentesesTest = ")()(";
	EXPECT_FALSE(balanceamentoParenteses(parentesesTest, 4));
	parentesesTest = "(()))";
	EXPECT_FALSE(balanceamentoParenteses(parentesesTest, 5));
	parentesesTest = "(())()())";
	EXPECT_FALSE(balanceamentoParenteses(parentesesTest, 9));
	parentesesTest = "(((())()())";
	EXPECT_FALSE(balanceamentoParenteses(parentesesTest, 11));
	parentesesTest = "())(";
	EXPECT_FALSE(balanceamentoParenteses(parentesesTest, 4));
}


/******************************************/

/* Q3: Inverta uma lista ligada (LinkedList)
 * com um algoritmo in-place (ou seja, sem
 * criar uma nova LinkedList)
 */

TEST_F(Unidade1Test, InverterLinkedListNumPar) {
	int qtdadeElementos = 10;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(listaLL, i);
	}
	inverterLinkedListInPlace(listaLL);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(listaLL, i), qtdadeElementos - i);
	}
}

TEST_F(Unidade1Test, InverterLinkedListNumImpar) {
	int qtdadeElementos = 11;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(listaLL, i);
	}
	inverterLinkedListInPlace(listaLL);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(listaLL, i), qtdadeElementos - i);
	}
}

TEST_F(Unidade1Test, InverterLinkedList1Elemento) {
	int qtdadeElementos = 1;
	for (int i = 1; i <= qtdadeElementos; i++) {
		inserirElementoNoFim(listaLL, i);
	}
	inverterLinkedListInPlace(listaLL);
	for (int i = 0; i < qtdadeElementos; i++) {
		EXPECT_EQ(obterElementoEmPosicao(listaLL, i), qtdadeElementos - i);
	}
}