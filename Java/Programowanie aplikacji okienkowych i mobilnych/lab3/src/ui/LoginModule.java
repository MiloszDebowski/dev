package ui;

import models.ShelterManager;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginModule {
    private ShelterManager shelterManager;

    public LoginModule(ShelterManager shelterManager) {
        this.shelterManager = shelterManager;
    }

    public void showLoginPanel() {
        JFrame frame = new JFrame("Logowanie");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);
        frame.setLayout(new BorderLayout());

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(3, 1));

        JLabel label = new JLabel("Wybierz typ konta:");
        panel.add(label);

        JButton adminButton = new JButton("Admin");
        JButton userButton = new JButton("Użytkownik");

        // Akcja dla administratora
        adminButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.dispose();  // Zamknij okno logowania
                AdminPanel adminPanel = new AdminPanel(shelterManager);
                adminPanel.showAdminPanel();
            }
        });

        // Akcja dla użytkownika
        userButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.dispose();  // Zamknij okno logowania
                UserPanel userPanel = new UserPanel(shelterManager);
                userPanel.showUserPanel();
            }
        });

        panel.add(adminButton);
        panel.add(userButton);

        frame.add(panel, BorderLayout.CENTER);
        frame.setVisible(true);
    }
}
