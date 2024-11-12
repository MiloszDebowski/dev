import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.List;
import java.util.stream.Collectors;

public class MainGUI {
    private ShelterManager shelterManager;
    private JTable shelterTable;
    private JTable animalTable;

    public MainGUI(ShelterManager shelterManager) {
        this.shelterManager = shelterManager;
    }

    public void displayLogin() {
        JFrame loginFrame = new JFrame("Logowanie");
        loginFrame.setSize(300, 150);
        loginFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        loginFrame.add(panel);
        placeLoginComponents(panel);

        loginFrame.setVisible(true);
    }

    private void placeLoginComponents(JPanel panel) {
        panel.setLayout(null);

        JLabel userLabel = new JLabel("User");
        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        JTextField userText = new JTextField(20);
        userText.setBounds(100, 20, 165, 25);
        panel.add(userText);

        JButton loginButton = new JButton("Login");
        loginButton.setBounds(10, 80, 80, 25);
        panel.add(loginButton);

        loginButton.addActionListener(e -> {
            String userRole = userText.getText();
            if ("admin".equalsIgnoreCase(userRole)) {
                displayAdminPanel();
            } else {
                displayUserPanel();
            }
        });
    }

    private void displayAdminPanel() {
        JFrame frame = new JFrame("Panel Admina");
        frame.setSize(800, 600);

        JPanel panel = new JPanel(new BorderLayout());
        frame.add(panel);

        shelterTable = new JTable(new DefaultTableModel(new Object[]{"Nazwa Schroniska", "Pojemność"}, 0));
        refreshShelterTable();
        panel.add(new JScrollPane(shelterTable), BorderLayout.CENTER);

        JPanel adminActions = new JPanel(new FlowLayout());
        JButton addShelterButton = new JButton("Dodaj Schronisko");
        JButton addAnimalButton = new JButton("Dodaj Zwierzę");
        JButton viewAnimalsButton = new JButton("Wyświetl Zwierzęta");
        JButton changeAnimalStatusButton = new JButton("Zmień Stan Zwierzęcia");
        JButton sortSheltersButton = new JButton("Sortuj Schroniska");
        JButton sortAnimalsButton = new JButton("Sortuj Zwierzęta");

        adminActions.add(addShelterButton);
        adminActions.add(addAnimalButton);
        adminActions.add(viewAnimalsButton);
        adminActions.add(changeAnimalStatusButton);
        adminActions.add(sortSheltersButton);
        adminActions.add(sortAnimalsButton); // Dodaj przycisk do sortowania zwierząt

        panel.add(adminActions, BorderLayout.SOUTH);

        // Text Field for Filtering
        JTextField filterTextField = new JTextField(15);
        filterTextField.addActionListener(e -> filterSheltersByName(filterTextField.getText()));
        adminActions.add(filterTextField);

        // JComboBox for State Filtering
        JComboBox<AnimalCondition> stateComboBox = new JComboBox<>(AnimalCondition.values());
        stateComboBox.addActionListener(e -> filterAnimalsByState((AnimalCondition) stateComboBox.getSelectedItem()));
        adminActions.add(stateComboBox);

        addShelterButton.addActionListener(e -> {
            String shelterName = JOptionPane.showInputDialog("Podaj nazwę schroniska:");
            int maxCapacity = Integer.parseInt(JOptionPane.showInputDialog("Podaj maksymalną pojemność:"));
            shelterManager.addShelter(shelterName, maxCapacity);
            refreshShelterTable();
        });

        addAnimalButton.addActionListener(e -> {
            int selectedRow = shelterTable.getSelectedRow();
            if (selectedRow != -1) {
                String shelterName = (String) shelterTable.getValueAt(selectedRow, 0);
                AnimalShelter selectedShelter = shelterManager.editShelter(shelterName);

                if (selectedShelter.getAnimals().size() < selectedShelter.getCapacity()) {
                    String animalName = JOptionPane.showInputDialog("Podaj nazwę zwierzęcia:");
                    String species = JOptionPane.showInputDialog("Podaj gatunek:");
                    int age = Integer.parseInt(JOptionPane.showInputDialog("Podaj wiek:"));
                    double price = Double.parseDouble(JOptionPane.showInputDialog("Podaj cenę:"));

                    AnimalCondition[] conditions = AnimalCondition.values();
                    AnimalCondition condition = (AnimalCondition) JOptionPane.showInputDialog(
                            frame, "Wybierz stan zwierzęcia:", "Stan Zwierzęcia",
                            JOptionPane.QUESTION_MESSAGE, null, conditions, AnimalCondition.ZDROWE);

                    try {
                        selectedShelter.addAnimal(new Animal(animalName, species, condition, age, price));
                    } catch (Exception ex) {
                        throw new RuntimeException(ex);
                    }
                    JOptionPane.showMessageDialog(frame, "Dodano zwierzę do schroniska.");
                } else {
                    JOptionPane.showMessageDialog(frame, "Schronisko osiągnęło maksymalną pojemność.");
                }
            }
        });

        viewAnimalsButton.addActionListener(e -> {
            int selectedRow = shelterTable.getSelectedRow();
            if (selectedRow != -1) {
                String shelterName = (String) shelterTable.getValueAt(selectedRow, 0);
                AnimalShelter selectedShelter = shelterManager.editShelter(shelterName);
                displayAnimalList(selectedShelter);
            }
        });

        changeAnimalStatusButton.addActionListener(e -> {
            int selectedRow = shelterTable.getSelectedRow();
            if (selectedRow != -1) {
                String shelterName = (String) shelterTable.getValueAt(selectedRow, 0);
                AnimalShelter selectedShelter = shelterManager.editShelter(shelterName);

                String animalName = JOptionPane.showInputDialog("Podaj nazwę zwierzęcia:");
                Animal animalToEdit = selectedShelter.getAnimals().stream()
                        .filter(a -> a.getName().equalsIgnoreCase(animalName))
                        .findFirst()
                        .orElse(null);

                if (animalToEdit != null) {
                    AnimalCondition[] conditions = AnimalCondition.values();
                    AnimalCondition newCondition = (AnimalCondition) JOptionPane.showInputDialog(
                            frame, "Wybierz nowy stan:", "Zmiana stanu",
                            JOptionPane.QUESTION_MESSAGE, null, conditions, animalToEdit.getCondition());
                    animalToEdit.setCondition(newCondition);
                    JOptionPane.showMessageDialog(frame, "Zmieniono stan zwierzęcia.");
                } else {
                    JOptionPane.showMessageDialog(frame, "Nie znaleziono zwierzęcia.");
                }
            }
        });

        sortSheltersButton.addActionListener(e -> sortSheltersByCapacity());

        // Sortowanie zwierząt po nazwie
        sortAnimalsButton.addActionListener(e -> sortAnimalsByName());

        frame.setVisible(true);
    }

