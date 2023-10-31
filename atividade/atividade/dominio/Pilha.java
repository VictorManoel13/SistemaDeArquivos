package atividade.dominio;
public class Pilha {
    private ListBlock listBlock = new ListBlock();
    public void push(String content){
        Block block = new Block();
        block.setContent(content);
        listBlock.add(block);
    }
    public void pop(){
        try{
            listBlock.remove(listBlock.quantidadeDeElementos()-1);
        }
        catch (NullPointerException e) {
            System.out.println("Pilha vazia, não foi possível remover!");
        }
    }
    public void imprime(){
        listBlock.imprime();
    }
}