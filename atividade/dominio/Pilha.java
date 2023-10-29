package atividade.dominio;
public class Pilha {
    private ListBlock listBlock = new ListBlock();
    public void push(String content){
        Block block = new Block();
        block.setContent(content);
        listBlock.add(block);
    }
    public void pop(){
        listBlock.remove(listBlock.quantidadeDeElementos()-1);
    }
    public void imprime(){
        listBlock.imprime();
    }
}