    private void filterSheltersByName(String name) {
        DefaultTableModel model = (DefaultTableModel) shelterTable.getModel();
        model.setRowCount(0);
        for (AnimalShelter shelter : shelterManager.getShelters()) {
            if (shelter.getShelterName().toLowerCase().contains(name.toLowerCase())) {
                model.addRow(new Object[]{shelter.getShelterName(), shelter.getCapacity()});
            }
        }
    }

    private void filterAnimalsByState(AnimalCondition condition) {
        int selectedRow = shelterTable.getSelectedRow();
        if (selectedRow != -1) {
            String shelterName = (String) shelterTable.getValueAt(selectedRow, 0);
            AnimalShelter selectedShelter = shelterManager.editShelter(shelterName);

            DefaultTableModel model = (DefaultTableModel) animalTable.getModel();
            model.setRowCount(0);
            for (Animal animal : selectedShelter.getAnimals()) {
                if (animal.getCondition() == condition) {
                    model.addRow(new Object[]{animal.getName(), animal.getSpecies(), animal.getCondition(), animal.getAge(), animal.getPrice()});
                }
            }
        }
    }

    private void sortSheltersByCapacity() {
        List<AnimalShelter> sortedShelters = shelterManager.getShelters().stream()
                .sorted((s1, s2) -> Integer.compare(s1.getCapacity(), s2.getCapacity()))
                .collect(Collectors.toList());

        DefaultTableModel model = (DefaultTableModel) shelterTable.getModel();
        model.setRowCount(0);
        for (AnimalShelter shelter : sortedShelters) {
            model.addRow(new Object[]{shelter.getShelterName(), shelter.getCapacity()});
        }
    }

