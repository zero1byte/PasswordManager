# Password Manager

**Password Manager** is a lightweight, terminal-based application designed to securely store and manage your passwords using RSA encryption. Developed using **C++** and **Bash scripting**, the application ensures that all your sensitive information remains encrypted and accessible only with your personal Master Key.

This project is ideal for privacy-conscious individuals who prefer storing passwords locally without relying on third-party services.

---

## Key Features

* All passwords are encrypted using the **RSA encryption algorithm**.
* A **Master Key** is created once during the initial installation.
* The Master Key is **never stored**—it must be entered every time to access stored passwords.
* Passwords are saved in a local JSON file in an encrypted format.
* A unique substring is prepended to each password before encryption to enhance validation logic.

---

## Why This Project?

While many password managers exist, most rely on cloud storage and require user registration. This project was created to serve users who:

* Want **full control** over their credentials.
* Prefer a **CLI-based solution** over graphical interfaces.
* Need a **portable, lightweight, and offline** password manager.
* Value **transparency** and wish to understand or modify the source code for their needs.

---

## Project Workflow

A complete visual representation of the project flow is available at the following link:

[View Flowchart on Canva](https://www.canva.com/design/DAGrvfaJ0fE/99wuFkAd2HsG7IAsTcumgQ/edit?utm_content=DAGrvfaJ0fE&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton)

---

## Installation Instructions

To set up and run the Password Manager on your local system:

```bash
# Clone the repository
git clone https://github.com/your-username/password-manager.git

# Navigate to the project directory
cd password-manager

# Give executable permission to necessary scripts
chmod +x install.sh
chmod +x run.sh

# Run the installer to generate your Master Key
./install.sh

# Start the Password Manager
./run.sh
```

During installation, you will be prompted to create your **Master Key**. This key is essential for encrypting and decrypting your stored passwords. If you forget your Master Key, **there is no recovery option**.

---

## How It Works

* When you add a password, it is prefixed with a specific substring, encrypted using RSA, and stored in a local JSON file.
* When you want to view your passwords (individual or all), you must enter the Master Key.
* The Master Key is used at runtime to decrypt the stored data securely.

---

## Technologies Used

* **C++** – for implementing core encryption logic and file operations.
* **Bash** – for creating the user interface and automating the workflow.
* **RSA Encryption** – to ensure that all stored data is securely encrypted.

---

## Contribution Guidelines

This is an open-source project, and contributions are highly encouraged. Whether you’re fixing a bug, improving the UI/UX, optimizing code, or adding new features—your help is welcome.

### How to Contribute

1. Fork the repository
2. Create a new branch (`git checkout -b feature-name`)
3. Make your changes
4. Commit your changes (`git commit -m 'Add new feature'`)
5. Push to the branch (`git push origin feature-name`)
6. Open a Pull Request

Your input can help make this project more robust, secure, and useful to others.

---

## License

This project is released under the [MIT License](). You are free to use, modify, and distribute this project as long as the original license is included.

---

If you find this tool helpful or want to contribute to its future, consider giving it a star or sharing it with others who value privacy-focused tools.

