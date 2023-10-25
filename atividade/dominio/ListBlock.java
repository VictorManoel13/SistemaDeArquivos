package atividade.dominio;

public class ListBlock {

	private Block refBlock;
	public void add(Block b) {

		b.setProx(this.refBlock);
		this.refBlock = b;
	}

	public void addByIndex(Block b, int index) {

		if(index == contagem()){
			add(b);
		} else if(index != 0){
			Block atual = find(index);
			b.setProx(atual.getProx());
			atual.setProx(b);
		} else{
			
		}

	}
	/*
	* Localiza um bloco de uma posição especificadas por index - 0, 1, 2, ...
	*/
	public int contagem(){
		int quantidade = 0;
		Block aux = this.refBlock;
		while(aux != null){
			quantidade++;
			aux = aux.getProx();
		}
		return quantidade;
	}
	public Block find(int index) {
		int quantidade = contagem();
		Block aux = this.refBlock;
		while(aux != null && index != quantidade){
			quantidade--;
			aux = aux.getProx();
		}
		return aux;
	}
	/*
	* Remove de uma posição especificada por index - 0, 1, 2, ...
	*/
	public void remove(int index) {
		Block anterior = find(index+1);
		Block atual = find(index);
		if(contagem() == index){
			this.refBlock = atual.getProx();
		} else{
			anterior.setProx(atual.getProx());
		}
	}

	public void imprime(){
		Block aux = this.refBlock;
		while(aux != null){
			System.out.println(aux.getContent());
			aux = aux.getProx();
		}
	}
}
