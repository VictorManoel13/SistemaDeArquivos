package atividade.teste;

import atividade.dominio.Fila;

public class FilaTest {
    public static void main(String[] args) {
        Fila fila = new Fila();

        fila.add("Carla");
        fila.add("Victor");
        fila.add("Manoel");
        fila.add("Joselita");
        fila.add("Helder");
        fila.add("Ingridy");
        fila.remove();
        fila.remove();
        fila.remove();
        fila.imprime();
    }
}
