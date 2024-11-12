package ui;

import models.AnimalShelter;
import models.ShelterManager;
import models.Animal;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AdminPanel {
    private ShelterManager shelterManager;

    public AdminPanel(ShelterManager shelterManager) {
        this.shelterManager = shelterManager;
    }

    public void showAdminPanel() {
        JFrame frame = new JFrame("Panel Administratora");
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setLayout(new BorderLayout());

        // Wybór schroniska
        JComboBox<String> shelterComboBox = new JComboBox<>(shelterManager.getShelterNames());
        frame.add(shelterComboBox, BorderLayout.NORTH);

        // Tabela zwierząt
        JTable animalTable = new JTable(); // Tabela dla zwierząt
        frame.add(new JScrollPane(animalTable), BorderLayout.CENTER);

        // Przycisk dodawania zwierzęcia
        JButton addButton = new JButton("Dodaj zwierzę");
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String name = JOptionPane.showInputDialog("Podaj imię zwierzęcia:");
                String species = JOptionPane.showInputDialog("Podaj gatunek:");
                int age = Integer.parseInt(JOptionPane.showInputDialog("Podaj wiek zwierzęcia:"));
                String description = JOptionPane.showInputDialog("Podaj opis zwierzęcia:");

                Animal newAnimal = new Animal(name, species, age, description);
                AnimalShelter selectedShelter = shelterManager.getShelterByName((String) shelterComboBox.getSelectedItem());
                selectedShelter.addAnimal(newAnimal);
                updateAnimalTable(animalTable, selectedShelter);
            }
        });

        // Przycisk usuwania zwierzęcia
        JButton deleteButton = new JButton("Usuń zwierzę");
        deleteButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int selectedRow = animalTable.getSelectedRow();
                if (selectedRow != -1) {
                    AnimalShelter selectedShelter = shelterManager.getShelterByName((String) shelterComboBox.getSelectedItem());
                    selectedShelter.removeAnimal(selectedRow);
                    updateAnimalTable(animalTable, selectedShelter);
                }
            }
        });

        // Przycisk edytowania zwierzęcia
        JButton editButton = new JButton("Edytuj zwierzę");
        editButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int selectedRow = animalTable.getSelectedRow();
                if (selectedRow != -1) {
                    AnimalShelter selectedShelter = shelterManager.getShelterByName((String) shelterComboBox.getSelectedItem());
                    Animal animal = selectedShelter.getAnimals().get(selectedRow);
                    String newName = JOptionPane.showInputDialog("Podaj nowe imię:", animal.getName());
                    String newSpecies = JOptionPane.showInputDialog("Podaj nowy gatunek:", animal.getSpecies());
                    int newAge = Integer.parseInt(JOptionPane.showInputDialog("Podaj nowy wiek:", animal.getAge()));
                    String newDescription = JOptionPane.showInputDialog("Podaj nowy opis:", animal.getDescription());

                    animal.setName(newName);
                    animal.setSpecies(newSpecies);
                    animal.setAge(newAge);
                    animal.setDescription(newDescription);
                    updateAnimalTable(animalTable, selectedShelter);
                }
            }
        });

        // Panel przycisków
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(addButton);
        buttonPanel.add(deleteButton);
        buttonPanel.add(editButton);
        frame.add(buttonPanel, BorderLayout.SOUTH);

        // Aktualizacja tabeli
        shelterComboBox.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                AnimalShelter selectedShelter = shelterManager.getShelterByName((String) shelterComboBox.getSelectedItem());
                updateAnimalTable(animalTable, selectedShelter);
            }
        });

        frame.pack();
        frame.setVisible(true);
    }

    private void updateAnimalTable(JTable animalTable, AnimalShelter shelter) {
        AnimalTableModel animalTableModel = new AnimalTableModel(shelter.getAnimals());
        animalTable.setModel(animalTableModel);
    }
}