    private void sortAnimalsByName() {
        int selectedRow = shelterTable.getSelectedRow();
        if (selectedRow != -1) {
            String shelterName = (String) shelterTable.getValueAt(selectedRow, 0);
            AnimalShelter selectedShelter = shelterManager.editShelter(shelterName);

            List<Animal> sortedAnimals = selectedShelter.getAnimals().stream()
                    .sorted((a1, a2) -> a1.getName().compareToIgnoreCase(a2.getName()))
                    .collect(Collectors.toList());

            DefaultTableModel model = (DefaultTableModel) animalTable.getModel();
            model.setRowCount(0);
            for (Animal animal : sortedAnimals) {
                model.addRow(new Object[]{animal.getName(), animal.getSpecies(), animal.getCondition(), animal.getAge(), animal.getPrice()});
            }
        }
    }

    private void displayUserPanel() {
        JFrame frame = new JFrame("Panel Użytkownika");
        frame.setSize(800, 600);

        JPanel panel = new JPanel(new BorderLayout());
        frame.add(panel);

        shelterTable = new JTable(new DefaultTableModel(new Object[]{"Nazwa Schroniska", "Pojemność"}, 0));
        refreshShelterTable();
        panel.add(new JScrollPane(shelterTable), BorderLayout.CENTER);

        JButton viewShelterButton = new JButton("Wyświetl Schronisko");
        panel.add(viewShelterButton, BorderLayout.SOUTH);

        viewShelterButton.addActionListener(e -> {
            int selectedRow = shelterTable.getSelectedRow();
            if (selectedRow != -1) {
                String shelterName = (String) shelterTable.getValueAt(selectedRow, 0);
                AnimalShelter selectedShelter = shelterManager.editShelter(shelterName);
                displayAnimalList(selectedShelter);
            }
        });

        frame.setVisible(true);
    }

    private void refreshShelterTable() {
        DefaultTableModel model = (DefaultTableModel) shelterTable.getModel();
        model.setRowCount(0); // Usuwamy wszystkie wiersze z tabeli

        // Iterujemy przez wszystkie schroniska i dodajemy je do tabeli
        for (AnimalShelter shelter : shelterManager.getShelters()) {
            model.addRow(new Object[]{shelter.getShelterName(), shelter.getCapacity()});
        }
    }


    private void displayAnimalList(AnimalShelter shelter) {
        JFrame animalFrame = new JFrame("Zwierzęta w " + shelter.getShelterName());
        animalFrame.setSize(800, 600);

        JPanel panel = new JPanel(new BorderLayout());
        animalFrame.add(panel);

        animalTable = new JTable(new DefaultTableModel(new Object[]{"Nazwa", "Gatunek", "Stan", "Wiek", "Cena"}, 0));
        panel.add(new JScrollPane(animalTable), BorderLayout.CENTER);

        DefaultTableModel model = (DefaultTableModel) animalTable.getModel();
        model.setRowCount(0);
        for (Animal animal : shelter.getAnimals()) {
            model.addRow(new Object[]{animal.getName(), animal.getSpecies(), animal.getCondition(), animal.getAge(), animal.getPrice()});
        }

        JButton adoptAnimalButton = new JButton("Adoptuj Zwierzę");
        panel.add(adoptAnimalButton, BorderLayout.SOUTH);

        adoptAnimalButton.addActionListener(e -> {
            int selectedRow = animalTable.getSelectedRow();
            if (selectedRow != -1) {
                String animalName = (String) animalTable.getValueAt(selectedRow, 0);
                Animal animalToAdopt = shelter.getAnimals().stream()
                        .filter(a -> a.getName().equalsIgnoreCase(animalName))
                        .findFirst()
                        .orElse(null);

                if (animalToAdopt != null) {
                    shelter.removeAnimal(animalToAdopt);
                    JOptionPane.showMessageDialog(animalFrame, "Adoptowałeś zwierzę: " + animalName);
                    refreshShelterTable();
                } else {
                    JOptionPane.showMessageDialog(animalFrame, "Nie znaleziono zwierzęcia.");
                }
            }
        });

        animalFrame.setVisible(true);
    }
}

