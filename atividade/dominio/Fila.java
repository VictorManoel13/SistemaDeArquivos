package atividade.dominio;

public class Fila {
    private ListBlock listBlock = new ListBlock();
    public void add(String content){
        Block block = new Block();
        block.setContent(content);
        listBlock.add(block);
    }
    public void remove(){
        listBlock.remove(0);
    }
    public void imprime(){
        listBlock.imprime();
    }
}
