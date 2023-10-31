package atividade.dominio;

public class Fila {
    private ListBlock listBlock = new ListBlock();
    public void add(String content){
        Block block = new Block();
        block.setContent(content);
        listBlock.add(block);
    }
    public void remove(){
        try {
            listBlock.remove(0);
        } catch (NullPointerException e) {
            System.out.println("Fila vazia, não é possível remover!");
        }
    }
    public void imprime(){
        listBlock.imprime();
    }
}
