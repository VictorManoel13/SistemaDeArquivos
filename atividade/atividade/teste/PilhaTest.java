package atividade.teste;

import atividade.dominio.Pilha;

public class PilhaTest {
    public static void main(String[] args) {
        Pilha pilha = new Pilha();

        pilha.push("Carla");
        pilha.push("Victor");
        pilha.push("Manoel");
        pilha.push("Joselita");
        pilha.push("Helder");
        pilha.push("Ingridy");
        pilha.pop();
        pilha.pop();
        pilha.pop();
        pilha.pop();
        pilha.pop();
        pilha.pop();

        pilha.push("Ingridy");

        pilha.imprime();
    }
}
