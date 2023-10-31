package atividade.teste;

import atividade.dominio.Block;
import atividade.dominio.ListBlock;

public class BlockTest {
    public static void main(String[] args) {
        Block block1 = new Block();
        Block block2 = new Block();
        Block block3 = new Block();
        Block block4 = new Block();
        Block block5 = new Block();

        Block blockRef = new Block();
        ListBlock listBlock = new ListBlock();

        block1.setContent("Block 1");
        block2.setContent("Block 2");
        block3.setContent("Block 3");
        block4.setContent("Block 4");
        block5.setContent("Block 5");

        listBlock.addByIndex(block1, 0);
        listBlock.addByIndex(block2, 1);
        listBlock.addByIndex(block3, 1);
        listBlock.addByIndex(block4, 1);
        listBlock.addByIndex(block5, 3);

        blockRef = listBlock.find("Block 5");
        //listBlock.remove(2);
        System.out.println(blockRef.getContent());
        listBlock.imprime();
        //System.out.println(blockRef.getContent());

    }
}
