package atividade.dominio;

public class Block {

	private String content;
	private Block prox;

	public void setProx(Block b) {

		this.prox = b;
	}

	public Block getProx() {

		return this.prox;
	}

	public void setContent(String content) {

		this.content = content;
	}

	public String getContent() {

		return this.content;
	}

}