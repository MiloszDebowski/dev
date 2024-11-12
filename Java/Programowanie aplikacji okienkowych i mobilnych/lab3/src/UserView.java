import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class UserView extends JFrame {
    private final ShelterManager shelterManager;

    public UserView(ShelterManager shelterManager) {
        this.shelterManager = shelterManager;
        setTitle("User Panel");
        setSize(500, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);


        JPanel panel = new JPanel(new GridBagLayout());
        panel.setBackground(Color.PINK);
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10); // Marginesy między komponentami

        // Etykieta "Choose an option"
        JLabel label = new JLabel("Choose an option:");
        label.setFont(new Font("Arial", Font.BOLD, 16));
        label.setForeground(Color.WHITE); // Biały kolor czcionki
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 2;
        gbc.anchor = GridBagConstraints.CENTER;
        panel.add(label, gbc);

        // Przycisk "View Animals"
        JButton viewAnimalsButton = new JButton("View Animals");
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridwidth = 1;
        gbc.anchor = GridBagConstraints.CENTER;
        panel.add(viewAnimalsButton, gbc);

        // Przycisk "Adopt Animal"
        JButton adoptButton = new JButton("Adopt Animal");
        gbc.gridx = 1;
        gbc.gridy = 1;
        panel.add(adoptButton, gbc);

        // Akcja dla przycisku "View Animals"
        viewAnimalsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String shelterName = JOptionPane.showInputDialog("Enter shelter name to view animals:");
                AnimalShelter shelter = shelterManager.getShelters().get(shelterName);

                if (shelter == null) {
                    JOptionPane.showMessageDialog(null, "Shelter not found.");
                    return;
                }

                List<Animal> animals = shelter.sortByName(); // Sortowanie zwierząt po nazwie
                StringBuilder animalsList = new StringBuilder("Animals in " + shelterName + ":\n");

                for (Animal animal : animals) {
                    animalsList.append(animal.toString()).append("\n");
                }

                JOptionPane.showMessageDialog(null, animalsList.toString());
            }
        });

        // Akcja dla przycisku "Adopt Animal"
        adoptButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String shelterName = JOptionPane.showInputDialog("Enter shelter name to adopt from:");
                AnimalShelter shelter = shelterManager.getShelters().get(shelterName);

                if (shelter == null) {
                    JOptionPane.showMessageDialog(null, "Shelter not found.");
                    return;
                }

                String animalName = JOptionPane.showInputDialog("Enter animal name to adopt:");
                Animal animalToAdopt = shelter.search(animalName).stream().findFirst().orElse(null);

                if (animalToAdopt == null) {
                    JOptionPane.showMessageDialog(null, "Animal not found.");
                    return;
                }

                shelter.adoptAnimal(animalToAdopt);
                JOptionPane.showMessageDialog(null, animalToAdopt.getName() + " has been adopted.");
            }
        });

        // Dodanie panelu do ramki
        add(panel);
    }
}
