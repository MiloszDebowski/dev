package ui;

import models.Animal;
import javax.swing.table.AbstractTableModel;
import java.util.List;

public class AnimalTableModel extends AbstractTableModel {
    private List<Animal> animals;
    private final String[] columnNames = {"Imię", "Gatunek", "Stan", "Wiek", "Cena"};

    public AnimalTableModel(List<Animal> animals) {
        this.animals = animals;
    }

    @Override
    public int getRowCount() {
        return animals.size();
    }

    @Override
    public int getColumnCount() {
        return columnNames.length;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        Animal animal = animals.get(rowIndex);
        switch (columnIndex) {
            case 0: return animal.getName();
            case 1: return animal.getSpecies();
            case 2: return animal.getCondition();
            case 3: return animal.getAge();
            case 4: return animal.getPrice();
            default: return null;
        }
    }

    @Override
    public String getColumnName(int column) {
        return columnNames[column];
    }
}
