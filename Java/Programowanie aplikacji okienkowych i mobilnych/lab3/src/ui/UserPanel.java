package ui;

import models.AnimalShelter;
import models.ShelterManager;
import models.Animal;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UserPanel {
    private ShelterManager shelterManager;

    public UserPanel(ShelterManager shelterManager) {
        this.shelterManager = shelterManager;
    }

    public void showUserPanel() {
        JFrame frame = new JFrame("Panel Użytkownika");
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setLayout(new BorderLayout());

        // Wybór schroniska
        JComboBox<String> shelterComboBox = new JComboBox<>(shelterManager.getShelterNames());
        frame.add(shelterComboBox, BorderLayout.NORTH);

        // Tabela zwierząt
        JTable animalTable = new JTable();
        frame.add(new JScrollPane(animalTable), BorderLayout.CENTER);

        shelterComboBox.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                AnimalShelter selectedShelter = shelterManager.getShelterByName((String) shelterComboBox.getSelectedItem());
                AnimalTableModel animalTableModel = new AnimalTableModel(selectedShelter.getAnimals());
                animalTable.setModel(animalTableModel);
            }
        });

        // Wyświetlanie szczegółów zwierzęcia
        JButton detailsButton = new JButton("Szczegóły zwierzęcia");
        detailsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int selectedRow = animalTable.getSelectedRow();
                if (selectedRow != -1) {
                    AnimalShelter selectedShelter = shelterManager.getShelterByName((String) shelterComboBox.getSelectedItem());
                    Animal selectedAnimal = selectedShelter.getAnimals().get(selectedRow);
                    JOptionPane.showMessageDialog(frame, "Imię: " + selectedAnimal.getName() +
                            "\nGatunek: " + selectedAnimal.getSpecies() +
                            "\nWiek: " + selectedAnimal.getAge() +
                            "\nOpis: " + selectedAnimal.getDescription());
                }
            }
        });

        // Panel przycisków
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(detailsButton);
        frame.add(buttonPanel, BorderLayout.SOUTH);

        frame.pack();
        frame.setVisible(true);
    }
}
