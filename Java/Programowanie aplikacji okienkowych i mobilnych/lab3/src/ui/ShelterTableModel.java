package ui;

import models.AnimalShelter;
import javax.swing.table.AbstractTableModel;
import java.util.List;

public class ShelterTableModel extends AbstractTableModel {
    private List<AnimalShelter> shelters;

    public ShelterTableModel(List<AnimalShelter> shelters) {
        this.shelters = shelters;
    }

    @Override
    public int getRowCount() {
        return shelters.size();
    }

    @Override
    public int getColumnCount() {
        return 2; // np. Nazwa i Pojemność
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        AnimalShelter shelter = shelters.get(rowIndex);
        switch (columnIndex) {
            case 0: return shelter.getShelterName();
            case 1: return shelter.getCapacity();
            default: return null;
        }
    }

    @Override
    public String getColumnName(int column) {
        return switch (column) {
            case 0 -> "Nazwa Schroniska";
            case 1 -> "Pojemność";
            default -> "";
        };
    }

    public void setShelters(List<AnimalShelter> shelters) {
        this.shelters = shelters;
        fireTableDataChanged();
    }
}
