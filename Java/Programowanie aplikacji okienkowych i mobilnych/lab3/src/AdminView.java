import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.List;


public class AdminView extends JFrame {
    private final ShelterManager shelterManager;
    private JComboBox<String> shelterComboBox;
    private JTextArea animalsTextArea;
    private JTextField filterTextBox;
    private JComboBox<String> stateComboBox;
    private JButton sortSheltersButton;

    public AdminView(ShelterManager shelterManager) {
        this.shelterManager = shelterManager;
        setTitle("Admin Panel");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        //panele
        JPanel mainPanel = new JPanel(new BorderLayout());
        JPanel topPanel = new JPanel();
        JPanel centerPanel = new JPanel(new BorderLayout());
        JPanel bottomPanel = new JPanel();


        //layout
        topPanel.setLayout(new BoxLayout(topPanel, BoxLayout.Y_AXIS));
        bottomPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10));

        //schroniska
        shelterComboBox = new JComboBox<>();
        updateShelterComboBox();
        shelterComboBox.addActionListener(e -> showAnimalsInShelter());

        //sortuj
        sortSheltersButton = new JButton("Sort Shelters");
        sortSheltersButton.addActionListener(e -> sortShelters());

        //filtrowanie po nazwie
        filterTextBox = new JTextField(20);
        filterTextBox.setText("Filter by name or species...");
        filterTextBox.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                    filterAnimalsOrShelters();
                }
            }
        });

        //filtrowanie po stanie
        stateComboBox = new JComboBox<>(new String[]{"ALL", "HEALTHY", "SICK", "IN_ADOPTION", "QUARANTINE"});
        stateComboBox.addActionListener(e -> filterByState());

        //wyswietlanie informacji o zwierzetach
        animalsTextArea = new JTextArea(15, 50);
        animalsTextArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(animalsTextArea);

        //przyciski
        JButton addShelterButton = new JButton("Add Shelter");
        JButton addAnimalButton = new JButton("Add Animal");
        JButton removeShelterButton = new JButton("Remove Shelter");

        addShelterButton.addActionListener(e -> {
            String shelterName = JOptionPane.showInputDialog("Enter shelter name:");
            int capacity = Integer.parseInt(JOptionPane.showInputDialog("Enter max capacity:"));
            shelterManager.addShelter(shelterName, capacity);
            updateShelterComboBox();
            JOptionPane.showMessageDialog(null, "Shelter added.");
        });

        addAnimalButton.addActionListener(e -> {
            String shelterName = (String) shelterComboBox.getSelectedItem();
            if (shelterName == null) {
                JOptionPane.showMessageDialog(null, "Please select a shelter first.");
                return;
            }

            AnimalShelter shelter = shelterManager.getShelters().get(shelterName);
            if (shelter != null) {
                try {
                    String name = JOptionPane.showInputDialog("Enter animal name:");
                    String species = JOptionPane.showInputDialog("Enter animal species:");
                    String conditionInput = JOptionPane.showInputDialog("Enter animal condition (HEALTHY, SICK, IN_ADOPTION, QUARANTINE):");
                    AnimalCondition condition = AnimalCondition.valueOf(conditionInput.toUpperCase());
                    int age = Integer.parseInt(JOptionPane.showInputDialog("Enter animal age:"));
                    double price = Double.parseDouble(JOptionPane.showInputDialog("Enter animal price:"));

                    if (age < 0 || price < 0) {
                        throw new InvalidAnimalDataException("Age and price cannot be negative.");
                    }

                    Animal animal = new Animal(name, species, condition, age, price);
                    if (shelter.getAnimals().size() >= shelter.getMaxCapacity()) {
                        throw new ShelterCapacityExceededException("Shelter has reached its maximum capacity.");
                    }

                    shelter.addAnimal(animal);
                    showAnimalsInShelter();
                    JOptionPane.showMessageDialog(null, "Animal added.");
                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(null, "Error adding animal: " + ex.getMessage());
                }
            }
        });

        removeShelterButton.addActionListener(e -> {
            String shelterName = (String) shelterComboBox.getSelectedItem();
            if (shelterName != null) {
                shelterManager.removeShelter(shelterName);
                updateShelterComboBox();
                animalsTextArea.setText("");
                JOptionPane.showMessageDialog(null, "Shelter removed.");
            }
        });

        // Dodawanie komponentów do paneli
        topPanel.add(new JLabel("Select Shelter:"));
        topPanel.add(shelterComboBox);
        topPanel.add(sortSheltersButton);
        topPanel.add(new JLabel("Filter by name or species:"));
        topPanel.add(filterTextBox);
        topPanel.add(new JLabel("Filter by condition:"));
        topPanel.add(stateComboBox);

        bottomPanel.add(addShelterButton);
        bottomPanel.add(addAnimalButton);
        bottomPanel.add(removeShelterButton);

        centerPanel.add(scrollPane, BorderLayout.CENTER);

        //dodanie paneli
        mainPanel.add(topPanel, BorderLayout.NORTH);
        mainPanel.add(centerPanel, BorderLayout.CENTER);
        mainPanel.add(bottomPanel, BorderLayout.SOUTH);

        add(mainPanel);
    }

    private void updateShelterComboBox() {
        updateShelterComboBox(null);//refresh
    }

    private void updateShelterComboBox(List<AnimalShelter> sortedShelters) {
        shelterComboBox.removeAllItems();
        if (sortedShelters != null) {
            //dodaje posortowane schroniska
            for (AnimalShelter shelter : sortedShelters) {
                shelterComboBox.addItem(shelter.getShelterName());
            }
        } else {
            //dodaje schroniska z managera jeśli lista nie została podana
            for (String shelterName : shelterManager.getShelters().keySet()) {
                shelterComboBox.addItem(shelterName);
            }
        }


        if (shelterComboBox.getItemCount() > 0) {
            shelterComboBox.setSelectedIndex(0);
            showAnimalsInShelter();
        }
    }


    private void showAnimalsInShelter() {
        String selectedShelterName = (String) shelterComboBox.getSelectedItem();
        if (selectedShelterName != null) {
            AnimalShelter shelter = shelterManager.getShelters().get(selectedShelterName);
            if (shelter != null) {
                List<Animal> animals = shelter.getAnimals();
                StringBuilder animalsText = new StringBuilder("Animals in " + selectedShelterName + ":\n");
                for (Animal animal : animals) {
                    animalsText.append(animal.toString()).append("\n");
                }
                animalsTextArea.setText(animalsText.toString());
            }
        }
    }

    private void sortShelters() {
        List<AnimalShelter> sortedShelters = shelterManager.getSortedShelters();
        updateShelterComboBox(sortedShelters);
        JOptionPane.showMessageDialog(null, "Shelters sorted by max capacity.");
    }


    private void filterAnimalsOrShelters() {
        String query = filterTextBox.getText().trim();
        if (query.isEmpty()) {
            showAnimalsInShelter();
        }
    }

    private void filterByState() {
        String stateFilter = (String) stateComboBox.getSelectedItem();
    }
}
