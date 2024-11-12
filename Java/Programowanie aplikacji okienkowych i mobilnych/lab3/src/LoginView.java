import javax.swing.*;
import java.awt.*;

public class LoginView extends JFrame {
    private final ShelterManager shelterManager;

    public LoginView(ShelterManager shelterManager) {
        this.shelterManager = shelterManager;
        setTitle("Login");
        setSize(400, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);


        JPanel panel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(10, 10, 10, 10);


        JLabel label = new JLabel("Login:");
        label.setFont(new Font("Arial", Font.BOLD, 16));
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 2;
        gbc.anchor = GridBagConstraints.CENTER;
        panel.add(label, gbc);


        JButton userButton = new JButton("User");
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridwidth = 1;
        gbc.anchor = GridBagConstraints.EAST;
        panel.add(userButton, gbc);


        JButton adminButton = new JButton("Admin");
        gbc.gridx = 1;
        gbc.gridy = 1;
        gbc.anchor = GridBagConstraints.WEST;
        panel.add(adminButton, gbc);


        userButton.addActionListener(e -> {
            new UserView(shelterManager).setVisible(true);
            dispose();
        });
        adminButton.addActionListener(e -> {
            new AdminView(shelterManager).setVisible(true);
            dispose();
        });


        add(panel);
    }
}
