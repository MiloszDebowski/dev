import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;
import java.util.List;

class AnimalTableModel extends AbstractTableModel {
    private List<Animal> animals;
    private String[] columnNames = {"Name", "Species", "Condition", "Age", "Price"};

    public AnimalTableModel() {
        this.animals = new ArrayList<>();
    }

    public void setAnimals(List<Animal> animals) {
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

    public Animal getAnimalAt(int selectedRow) {
        return animals.get(selectedRow);
    }
}